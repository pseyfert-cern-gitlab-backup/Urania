from ROOT import *
from FitnGenInterface import *
from GetAccInterface import *


# Inverse of the Phase Space model.
invPSmodel = RooRealVar("invPSmodel","invPSmodel",0.,100000.)

# MC data identifiers.
MCtype11 = -73
MCtype12 = -83

# Trigger lines.
trigline1_name = "B_s0_L0Global_TIS"
trigline2_name = "B_s0_L0HadronDecision_TOS"
trigline3_name = "B_s0_Hlt1DiHadronDecision_TOS"
trigline4_name = "B_s0_Hlt1SingleHadronDecision_TOS"
trigline5_name = "B_s0_Hlt1TrackAllL0Decision_TOS"
trigline6_name = "B_s0_Hlt2B2HHDecision_TOS"
trigline7_name = "B_s0_Hlt2Topo2BodyBBDTDecision_TOS"
trigline8_name = "B_s0_Hlt2Topo2BodySimpleDecision_TOS"
trigline9_name = "B_s0_Hlt2Topo3BodyBBDTDecision_TOS"
trigline10_name = "B_s0_Hlt2Topo3BodySimpleDecision_TOS"
trigline11_name = "B_s0_Hlt2Topo4BodyBBDTDecision_TOS"
trigline12_name = "B_s0_Hlt2Topo4BodySimpleDecision_TOS"

# Analysis variable names.
m1check_name = "B_s0_DTF_KST1_M"
m2check_name = "B_s0_DTF_KST2_M"
cos1check_name = "B_s0_DTF_KST1_COSTHETA"
cos2check_name = "B_s0_DTF_KST2_COSTHETA"
phicheck_name = "B_s0_DTF_B_s0_PHI"
tcheck_name = "B_s0_DTF_B_s0_TAU"

# Year and trigger line variables.
year_cat = RooCategory("year_cat","year")
year_cat.defineType("2011",0)
year_cat.defineType("2012",1)
trigline1_cat = RooCategory(trigline1_name,trigline1_name)
trigline1_cat.defineType("false",0)
trigline1_cat.defineType("true",1)
trigline2_cat = RooCategory(trigline2_name,trigline2_name)
trigline2_cat.defineType("false",0)
trigline2_cat.defineType("true",1)
trigline3_cat = RooCategory(trigline3_name,trigline3_name)
trigline3_cat.defineType("false",0)
trigline3_cat.defineType("true",1)
trigline4_cat = RooCategory(trigline4_name,trigline4_name)
trigline4_cat.defineType("false",0)
trigline4_cat.defineType("true",1)
trigline5_cat = RooCategory(trigline5_name,trigline5_name)
trigline5_cat.defineType("false",0)
trigline5_cat.defineType("true",1)
trigline6_cat = RooCategory(trigline6_name,trigline6_name)
trigline6_cat.defineType("false",0)
trigline6_cat.defineType("true",1)
trigline7_cat = RooCategory(trigline7_name,trigline7_name)
trigline7_cat.defineType("false",0)
trigline7_cat.defineType("true",1)
trigline8_cat = RooCategory(trigline8_name,trigline8_name)
trigline8_cat.defineType("false",0)
trigline8_cat.defineType("true",1)
trigline9_cat = RooCategory(trigline9_name,trigline9_name)
trigline9_cat.defineType("false",0)
trigline9_cat.defineType("true",1)
trigline10_cat = RooCategory(trigline10_name,trigline10_name)
trigline10_cat.defineType("false",0)
trigline10_cat.defineType("true",1)
trigline11_cat = RooCategory(trigline11_name,trigline11_name)
trigline11_cat.defineType("false",0)
trigline11_cat.defineType("true",1)
trigline12_cat = RooCategory(trigline12_name,trigline12_name)
trigline12_cat.defineType("false",0)
trigline12_cat.defineType("true",1)


