from BsDsMuNuForRDS.DataRetrieval import getChain
from ROOT import TLorentzVector, TFile, TTree, gROOT, gStyle, gDirectory
import sys, os
gROOT.SetBatch()
gROOT.ProcessLine('.x ~/lhcbStyle.C')
#gStyle.SetPadRightMargin(0.1) 
dataType = 'data'
polarity = 'up'

# Resonance masses in GeV/c2 from the PDG.
M_phi   = 1019.461
M_Kstar = 895.5

# Final state particle masses.
M_K  = 493.677
M_pi = 139.570
M_p  = 938.272
M_mu = 105.658

# Get the chain with the package functions.
c = getChain(dataType, polarity)

# Now make branches for all the Ds daughter kinematics.
from numpy import zeros as z
Km_Px = z(1, dtype=float)
Km_Py = z(1, dtype=float)
Km_Pz = z(1, dtype=float)
Km_Pe = z(1, dtype=float)
Km_P  = z(1, dtype=float)

Kp_Px = z(1, dtype=float)
Kp_Py = z(1, dtype=float)
Kp_Pz = z(1, dtype=float)
Kp_Pe = z(1, dtype=float)
Kp_P  = z(1, dtype=float)

pip_Px = z(1, dtype=float)
pip_Py = z(1, dtype=float)
pip_Pz = z(1, dtype=float)
pip_Pe = z(1, dtype=float)
pip_P  = z(1, dtype=float)

pip_isMuon = z(1, dtype=int)
Kp_isMuon = z(1, dtype=int)

mu_Px = z(1, dtype=float)
mu_Py = z(1, dtype=float)
mu_Pz = z(1, dtype=float)
mu_Pe = z(1, dtype=float)
mu_P  = z(1, dtype=float)

inputDs_M = z(1, dtype=float)

Kp_PIDK = z(1, dtype=float)
Kp_PIDp = z(1, dtype=float)
Km_PIDK = z(1, dtype=float)
Km_PIDp = z(1, dtype=float)
pip_PIDK = z(1, dtype=float)
pip_PIDp = z(1, dtype=float)

#Kp_ProbNNK = z(1, dtype=float)
#Kp_ProbNNp = z(1, dtype=float)
Kp_ProbNNK = z(1, dtype=float)
Kp_ProbNNp = z(1, dtype=float)
Km_ProbNNK = z(1, dtype=float)
pip_ProbNNK = z(1, dtype=float)

Kp_IPChi2 = z(1, dtype=float)
Km_IPChi2 = z(1, dtype=float)
pip_IPChi2 = z(1, dtype=float)

branchDict = {
    'sim'   : '%s_TRUEP_%s'
    ,'data' : '%s_P%s'
    }
b = branchDict[dataType]

c.SetBranchAddress(b %('Kmi', 'X'), Kp_Px)
c.SetBranchAddress(b %('Kmi', 'Y'), Kp_Py)
c.SetBranchAddress(b %('Kmi', 'Z'), Kp_Pz)
c.SetBranchAddress(b %('Kmi', 'E'), Kp_Pe)
c.SetBranchAddress(b %('Kmi', ''),  Kp_P)

c.SetBranchAddress(b %('Kpl', 'X'), Km_Px)
c.SetBranchAddress(b %('Kpl', 'Y'), Km_Py)
c.SetBranchAddress(b %('Kpl', 'Z'), Km_Pz)
c.SetBranchAddress(b %('Kpl', 'E'), Km_Pe)
c.SetBranchAddress(b %('Kpl', ''),  Km_P)

c.SetBranchAddress(b %('pi', 'X'), pip_Px)
c.SetBranchAddress(b %('pi', 'Y'), pip_Py)
c.SetBranchAddress(b %('pi', 'Z'), pip_Pz)
c.SetBranchAddress(b %('pi', 'E'), pip_Pe)
c.SetBranchAddress(b %('pi', ''),  pip_P)
c.SetBranchAddress('pi_isMuon', pip_isMuon)
c.SetBranchAddress('Kmi_isMuon', Kp_isMuon)

