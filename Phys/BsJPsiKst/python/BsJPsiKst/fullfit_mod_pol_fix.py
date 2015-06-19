from ROOT import *
from math import *
gROOT.ProcessLine(".x $BSJPSIKSTROOT/src/AngJpsiKst_Swave.cxx++")
#gSystem.Load("AngJPsiKst_cxx")


print "Class for fitting polarization: AngularPDF"

#CHANNEL = "Bd"
#s_a = 5.

Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
CTheta = RooRealVar("CTheta","CTheta",-1.,1.)

 ## Acceptance
        
c1_psi = RooRealVar("c1_psi","c1_psi",-0.522)#,-0.488-s_a*0.014,-0.488+s_a*.014)
c2_psi = RooRealVar("c2_psi","c2_psi",-0.723)#,-0.642-s_a*0.022,-0.642+s_a*0.022)
c3_psi = RooRealVar("c3_psi","c3_psi",-0.190)#,-0.331-3*s_a,0.331+3*s_a)
c4_psi = RooRealVar("c4_psi","c4_psi",0.208)#,0.092-s_a*0.023,0.092+s_a*0.023)

        
y = RooRealVar("y","y",0.)#,0.,s_a*1.6e-04)
c5_psi = RooFormulaVar("c5_psi","c5_psi","y + (-1.-c1_psi-c2_psi-c3_psi-c4_psi)",RooArgList(y,c1_psi,c2_psi,c3_psi,c4_psi))
       

c1_theta = RooRealVar("c1_theta","c1_theta",0.)
c2_theta = RooRealVar("c2_theta","c2_theta",-0.1783)#,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)

c1_phi = RooRealVar("c1_phi","c1_phi",0.090)#,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
c2_phi = RooRealVar("c2_phi","c2_phi",2.019)#,1.958-s_a*0.029,1.958+s_a*0.029)
c3_phi = RooRealVar("c3_phi","c3_phi",.09)#,.25-s_a*0.048,.25+s_a*0.048)
c4_phi = RooRealVar("c4_phi","c4_phi",0.)#,0.5)
c5_phi = RooRealVar("c5_phi","c5_phi",0.)#,6.)
c6_phi = RooRealVar("c6_phi","c6_phi",0.)#-pi/2.,pi/2.)

### Acceptance Bs

c1_psi_Bs = RooRealVar("c1_psi_Bs","c1_psi_Bs",-0.502)#,-0.488-s_a*0.014,-0.488+s_a*.014)
c2_psi_Bs = RooRealVar("c2_psi_Bs","c2_psi_Bs",-0.578)#,-0.642-s_a*0.022,-0.642+s_a*0.022)
c3_psi_Bs = RooRealVar("c3_psi_Bs","c3_psi_Bs",-0.393)#,-0.331-s_a*.045,0.331+s_a*.045)
c4_psi_Bs = RooRealVar("c4_psi_Bs","c4_psi_Bs",0.0425)#,0.092-s_a*0.023,0.092+s_a*0.023)

        
y_Bs = RooRealVar("y_Bs","y_Bs",0.)#,0.,s_a*1.6e-04)
c5_psi_Bs = RooFormulaVar("c5_psi_Bs","c5_psi_Bs","y_Bs + (-1.-c1_psi_Bs-c2_psi_Bs-c3_psi_Bs-c4_psi_Bs)",RooArgList(y_Bs,c1_psi_Bs,c2_psi_Bs,c3_psi_Bs,c4_psi_Bs))
       

c1_theta_Bs = RooRealVar("c1_theta_Bs","c1_theta_Bs",0.)
c2_theta_Bs = RooRealVar("c2_theta_Bs","c2_theta_Bs",-0.1783)#,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)

c1_phi_Bs = RooRealVar("c1_phi_Bs","c1_phi_Bs",0.073)#,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
c2_phi_Bs = RooRealVar("c2_phi_Bs","c2_phi_Bs",2.106)#,1.958-s_a*0.029,1.958+s_a*0.029)
c3_phi_Bs = RooRealVar("c3_phi_Bs","c3_phi_Bs",.225)#,.25-s_a*0.048,.25+s_a*0.048)
c4_phi_Bs = RooRealVar("c4_phi_Bs","c4_phi_Bs",0.)#,0.5)
c5_phi_Bs = RooRealVar("c5_phi_Bs","c5_phi_Bs",0.)#,6.)
c6_phi_Bs = RooRealVar("c6_phi_Bs","c6_phi_Bs",0.)#-pi/2.,pi/2.)


