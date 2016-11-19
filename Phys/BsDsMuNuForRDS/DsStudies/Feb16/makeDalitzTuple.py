from BsDsMuNuForRDS.DataRetrieval import *
from ROOT import TLorentzVector, TFile, TTree, gROOT, gStyle, gDirectory
import sys, os
gROOT.SetBatch()
gROOT.ProcessLine('.x ~/lhcbStyle.C')
#gStyle.SetPadRightMargin(0.1) 

tupleType = 'data'
dataTag  = sys.argv[1] #'BdDstDs'
polarity = sys.argv[2] #'MagDown'
#dataTag  = 'BdDstDs'
#polarity = 'MagDown'

# Resonance masses in GeV/c2 from the PDG.
M_phi   = 1019.461
M_Kstar = 895.5

# Final state particle masses.
M_K  = 493.677
M_pi = 139.570
M_p  = 938.272
M_mu = 105.658

# Make the new file.
outFileDir = getPostSelDataDirectory()
outFileName = outFileDir + outPutFileNameDict[dataTag][polarity]
#outFileName = outFileDir
fOut = TFile(outFileName, "recreate")

# Loop over the tuples.
for tName in fileNameDict[dataTag]['tNames']:

    # Get the chain with the package functions.
    c = getChainWithTupleName(dataTag, polarity, tName)

    # Make the TDirectory.
    dirName  = tName.split('/')[0]
    tNameEnd = tName.split('/')[1]

    theDir = fOut.mkdir(dirName)
    theDir.cd()
    
    # Make the new tuple.
    tOut = TTree('DecayTree', 'DecayTree') #c.CloneTree(0)

    #####################################################################################
    # Now make branches for all the Ds daughter kinematics.
    #####################################################################################
    from numpy import zeros as z
    SSK_Px = z(1, dtype=float)
    SSK_Py = z(1, dtype=float)
    SSK_Pz = z(1, dtype=float)
    SSK_Pe = z(1, dtype=float)
    SSK_P  = z(1, dtype=float)
    
    OSK_Px = z(1, dtype=float)
    OSK_Py = z(1, dtype=float)
    OSK_Pz = z(1, dtype=float)
    OSK_Pe = z(1, dtype=float)
    OSK_P  = z(1, dtype=float)
    
    pi_Px = z(1, dtype=float)
    pi_Py = z(1, dtype=float)
    pi_Pz = z(1, dtype=float)
    pi_Pe = z(1, dtype=float)
    pi_P  = z(1, dtype=float)
    
    pi_isMuon = z(1, dtype=int)
    OSK_isMuon = z(1, dtype=int)
    SSK_isMuon = z(1, dtype=int)
    
    mu_Px = z(1, dtype=float)
    mu_Py = z(1, dtype=float)
    mu_Pz = z(1, dtype=float)
    mu_Pe = z(1, dtype=float)
    mu_P  = z(1, dtype=float)
    
    Ds_M = z(1, dtype=float)
    
    OSK_PIDK = z(1, dtype=float)
    OSK_PIDp = z(1, dtype=float)
    SSK_PIDK = z(1, dtype=float)
    SSK_PIDp = z(1, dtype=float)
    pi_PIDK = z(1, dtype=float)
    pi_PIDp = z(1, dtype=float)
    
    OSK_ProbNNK = z(1, dtype=float)
    OSK_ProbNNp = z(1, dtype=float)
    SSK_ProbNNK = z(1, dtype=float)
    SSK_ProbNNp = z(1, dtype=float)
    pi_ProbNNK  = z(1, dtype=float)
    
    OSK_IPChi2 = z(1, dtype=float)
    SSK_IPChi2 = z(1, dtype=float)
    pi_IPChi2 = z(1, dtype=float)
    
    branchDict = {
        'sim'   : '%s_P%s' #'%s_TRUEP_%s'
        ,'data' : '%s_P%s'
        }
    b = branchDict[tupleType]

    #####################################################################################
    # Now the kaon assignments, this varies with the dataTag.
    #####################################################################################
    if dataTag == 'RDS_FromTauMu':
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
    else:
        c.SetBranchAddress(b %('Kpl', 'X'), OSK_Px)
        c.SetBranchAddress(b %('Kpl', 'Y'), OSK_Py)
        c.SetBranchAddress(b %('Kpl', 'Z'), OSK_Pz)
        c.SetBranchAddress(b %('Kpl', 'E'), OSK_Pe)
        c.SetBranchAddress(b %('Kpl', ''),  OSK_P)
    
        c.SetBranchAddress(b %('Kmi', 'X'), SSK_Px)
        c.SetBranchAddress(b %('Kmi', 'Y'), SSK_Py)
        c.SetBranchAddress(b %('Kmi', 'Z'), SSK_Pz)
        c.SetBranchAddress(b %('Kmi', 'E'), SSK_Pe)
        c.SetBranchAddress(b %('Kmi', ''),  SSK_P)

        c.SetBranchAddress('Kmi_isMuon', SSK_isMuon)
        c.SetBranchAddress('Kpl_isMuon', OSK_isMuon)

        c.SetBranchAddress('Kpl_ProbNNk', OSK_ProbNNK)
        c.SetBranchAddress('Kpl_ProbNNp', OSK_ProbNNp)
        c.SetBranchAddress('Kmi_ProbNNk', SSK_ProbNNK)
        c.SetBranchAddress('Kmi_ProbNNp', SSK_ProbNNp)
        
        c.SetBranchAddress('Kmi_PIDK'   , SSK_PIDK)
        c.SetBranchAddress('Kmi_PIDp'   , SSK_PIDp)
        c.SetBranchAddress('Kpl_PIDK'   , OSK_PIDK)
        c.SetBranchAddress('Kpl_PIDp'   , OSK_PIDp)

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
    
    #####################################################################################
    # Now make the containers for the new variables.
    #####################################################################################
    M_SSKpi = z(1, dtype=float)
    M_OSKpi = z(1, dtype=float)
    M_KK    = z(1, dtype=float)
    M_Ds    = z(1, dtype=float)
    resFlag = z(1, dtype=int)
    
    Beta_OSK  = z(1, dtype=float)
    Beta_SSK  = z(1, dtype=float)
    Beta_pi   = z(1, dtype=float)
    
    WM_Lc_SSKasproton = z(1, dtype=float)
    WM_Dp_SSKaspi     = z(1, dtype=float)

    WM_Dst_FullReco         = z(1, dtype=float)
    WM_Dst_SSKaspi_fromDz   = z(1, dtype=float)
    WM_Dst_OSKaspi_fromDz   = z(1, dtype=float)
    WM_Dst_SSKaspi_fromDst  = z(1, dtype=float)
    WM_Dst_OSKaspi_fromDst  = z(1, dtype=float)
    
    WM_Jpsi_piasmu  = z(1, dtype=float)
    WM_Jpsi_SSKasmu = z(1, dtype=float)
    WM_Jpsi_OSKasmu = z(1, dtype=float)
    
    WM_Kstar_SSKaspi  = z(1, dtype=float)
    WM_Kstar_OSKaspi  = z(1, dtype=float)
    
    WM_phi_piasK    = z(1, dtype=float)
    WM_KS_OSKaspi   = z(1, dtype=float)
    
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

    #####################################################################################
    # Now loop over the events and plot the Dalitz variables.
    #####################################################################################
    numToProcess = c.GetEntries()
    numPassedCounter = 0
    for i in xrange(numToProcess):

        ###################################################################
        # Some printout monitoring, and fetch the entry.
        if i%1000 == 0:
            sys.stdout.write('\rProcessing entry %i of %i...' %(i, numToProcess))
            sys.stdout.flush()
        numPassedCounter += 1
        c.GetEntry(i)

        ###################################################################
        # Now make the correctly identified TLVs.
        SSK_tlv  = TLorentzVector(SSK_Px,  SSK_Py,  SSK_Pz,  SSK_Pe)
        OSK_tlv  = TLorentzVector(OSK_Px,  OSK_Py,  OSK_Pz,  OSK_Pe)
        pi_tlv   = TLorentzVector(pi_Px, pi_Py, pi_Pz, pi_Pe)
        mu_tlv   = TLorentzVector(mu_Px, mu_Py, mu_Pz, mu_Pe)
        
        M_KK[0]     = (SSK_tlv + OSK_tlv).M()
        M_SSKpi[0]  = (SSK_tlv + pi_tlv).M()
        M_OSKpi[0]  = (OSK_tlv + pi_tlv).M()

        ###################################################################
        # Now check which region it falls into.
        # 0 is phi resonance, 1 is Kstar, 2 is non res.
        phi_flag    = abs(M_KK[0] - M_phi) < 20
        Kstar_flag  = (abs(M_OSKpi[0] - M_Kstar) < 90) and not phi_flag
        nonRes_flag = not (phi_flag or Kstar_flag)
        
        resIndex   = 0
        if Kstar_flag:
            resIndex = 1
        elif nonRes_flag:
            resIndex = 2
        resFlag[0] = resIndex

        ###################################################################        
        # Now the beta momentum asymmetry variables.
        Beta_OSK[0]  = (SSK_P[0] + pi_P[0] - OSK_P[0]) / (SSK_P[0] + pi_P[0] + OSK_P[0]) 
        Beta_SSK[0]  = (OSK_P[0] + pi_P[0] - SSK_P[0]) / (SSK_P[0] + pi_P[0] + OSK_P[0])
        Beta_pi[0]   = (SSK_P[0] + OSK_P[0] - pi_P[0]) / (SSK_P[0] + pi_P[0] + OSK_P[0])

        ###################################################################
        # Get the rival hypothesis TLVs.
        #E_OSKasproton      = (OSK_P**2 + M_p**2)**0.5
        E_OSKaspi        = (OSK_P**2 + M_pi**2)**0.5

        E_SSKasproton = (SSK_P**2 + M_p**2)**0.5
        E_SSKaspi     = (SSK_P**2 + M_pi**2)**0.5
        E_SSKasmu     = (SSK_P**2 + M_mu**2)**0.5
        
        #E_pimasantiproton = (pim_P**2 + M_p**2)**0.5
        E_piasK       = (pi_P**2 + M_K**2)**0.5
        E_piasmu      = (pi_P**2 + M_mu**2)**0.5

        #OSKpasproton_tlv      = TLorentzVector(OSK_Px, OSK_Py, OSK_Pz, E_Kpasproton)
        OSKaspi_tlv   = TLorentzVector(OSK_Px, OSK_Py, OSK_Pz, E_OSKaspi)

        SSKasproton_tlv  = TLorentzVector(SSK_Px, SSK_Py, SSK_Pz, E_SSKasproton)
        SSKaspi_tlv      = TLorentzVector(SSK_Px, SSK_Py, SSK_Pz, E_SSKaspi)
        SSKasmu_tlv      = TLorentzVector(SSK_Px, SSK_Py, SSK_Pz, E_SSKasmu)

        piasmu_tlv       = TLorentzVector(pi_Px, pi_Py, pi_Pz, E_piasmu)
        piasK_tlv        = TLorentzVector(pi_Px, pi_Py, pi_Pz, E_piasK)
        
        ###################################################################
        # Now make the WM Lc and Dp vars.
        WM_Lc_SSKasproton[0] = (SSKasproton_tlv + OSK_tlv + pi_tlv).M()
        WM_Dp_SSKaspi[0]     = (SSKaspi_tlv + OSK_tlv + pi_tlv).M()
        
        ###################################################################
        # Now the Dst WM variables. All of 'em.
        # First the fully reconstructed Dst->Dz(KK)pi.
        WM_Dst_FullReco[0]        = Ds_M - (SSK_tlv + OSK_tlv).M()

        # Now where the misID is : Dst*+ -> Dz(pi+[K+] K-) pi+ 
        WM_Dst_SSKaspi_fromDz[0]  = (pi_tlv + SSKaspi_tlv + OSK_tlv).M() - (SSKaspi_tlv + OSK_tlv).M()

        # Now where the misID is : Dst*+ -> Dz(pi+ K-) pi+[K+]
        WM_Dst_SSKaspi_fromDst[0] = (SSKaspi_tlv + OSK_tlv + pi_tlv).M() - (OSK_tlv + pi_tlv).M()

        ##################################################################
        # Now the Jpsi vars.
        # Reconstruct the pion as a muon.
        WM_Jpsi_piasmu[0]  = (mu_tlv + piasmu_tlv).M()
        # And now the kaon as a muon.
        WM_Jpsi_SSKasmu[0] = (mu_tlv + SSKasmu_tlv).M()
        
        # Now the Kstar vetoes.
        # We have already misreconstructed the same sign kaon as a pion.
        # Combine it with the opposite sign kaon.
        WM_Kstar_SSKaspi[0] = (SSKaspi_tlv + OSK_tlv).M()
        WM_Kstar_OSKaspi[0] = (OSKaspi_tlv + SSK_tlv).M()
        
        # Now check the pion under kaon hypothesis doesn't form
        # a phi with the opposite charge kaon.
        WM_phi_piasK[0] = (piasK_tlv + OSK_tlv).M()
        
        # Now check the opposite sign kaon under pion hypothesis
        # and pair with the pion to check for KS, f0 etc. backgrounds.
        WM_KS_OSKaspi[0] = (OSKaspi_tlv + SSK_tlv).M()
        
        ##################################################################
        # Now fill the ntuple.
        tOut.Fill()

    ##################################################################
    # Print some info.
    print 
    print '-- Created ntuple.'
    print '-- Passed %i entries of %i.' %(numPassedCounter, numToProcess)
    # Write and change up directory.
    tOut.Write()
    fOut.cd('..')

# Now close the file.    
fOut.Close()
