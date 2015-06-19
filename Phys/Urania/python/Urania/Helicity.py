from Urania.SympyBasic import *
from sympy.physics.quantum.spin import *
#from sympy.physics.quantum import Dagger


## Define the Helicity Angles

ThetaL = Symbol("\Theta_L",positive = True) ## Defined between 0 and pi
ThetaK = Symbol("\Theta_K",positive = True) ## Defined between 0 and pi
Phi = Symbol("\phi",real = True) ## Defined between -pi and pi
helicity = Symbol("lambda", integer = True)

ThetaJ = Symbol("\theta_J",positve = True) ## Defined between 0 and pi

H = {} ### Dictionary to store undetermined number of helicity amplitudes

A0 = Symbol("A_0")
Apa = Symbol("A_{pa}")
Ape = Symbol("A_{pe}")
As = Symbol("A_{S}")

TransversityAmplitudes = [A0,Apa,Ape, As]
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

def UseTransAmp(expr): return expr.subs([(H["1_0"],A0), (H["1_1"],1/Sqrt(2)*( Apa+Ape)),(H["1_-1"],1/Sqrt(2)*( Apa-Ape)),(H["0_0"],As)])

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

def squareAmpl(A, transAmp = 1):
    """
    Takes an amplitude combining several angular functions and squares it. Afterwards
    rewrites the exponentials in terms of cosines and sines, and returns the amplitude
    squared expanded.
    If transAmp = 1, the helicity amplitudes will be translated to transversity amplitudes.
    """
    Ab = A*A.conjugate()
    if transAmp : Ab = UseTransAmp(Ab)
    Ab = Ab.expand()
    Ab = Ab.rewrite(Exp, Cos) ## Do this shit at the very end!
    return Ab.expand()
    
    

def doB2JpsiX(Jlist, lepton = 1):
    """Generates an angular pdf for B-->Jpsi hh' for intermediate
    states with angular momentum included in Jlist
    lepton = 1 sums for muon helicity of \pm 1
    lepton = 0 treats the muons as scalars.
    """
    if lepton:
        A = 0
        B = 0
        for i in Jlist:
            A += LambdaSum(i,1)
            B += LambdaSum(i,-1)
        return  (squareAmpl(A) + squareAmpl(B)).expand()
    else:
        A = 0
        for i in Jlist: A += LambdaSum(i,0)
        return squareAmpl(A)

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
                


    
## def simple_test2():
##     A = doB2JpsiX(Jlist = [0,1])
##     f = file("out.tex","w")
##     f.write("\\begin{multline}\n")
##     for i in range(len(TransversityAmplitudes)):
##         Amp = TransversityAmplitudes[i]
##         for j in range(i,len(TransversityAmplitudes)):
##             Amp2 = TransversityAmplitudes[j]
##             w = Amp*Amp2.conjugate()
##             print w
##             if Amp != Amp2:
##                 _re, _im = TermsAsReImag(A,Amp,Amp2)
##                 _re = PhiMassage(simplify(_re))
##                 _im = PhiMassage(simplify(_im))
##                 exp1 = latex(simplify(_re))
##                 exp2 = latex(simplify(_im))  
##                 f.write(latex(re(w)) + "\t" + exp1 + "\\\\" + "\n")
##                 f.write(latex(im(w)) + "\t" + exp2 + "\\\\" + "\n")
           
##             else:
##                 q, dummy = collectTerms(A,Amp,Amp2)
##                 expression = latex(simplify(PhiMassage(simplify(q))))
##                 f.write(latex(w) + "\t" + expression + "\\\\" + "\n")
                                 
##     f.write("\\end{multline}")
##     f.close()

    
## #simple_test()


## def simple_test3():
##     #A = LambdaSum(1,0) + LambdaSum(0,0)
##     A = LambdaSum(1,1) + LambdaSum(0,1)
##     A = A*A.conjugate()
##     A = UseTransAmp(A)
##     A = A.expand()
##     A = A.rewrite(Exp, Cos) ## Do this shit at the very end!
##     A = A.expand()

##     B = LambdaSum(1,-1) + LambdaSum(0,-1)
##     B = B*B.conjugate()
##     B = UseTransAmp(B)
##     B = B.expand()
##     B = B.rewrite(Exp, Cos) ## Do this shit at the very end!
##     B = B.expand()
##     A += B
     
##     f = file("out.tex","w")
##     f.write("\\begin{multline}\n")
##     for i in range(len(TransversityAmplitudes)):
##         Amp = TransversityAmplitudes[i]
##         for j in range(i,len(TransversityAmplitudes)):
##             Amp2 = TransversityAmplitudes[j]
##             w = Amp*Amp2.conjugate()
##             d= A.collect(w,evaluate = False)
##             print w
##             if  w not in d.keys():
##                 print "Warning"
##                 expression = "0"
##                 f.write(latex(w) + "\t" + expression + "\\\\" + "\n")
##             elif Amp == Amp2:
##                 expression = latex(simplify(PhiMassage(simplify(d[w]))))
##                 f.write(latex(w) + "\t" + expression + "\\\\" + "\n")
        
##             else:
##                 w2 = Amp2*Amp.conjugate()
##                 d2= A.collect(w2,evaluate = False)
##                 q = d[w]
##                 q2 = d2[w2]
##                 _re = (q+q2)/2
##                 _im = im(q-q2)/2
            
##             ### Do Some Massaging
##                 _re = PhiMassage(simplify(_re))
##                 _im = PhiMassage(simplify(_im))

##                 exp1 = latex(simplify(_re))
##                 exp2 = latex(simplify(_im))
            
##                 f.write(latex(re(w)) + "\t" + exp1 + "\\\\" + "\n")
##                 f.write(latex(im(w)) + "\t" + exp2 + "\\\\" + "\n")
                                 
##     f.write("\\end{multline}")
##     f.close()

    
## ## #simple_test()


