from ROOT import *
from readData import *
from array import *
import cutStrings as cs

def plotVarInFiles():

	files = [
		'2011',
		'2012_Strip19_a','2012_Strip19_b',
		'2012_Strip19a_a','2012_Strip19a_b','2012_Strip19a_c','2012_Strip19a_d','2012_Strip19a_e','2012_Strip19a_f',
		'2012_Strip19b_a','2012_Strip19b_b','2012_Strip19b_c','2012_Strip19b_d','2012_Strip19b_e',
		'2012_Strip19c_a','2012_Strip19c_b','2012_Strip19c_c','2012_Strip19c_d','2012_Strip19c_e','2012_Strip19c_f',
		]

	#files = ['2012_Strip19_a','2012_Strip19_b']
	#files = ['2012_Strip19_a']
	ch = 'Bu'

	# -------------------------------------------------------------------------------#
	#Define the vars and what you want to be plotted
	vars = []

	v = {'name':'nLongTrks', 'noSBsubtraction': True, 'binning':100,'vLow':0, 'vHi':500, 'plotAverage':True, 'setYRange':False, 'yTitle':'Mean_nLongTracks'}
	vars.append(v)
	v = {'name':'nLongTrks', 'noSBsubtraction': False, 'binning':100,'vLow':0, 'vHi':500, 'plotAverage':True, 'setYRange':False, 'yTitle':'Mean_nLongTracks_SBsubtr'}
	#vars.append(v)

	cutString = cs.Bu_cut_TOS
	v = {'name':'Bplus_M', 'noSBsubtraction': True,  'binning':100,'vLow':5100, 'vHi':5500, 'plotEventFractions':True, 'setYRange':False, 'cut':cutString, 'yTitle':'FracOf_TOS_events'}
	#vars.append(v)
	v = {'name':'Bplus_M', 'noSBsubtraction': False,  'binning':100,'vLow':5100, 'vHi':5500, 'plotEventFractions':True, 'setYRange':False, 'cut':cutString, 'yTitle':'FracOf_TOS_SBSubtr'}
	#vars.append(v)

	cutString = cs.Bu_cut_TIS
	v = {'name':'Bplus_M', 'noSBsubtraction':True, 'binning':100,'vLow':4900, 'vHi':5700, 'plotEventFractions':True, 'setYRange':False, 'cut':cutString, 'yTitle':'FracOf_TIS_events'}
	#vars.append(v)
	v = {'name':'Bplus_M', 'noSBsubtraction':False, 'binning':100,'vLow':4900, 'vHi':5700, 'plotEventFractions':True, 'setYRange':False, 'cut':cutString, 'yTitle':'FracOf_TIS_SBsubtr'}
	#vars.append(v)

	cutString = cs.Bu_cut_TIS + cs.Bu_cut_TOS
	#v = {'name':'Bplus_M', 'noSBsubtraction':True, 'binning':100,'vLow':4900, 'vHi':5700, 'plotEventFractions':True, 'setYRange':False, 'cut':cutString, 'yTitle':'FracOf_TIS&TOS_events'}
	#vars.append(v)
	v = {'name':'Bplus_M', 'noSBsubtraction':False, 'binning':100,'vLow':4900, 'vHi':5700, 'plotEventFractions':True, 'setYRange':False, 'cut':cutString, 'yTitle':'FracOf_TISTOS_SBsubtr'}
	#vars.append(v)

	# -------------------------------------------------------------------------------#
	data = []
	for f in files:
		d = readData(f,{'channel':ch})
		data.append(d)


	for i,v in enumerate(vars):
		canv = []
		n_tot = []
		hists = []
		for d in data:
			s = 0	# 0 picks the SB subtracted signal histogram
			if v.get('plotBkg',0): s = 1

			if v.get('plotEventFractions',0): 	# Get the total nr of event before cut
				h_tot = getSBSubtractedHist(d.get('tree'), v , 35, 70, '', ch, 100, true)
				n_tot.append(h_tot[s].GetEntries())

			h = getSBSubtractedHist(d.get('tree'), v , 35, 70, v.get('cut',''), ch, 100, true)
			hists.append(h[s])

		#Now do what you want with the histograms
		c = plotInBins(v,data,hists,n_tot)

		canv.append(c)

	print 'The end.'
	return canv


