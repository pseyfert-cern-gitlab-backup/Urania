from math import *

fdfs = 3.71
s_fdfs = 0.47

eff_r_MC = 0.977
s_eff_r_MC = 0.011

Rdat = 1.01
s_Rdat = 0.03

fKs = 1.01
s_fKs = 0.09

Nrat = 8.53e-03
s_Nrat = 0.85e-03

brrat =  fdfs*eff_r_MC*Rdat*fKs*Nrat

s_brrat = brrat*sqrt( (s_fdfs/fdfs)**2  + (s_eff_r_MC/eff_r_MC)**2 + (s_Rdat/Rdat)**2 + (s_fKs/fKs)**2 + (s_Nrat/Nrat)**2)

br = brrat*1.33e-03
s_br = br*(sqrt(s_brrat/brrat)**2 + (0.06/1.33)**2)
