from sympy import *

amp_name_list = ["00","01","10","02","20","110","11par","11perp","120","12par","12perp","210","21par","21perp","220","22par1","22perp1","22par2","22perp2"]

one = 1.#Symbol("1",real=True)
two = 2.#Symbol("2",real=True)
three = 3.#Symbol("3",real=True)
five = 5.#Symbol("5",real=True)
half = one/two

for name in amp_name_list:
   exec("modA"+name+" = Symbol('modA"+name+"',real=True)")
   exec("delta"+name+" = Symbol('delta"+name+"',real=True)")

modAsp = Symbol('modAsp',real=True)
modAsm = Symbol('modAsm',real=True)
deltasp = Symbol('deltasp',real=True)
deltasm = Symbol('deltasm',real=True)
Asp = modAsp*exp(I*deltasp)
Asm = modAsm*exp(I*deltasm)

gamma_L = Symbol("gamma_L",real=True)
gamma_H = Symbol("gamma_H",real=True)
gamma_Bs = half*(gamma_L+gamma_H)
delta_gamma_Bs = gamma_L-gamma_H

m1 = Symbol("m1",real=True)
m2 = Symbol("m2",real=True)
theta1 = Symbol("theta1",real=True)
theta2 = Symbol("theta2",real=True)
cos1 = cos(theta1)
cos2 = cos(theta2)
phi = Symbol("phi",real=True)

M0_1 = Symbol("M_0(m1)")
M1_1 = Symbol("M_1(m1)")
M2_1 = Symbol("M_2(m1)")
M0_2 = Symbol("M_0(m2)")
M1_2 = Symbol("M_1(m2)")
M2_2 = Symbol("M_2(m2)")

PhSp = Symbol("PhSp",real=True)

sqrtIm00 = Symbol("sqrt(Im00)",real=True)
sqrtIm01 = Symbol("sqrt(Im01)",real=True)
sqrtIm10 = Symbol("sqrt(Im10)",real=True)
sqrtIm02 = Symbol("sqrt(Im02)",real=True)
sqrtIm20 = Symbol("sqrt(Im20)",real=True)
sqrtIm11 = Symbol("sqrt(Im11)",real=True)
sqrtIm12 = Symbol("sqrt(Im12)",real=True)
sqrtIm21 = Symbol("sqrt(Im21)",real=True)
sqrtIm22 = Symbol("sqrt(Im22)",real=True)


# Amplitudes.

def modAj1j2h(j1,j2,h):

   if (j1==0):
      if (j2==0): return modA00
      elif (j2==1): return modA01
      elif (j2==2): return modA02
   elif (j1==1):
      if (j2==0): return modA10
      elif (j2==1):
         if (h==0): return modA110
         elif (h==1): return modA11par
         elif (h==2): return modA11perp
      elif (j2==2):
         if (h==0): return modA120
         elif (h==1): return modA12par
         elif (h==2): return modA12perp
   elif (j1==2):
      if (j2==0): return modA20
      elif (j2==1):
         if (h==0): return modA210
         elif (h==1): return modA21par
         elif (h==2): return modA21perp
      elif (j2==2):
         if (h==0): return modA220
         elif (h==1): return modA22par1
         elif (h==2): return modA22perp1
         elif (h==3): return modA22par2
         elif (h==4): return modA22perp2

def deltaj1j2h(j1,j2,h):

   if (j1==0):
      if (j2==0): return delta00
      elif (j2==1): return delta01
      elif (j2==2): return delta02
   elif (j1==1):
      if (j2==0): return delta10
      elif (j2==1):
         if (h==0): return delta110
         elif (h==1): return delta11par
         elif (h==2): return delta11perp
      elif (j2==2):
         if (h==0): return delta120
         elif (h==1): return delta12par
         elif (h==2): return delta12perp
   elif (j1==2):
      if (j2==0): return delta20
      elif (j2==1):
         if (h==0): return delta210
         elif (h==1): return delta21par
         elif (h==2): return delta21perp
      elif (j2==2):
         if (h==0): return delta220
         elif (h==1): return delta22par1
         elif (h==2): return delta22perp1
         elif (h==3): return delta22par2
         elif (h==4): return delta22perp2

