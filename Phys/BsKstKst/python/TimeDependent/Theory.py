from sympy import *

def fadd(z):
   w = exp(-z*z)*erfc(-I*z)
   return w.simplify()

def lambdify(x):
   ft = (x.subs([(dm,17.69),(gamma,0.668),(dg,0.08),(mut,0),(sigmat,0.04),(a_tacc,0.157826656652),(b_tacc,9.23693986588e-06),(f,0.920394119915),(sigmat1,0.0382719899719),(sigmat2,0.199999997666)])).simplify()
   ft_eval = lambda tau: (ft.subs(t,tau)).simplify()
   return ft_eval

def lambdifyinteg(x):
   ft = (x.subs([(dm,17.69),(gamma,0.668),(dg,0.08),(mut,0),(sigmat,0.04),(a_tacc,0.157826656652),(b_tacc,9.23693986588e-06),(f,0.920394119915),(sigmat1,0.0382719899719),(sigmat2,0.199999997666)])).simplify()
   ft_eval = lambda x1,x2: (ft.subs([(t1,x1),(t2,x2)])).simplify()
   return ft_eval

def dointegral(x,bins):
   step = 12./bins
   integral = 0
   for i in range(bins): integral += x((0.5+i)*step)
   return integral*step

def defininteg(fun):
   return (fun.subs(t,t2)-fun.subs(t,t1)).simplify()

t = Symbol("t",real=True)
t1 = Symbol("t1",real=True)
t2 = Symbol("t2",real=True)

gamma = Symbol("gamma",real=True)
dg = Symbol("dg",real=True)
dm = Symbol("dm",real=True)

sigmat = Symbol("sigmat",real=True)
f = Symbol("f",real=True)
sigmat1 = Symbol("sigmat1",real=True)
sigmat2 = Symbol("sigmat2",real=True)
mut = Symbol("mut",real=True)

a_tacc = Symbol("a_tacc",real=True)
b_tacc = Symbol("b_tacc",real=True)

x = (t-mut-gamma*sigmat*sigmat)/(sqrt(2)*sigmat)
x0 = dg*sigmat/(2*sqrt(2))
z = (dm*sigmat*sigmat-I*(t-mut-gamma*sigmat*sigmat))/(sqrt(2)*sigmat)

acc = t*t*t/(a_tacc+t*t*t)*(1.-b_tacc*t)

Tcosh_exact = (0.25*exp(-(t-mut)**2/(2*sigmat**2))*(exp((x+x0)**2)*erfc(-x-x0)+exp((x-x0)**2)*erfc(-x+x0))).simplify()
Tsinh_exact = (0.25*exp(-(t-mut)**2/(2*sigmat**2))*(exp((x+x0)**2)*erfc(-x-x0)-exp((x-x0)**2)*erfc(-x+x0))).simplify()
Tcos_exact = (0.5*exp(-(t-mut)**2/(2*sigmat**2))*re(fadd(z))).simplify()
Tsin_exact = (0.5*exp(-(t-mut)**2/(2*sigmat**2))*im(fadd(z))).simplify()

Tcosh_approx = exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat*sigmat+0.125*dg*dg*sigmat*sigmat)*cosh(0.5*dg*(t-mut)-0.5*gamma*dg*sigmat*sigmat)
Tsinh_approx = exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat*sigmat+0.125*dg*dg*sigmat*sigmat)*sinh(0.5*dg*(t-mut)-0.5*gamma*dg*sigmat*sigmat)
Tcos_approx = exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat*sigmat-0.5*dm*dm*sigmat*sigmat)*cos(dm*(t-mut)-gamma*dm*sigmat*sigmat)
Tsin_approx = exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat*sigmat-0.5*dm*dm*sigmat*sigmat)*sin(dm*(t-mut)-gamma*dm*sigmat*sigmat)

