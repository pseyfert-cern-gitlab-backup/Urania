from ROOT import *
from math import *
gROOT.ProcessLine(".x $BSJPSIKSTROOT/src/AngJpsiKst_Swave.cxx++")
#gSystem.Load("AngJPsiKst_cxx")


print "Class for fitting polarization: AngularPDF"

#faccBd = TFile("HistoAcceptanceBdMC11.root")
faccBd = TFile("Histo_ACC_MC10.root")
accBd = faccBd.Get("A")
#accBd = faccBd.Get("acc3D")
accBd.SetNameTitle("acc3D_Bd","acc3D_Bd")
accBd.Scale(1./accBd.GetSum())

faccBs = TFile("HistoAcceptanceBsMC11.root")
accBs = faccBs.Get("acc3D")
accBs.SetNameTitle("acc3D_Bs","acc3D_Bs")
accBs.Scale(1./accBs.GetSum())

CHANNEL = "Bd"
if CHANNEL == "Bd":acc = accBd
else: acc = accBs

databinned = acc.Clone()
N= 0

for i in range(acc.GetNbinsX()):
    for j in range(acc.GetNbinsY()):
        for k in range(acc.GetNbinsZ()):
            if acc.GetBinContent(i+1,j+1,k+1) ==0 :
                x=  acc.GetXaxis().GetBinCenter(i+1)
                
                #$acc.SetBinContent(i+1,j+1,k+1, 1e-12)
            databinned.SetBinContent(i+1,j+1,k+1, 0)



s_a = 5.
class AngularPDF:
    def __init__(self,acc):

        self.Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
        self.CPsi = RooRealVar("CPsi","CPsi",-1.,0.6)#1) 
        self.CTheta = RooRealVar("CTheta","CTheta",-1.,1.)


        
        ## Parameters of interest
        self.fL = RooRealVar("fL","fL",0.550,0.5, .7)
        self.fpa = RooRealVar("fpa","fpa",0.240,0.10, .30)
        self.As2 = RooRealVar("As2","As2",0,.2)
        self.A02 = RooFormulaVar("A02","A02","fL"+"*(1-As2"+")",RooArgList(self.fL,self.As2))
        self.Apa2 = RooFormulaVar("Apa2","Apa2","fpa"+"*(1-As2"+")",RooArgList(self.fpa,self.As2))#RooRealVar("As2","As2", 0.,.1)
        
        self.Ape2 = RooFormulaVar("Ape2","Ape2","(1-A02"+"-Apa2"+" - As2" +  ")",RooArgList(self.As2,self.A02,self.Apa2))#RooRealVar("As2","As2", 0.,.1)
        
        self.As = RooFormulaVar("As","As","sqrt(As2"+")",RooArgList(self.As2))
        
        self.A0 = RooFormulaVar("A0","A0","sqrt(A02"+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa","Apa","sqrt(Apa2"+")",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape","Ape","sqrt(Ape2"+")",RooArgList(self.Ape2))

        #self.As = RooFormulaVar("As","As","sqrt(1-A02-Apa2-Ape2)",RooArgList(self.A02,self.Apa2,self.Ape2))


        

        self.dpa = RooRealVar("dpa","dpa",-pi,0)#2*pi)
        self.ds = RooRealVar("ds","ds",0.,pi)


        ## Acceptance
        
        self.c1_psi = RooRealVar("c1_psi","c1_psi",0)#,-0.488-s_a*0.014,-0.488+s_a*.014)
        self.c2_psi = RooRealVar("c2_psi","c2_psi",0)#,-0.642-s_a*0.022,-0.642+s_a*0.022)
        self.c3_psi = RooRealVar("c3_psi","c3_psi",0)#,-0.331-3*s_a,0.331+3*s_a)
        self.c4_psi = RooRealVar("c4_psi","c4_psi",0)#,0.092-s_a*0.023,0.092+s_a*0.023)

        
        self.y = RooRealVar("y","y",1)#,0.,s_a*1.6e-04)
        self.c5_psi = RooFormulaVar("c5_psi","c5_psi","y + (-1.-c1_psi-c2_psi-c3_psi-c4_psi)",RooArgList(self.y,self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi))
        # self.c5_psi = RooRealVar("c5_psi","c5_psi",0.,5.)

        self.c1_theta = RooRealVar("c1_theta","c1_theta",0)#-1.,1.)
        self.c2_theta = RooRealVar("c2_theta","c2_theta",0)#-0.1783,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)

        self.c1_phi = RooRealVar("c1_phi","c1_phi",0)#0.0784,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
        self.c2_phi = RooRealVar("c2_phi","c2_phi",0)#1.958,1.958-s_a*0.029,1.958+s_a*0.029)
        self.c3_phi = RooRealVar("c3_phi","c3_phi",0)#.25,.25-s_a*0.048,.25+s_a*0.048)
        self.c4_phi = RooRealVar("c4_phi","c4_phi",0)#0.,0.5)
        self.c5_phi = RooRealVar("c5_phi","c5_phi",0)#0.,6.)
        self.c6_phi = RooRealVar("c6_phi","c6_phi",0)#-pi/2.,pi/2.)
        

        ## Model

        # Signal

        self.sigmodel_phys = AngJpsiKst_Swave("sigmodel","sigmodel",self.CPsi,self.CTheta,self.Phi,self.A0,self.Apa,self.Ape,self.As,self.dpa,self.ds,
                                   self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi,self.c1_theta,self.c2_theta,self.c1_phi,self.c2_phi,self.c3_phi,self.c4_phi,self.c5_phi,self.c6_phi)

        
        self.acc_histo = RooDataHist("acc_histo_","acc_histo_" ,RooArgList(self.CPsi,self.CTheta,self.Phi),acc)

        self.acceptance = RooHistPdf("acceptance_","acceptance_" ,RooArgSet(self.CPsi,self.CTheta,self.Phi),self.acc_histo)

        self.sigmodel = self.sigmodel_phys# RooProdPdf("angular ","angular " ,self.sigmodel_phys, self.acceptance)


        # Background
        #Polinomios
        self.c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg",-4.38046e-01)
        self.c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",1.24342e-01)
        self.c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",4.63368e-02)

        # Seno
