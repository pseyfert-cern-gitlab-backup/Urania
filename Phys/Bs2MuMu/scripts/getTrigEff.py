from ROOT import *
from array import *
from valAndErr import *
from tistosEff import *
import os

#For the screen turn off the whistles
gROOT.SetBatch(True)



def getTrigEff(nTupleName, directory, channel, mass_var):

        #---------------------------------------------#
        #-- Get the file names for the nTuple --------#
        #---------------------------------------------#
        print ' o) Get the TISTOS efficiency for:', nTupleName
        triggers = ['_TRIG_','_TIS_','_TOS_','_TISTOS_']
        yields = {}
        for tr_level in triggers:
                for f in os.listdir(directory+channel):
                        #Look for file:
                        if nTupleName in f and tr_level in f and mass_var in f and 'FitInfo' in f:
                                print 'Found file for:', tr_level
                                print '  File :', f
                                lines = open(str(directory+channel)+'/'+str(f), 'r').read().split('\n')
                                # N_sig :  85338.6017779  +-  317.058314102
                                for l in lines:
                                        if 'N_sig' in l:
                                                val = float(l.split(':')[1].split('+-')[0])
                                                #err = float(l.split(':')[1].split('+-')[1])
                                                #n_sig_raw = valAndErr(val, err)
                                                yields[tr_level] = val
                                                print yields

        #Check if TISTOS is bigger that TIS:
        tistosE = valAndErr(1,0)
        if yields.get('_TISTOS_') < yields.get('_TIS_'):
                #Build a tistosEff object and get the efficiency
                #def __init__(self, n_tistos, n_tos, n_tis = -1, n_trig = -1): # Can also be used just for tis or tos efficiency.
                tistosE = tistosEff(yields.get('_TISTOS_'),yields.get('_TOS_'),yields.get('_TIS_'),yields.get('_TRIG_',0))
                #trigEff = tistosEff(yields.get('_TISTOS_'),yields.get('_TOS_'),yields.get('_TIS_'),yields.get('_TRIG_')).getEff()
                #tisEff = tistosEff(yields.get('_TISTOS_'),yields.get('_TOS_'),yields.get('_TIS_'),yields.get('_TRIG_')).getTisEff()


        return tistosE


