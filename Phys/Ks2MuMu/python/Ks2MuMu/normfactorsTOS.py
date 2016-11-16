from ROOT import *
from fiducial import *
from histoTex import *
import cPickle
from KsmmMathCrap import *

eps = cPickle.load(file("eps_TOS"))
fmb = TFile("minbias.root")
tmb = fmb.Get("T")


eoffA, eoffB = [], []

eoffA.append([0.950652301311,0.301036395108])
eoffA.append([0.581049919128,0.179562435745])
eoffA.append([0.802769422531,0.312006477516])
eoffA.append([1.1546074152,0.41299420804])
eoffA.append([0.514910638332,0.194042511512])
eoffA.append([0.750933110714,0.277705928165])
eoffA.append([1.53992640972,0.914830914293])
eoffA.append([0.577663660049,0.211185095793])
eoffA.append([0.601687371731,0.237800835918])
eoffA.append([0.701687097549,0.109436884541])

eoffB.append([0.691381692886,0.125512672722])
eoffB.append([1.30542719364,0.517374351577])
eoffB.append([0.673821091652,0.185940208401])
eoffB.append([0.490690469742,0.165347470266])
eoffB.append([0.850407779217,0.35213329295])
eoffB.append([1.49424207211,0.997087893789])
eoffB.append([0.564610004425,0.161747873577])
eoffB.append([1.13661539555,0.467872694116])
eoffB.append([1.08737790585,0.849064501451])
eoffB.append([1.63465678692,0.668081336258])


noismu = "(!mu1ismu && !mu2ismu)"

NA, NB = [], []
for i in range(10):
    NA.append(tmb.GetEntries(fiducialtos +aa + mW+ "&&  BDTDTOSA>"+ str(eps(1-.1*i)) + "&& BDTDTOSA < " + str(eps(.9-.1*i ))))
    NB.append(tmb.GetEntries(fiducialtos + aa + mW +  "&&  BDTDTOSB>"+ str(eps(1-.1*i)) + "&& BDTDTOSB < " + str(eps(.9-.1*i ))))
eidA, eidB = [], []
eidA.append([17.13 , 2.74]), eidB.append([16.02 , 2.82])
eidA.append([16.88 , 2.70]), eidB.append([15.58 , 2.74])
eidA.append([17.24 , 2.76]), eidB.append([16.26 , 2.86])
eidA.append([16.63 , 2.66]), eidB.append([16.33 , 2.87])
eidA.append([16.11 , 2.58]), eidB.append([16.78 , 2.95])
eidA.append([15.47 , 2.48]), eidB.append([16.33 , 2.88])
eidA.append([15.62 , 2.50]), eidB.append([15.85 , 2.79])
eidA.append([15.57 , 2.49]), eidB.append([15.83 , 2.79])
eidA.append([15.49 , 2.48]), eidB.append([16.23 , 2.86])
eidA.append([14.78 , 2.37]), eidB.append([15.23 , 2.68])

for entry in eidA:
    entry[0] = entry[0]/100
    entry[1] = entry[1]/100

for entry in eidB:
    entry[0] = entry[0]/100
    entry[1] = entry[1]/100
    
frac_A = 3./6.8
frac_B = 3.8/6.8


def product(x,y, sx=0, sy=0):
    r = x*y
    if not sx :sx = sqrt(x)
    if not sy : sy = sqrt(y)
    if not x:
        print "warning"
        x = 1
    if not y:
        print "warning"
        y = 1


    sr = sqrt( (sx/x)**2 + (sy/y)**2)*r
    return r,sr
def ratio(a,b, sa = 0, sb=0):
    if not sa: sa = sqrt(a)
    if not sb: sb = sqrt(b)
    if (b*a)!= 0: return a*1./b, sqrt( (sa/a)**2 + (sb/b)**2)*a*1./b
    return 0,0

BR = 0.6920
sBR = 0.05/100
prsc = 2.7e-06
s_prsc = sqrt(0.7**2 + .3**2)*1e-06
mass = 1.08
smass = 0.04

def alpha_i(eof,s_eof, eid, s_eid, N):
    ef, sef = ratio(eof,eid,s_eof,s_eid)
    beta, sbeta = ratio(ef,N,sef,sqrt(N))
    alpha, salpha = product(beta, BR, sbeta,sBR)
    alpha, salpha = product(alpha, mass, salpha,smass)
    alpha, salpha, x , y = get_significant_digit(prsc*alpha, prsc*salpha, salpha)
    return "& $"+ str(alpha*1e08) + "\pm "+ str(salpha*1e08)+"$"
    

for i in range(10):
    eof, seof = eoffA[i]
    eid, seid = eidA[i]
    N = frac_A*NA[i]
    strinj = alpha_i(eof,seof,eid,seid,N)

    eof, seof = eoffB[i]
    eid, seid = eidB[i]
    N = frac_B*NB[i]
    strinj += alpha_i(eof,seof,eid,seid,N)
    print str(i+1) + strinj + "\\\\"
  

def alpha_iL(eof,s_eof, eid, s_eid, N):
    ef, sef = ratio(eof,eid,s_eof,s_eid)
    #print ef, sef
    beta, sbeta = ratio(ef,N,sef,sqrt(N))
    #print beta, sbeta
    alpha, salpha = product(beta, BR, sbeta,sBR)
    alpha, salpha = product(alpha, mass, salpha,smass)
    alpha, salpha, x , y = get_significant_digit(alpha, salpha, salpha)
    return [prsc*alpha*1e08 , prsc*salpha*1e08]

for i in range(10):
    eof, seof = eoffA[i]
    eid, seid = eidA[i]
    N = frac_A*NA[i]
    print "alphaTOSA.append(",alpha_iL(eof,seof,eid,seid,N),")"
    #print str(i+1) + strinj + "\\\\"
print "Sample B"
for i in range(10):
    eof, seof = eoffB[i]
    eid, seid = eidB[i]
    N = frac_B*NB[i]
    print "alphaTOSB.append(",alpha_iL(eof,seof,eid,seid,N),")"
    #strinj = alpha_i(eof,seof,eid,seid,N)
    #print str(i+1) + strinj + "\\\\"




## [1.4849999999999999, 0.54000000000000004]
## [1.4849999999999999, 0.51300000000000001]
## [2.7000000000000002, 1.161]
## [5.2380000000000004, 2.2949999999999999]
## [2.052, 0.83699999999999997]
## [3.1860000000000004, 1.2959999999999998]
## [6.4799999999999995, 4.0499999999999998]
## [2.1059999999999999, 0.83699999999999997]
## [1.9170000000000003, 0.83699999999999997]
## [0.7965000000000001, 0.18090000000000001]
## Sample B
## [0.74519999999999997, 0.19439999999999999]
## [1.9170000000000003, 0.83699999999999997]
## [1.2689999999999999, 0.40499999999999997]
## [1.026, 0.40499999999999997]
## [2.0249999999999999, 0.91800000000000004]
## [3.8340000000000005, 2.673]
## [1.6739999999999999, 0.56699999999999995]
## [3.4830000000000001, 1.5659999999999998]
## [3.5099999999999998, 2.9699999999999998]
## [5.0490000000000004, 2.1059999999999999]
