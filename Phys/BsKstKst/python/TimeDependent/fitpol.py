from ROOT import *
from math import sqrt
from array import array

c1 = 0.801457307276
c2 = -0.0519592129077
c3 = -9.81586492026
c4 = -5.63320302524

def modulus(xm):
   xm = xm/2.+0.5
   return 1.+c1*(xm+1)+c2*(xm*xm-1)+c3*(xm*xm*xm-1)+c4*(xm*xm*xm*xm-1)

xl = [-1.]
for i in range(1,1001): xl.append(-1.+i*2./1000.)

yl = []
for i in xl:
   yl.append(modulus(i))

x = array('d',xl)
y = array('d',yl)

gr = TGraph(len(x),x,y)

fun = TF1("fun","[0]*(1.+[1]*x+[2]*(2.*x*x-1.)+[3]*(4.*x*x*x-3.*x)+[c4]*(8.*x*x*x*x-8.*x*x+1.))",-1,1)

gr.Draw()
