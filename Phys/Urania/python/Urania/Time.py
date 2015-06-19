from Urania.Helicity import *
time = Symbol("t","t",positive = True)

mL = Symbol("m_L",positive = True)
mH = Symbol("m_H", positive = True)
mB = Symbol("m_B", positive = True)
GL = USymbol("GL", "\\Gamma_L", positive = True)
GH = USymbol("GH", "\\Gamma_H", positive = True)
DM = USymbol("DM", "\\DeltaM", positive = True)
DG = USymbol("DG", "\\Delta\\Gamma", real = True)
Gamma = USymbol("G","\\Gamma", positive = True)
gplus_eq = One/2*(Exp(-time*(I*mL+GL/2)) + Exp(-time*(I*mH+GH/2)))
gminus_eq = One/2*(Exp(-time*(I*mL+GL/2)) - Exp(-time*(I*mH+GH/2)))

gplus = Symbol("gplus")
gminus = Symbol("gminus")

WeakPhases = {}
Lambdas = {}


def massageTimeEvolution(A):
    th1= getThing(A,gplus*gplus.conjugate())
    th2= getThing(A,gminus*gminus.conjugate())
    th3= getThing(A,gplus*gminus.conjugate())
    th4= getThing(A,gminus*gplus.conjugate())
    return th1*gplus*gplus.conjugate() + th2*gminus*gminus.conjugate() + th3*gplus*gminus.conjugate() + th4*gminus*gplus.conjugate()

def CustomTrigSimp1(expr, TransAmpPhases, WeakPhases):
    out = expr
    phases = TransAmpPhases.values() + WeakPhases.values()
    for i in range(len(phases)):
        delta = phases[i]
        for j in range(i+1,len(phases)):
            phi = phases[j]
            out = out.subs([(Sin(delta)*Cos(phi),Sin(delta- phi) + Cos(delta)*Sin(phi)), (Sin(delta)*Sin(phi),Cos(delta- phi) - Cos(delta)*Cos(phi))])
            out2 = simplify(out.subs([(Sin(phi)*Cos(delta),Sin(phi+ delta) - Cos(phi)*Sin(delta)), (Sin(phi)*Sin(delta),-Cos(phi+ delta) + Cos(phi)*Cos(delta))]))
            out = simplify(out)
                   
            if len(str(out2)) < len(str(out)): out = out2 
    return out

def CustomTrigSimp2(expr, TransAmpPhases, WeakPhases):
    out = expr
    phases = TransAmpPhases.values() + WeakPhases.values()
    for i in range(len(phases)):
        delta = phases[i]
        for j in range(i+1,len(phases)):
            phi = phases[j]
            out = out.subs([(Sin(delta)*Cos(phi),Sin(delta- phi) + Cos(delta)*Sin(phi)), (Cos(delta)*Cos(phi),Cos(delta- phi) - Sin(delta)*Sin(phi))])
            out2 = simplify(out.subs([(Sin(phi)*Cos(delta),Sin(phi+ delta) - Cos(phi)*Sin(delta)), (Cos(phi)*Cos(delta),Cos(phi+ delta) + Sin(phi)*Sin(delta))]))
            out = simplify(out)
            if len(str(out2)) < len(str(out)): out = out2 
    return out

def CustomTrigSimp(expr, Strong, Weak):
    l = []
    out1 = CustomTrigSimp1(expr, Strong,Weak)
    l.append([len(str(out1)),out1])
    out2 = CustomTrigSimp2(expr, Strong,Weak)
    l.append([len(str(out2)),out2])
    l.sort()
    return l[0][1]

def defineTimeModList(TransAmpModuli,TransAmpPhases,Lambdas,WeakPhases):
    modlist = []
    for key in TransAmpModuli.keys(): 
        modlist.append( (TransAmplitudes[key],TransAmpModuli[key]*Exp(I*TransAmpPhases[key])*(gplus +Lambdas[key]*Exp(-I*WeakPhases[key])*gminus) ))
    return modlist
