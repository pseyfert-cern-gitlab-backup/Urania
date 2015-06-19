from ROOT import *
from ROOT import RooFit

import os
from SomeMassModels import RooPhysBkg #For the exclusive backgrounds
#mass_name = 'm_{#mu#mu}'

#########################################
# CONFIGURE
#########################################
opts = {}
#opts['RESULTDIR'] = 'Combination_Results/LHCb_CMS_separate/'
opts['RESULTDIR'] = 'Combination_Results/CMS_separate/'

if not os.path.exists(opts.get('RESULTDIR')): os.makedirs(opts.get('RESULTDIR'))

opts['FORCEFIT'] = 1

opts['FIX_LHCB_PDF'] = 0
opts['FIX_CMS_PDF'] = 1
opts['COMBINE_MASS'] = 0 #Easier when combined for plotting
opts['COMBINE_BRs_BRd'] = 0
opts['COMBINE_FSFD'] = 0
opts['COMBINE_BUJPSIK_BF'] = 0

#If not Constrained, then FIXXED!
opts['ADD_ALPHA_CONST'] = 0
opts['ADD_TIMEACCCORR_CONST'] = 0
opts['ADD_KPI_MUNU_MUMU_BR_CONST'] = 0
opts['ADD_FDFS_CONST'] = 0
opts['ADD_BUJPSIK_BF_CONST'] = 0
opts['ADD_BDT_FRAC_CONST'] = 0
opts['ADD_SIGSHAPE_CONST'] = 0
opts['ADD_BKGNORM_CONST'] = 0
opts['ADD_B0UPIMUMU_CONST'] = 0
opts['ADD_B2XMUNU_CONST'] = 0
opts['ADD_NMISTOT_CONS'] = 0
opts['ADD_CMS_CONST'] = 0 #if 0, then they nothing is done


#########################################
#MAIN FUNCTIONS USED
#########################################

		

