from ROOT import *
from readData import *
import cutStrings as cs

def compVarPerChannel(i):


	files = ['2011','2012_56','2012_159', '2012_195' , '2012']	

	#Define the channels to comapre	
	#channels = ['Bu','Bs']
	channels = ['Bu']
	dataFiles = defineDataFiles(files[i],channels)

	#-------------------------#
	#Declare a varDict for each comparison you want to make and add it to the list of varDict's
	varDict_list = []	
	
	cut_Bu = cs.minimalNormBu_lnf
	cut_Bs = cs.normBs_lnf 
	
	varDict = {'var':['J_psi_1S_P','J_psi_1S_P'], 'cut':[cut_Bu,cut_Bs], 'plotTitle':'JPsi momentum','bins':100,'min':0,'max':600000,
		'setLog':False,'plotRatio':False,'plotNamePrefix':'compVarInChannels_'}
	#varDict_list.append(varDict)
	varDict = {'var':['J_psi_1S_PT','J_psi_1S_PT'], 'cut':[cut_Bu,cut_Bs], 'plotTitle':'JPsi PT : PIDK on Bs->JpsiPhi','bins':100,'min':0,'max':40000,
		'setLog':False,'plotRatio':False,'plotNamePrefix':'compVarInChannels_'}
	#varDict_list.append(varDict)
	#-------------------------#
	#P and PT with the PIDK cut on Bs
	cut_Bu = cs.minimalNormBu_lnf
	cut_Bs = cs.normBsPID_lnf 
	varDict = {'var':['J_psi_1S_P','J_psi_1S_P'], 'cut':[cut_Bu,cut_Bs], 'plotTitle':'JPsi momentum:PIDK Bs->JpsiPhi','bins':100,'min':0,'max':600000,
		'setLog':False,'plotRatio':False,'plotNamePrefix':'compVarInChannels_PIDK_onBs_'}
	#varDict_list.append(varDict)

	varDict = {'var':['J_psi_1S_PT','J_psi_1S_PT'], 'cut':[cut_Bu,cut_Bs], 'plotTitle':'JPsi PT','bins':100,'min':0,'max':40000,
		'setLog':False,'plotRatio':False,'plotNamePrefix':'compVarInChannels_PIDK_onBs_'}
	#varDict_list.append(varDict)
	#-------------------------#
	#P and PT with the trigger cut on both
	cut_Bu = cs.minimalNormBu_lnf + cs.Bu_Jpsi_Hlt2
	cut_Bs = cs.normBs_lnf + cs.Bs_Jpsi_Hlt2 

	varDict = {'var':['J_psi_1S_P','J_psi_1S_P'], 'cut':[cut_Bu,cut_Bs], 'plotTitle':'JPsi momentum: JpsiHlt2','bins':100,'min':0,'max':600000,
		'setLog':False,'plotRatio':False,'plotNamePrefix':'compVarInChannels_JpsiHlt2_'}
	varDict_list.append(varDict)

	varDict = {'var':['J_psi_1S_PT','J_psi_1S_PT'], 'cut':[cut_Bu,cut_Bs], 'plotTitle':'JPsi PT : JpsiHlt2','bins':100,'min':0,'max':40000,
		'setLog':False,'plotRatio':False,'plotNamePrefix':'compVarInChannels_JpsiHlt2_'}
	varDict_list.append(varDict)
	#-------------------------#

	cut_Bu = cs.minimalNormBu_lnf + cs.Bu_Jpsi_Hlt2
	cut_Bs = cs.normBsPID_lnf + cs.Bs_Jpsi_Hlt2 

	varDict = {'var':['J_psi_1S_P','J_psi_1S_P'], 'cut':[cut_Bu,cut_Bs], 'plotTitle':'JPsi momentum: JpsiHlt2 & PIDK on Bs','bins':100,'min':0,'max':600000,
		'setLog':False,'plotRatio':False,'plotNamePrefix':'compVarInChannels_JpsiHlt2_PIDK_onBs_'}
	varDict_list.append(varDict)

	varDict = {'var':['J_psi_1S_PT','J_psi_1S_PT'], 'cut':[cut_Bu,cut_Bs], 'plotTitle':'JPsi PT: JpsiHlt2 & PIDK on Bs','bins':100,'min':0,'max':40000,
		'setLog':False,'plotRatio':False,'plotNamePrefix':'compVarInChannels_JpsiHlt2_PIDK_onBs_'}
	varDict_list.append(varDict)
	#-------------------------#

	for varD in varDict_list:
		print 'Getting hists for: ', varD.get('var','none')	
		hist_list = getVarHists(varD, dataFiles, channels, files[i])
		canvas = plotVars(hist_list,varD,dataFiles,channels,files[i])
		