def get_abcd(expr, modlist = [], TransAmplitudes = TransAmplitudes, TransAmpPhases = TransAmpPhases, WeakPhases = WeakPhases):
    
    #itsamplitudes = [] ### DMS May 30 comment out collect
    if not modlist:
        for key in TransAmplitudes.keys(): 
            modlist.append( (TransAmplitudes[key],TransAmpModuli[key]*Exp(I*TransAmpPhases[key])*(gplus +Lambdas[key]*Exp(-I*WeakPhases[key])*gminus) ))
        #itsamplitudes.append((TransAmplitudes[key], TransAmpModuli[key])) ### DMS May 30 comment out collect
    f = expr.func
    if f in [im,re]:
        arg = expr.args[0]
        arg = arg.subs( modlist )
        arg = arg.rewrite(Exp,Cos)
        t_dep = f(arg)
        
    elif expr.is_Pow and expr.args[0].func == Abs:
        xx = expr.args[0].args[0]
        expr2 = xx*xx.conjugate()
        out = expr2.subs( modlist )
        out = out.rewrite(Exp,Cos)
        t_dep =  simplify(massageTimeEvolution(out.expand()))
    else: print "ERROR"
    #t_dep = doTimeEvolution(key,TransAmplitudes) ### DMS May 30 comment out collect
    key = expr
    #if key.func.is_Pow: amps = key.args[0].subs(itsamplitudes)**2 ### DMS May 30 comment out collect
        
    #else:  amps = key.args[0].subs(itsamplitudes)
    if t_dep.func in [re,im]:
        _func = t_dep.func
        #print _func
        t_dep = t_dep.args[0].expand()#.collect(amps,evaluate = False) [amps]### DMS May 30 comment out collect
        alpha = getThing(t_dep,gplus*gplus.conjugate())
        beta = getThing(t_dep,gminus*gminus.conjugate())
        alphap = getThing(t_dep,gminus*gplus.conjugate())
        betap = getThing(t_dep,gplus*gminus.conjugate())
        ak = CustomTrigSimp(_func(alpha + beta),TransAmpPhases, WeakPhases)
        ck = CustomTrigSimp(_func(alpha - beta),TransAmpPhases, WeakPhases)
        bk = CustomTrigSimp(-_func((alphap + betap)),TransAmpPhases, WeakPhases)
        dk = CustomTrigSimp(_func((alphap-betap)*I),TransAmpPhases, WeakPhases)
    else:
        #print t_dep.func
        t_dep = t_dep.expand()#.collect(amps,evaluate = False) [amps] ###DMS May 30 comment out collect
        alpha = getThing(t_dep,gplus*gplus.conjugate())
        beta = getThing(t_dep,gminus*gminus.conjugate())
        alphap = getThing(t_dep,gminus*gplus.conjugate())
        betap = getThing(t_dep,gplus*gminus.conjugate())
        ak = CustomTrigSimp(alpha + beta,TransAmpPhases, WeakPhases)
        ck = CustomTrigSimp(alpha - beta,TransAmpPhases, WeakPhases)
        bk = CustomTrigSimp(-(alphap + betap),TransAmpPhases, WeakPhases)
        dk = CustomTrigSimp((alphap-betap)*I,TransAmpPhases, WeakPhases)    
    return ak, bk, ck, dk

def timeExpression(key, modlist = []):#, ta = Exp(-Gamma*time)*Cosh(DG*time/2), tb = Exp(-Gamma*time)*Sinh(DG*time/2), tc = Exp(-Gamma*time)*Cos(DM*time), td = Exp(-Gamma*time)*Sin(DM*time)):
    ak,bk,ck,dk = get_abcd(key, modlist)
    return  (ak*Cosh(DG*time/2) + bk*Sinh(DG*time/2) +ck*Cos(DM*time)+ dk*Sin(DM*time) )*Exp(-Gamma*time)

def timeExpressionBbar(key,modlist = [], ta = Exp(-Gamma*time)*Cosh(DG*time/2), tb = Exp(-Gamma*time)*Sinh(DG*time/2), tc = Exp(-Gamma*time)*Cos(DM*time), td = Exp(-Gamma*time)*Sin(DM*time)):
    ak,bk,ck,dk = get_abcd(key, modlist)
    return ak*ta  + bk*tb - ck*tc - dk*td 

def timeExpressionUntag(key):
    ak,bk,ck,dk = get_abcd(key)
    return (ak**Cosh(DG*time/2)  + bk* Sinh(DG*time/2))* Exp(-Gamma*time)
