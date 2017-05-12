import os

# List of input ROOT files with MC ntuples. Format: 
#   (inputfile, outputfile, dataset)
files = [
  ("root://eoslhcb.cern.ch//eos/lhcb/wg/PID/PIDGen/Validation/Lb2Lcpi/sim08_2012_md.root", "sim08_2012_md_pidcorr.root", "MagDown_2012"), 
]

# Name of the input tree
# Could also include ROOT directory, e.g. "Dir/Ntuple"
input_tree = "lb2lch_filt"

# Postfixes of the Pt, Eta and Ntracks variables (ntuple variable name w/o branch name)
# e.g. if the ntuple contains "pion_PT", it should be just "PT"
ptvar = "pt"
etavar = "eta"
##pvar = "p"      # Could use P variable instead of eta
ntrvar = "nTracks"  # This should correspond to the number of "Best tracks", not "Long tracks"!

# Dictionary of tracks with their PID variables, in the form {branch name}:{pidvars}
# For each track branch name, {pidvars} is a dictionary in the form {ntuple variable}:{pid config}, 
#   where 
#     {ntuple variable} is the name of the corresponding ntuple PID variable without branch name, 
#   and 
#     {pid_config} is the string describing the PID configuration. 
# Run PIDCorr.py without arguments to get the full list of PID configs
tracks = {
  'h'   : {
            "V2ProbNNK"  : "pi_V2ProbNNK", 
            "V2ProbNNpi" : "pi_V2ProbNNpi", 
            "V2ProbNNp"  : "pi_V2ProbNNp", 
            "V3ProbNNK"  : "pi_V3ProbNNK", 
            "V3ProbNNpi" : "pi_V3ProbNNpi", 
            "V3ProbNNp"  : "pi_V3ProbNNp", 
            "pidk"       : "pi_CombDLLK", 
            "pidp"       : "pi_CombDLLp", 
           }, 
  'lpi' : { 
            "V2ProbNNK"  : "pi_V2ProbNNK", 
            "V2ProbNNpi" : "pi_V2ProbNNpi", 
            "V2ProbNNp"  : "pi_V2ProbNNp", 
            "V3ProbNNK"  : "pi_V3ProbNNK", 
            "V3ProbNNpi" : "pi_V3ProbNNpi", 
            "V3ProbNNp"  : "pi_V3ProbNNp", 
            "pidk"       : "pi_CombDLLK", 
            "pidp"       : "pi_CombDLLp", 
           }, 
  'lk'  : { 
            "V2ProbNNK"  : "K_V2ProbNNK", 
            "V2ProbNNpi" : "K_V2ProbNNpi", 
            "V2ProbNNp"  : "K_V2ProbNNp", 
            "V3ProbNNK"  : "K_V3ProbNNK", 
            "V3ProbNNpi" : "K_V3ProbNNpi", 
            "V3ProbNNp"  : "K_V3ProbNNp", 
            "pidk"       : "K_CombDLLK", 
            "pidp"       : "K_CombDLLp", 
           }, 
  'lp'  : {
            "V2ProbNNK"  : "p_V2ProbNNK", 
            "V2ProbNNpi" : "p_V2ProbNNpi", 
            "V2ProbNNp"  : "p_V2ProbNNp", 
            "V3ProbNNK"  : "p_V3ProbNNK", 
            "V3ProbNNpi" : "p_V3ProbNNpi", 
            "V3ProbNNp"  : "p_V3ProbNNp", 
            "pidk"       : "p_CombDLLK", 
            "pidp"       : "p_CombDLLp", 
           }, 
}

output_tree = input_tree.split("/")[-1]
treename = input_tree

for input_file, output_file, dataset in files : 
  tmpinfile = input_file
  tmpoutfile = "tmp1.root"
  for track, subst in tracks.iteritems() : 
    for var, config in subst.iteritems() : 
      command = "python $PIDPERFSCRIPTSROOT/scripts/python/PIDGenUser/PIDCorr.py"
#      command = "python ../../PIDCorr.py"
      command += " -m %s_%s" % (track, ptvar)
      command += " -e %s_%s" % (track, etavar)
##      command += " -q %s_%s" % (track, pvar)   # Could also use P variable instead of eta
      command += " -n %s" % ntrvar
      command += " -t %s" % treename
      command += " -p %s_%s_corr" % (track, var)
      command += " -s %s_%s" % (track, var)
      command += " -c %s" % config
      command += " -d %s" % dataset
      command += " -i %s" % tmpinfile
      command += " -o %s" % tmpoutfile

      treename = output_tree
      tmpinfile = tmpoutfile
      if tmpoutfile == "tmp1.root" : 
        tmpoutfile = "tmp2.root"
      else : 
        tmpoutfile = "tmp1.root"

      print command
      os.system(command)

  os.system("rm %s" % tmpoutfile)
  os.system("mv %s %s" % (tmpinfile, output_file))
