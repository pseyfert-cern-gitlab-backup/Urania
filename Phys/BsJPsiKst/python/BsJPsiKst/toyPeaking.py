import cPickle
from Urania import *
AccessPackage("Bs2MuMu")
G = cPickle.load(file(os.environ["BSJPSIKSTROOT"] + "/generators/generator_2012"))
from math import *
from triggerclass import *
from scipy import random as rnd
import sys, os

Nevt = 500000

out = channelData(G.generate(int(Nevt)))
round_vars = ["Kplus_ID"] ## Variables that you want 
keytypes = {}
#delta= int(sys.argv[1])

for i in range(len(out)):
    entry = out[i]
    #entry["evt"] = i + 2*delta*Nevt
    
    for key in round_vars:
        entry[key] = int(round(entry[key]))

for key in out[1].keys():
    if key in round_vars: keytypes[key] = "I"
    else: keytypes[key] = "F"


#out.save(os.environ["HOME"] + "/vol5/BsJpsiPhi/fakeBkg/Bkg_sample_" + str(Nevt/1000)+ "_K_test", keytypes = keytypes)

out.save(os.environ["HOME"] + "/Bkg_sample_2015_" + str(int(round(Nevt/1000)))+ "K", keytypes = keytypes)
