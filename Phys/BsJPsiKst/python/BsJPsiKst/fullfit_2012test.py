from ROOT import *
from math import *
import os
if not "BSJPSIKSTROOT" in os.environ.keys(): os.environ["BSJPSIKSTROOT"] = "../../"
gROOT.ProcessLine(".x " + os.environ["BSJPSIKSTROOT"]+"/src/AngJpsiKst_Swave.cxx++")
#gSystem.Load("AngJPsiKst_cxx")


print "Class for fitting polarization: AngularPDF"

#CHANNEL = "Bd"
s_a = 5.

ACC_FREE = 1
FIX_Bd = ACC_FREE
SAME_ACC = 1

CPsi = RooRealVar("CPsi","CPsi",-1.,1.)
CTheta = RooRealVar("CTheta","CTheta",-1.,1.)
Phi = RooRealVar("B0_PhiTr","B0_PhiTr",-1.*pi,pi)

f05 = RooRealVar("f05","f05",0.5)#, 0., 1.)

 ## Acceptance
        
c1_psi = RooRealVar("c1_psi","c1_psi",-0.522,-0.522-s_a*0.014,-0.522+s_a*.014)
c2_psi = RooRealVar("c2_psi","c2_psi",-0.723,-0.723-s_a*0.022,-0.723+s_a*0.022)
c3_psi = RooRealVar("c3_psi","c3_psi",-0.190,-0.190-3*s_a,0.190+3*s_a)
c4_psi = RooRealVar("c4_psi","c4_psi",0.208,0.208-s_a*0.023,0.208+s_a*0.023)

        
y = RooRealVar("y","y",0.)#,0.,s_a*1.6e-04)
c5_psi = RooFormulaVar("c5_psi","c5_psi","y + (-1.-c1_psi-c2_psi-c3_psi-c4_psi)",RooArgList(y,c1_psi,c2_psi,c3_psi,c4_psi))
       

c1_theta = RooRealVar("c1_theta","c1_theta",0.)
c2_theta = RooRealVar("c2_theta","c2_theta",-0.1783,-0.1783-s_a*0.0075,-0.1783+s_a*0.0075)

c1_phi = RooRealVar("c1_phi","c1_phi",0.090,0.0784-s_a*0.0039,0.0784+s_a*0.0039)
c2_phi = RooRealVar("c2_phi","c2_phi",2.019,2.019-s_a*0.029,2.109+s_a*0.029)
c3_phi = RooRealVar("c3_phi","c3_phi",.33,.33-s_a*0.048,.33+s_a*0.048)
c4_phi = RooRealVar("c4_phi","c4_phi",0.)#,0.5)
c5_phi = RooRealVar("c5_phi","c5_phi",0.)#,6.)
c6_phi = RooRealVar("c6_phi","c6_phi",0.)#-pi/2.,pi/2.)

if not ACC_FREE:
    c1_phi.setConstant(kTRUE)
    c2_phi.setConstant(kTRUE)
    c3_phi.setConstant(kTRUE)
    c4_phi.setConstant(kTRUE)
    c5_phi.setConstant(kTRUE)
    c6_phi.setConstant(kTRUE)
    c1_psi.setConstant(kTRUE)
    c2_psi.setConstant(kTRUE)
    c3_psi.setConstant(kTRUE)
    c4_psi.setConstant(kTRUE)
    c5_psi.setConstant(kTRUE)
    y.setConstant(kTRUE)
    c1_theta.setConstant(kTRUE)
    c2_theta.setConstant(kTRUE)
    
    
### Acceptance Bs
if SAME_ACC:
    c1_psi_Bs, c2_psi_Bs, c3_psi_Bs, c4_psi_Bs, y_Bs, c5_psi_Bs = c1_psi, c2_psi, c3_psi, c4_psi, y, c5_psi
    c1_theta_Bs, c2_theta_Bs = c1_theta, c2_theta
    c1_phi_Bs, c2_phi_Bs, c3_phi_Bs, c4_phi_Bs, c5_phi_Bs, c6_phi_Bs = c1_phi, c2_phi, c3_phi, c4_phi, c5_phi, c6_phi
    
