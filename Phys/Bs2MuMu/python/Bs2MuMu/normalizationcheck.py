import scipy.stats
from math import *
alpha = 8.4e-09

#s = 0.14 # relative error
#s_alpha = s*alpha

poisson = scipy.stats.poisson
sq2pi = 1./sqrt(2*pi)

from ROOT import *


def gauss(a,sigma,x):
    sigmai = 1./sigma
    return sigmai *sq2pi*exp( -0.5 * ((x-a)*sigmai)**2)


def toylimit(N, s, CL):
    l = []
    brs = {}
    for i in range(100):
        brs[alpha*i*.1] = 0.
        
    #p = poisson(N)
    
    
    def addToBr(br, prob):
        q = []
        for key in brs.keys():
            q.append([abs(key-br),key])
        q.sort()
        brs[q[0][1]] += prob
    s_alpha = s*alpha
    h1 = TH2F("A","A",10, alpha - 3*s_alpha, alpha+3*s_alpha,10,0,10)
    h2 = TH2F("B","B",10, alpha - 3*s_alpha, alpha+3*s_alpha,10,0,10)
    
    delta_a = 3*s_alpha/50
    Px = 0
    #Py = 0
    dn = 0.1
    for i in range(1,100):
        n = dn*i
        p = poisson(n)
        pndn = p.pmf(N)*dn
        Px +=pndn
        Py = 0
        for j in range(100):
            beta = alpha -3*s_alpha + j*delta_a
            pbdb = gauss(alpha,s_alpha,beta)*delta_a
           # print pb, pn
            br = beta*n
            Py += pbdb
            h1.Fill(beta, n, pbdb*pndn)
            if br>3.8e-08 and br<4.2e-08:  h2.Fill(beta, n, pbdb*pndn)
            addToBr(br,pbdb*pndn)
    print Px, Py
    z = brs.keys()
    z.sort()
    P = 0
    for x in z:
        P+= brs[x]
        if P>CL: break
    return x#, h1,h2
            

g90 = TGraph()
g95 = TGraph()
for i in range(1,60):
    g95.SetPoint(i,.01*i, toylimit(1,.01*i,.95))
    g90.SetPoint(i,.01*i, toylimit(1,.01*i,.90))
## ###
##     ****************************************
## Minimizer is Linear
## Chi2                      =	3.65214e-18
## NDf                       =	52
## p0                        =	4.02354e-08  	+/-	1.46497e-10 
## p1                        =	4.64336e-09  	+/-	1.03983e-09 
## p2                        =	2.33697e-08  	+/-	1.58621e-09
##     >>> g90.Draw("AL")
## <TCanvas::MakeDefCanvas>: created default TCanvas with name c1
## >>> 
## ****************************************
## Minimizer is Linear
## Chi2                      =	3.5603e-18
## NDf                       =	52
## p0                        =	3.27709e-08  	+/-	1.44641e-10 
## p1                        =	1.68509e-09  	+/-	1.02664e-09 
## p2                        =	1.4243e-08   	+/-	1.56608e-09 
