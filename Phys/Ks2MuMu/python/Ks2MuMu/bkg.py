from ROOT import *
from SomeMassModels.KsmmBkgModels import *
from SomeMassModels.sidebands import *
gROOT.ProcessLine(".L RooPowerLaw.cxx++")
from histoTex import *
from fiducial import *
import cPickle

sample = "A"
trigger = "TIS"
trig = tis
bdtname = "BDTD"
if trigger == "TOS" :
     fiducial = fiducialtos
     trig = xtos
     bdtname += trigger
fiducial += aa + dll
bdtname+=sample

eps = cPickle.load(file("eps_" + trigger))
f = TFile("~/vol5/ks/ksmumu1fb" +str(sample)+"_" + trigger + ".root")
     
t = f.Get("T")
def expo_and_powerLaw (fiter):
     fiter.mean_bkg  =RooRealVar("mean_bkg", "mean_bkg", 448., 200, 470.)
     fiter.ind_bkg   =RooRealVar("ind_bkg",  "ind_bkg" ,1.1,80.)
     fiter.indx  = RooRealVar("k", "k", -1.e-04, -1.e-02, 0.01)
     fiter.f_peak= RooRealVar("f_peak"  ,"f_peak"  ,0.2, 0., 1.)
     fiter.peakbg=RooPowerLaw('poln',"poln",fiter.mass, fiter.mean_bkg, fiter.ind_bkg)
     fiter.expbkg=RooExponential("expbkg", " exp background pdf", fiter.mass, fiter.indx)

     fiter.bkg  =RooAddPdf( 'peak_expo',  'peak_expo',  fiter.peakbg, fiter.expbkg, fiter.f_peak  )

     return 1


def InvCB_bkg(fiter):
    #f#iter.mean = RooRealVar("mean","mean",5200, 5400)#5168.)
    fiter.sigma_bkg = RooRealVar("sigma bkg","sigma bkg", 2.,6)#35.)
    #fiter.n = RooRealVar("exponent", "exponent",1.)
    fiter.a_bkg = RooRealVar("transition bkg","transition bkg",-3,-0.5)
    fiter.mean_bkg  =RooRealVar("mean_bkg", "mean_bkg", 448., 400., 470.)
    fiter.ind_bkg   =RooRealVar("ind_bkg",  "ind_bkg" , 11.,1.,50.)
    fiter.indx  = RooRealVar("k", "k", -1.e-04, -1., 0.1)
    fiter.f_expo= RooRealVar("f_expo"  ,"f_expo"  ,0.5, 0., 1.)
    fiter.peakbg  = RooCBShape("peak bkg","peak", fiter.mass, fiter.mean_bkg, fiter.sigma_bkg, fiter.a_bkg, fiter.ind_bkg)
    fiter.expbkg=RooExponential("expbkg", " exp background pdf", fiter.mass, fiter.indx)

    fiter.bkg  =RooAddPdf( 'peak_expo',  'peak_expo',  fiter.peakbg, fiter.expbkg, fiter.f_expo  )

    return 1

#aa = "&&"
#tis = "L0Tis&&Hlt1Tis&&Hlt2Tis"
Mmin = 470
Mmax = 600
left = 492
right = 504

l = []

print Mmin, Mmax, sample
BKG = expo_and_powerLaw
warning = {}

BREAK
for i in range(10):
     
     op = sidebandsFiter(t,"Bmass",fiducial + aa + trig + "&& "+ bdtname + ">" +str(eps(1-i*0.1)) + "&& " +bdtname + "<" + str(eps(1-(i+1)*0.1)), left, right, bkgf = BKG , Mmin = Mmin, Mmax = Mmax, shorTime = False)
     if not op.nbkg.getAsymErrorHi():
          op.f_peak.setConstant(1)
          op.fit(op.data,shorTime=False)
          
     if not op.nbkg.getAsymErrorHi():
          #op.ind_bkg.setVal(40)
          op.ind_bkg.setConstant(1)
          op.fit(op.data,shorTime=False)
     if not op.nbkg.getAsymErrorHi():
          op.indx.setConstant(1)
          op.fit(op.data,shorTime=False)
     if not op.nbkg.getAsymErrorHi():
          op.mean_bkg.setConstant(1)
          op.fit(op.data,shorTime=False)
     
     l.append([op.nbkg.getVal(),op.nbkg.getError(), op.nbkg.getAsymErrorHi(),op.nbkg.getAsymErrorLo()])
     print t.GetEntries(fiducial+ aa + trig + "&&" + bdtname + ">" +str(eps(1-i*0.1)) + "&& " +bdtname + "<" + str(eps(1-(i+1)*0.1)) + aa + "Bmass>"+str(Mmin) + "&& Bmass<500"),  t.GetEntries(fiducial+ aa + trig + "&& " + bdtname + ">" +str(eps(1-i*0.1)) + "&& " +bdtname + "<" + str(eps(1-(i+1)*0.1)) + aa + "Bmass<"+str(Mmax) + "&& Bmass>500")

