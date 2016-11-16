from sympy import *

t = Symbol("t",real=True)
one = t/t
tp = Symbol("tp",real=True)
sigma = Symbol("sigma",real=True)
mu = Symbol("mu",real=True)
gamma = Symbol("gamma",real=True)
deltagamma = Symbol("deltagamma",real=True)
deltam = Symbol("deltam",real=True)
half = one/2

gp = half*exp(-gamma*t)*(exp(I*half*deltam*t-half*deltagamma*t)+exp(-I*half*deltam*t+half*deltagamma*t))
gm = half*exp(-gamma*t)*(exp(I*half*deltam*t-half*deltagamma*t)-exp(-I*half*deltam*t+half*deltagamma*t))

gpgp = gp*conjugate(gp)
gmgm = gm*conjugate(gm)
gpgm = gp*conjugate(gm)

Tcosh = (gpgp+gmgm).expand()
Tsinh = (-2*re(gpgm)).expand()
Tcos = (gpgp-gmgm).expand()
Tsin = (-2*im(gpgm)).expand()
