from smartpyROOT import *
from triggerclass import *
#from BsMuMuPy.pyAna.bhhbkg_th import addMasses
import random
from ROOT import *
from NTuple_names import *

l = ["Bmass"]#,"MKK","MKpi","MpiK","Mpipi"]
labels = l + ["evt","mc1","mc2","mu1ismu","mu2ismu","mc_mu1_px","mc_mu1_py","mc_mu1_pz", "mc_mu2_px","mc_mu2_py","mc_mu2_pz","mu1ptot","mu2ptot"]
labels += ["GLKsm_MC10sb."]
Mmu = 105.658367

#bskpi = channelData("~/vol5/NTuples/MC10_Bs2Kpi_sm1_2011_BDT", name2 = "T", labels = labels) 
#bdkpi = channelData("~/vol5/NTuples/MC10_B02Kpi_sm1_2011_BDT", name2 = "T", labels = labels)
#bskk = channelData("~/vol5/NTuples/MC10_Bs2KK_sm1_2011_BDT", name2 = "T", labels = labels)
#bdpipi = channelData("~/vol5/NTuples/MC10_B02pipi_sm1_2011_BDT", name2 = "T", labels = labels)

bskpi = channelData("~/vol5/NTuples/bskpi_mc10_ntuple_2011trig", name2 = "B2hh", labels = labels) 
bdkpi = channelData("~/vol5/NTuples/bdkpi_mc10_ntuple_2011trig", name2 = "B2hh", labels = labels)
bskk = channelData("~/vol5/NTuples/bskk_mc10_ntuple_2011trig", name2 = "B2hh", labels = labels)
bdpipi = channelData("~/vol5/NTuples/bdpipi_mc10_ntuple_2011trig", name2 = "B2hh", labels = labels)

kpit = channelData("~/vol5/MC11_BdKPi_misID_Stp17_0x006d0032_up_FrascaTuple", name2 = "B2MuMuTuple/DecayTree")#, labels = labels)
kpit2 = channelData("~/vol5/MC11_BdKPi_misID_Stp17_0x006d0032_down_FrascaTuple", name2 = "B2MuMuTuple/DecayTree")#, labels = labels)

mct_inc = "((rmo1key == rmo2key && rmo1isB2qq) && ( abs(mo1) ==511 || abs(mo1) == 531) && ( abs(mo2) ==511 || abs(mo2) == 531 ) && (mo1==mo2)"\
          "&& (abs(mc1) ==321 || abs(mc1) ==211) && (abs(mc2) ==321 || abs(mc2) ==211))"

def misid_p(mcp,p, par = "pi", deb = 0, pesimistic =-1):
    x0 = random.random()
    if pesimistic: print "overdoing ",pesimistic, " sigmas"
    if   par in ["pi",211.0,-211.0]:
        p0 = 1.69634e+02 - pesimistic* 7.08501e+00 
        p2 = 4.82443e-03 -  pesimistic* 1.67438e-04 
        p3 = 1.11642e+01 +  pesimistic* 8.07570e-01
        m =  -3.11790e-02  
        s =   3.06433e-02 +  pesimistic* 1.20827e-03
        
        
    elif par in ["k",321.0,-321.0]:
        p0 = 5.35791e+01- pesimistic* 3.65008e+00
        p2 = 5.79992e-03- pesimistic*  3.31e-04
        p3 = 2.23105e+00 +pesimistic*3.79567e-01
        m = -2.41388e-03 
        s = 5.05413e-02 + pesimistic*5.96430e-03
    else:
        print "error", par, " using randon"
        if random.random() < 0.5: return misid_p(mcp,p,211.0)
        else: return misid_p(mcp,p,321.0)
    if pesimistic:
        p0 = 1.69634e+02
        p2 = 4.82443e-03
        p3 = 1.11642e+01
        s =  5.05413e-02
        
    k1 = p0*p2
    k2 = p3*s
    f = k2/(k1+k2)
    if deb: print f
   # f = 0
    if x0 > f: return p
    p2 = random.gauss(mcp *(1+m),s*mcp)
    if p2 <0:return misid_p(mcp,p,par)
    return p2


