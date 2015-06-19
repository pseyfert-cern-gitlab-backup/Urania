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

opts['ADD_CMS_CONST'] = 1 #if 0, then they nothing is done


#########################################
#Import LHCb
#########################################
print '  o) Import LHCb workspace...'
lhcb_file = TFile('lhcb_ws.root')
lhcb_ws = lhcb_file.Get('lhcb_ws')
lhcb_pdf = lhcb_ws.pdf('lhcb_pdf') # final simultaneous PDF
lhcb_data = lhcb_ws.data('lhcb_data') # final data set

#########################################
#Import CMS
#########################################

#print '  o) Import CMS workspace...'
cms_file = TFile('CMS_ws_final.root')
cms_ws = cms_file.Get('ws')
cms_pdf = cms_ws.pdf('pdf_ext_simul') # final simultaneous PDF
cms_data = cms_ws.data('global_data') # final data set

#BF = RooArgSet(cms_ws.var('BF_bs'), cms_ws.var('BF_bd')) # two branching fractions, for minos calculations
#pdf.fitTo(data, RooFit.ExternalConstraints(ext_constr), RooFit.Strategy(2) ,RooFit.Extended(), RooFit.Minos(BF), RooFit.Hesse(1))

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
print " o) Merge the workspaces:"
comb_ws = lhcb_ws.Clone()
comb_ws.SetNameTitle('comb_ws','comb_ws')

#------------------------------------------------#
# Combining variables between workspaces
# IDEA: Copy cms pdf with changes, and import to the comb_ws
#------------------------------------------------#
print " o) Combine the variables between LHCb and CMS LL:"
#Use the RooCustomizer to build a new pdf with a different variables in it!
getattr(comb_ws,"import")(cms_pdf)
cust = RooCustomizer(comb_ws.pdf("pdf_ext_simul"),'cms_pdf')

#cust = RooCustomizer(cms_pdf,'cms_pdf') #Rename to cms_pdf

if opts.get('COMBINE_MASS'):
    cust.replaceArg(comb_ws.var('Mass'),comb_ws.var('B_s0_MM'))

if opts.get('COMBINE_BRs_BRd'):
    cust.replaceArg(comb_ws.var('BF_bs'),comb_ws.var('BRs'))

if opts.get('COMBINE_FSFD'):
    name = 'fdfs' 
    getattr(ws,"import")(RooFormulaVar("one_over_"+str(name),"one_over_"+str(name),"1/@0",RooArgList(ws.var(name))))
    cust.replaceArg(comb_ws.var('fs_over_fu'),comb_ws.var("one_over_"+str(name)))

if opts.get('COMBINE_BUJPSIK_BF'):
    bindVar(comb_ws,"BuJpsiK_BF","one_over_BRBR","BuJpsiK_BF",True)
    name = 'BuJpsiK_BF' 
    getattr(ws,"import")(RooFormulaVar("one_over_"+str(name),"one_over_"+str(name),"1/@0",RooArgList(ws.var(name))))
    cust.replaceArg(comb_ws.var('one_over_BRBR'),comb_ws.var("one_over_"+str(name)))


#Builf the new cms_pdf and import it to the comb_ws
cms_cust_pdf = cust.build(kTRUE)
getattr(comb_ws,"import")(cms_cust_pdf)

##########################################################################
# Build the combined model
##########################################################################
print " o) Build a combined SIMULTANEOUS PDF:"
comb_cat_name = 'experiment'
comb_ws.factory("SIMUL::comb_pdf("+comb_cat_name+"[LHCB,CMS],LHCB="+lhcb_pdf.GetName()+",CMS="+cms_cust_pdf.GetName()+")") 


comb_ws.pdf('comb_pdf').Print()
#raw_input("Comb pdf, check variables")

print " o) Associate the simultaneous pdf components to the datasets"

