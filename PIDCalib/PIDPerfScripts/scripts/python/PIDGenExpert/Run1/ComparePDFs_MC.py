import os, sys
from PlotPIDComparison import plotComparison

from ConfigMC import *

config = None
if len(sys.argv)>1 : 
  config = sys.argv[1]
else : 
  print "Usage: ComparePDFs.py [config]"
  print "  configs are: "
  for i in sorted(configs.keys()) : 
    print "    ", i
  sys.exit(0)

var = config
bins = configs[config]["bins"]
syst = 1
stat = 10
if 'syst' in configs[config] : syst = configs[config]['syst']
if 'stat' in configs[config] : stat = configs[config]['stat']
limits = None
if 'limits' in configs[config] : limits = configs[config]['limits']

polarity = [ "MagDown", "MagUp" ]
year = [ 2011, 2012 ]
#polarity = [ "MagDown"]
#year = [ 2012 ]

# Do not plot for now
syst = None
stat = None

outdir = eosrootdir + "/" + config

filelist = []

for p in polarity : 
  for y in year : 
    calibfile = "%s/%s_%s.root" % (outdir, p, y)
    name = "%s_%s" % (p, y)
    filelist   += [ ( calibfile, outdir + "/control/" + name + "_control.root", "plots_mc/" + var + "_" + name) ] 
    if stat : 
      for i in range(0, stat) : 
        name = "%s_%s_stat_%d" % (p, y, i)
        filelist += [ ( calibfile, outdir + "/control/" + name + "_control.root", "plots_mc/" + var + "_" + name) ] 
    if syst : 
      for i in range(1, syst+1) : 
        name = "%s_%s_syst_%d" % (p, y, i)
        filelist += [ ( calibfile, outdir + "/control/" + name + "_control.root", "plots_mc/" + var + "_" + name) ] 

for f in filelist : 
  print f
  if limits : 
    plotComparison(f[0], f[1], f[2], var, bins, limits[0], limits[1] )
  else : 
    plotComparison(f[0], f[1], f[2], var, bins)
#  os.system("eos cp %s %s/plots/%s" % (f[2], eosdir, ))
