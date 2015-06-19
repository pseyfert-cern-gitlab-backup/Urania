using namespace RooFit;

/*
Variables           Meaning                                     Comments
=====================================================================================
BF_bd               Branching fraction of Bd
BF_bs               Branching fraction of Bs
B_1comb_i_j         Combinatorial background slope in each bin
N_bu_i_j            N(B+) in each bin                           Constrained/Gaussian  
N_comb_i_j          # of combinatorial background in each bin
N_peak_i_j          # of peaking background in each bin         Constrained/Lognormal 
N_semi_i_j          # of semileptonic background in each bin    Constrained/Gaussian  
effratio_bd_i_j     relative efficiencies for Bd in each bin    Constrained/Gaussian
effratio_bs_i_j     relative efficiencies for Bs in each bin    Constrained/Gaussian
fs_over_fu          fs/fu                                       Constrained/Gaussian
one_over_BRBR       1/BF(B+ ->J/psi K+)/BF(J/psi -> mumu)       Constrained/Gaussian
*/
 
void fit()
{
    TFile *fin = new TFile("ws_final.root");
    RooWorkspace *wspace = (RooWorkspace*)fin->Get("ws");
    
    RooAbsPdf *pdf = wspace->pdf("pdf_ext_simul"); // final simultaneous PDF
    
    RooAbsData *data = wspace->data("global_data"); // final data set
    
    RooArgSet ext_constr(*wspace->pdf("fs_over_fu_gau"),*wspace->pdf("one_over_BRBR_gau")); // external Gaussian constraints
    
    RooArgSet BF(*wspace->var("BF_bs"), *wspace->var("BF_bd")); // two branching fractions, for minos calculations
    
    pdf->fitTo(*data, ExternalConstraints(ext_constr), Strategy(2) ,Extended(), Minos(BF), Hesse(1));
}