def skrew_up_masses(entry, dmass =0 , s_mc = 20, s_d = 24):
    entry["Bmass_or"] = entry["Bmass"]
    for x in l:
        entry[x] = random.gauss(entry[x] + dmass , sqrt(s_d**2-s_mc**2))
    entry["Bmass_sm"] = entry["Bmass"]
    
    ##     a = h.Fill(t.Bmass)
    p1 = entry["mu1ptot"]
    p2 = entry["mu2ptot"]
    
    Th = (Mmu**2 -0.5*entry["Bmass_or"]**2 + sqrt( (p1*p1  +Mmu**2)*(p2*p2  +Mmu**2)) )/(p1*p2)
    pmc = vector(entry["mc_mu1_px"], entry["mc_mu1_py"],entry["mc_mu1_pz"])
    pmc = vmod(pmc)
    pmc2 = vector(entry["mc_mu2_px"], entry["mc_mu2_py"],entry["mc_mu2_pz"])
    pmc2 = vmod(pmc2)
    
    p1 = misid_p(pmc,p1,entry["mc1"])
    p2 = misid_p(pmc2,p2,entry["mc2"])
    mass = sqrt(Mmu**2 + Mmu**2 +  2* (sqrt( (p1**2+Mmu**2)*(p2**2+Mmu**2)) -p1*p2*Th))
    entry["Bmass"] = random.gauss(mass + dmass , sqrt(s_d**2-s_mc**2))
    entry["Bmass_missid"] =entry["Bmass"]
    
    return 1
       
        
def mixup( rnd = 0.,dmass = 5284.63-5279.5, s_mc=20,s_d=24.8, misid = 1):
    fdfs = 3.71
    sfdfs = 0.47
    fi = 1./fdfs
    pipikpi =.513/1.95
    kkkpi = 3.5/1.95
    kpikk = .505/3.5
    if misid:
        print "Mixing with misid probs"
        pipikpi *= 0.3226/0.1484  ## last ratio is misid correction
        kkkpi *= 0.066/0.1484
        kpikk *= 0.1484/.066
   
    
    if rnd:
        fdfs = random.gauss(fdfs,sfdfs)
        pipikpi = random.random(0.9,1.1) * pipikpi
        kkkpi = random.random(0.6,1.4) * kkkpi
        kpikk = random.random(0.6,1.4) * kpikk

    a = len(bdkpi)
    b = len(bdpipi)*1/pipikpi
    c = len(bskk)*fdfs*1./kkkpi
    print a , b, c
    m = min(a,b,c)
         
    if m == c:#fi*kkkpi > pipikpi:
        print "1"
        Nkk = len(bskk)
        Npipi = round(pipikpi/(fi*kkkpi)*Nkk)
        Nkpi = round((1./pipikpi)*Npipi)
        
    elif m == b:
        print "2"
        Npipi = len(bdpipi)
        Nkk = round(1./(pipikpi/(fi*kkkpi))*Npipi)
        Nkpi = round((1./pipikpi)*Npipi)
    else:
        print "3"
        Nkpi = len(bdkpi)
        Npipi = round(pipikpi*Nkpi)
        Nkk = round(1./(pipikpi/(fi*kkkpi))*Npipi)
    
    Nskpi = round(kpikk*Nkk)
    all = []
       
    for i in range(Nkpi):
        entry = bdkpi[i]
        if s_d != -1: skrew_up_masses(entry, dmass= dmass, s_mc = s_mc, s_d = s_d)
        all.append(entry)
    for i in range(Nskpi): #### warning: cheating Bs Kpi because I've lost the NTuple
        entry = bskpi[i]
       # print entry["Bmass"]
        if s_d != -1:skrew_up_masses(entry, dmass= dmass , s_mc = s_mc, s_d = s_d)
        #print entry["Bmass"]
        #print "======"
        all.append(entry)
    for i in range(Nkk):
        entry = bskk[i]
        if s_d != -1: skrew_up_masses(entry, dmass= dmass, s_mc = s_mc, s_d = s_d)
        all.append(entry)
    for i in range(Npipi):
        entry = bdpipi[i]
        if s_d != -1: skrew_up_masses(entry, dmass= dmass, s_mc = s_mc, s_d = s_d)
        all.append(entry)

    print "Nkpi", Nkpi
    print "Nkk", Nkk
    print "Npipi", Npipi
    print "Nskpi", Nskpi
    
    all = channelData(all)
    all.save("~/vol5/MCbhh_mixed_2012_misidp_Overpesimistic_fdfsm1s_rnd"+str(rnd))
