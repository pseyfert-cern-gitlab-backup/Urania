#********************************************************************
#
# DESCRIPTION: script used to obtain a parametrization for the decay
# time resolution.
# AUTHOR: Julian Garcia Pardinhas, julian.garcia.pardinas@rai.usc.es
# UNIVERSITY: Universidade de Santiago de Compostela
# DATE: 02/2015
#
#********************************************************************

from GetResInterface import *


# ################################################################
# G L O B A L   O P T I O N S
# ################################################################

# MC data used to obtain the decay time error distributions.
data_file = 'AnalysisOutWSWeightsSelectedAllBranchesNew.root'#'AnalysisOutWithCuts_AllBranches_PHIstudy.root'
data_tree = 'AnalysisTree'
MC_datatype = 2 # 0 for PhSp only, 1 for VV only, 2 for both
evnum_limit = 0

# Binning in deltat.
nbins_deltat_fit = 20

# Binning of t_err for the parametrization study.
bin_sim = 10

# Parametrization of the time resolution as a function of the decay time error.
pol_order = 1
q0_term = 1
mean_offset = 0

# Plots of the decay time resolution.
nbins_difft = 20
nbins_deltat = 20


# ################################################################
# D E C A Y   T I M E   E R R O R   F I T
# ################################################################

def Fit1DRes():

	# Data importation.
	LoadData_1D(data_file,data_tree,MC_datatype,evnum_limit)

	# Fit of the 1D effective PDF to data.
	fit_list = Fit1DPDF(mean_offset)

	# Plot the 1D model and data distributions.
	Make1DPlot(nbins_difft)

	# Print the resulting sigma_eff.
	printSigmaEff(*fit_list)

	# Print the resulting parameters.
	PrintTReseffPars()

"""def FitSim():

	# Defining different parameters for each bin.
	sim_pars = DefineParams(bin_sim)

	# Created separated datasets per bin.
	#FitMargPDF()
	binning_2011, binning_2012 = GetBinning(bin_sim)
	CreateDatasets(bin_sim)
	LoadData_sim(data_file,data_tree,MC_datatype,evnum_limit,binning_2011,binning_2012)"""

def Fit2DRes():

	# Data importation.
	LoadData_2D(data_file,data_tree,MC_datatype,evnum_limit)
	
	# Creation of a marginal PDF for the decay time error.
	FitMargPDF()

	# Fit of the 2D PDF to data.
	fit_list = Fit2DPDF(pol_order,q0_term,mean_offset)

	# Plot of the 2D model and data distributions.
	Make2DPlot(nbins_difft,nbins_deltat)

	# Print out of the resulting parameters.
	PrintTResPars()