#First, add a new column to the cms dataset with the LHCb mass var name
#cms_data.addColumn(RooFormulaVar("B_s0_MM","B_s0_MM","@0*e3",RooArgList(cms_ws.var("Mass"))))
#raw_input("CMS data, check the mass var")
#comb_data = RooDataSet("comb_data", "Combined CMS and LHCb data", RooArgSet(comb_ws.var("B_s0_MM")), RooFit.Index(comb_ws.cat(comb_cat_name)), RooFit.Import("LHCB", lhcb_data), RooFit.Import("CMS", cms_data))

#For separate fits import the original data
getattr(comb_ws,"import")(cms_data)


comb_data_lhcb = RooDataSet("comb_data_lhcb", "Combined LHCb data", RooArgSet(comb_ws.var("B_s0_MM")), RooFit.Index(comb_ws.cat(comb_cat_name)), RooFit.Import("LHCB", lhcb_data))
comb_data_cms = RooDataSet("comb_data_cms", "Combined CMS data", RooArgSet(comb_ws.var("Mass")), RooFit.Index(comb_ws.cat(comb_cat_name)), RooFit.Import("CMS", cms_data))

comb_data = comb_data_lhcb.Clone() 
comb_data.append(comb_data_cms)

cms_data.Print()
getattr(comb_ws,"import")(comb_data)

#comb_ws.Print()
#raw_input("Are the DATASET asd COMB_PDF added?")

##########################################################################
# Build the constraints
##########################################################################

print " o) Get the LHCb constraints"
#String with all the constrain function names in the WS
# MisID
#------------------------------------------------------------------------#
comb_const_str = "Nmis_const"

# Normalization/Corrections
#------------------------------------------------------------------------#
if opts.get('ADD_ALPHA_CONST'):
   comb_const_str += ",alpha_Bu_const,alpha_KPi_const,"
else:
   comb_ws.var("alpha_Bu").setConstant()
   comb_ws.var("alpha_KPi").setConstant()

if opts.get('ADD_TIMEACCCORR_CONST'):
   comb_const_str += ",timeAccCorrBd_const,timeAccCorrBs_const"
else:
   comb_ws.var("timeAccCorrBd").setConstant()
   comb_ws.var("timeAccCorrBs").setConstant()

if opts.get('ADD_KPI_MUNU_MUMU_BR_CONST'):
   comb_const_str += ",BdKpi_BF_const,KMuNuBR_const,PiMuMuBR_const,PiMuNuBR_const"
else:
   comb_ws.var("BdKpi_BF").setConstant()
   comb_ws.var("KMuNuBR").setConstant()
   comb_ws.var("PiMuNuBR").setConstant()
   comb_ws.var("PiMuMuBR").setConstant()


# Constraints Shared WILL be shared with CMS
#------------------------------------------------------------------------#
if opts.get('ADD_FDFS_CONST'):
   comb_const_str += ",fdfs_const"
else:
   comb_ws.var("fdfs").setConstant()

if opts.get('ADD_BUJPSIK_BF_CONST'):
   comb_const_str += ",BuJpsiK_BF_const"
else:
   comb_ws.var("BuJpsiK_BF").setConstant()
#------------------------------------------------------------------------#

# BDT shape
#------------------------------------------------------------------------#
if opts.get('ADD_BDT_FRAC_CONST'):
   for i in range(1,9): comb_const_str += ",BDT_f"+str(i)+"_const" 
else:
   for i in range(1,9): comb_ws.var("BDT_f"+str(i)).setConstant()

if opts.get('ADD_SIGSHAPE_CONST'):
   comb_const_str += ",sigmaBd_const,sigmaBs_const,CBExpo_const,CBTrans_const,MBd_const,MBs_const"
else:
   comb_ws.var("sigmaBd").setConstant()
   comb_ws.var("sigmaBs").setConstant()
   comb_ws.var("CBExpo").setConstant()
   comb_ws.var("CBTrans").setConstant()
   comb_ws.var("MBd").setConstant()
   comb_ws.var("MBs").setConstant()

# Peaking background 
#------------------------------------------------------------------------#
if opts.get('ADD_BKGNORM_CONST'):
   comb_const_str += ",BkgNorm_const"
