import sys, os

#dataTags = ['MC_AllNeutrals_iso','InclDs_AllNeutrals_iso']
#dataTags = ['MC_LbLcDs', 'MC_BdDstDs', 'MC_BsDsDs', 'MC_BuD0Ds', 'MC_InclDs', 'MC_Signal', 'Data']
#dataTags = ['Data']
#dataTags = ['MC_Signal', 'MC_LbLcDs', 'MC_BdDstDs', 'MC_BsDsDs', 'MC_BuD0Ds']
dataTags = ['MC_Tau', 'MC_Signal', 'MC_LbLcDs', 'MC_BdDstDs', 'MC_BsDsDs', 'MC_BuD0Ds']
polarities = ['MagDown', 'MagUp']

for dataTag in dataTags:
    for pol in polarities:
        os.system('python makeDalitzTuple.py %s %s' %(dataTag, pol) )

#os.system('touch ifinished.log')
