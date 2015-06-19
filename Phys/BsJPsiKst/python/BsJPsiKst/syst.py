from math import *
eps = 1.011
f = 0.951
k = 1.063

def err(s1,s2,v):
    a1 = abs(s1-v)
    a2 = abs(s2-v)
    return max(a1,a2)
