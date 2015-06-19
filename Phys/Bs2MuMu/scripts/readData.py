from ROOT import *

from ROOT import gROOT
gROOT.SetBatch(True)

# valAndErr is a container for the value and error. It also provides
#simple error propagation operation (multiplication and division)

from valAndErr import *

def readData(nTupleName, opts={}):
	#Read in data files
	#Combine 2012 data
		
	#lumiUnc = 0.05 # The luminosity uncertainty in percentage from the value
	
	#When comparing yields we  do not care about absolute scale and then the error is smaller :)	
	lumiUnc = 0.005 # The luminosity uncertainty in percentage from the value
		
	t_name = 'B2JpsiKTuple/DecayTree'
	if opts.get('channel','Bu')=='Bs': t_name = 'B2JpsiPhiTuple/DecayTree'
	if opts.get('channel','Bu')=='Bhh': t_name = 'B2HHTuple/DecayTree'
	if opts.get('channel','Bu')=='Bmumu': t_name = 'B2MuMuTuple/DecayTree'
	if opts.get('channel','Bu')=='Bd': t_name = 'B2JpsiKst/DecayTree'

	#---------------------------------------------------------------#	
	# Reprocessed 2011 data	
	#---------------------------------------------------------------#	
	
	if nTupleName=='2011_Strip20r1_71pb':
		#2011 data
		print '    o) Importing reprocessed 71pb-1 of 2011 data'	
		dir = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip20/'
		f_repro = dir + 'DiMuon_Strip20r1_280113_71pb__blind_280113.root'
		
		tree_repro = TChain(t_name) #Chain can be treated as a TTree object
		tree_repro.Add(f_repro)	
		lumi_repro = 71.
		tree = tree_repro
		lumi = valAndErr(lumi_repro, lumiUnc*lumi_repro)	#Object contaning value and uncertainty
		print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'	

	#---------------------------------------------------------------#	
	# Reprocessed 2012 data	
	#---------------------------------------------------------------#	
	if nTupleName=='2012_Strip20':
		#2012 data reprocessed
		print '    o) Importing reprocessed 2012', nTupleName, '1008pb-1(MagDown)  \
		+ 1011pb-1(MagUp) pb-1 dataset '	
		
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
		
		#MagnetUp:	
		f_2d = dir + prefix + 'd_112pb__blind_190113.root'
		f_2e = dir + prefix + 'e_124pb__blind_190113.root'
		f_2f = dir + prefix + 'f_124pb__blind_190113.root'
		f_2g = dir + prefix + 'g_124pb__blind_190113.root'
		f_2h = dir + prefix + 'h_133pb__blind_190113.root'
		f_2i = dir + prefix + 'i_122pb__blind_190113.root'
		f_2j = dir + prefix + 'j_119pb__blind_190113.root'
		f_2k = dir + prefix + 'k_153pb__blind_190113.root'
	

		lumi_f =   106 + 126 + 115 + 115 + 116 + 93 + 63  \
			 + 101 + 112 + 59 + 112 + 124 + 124 + 124  \
			 + 133 + 122 + 119 + 153

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
		
		lumi = valAndErr(lumi_f, lumiUnc*lumi_f)	#Object contaning value and uncertainty
		
		print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'	




	#---------------------------------------------------------------#	
	# MC samaples 
	#---------------------------------------------------------------#	


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
		print '    o) Importing 2012 MC Sm0'	
		dir  = '/castor/cern.ch/user/f/fdettori/bsmumu/control/'
		#f_MC12 = dir + 'MC2012_BJpsiK_down_500k_Strip.root'
		f_MC12 = dir + 'MC2012_BJpsiK_down_127k_Strip_match.root'
	
		tree_MC12 = TChain(t_name) #Chain can be treated as a TTree object
		tree_MC12.Add(f_MC12)	
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

	#if nTupleName=='2011':
	#	#2011 data
	#	print '    o) Importing 2011 data'	
	#	f_2011 = '/castor/cern.ch/user/f/fsoomro/Bs2MuMuStrip17/OneInvFB/1020pbDecember7BDTS.root'
	#	tree_2011 = TChain(t_name) #Chain can be treated as a TTree object
	#	tree_2011.Add(f_2011)	
	#	lumi_2011 = 1020	
	#	tree = tree_2011
	#	lumi = valAndErr(lumi_2011, lumiUnc*lumi_2011)	#Object contaning value and uncertainty
	#	print '    Tree ',t_name,' from ',nTupleName,' data has been imported!'	

	if nTupleName=='2011_Strip17':
		#2011 data
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


	if nTupleName=='2012_Strip19abc':
		#2012 data
		print '    o) Importing 2012 data'	
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
		
		#lumi_2012 = 74 + 445 + 145 + 135
		#lumi_2012 = 74 + 445 + 145 + 135 -  45 # 45 accounts for the bad runs in Strip19b
		#lumi_2012 = 75 + 444 + 303	# Sept 10
		lumi_2012 = 75 + 444 + 303 + 177 + 110	# Sept 10 and 14
		#lumi_2012 = 75 + 444 + 303 - 74	# Sept 10
		
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
		cutBadRuns = '!(runNumber<124272||runNumber>124505)&& '
		opts['cut'] = cutBadRuns + opts.get('cut','1') 
		
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
		cutBadRuns = '(runNumber<124272||runNumber>124505)&&'
		opts['cut'] = cutBadRuns + opts.get('cut','1') 
	

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
	if opts.get('cut',0):
		print '    Applying a cut to the nTuple:'
		print opts.get('cut',' -none-')
		t = tree.CopyTree(opts.get('cut',''))
		print '    ...be patient...'
		tree = t
		print '    ..tree contains events that passed the cut!' 
	# ---------------------------------------------------------------- #


	return {'tree':tree, 'name':nTupleName, 'lumi':lumi, 'lumiUnc':lumiUnc}