#mixup(dmass = -7.5)

#mixup()


def doplot(t, fiter, m, limits = [4800, 5900]):
    from ROOT import kTRUE
    op = fiter(t,m,mct_inc + "&& "+m+ ">" + str(limits[0]) + "&& " + m + "<" + str(limits[1]))
    op.nbkg.setVal(0)
    op.nbkg.setConstant(kTRUE)
    op.model.fitTo(op.data)
    return op, op.plot()


def doNbins(N, s0):
    st = (1-s0)*1./N
    l = []
    for i in range(N+1):
        l.append(s0 + st*i)
    return l

def testbins(s0, ns = range(1,20)):
   # from ROOT import TH1F
    hg = TH1F("A","A",ns[-1], 0.5, ns[-1]+0.5)
    hg2 = TH1F("b","b",ns[-1], 0.5, ns[-1]+0.5)
    for n in ns:
        bins = doNbins(n,s0)
        print bins
        h = do_distribution(t, B.InclusiveFiter01,"GLsb.", bins,"Bmass>4900 && Bmass<5700")
        tot = 0
        stot = 0
        for j in range(h.GetNbinsX()):
            print "0/0/0"
            tot+= h.GetBinContent(j+1)
            stot += h.GetBinError(j+1)**2
            print tot,"+-", sqrt(stot)
        stot = sqrt(stot)
        hg.SetBinContent(n,tot)
        hg.SetBinError(n,stot)
        hg2.SetBinContent(n, stot)
    return hg, hg2







def getCosTheta(t):
    p1 = t.mu1ptot
    p2 = t.mu2ptot
    return (Mmu**2 -0.5*t.Bmass**2 + sqrt( (p1*p1  +Mmu**2)*(p2*p2  +Mmu**2)) )/(p1*p2)
    
    
def getMass(M1,M2,p1,p2,t):
    #p1 = t.mu1ptot
    #p2 = t.mu2ptot
    return sqrt(M1**2 + M2**2 +  2* (sqrt( (p1**2+M1**2)*(p2**2+M2**2)) -p1*p2*getCosTheta(t)))

var = "(mu1ptot - sqrt(mc_mu1_px^2 + mc_mu1_py^2 + mc_mu1_pz^2))/sqrt(mc_mu1_px^2 + mc_mu1_py^2 + mc_mu1_pz^2)"

def doH(t):
    h = TH1F("A","A",100,-0.1,0.1)
    for entry in t:
        #if not entry.mu1ismu: continue
        mu1ptot = entry.mu1ptot
        #mu2ptot = entry.mu2ptot
        mc_mu1_px = entry.mc_mu1_px
        mc_mu1_py = entry.mc_mu1_py
        mc_mu1_pz = entry.mc_mu1_pz
        mcp = sqrt(mc_mu1_px**2 + mc_mu1_py**2 + mc_mu1_pz**2)
        if not mcp: continue
        
        h.Fill((mu1ptot - mcp)/mcp)

    return h


## f = TFile("~/vol5/MC10_bskk_stripping17.root")
## t = f.Get("B2hh")#/B2hh")
## f2 = TFile("/tmp/crap", "recreate")
## t2 = t.CopyTree(mct_inc + aa + fiducial0 + aa + "mu1ismu && PIDk1<10 && PIDmu1>-5" )
## f1 = TF1("W","[0]*exp(-0.5*((x-[1])/[2])^2) +[3]*exp(-0.5*((x-[4])/[5])^2) ")
## f1.SetParameter(0,400)
## f1.SetParameter(1,-0.005)
## f1.SetParameter(2,0.005)
## f1.SetParameter(3,11.)
## f1.SetParameter(4,-0.005)
## f1.SetParameter(5,0.02)
## h = doH(t2)
## h.Fit("W","LL")