def loadDataAccCheck(data_file, data_tree, wide_window = 1, evnum_limit = 0, file_path = NTUPLE_PATH):

	# Information.
	print "\nNEW INPUT DATA FILE"
	print 'Loading data file ' + data_file + ' ...'
	if (evnum_limit == 0): print 'All events selected.'
	else: print str(evnum_limit)+' events selected.'

	# PhSp generation model.
	PDF_gen = MCGenPHSP("PDF_gen","PDF_gen",RooFit.RooConst(wide_window),mKp1,mKp2,t,RooFit.RooConst(1))

	# Input file.
	file_in = TFile(file_path + data_file)

	# Tree with the selected events.
	tree = file_in.Get(data_tree)
	file_out = TFile(file_path + "trash.root","recreate")
	if wide_window: range_cut = tcheck_name+">=0. && "+tcheck_name+"<=12."
	else: range_cut = "abs("+m1check_name+"-900.)<150. && abs("+m2check_name+"-900.)<150. && "+tcheck_name+">=0. && "+tcheck_name+"<=12."
	MCdata1112_cut = " && (itype==" + str(MCtype11) + " || itype==" + str(MCtype12) + ")"
	tree2 = tree.CopyTree(range_cut + MCdata1112_cut)

	# Construction of datasets.
	if (wide_window): data_ = RooDataSet("data_","data_",RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,invPSmodel,year_cat))
	else: data_ = RooDataSet("data_","data_",RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,invPSmodel,year_cat))
	more_cat_1 = RooDataSet("more_cat_1","more_cat_1",RooArgSet(trigline1_cat,trigline2_cat,trigline3_cat,trigline4_cat,trigline5_cat,trigline6_cat))
	more_cat_2 = RooDataSet("more_cat_2","more_cat_2",RooArgSet(trigline7_cat,trigline8_cat,trigline9_cat,trigline10_cat,trigline11_cat,trigline12_cat))
	ev_counter = 0
	normalizer = 1./((1700.-750.)*(1700.-750.)*12.)
	for i in tree2:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))):
			if (wide_window):
				mKp1.setVal(eval("i."+m1check_name))
				mKp2.setVal(eval("i."+m2check_name))
			else:
				mKp1_narrowwin.setVal(eval("i."+m1check_name))
				mKp2_narrowwin.setVal(eval("i."+m2check_name))
			cos1.setVal(eval("i."+cos1check_name))
			cos2.setVal(eval("i."+cos2check_name))
			phi.setVal(eval("i."+phicheck_name))
			t.setVal(eval("i."+tcheck_name))
			invPSmodel.setVal(normalizer/(PDF_gen.phasespace(eval("i."+m1check_name),eval("i."+m2check_name))*PDF_gen.timemodel(eval("i."+tcheck_name))))
			if i.itype == MCtype11: year_cat.setIndex(0)
			elif i.itype == MCtype12: year_cat.setIndex(1)
			else: print 'ERROR: the event does not correspond to the chosen data sample.'
			trigline1_cat.setIndex(eval("i."+trigline1_name))
			trigline2_cat.setIndex(eval("i."+trigline2_name))
			trigline3_cat.setIndex(eval("i."+trigline3_name))
			trigline4_cat.setIndex(eval("i."+trigline4_name))
			trigline5_cat.setIndex(eval("i."+trigline5_name))
			trigline6_cat.setIndex(eval("i."+trigline6_name))
			trigline7_cat.setIndex(eval("i."+trigline7_name))
			trigline8_cat.setIndex(eval("i."+trigline8_name))
			trigline9_cat.setIndex(eval("i."+trigline9_name))
			trigline10_cat.setIndex(eval("i."+trigline10_name))
			trigline11_cat.setIndex(eval("i."+trigline11_name))
			trigline12_cat.setIndex(eval("i."+trigline12_name))
			if (wide_window): data_.add(RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,invPSmodel,year_cat))
			else: data_.add(RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,invPSmodel,year_cat))
			more_cat_1.add(RooArgSet(trigline1_cat,trigline2_cat,trigline3_cat,trigline4_cat,trigline5_cat,trigline6_cat))
			more_cat_2.add(RooArgSet(trigline7_cat,trigline8_cat,trigline9_cat,trigline10_cat,trigline11_cat,trigline12_cat))
			ev_counter += 1
	data_.merge(more_cat_1)
	data_.merge(more_cat_2)
	data = RooDataSet("data","data",data_,data_.get(),"","invPSmodel")

	print str(ev_counter) + ' events loaded.\n'

	return data

