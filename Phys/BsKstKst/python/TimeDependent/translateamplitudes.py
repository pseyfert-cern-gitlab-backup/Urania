from sympy import *

f_VV = Symbol("f_VV",real=True,domain=Interval(0,1),positive=True)
f_Swave = Symbol("f_Swave",real=True,domain=Interval(0,1),positive=True)
f_SS = Symbol("f_SS",real=True,domain=Interval(0,1),positive=True)
D_SVVS = Symbol("D_SVVS",real=True,domain=Interval(-1,1))
D_SVVSplus = Symbol("(1+D_SVVS)",real=True,domain=Interval(0,2),positive=True)
D_SVVSminus = Symbol("(1-D_SVVS)",real=True,domain=Interval(0,2),positive=True)
f_VTTV = Symbol("f_VTTV",real=True,domain=Interval(0,1),positive=True)
f_TT = Symbol("f_TT",real=True,domain=Interval(0,1),positive=True)
D_STTS = Symbol("D_STTS",real=True,domain=Interval(-1,1))
D_STTSplus = Symbol("(1+D_STTS)",real=True,domain=Interval(0,2),positive=True)
D_STTSminus = Symbol("(1-D_STTS)",real=True,domain=Interval(0,2),positive=True)
D_VTTV = Symbol("D_VTTV",real=True,domain=Interval(-1,1))
D_VTTVplus = Symbol("(1+D_VTTV)",real=True,domain=Interval(0,2),positive=True)
D_VTTVminus = Symbol("(1-D_VTTV)",real=True,domain=Interval(0,2),positive=True)
fL_VV = Symbol("fL_VV",real=True,domain=Interval(0,1),positive=True)
xpar_VV = Symbol("xpar_VV",real=True,domain=Interval(0,1),positive=True)
fL_VT = Symbol("fL_VT",real=True,domain=Interval(0,1),positive=True)
xpar_VT = Symbol("xpar_VT",real=True,domain=Interval(0,1),positive=True)
fL_TV = Symbol("fL_TV",real=True,domain=Interval(0,1),positive=True)
xpar_TV = Symbol("xpar_TV",real=True,domain=Interval(0,1),positive=True)
fL_TT = Symbol("fL_TT",real=True,domain=Interval(0,1),positive=True)
xpar1_TT = Symbol("xpar1_TT",real=True,domain=Interval(0,1),positive=True)
xperp1_TT = Symbol("xperp1_TT",real=True,domain=Interval(0,1),positive=True)
xpar2_TT = Symbol("xpar2_TT",real=True,domain=Interval(0,1),positive=True)
f_VVminus = Symbol("(1-f_VV)",real=True,domain=Interval(0,1),positive=True)
f_SSminus = Symbol("(1-f_SS)",real=True,domain=Interval(0,1),positive=True)
f_Swaveminus = Symbol("(1-f_Swave)",real=True,domain=Interval(0,1),positive=True)
f_VTTVminus = Symbol("(1-f_VTTV)",real=True,domain=Interval(0,1),positive=True)
f_TTminus = Symbol("(1-f_TT)",real=True,domain=Interval(0,1),positive=True)
fL_VVminus = Symbol("(1-fL_VV)",real=True,domain=Interval(0,1),positive=True)
fL_VTminus = Symbol("(1-fL_VT)",real=True,domain=Interval(0,1),positive=True)
fL_TVminus = Symbol("(1-fL_TV)",real=True,domain=Interval(0,1),positive=True)
fL_TTminus = Symbol("(1-fL_TT)",real=True,domain=Interval(0,1),positive=True)
xpar_VVminus = Symbol("(1-xpar_VV)",real=True,domain=Interval(0,1),positive=True)
xpar_VTminus = Symbol("(1-xpar_VT)",real=True,domain=Interval(0,1),positive=True)
xpar_TVminus = Symbol("(1-xpar_TV)",real=True,domain=Interval(0,1),positive=True)
xpar1_TTminus = Symbol("(1-xpar1_TT)",real=True,domain=Interval(0,1),positive=True)
xperp1_TTminus = Symbol("(1-xperp1_TT)",real=True,domain=Interval(0,1),positive=True)
xpar2_TTminus = Symbol("(1-xpar2_TT)",real=True,domain=Interval(0,1),positive=True)
delta00 = Symbol("delta00",real=True)
delta01 = Symbol("delta01",real=True)
delta10 = Symbol("delta10",real=True)
delta02 = Symbol("delta02",real=True)
delta20 = Symbol("delta20",real=True)
delta11par = Symbol("delta11par",real=True)
delta11perp = Symbol("delta11perp",real=True)
delta120 = Symbol("delta120",real=True)
delta12par = Symbol("delta12par",real=True)
delta12perp = Symbol("delta12perp",real=True)
delta210 = Symbol("delta210",real=True)
delta21par = Symbol("delta21par",real=True)
delta21perp = Symbol("delta21perp",real=True)
delta220 = Symbol("delta220",real=True)
delta22par = Symbol("delta22par",real=True)
delta22perp = Symbol("delta22perp",real=True)
delta22par2 = Symbol("delta22par2",real=True)
delta22perp2 = Symbol("delta22perp2",real=True)
DCP_withBlinding = Symbol("DCP_withBlinding",real=True,domain=Interval(-1,1))
DCP_withBlindingplus = Symbol("(1+DCP_withBlinding)",real=True,domain=Interval(0,2),positive=True)
DCP_withBlindingminus = Symbol("(1-DCP_withBlinding)",real=True,domain=Interval(0,2),positive=True)

