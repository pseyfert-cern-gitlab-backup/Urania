from ROOT import *
gROOT.SetBatch(True)

import cutStrings as cs
from readData import readData
from MLLfit import fitBu2JpsiKplus

#In terminal
# python
# from anaMassReso2013 import *

def anaAll():

# For reprocessed 2011 and 2012 data:
        #anaMassReso_Bu('2011_Strip20r1')
        #anaMassReso_Bu('2012_Strip20', {'GoodRuns':True}) #GoodRuns...
        #anaMassReso_Bu('2012_Strip20', {'GoodRuns':False}) #GoodRuns...

# For 2012 analyzed pre-reprocessing 2011 and 2012 data:
        #anaMassReso_Bu('2011_Strip17')
        #anaMassReso_Bu('2012_Strip19abc' , {'GoodRuns':True})
        #anaMassReso_Bu('2012_Strip19abc' , {'GoodRuns':False})

# Study ranges with bad IT alignment
        #anaMassReso_Bu('2012_Strip20_MagUp_i' ) #For Testing
        #anaMassReso_Bu('2012_Strip19abc_BadITRuns' )
#        anaMassReso_Bu('2012_Strip20_BadITRuns' )

# Study ranges withOUT bad IT alignment
        anaMassReso_Bu('2012_Strip19abc_GoodITRuns' )
        anaMassReso_Bu('2012_Strip20_GoodITRuns' )

def anaMassReso_Bu(nTupleName = 'MC12_Sm0', opts =  {}):
        """ Function that combines steps for analyzing the mass resolution for the control channels """

        print ' o) Read in a dataset:'
        Bu_data = readData(nTupleName, {'channel':'Bu'})

        print ' o) Define the cut...'
        cut = Bu_data.get('cut','') + cs.minimalNormBu_rawM_lnf	# cut for raw mass
        cutName = 'minimalNormBu_rawM_lnf'

        #Add PID cut for Kaon
        if opts.get('PIDK', False):
                cut +=	cs.Bu_PID
                cutName += '_PIDK'

        #Add GhostProb cut on all the tracks
        if opts.get('GhostProbCut',0):
                cut +=	cs.Bu_GhostProb
                cutName += '_GPmumuK'

        #Add GhostProb cut on muons
        if opts.get('MuMuGhostProbCut',0):
                cut +=	cs.MuMu_GhostProb
                cutName += '_GPmumu'

        #Require JpsiDiMuon triggers
        if opts.get('JpsiTrig', False):
                Bu_Jpsi_trig = cs.Bu_Jpsi_L0 + cs.Bu_Jpsi_Hlt1 + cs.Bu_Jpsi_Hlt2
                cut +=	Bu_Jpsi_trig

        print ' o) Perform mass fits using an unconstrained mass...'
        massVar = 'Bplus_M'

        fitBu2JpsiKplus(Bu_data,massVar,cutName+'_TRIG',cut)

