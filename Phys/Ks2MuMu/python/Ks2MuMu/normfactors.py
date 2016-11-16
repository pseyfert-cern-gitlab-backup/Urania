from ROOT import *
from histoTex import *

eoff = []
eoff.append([0.77,0.18])
eoff.append([1.00,0.39])
eoff.append([0.84,0.18])
eoff.append([0.73,0.14])
eoff.append([0.90,0.14])
eoff.append([0.70,0.12])
eoff.append([0.68,0.15])
eoff.append([0.65,0.17])
eoff.append([1.17,0.54])
eoff.append([0.81,0.17])

NA = [5204, 5069, 5002, 5134, 5081, 5004, 4937 , 4692 , 4496 , 4067 ]
NB = [5134 , 5153 , 5202, 5276, 5319, 5223, 5467, 5368, 5365, 5480 ]

eidA, eidB = [], []

eidA.append([68.87 , 0.22]), eidB.append([68.65 , 0.22])
eidA.append([69.80 , 0.22]), eidB.append([69.18 , 0.22])
eidA.append([68.56 , 0.22]), eidB.append([69.65 , 0.22])
eidA.append([68.91 , 0.22]), eidB.append([68.29 , 0.22])
eidA.append([68.72 , 0.22]), eidB.append([70.66 , 0.22])
eidA.append([68.87 , 0.22]), eidB.append([69.46 , 0.22])
eidA.append([67.73 , 0.21]), eidB.append([68.84 , 0.22])
eidA.append([68.82 , 0.22]), eidB.append([69.32 , 0.22])
eidA.append([69.00 , 0.22]), eidB.append([69.45 , 0.22])
eidA.append([69.48 , 0.22]), eidB.append([69.73 , 0.22])

for entry in eidA:
    entry[0] = entry[0]/100
    entry[1] = entry[1]/100

for entry in eidB:
    entry[0] = entry[0]/100
    entry[1] = entry[1]/100

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
prsc = 1./1000

def alpha_i(eof,s_eof, eid, s_eid, N):
    ef, sef = ratio(eof,eid,s_eof,s_eid)
    beta, sbeta = ratio(ef,N,sef,sqrt(N))
    alpha, salpha = product(beta, BR, sbeta,sBR)
    alpha, salpha, x , y = get_significant_digit(alpha, salpha, salpha)
    return "& $"+ str(prsc*alpha*1e07) + "\pm "+ str(prsc*salpha*1e07)+"$"
    #print "Val, err",  prsc*BR*ef/N, prsc*BR*sef/N
    #print "Val, tot err",  prsc*alpha, prsc*salpha

for i in range(10):
    eof, seof = eoff[i]
    eid, seid = eidA[i]
    N = NA[i]
    strinj = alpha_i(eof,seof,eid,seid,N)
    print str(i+1) + strinj + "\\\\"
print "Sample B"
for i in range(10):
    eof, seof = eoff[i]
    eid, seid = eidB[i]
    N = NB[i]
    strinj = alpha_i(eof,seof,eid,seid,N)
    print str(i+1) + strinj + "\\\\"
  