def etah(h):

   if (h == 2) or (h == 4): return -1
   else: return 1

def etaj1j2h(j1,j2,h):

   return (-1)**(j1+j2)*etah(h)

def Aj1j2h(j1,j2,h):

   if j1==1 and j2==0 and h==0: return one/sqrt(two)*(Asp+Asm)
   elif j1==0 and j2==1 and h==0: return one/sqrt(two)*(Asp-Asm)
   else: return modAj1j2h(j1,j2,h)*exp(I*deltaj1j2h(j1,j2,h))

def Abarj1j2h(j1,j2,h):

   if j1==1 and j2==0 and h==0: return etaj1j2h(j2,j1,h)*one/sqrt(two)*(Asp-Asm)
   elif j1==0 and j2==1 and h==0: return etaj1j2h(j2,j1,h)*one/sqrt(two)*(Asp+Asm)
   else: return etaj1j2h(j2,j1,h)*modAj1j2h(j2,j1,h)*exp(I*deltaj1j2h(j2,j1,h))

def M_Average(j1,j2,h,j1p,j2p,hp):

   return Aj1j2h(j1,j2,h)*Aj1j2h(j1p,j2p,hp).conjugate()+Abarj1j2h(j1,j2,h)*Abarj1j2h(j1p,j2p,hp).conjugate()

def M_DeltaGamma(j1,j2,h,j1p,j2p,hp):

   return Aj1j2h(j1,j2,h)*Abarj1j2h(j1p,j2p,hp).conjugate()+Abarj1j2h(j1,j2,h)*Aj1j2h(j1p,j2p,hp).conjugate()

def M_DirCP(j1,j2,h,j1p,j2p,hp):

   return Aj1j2h(j1,j2,h)*Aj1j2h(j1p,j2p,hp).conjugate()-Abarj1j2h(j1,j2,h)*Abarj1j2h(j1p,j2p,hp).conjugate()

def M_MixCP(j1,j2,h,j1p,j2p,hp):

   return -I*(Aj1j2h(j1,j2,h)*Abarj1j2h(j1p,j2p,hp).conjugate()-Abarj1j2h(j1,j2,h)*Aj1j2h(j1p,j2p,hp).conjugate())

def IT_j1j2hj1pj2php(j1,j2,h,j1p,j2p,hp):

   return ((gamma_H+gamma_L)/4/gamma_H/gamma_L*(M_Average(j1,j2,h,j1p,j2p,hp)-half*delta_gamma_Bs/gamma_Bs*M_DeltaGamma(j1,j2,h,j1p,j2p,hp))).simplify()


# Angles.

def fi(x,i):

   if i==1 : return one
   elif i==2 : return x
   elif i==3 : return sqrt(one-x*x)
   elif i==4 : return three*x*x-one
   elif i==5 : return x*sqrt(one-x*x)
   elif i==6 : return x*x
   elif i==7 : return x*(three*x*x-one)
   elif i==8 : return x*x*sqrt(one-x*x)
   elif i==9 : return one-x*x
   elif i==10 : return (three*x*x-one)*sqrt(one-x*x)
   elif i==11 : return x*(one-x*x)
   elif i==12 : return (three*x*x-one)*(three*x*x-one)
   elif i==13 : return x*(three*x*x-one)*sqrt(one-x*x)
   elif i==14 : return x*x*(one-x*x)
   elif i==15 : return (one-x*x)*sqrt(one-x*x)
   elif i==16 : return (three*x*x-one)*(one-x*x)
   elif i==17 : return x*(one-x*x)*sqrt(one-x*x)
   elif i==18 : return (one-x*x)*(one-x*x)