#         self.c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg",2.42)
#         self.c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",2.11)
#         self.c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",1.09)


        self.psibkg = RooPolynomial("psibkg","psibkg",self.CPsi,RooArgList(self.c1_psi,self.c2_psi,self.c3_psi,self.c4_psi,self.c5_psi))

        self.thetabkg = RooPolynomial("thetabkg","thetabkg",self.CTheta,RooArgList(self.c1_theta,self.c2_theta))

        self.phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi_bkg*PhiP + c2_phi_bkg*PhiP*PhiP + c3_phi_bkg*PhiP*PhiP*PhiP",RooArgList(self.Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg))
#         self.phibkg = RooGenericPdf("phibkg","phibkg","c1_phi_bkg +sin(c2_phi_bkg*PhiP + c3_phi_bkg)",RooArgList(self.Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg))

        self.bkgmodel = RooProdPdf("bkgmodel","bkgmodel",RooArgList(self.psibkg,self.thetabkg,self.phibkg))

        self.fsig = RooRealVar("fsig","fsig",0.,1)
        self.model = RooAddPdf("model","model",self.sigmodel,self.bkgmodel,self.fsig)



if __name__=="__main__":


    f=TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")
    t2=f.Get("T/T")


    cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
#     cuts += "&& Bmass_JC>5150 && Bmass_JC<5800"
#     cuts += "&& abs(Bmass_JC-5279.5)<25"
    
    cuts += "&& kaon_pt>500 && pion_pt>500"
    if CHANNEL =="Bs":
        cuts += "&& abs(Bmass_JC-5366.3)<25"
        _fsig = 1-0.13
        nbins = 9
    else:
        cuts += "&& abs(Bmass_JC-5279)<25"
        _fsig = 1-2.1e-03
        nbins = 50
        
    cuts += "&& abs(Mjpsik-5279)>60"
    cuts += "&& abs(KstMass-896)<40"

    trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

    cuts += " && "+ trigger


    f2=TFile("nada.root","recreate")
    t=t2.CopyTree(cuts+"&& GL11sb.>0.2")
    for entry in t:
        databinned.Fill(entry.CPsi, entry.CTheta, entry.PhiP)
    
    fit = AngularPDF(acc)

    fit.c1_psi.setVal(0)
    fit.c2_psi.setVal(0)#-7.22515e-01)
    fit.c3_psi.setVal(0)#-1.87868e-01)
    fit.c4_psi.setVal(0)#2.07842e-01)
    fit.y.setVal(1)#.20308e-05)
    fit.c1_theta.setVal(0)
    fit.c2_theta.setVal(0)#-1.78189e-01)
    fit.c1_phi.setVal(0)#9.04100e-02)
    fit.c2_phi.setVal(0)#2.01930e+00)
    fit.c3_phi.setVal(0)#8.70169e-02)


    fit.c4_phi.setVal(0.)
    fit.c6_phi.setVal(0.)
    fit.c5_phi.setVal(0.)


    fit.c1_psi.setConstant(1)
    fit.c2_psi.setConstant(1)
    fit.c3_psi.setConstant(1)
    fit.c4_psi.setConstant(1)
    fit.y.setConstant(1)
    fit.c1_theta.setConstant(1)
    fit.c2_theta.setConstant(1)
    fit.c1_phi.setConstant(1)
    fit.c2_phi.setConstant(1)
    fit.c3_phi.setConstant(1)
    fit.c4_phi.setConstant(1)
    fit.c6_phi.setConstant(1)
    fit.c5_phi.setConstant(1)
    fit.fsig.setVal(_fsig)
    fit.fsig.setConstant(1)
    
    
                    
    #BREAK
    
    eff0 = acc.GetSumOfWeights()*1./(acc.GetNbinsX()*acc.GetNbinsY()*acc.GetNbinsZ())
    dataset = RooDataHist("acc_histo_","acc_histo_" ,RooArgList(fit.CPsi,fit.CTheta,fit.Phi),databinned)
    from SomeUtils.alyabar import *
    for i in range(acc.GetNbinsX()):
        for j in range(acc.GetNbinsY()):
            for k in range(acc.GetNbinsZ()):
                
                x= acc.GetXaxis().GetBinCenter(i+1)
                y=  acc.GetYaxis().GetBinCenter(j+1)
                z=  acc.GetZaxis().GetBinCenter(k+1)
                fit.CPsi.setVal(x), fit.CTheta.setVal(y), fit.Phi.setVal(z)
                eff = acc.GetBinContent(i+1,j+1,k+1)/eff0
                seff = acc.GetBinError(i+1,j+1,k+1)/eff0
                Ndata = databinned.GetBinContent(i+1,j+1,k+1)
                ndp, ndn = poissonErrors(Ndata)
                if eff != 0 and Ndata != 0:
                    wght = Ndata*1./eff
                    swghtp = sqrt( (seff/eff) **2 + (ndp/Ndata)**2)*wght
                    swghtn = sqrt( (seff/eff) **2 + (ndn/Ndata)**2)*wght
                else:
                    wght = 0.00000000
                    swghtp = 2
                    swghtn = 0
                swght = 1/sqrt(2)* sqrt(swghtp**2+swghtn**2)
                dataset.set(RooArgSet(fit.CPsi,fit.CTheta,fit.Phi),wght,swght)#, swghtp)
                    
    #fr = fit.CPsi.frame()
    #dataset.plotOn(fr)
    #fr.Draw()
   # dataset = RooDataSet("data","data",t,RooArgSet(fit.CPsi,fit.CTheta,fit.Phi))
   # BREAK
    fitres = fit.model.fitTo(dataset,RooFit.Minos(1),RooFit.Save(),RooFit.SumW2Error( kTRUE ))
    ## Next = RooRealVar("Next","Next", 0, 30000.)