class AngularPDF:
    def __init__(self, neim = "Bd"):

        


        ## Parameters of interest

        #self.A02 = RooRealVar("A02"+neim,"A02"+neim,0.,1.)
        self.A02 = RooRealVar("A02"+neim,"A02"+neim,0.,1.)
        self.x1 = RooRealVar("x1"+neim,"x1"+neim,0.,1.)

        self.x2 = RooRealVar("x2"+neim,"x2"+neim,0.,1.)
        self.Apa2 = RooFormulaVar("Apa2"+neim,"Apa2"+neim,"x1"+neim+"*(1-A02"+neim+")",RooArgList(self.x1,self.A02))#RooRealVar("As2","As2", 0.,.1)
        self.Ape2 = RooFormulaVar("Ape2"+neim,"Ape2"+neim,"x2"+neim+"*(1-A02"+neim+"-Apa2"+neim+")",RooArgList(self.x2,self.A02,self.Apa2))#RooRealVar("As2","As2", 0.,.1)
        self.As2 = RooFormulaVar("As2"+neim,"As2"+neim,"1-A02"+neim+"-Apa2"+neim+"-Ape2"+neim,RooArgList(self.A02,self.Apa2,self.Ape2))
        self.As = RooFormulaVar("As"+neim,"As"+neim,"sqrt(As2"+neim+")",RooArgList(self.As2))
        
        self.A0 = RooFormulaVar("A0"+neim,"A0"+neim,"sqrt(A02"+neim+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa"+neim,"Apa"+neim,"sqrt(Apa2"+neim+")",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape"+neim,"Ape"+neim,"sqrt(Ape2"+neim+")",RooArgList(self.Ape2))
        
     
        self.dpa = RooRealVar("dpa"+neim,"dpa" + neim,0.,2*pi)
        self.ds = RooRealVar("ds"+neim,"ds"+neim,0.,2*pi)


        

        ## Model

        # Signal

        self.sigmodel = AngJpsiKst_Swave("angular " + neim,"angular " + neim,CPsi,CTheta,Phi,self.A0,self.Apa,self.Ape,self.As,self.dpa,self.ds,
                                   c1_psi,c2_psi,c3_psi,c4_psi,c5_psi,c1_theta,c2_theta,c1_phi,c2_phi,c3_phi,c4_phi,c5_phi,c6_phi)

class AngularPDFMOD:
    def __init__(self, neim = "Bd"):

        


        ## Parameters of interest

        self.fL = RooRealVar("fL"+neim,"fL"+neim,0.507,0.2, .65)
        self.fpa = RooRealVar("fpa"+neim,"fpa"+neim,0.172,0.07, .35)
        self.As2 = RooRealVar("As2"+neim,"As2"+neim,0,1)
        self.A02 = RooFormulaVar("A02"+neim,"A02"+neim,"fL"+neim+"*(1-As2"+neim+")",RooArgList(self.fL,self.As2))
        self.Apa2 = RooFormulaVar("Apa2"+neim,"Apa2"+neim,"fpa"+neim+"*(1-As2"+neim+")",RooArgList(self.fpa,self.As2))#RooRealVar("As2","As2", 0.,.1)
        
        self.Ape2 = RooFormulaVar("Ape2"+neim,"Ape2"+neim,"(1-A02"+neim+"-Apa2"+neim+" - As2" + neim + ")",RooArgList(self.As2,self.A02,self.Apa2))#RooRealVar("As2","As2", 0.,.1)
        
        self.As = RooFormulaVar("As"+neim,"As"+neim,"sqrt(As2"+neim+")",RooArgList(self.As2))
        
        self.A0 = RooFormulaVar("A0"+neim,"A0"+neim,"sqrt(A02"+neim+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa"+neim,"Apa"+neim,"sqrt(Apa2"+neim+")",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape"+neim,"Ape"+neim,"sqrt(Ape2"+neim+")",RooArgList(self.Ape2))
        
     
        self.dpa = RooRealVar("dpa"+neim,"dpa" + neim, -pi,0)
        self.ds = RooRealVar("ds"+neim,"ds"+neim,0.,pi)

        self.sigmodel = AngJpsiKst_Swave("angular " + neim,"angular " + neim,CPsi,CTheta,Phi,self.A0,self.Apa,self.Ape,self.As,self.dpa,self.ds,
                                   c1_psi_Bs,c2_psi_Bs,c3_psi_Bs,c4_psi_Bs,c5_psi_Bs,c1_theta_Bs,c2_theta_Bs,c1_phi_Bs,c2_phi_Bs,c3_phi_Bs,c4_phi_Bs,c5_phi_Bs,c6_phi_Bs)

