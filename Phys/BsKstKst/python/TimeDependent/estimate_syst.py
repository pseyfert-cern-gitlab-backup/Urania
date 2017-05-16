from ROOT import *

from _wide import par_result_dict as dict0
from _Lass import par_result_dict as dict1

h = TH1F("h","h",100,-20,20)

for par in dict0.keys(): h.Fill((dict1[par][0]-dict0[par][0])/dict0[par][1])

h.Draw()

for par in dict0.keys(): print par+' = '+'{:.3f}'.format(dict0[par][0])+' +- '+'{:.3f}'.format(dict0[par][1])+' +- '+'{:.3f}'.format(dict1[par][0]-dict0[par][0])
