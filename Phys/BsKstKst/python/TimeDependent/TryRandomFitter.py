from FitnGen import *

ForceCompileLibs()

data, hist_mistag_SSK, hist_mistag_OS, hist_deltat = loadData(NTUPLE_PATH,data_type,data_file,data_tree,MC_file,MC_tree,MC_type,TD_fit,sweighted,wide_window,extra_cuts,evnum_limit,use_GRID)

setParamVals(wide_window)
#for par in [reA00,reA01,reA10,imA00,imA01,imA10]:
#	par.setVal(0.)
#	par.setConstant(1)

model, params = createSimPDF(TD_fit,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

ll = ROOT.RooNLLVar("ll","ll",model[0],data[0],ROOT.RooFit.NumCPU(30))

ROOT.gROOT.ProcessLine('.L ../../src/TimeDependent/RooMinuitMCMC.cpp++')

minimizer = ROOT.RooMinuitMCMC(ll)

minimizer.mcmc(10000,0)

for i in params: print '\t\t'+i.GetName()+'.setVal('+str(i.getVal())+')'
