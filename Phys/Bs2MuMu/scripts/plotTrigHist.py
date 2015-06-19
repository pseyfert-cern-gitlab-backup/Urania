#------------------------------#
# Author: Siim Tolk (NIKHEF)
#------------------------------#


#Needed in general
from ROOT import *
from operator import itemgetter
import os
#--------------------------------------------------#
#From BsMuMu package
from valAndErr import *
from readData import *
#--------------------------------------------------#

##########################################################################################################
##########################################################################################################
## CONFIGURE THE TRIGGER HISTOGRAMS
##########################################################################################################
##########################################################################################################

def getTrigHistsInPeriod(nTupleName):

	# Output directory
	dire = 'TriggerHistograms/'

	channel = 'Bu'
	base = 'Bplus' #The beginning of the trigger lines

	#Which trigger levels to plot
	trig=['L0','Hlt1','Hlt2']

	#Print the top lines or predefined list?
	#(the list can be predefined in plotTrigHist::defineVars())
	topLines = True
	#The number of most popular lines
	nTop = 10

	# The following loop will plot for each data file a trigger plot:
	# a) The overal top _nTop_
	# b) A plot with defined lines for triggers in _trig_ separately
	# c) A plot with top _nTop_ trigger lines for triggers in _trig_ separately

	print '---> File:', nTupleName
	if topLines: print '		---> top Lines:', nTop
	else: print ' Plotting predefined list of trigger lines.'

	for t in trig:
		print '		---> Trigger:', t
		#To get the nTop lines for all the trigger levels together, use
		#p = plotTrigHist({'nTupleName':str(nTupleName), 'channel':channel, 'nTop': nTop, 'base':base,'topLines':True})

		#To get the nTop lines for levels in triggers[] separately
		p = plotTrigHist( {'nTupleName':str(nTupleName), 'channel':channel, 'topLines':topLines, 'nTop': nTop, 'base':base, 'trig':t, 'directory':dire} )
		del p

##########################################################################################################
##########################################################################################################


class plotTrigHist():

	def __init__(self, opts={'channel':'Bu' , 'topLines':False, 'base':'Bplus', 'trig':'L0'}):

		self.dire = opts.get('directory','')
		self.nTupleName = opts.get('nTupleName','none')
		self.channel = opts.get('channel','Bu')
		print self.nTupleName
		#--------------------------------------------------#
		#Substitute here your own code for reading a nTuple
                self.dictData = readData(self.nTupleName,{'channel':self.channel, 'applyCut':True}) #ApplyCut applied the runNr cuts defined for GoodITRuns for example
		self.tree = self.dictData.get('tree',0.)
		self.lumi = self.dictData.get('lumi',0.)
		#--------------------------------------------------#

		if opts.get('topLines',0):
			#For making histograms from the most popular lines:
			nTop = opts.get('nTop',5)
			trigStr = opts.get('trig','All')
			self.suf = '_top'+str(nTop)+'LinesFor_'+str(trigStr)
			self.varDict = self.getTopVarDict(opts)
		else:
			#For making histograms from defined lines:
			self.suf = '_'+opts.get('trig','L0')
			self.varDict = self.defineVars(opts)


		self.activateBranches(self.varDict)
		self.hists = self.fillHistogram(self.varDict)
		self.drawHistogram(self.varDict,self.hists)




	def defineVars(self,opts):
		'''Define the dictionary 'varDict' of trigger lines to be looked for in the nTuple'''
		#-----------------------------------------------------------------------------------------#
		base = opts.get('base','')
		trig = opts.get('trig',0)

		#Common suffix for all the triggers
		commonLines = ['Global']

		L0Lines = ['MuonDecision','DiMuonDecision','HadronDecision','ElectronDecision','PhotonDecision']
		Hlt1Lines = ['Phys','SingleMuonHighPTDecision','TrackMuonDecision','DiMuonHighMassDecision','DiMuonLowMassDecision','TrackAllL0Decision']
		Hlt2Lines = ['Phys','SingleMuonDecision',
				'Topo2BodyBBDTDecision','Topo3BodyBBDTDecision',
				'TopoMu2BodyBBDTDecision','TopoMu3BodyBBDTDecision']


		triggers = {	'L0'	:	commonLines + L0Lines} #Default
		if trig == 'Hlt1' : triggers = {'Hlt1': commonLines + Hlt1Lines}
		if trig == 'Hlt2' : triggers = {'Hlt2': commonLines + Hlt2Lines}

		#Make individual histograms for each decision:
		decisions = {'Dec':'_Dec', 'TOS':'_TOS', 'TIS':'_TIS'}
		#decisions = {'TOS':'_TOS', 'TIS':'_TIS'}

		#-----------------------------------------------------------------------------------------#
		#Putting it all together in varDictionaries

		varDict = dict.fromkeys(decisions) #Define empty dictionary with the keys from decisions
		for decision in decisions:
			varDict[decision] = []
			for trig, line in triggers.iteritems():
				for lineItem in line:
					var = base + trig + lineItem + decisions.get(decision)
					print 'Built line name: ',var
					varDict[decision].append(var)

			print '		Lines for ', decision, ' added.'


		varDict.items()
		return varDict



	def getTopVarDict(self, opts):
		'''Get the top _nTop_ trigger line names containing _triggers_ for _Dec and return a sorted dictionary 'varDict' with 'types' as keys and lines as values. '''
		#This is just a wrapper around getTopTriggerDecLineRoots and gives
		#the output varDict a proper format.
		print 'Get the top Lines.'

		#Get the top lines:
		topLineRoots = self.getTopTriggerDecLineRoots(opts)


		#Edit the top line names for filling the histograms:
		types = {'Dec':'_Dec','TOS':'_TOS','TIS':'_TIS'}
		topLines = dict.fromkeys(types)
		for type in types:
			topLines[type] = []
			for root in topLineRoots:
				topLines[type].append(root+types[type])
		#Return topLines as a varDict to be plotted
		return topLines

	def getTopTriggerDecLineRoots(self,opts):
		'''Get the list of branches containing triggers=['a','b',...]'''

		end = opts.get('end','_Dec')	#Select only lines with '_Dec' ending by default
		triggers = ['L0','Hlt1','Hlt2'] #Be default, get the overal top lines fo all the triggers.
		if opts.get('trig'): triggers = [opts.get('trig')]

		base = opts.get('base','')
		nTop = opts.get('nTop',5)


		totBrList = self.tree.GetListOfBranches()
		brLineCount = {}

		for br in totBrList:
			for trig in triggers:
				brName = br.GetName()
				brName_end = '' #Pick only the end, as __Decision might also be in the middle of the name
				for x in range( len(brName)-4, len(brName)): brName_end += brName[x]

				if (brName.find(str(base+trig)) > -1) and (brName_end.find(end)>-1): #If the line name is the one we want
					#Fill in the dictionary with the name and count
					brLineCount[brName] = int(br.GetTree().GetEntries( brName+'==1'))

		#Sort the dictionary from highest to lowest count
		print 'Before sorting:'
		print brLineCount
		print '...sorting...'
		sortedBrLineCount = sorted(brLineCount.items(),key=itemgetter(1),reverse=True)
		print 'After sorting:'
		for line in sortedBrLineCount: print line
		#Select the topN lines, and remove the _Dec ends
	       	topLines = []
		n = 0
		for key in sortedBrLineCount:
			print 'Key is:', key
			if n<nTop and key[0].find('_Dec')>0:
				line_name = ''
				for x in  range(0,len(str(key[0]))-4): line_name += str(key[0])[x]
				print '     Line name included: ', line_name

				topLines.append(line_name)

			n+=1

		return topLines


