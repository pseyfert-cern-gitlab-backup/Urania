from ROOT import *
gROOT.SetBatch(True)

import cutStrings as cs
from readData import readData
from MLLfit import fitBu2JpsiKplus

#In terminal
# python
# from anaMassReso2013 import *

def anaYields(what, tistos = False):

# The idea is to to get all the TRIG yields, save them in files
# Then get all the TIS TOS and TISTOS yields for the samples where
# we need the trigger efficeinacy from.

# Evaluate the trigger efficiency later when plotting and reading in the
# yields from the files (plotYields2.py)


        files = []
        # ----------------------------- #
        # Old 11+12
        if what is 'old':
                files = ['2011_Strip17','2012_Strip19abc']

        # New 11+12
        if what is 'new':
                files = ['2011_Strip20r1','2012_Strip20']

        # ----------------------------- #
        # New 2011
        if what is '2011_subsamples':
                files = [ '2011_Strip20r1_A','2011_Strip20r1_B','2011_Strip20r1_C','2011_Strip20r1_D' ]

        if what is '2011_all_files':
                # Reprocessed 2011 on old 2011 - all the individual files
                files = ['2011_Strip20r1_a0',
                        '2011_Strip20r1_a','2011_Strip20r1_b','2011_Strip20r1_c','2011_Strip20r1_d','2011_Strip20r1_e','2011_Strip20r1_f',
                        '2011_Strip20r1_g', '2011_Strip20r1_h', '2011_Strip20r1_i', '2011_Strip20r1_j', '2011_Strip20r1_k','2011_Strip20r1_l']

        # Old 2012
        if what is '2012_old_subsamples':
                files = ['2012_Strip19',
                        '2012_Strip19a',
                        '2012_Strip19b',
                        '2012_Strip19c']
        # New 2012
        if what is '2012_all_files':
                files_12 = [
                        '2012_Strip20_MagDown_a','2012_Strip20_MagDown_b','2012_Strip20_MagDown_c','2012_Strip20_MagDown_d','2012_Strip20_MagDown_e','2012_Strip20_MagDown_f',
                        '2012_Strip20_MagDown_g', '2012_Strip20_MagDown_h', '2012_Strip20_MagDown_i', '2012_Strip20_MagDown_j', '2012_Strip20_MagDown_k',
                        '2012_Strip20_MagUp_a','2012_Strip20_MagUp_b','2012_Strip20_MagUp_c','2012_Strip20_MagUp_d','2012_Strip20_MagUp_e','2012_Strip20_MagUp_f',
                        '2012_Strip20_MagUp_g', '2012_Strip20_MagUp_h', '2012_Strip20_MagUp_i']

        if what is '2012_subsamples':
                files = ['2012_Strip20_MagDown_A','2012_Strip20_MagDown_B','2012_Strip20_MagDown_C','2012_Strip20_MagDown_D',
                        '2012_Strip20_MagUp_A','2012_Strip20_MagUp_B','2012_Strip20_MagUp_C','2012_Strip20_MagUp_D' ]

        # Good/Bad IT runs
        if what is 'GoodBadIT':
                files = ['2012_Strip20_GoodITRuns', '2012_Strip20_BadITRuns',
                        '2012_Strip19abc_GoodITRuns', '2012_Strip19abc_BadITRuns']

        if tistos:
                for f in files:
                        print ' Fitting TIS TOS and TISTOS:'
                        getYield_Bu(f,{'trigLev':'TIS'})
                        getYield_Bu(f,{'trigLev':'TOS'})
                        getYield_Bu(f,{'trigLev':'TISTOS'})
        else:
                for f in files:
                        getYield_Bu(f) #Get the TRIG yield:w


def getYield_Bu(nTupleName = 'MC12_Sm0', opts =  {}):
        """ Function that combines steps for analyzing the mass resolution for the control channels """

        print ' o) Read in a dataset:'
        Bu_data = readData(nTupleName, {'channel':'Bu'})

        print ' o) Define the cut...'
        cut = cs.minimalNormBu_lnf
        cutName = 'minimalNormBu_lnf'

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
                cutName += '_JpsiTrig_'

       #Do a TIS fit
        if opts.get('trigLev', 'TRIG') is 'TIS':
                cut += cs.Bu_cut_TIS
                print '  TIS cut:', cut

        #Do a TIS fit
        if opts.get('trigLev', 'TRIG') is 'TOS':
                cut += cs.Bu_cut_TOS
                print '  TOS cut:', cut

         #Do a TISTOS fit
        if opts.get('trigLev', 'TRIG') is 'TISTOS':
                cut += cs.Bu_cut_TIS +  cs.Bu_cut_TOS
                print '  TISTOS cut:', cut

        print ' o) Perform mass fits using an constrained mass...'
        massVar = 'Bplus_JCMass'
        fitBu2JpsiKplus(Bu_data,massVar,cutName+'_'+str(opts.get('trigLev','TRIG')),cut)


def getYield_Bs(nTupleName = 'MC12_Sm0', opts =  {}):
        """ Function that combines steps for analyzing the mass resolution for the control channels """

        print ' o) Read in a dataset:'
        Bu_data = readData(nTupleName, {'channel':'Bs'})

        print ' o) Define the cut...'
        cut = cs.normBs_lnf
        cutName = 'normBs_lnf'

        #PIDK cut
        if opts.get('PIDK', False):
                sufId = 'PIDK'
                cut = cs.normBsPID_lnf
                cutName = 'normBsPID_lnf'

        #Remove bad runs from Strip 19b
        #cut +=	cs.cutBadRuns
        #Add GhostProb cut

        if opts.get('GhostProbCut', False):
                cut +=	cs.Bs_GhostProb
                cutName = 'normBsPID_lnf_GP_'


        #Require JpsiDiMuon triggers
        if opts.get('JpsiTrig', False):
                Bs_Jpsi_trig = cs.Bs_Jpsi_L0 + cs.Bs_Jpsi_Hlt1 + cs.Bs_Jpsi_Hlt2
                cut +=	Bs_Jpsi_trig
                cutName += '_JpsiTrig_'


        #Add GhostProb cut on muons
        if opts.get('MuMuGhostProbCut',0):
                cut +=	cs.MuMu_GhostProb
                cutName += '_GPmumu'

       #Do a TIS fit
        if opts.get('trigLev', 'TRIG') is 'TIS':
                cut += cs.Bs_cut_TIS
                print '  TIS cut:', cut

        #Do a TIS fit
        if opts.get('trigLev', 'TRIG') is 'TOS':
                cut += cs.Bs_cut_TOS
                print '  TOS cut:', cut

         #Do a TISTOS fit
        if opts.get('trigLev', 'TRIG') is 'TISTOS':
                cut += cs.Bs_cut_TIS +  cs.Bs_cut_TOS
                print '  TISTOS cut:', cut

        print ' o) Perform mass fits using an constrained mass...'
        massVar = 'B_s0_JCMass'
        fitBu2JpsiKplus(Bs_data,massVar,cutName+'_'+str(opts.get('trigLev','TRIG')),cut)