def defineDataFiles(file, channels):
	#Trees per channel  
	data_ch = []	
	dataFiles = {}
	for ch in channels:	
		tree = readData(file,{'channel':ch}).get('tree')
		#print 'tree copied:', t.Print(), '  _end of Print Tree.'
		print 'Datafiles for channel:',ch,' read in!'
		dataFiles[file+'_'+ch]=tree

	return dataFiles


def getVarHists(varDict, dataFiles, channels, file):
	'''Returning histograms for a given set of variables in given set of trees. VarDict = {'var','bins','min','max','log','plotRatio','plotNamePrefix'i,'plotDir'}
	   dataFiles is also a dictionaty with the file year_lumi_channel as a label.'''
	
	var = varDict.get('var','noVariableDefined')
	cut = varDict.get('cut','noVariableDefined')
	min = varDict.get('min',0)
	max = varDict.get('max',10000)
	bins = varDict.get('bins',100)
	
	#print 'Getting the histograms for var:', var

	hist_list = []
	for i,ch in enumerate(channels):	
		print 'Getting histogram for:', ch+file
		hist = TH1D('h_'+str(i), 'h_'+str(i), bins, min, max)
		print 'Using cut:', cut[i]	
		dataFiles[file+'_'+ch].Draw( var[i]+" >> h_"+str(i), cut[i])
		hist_list.append(hist)
	
	return hist_list


def plotVars(hist_list, varDict, dataFiles, channels, file):
	'''Plot the variable histograms inside hist_list, which is a list of histograms'''
	
	var = varDict.get('var','noVariableDefined')
	#Find the largest value for Y
	maxY = 0	
	
	#This does not work..	
	for hist in hist_list:
		if hist.GetBinContent(hist.GetMaximumBin())> maxY : 
			maxY = hist.GetBinContent(hist.GetMaximumBin())
			print 'The maximum Y : ', maxY	
			tot =  hist.GetEntries()
			print 'The total : ', tot	
			
	maxY = 1.2*maxY
	print 'The maximum Y will be set to(1.2x) : ', maxY	
	
	color = 1	
	var = varDict.get('var','noVariableDefined')
	canvas = TCanvas(var[0]+'_canv',var[0]+'_canv')	

	for hist in hist_list:
		print 'color = ' , color	
		#Configure the plotting style
		#---------------------------#
		option = 'HIST'	
		gStyle.SetFillStyle(4000)	
		gStyle.SetOptStat(kFALSE); 
		gStyle.SetLineWidth(3); 
		hist.SetTitle(varDict.get('plotTitle',''))	
		hist.SetLineWidth(4)	
		hist.SetLineColor(color)	
		hist.SetMaximum(maxY)
		if varDict.get('setLog',False): gPad.SetLogy()	
		#---------------------------#
		if color > 1: 
			print 'Plotting with SAME option'	
			hist.DrawNormalized(option+'SAME',1) 
		else: 
			print 'Plotting first time..'
			hist.DrawNormalized(option,1)
	
		color+=1

		#Add the hist to the legend
	
	#Add a legend 
	leg = TLegend(0.6,0.75,0.9,0.9)

	for i,f in enumerate(channels):	
		print 'Adding:', f, var[i]
		leg.AddEntry(hist_list[i], f+' '+var[i])
	
	#leg.Draw('same')
	leg.Draw()

	#Save the plot
	name_suf = '_'
	for name in dataFiles: name_suf += name +'_'

	plotDir = varDict.get('plotDir','VarPlots/CompVarsInCh/')
	prefix = varDict.get('plotNamePrefix','compVarInChannels_')
	canvas.Print(plotDir+prefix+str(var[0])+name_suf+'.ps')

	#colors=['Black','Red','Green','Blue','Yellow','Purple','LightBlue']
	#text = TPaveText(0.7,0.9,0.6,0.89)
	#for i,f in enumerate(dataFiles):	
	#	text.AddText(f+' '+var[i]+' : '+colors[i])
	#text.Draw('SAME')


	return canvas
	