else:
   comb_ws.var("BkgNorm").setConstant()

#   PiMuMu
#------------------------------------------------------------------------#
if opts.get('ADD_B0UPIMUMU_CONST'):
   comb_const_str += ",PiMuMuEff_const"
   for i in range(2,9): comb_const_str += ",PiMuMuFrac"+str(i)+"_const"
   for i in range(1,9): 
      comb_const_str += ",PiMuMuMean"+str(i)+"_const"
      comb_const_str += ",PiMuMuSigma"+str(i)+"_const"
      comb_const_str += ",PiMuMuShc"+str(i)+"_const"
else:
   comb_ws.var('PiMuMuEff').setConstant()
   for i in range(2,9): comb_ws.var("PiMuMuFrac"+str(i)).setConstant()
   for i in range(1,9): 
   	comb_ws.var("PiMuMuMean"+str(i)).setConstant()
   	comb_ws.var("PiMuMuSigma"+str(i)).setConstant()
   	comb_ws.var("PiMuMuShc"+str(i)).setConstant()


#   PiMuNu and KMuNu
#------------------------------------------------------------------------#
if opts.get('ADD_B2XMUNU_CONST'):
   comb_const_str += ",PiMuNuEff_const"
   comb_const_str += ",KMuNuEff_const"
   for i in range(2,9): 
      comb_const_str += ",PiMuNuFrac"+str(i)+"_const"
      #comb_const_str += ",KMuNuFrac"+str(i)+"_const"
      comb_ws.var("KMuNuFrac"+str(i)).setConstant() #Otherwise the number oy PiMuNu ans KMuNu f_a_x*tot_a_x + f_b_x*tot_b_x is ambiguous

   for i in range(1,9): 
      comb_const_str += ",PiMuNuMean"+str(i)+"_const"
      comb_const_str += ",PiMuNuSigma"+str(i)+"_const"
      #if i is 4: comb_const_str += ",PiMuNuShc"+str(i)+"shift_const"
      #else: 
      comb_const_str += ",PiMuNuShc"+str(i)+"_const"
else:
   comb_ws.var("PiMuNuEff").setConstant()
   comb_ws.var("KMuNuEff").setConstant()
   for i in range(2,9): 
      comb_ws.var("PiMuNuFrac"+str(i)).setConstant()
      comb_ws.var("KMuNuFrac"+str(i)).setConstant()
   for i in range(1,9): 
      comb_ws.var("PiMuNuMean"+str(i)).setConstant()
      comb_ws.var("PiMuNuSigma"+str(i)).setConstant()
      #if i is 4: comb_ws.var("PiMuNuShc4shift").setConstant()
      #else: 
      comb_ws.var("PiMuNuShc"+str(i)).setConstant()
#------------------------------------------------------------------------#

if opts.get('ADD_CMS_CONST'):
   getattr(comb_ws,"import")(cms_ws.pdf("one_over_BRBR_gau"))
   getattr(comb_ws,"import")(cms_ws.pdf("fs_over_fu_gau"))
   
   comb_const_str += ",one_over_BRBR_gau"
   comb_const_str += ",fs_over_fu_gau"

#------------------------------------------------------------------------#

# Get the constraints
comb_cons = comb_ws.argSet(comb_const_str) # external Gaussian constraints


cms_cons = RooArgSet(comb_ws.pdf('fs_over_fu_gau'),comb_ws.pdf('one_over_BRBR_gau')) # external Gaussian constraints
#####################################################################################
# FIT THE MODEL
#####################################################################################
#params = comb_ws.pdf('comb_pdf').getParameters(comb_ws.var(opts.get('MASSVAR')))
params = comb_ws.pdf('comb_pdf').getParameters(comb_data)
#Save a snapshot before the fit
initialParams = params.snapshot()