def gi(x,i):

   if i==1 : return one
   elif i==2 : return cos(x)
   elif i==3 : return sin(x)
   elif i==4 : return cos(x)*cos(x)
   elif i==5 : return sin(x)*cos(x)
   elif i==6 : return sin(x)*sin(x)
   elif i==7 : return cos(two*x)
   elif i==8 : return sin(two*x)
   elif i==9 : return cos(x)*cos(two*x)
   elif i==10 : return cos(x)*sin(two*x)
   elif i==11 : return sin(x)*cos(two*x)
   elif i==12 : return sin(x)*sin(two*x)
   elif i==13 : return cos(two*x)*cos(two*x)
   elif i==14 : return sin(two*x)*cos(two*x)
   elif i==15 : return sin(two*x)*sin(two*x)

fjjphhpindexdict = [[[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]],[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]],[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]]],[[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]],[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]],[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]]],[[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]],[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]],[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]]]]

fjjphhpindexdict[0][0][0][0] = 1
fjjphhpindexdict[0][1][0][0] = 2
fjjphhpindexdict[0][1][0][1] = 3
fjjphhpindexdict[0][1][0][2] = 3
fjjphhpindexdict[0][2][0][0] = 4
fjjphhpindexdict[0][2][0][1] = 5
fjjphhpindexdict[0][2][0][2] = 5
fjjphhpindexdict[1][0][0][0] = 2
fjjphhpindexdict[1][1][0][0] = 6
fjjphhpindexdict[1][1][0][1] = 5
fjjphhpindexdict[1][1][0][2] = 5
fjjphhpindexdict[1][2][0][0] = 7
fjjphhpindexdict[1][2][0][1] = 8
fjjphhpindexdict[1][2][0][2] = 8
fjjphhpindexdict[1][0][1][0] = 3
fjjphhpindexdict[1][0][2][0] = 3
fjjphhpindexdict[1][1][1][0] = 5
fjjphhpindexdict[1][1][2][0] = 5
fjjphhpindexdict[1][1][1][1] = 9
fjjphhpindexdict[1][1][1][2] = 9
fjjphhpindexdict[1][1][2][1] = 9
fjjphhpindexdict[1][1][2][2] = 9
fjjphhpindexdict[1][2][1][0] = 10
fjjphhpindexdict[1][2][2][0] = 10
fjjphhpindexdict[1][2][1][1] = 11
fjjphhpindexdict[1][2][1][2] = 11
fjjphhpindexdict[1][2][2][1] = 11
fjjphhpindexdict[1][2][2][2] = 11
fjjphhpindexdict[2][0][0][0] = 4
fjjphhpindexdict[2][1][0][0] = 7
fjjphhpindexdict[2][1][0][1] = 10
fjjphhpindexdict[2][1][0][2] = 10
fjjphhpindexdict[2][2][0][0] = 12
fjjphhpindexdict[2][2][0][1] = 13
fjjphhpindexdict[2][2][0][2] = 13
fjjphhpindexdict[2][0][1][0] = 5
fjjphhpindexdict[2][0][2][0] = 5
fjjphhpindexdict[2][1][1][0] = 8
fjjphhpindexdict[2][1][2][0] = 8
fjjphhpindexdict[2][1][1][1] = 11
fjjphhpindexdict[2][1][1][2] = 11
fjjphhpindexdict[2][1][2][1] = 11
fjjphhpindexdict[2][1][2][2] = 11
fjjphhpindexdict[2][2][1][0] = 13
fjjphhpindexdict[2][2][2][0] = 13
fjjphhpindexdict[2][2][1][1] = 14
fjjphhpindexdict[2][2][1][2] = 14
fjjphhpindexdict[2][2][2][1] = 14
fjjphhpindexdict[2][2][2][2] = 14
fjjphhpindexdict[0][2][0][3] = 9
fjjphhpindexdict[0][2][0][4] = 9
fjjphhpindexdict[1][2][0][3] = 11
fjjphhpindexdict[1][2][0][4] = 11
fjjphhpindexdict[1][2][1][3] = 15
fjjphhpindexdict[1][2][1][4] = 15
fjjphhpindexdict[1][2][2][3] = 15
fjjphhpindexdict[1][2][2][4] = 15
fjjphhpindexdict[2][2][0][3] = 16
fjjphhpindexdict[2][2][0][4] = 16
fjjphhpindexdict[2][2][1][3] = 17
fjjphhpindexdict[2][2][1][4] = 17
fjjphhpindexdict[2][2][2][3] = 17
fjjphhpindexdict[2][2][2][4] = 17
fjjphhpindexdict[2][0][3][0] = 9
fjjphhpindexdict[2][0][4][0] = 9
fjjphhpindexdict[2][1][3][0] = 11
fjjphhpindexdict[2][1][4][0] = 11
fjjphhpindexdict[2][1][3][1] = 15
fjjphhpindexdict[2][1][3][2] = 15
fjjphhpindexdict[2][1][4][1] = 15
fjjphhpindexdict[2][1][4][2] = 15
fjjphhpindexdict[2][2][3][0] = 16
fjjphhpindexdict[2][2][4][0] = 16
fjjphhpindexdict[2][2][3][1] = 17
fjjphhpindexdict[2][2][3][2] = 17
fjjphhpindexdict[2][2][4][1] = 17
fjjphhpindexdict[2][2][4][2] = 17
fjjphhpindexdict[2][2][3][3] = 18
fjjphhpindexdict[2][2][3][4] = 18
fjjphhpindexdict[2][2][4][3] = 18
fjjphhpindexdict[2][2][4][4] = 18