c.SetBranchAddress(b %('mu', 'X'), mu_Px)
c.SetBranchAddress(b %('mu', 'Y'), mu_Py)
c.SetBranchAddress(b %('mu', 'Z'), mu_Pz)
c.SetBranchAddress(b %('mu', 'E'), mu_Pe)
c.SetBranchAddress(b %('mu', ''),  mu_P)

c.SetBranchAddress('Kpl_IPCHI2_OWNPV', Km_IPChi2)
c.SetBranchAddress('Kmi_IPCHI2_OWNPV', Kp_IPChi2)
c.SetBranchAddress('pi_IPCHI2_OWNPV' , pip_IPChi2)

c.SetBranchAddress('Kmi_ProbNNk', Kp_ProbNNK)
c.SetBranchAddress('Kmi_ProbNNp', Kp_ProbNNp)
c.SetBranchAddress('Kpl_ProbNNk', Km_ProbNNK)
c.SetBranchAddress('pi_ProbNNk', pip_ProbNNK)

c.SetBranchAddress('Ds_M', inputDs_M)

c.SetBranchAddress('Kmi_PIDK', Kp_PIDK)
c.SetBranchAddress('Kmi_PIDp', Kp_PIDp)
c.SetBranchAddress('Kpl_PIDK', Km_PIDK)
c.SetBranchAddress('Kpl_PIDp', Km_PIDp)
c.SetBranchAddress('pi_PIDK', pip_PIDK)
c.SetBranchAddress('pi_PIDp', pip_PIDp)

# Now to speed up the reading of the tuple turn off all unnecessary branches.
c.SetBranchStatus('*', 0)
for hadron in ['mu', 'pi', 'Kpl', 'Kmi']:
    for momentum in ['P', 'PX', 'PY', 'PZ', 'PE']:
        c.SetBranchStatus('%s_%s' %(hadron, momentum), 1)

for branch in ['Kmi_ProbNNk', 'Kmi_ProbNNp', 'Kpl_ProbNNk', 'pi_ProbNNk', 'Kpl_IPCHI2_OWNPV', 'Kmi_IPCHI2_OWNPV', 'pi_IPCHI2_OWNPV',
               'pi_PIDK', 'pi_PIDp', 'Kpl_PIDK', 'Kpl_PIDp', 'Kpl_MINIPCHI2', 'Kpl_PT', 'Kmi_PT', 'Kmi_PT', 'pi_PT', 'pi_MINIPCHI2',
               'Ds_PT', 'Ds_ENDVERTEX_CHI2', 'Ds_DIRA_ORIVX', 'nLongTracks', 'nSPDHits', 'Kmi_MINIPCHI2', 'mu_MINIPCHI2', 'Kmi_isMuon']:
    c.SetBranchStatus(branch, 1)
c.SetBranchStatus('pi_isMuon', 1)
c.SetBranchStatus('Ds_M', 1)
c.SetBranchStatus('Kmi_PIDK', 1)
c.SetBranchStatus('Kmi_PIDp', 1)

# Now make the new tuple and set all the branches I want to keep.
fOut = TFile('DalitzTuple_%s_%s.root' %(dataType, polarity), "recreate")
tOut = TTree('DalitzTuple', 'DalitzTuple')

M_Kmpi = z(1, dtype=float)
M_Kppi = z(1, dtype=float)
M_KmKp = z(1, dtype=float)
M_Ds   = z(1, dtype=float)
resFlag = z(1, dtype=int)

Beta_Kp  = z(1, dtype=float)
Beta_Km  = z(1, dtype=float)
Beta_pip = z(1, dtype=float)

WM_pKpi  = z(1, dtype=float)
WM_piKpi = z(1, dtype=float)

WM_Dst   = z(1, dtype=float)
WM_Dst2  = z(1, dtype=float)
WM_Dst3  = z(1, dtype=float)
WM_Dst4  = z(1, dtype=float)

WM_Jpsi_pi  = z(1, dtype=float)
WM_Jpsi_K   = z(1, dtype=float)

WM_Kstar  = z(1, dtype=float)
WM_Kstar2 = z(1, dtype=float)

