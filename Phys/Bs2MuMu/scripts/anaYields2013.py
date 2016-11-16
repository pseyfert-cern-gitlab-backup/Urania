from ROOT import *
gROOT.SetBatch(True)

import cutStrings as cs
from readData import readData
#from MLLfit import fitBu2JpsiKplus
#from MLLfit import fitBs2JpsiPhi

from MLLfit_nicePlot import fitBu2JpsiKplus
from MLLfit_nicePlot import fitBs2JpsiPhi


#In terminal
# python
# from anaMassReso2013 import *
#anaYields('2011_new','Bu',0,{'directory':'Bu2JpsiKplus_2011_1018pb/','noCut':True})

def anaYields(what, channel = 'Bu', tistos = False, opts = {}): #tistos=True fits the TIS TOS and TISTOS yields for the samples
        #opts['configure']: Add constraints to the fit or not

# The idea is to to get all the TRIG yields, save them in files
# Then get all the TIS TOS and TISTOS yields for the samples where
# we need the trigger efficeinacy from.

# Evaluate the trigger efficiency later when plotting and reading the
# yields from the files (plotYields2.py)


        files = []
        # ----------------------------- #
        if what is '2011_new':
            files = ['2011_S20r1_July_SEL']
            #files = ['2011_S20r1_July']

        if what is '2011and2012':
                files = ['2011and12_SEL']
        if what is 'MC':
                files = ['MC12_Sm0']
        if what is 'sub':
                files = ['2012_Strip20_Sub']
        # Old 11+12
        if what is 'old':
                files = ['2011_Strip17','2012_Strip19abc']
        if what is '2012_S19abc':
                files = ['2012_Strip19abc']
        if what is '2012_S20':
                files = ['2012_Strip20']
        if what is '2011_S17':
                files = ['2011_Strip17']
        if what is '2011_S20r1':
                files = ['2011_Strip20r1']
        if what is '2011_S20r1_excl5': #excluding runs 130560, 132228, 132275, 132280, 132282
                files = ['2011_Strip20r1_excl5']
                print 'Test'
        # New 11+12
        if what is 'new':
                files = ['2011_Strip20r1','2012_Strip20']
                #files = ['2012_Strip20']

        # ----------------------------- #
        # New 2011
        if what is '2011_subsamples':
                #files = [ '2011_Strip20r1_A','2011_Strip20r1_B','2011_Strip20r1_C','2011_Strip20r1_D' ]
                files = [ '2011_Strip20r1_D' ]

        if what is '2011_all_files':
                # Reprocessed 2011 on old 2011 - all the individual files
                files = [
                        '2011_Strip20r1_a',
                        '2011_Strip20r1_b','2011_Strip20r1_c','2011_Strip20r1_d','2011_Strip20r1_e','2011_Strip20r1_f',
                        '2011_Strip20r1_g', '2011_Strip20r1_h', '2011_Strip20r1_i', '2011_Strip20r1_j', '2011_Strip20r1_k','2011_Strip20r1_l']

        if what is '2011_test':
            files = ['2011_Strip20r1_d'] #small testing sample

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
                        if channel is 'Bu':
                                tag = ''
                                if opts.get('useL0Hlt1',0):
                                    tag = '_L0Hlt1'
                                    print '  Fitting for L0Hlt1 level!'
                                #getYield_Bu(f,opts) #Get the TRIG yield
                                getYield_Bu(f,{'trigLev':'TIS'+str(tag)})
                                getYield_Bu(f,{'trigLev':'TOS'+str(tag)})
                                getYield_Bu(f,{'trigLev':'TISTOS'+str(tag)})
                        else:
                                #getYield_Bs(f,opts) #Get the TRIG yield
                                # Fix the CB mean from TRIG for the rest, see MLLfit
                                getYield_Bs(f,{'trigLev':'TIS'})
                                getYield_Bs(f,{'trigLev':'TOS'})
                                getYield_Bs(f,{'trigLev':'TISTOS'})
        else:
                for f in files:
                        if channel is 'Bu':
                                getYield_Bu(f,opts) #Get the TRIG yield:w
                        else:
                                getYield_Bs(f,opts)


