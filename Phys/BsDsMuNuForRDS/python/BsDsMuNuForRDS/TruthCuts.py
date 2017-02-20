###################################################################################
# Module to contain the truth matching cut strings for the various Bs2DsX modes.
###################################################################################

###################################################################################
# Cut to say it's a valid reconstructed Ds2KKpi decay.
###################################################################################
# Match all the IDs
isDsDs     = '( TMath::Abs(Ds_TRUEID) == 431 )'
ispipi     = '( TMath::Abs(pi_TRUEID) == 211 )'
isKmKm     = '( TMath::Abs(Kmi_TRUEID) == 321)'
isKpKp     = '( TMath::Abs(Kpl_TRUEID) == 321)'
# Finally check that the pion and the two kaons (allowing for the phi resonances) have a shared mother
# by using the MC_MOTHER_KEY
isDsDaughtersCommon = '( ( (pi_MC_MOTHER_KEY == Kmi_MC_MOTHER_KEY) && (pi_MC_MOTHER_KEY == Kpl_MC_MOTHER_KEY) ) ||'\
                      '( (pi_MC_MOTHER_KEY == Kmi_MC_GD_MOTHER_KEY) && (pi_MC_MOTHER_KEY == Kpl_MC_GD_MOTHER_KEY) ) )'
# Combine these.
isDs2KKpi = '( %s && %s && %s && %s && %s )' %(isDsDs, ispipi, isKmKm, isKpKp, isDsDaughtersCommon)

###################################################################################
# Now some muon truth cuts.
###################################################################################
# Match the muon IDs
muIsmuCut = '( TMath::Abs(mu_TRUEID) == 13 )'
muIsmuFromtauCut = '( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15)'
# Now combine these with tests of parenthood.
tauFromBsCut = '( %s && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )' %muIsmuFromtauCut
muFromBsCut  = '( %s && TMath::Abs(mu_MC_MOTHER_ID) == 531 )' %muIsmuCut

###################################################################################
# Some Bs and Ds hierarchy cuts.
###################################################################################
# Cut to say the head of the chain is a genuine Bs
isBsBs = '( TMath::Abs(Bs_0_TRUEID) == 531 )'
# Cut to indicate the Ds was a direct product of the Bs.
DsFromBsCut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )'
# Cuts to say the Ds came from an intermediate Ds*/Ds2317/Ds2460.
DsStarCut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 433)'
Ds2317Cut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 10431 )'
Ds2460Cut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 20433 )'

# Cut to look for feed-down to Ds* from Ds2460.
DsGMIsBsCut  = '( TMath::Abs(Ds_MC_GD_MOTHER_ID) == 531 )'
DsGMIsDs2460 = '( TMath::Abs(Ds_MC_GD_MOTHER_ID) == 20433 )'

# Some more general cuts.
# Is the Ds from a Bs, ignoring any intermediate excited Ds states?
BsInDsHierarchy = '( TMath::Abs(Ds_MC_MOTHER_ID) == 531 || TMath::Abs(Ds_MC_GD_MOTHER_ID) == 531 || TMath::Abs(Ds_MC_GD_GD_MOTHER_ID) == 531)'
# Is the muon candidate from a Bs or from a tau from a Bs?
muonIsSignal = '(%s || %s)' %(muFromBsCut, tauFromBsCut)

# Finally have a cut to verify that the muon parent/grandparent and the Ds
# parent/grandparent/greatgrandparent are the same using the MC KEY.
isDsandmuonCommon = '( ( Ds_MC_MOTHER_KEY       == mu_MC_MOTHER_KEY ) ||'        \
                    '(   Ds_MC_MOTHER_KEY       == mu_MC_GD_MOTHER_KEY ) ||'     \
                    '(   Ds_MC_GD_MOTHER_KEY    == mu_MC_MOTHER_KEY ) ||'     \
                    '(   Ds_MC_GD_MOTHER_KEY    == mu_MC_GD_MOTHER_KEY ) ||'  \
                    '(   Ds_MC_GD_GD_MOTHER_KEY == mu_MC_MOTHER_KEY ) ||'  \
                    '(   Ds_MC_GD_GD_MOTHER_KEY == mu_MC_GD_MOTHER_KEY ) )'
                    
# Now one to determine if it's what we'd call "signal", i.e. any of the valid modes.   
isSignal = '( %s && %s && %s && %s && %s )' %(muonIsSignal, BsInDsHierarchy,
                                              isDs2KKpi, isBsBs, isDsandmuonCommon)

###################################################################################
# Now some cuts for the double charm.
###################################################################################
# For the muon in these, there are only so many weakly decaying states.
# So I think we can just explicitly include them all in the muon checking.
# In order these check the muon is either from a D+, D0, Ds or a Lambdac+.
isMuonFromCharm = '( (%s) && (%s || %s || %s || %s) )' %(muIsmuCut,
                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 411',
                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 421',
                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 431',
                                                         'TMath::Abs(mu_MC_MOTHER_ID) == 4122')
