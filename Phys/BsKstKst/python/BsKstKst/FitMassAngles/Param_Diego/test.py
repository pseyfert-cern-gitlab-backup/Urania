from ROOT import *
from math import *
from array import *
from Urania import PDG
from Urania.Helicity import *
from Urania import RooInterfaces as D


#     ftin = open("int_tmp.txt","r")
#     line = ""
#     while True:
#         line_ = ftin.readline()
#         if not line_: break
#         line += line_[:-1]


# def no_rule(m):

#     prev = m.group(1)
#     inside = m.group(2)
#     after = ""
#     if len(m.groups())>2: after = m.groups(3) 
    
#     m2 = match(r"\A([^=]+)([\^\-\*/\+=]=?)([^\]]+)\Z",prev)
    
#     return parse(m2.group(1))+translateOperator(m.group(2))+translateFunction(m.group(3))+"("+parse(inside)+")"

#     rules = (
#         (r"\A(\w+)\[([^\]]+[^\[]*)\]\Z",  # Function call
#         lambda m: translateFunction(
#             m.group(1)) + "(" + parse(m.group(2)) + ")" ),

#         (r"\((.+)\)\((.+)\)",  # Parenthesized implied multiplication
#         lambda m: "(" + parse(m.group(1)) + ")*(" + parse(m.group(2)) + ")" ),

#         (r"\((.+)\)\/\((.+)\)",  # Parenthesized division
#         lambda m: "(" + TranslateMathematica(m.group(1)) + ")/(" + TranslateMathematica(m.group(2)) + ")" ),

#         (r"\A\((.+)\)\Z",  # Parenthesized expression
#         lambda m: "(" + parse(m.group(1)) + ")" ),

#         (r"\A(.*[\w\.])\((.+)\)\Z",  # Implied multiplication - a(b)
#         lambda m: parse(m.group(1)) + "*(" + parse(m.group(2)) + ")" ),

#         (r"\A\((.+)\)([\w\.].*)\Z",  # Implied multiplication - (a)b
#         lambda m: "(" + parse(m.group(1)) + ")*" + parse(m.group(2)) ),

#         (r"\A([\d\.]+)([a-zA-Z].*)\Z",  # Implied multiplicatin - 2a
#         lambda m: parse(m.group(1)) + "*" + parse(m.group(2)) ),

#         (r"\A([^=]+)([\^\-\*/\+=]=?)([^\]]+)\Z",  # Infix operator
#         lambda m: parse(m.group(1)) + translateOperator(m.group(2)) + parse(m.group(3)) ) ,

#         (r"(.+)\[([^\]]+[^\[]*)\](\)?)\Z", no_rule))

#     for rule, action in rules:
#         m = match(rule, line)
#         if m: break
   

# Generate the pdf using the tools in Urania.Helicity
A = doB2VX([0,1,2], helicities = [0], transAmp = 1)#0)
### masage a bit the expression to make it more suitable for fitting
pdf_split = DecomposeAmplitudes(A,TransAmplitudes.values())#H.values())
pdf_delete = {}
ape = TransAmplitudes["1_pe"]
for ak in TransAmplitudes.values():
    if ape==ak: continue
    _re, _im = TermsAsReImag(A,ak,ape)
    pdf_delete[re(ak*ape.conjugate())]=_re
    pdf_delete[im(ak*ape.conjugate())]=_im
    pdf_delete[re(ape*ak.conjugate())]=_re
    pdf_delete[im(ape*ak.conjugate())]=_im
    

phys = 0
for key in pdf_split:
    if key in pdf_delete.keys():
        print "deleting ",key
        continue
    phys += StrongPhases(key)*pdf_split[key]

### change the free variables to cosines
x = Symbol("helcosthetaK",real = True)
y = Symbol("helcosthetaL", real = True)
z = Symbol("helphi", real = True)
CThL = Cos(ThetaL)
CThK = Cos(ThetaK)
def changeFreeVars(function):
    function  = function.subs( Sin(2*ThetaK), 2*Sin(ThetaK)*Cos(ThetaK) )
    function  = function.subs( Cos(2*ThetaK), Cos(ThetaK)**2 - Sin(ThetaK)**2)
    function  = function.subs( Sin(2*ThetaL), 2*Sin(ThetaL)*Cos(ThetaL) )
    function  = function.subs( Cos(2*ThetaL), Cos(ThetaL)**2 - Sin(ThetaL)**2)
    function  = function.subs( Sin(ThetaK), Sqrt(1-Cos(ThetaK)**2))
    function  = function.subs( Sin(ThetaL), Sqrt(1-Cos(ThetaL)**2))
    function = function.subs([(CThK,x),(CThL,y), (Phi,z)])

    return function

func = changeFreeVars(phys)

c1_th1 = Symbol("c1th1",real=True)
c2_th1 = Symbol("c2th1",real=True)
c3_th1 = Symbol("c3th1",real=True)
c4_th1 = Symbol("c4th1",real=True)
y_th1 = Symbol("yth1",real=True)

c1_th2 = Symbol("c1th2",real=True)
c2_th2 = Symbol("c2th2",real=True)
c3_th2 = Symbol("c3th2",real=True)
c4_th2 = Symbol("c4th2",real=True)
y_th2 = Symbol("yth2",real=True)

acc_coefs = [c1_th1,c2_th1,c3_th1,c4_th1,y_th1,c1_th2,c2_th2,c3_th2,c4_th2,y_th2]

