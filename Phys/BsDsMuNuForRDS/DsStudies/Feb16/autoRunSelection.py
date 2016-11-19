import sys, os

dataTags = ['BuD0Ds', 'InclDs', 'LbLcDs', 'MCSignal_Sim08h', 'MCSignal_Sim08a', 'BdDstDs']
polarities = ['MagDown', 'MagUp']

for dataTag in dataTags:
    for pol in polarities:
        os.system('python makeDalitzTuple.py %s %s' %(dataTag, pol) )

#os.system('touch ifinished.log')