Tcosh_exre = lambdify(Tcosh_exact*acc)
Tsinh_exre = lambdify(Tsinh_exact*acc)
Tcos_exre = lambdify(Tcos_exact*acc)
Tsin_exre = lambdify(Tsin_exact*acc)
Tcosh_apre = lambdify(Tcosh_approx*acc)
Tsinh_apre = lambdify(Tsinh_approx*acc)
Tcos_apre = lambdify(Tcos_approx*acc)
Tsin_apre = lambdify(Tsin_approx*acc)

ft1 = f*exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat1*sigmat1+1./8.*dg*dg*sigmat1*sigmat1)*cosh(0.5*dg*(t-mut)-0.5*gamma*dg*sigmat1*sigmat1)+(1.-f)*exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat2*sigmat2+1./8.*dg*dg*sigmat2*sigmat2)*cosh(0.5*dg*(t-mut)-0.5*gamma*dg*sigmat2*sigmat2)

ft2 = f*exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat1*sigmat1+1./8.*dg*dg*sigmat1*sigmat1)*sinh(0.5*dg*(t-mut)-0.5*gamma*dg*sigmat1*sigmat1)+(1.-f)*exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat2*sigmat2+1./8.*dg*dg*sigmat2*sigmat2)*sinh(0.5*dg*(t-mut)-0.5*gamma*dg*sigmat2*sigmat2)

ft3 = f*exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat1*sigmat1-0.5*dm*dm*sigmat1*sigmat1)*cos(dm*(t-mut)-gamma*dm*sigmat1*sigmat1)+(1.-f)*exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat2*sigmat2-0.5*dm*dm*sigmat2*sigmat2)*cos(dm*(t-mut)-gamma*dm*sigmat2*sigmat2)

ft4 = f*exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat1*sigmat1-0.5*dm*dm*sigmat1*sigmat1)*sin(dm*(t-mut)-gamma*dm*sigmat1*sigmat1)+(1.-f)*exp(-gamma*(t-mut)+0.5*gamma*gamma*sigmat2*sigmat2-0.5*dm*dm*sigmat2*sigmat2)*sin(dm*(t-mut)-gamma*dm*sigmat2*sigmat2)

Ift1 = ((0.5*dg*f*exp(sigmat1**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat1**2 + 0.5*mut - 0.5*t1)) - 0.5*dg*f*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t1)) + 0.5*dg*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t1)) - 1.0*f*gamma*exp(sigmat1**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat1**2 + 0.5*mut - 0.5*t1)) + 1.0*f*gamma*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t1)) - 1.0*gamma*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t1)))*exp(gamma*(mut - t1)) - (0.5*dg*f*exp(sigmat1**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat1**2 + 0.5*mut - 0.5*t2)) - 0.5*dg*f*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t2)) + 0.5*dg*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t2)) - 1.0*f*gamma*exp(sigmat1**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat1**2 + 0.5*mut - 0.5*t2)) + 1.0*f*gamma*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t2)) - 1.0*gamma*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t2)))*exp(gamma*(mut - t2)))/((0.5*dg - gamma)*(0.5*dg + gamma))

Ift2 = -((0.5*dg*f*exp(sigmat1**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat1**2 + 0.5*mut - 0.5*t1)) - 0.5*dg*f*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t1)) + 0.5*dg*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t1)) - 1.0*f*gamma*exp(sigmat1**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat1**2 + 0.5*mut - 0.5*t1)) + 1.0*f*gamma*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t1)) - 1.0*gamma*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t1)))*exp(gamma*(mut - t1)) - (0.5*dg*f*exp(sigmat1**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat1**2 + 0.5*mut - 0.5*t2)) - 0.5*dg*f*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t2)) + 0.5*dg*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*cosh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t2)) - 1.0*f*gamma*exp(sigmat1**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat1**2 + 0.5*mut - 0.5*t2)) + 1.0*f*gamma*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t2)) - 1.0*gamma*exp(sigmat2**2*(0.125*dg**2 + 0.5*gamma**2))*sinh(dg*(0.5*gamma*sigmat2**2 + 0.5*mut - 0.5*t2)))*exp(gamma*(mut - t2)))/((0.5*dg - gamma)*(0.5*dg + gamma))

