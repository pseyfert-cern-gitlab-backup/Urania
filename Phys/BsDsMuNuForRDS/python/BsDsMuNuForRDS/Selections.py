##################################################################
## Module to contain selections for the Bs2Ds measurements.
#################################################################
import sys
#from BsDsMuNuForRDS.Constants import M_Ds, M_Ds_Width

#################################################################
# Charm reflection vetoes
#################################################################
# The final veto for the charm reflections.
cutStringDsVetoesFull = "( (resFlag == 0 && (((TMath::Abs(3096.916000 - WM_Jpsi_piasmu) > 50.0 || pi_isMuon==0)) && ((WM_Dst_FullReco > 190)) && ((WM_Dst_SSKaspi_fromDz > 190)) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 7)) && (1) && ((WM_Dst_SSKaspi_fromDst > 190)) && ((TMath::Abs(3096.916000 - WM_Jpsi_SSKasmu) > 50.0  || SSK_isMuon==0)) ) ) || (resFlag == 1 && (((TMath::Abs(3096.916000 - WM_Jpsi_piasmu) > 50.0 || pi_isMuon==0)) && ((WM_Dst_FullReco > 190)) && ((WM_Dst_SSKaspi_fromDz > 190)) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 10)) && (((TMath::Abs(1869.570000 - WM_Dp_SSKaspi) > 30 && TMath::Abs(1968.300000 - WM_Dp_SSKaspi) > 30 ) || SSK_PIDK > 8) ) && ((WM_Dst_SSKaspi_fromDst > 190)) && ((TMath::Abs(3096.916000 - WM_Jpsi_SSKasmu) > 50.0  || SSK_isMuon==0)) ) ))"
# And a version without the muon PID cuts.
cutStringDsVetoesNoMuon = "( (resFlag == 0 && ( (WM_Dst_FullReco > 190) && (WM_Dst_SSKaspi_fromDz > 190) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 7)) && (WM_Dst_SSKaspi_fromDst > 190) ) ) || (resFlag == 1 && (WM_Dst_FullReco > 190) && (WM_Dst_SSKaspi_fromDz > 190) && ((TMath::Abs(2286.460000 - WM_Lc_SSKasproton) > 33 || (SSK_PIDK - SSK_PIDp) > 10)) && ((TMath::Abs(1869.570000 - WM_Dp_SSKaspi) > 30 && TMath::Abs(1968.300000 - WM_Dp_SSKaspi) > 30) || SSK_PIDK > 8) && (WM_Dst_SSKaspi_fromDst > 190) ) )"

#################################################################
# Trigger requirements and trigger mimicking.
#################################################################
# The Hlt2 cut in the primary analysis.
triggerCutRDS     = '(Bs_0_Hlt2XcMuXForTauB2XcMuDecision_TOS==1)'
# The cut to mimic the trigger cut on the MC which doesn't have the Hlt2 trigger line info.
triggerCutMimic   = '(Kpl_PIDK > 4 && Kpl_PT > 300 && Kpl_MINIPCHI2 > 9 && Kmi_PIDK > 4 && Kmi_PT > 300 && Kmi_MINIPCHI2 > 9 && pi_PIDK < 2 && pi_PT > 300 && pi_MINIPCHI2 > 9 && mu_MINIPCHI2 > 16 && Ds_PT > 2500 && Ds_ENDVERTEX_CHI2 < 4 && Ds_DIRA_ORIVX > 0.999 && nLongTracks < 250 && nSPDHits < 600 && Ds_M > 1900)'

#################################################################
# General preselection and sanity cuts.
#################################################################
# The preselection to speed up offline processing.
preselectionCut = '(Bs_0_MCORR < 8e3)'
muPID           = '(mu_PIDmu > -4)'
kaonPID         = '(Kmi_ProbNNk > 0.18 && Kpl_ProbNNk > 0.16)'
# A cut to remove candidates where any of the tracks have error values on the ProbNN candidates.
KplPIDSanityCuts = '(Kpl_ProbNNp > 0 && Kpl_ProbNNk > 0 && Kpl_ProbNNpi > 0 && Kpl_ProbNNghost > 0)'
KmiPIDSanityCuts = '(Kmi_ProbNNp > 0 && Kmi_ProbNNk > 0 && Kmi_ProbNNpi > 0 && Kmi_ProbNNghost > 0)'
piPIDSanityCuts  = '(pi_ProbNNp > 0 && pi_ProbNNk > 0 && pi_ProbNNpi > 0 && pi_ProbNNghost > 0)'
muPIDSanityCuts  = '(mu_ProbNNp > 0 && mu_ProbNNk > 0 && mu_ProbNNpi > 0 && mu_ProbNNghost > 0)'
PIDSanityCuts    = '(%s && %s && %s && %s)' %(KplPIDSanityCuts, KmiPIDSanityCuts, piPIDSanityCuts, muPIDSanityCuts)
# A cut to remove the non-resonant Ds2KKpi decay.
DsResonantCut = '( (TMath::Abs(TMath::Sqrt(Ds_Dalitz_Kminus_Kplus_M2)-1019.461)<20) || (TMath::Abs(TMath::Sqrt(Ds_Dalitz_Kminus_piplus_M2)-891.66)<90) )'

#################################################################
# MC truth-matching cuts.
#################################################################
# Import the generic truth cuts for signal and double charm
# from the TruthCuts module.
from BsDsMuNuForRDS.TruthCuts import isSignal, isDoubleCharm
truthCutDict = {
    'signal'       : isSignal
    ,'doubleCharm' : isDoubleCharm
    }

