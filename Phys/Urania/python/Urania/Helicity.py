from Urania.SympyBasic import *
from sympy.physics.quantum.spin import *
#from sympy.physics.quantum import Dagger


## Define the Helicity Angles

ThetaL = Symbol("\\theta_L",positive = True) ## Defined between 0 and pi
ThetaK = Symbol("\\theta_K",positive = True) ## Defined between 0 and pi
Phi = Symbol("\\phi",real = True) ## Defined between -pi and pi
helicity = Symbol("lambda", integer = True)

ThetaJ = Symbol("\\theta_J",positve = True) ## Defined between 0 and pi

H = {} ### Dictionary to store undetermined number of helicity amplitudes

TransAmplitudes = {}
TransAmplitudes["0_0"]  = Symbol("A_S")
TransAmplitudes["1_0"] = Symbol("A_0")
TransAmplitudes["1_pe"],TransAmplitudes["1_pa"] = Symbol("A_pe"), Symbol("A_pa")

Psi_tr = Symbol("\\psi_{tr}", positive = True)
Phi_tr = Symbol("\\phi_{tr}", real = True)
Theta_tr = Symbol("\\theta_{tr}",positive = True)



## Make the test for B -->J/psi hh

def doTerm(J,l,alpha):
    """ Does a J, lambda, alpha term ...
    """
    thingie = str(J)+"_"+str(l)
    H[thingie] = Symbol("H_("+thingie+")")
    z = Sqrt( (2*J+1)/(Pi*4)) * H[thingie]*Exp(I*l*Phi)*Rotation.d(1,l,alpha,ThetaL)*Rotation.d(J,-l,0,ThetaK)
    return z.doit()

def LambdaSum(J,alpha):
    """
    Performs the sumation in helicities given the angular momentum J
    of the interemdiate state and the helicity sum of the daghters on the
    opposite pair.
    For the moment this is only for B -> V x y
    """
    out = 0
    for i in range(2*J+1):
        l = -J + i
        out += doTerm(J,l,alpha)
    return simplify(out)

def UseTransAmp(expr, Jlist):
    out = expr
    for i in Jlist:
        j = str(i)
        if int(j)==0:
            if not "0_0" in dir(TransAmplitudes): TransAmplitudes["0_0"]  = Symbol("A_S")
            out = out.subs(H[j+"_0"],TransAmplitudes[j+"_0"])
            continue
        a0 = j +"_0"
        apa,ape = j+"_pa",j + "_pe"
        if not a0 in TransAmplitudes.keys(): TransAmplitudes[a0] = Symbol("A_"+j+"0")
        if not apa in TransAmplitudes.keys(): TransAmplitudes[apa] = Symbol("A_"+j+"pa")
        if not ape in TransAmplitudes.keys(): TransAmplitudes[ape] = Symbol("A_"+j+"pe")
        out = out.subs( [(H[j+"_0"],TransAmplitudes[j+"_0"]), (H[j+"_1"],1/Sqrt(2)*( TransAmplitudes[j+"_pa"] +TransAmplitudes[j+"_pe"])),(H[j+"_-1"],1/Sqrt(2)*( TransAmplitudes[j+"_pa"]-TransAmplitudes[j+"_pe"]))])
        
    return out
                         
                        

def PhiMassage(expr):
    """
    Some massaging of expressions for the helicity angle phi, which turn out to be useful
    to get cancellations.
    """
    out = expr
    out = out.subs(Sin(2*Phi), 2*Sin(Phi)*Cos(Phi)) 
    out = out.subs(Cos(2*Phi), Cos(Phi)**2 - Sin(Phi)**2)
    return out

