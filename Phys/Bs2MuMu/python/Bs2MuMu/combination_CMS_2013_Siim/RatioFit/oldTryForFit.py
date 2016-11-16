from ROOT import *
from ROOT import RooFit
from ROOT import RooStats

from SomeMassModels import RooPhysBkg #Run on LxPlus

#from SomeMassModelsLocal import RooPhysBkg #Run on laptop
#To run on laptop, you need to give the PATH in the local folder
#SomeMassModels __init__.py

#Make RooFit quiet
print 'Importing done!'
RooFit.gErrorIgnoreLevel = kError
RooMsgService.instance().setGlobalKillBelow(RooFit.ERROR)
print ' errors disabled'

#Main WARNING:
#0] WARNING:Eval -- RooAbsPdf::getLogVal(PiMuNuShc4_const) WARNING: large likelihood value: 6.7937e+11

print ' CMS/LHCB ready to fit!'

def getFitArgs(offset = 1, nCPU = 8):

    def_arg_list = RooLinkedList()
    #def_arg_list.Add(RooFit.Minos(kTRUE))
    def_arg_list.Add(RooFit.Strategy(2))
    def_arg_list.Add(RooFit.Save()) #Save result
    def_arg_list.Add(RooFit.Hesse(1))
    def_arg_list.Add(RooFit.NumCPU(nCPU))
    def_arg_list.Add(RooFit.Optimize(1))
    def_arg_list.Add(RooFit.Offset(offset))
    def_arg_list.Add(RooFit.Verbose(0))
    def_arg_list.Add(RooFit.Extended())
    def_arg_list.Add(RooFit.Timer(1)) #Times the CPU and wall clock consumption
    #def_arg_list.Add(RooFit.PrintLevel(3))

    return def_arg_list


#Variables           Meaning                                     Comments
#=====================================================================================
#BF_bd               Branching fraction of Bd
#BF_bs               Branching fraction of Bs
#B_1comb_i_j         Combinatorial background slope in each bin
#N_bu_i_j            N(B+) in each bin                           Constrained/Gaussian
#N_comb_i_j          # of combinatorial background in each bin
#N_peak_i_j          # of peaking background in each bin         Constrained/Lognormal
#N_semi_i_j          # of semileptonic background in each bin    Constrained/Gaussian
#effratio_bd_i_j     relative efficiencies for Bd in each bin    Constrained/Gaussian
#effratio_bs_i_j     relative efficiencies for Bs in each bin    Constrained/Gaussian
#fs_over_fu          fs/fu                                       Constrained/Gaussian
#one_over_BRBR       1/BF(B+ .J/psi K+)/BF(J/psi . mumu)       Constrained/Gaussian


def fit_CMS(offset=1, nCPU=8, fixBRs = 0, fixBRd = 0):

    fin = TFile('ws_revised_20140104.root')

    wspace = fin.Get('ws')

    pdf = wspace.pdf('pdf_ext_simul') # final simultaneous PDF

    data = wspace.data('global_data') # final data set

    ext_constr = RooArgSet(wspace.pdf('fs_over_fu_gau'),wspace.pdf('one_over_BRBR_gau')) # external Gaussian constraints

    if fixBRd and not fixBRs:
        wspace.var('BF_bd').setVal(0.)
        wspace.var('BF_bd').setConstant(1)
        BF = RooArgSet(wspace.var('BF_bs')) # two branching fractions, for minos calculations

    if fixBRs and not fixBRd:
        wspace.var('BF_bs').setVal(0.)
        wspace.var('BF_bs').setConstant(1)
        BF = RooArgSet(wspace.var('BF_bd')) # two branching fractions, for minos calculations
    if fixBRd and fixBRs:
        wspace.var('BF_bd').setVal(0.)
        wspace.var('BF_bs').setVal(0.)
        wspace.var('BF_bd').setConstant(1)
        wspace.var('BF_bs').setConstant(1)
    else:
        BF = RooArgSet(wspace.var('BF_bs'), wspace.var('BF_bd')) # two branching fractions, for minos calculations

    arg_list = getFitArgs(offset, nCPU)
    arg_list.Add(RooFit.ExternalConstraints(ext_constr))
    arg_list.Add(RooFit.Minos(BF))
    #Create the NLL object
    nll = pdf.createNLL(data, arg_list)
    #Fit and save the fitResult
    fitRes = pdf.fitTo(data, arg_list)

    #Write the fitResult
    fRes = TFile("fitResult_CMS.root","RECREATE")
    fitRes.Write("fitResult_CMS")
    fRes.Close()


    return [wspace, nll, fitRes]