# Now a dictionary of cuts for the individual data tags.
# We want to automatically populate this dictionary based on the specified configuration.
# For each dataTag we build a dictionary of 4 cuts:
# - no vetoes and with muon cuts.
# - no vetoes and no muon cuts.
# - with vetoes and with muon cuts.
# - with vetoes and no muon cuts.
# We need versions without Ds vetoes as preselection for making the wrong mass scripts.
# We need versions without any muon ID for the muon fake tuples.
selectionCutDict = {}
from BsDsMuNuForRDS.Configuration import configurationDict
for dataTag in configurationDict.keys():
    config = configurationDict[dataTag]
    cutComponents          = []
    # For all cases we want to add the preselection.
    cutComponents.append(preselectionCut)
    cutComponents.append(PIDSanityCuts)
    cutComponents.append(DsResonantCut)
    cutComponents.append(kaonPID)
    #if 'truthMatch' in config.keys():
    #    truthCut = truthCutDict[config['truthMatch']]
    #    cutComponents.append(truthCut)

    # Now clone the list and add the muon PID to the
    # appropriate list.
    cutComponentsNoMuonPIDNoVetoes   = list(cutComponents)
    cutComponentsWithMuonPIDNoVetoes = list(cutComponents)
    cutComponentsWithMuonPIDNoVetoes.append(muPID)

    # Now we want equivalents but with the appropriate vetoes added.
    cutComponentsNoMuonPIDWithVetoes = list(cutComponentsNoMuonPIDNoVetoes)
    cutComponentsNoMuonPIDWithVetoes.append(cutStringDsVetoesNoMuon)

    cutComponentsWithMuonPIDWithVetoes = list(cutComponentsWithMuonPIDNoVetoes)
    cutComponentsWithMuonPIDWithVetoes.append(cutStringDsVetoesFull)

    # Now combine them all and append to the selectionCutDict.
    combinedCutNoMuonPIDNoVetoes = '(' + ' && '.join(cutComponentsNoMuonPIDNoVetoes) + ')'
    combinedCutWithMuonPIDNoVetoes = '(' + ' && '.join(cutComponentsWithMuonPIDNoVetoes) + ')'

    combinedCutNoMuonPIDWithVetoes = '(' + ' && '.join(cutComponentsNoMuonPIDWithVetoes) + ')'
    combinedCutWithMuonPIDWithVetoes = '(' + ' && '.join(cutComponentsWithMuonPIDWithVetoes) + ')'

    selectionCutDict[dataTag] = {
        'noVetoesNoMuonPID'      : combinedCutNoMuonPIDNoVetoes
        ,'withVetoesNoMuonPID'   : combinedCutNoMuonPIDWithVetoes
        ,'noVetoesWithMuonPID'   : combinedCutWithMuonPIDNoVetoes
        ,'withVetoesWithMuonPID' : combinedCutWithMuonPIDWithVetoes
        }
    
#################################################################
# FUNCS - functions to use these.
#################################################################
def getTruthCut(dataTag):
    '''
    Simple function to return the truth cut for the MC modes.
    '''
    cutKey = configurationDict[dataTag]['truthMatch']
    return truthCutDict[cutKey]

def getCutStringNoDsVetoes(dataTag, tName="B2DsMuNuTuple/DecayTree"):
    '''
    Function to return the cuts without the Ds vetoes.
    We use this to lower the amount of candidates for which
    we must calculate the wrong-mass and Dalitz variables.
    '''
    if dataTag not in selectionCutDict.keys():
        sys.exit('BsDsMuNuForRDS.Selections ERROR: dataTag not recognised.')
    # If a fake muon line apply no muon PID.    
    if tName == 'B2DsMuNuTupleFake/DecayTree' or tName == 'B2DsMuNuSSTupleFake/DecayTree':
        theCut = selectionCutDict[dataTag]['noVetoesNoMuonPID']
    else:
        theCut = selectionCutDict[dataTag]['noVetoesWithMuonPID']
    # If not a fake muon or SS line, apply truth matching.
    if tName=="B2DsMuNuTuple/DecayTree":
        truthCut = getTruthCut(dataTag)
        theCut   = '( %s && %s )' %(truthCut, theCut)
    print '-- Selections.getCutStringNoDsVetoes: returns cut:'
    print '----', theCut
    return theCut

def getCutStringOnlyDsVetoes(dataTag, tName="B2DsMuNuTuple/DecayTree"):
    '''
    Function to return only the Ds vetoes.
    '''
    if tName == 'B2DsMuNuTupleFake/DecayTree' or tName == 'B2DsMuNuSSTupleFake/DecayTree':
        print cutStringDsVetoesNoMuon
        return cutStringDsVetoesNoMuon
    else:
        return cutStringDsVetoesFull
    
def getCutStringWithDsVetoes(dataTag, tName="B2DsMuNuTuple/DecayTree"):
    '''
    Function to return the cuts with the Ds vetoes.
    '''
    if dataTag not in selectionCutDict.keys():
        sys.exit('BsDsMuNuForRDS.Selections ERROR: dataTag not recognised.')
    # If a fake muon line apply no muon PID.
    if tName == 'B2DsMuNuTupleFake/DecayTree' or tName == 'B2DsMuNuSSTupleFake/DecayTree':
        theCut = selectionCutDict[dataTag]['withVetoesNoMuonPID']
    else:
        theCut = selectionCutDict[dataTag]['withVetoesWithMuonPID']
    # If not a fake muon or SS line, apply truth matching.
    if tName=="B2DsMuNuTuple/DecayTree":
        truthCut = getTruthCut(dataTag)
        theCut   = '( %s && %s )' %(truthCut, theCut)
    print '-- Selections.getCutStringWithDsVetoes: returns cut:'
    print '----', theCut
    return theCut
