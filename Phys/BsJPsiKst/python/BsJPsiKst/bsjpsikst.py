#este codigo saca os histogramas dos eventos de kstar da bd e da bs, conten o string do corte da bplus, e saca a estimacion da BR


from ROOT import *
stuff ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 && Bmass_JC>4800 && Bmass_JC<5800&& kaon_pt>500 && pion_pt>500 && abs(Mjpsik-5279)>60" 


from array import array as afC

option = 1#1 for Bs, 0 for Bd

## f = TFile("~/vol5/NTuples/B24Mu_merged_341.root")
## t = f.Get("Bd2JPsiKstar")

## f2 = TFile("~/vol5/eraseme.root","recreate")
## t2 = t.CopyTree(stuff)
## t2.Write()
## f2.Close()
## f.Close()
## import cPickle
## gl = cPickle.load(file("/afs/cern.ch/user/d/diegoms/cmtuser/Erasmus_v5r3/Phys/BsJPsiKst/operators/GL_JPsiKst_Sept5"))
## import os , sys
## sys.path.append(os.environ["BS2MUMUROOT"] + "/python/Bs2MuMu")
## from triggerclass import *
## ch = channelData("~/vol5/eraseme", name2 = "Bd2JPsiKstar")

## gl(ch,"GL11")
## ch.save("~/vol5/NTuples/BsJPsiKst_341")

## BREAK
##f2 = TFile("~/vol5/BsJPsiKst_GL_PID6.root") ## OLD
#f = TFile("~/vol5/NTuples/BsJPsiKst_341.root")
f=TFile("~diegoms/vol5/BsJPsiKst_341_v2.root")

t = f.Get("T/T")

#acc = accpsi + "*"+accphi+"*"+accth

from SomeMassModels import B2JpsiModels as B
op = B.JpsiKstarFit(t,"Bmass_JC", stuff +"&&Bmass_JC>5000 && Bmass_JC<5600 && GL11sb.>0.2 && abs(KstMass-895.94)<40", fit_in_init=0, shorTime=False, weight_var ="xtype")
op.fit(fixing = {'fsh2':0, 'sh_mean2':5300,'sh_sigma2':40,'sh_dtrans2':4,'f_phi':0})
BREAK
#op2 = B.JpsiKstarFit(t,"Bmass_JC", stuff2 +"&&Bmass_JC>5150 && Bmass_JC<5600 && GL2011sb.>0.2", fit_in_init=0)
#op2.fit(fixing = {'fsh':0, 'fsh2':1, 'sh_mean':5107,'sh_sigma':40,'sh_dtrans':4,'sh_mean2':5300,'sh_sigma2':40,'sh_dtrans2':4})
#op.plot()
#op2.plot()

#BREAK
###

kst_bin = range( 640,1920,80)
#h1 = D.do_distribution(t,B.JpsiKstarFit, "KstMass", kst_bin, "Bmass_JC>4900 && Bmass_JC<5600 && GL2011sb.>0.24 && abs(KstMass-895.94)<300", mass = "Bmass")
## h2 = D.do_distribution(tk,BsKstKstFitFF, "P2_mass", kst_bin, cutsk + "&&GLKsb.>0.24 && P11_richPID_k>2 && P21_richPID_k>2", mass = "B_mass")

hz = TH1F("hist_Kst_Bs","hist_Kst_Bs",len(kst_bin)-1, afC('f',kst_bin))
#hz = TH1F("hist_Kst_Bd","hist_Kst_Bd ",len(kst_bin)-1, afC('f',kst_bin))
#BREAK
for i in range(hz.GetNbinsX()):
    op = B.JpsiKstarFit(t,"Bmass_JC", stuff+ "&& Bmass_JC>5150 && Bmass_JC<5600 && GL11sb.>0.2 && KstMass>" + str(kst_bin[i]) + "&& KstMass<"+ str(kst_bin[i+1]), fit_in_init=0)
    op.fit(fixing = {'fsh':0, 'fsh2':1, 'sh_mean':5107,'sh_sigma':40,'sh_dtrans':4,'sh_mean2':5300,'sh_sigma2':40,'sh_dtrans2':4 ,"f_phi":0})
    #op.fit(fixing = {"fsh":0,"sh_sigma":30,"sh_dtrans":0.4})
    
    if(option):
        hz.SetBinContent(i+1,op.nsig.getVal()*op.fB2.getVal()) ##Bs
        hz.SetBinError(i+1,sqrt((op.nsig.getVal()*op.fB2.getError())**2 +(op.nsig.getError()*op.fB2.getVal())**2  ) )
    else:
        hz.SetBinContent(i+1,op.nsig.getVal()*(1-op.fB2.getVal())) ##Bd
        hz.SetBinError(i+1,sqrt(op.nsig.getError()**2*(1+op.fB2.getVal()**2) +(op.nsig.getVal()*op.fB2.getError())**2 ))
fH = TFile("Kst_for_" + option*"Bs" + (not option)*"Bd" + ".root","recreate")
hz.Write()
fH.Close()
BREAK

op = B.KstarFiter(t,"KstMass", "GL2011sb.>0.2")
op.fsig = RooFormulaVar("f_sig","f_sig", "Sigfraction/(Sigfraction+ bkgfraction)",RooArgList(op.nsig, op.nbkg))
hkstar = RooDataHist("deita","data", RooArgList(op.mass),hz)
_kstres = op.model.fitTo(hkstar, RooFit.Minos(kTRUE),RooFit.Save(kTRUE))

fr = op.mass.frame()

RooAbsData.plotOn(hkstar,fr)

op.model.plotOn(fr)
op.model.plotOn(fr,RooFit.Components("bkg"), RooFit.LineStyle(kDashed), RooFit.LineColor(kBlue))
op.model.plotOn(fr,RooFit.Components("Sigmodel"), RooFit.LineColor(kRed))
fr.Draw()


salvar = TFile('$HOME/tuplas/hist_Kst_Bs.root','recreate')
hz.Write()
salvar.Close()


##codigo para sacar el fit desastroso
op = B.JpsiKstarFit(t,"Bmass_JC",stuff0 + "&& GL2011sb.>0.2 && Bmass_JC>4800 && Bmass_JC<5800",fit_in_init=1)
op.plot()

##codigo con los cortes buenos
op = B.JpsiKstarFit(t,"Bmass_JC", stuff+ "&& Bmass_JC>5150 && Bmass_JC<5600 && GL2011sb.>0.2", fit_in_init=1)
op.plot()

##calculo de BR(Bs-->JpsiKst)
#BRBs = BRBd * fd_fs * fb2/(1 - fb2) * nBs / nBd

BRBd = 1.33e-03
sBRBd = .06e-03
fd_fs = 3.75
sfd_fs = 0.29
fb2 = op.fB2.getVal()
sfb2 = op.fB2.getError()
nbs = 0.734
snbs = 0.055
nbd = 0.85808
snbd = 0.00013

BRBs = BRBd*fd_fs*fb2/(1-fb2)*nbs/nbd
sBRBs = sqrt((BRBs/BRBd*sBRBd)**2 + (BRBs/fd_fs*sfd_fs)**2 + (BRBd*fd_fs/(1-fb2)/(1-fb2)*nbs/nbd*sfb2)**2 + (BRBs/nbs*snbs)**2 + (BRBs/nbd*snbd)**2)
