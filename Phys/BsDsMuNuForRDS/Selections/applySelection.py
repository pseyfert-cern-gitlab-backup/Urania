from BsDsMuNuForRDS.Selections    import getCutStringNoDsVetoes, getCutStringWithDsVetoes, getCutStringOnlyDsVetoes
from BsDsMuNuForRDS.Configuration import configurationDict
from BsDsMuNuForRDS.DataRetrieval import *
from BsDsMuNuForRDS.Constants     import *
import sys, os, array, numpy
from ROOT import TFile, TTree, gROOT, gDirectory, TLorentzVector, TVector3, TMVA
gROOT.SetBatch(True)
####################################################################
# Some settings
####################################################################
#dataTags = ['MC_LbLcDs', 'MC_BdDstDs', 'MC_BsDsDs', 'MC_BuD0Ds']
#dataTags = ['MC_Signal', 'MC_LbLcDs', 'MC_BdDstDs', 'MC_BsDsDs', 'MC_BuD0Ds', 'MC_InclDs', 'Data']
dataTags = ['MC_Tau', 'MC_Signal', 'MC_LbLcDs', 'MC_BdDstDs', 'MC_BsDsDs', 'MC_BuD0Ds']
polarities = ['MagUp', 'MagDown']
# If command line arguments are specified overwrite these.
if len(sys.argv) == 2:
    dataTags   = [sys.argv[1]]
    #polarities = [sys.argv[2]]

isMC = False
mB_PDG  = 5366.79 # in MeV/c^{2}
mDs_PDG = 1968.30

####################################################################
# Some containers for the ntuple variables.
####################################################################
from BsDsMuNuForRDS.VarContainers import *