z = []
print trigger, sample
for i in range(len(l)):
     entry = l[i]
     #print t.GetEntries(fiducial+ aa + trig + "&& BDTD" + sample + ">" +str(eps(1-i*0.1)) + "&& BDTD" +sample + "<" + str(eps(1-(i+1)*0.1)) + aa + "Bmass>"+str(Mmin) + "&& Bmass<500"),  t.GetEntries(fiducial+ aa + trig + "&& BDTD" + sample + ">" +str(eps(1-i*0.1)) + "&& BDTD" +sample + "<" + str(eps(1-(i+1)*0.1)) + aa + "Bmass<"+str(Mmax) + "&& Bmass>500")

     if entry[2] and entry[3]:
          x, s1,s2,www = get_significant_digit(entry[0],entry[2], entry[3])
          print "bin ", i+1, "&", x , "_{"+str(s2)+"}^{+"+ str(s1) + "}"
          
     elif entry[2] :
          x, s1,s2,www = get_significant_digit(entry[0],entry[2], entry[0])
          print "bin ", i+1, "&", x , "_{"+str(s2)+"}^{+"+ str(s1) + "}"
     else:
          x, s1,s2,www = get_significant_digit(entry[0],entry[1], entry[1])
          print "bin ", i+1, "&",x , " \pm " , s1
     z.append(entry[0])


## 0.538599102884 _{-0.164711615678}^{+0.319807493918}
## 2.58594846068 _{-0.948724599179}^{+1.17632189025}
## 0.811119349571 _{-0.370932368339}^{+0.60472185941}
## 0.470688025713 _{-0.218639670408}^{+0.333363760094}
## 0.354817911087 _{-0.2319334562}^{+0.436305708369}
## 1.09417291695 _{-1.09417291695}^{+0.724400149408}
## 0.107169672755 _{-0.101261065762}^{+0.275844831354}
## 0.0126669048069 _{-0.0110924640766}^{+0.127268675162}
## 0.232845391818 _{-0.232845391818}^{+0.335910573464}
## 0.217862565585 _{-0.15758449212}^{+0.265468258734}

TOSA = [2.0417486942769583, 0.96621259573219054, 0.22661552817230668, 0.23372795473266716, 0.32395166564186456, 0.17291788039439288, 0.14897716390374083, 0.47137062648403916, 0.0021655358911720768, 0.67740756921980116]
TOSB = [1.6505608878849158, 1.0663438928460929, 0.42138143544254436, 0.39714584217267146, 0.30581062264863768, 0.0094121611362196766, 0.019611035243595087, 0.83674484757307832, 0.009634675636172263, 0.023961312378066868]
TISA =[3.1539571162946696, 1.1693954263868309, 2.2078212486508626, 1.3205068425953814, 1.1370849978247177, 0.17910024727574303, 0.00066437472163433098, 0.17853951938967771, 2.6763411062891151e-05, 8.7197889676815521e-05]
TISB = [0.52913551421568572, 2.5662321283779308, 0.79399913527150701, 0.4633633584739475, 0.35641862533630997, 1.0710606735960353, 0.10503234791718125, 0.01149479704724754, 0.23062803867363491, 0.2171103218899102]

## TIS B
## bin  1 & 0.53 _{-0.16}^{+0.32}
## bin  2 & 2.57 _{-0.93}^{+1.2}
## bin  3 & 0.79 _{-0.35}^{+0.41}
## bin  4 & 0.46 _{-0.22}^{+0.33}
## bin  5 & 0.36 _{-0.22}^{+0.43}
## bin  6 & 1.07 _{-0.57}^{+0.75}
## bin  7 & 0.105 _{-0.099}^{+0.278}
## bin  8 & 0.0115 _{-0.0099}^{+0.1077}
## bin  9 & 0.23 _{0.23}^{+0.34}
## bin  10 & 0.22 _{-0.16}^{+0.27}
