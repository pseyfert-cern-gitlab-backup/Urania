from Urania.Helicity import *
from Urania.SympyBasic import *
from os import *

DiLeptonSpins = [0,1,2] ## DMS: I doube we'll need 2, probably we'll only
                    ## have Pwave (J=1) from the photon, plus maybe some S-wave (J=0)
### transAmp=1 : Changes to transversity amplitude basis
A = doKsPizeroMuMu(DiLeptonSpins ) ## This is now in Urania.Helicity

### massage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())
phys = 0
for key in pdf_split: phys += StrongPhases(key)*pdf_split[key]


### change the free variables to cosines
x = USymbol("helcosthetaK","c\\theta_{K}",real = True)
y = USymbol("helcosthetaL", "c\\theta_{l}", real = True)
z = USymbol("helphi" , "\\phi", real = True)
CThL = Cos(ThetaL)
CThK = Cos(ThetaK)
def changeFreeVars(function):
    ### Phi now as in DTT !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    function  = function.subs( Sin(2*ThetaK), 2*Sin(ThetaK)*Cos(ThetaK))
    function  = function.subs( Sin(2*ThetaL), 2*Sin(ThetaL)*Cos(ThetaL))

    function  = function.subs( Cos(2*ThetaK), 2*Cos(ThetaK)**2 - 1)
    function  = function.subs( Cos(2*ThetaL), 2*Cos(ThetaL)**2 - 1)
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi, -z)])

    return function



func = changeFreeVars(phys)


### Print out to a latex document
from Urania.LatexFunctions import *
flatex = file("Kspizeromm_PDF.tex","w")
begintex(flatex)

begin_multline(flatex)
i = 0
for key in pdf_split.keys():
    if i > 20:
        i = 0
        multline_break(flatex)
    if pdf_split[key]:
        flatex.write(Ulatex(key) + "\t" + Ulatex(pdf_split[key]) + "\\\\" + "\n")
        i += 1
end_multline(flatex)
flatex.write("\\end{document}\n")
flatex.close()

system("pdflatex " + "Kspizeromm_PDF")

print "angular function saved in Kspizeromm_PDF.pdf"
print "Now making RooFit class as well"


##BREAK
##### Generate and compile a fitting class corresponding to "A"
### Trial 1, w/o analytical integrals
from Urania.RooInterfaces import *

potential_list = [x,y,z]+TransAmpModuli.values() + TransAmpPhases.values()
final_list = []
for thing in potential_list:
    if thing in func.atoms(): final_list.append(thing)
 
op = RooClassGenerator(func, final_list ,"RooKspizeroMM")

### Define intermediate variables to be calculated once

op.makePdf(integrable = 1)
op.doIntegral(1,(y,-1,1))#,(y,-1,1),(z,-Pi,Pi))
##op.doIntegral(2,(x,-1,1),(y,-1,1))
##op.doIntegral(3,(x,-1,1),(z,-Pi,Pi))
##op.doIntegral(4,(y,-1,1),(z,-Pi,Pi))
op.overwrite()

op.invoke()