def FitBins():

	# Data importation.
	LoadData_2D(data_file,data_tree,MC_datatype,evnum_limit)
	
	# Binning construction.
	boundlist = map(lambda d:adaptiveBinning(deltat,nbins_deltat_fit,0,d),[data_2011_wide,data_2012_wide,data_2011_narrow,data_2012_narrow])

	# Fit in bins of deltat.
	sigma = ROOT.RooRealVar("sigma","sigma",0.04,0.,0.1)
	g = ROOT.RooGaussian("g","g",difft,ROOT.RooFit.RooConst(0.),sigma)

	datalist = [data_2011_wide,data_2012_wide,data_2011_narrow,data_2012_narrow]
	bincenterlist = [[],[],[],[]]
	binerrlist = [[],[],[],[]]
	sigmalist = [[],[],[],[]]
	sigmaerrlist = [[],[],[],[]]
	for idataset in range(4):
		for ibin in range(nbins_deltat_fit):
			d = datalist[idataset].reduce(ROOT.RooArgSet(difft,deltat),"deltat>"+str(boundlist[idataset][ibin])+" && deltat<="+str(boundlist[idataset][ibin+1]))
			sigma.setVal(0.5*(boundlist[idataset][ibin]+boundlist[idataset][ibin+1]))
			g.fitTo(d,ROOT.RooFit.Minos(1))
			#fr = difft.frame()
			#d.plotOn(fr)
			#g.plotOn(fr)
			#c = ROOT.TCanvas("c","c")
			#fr.Draw()
			#c.Print("res_dataset"+str(idataset)+"_bin"+str(ibin)+".pdf")
			bincenterlist[idataset].append(0.5*(boundlist[idataset][ibin+1]+boundlist[idataset][ibin]))
			binerrlist[idataset].append(0.5*(boundlist[idataset][ibin+1]-boundlist[idataset][ibin]))
			sigmalist[idataset].append(sigma.getVal())
			sigmaerrlist[idataset].append(sigma.getError())

	tgraphlist = map(lambda xl,yl,xerrl,yerrl: ROOT.TGraphErrors(nbins_deltat_fit,array('d',xl),array('d',yl),array('d',xerrl),array('d',yerrl)),bincenterlist,sigmalist,binerrlist,sigmaerrlist)
	map(lambda gr:gr.GetXaxis().SetTitle("#delta_{t} (ps)"),tgraphlist)
	map(lambda gr:gr.GetYaxis().SetTitle("#sigma_{t} (ps)"),tgraphlist)

	leg11wide = ROOT.TLegend(0.6,0.7,0.95,0.9)
	leg11wide.SetFillColor(kWhite)
	leg11wide.SetBorderSize(0)
	leg11wide.SetHeader("2011 MC data")
	#leg11wide.AddEntry(fdifft11wide.findObject("h_data_difft_2011_wide"),"Data","epl")
	#leg11wide.AddEntry(fdifft11wide.findObject("res_eff_2011_wide_Norm[difft]"),"2-Gaussian fit","epl")
	leg12wide = ROOT.TLegend(0.6,0.7,0.95,0.9)
	leg12wide.SetFillColor(kWhite)
	leg12wide.SetBorderSize(0)
	leg12wide.SetHeader("2012 MC data")
	#leg12wide.AddEntry(fdifft12wide.findObject("h_data_difft_2012_wide"),"Data","epl")
	#leg12wide.AddEntry(fdifft12wide.findObject("res_eff_2012_wide_Norm[difft]"),"2-Gaussian fit","epl")
	leg11narrow = ROOT.TLegend(0.6,0.7,0.95,0.9)
	leg11narrow.SetFillColor(kWhite)
	leg11narrow.SetBorderSize(0)
	leg11narrow.SetHeader("2011 MC data")
	#leg11narrow.AddEntry(fdifft11narrow.findObject("h_data_difft_2011_narrow"),"Data","epl")
	#leg11narrow.AddEntry(fdifft11narrow.findObject("res_eff_2011_narrow_Norm[difft]"),"2-Gaussian fit","epl")
	leg12narrow = ROOT.TLegend(0.6,0.7,0.95,0.9)
	leg12narrow.SetFillColor(kWhite)
	leg12narrow.SetBorderSize(0)
	leg12narrow.SetHeader("2012 MC data")
	#leg12narrow.AddEntry(fdifft12narrow.findObject("h_data_difft_2012_narrow"),"Data","epl")
	#leg12narrow.AddEntry(fdifft12narrow.findObject("res_eff_2012_narrow_Norm[difft]"),"2-Gaussian fit","epl")

	polfun_2011_wide = ROOT.TF1("polfun_2011_wide", "[0] + [1]*(x - "+str(deltat_mean_2011_wide.getVal())+")",0.,0.08)
	polfun_2011_wide.SetParameters(0.045,1.)
	polfun_2012_wide = ROOT.TF1("polfun_2012_wide", "[0] + [1]*(x - "+str(deltat_mean_2012_wide.getVal())+")",0.,0.08)
	polfun_2012_wide.SetParameters(0.045,1.)
	polfun_2011_narrow = ROOT.TF1("polfun_2011_narrow", "[0] + [1]*(x - "+str(deltat_mean_2011_narrow.getVal())+")",0.,0.08)
	polfun_2011_narrow.SetParameters(0.045,1.)
	polfun_2012_narrow = ROOT.TF1("polfun_2012_narrow", "[0] + [1]*(x - "+str(deltat_mean_2012_narrow.getVal())+")",0.,0.08)
	polfun_2012_narrow.SetParameters(0.045,1.)

	cwide = ROOT.TCanvas("cwide","cwide",1600,600)
	cwide.Divide(2)
	cwide.cd(1)
	tgraphlist[0].Draw("ap")
	r0 = tgraphlist[0].Fit("polfun_2011_wide","S")
	leg11wide.Draw()
	cwide.cd(2)
	tgraphlist[1].Draw("ap")
	r1 = tgraphlist[1].Fit("polfun_2012_wide","S")
	leg12wide.Draw()
	tgraphlist[0].GetFunction("polfun_2011_wide").SetLineColor(kRed)
	tgraphlist[1].GetFunction("polfun_2012_wide").SetLineColor(kRed)
	cnarrow = ROOT.TCanvas("cnarrow","cnarrow",1600,600)
	cnarrow.Divide(2)
	cnarrow.cd(1)
	tgraphlist[2].Draw("ap")
	r2 = tgraphlist[2].Fit("polfun_2011_narrow","S")
	leg11narrow.Draw()
	cnarrow.cd(2)
	tgraphlist[3].Draw("ap")
	r3 = tgraphlist[3].Fit("polfun_2012_narrow","S")
	leg12narrow.Draw()
	tgraphlist[2].GetFunction("polfun_2011_narrow").SetLineColor(kRed)
	tgraphlist[3].GetFunction("polfun_2012_narrow").SetLineColor(kRed)

	cwide.Print("res_binfit_wide.pdf")
	cwide.Print("res_binfit_wide.root")
	cnarrow.Print("res_binfit_narrow.pdf")
	cnarrow.Print("res_binfit_narrow.root")

	print '\nWide window parameters:'
	print 'p0(2011) =',tgraphlist[0].GetFunction("polfun_2011_wide").GetParameter(0),'+-',tgraphlist[0].GetFunction("polfun_2011_wide").GetParError(0)
	print 'p1(2011) =',tgraphlist[0].GetFunction("polfun_2011_wide").GetParameter(1),'+-',tgraphlist[0].GetFunction("polfun_2011_wide").GetParError(1)
	print r0.Print("V")
	print 'p0(2012) =',tgraphlist[1].GetFunction("polfun_2012_wide").GetParameter(0),'+-',tgraphlist[1].GetFunction("polfun_2012_wide").GetParError(0)
	print 'p1(2012) =',tgraphlist[1].GetFunction("polfun_2012_wide").GetParameter(1),'+-',tgraphlist[1].GetFunction("polfun_2012_wide").GetParError(1)
	print r1.Print("V")
	print '\nNarrow window parameters:'
	print 'p0(2011) =',tgraphlist[2].GetFunction("polfun_2011_narrow").GetParameter(0),'+-',tgraphlist[2].GetFunction("polfun_2011_narrow").GetParError(0)
	print 'p1(2011) =',tgraphlist[2].GetFunction("polfun_2011_narrow").GetParameter(1),'+-',tgraphlist[2].GetFunction("polfun_2011_narrow").GetParError(1)
	print r2.Print("V")
	print 'p0(2012) =',tgraphlist[3].GetFunction("polfun_2012_narrow").GetParameter(0),'+-',tgraphlist[3].GetFunction("polfun_2012_narrow").GetParError(0)
	print 'p1(2012) =',tgraphlist[3].GetFunction("polfun_2012_narrow").GetParameter(1),'+-',tgraphlist[3].GetFunction("polfun_2012_narrow").GetParError(1)
	print r3.Print("V")
	print ''

	trescalibmodule = 'import ROOT\n\nmu_tres_p0_2011_wide = ROOT.RooConstVar("mu_tres_p0_2011_wide","mu_tres_p0_2011_wide",'+str(tgraphlist[0].GetFunction("polfun_2011_wide").GetParameter(0))+')\nmu_tres_p1_2011_wide = ROOT.RooConstVar("mu_tres_p1_2011_wide","mu_tres_p1_2011_wide",'+str(tgraphlist[0].GetFunction("polfun_2011_wide").GetParameter(1))+')\nmuvector_tres_p0_tres_p1_2011_wide = ROOT.RooArgList(mu_tres_p0_2011_wide,mu_tres_p1_2011_wide)\ncov_tres_p0_tres_p1_2011_wide = ROOT.TMatrixDSym(2)\ncov_tres_p0_tres_p1_2011_wide[0][0] = '+str(r0.GetCovarianceMatrix()[0][0])+'\ncov_tres_p0_tres_p1_2011_wide[0][1] = '+str(r0.GetCovarianceMatrix()[0][1])+'\ncov_tres_p0_tres_p1_2011_wide[1][0] = '+str(r0.GetCovarianceMatrix()[1][0])+'\ncov_tres_p0_tres_p1_2011_wide[1][1] = '+str(r0.GetCovarianceMatrix()[1][1])+'\nmu_tres_p0_2012_wide = ROOT.RooConstVar("mu_tres_p0_2012_wide","mu_tres_p0_2012_wide",'+str(tgraphlist[1].GetFunction("polfun_2012_wide").GetParameter(0))+')\nmu_tres_p1_2012_wide = ROOT.RooConstVar("mu_tres_p1_2012_wide","mu_tres_p1_2012_wide",'+str(tgraphlist[1].GetFunction("polfun_2012_wide").GetParameter(1))+')\nmuvector_tres_p0_tres_p1_2012_wide = ROOT.RooArgList(mu_tres_p0_2012_wide,mu_tres_p1_2012_wide)\ncov_tres_p0_tres_p1_2012_wide = ROOT.TMatrixDSym(2)\ncov_tres_p0_tres_p1_2012_wide[0][0] = '+str(r1.GetCovarianceMatrix()[0][0])+'\ncov_tres_p0_tres_p1_2012_wide[0][1] = '+str(r1.GetCovarianceMatrix()[0][1])+'\ncov_tres_p0_tres_p1_2012_wide[1][0] = '+str(r1.GetCovarianceMatrix()[1][0])+'\ncov_tres_p0_tres_p1_2012_wide[1][1] = '+str(r1.GetCovarianceMatrix()[1][1])+'\nmu_tres_p0_2011_narrow = ROOT.RooConstVar("mu_tres_p0_2011_narrow","mu_tres_p0_2011_narrow",'+str(tgraphlist[2].GetFunction("polfun_2011_narrow").GetParameter(0))+')\nmu_tres_p1_2011_narrow = ROOT.RooConstVar("mu_tres_p1_2011_narrow","mu_tres_p1_2011_narrow",'+str(tgraphlist[2].GetFunction("polfun_2011_narrow").GetParameter(1))+')\nmuvector_tres_p0_tres_p1_2011_narrow = ROOT.RooArgList(mu_tres_p0_2011_narrow,mu_tres_p1_2011_narrow)\ncov_tres_p0_tres_p1_2011_narrow = ROOT.TMatrixDSym(2)\ncov_tres_p0_tres_p1_2011_narrow[0][0] = '+str(r2.GetCovarianceMatrix()[0][0])+'\ncov_tres_p0_tres_p1_2011_narrow[0][1] = '+str(r2.GetCovarianceMatrix()[0][1])+'\ncov_tres_p0_tres_p1_2011_narrow[1][0] = '+str(r2.GetCovarianceMatrix()[1][0])+'\ncov_tres_p0_tres_p1_2011_narrow[1][1] = '+str(r2.GetCovarianceMatrix()[1][1])+'\nmu_tres_p0_2012_narrow = ROOT.RooConstVar("mu_tres_p0_2012_narrow","mu_tres_p0_2012_narrow",'+str(tgraphlist[3].GetFunction("polfun_2012_narrow").GetParameter(0))+')\nmu_tres_p1_2012_narrow = ROOT.RooConstVar("mu_tres_p1_2012_narrow","mu_tres_p1_2012_narrow",'+str(tgraphlist[3].GetFunction("polfun_2012_narrow").GetParameter(1))+')\nmuvector_tres_p0_tres_p1_2012_narrow = ROOT.RooArgList(mu_tres_p0_2012_narrow,mu_tres_p1_2012_narrow)\ncov_tres_p0_tres_p1_2012_narrow = ROOT.TMatrixDSym(2)\ncov_tres_p0_tres_p1_2012_narrow[0][0] = '+str(r3.GetCovarianceMatrix()[0][0])+'\ncov_tres_p0_tres_p1_2012_narrow[0][1] = '+str(r3.GetCovarianceMatrix()[0][1])+'\ncov_tres_p0_tres_p1_2012_narrow[1][0] = '+str(r3.GetCovarianceMatrix()[1][0])+'\ncov_tres_p0_tres_p1_2012_narrow[1][1] = '+str(r3.GetCovarianceMatrix()[1][1])+'\n'
	modulefile = open('TResCalib.py','w')
	modulefile.write(trescalibmodule)
	modulefile.close()

	print 'Wide window params.:'
	print '$\langle\delta_t\\rangle$ $[ps]$ & $'+str(round(deltat_mean_2011_wide.getVal(),4))+'$ & $'+str(round(deltat_mean_2012_wide.getVal(),4))+'$ \\\\'
	print '$p_{0}^{\sigma_t}$ $[ps]$ & $'+str(round(tgraphlist[0].GetFunction("polfun_2011_wide").GetParameter(0),4))+'\pm'+str(round(tgraphlist[0].GetFunction("polfun_2011_wide").GetParError(0),4))+'$ & $'+str(round(tgraphlist[1].GetFunction("polfun_2012_wide").GetParameter(0),4))+'\pm'+str(round(tgraphlist[1].GetFunction("polfun_2012_wide").GetParError(0),4))+'$ \\\\'
	print '$p_{1}^{\sigma_t}$ & $'+str(round(tgraphlist[0].GetFunction("polfun_2011_wide").GetParameter(1),4))+'\pm'+str(round(tgraphlist[0].GetFunction("polfun_2011_wide").GetParError(1),4))+'$ & $'+str(round(tgraphlist[1].GetFunction("polfun_2012_wide").GetParameter(1),4))+'\pm'+str(round(tgraphlist[1].GetFunction("polfun_2012_wide").GetParError(1),4))+'$ \\\\'
	print 'Narrow window params.:'
	print '$\langle\delta_t\\rangle$ $[ps]$ & $'+str(round(deltat_mean_2011_narrow.getVal(),4))+'$ & $'+str(round(deltat_mean_2012_narrow.getVal(),4))+'$ \\\\'
	print '$p_{0}^{\sigma_t}$ $[ps]$ & $'+str(round(tgraphlist[2].GetFunction("polfun_2011_narrow").GetParameter(0),4))+'\pm'+str(round(tgraphlist[2].GetFunction("polfun_2011_narrow").GetParError(0),4))+'$ & $'+str(round(tgraphlist[3].GetFunction("polfun_2012_narrow").GetParameter(0),4))+'\pm'+str(round(tgraphlist[3].GetFunction("polfun_2012_narrow").GetParError(0),4))+'$ \\\\'
	print '$p_{1}^{\sigma_t}$ & $'+str(round(tgraphlist[2].GetFunction("polfun_2011_narrow").GetParameter(1),4))+'\pm'+str(round(tgraphlist[2].GetFunction("polfun_2011_narrow").GetParError(1),4))+'$ & $'+str(round(tgraphlist[3].GetFunction("polfun_2012_narrow").GetParameter(1),4))+'\pm'+str(round(tgraphlist[3].GetFunction("polfun_2012_narrow").GetParError(1),4))+'$ \\\\'

