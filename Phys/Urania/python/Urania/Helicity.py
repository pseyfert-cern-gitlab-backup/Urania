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
TransAmplitudes["1_0"] = Symbol("A_0")
TransAmplitudes["1_pe"],TransAmplitudes["1_pa"] = Symbol("A_{pe}"), Symbol("A_{pa}")

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
            TransAmplitudes["0_0"]  = Symbol("A_S")
            out = out.subs(H[j+"_0"],TransAmplitudes[j+"_0"])
            continue
        a0 = j +"_0"
        apa,ape = j+"_pa",j + "_pe"
        if not a0 in TransAmplitudes.keys(): TransAmplitudes[a0] = Symbol("A_{"+j+",0}")
        if not apa in TransAmplitudes.keys(): TransAmplitudes[apa] = Symbol("A_{"+j+",pa}")
        if not ape in TransAmplitudes.keys(): TransAmplitudes[ape] = Symbol("A_{"+j+",pe}")
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
    _re = (q+q2)/2
    _im = im(q-q2)/2
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
    if transAng: out = TransversityAngles(out)
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
                

