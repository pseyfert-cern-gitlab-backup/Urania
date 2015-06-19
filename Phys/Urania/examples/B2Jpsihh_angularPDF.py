from Urania.Helicity import *
from Urania.SympyBasic import *
from os import *


### transAmp=1 : Changes to transversity amplitude basis
A = doB2VX([0,1],helicities=[-1,1],transAmp=1,transAng=0)

### massage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())
phys = 0
for key in pdf_split: phys += StrongPhases(key)*pdf_split[key]


### change the free variables to cosines
x = Symbol("helcosthetaK",real = True)
y = Symbol("helcosthetaL", real = True)
z = Symbol("helphi", real = True)
CThL = Cos(ThetaL)
CThK = Cos(ThetaK)
def changeFreeVars(function):
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi,z)])

    return function

func = changeFreeVars(phys)


### Print out to a latex document
from Urania.LatexFunctions import *
flatex = file("BJspihh_PDF.tex","w")
begintex(flatex)

begin_multline(flatex)
i = 0
for key in pdf_split.keys():
    if i > 20:
        i = 0
        multline_break(flatex)
    if pdf_split[key]: flatex.write(Ulatex(key) + "\t" + Ulatex(pdf_split[key]) + "\\\\" + "\n")
    i += 1
end_multline(flatex)
flatex.write("\\end{document}\n")
flatex.close()

system("pdflatex " + "BJspihh__PDF")



BREAK
##### Generate and compile a fitting class corresponding to "A"
### Trial 1, w/o analytical integrals
from Urania.RooInterfaces import *

var_list = [x,y,z]+TransAmpModuli.values() + TransAmpPhases.values()

op = RooClassGenerator(func, var_list ,"RooB2Jpsihh")

### Define intermediate variables to be calculated once
op.addSubstitutions([(Sqrt(-x**2+1),"sthk"),(Sqrt(-y**2+1),"sthl"),((-x**2+1),"sthk2"),((-y**2+1),"sthl2")])
op.addSubstitutions([(x**2,"cthk2"),(y**2,"cthl2"),(Cos(z)**2,"cosphi2"),(Sin(z)**2,"sinphi2"),(Cos(z),"cosphi"),(Sin(z),"sinphi")])


op.makePdf(integrable = 1)
op.doIntegral(1,(x,-1,1))
op.doIntegral(2,(y,-1,1))
op.doIntegral(3,(z,-Pi,Pi))
op.doIntegral(4,(x,-1,1),(y,-1,1))
op.doIntegral(5,(x,-1,1),(z,-Pi,Pi))
op.doIntegral(6,(y,-1,1),(z,-Pi,Pi))
op.doIntegral(7,(x,-1,1),(y,-1,1),(z,-Pi,Pi))
op.overwrite()

op.invoke()