Ift3 = ((-f*(dm*sin(dm*(gamma*sigmat1**2 + mut - t1)) + gamma*cos(dm*(gamma*sigmat1**2 + mut - t1)))*exp(sigmat2**2*(0.5*dm**2 - 0.5*gamma**2)) + 1.0*(dm*f*sin(dm*(gamma*sigmat2**2 + mut - t1)) - dm*sin(dm*(gamma*sigmat2**2 + mut - t1)) + f*gamma*cos(dm*(gamma*sigmat2**2 + mut - t1)) - gamma*cos(dm*(gamma*sigmat2**2 + mut - t1)))*exp(sigmat1**2*(0.5*dm**2 - 0.5*gamma**2)))*exp(gamma*(mut - t1) - sigmat1**2*(0.5*dm**2 - 0.5*gamma**2) - sigmat2**2*(0.5*dm**2 - 0.5*gamma**2)) + (f*(dm*sin(dm*(gamma*sigmat1**2 + mut - t2)) + gamma*cos(dm*(gamma*sigmat1**2 + mut - t2)))*exp(sigmat2**2*(0.5*dm**2 - 0.5*gamma**2)) + 1.0*(-dm*f*sin(dm*(gamma*sigmat2**2 + mut - t2)) + dm*sin(dm*(gamma*sigmat2**2 + mut - t2)) - f*gamma*cos(dm*(gamma*sigmat2**2 + mut - t2)) + gamma*cos(dm*(gamma*sigmat2**2 + mut - t2)))*exp(sigmat1**2*(0.5*dm**2 - 0.5*gamma**2)))*exp(gamma*(mut - t2) - sigmat1**2*(0.5*dm**2 - 0.5*gamma**2) - sigmat2**2*(0.5*dm**2 - 0.5*gamma**2)))/(-dm*dm - gamma*gamma)

Ift4 = ((-f*(dm*cos(dm*(gamma*sigmat1**2 + mut - t1)) - gamma*sin(dm*(gamma*sigmat1**2 + mut - t1)))*exp(sigmat2**2*(0.5*dm**2 - 0.5*gamma**2)) + 1.0*(dm*f*cos(dm*(gamma*sigmat2**2 + mut - t1)) - dm*cos(dm*(gamma*sigmat2**2 + mut - t1)) - f*gamma*sin(dm*(gamma*sigmat2**2 + mut - t1)) + gamma*sin(dm*(gamma*sigmat2**2 + mut - t1)))*exp(sigmat1**2*(0.5*dm**2 - 0.5*gamma**2)))*exp(gamma*(mut - t1) - sigmat1**2*(0.5*dm**2 - 0.5*gamma**2) - sigmat2**2*(0.5*dm**2 - 0.5*gamma**2)) + (f*(dm*cos(dm*(gamma*sigmat1**2 + mut - t2)) - gamma*sin(dm*(gamma*sigmat1**2 + mut - t2)))*exp(sigmat2**2*(0.5*dm**2 - 0.5*gamma**2)) + 1.0*(-dm*f*cos(dm*(gamma*sigmat2**2 + mut - t2)) + dm*cos(dm*(gamma*sigmat2**2 + mut - t2)) + f*gamma*sin(dm*(gamma*sigmat2**2 + mut - t2)) - gamma*sin(dm*(gamma*sigmat2**2 + mut - t2)))*exp(sigmat1**2*(0.5*dm**2 - 0.5*gamma**2)))*exp(gamma*(mut - t2) - sigmat1**2*(0.5*dm**2 - 0.5*gamma**2) - sigmat2**2*(0.5*dm**2 - 0.5*gamma**2)))/(-dm*dm - gamma*gamma)

