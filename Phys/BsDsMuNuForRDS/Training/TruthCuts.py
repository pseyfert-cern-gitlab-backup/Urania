###################################################################################
# Module to contain the truth matching cut strings for the various Bs2DsX modes.
###################################################################################

###################################################################################
# Cut to say it's a valid reconstructed Ds2KKpi decay.
###################################################################################
isDsDs     = '( TMath::Abs(Ds_TRUEID) == 431 )'
ispipi     = '( TMath::Abs(pi_TRUEID) == 211 )'
isKmKm     = '( TMath::Abs(Kmi_TRUEID) == 321)'
isKpKp     = '( TMath::Abs(Kpl_TRUEID) == 321)'

# Now are the Ds daughters from an actual Ds?
ispiFromDs = '( TMath::Abs(pi_MC_MOTHER_ID) == 431 )'
# BUT for the kaon it could be from either a Ds or from a phi.
# So check for both scenarios.
isKmFromDs = '( (TMath::Abs(Kmi_MC_MOTHER_ID) == 431) || ( (TMath::Abs(Kmi_MC_MOTHER_ID) == 333) && (TMath::Abs(Kmi_MC_GD_MOTHER_ID) == 431) ) )'
isKpFromDs = '( (TMath::Abs(Kpl_MC_MOTHER_ID) == 431) || ( (TMath::Abs(Kpl_MC_MOTHER_ID) == 333) && (TMath::Abs(Kpl_MC_GD_MOTHER_ID) == 431) ) )'
isDs2KKpi = '( %s && %s && %s && %s && %s && %s && %s )' %(isDsDs, ispipi, isKmKm, isKpKp, ispiFromDs, isKmFromDs, isKpFromDs)

###################################################################################
# Now some muon truth cuts.
###################################################################################
muIsmuCut = '( TMath::Abs(mu_TRUEID) == 13 )'
muIsmuFromtauCut = '( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15)'

tauFromBsCut = '( %s && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )' %muIsmuFromtauCut
muFromBsCut  = '( %s && TMath::Abs(mu_MC_MOTHER_ID) == 531 )' %muIsmuCut

###################################################################################
# Some Bs and Ds hierarchy cuts.
###################################################################################
# Cut to say the head of the chain is a genuine Bs
isBsBs = '( TMath::Abs(Bs_0_TRUEID) == 531 )'
# Cut to indicate the Ds was a direct product of the Bs.
DsFromBsCut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )'

# Cuts to say the D came from an intermediate Ds*.
DsStarCut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 433)'
Ds2460Cut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 20433 )'
Ds2536Cut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 10433 )'
Ds0StarCut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 )'

# Cut to say the grandmother of the Ds was the Bs.
# This is specifically to look for feed-down to Ds* from higher
# excited states.
DsGMIsBsCut  = '( TMath::Abs(Ds_MC_GD_MOTHER_ID) == 531 )'
DsGMIsDs2460 = '( TMath::Abs(Ds_MC_GD_MOTHER_ID) == 20433 )'
DsGMIsDs2536 = '( TMath::Abs(Ds_MC_GD_MOTHER_ID) == 10433 )'
DsGMIsDs0    = '( TMath::Abs(Ds_MC_GD_MOTHER_ID) == 10431 )'

# A cut to say the the Ds is from a b-decay, either produced immediately in the Bs
# decay or produced in some Bs -> Dsstar -> Ds chain.
DsNotPromptCut = '( (TMath::Abs(Ds_MC_MOTHER_ID) == 531) || ((TMath::Abs(Ds_MC_GD_MOTHER_ID) == 531)) )'

# Some more general cuts.
# Is the Ds from a Bs, ignoring any intermediate excited Ds states?
BsInDsHierarchy = '( TMath::Abs(Ds_MC_MOTHER_ID) == 531 || TMath::Abs(Ds_MC_GD_MOTHER_ID) == 531 || TMath::Abs(Ds_MC_GD_GD_MOTHER_ID) == 531)'
# Is the muon candidate from a Bs or from a tau from a Bs?
muonIsSignal = '(%s || %s)' %(muIsmuCut, tauFromBsCut)
# Now one to determine if it's what we'd call "signal", i.e. any of the valid modes.
isSignal = '(%s && %s && %s && %s)' %(muonIsSignal, BsInDsHierarchy, isDs2KKpi, isBsBs)