ghhpindexdict = [[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]]

ghhpindexdict[0][0] = 1
ghhpindexdict[0][1] = 2
ghhpindexdict[0][2] = 3
ghhpindexdict[1][0] = 2
ghhpindexdict[1][1] = 4
ghhpindexdict[1][2] = 5
ghhpindexdict[2][0] = 3
ghhpindexdict[2][1] = 5
ghhpindexdict[2][2] = 6
ghhpindexdict[0][3] = 7
ghhpindexdict[0][4] = 8
ghhpindexdict[1][3] = 9
ghhpindexdict[1][4] = 10
ghhpindexdict[2][3] = 11
ghhpindexdict[2][4] = 12
ghhpindexdict[3][0] = 7
ghhpindexdict[3][1] = 9
ghhpindexdict[3][2] = 11
ghhpindexdict[3][3] = 13
ghhpindexdict[3][4] = 14
ghhpindexdict[4][0] = 8
ghhpindexdict[4][1] = 10
ghhpindexdict[4][2] = 12
ghhpindexdict[4][3] = 14
ghhpindexdict[4][4] = 15

Nj1j2hdict = [[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]],[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]],[[0,0,0,0,0],[0,0,0,0,0],[0,0,0,0,0]]]

Nj1j2hdict[0][0][0] = one/(two*sqrt(two*pi))
Nj1j2hdict[0][1][0] = -sqrt(three)/(two*sqrt(two*pi))
Nj1j2hdict[0][2][0] = sqrt(five)/(two*two*sqrt(two*pi))
Nj1j2hdict[1][0][0] = sqrt(three)/(two*sqrt(two*pi))
Nj1j2hdict[1][1][0] = -three/(two*sqrt(two*pi))
Nj1j2hdict[1][1][1] = -three/(two*two*sqrt(pi))
Nj1j2hdict[1][1][2] = -I*three/(two*two*sqrt(pi))
Nj1j2hdict[1][2][0] = sqrt(three*five)/(two*two*sqrt(two*pi))
Nj1j2hdict[1][2][1] = three*sqrt(five)/(two*two*sqrt(pi))
Nj1j2hdict[1][2][2] = I*three*sqrt(five)/(two*two*sqrt(pi))
Nj1j2hdict[2][0][0] = sqrt(five)/(two*two*sqrt(two*pi))
Nj1j2hdict[2][1][0] = -sqrt(three*five)/(two*two*sqrt(two*pi))
Nj1j2hdict[2][1][1] = -three*sqrt(five)/(two*two*sqrt(pi))
Nj1j2hdict[2][1][2] = -I*three*sqrt(five)/(two*two*sqrt(pi))
Nj1j2hdict[2][2][0] = five/(two*two*two*sqrt(two*pi))
Nj1j2hdict[2][2][1] = three*five/(two*two*sqrt(pi))
Nj1j2hdict[2][2][2] = I*three*five/(two*two*sqrt(pi))
Nj1j2hdict[2][2][3] = three*five/(two*two*two*two*sqrt(pi))
Nj1j2hdict[2][2][4] = I*three*five/(two*two*two*two*sqrt(pi))