class AngularPDFMODBd:
    def __init__(self, neim = "Bd"):

        


        ## Parameters of interest

        self.fL = RooRealVar("fL"+neim,"fL"+neim,0.550,0.5, .6)
        self.fpa = RooRealVar("fpa"+neim,"fpa"+neim,0.240,0.210, .260)
        self.As2 = RooRealVar("As2"+neim,"As2"+neim,0,.2)
        self.A02 = RooFormulaVar("A02"+neim,"A02"+neim,"fL"+neim+"*(1-As2"+neim+")",RooArgList(self.fL,self.As2))
        self.Apa2 = RooFormulaVar("Apa2"+neim,"Apa2"+neim,"fpa"+neim+"*(1-As2"+neim+")",RooArgList(self.fpa,self.As2))#RooRealVar("As2","As2", 0.,.1)
        
        self.Ape2 = RooFormulaVar("Ape2"+neim,"Ape2"+neim,"(1-A02"+neim+"-Apa2"+neim+" - As2" + neim + ")",RooArgList(self.As2,self.A02,self.Apa2))#RooRealVar("As2","As2", 0.,.1)
        
        self.As = RooFormulaVar("As"+neim,"As"+neim,"sqrt(As2"+neim+")",RooArgList(self.As2))
        
        self.A0 = RooFormulaVar("A0"+neim,"A0"+neim,"sqrt(A02"+neim+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa"+neim,"Apa"+neim,"sqrt(Apa2"+neim+")",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape"+neim,"Ape"+neim,"sqrt(Ape2"+neim+")",RooArgList(self.Ape2))
        
     
        self.dpa = RooRealVar("dpa"+neim,"dpa" + neim,-pi,0)
        self.ds = RooRealVar("ds"+neim,"ds"+neim,0.,pi)

        self.sigmodel = AngJpsiKst_Swave("angular " + neim,"angular " + neim,CPsi,CTheta,Phi,self.A0,self.Apa,self.Ape,self.As,self.dpa,self.ds,
                                   c1_psi,c2_psi,c3_psi,c4_psi,c5_psi,c1_theta,c2_theta,c1_phi,c2_phi,c3_phi,c4_phi,c5_phi,c6_phi)
        


# Background

c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg",-4.38046e-01, -1,1)
c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",1.24342e-01,0.,.3)
c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",4.63368e-02,-0.1,.1)

## c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg", 1.1,20.)
## c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",0.01,6.)
## c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",0, pi)
        

ncb = RooRealVar("ncb","ncb",1)
a1_cb = RooRealVar("a1_cb","a1_cb",2.8)#0.5,3)
a2_cb = RooRealVar("a2_cb","a2_cb",2.3)#0.5,3)

kbkg = RooRealVar("k","k",-1e-03,-1,0)

fsig = RooRealVar("fsig","fsig",0.,1)




