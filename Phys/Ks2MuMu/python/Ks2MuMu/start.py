from os import *
import sys
sys.path.append(environ["BS2MUMUROOT"] + "/python/Bs2MuMu")

from triggerclass import *
m = channelData("ks2mumumc11")

def eff(b,tau):
    g = 1./tau
    alpha = beta - g
    print alpha
    return g/(b-g)*(exp(alpha*130)-exp(alpha*8.95))