WM_phi     = z(1, dtype=float)
WM_phi2    = z(1, dtype=float)
WM_f0     = z(1, dtype=float)

WM_Lz = z(1, dtype=float)

tOut.Branch('Km_IPCHI2_OWNPV', Km_IPChi2, 'Km_IPCHI2_OWNPV/D')
tOut.Branch('Kp_IPCHI2_OWNPV', Kp_IPChi2, 'Kp_IPCHI2_OWNPV/D')
tOut.Branch('pip_IPCHI2_OWNPV', pip_IPChi2, 'pip_IPCHI2_OWNPV/D')

tOut.Branch('Kp_ProbNNK', Kp_ProbNNK, 'Kp_ProbNNK/D')
tOut.Branch('Kp_ProbNNp', Kp_ProbNNp, 'Kp_ProbNNp/D')
tOut.Branch('Km_ProbNNK', Km_ProbNNK, 'Km_ProbNNK/D')
tOut.Branch('pip_ProbNNK', pip_ProbNNK, 'pip_ProbNNK/D')

tOut.Branch("M_Kmpi", M_Kmpi, "M_Kmpi/D")
tOut.Branch("M_Kppi", M_Kppi, "M_Kppi/D")
tOut.Branch("M_KmKp", M_KmKp, "M_KmKp/D")
tOut.Branch("M_Ds"  , M_Ds,   "M_Ds/D")
tOut.Branch("resFlag", resFlag, "resFlag/I")

tOut.Branch("Beta_Kp", Beta_Kp, "Beta_Kp/D")
tOut.Branch("Beta_Km", Beta_Km, "Beta_Km/D")
tOut.Branch("Beta_pip", Beta_pip, "Beta_pip/D")

tOut.Branch("WM_Lc_Kpasproton", WM_pKpi, "WM_Lc_Kpasproton/D")
tOut.Branch("WM_Dp_Kpaspip", WM_piKpi, "WM_Dp_Kpaspip/D")

tOut.Branch("WM_Dst_Kpaspip_fromDz", WM_Dst, "WM_Dst_Kpaspip_fromDz/D")
tOut.Branch("WM_Dst_Kmaspim_fromDz", WM_Dst2, "WM_Dst_Kmaspim_fromDz/D")
tOut.Branch("WM_Dst_Kmaspim_fromDst", WM_Dst3, "WM_Dst_Kmaspim_fromDst/D")
tOut.Branch("WM_Dst_Kpaspip_fromDst", WM_Dst4, "WM_Dst_Kpaspip_fromDst/D")

tOut.Branch('WM_Jpsi_pipasmup', WM_Jpsi_pi, 'WM_Jpsi_pipasmup/D')
tOut.Branch('WM_Jpsi_Kpasmup' , WM_Jpsi_K,  'WM_Jpsi_Kpasmup/D')

tOut.Branch("WM_Kstar_Kpaspip", WM_Kstar, "WM_Kstar_Kpaspip/D")
tOut.Branch("WM_Kstar_Kmaspim", WM_Kstar2, "WM_Kstar_Kmaspim/D")

tOut.Branch("WM_phi_pipasKp", WM_phi, "WM_phi_pipasKp/D")
#tOut.Branch("WM_phi_pasKp", WM_phi, "WM_phi_pipasKp/D")

tOut.Branch("WM_f0_Kmaspim", WM_f0, "WM_f0_Kmaspim/D")

#tOut.Branch("WM_Lz_pim", WM_f0, "WM_f0_Kmaspim/D")

tOut.Branch('Km_PIDK', Km_PIDK, 'Km_PIDK/D')
tOut.Branch('Km_PIDp', Km_PIDp, 'Km_PIDp/D')
tOut.Branch('Kp_PIDK', Kp_PIDK, 'Kp_PIDK/D')
tOut.Branch('Kp_PIDp', Kp_PIDp, 'Kp_PIDp/D')
tOut.Branch('pip_PIDK', pip_PIDK, 'pip_PIDK/D')
tOut.Branch('pip_PIDp', pip_PIDp, 'pip_PIDp/D')

