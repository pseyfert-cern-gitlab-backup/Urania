from ROOT import *
from math import *
gStyle.SetPalette(1)    #Color Palette

#Bdlifetime = 1519e-15
#Bslifetime = 1568e-15
Bdlifetime = 1.519
Bslifetime = 1.425

#Open the file and create the Tree
Bdf_real = TFile("~/vol5/BsJPsiKst_341_v2.root ")
Bd2_real = gDirectory.Get("T/T")
Bdf_mc = TFile("~/vol5/BdJpsiKstTotMC11_v2.root ")
Bd2_mc = gDirectory.Get("T/T")
#Bsf_mc = TFile("/scratch10/Ntuples_BsJpsiKst/BsJpsiKstTot.root  ")
#Bs2_mc = gDirectory.Get("T/T")

#f = TFile("/tmp/alvarezc/BdJPsiKstMC_GL_v3.root")
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BdJPsiKstMC_nopt_v3.root")
#f = TFile("/afs/cern.ch/user/d/diegoms/vol5/BsJpsiKstTot.root")
#t2 = f.Get("T")#/T")


cuts ="dDsig>13 && mu1ips>5 && mu2ips>5 && Bips<5 && DOCA<0.3 && p1ips>2 && k1ips>2 && JPsiChi2<9 && KstChi2<9 && Vchi2<25 && abs(JPsiMass-3096.916)<60 && PIDk>6 && PIDpi<-6 "
#     cuts += "&& Bmass_JC>5150 && Bmass_JC<5800"
cuts += "&& abs(Bmass_JC-5279.5)<25"
#cuts = "&& abs(Bmass_JC-5366.3)<25"
cuts += "&& kaon_pt>500 && pion_pt>500"
cuts += "&& abs(Mjpsik-5279)>60"
cuts += "&& abs(KstMass-896)<40"
#cuts += "&& KstMass>856 && KstMass >1200"
#cuts += "&& KstMass > 1000"


trigger = "L0Decision==1 && Hlt1Decision==1 && Hlt2Decision==1"

cuts += " && "+ trigger


Bd2f_real=TFile("nadar.root","recreate")
Bd_real=Bd2_real.CopyTree(cuts+" && GL11sb.>0.2")

Bd2f_mc=TFile("nadam.root","recreate")
Bd_mc=Bd2_mc.CopyTree(cuts+" && GL11sb.>0.2")


#histogram creation
nBins = 100
hlifeTime_real = TH1F( "lifeTime_real", "lifeTime_real", nBins, 0, 10)
hlifeTime_mc = TH1F( "lifeTime_mc", "lifeTime_mc", nBins, 0, 10)
hlifeTimeacc_real = TH1F( "lifeTimeacc_real", "lifeTimeacc_real", nBins, 0, 10)
hlifeTimeacc_mc = TH1F( "lifeTimeacc_mc", "lifeTimeacc_mc", nBins, 0, 10)

hlifeTimeBs_real = TH1F( "lifeTimeBs_real", "lifeTimeBs_real", nBins, 0, 10)
hlifeTimeBs_mc = TH1F( "lifeTimeBs_mc", "lifeTimeBs_mc", nBins, 0, 10)
hlifeTimeBs_id = TH1F( "lifeTimeBs_id", "lifeTimeBs_id", nBins, 0, 10)
hlifeTimeBd_real = TH1F( "lifeTimeBd_real", "lifeTimeBd_real", nBins, 0, 10)
hlifeTimeBd_mc = TH1F( "lifeTimeBd_mc", "lifeTimeBd_mc", nBins, 0, 10)
hlifeTimeBd_id = TH1F( "lifeTimeBd_id", "lifeTimeBd_id", nBins, 0, 10)



for i in Bd_real:
    hlifeTime_real.Fill(i.Blife_ps_r)
for i in Bd_mc:
    hlifeTime_mc.Fill(i.Blife_ps_r)

for i in range(1,nBins):
    hlifeTimeacc_real.SetBinContent(i, hlifeTime_real.GetBinContent(i)/exp((-1)*hlifeTime_real.GetBinCenter(i)/Bdlifetime))
for i in range(1,nBins):
    hlifeTimeacc_mc.SetBinContent(i, hlifeTime_mc.GetBinContent(i)/exp((-1)*hlifeTime_mc.GetBinCenter(i)/Bdlifetime))

hlifeTimeacc_mc.Scale(1./hlifeTimeacc_mc.GetSum())
hlifeTimeacc_real.Scale(1./hlifeTimeacc_real.GetSum())

#BREAK
clifeTime = TCanvas( 'clifeTime', 'clifetime', 1000, 600)
clifeTime.Divide(2)
clifeTime.cd(1)
hlifeTimeacc_real.Draw()
clifeTime.cd(2)
hlifeTimeacc_mc.Draw()

for i in range(1,nBins):
    hlifeTimeBs_real.SetBinContent(i, exp((-1)*hlifeTime_real.GetBinCenter(i)/Bslifetime)*hlifeTimeacc_real.GetBinContent(i))
    hlifeTimeBs_mc.SetBinContent(i, exp((-1)*hlifeTime_mc.GetBinCenter(i)/Bslifetime)*hlifeTimeacc_mc.GetBinContent(i))
    hlifeTimeBs_id.SetBinContent(i, exp((-1)*hlifeTime_real.GetBinCenter(i)/Bslifetime))

    hlifeTimeBd_real.SetBinContent(i, exp((-1)*hlifeTime_real.GetBinCenter(i)/Bdlifetime)*hlifeTimeacc_real.GetBinContent(i))
    hlifeTimeBd_mc.SetBinContent(i, exp((-1)*hlifeTime_mc.GetBinCenter(i)/Bdlifetime)*hlifeTimeacc_mc.GetBinContent(i))
    hlifeTimeBd_id.SetBinContent(i, exp((-1)*hlifeTime_real.GetBinCenter(i)/Bdlifetime))


effBs_real = hlifeTimeBs_real.Integral()/hlifeTimeBs_id.Integral()
effBs_mc = hlifeTimeBs_mc.Integral()/hlifeTimeBs_id.Integral()
effBd_real = hlifeTimeBd_real.Integral()/hlifeTimeBd_id.Integral()
effBd_mc = hlifeTimeBd_mc.Integral()/hlifeTimeBd_id.Integral()

print "effBs_dat/effBs_mc <=> effBd_dat/effBd_mc = ", effBs_real,"/",effBs_mc,"<=>", effBd_real, "/", effBd_mc, "= ", effBs_real/effBs_mc, "<=>", effBd_real/effBd_mc
