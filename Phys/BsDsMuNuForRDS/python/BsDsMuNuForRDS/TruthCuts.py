###################################################################################
# Module to contain the truth matching cut strings for the various Bs2DsX modes.
###################################################################################

# Will start with some common cuts. There will be redundancies there but I don't care too much.
# Cut to say it's a valid reconstructed Ds2KKpi decay.
DsCut = '( TMath::Abs(Ds_TRUEID) == 431 && TMath::Abs(pi_TRUEID) == 211 && TMath::Abs(pi_MC_MOTHER_ID) == 431 && TMath::Abs(Kpl_TRUEID) == 321 && TMath::Abs(Kpl_MC_MOTHER_ID) == 431 && TMath::Abs(Kmi_TRUEID) == 321 && TMath::Abs(Kmi_MC_MOTHER_ID) == 431 && (Kpl_MC_GD_MOTHER_ID ++ Kmi_MC_MOTHER_ID) )'

# Cut to say it's a valid mu from a Bs->tau->mu
tauCut = '( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 15 && TMath::Abs(mu_MC_GD_MOTHER_ID) == 531 )'

# Cut to say it's a valid mu from Bs->mu
muCut = '( TMath::Abs(mu_TRUEID) == 13 && TMath::Abs(mu_MC_MOTHER_ID) == 531 )'

# Cut to say the head of the chain is a genuine Bs
Bs0Cut = '( TMath::Abs(Bs_0_TRUEID) == 531 )'

# Cut to indicate the Ds was a direct product of the Bs.
DsFromBsCut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 531 )'

# Cut to say the D came from an intermediate Ds* which came directly from a Bs0.
DsStarCut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 433)'
Ds2460Cut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 20433 )'
Ds2536Cut = '( TMath::Abs(Ds_MC_MOTHER_ID) == 10433 )'
# For the Ds0*(2317)
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

# Now make a dictionary of these cuts for easy formatting.
cutComponentDict = {
    'DsCut'        : DsCut
    ,'tauCut'      : tauCut
    ,'muCut'       : muCut
    ,'Bs0Cut'      : Bs0Cut
    ,'DsStarCut'   : DsStarCut
    ,'Ds2460Cut'   : Ds2460Cut
    ,'Ds2536Cut'   : Ds2536Cut
    ,'Ds0StarCut'  : Ds0StarCut
    ,'DsFromBsCut' : DsFromBsCut
    }

# Dsstar cut, without specifying feed down.
DsStarCutFull = '(%s && %s)' %(DsCut, DsStarCut)

# Now for the cut independent strings.
# For the ground state Ds modes...
# For Bs0->Dsmu:
Dsmu = '( %(DsCut)s && %(muCut)s && %(DsFromBsCut)s && %(Bs0Cut)s )' %cutComponentDict
# for the Bs0->Dstau:
Dstau = '(%(DsCut)s && %(tauCut)s && %(DsFromBsCut)s && %(Bs0Cut)s )' %cutComponentDict

# For the DsStar modes...
DsStarmu  = '( %(DsCut)s && %(muCut)s && %(DsStarCut)s && %(Bs0Cut)s )' %cutComponentDict
DsStartau = '( %(DsCut)s && %(tauCut)s && %(DsStarCut)s && %(Bs0Cut)s )' %cutComponentDict

# For the Ds2460 modes...
Ds2460mu  = '( %(DsCut)s && %(muCut)s  && %(Ds2460Cut)s && %(Bs0Cut)s )' %cutComponentDict
Ds2460tau = '( %(DsCut)s && %(tauCut)s && %(Ds2460Cut)s && %(Bs0Cut)s )' %cutComponentDict

# For the Ds2536 modes...
Ds2536mu  = '( %(DsCut)s && %(muCut)s  && %(Ds2536Cut)s && %(Bs0Cut)s )' %cutComponentDict
Ds2536tau = '( %(DsCut)s && %(tauCut)s && %(Ds2536Cut)s && %(Bs0Cut)s )' %cutComponentDict

# For the Ds0Star modes...
Ds0Starmu  = '( %(DsCut)s && %(muCut)s  && %(Ds0StarCut)s && %(Bs0Cut)s )' %cutComponentDict
Ds0Startau = '( %(DsCut)s && %(tauCut)s && %(Ds0StarCut)s && %(Bs0Cut)s )' %cutComponentDict


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
    