#########################################################
# Loop over the requested data and polarities.
#########################################################
for dataTag in dataTags:
    # Get the Dalitz file.
    fFriendName = getEOSDalitzFile(dataTag)
    fFriend = TFile.Open(fFriendName)
    
    # Make the new file.
    fOutName = getLocalPostSelectionFileName(dataTag)
    fOut = TFile(fOutName, 'recreate')
    
    # Now iterate over each tree in the file.
    for tName in configurationDict[dataTag]['tNames']:

        if ignoreFakes:
            if tName != 'B2DsMuNuTuple/DecayTree': continue

        # Get the original tuple.
        # Then set the branches we need to calculate the new vars.
        c = getChainWithTupleName(dataTag, tName)

        # Set mu kin vars
        c.SetBranchAddress('Bs_0_M', mB)
        c.SetBranchAddress('Bs_0_PZ', pzB)
        c.SetBranchAddress('Bs_0_OWNPV_X', PVx)
        c.SetBranchAddress('Bs_0_OWNPV_Y', PVy)
        c.SetBranchAddress('Bs_0_OWNPV_Z', PVz)
        c.SetBranchAddress('Bs_0_ENDVERTEX_X', BVx)
        c.SetBranchAddress('Bs_0_ENDVERTEX_Y', BVy)
        c.SetBranchAddress('Bs_0_ENDVERTEX_Z', BVz)
        c.SetBranchAddress('mu_PX', muPx)
        c.SetBranchAddress('mu_PY', muPy)
        c.SetBranchAddress('mu_PZ', muPz)
        c.SetBranchAddress('mu_PE', muPe)
        c.SetBranchAddress('Ds_PX', DPx)
        c.SetBranchAddress('Ds_PY', DPy)
        c.SetBranchAddress('Ds_PZ', DPz)
        c.SetBranchAddress('Ds_PE', DPe)
        
        # Set trigger vars
        c.SetBranchAddress('Kpl_P', Kpl_P)
        c.SetBranchAddress('Kmi_P', Kmi_P)
        c.SetBranchAddress('pi_P', pi_P)
        c.SetBranchAddress('Kpl_PT', Kpl_PT)
        c.SetBranchAddress('Kmi_PT', Kmi_PT)
        c.SetBranchAddress('pi_PT', pi_PT)
        c.SetBranchAddress('Ds_PT', Ds_PT)
        #c.SetBranchAddress('Bs_0_BDTS_DOCA', Bs_0_BDTS_DOCA)
        c.SetBranchAddress('Bs_0_FDCHI2_TOPPV', Bs_0_FDCHI2_TOPPV)
        c.SetBranchAddress('Ds_MM', Ds_MM)
        
        # Set excited charm vars.
        if not 'MB2DsMuNuTuple' in tName:
            c.SetBranchAddress('Ds_0.40_nc_maxPt_PE', Ds_0_40_nc_maxPt_PE)
            c.SetBranchAddress('Ds_0.40_nc_maxPt_PX', Ds_0_40_nc_maxPt_PX)
            c.SetBranchAddress('Ds_0.40_nc_maxPt_PY', Ds_0_40_nc_maxPt_PY)
            c.SetBranchAddress('Ds_0.40_nc_maxPt_PZ', Ds_0_40_nc_maxPt_PZ)
            
            c.SetBranchAddress('Ds_0.40_nc_secPt_PE', Ds_0_40_nc_secPt_PE)
            c.SetBranchAddress('Ds_0.40_nc_secPt_PX', Ds_0_40_nc_secPt_PX)
            c.SetBranchAddress('Ds_0.40_nc_secPt_PY', Ds_0_40_nc_secPt_PY)
            c.SetBranchAddress('Ds_0.40_nc_secPt_PZ', Ds_0_40_nc_secPt_PZ)
            
            c.SetBranchAddress('Ds_0.40_pi0_maxPt_PE', Ds_0_40_pi0_maxPt_PE)
            c.SetBranchAddress('Ds_0.40_pi0_maxPt_PX', Ds_0_40_pi0_maxPt_PX)
            c.SetBranchAddress('Ds_0.40_pi0_maxPt_PY', Ds_0_40_pi0_maxPt_PY)
            c.SetBranchAddress('Ds_0.40_pi0_maxPt_PZ', Ds_0_40_pi0_maxPt_PZ)

        if isMC:
            c.SetBranchAddress('Bs_0_TRUEP_X', pxBT)
            c.SetBranchAddress('Bs_0_TRUEP_Y', pyBT)
            c.SetBranchAddress('Bs_0_TRUEP_Z', pzBT)
            c.SetBranchAddress('Bs_0_TRUEP_E', peBT)
            c.SetBranchAddress('mu_TRUEP_X', muPxT)
            c.SetBranchAddress('mu_TRUEP_Y', muPyT)
            c.SetBranchAddress('mu_TRUEP_Z', muPzT)
            c.SetBranchAddress('mu_TRUEP_E', muPeT)
            c.SetBranchAddress('Ds_TRUEP_X', DPxT)
            c.SetBranchAddress('Ds_TRUEP_Y', DPyT)
            c.SetBranchAddress('Ds_TRUEP_Z', DPzT)
            c.SetBranchAddress('Ds_TRUEP_E', DPeT)
            
        # Make the TDirectory.
        dirName  = tName.split('/')[0]
        tNameEnd = tName.split('/')[1]
        
        theDir = fOut.mkdir(dirName)
        theDir.cd()
        
        # Make the new tree and add the relevant variables.
        tNew = c.CloneTree(0)

        # Muon reconstructed kinematics
        tNew.Branch('q2', q2, 'q2/D')
        tNew.Branch('Emu', Emu, 'Emu/D')
        tNew.Branch('MM2', MM2, 'MM2/D')
        
        # Neutral vars.
        tNew.Branch('MassDsG1_0_40', MassDsG1_0_40, 'MassDsG1_0_40/D')
        tNew.Branch('MassDsG2_0_40', MassDsG2_0_40, 'MassDsG2_0_40/D')
        tNew.Branch('isGamma1InCone', isGamma1InCone, 'isGamma1InCone/I')
        tNew.Branch('isGamma2InCone', isGamma2InCone, 'isGamma2InCone/I')
        
        tNew.Branch('MassDsPi01_0_40', MassDsPi01_0_40, 'MassDsPi01_0_40/D')
        tNew.Branch('isPi01InCone', isPi01InCone, 'isPi01InCone/I')
        
        tNew.Branch('MassDsPi0G1_0_40', MassDsPi0G1_0_40, 'MassDsPi0G1_0_40/D')
        
        # Dalitz vars.
        tNew.Branch("M_SSKpi", M_SSKpi, "M_SSKpi/D")
        tNew.Branch("M_OSKpi", M_OSKpi, "M_OSKpi/D")
        tNew.Branch("M_KK",    M_KK,    "M_KK/D")
        tNew.Branch("Ds_M",    Ds_M,    "Ds_M/D")
        tNew.Branch("resFlag", resFlag, "resFlag/I")
        
        tNew.Branch("Beta_OSK", Beta_OSK, "Beta_OSK/D")
        tNew.Branch("Beta_SSK", Beta_SSK, "Beta_SSK/D")
        tNew.Branch("Beta_pi",  Beta_pi,  "Beta_pi/D")
        
        tNew.Branch("WM_Lc_SSKasproton", WM_Lc_SSKasproton, "WM_Lc_SSKasproton/D")
        tNew.Branch("WM_Dp_SSKaspi",     WM_Dp_SSKaspi,     "WM_Dp_SSKaspi/D")
        
        tNew.Branch("WM_Dst_FullReco",        WM_Dst_FullReco,        "WM_Dst_FullReco/D")
        tNew.Branch("WM_Dst_SSKaspi_fromDz",  WM_Dst_SSKaspi_fromDz,  "WM_Dst_SSKaspi_fromDz/D")
        tNew.Branch("WM_Dst_SSKaspi_fromDst", WM_Dst_SSKaspi_fromDst, "WM_Dst_SSKaspi_fromDst/D")
        
        tNew.Branch('WM_Jpsi_piasmu',  WM_Jpsi_piasmu, 'WM_Jpsi_piasmu/D')
        tNew.Branch('WM_Jpsi_SSKasmu', WM_Jpsi_SSKasmu,'WM_Jpsi_SSKasmu/D')
        
        tNew.Branch("WM_Kstar_SSKaspi", WM_Kstar_SSKaspi, "WM_Kstar_SSKaspi/D")
        tNew.Branch("WM_Kstar_OSKaspi", WM_Kstar_OSKaspi, "WM_Kstar_OSKaspi/D")
        
        tNew.Branch("WM_phi_piasK", WM_phi_piasK, "WM_phi_piasK/D")
        tNew.Branch("WM_KS_OSKaspi", WM_KS_OSKaspi, "WM_KS_OSKaspi/D")
        
        # Now the PID entries we need to tune the selection.
        tNew.Branch('SSK_PIDK', SSK_PIDK, 'SSK_PIDK/D')
        tNew.Branch('SSK_PIDp', SSK_PIDp, 'SSK_PIDp/D')
        tNew.Branch('OSK_PIDK', OSK_PIDK, 'OSK_PIDK/D')
        tNew.Branch('OSK_PIDp', OSK_PIDp, 'OSK_PIDp/D')
        tNew.Branch('pi_PIDK', pi_PIDK, 'pi_PIDK/D')
        tNew.Branch('pi_PIDp', pi_PIDp, 'pi_PIDp/D')
        
        tNew.Branch('pi_isMuon', pi_isMuon, 'pi_isMuon/I')
        tNew.Branch('OSK_isMuon', OSK_isMuon, 'OSK_isMuon/I')
        tNew.Branch('SSK_isMuon', SSK_isMuon, 'SSK_isMuon/I')
        
        tNew.Branch('SSK_ProbNNk', SSK_ProbNNK, 'SSK_ProbNNk/D')
        tNew.Branch('SSK_ProbNNp', SSK_ProbNNp, 'SSK_ProbNNp/D')
        tNew.Branch('OSK_ProbNNk', OSK_ProbNNK, 'OSK_ProbNNk/D')
        tNew.Branch('OSK_ProbNNp', OSK_ProbNNp, 'OSK_ProbNNp/D')
        tNew.Branch('SSK_ProbNNp', SSK_ProbNNp, 'SSK_ProbNNp/D')
            
        if isMC:
            tNew.Branch('q2True', q2True, 'q2True/D')
            tNew.Branch('EmuTrue', EmuTrue, 'EmuTrue/D')
            tNew.Branch('MM2True', MM2True, 'MM2True/D')

        # Get the friend tree and make a TEventList with it.
        tFriend = fFriend.Get(tName)
        cutStringOnlyDsVetoes = getCutStringOnlyDsVetoes(dataTag, tName)
        print '-- Using reflection cuts:', cutStringOnlyDsVetoes
        tFriend.Draw('>>eList', cutStringOnlyDsVetoes)
        eListDalitz = gDirectory.Get('eList')

        tFriend.SetBranchAddress("M_SSKpi", M_SSKpi)
        tFriend.SetBranchAddress("M_OSKpi", M_OSKpi)
        tFriend.SetBranchAddress("M_KK",    M_KK)
        tFriend.SetBranchAddress("Ds_M",    Ds_M)
        tFriend.SetBranchAddress("resFlag", resFlag)
        
        tFriend.SetBranchAddress("Beta_OSK", Beta_OSK)
        tFriend.SetBranchAddress("Beta_SSK", Beta_SSK)
        tFriend.SetBranchAddress("Beta_pi",  Beta_pi)
        
        tFriend.SetBranchAddress("WM_Lc_SSKasproton", WM_Lc_SSKasproton)
        tFriend.SetBranchAddress("WM_Dp_SSKaspi",     WM_Dp_SSKaspi)
        
        tFriend.SetBranchAddress("WM_Dst_FullReco",        WM_Dst_FullReco)
        tFriend.SetBranchAddress("WM_Dst_SSKaspi_fromDz",  WM_Dst_SSKaspi_fromDz)
        tFriend.SetBranchAddress("WM_Dst_SSKaspi_fromDst", WM_Dst_SSKaspi_fromDst)
            
        tFriend.SetBranchAddress('WM_Jpsi_piasmu',  WM_Jpsi_piasmu)
        tFriend.SetBranchAddress('WM_Jpsi_SSKasmu', WM_Jpsi_SSKasmu)
        
        tFriend.SetBranchAddress("WM_Kstar_SSKaspi", WM_Kstar_SSKaspi)
        tFriend.SetBranchAddress("WM_Kstar_OSKaspi", WM_Kstar_OSKaspi)
        
        tFriend.SetBranchAddress("WM_phi_piasK", WM_phi_piasK)
        tFriend.SetBranchAddress("WM_KS_OSKaspi", WM_KS_OSKaspi)
        
        # Now the PID entries we need to tune the selection.
        tFriend.SetBranchAddress('SSK_PIDK', SSK_PIDK)
        tFriend.SetBranchAddress('SSK_PIDp', SSK_PIDp)
        tFriend.SetBranchAddress('OSK_PIDK', OSK_PIDK)
        tFriend.SetBranchAddress('OSK_PIDp', OSK_PIDp)
        tFriend.SetBranchAddress('pi_PIDK', pi_PIDK)
        tFriend.SetBranchAddress('pi_PIDp', pi_PIDp)
        
        tFriend.SetBranchAddress('pi_isMuon', pi_isMuon)
        tFriend.SetBranchAddress('OSK_isMuon', OSK_isMuon)
        tFriend.SetBranchAddress('SSK_isMuon', SSK_isMuon)
        
        tFriend.SetBranchAddress('SSK_ProbNNk', SSK_ProbNNK)
        tFriend.SetBranchAddress('SSK_ProbNNp', SSK_ProbNNp)
        tFriend.SetBranchAddress('OSK_ProbNNk', OSK_ProbNNK)
        tFriend.SetBranchAddress('OSK_ProbNNp', OSK_ProbNNp)
        tFriend.SetBranchAddress('SSK_ProbNNp', SSK_ProbNNp)

        # One for the muaspi B mass
        MBsDsspi = numpy.zeros(1, dtype=float)
        tNew.Branch('MBsDsspi', MBsDsspi, 'MBsDsspi/D')
        MBsDspi = numpy.zeros(1, dtype=float)
        tNew.Branch('MBsDspi', MBsDspi, 'MBsDspi/D')
        # Make another EList to apply cuts based on the mother ntuple variables.
        #from BsDsMuNuForRDS.Selections import getCutString
        #preselectionCut = getCutString(dataTag, tName)
        cutStringNoVetoes = getCutStringNoDsVetoes(dataTag, tName)
        #from BsDsMuNuForRDS.TruthCuts import isSignal
        c.Draw('>>eList2', cutStringNoVetoes)
        eListPreselection = gDirectory.Get('eList2')

        # Make sure the number of events in the Dalitz tree is the same
        # as the number of events in the original tree after the preselection.
        print '-- Checking number of entries are the same...'
        print '---- Dalitz number entries      = %i' %tFriend.GetEntries()
        print '---- Master file number entries = %i' %eListPreselection.GetN()
        if tFriend.GetEntries() != eListPreselection.GetN():
            sys.exit('ERROR: Dalitz and master files have different number of events.')
            
        # Loop over the tree.
        numEntries = c.GetEntries()

        # Make another index for the Dalitz tree, which is smaller.
        dalitzIndex = 0
        numPassed   = 0
        for i in range(numEntries):
                
            if i%1000==0:
                sys.stdout.write('\rProcessing event %i of %i...' %(i, numEntries) )
                sys.stdout.flush()

            # If it doesn't pass the vetoes then continue.
            if not eListPreselection.Contains(i):
                continue
            # If we get to here then the Dalitz file has the corresponding
            # entry. So increment the Dalitz index only here.
            if not eListDalitz.Contains(dalitzIndex):
                dalitzIndex += 1
                continue
            # Get the dalitz entry and then increment it for the next loop.
            tFriend.GetEntry(dalitzIndex)
            dalitzIndex += 1
            
            # Get that entry.
            c.GetEntry(i)

            ##############################################################################
            # Now add the muon vars.
            ##############################################################################
            flightVector = TVector3(BVx[0] - PVx[0], BVy[0] - PVy[0], BVz[0] - PVz[0])
            tantheta = (flightVector.Unit()).Perp()/(flightVector.Unit().Z())
            approxBPT = (mB_PDG / mB[0]) * pzB[0]*tantheta
            approxB4V = TLorentzVector()
            approxB4V.SetPtEtaPhiM(approxBPT, flightVector.Eta(), flightVector.Phi(), mB_PDG)
            Ds4VLab = TLorentzVector(DPx[0], DPy[0], DPz[0], DPe[0])
            mu4VLab = TLorentzVector(muPx[0], muPy[0], muPz[0], muPe[0])
            approxBRestBoost = -approxB4V.BoostVector()
            mu4VBRest = mu4VLab.Clone()
            mu4VBRest.Boost(-approxB4V.BoostVector())
            Emu[0] = mu4VBRest.E()
            q2[0] = (approxB4V - Ds4VLab).M2()
            MM2[0] = (approxB4V - Ds4VLab - mu4VLab).M2()

            ##############################################################################
            # Make some TLVs for the muon under the pion hypothesis, and the Ds_M candidate.
            # Also the photon candidate.
            ##############################################################################
            TLV_Ds = TLorentzVector()
            TLV_Ds.SetPxPyPzE(DPx[0], DPy[0], DPz[0], DPe[0])

            muonCombinedMom = (muPx[0]**2 + muPy[0]**2 + muPz[0]**2)**0.5
            pionAsMuonEnergy = (muonCombinedMom**2 + M_pi**2)**0.5
            TLV_muonAsPion = TLorentzVector()
            TLV_muonAsPion.SetPxPyPzE(muPx[0], muPy[0], muPz[0], pionAsMuonEnergy)

            TLV_gamma = TLorentzVector()
            TLV_gamma.SetPxPyPzE(Ds_0_40_nc_maxPt_PX[0], Ds_0_40_nc_maxPt_PY[0]
                                 ,Ds_0_40_nc_maxPt_PZ[0], Ds_0_40_nc_maxPt_PE[0])

            TLV_BsDsspi  = TLV_gamma + TLV_Ds + TLV_muonAsPion
            #TLV_BsDsspi2 = (TLV_gamma + TLV_Ds) + TLV_muonAsPion

            TLV_BsDspi   = TLV_Ds + TLV_muonAsPion
            
            MBsDsspi[0] = TLV_BsDsspi.M()
            MBsDspi[0]  = TLV_BsDspi.M()
            
            #print '*'*50
            #print TLV_BsDsspi.M(), TLV_BsDsspi2.M()
            #print muPx[0], muPy[0], muPz[0], M_pi
            #print muonCombinedMom, pionAsMuonEnergy
            #TLV_Ds.Print()
            #TLV_muonAsPion.Print()
            #print TLV_muonAsPion.M()
            #TLV_gamma.Print()
            #print TLV_gamma.M()
            #TLV_BsDsspi.Print()

            ##############################################################################
            # Set the invariant mass pairs for the excited charm.
            ##############################################################################                
            MassDsG1_0_40[0] = ( (DPe[0]+Ds_0_40_nc_maxPt_PE[0])**2 -
                                 (DPx[0]+Ds_0_40_nc_maxPt_PX[0])**2 -
                                 (DPy[0]+Ds_0_40_nc_maxPt_PY[0])**2 -
                                 (DPz[0]+Ds_0_40_nc_maxPt_PZ[0])**2 )**0.5 - Ds_MM[0] + mDs_PDG
            
            MassDsG2_0_40[0] = ( (DPe[0]+Ds_0_40_nc_secPt_PE[0])**2 -
                                 (DPx[0]+Ds_0_40_nc_secPt_PX[0])**2 - 
                                 (DPy[0]+Ds_0_40_nc_secPt_PY[0])**2 -
                                 (DPz[0]+Ds_0_40_nc_secPt_PZ[0])**2 )**0.5 - Ds_MM[0] + mDs_PDG
            
            MassDsPi01_0_40[0] = ( (DPe[0]+Ds_0_40_pi0_maxPt_PE[0])**2 -
                                   (DPx[0]+Ds_0_40_pi0_maxPt_PX[0])**2 -
                                   (DPy[0]+Ds_0_40_pi0_maxPt_PY[0])**2 -
                                   (DPz[0]+Ds_0_40_pi0_maxPt_PZ[0])**2 )**0.5 - Ds_MM[0] + mDs_PDG
            
            MassDsPi0G1_0_40[0] = ( (DPe[0]+Ds_0_40_pi0_maxPt_PE[0]+Ds_0_40_nc_maxPt_PE[0])**2 -
                                    (DPx[0]+Ds_0_40_pi0_maxPt_PX[0]+Ds_0_40_nc_maxPt_PX[0])**2 -
                                    (DPy[0]+Ds_0_40_pi0_maxPt_PY[0]+Ds_0_40_nc_maxPt_PY[0])**2 -
                                    (DPz[0]+Ds_0_40_pi0_maxPt_PZ[0]+Ds_0_40_nc_maxPt_PZ[0])**2 )**0.5 - Ds_MM[0] + mDs_PDG
            
            # Determine if there is an N=1,2,3 gamma in the cone.
            isGamma1InCone[0] = 0
            if Ds_0_40_nc_maxPt_PE[0] > 0.0:
                isGamma1InCone[0] = 1
            isGamma2InCone[0] = 0
            if Ds_0_40_nc_secPt_PE[0] > 0.0:
                isGamma2InCone[0] = 1
            isGamma3InCone[0] = 0
            if Ds_0_40_nc_thiPt_PE[0] > 0.0:
                isGamma3InCone[0] = 1

            # Determine if there is an N=1,2,3 pi0 in the cone.
            isPi01InCone[0] = 0
            if Ds_0_40_pi0_maxPt_PE[0] > 0.0:
                isPi01InCone[0] = 1
            isPi02InCone[0] = 0
            if Ds_0_40_pi0_secPt_PE[0] > 0.0:
                isPi02InCone[0] = 1
            isPi03InCone[0] = 0
            if Ds_0_40_pi0_thiPt_PE[0] > 0.0:
                isPi03InCone[0] = 1
                
            if isMC:
                # But check the B and D are real, or else it'll give errors.
                if (pzBT[0] == 0 or DPzT[0] == 0):
                    q2True[0]  = -10e6
                    EmuTrue[0] = -10e6
                    MM2True[0] = -10e6
                else:
                    # Just get the B kinematics from the truth.
                    TrueB4VLab = TLorentzVector(pxBT[0], pyBT[0], pzBT[0], peBT[0])
                    TrueDs4VLab = TLorentzVector(DPxT[0], DPyT[0], DPzT[0], DPeT[0])
                    Truemu4VLab = TLorentzVector(muPxT[0], muPyT[0], muPzT[0], muPeT[0])
                    Truemu4VBRest = Truemu4VLab.Clone()
                    Truemu4VBRest.Boost(-TrueB4VLab.BoostVector())
                    q2True[0]  = (TrueB4VLab - TrueDs4VLab).M2()
                    EmuTrue[0] = Truemu4VBRest.E()
                    MM2True[0] = (TrueB4VLab - TrueDs4VLab - Truemu4VLab).M2()
                        
            ##############################################################################
            # Fill the ntuple
            ##############################################################################
            if dataTag == 'Data':
                if resFlag[0] == 2: continue
            tNew.Fill()
            numPassed += 1

        print '\n-- Number entries passed:', numPassed
        print '*'*40
        tNew.Write()
        fOut.cd('..')
            
    fOut.Close()

    # Now copy to eos.
    eoscommand = '/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select cp'
    finalName = getEOSPostSelectionFileName(dataTag)
    os.system('%s %s %s' %(eoscommand, fOutName, finalName))
    print '-- Copied file to eos.'
    
    # Now delete the original.
    #os.system('rm %s' %fOutName)