def r_corr(data,xvar,yvar,weighted):

	if weighted: n = data.sumEntries()
	else: n = data.numEntries()
	sum_x,sum_y,sum_xy,sum_xx,sum_yy = 0.,0.,0.,0.,0.
	x_i,y_i = 0.,0.

	for i in range(data.numEntries()):

		if type(xvar) == RooRealVar: x_i = data.get(i).getRealValue(xvar.GetName())
		elif type(xvar) == RooCategory: x_i = float(data.get(i).getCatIndex(xvar.GetName()))
		else: return 0.
		if type(yvar) == RooRealVar: y_i = data.get(i).getRealValue(yvar.GetName())
		elif type(yvar) == RooCategory: y_i = float(data.get(i).getCatIndex(yvar.GetName()))
		else: return 0.

		if weighted:
			data.get(i)
			ev_weight = data.weight()
		else: ev_weight = 1.

		sum_x += x_i*ev_weight
		sum_y += y_i*ev_weight
		sum_xy += x_i*y_i*ev_weight
		sum_xx += x_i*x_i*ev_weight
		sum_yy += y_i*y_i*ev_weight

	r_xy = (n*sum_xy-sum_x*sum_y)/(sqrt(n*sum_xx-sum_x*sum_x)*sqrt(n*sum_yy-sum_y*sum_y))

	return r_xy