parlist = [f_VV,f_Swave,f_SS,D_SVVS,f_VTTV,f_TT,D_STTS,D_VTTV,fL_VV,xpar_VV,fL_VT,xpar_VT,fL_TV,xpar_TV,fL_TT,xpar1_TT,\
xperp1_TT,xpar2_TT,delta00,delta01,delta10,delta02,delta20,delta11par,delta11perp,delta120,delta12par,delta12perp,delta210,\
delta21par,delta21perp,delta220,delta22par,delta22perp,delta22par2,delta22perp2,DCP_withBlinding]


def simplifyexpression(s):

   return (s.subs([(D_SVVSplus,(1+D_SVVS)),(D_STTSplus,(1+D_STTS)),(D_VTTVplus,(1+D_VTTV)),(DCP_withBlindingplus,(1+DCP_withBlinding)),(D_SVVSminus,(1-D_SVVS)),(D_STTSminus,(1-D_STTS)),(D_VTTVminus,(1-D_VTTV)),(DCP_withBlindingminus,(1-DCP_withBlinding)),(f_VVminus,(1-f_VV)),(f_SSminus,(1-f_SS)),(f_Swaveminus,(1-f_Swave)),(f_VTTVminus,(1-f_VTTV)),(f_TTminus,(1-f_TT)),(fL_VVminus,(1-fL_VV)),(fL_VTminus,(1-fL_VT)),(fL_TVminus,(1-fL_TV)),(fL_TTminus,(1-fL_TT)),(xpar_VVminus,(1-xpar_VV)),(xpar_VTminus,(1-xpar_VT)),(xpar_TVminus,(1-xpar_TV)),(xpar1_TTminus,(1-xpar1_TT)),(xperp1_TTminus,(1-xperp1_TT)),(xpar2_TTminus,(1-xpar2_TT))])).simplify()