### Pion, DLL
                    #EDM=5.19411e-08    STRATEGY= 1  ERROR MATRIX UNCERTAINTY   1.7 per cent
##   EXT PARAMETER                                   STEP         FIRST   
##   NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
##    1  p0           1.69634e+02   7.08501e+00   2.01544e-02   1.59251e-05
##    2  p1           1.74252e-05   1.76008e-04   3.95796e-07  -2.29502e-01
##    3  p2           4.82443e-03   1.67438e-04  -4.73090e-07   7.75857e-01
##    4  p3           1.11642e+01   8.07570e-01   3.05659e-03  -5.40936e-05
##    5  p4          -3.15376e-02   1.93634e-03  -5.87456e-07   1.20205e-02
##    6  p5           3.06433e-02   1.20827e-03   8.63970e-07  -2.61009e-01
##                                ERR DEF= 0.5
## >>> 

### Pion,NO  DLL
##  EXT PARAMETER                                   STEP         FIRST   
##   NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
##    1  p0           1.96143e+02   7.72555e+00   3.93376e-02   1.25453e-04
##    2  p1           4.70940e-05   1.60761e-04   7.44805e-07  -2.36855e+00
##    3  p2           4.73123e-03   1.53585e-04  -6.66723e-07   3.59091e+00
##    4  p3           1.16321e+01   8.28600e-01  -5.14565e-03  -8.79789e-04
##    5  p4          -3.11790e-02   1.86842e-03  -7.02915e-06  -5.86751e-02
##    6  p5           3.06227e-02   1.17491e-03   8.23169e-06  -7.59137e-01
      
## Kaon, DLL

##   1  p0           5.35791e+01   3.65008e+00   6.20377e-02   5.80770e-06
##    2  p1          -3.73239e-04   3.42303e-04   7.33286e-06   1.65518e-01
##    3  p2           5.79992e-03   3.30902e-04   4.97481e-06  -1.51599e-01
##    4  p3           2.23105e+00   3.79567e-01   4.82313e-03  -3.24378e-04
##    5  p4          -2.41388e-03   5.02426e-03   1.09669e-04  -9.48718e-03
##    6  p5           5.05413e-02   5.96430e-03   8.11840e-05  -9.92593e-04
 
## ###
###    Kaon, NO DLL
##  NO.   NAME      VALUE            ERROR          SIZE      DERIVATIVE 
##    1  p0           3.62993e+02   1.03773e+01   3.87372e-03   1.31539e-06
##    2  p1           8.56869e-05   1.07467e-04   2.62564e-08   4.50749e-02
##    3  p2           4.48716e-03   9.26598e-05  -1.08928e-07   1.24367e+00
##    4  p3           6.65584e+00   5.92065e-01  -5.19241e-05   4.62534e-05
##    5  p4          -2.67455e-03   2.81933e-03  -2.66028e-06   1.47787e-02
##    6  p5           4.89730e-02   3.08234e-03   1.45489e-06  -3.27984e-03
   
## h = TH1F("A","A", 100,4800, 6000)
## h2 = TH1F("A","A", 100,4800, 6000)
## h3 = TH1F("A","A", 100,4800, 6000)

## for i in range(t.GetEntries()):
##     a = t.GetEntry(i)
##     a = h.Fill(t.Bmass)
##     p1 = t.mu1ptot
##     p2 = t.mu2ptot
##     Th = getCosTheta(t)
##     pmc = vector(t.mc_mu1_px, t.mc_mu1_py,t.mc_mu1_pz)
##     pmc = vmod(pmc)
##     if t.mu1ismu: h2.Fill(t.Bmass)
    
##     #if not t.mc1: continue
##     p1 = misid_p(pmc,p1,t.mc1)
##    # print p1, t.mu1ptot
##     mass = getMass(Mmu,Mmu,p1,p2,t)
##    # print "M:", mass
##     h3.Fill(mass)

