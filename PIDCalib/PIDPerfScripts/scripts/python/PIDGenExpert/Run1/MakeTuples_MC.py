import os, sys
from ROOT import TFile, TNtuple, gDirectory, gROOT
from math import sqrt, log

from ConfigMC import *

def convert_single_file(infile, indir, f2, nt2, treename, pidvar, ptvar, etavar, ntracksvar, transform) :
  match_code = None
  f1 = TFile.Open(infile)
  gDirectory.cd(indir)
  nt1 = gROOT.FindObject(treename)
  f2.cd()
  nentries = nt1.GetEntries()
  print "tuple %s: %d entries" % (treename, nentries )
  n = 0
  x_code = compile("i.%s" % pidvar, '<string>', 'eval')
  pid_code = compile(transform, '<string>', 'eval')
  pt_code = compile("log(i.%s)" % ptvar, '<string>', 'eval')
  eta_code = compile("i.%s" % etavar, '<string>', 'eval')
  ntracks_code = compile("log(i.%s)" % ntracksvar, '<string>', 'eval')
  if 'match' in [ b.GetName() for b in nt1.GetListOfBranches() ] : 
    match_code = compile("i.match", '<string>', 'eval')
  for i in nt1 :
      n += 1
      if (n % 10000 == 0) : 
        print "  event %d/%d" % (n, nentries)
      if match_code : 
        m = eval(match_code)
        if m < 1. : continue
      x = eval(x_code)
      pid = eval(pid_code)
      pt  = eval(pt_code)
      eta = eval(eta_code)
      ntracks = eval(ntracks_code)
      nt2.Fill(pid, pt, eta, ntracks, 1., 1.)
  f1.Close()

if len(sys.argv)>1 : 
  # config name, e.g. "p_ProbNNp"
  configname = sys.argv[1]
else : 
  print "Usage: MakeTuples [config] [option1:option2:...] [dataset1:dataset2:]"
  print "  configs are: "
  for i in sorted(configs.keys()) : 
    print "    ", i
  print "  options are: "
  print "    test - run for just a single PIDCalib file rather than whole dataset"
  print "  datasets can be, e.g. "
  print "    MagDown_2012:MadUp_2011"
  print "    or leave empty to process all available datasets"
  sys.exit(0)

config = configs[configname]
# sample name, e.g. "p" for proton
samplename = config['sample']
sample = samples[samplename]
datasets = sample['datasets']
dslist = datasets.keys()
options = ""
if len(sys.argv)>2 : options = sys.argv[2].split(":")
if len(sys.argv)>3 : dslist = sys.argv[3].split(":")

# resampled variable name
var = configname

# other variable names
pidvar = config['var']
ptvar = sample['pt']
etavar = sample['eta']
ntracksvar = sample['ntracks']
treename = sample['tree']
indir = sample['dir']
transform = config['transform_forward']

os.system("/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select mkdir -p %s/%s" % (eosdir, configname))
#os.system("mkdir -p %s/%s/" % (datadir, var))

# Create dictionary with the lists of PIDCalib datasets for each year and magnet polarity
dsdict = {}
for ds in dslist : 
  dsdict[ds] = [ datasets[ds] ]
  if "test" in options : break

# Loop over PIDCalib datasets
for pol,dss in dsdict.iteritems() : 

  calibfile = eosrootdir + "/" + var + "/" + pol + ".root"

  f2 = TFile.Open(calibfile,"RECREATE")
  nt2 = TNtuple("pid","pid", "%s:Pt:Eta:Ntracks:Charge:w" % var)

  print "Polarity " + pol

  for ds in dss : 
    infile = eosrootdir + "/" + ds
    convert_single_file(infile, indir, f2, nt2, treename, pidvar, ptvar, etavar, ntracksvar, transform)

  nt2.Write()
  f2.Close()
