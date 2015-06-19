from ROOT import *
from ROOT import RooFit 

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

print ' CMS ready to fit!'

def fit():
    
    fin = TFile('CMS_ws_final.root')

    wspace = fin.Get('ws')
    
    pdf = wspace.pdf('pdf_ext_simul') # final simultaneous PDF
   
    data = wspace.data('global_data') # final data set
    
    ext_constr = RooArgSet(wspace.pdf('fs_over_fu_gau'),wspace.pdf('one_over_BRBR_gau')) # external Gaussian constraints
    
   # BF = RooArgSet(wspace.var('BF_bs'), wspace.var('BF_bd')) # two branching fractions, for minos calculations
  
    #wspace.var('Mass').SetNameTitle('BMass','BMass')
    
    #pdf.fitTo(data, RooFit.ExternalConstraints(ext_constr), RooFit.Strategy(2) ,RooFit.Extended(), RooFit.Minos(BF), RooFit.Hesse(1))
    pdf.fitTo(data, RooFit.ExternalConstraints(ext_constr), RooFit.Strategy(2) ,RooFit.Extended(), RooFit.Hesse(1))

    return wspace