if __name__=="__main__":


    f=TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")
    t2=f.Get("T/T")


    cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "

    
    cuts += "&& kaon_pt>500 && pion_pt>500"
    
        
    cuts += "&& abs(Mjpsik-5279)>60"
    cuts += "&& abs(KstMass-896)<40"

    trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

    cuts += " && "+ trigger


    f2=TFile("nada.root","recreate")
    t=t2.CopyTree(cuts+"&& GL11sb.>0.2")

    

    Mass = RooRealVar("Bmass_JC","Bmass_JC",5150, t.GetMaximum("Bmass_JC"))
    AngBd = AngularPDFMODBd()
    
    
    AngBs = AngularPDFMOD("Bs")
    
    psibkg = RooPolynomial("psibkg","psibkg",CPsi,RooArgList(c1_psi,c2_psi,c3_psi,c4_psi,c5_psi))
    thetabkg = RooPolynomial("thetabkg","thetabkg",CTheta,RooArgList(c1_theta,c2_theta))
    phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi_bkg*PhiP + c2_phi_bkg*PhiP*PhiP + c3_phi_bkg*PhiP*PhiP*PhiP",RooArgList(Phi,c1_phi_bkg,c2_phi_bkg,c3_phi_bkg))
    #phibkg = RooGenericPdf("phibkg","phibkg","c1_phi_bkg +sin(c2_phi_bkg*PhiP + c3_phi_bkg)",RooArgList(Phi,c1_phi_bkg,c2_phi_bkg,c3_phi_bkg))

    massbkg = RooExponential("bkg", "Exponential background pdf", Mass, kbkg)
    bkgmodel = RooProdPdf("bkgmodel","bkgmodel",RooArgList(psibkg,thetabkg,phibkg,massbkg))

    mean1 = RooRealVar("mean1","mean1",5279, 5276,5280)
    sigma1 = RooRealVar("sigma1","sigma1", 6.,10.)
    
    delta_s = RooRealVar("delta_s", "delta_s", 2.,1.,15.)
    delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
    sigma2 = RooFormulaVar("sigma2","sigma2", "sigma1 + delta_s" ,RooArgList(sigma1,delta_s) )
    mean2 = RooFormulaVar("mean2","mean2", "mean1 + delta_m" ,RooArgList(mean1,delta_m) )
    sigb11  = RooCBShape("SigmodelB11","SigmodelB11", Mass, mean1, sigma1, a1_cb, ncb)
    sigb12  = RooCBShape("SigmodelB12","SigmodelB12", Mass, mean1, sigma2, a2_cb, ncb)
    sigb21  = RooCBShape("SigmodelB21","SigmodelB21", Mass, mean2, sigma1, a1_cb, ncb)
    sigb22  = RooCBShape("SigmodelB22","SigmodelB22", Mass, mean2, sigma2, a2_cb, ncb)
    fsmres = RooRealVar("f small res","f small res",0.8, 0., 1.)
    sigB1  = RooAddPdf("SigmodelB1","SigmodelB1", sigb11, sigb12, fsmres)
    sigB2  = RooAddPdf("SigmodelB2","SigmodelB2", sigb21, sigb22, fsmres)

    SigBs = RooProdPdf("Bs pdf", "Bs pdf",RooArgList(AngBs.sigmodel,sigB2))
    SigBd = RooProdPdf("Bd pdf", "Bd pdf",RooArgList(AngBd.sigmodel,sigB1))

    fBs = RooRealVar("fBs","fBs", 1e-02,1e-03,.1)
    
    nd = RooRealVar("nBd","nBd", 0.5*t.GetEntries(),t.GetEntries())
    ns = RooFormulaVar("nBs","nBs", "fBs*nBd",RooArgList(fBs,nd))
    nbkg = RooRealVar("n nbkg","n bkg", 0.,0.1*t.GetEntries())

    model = RooAddPdf("model","model",RooArgList(SigBs,SigBd,bkgmodel),RooArgList(ns,nd,nbkg))
    dataset = RooDataSet("data","data",t,RooArgSet(CPsi,CTheta,Phi, Mass))
    
    fitres = model.fitTo(dataset,RooFit.Minos(1),RooFit.Save())


    Mass.setRange("ref",Mass.getMin(),Mass.getMax())
    CPsi.setRange("ref",CPsi.getMin(),CPsi.getMax())
    CTheta.setRange("ref",CTheta.getMin(),CTheta.getMax())
    Phi.setRange("ref",Phi.getMin(),Phi.getMax())


    model.fixCoefRange("ref")
    
    
def replot(rangename,nbins):
    

    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
