from ROOT import *

from Urania.Helicity import *
#AccessPackage("Urania")
#import Helicity as H
from Urania.SympyBasic import *
from Urania.RooInterfaces import *
from os import *

MyTransAmplitudes = {}

MyTransAmplitudes["A0"] = Symbol("A_0")
MyTransAmplitudes["Apa"] = Symbol("A_pa")
MyTransAmplitudes["Ape"] = Symbol("A_pe")
MyTransAmplitudes["ASS"] = Symbol("A_SS")
MyTransAmplitudes["ASplus"] = Symbol("A_Splus")
MyTransAmplitudes["ASminus"] = Symbol("A_Sminus")
for key in MyTransAmplitudes:
    amp = str(MyTransAmplitudes[key])
    if key not in TransAmpModuli.keys(): TransAmpModuli[key] = Symbol(amp+"_mod",positive = True)
    if key not in TransAmpPhases.keys(): TransAmpPhases[key] = Symbol("delta" + amp.replace("A",""),real = True)

### convencion delta0 = 0
TransAmpPhases.pop("A0")

Hmod, Hphases = {}, {}
A = doB2XhhYhh([1],range(2))
A = A.subs([(H["Ja1_Jb1_0"], MyTransAmplitudes["A0"]), (H["Ja1_Jb1_1"],1/Sqrt(2)*( MyTransAmplitudes["Apa"] + MyTransAmplitudes["Ape"])),(H["Ja1_Jb1_-1"],1/Sqrt(2)*( MyTransAmplitudes["Apa"]-MyTransAmplitudes["Ape"]))]) ### De momentosolo te sustituyo los del PP-wave....
A = A.subs([(H["Ja0_Jb0_0"], MyTransAmplitudes["ASS"]), (H["Ja1_Jb0_0"],1/Sqrt(2)*( MyTransAmplitudes["ASplus"] + MyTransAmplitudes["ASminus"])),(H["Ja0_Jb1_0"],1/Sqrt(2)*( MyTransAmplitudes["ASplus"]-MyTransAmplitudes["ASminus"]))]) ### Y las Ss, SP
A = A.expand()/9 ### Normalizacion de London

for key in H:
    amp = str(H[key])
    Hmod[key] = Symbol(amp+"_mod",positive = True)
    Hphases[key] = Symbol("delta" + amp.replace("H",""),real = True)


pdf_split = DecomposeAmplitudes(A,MyTransAmplitudes.values() + H.values())


### Deleting terms not present in the Untagged fit
pdf_delete = {}
ape = TransAmplitudes["1_pe"]
asp = TransAmplitudes["asp"]
for ak in TransAmplitudes.values():
    if ape!=ak: 
        _re, _im = TermsAsReImag(A,ak,ape)
        pdf_delete[re(ak*ape.conjugate())]=_re
        pdf_delete[im(ak*ape.conjugate())]=_im
        pdf_delete[re(ape*ak.conjugate())]=_re
        pdf_delete[im(ape*ak.conjugate())]=_im

    if asp!=ak:
        _re, _im = TermsAsReImag(A,ak,asp)
        pdf_delete[re(ak*asp.conjugate())]=_re
        pdf_delete[im(ak*asp.conjugate())]=_im
        pdf_delete[re(asp*ak.conjugate())]=_re
        pdf_delete[im(asp*ak.conjugate())]=_im


phys = 0

def MyStrongPhases(expr, free_delta0=0):
    """ Modifies a term written as A1*conj(A2) as a function of the strong phases
    """
    modlist = []
    #DefineStrongPhases()
    for key in MyTransAmplitudes.keys():
        if key == "A0" and not free_delta0:
            modlist.append( (MyTransAmplitudes[key], TransAmpModuli[key]))
            continue
        modlist.append( (MyTransAmplitudes[key],TransAmpModuli[key]*Exp(I*TransAmpPhases[key])) )
    for key in H.keys(): ### These we keep in Helicity formalism because... well, because I don't know otherwise
        modlist.append( (H[key],Hmod[key]*Exp(I*Hphases[key])) )
    f = expr.func
    if f in [im,re]:
        arg = expr.args[0]
        arg = arg.subs( modlist )
        arg = arg.rewrite(Exp,Cos)
        return simplify(f(arg))
    out = expr.subs( modlist )
    out = out.rewrite(Exp,Cos)
    return simplify(out)


for key in pdf_split: phys += MyStrongPhases(key)*pdf_split[key]

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

##### Generate and compile a fitting class corresponding to "func"

### Trial 1, w/o analytical integrals

potential_list = [x,y,z]+TransAmpModuli.values() + TransAmpPhases.values() + Hmod.values() + Hphases.values()  ### Esto es una chapuza, por no pensar cuales son los parametros del modelo, meto todas
                                                                                                               ### las amplitudes y phases, y luego filtro las que no estan en la formula :D
final_list = []
for thing in potential_list:
     if thing in func.atoms() and thing not in final_list: final_list.append(thing)

op2 = RooClassGenerator(func, final_list ,"RooCrap")

### Define intermediate variables to be calculated once
op2.addSubstitutions([(Sqrt(-x**2+1),"sthk"),(Sqrt(-y**2+1),"sthl"),((-x**2+1),"sthk2"),((-y**2+1),"sthl2")])

op2.addSubstitutions([(x**2,"cthk2"),(y**2,"cthl2"),(Cos(z)**2,"cosphi2"),(Sin(z)**2,"sinphi2"),(Cos(z),"cosphi"),(Sin(z),"sinphi")])
### Mira si puedes poner cosas como las de abajo, para hacer el codigo mas rapido

#op2.addSubstitutions([(Sqrt(s_As2),"As"),(Sqrt(s_fD),"sqfD")])
#op2.addSubstitutions([(Sqrt(s_fL),"sqfL"),(Sqrt(s_xpa),"sqxpa")])
#op2.addSubstitutions([(Sqrt(s_f2L),"sqf2L"),(Sqrt(s_x2pa),"sqx2pa")])
#op2.addSubstitutions([(Cos(TransAmpPhases["2_0"]), "cdelta20"),(Cos(TransAmpPhases["2_pa"]), "cdelta2pa"),(Cos(TransAmpPhases["2_pe"]), "cdelta2pe")])
#op2.addSubstitutions([(Sin(TransAmpPhases["2_0"]), "sdelta20"),(Sin(TransAmpPhases["2_pa"]), "sdelta2pa"),(Sin(TransAmpPhases["2_pe"]), "sdelta2pe")])
#op2.addSubstitutions([(Cos(TransAmpPhases["1_pa"]), "cdelta_pa"),(Cos(TransAmpPhases["1_pe"]), "cdelta_pe")])
#op2.addSubstitutions([(Sin(TransAmpPhases["1_pa"]), "sdelta_pa"),(Sin(TransAmpPhases["1_pe"]), "sdelta_pe")])
#op2.addSubstitutions([(Sin(TransAmpPhases["0_0"]), "sdelta_s"),(Cos(TransAmpPhases["0_0"]), "cdelta_s")])


op2.makePdf(integrable = kTRUE)
op2.doIntegral(1,(x,-1,1))
op2.doIntegral(2,(y,-1,1))
op2.doIntegral(3,(z,-Pi,Pi))
op2.doIntegral(4,(x,-1,1),(y,-1,1))
op2.doIntegral(5,(x,-1,1),(z,-Pi,Pi))
op2.doIntegral(6,(y,-1,1),(z,-Pi,Pi))
op2.doIntegral(7,(x,-1,1),(y,-1,1),(z,-Pi,Pi))
op2.overwrite()

op2.invoke()