else:
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


class AngularPDFMOD:
    def __init__(self, neim = "Bd"):

        


        ## Parameters of interest

        self.fL = RooRealVar("fL"+neim,"fL"+neim,0.507,0.2, .65)
        self.fpa = RooRealVar("fpa"+neim,"fpa"+neim,0.172,0.07, .35)
        self.As2 = RooRealVar("As2"+neim,"As2"+neim,0.05, 0,0.3)
        self.A02 = RooFormulaVar("A02"+neim,"A02"+neim,"fL"+neim+"*(1-As2"+neim+")",RooArgList(self.fL,self.As2))
        self.Apa2 = RooFormulaVar("Apa2"+neim,"Apa2"+neim,"fpa"+neim+"*(1-As2"+neim+")",RooArgList(self.fpa,self.As2))#RooRealVar("As2","As2", 0.,.1)
        
        self.Ape2 = RooFormulaVar("Ape2"+neim,"Ape2"+neim,"(1-A02"+neim+"-Apa2"+neim+" - As2" + neim + ")",RooArgList(self.As2,self.A02,self.Apa2))#RooRealVar("As2","As2", 0.,.1)
        
        self.As = RooFormulaVar("As"+neim,"As"+neim,"sqrt(As2"+neim+")",RooArgList(self.As2))
        
        self.A0 = RooFormulaVar("A0"+neim,"A0"+neim,"sqrt(A02"+neim+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa"+neim,"Apa"+neim,"sqrt(Apa2"+neim+")",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape"+neim,"Ape"+neim,"sqrt(Ape2"+neim+")",RooArgList(self.Ape2))
        
     
        self.dpa = RooRealVar("dpa"+neim,"dpa" + neim, -pi,0)
        self.ds = RooRealVar("ds"+neim,"ds"+neim,0 , pi)

        self.sigmodel = AngJpsiKst_Swave("angular " + neim,"angular " + neim,CPsi,CTheta,Phi,self.A0,self.Apa,self.Ape,self.As,self.dpa,self.ds,
                                   c1_psi_Bs,c2_psi_Bs,c3_psi_Bs,c4_psi_Bs,c5_psi_Bs,c1_theta_Bs,c2_theta_Bs,c1_phi_Bs,c2_phi_Bs,c3_phi_Bs,c4_phi_Bs,c5_phi_Bs,c6_phi_Bs)

class AngularPDFMODBd:
    def __init__(self, neim = "Bd"):

        


        ## Parameters of interest

        self.fL = RooRealVar("fL"+neim,"fL"+neim,0.5488,0.5, .6)
        self.fpa = RooRealVar("fpa"+neim,"fpa"+neim,0.2392,0.210, .260)
        self.As2 = RooRealVar("As2"+neim,"As2"+neim,0.047, 0,.2)
        self.A02 = RooFormulaVar("A02"+neim,"A02"+neim,"fL"+neim+"*(1-As2"+neim+")",RooArgList(self.fL,self.As2))
        self.Apa2 = RooFormulaVar("Apa2"+neim,"Apa2"+neim,"fpa"+neim+"*(1-As2"+neim+")",RooArgList(self.fpa,self.As2))#RooRealVar("As2","As2", 0.,.1)
        
        self.Ape2 = RooFormulaVar("Ape2"+neim,"Ape2"+neim,"(1-A02"+neim+"-Apa2"+neim+" - As2" + neim + ")",RooArgList(self.As2,self.A02,self.Apa2))#RooRealVar("As2","As2", 0.,.1)
        
        self.As = RooFormulaVar("As"+neim,"As"+neim,"sqrt(As2"+neim+")",RooArgList(self.As2))
        
        self.A0 = RooFormulaVar("A0"+neim,"A0"+neim,"sqrt(A02"+neim+")",RooArgList(self.A02))
        self.Apa = RooFormulaVar("Apa"+neim,"Apa"+neim,"sqrt(Apa2"+neim+")",RooArgList(self.Apa2))
        self.Ape = RooFormulaVar("Ape"+neim,"Ape"+neim,"sqrt(Ape2"+neim+")",RooArgList(self.Ape2))
        
     
        self.dpa = RooRealVar("dpa"+neim,"dpa" + neim,-2.98, -pi, 0)
        self.ds = RooRealVar("ds"+neim,"ds"+neim,2.20,0.,pi)
        if FIX_Bd:
            self.fL.setConstant(kTRUE)
            self.fpa.setConstant(kTRUE)
            self.As2.setConstant(kTRUE)
            self.ds.setConstant(kTRUE)
            self.dpa.setConstant(kTRUE)
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
#a1_cb = RooRealVar("a1_cb","a1_cb",2.8, 0.5,3.5)
#a2_cb = RooRealVar("a2_cb","a2_cb",2.3, 0.5,3.5)