isMuonFromTauFromCharm = '( (%s) && (%s || %s || %s || %s) )' %(muIsmuFromtauCut,
                                                                'TMath::Abs(mu_MC_GD_MOTHER_ID) == 411',
                                                                'TMath::Abs(mu_MC_GD_MOTHER_ID) == 421',
                                                                'TMath::Abs(mu_MC_GD_MOTHER_ID) == 431',
                                                                'TMath::Abs(mu_MC_GD_MOTHER_ID) == 4122')
isMuonOrTauonFromCharm = '(%s || %s)' %(isMuonFromCharm, isMuonFromTauFromCharm)

# One for when the Bs is really another b-hadron.
isBsLb = '( TMath::Abs(Bs_0_TRUEID) == 5122 )'
isBsB0 = '( TMath::Abs(Bs_0_TRUEID) == 511 )'
isBsBu = '( TMath::Abs(Bs_0_TRUEID) == 521 )'
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

# Now check there is a common ancestor between the Ds and muon.
isDsAndmuFromSameBeauty = '( ( Ds_MC_MOTHER_KEY == mu_MC_GD_MOTHER_KEY ) ||'        \
                          '( Ds_MC_MOTHER_KEY == mu_MC_GD_GD_MOTHER_KEY ) ||'       \
                          '( Ds_MC_GD_MOTHER_KEY == mu_MC_GD_MOTHER_KEY ) ||'       \
                          '( Ds_MC_GD_MOTHER_KEY == mu_MC_GD_GD_MOTHER_KEY ) ||'    \
                          '( Ds_MC_GD_GD_MOTHER_KEY == mu_MC_GD_MOTHER_KEY ) ||'    \
                          '( Ds_MC_GD_GD_MOTHER_KEY == mu_MC_GD_GD_MOTHER_KEY ) )'

# Now one catch-all expression for checking if it's really double charm.
# Or, is it a valid Ds candidate, is the muon from a charm decay, is the
# reconstructed Bs candidate really a b-hadron, did the Ds come from a b-hadron,
# and finally do the muon and Ds candidates share a common b-hadron in their ancestry.
isDoubleCharm = '(%s && %s && %s && %s && %s)' %(isDs2KKpi
                                                 ,isMuonOrTauonFromCharm
                                                 ,isBsBeauty
                                                 ,isBeautyInDsHierarchy
                                                 ,isDsAndmuFromSameBeauty)

#######################################################################################################
# Now make a dictionary of these cuts for easy formatting.
#######################################################################################################
cutComponentDict = {
    'isDs2KKpi'        : isDs2KKpi
    ,'tauFromBsCut'    : tauFromBsCut
    ,'muFromBsCut'     : muFromBsCut
    ,'isSignal'        : isSignal
    ,'isDoubleCharm'   : isDoubleCharm
    ,'isBsBs'          : isBsBs
    ,'DsStarCut'       : DsStarCut
    ,'Ds2317Cut'       : Ds2317Cut
    ,'Ds2460Cut'       : Ds2460Cut
    ,'DsFromBsCut'     : DsFromBsCut
    }

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

# For the Ds0Star modes...
Ds2317mu  = '( %(isDs2KKpi)s && %(muFromBsCut)s  && %(Ds2317Cut)s && %(isBsBs)s )' %cutComponentDict
Ds2317tau = '( %(isDs2KKpi)s && %(tauFromBsCut)s && %(Ds2317Cut)s && %(isBsBs)s )' %cutComponentDict

###################################################################
# Now put the final cuts into a dictionary so we can iterate over the relevant states.
# in the package scripts.
###################################################################
allDsmu  = '( %s || %s || %s || %s )' %(Dsmu, DsStarmu, Ds2317mu, Ds2460mu)
allDstau = '( %s || %s || %s || %s )' %(Dstau, DsStartau, Ds2317tau, Ds2460tau)

cutDict = {
    'Dsmu'         : Dsmu
    ,'Dstau'       : Dstau
    ,'DsStarmu'    : DsStarmu
    ,'DsStartau'   : DsStartau
    ,'Ds2370mu'    : Ds2317mu
    ,'Ds2370tau'   : Ds2317tau
    ,'Ds2460mu'    : Ds2460mu
    ,'Ds2460tau'   : Ds2460tau
    ,'allDsmu'     : allDsmu
    ,'allDstau'    : allDstau
    }

###################################################################
# A dict for the dataTags.
# These are to be generally applied in the selections.
###################################################################
tagDict = {
    'MC09_Mu'     : isSignal
    ,'MC09_Tau'   : isSignal
    ,'MC_BdDstDs' : isDoubleCharm
    ,'MC_BsDsDs'  : isDoubleCharm
    ,'MC_BuD0Ds'  : isDoubleCharm
    ,'MC_LbLcDs'  : isDoubleCharm
    }
