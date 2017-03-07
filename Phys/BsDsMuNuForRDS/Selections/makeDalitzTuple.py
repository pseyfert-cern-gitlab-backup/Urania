from BsDsMuNuForRDS.DataRetrieval import *
from BsDsMuNuForRDS.Constants     import *
from BsDsMuNuForRDS.VarContainers import *
from BsDsMuNuForRDS.Configuration import configurationDict
from BsDsMuNuForRDS.BranchSetters import assignDalitzInputBranches, assignDalitzOutputBranches
from ROOT import TLorentzVector, TFile, TTree, gROOT, gStyle, gDirectory
import sys, os
gROOT.SetBatch()

###################################################################
# Parse command line args and error check.
###################################################################
if len(sys.argv) != 2:
    print '-- ERROR: specify dataTag as command line argument.'
    print '--        DataTag not recognised. Valid tags are:'
    for dataTag in configurationDict.keys():
        print '---- ', dataTag
    sys.exit()
dataTag  = sys.argv[1]
if dataTag not in configurationDict.keys():
    print '-- ERROR: dataTag not recognised. Valid tags are:'
    for dataTag in configurationDict.keys():
        print '----', dataTag
    sys.exit()    

###################################################################
# Configuration
###################################################################
# Ignore the MCMATCH, fake and SS lines?
ignoreFakes = False

# Make the new file.
outFileName = getLocalDalitzFileName(dataTag)
print '-- INFO: making new file:'
print '----', outFileName
fOut = TFile(outFileName, "recreate")

# Loop over the tuples.
for tName in configurationDict[dataTag]['tNames']:

    if ignoreFakes:
        if tName != 'B2DsMuNuTuple/DecayTree': continue

    # Get the chain with the package functions.
    c = getChainWithTupleName(dataTag, tName)

    # Make the TDirectory.
    dirName  = tName.split('/')[0]
    tNameEnd = tName.split('/')[1]
    theDir = fOut.mkdir(dirName)
    theDir.cd()
    
    # Make the new tuple.
    tOut = TTree('DecayTree', 'DecayTree') #c.CloneTree(0)

    # Assign all the input and output branch addresses.
    assignDalitzInputBranches(c)
    assignDalitzOutputBranches(tOut)

    #####################################################################################
    # Now loop over the events and plot the Dalitz variables.
    #####################################################################################
    numToProcess = c.GetEntries()
    numPassedCounter = 0

    # Make a filter for the preselection.
    from BsDsMuNuForRDS.Selections import getCutStringNoDsVetoes
    preselectionCut = getCutStringNoDsVetoes(dataTag, tName)
    c.Draw('>>eList', preselectionCut)
    eList = gDirectory.Get('eList')
    print '-- INFO: number of events passing preselection:', eList.GetN()

    for i in xrange(numToProcess):

        ###################################################################
        # Some printout monitoring, and fetch the entry.
        if i%1000 == 0:
            sys.stdout.write('\rProcessing entry %i of %i...' %(i, numToProcess))
            sys.stdout.flush()
        if not eList.Contains(i): continue    

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

# Now copy to eos.
eoscommand = '/afs/cern.ch/project/eos/installation/0.3.15/bin/eos.select cp'
finalName = getEOSDalitzFileName(dataTag)
os.system('%s %s %s' %(eoscommand, outFileName, finalName))
print '-- Copied file to eos.'
