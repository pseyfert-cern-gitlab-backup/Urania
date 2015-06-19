from ROOT import *
from math import *
gROOT.ProcessLine(".x $BSJPSIKSTROOT/src/AngJPsiKst.cxx++")
gROOT.ProcessLine(".x $BSJPSIKSTROOT/src/AngJpsiKst_Swave.cxx++")
#gSystem.Load("AngJPsiKst_cxx")


print "Class for fitting polarization: AngularPDF"

s_a = 3.


cat =  RooCategory("sample", "sample")
cat.defineType("MC")
cat.defineType("Data")


Mass = RooRealVar("Bmass_JC","Bmass_JC",5150,5800)
Phi = RooRealVar("PhiP","PhiP",-1.*pi,pi)
CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
CTheta = RooRealVar("CTheta","CTheta",-1.,1.)

 ## Acceptance Bd 
        
c1_psi = RooRealVar("c1_psi","c1_psi",-0.488,-0.488-s_a*0.014,-0.488+s_a*.014)
c2_psi = RooRealVar("c2_psi","c2_psi",-0.642,-0.642-s_a*0.022,-0.642+s_a*0.022)
c3_psi = RooRealVar("c3_psi","c3_psi",-0.331,-0.331-s_a*.045,0.331+s_a*.045)
c4_psi = RooRealVar("c4_psi","c4_psi",0.092,0.092-s_a*0.023,0.092+s_a*0.023)

        
y = RooRealVar("y","y",0.)#,0.,s_a*1.6e-04)
c5_psi = RooFormulaVar("c5_psi","c5_psi","y + (-1.-c1_psi-c2_psi-c3_psi-c4_psi)",RooArgList(y,c1_psi,c2_psi,c3_psi,c4_psi))
       

c1_theta = RooRealVar("c1_theta","c1_theta",0.)
c2_theta = RooRealVar("c2_theta","c2_theta",-0.1783,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)

