from ROOT import *
from readData import *

def plotAllRuns(channel,files = [], plotName = 'runNumbers_'):

	#files = ['2012_Strip19abc','2012_Strip19','2012_Strip19a','2012_Strip19b_abc','2012_Strip19b_d']
	#files = ['2012','2012_Strip19','2012_Strip19a','2012_Strip19b']

#	files = ['2012',
#		'2012_Strip19_a','2012_Strip19_b',
#		'2012_Strip19a_a','2012_Strip19a_b','2012_Strip19a_c','2012_Strip19a_d','2012_Strip19a_e','2012_Strip19a_f',
#		'2012_Strip19b_a','2012_Strip19b_b','2012_Strip19b_c','2012_Strip19b_d','2012_Strip19b_e']

	#files = ['2012',
	#	'2012_Strip19',
	#	'2012_Strip19a',
	#	'2012_Strip19b',
	#	'2012_Strip19c']

	#files = ['2011',
#		'Strip20r1_71pb']
	#plotName = '2011_ReproRunNr_'

       # Reprocessed 2011 on old 2011
       # files = ['2011_Strip17',
       #         '2011_Strip20r1_A',
       #         '2011_Strip20r1_a','2011_Strip20r1_b','2011_Strip20r1_c','2011_Strip20r1_d','2011_Strip20r1_e','2011_Strip20r1_f',
       #         '2011_Strip20r1_g', '2011_Strip20r1_h', '2011_Strip20r1_i', '2011_Strip20r1_j', '2011_Strip20r1_k','2011_Strip20r1_l']

       # Reprocessed 2012
        files = ['2012_Strip20',
                '2012_Strip20_MagDown_a','2012_Strip20_MagDown_b','2012_Strip20_MagDown_c','2012_Strip20_MagDown_d','2012_Strip20_MagDown_e','2012_Strip20_MagDown_f',
                '2012_Strip20_MagDown_g', '2012_Strip20_MagDown_h', '2012_Strip20_MagDown_i', '2012_Strip20_MagDown_j', '2012_Strip20_MagDown_k',
                '2012_Strip20_MagUp_a','2012_Strip20_MagUp_b','2012_Strip20_MagUp_c','2012_Strip20_MagUp_d','2012_Strip20_MagUp_e','2012_Strip20_MagUp_f',
                '2012_Strip20_MagUp_g', '2012_Strip20_MagUp_h', '2012_Strip20_MagUp_i']

        c = TCanvas('runNumbers','runNumbers')

	gStyle.SetFillStyle(4000)
	gStyle.SetOptStat(kFALSE);
	leg = TLegend(0.65,0.60,0.89,0.89)
        leg.SetLineWidth(0)
        leg.SetLineColor(4000)
        leg.SetFillColor(4000)
        option = 'HIST'

        #Set the rotation in space
        #option = 'LEGO1'
        #gPad.SetFrameFillColor(0)
        #gPad.SetTheta(3.77)
        #gPad.SetPhi(2.9)

        color = 1
	hists = []
	bins = 200

	#get max and min run numbers
	limits = getMaxMin(files[0], channel)
	min = round(limits[0]-300,-2)
	max = round(limits[1]+300,-2)

	#min = 111000
	#max = 130000

	print 'The limiting run mumbers:', min, ' , ', max

	#Make an array of histograms to store them
	for f in files:
		hist = getRunNrHist(f,channel, bins, min, max)
		hists.append(hist)

	#get maximum y value
	maxY = 1.4 * getMaxY(hists)
        stack = THStack('SubSamples','Stacked subsample histograms')

	for i,hist in enumerate(hists):
		print 'color=', color
		#Configure the plotting style
		#---------------------------#
		hist.SetLineWidth(3)
		hist.SetLineColor(color)
		hist.SetTitle('')
		hist.SetFillColor(color)
		hist.SetMaximum(maxY)
                #---------------------------#
		if color > 1:
			print 'Adding the histograms to a TStack'
			#hist.DrawCopy(option+'SAME')
                        stack.Add(hist)
                else:
			print 'Plotting first time..'
			hist.DrawCopy(option)
			print 'Min max X bins =', min, ' , ', max, '' , bins

		leg.AddEntry(hist,files[i]+' '+ channel,'l');
		color+=1

        stack.Draw(option+'SAME')
	leg.Draw('SAME')


	#Draw lines where the bad runs are at
	#start = 124272
	#end = 124505

	#start =129534
	#end = 129538

	#40000 for Bu, 4000 for Bs

	#line_1 = TLine(start, 0, start, 4000)
	#line_2 = TLine(end, 0, end, 4000)
	#line_1.SetLineColor(2)
	#line_2.SetLineColor(2)
	#line_1.SetLineWidth(4)
	#line_2.SetLineWidth(4)
	#line_1.Draw('SAME')
	#line_2.Draw('SAME')

	directory = 'runNrPlots/'
        if not os.path.exists(directory): os.makedirs(directory)
        c.Print(directory+plotName+channel+'.ps')

	return '-- THE END --'


def getMaxY(h_list):
	maxY = 0
	for hist in h_list:
		print 'hist max = ', hist.GetName(),' , ', hist.GetMaximum()
		if hist.GetMaximum()> maxY :
			maxY = hist.GetMaximum()
	print '    The maximum of the plot is :', maxY
	return maxY


def getMaxMin(nTupleName, channel):
	t = readData(nTupleName, {'channel':channel}).get('tree')
	min = t.GetMinimum('runNumber')
	max = t.GetMaximum('runNumber')
	return [min,max]


def getRunNrHist(nTupleName, channel, bins, min, max):

	gStyle.SetFillStyle(4000)
	gStyle.SetOptStat(kFALSE);
	t = readData(nTupleName, {'channel':channel}).get('tree')
	plotName = nTupleName +'_'+channel+'_runNumbers'

	hist = TH1D(nTupleName+'_hist', nTupleName+'_hist', bins, min, max)
	t.Draw('runNumber >>'+nTupleName+'_hist')
	#t.Draw('runNumber >> hist')
	return hist