def fit_LHCb(offset = 1, nCPU = 8):

    fin = TFile('lhcb_ws_26022014.root')

    wspace = fin.Get('lhcb_ws')

    pdf = wspace.pdf('lhcb_pdf') # final simultaneous PDF

    data = wspace.data('lhcb_data') # final data set

    ext_constr = wspace.set('lhcb_cons')

    wspace.var('BRs').setVal(1.)
    wspace.var('BRd').setVal(1.)
    BF = RooArgSet(wspace.var('BRs'), wspace.var('BRd')) # two branching fractions, for minos calculations

    arg_list = getFitArgs(offset,nCPU)
    arg_list.Add(RooFit.ExternalConstraints(ext_constr))
    arg_list.Add(RooFit.Minos(BF))
    #if 'fit' in raw_input(' LHCb ready to fit! Type fit to fit : '):
    nll = pdf.createNLL(data, arg_list)
    fitRes = pdf.fitTo(data, arg_list)

    #Write the fitResult
    fRes = TFile("fitResult_LHCb.root","RECREATE")
    fitRes.Write("fitResult_LHCb")
    fRes.Close()

    return [wspace, nll, fitRes]


def addModelConfig():

    fileName = 'ws_revised_20140104'

    fin = TFile(fileName+'.root')
    wspace = fin.Get('ws')
    pdf = wspace.pdf('pdf_ext_simul') # final simultaneous PDF
    data = wspace.data('global_data') # final data set

    mc = RooStats.ModelConfig("ModelConfig",wspace)
    mc.SetPdf(pdf)
    mc.SetParametersOfInterest(RooArgSet(wspace.var("BF_bd"), wspace.var("BF_bs")))

    mc.SetObservables(RooArgSet(wspace.var("m_{#mu#mu}")))
    #mc.SetObservables(wspace.set('obs'))

    #define set of nuisance parameters
    wspace.defineSet("nuisParams","Alpha_bd_0_0,Alpha_bd_0_1,Alpha_bd_1_0,Alpha_bd_1_1,Alpha_bd_2_0,Alpha_bd_2_1,Alpha_bd_2_2,Alpha_bd_2_3,Alpha_bd_3_0,Alpha_bd_3_1,Alpha_bd_3_2,Alpha_bd_3_3,Alpha_bs_0_0,Alpha_bs_0_1,Alpha_bs_1_0,Alpha_bs_1_1,Alpha_bs_2_0,Alpha_bs_2_1,Alpha_bs_2_2,Alpha_bs_2_3,Alpha_bs_3_0,Alpha_bs_3_1,Alpha_bs_3_2,Alpha_bs_3_3,Alpha_peak_0_0,Alpha_peak_0_1,Alpha_peak_1_0,Alpha_peak_1_1,Alpha_peak_2_0,Alpha_peak_2_1,Alpha_peak_2_2,Alpha_peak_2_3,Alpha_peak_3_0,Alpha_peak_3_1,Alpha_peak_3_2,Alpha_peak_3_3,Btr_1comb_0_0,Btr_1comb_0_1,Btr_1comb_1_0,Btr_1comb_1_1,Btr_1comb_2_0,Btr_1comb_2_1,Btr_1comb_2_2,Btr_1comb_2_3,Btr_1comb_3_0,Btr_1comb_3_1,Btr_1comb_3_2,Btr_1comb_3_3,CoeffGauss_peak_0_0,CoeffGauss_peak_0_1,CoeffGauss_peak_1_0,CoeffGauss_peak_1_1,CoeffGauss_peak_2_0,CoeffGauss_peak_2_1,CoeffGauss_peak_2_2,CoeffGauss_peak_2_3,CoeffGauss_peak_3_0,CoeffGauss_peak_3_1,CoeffGauss_peak_3_2,CoeffGauss_peak_3_3,Enne_bd_0_0,Enne_bd_0_1,Enne_bd_1_0,Enne_bd_1_1,Enne_bd_2_0,Enne_bd_2_1,Enne_bd_2_2,Enne_bd_2_3,Enne_bd_3_0,Enne_bd_3_1,Enne_bd_3_2,Enne_bd_3_3,Enne_bs_0_0,Enne_bs_0_1,Enne_bs_1_0,Enne_bs_1_1,Enne_bs_2_0,Enne_bs_2_1,Enne_bs_2_2,Enne_bs_2_3,Enne_bs_3_0,Enne_bs_3_1,Enne_bs_3_2,Enne_bs_3_3,Enne_peak_0_0,Enne_peak_0_1,Enne_peak_1_0,Enne_peak_1_1,Enne_peak_2_0,Enne_peak_2_1,Enne_peak_2_2,Enne_peak_2_3,Enne_peak_3_0,Enne_peak_3_1,Enne_peak_3_2,Enne_peak_3_3,Mean_bd_0_0,Mean_bd_0_1,Mean_bd_1_0,Mean_bd_1_1,Mean_bd_2_0,Mean_bd_2_1,Mean_bd_2_2,Mean_bd_2_3,Mean_bd_3_0,Mean_bd_3_1,Mean_bd_3_2,Mean_bd_3_3,Mean_bs_0_0,Mean_bs_0_1,Mean_bs_1_0,Mean_bs_1_1,Mean_bs_2_0,Mean_bs_2_1,Mean_bs_2_2,Mean_bs_2_3,Mean_bs_3_0,Mean_bs_3_1,Mean_bs_3_2,Mean_bs_3_3,Mean_peak_0_0,Mean_peak_0_1,Mean_peak_1_0,Mean_peak_1_1,Mean_peak_2_0,Mean_peak_2_1,Mean_peak_2_2,Mean_peak_2_3,Mean_peak_3_0,Mean_peak_3_1,Mean_peak_3_2,Mean_peak_3_3,N_bu_0_0,N_bu_0_1,N_bu_1_0,N_bu_1_1,N_bu_2_0,N_bu_2_1,N_bu_2_2,N_bu_2_3,N_bu_3_0,N_bu_3_1,N_bu_3_2,N_bu_3_3,N_peak_0_0,N_peak_0_1,N_peak_1_0,N_peak_1_1,N_peak_2_0,N_peak_2_1,N_peak_2_2,N_peak_2_3,N_peak_3_0,N_peak_3_1,N_peak_3_2,N_peak_3_3,Nsq_comb_0_0,Nsq_comb_0_1,Nsq_comb_1_0,Nsq_comb_1_1,Nsq_comb_2_0,Nsq_comb_2_1,Nsq_comb_2_2,Nsq_comb_2_3,Nsq_comb_3_0,Nsq_comb_3_1,Nsq_comb_3_2,Nsq_comb_3_3,Nsq_semi_0_0,Nsq_semi_0_1,Nsq_semi_1_0,Nsq_semi_1_1,Nsq_semi_2_0,Nsq_semi_2_1,Nsq_semi_2_2,Nsq_semi_2_3,Nsq_semi_3_0,Nsq_semi_3_1,Nsq_semi_3_2,Nsq_semi_3_3,PeeK_bd_0_0,PeeK_bd_0_1,PeeK_bd_1_0,PeeK_bd_1_1,PeeK_bd_2_0,PeeK_bd_2_1,PeeK_bd_2_2,PeeK_bd_2_3,PeeK_bd_3_0,PeeK_bd_3_1,PeeK_bd_3_2,PeeK_bd_3_3,PeeK_bs_0_0,PeeK_bs_0_1,PeeK_bs_1_0,PeeK_bs_1_1,PeeK_bs_2_0,PeeK_bs_2_1,PeeK_bs_2_2,PeeK_bs_2_3,PeeK_bs_3_0,PeeK_bs_3_1,PeeK_bs_3_2,PeeK_bs_3_3,Sigma2_peak_0_0,Sigma2_peak_0_1,Sigma2_peak_1_0,Sigma2_peak_1_1,Sigma2_peak_2_0,Sigma2_peak_2_1,Sigma2_peak_2_2,Sigma2_peak_2_3,Sigma2_peak_3_0,Sigma2_peak_3_1,Sigma2_peak_3_2,Sigma2_peak_3_3,Sigma_peak_0_0,Sigma_peak_0_1,Sigma_peak_1_0,Sigma_peak_1_1,Sigma_peak_2_0,Sigma_peak_2_1,Sigma_peak_2_2,Sigma_peak_2_3,Sigma_peak_3_0,Sigma_peak_3_1,Sigma_peak_3_2,Sigma_peak_3_3,effratio_bd_0_0,effratio_bd_0_1,effratio_bd_1_0,effratio_bd_1_1,effratio_bd_2_0,effratio_bd_2_1,effratio_bd_2_2,effratio_bd_2_3,effratio_bd_3_0,effratio_bd_3_1,effratio_bd_3_2,effratio_bd_3_3,effratio_bs_0_0,effratio_bs_0_1,effratio_bs_1_0,effratio_bs_1_1,effratio_bs_2_0,effratio_bs_2_1,effratio_bs_2_2,effratio_bs_2_3,effratio_bs_3_0,effratio_bs_3_1,effratio_bs_3_2,effratio_bs_3_3,fs_over_fu,one_over_BRBR")

    #Test the nuisance parameters
    wspace.set('nuisParams').Print()

    mc.SetNuisanceParameters(wspace.set("nuisParams"))

    #Save a snapshot
    wspace.saveSnapshot("nominalNuis",wspace.set('nuisParams'),kTRUE)

    #Import the ModelConfig
    getattr(wspace,'import')(mc)
    wspace.writeToFile(fileName+'_ModelConf.root')

    return wspace


