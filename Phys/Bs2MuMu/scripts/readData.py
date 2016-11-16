from ROOT import *
gROOT.SetBatch(True)
import os

# valAndErr is a container for the value and error. It also provides
#simple error propagation operation (multiplication and division)
from valAndErr import *

def readData(nTupleName, opts={}):
	#Read in data files
	#Combine 2012 data

    # LUMINOCITY UNCERTAINTY
    lumiUnc = 0.05 # The luminosity uncertainty in percentage from the value
    #When comparing yields we do not care about absolute scale and then the error is smaller :)
    #lumiUnc = 0.005 # The luminosity uncertainty in percentage from the value

    #THE CHANNELS IN THE FILES
    t_name = 'B2JpsiKTuple/DecayTree'
    if opts.get('channel','Bu')=='Bs': t_name = 'B2JpsiPhiTuple/DecayTree'
    if opts.get('channel','Bu')=='Bhh': t_name = 'B2HHTuple/DecayTree'
    if opts.get('channel','Bu')=='Bmumu': t_name = 'B2MuMuTuple/DecayTree'
    if opts.get('channel','Bu')=='Bd': t_name = 'B2JpsiKst/DecayTree'

    #FATIMAS NTUPLES FROM:
    #https://twiki.cern.ch/twiki/bin/viewauth/LHCbPhysics/Bs2MuMuNtuples


    #---------------------------------------------------------------#
    # The unblinded 2011 and 2012
    #---------------------------------------------------------------#
    if nTupleName=='UB_2013':
        print '    o) Importing: ', nTupleName
        lumi_MC = 2.12 + 9.12 + 101 + 112 + 59 + 112 + 124 + 124 + 124 + 133 + 122+ 119+ 153 + 106 + 126 + 115 + 115 + 116 + 93 + 63 + 134 + 139 + 146 + 80 + 85 + 123 + 135 + 141 + 35
	dir = '/castor/cern.ch/user/r/rvazquez/UB20'
	files = ['DiMuon_Strip20_140213_a_2.12pb.root'
		,'DiMuon_Strip20_140213_b_9.12pb.root'
		,'DiMuon_Strip20_170113_a_101pb.root'
		,'DiMuon_Strip20_170113_b_112pb.root'
		,'DiMuon_Strip20_170113_c_059pb.root'
		,'DiMuon_Strip20_170113_d_112pb.root'
		,'DiMuon_Strip20_170113_e_124pb.root'
		,'DiMuon_Strip20_170113_f_124pb.root'
		,'DiMuon_Strip20_170113_g_124pb.root'
		,'DiMuon_Strip20_170113_h_133pb.root'
		,'DiMuon_Strip20_170113_i_122pb.root'
		,'DiMuon_Strip20_170113_j_119pb.root'
		,'DiMuon_Strip20_170113_k_153pb.root'
		,'DiMuon_Strip20_241112_a_106pb.root'
		,'DiMuon_Strip20_241112_b_126pb.root'
		,'DiMuon_Strip20_241112_c_115pb.root'
		,'DiMuon_Strip20_241112_d_115pb.root'
		,'DiMuon_Strip20_241112_e_116pb.root'
		,'DiMuon_Strip20_241112_f_093pb.root'
		,'DiMuon_Strip20_241112_g_063pb.root'
		,'DiMuon_Strip20r1_Down_134pb.root'
		,'DiMuon_Strip20r1_Down_139pb.root'
		,'DiMuon_Strip20r1_Down_146pb.root'
		,'DiMuon_Strip20r1_Down_80pb.root'
		,'DiMuon_Strip20r1_Down_85pb.root'
		,'DiMuon_Strip20r1_Up_123pb.root'
		,'DiMuon_Strip20r1_Up_135pb.root'
		,'DiMuon_Strip20r1_Up_141pb.root'
		,'DiMuon_Strip20r1_Up_35pb.root'
		]

        tree= TChain(t_name) #Chain can be treated as a TTree object
       	for f in files:
		tree.Add(dir+'/'+f)

        lumi = valAndErr(lumi_MC, lumiUnc*lumi_MC)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    #---------------------------------------------------------------#
    # The Signal MC:
    #---------------------------------------------------------------#
    if nTupleName=='MC2012_BsMuMu':
        print '    o) Importing: ', nTupleName
        lumi_MC = 100 #random lumi for MC
        dir = '/castor/cern.ch/user/f/fdettori/bsmumu/BsMuMu/'

        tree_MC= TChain(t_name) #Chain can be treated as a TTree object
        f_down = dir + 'MC2012_BsMuMu_down_1M_Strip_match.root'
        f_up= dir + 'MC2012_BsMuMu_up_1M_Strip_match.root'
        tree_MC.Add(f_down)
        tree_MC.Add(f_up)

        tree = tree_MC
        lumi = valAndErr(lumi_MC, lumiUnc*lumi_MC)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

	#---------------------------------------------------------------#
    # Reprocessed 2011 data and 2012 combined, SELECTED
    #---------------------------------------------------------------#
    if nTupleName=='2011and12_SEL':
        print '    o) Importing combined reprocessed data WITH SELECTION APPLIED: ', nTupleName
        print '    o) 2011 S20r1 and  2012', nTupleName, '1017pb-1(MagDown)  \
        + 1013pb-1(MagUp) pb-1 dataset '
        tree = TChain('DecayTree') #Chain can be treated as a TTree object
        path = 'CutDatasets/2011and12_Strip20_SEL.root'
        path = 'CutDatasets/2011_S20r1_July_SEL.root'
        tree.Add(path)
        path = 'CutDatasets/2012_Strip20_SEL.root'
        tree.Add(path)

        #lumi_11 = 132 + 120 + 164 + 41.5 + 54.7 + 64.7 + 70.7 + 67.3 + 74.7 + 73.7 + 72.4 + 35.0 # 970.7pb
        lumi_11 = 134+139+146+80+85+123+135+141+35 # 1018pb
        lumi_12 =   106 + 126 + 115 + 115 + 116 + 93 + 63  \
        + 101 + 112 + 59 + 112 + 124 + 124 + 124  \
        + 133 + 122 + 119 + 153 + 2.12 + 9.12
        lumi_repro = lumi_11 + lumi_12

        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'



	#---------------------------------------------------------------#
    # Reprocessed 2011 data and 2012 combined
    #---------------------------------------------------------------#
    if nTupleName=='2011and12_Strip20':
        print '    o) Importing combined reprocessed data: ', nTupleName
        print '    o) 2011 S20r1 and  2012', nTupleName, '1017pb-1(MagDown)  \
        + 1013pb-1(MagUp) pb-1 dataset '

        lumi_11 = 132 + 120 + 164 + 41.5 + 54.7 + 64.7 + 70.7 + 67.3 + 74.7 + 73.7 + 72.4 + 35.0 # 970.7pb
        lumi_12 =   106 + 126 + 115 + 115 + 116 + 93 + 63  \
        + 101 + 112 + 59 + 112 + 124 + 124 + 124  \
        + 133 + 122 + 119 + 153 + 2.12 + 9.12
        lumi_repro = lumi_11 + lumi_12

        #2011 data
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree = TChain(t_name) #Chain can be treated as a TTree object
        #f_repro = dir + 'DiMuon_Strip20r1_280113_71pb__blind_280113.root' #Do not Include, this is validation sample!
        #tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_a_132pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_b_120pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_c_164pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_d_41.5pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_e_54.7pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_f_64.7pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_g_70.7pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_h_67.3pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_i_74.7pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_j_73.7pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_k_72.4pb__blind_060313.root'
        tree.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_l_35.0pb__blind_060313.root'
        tree.Add(f_repro)


        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        # 2012 MagnetDown:
        prefix = 'DiMuon_Strip20_241112_'
        f_1a = dir + prefix + 'a_106pb__blind_031212.root'
        f_1b = dir + prefix + 'b_126pb__blind_031212.root'
        f_1c = dir + prefix + 'c_115pb__blind_031212.root'
        f_1d = dir + prefix + 'd_115pb__blind_031212.root'
        f_1e = dir + prefix + 'e_116pb__blind_031212.root'
        f_1f = dir + prefix + 'f_093pb__blind_031212.root'
        f_1g = dir + prefix + 'g_063pb__blind_031212.root'

        prefix = 'DiMuon_Strip20_170113_'
        f_2a = dir + prefix + 'a_101pb_blind__190113.root'
        f_2b = dir + prefix + 'b_112pb_blind__190113.root'
        f_2c = dir + prefix + 'c_059pb_blind__190113.root'

        prefix = 'DiMuon_Strip20_140213_'
        f_3a = dir + prefix + 'a_2.12pb__blind_140213.root' #MagDown
        f_3b = dir + prefix + 'b_9.12pb__blind_140213.root' #MagUp

        # 2012 MagnetUp:
        prefix = 'DiMuon_Strip20_170113_'
        f_2d = dir + prefix + 'd_112pb__blind_190113.root'
        f_2e = dir + prefix + 'e_124pb__blind_190113.root'
        f_2f = dir + prefix + 'f_124pb__blind_190113.root'
        f_2g = dir + prefix + 'g_124pb__blind_190113.root'
        f_2h = dir + prefix + 'h_133pb__blind_190113.root'
        f_2i = dir + prefix + 'i_122pb__blind_190113.root'
        f_2j = dir + prefix + 'j_119pb__blind_190113.root'
        f_2k = dir + prefix + 'k_153pb__blind_190113.root'

        tree.Add(f_1a)
        tree.Add(f_1b)
        tree.Add(f_1c)
        tree.Add(f_1d)
        tree.Add(f_1e)
        tree.Add(f_1f)
        tree.Add(f_1g)

        tree.Add(f_2a)
        tree.Add(f_2b)
        tree.Add(f_2c)
        tree.Add(f_2d)
        tree.Add(f_2e)
        tree.Add(f_2f)
        tree.Add(f_2g)
        tree.Add(f_2h)
        tree.Add(f_2i)
        tree.Add(f_2j)
        tree.Add(f_2k)

        tree.Add(f_3a)
        tree.Add(f_3b)

        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    #---------------------------------------------------------------#
    # 2011 Strip 20 r1
    #---------------------------------------------------------------#
    if nTupleName is '2011_S20r1_July':
        print '    o) Importing ', nTupleName
        lumi_11 = 134+139+146+80+85+123+135+141+35 # 1018pb

        dir = '/castor/cern.ch/user/r/rvazquez/BsMuMu/Stripping20r1/'
        files = [
            'DiMuon_Strip20r1_Down_134pb__blind_140613.root',
            'DiMuon_Strip20r1_Down_139pb__blind_140613.root',
            'DiMuon_Strip20r1_Down_146pb__blind_140613.root',
            'DiMuon_Strip20r1_Down_80pb__blind_140613.root',
            'DiMuon_Strip20r1_Down_85pb__blind_140613.root',
            'DiMuon_Strip20r1_Up_123pb__blind_140613.root',
            'DiMuon_Strip20r1_Up_135pb__blind_140613.root',
            'DiMuon_Strip20r1_Up_141pb__blind_140613.root',
            'DiMuon_Strip20r1_Up_35pb__blind_140613.root']

        tree= TChain(t_name)
        for f in files:
            tree.Add(dir+f)

        lumi = valAndErr(lumi_11, lumiUnc*lumi_11)  #Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    #---------------------------------------------------------------#
    # 2011 Strip 20 r1 SELECTED (fiducial cut)
    #---------------------------------------------------------------#
    if nTupleName is '2011_S20r1_July_SEL':
        print '    o) Importing ', nTupleName
        lumi_11 = 134+139+146+80+85+123+135+141+35 # 1018pb


        f = 'CutDatasets/2011_S20r1_July_SEL.root'
        tree = TChain('DecayTree') #Chain can be treated as a TTree object
        tree.Add(f)

        lumi = valAndErr(lumi_11, lumiUnc*lumi_11)  #Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    #---------------------------------------------------------------#
    # Reprocessed 2011 data
    #---------------------------------------------------------------#
    if nTupleName=='2011_Strip20r1' or nTupleName is '2011_Strip20r1_excl5':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        #lumi_repro = 71 + 132 + 120 + 164 + 41.5 + 54.7 + 64.7 + 70.7 + 67.3 + 74.7 + 73.7 + 72.4 + 35.0 # 1041.7pb #WRONG!
        lumi_repro = 132 + 120 + 164 + 41.5 + 54.7 + 64.7 + 70.7 + 67.3 + 74.7 + 73.7 + 72.4 + 35.0 # 970.7pb
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object

        if nTupleName is '2011_Strip20r1_excl5':
            lumi_repro = 132 + 120 + 164 + 41.5 + 54.7 + 64.7 + 70.7 + 67.3 + 74.7 + 73.7 + 72.4 + 35.0 - 15 # 970.7pb-15
            #Cut away bad runs 130560, 132228, 132275, 132280, 132282
            #cut = '!(runNumber==130560||runNumber==132228||runNumber==132275||runNumber==132280||runNumber==132282)'
            cut = '(runNumber!=130560&&runNumber!=132228&&runNumber!=132275&&runNumber!=132280&&runNumber!=132282)'
            opts['cut'] = cut + opts.get('cut','')


        #f_repro = dir + 'DiMuon_Strip20r1_280113_71pb__blind_280113.root' #Do not Include, this is validation sample!
        #tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_a_132pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_b_120pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_c_164pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_d_41.5pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_e_54.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_f_64.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_g_70.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_h_67.3pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_i_74.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_j_73.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_k_72.4pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_l_35.0pb__blind_060313.root'
        tree_repro.Add(f_repro)

        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    # Four subgroups of files:

    if nTupleName=='2011_Strip20r1_A':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        #lumi_repro = 71+132+41.5
        lumi_repro = 132+41.5
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        #f_repro = dir + 'DiMuon_Strip20r1_280113_71pb__blind_280113.root' #validation sample, do not include
        #tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_a_132pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_d_41.5pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_B':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 120+70.7+54.7
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_b_120pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_g_70.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_e_54.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_C':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 164+64.7+67.3
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_c_164pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_f_64.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_h_67.3pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_D':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 74.7+73.7+72.4+35.0
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_i_74.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_j_73.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_k_72.4pb__blind_060313.root'
        tree_repro.Add(f_repro)
        f_repro = dir + 'DiMuon_Strip20r1_040313_l_35.0pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    #Individual files:

    if nTupleName=='2011_Strip20r1_vali':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 71
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_280113_71pb__blind_280113.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2011_Strip20r1_a':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 132
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_a_132pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_b':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 120
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_b_120pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_c':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 164
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_c_164pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_d':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 41.5
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_d_41.5pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_e':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 54.7
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_e_54.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_f':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 64.7
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_f_64.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_g':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 70.7
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_g_70.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_h':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 67.3
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_h_67.3pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_i':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 74.7
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_i_74.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2011_Strip20r1_j':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 73.7
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_j_73.7pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_k':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 72.4
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_k_72.4pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip20r1_l':
        #2011 data
        print '    o) Importing reprocessed: ', nTupleName
        lumi_repro = 35.0
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        tree_repro = TChain(t_name) #Chain can be treated as a TTree object
        f_repro = dir + 'DiMuon_Strip20r1_040313_l_35.0pb__blind_060313.root'
        tree_repro.Add(f_repro)
        tree = tree_repro
        lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    #---------------------------------------------------------------#
    # Reprocessed 2012 data
    #---------------------------------------------------------------#
    if nTupleName=='2012_Strip20' or nTupleName=='2012_Strip20_BadITRuns' or nTupleName=='2012_Strip20_GoodITRuns' or nTupleName=='2012_Strip20_Ipart' or nTupleName=='2012_Strip20_IIpart':
        #2012 data reprocessed
        print '    o) Importing reprocessed 2012', nTupleName, '1017pb-1(MagDown)  \
        + 1013pb-1(MagUp) pb-1 dataset '
        lumi_f =   106 + 126 + 115 + 115 + 116 + 93 + 63  \
        + 101 + 112 + 59 + 112 + 124 + 124 + 124  \
        + 133 + 122 + 119 + 153 + 2.12 + 9.12

        if nTupleName=='2012_Strip20_BadITRuns':
            #Select bad runs
            cut = '(runNumber>111955&&runNumber<112541)'
            cut += '||(runNumber>112542&&runNumber<113013)'
            #opts['cut'] = cut + opts.get('cut','1')
            opts['cut'] = cut + opts.get('cut','')
            lumi_f = 19.59+18.74

        if nTupleName=='2012_Strip20_GoodITRuns':
            #Select good runs
            cut = '!(runNumber>111955&&runNumber<112541)'
            cut += '&&!(runNumber>112542&&runNumber<113013)'
            #opts['cut'] = cut + opts.get('cut','1')
            opts['cut'] = cut + opts.get('cut','')
            lumi_f = lumi_f + (19.59+18.74)

        if nTupleName=='2012_Strip20_Ipart':
            #Select same runs present in Strip19abc
            cut = '(runNumber>111761&&runNumber<128109)'
            opts['cut'] = cut + opts.get('cut','')
            lumi_f = 1109

        if nTupleName=='2012_Strip20_IIpart':
            #Select same runs present in Strip19abc
            cut = '(runNumber>128108)'
            opts['cut'] = cut + opts.get('cut','')
            lumi_f = 919

        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'

        #MagnetDown:
        prefix = 'DiMuon_Strip20_241112_'
        f_1a = dir + prefix + 'a_106pb__blind_031212.root'
        f_1b = dir + prefix + 'b_126pb__blind_031212.root'
        f_1c = dir + prefix + 'c_115pb__blind_031212.root'
        f_1d = dir + prefix + 'd_115pb__blind_031212.root'
        f_1e = dir + prefix + 'e_116pb__blind_031212.root'
        f_1f = dir + prefix + 'f_093pb__blind_031212.root'
        f_1g = dir + prefix + 'g_063pb__blind_031212.root'

        prefix = 'DiMuon_Strip20_170113_'
        f_2a = dir + prefix + 'a_101pb_blind__190113.root'
        f_2b = dir + prefix + 'b_112pb_blind__190113.root'
        f_2c = dir + prefix + 'c_059pb_blind__190113.root'

        prefix = 'DiMuon_Strip20_140213_'
        f_3a = dir + prefix + 'a_2.12pb__blind_140213.root' #MagDown
        f_3b = dir + prefix + 'b_9.12pb__blind_140213.root' #MagUp

        #MagnetUp:
        prefix = 'DiMuon_Strip20_170113_'
        f_2d = dir + prefix + 'd_112pb__blind_190113.root'
        f_2e = dir + prefix + 'e_124pb__blind_190113.root'
        f_2f = dir + prefix + 'f_124pb__blind_190113.root'
        f_2g = dir + prefix + 'g_124pb__blind_190113.root'
        f_2h = dir + prefix + 'h_133pb__blind_190113.root'
        f_2i = dir + prefix + 'i_122pb__blind_190113.root'
        f_2j = dir + prefix + 'j_119pb__blind_190113.root'
        f_2k = dir + prefix + 'k_153pb__blind_190113.root'

        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_1a)
        tree.Add(f_1b)
        tree.Add(f_1c)
        tree.Add(f_1d)
        tree.Add(f_1e)
        tree.Add(f_1f)
        tree.Add(f_1g)

        tree.Add(f_2a)
        tree.Add(f_2b)
        tree.Add(f_2c)
        tree.Add(f_2d)
        tree.Add(f_2e)
        tree.Add(f_2f)
        tree.Add(f_2g)
        tree.Add(f_2h)
        tree.Add(f_2i)
        tree.Add(f_2j)
        tree.Add(f_2k)

        tree.Add(f_3a)
        tree.Add(f_3b)

        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    #Subsample for the mass model study (equal from MagUp and MagDown)
    if nTupleName=='2012_Strip20_Sub':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f =   124+126
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'b_126pb__blind_031212.root'
        tree.Add(f)
        #MagnetUp:
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'e_124pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    #Subsamples for 2012 yield study
    if nTupleName=='2012_Strip20_MagDown_A':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f =   106+126
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'a_106pb__blind_031212.root'
        tree.Add(f)
        f = dir + prefix + 'b_126pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_B':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f =   115+115
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'c_115pb__blind_031212.root'
        tree.Add(f)
        f = dir + prefix + 'd_115pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_C':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f =   116+93+63
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'e_116pb__blind_031212.root'
        tree.Add(f)
        f = dir + prefix + 'f_093pb__blind_031212.root'
        tree.Add(f)
        f = dir + prefix + 'g_063pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_D':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f =   101+112+59+2.12
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'a_101pb_blind__190113.root'
        tree.Add(f)
        f = dir + prefix + 'b_112pb_blind__190113.root'
        tree.Add(f)
        f = dir + prefix + 'c_059pb_blind__190113.root'
        tree.Add(f)

        prefix = 'DiMuon_Strip20_140213_'
        f = dir + prefix + 'a_2.12pb__blind_140213.root' #MagDown
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagUp_A':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f =   9.12+112+124
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_140213_'
        f = dir + prefix + 'b_9.12pb__blind_140213.root' #MagUp
        tree.Add(f)

        #MagnetUp:
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'd_112pb__blind_190113.root'
        tree.Add(f)
        f = dir + prefix + 'e_124pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagUp_B':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 124 + 124
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        #MagnetUp:
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'f_124pb__blind_190113.root'
        tree.Add(f)
        f = dir + prefix + 'g_124pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip20_MagUp_C':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 133+ 122
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        #MagnetUp:
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'h_133pb__blind_190113.root'
        tree.Add(f)
        f = dir + prefix + 'i_122pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip20_MagUp_D':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 119+153
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        #MagnetUp:
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'j_119pb__blind_190113.root'
        tree.Add(f)
        f = dir + prefix + 'k_153pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    #Individual files for 2012

    if nTupleName=='2012_Strip20_MagDown_a':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f =   106
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'a_106pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_b':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 126
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'b_126pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_c':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 115
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'c_115pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_d':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 115
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'd_115pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_e':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 116
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'e_116pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_f':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 93
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'f_093pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_g':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 63
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_241112_'
        f = dir + prefix + 'g_063pb__blind_031212.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_h':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 101
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'a_101pb_blind__190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_i':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 112
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'b_112pb_blind__190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip20_MagDown_j':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 59
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'c_059pb_blind__190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagDown_k':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 9.12
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_140213_'
        f = dir + prefix + 'b_9.12pb__blind_140213.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    #Mag UP:

    if nTupleName=='2012_Strip20_MagUp_a':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 112
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'd_112pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagUp_b':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 124
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'e_124pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagUp_c':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 124
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'f_124pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagUp_d':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 124
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'g_124pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip20_MagUp_e':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 133
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'h_133pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagUp_f':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 122
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'i_122pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagUp_g':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 119
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'j_119pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip20_MagUp_h':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName
        lumi_f = 153
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_170113_'
        f = dir + prefix + 'k_153pb__blind_190113.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip20_MagUp_i':
        #2012 data reprocessed
        print '    o) Importing reprocessed: ', nTupleName

        #Just for testing another code faster!!! Remove after..
        cut = '(runNumber>1)&&'
        #opts['cut'] = cut + opts.get('cut','1')
        opts['cut'] = cut + opts.get('cut','')

        lumi_f = 2.12
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
        #MagnetDown:
        tree = TChain(t_name) #Chain can be treated as a TTree object
        prefix = 'DiMuon_Strip20_140213_'
        f = dir + prefix + 'a_2.12pb__blind_140213.root'
        tree.Add(f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    #---------------------------------------------------------------#
    # MC samaples
    #---------------------------------------------------------------#

    if nTupleName=='MC12_S17':
        print '    o) Importing MC Stp17 filtered inclusive bkg'
        dir = '/castor/cern.ch/user/f/fsoomro/B2MuMu_2012MonteCarlo/'

        f_MC_a = dir + 'MC12_10012009_MagDn_Job396.root'
        f_MC_b = dir + 'MC12_10012009_MagDn_Job401.root'
        f_MC_c = dir + 'MC12_10012009_MagUp_Job395.root'
        f_MC_d = dir + 'MC12_10012009_MagUp_Job400.root'

        tree_MC = TChain(t_name) #Chain can be treated as a TTree object
        tree_MC.Add(f_MC_a)
        tree_MC.Add(f_MC_b)
        tree_MC.Add(f_MC_c)
        tree_MC.Add(f_MC_d)

        lumi_MC = 100.# a random value for MC
        tree = tree_MC
        lumi = valAndErr(lumi_MC, lumiUnc*lumi_MC)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='MC12_S20':
        print '    o) Importing MC Stp20 filtered inclusive bkg'
        dir = '/castor/cern.ch/user/f/fsoomro/B2MuMu_2012MonteCarlo/'
        f_MC_a = dir + 'MC12_R14S20_10012009_MagDn_Job417.root'
        f_MC_b = dir + 'MC12_R14S20_10012009_MagUp_Job418.root'
        tree_MC = TChain(t_name) #Chain can be treated as a TTree object
        tree_MC.Add(f_MC_a)
        tree_MC.Add(f_MC_b)
        lumi_MC = 100.# a random value for MC
        tree = tree_MC
        lumi = valAndErr(lumi_MC, lumiUnc*lumi_MC)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='MC10_Sm1':
        #2011 data
        print '    o) Importing MC10 Sm1 Stp17'
        dir = '/castor/cern.ch/user/f/fdettori/bsmumu/control/'
        f_MC10 = dir + 'MC10_BuJpsiK_Sm1_Stp17_FrascaTuple_0501.root'
        tree_MC10 = TChain(t_name) #Chain can be treated as a TTree object
        tree_MC10.Add(f_MC10)
        lumi_MC10 = 100.
        tree = tree_MC10
        lumi = valAndErr(lumi_MC10, lumiUnc*lumi_MC10)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='MC12_Sm0':
        #2011 data
        print '    o) Importing MC12 Sm0'
        dir  = '/castor/cern.ch/user/f/fdettori/bsmumu/control/'
        f_MC12 = dir + 'MC2012_BJpsiK_down_500k_Strip.root'
        f_MC12 = dir + 'MC2012_BJpsiK_down_127k_Strip_match.root'

        tree_MC12 = TChain(t_name) #Chain can be treated as a TTree object
        #tree_MC12.Add(f_MC12)
        tree_MC12.Add(f_MC12)
        tree_MC12.Add(f_MC12)
        lumi_MC12 = 100.
        tree = tree_MC12
        lumi = valAndErr(lumi_MC12, lumiUnc*lumi_MC12)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='MC2012_BuJpsiKplus':
        #2012
        print '    o) Importing 2012 MC BuJpsiKplus'
        dir  = '/castor/cern.ch/user/f/fdettori/bsmumu/control/'
        f_MC12_up = '/castor/cern.ch/user/f/fdettori/bsmumu/control/MC2012_BJpsiK_down_500k_Strip_match.root'
        f_MC12_down = '/castor/cern.ch/user/f/fdettori/bsmumu/control/MC2012_BJpsiK_down_500k_Strip_match.root'

        tree_MC12 = TChain(t_name) #Chain can be treated as a TTree object
        tree_MC12.Add(f_MC12_up)
        tree_MC12.Add(f_MC12_down)
        lumi_MC12 = 100.
        tree = tree_MC12
        lumi = valAndErr(lumi_MC12, lumiUnc*lumi_MC12)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='MC12_Sm1':
        #2011 data
        print '    o) Importing 2012 MC Sm1'
        dir  = '/castor/cern.ch/user/f/fdettori/bsmumu/control/'
        f_MC12 = dir + 'MC2012_BJpsiK_down_127k_Strip_match_NewSm1.root'

        tree_MC12 = TChain(t_name) #Chain can be treated as a TTree object
        tree_MC12.Add(f_MC12)
        lumi_MC12 = 100.
        tree = tree_MC12
        lumi = valAndErr(lumi_MC12, lumiUnc*lumi_MC12)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='MC12_BsJpsiPhi':
        #2011 data
        print '    o) Importing 2012 MC'
        dir = '/castor/cern.ch/user/f/fdettori/bsmumu/control/'
        f_MC12 = dir + 'MC2012_BsJpsiPhi_down_NewSm1.root'
        t_name = 'B2JpsiPhiTuple/DecayTree'
        tree_MC12 = TChain(t_name) #Chain can be treated as a TTree object
        tree_MC12.Add(f_MC12)
        lumi_MC12 = 100.
        tree = tree_MC12
        lumi = valAndErr(lumi_MC12, lumiUnc*lumi_MC12)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    #---------------------------------------------------------------#
    # 2011 data
    #---------------------------------------------------------------#

    if nTupleName=='2011_Strip17':
        #2011 data
        print '    o) Importing 2011 data'
        f_2011 = '/castor/cern.ch/user/f/farchill/1020pbDecember7BDTSwBDT.root'
        tree_2011 = TChain(t_name) #Chain can be treated as a TTree object
        tree_2011.Add(f_2011)
        lumi_2011 = 1020
        tree = tree_2011
        lumi = valAndErr(lumi_2011, lumiUnc*lumi_2011)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip17_DQgood':
        #2011 data
        print '    o) Importing 2011 data'
        f_2011 = '/castor/cern.ch/user/f/farchill/1020pbDecember7BDTSwBDT.root'
        tree_2011 = TChain(t_name) #Chain can be treated as a TTree object
        tree_2011.Add(f_2011)
        lumi_2011 = 970.7 #Assume the same as in reprocessed 2012 without the bad runs
        tree = tree_2011
        lumi = valAndErr(lumi_2011, lumiUnc*lumi_2011)	#Object contaning value and uncertainty

        #Remove the runs that DQflag20121016 removes in the reprocessed 2011 data R14S20r1 2011
        bad_muon = [87723, 87724, 87725, 87901, 103599, 103609, 103681]
        bad_hlt = [103936, 103937, 103938, 103939, 103954, 103955, 103956, 103957, 103958,
        103959, 103960, 103961, 103962, 103963, 103964, 103965, 103966, 103967,
        103968, 103969, 103971, 103972, 103973, 103974, 103975, 103976, 103977,
        103978, 103979, 103998, 103999, 104000, 104001]
        bad_l0muon = [90071, 90072, 90073, 90074, 90075, 90076, 90077, 90078, 90079, 90080,
        90081, 90082, 90083, 90084, 90085, 90086, 90087, 90088, 90089, 90090,
        90091, 90092, 90093]
        bad_rich = [92217, 93261, 94005, 94006, 94007, 94008, 94171, 94172, 94173]

        bad_runs = bad_muon + bad_hlt + bad_l0muon + bad_rich

        cut = '1'
        for run in bad_runs: cut += '&&(runNumber!='+str(run)+')'

        opts['cut'] = cut + '&&' + opts.get('cut','')

        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip17_DQgood_Jpsimm':
        #2011 data
        print '    o) Importing 2011 data'
        f_2011 = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/JpsimmK_S17_1011pb_Job342.root'
        tree_2011 = TChain(t_name) #Chain can be treated as a TTree object
        tree_2011.Add(f_2011)
        lumi_2011 = 970.7 #Assume the same as in reprocessed 2012 without the bad runs
        tree = tree_2011
        lumi = valAndErr(lumi_2011, lumiUnc*lumi_2011)	#Object contaning value and uncertainty

        #Remove the runs that DQflag20121016 removes in the reprocessed 2011 data R14S20r1 2011
        bad_muon = [87723, 87724, 87725, 87901, 103599, 103609, 103681]
        bad_hlt = [103936, 103937, 103938, 103939, 103954, 103955, 103956, 103957, 103958,
        103959, 103960, 103961, 103962, 103963, 103964, 103965, 103966, 103967,
        103968, 103969, 103971, 103972, 103973, 103974, 103975, 103976, 103977,
        103978, 103979, 103998, 103999, 104000, 104001]
        bad_l0muon = [90071, 90072, 90073, 90074, 90075, 90076, 90077, 90078, 90079, 90080,
        90081, 90082, 90083, 90084, 90085, 90086, 90087, 90088, 90089, 90090,
        90091, 90092, 90093]
        bad_rich = [92217, 93261, 94005, 94006, 94007, 94008, 94171, 94172, 94173]

        bad_runs = bad_muon + bad_hlt + bad_l0muon + bad_rich

        cut = '1'
        for run in bad_runs: cut += '&&(runNumber!='+str(run)+')'

        opts['cut'] = cut + '&&' + opts.get('cut','')

        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2011_Strip17_DQbad':
        #2011 data
        print '    o) Importing 2011 data'
        f_2011 = '/castor/cern.ch/user/f/farchill/1020pbDecember7BDTSwBDT.root'
        tree_2011 = TChain(t_name) #Chain can be treated as a TTree object
        tree_2011.Add(f_2011)
        lumi_2011 = 49.3 #Assume the same as in reprocessed 2012 without the bad runs
        tree = tree_2011
        lumi = valAndErr(lumi_2011, lumiUnc*lumi_2011)	#Object contaning value and uncertainty

        #Remove the runs that DQflag20121016 removes in the reprocessed 2011 data R14S20r1 2011
        bad_muon = [87723, 87724, 87725, 87901, 103599, 103609, 103681]
        bad_hlt = [103936, 103937, 103938, 103939, 103954, 103955, 103956, 103957, 103958,
        103959, 103960, 103961, 103962, 103963, 103964, 103965, 103966, 103967,
        103968, 103969, 103971, 103972, 103973, 103974, 103975, 103976, 103977,
        103978, 103979, 103998, 103999, 104000, 104001]
        bad_l0muon = [90071, 90072, 90073, 90074, 90075, 90076, 90077, 90078, 90079, 90080,
        90081, 90082, 90083, 90084, 90085, 90086, 90087, 90088, 90089, 90090,
        90091, 90092, 90093]
        bad_rich = [92217, 93261, 94005, 94006, 94007, 94008, 94171, 94172, 94173]

        bad_runs = bad_muon + bad_hlt + bad_l0muon + bad_rich

        cut = ')'
        cut = '('
        first = True
        for run in bad_runs:
            if first:
                cut += '(runNumber=='+str(run)+')'
                first = False
            else: cut += '||(runNumber=='+str(run)+')'
            cut += ')'



        opts['cut'] = cut + '&&' + opts.get('cut','')

        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip17_DQbad_Jpsimm':
        #2011 data
        print '    o) Importing 2011 data'
        f_2011 = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/JpsimmK_S17_1011pb_Job342.root'
        tree_2011 = TChain(t_name) #Chain can be treated as a TTree object
        tree_2011.Add(f_2011)
        lumi_2011 = 49.3 #Assume the same as in reprocessed 2012 without the bad runs
        tree = tree_2011
        lumi = valAndErr(lumi_2011, lumiUnc*lumi_2011)	#Object contaning value and uncertainty

        #Remove the runs that DQflag20121016 removes in the reprocessed 2011 data R14S20r1 2011
        bad_muon = [87723, 87724, 87725, 87901, 103599, 103609, 103681]
        bad_hlt = [103936, 103937, 103938, 103939, 103954, 103955, 103956, 103957, 103958,
        103959, 103960, 103961, 103962, 103963, 103964, 103965, 103966, 103967,
        103968, 103969, 103971, 103972, 103973, 103974, 103975, 103976, 103977,
        103978, 103979, 103998, 103999, 104000, 104001]
        bad_l0muon = [90071, 90072, 90073, 90074, 90075, 90076, 90077, 90078, 90079, 90080,
        90081, 90082, 90083, 90084, 90085, 90086, 90087, 90088, 90089, 90090,
        90091, 90092, 90093]
        bad_rich = [92217, 93261, 94005, 94006, 94007, 94008, 94171, 94172, 94173]

        bad_runs = bad_muon + bad_hlt + bad_l0muon + bad_rich

        cut = ')'
        cut = '('
        first = True
        for run in bad_runs:
            if first:
                cut += '(runNumber=='+str(run)+')'
                first = False
            else: cut += '||(runNumber=='+str(run)+')'
            cut += ')'



        opts['cut'] = cut + '&&' + opts.get('cut','')

        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip17_wIso':
        #2011 data
        print '    o) Importing 2011 data'
        #f_2011 = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip17/OneInvFB/1020pbDecember7BDTS.root'
        f_2011 = '/castor/cern.ch/user/f/farchill/1020pbDecember7BDTSwBDT.root'
        tree_2011 = TChain(t_name) #Chain can be treated as a TTree object
        tree_2011.Add(f_2011)
        lumi_2011 = 1020
        tree = tree_2011
        lumi = valAndErr(lumi_2011, lumiUnc*lumi_2011)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2011_Strip17_Jpsimm':
        #2011 data, has the isolation variables but no BsJpsiPhi tuple
        print '    o) Importing JpsimmK_S17_1011pb_Job342.root'
        file = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/JpsimmK_S17_1011pb_Job342.root'
        tree_2011 = TChain(t_name) #Chain can be treated as a TTree object
        tree_2011.Add(file)
        lumi_2011 = 1011
        tree = tree_2011
        lumi = valAndErr(lumi_2011, lumiUnc*lumi_2011)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

        #---------------------------------------------------------------#
        # 2012 data
        #---------------------------------------------------------------#


    if nTupleName=='2012_Strip19abc' or nTupleName=='2012_Strip19abc_BadITRuns' or nTupleName=='2012_Strip19abc_GoodITRuns':
        #2012 data
        print '    o) Importing 2012 data', nTupleName

        #lumi_2012 = 74 + 445 + 145 + 135 -  45 # 45 accounts for the bad runs in Strip19b
        #lumi_2012 = 75 + 444 + 303	# Sept 10
        lumi_2012 = 75 + 444 + 303 + 177 + 110	# Sept 10 and 14
        #lumi_2012 = 75 + 444 + 303 - 74	# Sept 10

        if nTupleName=='2012_Strip19abc_BadITRuns':
            #Select bad runs
            cut = '(runNumber>111955&&runNumber<112541)'
            cut += '||(runNumber>112542&&runNumber<113013)&&'
            #opts['cut'] = cut + opts.get('cut','1')
            opts['cut'] = cut + opts.get('cut','')
            lumi_2012 = 19.59+18.74

        if nTupleName=='2012_Strip19abc_GoodITRuns':
            #Select good runs
            cut = '!(runNumber>111955&&runNumber<112541)'
            cut += '&&!(runNumber>112542&&runNumber<113013)&&'
            #opts['cut'] = cut + opts.get('cut','1')
            opts['cut'] = cut + opts.get('cut','')
            lumi_2012 = lumi_2012-(19.59+18.74)

        tree_2012 = TChain(t_name) #Chain can be treated as a TTree object

        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        #f_1  = dir + 'Strip19_74pb_Blind_11Aug.root'
        #f_2a = dir + 'Strip19a_445pb_Blind_11Aug_a.root'
        #f_2b = dir + 'Strip19a_445pb_Blind_11Aug_b.root'
        #f_2c = dir + 'Strip19a_445pb_Blind_11Aug_c.root'
        #f_3a = dir + 'Strip19b_145pb_Blind_11Aug_a.root'
        #f_3b = dir + 'Strip19b_145pb_Blind_11Aug_b.root'
        #f_3c = dir + 'Strip19b_145pb_Blind_11Aug_c.root'
        #f_3d = dir + 'Strip19b_135pb_Blind_26Aug_d.root'

        f_1a = dir + 'Strip19_75pb_DiMuon_10Sept_a.root'
        f_1b = dir + 'Strip19_75pb_DiMuon_10Sept_b.root'
        f_2a = dir + 'Strip19a_444pb_DiMuon_10Sept_a.root'
        f_2b = dir + 'Strip19a_444pb_DiMuon_10Sept_b.root'
        f_2c = dir + 'Strip19a_444pb_DiMuon_10Sept_c.root'
        f_2d = dir + 'Strip19a_444pb_DiMuon_10Sept_d.root'
        f_2e = dir + 'Strip19a_444pb_DiMuon_10Sept_e.root'
        f_2f = dir + 'Strip19a_444pb_DiMuon_10Sept_f.root'
        f_3a = dir + 'Strip19b_303pb_DiMuon_10Sept_a.root'
        f_3b = dir + 'Strip19b_303pb_DiMuon_10Sept_b.root'
        f_3c = dir + 'Strip19b_303pb_DiMuon_10Sept_c.root'
        f_3d = dir + 'Strip19b_303pb_DiMuon_10Sept_d.root'
        f_3e = dir + 'Strip19b_303pb_DiMuon_10Sept_e.root'
        f_4a = dir + 'Strip19c_177pb_DiMuon_14Sept_a.root'
        f_4b = dir + 'Strip19c_177pb_DiMuon_14Sept_b.root'
        f_4c = dir + 'Strip19c_177pb_DiMuon_14Sept_c.root'
        f_4d = dir + 'Strip19c_177pb_DiMuon_14Sept_d.root'
        f_5a = dir + 'Strip19c_110pb_DiMuon_14Sept_a.root '
        f_5b = dir + 'Strip19c_110pb_DiMuon_14Sept_b.root '

        tree_2012.Add(f_1a)
        tree_2012.Add(f_1b)
        tree_2012.Add(f_2a)
        tree_2012.Add(f_2b)
        tree_2012.Add(f_2c)
        tree_2012.Add(f_2d)
        tree_2012.Add(f_2e)
        tree_2012.Add(f_2f)
        tree_2012.Add(f_3a)
        tree_2012.Add(f_3b)
        tree_2012.Add(f_3c)
        tree_2012.Add(f_3d)
        tree_2012.Add(f_3e)
        tree_2012.Add(f_4a)
        tree_2012.Add(f_4b)
        tree_2012.Add(f_4c)
        tree_2012.Add(f_4d)
        tree_2012.Add(f_5a)
        tree_2012.Add(f_5b)

        tree = tree_2012
        lumi = valAndErr(lumi_2012, lumiUnc*lumi_2012)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported'

    if nTupleName=='2012_Strip19':
        #2012 data
        print '    o) Importing 2012', nTupleName, ' 74 pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        #Blind 1Aug
        #f_1  = dir + 'Strip19_74pb_Blind_11Aug.root'
        #lumi_f = 74

        f_1a = dir + 'Strip19_75pb_DiMuon_10Sept_a.root'
        f_1b = dir + 'Strip19_75pb_DiMuon_10Sept_b.root'
        lumi_f = 38.2 + 36.8

        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_1a)
        tree.Add(f_1b)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19a':
        #2012 data
        print '    o) Importing 2012', nTupleName, '444 pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        #f_2a = dir + 'Strip19a_445pb_Blind_11Aug_a.root'
        #f_2b = dir + 'Strip19a_445pb_Blind_11Aug_b.root'
        #f_2c = dir + 'Strip19a_445pb_Blind_11Aug_c.root'
        #lumi_f = 445

        f_2a = dir + 'Strip19a_444pb_DiMuon_10Sept_a.root'
        f_2b = dir + 'Strip19a_444pb_DiMuon_10Sept_b.root'
        f_2c = dir + 'Strip19a_444pb_DiMuon_10Sept_c.root'
        f_2d = dir + 'Strip19a_444pb_DiMuon_10Sept_d.root'
        f_2e = dir + 'Strip19a_444pb_DiMuon_10Sept_e.root'
        f_2f = dir + 'Strip19a_444pb_DiMuon_10Sept_f.root'
        lumi_f = 100 + 69 + 67.5 + 68 + 72 + 67.5

        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_2a)
        tree.Add(f_2b)
        tree.Add(f_2c)
        tree.Add(f_2d)
        tree.Add(f_2e)
        tree.Add(f_2f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty

        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip19b':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19b 303pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        #f_3a = dir + 'Strip19b_145pb_Blind_11Aug_a.root'
        #f_3b = dir + 'Strip19b_145pb_Blind_11Aug_b.root'
        #f_3c = dir + 'Strip19b_145pb_Blind_11Aug_c.root'
        #f_3d = dir + 'Strip19b_135pb_Blind_26Aug_d.root'
        #lumi_f = 145+135

        f_3a = dir + 'Strip19b_303pb_DiMuon_10Sept_a.root'
        f_3b = dir + 'Strip19b_303pb_DiMuon_10Sept_b.root'
        f_3c = dir + 'Strip19b_303pb_DiMuon_10Sept_c.root'
        f_3d = dir + 'Strip19b_303pb_DiMuon_10Sept_d.root'
        f_3e = dir + 'Strip19b_303pb_DiMuon_10Sept_e.root'
        lumi_f = 69.7 + 63.4 + 74 + 65 + 31.6

        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_3a)
        tree.Add(f_3b)
        tree.Add(f_3c)
        tree.Add(f_3d)
        tree.Add(f_3e)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19c':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19c 286.5pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'

        f_4a = dir + 'Strip19c_177pb_DiMuon_14Sept_a.root'
        f_4b = dir + 'Strip19c_177pb_DiMuon_14Sept_b.root'
        f_4c = dir + 'Strip19c_177pb_DiMuon_14Sept_c.root'
        f_4d = dir + 'Strip19c_177pb_DiMuon_14Sept_d.root'
        f_5a = dir + 'Strip19c_110pb_DiMuon_14Sept_a.root '
        f_5b = dir + 'Strip19c_110pb_DiMuon_14Sept_b.root '
        lumi_f = 40 + 36 + 58.5 + 42 + 65 + 45

        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_4a)
        tree.Add(f_4b)
        tree.Add(f_4c)
        tree.Add(f_4d)
        tree.Add(f_5a)
        tree.Add(f_5b)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19b_BadRuns':
        #2012 data
        cut = '!(runNumber<124272||runNumber>124505)&&'
        #opts['cut'] = cut + opts.get('cut','1')
        opts['cut'] = cut + opts.get('cut','')

        print '    o) Importing 2012', nTupleName, 'Strip 19b (145+135 pb-1) dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_3a = dir + 'Strip19b_145pb_Blind_11Aug_a.root'
        f_3b = dir + 'Strip19b_145pb_Blind_11Aug_b.root'
        f_3c = dir + 'Strip19b_145pb_Blind_11Aug_c.root'
        f_3d = dir + 'Strip19b_135pb_Blind_26Aug_d.root'
        lumi_f = 45 # 45 for the bad runs

        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_3a)
        tree.Add(f_3b)
        tree.Add(f_3c)
        tree.Add(f_3d)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty

        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19b_GoodRuns':
        #2012 data
        cut = '(runNumber<124272||runNumber>124505)&&'
        #opts['cut'] = cut + opts.get('cut','1')
        opts['cut'] = cut + opts.get('cut','')


        print '    o) Importing 2012', nTupleName, 'Strip 19b (145+135 pb-1) dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_3a = dir + 'Strip19b_145pb_Blind_11Aug_a.root'
        f_3b = dir + 'Strip19b_145pb_Blind_11Aug_b.root'
        f_3c = dir + 'Strip19b_145pb_Blind_11Aug_c.root'
        f_3d = dir + 'Strip19b_135pb_Blind_26Aug_d.root'
        lumi_f = 145 + 135 - 45 # 45 for the bad runs

        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_3a)
        tree.Add(f_3b)
        tree.Add(f_3c)
        tree.Add(f_3d)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty

        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


        # ---------------------------------------------------------------- #
        # Files separately
    if nTupleName=='2012_Strip19_a':
        #2012 data
        print '    o) Importing 2012', nTupleName, ' 38.2pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'


        f_1a = dir + 'Strip19_75pb_DiMuon_10Sept_a.root'
        lumi_f = 38.2

        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_1a)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19_b':
        #2012 data
        print '    o) Importing 2012', nTupleName, ' 38.2pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_1b = dir + 'Strip19_75pb_DiMuon_10Sept_b.root'
        lumi_f = 36.8
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_1b)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip19a_a':
        #2012 data
        print '    o) Importing 2012', nTupleName, '100 pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_2a = dir + 'Strip19a_444pb_DiMuon_10Sept_a.root'
        lumi_f = 100
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_2a)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19a_b':
        #2012 data
        print '    o) Importing 2012', nTupleName, '69 pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_2b = dir + 'Strip19a_444pb_DiMuon_10Sept_b.root'
        lumi_f = 69
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_2b)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19a_c':
        #2012 data
        print '    o) Importing 2012', nTupleName, '67.5 pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_2c = dir + 'Strip19a_444pb_DiMuon_10Sept_c.root'
        lumi_f = 67.5
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_2c)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19a_d':
        #2012 data
        print '    o) Importing 2012', nTupleName, '68 pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_2d = dir + 'Strip19a_444pb_DiMuon_10Sept_d.root'
        lumi_f = 68
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_2d)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19a_e':
        #2012 data
        print '    o) Importing 2012', nTupleName, '72 pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_2e = dir + 'Strip19a_444pb_DiMuon_10Sept_e.root'
        lumi_f = 72
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_2e)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19a_f':
        #2012 data
        print '    o) Importing 2012', nTupleName, '67.5 pb-1 dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_2f = dir + 'Strip19a_444pb_DiMuon_10Sept_f.root'
        lumi_f = 67.5
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_2f)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip19b_a':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19b 69.7pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_3a = dir + 'Strip19b_303pb_DiMuon_10Sept_a.root'
        lumi_f = 69.7
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_3a)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip19b_b':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19b 63.4pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_3b = dir + 'Strip19b_303pb_DiMuon_10Sept_b.root'
        lumi_f = 63.4
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_3b)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip19b_c':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19b 74pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_3c = dir + 'Strip19b_303pb_DiMuon_10Sept_c.root'
        lumi_f = 74
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_3c)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip19b_d':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19b 65pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_3d = dir + 'Strip19b_303pb_DiMuon_10Sept_d.root'
        lumi_f = 65
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_3d)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'


    if nTupleName=='2012_Strip19b_e':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19b 31.6pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_3e = dir + 'Strip19b_303pb_DiMuon_10Sept_e.root'
        lumi_f = 31.6
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_3e)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19c_a':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19c 40pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_4a = dir + 'Strip19c_177pb_DiMuon_14Sept_a.root'
        lumi_f = 40
        #lumi_f = 40 + 36 + 58.5 + 42
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_4a)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19c_b':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19c 36pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_4b = dir + 'Strip19c_177pb_DiMuon_14Sept_b.root'
        lumi_f = 36
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_4b)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19c_c':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19c 58.5pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_4c = dir + 'Strip19c_177pb_DiMuon_14Sept_c.root'
        lumi_f = 58.5
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_4c)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19c_d':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19c 42pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_4d = dir + 'Strip19c_177pb_DiMuon_14Sept_d.root'
        lumi_f = 42
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_4d)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19c_e':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19c 65pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_5a = dir + 'Strip19c_110pb_DiMuon_14Sept_a.root '
        lumi_f = 65
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_5a)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'

    if nTupleName=='2012_Strip19c_f':
        #2012 data
        print '    o) Importing 2012', nTupleName, 'Strip 19c 65pb dataset '
        dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip19/'
        f_5b = dir + 'Strip19c_110pb_DiMuon_14Sept_b.root '
        lumi_f = 45
        tree = TChain(t_name) #Chain can be treated as a TTree object
        tree.Add(f_5b)
        lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
        print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'



        # ---------------------------------------------------------------- #
        # Add a specified cut to the dataset
    #if opts.get('cut',0) and opts.get('applyCut',False):

        #Make tree smaller
        #strip = stripTree(tree, opts.get('cut'))
        #tree = strip[0]
        #tree = t_strip.CopyTree(opts.get('cut',''))

        #Clone only the selected branches
        #fileName = 'branchList.txt'
        #print ' o) Stripping an nTuple, keeping branches in:', fileName
        #print '    ...be patient...'
        #f = open(fileName)
        #branches = f.readlines()
        #f.close()

        #Set top branch address
        #tree.SetBranchStatus("*",0)
        #for br in branches:
        #        tree.SetBranchStatus(br.split()[0],1)

        ##clone of old tree
        #newtree = tree.CloneTree()
        #print '  Stripped Tree has: ', newtree.GetEntries()
        #print ' sripping complete! Applying cut:', cut
        #print '    ...be patient...'
        #tree = newtree.CopyTree(opts.get('cut'))
        #t = tree.CopyTree(opts.get('cut'))
        #tree = t
        #print '    ..after cut tree contains:', tree.GetEntries()
        #return {'tree':t, 'name':nTupleName, 'lumi':lumi, 'lumiUnc':lumiUnc, 'cut':opts.get('cut')}
        # ---------------------------------------------------------------- #

    return {'tree':tree, 'name':nTupleName, 'lumi':lumi, 'lumiUnc':lumiUnc, 'cut':opts.get('cut','1')}


