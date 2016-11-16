from __future__ import division
from ROOT import *
from os import *
from SomeMassModels import B2JpsiModels as B

#Import a class for propagating errors in products and dicisions
from valAndErr import *
from readData import *

from math import *
import cutStrings as cs

class massFit:

	def __init__(self,nTupleName, channel = 'Bu'):
		self.dataDict = readData(nTupleName, {'channel':channel});
		self.tree = self.dataDict.get('tree',0)
		self.lumi = self.dataDict.get('lumi',0)
		self.lumiUnc = self.dataDict.get('lumiUnc',0)
		self.nTupleName = nTupleName
		print 'massFit : ciao! nTuple under investigation:', nTupleName
	 	#Broaden the cutstring maximum	(we have looooong trigger conditions)
		TFormula.SetMaxima(100000,1000,1000000)

	def getTriggerEff_Bu(self, opts={'plotName':'totalTrig', 'useConstrainedBMass':True, 'fitAnyhow':False, 'PIDK':False, 'GhostProbCut':False, }):
		#Fit for the Bu yields in the formula ef = [TIS&TOS / TOS] * [TRIGGERED / TIS]
		print 'Calculating the trigger efficiancy:'


		#This is for storing the fit results and reading them in later
		sufId = '1'	# id for the massFitResult files
		resultDir = 'MassFitResults/'

		plotName = opts.get('plotName','totalTrig')

		massVar  = 'Bplus_M'
		testCut = opts.get('testCut','')
		cut = cs.minimalNormBu_rawM_lnf	+ testCut

		if opts.get('useConstrainedBMass',True):
			massVar = 'Bplus_JCMass'
			cut = cs.minimalNormBu_lnf

		if opts.get('PIDK', False):
			cut +=	cs.Bu_PID

		#Remove bad runs from Strip 19b
		#cut +=	cs.cutBadRuns	# it is easier to define a new object in readData

		#Fo< Strip2> validation
		if opts.get('2011S17runCut',False):
			cut += '&&(runNumber<93500&&runNumber>87665)'
		if opts.get('2012S20runCut',False):
			cut += '&&(runNumber<128108&&runNumber>111761)&&!(runNumber>124272&&runNumber<124505)'
		#-------------#


		#Add GhostProb cut
		if opts.get('GhostProbCut',0):
			cut +=	cs.Bu_GhostProb

		#Add GhostProb cut
		if opts.get('MuMuGhostProbCut',0):
			cut +=	cs.MuMu_GhostProb

		#Add the trigger lines used for TIS and TOS, requiring only Dec here for TRIG events
		cut += cs.Bu_cut_Dec


		print '  The fiducial cut used: ', cut
		print '   TIS cut:', cut+'&&'+cs.Bu_cut_TIS
		print '   TOS cut:', cut+'&&'+cs.Bu_cut_TOS
		print '   TISandTOS cut:', cut + cs.Bu_cut_TIS + cs.Bu_cut_TOS

		#Canvas for saving the plots
		canvas = TCanvas(massVar+'_canv',massVar+'_canv', 800,600)
		setLog = True

		bins = 100

		print 'Fitting  i) TIS yield'
		self.fitTIS = B.BuJPsiK(self.tree,massVar, cut+cs.Bu_cut_TIS, True)
		#self.confAndFitBu(self.fitTIS)
		suf = 'TIS_'+sufId
		fitResultFile = 'Bu_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'
		self.confAndFitBu(self.fitTIS, {'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':opts.get('fitAnyhow',0)})
		self.fitTIS.plot(bins)
		#canvas.Print('TriggerEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_TIS_'+plotName+'.ps')
		canvas.Print('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TIS_'+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTIS.model.getParameters(self.fitTIS.data).writeToFile('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TIS_'+plotName+'_PARAMETERS.txt')

		self.N_tis = valAndErr(self.fitTIS.nsig.getVal(), self.fitTIS.nsig.getError())
		#del self.fitTIS

		print 'Fitting  i) TOS yield'
		self.fitTOS = B.BuJPsiK(self.tree,massVar, cut+cs.Bu_cut_TOS, True)
		suf = 'TOS_'+sufId
		fitResultFile = 'Bu_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'
		self.confAndFitBu(self.fitTOS, {'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':opts.get('fitAnyhow',0)})
		self.fitTOS.plot(bins)
		#canvas.Print('TriggerEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_TOS_'+plotName+'.ps')
		canvas.Print('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TOS_'+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTOS.model.getParameters(self.fitTOS.data).writeToFile('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TOS_'+plotName+'_PARAMETERS.txt')

		self.N_tos = valAndErr(self.fitTOS.nsig.getVal(), self.fitTOS.nsig.getError())


		print 'Fitting  i) TIS&TOS yield'
		self.fitTISTOS = B.BuJPsiK(self.tree,massVar, cut+cs.Bu_cut_TIS+cs.Bu_cut_TOS, True)
		#self.confAndFitBu(self.fitTISTOS)
		suf = 'TISTOS_'+sufId
		fitResultFile = 'Bu_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'
		self.confAndFitBu(self.fitTISTOS, {'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':opts.get('fitAnyhow',0)})
		self.fitTISTOS.plot(bins)
		#canvas.Print('TriggerEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_TISTOS_'+plotName+'.ps')
		canvas.Print('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TISTOS_'+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTISTOS.model.getParameters(self.fitTISTOS.data).writeToFile('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TISTOS_'+plotName+'_PARAMETERS.txt')

		self.N_tistos = valAndErr(self.fitTISTOS.nsig.getVal(), self.fitTISTOS.nsig.getError())


		print 'Fitting  i) TRIGGERED yield'
		self.fitTRIG = B.BuJPsiK(self.tree,massVar,cut, True)
		#self.confAndFitBu(self.fitTRIG)
		suf = sufId
		fitResultFile = 'Bu_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'
		self.confAndFitBu(self.fitTRIG, {'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':opts.get('fitAnyhow',0)})
		self.fitTRIG.plot(bins)
		#canvas.Print('TriggerEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_TRIG_'+plotName+'.ps')
		canvas.Print('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TRIG_'+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTRIG.model.getParameters(self.fitTRIG.data).writeToFile('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TRIG_'+plotName+'_PARAMETERS.txt')


		print 'S:'
		self.N_trig = valAndErr(self.fitTRIG.nsig.getVal(), self.fitTRIG.nsig.getError())
		#The background yield
		#self.N_trig_bkg = self.fitTRIG.nbkg.getVal()
		#self.sig_N_trig_bkg = self.fitTRIG.nbkg.getError()
		print 'B:'
		self.N_trig_bkg = valAndErr(self.fitTRIG.nbkg.getVal(), self.fitTRIG.nbkg.getError())

		# Signal / Background ratio
		print 'S/B:'
		self.SoverB = self.N_trig.over(self.N_trig_bkg)

		#Evaluate the trigger efficiency
		print 'TIS, TOS, and TRIG eff:'
		#TIS trigger efficiency
		isEff = True
		self.tisEff = self.N_tistos.over(self.N_tos, isEff)

		#TOS trigger efficiency
		self.tosEff = self.N_tistos.over(self.N_tis, isEff)

		#Total trigger efficiency
		self.trigEff = self.tisEff.times( self.N_trig.over(self.N_tis) )

		#Signal and Background yields per pb
		print 'S/pb:'
		self.raw_sig_yield_per_pb = self.N_trig.over( self.lumi )
		self.sig_yield_per_pb = self.N_trig.over( self.lumi.times(self.trigEff) )
		print 'B/pb:'
		self.bkg_yield_per_pb = self.N_trig_bkg.over( self.lumi.times(self.trigEff) )

		#B mass error from 2 gaussians

		self.f = valAndErr(self.fitTRIG.f1.getVal(), self.fitTRIG.f1.getError())
		self.Bmass_mean = valAndErr(self.fitTRIG.mean1.getVal(), self.fitTRIG.mean1.getError())

		self.sigma1 = valAndErr(self.fitTRIG.sigma1.getVal(), self.fitTRIG.sigma1.getError())
		self.delta_s = valAndErr(self.fitTRIG.delta_s.getVal(), self.fitTRIG.delta_s.getError())
		self.sigma2 = self.sigma1.plus( self.delta_s )

		self.Bmass_sigma = ( ( self.f.times( self.sigma1.times(self.sigma1) ).plus(self.sigma2.times(self.sigma2)) ).minus( self.f.times(self.sigma2.times(self.sigma2)) ) ).sqrt()

		#Print the cuts
		print '-------------------------------------------------------'
		print '   Datasample:', self.nTupleName
		print '   Mass Variable:', massVar
		print '   Luminosity of the datasample:', self.lumi.getVal()
		print '-------------------------------------------------------'
		print '--Cuts used: ------------------------------------------'
		print '   TIS cut:', cut+'&&'+cs.Bu_cut_TIS
		print '   TOS cut:', cut+'&&'+cs.Bu_cut_TOS
		print '   TISandTOS cut:', cut + '&&' + cs.Bu_cut_TIS + '&&' + cs.Bu_cut_TOS
		print '------------------------------------------------------'
		print '  The fiducial cut used: ', cut
		print '   The N_tis: ', self.N_tis.getVal() ,' +- ', self.N_tis.getErr()
		print '   The N_tos: ', self.N_tos.getVal() ,' +- ', self.N_tos.getErr()
		print '   The N_tistos: ', self.N_tistos.getVal() ,' +- ', self.N_tistos.getErr()
		print "Bu-->JPsi K+ raw Signal: ",self.N_trig.getVal() ," +- ", self.N_trig.getErr()
		print "             	nBkg  : ", self.N_trig_bkg.getVal() ," +- ", self.N_trig_bkg.getErr()
		print "            and S/B: " , self.SoverB.getVal(), ' +- ', self.SoverB.getErr()
		print "             Signal yield per pb: ",self.raw_sig_yield_per_pb.getVal()," +- ",self.raw_sig_yield_per_pb.getErr()
		print '			LUMINOSITY UNCERTAINTY: ', self.lumiUnc
		print '------------------------------------------------------'

		#Print the trigger efficiencies
		print '------------------------------------------------------'
		print 'Trigger efficiency: ', self.trigEff.getVal(), ' +- ', self.trigEff.getErr()
		print '  tisEff = ', self.tisEff.getVal(), ' +- ', self.tisEff.getErr()
		print '  tosEff = ', self.tosEff.getVal(), ' +- ', self.tosEff.getErr()
		print '------------------------------------------------------'
		#Print the signal and background yields
		print '	Trigger efficiency corrected yields:'
		print "             Signal yield per pb: ", self.sig_yield_per_pb.getVal() ," +- ", self.sig_yield_per_pb.getErr()
		print "             Bkg    yield per pb: ", self.bkg_yield_per_pb.getVal() ," +- ", self.bkg_yield_per_pb.getErr()
		print '		NB! The Bmass mean error is the fit one, consider B_mass_sigma as uncertanity!'
		print '   Fitted Bu mass mean: ', self.Bmass_mean.getVal(), ' +- ', self.Bmass_mean.getErr()
		print '   Fitted Bu mass sigma: ', self.Bmass_sigma.getVal(), ' +- ', self.Bmass_sigma.getErr()
		print '------------------------------------------------------'

		return {'trigEff':self.trigEff.getVal(), 'trigEff_err':self.trigEff.getErr(), 'Nsig': self.N_trig.getVal() , 'Nsig_err': self.N_trig.getErr()}


	def confAndFitBu(self,fit, opts):
			print '    configuring fitter..'
			fit.fsh.setVal(0)
			fit.fsh.setConstant(kTRUE)
			fit.sh_mean.setConstant(kTRUE)
			fit.sh_sigma.setConstant(kTRUE)

			fit.delta_m.setRange(0.,200.) #Let the resolution addition of the second Gaussian go to zero if needed.

			#Constrain the slope of the exponential background so that it is not negative.
			#This is needed for Strip19b_abc TIS&TOS fot

			#fit.fitIfNotSaved(opts)
			fit.fit({},8)


	def getCutEff_Bu(self, opts):
		#{'meson':'Bu', 'cuts':['',''],'massVar':'Bplus_JCMass','savePlots':False, 'dir':PIDKeffPlots}
		'''This function calculates the cut efficiency w.r.t. fiducial cuts for an array of given cuts.'''

		resultDir = 'MassFitResults/'
		massVar  = opts.get('massVar','Bplus_JCMass')

		#No PID cut
		plotName = 'cutEff'
		cut = cs.minimalNormBu_rawM_lnf

		if massVar=='Bplus_JCMass':
			cut = cs.minimalNormBu_lnf
		sufId = '1'	# massFitResult files without PIDK cut

		print '  The fiducial cut used: ', cut
		canvas = TCanvas(massVar+'_canv',massVar+'_canv', 800,600)

		testCut = opts.get('testCut','')
		print 'Fitting  i) testCut yield',testCut
		self.fitCUT = B.BuJPsiK(self.tree,massVar, cut+testCut,True)
		suf = testCut+'_'+sufId
		fitResultFile = 'Bu_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'

		self.confAndFitBu(self.fitCUT, {'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8})
		self.fitCUT.plot()

		#canvas.Print('CutEffPlots/'+massVar+'_'+str(self.lumi.getVal())+testCut+plotName+'.ps')
		canvas.Print('CutEffPlots/'+massVar+'_'+self.nTupleName+'_'+testCut+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTUT.model.getParameters(self.fitTUT.data).writeToFile('CutEffPlots/'+massVar+'_'+self.nTupleName+testCut+plotName+'_PARAMETERS.txt')

		self.N_cut = valAndErr(self.fitCUT.nsig.getVal(), self.fitCUT.nsig.getError())

		print 'Fitting  i) Fiducial cut yield'
		self.fitTRIG = B.BuJPsiK(self.tree,massVar, cut,True)
		suf = sufId
		fitResultFile = 'Bu_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'
		self.confAndFitBu(self.fitTRIG, {'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8})
		self.fitTRIG.plot()
		canvas.Print('CutEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_FIDUCIAL_'+plotName+'.ps')

		print 'All:'
		self.N_trig = valAndErr(self.fitTRIG.nsig.getVal(), self.fitTRIG.nsig.getError())

		# Signal / Background ratio
		print 'Efficiency::'
		cutEff = self.N_cut.over(self.N_trig, True)

		#Evaluate the trigger efficiency
		print 'testCut:', testCut
		print 'Efficiency:', cutEff.getVal(),'+-',cutEff.getErr()

		return cutEff



	def getNormBu_lnf(self,  opts={'testCut':'', 'massVar':'Bplus_JCMass', 'resultDir':'MassFitResults/','plotDir':'MassFitPlots/', 'sufId':'1', 'fitAnyhow':0}):
		'''This function performs Bu mass fit and gives the signal and background yields.
		   If a testCut='&&....' cut is given, the testCut is added to the fiducial cuts.'''

		massVar = opts.get('massVar','Bplus_JCMass')
		testCut = opts.get('testCut','')
		resultDir = opts.get('resultDir','MassFitResults/')
		plotDir = opts.get('plotDir','MassFitPlots/')
		sufId = opts.get('sufId','1')
		fitAnyhow = opts.get('fitAnyhow',0)

		cut = cs.minimalNormBu_rawM_lnf
		if massVar=='Bplus_JCMass':
			cut = cs.minimalNormBu_lnf

		if opts.get('PIDK', False):
			cut +=	cs.Bu_PID

		#Add GhostProb cut
		if opts.get('GhostProbCut',0):
			cut +=	cs.Bu_GhostProb

		#Add GhostProb cut
		if opts.get('MuMuGhostProbCut',0):
			cut +=	cs.MuMu_GhostProb

		#Require JpsiDiMuon triggers
		if opts.get('JpsiTrig', False):
			Bu_Jpsi_trig = cs.Bu_Jpsi_L0 + cs.Bu_Jpsi_Hlt1 + cs.Bu_Jpsi_Hlt2
			cut +=	Bu_Jpsi_trig

		cut += testCut
		#fitBu = B.BuJPsiK(self.tree, massVar , cut, False)
		fitBu = B.BuJPsiK(self.tree, massVar , cut, True)

		#Select signal events:
		fitResultFile = 'Bu_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(sufId)+'.root'
		self.confAndFitBu(fitBu, {'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':fitAnyhow})

				#fitBu.plot()

		scale = [True,False]

		for log in scale:
			#Save the plot
			canvas = TCanvas(massVar+'_canv',massVar+'_canv', 800,600)
			fr = fitBu.plot(100,log)
			file = TFile('LHCbStylePlots/BplusJpsiKplus_'+opts.get('massVar','BplusJCMass')+'_fidCut_Fit_LogScale_'+str(log)+'.root','RECREATE')
			fr.Write()
			file.Close()
			canvas.Print(plotDir+massVar+'_'+self.nTupleName+'_fidCut_LogScale_'+str(log)+'.ps')

		#Save the fitted parameters to a file
		fitBu.model.getParameters(fitBu.data).writeToFile(str(resultDir)+str(massVar)+'_'+str(self.nTupleName)+'_fidCut_PARAMETERS.txt')

		N_sig = valAndErr(fitBu.nsig.getVal(), fitBu.nsig.getError())
		N_bkg = valAndErr(fitBu.nbkg.getVal(), fitBu.nbkg.getError())
		SoverB = N_sig.over(N_bkg)
		sig_yield_per_pb = N_sig.over(self.lumi)
		bkg_yield_per_pb = N_bkg.over(self.lumi)

		#B mass error from 2 gaussians
		self.f = valAndErr(fitBu.f1.getVal(), fitBu.f1.getError())
		self.Bmass_mean = valAndErr(fitBu.mean1.getVal(), fitBu.mean1.getError())

		self.sigma1 = valAndErr(fitBu.sigma1.getVal(), fitBu.sigma1.getError())
		self.delta_s = valAndErr(fitBu.delta_s.getVal(), fitBu.delta_s.getError())
		self.sigma2 = self.sigma1.plus( self.delta_s )

		self.Bmass_sigma = ( ( self.f.times( self.sigma1.times(self.sigma1) ).plus(self.sigma2.times(self.sigma2)) ).minus( self.f.times(self.sigma2.times(self.sigma2)) ) ).sqrt()


		print "-------------------------------------------"
		print "-------------------------------------------"
		print 'The mass variable used:', massVar
		print 'Datafile :', self.nTupleName
		print "The luminosity is: ", self.lumi.getVal();
		print "tree has ",self.tree.GetEntries()," entries"
		print "Fiducial cuts applied", cut
		print 'test Cut used:', testCut
		print "tree has ",self.tree.GetEntries(cut)," entries after cuts"
		print "-------------------------------------------"

		#    fitBu.fit()

		print "Bu-->JPsi K+ nSignal: ",N_sig.getVal()," +- ",N_sig.getErr()," and S/B: " , SoverB.getVal(), '+-', SoverB.getErr()
		print "             Signal yield per pb: ",sig_yield_per_pb.getVal()," +- ",sig_yield_per_pb.getErr()
		print "             Bkg    yield per pb: ",bkg_yield_per_pb.getVal()," +- ",bkg_yield_per_pb.getErr()
		print '		NB! The Bmass mean error is the fit one, consider B_mass_sigma as uncertanity!'
		print '   Fitted Bu mass mean: ', self.Bmass_mean.getVal(), ' +- ', self.Bmass_mean.getErr()
		print '   Fitted Bu mass sigma: ', self.Bmass_sigma.getVal(), ' +- ', self.Bmass_sigma.getErr()
		print '------------------------------------------------------'



		ef=fitBu.f1.getError()/fitBu.f1.getVal()
		es1=fitBu.sigma1.getError()/fitBu.sigma1.getVal()
		es2=sqrt((fitBu.sigma1.getError()/fitBu.sigma1.getVal())**2+(fitBu.delta_s.getError()/(fitBu.sigma1.getVal()+fitBu.sigma2.getVal()))**2)
		res = fitBu.f1.getVal()*fitBu.sigma1.getVal()+(1-fitBu.f1.getVal())*fitBu.sigma2.getVal()
		eres = sqrt(ef**2+es1**2)*fitBu.f1.getVal()*fitBu.sigma1.getVal()+sqrt(ef**2+es2**2)*(1-fitBu.f1.getVal())*fitBu.sigma2.getVal()

		print "resolution: ",res," +- ",eres
		return fitBu

	def getCutEff_Bs(self, opts):
		#{'meson':'Bs', 'cuts':['',''],'massVar':'B_s0__JCMass','savePlots':False, 'dir':PIDKeffPlots}
		'''This function calculates the cut efficiency w.r.t. fiducial cuts for an array of given cuts.'''

		resultDir = 'MassFitResults/'
		massVar  = opts.get('massVar','B_s0_JCMass')

		#No PID cut
		plotName = 'cutEff'
		cut = cs.normBs_lnf
		sufId = 'noPID'	# massFitResult files without PIDK cut

		#PIDK cut
		if opts.get('PIDK', False):
			sufId = 'PIDK'
			cut = cs.normBsPID_lnf
			plotName = 'totalTrig_PIDK'

		print '  The fiducial cut used: ', cut
		canvas = TCanvas(massVar+'_canv',massVar+'_canv', 800,600)


		testCut = opts.get('testCut','')
		print 'Fitting  i) testCut yield',testCut
		self.fitCUT = B.DoubleGaussian(self.tree,massVar,cut+testCut)
		suf = testCut+'_'+sufId
		fitResultFile = 'Bs_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'

		#self.fitCUT.fitIfNotSaved({'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8})
		self.fitCUT.fit({},8)
		self.fitCUT.plot()

		#canvas.Print('CutEffPlots/'+massVar+'_'+str(self.lumi.getVal())+testCut+plotName+'.ps')
		canvas.Print('CutEffPlots/'+massVar+'_'+self.nTupleName+testCut+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitCUT.model.getParameters(self.fitCUT.data).writeToFile('MassFitPlots/'+massVar+'_'+self.nTupleName+'_fidCut_'+testCut+'_PARAMETERS.txt')

		self.N_cut = valAndErr(self.fitCUT.nsig.getVal(), self.fitCUT.nsig.getError())

		print 'Fitting  i) Fiducial cut yield'
		self.fitTRIG = B.DoubleGaussian(self.tree,massVar,cut)
		suf = sufId
		fitResultFile = 'Bs_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'

		#self.fitTRIG.fitIfNotSaved({'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8})
		self.fitTRIG.fit({},8)

		self.fitTRIG.plot()
		#canvas.Print('CutEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_FIDUCIAL_'+plotName+'.ps')
		canvas.Print('CutEffPlots/'+massVar+'_'+self.nTupleName+'_FIDUCIAL_'+plotName+'.ps')

		print 'All:'
		self.N_trig = valAndErr(self.fitTRIG.nsig.getVal(), self.fitTRIG.nsig.getError())

		# Signal / Background ratio
		print 'Efficiency::'
		cutEff = self.N_cut.over(self.N_trig, True)

		#Evaluate the trigger efficiency
		print 'testCut:', testCut
		print 'Efficiency:', cutEff.getVal(),'+-',cutEff.getErr()

		return cutEff


	def getNormBs_lnf(self, opts):
		#self,  testCut='', massVar = 'Bplus_JCMass', resultDir = 'MassFitResults/', sufId = '1', fitAnyhow=0

		testCut = opts.get('testCut','')
		massVar = opts.get('massVar','B_s0_JCMass')
		resultDir = opts.get('resultDir','MassFitResults/')
		plotDir = opts.get('plotDir','MassFitPlots/')
		sufId = opts.get('sufId','1')
		fitAnyhow = opts.get('fitAnyhow',0)

		fitResultFile = 'Bs_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(sufId)+'.root'

		#PIDK cut
		cut = cs.normBs_lnf

		if opts.get('noCuts', False): cut = 'B_s0_JCMass>0'

		if opts.get('PIDK', False):
			sufId = 'PIDK'
			cut = cs.normBsPID_lnf
		#Remove bad runs from Strip 19b
		#cut +=	cs.cutBadRuns
		#Add GhostProb cut
		if opts.get('GhostProbCut', False):
			cut +=	cs.Bs_GhostProb

		#Require JpsiDiMuon triggers
		if opts.get('JpsiTrig', False):
			Bs_Jpsi_trig = cs.Bs_Jpsi_L0 + cs.Bs_Jpsi_Hlt1 + cs.Bs_Jpsi_Hlt2
			cut +=	Bs_Jpsi_trig

		cut += testCut
		print cut

		fitBs = B.DoubleGaussian(self.tree,"B_s0_JCMass",cut)
    		#fitBs.fitIfNotSaved({'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':fitAnyhow})
		fitBs.fit({},8)

		canvas = TCanvas(massVar+'_canv',massVar+'_canv', 800,600)
		bins = 100
		setLog = True
		#fitBs.plot(bins,setLog)
		fitBs.plot(bins)
		#canvas.Print('MassFitPlots/'+massVar+'_'+str(self.lumi.getVal())+'_fidCut_'+testCut+'.ps')
		canvas.Print(plotDir+massVar+'_'+self.nTupleName+'_fidCut_'+testCut+'.ps')
		#Save the fitted parameters to a file
		fitBs.model.getParameters(fitBs.data).writeToFile(plotDir+massVar+'_'+self.nTupleName+'_fidCut_'+testCut+'_PARAMETERS.txt')


		N_sig = valAndErr(fitBs.nsig.getVal(), fitBs.nsig.getError())
		N_bkg = valAndErr(fitBs.nbkg.getVal(), fitBs.nbkg.getError())
		SoverB = N_sig.over(N_bkg)
		sig_yield_per_pb = N_sig.over(self.lumi)
		bkg_yield_per_pb = N_bkg.over(self.lumi)

		print '-------------------------------------------------------'
		print '   Datasample:', self.nTupleName
		print '   Mass Variable:', massVar
		print '   Luminosity of the datasample:', self.lumi.getVal()
		print '-------------------------------------------------------'
		print '  The fiducial cut used: ', cut
		print '------------------------------------------------------'
		print "Bs-->JPs Phi nSignal: ",fitBs.nsig.getVal()," +- ",fitBs.nsig.getError()," and S/B: " ,  fitBs.nsig.getVal()/(1.*fitBs.nbkg.getVal())
		print "             Signal yield per pb: ",sig_yield_per_pb.getVal()," +- ",sig_yield_per_pb.getErr()
		print "             Bkg    yield per pb: ",bkg_yield_per_pb.getVal()," +- ",bkg_yield_per_pb.getErr()
		print '			LUMINOSITY UNCERTAINTY: ', self.lumiUnc


		self.Bmass_mean = valAndErr(fitBs.mean1.getVal(), fitBs.mean1.getError())
		self.sigma1 = valAndErr(fitBs.sigma1.getVal(), fitBs.sigma1.getError())
		self.delta_s = valAndErr(fitBs.delta_s.getVal(), fitBs.delta_s.getError())
		self.sigma2 = self.sigma1.plus( self.delta_s )
		self.f = valAndErr(fitBs.f1.getVal(), fitBs.f1.getError())
		self.Bmass_sigma = ( ( self.f.times( self.sigma1.times(self.sigma1) ).plus(self.sigma2.times(self.sigma2)) ).minus( self.f.times(self.sigma2.times(self.sigma2)) ) ).sqrt()

	#Print the signal and background yields
		print '		NB! The Bmass mean error is the fit one, consider B_mass_sigma as uncertanity!'
		print '   Fitted Bs mass mean: ', self.Bmass_mean.getVal(), ' +- ', self.Bmass_mean.getErr()
		print '   Fitted Bs mass sigma: ', self.Bmass_sigma.getVal(), ' +- ', self.Bmass_sigma.getErr()
		print '------------------------------------------------------'


		ef=fitBs.f1.getError()/fitBs.f1.getVal()
		es1=fitBs.sigma1.getError()/fitBs.sigma1.getVal()
		es2=sqrt((fitBs.sigma1.getError()/fitBs.sigma1.getVal())**2+(fitBs.delta_s.getError()/(fitBs.sigma1.getVal()+fitBs.sigma2.getVal()))**2)
		res=fitBs.f1.getVal()*fitBs.sigma1.getVal()+(1-fitBs.f1.getVal())*fitBs.sigma2.getVal()
		eres=sqrt(ef**2+es1**2)*fitBs.f1.getVal()*fitBs.sigma1.getVal()+sqrt(ef**2+es2**2)*(1-fitBs.f1.getVal())*fitBs.sigma2.getVal()

		print "resolution: ",res," +- ",eres

		return fitBs

	def getTriggerEff_Bs(self, opts={'plotName':'totalTrig', 'PIDK':False, 'fitAnyhow':False, 'GhostProbCut':True}):
		#Fit for the Bs yields in the formula ef = [TIS&TOS / TOS] * [TRIGGERED / TIS]
		print 'Calculating the trigger efficiancy:'


		resultDir = 'MassFitResults/'
		massVar  = 'B_s0_JCMass'


		#No PID cut
		plotName = 'totalTrig'
		cut = cs.normBs_lnf
		sufId = 'noPID'	# massFitResult files without PIDK cut

		#PIDK cut
		if opts.get('PIDK', False):
			sufId = 'PIDK'
			cut = cs.normBsPID_lnf
			plotName = 'totalTrig_PIDK'
		#Remove bad runs from Strip 19b
		#cut +=	cs.cutBadRuns
		#Add GhostProb cut
		if opts.get('GhostProbCut', False):
			cut +=	cs.Bs_GhostProb

		print '  The fiducial cut used: ', cut
		print '   TIS cut:', cut+'&&'+cs.Bs_cut_TIS
		print '   TOS cut:', cut+'&&'+cs.Bs_cut_TOS
		print '   TISandTOS cut:', cut + cs.Bs_cut_TIS + cs.Bs_cut_TOS

		#Canvas for saving the plots
		canvas = TCanvas(massVar+'_canv',massVar+'_canv', 800,600)
		setLog = True
		bins = 100


		print 'Fitting  i) TIS yield'
		self.fitTIS = B.DoubleGaussian(self.tree,massVar,cut+cs.Bs_cut_TIS)
		suf = 'TIS_'+sufId
		fitResultFile = 'Bs_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'

		#self.fitTIS.fitIfNotSaved({'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':opts.get('fitAnyhow',0)})
		self.fitTIS.fit({},8)

		self.fitTIS.plot(bins)
		#canvas.Print('TriggerEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_TIS_'+plotName+'.ps')
		canvas.Print('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TIS_'+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTIS.model.getParameters(self.fitTIS.data).writeToFile('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TIS_'+plotName+'_PARAMETERS.txt')

		self.N_tis = valAndErr(self.fitTIS.nsig.getVal(), self.fitTIS.nsig.getError())
		del self.fitTIS

		print 'Fitting  i) TOS yield'
		self.fitTOS = B.DoubleGaussian(self.tree,massVar,cut+cs.Bs_cut_TOS)
		suf = 'TOS_'+sufId
		fitResultFile = 'Bs_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'

		#self.fitTOS.fitIfNotSaved({'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':opts.get('fitAnyhow',0)})
		self.fitTOS.fit({},8)

		self.fitTOS.plot(bins)
		#canvas.Print('TriggerEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_TOS_'+plotName+'.ps')
		canvas.Print('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TOS_'+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTOS.model.getParameters(self.fitTOS.data).writeToFile('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TOS_'+plotName+'_PARAMETERS.txt')

		self.N_tos = valAndErr(self.fitTOS.nsig.getVal(), self.fitTOS.nsig.getError())
		del self.fitTOS

		print 'Fitting  i) TISTOS yield'
		self.fitTISTOS = B.DoubleGaussian(self.tree,massVar,cut+cs.Bs_cut_TIS+cs.Bs_cut_TOS)
		suf = 'TISTOS_'+sufId
		fitResultFile = 'Bs_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'

		#self.fitTISTOS.fitIfNotSaved({'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':opts.get('fitAnyhow',0)})
		self.fitTISTOS.fit({},8)
		self.fitTISTOS.plot(bins)

		#canvas.Print('TriggerEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_TISTOS_'+plotName+'.ps')
		canvas.Print('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TISTOS_'+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTISTOS.model.getParameters(self.fitTISTOS.data).writeToFile('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TISTOS_'+plotName+'_PARAMETERS.txt')

		self.N_tistos = valAndErr(self.fitTISTOS.nsig.getVal(), self.fitTISTOS.nsig.getError())
		del self.fitTISTOS

		print 'Fitting  i) TRIGGERED yield'
		self.fitTRIG = B.DoubleGaussian(self.tree,massVar,cut)
		suf = sufId
		fitResultFile = 'Bs_massFit_'+ massVar + '_' + self.nTupleName +'_'+str(suf)+'.root'

	#	self.fitTRIG.fitIfNotSaved({'fileName':fitResultFile, 'fitResultDir':resultDir, 'cpus':8, 'fitAnyhow':opts.get('fitAnyhow',0)})
		self.fttTRIG.fit({},8)
		self.fitTRIG.plot(bins)
		#canvas.Print('TriggerEffPlots/'+massVar+'_'+str(self.lumi.getVal())+'_TRIG_'+plotName+'.ps')
		canvas.Print('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TRIG_'+plotName+'.ps')
		#Save the fitted parameters to a file
		self.fitTRIG.model.getParameters(self.fitTRIG.data).writeToFile('TriggerEffPlots/'+massVar+'_'+self.nTupleName+'_TRIG_'+plotName+'_PARAMETERS.txt')

		print 'S:'
		self.N_trig = valAndErr(self.fitTRIG.nsig.getVal(), self.fitTRIG.nsig.getError())
		print 'B:'
		self.N_trig_bkg = valAndErr(self.fitTRIG.nbkg.getVal(), self.fitTRIG.nbkg.getError())

		# Signal / Background ratio
		print 'S/B:'
		self.SoverB = self.N_trig.over(self.N_trig_bkg)

		#Evaluate the trigger efficiency
		print 'TIS, TOS, and TRIG eff:'
		#TIS trigger efficiency
		print 'TIS eff:'
		isEff = True
		print 'N_tos: ', self.N_tos.getVal()
		print 'N_tistos: ', self.N_tistos.getVal()
		self.tisEff = self.N_tistos.over(self.N_tos, isEff)

		#TOS trigger efficiency
		print 'TOS eff:'
		print 'N_tistos: ', self.N_tistos.getVal()
		print 'N_tis: ', self.N_tis.getVal()
		self.tosEff = self.N_tistos.over(self.N_tis, isEff)

		#Total trigger efficiency
		print 'TRIG eff:'
		self.trigEff = self.tisEff.times( self.N_trig.over(self.N_tis) )

		#Signal and Background yields per pb
		print 'S/pb:'
		self.sig_yield_per_pb = self.N_trig.over( self.lumi.times(self.trigEff) )
		self.raw_sig_yield_per_pb = self.N_trig.over( self.lumi )
		print 'B/pb:'
		self.bkg_yield_per_pb = self.N_trig_bkg.over( self.lumi.times(self.trigEff) )


		#B mass error from 2 gaussians

		self.f = valAndErr(self.fitTRIG.f1.getVal(), self.fitTRIG.f1.getError())
		self.Bmass_mean = valAndErr(self.fitTRIG.mean1.getVal(), self.fitTRIG.mean1.getError())

		self.sigma1 = valAndErr(self.fitTRIG.sigma1.getVal(), self.fitTRIG.sigma1.getError())
		self.delta_s = valAndErr(self.fitTRIG.delta_s.getVal(), self.fitTRIG.delta_s.getError())
		self.sigma2 = self.sigma1.plus( self.delta_s )

		self.Bmass_sigma = ( ( self.f.times( self.sigma1.times(self.sigma1) ).plus(self.sigma2.times(self.sigma2)) ).minus( self.f.times(self.sigma2.times(self.sigma2)) ) ).sqrt()

		#Print the cuts
		print '-------------------------------------------------------'
		print '   Datasample:', self.nTupleName
		print '   Mass Variable:', massVar
		print '   Luminosity of the datasample:', self.lumi.getVal()
		print '-------------------------------------------------------'
		print '--Cuts used: ------------------------------------------'
		print '   TIS cut:', cut+'&&'+cs.Bs_cut_TIS
		print '   TOS cut:', cut+'&&'+cs.Bs_cut_TOS
		print '   TISandTOS cut:', cut + '&&' + cs.Bs_cut_TIS + '&&' + cs.Bs_cut_TOS
		print '------------------------------------------------------'
		print '  The fiducial cut used: ', cut
		print '   The N_tis: ', self.N_tis.getVal() ,' +- ', self.N_tis.getErr()
		print '   The N_tos: ', self.N_tos.getVal() ,' +- ', self.N_tos.getErr()
		print '   The N_tistos: ', self.N_tistos.getVal() ,' +- ', self.N_tistos.getErr()
		print "Bs-->JPsi Phi nSignal: ",self.N_trig.getVal() ," +- ", self.N_trig.getErr()
		print "             nBkg  : ", self.N_trig_bkg.getVal() ," +- ", self.N_trig_bkg.getErr()
		print "            and S/B: " , self.SoverB.getVal(), ' +- ', self.SoverB.getErr()
		print "             Signal yield per pb: ",self.raw_sig_yield_per_pb.getVal()," +- ",self.raw_sig_yield_per_pb.getErr()
		print '			LUMINOSITY UNCERTAINTY: ', self.lumiUnc
		print '------------------------------------------------------'

		#Print the trigger efficiencies
		print '------------------------------------------------------'
		print 'Trigger efficiency: ', self.trigEff.getVal(), ' +- ', self.trigEff.getErr()
		print '  tisEff = ', self.tisEff.getVal(), ' +- ', self.tisEff.getErr()
		print '  tosEff = ', self.tosEff.getVal(), ' +- ', self.tosEff.getErr()
		print '------------------------------------------------------'

		#Print the signal and background yields
		print "             Signal yield per pb: ", self.sig_yield_per_pb.getVal() ," +- ", self.sig_yield_per_pb.getErr()
		print "             Bkg    yield per pb: ", self.bkg_yield_per_pb.getVal() ," +- ", self.bkg_yield_per_pb.getErr()
		print '		NB! The Bmass mean error is the fit one, consider B_mass_sigma as uncertanity!'
		print '   Fitted Bs mass mean: ', self.Bmass_mean.getVal(), ' +- ', self.Bmass_mean.getErr()
		print '   Fitted Bs mass sigma: ', self.Bmass_sigma.getVal(), ' +- ', self.Bmass_sigma.getErr()
		print '------------------------------------------------------'

		return {'trigEff':self.trigEff.getVal(), 'trigEff_err':self.trigEff.getErr(), 'Nsig': self.N_trig.getVal() , 'Nsig_err': self.N_trig.getErr()}