## h2.SetLineColor(kRed)
## h3.SetLineColor(kBlue)
## h.DrawNormalized()
## h2.DrawNormalized("Same")
## h3.DrawNormalized("same")


## f = TFile("~/vol5/MCbhh_mixed_X_misidp_rnd0.0.root")
## t = f.Get("T")
## print t.GetEntries("GLKsm_MC10sb.>0.5 && abs(Bmass-5272)<60")*1./t.GetEntries("GLKsm_MC10sb.>0.5")

## print t.GetEntries("GLKsm_MC10sb.>0.5 && abs(Bmass-5358)<60")*1./t.GetEntries("GLKsm_MC10sb.>0.5")

## print t.GetEntries("GLKsm_MC10sb.>0.5 && Bmass<5212")*1./t.GetEntries("GLKsm_MC10sb.>0.5")

## print t.GetEntries("GLKsm_MC10sb.>0.5 && abs(Bmass_sm-5272)<60 && mu1ismu && mu2ismu")*1./t.GetEntries("GLKsm_MC10sb.>0.5&& mu1ismu && mu2ismu")

## print t.GetEntries("GLKsm_MC10sb.>0.5 && abs(Bmass_sm-5358)<60 && mu1ismu && mu2ismu")*1./t.GetEntries("GLKsm_MC10sb.>0.5&& mu1ismu && mu2ismu")

## print t.GetEntries("GLKsm_MC10sb.>0.5 && Bmass_sm<5212 && mu1ismu && mu2ismu")*1./t.GetEntries("GLKsm_MC10sb.>0.5&& mu1ismu && mu2ismu")


f2 = TFile("~/vol5/MCbhh_mixed_2012_misidp_Pesimistic_fdfsm1s_rnd0.0.root")
t2 = f2.Get("T")
f1 = TFile("~/vol5/MCbhh_mixed_2012_misidp_Optimistic_fdfsm1s_rnd0.0.root")
t1 = f1.Get("T")
f = TFile("~/vol5/MCbhh_mixed_2012_misidp_0mistic_fdfsm1s_rnd0.0.root")
t = f.Get("T")

f3 = TFile("~/vol5/MCbhh_mixed_2012_misidp_Overpesimistic_fdfsm1s_rnd0.0.root")
t3 = f3.Get("T")


## fh = TFile("misid_Bs.root","recreate")
## from array import array as afC
## b = afC("d", [5312.96, 5324.96, 5336.96, 5342.96, 5354.96, 5390.96, 5402.96, 5408.96, 5420.96, 5432.96])
## #b = afC("d",[5224.6300000000001, 5236.6300000000001, 5248.6300000000001, 5254.6300000000001, 5266.6300000000001, 5302.6300000000001, 5314.6300000000001, 5320.6300000000001, 5332.6300000000001, 5344.6300000000001])
## h1 = TH1F("misid Bs sm","misid Bs sm", len(b)-1, b)
## h2 = TH1F("misid Bs nom","misid Bs nom", len(b)-1, b)
## h3 = TH1F("misid Bs pes","misid Bs pes", len(b)-1, b)

## for entry in t:
##     m = entry.Bmass
##     m0 = entry.Bmass_sm
##     if m+100 > b[0] and m<b[-1] : xxx = h2.Fill(m+100)
##     if m0 +100> b[0] and m0<b[-1] : xxx = h1.Fill(m0+100)
## h1.Scale(1./h1.GetSumOfWeights())
## h2.Scale(1./h2.GetSumOfWeights())
## for entry in t3:
##     m = entry.Bmass
##     #m0 = entry.Bmass_sm
##     if m +100> b[0] and m<b[-1] : xxx = h3.Fill(m+100)
##     #if m0 > b[0] and m0<b[-1] : xxx = h1.Fill(m0)
## h3.Scale(1./h3.GetSumOfWeights())
## h1.Write()
## h2.Write()
## h3.Write()

## fh.Close()