#READ IN FIT RESULT / OR FIT
def fitModel(model,data,params,fitName, constraints = 0,minosParams = 0, forceFit = 0):
	#Perform a fit on this model, and save the result in a .root file
	#If the .root file exists, read it in

	#Save a snapshot before the fit
	initialParams = params.snapshot()

	#Do the fit
	fitResult = 0
	arg_list = RooLinkedList()
	resultFile = opts.get('RESULTDIR')+str(fitName)+'_CombFitResult.root'
	
	if not os.path.exists(resultFile) or forceFit: 
	    #List of arguments
	    if constraints not 0:
	    	arg_list.Add(RooFit.ExternalConstraints(constraints))
	    
	    if minosParams not 0: 
	    	arg_list.Add(RooFit.Minos(kTRUE))
		arg_list.Add(RooFit.Minos(minosParams))
	    
	    arg_list.Add(RooFit.Offset(True))
	    arg_list.Add(RooFit.Strategy(2))
	    arg_list.Add(RooFit.Hesse(1))
	    arg_list.Add(RooFit.NumCPU(8))
	    arg_list.Add(RooFit.Optimize(1))
	    arg_list.Add(RooFit.Save(1))
	    #Chatty FIT:
            #arg_list.Add(RooFit.Verbose(kTRUE))
	    #arg_list.Add(RooFit.PrintLevel(3))

	    fitResult = model.fitTo(data, arg_list)

	    #Save the fit result
	    f = TFile(resultFile,'RECREATE')
	    fitResult.Write("fit_result") 
	    f.Close() 

	else: 
	    print " o) Fit result file found, reading it : ", resultFile
	    fitResult = gDirectory.Get(fitName)

	# Save the fitted parameter values
	# Print two parameter lists side by side (name values initvalues)
	# params.printLatex(RooFit.Columns(2))

	# Write LaTex table to file
	# params.printLatex(RooFit.Sibling(initialParams),OutputFile(fileName))
	fileName = opts.get('RESULTDIR')+str(fitName)+'_CombFitParameters'
	params.printLatex(RooFit.OutputFile(fileName+"_latex.txt")
	
	# Write just txt file of parameters
	params.writeToFile(fileName+".txt")


def writeSummary(ws,name,vars):

	# Write a summary of the fit configuration to a file
	fileName = opts.get('RESULTDIR')+str(name)+'_CombFitSummary.txt'
	f = open(fileName,'w')
	print >> f, '#----------------------------------------#'
	print >> f, '  This is the configuration for the fit:'
	for name, val in opts.items(): print >> f, '  o) '+str(name)+' : '+str(val)
	print >> f, '#----------------------------------------#'
        for var in vars:
		print >> f, ws.var(var).GetName() +' = ', ws.var(var).getVal(), ' +- ', ws.var(var).getError()
	print >> f, '#----------------------------------------#'
	f.close()
	content =  open(fileName).read()
	print content


#########################################
#Import LHCb
#########################################
print '  o) Import LHCb workspace...'
lhcb_file = TFile('lhcb_ws.root')
lhcb_ws = lhcb_file.Get('lhcb_ws')
lhcb_pdf = lhcb_ws.pdf('lhcb_pdf') # final simultaneous PDF
lhcb_data = lhcb_ws.data('lhcb_data') # final data set
lhcb_cons = lhcb_ws.set('lhcb_cons') # final data set
lhcb_params =  lhcb_pdf.getParameters(lhcb_data)

if opts.get('LHCB_READ_START_PARAMS'):
   	params.readFromFile(opts.get('RESULTSDIR)"LHCB_START_PARAMS.txt")

if opts.get('LHCB_READ_FIT_PARAMS'):
   	params.readFromFile("LHCB_FIT_PARAMS.txt")



#########################################
#Import CMS
#########################################

#print '  o) Import CMS workspace...'
#cms_file = TFile('CMS_ws_final.root')
#cms_ws = cms_file.Get('ws')
#cms_pdf = cms_ws.pdf('pdf_ext_simul') # final simultaneous PDF
#cms_data = cms_ws.data('global_data') # final data set


##########################################################################
# COMBINE THE WORKSPACES
##########################################################################
#CMS parameters that need to be linked to LHCB:
#BF_bd               Branching fraction of Bd
#BF_bs               Branching fraction of Bs
#fs_over_fu          fs/fu                                       Constrained/Gaussian
#one_over_BRBR       1/BF(B+ .J/psi K+)/BF(J/psi . mumu)       Constrained/Gaussian
##########################################################################


#If you have two workspaces with pdfs you wish to combine: 
#RooWorkspace w("w", "combined workspace"); 
#w.import("filename:workspace:objectname",); 
#eg: w.import("channelA:w1:pdfA",RenameAllVariablesExcept("A","mHiggs")); 
#w.import("channelB:w5:pdfB",RenameVariable("m","mHiggs")); 
#w.factory("SIMUL::joint(chan[A,B],A=pdfA,B=pdfB)"); 
#This creates a simultaneous pdf called joint combining the two channels A and B using pdfA and pdfB. 
#This object will now reside within the workspace and can be accessed in the same was using the 
#w->pdf("joint") method to do with what you will.

#Merge the workspaces
#print " o) Merge the workspaces:"
#comb_ws = lhcb_ws.Clone()
#comb_ws.SetNameTitle('comb_ws','comb_ws')

#------------------------------------------------#
# Combining variables between workspaces
# IDEA: Copy cms pdf with changes, and import to the comb_ws
#------------------------------------------------#
#print " o) Combine the variables between LHCb and CMS LL:"
##Use the RooCustomizer to build a new pdf with a different variables in it!
#getattr(comb_ws,"import")(cms_pdf)
#cust = RooCustomizer(comb_ws.pdf(cms_pdf.GetName()),'comb')
#
##if opts.get('COMBINE_MASS'):
##    cust.replaceArg(comb_ws.var('Mass'),comb_ws.var('B_s0_MM'))
#
#if opts.get('COMBINE_BRs_BRd'):
#    cust.replaceArg(comb_ws.var('BF_bs'),comb_ws.var('BRs'))
#    cust.replaceArg(comb_ws.var('BF_bd'),comb_ws.var('BRd'))
#
#    name = 'BRs' 
#    getattr(ws,"import")(RooFormulaVar("bind_"+str(name),"bind_"+str(name),"@0*1e-9",RooArgList(ws.var(name))))
#    cust.replaceArg(comb_ws.var('BF_bs'),comb_ws.var("bind_"+str(name)))
#
#    name = 'BRd' 
#    getattr(ws,"import")(RooFormulaVar("bind_"+str(name),"bind_"+str(name),"@0*1e-10",RooArgList(ws.var(name))))
#    cust.replaceArg(comb_ws.var('BF_bd'),comb_ws.var("bind_"+str(name)))
#
#
#if opts.get('COMBINE_FSFD'):
#    name = 'fdfs' 
#    getattr(ws,"import")(RooFormulaVar("one_over_"+str(name),"one_over_"+str(name),"1/@0",RooArgList(ws.var(name))))
#    cust.replaceArg(comb_ws.var('fs_over_fu'),comb_ws.var("one_over_"+str(name)))
#
#if opts.get('COMBINE_BUJPSIK_BF'):
#    bindVar(comb_ws,"BuJpsiK_BF","one_over_BRBR","BuJpsiK_BF",True)
#    name = 'BuJpsiK_BF' 
#    getattr(ws,"import")(RooFormulaVar("one_over_"+str(name),"one_over_"+str(name),"1/@0",RooArgList(ws.var(name))))
#    cust.replaceArg(comb_ws.var('one_over_BRBR'),comb_ws.var("one_over_"+str(name)))
#
##Builf the new cms_pdf and import it to the comb_ws
#cms_cust_pdf = cust.build(kTRUE)
##getattr(comb_ws,"import")(cms_cust_pdf)
#print 'CMS pdf name:', cms_pdf.GetName()
#print 'CMS cust pdf name:', cms_cust_pdf.GetName()
##raw_input("ok?")


###########################################################################
## Build the combined model, import DATA
###########################################################################
#print " o) Build a combined SIMULTANEOUS PDF:"
#comb_cat_name = 'experiment'
##comb_ws.factory("SIMUL::comb_pdf("+comb_cat_name+"[LHCB,CMS],LHCB="+lhcb_pdf.GetName()+",CMS="+cms_cust_pdf.GetName()+")") 
#comb_ws.factory("SIMUL::comb_pdf("+comb_cat_name+"[LHCB,CMS],LHCB="+lhcb_pdf.GetName()+",CMS="+cms_pdf.GetName()+")") 
#
#print " o) Associate the simultaneous pdf components to the datasets"
##Make sure both datasets have both, LHCb and CMS mass variables
##Otherwise we cannot append them
#cms_data.addColumn(RooFormulaVar("B_s0_MM","B_s0_MM","@0*1.e3",RooArgList(cms_ws.var("Mass"))))
#lhcb_data.addColumn(RooFormulaVar("Mass","Mass","@0/1.e3",RooArgList(lhcb_ws.var("B_s0_MM"))))
#lhcb_data.Print('v')
#cms_data.Print('v')
##raw_input("CMS data, check the mass var")
#
#
##For separate fits import the original data
#getattr(comb_ws,"import")(cms_data)
#
#comb_data_lhcb = RooDataSet("comb_data_lhcb", "Combined LHCb data", RooArgSet(comb_ws.var("B_s0_MM"),comb_ws.var("Mass")), RooFit.Index(comb_ws.cat(comb_cat_name)), RooFit.Import("LHCB", lhcb_data))
##comb_data_cms = RooDataSet("comb_data_cms", "Combined CMS data", RooArgSet(comb_ws.var("B_s0_MM")), RooFit.Index(comb_ws.cat(comb_cat_name)), RooFit.Import("CMS", cms_data))
#comb_data_cms = RooDataSet("comb_data_cms", "Combined CMS data", RooArgSet(comb_ws.var("B_s0_MM"),comb_ws.var("Mass")), RooFit.Index(comb_ws.cat(comb_cat_name)), RooFit.Import("CMS", cms_data))
#
#comb_data = RooDataSet("comb_data", "Combined data", RooArgSet(comb_ws.var("B_s0_MM"),comb_ws.var("Mass")), RooFit.Index(comb_ws.cat(comb_cat_name)), RooFit.Import("CMS", cms_data), RooFit.Import("LHCb", lhcb_data))
##comb_data = comb_data_lhcb.Clone() 
##comb_data.SetNameTitle('comb_data','Combined dataset')
##comb_data.append(comb_data_cms)
#getattr(comb_ws,"import")(comb_data)
#
#comb_ws.Print()
##raw_input('ok?')

###########################################################################
## Build the constraints
###########################################################################
#
#print " o) Get the LHCb constraints"
#comb_const_str = ""
##String with all the constrain function names in the WS
## MisID
##------------------------------------------------------------------------#
#if opts.get('ADD_NMISTOT_CONS'):
#   comb_const_str += ",Nmis_const" #On by default
#else:
#   comb_ws.var("Nmis").setConstant()
#
## Normalization/Corrections
##------------------------------------------------------------------------#
#if opts.get('ADD_ALPHA_CONST'):
#   comb_const_str += ",alpha_Bu_const,alpha_KPi_const,"
#else:
#   comb_ws.var("alpha_Bu").setConstant()
#   comb_ws.var("alpha_KPi").setConstant()
#
#if opts.get('ADD_TIMEACCCORR_CONST'):
#   comb_const_str += ",timeAccCorrBd_const,timeAccCorrBs_const"
#else:
#   comb_ws.var("timeAccCorrBd").setConstant()
#   comb_ws.var("timeAccCorrBs").setConstant()
#
#if opts.get('ADD_KPI_MUNU_MUMU_BR_CONST'):
#   comb_const_str += ",BdKpi_BF_const,KMuNuBR_const,PiMuMuBR_const,PiMuNuBR_const"
#else:
#   comb_ws.var("BdKpi_BF").setConstant()
#   comb_ws.var("KMuNuBR").setConstant()
#   comb_ws.var("PiMuNuBR").setConstant()
#   comb_ws.var("PiMuMuBR").setConstant()
#
## Constraints Shared WILL be shared with CMS
##------------------------------------------------------------------------#
#if opts.get('ADD_FDFS_CONST'):
#   comb_const_str += ",fdfs_const"
#else:
#   comb_ws.var("fdfs").setConstant()
#
#if opts.get('ADD_BUJPSIK_BF_CONST'):
#   comb_const_str += ",BuJpsiK_BF_const"
#else:
#   comb_ws.var("BuJpsiK_BF").setConstant()
##------------------------------------------------------------------------#
#
## BDT shape
##------------------------------------------------------------------------#
#if opts.get('ADD_BDT_FRAC_CONST'):
#   for i in range(1,9): comb_const_str += ",BDT_f"+str(i)+"_const" 
#else:
#   for i in range(1,9): comb_ws.var("BDT_f"+str(i)).setConstant()
#
#if opts.get('ADD_SIGSHAPE_CONST'):
#   comb_const_str += ",sigmaBd_const,sigmaBs_const,CBExpo_const,CBTrans_const,MBd_const,MBs_const"
#else:
#   comb_ws.var("sigmaBd").setConstant()
#   comb_ws.var("sigmaBs").setConstant()
#   comb_ws.var("CBExpo").setConstant()
#   comb_ws.var("CBTrans").setConstant()
#   comb_ws.var("MBd").setConstant()
#   comb_ws.var("MBs").setConstant()
#
## Peaking background 
##------------------------------------------------------------------------#
#if opts.get('ADD_BKGNORM_CONST'):
#   comb_const_str += ",BkgNorm_const"
#else:
#   comb_ws.var("BkgNorm").setConstant()
#
##   PiMuMu
##------------------------------------------------------------------------#
#if opts.get('ADD_B0UPIMUMU_CONST'):
#   comb_const_str += ",PiMuMuEff_const"
#   for i in range(2,9): comb_const_str += ",PiMuMuFrac"+str(i)+"_const"
#   for i in range(1,9): 
#      comb_const_str += ",PiMuMuMean"+str(i)+"_const"
#      comb_const_str += ",PiMuMuSigma"+str(i)+"_const"
#      comb_const_str += ",PiMuMuShc"+str(i)+"_const"
#else:
#   comb_ws.var('PiMuMuEff').setConstant()
#   for i in range(2,9): comb_ws.var("PiMuMuFrac"+str(i)).setConstant()
#   for i in range(1,9): 
#   	comb_ws.var("PiMuMuMean"+str(i)).setConstant()
#   	comb_ws.var("PiMuMuSigma"+str(i)).setConstant()
#   	comb_ws.var("PiMuMuShc"+str(i)).setConstant()
#
#
##   PiMuNu and KMuNu
##------------------------------------------------------------------------#
#if opts.get('ADD_B2XMUNU_CONST'):
#   comb_const_str += ",PiMuNuEff_const"
#   comb_const_str += ",KMuNuEff_const"
#   for i in range(2,9): 
#      comb_const_str += ",PiMuNuFrac"+str(i)+"_const"
#      #comb_const_str += ",KMuNuFrac"+str(i)+"_const"
#      comb_ws.var("KMuNuFrac"+str(i)).setConstant() #Otherwise the number oy PiMuNu ans KMuNu f_a_x*tot_a_x + f_b_x*tot_b_x is ambiguous
#
#   for i in range(1,9): 
#      comb_const_str += ",PiMuNuMean"+str(i)+"_const"
#      comb_const_str += ",PiMuNuSigma"+str(i)+"_const"
#      #if i is 4: comb_const_str += ",PiMuNuShc"+str(i)+"shift_const"
#      #else: 
#      comb_const_str += ",PiMuNuShc"+str(i)+"_const"
#else:
#   comb_ws.var("PiMuNuEff").setConstant()
#   comb_ws.var("KMuNuEff").setConstant()
#   for i in range(2,9): 
#      comb_ws.var("PiMuNuFrac"+str(i)).setConstant()
#      comb_ws.var("KMuNuFrac"+str(i)).setConstant()
#   for i in range(1,9): 
#      comb_ws.var("PiMuNuMean"+str(i)).setConstant()
#      comb_ws.var("PiMuNuSigma"+str(i)).setConstant()
#      #if i is 4: comb_ws.var("PiMuNuShc4shift").setConstant()
#      #else: 
#      comb_ws.var("PiMuNuShc"+str(i)).setConstant()
##------------------------------------------------------------------------#
#
#if opts.get('ADD_CMS_CONST'):
#   getattr(comb_ws,"import")(cms_ws.pdf("one_over_BRBR_gau"))
#   getattr(comb_ws,"import")(cms_ws.pdf("fs_over_fu_gau"))
#   
#   comb_const_str += ",one_over_BRBR_gau"
#   comb_const_str += ",fs_over_fu_gau"
#
##------------------------------------------------------------------------#
#
## Get the constraints
#if len(comb_const_str)>0 and comb_const_str[0] is ',': comb_const_str = comb_const_str[1:]
#comb_cons = comb_ws.argSet(comb_const_str) # external Gaussian constraints
##cms_cons = RooArgSet(comb_ws.pdf('fs_over_fu_gau'),comb_ws.pdf('one_over_BRBR_gau')) # external Gaussian constraints
#cms_cons = RooArgSet(cms_ws.pdf('fs_over_fu_gau'),cms_ws.pdf('one_over_BRBR_gau')) # external Gaussian constraints
#
#
#print ' Constraints:'
#print ' combined =', comb_const_str
#print ' CMS =', cms_cons
##raw_input('ok?')
#
##Fix everything
#def fixParams(params):
#    paramsIT = params.createIterator()
#    p = paramsIT.Next()
#    while p and isinstance(p,RooRealVar):
#        p.setConstant()
#        print '     Fixed:', p.GetName()
#        print '     @ ', p.getVal()
#        p = paramsIT.Next()
#    print '  --------------------------------'
#
#if opts.get('FIX_LHCB_PDF'):
#    print '  --------------------------------'
#    print '     Fix the fit parameters ......\n'
#    #params = comb_ws.pdf('comb_pdf').getPdf('experiment=LHCB').getParameters(comb_data)
#    params = comb_ws.pdf('lhcb_pdf').getParameters(comb_data)
#    fixParams(params)
#
#if opts.get('FIX_CMS_PDF'):
#    print '  --------------------------------'
#    print '     Fix the fit parameters ......\n'
#    #params = comb_ws.pdf('comb_pdf').getPdf('experiment=LHCB').getParameters(comb_data)
#    params = comb_ws.pdf('pdf_ext_simul').getParameters(comb_data)
#    fixParams(params)
#
#
## Check if names of the parameters in CMS and LHCb pdf are different
#
#print " o) Compare lhcb and cms pdf parameter names: no!"
##cms_par = comb_ws.pdf('lhcb_pdf').getParameters(comb_data)
##lhcb_par = comb_ws.pdf('pdf_ext_simul').getParameters(comb_data)
##cms_p_it = cms_par.createIterator()
##cms_p = cms_p_it.Next()
##while cms_p:
##    lhcb_p_it = lhcb_par.createIterator()
##    lhcb_p = lhcb_p_it.Next()
##    while lhcb_p:
##        if cms_p.GetName() is lhcb_p.GetName(): print '  ----> Found parameter with the same name:', cms_p.GetName()
##        else: print '  ',cms_p.GetName(),' != ', lhcb_p.GetName()
##        lhcb_p = lhcb_p_it.Next()
##    cms_p = cms_p_it.Next()
##    #print ' ..get new CMS par:', cms_p.GetName()
##print '  --------------------------------'
##raw_input('ok?')
#