def collectTerms(A,Amp,Amp2):
    """
    Searches in the pdf A for terms with Amp*conj(Amp2) -as well as its conjugate- and returns them
    """
    w = Amp*Amp2.conjugate()
    d= A.collect(w,evaluate = False)
    if  w not in d.keys():
        print "Warning, ",w, " not found. Returning 0"
        return 0,0
    if Amp == Amp2 : return d[w],0
    w2 = Amp2*Amp.conjugate()
    d2= A.collect(w2,evaluate = False)
    q = d[w]
    q2 = d2[w2]
    return q,q2

def TermsAsReImag(A,Amp,Amp2):
    """
    Searches in the pdf A for terms with Amp*conj(Amp2) -as well as its conjugate- and returns them
    splitted by real and imaginary parts of such product
    """
    q, q2 =collectTerms(A,Amp,Amp2)
    _re = (q+q2)#/2
    _im = im(q-q2)#/2
    return _re, _im

def squareAmpl(A):
    """
    Takes an amplitude combining several angular functions and squares it. Afterwards
    rewrites the exponentials in terms of cosines and sines, and returns the amplitude
    squared expanded.
    """
    Ab = A*A.conjugate()
    Ab = Ab.expand()
    Ab = Ab.rewrite(Exp, Cos) ## Do this shit at the very end!
    return Ab.expand()
    
    

def doB2VX(Jlist,  helicities = [1,-1], transAmp = 1,transAng = 0):
    """Generates an angular pdf for B-->Jpsi hh' for intermediate
    states with angular momentum included in Jlist
    lepton = 1 sums for muon helicity of \pm 1
    lepton = 0 treats the muons as scalars.
    """
    AllTerms = {}
    out = 0
    for h in helicities:
        AllTerms[h] = 0
        for i in Jlist: AllTerms[h] += LambdaSum(i,h)
        if transAmp: AllTerms[h] = UseTransAmp(AllTerms[h] , Jlist)
        out += squareAmpl(AllTerms[h])
    #if transAng: out = TransversityAngles(out)
    return out.expand()
    
## def TransversityAngles(expr):
##     out = expr.subs([(ThetaK,Psi_tr), (Cos(Phi), -Sin(Theta_tr)*Sin(Phi_tr)/(Sin(ThetaL))),(Sin(Phi),Cos(Theta_tr)/Sin(ThetaL))])
##     out = out.subs(Sin(ThetaL),Sqrt(1-Cos(ThetaL)**2))
##     return out.subs(Cos(ThetaL),-Sin(Theta_tr)*Cos(Phi_tr))
    

def DecomposeAmplitudes(A,list):
    """
    Returns a dictionary specifying which angular functions go with each amplitude combination
    """
    out = {}
    for i in range(len(list)):
        Amp = list[i]
        for j in range(i,len(list)):
            Amp2 = list[j]
            w = Amp*Amp2.conjugate()
            print w
            if Amp != Amp2:
                _re, _im = TermsAsReImag(A,Amp,Amp2)
                _re = PhiMassage(simplify(_re))
                _im = PhiMassage(simplify(_im))
                out[re(w)] = simplify(_re)
                out[im(w)] = simplify(_im)
            else:
                q, dummy = collectTerms(A,Amp,Amp2)
                out[abs(Amp)**2] = simplify(PhiMassage(simplify(q)))
    return out
                


As_ = TransAmplitudes["0_0"]
Apa_ = TransAmplitudes["1_pa"]
Ape_ = TransAmplitudes["1_pe"]
A0_ = TransAmplitudes["1_0"]

A02 = Symbol("A_{0}^{2}", positive = True)
Apa2 = Symbol("A_{pa}^2", positive = True)
Ape2 = Symbol("A_{pe}^2", positive = True)
AS2 = Symbol("A_S^2", positive = True)

delta_s = Symbol("delta_S",real = True)
delta_pa = Symbol("delta_{pa}",real = True)
delta_pe = Symbol("delta_{pe}", real = True)

A02C = Symbol("A02", positive = True)
Apa2C = Symbol("Apa2", positive = True)
Ape2C = Symbol("Ape2", positive = True)
AS2C = Symbol("AS2", positive = True)

