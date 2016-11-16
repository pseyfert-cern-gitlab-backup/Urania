from sympy import *

t = Symbol("t",real=True)

one = t/t
zero = 0*t

x0 = Symbol("x0",real=True)
x1 = Symbol("x1",real=True)
x2 = Symbol("x2",real=True)
x3 = Symbol("x3",real=True)
x4 = Symbol("x4",real=True)
x5 = Symbol("x5",real=True)

c0 = Symbol("c0",real=True)
c1 = Symbol("c1",real=True)
c2 = Symbol("c2",real=True)
c3 = Symbol("c3",real=True)
c4 = Symbol("c4",real=True)
c5 = Symbol("c5",real=True)
c6 = Symbol("c6",real=True)
c7 = Symbol("c7",real=True)

knot = [x0,x0,x0,x0,x1,x2,x3,x4,x5,x5,x5,x5]
coef = [c0,c1,c2,c3,c4,c5,c6,c7]

def Bid(i,d,it):
   if d==0:
      if it == i-3: return one
      else: return zero
   else:
      Bidsum = 0
      term1 = Bid(i,d-1,it)
      term2 = Bid(i+1,d-1,it)
      if term1 != zero: Bidsum += (t-knot[i])/(knot[i+d]-knot[i])*term1
      if term2 != zero: Bidsum += (knot[i+1+d]-t)/(knot[i+1+d]-knot[i+1])*term2
      return Bidsum

print 'Computing the polynomials ...'
binnedpol = [0,0,0,0,0]
for ibin in range(5):
   print 'Bin '+str(ibin)
   for ipol in range(8): binnedpol[ibin] += coef[ipol]*Bid(ipol,3,ibin)
   binnedpol[ibin] = binnedpol[ibin].expand()
print 'Polynomials computed.'

print 'Determining the coefficients ...'
coefmatrix = [[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
for ibin in range(5):
   print 'Bin '+str(ibin)
   for deg in range(4):
      print 'Degree '+str(deg)
      coefmatrix[ibin][deg] = (binnedpol[ibin].coeff(t,deg)).simplify()
print 'Coefficients determined.'

def asx2pow(s):
   astlist = ['x0**2','x1**2','x2**2','x3**2','x4**2','x5**2','x0**3','x1**3','x2**3','x3**3','x4**3','x5**3','x0**4','x0**5','x0**6','x5**4','x5**5','x5**6']
   powlist = ['pow(x0,2)','pow(x1,2)','pow(x2,2)','pow(x3,2)','pow(x4,2)','pow(x5,2)','pow(x0,3)','pow(x1,3)','pow(x2,3)','pow(x3,3)','pow(x4,3)','pow(x5,3)','pow(x0,4)','pow(x0,5)','pow(x0,6)','pow(x5,4)','pow(x5,5)','pow(x5,6)']
   snew = s
   for term in range(len(astlist)): snew = snew.replace(astlist[term],powlist[term])
   return snew

scoefmatrix = [['','','',''],['','','',''],['','','',''],['','','',''],['','','','']]
for ibin in range(5):
   for deg in range(4): scoefmatrix[ibin][deg] = asx2pow(str(coefmatrix[ibin][deg]))

printfun = '	if (ibin == 0) {\n\n		if (deg == 0) {return '+scoefmatrix[0][0]+';}\n\n		else if (deg == 1) {return '+scoefmatrix[0][1]+';}\n\n		else if (deg == 2) {return '+scoefmatrix[0][2]+';}\n\n		else if (deg == 3) {return '+scoefmatrix[0][3]+';}\n	}\n	else if (ibin == 1) {\n\n		if (deg == 0) {return '+scoefmatrix[1][0]+';}\n\n		else if (deg == 1) {return '+scoefmatrix[1][1]+';}\n\n		else if (deg == 2) {return '+scoefmatrix[1][2]+';}\n\n		else if (deg == 3) {return '+scoefmatrix[1][3]+';}\n	}\n	else if (ibin == 2) {\n\n		if (deg == 0) {return '+scoefmatrix[2][0]+';}\n\n		else if (deg == 1) {return '+scoefmatrix[2][1]+';}\n\n		else if (deg == 2) {return '+scoefmatrix[2][2]+';}\n\n		else if (deg == 3) {return '+scoefmatrix[2][3]+';}\n	}\n	else if (ibin == 3) {\n\n		if (deg == 0) {return '+scoefmatrix[3][0]+';}\n\n		else if (deg == 1) {return '+scoefmatrix[3][1]+';}\n\n		else if (deg == 2) {return '+scoefmatrix[3][2]+';}\n\n		else if (deg == 3) {return '+scoefmatrix[3][3]+';}\n	}\n	else if (ibin == 4) {\n\n		if (deg == 0) {return '+scoefmatrix[4][0]+';}\n\n		else if (deg == 1) {return '+scoefmatrix[4][1]+';}\n\n		else if (deg == 2) {return '+scoefmatrix[4][2]+';}\n\n		else if (deg == 3) {return '+scoefmatrix[4][3]+';}\n	}\n'

print printfun