def getSBSubtractedHist(tree, var, sw_range = 35, sb_start = 70, cut = '', channel = 'Bu', mass_range = 100, sumw2 = true):

	res = [] #result
	h_sw = TH1D('h_sw', 'h_sw', var.get('binning',100), var.get('vLow',0), var.get('vHi',1000))
	h_sb = TH1D('h_sb', 'h_sb', var.get('binning',100), var.get('vLow',0), var.get('vHi',1000))

	if sumw2:
		h_sw.Sumw2()
		h_sb.Sumw2()


	fid_cut = cs.minimalNormBu_lnf

	cutVar = "&&fabs(Bplus_JCMass-5279.17)"
	if channel=='Bs' : cutVar = "&&fabs(B_s0_JCMass-5366.3)"
	if channel=='Bhh': cutVar = "&&fabs(B_s0_M-5366.3)"
	cutVar = fid_cut + cut + cutVar
	print '  THE CUT: ', cutVar

	if var.get('noSBsubtraction',0):
		print 'NO SUBTRACTION!'
		tree.Draw(var.get('name')+" >> h_sw", cutVar + '<'+str(mass_range))
		res = [h_sw,h_sw]
	else:
		print 'SUBTRACTION!'

		tree.Draw(var.get('name')+" >> h_sw", cutVar+'<'+str(sw_range))
		tree.Draw(var.get('name')+" >> h_sb", cutVar+'>'+str(sb_start))

		#Subtract the normalized number of projected backgrond events in the signal region
		#for the given variable.
		print 'Mass range :', mass_range

		m_sb_norm = (sw_range) / (mass_range - sb_start)
		print 'Scalefactor is %f' % m_sb_norm

		print "Cloning the h_sw:"
		h_sig = h_sw.Clone()
		h_sig.SetName('sig_hist')
		h_sig.Add(h_sb, -1*m_sb_norm)
		res = [h_sig,h_sb]


	return res


def plotInBins( v, data, hists, n_tot = 1):
	#Fill in an array with the averages and plot them

	labels = []
	x = []
	y = []
	ex = []
	ey = []
	bins = [0.]

	for i,f in enumerate(data):

		labels.append(f.get('name','noname')+'_'+str(f.get('lumi',0).getVal())+'pb')

		step = 100
		if v.get('weighBinWidthWithLumi',0): step = f.get('lumi',0.).getVal()

		bins.append(bins[i]+step)
		#Calculate x
		x_val = bins[i] + (bins[i+1]-bins[i])/2
		x.append(x_val)
		print 'x=',x[i]
		ex.append(bins[i+1]-x_val)
		print 'ex=',ex[i]

		if v.get('plotAverage',0):
			print 'Mean values:'
			y.append(hists[i].GetMean())
			print 'y=',y[i]
			ey.append(hists[i].GetMeanError())
			print 'ey=',ey[i]

		if v.get('plotEventFractions',0):
			print 'Event fractions:'
			n_cut = hists[i].GetEntries()
			frac = 	float(n_cut) / float(n_tot[i])
			print 'N_tot: ', n_tot[i], '  and N_cut: ', n_cut
			y.append(frac)
			print 'y=',y[i]
			ey.append(0.)
			print 'ey=',ey[i]

		bins[i+1]+=50 #to separate the bins

	bins[0]-=20 #to separate first bin from the axis

	n = len(x)
	gr = TGraphErrors(n,array('d',x),array('d',y),array('d',ex),array('d',ey))

	#Build and plot the Graph
	gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
	gStyle.SetFillStyle(4000)
	gStyle.SetLabelOffset(0.02)

	#c1 = TCanvas("c1","The yields per pb",200,10,700,500)
	c = TCanvas("c","The yields per pb",1200,600)
	gPad.SetRightMargin(0.2)
	gPad.SetBottomMargin(0.25)

	gr = TGraphErrors(n,array('d',x),array('d',y),array('d',ex),array('d',ey))

	#Mess around with the axis
	#Add the binning and labels
	gr.GetXaxis().Set(n,array('d',bins))
	for i,l in enumerate(labels): gr.GetXaxis().SetBinLabel(i+1,l)
	gr.GetXaxis().LabelsOption('d')
	gr.GetXaxis().SetTickLength(0.)

	if v.get('setYRange',0): gr.GetYaxis().SetRangeUser(v.get('setYRange')[0] , v.get('setYRange')[1])

	gr.GetYaxis().SetTitle(v.get('yTitle',''))

	gr.SetMarkerColor(2)
	gr.SetMarkerStyle(20)

	#Store
	gr.Draw('AP')
	c.Print('../../../VarPlots/2012_1109pb/'+v.get('yTitle')+'.ps')

	return [c, gr]