a1_cb = RooRealVar("a1_cb","a1_cb",2.8)#, 0.5,3.5)
a2_cb = RooRealVar("a2_cb","a2_cb",2.3)#, 0.5,3.5)

#1b_cb = RooRealVar("a1b_cb","a1b_cb",2.8, 0.5,3.5)
#a2b_cb = RooRealVar("a2b_cb","a2b_cb",2.8, 0.5,3.5)
a2r_cb = RooRealVar("a2r_cb","a2_cb",-1.79)#, -6,-0.5)
#a1r_cb = RooRealVar("a1r_cb","a1_cb",-2.3, -6,-0.5)
ncb2 = RooRealVar("ncb2","ncb2",3.1)#)

kbkg = RooRealVar("k","k",-1e-03,-1,0)

fsig = RooRealVar("fsig","fsig",0.,1)




if __name__=="__main__":

    #f = TFile("~/vol5/OL_2011_GL.root")
    f = TFile("/user/diegoms/cmtuser/NTuples/OL_2011_GL.root")
    t2 = f.Get("T")
    #f=TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")
    #t2=f.Get("T/T")


#    cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "

    
 #   cuts += "&& kaon_pt>500 && pion_pt>500"

    cuts = "muplus_MINIPCHI2 > 25 && muminus_MINIPCHI2 > 25 && Kplus_MINIPCHI2 > 4 && piminus_MINIPCHI2 > 4  && Kplus_PT > 500 && piminus_PT>500 && piminus_PIDK<-6 && Kplus_PIDK > 6 && J_psi_1S_FDCHI2_TOPPV > 169 &&  J_psi_1S_LOKI_DOCA_1_2<0.3"
    cuts += "&&  J_psi_1S_ENDVERTEX_CHI2 < 9 && B0_IPCHI2_OWNPV < 25"
        
    cuts += "&& abs(Mjpsik-5279)>60"
    cuts += "&& abs(Kst_892_0_MM-896)<70"
    
    #trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

    #cuts += " && "+ trigger
    #BREAK

    f2=TFile("nada.root","recreate")
    t=t2.CopyTree(cuts+"&& GLsb>0.2")
    #BREAK
    
    Mass = RooRealVar("B0_MM","B0_MM",5150, t.GetMaximum("B0_MM"))
    AngBd = AngularPDFMODBd()
    
    
    AngBs = AngularPDFMOD("Bs")
    
    psibkg = RooPolynomial("psibkg","psibkg",CPsi,RooArgList(c1_psi,c2_psi,c3_psi,c4_psi,c5_psi))
    thetabkg = RooPolynomial("thetabkg","thetabkg",CTheta,RooArgList(c1_theta,c2_theta))
    phibkg = RooGenericPdf("phibkg","phibkg","1+c1_phi_bkg*B0_PhiTr + c2_phi_bkg*B0_PhiTr*B0_PhiTr + c3_phi_bkg*B0_PhiTr*B0_PhiTr*B0_PhiTr",RooArgList(Phi,c1_phi_bkg,c2_phi_bkg,c3_phi_bkg))
    #phibkg = RooGenericPdf("phibkg","phibkg","c1_phi_bkg +sin(c2_phi_bkg*B0_PhiTr + c3_phi_bkg)",RooArgList(Phi,c1_phi_bkg,c2_phi_bkg,c3_phi_bkg))

    massbkg = RooExponential("bkg", "Exponential background pdf", Mass, kbkg)
    bkgmodel = RooProdPdf("bkgmodel","bkgmodel",RooArgList(psibkg,thetabkg,phibkg,massbkg))

    mean1 = RooRealVar("mean1","mean1",5279, 5276,5300)
    sigma1 = RooRealVar("sigma1","sigma1", 6.,10.)
    
    delta_s = RooRealVar("delta_s", "delta_s", 2.,1.,15.)
    delta_m = RooRealVar("delta_m", "delta_m", 5366.3-5279)
    sigma2 = RooFormulaVar("sigma2","sigma2", "sigma1 + delta_s" ,RooArgList(sigma1,delta_s) )
    mean2 = RooFormulaVar("mean2","mean2", "mean1 + delta_m" ,RooArgList(mean1,delta_m) )
    sigb11  = RooCBShape("SigmodelB11","SigmodelB11", Mass, mean1, sigma1, a1_cb, ncb)

    #sigb12  = RooCBShape("SigmodelB12","SigmodelB12", Mass, mean1, sigma2, a2_cb, ncb)
    sigb12l  = RooCBShape("SigmodelB12l","SigmodelB12l", Mass, mean1, sigma2, a2_cb, ncb)
    sigb12r  = RooCBShape("SigmodelB12r","SigmodelB12r", Mass, mean1, sigma2, a2r_cb, ncb2)
    sigb12  = RooAddPdf("SigmodelB12","SigmodelB12", sigb12l, sigb12r, f05)
    
    sigb21  = RooCBShape("SigmodelB21","SigmodelB21", Mass, mean2, sigma1, a1_cb, ncb)

    #sigb22  = RooCBShape("SigmodelB22","SigmodelB22", Mass, mean2, sigma2, a2_cb, ncb)
    sigb22l  = RooCBShape("SigmodelB22l","SigmodelB22l", Mass, mean2, sigma2, a2_cb, ncb)
    sigb22r  = RooCBShape("SigmodelB22r","SigmodelB22r", Mass, mean2, sigma2, a2r_cb, ncb2)
    sigb22  = RooAddPdf("SigmodelB22","SigmodelB22", sigb22l, sigb22r, f05)
    
    fsmres = RooRealVar("f small res","f small res",0.8, 0., 1.)
    sigB1  = RooAddPdf("SigmodelB1","SigmodelB1", sigb11, sigb12, fsmres)
    sigB2  = RooAddPdf("SigmodelB2","SigmodelB2", sigb21, sigb22, fsmres)

    SigBs = RooProdPdf("Bs pdf", "Bs pdf",RooArgList(AngBs.sigmodel,sigB2))
    SigBd = RooProdPdf("Bd pdf", "Bd pdf",RooArgList(AngBd.sigmodel,sigB1))

    fBs = RooRealVar("fBs","fBs", 1e-02,1e-03,.1)
    
    nd = RooRealVar("nBd","nBd", 0.5*t.GetEntries(),t.GetEntries())
    ns = RooFormulaVar("nBs","nBs", "fBs*nBd",RooArgList(fBs,nd))
    nbkg = RooRealVar("n nbkg","n bkg", 0.,0.1*t.GetEntries())
    just_mass_model = RooAddPdf("jmmodel","jmmodel",RooArgList(sigB2,sigB1,massbkg),RooArgList(ns,nd,nbkg))
    #BREAK
    model = RooAddPdf("model","model",RooArgList(SigBs,SigBd,bkgmodel),RooArgList(ns,nd,nbkg))
    dataset = RooDataSet("data","data",t,RooArgSet(CPsi,CTheta,Phi, Mass))
    #just_mass_model.fitTo(dataset,RooFit.Minos(1),RooFit.Save())
    #BREAK
    fitres = model.fitTo(dataset,RooFit.Minos(0),RooFit.Save(), RooFit.Offset(kTRUE))


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