c5_th1 = y_th1-(1+c1_th1+c2_th1+c3_th1+c4_th1)
c5_th2 = y_th2-(1+c1_th2+c2_th2+c3_th2+c4_th2)
acc1 = 1 + c1_th1*x + c2_th1*x*x + c3_th1*x*x*x + c4_th1*x*x*x*x + c5_th1*x*x*x*x*x
acc2 = 1 + c1_th2*y + c2_th2*y*y + c3_th2*y*y*y + c4_th2*y*y*y*y + c5_th2*y*y*y*y*y

func = func*acc1*acc2


# BREAK
##### Generate and compile a fitting class corresponding to "func"

### Trial 1, w/o analytical integrals

op = D.RooClassGenerator(func, [x,y,z]+TransAmpModuli.values()+TransAmpPhases.values()+acc_coefs,"AngularPDFAcc_v3")
# op = D.RooClassGenerator(func, [x,y,z]+TransAmpModuli.values()+TransAmpPhases.values(),"AngularPDFNoAcc")
op.makePdf(integrable = kTRUE) ## You can also use makeFunc to generate just a RooAbsReal. Still not tested though
op.doIntegral(1,1,["Abs["+y.name+"]<1"],(x,-1,1))
op.doIntegral(2,1,["Abs["+x.name+"]<1"],(y,-1,1))
op.doIntegral(3,1,["Abs["+x.name+"]<1","Abs["+y.name+"]<1"],(z,-Pi,Pi))
op.doIntegral(4,1,[],(x,-1,1),(y,-1,1))
op.doIntegral(5,1,["Abs["+y.name+"]<1"],(x,-1,1),(z,-Pi,Pi))
op.doIntegral(6,1,["Abs["+x.name+"]<1"],(y,-1,1),(z,-Pi,Pi))
op.doIntegral(7,1,[],(x,-1,1),(y,-1,1),(z,-Pi,Pi))
op.overwrite()

### Trial 2, now lets generate a version using analytical integrals

# op2 = D.RooClassGenerator(func, [x,y,z]+TransAmpModuli.values()+TransAmpPhases.values()+acc_coefs,"RooSecond")
# op2.makePdf(integrable = kTRUE)
# op2.doIntegral(1,(x,-1,1))
# op2.doIntegral(2,(y,-1,1))
# op2.doIntegral(3,(z,-Pi,Pi))
# op2.doIntegral(4,(x,-1,1),(y,-1,1))
# op2.doIntegral(5,(x,-1,1),(z,-Pi,Pi))
# op2.doIntegral(6,(y,-1,1),(z,-Pi,Pi))
# op2.doIntegral(7,(x,-1,1),(y,-1,1),(z,-Pi,Pi))
# op2.overwrite()

### Compile online the two models and load the class to python
op.invoke()#, op2.invoke()

BREAK


gROOT.ProcessLine(".x RooSecond.cxx+")

##############  MAKING TREE


plot = 1
label = 'PLOT'
f = TFile("${WHOME}/NTuples_Bs2KstKst_strip17/public/Bs2KstKst_generated_MC11_angles.root")
tree=f.Get("T")
f1=TFile("/tmp/trash.root","recreate")
tree1 = tree.CopyTree("1")
tree2 = tree.CopyTree("1")

###################  CONSTRUCTING THE MODEL

CThetaL = RooRealVar("CosTheta1","cos(ThetaL) ", -1,1)
CThetaK = RooRealVar("CosTheta2","cos(ThetaK) ", -1,1)
Phi = RooRealVar("Phi","Phi", -pi,pi)
A0 = RooRealVar("A0","A0",0.77,0.5,1.)
Apa = RooRealVar("Apa","Apa",0.5,0.3,1.)
As  = RooRealVar("As" ,"As" ,1/2,0.,1.)

Ape = RooFormulaVar("Ape","Ape","sqrt(1-As*As-Apa*Apa-A0*A0)",RooArgList(A0,As,Apa))
deltaPa = RooRealVar("deltaPa","deltaPa",2.501,0.,2*pi)
deltaPe = RooRealVar("deltaPe","deltaPe",0.)#1,  -pi,pi)
deltaS  = RooRealVar("deltaS" ,"deltaS" ,0.9,0.,2*pi)

model=RooFirst("model","model",CThetaK,CThetaL,Phi,Apa,Ape,As,A0,deltaPa,deltaPe,deltaS)
# model2=RooSecond("model2","model2",CThetaK,CThetaL,Phi,Apa,Ape,As,A0,deltaPa,deltaPepi,deltaS)
###################  FITTING DATA

  ### tree - mix of B & Bbar
  ### tree1 - K+
  ### tree2 - K-

data = RooDataSet(label, label,tree1,RooArgSet(CThetaL,CThetaK,Phi))
#data = model.generate(RooArgSet(CThetaL,CThetaK,Phi),100000) ;

As.setVal(0)
As.setConstant(kTRUE)
deltaS.setConstant(kTRUE)
#deltaPe.setConstant(kTRUE)


def test(model,cv):
    res = model.fitTo(data,RooFit.Minos(kTRUE))#, RooFit.Range("REDUCED"))
    cv.Divide(2,2)
    cv.cd(1)
    Angframe = CThetaK.frame()
    data.plotOn(Angframe)
    model.plotOn(Angframe)
    Angframe.Draw()

    cv.cd(2)
    Angframeb = CThetaL.frame()
    data.plotOn(Angframeb)
    model.plotOn(Angframeb)
    Angframeb.Draw()

    cv.cd(3)
    Angframec = Phi.frame()
    data.plotOn(Angframec)
    model.plotOn(Angframec)
    Angframec.Draw()
    
    
    
    return res, Angframe, Angframeb, Angframec

cv = TCanvas()
w_1 = test(model,cv)
# w_2 = test(model2)

################ DRAWING 
