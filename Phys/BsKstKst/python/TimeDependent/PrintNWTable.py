from ROOT import *
gROOT.ProcessLine('.x ../../src/TimeDependent/NWclass.h')

nw = NWclass()

def name(j1,j2,h,j1p,j2p,hp,part):

   s = ''
   if part==0: s += '\\mathrm{Re}(F_{'
   else: s += '\\mathrm{Im}(F_{'

   if j1==0: s += 'S'
   elif j1==1: s += 'V'
   elif j1==2: s += 'T'

   if j2==0: s += 'S'
   elif j2==1: s += 'V'
   elif j2==2: s += 'T'

   if h==0: s += ''
   elif h==1: s += ''
   elif h==2: s += ''

   if j1p==0: s += ''
   elif j1p==1: s += ''
   elif j1p==2: s += ''

   if j2p==0: s += ''
   elif j2p==1: s += ''
   elif j2p==2: s += ''

   if hp==0: s += ''
   elif hp==1: s += ''
   elif hp==2: s += ''