tOut.Branch('pip_isMuon', pip_isMuon, 'pip_isMuon/I')
tOut.Branch('Kp_isMuon', Kp_isMuon, 'Kp_isMuon/I')

# Make a preselection to get only the truth matched Ds if simulation.
#from BsDsMuNuForRDS.TruthCuts import DsCut
testSel = '( TMath::Abs(Ds_TRUEID) == 431)'# && TMath::Abs(pi_TRUEID) == 211 )'
#( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431)
preselectionDict = {
    'sim'   : testSel #DsCut
    ,'data' : '1'
    }
preselectionCut = '(Kpl_PIDK > 4 && Kpl_PT > 300 && Kpl_MINIPCHI2 > 9 && Kmi_PIDK > 4 && Kmi_PT > 300 && Kmi_MINIPCHI2 > 9 && pi_PIDK < 2 && pi_PT > 300 && pi_MINIPCHI2 > 9 && mu_MINIPCHI2 > 16 && Ds_PT > 2500 && Ds_ENDVERTEX_CHI2 < 4 && Ds_DIRA_ORIVX > 0.999 && nLongTracks < 250 && nSPDHits < 600)'
c.Draw('>>eList', preselectionCut)
#c.Draw('>>eList', preselectionDict[dataType])
eList = gDirectory.Get('eList')

# Now loop over the events and plot the Dalitz variables.
numToProcess = c.GetEntries()
if dataType == 'data':
    numToProcess = c.GetEntries()
