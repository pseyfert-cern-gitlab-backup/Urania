from ROOT import *
from Urania import PDG
Unit = 1
print "Using GeV for the moment"
GF = 1.1e-11*Unit**2
print GF
lepton = "muon"#"electron"
pion = "pi0"#"piplus"
kaon = "K0"#"Kplus"
Mmu = getattr(PDG, lepton).mass/Unit
Mpi = getattr(PDG, pion).mass/Unit
MKs = getattr(PDG, kaon).mass/Unit

rl = Mmu/MKs
rpi = Mpi/MKs
MKs2 = MKs**2
rl2 = rl**2
rpi2 = rpi**2
b2 = -3.9e-08 ## update?
d2 = 0.2e-08 ## update ?
bc = 24.5e-08
dc = -1.6e-08
if kaon == "Kplus":
    alpha = -(bc + b2)
    beta = 2*(dc+d2)
    aS = -0.62 ## put correct number
    bS = -0.3 ##put correct number
else:
    alpha = 4./3 *b2 ## Use the KS ones, now using K+
    beta = -8./3*d2
    aS = 1.2 ## put correct number
    bS = 0.49 ##put correct number

z0 = 1./3 + rpi2
#from Urania.SympyBasic import *
from numpy import *
def G(z):
    if z < 4: return sqrt(4./z-1) *asin(sqrt(z)/2.)
    elif z == 4: return "Fuck off"
    else : return -0.5*sqrt(1-4./z)*(log( (1 - sqrt(1-4./z))/(1 + sqrt(1-4./z))) + 1j*pi)

def xi(z): return 4./9 - 4*rpi2/(3*z) -1./3 *(1 - 4*rpi2/z)*G(z/rpi2)

def F(z) : return 1 + z/2.5

def Wpipi(z, alpha = alpha, beta = beta): return 1./rpi2 *(alpha + beta *( z-z0 )/rpi2 )*F(z)*xi(z)
def W1(z, aS= aS, bS = bS): return GF*MKs*MKs*(aS+bS*z)
def W(z, aS=aS, bS=bS, alpha=alpha,beta=beta) : return W1(z, aS,bS) + Wpipi(z,alpha, beta)

def lam(a,b,c): return a**2 + b**2 + c**2 - 2*(a*b + a*c + b*c)

def dGdz(z, aS=aS,bS=bS, alpha= alpha, beta = beta) : return lam(1.0,z,rpi2)**(3./2)*sqrt(1-4*rl2/z)*(1+2*rl2/z)#*W(z,aS,bS,alpha,beta)*W(z,aS,bS,alpha,beta).conjugate()

def dGdm(m,aS=aS,bS=bS,alpha=alpha,beta=beta): return 2*m/MKs2 * dGdz (m*m/MKs2,aS,bS,alpha,beta)


Npoints = 100
step = (MKs - Mpi - 2*Mmu*1.00001)/Npoints
from array import array as afC
x = Double()
y = Double()
x2 = Double()
y2 = Double()

def do(aS= aS,bS = bS,b2 = b2,d2 = d2):
    g = TGraph()
    g2, g3, g4,g5, g6  = TGraph(), TGraph(), TGraph(), TGraph(), TGraph()
    alpha = 4./3 *b2 ## Use the KS ones, now using K+
    beta = -8./3*d2
    for i in range(Npoints):
        m = 2*Mmu*1.00001 + step*i
        z = m*m/MKs2
        print m ,dGdm(m,aS,bS,alpha,beta).real #abs(dGdm(m))
        g.SetPoint(i,m,dGdm(m,aS,bS,alpha,beta).real)
        Wpi2 = Wpipi(z,alpha,beta)*Wpipi(z,alpha,beta).conjugate()
        g2.SetPoint(i, z, Wpi2 *1e12)
        g3.SetPoint(i, z, W(z,aS,bS,alpha,beta)*W(z,aS,bS,alpha,beta).conjugate()*1e12)
        g4.SetPoint(i, z, W1(z,aS,bS)*W1(z,aS,bS).conjugate()*1e12)
        inter = W1(z,aS,bS)*Wpipi(z,alpha,beta).conjugate()*1e12
        g5.SetPoint(i, z, inter.real)
        g6.SetPoint(i, z, inter.imag)
        
        #g4.SetPoint(i,z, G(z/rpi2)*G(z/rpi2).conjugate())
        #g.Draw("AL")
    return g, g2,g3, g4,g5,g6
#g3.Draw("AL")
#g4.Draw("AL")
