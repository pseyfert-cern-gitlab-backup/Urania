from ROOT import *

# Global factors
br_kspipi = 0.69
lumi_gain = 2.

# Get alpha_2011
import fiducial_2011
smb_2011              = 2.7e-6
trig_presc_2011       = 0.5
gen_eff_cut_mumu_2011 = 0.27

path_2011      = '/afs/cern.ch/user/d/diegoms/vol5/ks/'
fkspipi_2011   = TFile(path_2011 + 'KsPiPi_MC11_ntuples.root')
fksmumu_2011   = TFile(path_2011 + 'KsMuMu_MC11_ntuples.root')
fkspipimb_2011 = TFile(path_2011 + 'KsPiPi_MinBiasData_TriggerUnbiased_ntuple.root')
kspipi_2011    = fkspipi_2011.Get('Kspipi')
kspipimc_2011  = fkspipi_2011.Get('Kspipi_mct')
ksmumu_2011    = fksmumu_2011.Get('Ksmumu')
ksmumumc_2011  = fksmumu_2011.Get('Ksmumu_mct')
kspipimb_2011  = fkspipimb_2011.Get('Kspipi')

#ppmbcuts_2011 = fiducial_2011.selection
pipicuts_2011    = fiducial_2011.fiducial
mumuselcuts_2011 = fiducial_2011.fiducial + ' && mu1ismu && mu2ismu'
mumucuts_2011    = mumuselcuts_2011 + ' && ' + fiducial_2011.tos

npipi_strip_mb    = kspipimb_2011.GetEntries(pipicuts_2011)
eff_pipi_strip_mc = kspipi_2011.GetEntries(pipicuts_2011)*1./kspipimc_2011.GetEntries()
eff_mumu_strip_mc = ksmumu_2011.GetEntries(mumucuts_2011)*1./ksmumumc_2011.GetEntries()

par = eff_pipi_strip_mc/(trig_presc_2011*gen_eff_cut_mumu_2011*
                         eff_mumu_strip_mc*npipi_strip_mb)

eff_trigger_2011 = trig_presc_2011*ksmumu_2011.GetEntries(mumucuts_2011)*1./ksmumu_2011.GetEntries(mumuselcuts_2011)

alpha_2011 = br_kspipi*smb_2011*par
print '--- Alpha 2011:', alpha_2011

sel_eff_2011 = gen_eff_cut_mumu_2011*ksmumu_2011.GetEntries(mumuselcuts_2011)*1./ksmumumc_2011.GetEntries()

# Get alpha_2012
import fiducial

gen_eff_cut_mumu_2012 = 0.27
smb_2012              = 3.39e-7

path_2012       = '/eos/lhcb/wg/RD/K0SMuMu/NEW/'
#fkspipi_2012    = TFile(path_2012 + 'MC/Kspipi_MC2012_mcMatch_MVA.root')
#fkspipimc_2012  = TFile(path_2012 + 'MC/Kspipi_MC2012_mcMatch.root')
fksmumu_2012    = TFile(path_2012 + 'MC/Ksmumu_MC2012_mcMatch_MVA.root')
fksmumumc_2012  = TFile(path_2012 + 'MC/Ksmumu_MC2012_mcMatch.root')
fkspipimb_2012  = TFile(path_2012 + 'DATA/KsMB_Data2012_MVA.root')
fksmumustr_2012 = TFile(path_2012 + 'MC/Ksmumu_StrippedMC2012_mcMatch_MVA.root')
#kspipi_2012     = fkspipi_2012.Get('DecayTree')
#kspipimc_2012   = fkspipimc_2012.Get('MCtruthKspipi/MCDecayTree')
ksmumu_2012     = fksmumu_2012.Get('DecayTree')
ksmumumc_2012   = fksmumumc_2012.Get('MCtruthKsmumu/MCDecayTree')
kspipimb_2012   = fkspipimb_2012.Get('DecayTree')
ksmumustr_2012  = fksmumustr_2012.Get('DecayTree')

sel_eff_2012 = gen_eff_cut_mumu_2012*ksmumu_2012.GetEntries('StrippingKS02MuMuLine'\
                                                                'Decision && ' +
                                                            fiducial.fullsel)*1./ksmumumc_2012.GetEntries()

eff_trigger_2012 = ksmumustr_2012.GetEntries(fiducial.SEL['TOS1_']  + " && StrippingKS02MuMuLineDecision")*1./ksmumustr_2012.GetEntries(fiducial.fullsel + " && StrippingKS02MuMuLineDecision")

trigger_gain = eff_trigger_2012/eff_trigger_2011

alpha_2012 = alpha_2011*sel_eff_2011/(trigger_gain*lumi_gain*sel_eff_2012)

print '--- Alpha 2012 extrapolated:', alpha_2012
print '--- Expected:', 7e-11
print '--- Trigger efficiency 2011:', eff_trigger_2011
print '--- Trigger efficiency 2012:', eff_trigger_2012
print '--- Trigger gain:', trigger_gain