def fjjphhp(x,j,jp,h,hp):

   return fi(x,fjjphhpindexdict[j][jp][h][hp])

def ghhp(x,h,hp):

   return gi(x,ghhpindexdict[h][hp])

def Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp):

   return Nj1j2hdict[j1][j2][h]*Nj1j2hdict[j1p][j2p][hp].conjugate()
  

# Masses.

def Mji_1(ji):

   if ji==0: return M0_1
   elif ji==1: return M1_1
   elif ji==2: return M2_1

def Mji_2(ji):

   if ji==0: return M0_2
   elif ji==1: return M1_2
   elif ji==2: return M2_2

def Mj1j2(j1,j2):

   if ((j1 == 0) and (j2 == 0)): return Mji_1(0)*Mji_2(0)
   elif ((j1 == 0) and (j2 == 1)): return Mji_1(0)*Mji_2(1)
   elif ((j1 == 1) and (j2 == 0)): return Mji_1(1)*Mji_2(0)
   elif ((j1 == 0) and (j2 == 2)): return Mji_1(0)*Mji_2(2)
   elif ((j1 == 2) and (j2 == 0)): return Mji_1(2)*Mji_2(0)
   elif ((j1 == 1) and (j2 == 1)): return Mji_1(1)*Mji_2(1)
   elif ((j1 == 1) and (j2 == 2)): return Mji_1(1)*Mji_2(2)
   elif ((j1 == 2) and (j2 == 1)): return Mji_1(2)*Mji_2(1)
   elif ((j1 == 2) and (j2 == 2)): return Mji_1(2)*Mji_2(2)

def hj1j2j1pj2p(j1,j2,j1p,j2p):

   return Mj1j2(j1,j2)*Mj1j2(j1p,j2p).conjugate()*PhSp


def comp_num_fit(j1,j2,h,j1p,j2p,hp):

   factor = one/three/three/PhSp*two**(3)*pi

   if (j1==j1p) and (j2==j2p) and (h==hp): return (factor*re(IT_j1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(j1,j2,j1p,j2p))*ghhp(phi,h,hp)*fjjphhp(cos1,j1,j1p,h,hp)*fjjphhp(cos2,j2,j2p,h,hp)).simplify()

   else: return (factor*two*re(IT_j1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*Nj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp)*hj1j2j1pj2p(j1,j2,j1p,j2p))*ghhp(phi,h,hp)*fjjphhp(cos1,j1,j1p,h,hp)*fjjphhp(cos2,j2,j2p,h,hp)).simplify()

term_list = [[1,1,0,1,1,0],[1,1,1,1,1,1],[1,1,2,1,1,2],[1,1,1,1,1,0],[1,1,2,1,1,0],[1,1,2,1,1,1],[1,0,0,1,0,0],[1,0,0,1,1,0],[1,0,0,1,1,1],[1,0,0,1,1,2],[1,0,0,0,0,0],[0,1,0,0,1,0],[0,1,0,1,1,0],[0,1,0,1,1,1],[0,1,0,1,1,2],[0,1,0,0,0,0],[0,1,0,1,0,0],[0,0,0,0,0,0],[0,0,0,1,1,0],[0,0,0,1,1,1],[0,0,0,1,1,2]]

def printi(i):

   return comp_num_fit(*term_list[i])