c1_phi = RooRealVar("c1_phi","c1_phi",0.0784,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
c2_phi = RooRealVar("c2_phi","c2_phi",1.958,1.958-s_a*0.029,1.958+s_a*0.029)
c3_phi = RooRealVar("c3_phi","c3_phi",.25,.25-s_a*0.048,.25+s_a*0.048)
c4_phi = RooRealVar("c4_phi","c4_phi",0.)#,0.5)
c5_phi = RooRealVar("c5_phi","c5_phi",0.)#,6.)
c6_phi = RooRealVar("c6_phi","c6_phi",0.)#-pi/2.,pi/2.)



class BsJpsiKstFitter:

    def __init__(self,name="BsKstKst"):



        self.fs = RooRealVar("fs","fs", 1e-02,1e-04,0.1)
        #self.ns = RooFormulaVar("nBs","nBs","fs*nBd",RooArgList(self.fBs,self.nd))
        self.nd = RooRealVar("nBd","nBd", 1.37048e+04,0.37048e+04,2.37048e+04)
        self.ns = RooFormulaVar("nBs","nBs","fs*nBd",RooArgList(self.fs,self.nd))
        self.nbkg = RooRealVar("nbkg","n bkg",1.17920e+02 , 0.17920e+02 ,2.17920e+02 )

        
        ## Parameters of interest
        
        self.A02_Bd = RooRealVar("A02_Bd","A02_Bd",0.,1.)
        self.x1_Bd = RooRealVar("x1_Bd","x1_Bd",0.,1.)
        self.x2_Bd = RooRealVar("x2_Bd","x2_Bd",0.,1.)

        self.Apa2_Bd = RooFormulaVar("Apa2_Bd","Apa2_Bd","x1_Bd*(1-A02_Bd)",RooArgList(self.x1_Bd,self.A02_Bd))#RooRealVar("As2","As2", 0.,.1)
        self.Ape2_Bd = RooFormulaVar("Ape2_Bd","Ape2_Bd","x2_Bd*(1-A02_Bd-Apa2_Bd)",RooArgList(self.x2_Bd,self.A02_Bd,self.Apa2_Bd))#RooRealVar("As2","As2", 0.,.1)
        self.As2_Bd = RooFormulaVar("As2_Bd","As2_Bd","1-A02_Bd-Apa2_Bd-Ape2_Bd",RooArgList(self.A02_Bd,self.Apa2_Bd,self.Ape2_Bd))

        self.As_Bd = RooFormulaVar("As_Bd","As_Bd","sqrt(As2_Bd)",RooArgList(self.As2_Bd))
        self.A0_Bd = RooFormulaVar("A0_Bd","A0_Bd","sqrt(A02_Bd)",RooArgList(self.A02_Bd))
        self.Apa_Bd = RooFormulaVar("Apa_Bd","Apa_Bd","sqrt(Apa2_Bd)",RooArgList(self.Apa2_Bd))
        self.Ape_Bd = RooFormulaVar("Ape_Bd","Ape_Bd","sqrt(Ape2_Bd)",RooArgList(self.Ape2_Bd))
        
     
        self.dpa_Bd = RooRealVar("dpa_Bd","dpa_Bd",0.,2*pi)
        self.ds_Bd = RooRealVar("ds_Bd","ds_Bd",0.,2*pi)


        #self.A02_ratio = RooRealVar("A02_ratio","A02_ratio",0.,2.)
        self.x1_Bs = RooRealVar("x1_Bs","x1_Bs",0.,1.)
        self.x2_Bs = RooRealVar("x2_Bs","x2_Bs",0.,1.)
        

        self.A02_Bs = RooRealVar("A02_Bs","A02_Bs",0,1)

        self.Apa2_ratio = RooFormulaVar("Apa2_ratio","Apa2_ratio","x1_Bs*(1-A02_Bs)/Apa2_Bd",
                                        RooArgList(self.x1_Bs,self.A02_Bs,self.Apa2_Bd))

        self.Apa2_Bs = RooFormulaVar("Apa2_Bs","Apa2_Bs","Apa2_ratio*Apa2_Bd",RooArgList(self.Apa2_ratio,self.Apa2_Bd))

        
        self.Ape2_ratio = RooFormulaVar("Ape2_ratio","Ape2_ratio","x2_Bs*(1-A02_Bs-Apa2_Bs)/Ape2_Bd",
                                  RooArgList(self.x2_Bs,self.A02_Bs,self.Apa2_Bs,self.Ape2_Bd))
        

        self.Ape2_Bs = RooFormulaVar("Ape2_Bs","Ape2_Bs","Ape2_ratio*Ape2_Bd",RooArgList(self.Ape2_ratio,self.Ape2_Bd))



        self.As2_ratio = RooFormulaVar("As2_ratio","As2_ratio","(1-A02_Bs-Apa2_Bs-Ape2_Bs)/As2_Bd",
                                 RooArgList(self.A02_Bs,self.Apa2_Bs,self.Ape2_Bs,self.As2_Bd))
        

        self.As2_Bs = RooFormulaVar("As2_Bs","As2_Bs","As2_ratio*As2_Bd",RooArgList(self.As2_ratio,self.As2_Bd))

        
        self.As_Bs = RooFormulaVar("As_Bs","As_Bs","sqrt(As2_Bs)",RooArgList(self.As2_Bs))
        self.A0_Bs = RooFormulaVar("A0_Bs","A0_Bs","sqrt(A02_Bs)",RooArgList(self.A02_Bs))
        self.Apa_Bs = RooFormulaVar("Apa_Bs","Apa_Bs","sqrt(Apa2_Bs)",RooArgList(self.Apa2_Bs))
        self.Ape_Bs = RooFormulaVar("Ape_Bs","Ape_Bs","sqrt(Ape2_Bs)",RooArgList(self.Ape2_Bs))
        
     
        self.dpa_Bs = RooRealVar("dpa_Bs","dpa_Bs",0.,2*pi)
        self.ds_Bs = RooRealVar("ds_Bs","ds_Bs",0.,2*pi)



        self.angular_Bd = AngJpsiKst_Swave("angular_Bd","angular_Bd",CPsi,CTheta,Phi,self.A0_Bd,self.Apa_Bd,self.Ape_Bd,self.As_Bd,self.dpa_Bd,self.ds_Bd,
                                   c1_psi,c2_psi,c3_psi,c4_psi,c5_psi,c1_theta,c2_theta,c1_phi,c2_phi,c3_phi,c4_phi,c5_phi,c6_phi)


        self.angular_Bs = AngJpsiKst_Swave("angular_Bs","angular_Bs",CPsi,CTheta,Phi,self.A0_Bs,self.Apa_Bs,self.Ape_Bs,self.As_Bs,self.dpa_Bs,self.ds_Bs,
                                   c1_psi,c2_psi,c3_psi,c4_psi,c5_psi,c1_theta,c2_theta,c1_phi,c2_phi,c3_phi,c4_phi,c5_phi,c6_phi)





        self.AddBkgModel()
        self.AddMassModel()

        
        self.Bdmodel = RooProdPdf("Bdmodel","Bdmodel",RooArgList(self.angular_Bd,self.sigB1))
        self.Bsmodel = RooProdPdf("Bsmodel","Bsmodel",RooArgList(self.angular_Bs,self.sigB2))


        #self.model = self.angular_Bd#Bdmodel
        self.model = RooAddPdf("model_"+name,"model "+name,RooArgList(self.Bsmodel,self.Bdmodel,self.bkgmodel),RooArgList(self.ns,self.nd,self.nbkg))


    def AddBkgModel(self):
        
        
        # Background
        
        #self.c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg",-4.38046e-01, -1,1)
        #self.c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",1.24342e-01,-1,1)
        #self.c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",4.63368e-02,-1,1)

        self.c1_phi_bkg = RooRealVar("c1_phi_bkg","c1_phi_bkg", 1.5,10.)
        self.c2_phi_bkg = RooRealVar("c2_phi_bkg","c2_phi_bkg",0.1,5.)
        self.c3_phi_bkg = RooRealVar("c3_phi_bkg","c3_phi_bkg",-pi, pi)
        
        self.psibkg = RooPolynomial("psibkg","psibkg",CPsi,RooArgList(c1_psi,c2_psi,c3_psi,c4_psi,c5_psi))
        self.thetabkg = RooPolynomial("thetabkg","thetabkg",CTheta,RooArgList(c1_theta,c2_theta))
        #self.phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi_bkg*PhiP + c2_phi_bkg*PhiP*PhiP + c3_phi_bkg*PhiP*PhiP*PhiP",RooArgList(Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg))
        self.phibkg = RooGenericPdf("phibkg","phibkg","c1_phi_bkg +sin(c2_phi_bkg*PhiP + c3_phi_bkg)",RooArgList(Phi,self.c1_phi_bkg,self.c2_phi_bkg,self.c3_phi_bkg))
        
        
        self.kbkg = RooRealVar("k","k",-1e-03,-1,0)
        
        self.massbkg = RooExponential("bkg", "Exponential background pdf", Mass, self.kbkg)
        
        self.bkgmodel = RooProdPdf("bkgmodel","bkgmodel",RooArgList(self.psibkg,self.thetabkg,self.phibkg,self.massbkg))
        
        
        
        
        
    def AddMassModel(self):
        
        self.ncb = RooRealVar("ncb","ncb",1)
        self.a1_cb = RooRealVar("a1_cb","a1_cb",2.8)#0.5,3)
        self.a2_cb = RooRealVar("a2_cb","a2_cb",2.3)#0.5,3)
        
        
        self.mean1 = RooRealVar("mean1","mean1",5279, 5276,5280)
        self.sigma1 = RooRealVar("sigma1","sigma1", 6.,10.)
        
        self.delta_s = RooRealVar("delta_s", "delta_s", 2.,1.,15.)
        self.delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
        self.sigma2 = RooFormulaVar("sigma2","sigma2", "sigma1 + delta_s" ,RooArgList(self.sigma1,self.delta_s) )
        self.mean2 = RooFormulaVar("mean2","mean2", "mean1 + delta_m" ,RooArgList(self.mean1,self.delta_m) )
        self.sigb11  = RooCBShape("SigmodelB11","SigmodelB11", Mass, self.mean1, self.sigma1, self.a1_cb, self.ncb)
        self.sigb12  = RooCBShape("SigmodelB12","SigmodelB12", Mass, self.mean1, self.sigma2, self.a2_cb, self.ncb)
        self.sigb21  = RooCBShape("SigmodelB21","SigmodelB21", Mass, self.mean2, self.sigma1, self.a1_cb, self.ncb)
        self.sigb22  = RooCBShape("SigmodelB22","SigmodelB22", Mass, self.mean2, self.sigma2, self.a2_cb, self.ncb)
        self.fsmres = RooRealVar("f small res","f small res",0.8, 0., 1.)
        self.sigB1  = RooAddPdf("SigmodelB1","SigmodelB1", self.sigb11, self.sigb12, self.fsmres)
        self.sigB2  = RooAddPdf("SigmodelB2","SigmodelB2", self.sigb21, self.sigb22, self.fsmres)



class BdJpsiKstMCFitter:

    def __init__(self,name="MC"):

                ## Parameters of interest
        Apa2mcd = 0.2397
        Ape2mcd = 0.1601
        A02mcd = 1.-Apa2mcd-Ape2mcd
        dpamcd = 2.501

       
        self.A02mcd = RooRealVar("A02mcd","A0mcd2",A02mcd)
        self.xmcd = RooRealVar("xmcd","xmcd",Apa2mcd/(1-A02mcd))
        self.Apa2mcd = RooFormulaVar("Apa2mcd","Apa2mcd","xmcd*(1-A02mcd)",RooArgList(self.xmcd,self.A02mcd))
        self.A0mcd = RooFormulaVar("A0mcd","A0mcd","sqrt(A02mcd)",RooArgList(self.A02mcd))
        self.Apamcd = RooFormulaVar("Apamcd","Apamcd","sqrt(Apa2mcd)",RooArgList(self.Apa2mcd))
        self.Apemcd = RooFormulaVar("Apemcd","Apemcd","sqrt(1-A02mcd-Apa2mcd)",RooArgList(self.A02mcd,self.Apa2mcd))
        self.cdpamcd = RooRealVar("cdpamcd","cdpamcd",cos(dpamcd))

        self.ndMC = RooRealVar("MC_nbd","MC_ndb", 436786,436786*0.1,436786*10)

        self.modelmcd = AngJPsiKst("angmodelmcd","angmodelmcd",CPsi,CTheta,Phi,self.A0mcd,self.Apamcd,self.Apemcd,self.cdpamcd,
                                   c1_psi,c2_psi,c3_psi,c4_psi,c5_psi,c1_theta,c2_theta,c1_phi,c2_phi,c3_phi,c4_phi,c5_phi,c6_phi)
        self.model = RooExtendPdf("angmodel_mcd","angmodel_mcd", self.modelmcd, self.ndMC)



   


if __name__=="__main__":




    cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
    cuts += "&& kaon_pt>500 && pion_pt>500"
    cuts += "&& abs(Mjpsik-5279)>60"
    cuts += "&& abs(KstMass-896)<40"

    trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

    cuts += " && "+ trigger
   # cuts += " && abs(Bmass_JC-5279)<15"


    


    DataModel = BsJpsiKstFitter("DataModel")
    MCModel_d = BdJpsiKstMCFitter("MCModeld")
 
    fitter = RooSimultaneous("fitter","fitter",cat)
    fitter.addPdf(DataModel.model,"Data")
    fitter.addPdf(MCModel_d.model,"MCd")
    
    fdata = TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")
    tdata2 = fdata.Get("T/T")

    fmcd = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJPsiKstMC_nopt_v3.root")
    tmcd2 = fmcd.Get("T/T")

    #fmcs = TFile("/afs/cern.ch/user/d/diegoms/vol5/BsJpsiKstTot.root")
    #tmcs2 = fmcs.Get("T")

    ftrash = TFile("/tmp/diegoms/trash2.root","RECREATE")
    tdata = tdata2.CopyTree(cuts+"&& GL11sb.>0.2")
    tmcd = tmcd2.CopyTree(cuts+"&& GL11sb.>0.2 && abs(Bmass_JC-5279)<25")
    #tmcs = tmcs2.CopyTree(cuts+"&& GL11sb.>0.2 && abs(Bmass_JC-5366.3)<25")


    DataDset = RooDataSet("DataDset","DataDset",tdata,RooArgSet(CPsi,CTheta,Phi, Mass))
    MCdDset = RooDataSet("MCdDset","MCdDset",tmcd,RooArgSet(CPsi,CTheta,Phi, Mass))
    #MCsDset = RooDataSet("MCsDset","MCsDset",tmcs,RooArgSet(CPsi,CTheta,Phi, Mass))

    AllDset = RooDataSet("AllDset","AllDset",RooArgSet(CPsi,CTheta,Phi, Mass),RooFit.Index(cat),RooFit.Import("Data",DataDset),RooFit.Import("MCd",MCdDset))#,RooFit.Import("MCs",MCsDset))

    #BREAK
    fitres = fitter.fitTo(AllDset,RooFit.Minos(1),RooFit.Save())



    Mass.setRange("ref",Mass.getMin(),Mass.getMax())
    CPsi.setRange("ref",CPsi.getMin(),CPsi.getMax())
    CTheta.setRange("ref",CTheta.getMin(),CTheta.getMax())
    Phi.setRange("ref",Phi.getMin(),Phi.getMax())


    DataModel.model.fixCoefRange("ref")
    
    
def replot(dataset,model,rangename,nbins):

    
    cv3 = TCanvas()
    cv3.SetFillColor(0)
    cv3.Divide(2,2)

    cv3.cd(1)
    cpsif = CPsi.frame()
    RooAbsData.plotOn(dataset,cpsif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("Bsmodel"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cpsif,RooFit.ProjectionRange(rangename),RooFit.Components("Bdmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
#     model.paramOn(cpsif)
    cpsif.Draw()

    cv3.cd(2)
    cthf = CTheta.frame()
    RooAbsData.plotOn(dataset,cthf,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bsmodel"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cthf,RooFit.ProjectionRange(rangename),RooFit.Components("Bdmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cthf.Draw()

    cv3.cd(3)
    cphif = Phi.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.CutRange(rangename),RooFit.Binning(nbins))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bsmodel"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cphif,RooFit.ProjectionRange(rangename),RooFit.Components("Bdmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    cphif.Draw()

    return cv3, cphif,cthf, cpsif


    
def plot_mass(dataset,model,nbins):
    

    cv3 = TCanvas()
    
    
    cphif = Mass.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
    model.plotOn(cphif)
    model.plotOn(cphif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
    model.plotOn(cphif,RooFit.Components("Bsmodel"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
    model.plotOn(cphif,RooFit.Components("Bdmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
    #model.plotOn(cphif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    cphif.Draw()

    return cv3, cphif#,cthf, cpsif

#ratioBs = RooFormulaVar("rBs","rBs", "nBs/nBd", RooArgList(DataModel.ns,DataModel.nd))
#print "NBs/NBd = ", ratioBs.getVal(), "+/-", ratioBs.getPropagatedError(fitres)
print "Apa2 Bd = ", DataModel.Apa2_Bd.getVal(), "+/-", DataModel.Apa2_Bd.getPropagatedError(fitres)
print "Ape2 Bd = ", DataModel.Ape2_Bd.getVal(), "+/-", DataModel.Ape2_Bd.getPropagatedError(fitres)
print "As2 Bd = ", DataModel.As2_Bd.getVal(), "+/-", DataModel.As2_Bd.getPropagatedError(fitres)
print "Apa2 Bs = ", DataModel.Apa2_Bs.getVal(), "+/-", DataModel.Apa2_Bs.getPropagatedError(fitres)
print "Ape2 Bs = ", DataModel.Ape2_Bs.getVal(), "+/-", DataModel.Ape2_Bs.getPropagatedError(fitres)
print "As2 Bs = ", DataModel.As2_Bs.getVal(), "+/-", DataModel.As2_Bs.getPropagatedError(fitres)
print "Apa2(Bs)/Apa(Bd) = ", DataModel.Apa2_ratio.getVal(), "+/-", DataModel.Apa2_ratio.getPropagatedError(fitres)
print "Ape2(Bs)/Apa(Bd) = ", DataModel.Ape2_ratio.getVal(), "+/-", DataModel.Ape2_ratio.getPropagatedError(fitres)
print "As2(Bs)/As2(Bd) = ", DataModel.As2_ratio.getVal(), "+/-", DataModel.As2_ratio.getPropagatedError(fitres)

### Renormalized to 1

rA02d = RooFormulaVar("rA02d","rA02d","A02_Bd/(A02_Bd+Apa2_Bd+Ape2_Bd)",RooArgList(DataModel.A02_Bd,DataModel.Apa2_Bd,DataModel.Ape2_Bd))
rApa2d = RooFormulaVar("rApa2d","rApa2d","Apa2_Bd/(A02_Bd+Apa2_Bd+Ape2_Bd)",RooArgList(DataModel.A02_Bd,DataModel.Apa2_Bd,DataModel.Ape2_Bd))
rApe2d = RooFormulaVar("rApe2d","rApe2d","Ape2_Bd/(A02_Bd+Apa2_Bd+Ape2_Bd)",RooArgList(DataModel.A02_Bd,DataModel.Apa2_Bd,DataModel.Ape2_Bd))
rA02s = RooFormulaVar("rA02s","rA02s","A02_Bs/(A02_Bs+Apa2_Bs+Ape2_Bs)",RooArgList(DataModel.A02_Bs,DataModel.Apa2_Bs,DataModel.Ape2_Bs))
rApa2s = RooFormulaVar("rApa2s","rApa2s","Apa2_Bs/(A02_Bs+Apa2_Bs+Ape2_Bs)",RooArgList(DataModel.A02_Bs,DataModel.Apa2_Bs,DataModel.Ape2_Bs))
rApe2s = RooFormulaVar("rApe2s","rApe2s","Ape2_Bs/(A02_Bs+Apa2_Bs+Ape2_Bs)",RooArgList(DataModel.A02_Bs,DataModel.Apa2_Bs,DataModel.Ape2_Bs))
print "RENORMALZED"
print "r Apa2 Bd = ", rApa2d.getVal(), "+/-", rApa2d.getPropagatedError(fitres)
print "r Ape2 Bd = ", rApe2d.getVal(), "+/-", rApe2d.getPropagatedError(fitres)
print "r A02 Bd = ", rA02d.getVal(), "+/-", rA02d.getPropagatedError(fitres)
print "r Apa2 Bs = ", rApa2s.getVal(), "+/-", rApa2s.getPropagatedError(fitres)
print "r Ape2 Bs = ", rApe2s.getVal(), "+/-", rApe2s.getPropagatedError(fitres)
print "r A02 Bs = ", rA02s.getVal(), "+/-", rA02s.getPropagatedError(fitres)



Mass.setRange("Bs_range",5366.3-25,5366.3+25)
Mass.setRange("Bd_range",5279.5-25,5279.5+25)


foutput=TFile("output_SimultaneousOne.root","recreate")

cv1, psif1, thf1, phif1 = replot(DataDset,DataModel.model,"Bd_range",50)
cv2, psif2, thf2, phif2 = replot(DataDset,DataModel.model,"Bs_range",10)
cv3, mf = plot_mass(DataDset,DataModel.model,100)

cv4, psif4, thf4, phif4 = replot(MCdDset,MCModel_d.model,"Bd_range",50)
#cv5, psif5, thf5, phif5 = replot(MCsDset,MCModel_s.model,"Bs_range",50)

foutput.Write()
foutput.Save()

cv1.SaveAs("anglesBd_amp_ratio_simOne.root")
cv2.SaveAs("anglesBs_amp_ratio_simOne.root")
cv3.SaveAs("mass_amp_ratio_simOne.root")
cv4.SaveAs("MC_BdOne.root")
#cv5.SaveAs("MC_Bs.root")
