from ROOT import *
from array import *
from valAndErr import *
import os
#For the screen turn off the whistles
gROOT.SetBatch(True)

#This file contains code for reading the mass fit result fiels,
#getting the variables and plotting them on a single plot for comparison

# The plotting is called from plotYiedlds2011.py or ..2012.py

def addFiles(directory,channel,entries, tr_level, mass_var):

        #---------------------------------------------#
        #-- Get the file names for the nTuples -------#
        #---------------------------------------------#
        print ' o) Get the file names for the neede nTuples'
        for f in os.listdir(directory+channel):
                if tr_level in f and mass_var in f and 'FitInfo' in f:
                        for e in entries:
                                print ' Trying: ',f
                                if e.get('nTupleName') in f: e['file'] = f

        print ' o) The list of files selected:'
        print '   Entries will be read from the files: '
        for e in entries:
            print ' For nTuple: ',e.get('nTupleName')
            print e.get('file')

        return entries

def readVars(directory,channel,entries):


        #-----------------------------------------#
        #-- READ THE YIELDS FROM THE FILES -------#
        #-----------------------------------------#
        for e in entries:
                f = e.get('file')
                lines = open(str(directory+channel)+'/'+str(f), 'r').read().split('\n')

                # Luminosity in pb :  244.5  +-  12.225
                for l in lines:
                        if 'Luminosity in pb' in l:
                                val = float(l.split(':')[1].split('+-')[0])
                                err = val * float(e.get('lumiUnc',0.))
                                lumi = valAndErr(val, err)
                                e['lumi'] = lumi

                # N_sig :  85338.6017779  +-  317.058314102
                for l in lines:
                        if 'N_sig' in l:
                                val = float(l.split(':')[1].split('+-')[0])
                                err = float(l.split(':')[1].split('+-')[1]) #This is the fit error!
                                n_sig_raw = valAndErr(val, 'P').plus(valAndErr(0., err)) #Add fit and poissonian errors
                                e['n_sig_raw'] = n_sig_raw
                                n_sig = n_sig_raw.over(e.get('eff_cor'))
                                e['n_sig_cor'] = n_sig #corrected for eff_cor
                                e['n_sig_raw_perpb'] = n_sig_raw.over(e.get('lumi'))
                                e['n_sig'] = n_sig_raw.over(e.get('eff_cor')).over(e.get('lumi')) #corrected n_sig per pb


        print ' o) Entries to be plotted:'
        for e in entries: print e

        return entries


def plotVarInEntries(var, entries, plotOpts):
        #Loop over the points and fill the info
	labels = []; x = []; y = []; ex = []; ey = []

        bins = [0.]
        # Get the labels for the x axis
        # Set the bin sizes according to the luminosity within each bin


        for i,f in enumerate(entries):
	        if f.get('type') is 'point':
                        labels.append(f.get('nTupleName','noname')+'_'+str(f.get('lumi',0).getVal())+'pb')
                        bins.append(bins[i]+f.get('lumi',0.).getVal())
                        # Calculate x
                        x_val = bins[i] + (bins[i+1]-bins[i])/2
                        x.append(x_val)
                        print 'x=',x[i]
                        ex.append(bins[i+1]-x_val)
                        print 'ex=',ex[i]
                        y.append(f.get(var).getVal())
                        print 'y=',y[i]
                        ey.append(f.get(var).getErr())
                        print 'ey=',ey[i]
                        bins[i+1]+=50 #to separate the bins

	bins[0]-=20 #to separate the bins
	n = len(x)

	#Build and plot the Graph
	gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
	gStyle.SetFillStyle(4000)
	gStyle.SetLabelOffset(0.02)

	#c1 = TCanvas("c1","The yields per pb",200,10,700,500)
	c1 = TCanvas("c1","The yields per pb",1200,600)
	gPad.SetRightMargin(0.23)
	gPad.SetBottomMargin(0.4)

	gr = TGraphErrors(n,array('d',x),array('d',y),array('d',ex),array('d',ey))


	#Mess around with the axis
	#Add the binning and labels
	gr.GetXaxis().Set(n,array('d',bins))
	for i,l in enumerate(labels): gr.GetXaxis().SetBinLabel(i+1,l)
	gr.GetXaxis().LabelsOption('d')
	gr.GetXaxis().SetTickLength(0.)
	gr.GetXaxis().SetLabelSize(0.06)

        y_title = plotOpts.get('yTitle')
        y_range= plotOpts.get('yRange')

	gr.GetYaxis().SetRangeUser(y_range[0], y_range[1])
	gr.GetYaxis().SetTitle(y_title)
	gr.GetYaxis().SetTitleSize(0.06)
	gr.GetYaxis().SetLabelSize(0.06)

	gr.SetMarkerColor(1)
	gr.SetMarkerStyle(20)

	#Draw the benchmark lines
	leg = TLegend(0.4,0.70,0.70,0.92)
        leg.SetHeader(plotOpts.get('channel','No channel'))
	leg.SetFillStyle(0)
	leg.SetTextSize(0.04)
	gr.Draw('AP')
	leg.AddEntry(gr,y_title,'lep');

	m_store = [] #so we see everything also on the popup graph

	for i,b in enumerate(entries):
	        if b.get('type') is 'line':
                        mean = b.get(var).getVal()
                        err = b.get(var).getErr()
                        m_plus = TLine(bins[0], mean+err, bins[n], mean+err)
                        m = TLine(bins[0], mean, bins[n], mean)
                        m_min = TLine(bins[0], mean-err, bins[n], mean-err)
                        color = b.get('color',1)
                        m.SetLineColor(color)
                        m_plus.SetLineColor(color)
                        m_min.SetLineColor(color)
                        m.SetLineWidth(3)
                        m_plus.SetLineWidth(1)
                        m_min.SetLineWidth(1)
                        m_plus.SetLineStyle(3)
                        #m.SetLineStyle(2)
                        m_min.SetLineStyle(3)
                        m.Draw('SAME')
                        m_plus.Draw('SAME')
                        m_min.Draw('SAME')

                        leg.AddEntry(m,b.get('nTupleName'),'l')

                        m_store.append(m)
                        m_store.append(m_plus)
                        m_store.append(m_min)

	#ReDraw point on the benchmark lines
	gr.Draw('PSAME')
	leg.Draw('same')

	#Store
	#c1.Print(dir+plotName+'.ps')
	c1.SaveAs(plotOpts.get('plotName','yields')+'.ps')


