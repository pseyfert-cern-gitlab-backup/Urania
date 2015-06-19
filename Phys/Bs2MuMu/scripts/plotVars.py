from __future__ import division 
from ROOT import *
import cutStrings as cs
from readData import *

#Author: Siim Tolk (NIKHEF)
#Plot a selected variable for signal and background.
# Cut away the events under in the sidebands


class plotVars:
	"""	Plot a given variable for signal by simply cutting.
		Define p = plotVars(opts={}):	\n\
		With options:\n\
		#Datasets: \n\
		'includeMC10':False, 'includeMC12':False, \n\
		'include2011_Strip17':False, 'include2011_Strip20r1_71pb':False,\n\
		'include2012_Strip19abc':False, 'include2012_Strip20':False,\n\
		#Channel:\n\
		'channel':'Bu' ,\n\
		#Selection:\n\
		'JpsiTrig':False,  \n\
		#Require Jpsi trigger\n\
		'selectRuns_2011_Strip20r1':False,  #Restrict the study to runs that have been already reprocessed\n\
		'selectRuns_2012_Strip19': False,  # Restrict the study to the runs available in Strip19, and remove 'bad runs'\n\
		#Variables to be compared:\n\
		'plotBVars':False,  'plotJpsiVars':False, 'plotMuonVars':False, 'plotKaonVars':False,  #Kinetic variables\n\
		'plotBDT':False, 'plotBDTSVars':False, 'plotBDTVars':False,  #BDT\n\
		'plotMuonGhostProb':False, 'plotKaonGhostProb':False, \\n\
		'plotMultVars_forAll':False,  #For different variables names in the data sets, NB! Dataset order matters!\n\
		'plotMultVars_Trks':False,  #For names with 'Trks' \n\
		'plotMultVars_Tracks':False,  # For names with 'Tracks'\n\
		'plotMultData':False ,  # Multiplicity variables only in data. SPD mult, etc\n\
		'plotIsolationVars':False  #Isolation variables, only in data. """


	def __init__(self , opts = {	}):
		
		print "Preparing plotBasis:"
		#Define local variables to be used
		self.var = RooRealVar()
		self.datafiles = []
		self.inc_list = []
		self.var_list = []
		self.opts = opts
		
		#Save also the root files of the plots
		self.rootFileDir = 'VarPlots/rootFiles/'
		self.plotDir = 'VarPlots/Strip20r1/'
		self.name_suf = ''
		
		#self.plotDir = '../../../VarPlots/Strip19b_BadRuns/'
		#self.name_suf = '_Strip19b_BadRunsVS_Strip19b_Strip19a'

		#Specify the channel
		prefix = 'Bplus'
		if opts.get('channel','Bu')=='Bs' or opts.get('channel','Bu')=='Bhh' or opts.get('channel','Bu')=='Bmumu': prefix = 'B_s0'

		#The var=['name in MC','name in 2011','name in 2012',etc.], if MC excluded, leave out the first	
		if opts.get('plotBDT',0):
			#self.tmpVar = { 'var' : ['aBDT05','bBDT05'] , 'min' : -0.5 , 'max' : 1., 'n_bins': 50, 'doSBsubtraction':False}
			self.tmpVar = { 'var' : ['aBDT05','bBDT05'] , 'min' : -0.5 , 'max' : 1., 'n_bins': 50, 'doSBsubtraction':True}
			self.var_list.append(self.tmpVar)
			#self.tmpVar = { 'var' : ['aBDT05flat','bBDT05flat'] , 'min' : 0. , 'max' : 1., 'n_bins': 50, 'setLog':True, 'doSBsubtraction':False}
			self.tmpVar = { 'var' : ['aBDT05flat','bBDT05flat'] , 'min' : 0. , 'max' : 1., 'n_bins': 50, 'setLog':True, 'doSBsubtraction':True}
			self.var_list.append(self.tmpVar)
	

		if opts.get('plotBVars',0):
			self.tmpVar = { 'var' : [prefix+'_JCMass'] , 'min' : 5179.17 , 'max' : 5379.17, 'n_bins': 100, 'doSBsubtraction':False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : [prefix+'_M'] , 'min' : 5100 , 'max' : 5450, 'n_bins': 100, 'doSBsubtraction':False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : [prefix+'_PT'] , 'min' : 0. , 'max' : 50000., 'n_bins' : 50, 'setLog': True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : [prefix+'_P'] , 'min' : 0 , 'max' : 1000000., 'n_bins' : 50, 'setLog': True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : [prefix+'_eta'] , 'min' : 1 , 'max' : 8, 'n_bins' : 50, 'setLog': True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : [prefix+'_phi'] , 'min' : -3.5 , 'max' : 5.5, 'n_bins' : 90}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : [prefix+'_TAU'] , 'min' : 0 , 'max' : 0.015, 'n_bins' : 50,'setLog':'True'}
			self.var_list.append(self.tmpVar)
			
		if opts.get('plotJpsiVars',0):
                        self.tmpVar = { 'var' : ['Jpsi_dist_chi2'] , 'min' : 0 , 'max' : 300, 'n_bins' : 50,'setLog':True}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : ['J_psi_1S_P'] , 'min' : 0 , 'max' : 800000, 'n_bins' : 50, 'setLog': True}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : ['J_psi_1S_PT'] , 'min' : 0 , 'max' : 50000, 'n_bins' : 50, 'setLog': True}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : ['J_psi_1S_M'] , 'min' : 3000 , 'max' : 3200, 'n_bins' : 50}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : ['J_psi_1S_MM'] , 'min' : 3000 , 'max' : 3200, 'n_bins' : 50}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : ['J_psi_1S_eta'] , 'min' : 1 , 'max' : 8, 'n_bins' : 50, 'setLog': True}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : ['J_psi_1S_doca'] , 'min' : 0 , 'max' : 0.25, 'n_bins' : 50, 'setLog':'True'}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : ['J_psi_1S_phi'] , 'min' : -3.5 , 'max' : 5.5, 'n_bins' : 90, 'setLog':'True'}
                        self.var_list.append(self.tmpVar)

                if opts.get('plotBDTSVars',0):
                        self.tmpVar = { 'var' : [prefix+'_BDTS_BIPS'] , 'min' : 0 , 'max' : 7, 'n_bins' : 35}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : [prefix+'_BDTS_DOCA'] , 'min' : 0 , 'max' : 0.2 , 'n_bins' : 50}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : [prefix+'_BDTS_VTXCHI2'] , 'min' : 0 , 'max' : 10, 'n_bins' : 50, 'setLog': True}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : [prefix+'_BDTS_DIRA'] , 'min' : 0.99990 , 'max' : 1., 'n_bins' : 50, 'setLog': True}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : [prefix+'_BDTS_BIP'] , 'min' : 0 , 'max' : 0.15, 'n_bins' : 30}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : [prefix+'_BDTS_MuonMINIP'] , 'min' : 0 , 'max' : 3, 'n_bins' : 50}
                        self.var_list.append(self.tmpVar)
                        self.tmpVar = { 'var' : [prefix+'_BDTS'] , 'min' : 0 , 'max' : 1, 'n_bins' : 50}
                        self.var_list.append(self.tmpVar)
               
	       	if opts.get('plotBDTVars',0):
			#NB! For Bmumu channel	
			#The DOCA and IP(B) are already included in BDTS	
			self.tmpVar = { 'var' : [prefix+'_PT'] , 'min' : 0. , 'max' : 15000., 'n_bins' : 50, 'setLog': True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : [prefix+'_TAU'] , 'min' : 0 , 'max' : 0.015, 'n_bins' : 50,'setLog':'True'}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['muplus_MINIPCHI2'] , 'min' : 0 , 'max' : 40000, 'n_bins' : 50, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['muplus_PT'] , 'min' : 0 , 'max' : 30000, 'n_bins' : 50, 'setLog': True}
			self.var_list.append(self.tmpVar)

		if opts.get('channel','Bu')!='Bhh' and opts.get('plotIsolationVars',0):
			self.tmpVar = { 'var' : ['J_psi_1S_D1_isolation_Giampi'] , 'min' : 0 , 'max' : 15, 'n_bins' : 15, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['J_psi_1S_D2_isolation_Giampi'] , 'min' : 0 , 'max' : 15, 'n_bins' : 15, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['J_psi_1S_yetanother_CDF_iso'] , 'min' : 0. , 'max' : 1.0, 'n_bins' : 20, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['J_psi_1S_cosnk'] , 'min' : -1.1 , 'max' : 1.1, 'n_bins' : 25, 'setLog': False}
			self.var_list.append(self.tmpVar)

		if opts.get('channel','Bu')=='Bhh' and opts.get('plotIsolationVars',0):
			self.tmpVar = { 'var' : ['B_s0_D1_isolation_Giampi'] , 'min' : 0 , 'max' : 15, 'n_bins' : 50, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['B_s0_D2_isolation_Giampi'] , 'min' : 0 , 'max' : 15, 'n_bins' : 50, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['B_s0_yetanother_CDF_iso'] , 'min' : 1.4 , 'max' : 15, 'n_bins' : 50, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['B_s0_CDFiso'] , 'min' : 0 , 'max' : 1.5, 'n_bins' : 50, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['B_s0_cosnk'] , 'min' : -1.1 , 'max' : 1.1, 'n_bins' : 50, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['bBDT'] , 'min' : -0.5 , 'max' : 1., 'n_bins' : 50, 'setLog': False}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['bBDTflat'] , 'min' : 0. , 'max' : 1.2, 'n_bins' : 50, 'setLog': False}
			self.var_list.append(self.tmpVar)


		if opts.get('plotMuonVars',0):
			#suffixes = ['plus','minus']
			suffixes = ['plus']
			for suf in suffixes:	
				#self.tmpVar = { 'var' : 'mu'+suf+'_IPCHI2_OWNPV' , 'min' : 0 , 'max' : 20000, 'n_bins' : 100, 'setLog':'True'}
				self.tmpVar = { 'var' : ['mu'+suf+'_MINIPCHI2'] , 'min' : 0 , 'max' : 40000, 'n_bins' : 50, 'setLog':True}
				self.var_list.append(self.tmpVar)
				self.tmpVar = { 'var' : ['mu'+suf+'_PT'] , 'min' : 0 , 'max' : 50000, 'n_bins' : 50, 'setLog': True}
				self.var_list.append(self.tmpVar)
				self.tmpVar = { 'var' : ['mu'+suf+'_phi'] , 'min' : -3.5 , 'max' : 5.5, 'n_bins' : 70}
				self.var_list.append(self.tmpVar)
				self.tmpVar = { 'var' : ['mu'+suf+'_eta'] , 'min' : 1., 'max' : 6, 'n_bins' : 50, 'setLog': True}
				self.var_list.append(self.tmpVar)
				self.tmpVar = { 'var' : ['mu'+suf+'_TRACK_CHI2NDOF'] , 'min' : 0 , 'max' : 5.0, 'n_bins' : 50}
				self.var_list.append(self.tmpVar)
		
		if opts.get('plotMuonGhostProb',0):
			suffixes = ['plus']
			for suf in suffixes:	
				self.tmpVar = { 'var' : ['mu'+suf+'_TRACK_GhostProb'] , 'min' : 0 , 'max' : 1., 'n_bins' : 50,'setLog':'False'}
				self.var_list.append(self.tmpVar)
		
		if opts.get('plotKaonVars',0):
			suffixes = ['plus']
			for suf in suffixes:	
				self.tmpVar = { 'var' : ['K'+suf+'_MINIPCHI2'] , 'min' : 0 , 'max' : 40000, 'n_bins' : 50, 'setLog':True}
				self.var_list.append(self.tmpVar)
				self.tmpVar = { 'var' : ['K'+suf+'_PT'] , 'min' : 0 , 'max' : 50000, 'n_bins' : 50, 'setLog': True}
				self.var_list.append(self.tmpVar)
				self.tmpVar = { 'var' : ['K'+suf+'_phi'] , 'min' : -3.5 , 'max' : 3.5, 'n_bins' : 70}
				self.var_list.append(self.tmpVar)
				self.tmpVar = { 'var' : ['K'+suf+'_eta'] , 'min' : 1., 'max' : 6, 'n_bins' : 50, 'setLog': True}
				self.var_list.append(self.tmpVar)
				self.tmpVar = { 'var' : ['K'+suf+'_TRACK_CHI2NDOF'] , 'min' : 0 , 'max' : 5.0, 'n_bins' : 50}
				self.var_list.append(self.tmpVar)
				#self.tmpVar = { 'var' : ['K'+suf+'_TRACK_GhostProb'] , 'min' : 0 , 'max' : 1., 'n_bins' : 50,'setLog':'False'}
				#self.var_list.append(self.tmpVar)
		
		if opts.get('plotKaonGhostProb',0):
			suffixes = ['plus']
			for suf in suffixes:	
				self.tmpVar = { 'var' : ['K'+suf+'_TRACK_GhostProb'] , 'min' : 0 , 'max' : 1., 'n_bins' : 50,'setLog':'False'}
				self.var_list.append(self.tmpVar)
		

		if opts.get('plotMultVars_Trks',0):
			#Variables with the same names in MC, 2011, and Stripping19/19a	
			#self.tmpVar = { 'var' : ['nDownTrks'] , 'min' : 0 , 'max' : 300, 'n_bins' : 100, 'setLog':True}
			self.tmpVar = { 'var' : ['nDownTrks'] , 'min' : 0 , 'max' : 250, 'n_bins' : 125, 'setLog':True}
			self.var_list.append(self.tmpVar)
			#self.tmpVar = { 'var' : ['nLongTrks'] , 'min' : 0 , 'max' : 600, 'n_bins' : 100, 'setLog':True}
			self.tmpVar = { 'var' : ['nLongTrks'] , 'min' : 0 , 'max' : 250, 'n_bins' : 125, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nTTCls'] , 'min' : 0 , 'max' : 3000, 'n_bins' : 100, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nTTrks'] , 'min' : 0 , 'max' : 500, 'n_bins' : 50, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nVeloTrks'] , 'min' : 0 , 'max' : 400, 'n_bins' : 100, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['Primaries'] , 'min' : 1 , 'max' : 10, 'n_bins' : 10, 'setLog':True} 
			self.var_list.append(self.tmpVar)
	
		
		if opts.get('plotUpstreamTracks',0):
			self.tmpVar = { 'var' : ['nUpstreamTracks'] , 'min' : 0 , 'max' : 150, 'n_bins' : 125, 'setLog':True}
			self.var_list.append(self.tmpVar)


		if opts.get('plotMultVars_Tracks',0):
			#Variables with the same names in MC, 2011, and Stripping19/19a	
			self.tmpVar = { 'var' : ['nUpstreamTracks'] , 'min' : 0 , 'max' : 150, 'n_bins' : 125, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nDownstreamTracks'] , 'min' : 0 , 'max' : 250, 'n_bins' : 125, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nLongTracks'] , 'min' : 0 , 'max' : 250, 'n_bins' : 125, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nTTClusters'] , 'min' : 0 , 'max' : 3000, 'n_bins' : 100, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nTTracks'] , 'min' : 0 , 'max' : 500, 'n_bins' : 50, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nVeloTracks'] , 'min' : 0 , 'max' : 400, 'n_bins' : 100, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nPVs'] , 'min' : 1 , 'max' : 10, 'n_bins' : 10, 'setLog':True} 
			self.var_list.append(self.tmpVar)
		
		if opts.get('plotMultVars_forAll',0):
			#Variables for data order MC10, MC12m, 2011, 2012, Strip20r1
			self.tmpVar = { 'var' : ['nDownTrks','nDownTrks','nDownstreamTracks','nDownTrks','nDownstreamTracks'] , 'min' : 0 , 'max' : 250, 'n_bins' : 125, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nLongTrks','nLongTrks','nLongTracks','nLongTrks','nLongTracks'] , 'min' : 0 , 'max' : 250, 'n_bins' : 125, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nTTCls','nTTCls','nTTClusters','nTTCls','nTTClusters'] , 'min' : 0 , 'max' : 3000, 'n_bins' : 100, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nTTrks','nTTrks','nTTracks','nTTrks','nTTracks'] , 'min' : 0 , 'max' : 500, 'n_bins' : 50, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nVeloTrks','nVeloTrks','nVeloTracks','nVeloTrks','nVeloTracks'] , 'min' : 0 , 'max' : 400, 'n_bins' : 100, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['Primaries','Primaries','nPVs','Primaries','nPVs'] , 'min' : 1 , 'max' : 13, 'n_bins' : 10, 'setLog':True} 
			self.var_list.append(self.tmpVar)

		#if opts.get('plotMultData2012',0) and not opts.get('includeMC',True): #the variables not in MC
		#	self.tmpVar = { 'var' : ['nSPDHits'] , 'min' : 0 , 'max' : 950, 'n_bins' : 100, 'setLog':True}
		#	self.var_list.append(self.tmpVar)
		#	self.tmpVar = { 'var' : ['nMuonTracks'] , 'min' : 0 , 'max' : 160, 'n_bins' : 80, 'setLog':True}
		#	self.var_list.append(self.tmpVar)
		#	self.tmpVar = { 'var' : ['nBackTracks'] , 'min' : 0 , 'max' : 150, 'n_bins' : 75, 'setLog':True}
		#	self.var_list.append(self.tmpVar)
		#	self.tmpVar = { 'var' : ['nOTClusters'] , 'min' : 0 , 'max' : 15000, 'n_bins' : 50, 'setLog':True}
		#	self.var_list.append(self.tmpVar)
		#	self.tmpVar = { 'var' : ['nITClusters'] , 'min' : 0 , 'max' : 2500, 'n_bins' : 50, 'setLog':True}
		#	self.var_list.append(self.tmpVar)

		if opts.get('plotMultData',0) : #the variables not in MC10
			self.tmpVar = { 'var' : ['nSPDHits'] , 'min' : 0 , 'max' : 950, 'n_bins' : 100, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nMuonTracks'] , 'min' : 0 , 'max' : 200, 'n_bins' : 50, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nBackTracks'] , 'min' : 0 , 'max' : 200, 'n_bins' : 50, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nOTClusters'] , 'min' : 0 , 'max' : 15000, 'n_bins' : 50, 'setLog':True}
			self.var_list.append(self.tmpVar)
			self.tmpVar = { 'var' : ['nITClusters'] , 'min' : 0 , 'max' : 2500, 'n_bins' : 50, 'setLog':True}
			self.var_list.append(self.tmpVar)

		#---------------------------------------------------------------------------------------------------------------------------#
		print "Variables to be compared:"
		for varDict in self.var_list:
			print "    v)", varDict.get('var','Key not in the dictionary.')
	
		#---------------------------------------------------------------------------------------------------------------------------#
		#Default fiducial cutstring:	
		self.mass_range = 100
		
		#self.cutstring = 'fabs(Bplus_JCMass-5279.17)<'+str(self.mass_range)+'&&fabs(J_psi_1S_M-3096.916)<60&&Jpsi_dist_chi2_r>15'
		#self.cutstring = self.cutstring + cs.fcuts + cs.moreCuts + cs.bdts;
		#self.cutstring = self.cutstring + cs.fcuts + cs.moreCuts + cs.bdts;
		
		# SELECTION	
		self.cutstring = cs.minimalNormBu_lnf 
		
		if self.opts.get('JpsiTrig',0): 
			self.cutstring+= cs.Bu_Jpsi_L0 + cs.Bu_Jpsi_Hlt1 + cs.Bu_Jpsi_Hlt2

		if opts.get('channel','Bu')=='Bs' :
			self.cutstring = cs.normBs_lnf	
			if self.opts.get('JpsiTrig',0): self.cutstring += cs.Bs_Jpsi_L0 + cs.Bs_Jpsi_Hlt1 + cs.Bs_Jpsi_Hlt2
		
		if opts.get('channel','Bu')=='Bhh':
			self.cutstring = ''	
			#self.cutstring = 'B_s0_BDTS>0.05'	

		#Cuts on run numbers
		self.cutstring_11 = self.cutstring	
		self.cutstring_12 = self.cutstring	
		if self.opts.get('selectRuns_2011_Strip20r1',0): self.cutstring_11 = self.cutstring + '&&(runNumber<93500&&runNumber>87665) '
		if self.opts.get('selectRuns_2012_Strip19',0): self.cutstring_12 = self.cutstring + '&&(runNumber<128108&&runNumber>111761)&&!(runNumber>124272&&runNumber<124505)'
	

		# DATASETS:
		if opts.get('includeMC10',False):
			self.datafiles.append(readData('MC10_Sm1',{'channel':opts.get('channel','Bu') , 'cut':self.cutstring}))
		if opts.get('includeMC12',False):
			#self.datafiles.append(readData('MC12_Sm0',{'channel':opts.get('channel','Bu') , 'cut':self.cutstring}))
			self.datafiles.append(readData('MC12_Sm1',{'channel':opts.get('channel','Bu') , 'cut':self.cutstring}))
		
		#Include the datafiles
		if opts.get('include2011_Strip17',True):
			self.datafiles.append(readData('2011_Strip17',{'channel':opts.get('channel','Bu'),'cut':self.cutstring_11}))
		if opts.get('include2011_Strip20r1_71pb',True):
			self.datafiles.append(readData('2011_Strip20r1_71pb',{'channel':opts.get('channel','Bu'),'cut':self.cutstring_11}))
		
		if opts.get('include2012_Strip19a',False):
			self.datafiles.append(readData('2012_Strip19a',{'channel':opts.get('channel','Bu') , 'cut':self.cutstring_12}))
		if opts.get('include2012_Strip19abc',False):
			self.datafiles.append(readData('2012_Strip19abc',{'channel':opts.get('channel','Bu') , 'cut':self.cutstring_12}))
		if opts.get('include2012_Strip20',False):
			self.datafiles.append(readData('2012_Strip20',{'channel':opts.get('channel','Bu') , 'cut':self.cutstring_12}))
	
		#-----------------------------------------------------------------------------------------------------------------------------#
		#-----------------------------------------------------------------------------------------------------------------------------#
		#-----------------------------------------------------------------------------------------------------------------------------#

	def getLegend(self):
		"""Tell which colors on the plotts correspond to which datasets."""
		colors=['Black','Red','Green','Blue','Yellow','Purple','LightBlue']
		color = 0	
		for item in self.datafiles:
			print '    l)', item.get('name','-noname-'), ' has color: ', colors[color]
			color+=1


	def compareVars(self):
		print " Plotting the distributions..."
		for var in self.var_list:
			self.compareVar(var)	
	
		print '------------------'
		print '   The cut applied:'
		print self.cutstring

		return(1)	

	def compareVar(self,varDict):
		"""Comapre the distribution of the given variable in included nTuples."""
		print 'Plotting distributions for : ', varDict['var']
		
		#Get the histograms from all the nTuples for the given var
		h_list = []
		df = 0	
		maxY = 0.	
		varStore = varDict.get('var',[])	
		sort_data = []	
		
		for datafile in self.datafiles:
			print "       ..dataset: ", datafile.get('name','-none-')
		
			varDict['tree'] = datafile.get('tree','0') 
			
			if df<len(varStore): 
				varDict['var'] = varStore[df]	
				df+=1
			else: varDict['var'] = varStore[df-1]	
		
			if varDict.get('doSBsubtraction',True):
				h_tmp = self.getSBSubtractedHist(**varDict)	
			else:	
				h_tmp = self.getHist(varDict)	
			
			#Save the histogram to a .root file
			f = TFile( str(self.rootFileDir)+str(varDict.get('var'))+str(self.name_suf)+ str(datafile.get('name')) +'.root', 'RECREATE')
			h_tmp.SetName(str(varDict.get('var'))+str(self.name_suf) + str(datafile.get('name')))
			print 'HIST NAME:', str(varDict.get('var'))+str(self.name_suf)+ str(datafile.get('name')) 
			
			#Put the histogram with the most entries in the front	
			#h_list.append(h_tmp)
			print 'h_tmp max = ', h_tmp.GetName(),' , ', h_tmp.GetMaximum()
			if h_tmp.GetMaximum()> maxY : 
				maxY = h_tmp.GetMaximum() 
				h_list.insert(0,h_tmp)		#add as a first element
				sort_data.insert(0,datafile)	# Keep the datafiles in the same order
			else:	
				h_list.append(h_tmp)		
				sort_data.append(datafile)	# Keep the datafiles in the same order
			
			h_tmp.Write()	
			f.Close()

		#Plot the normalized histograms in the same plot and save it
		color = 1	
		canv_name = varDict['var']+'_canv'	
		self.canv = TCanvas( canv_name, canv_name)

		maxY = 1.4*maxY
		print '    The maximum of the plot is set to(1.4 x max):', maxY	

		gStyle.SetFillStyle(4000)	
		gStyle.SetOptStat(kFALSE); 
		leg = TLegend(0.7,0.7,0.9,0.9)

		#PLOT ALL THE HISTOGRAMS FOR A VARIABLE:
		for data,hist in zip(sort_data , h_list):
			if color is 5: color=+1  #Violet is the new yellow
			print 'color = ' , color	
			#Configure the plotting style
			#---------------------------#
			option = 'E'	
			if varDict.get('setLog',False): gPad.SetLogy()	
			hist.SetLineWidth(1)	
			hist.SetLineColor(color)	
		        hist.SetMarkerStyle(color+20) #color is just a number
			hist.SetMarkerColor(color)
			hist.SetMarkerSize(.6);	
			hist.SetMaximum(maxY)
			#---------------------------#
			if color > 1: 
				print 'Plotting with SAME option'	
				hist.DrawNormalized(option+'SAME',1) 
			else: 
				print 'Plotting first time..'
				hist.DrawNormalized(option,1)
		        leg.AddEntry(hist,data.get('name','noname'),'lep');
			color+=1
	
			print 'Mean value and RMS of a histograms for : ', varDict['var']
			print '		File : ', data.get('name','noname')
			print '		Hist : ', hist.GetName()
			print '		N    : ', hist.GetEntries()	
			print '		Mean : ', hist.GetMean()	
			print '		RMS  : ', hist.GetRMS()	
			print '		---------------------------	'


		leg.Draw('SAME')	
		plotName = 'none'
		if varDict.get('plotNamePrefix',0): plotName = self.plotDir+varDict.get('plotNamePrefix')+self.name_suf
		else: plotName = self.plotDir+varDict['var']+self.name_suf
			
		if self.opts.get('JpsiTrig',0): plotName += '_JpsiTrig' 
		self.canv.Print(plotName+'.ps')

		return(1)

	def getSBSubtractedHist(self, var, tree,  min, max, n_bins = 100, sw_range = 35, sb_start = 70, setLog = False, plotName = '', doSBsubtraction = 1):
		""" Subtracts the events from the mass sidebands, return a histogram of a given variable"""

		#Make two histograms, one for signal and the other for background
		h_sw = TH1D("h_sw", "h_sw", n_bins, min, max)
		h_sw.Sumw2()
		h_sb = TH1D("h_sb", "h_sb", n_bins, min, max)
		h_sb.Sumw2()
		print "Before creating SB and SIGWIN datasets.."
		c = TCanvas(">> h_sx",">> h_sx")	
		
		cutVar = "fabs(Bplus_JCMass-5279.17)" 
		if self.opts.get('channel','Bu')=='Bs' : cutVar = "fabs(B_s0_JCMass-5366.3)" 
		if self.opts.get('channel','Bu')=='Bhh': cutVar = "fabs(B_s0_M-5366.3)" 

		
		print '  THE CUTVAR: ', cutVar	
		tree.Draw(var+" >> h_sw", cutVar+"<"+str(sw_range))
		tree.Draw(var+" >> h_sb", cutVar+">"+str(sb_start))
		del c		
		# Plot the sb and sw histograms	
		#self.h_sw.SetLineColor(2)	
		#self.h_sw.Draw()
		#self.h_sb.SetLineColor(3)	
		#self.h_sb.Draw('same')

		#Subtract the normalized number of projected backgrond events in the signal region
		#for the given variable.

		m_sb_norm = (sw_range) / (self.mass_range - sb_start)
		print 'Scalefactor is %f' % m_sb_norm	
		
		#self.h_out = h_sw.Clone()
		#self.canvas = TCanvas(var+'_canv',var+'_canv')	
		#self.h_out.SetName(var+'_hist')
		#self.h_out.SetTitle(var+'hist')
		#self.h_tmp = self.h_out.Clone()
		#self.h_tmp.Draw()	
		#self.h_out.Add(h_sb, -1*m_sb_norm)
		#self.h_out.SetLineColor(2)	
		#self.h_out.Draw('same')	
		print "Cloning the h_sw:"	
		h_out = h_sw.Clone()
		h_out.SetName(var+'_hist')
		title = var.split('_')	
		plotTitle = ''
		
		for word in title: plotTitle+= str(word)+' '
		if plotName!='': plotTitle = plotName	
		h_out.SetTitle(plotTitle)
		h_out.Add(h_sb, -1*m_sb_norm)
		return(h_out)

	#def getHist(self, var, tree,  min, max, n_bins = 100, setLog = False, plotName = '', doSBsubtraction = 0):
	def getHist(self, varDict):
		""" Return a histogram of a given variable"""

		var = varDict.get('var','none')
		#Make two histograms, one for signal and the other for background
		print 'Returninng histogram without SB subtraction!'	
		h_out = TH1D("h_out", "h_out", varDict.get('n_bins',100), varDict.get('min',0.), varDict.get('max',100))
		h_out.Sumw2()
		c = TCanvas(">> hist",">> hist")	
		
		varDict.get('tree').Draw(var+" >> h_out")
		del c		
		# Plot the sb and sw histograms	
		#self.h_sw.SetLineColor(2)	
		#self.h_sw.Draw()
		#self.h_sb.SetLineColor(3)	
		#self.h_sb.Draw('same')

		#Subtract the normalized number of projected backgrond events in the signal region
		#for the given variable.

		
		#self.h_out = h_sw.Clone()
		#self.canvas = TCanvas(var+'_canv',var+'_canv')	
		#self.h_out.SetName(var+'_hist')
		#self.h_out.SetTitle(var+'hist')
		#self.h_tmp = self.h_out.Clone()
		#self.h_tmp.Draw()	
		#self.h_out.Add(h_sb, -1*m_sb_norm)
		#self.h_out.SetLineColor(2)	
		#self.h_out.Draw('same')	
		h_out.SetName(var+'_hist')
		title = var.split('_')	
		plotTitle = ''
	
		plotName = varDict.get('plotName','')
		for word in title: plotTitle+= str(word)+' '
		if plotName!='': plotTitle = plotName	
		h_out.SetTitle(plotTitle)
		return(h_out)


	def drawVar(self,var,x_hi = 0, x_lo = 0, bins = 100):
		"""Draw the plot for the variable in the nTuple with cuts."""
		
		if self.var.GetName() != var :
			self.var = RooRealVar(var, var,  self.tK2.GetMinimum(var), self.tK2.GetMaximum(var))
			self.data = RooDataSet("dataset","The datasett for var after cutting.",self.tree,RooArgSet(self.var))	
			
		if x_hi > 0 :
			self.var.setRange(x_lo,x_hi)
			print "Custom range set for variable",var	
		
		fr = self.var.frame()
		self.data.plotOn(fr, RooFit.Binning(bins))
		fr.Draw()
		return(fr)