def corr_table_2D(data,listofvars,weighted,output_tag,rotated):

	matrix = []
	for i in range(len(listofvars)):
		matrix.append([])
		for j in range(len(listofvars)): matrix[i].append([])

	print 'Computing the linear correlation matrix ...'
	for i in range(len(listofvars)):
		for j in range(len(listofvars)):
			if j >= i:
				r_xy = r_corr(data,listofvars[i],listofvars[j],weighted)
				if r_xy >= 0.2:
					if i == j: matrix[i][j] = '\\textbf{%.2f}'%r_xy
					else: matrix[i][j] = '\\textcolor{red}{%.2f}'%r_xy
				else: matrix[i][j] = '%.2f'%r_xy
			else: matrix[i][j] = ' '
	print 'Linear correlation matrix computed.\n'

	if rotated: table_type = 'sidewaystable'
	else: table_type = 'table'
	text = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\\usepackage{color}\n\\usepackage{rotating}\n\n\\begin{document}\n\n\\begin{' + table_type + '}[h]\n\\centering\n\\begin{tabular}{|c|'
	for i in range(len(listofvars)): text += 'c'
	text += '|}\n\hline\nParameter & '
	for var in listofvars: text += '$' + str(var.GetTitle()) + '$ & '
	text += '\\\\\n\\hline\n'
	for i in range(len(listofvars)):
		text += '$' + str(listofvars[i].GetTitle()) + '$ & '
		for j in range(len(listofvars)): text += matrix[i][j] + ' & '
		text += '\\\\\n'
	text += '\\hline\n\\end{tabular}\n\\end{' + table_type + '}\n\n\\end{document}'
	text = text.replace('& \\\\','\\\\')
	text = text.replace('#','\\')

	texfile = open(output_tag + '.tex','w')
	texfile.write(text)
	texfile.close()
	os.system('pdflatex ' + output_tag + '.tex')

	return

def createSubSample(data,cutstring1,cutstring2,wide_window,name):

	if wide_window: argset = RooArgSet(mKp1,mKp2,cos1,cos2,phi,t,invPSmodel)
	else: argset = RooArgSet(mKp1_narrowwin,mKp2_narrowwin,cos1,cos2,phi,t,invPSmodel)
	datacut_ = RooDataSet("datacut_","datacut_",argset)

	norm = 1./data.sumEntries(cutstring1)
	for i in range(data.numEntries()):
		if eval(cutstring2):
			if (wide_window):
				mKp1.setVal(data.get(i).getRealValue(mKp1.GetName()))
				mKp2.setVal(data.get(i).getRealValue(mKp2.GetName()))
			else:
				mKp1_narrowwin.setVal(data.get(i).getRealValue(mKp1_narrowwin.GetName()))
				mKp2_narrowwin.setVal(data.get(i).getRealValue(mKp2_narrowwin.GetName()))
			cos1.setVal(data.get(i).getRealValue(cos1.GetName()))
			cos2.setVal(data.get(i).getRealValue(cos2.GetName()))
			phi.setVal(data.get(i).getRealValue(phi.GetName()))
			t.setVal(data.get(i).getRealValue(t.GetName()))
			invPSmodel.setVal(norm*data.weight())
			datacut_.add(argset)

	datacut = RooDataSet(name,name,datacut_,datacut_.get(),"","invPSmodel")

	return datacut

def makeTimeAccCorrPlot(data,output_TimeAccCorr,nbinsplot,nbinscut,applyweights,wide_window):

	print 'Computing adaptive binning for each variable ...'
	if wide_window:
		bounds_m1 = adaptiveBinning(mKp1,nbinscut,applyweights,data)
		bounds_m2 = adaptiveBinning(mKp2,nbinscut,applyweights,data)
	else:
		bounds_m1 = adaptiveBinning(mKp1_narrowwin,nbinscut,applyweights,data)
		bounds_m2 = adaptiveBinning(mKp2_narrowwin,nbinscut,applyweights,data)
	bounds_cos1 = adaptiveBinning(cos1,nbinscut,applyweights,data)
	bounds_cos2 = adaptiveBinning(cos2,nbinscut,applyweights,data)
	bounds_phi = adaptiveBinning(phi,nbinscut,applyweights,data)
	bounds_t = adaptiveBinning(t,nbinsplot,applyweights,data)
	binning_t = getRooBinning(t,bounds_t)
	print 'Adaptive binning computed.'

	timeaccdatasets = [[],[],[],[],[]]
	for i in range(nbinscut):
		timeaccdatasets[0].append(createSubSample(data,mKp1.GetName()+" >= "+str(bounds_m1[i])+" && "+mKp1.GetName()+" < "+str(bounds_m1[i+1]),"(data.get(i).getRealValue('"+mKp1.GetName()+"') >= "+str(bounds_m1[i])+" and data.get(i).getRealValue('"+mKp1.GetName()+"') < "+str(bounds_m1[i+1])+")",wide_window,"data_mKp1Bin"+str(i+1)))
		timeaccdatasets[1].append(createSubSample(data,mKp2.GetName()+" >= "+str(bounds_m2[i])+" && "+mKp2.GetName()+" < "+str(bounds_m2[i+1]),"(data.get(i).getRealValue('"+mKp2.GetName()+"') >= "+str(bounds_m2[i])+" and data.get(i).getRealValue('"+mKp2.GetName()+"') < "+str(bounds_m2[i+1])+")",wide_window,"data_mKp2Bin"+str(i+1)))
		timeaccdatasets[2].append(createSubSample(data,cos1.GetName()+" >= "+str(bounds_cos1[i])+" && "+cos1.GetName()+" < "+str(bounds_cos1[i+1]),"(data.get(i).getRealValue('"+cos1.GetName()+"') >= "+str(bounds_cos1[i])+" and data.get(i).getRealValue('"+cos1.GetName()+"') < "+str(bounds_cos1[i+1])+")",wide_window,"data_cos1Bin"+str(i+1)))
		timeaccdatasets[3].append(createSubSample(data,cos2.GetName()+" >= "+str(bounds_cos2[i])+" && "+cos2.GetName()+" < "+str(bounds_cos2[i+1]),"(data.get(i).getRealValue('"+cos2.GetName()+"') >= "+str(bounds_cos2[i])+" and data.get(i).getRealValue('"+cos2.GetName()+"') < "+str(bounds_cos2[i+1])+")",wide_window,"data_cos2Bin"+str(i+1)))
		timeaccdatasets[4].append(createSubSample(data,phi.GetName()+" >= "+str(bounds_phi[i])+" && "+phi.GetName()+" < "+str(bounds_phi[i+1]),"(data.get(i).getRealValue('"+phi.GetName()+"') >= "+str(bounds_phi[i])+" and data.get(i).getRealValue('"+phi.GetName()+"') < "+str(bounds_phi[i+1])+")",wide_window,"data_phiBin"+str(i+1)))

	colorlist = [632,633,634,635,636,604,603,602,601,600]
	frame_t_m1 = t.frame()
	frame_t_m2 = t.frame()
	frame_t_cos1 = t.frame()
	frame_t_cos2 = t.frame()
	frame_t_phi = t.frame()

	for i in range(nbinscut):
		timeaccdatasets[0][i].plotOn(frame_t_m1,RooFit.Name("m1_bin"+str(i)),RooFit.Binning(binning_t),RooFit.MarkerSize(0),RooFit.LineColor(colorlist[i]))
		timeaccdatasets[1][i].plotOn(frame_t_m2,RooFit.Name("m2_bin"+str(i)),RooFit.Binning(binning_t),RooFit.MarkerSize(0),RooFit.LineColor(colorlist[i]))
		timeaccdatasets[2][i].plotOn(frame_t_cos1,RooFit.Name("cos1_bin"+str(i)),RooFit.Binning(binning_t),RooFit.MarkerSize(0),RooFit.LineColor(colorlist[i]))
		timeaccdatasets[3][i].plotOn(frame_t_cos2,RooFit.Name("cos2_bin"+str(i)),RooFit.Binning(binning_t),RooFit.MarkerSize(0),RooFit.LineColor(colorlist[i]))
		timeaccdatasets[4][i].plotOn(frame_t_phi,RooFit.Name("phi_bin"+str(i)),RooFit.Binning(binning_t),RooFit.MarkerSize(0),RooFit.LineColor(colorlist[i]))

	frame_t_m1.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_t_m2.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_t_cos1.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_t_cos2.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_t_phi.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_t_m1.GetXaxis().SetTitle("Time (ps)")
	frame_t_m2.GetXaxis().SetTitle("Time (ps)")
	frame_t_cos1.GetXaxis().SetTitle("Time (ps)")
	frame_t_cos2.GetXaxis().SetTitle("Time (ps)")
	frame_t_phi.GetXaxis().SetTitle("Time (ps)")

	c1 = TCanvas("c1","c1",1000,700)

	leg_m1 = TLegend(0.7,0.2,0.9,0.6)
	leg_m1.SetHeader("Bins in M(K+pi-)")
	leg_m2 = TLegend(0.7,0.2,0.9,0.6)
	leg_m2.SetHeader("Bins in M(K-pi+)")
	leg_cos1 = TLegend(0.7,0.2,0.9,0.6)
	leg_cos1.SetHeader("Bins in cos(theta1)")
	leg_cos2 = TLegend(0.7,0.2,0.9,0.6)
	leg_cos2.SetHeader("Bins in cos(theta2)")
	leg_phi = TLegend(0.7,0.2,0.9,0.6)
	leg_phi.SetHeader("Bins in phi")

	c1.Divide(2,3)
	c1.cd(1)
	frame_t_m1.Draw()
	for i in range(nbinscut): leg_m1.AddEntry("m1_bin"+str(i),"Bin "+str(i+1),"el")
	leg_m1.Draw()
	c1.cd(2)
	frame_t_m2.Draw()
	for i in range(nbinscut): leg_m2.AddEntry("m2_bin"+str(i),"Bin "+str(i+1),"el")
	leg_m2.Draw()
	c1.cd(3)
	frame_t_cos1.Draw()
	for i in range(nbinscut): leg_cos1.AddEntry("cos1_bin"+str(i),"Bin "+str(i+1),"el")
	leg_cos1.Draw()
	c1.cd(4)
	frame_t_cos2.Draw()
	for i in range(nbinscut): leg_cos2.AddEntry("cos2_bin"+str(i),"Bin "+str(i+1),"el")
	leg_cos2.Draw()
	c1.cd(5)
	frame_t_phi.Draw()
	for i in range(nbinscut): leg_phi.AddEntry("phi_bin"+str(i),"Bin "+str(i+1),"el")
	leg_phi.Draw()
	c1.Print(output_TimeAccCorr + '.root')
	c1.Print(output_TimeAccCorr + '.pdf')

	return

def makeYearAccPlot(data,output_YearAcc,nbins,applyweights,wide_window):

	print 'Computing adaptive binning for each variable ...'
	if wide_window:
		bounds_m1 = adaptiveBinning(mKp1,nbins,applyweights,data)
		bounds_m2 = adaptiveBinning(mKp2,nbins,applyweights,data)
	else:
		bounds_m1 = adaptiveBinning(mKp1_narrowwin,nbins,applyweights,data)
		bounds_m2 = adaptiveBinning(mKp2_narrowwin,nbins,applyweights,data)
	bounds_cos1 = adaptiveBinning(cos1,nbins,applyweights,data)
	bounds_cos2 = adaptiveBinning(cos2,nbins,applyweights,data)
	bounds_phi = adaptiveBinning(phi,nbins,applyweights,data)
	bounds_t = adaptiveBinning(t,nbins,applyweights,data)
	if wide_window:
		binning_m1 = getRooBinning(mKp1,bounds_m1)
		binning_m2 = getRooBinning(mKp2,bounds_m2)
	else:
		binning_m1 = getRooBinning(mKp1_narrowwin,bounds_m1)
		binning_m2 = getRooBinning(mKp2_narrowwin,bounds_m2)
	binning_cos1 = getRooBinning(cos1,bounds_cos1)
	binning_cos2 = getRooBinning(cos2,bounds_cos2)
	binning_phi = getRooBinning(phi,bounds_phi)
	binning_t = getRooBinning(t,bounds_t)
	print 'Adaptive binning computed.'

	data_11 = createSubSample(data,"year_cat == 0","data.get(i).getCatIndex('year_cat') == 0",wide_window,"data11")
	data_12 = createSubSample(data,"year_cat == 1","data.get(i).getCatIndex('year_cat') == 1",wide_window,"data12")
	if wide_window:
		data11.plotOn(frame_m1,RooFit.Binning(binning_m1),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
		data11.plotOn(frame_m2,RooFit.Binning(binning_m2),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
		frame_m1.GetYaxis().SetTitle("Efficiency (a.u.)")
		frame_m2.GetYaxis().SetTitle("Efficiency (a.u.)")
	else:
		data11.plotOn(frame_m1_narrowwin,RooFit.Binning(binning_m1),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
		data11.plotOn(frame_m2_narrowwin,RooFit.Binning(binning_m2),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
		frame_m1_narrowwin.GetYaxis().SetTitle("Efficiency (a.u.)")
		frame_m2_narrowwin.GetYaxis().SetTitle("Efficiency (a.u.)")
	data11.plotOn(frame_cos1,RooFit.Binning(binning_cos1),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
	data11.plotOn(frame_cos2,RooFit.Binning(binning_cos2),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
	data11.plotOn(frame_phi,RooFit.Binning(binning_phi),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
	data11.plotOn(frame_t,RooFit.Name("data11_t"),RooFit.Binning(binning_t),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
	frame_cos1.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_cos2.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_phi.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_t.GetYaxis().SetTitle("Efficiency (a.u.)")
	if wide_window:
		data12.plotOn(frame_m1,RooFit.Binning(binning_m1),RooFit.LineColor(kRed),RooFit.MarkerSize(0))
		data12.plotOn(frame_m2,RooFit.Binning(binning_m2),RooFit.LineColor(kRed),RooFit.MarkerSize(0))
	else:
		data12.plotOn(frame_m1_narrowwin,RooFit.Binning(binning_m1),RooFit.LineColor(kRed),RooFit.MarkerSize(0))
		data12.plotOn(frame_m2_narrowwin,RooFit.Binning(binning_m2),RooFit.LineColor(kRed),RooFit.MarkerSize(0))
	data12.plotOn(frame_cos1,RooFit.Binning(binning_cos1),RooFit.LineColor(kRed),RooFit.MarkerSize(0))
	data12.plotOn(frame_cos2,RooFit.Binning(binning_cos2),RooFit.LineColor(kRed),RooFit.MarkerSize(0))
	data12.plotOn(frame_phi,RooFit.Binning(binning_phi),RooFit.LineColor(kRed),RooFit.MarkerSize(0))
	data12.plotOn(frame_t,RooFit.Name("data12_t"),RooFit.Binning(binning_t),RooFit.LineColor(kRed),RooFit.MarkerSize(0))

	c1 = TCanvas("c1","c1",1000,700)
	c1.Divide(2,3)
	c1.cd(1)
	if wide_window: frame_m1.Draw()
	else: frame_m1_narrowwin.Draw()
	c1.cd(2)
	if wide_window: frame_m2.Draw()
	else: frame_m2_narrowwin.Draw()
	c1.cd(3)
	frame_cos1.Draw()
	c1.cd(4)
	frame_cos2.Draw()
	c1.cd(5)
	frame_phi.Draw()
	c1.cd(6)
	frame_t.Draw()
	leg_t = TLegend(0.7,0.2,0.9,0.6)
	leg_t.SetHeader("Year")
	leg_t.AddEntry("data11_t","2011","el")
	leg_t.AddEntry("data12_t","2012","el")
	leg_t.Draw()
	c1.Print(output_YearAcc + '.root')
	c1.Print(output_YearAcc + '.pdf')

	return

def makeTrigAccPlot(data,output_TrigAcc,nbins,applyweights,wide_window):

	print 'Computing adaptive binning ...'
	bounds_t = adaptiveBinning(t,nbins,applyweights,data)
	binning_t = getRooBinning(t,bounds_t)
	print 'Adaptive binning computed.'

	data_tl1 = createSubSample(data,trigline1_name+" == 1 && "+trigline2_name+" == 0","(data.get(i).getCatIndex('"+trigline1_name+"') == 1 and data.get(i).getCatIndex('"+trigline2_name+"') == 0)",wide_window,"datatl1")
	data_tl2 = createSubSample(data,trigline1_name+" == 0 && "+trigline2_name+" == 1","(data.get(i).getCatIndex('"+trigline1_name+"') == 0 and data.get(i).getCatIndex('"+trigline2_name+"') == 1)",wide_window,"datatl2")
	data_tl7 = createSubSample(data,trigline7_name+" == 1 && "+trigline8_name+" == 0 && "+trigline9_name+" == 0 && "+trigline10_name+" == 0 && "+trigline11_name+" == 0 && "+trigline12_name+" == 0","(data.get(i).getCatIndex('"+trigline7_name+"') == 1 and data.get(i).getCatIndex('"+trigline8_name+"') == 0 and data.get(i).getCatIndex('"+trigline9_name+"') == 0 and data.get(i).getCatIndex('"+trigline10_name+"') == 0 and data.get(i).getCatIndex('"+trigline11_name+"') == 0 and data.get(i).getCatIndex('"+trigline12_name+"') == 0)",wide_window,"datatl7")
	data_tl8 = createSubSample(data,trigline7_name+" == 0 && "+trigline8_name+" == 1 && "+trigline9_name+" == 0 && "+trigline10_name+" == 0 && "+trigline11_name+" == 0 && "+trigline12_name+" == 0","(data.get(i).getCatIndex('"+trigline7_name+"') == 0 and data.get(i).getCatIndex('"+trigline8_name+"') == 1 and data.get(i).getCatIndex('"+trigline9_name+"') == 0 and data.get(i).getCatIndex('"+trigline10_name+"') == 0 and data.get(i).getCatIndex('"+trigline11_name+"') == 0 and data.get(i).getCatIndex('"+trigline12_name+"') == 0)",wide_window,"datatl8")
	data_tl9 = createSubSample(data,trigline7_name+" == 0 && "+trigline8_name+" == 0 && "+trigline9_name+" == 1 && "+trigline10_name+" == 0 && "+trigline11_name+" == 0 && "+trigline12_name+" == 0","(data.get(i).getCatIndex('"+trigline7_name+"') == 0 and data.get(i).getCatIndex('"+trigline8_name+"') == 0 and data.get(i).getCatIndex('"+trigline9_name+"') == 1 and data.get(i).getCatIndex('"+trigline10_name+"') == 0 and data.get(i).getCatIndex('"+trigline11_name+"') == 0 and data.get(i).getCatIndex('"+trigline12_name+"') == 0)",wide_window,"datatl9")
	data_tl10 = createSubSample(data,trigline7_name+" == 0 && "+trigline8_name+" == 0 && "+trigline9_name+" == 0 && "+trigline10_name+" == 1 && "+trigline11_name+" == 0 && "+trigline12_name+" == 0","(data.get(i).getCatIndex('"+trigline7_name+"') == 0 and data.get(i).getCatIndex('"+trigline8_name+"') == 0 and data.get(i).getCatIndex('"+trigline9_name+"') == 0 and data.get(i).getCatIndex('"+trigline10_name+"') == 1 and data.get(i).getCatIndex('"+trigline11_name+"') == 0 and data.get(i).getCatIndex('"+trigline12_name+"') == 0)",wide_window,"datatl10")
	data_tl11 = createSubSample(data,trigline7_name+" == 0 && "+trigline8_name+" == 0 && "+trigline9_name+" == 0 && "+trigline10_name+" == 0 && "+trigline11_name+" == 1 && "+trigline12_name+" == 0","(data.get(i).getCatIndex('"+trigline7_name+"') == 0 and data.get(i).getCatIndex('"+trigline8_name+"') == 0 and data.get(i).getCatIndex('"+trigline9_name+"') == 0 and data.get(i).getCatIndex('"+trigline10_name+"') == 0 and data.get(i).getCatIndex('"+trigline11_name+"') == 1 and data.get(i).getCatIndex('"+trigline12_name+"') == 0)",wide_window,"datatl11")
	data_tl12 = createSubSample(data,trigline7_name+" == 0 && "+trigline8_name+" == 0 && "+trigline9_name+" == 0 && "+trigline10_name+" == 0 && "+trigline11_name+" == 0 && "+trigline12_name+" == 1","(data.get(i).getCatIndex('"+trigline7_name+"') == 0 and data.get(i).getCatIndex('"+trigline8_name+"') == 0 and data.get(i).getCatIndex('"+trigline9_name+"') == 0 and data.get(i).getCatIndex('"+trigline10_name+"') == 0 and data.get(i).getCatIndex('"+trigline11_name+"') == 0 and data.get(i).getCatIndex('"+trigline12_name+"') == 1)",wide_window,"datatl12")

	frame_t_L0 = t.frame()
	frame_t_Hlt2 = t.frame()
	colorlist = [632,633,634,635,636,604,603,602,601,600]

	data_tl1.plotOn(frame_t_L0,RooFit.Name(trigline1_name),RooFit.Binning(binning_t),RooFit.LineColor(kRed),RooFit.MarkerSize(0))
	data_tl2.plotOn(frame_t_L0,RooFit.Name(trigline2_name),RooFit.Binning(binning_t),RooFit.LineColor(kBlue),RooFit.MarkerSize(0))
	data_tl7.plotOn(frame_t_Hlt2,RooFit.Name(trigline7_name),RooFit.Binning(binning_t),RooFit.LineColor(colorlist[2]),RooFit.MarkerSize(0))
	data_tl8.plotOn(frame_t_Hlt2,RooFit.Name(trigline8_name),RooFit.Binning(binning_t),RooFit.LineColor(colorlist[3]),RooFit.MarkerSize(0))
	data_tl9.plotOn(frame_t_Hlt2,RooFit.Name(trigline9_name),RooFit.Binning(binning_t),RooFit.LineColor(colorlist[4]),RooFit.MarkerSize(0))
	data_tl10.plotOn(frame_t_Hlt2,RooFit.Name(trigline10_name),RooFit.Binning(binning_t),RooFit.LineColor(colorlist[5]),RooFit.MarkerSize(0))
	data_tl11.plotOn(frame_t_Hlt2,RooFit.Name(trigline11_name),RooFit.Binning(binning_t),RooFit.LineColor(colorlist[6]),RooFit.MarkerSize(0))
	data_tl12.plotOn(frame_t_Hlt2,RooFit.Name(trigline12_name),RooFit.Binning(binning_t),RooFit.LineColor(colorlist[7]),RooFit.MarkerSize(0))
	frame_t_L0.GetYaxis().SetTitle("Efficiency (a.u.)")
	frame_t_Hlt2.GetYaxis().SetTitle("Efficiency (a.u.)")

	c1 = TCanvas("c1","c1")
	c1.Divide(2)
	c1.cd(1)
	frame_t_L0.Draw()
	legL0_t = TLegend(0.7,0.2,0.9,0.6)
	legL0_t.SetHeader("L0 Trigger lines (exclusive)")
	legL0_t.AddEntry(trigline1_name,trigline1_name,"el")
	legL0_t.AddEntry(trigline2_name,trigline2_name,"el")
	legL0_t.Draw()
	c1.cd(2)
	frame_t_Hlt2.Draw()
	legHlt2_t = TLegend(0.7,0.2,0.9,0.6)
	legHlt2_t.SetHeader("Hlt2 Trigger lines (exclusive)")
	legHlt2_t.AddEntry(trigline7_name,trigline7_name,"el")
	legHlt2_t.AddEntry(trigline8_name,trigline8_name,"el")
	legHlt2_t.AddEntry(trigline9_name,trigline9_name,"el")
	legHlt2_t.AddEntry(trigline10_name,trigline10_name,"el")
	legHlt2_t.AddEntry(trigline11_name,trigline11_name,"el")
	legHlt2_t.AddEntry(trigline12_name,trigline12_name,"el")
	legHlt2_t.Draw()
	c1.Print(output_TrigAcc + '.root')
	c1.Print(output_TrigAcc + '.pdf')

	return
