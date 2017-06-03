from ROOT import *

from _wide_Pelaez_varnw import par_result_dict as dict0 # default
from _wide_Pelaez_CPVperchannel_varnw import par_result_dict as dict1

h = TH1F("h","h",100,-20,20)

c_mass_pars = ['mV','gammaV','mT','gammaT','c1_mass_swave','c2_mass_swave','c3_mass_swave','c4_mass_swave','c5_mass_swave','c6_mass_swave','c7_mass_swave','c8_mass_swave','c9_mass_swave']

for par in dict0.keys():
   if par not in c_mass_pars: h.Fill((dict1[par][0]-dict0[par][0])/dict0[par][1])

h.Draw()

for par in dict0.keys():
   if par not in c_mass_pars: print par+' = '+'{:.3f}'.format(dict0[par][0])+' +- '+'{:.3f}'.format(dict0[par][1])+' +- '+'{:.3f}'.format(dict1[par][0]-dict0[par][0])