def wfj1j2(j1,j2):

   if j1 == 0:
      if j2 == 0: return f_VVminus*f_Swave*f_SS
      elif j2 == 1: return f_VVminus*f_Swave*f_SSminus*0.5*D_SVVSplus
      elif j2 == 2: return f_VVminus*f_Swaveminus*f_VTTVminus*f_TTminus*0.5*D_STTSplus
   elif j1 == 1:
      if j2 == 0: return f_VVminus*f_Swave*f_SSminus*0.5*D_SVVSminus
      elif j2 == 1: return f_VV
      elif j2 == 2: return f_VVminus*f_Swaveminus*f_VTTV*0.5*D_VTTVplus
   elif j1 == 2:
      if j2 == 0: return f_VVminus*f_Swaveminus*f_VTTVminus*f_TTminus*0.5*D_STTSminus
      elif j2 == 1: return f_VVminus*f_Swaveminus*f_VTTV*0.5*D_VTTVminus
      elif j2 == 2: return f_VVminus*f_Swaveminus*f_VTTVminus*f_TT


def pfj1j2h(j1,j2,h):

   if j1 == 1:
      if j2 == 1:
         if h == 0: return fL_VV
         elif h == 1: return fL_VVminus*xpar_VV
         elif h == 2: return fL_VVminus*xpar_VVminus
      elif j2 == 2:
         if h == 0: return fL_VT
         elif h == 1: return fL_VTminus*xpar_VT
         elif h == 2: return fL_VTminus*xpar_VTminus
   elif j1 == 2:
      if j2 == 1:
         if h == 0: return fL_TV
         elif h == 1: return fL_TVminus*xpar_TV
         elif h == 2: return fL_TVminus*xpar_TVminus
      elif j2 == 2:
         if h == 0: return fL_TT
         elif h == 1: return fL_TTminus*xpar1_TT
         elif h == 2: return fL_TTminus*xpar1_TTminus*xperp1_TT
         elif h == 3: return fL_TTminus*xpar1_TTminus*xperp1_TTminus*xpar2_TT
         elif h == 4: return fL_TTminus*xpar1_TTminus*xperp1_TTminus*xpar2_TTminus
   return 1

def deltaj1j2h(j1,j2,h):

   if j1 == 0:
      if j2 == 0: return delta00
      elif j2 == 1: return delta01
      elif j2 == 2: return delta02
   elif j1 == 1:
      if j2 == 0: return delta10
      elif j2 == 1:
         if h == 0: return 0
         elif h == 1: return delta11par
         elif h == 2: return delta11perp
      elif j2 == 2:
         if h == 0: return delta120
         elif h == 1: return delta12par
         elif h == 2: return delta12perp      
   elif j1 == 2:
      if j2 == 0: return delta20
      elif j2 == 1:
         if h == 0: return delta210
         elif h == 1: return delta21par
         elif h == 2: return delta21perp
      elif j2 == 2:
         if h == 0: return delta220
         elif h == 1: return delta22par
         elif h == 2: return delta22perp
         elif h == 3: return delta22par2
         elif h == 4: return delta22perp2


def etah(h):

   if (h == 2) or (h == 4): return -1
   else: return 1


def etaj1j2h(j1,j2,h):

   return (-1)**(j1+j2)*etah(h)


def Aj1j2h(j1,j2,h):

   wf = wfj1j2(j1,j2)
   pf = pfj1j2h(j1,j2,h)
   delta = deltaj1j2h(j1,j2,h)
   return sqrt(wf*pf*DCP_withBlindingplus)*(cos(delta)+I*sin(delta))


def Abarj1j2h(j1,j2,h):

   wf = wfj1j2(j2,j1)
   pf = pfj1j2h(j2,j1,h)
   delta = deltaj1j2h(j2,j1,h)
   return etaj1j2h(j2,j1,h)*sqrt(wf*pf*DCP_withBlindingminus)*(cos(delta)+I*sin(delta))


def Aplus(j1,j2,h):

   return 1/sqrt(2)*(Aj1j2h(j1,j2,h)+Aj1j2h(j2,j1,h))


def Aminus(j1,j2,h):

   return 1/sqrt(2)*(Aj1j2h(j1,j2,h)-Aj1j2h(j2,j1,h))


def Abarplus(j1,j2,h):

   return 1/sqrt(2)*(Abarj1j2h(j1,j2,h)+Abarj1j2h(j2,j1,h))