cv1.SaveAs("Bd_fit_FL_MC11MC11_pol.root")
cv2.SaveAs("Bs_fit_FL_MC11MC11_pol.root")
cv3.SaveAs("Mass_fit_FL_MC11MC11_pol.root")
## fmcd = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJpsiKstTotMC11_v2.root")
## tmcd2 = fmcd.Get("T/T")


## tmcd = tmcd2.CopyTree(cuts+"&& GL11sb.>0.2 && abs(B0_MM-5279)<25")
def plot_jmass(nbins):
    cv3 = TCanvas()    
    cphif = Mass.frame()
    RooAbsData.plotOn(dataset,cphif,RooFit.Binning(nbins))
    just_mass_model.plotOn(cphif)
    ## model.plotOn(cphif,RooFit.Components("bkgmodel"),RooFit.LineColor(kBlue),RooFit.LineStyle(kDashed))
##     model.plotOn(cphif,RooFit.Components("Bs pdf"),RooFit.LineColor(TColor.GetColor("#ff99cc")),RooFit.LineStyle(9))
##     model.plotOn(cphif,RooFit.Components("Bd pdf"),RooFit.LineColor(kRed),RooFit.LineStyle(7))
##     #model.plotOn(cphif,RooFit.Components("sigmodel"),RooFit.LineColor(kRed),RooFit.LineStyle(kDotted))
    cphif.Draw()

    return cv3, cphif#,cthf, cpsif



