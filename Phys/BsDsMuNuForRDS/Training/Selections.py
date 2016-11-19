##################################################################
## Module to contain selections for the analysis.
#################################################################

# The preselection to mimic the RDs selection closely on the Vub data.
cutStringVubasRDs = '(Kpl_PIDK > 4 && Kpl_PT > 300 && Kpl_MINIPCHI2 > 9 && Kmi_PIDK > 4 && Kmi_PT > 300 && Kmi_MINIPCHI2 > 9 && pi_PIDK < 2 && pi_PT > 300 && pi_MINIPCHI2 > 9 && mu_MINIPCHI2 > 16 && Ds_PT > 2500 && Ds_ENDVERTEX_CHI2 < 4 && Ds_DIRA_ORIVX > 0.999 && nLongTracks < 250 && nSPDHits < 600 && Ds_M > 1900)'

# The final veto for the charm reflections.
cutStringDsVetoes = "(resFlag == 0 && (((TMath::Abs(3096.916000 - WM_Jpsi_piasmu) > 50.0 || pi_isMuon==0)) && ((WM_Dst_FullReco > 190)) && ((WM_Dst_SSKaspi_fromDz > 190)) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 7)) && (1) && ((WM_Dst_SSKaspi_fromDst > 190)) && ((TMath::Abs(3096.916000 - WM_Jpsi_SSKasmu) > 50.0  || SSK_isMuon==0)) ) && ((1)) ) || (resFlag == 1 && (((TMath::Abs(3096.916000 - WM_Jpsi_piasmu) > 50.0 || pi_isMuon==0)) && ((WM_Dst_FullReco > 190)) && ((WM_Dst_SSKaspi_fromDz > 190)) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 10)) && (((TMath::Abs(1869.570000 - WM_Dp_SSKaspi) > 30 && TMath::Abs(1968.300000 - WM_Dp_SSKaspi) > 30 ) || SSK_PIDK > 8) ) && ((WM_Dst_SSKaspi_fromDst > 190)) && ((TMath::Abs(3096.916000 - WM_Jpsi_SSKasmu) > 50.0  || SSK_isMuon==0)) ) && ((SSK_ProbNNk > 0.25 && OSK_ProbNNk > 0.25)) ) || (resFlag == 2 && (((TMath::Abs(3096.916000 - WM_Jpsi_piasmu) > 50.0 || pi_isMuon==0)) && ((WM_Dst_FullReco > 190)) && ((WM_Dst_SSKaspi_fromDz > 190)) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 12)) && (((TMath::Abs(1869.570000 - WM_Dp_SSKaspi) > 30 && TMath::Abs(1968.300000 - WM_Dp_SSKaspi) > 30 ) || SSK_PIDK > 8) ) && ((WM_Dst_SSKaspi_fromDst > 190)) && ((TMath::Abs(3096.916000 - WM_Jpsi_SSKasmu) > 50.0  || SSK_isMuon==0)) ) && ((SSK_ProbNNk > 0.3 && OSK_ProbNNk > 0.3 && pi_PIDK < 8)))"

# The preselection to speed up offline processing.
preselectionCut = '(Bs_0_MCORR < 8e3)'

# A cut to isolate the Ds mass sidebands for my background studies.
DsSidebandCut = '( TMath::Abs(1968.30 - Ds_M) > 30.0)'