def ChangeInSigmaEff(nsigma):

	stdp0val = 0.00193890551866
	p0err = 0.00130667068564
	stdp1val = 1.20439782953
	p1err = 0.0488591770277

	newp0 = ROOT.RooRealVar("newp0","newp0",0.)
	newp1 = ROOT.RooRealVar("newp1","newp1",1.)

	sigma_diff = ROOT.RooFormulaVar("sigma_diff","sigma_diff","newp0+newp1*deltat",ROOT.RooArgList(newp0,newp1,deltat))
	gaussian_diff = ROOT.RooGaussian("gaussian_diff","gaussian_diff",difft,ROOT.RooFit.RooConst(0.),sigma_diff)
	gen_model = ROOT.RooProdPdf("gen_model","gen_model",ROOT.RooArgList(gaussian_diff,marg_pdf_2011_wide))

	off_2011_wide.setVal(0)
	off_2011_wide.setConstant(1)
	sigma1_eff_2011_wide.setMin(0.0001)
	sigma1_eff_2011_wide.setMax(1.)
	sigma2_eff_2011_wide.setMin(0.0001)
	sigma2_eff_2011_wide.setMax(1.)

	sigma_eff_dev_list = []
	sigma_full_list = []
	for i in [-1,0,1]:
		for j in [-1,0,1]:
			newp0.setVal(stdp0val+i*nsigma*p0err)
			newp1.setVal(stdp1val+j*nsigma*p1err)
			dtemp = gen_model.generate(ROOT.RooArgSet(difft,deltat),10000)
			res_eff_2011_wide.fitTo(dtemp)
			sigma_eff_dev_list.append(sigma_eff_2011_wide.getVal())
			sigma_full_list.append([sigma_eff_2011_wide.getVal(),f1_eff_2011_wide.getVal(),sigma1_eff_2011_wide.getVal(),sigma2_eff_2011_wide.getVal()])

	smin, smax = min(sigma_eff_dev_list), max(sigma_eff_dev_list)
	for i in range(len(sigma_full_list)):
		if sigma_full_list[i][0] == smin: print 'min: sigmaeff =',sigma_full_list[i][0],', f1 =',sigma_full_list[i][1],', sigma1 =',sigma_full_list[i][2],', sigma2 =',sigma_full_list[i][3]
		if sigma_full_list[i][0] == smax: print 'max: sigmaeff =',sigma_full_list[i][0],', f1 =',sigma_full_list[i][1],', sigma1 =',sigma_full_list[i][2],', sigma2 =',sigma_full_list[i][3]


# ################################################################
# A C T I O N S
# ################################################################

if (len(sys.argv) > 1):
	if (sys.argv[1] == "fit1d"): Fit1DRes()
	elif (sys.argv[1] == "fit2d"): Fit2DRes()
	elif (sys.argv[1] == "fitbins"): FitBins()