def Abarminus(j1,j2,h):

   return 1/sqrt(2)*(Abarj1j2h(j1,j2,h)-Abarj1j2h(j2,j1,h))


def sqmod(amp):

   return (amp*conjugate(amp)).simplify()


def phase(amp):

   amp_re = (re(amp)).simplify()
   amp_im = (im(amp)).simplify()
   return (atan(amp_im/amp_re)).simplify()


def avsqmodplus(j1,j2,h):

   return simplifyexpression((0.5*(sqmod(Aplus(j1,j2,h))+sqmod(Abarplus(j1,j2,h)))).simplify())


def avsqmodminus(j1,j2,h):

   return simplifyexpression((0.5*(sqmod(Aminus(j1,j2,h))+sqmod(Abarminus(j1,j2,h)))).simplify())


def deltaphaseplus(j1,j2,h):

   return simplifyexpression((0.5*(phase(Aplus(j1,j2,h))+phase(Abarplus(j1,j2,h)))).simplify())


def deltaphaseminus(j1,j2,h):

   return simplifyexpression((0.5*(phase(Aminus(j1,j2,h))+phase(Abarminus(j1,j2,h)))).simplify())


def formulaavsqmodplus(j1,j2,h):

   expression = avsqmodplus(j1,j2,h)
   arglist = []
   symsinexpression = list(expression.atoms())
   for i in parlist:
      if i in symsinexpression: arglist.append(i)

   print 'avsqmodplus_'+str(j1)+str(j2)+str(h)+' = RooFormulaVar("avsqmodplus_'+str(j1)+str(j2)+str(h)+'","avsqmodplus_'+str(j1)+str(j2)+str(h)+'","'+str(expression)+'",RooArgList'+str(tuple(arglist)).replace(' ','')+')'


def formulaavsqmodminus(j1,j2,h):

   expression = avsqmodminus(j1,j2,h)
   arglist = []
   symsinexpression = list(expression.atoms())
   for i in parlist:
      if i in symsinexpression: arglist.append(i)

   print 'avsqmodminus_'+str(j1)+str(j2)+str(h)+' = RooFormulaVar("avsqmodminus_'+str(j1)+str(j2)+str(h)+'","avsqmodminus_'+str(j1)+str(j2)+str(h)+'","'+str(expression)+'",RooArgList'+str(tuple(arglist)).replace(' ','')+')'


def formuladeltaphaseplus(j1,j2,h):

   expression = deltaphaseplus(j1,j2,h)
   arglist = []
   symsinexpression = list(expression.atoms())
   for i in parlist:
      if i in symsinexpression: arglist.append(i)

   print 'deltaphaseplus_'+str(j1)+str(j2)+str(h)+' = RooFormulaVar("deltaphaseplus_'+str(j1)+str(j2)+str(h)+'","deltaphaseplus_'+str(j1)+str(j2)+str(h)+'","'+str(expression)+'",RooArgList'+str(tuple(arglist)).replace(' ','')+')'


def formuladeltaphaseminus(j1,j2,h):

   expression = deltaphaseminus(j1,j2,h)
   arglist = []
   symsinexpression = list(expression.atoms())
   for i in parlist:
      if i in symsinexpression: arglist.append(i)

   print 'deltaphaseminus_'+str(j1)+str(j2)+str(h)+' = RooFormulaVar("deltaphaseminus_'+str(j1)+str(j2)+str(h)+'","deltaphaseminus_'+str(j1)+str(j2)+str(h)+'","'+str(expression)+'",RooArgList'+str(tuple(arglist)).replace(' ','')+')'


def rotateamplitudes(j1,j2,h):

   formulaavsqmodplus(j1,j2,h)
   formulaavsqmodminus(j1,j2,h)
   formuladeltaphaseplus(j1,j2,h)
   formuladeltaphaseminus(j1,j2,h)