##     chi2model = RooExtendPdf("chi2M","chi2M",fit.model,Next)
           
##     chi2 = RooChi2Var("chi2","chi2", chi2model, dataset, RooFit.DataError(RooAbsData.SumW2),RooFit.Extended(kTRUE))
##     m = RooMinuit(chi2)
##     m.migrad()
##     m.hesse()
##     m.minos()
    

#     nbins = 50

   

    ## Apa2 = fit.Apa2.getVal()
##     Apa2err = fit.Apa2.getPropagatedError(fitres)
##     Ape2 = fit.Ape2.getVal()
##     Ape2err = fit.Ape2.getPropagatedError(fitres)
##     As2 = fit.As.getVal()**2
##     As2err = 2*fit.As.getVal()*fit.As.getPropagatedError(fitres)



##     print "Apa2 = %.6f"%Apa2+" + %.6f"%Apa2err
##     print "Ape2 = %.6f"%Ape2," + %.6f"%Ape2err
##     print "As2 = %.6f"%As2," + %.6f"%As2err


##     fl = RooFormulaVar("fl","fl","A02/(A02+Apa2+Ape2)",RooArgList(fit.A02,fit.Apa2,fit.Ape2))
##     flerr = fl.getPropagatedError(fitres)
##     print "f_L = %.3f"%fl.getVal()," + %.3f"%flerr
##     fpa = RooFormulaVar("fpa","fpa","Apa2/(A02+Apa2+Ape2)",RooArgList(fit.A02,fit.Apa2,fit.Ape2))
##     fpaerr = fpa.getPropagatedError(fitres)
##     print "f_pa = %.3f"%fpa.getVal()," + %.3f"%fpaerr

def replot(nbins):
    

    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = fit.CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif, RooFit.DataError(RooAbsData.SumW2))
    fit.model.plotOn(cpsif)
    fit.model.plotOn(cpsif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    fit.model.plotOn(cpsif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    fit.model.paramOn(cpsif)
    cpsif.Draw()

    cv3.cd(2)
    cthf = fit.CTheta.frame()
    RooAbsData.plotOn(dataset,cthf, RooFit.DataError(RooAbsData.SumW2))
    fit.model.plotOn(cthf)
    fit.model.plotOn(cthf,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    fit.model.plotOn(cthf,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    cthf.Draw()

    cv3.cd(3)
    cphif = fit.Phi.frame()
    RooAbsData.plotOn(dataset,cphif, RooFit.DataError(RooAbsData.SumW2))
    fit.model.plotOn(cphif)
    fit.model.plotOn(cphif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    fit.model.plotOn(cphif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    cphif.Draw()

    return cv3, cphif,cthf, cpsif


