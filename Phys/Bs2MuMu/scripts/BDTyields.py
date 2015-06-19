from __future__ import division 
from ROOT import *
import cutStrings as cs
from readData import *
from valAndErr import *
from array import *
#Read in the datasets A and B  (name, channel)
#Define a cut to be used
#Count events in BDT bins
#Compare the count between two datasets

class BDTyields():
	
	def __init__(self , opts = {}):
		"""
		Options:
			'data' = ['a','b']
			'channel':'Bhh'
			'cut'= 	
		"""	
			
		#Create BDT histograms	
		self.bdt_bins = [0., 0.25 , 0.4 , 0.5 , 0.6 , 0.7 , 0.8 ,1.0]
		self.bins =  len(self.bdt_bins)
		self.h_list = []
		

		self.data = []
		self.var = 'bBDT05flat'
		self.cut = 'B_s0_M>4866&&B_s0_M<5866'
		#Import the datasets
		for d in opts.get('data'):
			t = readData(d,opts)
			self.data.append(t)	
			h = TH1D(d+'_hist', d+'_hist', self.bins-1, array('d',self.bdt_bins))
			t.get('tree').Draw(self.var+'>>'+d+'_hist',self.cut)	
			self.h_list.append(h)
			
		#Plot the histigrams
		#---------------#
		#Tweak the plotting
		gROOT.ProcessLine(".x $LHCBSTYLEROOT/src/lhcbStyle.C")
		gStyle.SetOptStat(kFALSE)
		gStyle.SetLabelOffset(0.01)	
		#gStyle.SetLineWidth(3)
		TGaxis.SetMaxDigits(4)
		
		#Create and modufy pads
		canv = TCanvas("Cut efficiency","Cut efficiency",800,600)	
		canv.SetFillColor(0)	
		
		#Add relative change plot |a-b|/a
		self.h_rel = TH1D(d+'_hist_rel', d+'_hist_rel', self.bins-1, array('d',self.bdt_bins))
		if len(self.data)==2:	
			for b in range(1,self.bins+1):
				a = valAndErr(self.h_list[0].GetBinContent(b),'P')
				b = valAndErr(self.h_list[1].GetBinContent(b),'P')
				rel = a.minus(b).over(a)	
				val = rel.getVal()	
				err = rel.getErr()	
				self.h_rel.SetBinContent(int(b),val)
				self.h_rel.SetBinError(int(b),err)
				
				#Create and modufy pads
				canv.Divide(1,2)
				canv.cd(1).SetPad(0.,0.2,1.,1.)	
				canv.cd(2).SetPad(0.,0.,1,0.2)	
				canv.cd(2)	
				h_rel.SetFillColor(9)	
				h_rel.SetLineColor(9)	
				h_rel.SetLineWidth(1)	
				h_rel.Draw('hist')

				canv.cd(1)	

		gPad.SetLogy()	
		self.h_list[0].Draw()
		for h in self.h_list:
			h.Draw('sameE')


		canv.SaveAs('VarPlots/bdtYields_MC/BDTyields.ps')		