### 2012

## MIGRAD FAILS TO FIND IMPROVEMENT
##  MIGRAD MINIMIZATION HAS CONVERGED.
##  FCN=-183954 FROM MIGRAD    STATUS=CONVERGED    2076 CALLS        2077 TOTAL
##                      EDM=0.000151415    STRATEGY= 1  ERROR MATRIX UNCERTAINTY   7.3 per cent
##   EXT PARAMETER                                   STEP         FIRST   
##   NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
##    1  As2Bs        1.05631e-02   9.09116e-03  -0.00000e+00  -5.39445e-03
##    2  c1_phi       8.27540e-02   6.64697e-03   0.00000e+00  -3.57603e-04
##    3  c1_phi_bkg   6.46888e-02   6.70141e-02   0.00000e+00   4.62356e-02
##    4  c1_psi      -4.92125e-01   1.12393e-02   0.00000e+00   1.02845e-02
##    5  c2_phi       1.95043e+00   4.30674e-02  -0.00000e+00   1.52018e-03
##    6  c2_phi_bkg   1.41043e-02   1.71411e-02  -0.00000e+00  -2.69783e-02
##    7  c2_psi      -6.67997e-01   2.71183e-02   0.00000e+00   2.56465e-02
##    8  c2_theta    -1.66534e-01   1.09071e-02  -0.00000e+00   6.57177e-04
##    9  c3_phi       3.29997e-01   6.76948e-02  -0.00000e+00  -8.50327e-03
##   10  c3_phi_bkg  -1.88888e-02   1.02447e-02   0.00000e+00   5.57910e-02
##   11  c3_psi      -3.89431e-01   4.71953e-02  -0.00000e+00   2.12973e+00
##   12  c4_psi       2.25646e-01   3.09036e-02  -0.00000e+00  -6.69580e-03
##   13  delta_s      7.69768e+00   3.36831e-01  -0.00000e+00   2.93483e-02
##   14  dpaBd       -2.88479e+00   3.15930e-02  -0.00000e+00  -1.95824e-01
##   15  dpaBs       -3.14159e+00   9.24546e-02   0.00000e+00** at limit **
##   16  dsBs         1.03308e-01   2.36294e-01  -0.00000e+00   4.33369e-02
##   17  f small res   7.69018e-01   1.43323e-02  -0.00000e+00  -1.96050e-02
##   18  fBs          8.34415e-03   4.74343e-04   0.00000e+00   5.21152e-04
##   19  fLBs         5.82140e-01   4.11027e-02  -0.00000e+00   4.44119e-03
##   20  fpaBs        1.19535e-01   4.09634e-02   0.00000e+00   3.47369e-03
##   21  k           -2.53057e-03   4.29443e-04   0.00000e+00   5.67949e-02
##   22  mean1        5.28132e+03   3.52903e-02   0.00000e+00   1.01048e-01
##   23  n nbkg       1.10287e+03   5.52045e+01   0.00000e+00   1.85048e-02
##   24  nBd          5.57124e+04   1.75821e+02  -0.00000e+00   3.89647e-01
##   25  sigma1       6.67469e+00   6.57346e-02  -0.00000e+00   1.74667e-01