delta_sC = Symbol("delta_S",real = True)
delta_paC = Symbol("delta_pa",real = True)
delta_peC = Symbol("delta_pe", real = True)

TransAmpModuli = {}
TransAmpPhases = {}


def ExplicitStrongPhases(expr):
    """ Modifies a term written as A1*conj(A2) as a function of the strong phases
    """
    print "I'm gonna be obsolete"
    f = expr.func
    if f in [im,re]:
        arg = expr.args[0]
        arg = arg.subs( [(As_,Sqrt(AS2)*Exp(I*delta_s)),(A0_,Sqrt(A02)),(Apa_,Sqrt(Apa2)*Exp(I*delta_pa)),(Ape_,Sqrt(Ape2)*Exp(I*delta_pe))] )
        arg = arg.rewrite(Exp,Cos)
        return simplify(f(arg))
    out = expr.subs( [(As_,Sqrt(AS2)*Exp(I*delta_s)),(A0_,Sqrt(A02)),(Apa_,Sqrt(Apa2)*Exp(I*delta_pa)),(Ape_,Sqrt(Ape2)*Exp(I*delta_pe))] )
    out = out.rewrite(Exp,Cos)
    return simplify(out)

def DefineStrongPhases(free_delta0 = 0):
    for key in TransAmplitudes:
        amp = str(TransAmplitudes[key])
        #name = str(amp)
        if key not in TransAmpModuli.keys(): TransAmpModuli[key] = Symbol(amp+"_mod",positive = True)
        if key not in TransAmpPhases.keys(): TransAmpPhases[key] = Symbol("delta" + amp.replace("A",""),real = True)
    if not free_delta0: TransAmpPhases.pop("1_0")

def StrongPhases(expr, free_delta0=0):
    """ Modifies a term written as A1*conj(A2) as a function of the strong phases
    """
    modlist = []
    DefineStrongPhases()
    for key in TransAmplitudes.keys():
        if key == "1_0" and not free_delta0:
            modlist.append( (TransAmplitudes[key], TransAmpModuli[key]))
            continue
        modlist.append( (TransAmplitudes[key],TransAmpModuli[key]*Exp(I*TransAmpPhases[key])) ) 
    f = expr.func
    if f in [im,re]:
        arg = expr.args[0]
        arg = arg.subs( modlist )
        arg = arg.rewrite(Exp,Cos)
        return simplify(f(arg))
    out = expr.subs( modlist )
    out = out.rewrite(Exp,Cos)
    return simplify(out)


def do4PTerm(J1,J2,l):
    """ Does a J1,J2, lambda term for spinless final state particles...
    """
    thingie = "Ja"+ str(J1)+"_"+ "Jb"+ str(J2)+"_"+str(l)
    H[thingie] = Symbol("H_("+thingie+")")
    z = Sqrt( (2*J1 + 1)*(2*J2+1)) * H[thingie]*Exp(-I*l*Phi)*Rotation.d(J1,l,0,ThetaL)*Rotation.d(J2,-l,0,Pi-ThetaK)
    return z.doit()

def do4PLambdaSum(J1,J2):
    """
    wwww
    """
    J = min(J1,J2)
    out = 0
    for i in range(2*J+1):
        l = -J + i
        out += do4PTerm(J1,J2,l)
    return simplify(out)


def doB2XhhYhh(J1list,J2list):
    """Generates an angular pdf for B-->X(-->hh) Y(--> hh') for intermediate
    states with angular momentum included in J1list and J2list
    """
    AllTerms = {}
    out = 0
    
    for h in J1list:
        for i in J2list: out += do4PLambdaSum(h,i)
        #if transAmp: AllTerms[h] = UseTransAmp(AllTerms[h] , Jlist)
    out = squareAmpl(out)
    #if transAng: out = TransversityAngles(out)
    return out.expand()