def getYield_Bu(nTupleName = 'MC12_Sm0', opts =  {}):
        """ Function that combines steps for analyzing the mass resolution for the control channels """
        print ' o) Read in a dataset:'
        Bu_data = readData(nTupleName, {'channel':'Bu','applyCut':True})

        print ' o) Define the cut...'
        trigLev = opts.get('trigLev','TRIG')
        print '     trigger level:', trigLev

        cut = Bu_data.get('cut')+ '&&' + cs.minimalNormBu_lnf
        cutName = 'minimalNormBu_lnf'

        # NO CUT FOR _SEL.root datasets in CutDataset/
        if opts.get('noCut', False):
                cut = ''

        # Add PID cut for Kaon
        if opts.get('PIDK', False):
                cut +=	cs.Bu_PID
                cutName += '_PIDK'

        # Add GhostProb cut on all the tracks
        if opts.get('GhostProbCut',0):
                cut +=	cs.Bu_GhostProb
                cutName += '_GPmumuK'

        # Add GhostProb cut on muons
        if opts.get('MuMuGhostProbCut',0):
                cut +=	cs.MuMu_GhostProb
                cutName += '_GPmumu'

        # Require JpsiDiMuon triggers
        if opts.get('JpsiTrig', False):
                Bu_Jpsi_trig = cs.Bu_Jpsi_L0 + cs.Bu_Jpsi_Hlt1 + cs.Bu_Jpsi_Hlt2
                cut +=	Bu_Jpsi_trig
                cutName += '_JpsiTrig_'

        #Do a TIS fit
        if trigLev is  'TIS':
                cut += cs.Bu_cut_TIS
                print '  TIS cut:', cut

        #Do a TIS fit
        if trigLev is 'TOS':
                cut += cs.Bu_cut_TOS
                print '  TOS cut:', cut

        #Do a TISTOS fit
        if trigLev is 'TISTOS':
                cut += cs.Bu_cut_TIS +  cs.Bu_cut_TOS
                print '  TISTOS cut:', cut

        # L0 Hlt1
        # Do a TIS fit
        if 'TIS_L0Hlt1' in trigLev:
                cut += cs.Bu_cut_TIS_L0Hlt1
                print '  L0Hlt1 TIS cut:', cut

        # Do a TIS fit
        if 'TOS_L0Hlt1' in trigLev:
                cut += cs.Bu_cut_TOS_L0Hlt1
                print '  L0Hlt1  TOS cut:', cut

        # Do a TISTOS fit
        if 'TISTOS_L0Hlt1' in trigLev:
                cut += cs.Bu_cut_TIS_L0Hlt1 +  cs.Bu_cut_TOS_L0Hlt1
                print '  L0Hlt1 TISTOS cut:', cut

        print ' o) Perform mass fits using an constrained mass...'
        massVar = 'Bplus_JCMass'
        fitBu2JpsiKplus(Bu_data,massVar,cutName+'_'+str(opts.get('trigLev','TRIG')),cut,opts.get('setLog',False), opts.get('directory',0), opts.get('param',False))


def getYield_Bs(nTupleName = 'MC12_Sm0', opts =  {}):
        """ Function that combines steps for analyzing the mass resolution for the control channels """

        print ' o) Read in a dataset:'
        Bs_data = readData(nTupleName, {'channel':'Bs'})

        print ' o) Define the cut...'
        #cut = cs.normBs_lnf
        cut = Bs_data.get('cut')+ '&&' + cs.normBs_lnf
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
        fitBs2JpsiPhi(Bs_data,massVar,cutName+'_'+str(opts.get('trigLev','TRIG')),cut,  opts.get('setLog',True), opts.get('directory',0))