numPassedCounter = 0
for i in xrange(numToProcess):
    
    #print tOut
    if i%1000 == 0:
        sys.stdout.write('\rProcessing entry %i of %i...' %(i, numToProcess))
        sys.stdout.flush()
    if not eList.Contains(i): continue
    numPassedCounter += 1
    c.GetEntry(i)

    # Now make the Dalitz variables.
    Km_tlv  = TLorentzVector(Km_Px,  Km_Py,  Km_Pz,  Km_Pe)
    Kp_tlv  = TLorentzVector(Kp_Px,  Kp_Py,  Kp_Pz,  Kp_Pe)
    pip_tlv = TLorentzVector(pip_Px, pip_Py, pip_Pz, pip_Pe)
    mu_tlv  = TLorentzVector(mu_Px,  mu_Py,  mu_Pz,  mu_Pe)

    KK_tlv = Km_tlv + Kp_tlv
    Kmpi_tlv = Km_tlv + pip_tlv
    Kppi_tlv = Kp_tlv + pip_tlv

    # Switch the charges of the kaons...
    M_Kmpi[0] = Kmpi_tlv.M()
    M_Kppi[0] = Kppi_tlv.M()
    M_KmKp[0] = KK_tlv.M()
    M_Ds[0]   = inputDs_M[0]

    # Now check which region it falls into.
    # 0 is phi resonance, 1 is Kstar, 2 is non res.
    phi_flag   = abs(M_KmKp[0] - M_phi) < 20
    Kstar_flag = (abs(M_Kmpi[0] - M_Kstar) < 90) and not phi_flag
    nonRes_flag = not (phi_flag or Kstar_flag)

    resIndex = 0
    if Kstar_flag: resIndex = 1
    elif nonRes_flag: resIndex = 2
    resFlag[0] = resIndex

    Beta_Kp[0]  = (Km_P[0] + pip_P[0] - Kp_P[0]) / (Km_P[0] + pip_P[0] + Kp_P[0]) 
    Beta_Km[0]  = (Kp_P[0] + pip_P[0] - Km_P[0]) / (Km_P[0] + pip_P[0] + Kp_P[0])
    Beta_pip[0] = (Km_P[0] + Kp_P[0]  - pip_P[0]) / (Km_P[0] + pip_P[0] + Kp_P[0])

    # Now the Lc and Dp WM vars.
    Eproton = (Kp_P**2 + M_p**2)**0.5
    Epion   = (Kp_P**2 + M_pi**2)**0.5

    Kasp_tlv = TLorentzVector(Kp_Px, Kp_Py, Kp_Pz, Eproton)
    Kaspi_tlv = TLorentzVector(Kp_Px, Kp_Py, Kp_Pz, Epion)

    pKpi_tlv = Kasp_tlv + Km_tlv + pip_tlv
    piKpi_tlv = Kaspi_tlv + Km_tlv + pip_tlv

    WM_pKpi[0] = pKpi_tlv.M()
    WM_piKpi[0] = piKpi_tlv.M()

    # Now the Dst WM variable.
    Kaspi_K_tlv = Kaspi_tlv + Km_tlv
    WM_Dst[0] = piKpi_tlv.M() - Kaspi_K_tlv.M()

    # Another for when the Km takes the pion mass hypothesis.
    E_Kmaspim = (Km_P**2 + M_pi**2)**0.5
    tlv_Kmaspim = TLorentzVector(Km_Px, Km_Py, Km_Pz, E_Kmaspim)

    tlv_KmaspimKppip = tlv_Kmaspim + pip_tlv + Kp_tlv
    #tlv_Dst2 = tlv_KmaspimKppip - (tlv_Kmaspim + Kp_tlv)
    WM_Dst2[0] = tlv_KmaspimKppip.M() - (tlv_Kmaspim + Kp_tlv).M() 

    # How about when we subtract the correctly ID'd particles?
    WM_Dst3[0] = tlv_KmaspimKppip.M() - (Kp_tlv + pip_tlv).M()

    # Now again but for Kp misID
    WM_Dst4[0] = piKpi_tlv.M() - (Km_tlv + pip_tlv).M()

    # Now the Jspi->mumu WM.
    # Reconstruct the pion as a muon.
    #print pip_P
    E_pipasmu  = (pip_P**2 + M_mu**2)**0.5
    piasmu_tlv = TLorentzVector(pip_Px, pip_Py, pip_Pz, E_pipasmu)

    Jpsi_tlv   = piasmu_tlv + mu_tlv
    WM_Jpsi_pi[0] = Jpsi_tlv.M()

    # One for when the kaon is the muon.
    E_kpasmu = (Kp_P**2 + M_mu**2)**0.5
    kpasmu_tlv = TLorentzVector(Kp_Px, Kp_Py, Kp_Pz, E_kpasmu)

    Jpsi_K_tlv = kpasmu_tlv + mu_tlv
    WM_Jpsi_K[0] = Jpsi_K_tlv.M()

    # Now the Kstar vetoes.
    # We have already misreconstructed the same sign kaon as a pion.
    # Combine it with the opposite sign kaon.
    Kstar_tlv   = Kaspi_tlv + Km_tlv
    WM_Kstar[0] = Kstar_tlv.M()

    # Now misreco the opp sign kaon as a pion
    # and combine with the same sign kaon.
    E_Kmaspim = (Km_P**2 + M_pi**2)**0.5
    Kmaspim_tlv = TLorentzVector(Km_Px, Km_Py, Km_Pz, E_Kmaspim)

    Kstar_Kmaspim_tlv = Kmaspim_tlv + Kp_tlv
    WM_Kstar2[0] = Kstar_Kmaspim_tlv.M()
    
    # Now check the pion under kaon hypothesis doesn't form
    # a phi with the opposite charge kaon.
    E_pipaskp = (pip_P**2 + M_K**2)**0.5
    pipaskp_tlv = TLorentzVector(pip_Px, pip_Py, pip_Pz, E_pipaskp)
    phi_tlv = pipaskp_tlv + Km_tlv
    WM_phi[0] = phi_tlv.M()

    # Now check the opposite sign kaon under pion hypothesis
    # and pair with the pion to check for f0 etc. backgrounds.
    #E_Kmaspim = (Km_P**2 + M_pi**2)**0.5
    #Kmaspim_tlv = TLorentzVector(Km_Px, Km_Py, Km_Pz, E_Kmaspim)
    f0_tlv = Kmaspim_tlv + pip_tlv
    WM_f0[0] = f0_tlv.M()
    
    tOut.Fill()
    
print 
print 'Created ntuple.'
print 'Passed %i entries of %i.' %(numPassedCounter, numToProcess)
tOut.AutoSave()
fOut.Close()