#     model.paramOn(cpsif)
    cpsif.Draw()

    cv3.cd(2)
    cthf = CTheta.frame()
    RooAbsData.plotOn(dataset,cthf,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cthf.Draw()

    cv3.cd(3)
    cphif = Phi.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bs pdf"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bd pdf"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cphif.Draw()

    return cv3, cphif,cthf, cpsif

    
def plot_mass(nbins):
    

    cv3 = TCanvas()
    
    
    cphif = Mass.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
    model.plotOn(cphif)
    model.plotOn(cphif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cphif,RooFit.Components("Bs pdf"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cphif,RooFit.Components("Bd pdf"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    #model.plotOn(cphif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    cphif.Draw()

    return cv3, cphif#,cthf, cpsif

ratioBs = RooFormulaVar("rBs","rBs", "nBs/nBd", RooArgList(ns,nd))
print "NBs/NBd = ", ratioBs.getVal(), "+/-", ratioBs.getPropagatedError(fitres)
print "Apa2 Bd = ", AngBd.Apa2.getVal(), "+/-", AngBd.Apa2.getPropagatedError(fitres)
print "Ape2 Bd = ", AngBd.Ape2.getVal(), "+/-", AngBd.Ape2.getPropagatedError(fitres)
print "As2 Bd = ", AngBd.As2.getVal(), "+/-", AngBd.As2.getPropagatedError(fitres)
print "Apa2 Bs = ", AngBs.Apa2.getVal(), "+/-", AngBs.Apa2.getPropagatedError(fitres)
print "Ape2 Bs = ", AngBs.Ape2.getVal(), "+/-", AngBs.Ape2.getPropagatedError(fitres)
print "As2 Bs = ", AngBs.As2.getVal(), "+/-", AngBs.As2.getPropagatedError(fitres)

### Renormalized to 1

rA02d = RooFormulaVar("rA02d","rA02d","A02Bd/(A02Bd+Apa2Bd+Ape2Bd)",RooArgList(AngBd.A02,AngBd.Apa2,AngBd.Ape2))
rApa2d = RooFormulaVar("rApa2d","rApa2d","Apa2Bd/(A02Bd+Apa2Bd+Ape2Bd)",RooArgList(AngBd.A02,AngBd.Apa2,AngBd.Ape2))
rApe2d = RooFormulaVar("rApe2d","rApe2d","Ape2Bd/(A02Bd+Apa2Bd+Ape2Bd)",RooArgList(AngBd.A02,AngBd.Apa2,AngBd.Ape2))
rA02s = RooFormulaVar("rA02s","rA02s","A02Bs/(A02Bs+Apa2Bs+Ape2Bs)",RooArgList(AngBs.A02,AngBs.Apa2,AngBs.Ape2))
rApa2s = RooFormulaVar("rApa2s","rApa2s","Apa2Bs/(A02Bs+Apa2Bs+Ape2Bs)",RooArgList(AngBs.A02,AngBs.Apa2,AngBs.Ape2))
rApe2s = RooFormulaVar("rApe2s","rApe2s","Ape2Bs/(A02Bs+Apa2Bs+Ape2Bs)",RooArgList(AngBs.A02,AngBs.Apa2,AngBs.Ape2))
print "RENORMALZED"
print "r Apa2 Bd = ", rApa2d.getVal(), "+/-", rApa2d.getPropagatedError(fitres)
print "r Ape2 Bd = ", rApe2d.getVal(), "+/-", rApe2d.getPropagatedError(fitres)
print "r A02 Bd = ", rA02d.getVal(), "+/-", rA02d.getPropagatedError(fitres)
print "r Apa2 Bs = ", rApa2s.getVal(), "+/-", rApa2s.getPropagatedError(fitres)
print "r Ape2 Bs = ", rApe2s.getVal(), "+/-", rApe2s.getPropagatedError(fitres)
print "r A02 Bs = ", rA02s.getVal(), "+/-", rA02s.getPropagatedError(fitres)


Mass.setRange("Bs_range",5366.3-25,5366.3+25)
Mass.setRange("Bd_range",5279.5-25,5279.5+25)

cv1, psif1, thf1, phif1 = replot("Bd_range",50)
cv2, psif2, thf2, phif2 = replot("Bs_range",10)
cv3, mf = plot_mass(100)

cv1.SaveAs("Bs_fit_FL_MC11MC11_pol.root")
cv2.SaveAs("Bs_fit_FL_MC11MC11_pol.root")
cv3.SaveAs("Mass_fit_FL_MC11MC11_pol.root")