## 2011

##   EXT PARAMETER                                INTERNAL      INTERNAL  
##   NO.   NAME      VALUE            ERROR       STEP SIZE       VALUE   
##    1  As2Bs        9.95469e-02   8.07230e-02   1.46704e-01  -2.79855e+00
##    2  c1_phi       6.89704e-02   6.73836e-03   1.00999e-01  -2.63687e+00
##    3  c1_phi_bkg   7.28656e-03   8.80077e-02   9.77246e-03   7.28662e-03
##    4  c1_psi      -5.16421e-01   2.16340e-02   2.73422e-02   7.97843e-02
##    5  c2_phi       2.05957e+00   5.87796e-02   8.33567e-02  -2.33157e-02
##    6  c2_phi_bkg   3.13500e-02   2.43750e-02   7.20067e-02  -9.12441e-01
##    7  c2_psi      -7.33556e-01   2.78579e-02   1.96283e-02  -9.61112e-02
##    8  c2_theta    -1.81475e-01   1.25898e-02   9.15030e-02  -8.47749e-02
##    9  c3_phi       4.48006e-01   1.08183e-01   1.22009e-01   5.14030e-01
##   10  c3_phi_bkg   1.73854e-03   1.38934e-02   1.54091e-02   1.73862e-02
##   11  c3_psi      -2.97910e-01   6.67044e-02   3.50446e-04  -1.96135e-02
##   12  c4_psi       2.69624e-01   3.00671e-02   2.49707e-02   5.65532e-01
##   13  delta_s      6.27515e+00   5.93361e-01   4.97630e-03  -2.48971e-01
##   14  dpaBd       -2.91572e+00   4.03840e-02   1.07951e-02  -1.02788e+00
##   15  dpaBs       -3.00454e+00   3.27747e-01   1.40716e-01  -1.99163e+00
##   16  dsBs         1.41557e+00   1.70069e-01   2.56904e-02  -9.89807e-02
##   17  f small res   7.37730e-01   4.01068e-02   3.10776e-03   4.95488e-01
##   18  fBs          8.40048e-03   4.95300e-04   4.91882e-03  -1.01693e+00
##   19  fLBs         5.56965e-01   4.73175e-02   5.82731e-02   6.26743e-01
##   20  fpaBs        1.93242e-01   5.44013e-02   9.69677e-02  -1.19986e-01
##   21  k           -2.24707e-03   5.33719e-04   2.98112e-03   1.47595e+00
##   22  mean1        5.28121e+03   3.77866e-02   1.02799e-03  -6.01184e-01
##   23  n nbkg       7.52020e+02   4.69671e+01   6.64061e-03  -7.68025e-01
##   24  nBd          4.81114e+04   2.21798e+02   1.13641e-02   1.13415e+00
##   25  sigma1       6.64630e+00   1.47629e-01   5.91648e-03  -7.43474e-01