#Do the fit
resultFile = opts.get('RESULTDIR')+'CombFitResult.root'
fitResult = 0
arg_list = RooLinkedList()
if not os.path.exists(resultFile) or opts.get('FORCEFIT'): 
    #List of arguments
    #arg_list.Add(RooFit.ExternalConstraints(comb_cons))
    arg_list.Add(RooFit.ExternalConstraints(cms_cons))
    arg_list.Add(RooFit.Offset(True))
    arg_list.Add(RooFit.Minos(kTRUE))
    #arg_list.Add(RooFit.Minos(RooArgSet(BR_s,BR_d)))
    arg_list.Add(RooFit.Strategy(2))
    #arg_list.Add(RooFit.Verbose(kTRUE))
    #arg_list.Add(RooFit.PrintLevel(3))
    arg_list.Add(RooFit.Hesse(1))
    arg_list.Add(RooFit.NumCPU(8))
    #arg_list.Add(RooFit.NumCPU(1))
    arg_list.Add(RooFit.Optimize(1))
    #arg_list.Add(RooFit.Optimize(0))
    
    #fitResult = comb_ws.pdf('comb_pdf').fitTo(comb_data, RooFit.ExternalConstraints(comb_cons), RooFit.Strategy(2) ,RooFit.Extended(), RooFit.Minos(BF), RooFit.Hesse(1), RooFit.NumCPU(8), RooFit.Save())
    #fitResult = comb_ws.pdf('comb_pdf').fitTo(comb_data, RooFit.ExternalConstraints(comb_cons), RooFit.Strategy(2) ,RooFit.Extended(), RooFit.Hesse(1), RooFit.NumCPU(8), RooFit.Save(), RooFit.Offset(1))

    #fitResult = comb_ws.pdf('pdf_ext_simul').fitTo(cms_data, arg_list)
    #fitResult = comb_ws.pdf(cms_cust_pdf.GetName()).fitTo(cms_data, arg_list)
    
    #fitResult = cms_pdf.fitTo(cms_data, arg_list)
    #fitResult = cms_pdf.fitTo(cms_data, RooFit.ExternalConstraints(cms_cons), RooFit.Strategy(2) ,RooFit.Extended(), RooFit.Hesse(1))
    
    fitResult = comb_ws.pdf('comb_pdf').fitTo(comb_data, arg_list)
   
    #Save the fit result
    f = TFile(resultFile,'RECREATE')
    fitResult.Write("comb_fit_result") 
    f.Close() 

else: 
    print " o) Fit result file found, reading it : ", resultFile
    fitResult = gDirectory.Get('comb_fit_result')

#Save the fitted parameter values
# Print two parameter lists side by side (name values initvalues)
#params.printLatex(RooFit.Sibling(initialParams),RooFit.Columns(2))
#params.printLatex(RooFit.Columns(2))

# Write LaTex table to file
fileName = opts.get('RESULTDIR')+'CombFitParameters.tex'
#params.printLatex(RooFit.Sibling(initialParams),OutputFile(fileName))
params.printLatex(RooFit.OutputFile(fileName))

#Write just txt file of parameters
fileName = opts.get('RESULTDIR')+'CombFitParameters.txt'
comb_ws.pdf('comb_pdf').getParameters(comb_data).writeToFile(fileName)

#####################################################################################
# Write a summary of the fit configuration to a file
fileName = opts.get('RESULTDIR')+'CombFitSummary.txt'
f = open(fileName,'w')
print >> f, '#----------------------------------------#'
print >> f, '  This is the configuration for the fit:'
for name, val in opts.items(): print >> f, '  o) '+str(name)+' : '+str(val)
print >> f, '#----------------------------------------#'
print >> f, ' BRs = ', comb_ws.var("BRs").getVal(), ' +- ', comb_ws.var("BRs").getError()
print >> f, ' BRd = ', comb_ws.var("BRd").getVal(), ' +- ', comb_ws.var("BRd").getError()
print >> f, ' fdfs = ', comb_ws.var("fdfs").getVal() 
print >> f, '#----------------------------------------#'
f.close()
content =  open(fileName).read()
print content
