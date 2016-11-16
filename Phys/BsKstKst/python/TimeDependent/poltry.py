from ROOT import *
from GetAcc import *

gROOT.ProcessLine(".L ../../src/TimeDependent/PolTAcc.cxx++")

polpdf = PolTAcc("polpdf","polpdf",t_MC,year_opt,trig_opt,wide_window_opt)