#-------------------------------------------------------------------------------------------------------------------#

	def activateBranches(self, varDict):

		#Activate the branches that will be added to the x axis bins
		self.tree.SetBranchStatus("*",0)

		for type,varList in varDict.iteritems():

			for varName in varList:
				self.tree.SetBranchStatus(varName,1)
				print 'Branch: ',varName
				print '							set ACTIVE!'


		print '		--------------------'
		print ' Start looping...'

	def fillHistogram(self, varDict):

		print 'Filling the histograms bins on the x axis by looping over the events..'

		nEntries = self.tree.GetEntries()

		hists = dict.fromkeys(varDict) #Define empty dictionary with the keys from decisions
		for decision,varList in	varDict.iteritems():
			#Create a histogram for each decision type

			self.nbins = len(varList)
			hists[decision] = (TH1F(decision+'_hist', decision + ' histogram',self.nbins,0,self.nbins))

		# Fill the histograms:
		for entry in range(nEntries):
			self.tree.GetEntry(entry)
			#Go through the varDict and fill in the variables that are equal to 1
			for decision,varList in varDict.iteritems():
				for i,varName in enumerate(varList):
					#For each decision type:
					if getattr(self.tree,varName):
						hists[decision].Fill(i)

		print 'Histograms filled! Call drawHistrogram'
		return hists

	def drawHistogram(self,varDict, hists):

		gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
		color = {'Black' : 1, 'Red': 2,  'Green':3, 'Blue':4, 'Yellow':5 }
		j = 1 #Color counter

		#Define the order according to which the histograms will be plotted
		order = ['Dec','TOS','TIS']
		#order = ['TOS','TIS']

		self.canv = TCanvas('canvas','canvas',900,600)
		self.canv.SetFillColor(0)
		#Add legend
		self.leg = TLegend(0.72,0.72,0.92,0.92)
		self.leg.SetHeader(self.nTupleName)
		self.leg.SetFillColor(0)
		self.leg.SetBorderSize(1)
		TGaxis.SetMaxDigits(3)

		for type in order:
			print 'Draw type:', type
			#Set bin labels for the histogram
			for bin in range(1,self.nbins+1):
				#Set names without the Dec, TIS, TOS ending
				line = varDict[type][bin-1]
				bin_label = ''
				for x in range(0,len(line)-4): bin_label += line[x]
				hists.get(type).GetXaxis().SetBinLabel(bin,bin_label)

			gStyle.SetOptStat(0)
			gStyle.SetHistFillColor(j)
			gStyle.SetLabelOffset(0.01)
			gStyle.SetLineWidth(3)
			#Increase the margins to accommodate trigger line names
			gPad.SetLeftMargin(0.10)
			gPad.SetRightMargin(0.35)
			gPad.SetBottomMargin(0.25)
			gPad.SetFillColor(0)

			hists.get(type).SetTitle('')
			hists.get(type).SetMinimum(0)
			hists.get(type).UseCurrentStyle()
			self.leg.AddEntry(self.hists.get(type),str(type),'f')

			if j==1:
				print 'Without same.'
				hists.get(type).Draw()
			else:
				print 'With same.'
				hists.get(type).Draw('same')
			j+=1

		print 'Print the legend: '
		self.leg.Draw('br same')

                #Check if dir exists:
                if not os.path.exists(self.dire): os.makedirs(self.dire)

		self.canv.Print(self.dire + 'TrigHist_'+self.nTupleName+self.suf+'.ps')
		return 1




