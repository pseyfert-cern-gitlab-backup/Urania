from BsDsMuNuForRDS.VarContainers import *

# First a function to assign the relevant branches when creating the Dalitz tuples.
def assignDalitzInputBranches(c):

    b = '%s_P%s'
    c.SetBranchAddress(b %('Kmi', 'X'), OSK_Px)
    c.SetBranchAddress(b %('Kmi', 'Y'), OSK_Py)
    c.SetBranchAddress(b %('Kmi', 'Z'), OSK_Pz)
    c.SetBranchAddress(b %('Kmi', 'E'), OSK_Pe)
    c.SetBranchAddress(b %('Kmi', ''),  OSK_P)
    
    c.SetBranchAddress(b %('Kpl', 'X'), SSK_Px)
    c.SetBranchAddress(b %('Kpl', 'Y'), SSK_Py)
    c.SetBranchAddress(b %('Kpl', 'Z'), SSK_Pz)
    c.SetBranchAddress(b %('Kpl', 'E'), SSK_Pe)
    c.SetBranchAddress(b %('Kpl', ''),  SSK_P)
    
    c.SetBranchAddress('Kmi_isMuon', OSK_isMuon)
    c.SetBranchAddress('Kpl_isMuon', SSK_isMuon)
    
    c.SetBranchAddress('Kpl_ProbNNk', SSK_ProbNNK)
    c.SetBranchAddress('Kpl_ProbNNp', SSK_ProbNNp)
    c.SetBranchAddress('Kmi_ProbNNk', OSK_ProbNNK)
    c.SetBranchAddress('Kmi_ProbNNp', OSK_ProbNNp)
    
    c.SetBranchAddress('Kmi_PIDK'   , OSK_PIDK)
    c.SetBranchAddress('Kmi_PIDp'   , OSK_PIDp)
    c.SetBranchAddress('Kpl_PIDK'   , SSK_PIDK)
    c.SetBranchAddress('Kpl_PIDp'   , SSK_PIDp)
    
    # Now the pions.
    c.SetBranchAddress(b %('pi', 'X'), pi_Px)
    c.SetBranchAddress(b %('pi', 'Y'), pi_Py)
    c.SetBranchAddress(b %('pi', 'Z'), pi_Pz)
    c.SetBranchAddress(b %('pi', 'E'), pi_Pe)
    c.SetBranchAddress(b %('pi', ''),  pi_P)
    c.SetBranchAddress('pi_isMuon', pi_isMuon)
    c.SetBranchAddress('pi_ProbNNk', pi_ProbNNK)

    # Now the muons.
    c.SetBranchAddress(b %('mu', 'X'), mu_Px)
    c.SetBranchAddress(b %('mu', 'Y'), mu_Py)
    c.SetBranchAddress(b %('mu', 'Z'), mu_Pz)
    c.SetBranchAddress(b %('mu', 'E'), mu_Pe)
    c.SetBranchAddress(b %('mu', ''),  mu_P)
    
    # Now the Ds mass.
    c.SetBranchAddress('Ds_M', Ds_M)

    return None


def assignDalitzOutputBranches(tOut):

    tOut.Branch("M_SSKpi", M_SSKpi, "M_SSKpi/D")
    tOut.Branch("M_OSKpi", M_OSKpi, "M_OSKpi/D")
    tOut.Branch("M_KK",    M_KK,    "M_KK/D")
    tOut.Branch("Ds_M",    Ds_M,    "Ds_M/D")
    tOut.Branch("resFlag", resFlag, "resFlag/I")
    
    tOut.Branch("Beta_OSK", Beta_OSK, "Beta_OSK/D")
    tOut.Branch("Beta_SSK", Beta_SSK, "Beta_SSK/D")
    tOut.Branch("Beta_pi",  Beta_pi,  "Beta_pi/D")
    
    tOut.Branch("WM_Lc_SSKasproton", WM_Lc_SSKasproton, "WM_Lc_SSKasproton/D")
    tOut.Branch("WM_Dp_SSKaspi",     WM_Dp_SSKaspi,     "WM_Dp_SSKaspi/D")
    
    tOut.Branch("WM_Dst_FullReco",        WM_Dst_FullReco,        "WM_Dst_FullReco/D")
    tOut.Branch("WM_Dst_SSKaspi_fromDz",  WM_Dst_SSKaspi_fromDz,  "WM_Dst_SSKaspi_fromDz/D")
    tOut.Branch("WM_Dst_SSKaspi_fromDst", WM_Dst_SSKaspi_fromDst, "WM_Dst_SSKaspi_fromDst/D")
    
    tOut.Branch('WM_Jpsi_piasmu',  WM_Jpsi_piasmu, 'WM_Jpsi_piasmu/D')
    tOut.Branch('WM_Jpsi_SSKasmu', WM_Jpsi_SSKasmu,'WM_Jpsi_SSKasmu/D')
    
    tOut.Branch("WM_Kstar_SSKaspi", WM_Kstar_SSKaspi, "WM_Kstar_SSKaspi/D")
    tOut.Branch("WM_Kstar_OSKaspi", WM_Kstar_OSKaspi, "WM_Kstar_OSKaspi/D")
    
    tOut.Branch("WM_phi_piasK", WM_phi_piasK, "WM_phi_piasK/D")
    tOut.Branch("WM_KS_OSKaspi", WM_KS_OSKaspi, "WM_KS_OSKaspi/D")
    
    # Now the PID entries we need to tune the selection.
    tOut.Branch('SSK_PIDK', SSK_PIDK, 'SSK_PIDK/D')
    tOut.Branch('SSK_PIDp', SSK_PIDp, 'SSK_PIDp/D')
    tOut.Branch('OSK_PIDK', OSK_PIDK, 'OSK_PIDK/D')
    tOut.Branch('OSK_PIDp', OSK_PIDp, 'OSK_PIDp/D')
    tOut.Branch('pi_PIDK', pi_PIDK, 'pi_PIDK/D')
    tOut.Branch('pi_PIDp', pi_PIDp, 'pi_PIDp/D')
    
    tOut.Branch('pi_isMuon', pi_isMuon, 'pi_isMuon/I')
    tOut.Branch('OSK_isMuon', OSK_isMuon, 'OSK_isMuon/I')
    tOut.Branch('SSK_isMuon', SSK_isMuon, 'SSK_isMuon/I')
    
    tOut.Branch('SSK_ProbNNk', SSK_ProbNNK, 'SSK_ProbNNk/D')
    tOut.Branch('SSK_ProbNNp', SSK_ProbNNp, 'SSK_ProbNNp/D')
    tOut.Branch('OSK_ProbNNk', OSK_ProbNNK, 'OSK_ProbNNk/D')
    tOut.Branch('OSK_ProbNNp', OSK_ProbNNp, 'OSK_ProbNNp/D')
    tOut.Branch('SSK_ProbNNp', SSK_ProbNNp, 'SSK_ProbNNp/D')
