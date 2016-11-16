from ROOT import *
from histoTex import *
from KsmmMathCrap import *
eoffA, eoffB = [], []

eoffA.append([0.619741499424,0.0161356490199])
eoffA.append([0.704002797604,0.0314906393161])
eoffA.append([0.69654661417,0.0393080760688])
eoffA.append([0.745312809944,0.048647780053])
eoffA.append([0.733579277992,0.060814228191])
eoffA.append([0.629234433174,0.0397782351362])
eoffA.append([0.754767596722,0.0682739734335])
eoffA.append([0.834207117558,0.1230894046])
eoffA.append([0.817752659321,0.119737249908])
eoffA.append([0.766114830971,0.0529896519813])

eoffB.append([0.609643042088,0.0169909991517])
eoffB.append([0.70308727026,0.0335610011418])
eoffB.append([0.64792650938,0.0309070804616])
eoffB.append([0.656402647495,0.0360817528407])
eoffB.append([0.779864609241,0.0588364080784])
eoffB.append([0.722584426403,0.0899681829835])
eoffB.append([0.766271531582,0.0601702153168])
eoffB.append([0.716127932072,0.0644998956796])
eoffB.append([0.722304582596,0.0724996760111])
eoffB.append([0.753790616989,0.059036296144])

NA = [8125L, 8629L, 9103L, 9579L, 9701L, 10111L, 9493L, 8586L, 7594L, 5124L]
#NB =[8868, 9154, 9316, 9471, 9629, 9873, 10030, 10096, 10136, 10157]
NB = [8807L, 9085L, 9234L, 9394L, 9559L, 9795L, 9956L, 9998L, 10043L, 10053L]

eidA, eidB = [], []

eidA.append([70.22 , 0.71]), eidB.append([69.93 , 3.06])
eidA.append([70.28 , 0.95]), eidB.append([70.41 , 1.09])
eidA.append([70.48 , 0.19]), eidB.append([70.27 , 0.79])
eidA.append([70.39 , 2.19]), eidB.append([70.52 , 0.83])
eidA.append([69.58 , 2.78]), eidB.append([70.46 , 1.83])
eidA.append([70.17 , 3.63]), eidB.append([70.55 , 2.45])
eidA.append([70.62 , 4.25]), eidB.append([70.35 , 1.96])
eidA.append([70.74 , 3.61]), eidB.append([70.90 , 4.63])
eidA.append([69.98 , 6.19]), eidB.append([70.86 , 8.02])
eidA.append([68.77 , 3.04]), eidB.append([70.20 , 3.71])


for entry in eidA:
    entry[0] = entry[0]/100
    entry[1] = entry[1]/100

for entry in eidB:
    entry[0] = entry[0]/100
    entry[1] = entry[1]/100

## def product(x,y, sx=0, sy=0):
##     r = x*y
##     if not sx :sx = sqrt(x)
##     if not sy : sy = sqrt(y)
##     if not x:
##         print "warning"
##         x = 1
##     if not y:
##         print "warning"
##         y = 1


##     sr = sqrt( (sx/x)**2 + (sy/y)**2)*r
##     return r,sr
## def ratio(a,b, sa = 0, sb=0):
##     if not sa: sa = sqrt(a)
##     if not sb: sb = sqrt(b)
##     if (b*a)!= 0: return a*1./b, sqrt( (sa/a)**2 + (sb/b)**2)*a*1./b
##     return 0,0

BR = 0.6920
sBR = .0#.05/100
prsc = 1./1000
mass = 1.08
smass = 0.04
def alpha_i(eof,s_eof, eid, s_eid, N):
    ef, sef = ratio(eof,eid,s_eof,s_eid)
    beta, sbeta = ratio(ef,N,sef,sqrt(N))
    alpha, salpha = product(beta, BR, sbeta,sBR)
    alpha, salpha = product(alpha, mass, salpha,smass)
    alpha, salpha, x , y = get_significant_digit(alpha, salpha, salpha)
    return "& $"+ str(prsc*alpha*1e08) + "\pm "+ str(prsc*salpha*1e08)+"$"
    #print "Val, err",  prsc*BR*ef/N, prsc*BR*sef/N
    #print "Val, tot err",  prsc*alpha, prsc*salpha

for i in range(10):
    eof, seof = eoffA[i]
    eid, seid = eidA[i]
    N = NA[i]
    strinj = alpha_i(eof,seof,eid,seid,N)
    eof, seof = eoffB[i]
    eid, seid = eidB[i]
    N = NB[i]
    strinj += alpha_i(eof,seof,eid,seid,N)
    print str(i+1) + strinj + "\\\\"
#print "Sample B"
#for i in range(10):
    #eof, seof = eoffB[i]
    #eid, seid = eidB[i]
    #N = NB[i]
    #strinj = alpha_i(eof,seof,eid,seid,N)
    #print str(i+1) + strinj + "\\\\"
  

def alpha_iL(eof,s_eof, eid, s_eid, N):
    ef, sef = ratio(eof,eid,s_eof,s_eid)
    beta, sbeta = ratio(ef,N,sef,sqrt(N))
    alpha, salpha = product(beta, BR, sbeta,sBR)
    alpha, salpha = product(alpha, mass, salpha,smass)
    alpha, salpha, x , y = get_significant_digit(alpha, salpha, salpha)
    return [prsc*alpha*1e08 , prsc*salpha*1e08]

for i in range(10):
    eof, seof = eoffA[i]
    eid, seid = eidA[i]
    N = NA[i]
    print "alphaA.append(", alpha_iL(eof,seof,eid,seid,N), ")"
    #print str(i+1) + strinj + "\\\\"
print "Sample B"
for i in range(10):
    eof, seof = eoffB[i]
    eid, seid = eidB[i]
    N = NB[i]
    print "alphaB.append(", alpha_iL(eof,seof,eid,seid,N),")"
    #strinj = alpha_i(eof,seof,eid,seid,N)
    #print str(i+1) + strinj + "\\\\"

#May 7, 2012