###################################################################################
# Now some cuts for the double charm.
###################################################################################
# For the muon in these, there are only so many weakly decaying states.
# So I think we can just explicitly include them all in the muon checking.
# In order these check the muon is either from a D+, D0, Ds, Lambdac+, Xic+, Xic0, Omegac0.
isMuonFromCharm = '( (%s) && (%s || %s || %s || %s || %s || %s || %s) )' %(muIsmuCut,
                                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 411',
                                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 421',
                                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 431',
                                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 4122',
                                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 4232',
                                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 4132',
                                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 4332')

isMuonFromTauFromCharm = '( (%s) && (%s || %s || %s || %s || %s || %s || %s) )' %(muIsmuFromtauCut,
                                                                                 'TMath::Abs(mu_MC_GD_MOTHER_ID) == 411',
                                                                                 'TMath::Abs(mu_MC_GD_MOTHER_ID) == 421',
                                                                                 'TMath::Abs(mu_MC_GD_MOTHER_ID) == 431',
                                                                                 'TMath::Abs(mu_MC_GD_MOTHER_ID) == 4122',
                                                                                 'TMath::Abs(mu_MC_GD_MOTHER_ID) == 4232',
                                                                                 'TMath::Abs(mu_MC_GD_MOTHER_ID) == 4132',
                                                                                 'TMath::Abs(mu_MC_GD_MOTHER_ID) == 4332')
isMuonOrTauonFromCharm = '(%s || %s)' %(isMuonFromCharm, isMuonFromTauFromCharm)

# One for when the Bs is really another b-hadron.
isBsLb = '( TMath::Abs(Bs_0_TRUEID) == 5122 )'
isBsB0 = '( TMath::Abs(Bs_0_TRUEID) == 511 )'
isBsBu = '( TMath::Abs(Bs_0_TRUEID) == 521 )'

# One for when the reconstructed Bs is really a b-hadron of any kind in our MC.
isBsBeauty = '( %s || %s || %s || %s )' %(isBsLb, isBsBs, isBsB0, isBsBu)

# Now one to verify that there is a beauty particle in the hierarchy.
# We need to check the particles in the hierarchy and check each against the beauty particles we could have.
isBeautyInDsHierarchy = '( %s || %s || %s || %s || %s || %s || %s || %s)' %('(TMath::Abs(Ds_MC_MOTHER_ID) == 511)',
                                                                            '(TMath::Abs(Ds_MC_GD_MOTHER_ID) == 511)',
                                                                            '(TMath::Abs(Ds_MC_MOTHER_ID) == 521)',
                                                                            '(TMath::Abs(Ds_MC_GD_MOTHER_ID) == 521)',
                                                                            '(TMath::Abs(Ds_MC_MOTHER_ID) == 531)',
                                                                            '(TMath::Abs(Ds_MC_GD_MOTHER_ID) == 531)',
                                                                            '(TMath::Abs(Ds_MC_MOTHER_ID) == 5122)',
                                                                            '(TMath::Abs(Ds_MC_GD_MOTHER_ID) == 5122)')

# Now check the muon candidate and the Ds candidate come from the same B hadron.
# First 2 cases are for muon, second 2 for tau.
isDsAndmuFromSameBeauty = '( (TMath::Abs(mu_MC_MOTHER_ID)  == TMath::Abs(Ds_MC_MOTHER_ID)) ||' \
                          '(TMath::Abs(mu_MC_MOTHER_ID)    == TMath::Abs(Ds_MC_GD_MOTHER_ID)) || ' \
                          '(TMath::Abs(mu_MC_GD_MOTHER_ID) == TMath::Abs(Ds_MC_MOTHER_ID)) ||' \
                          '(TMath::Abs(mu_MC_GD_MOTHER_ID) == TMath::Abs(Ds_MC_GD_MOTHER_ID)) ) '

# Now one catch-all expression for checking if it's really double charm.
# Or, is it a valid Ds candidate, is the muon from a charm decay, is the
# reconstructed Bs candidate really a b-hadron, did the Ds come from a b-hadron,
# and finally do the muon and Ds candidates share a common b-hadron in their ancestry.
isDoubleCharm = '(%s && %s && %s && %s)' %(isDs2KKpi,
                                                 isMuonOrTauonFromCharm,
                                                 #isBsBeauty,
                                                 isBeautyInDsHierarchy,
                                                 isDsAndmuFromSameBeauty)

#######################################################################################################
# Now make a dictionary of these cuts for easy formatting.
cutComponentDict = {
    'isDs2KKpi'        : isDs2KKpi
    ,'tauFromBsCut'    : tauFromBsCut
    ,'muFromBsCut'       : muFromBsCut
    ,'isBsBs'      : isBsBs
    ,'DsStarCut'   : DsStarCut
    ,'Ds2460Cut'   : Ds2460Cut
    ,'Ds2536Cut'   : Ds2536Cut
    ,'Ds0StarCut'  : Ds0StarCut
    ,'DsFromBsCut' : DsFromBsCut
    }

# Dsstar cut, without specifying feed down.
DsStarCutFull = '(%s && %s)' %(isDs2KKpi, DsStarCut)

# Now for the cut independent strings.
# For the ground state Ds modes...
# For Bs0->Dsmu:
Dsmu = '( %(isDs2KKpi)s && %(muFromBsCut)s && %(DsFromBsCut)s && %(isBsBs)s )' %cutComponentDict
# for the Bs0->Dstau:
Dstau = '(%(isDs2KKpi)s && %(tauFromBsCut)s && %(DsFromBsCut)s && %(isBsBs)s )' %cutComponentDict

# For the DsStar modes...
DsStarmu  = '( %(isDs2KKpi)s && %(muFromBsCut)s && %(DsStarCut)s && %(isBsBs)s )' %cutComponentDict
DsStartau = '( %(isDs2KKpi)s && %(tauFromBsCut)s && %(DsStarCut)s && %(isBsBs)s )' %cutComponentDict

# For the Ds2460 modes...
Ds2460mu  = '( %(isDs2KKpi)s && %(muFromBsCut)s  && %(Ds2460Cut)s && %(isBsBs)s )' %cutComponentDict
Ds2460tau = '( %(isDs2KKpi)s && %(tauFromBsCut)s && %(Ds2460Cut)s && %(isBsBs)s )' %cutComponentDict

# For the Ds2536 modes...
Ds2536mu  = '( %(isDs2KKpi)s && %(muFromBsCut)s  && %(Ds2536Cut)s && %(isBsBs)s )' %cutComponentDict
Ds2536tau = '( %(isDs2KKpi)s && %(tauFromBsCut)s && %(Ds2536Cut)s && %(isBsBs)s )' %cutComponentDict

# For the Ds0Star modes...
Ds0Starmu  = '( %(isDs2KKpi)s && %(muFromBsCut)s  && %(Ds0StarCut)s && %(isBsBs)s )' %cutComponentDict
Ds0Startau = '( %(isDs2KKpi)s && %(tauFromBsCut)s && %(Ds0StarCut)s && %(isBsBs)s )' %cutComponentDict



###################################################################
# Now put the final cuts into a dictionary so we can iterate over the relevant states.
# in the package scripts.
cutDict = {
    'Dsmu'         : Dsmu
    ,'Dstau'       : Dstau
    ,'DsStarmu'    : DsStarmu
    ,'DsStartau'   : DsStartau
    ,'Ds2460mu'    : Ds2460mu
    ,'Ds2460tau'   : Ds2460tau
    ,'Ds2536mu'    : Ds2536mu
    ,'Ds2536tau'   : Ds2536tau
    ,'Ds0Starmu'   : Ds0Starmu
    ,'Ds0Startau'  : Ds0Startau
    }
    
