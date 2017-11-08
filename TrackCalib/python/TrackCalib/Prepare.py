from array import array
import argparse
import sys
import os.path
import time
import math
from collections import defaultdict, namedtuple
import numpy as np

from ROOT import TTree, TChain, TFile, TVector3, TObject
from TrackCalib.Utils import *
import ROOT


# ------------------------------------------------------
# -- Prepare data, so it can be used more efficiently later
# ------------------------------------------------------

def Prepare(mode, WGProduct, year, test = False, method="", variables = "", noWeight = False, matchCrit = "", cuts = "", simVer = "Sim09b", weightVar = "nSPDHits", verbose = False, maxEntries = 2.5e7):
    #weight ranges

    # start printout
    print '##########################################################'
    print '#               Welcome to TrackEffReducer               #'
    print '#                    Running on %s                     #' %mode.ljust(4)
    print '##########################################################'

    #set the mode
    data = True if mode == "Data" else False
    if mode not in ["Data","MC"]:
        print ErrorMsg('Invalid mode %s given, must be "Data" or "MC"!' %mode)

    #list of methods used, default all
    meth_list = ['Long','T','Velo'] if method == "" else [method]
    for meth in meth_list:
        if meth not in ['Long','T','Velo']:
            print ErrorMsg('Invalid method %s given, must be "Long", "T" or "Velo"!' %meth)

    #create tuple path if not existing
    outputPath = "tuples"
    if not os.path.exists(outputPath):
        if verbose: InfoMsgList("Creating new folder for tuples: ", outputPath)
        os.makedirs(outputPath)
    else: InfoMsgList("Output path used: ", outputPath)

    #set output file name
    if matchCrit == "":
        if mode == "MC": outputFileName = outputPath+"/trackEffTuple_"+mode+"_"+year+"_"+simVer
        else: outputFileName = outputPath+"/trackEffTuple_"+mode+"_"+year
        if WGProduct:   outputFileName += "_WG"
        outputFileName += ".root"
    else:
        if mode == "MC": outputFileName = outputPath+"/trackEffTuple_"+mode+"_"+year+"_"+simVer+"_tight"
        else: outputFileName = outputPath+"/trackEffTuple_"+mode+"_"+year + "_tight"
        if WGProduct:   outputFileName += "_WG"
        outputFileName += ".root"

    #default variables lists to keep on tuple (split in global/particle vars)
    var_list_part = [
            "P"             ,
            "PT"            ,
            "ETA"           ,
            "M"             ,
            "ENDVERTEX_CHI2",
            "ENDVERTEX_X",
            "ENDVERTEX_Y",
            "ENDVERTEX_Z",
            "IPCHI2_OWNPV"  ,
            "OWNPV_X"  ,
            "OWNPV_Y"  ,
            "OWNPV_Z"  ,
            "IP_OWNPV"      ,
            "TRACK_CHI2NDOF",
            "BKGCAT",
            "Reconstructed",
            "Assoc",
            "Overlap_TTFraction",
            "Overlap_ITFraction",
            "Overlap_OTFraction",
            "Overlap_TFraction",
            "Overlap_VeloFraction",
            "Overlap_MuonFraction",
            "Matched_GhostProb",
            "TRACK_nVeloHits",
            "TRACK_nVeloRHits",
            "TRACK_nVeloPhiHits",
            "TRACK_nTTHits",
            "TRACK_nITHits",
            "TRACK_nOTHits",
            "TRACK_nMuHits"
            ]

    #If any other variable is needed by the user, it needs to be hardcoded here.
    var_list_glob = [
            "totCandidates",
            "nTracks"      ,
            "nLongTracks"  ,
            "nTTTracks"    ,
            "nVeloTracks"  ,
            "nPVs"         ,
            "nSPDHits"     ,
            "nVeloClusters",
            "nITClusters"  ,
            "nOTClusters"  ,
            "nTTClusters"  ,
            "nRich1Hits"   ,
            "nRich2Hits"   ,
            "nMuonTracks"  ,
            "matched"      ,
            "Polarity"     ,
            "runNumber"
            ]

    #input tree dicts:
    treePlus_dict   = {}
    treeMinus_dict  = {}
    weight_dict     = {}

    eosPath = "root://eoslhcb.cern.ch//eos/lhcb/wg/TrackingAlignment/TrackCalib/ToolTuples/"

    #read in trees, MC also reads in data tree with sweights for calculating multiplicity weights
    if data:
        if (WGProduct):
            eosPath = "root://eoslhcb.cern.ch//eos/lhcb/wg/TrackingAlignment/WGP_Oct2017/"
            for i in meth_list:
                treePlus_dict[i] = TChain("Tuple"+i+"Plus/DecayTree")
                treeMinus_dict[i] = TChain("Tuple"+i+"Minus/DecayTree")
                if test:
                    InfoMsg("Input file: " + eosPath + "Data_2016_MagDown/00066675_000000**_1.trkcalib.root for " + i + " method.")
                    treePlus_dict[i].Add(eosPath + "Data_2016_MagDown/00066675_000000*_1.trkcalib.root")
                    treeMinus_dict[i].Add(eosPath + "Data_2016_MagDown/00066675_000000*_1.trkcalib.root")
                    InfoMsg("Input file: " + eosPath + "Data_2016_MagUp/00066676_000000**_1.trkcalib.root for " + i + " method.")
                    treePlus_dict[i].Add(eosPath + "Data_2016_MagUp/00066676_000000*_1.trkcalib.root")
                    treeMinus_dict[i].Add(eosPath + "Data_2016_MagUp/00066676_000000*_1.trkcalib.root")
                else:
                    InfoMsg("Input file: " + eosPath + "Data_2016_MagDown/*.root for " + i + " method.")
                    treePlus_dict[i].Add(eosPath + "Data_2016_MagDown/*.root")
                    treeMinus_dict[i].Add(eosPath + "Data_2016_MagDown/*.root")
                    InfoMsg("Input file: " + eosPath + "Data_2016_MagUp/*.root for " + i + " method.")
                    treePlus_dict[i].Add(eosPath + "Data_2016_MagUp/*.root")
                    treeMinus_dict[i].Add(eosPath + "Data_2016_MagUp/*.root")
        else:
            inputFile = TFile.Open(eosPath+mode+"/"+year+"/Tuple_"+mode+".root","")
            if verbose:
                InfoMsgList("Input file:", eosPath+mode+"/"+year+"/Tuple_"+mode+".root")
    else:
        #inputFile = TFile.Open(eosPath+mode+"/"+year+"/"+simVer+"/old/Tuple_"+mode+".root","")
        inputFile = TFile.Open(eosPath+mode+"/"+year+"/"+simVer+"/Tuple_"+mode+".root","")
        if verbose:
            InfoMsgList( "Input file: ", eosPath+mode+"/"+year+"/"+simVer+"/Tuple_"+mode+".root")
    if not (WGProduct):
        for i in meth_list:
            if verbose:
                InfoMsg("Adding trees " +i+"_plus and" + i+"_minus")
            treePlus_dict[i]    = inputFile.Get("Tuple"+i+"Plus/DecayTree")
            treeMinus_dict[i]   = inputFile.Get("Tuple"+i+"Minus/DecayTree")

    #list of particles
    part_list = ['J_psi_1S','muplus','muminus']

    #check if custom variables are requested, use instead of defaults
    if variables != "":
        var_custom = variables
        var_custom = var_custom.split(',')
        var_list_part += var_custom  #If var_custom is global, no Branch is added (see line 94)
        if verbose: InfoMsgList( "Custom set of variables requested: ", var_custom)


    #set all branches to 0, needed to 1; Purpose is to reduce the tuple size and speed up read-in
    for i in meth_list:
        treePlus_dict[i].SetBranchStatus('*',0)
        treeMinus_dict[i].SetBranchStatus('*',0)
        for part in part_list:
            for part_var in var_list_part:
                treePlus_dict[i].SetBranchStatus(part+"_"+part_var,1)
                treeMinus_dict[i].SetBranchStatus(part+"_"+part_var,1)
        for glob_var in var_list_glob: #If var_custom is global, it needs to be added manually (see line 94)
            treePlus_dict[i].SetBranchStatus(glob_var,1)
            treeMinus_dict[i].SetBranchStatus(glob_var,1)



    ### START OF CUSTOM CUT READ-IN ###

    #define cuts dicts: these are only needed for 2015 data, in 2016 all were moved to the trigger, except totCandidates. Anyway only redundant, so shouldn't hurt
    cuts_plus = {
                'Long'  : "muplus_P > 5000 && muplus_PT > 100 &&  J_psi_1S_ENDVERTEX_CHI2 < 5 && J_psi_1S_IP_OWNPV < 0.8 && J_psi_1S_M < 3600 && J_psi_1S_M > 2600 && muminus_P > 10000 && muminus_PT > 1300 && muminus_TRACK_CHI2NDOF < 2 && totCandidates == 1",
                'T'     : "muplus_P > 5000 && muplus_PT > 500 &&  J_psi_1S_ENDVERTEX_CHI2 < 5 && J_psi_1S_M < 3600 && J_psi_1S_M > 2600 && muminus_P > 7000 && muminus_PT > 500 && muminus_TRACK_CHI2NDOF < 5 && muminus_IP_OWNPV > 0.2 && totCandidates == 1",
                'Velo'  : "muplus_P > 5000 && muplus_PT > 700 &&  J_psi_1S_ENDVERTEX_CHI2 < 5 && J_psi_1S_M < 3300 && J_psi_1S_M > 2900 && muminus_P > 5000 && muminus_PT > 700 && muminus_TRACK_CHI2NDOF < 5 && totCandidates == 1"
            }

    cuts_minus = {
                'Long'  : "muminus_P > 5000 && muminus_PT > 100 &&  J_psi_1S_ENDVERTEX_CHI2 < 5 && J_psi_1S_IP_OWNPV < 0.8 && J_psi_1S_M < 3600 && J_psi_1S_M > 2600 && muplus_P > 10000 && muplus_PT > 1300 && muplus_TRACK_CHI2NDOF < 2 && totCandidates == 1",
                'T'     : "muminus_P > 5000 && muminus_PT > 500 &&  J_psi_1S_ENDVERTEX_CHI2 < 5 && J_psi_1S_M < 3600 && J_psi_1S_M > 2600 && muplus_P > 7000 && muplus_PT > 500 && muplus_TRACK_CHI2NDOF < 5 && muplus_IP_OWNPV > 0.2 && totCandidates == 1",
                'Velo'  : "muminus_P > 5000 && muminus_PT > 700 &&  J_psi_1S_ENDVERTEX_CHI2 < 5 && J_psi_1S_M < 3300 && J_psi_1S_M > 2900 && muplus_P > 5000 && muplus_PT > 700 && muplus_TRACK_CHI2NDOF < 5 && totCandidates == 1"
            }

    #cut dictionary for custom cuts, split by type
    cut_dict = {
            'Tag'       : "",
            'Probe'     : "",
            'Global'    : ""
            }

    #get custom cuts from options, allow tag, probe, and global cuts, separated by semicolon, individual cuts by commata, type and cuts by colon
    #example: '-cuts "Tag:P>5000,ENDVERTEX_CHI2<1;Probe:P>10000;Global:nSPDHits<400" '
    if cuts != "":
        #strip of all spaces
        cuts_custom = cuts.replace(" ","")
        tmpcuts = cuts_custom.split(';')

        #cut_type should be tag, probe or global
        for cut_string in tmpcuts:
            tmp_string = cut_string.split(':')
            cut_type = tmp_string[0]
            try: tmp_list = tmp_string[1].split(',')
            except:
                WarnMsgList("No cut type defined in ", cut_string)
                WarnMsg("Please choose 'Tag','Probe' or 'Global'!")
                continue

            #check if valid cut type given
            if cut_type not in ['Tag','Probe','Global']:
                WarnMsgList("Invalid cut type given: ", cut_type)
                WarnMsg("It will be ignored (must be one of 'Tag', 'Probe', 'Global')!")
                continue

            else:
                cut_dict[cut_type] = tmp_list


        #build cut string out of these cuts, with proper charge assignments

        #first create list with prober cuts
        tag_cuts_plus = [ "muminus_"+cut for cut in cut_dict['Tag'] ] if cut_dict['Tag']!="" else []
        probe_cuts_plus = [ "muplus_"+cut for cut in cut_dict['Probe'] ] if cut_dict['Probe']!="" else []
        global_cuts_plus = cut_dict['Global'] if cut_dict['Global']!="" else []

        #in verbose printout show the cuts used
        if verbose:
            InfoMsgList("Tag cuts requested (plus sample):", tag_cuts_plus)
            InfoMsgList("Probe cuts requested (plus sample):", probe_cuts_plus)
            InfoMsgList("Global cuts requested (plus sample):", global_cuts_plus)

        cuts_list_plus = tag_cuts_plus
        cuts_list_plus += probe_cuts_plus
        cuts_list_plus += global_cuts_plus

        tag_cuts_minus = [ "muplus_"+cut for cut in cut_dict['Tag'] ] if cut_dict['Tag']!="" else []
        probe_cuts_minus = [ "muminus_"+cut for cut in cut_dict['Probe'] ] if cut_dict['Probe']!="" else []
        global_cuts_minus = cut_dict['Global'] if cut_dict['Global']!="" else []

        #in verbose printout show the cuts used
        if verbose:
            InfoMsgList("Tag cuts requested (minus sample):", tag_cuts_minus)
            InfoMsgList( "Probe cuts requested (minus sample):", probe_cuts_minus)
            InfoMsgList( "Global cuts requested (minus sample):", global_cuts_minus)

        cuts_list_minus = tag_cuts_minus
        cuts_list_minus += probe_cuts_minus
        cuts_list_minus += global_cuts_minus

        #put these into strings
        if len(cuts_list_plus) > 0:
            cuts_string_plus = str(cuts_list_plus[0])
            cuts_string_minus = str(cuts_list_minus[0])
            if len(cuts_list_plus) > 1:
                for i in range(len(cuts_list_plus)-1):
                    cuts_string_plus += " && "+str(cuts_list_plus[i+1])
                    cuts_string_minus += " && "+str(cuts_list_minus[i+1])


        if verbose:
            InfoMsgList( "Custom plus cut string used:", cuts_string_plus)
            InfoMsgList( "Custom minus cuts string used:", cuts_string_minus)

        #set new cuts for all three methods
        cuts_plus['Long'] = cuts_string_plus
        cuts_plus['T'] = cuts_string_plus
        cuts_plus['Velo'] = cuts_string_plus

        cuts_minus['Long'] = cuts_string_minus
        cuts_minus['T'] = cuts_string_minus
        cuts_minus['Velo'] = cuts_string_minus

    ### END OF CUSTOM CUT READ-IN ###


    ### START OF MATCHING CRITERIA READ-IN ###

    #cut dictionary for custom cuts, split by type
    crit_dict = {
            'Probe'     : "",
            'Global'    : ""
            }

    #get custom matching reqirements from option, either on probe track or globally
    #example '-matchCrit "Probe:Matched_GhostProb<0.3;Global:nSPDHits<400" '
    if matchCrit != "":
        #strip string of all spaces
        matchCrit = matchCrit.replace(" ","")
        tmpMatch = matchCrit.split(';')

        #criterion should be probe or global
        for crit_string in tmpMatch:
            tmp_crit = crit_string.split(':')
            crit_type = tmp_crit[0]
            try: tmp_list = tmp_crit[1].split(',')
            except:
                WarnMsgList( "No matching criterion type defined in ", crit_string)
                WarnMsg( "Please choose 'Probe' or 'Global'!")
                continue

            #check if valid criterion given
            if crit_type not in ['Probe','Global']:
                WarnMsgList("Invalid matching criterion type given: ", crit_type)
                WarnMsg("It will be ignored (must be one of 'Probe', 'Global')!")
                continue

            else:
                crit_dict[crit_type] = tmp_list

        #put the criteria into a cut string
        probe_crits_plus = [ "muplus_"+crit for crit in crit_dict['Probe'] ] if crit_dict['Probe']!="" else []
        global_crits_plus = crit_dict['Global'] if crit_dict['Global']!="" else []

        matchCritsPlus = ["muplus_Assoc"]
        matchCritsPlus += probe_crits_plus
        matchCritsPlus += global_crits_plus

        probe_crits_minus = [ "muminus_"+crit for crit in crit_dict['Probe'] ] if crit_dict['Probe']!="" else []
        global_crits_minus = crit_dict['Global'] if crit_dict['Global']!="" else []

        matchCritsMinus = ["muminus_Assoc"]
        matchCritsMinus += probe_crits_minus
        matchCritsMinus += global_crits_minus


    else: #no criteria defined, use default matching from trigger
        matchCritsPlus = ["muplus_Assoc"]
        matchCritsMinus = ["muminus_Assoc"]

    if verbose:
        InfoMsgList( "Plus matching criteria used:", matchCritsPlus)
        InfoMsgList( "Minus matching criteria used:", matchCritsMinus)

    ### END OF MATCHING CRITERIA READ-IN ###

    #list of min, max range for some standard weighting wars
    weightRange = {
            "nSPDHits"      :   [0,600],
            "nTracks"       :   [0,500],
            "nLongTracks"   :   [0,100],
            "nVeloTracks"   :   [0,300],
            "nTTracks"      :   [0,500]
            }

    #Declare the variable to hold ETA of the mother particle
    Eta_mother = array('f',[0])
    #Declare the weight variable
    weight = array('f',[0])
    #Declare the matched variable
    matched = array('i',[0])

    #Declare the new tree
    outfile = TFile(outputFileName, "RECREATE")
    outfile.cd()
    if verbose : InfoMsg("Output file " + outputFileName + " created!")

    #dicts for new trees and branches
    newTreePlus_dict = {}
    newTreeMinus_dict = {}
    branch_dict_eta_plus = {}
    branch_dict_eta_minus = {}
    branch_dict_plus = {}
    branch_dict_minus = {}
    branch_match_dict_plus = {}
    branch_match_dict_minus = {}

    #dicts for branches of read-in values
    mult_dict = {}
    match_dict = {}
    #PV and SV points for mother ETA calculation
    PV_X_dict = {}
    PV_Y_dict = {}
    PV_Z_dict = {}
    SV_X_dict = {}
    SV_Y_dict = {}
    SV_Z_dict = {}
    overlapT_dict = {}
    overlapTT_dict = {}
    overlapMuon_dict = {}
    overlapVelo_dict = {}
    if len(matchCritsPlus) > 1:
        extraCrit_dict_plus = {}
        extraCrit_dict_plus_comparitors = {}
        extraCrit_dict_plus_values = {}
        for i in xrange(len(matchCritsPlus)-1):
            #get variable from cut: expect it to be first part of string, separated by comparison operator
            try:
                tmpString = matchCritsPlus[i+1].split(">")[0]
                extraCrit_dict_plus_comparitors[tmpString] = ">"
                extraCrit_dict_plus_values[tmpString] = matchCritsPlus[i+1].split(">")[1] #this will trigger the exception if not the respective comparator
            except:
                try:
                    tmpString = matchCritsPlus[i+1].split("<")[0]
                    extraCrit_dict_plus_comparitors[tmpString] = "<"
                    extraCrit_dict_plus_values[tmpString] = matchCritsPlus[i+1].split("<")[1]
                except:
                    try:
                        tmpString = matchCritsPlus[i+1].split("==")[0]
                        extraCrit_dict_plus_comparitors[tmpString] = "=="
                        extraCrit_dict_plus_values[tmpString] = matchCritsPlus[i+1].split("==")[1]
                    except:
                        WarnMsg("Could not get branch from matching criterion "+matchCritsPlus[i+1]+", skipping!")
                        continue
            extraCrit_dict_plus[tmpString] = {}

    if len(matchCritsMinus) > 1:
        extraCrit_dict_minus = {}
        extraCrit_dict_minus_comparitors = {}
        extraCrit_dict_minus_values = {}
        for i in xrange(len(matchCritsMinus)-1):
            #get variable from cut: expect it to be first part of string, separated by comparison operator
            try:
                tmpString = matchCritsMinus[i+1].split(">")[0]
                extraCrit_dict_minus_comparitors[tmpString] = ">"
                extraCrit_dict_minus_values[tmpString] = matchCritsMinus[i+1].split(">")[1] #this will trigger the exception if not the respective comparator
            except:
                try:
                    tmpString = matchCritsMinus[i+1].split("<")[0]
                    extraCrit_dict_minus_comparitors[tmpString] = "<"
                    extraCrit_dict_minus_values[tmpString] = matchCritsMinus[i+1].split("<")[1]
                except:
                    try:
                        tmpString = matchCritsMinus[i+1].split("==")[0]
                        extraCrit_dict_minus_comparitors[tmpString] = "=="
                        extraCrit_dict_minus_values[tmpString] = matchCritsMinus[i+1].split("==")[1]
                    except:
                        WarnMsg("Could not get branch from matching criterion "+matchCritsMinus[i+1]+", skipping!")
                        continue
            extraCrit_dict_minus[tmpString] = {}


    #additional matching criteria branches

    for i in meth_list:
        if verbose:
            InfoMsgList( "Applying plus cuts for " + i + " method:", cuts_plus[i])
            if treePlus_dict[i].GetEntries() > maxEntries or treeMinus_dict[i].GetEntries() > maxEntries:
                WarnMsg("Large dataset for method " +i +", will only use first "+str(maxEntries/1.e6)+" million entries per charge. Specify runNumber range in cuts option, if dedicated range required!")
        newTreePlus_dict[i]  = treePlus_dict[i].CopyTree(cuts_plus[i],"",long(maxEntries),0)
        if verbose:
            InfoMsgList("Applying minus cuts for " + i + " method:", cuts_minus[i])
        newTreeMinus_dict[i] = treeMinus_dict[i].CopyTree(cuts_minus[i],"",long(maxEntries),0)
        if WGProduct:
            treePlus_dict[i].Reset()
            treeMinus_dict[i].Reset()
        treePlus_dict[i].Delete()
        treeMinus_dict[i].Delete()

        newTreePlus_dict[i].SetName("TrackEffTreePlus"+i)
        newTreeMinus_dict[i].SetName("TrackEffTreeMinus"+i)
        #create new branches
        branch_dict_eta_plus[i]     = newTreePlus_dict[i].Branch('Mother_ETA',Eta_mother,'Mother_ETA/F')
        branch_dict_eta_minus[i]    = newTreeMinus_dict[i].Branch('Mother_ETA',Eta_mother,'Mother_ETA/F')
        branch_dict_plus[i]     = newTreePlus_dict[i].Branch('weight',weight,'weight/F')
        branch_dict_minus[i]    = newTreeMinus_dict[i].Branch('weight',weight,'weight/F')
        branch_match_dict_plus[i]     = newTreePlus_dict[i].Branch('matched',matched,'matched/O')
        branch_match_dict_minus[i]    = newTreeMinus_dict[i].Branch('matched',matched,'matched/O')
        #set variables on PV and SV position branches
        SV_X_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress("J_psi_1S_ENDVERTEX_X",SV_X_dict[i])
        newTreeMinus_dict[i].SetBranchAddress("J_psi_1S_ENDVERTEX_X",SV_X_dict[i])
        SV_Y_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress("J_psi_1S_ENDVERTEX_Y",SV_Y_dict[i])
        newTreeMinus_dict[i].SetBranchAddress("J_psi_1S_ENDVERTEX_Y",SV_Y_dict[i])
        SV_Z_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress("J_psi_1S_ENDVERTEX_Z",SV_Z_dict[i])
        newTreeMinus_dict[i].SetBranchAddress("J_psi_1S_ENDVERTEX_Z",SV_Z_dict[i])
        PV_X_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress("J_psi_1S_OWNPV_X",PV_X_dict[i])
        newTreeMinus_dict[i].SetBranchAddress("J_psi_1S_OWNPV_X",PV_X_dict[i])
        PV_Y_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress("J_psi_1S_OWNPV_Y",PV_Y_dict[i])
        newTreeMinus_dict[i].SetBranchAddress("J_psi_1S_OWNPV_Y",PV_Y_dict[i])
        PV_Z_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress("J_psi_1S_OWNPV_Z",PV_Z_dict[i])
        newTreeMinus_dict[i].SetBranchAddress("J_psi_1S_OWNPV_Z",PV_Z_dict[i])
        #also set variable on multiplicity branch
        mult_dict[i] = array('i',[0])
        newTreePlus_dict[i].SetBranchAddress(weightVar,mult_dict[i])
        newTreeMinus_dict[i].SetBranchAddress(weightVar,mult_dict[i])
        #and the branches for matching criteria
        match_dict[i] = array('i',[0])
        newTreePlus_dict[i].SetBranchAddress('muplus_Assoc',match_dict[i])
        newTreeMinus_dict[i].SetBranchAddress('muminus_Assoc',match_dict[i])
        overlapT_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress('muplus_Overlap_TFraction',overlapT_dict[i])
        newTreeMinus_dict[i].SetBranchAddress('muminus_Overlap_TFraction',overlapT_dict[i])
        overlapTT_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress('muplus_Overlap_TTFraction',overlapTT_dict[i])
        newTreeMinus_dict[i].SetBranchAddress('muminus_Overlap_TTFraction',overlapTT_dict[i])
        overlapMuon_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress('muplus_Overlap_MuonFraction',overlapMuon_dict[i])
        newTreeMinus_dict[i].SetBranchAddress('muminus_Overlap_MuonFraction',overlapMuon_dict[i])
        overlapVelo_dict[i] = array('d',[0])
        newTreePlus_dict[i].SetBranchAddress('muplus_Overlap_VeloFraction',overlapVelo_dict[i])
        newTreeMinus_dict[i].SetBranchAddress('muminus_Overlap_VeloFraction',overlapVelo_dict[i])
        #add extra branches for additional criteria
        if len(matchCritsPlus) > 1:
            for crit in extraCrit_dict_plus.keys():
                extraCrit_dict_plus[crit][i] = array('d',[0])
                newTreePlus_dict[i].SetBranchAddress(crit,extraCrit_dict_plus[crit][i])
        if len(matchCritsMinus) > 1:
            for crit in extraCrit_dict_minus.keys():
                extraCrit_dict_minus[crit][i] = array('d',[0])
                newTreeMinus_dict[i].SetBranchAddress(crit,extraCrit_dict_minus[crit][i])



        if not data:
            data_file_weight    = TFile.Open(eosPath+"Data/"+year+"/Tuple_Data.root","")
            data_file_weight.cd()
            #Read in data tree to get weight, plus tree for each method should be fine
            treeWeight          = data_file_weight.Get("Tuple"+i+"Plus/DecayTree")
            #get weighting histo
            weight_dict[i]      = multiplicityRatio(treeWeight, newTreePlus_dict[i], newTreeMinus_dict[i], weightVar, i, weightRange[weightVar][0], weightRange[weightVar][1] )

        outfile.cd()

    #event loop to determine weight
    for i in meth_list:

        #plus tree loop
        n_events = newTreePlus_dict[i].GetEntries()
        if verbose:
            InfoMsg( "Starting loop over plus tree for " + i + " method, " + str(n_events) + " entries!")
        for event in xrange(n_events):
            newTreePlus_dict[i].GetEntry(event)
            if(event%10000)==0 and verbose:
                InfoMsg( "Processing event "+ str(event) + "/" + str(n_events))

            #calculate mother ETA from direction information
            PV_pos = TVector3(PV_X_dict[i][0],PV_Y_dict[i][0],PV_Z_dict[i][0])
            SV_pos = TVector3(SV_X_dict[i][0],SV_Y_dict[i][0],SV_Z_dict[i][0])
            direction = SV_pos - PV_pos
            Eta_mother[0] = direction.Eta()
            if direction.Z() < 1.:
            #if direction.Z() < 1. or Eta_mother[0] > 2.4:
                Eta_mother[0] = -999

            #set weight to 1 for data / mc without reasonable weight
            weight[0] = 1.0
            if not data and not noWeight:
                weight_bin = weight_dict[i].FindBin(mult_dict[i][0])
                weight_val = weight_dict[i].GetBinContent(weight_bin)
                weight_err = weight_dict[i].GetBinError(weight_bin)
                #only use weight if rel. error < 30%
                if weight_val != 0 and weight_err/weight_val < 0.3 and weight_val < 5.:
                    weight[0] = weight_val

            #check matching criteria
            matched[0] = False
            if match_dict[i][0]: matched[0] = True

            #check overlaps
            if i == "Long":
                if overlapTT_dict[i][0] <= 0. or overlapMuon_dict[i][0] <= 0.: matched[0] = False
            if i == "Velo":
                if overlapTT_dict[i][0] <= 0. or overlapT_dict[i][0] <= 0.: matched[0] = False
            if i == "T":
                if overlapVelo_dict[i][0] <= 0. or overlapMuon_dict[i][0] <= 0.: matched[0] = False

            if len(matchCritsPlus) > 1:
            #check all criteria one after another
                for crit in extraCrit_dict_plus.keys():
                    if extraCrit_dict_plus_comparitors[crit] == ">" and extraCrit_dict_plus[crit][i][0] <= float(extraCrit_dict_plus_values[crit]): matched[0] = False
                    elif extraCrit_dict_plus_comparitors[crit] == "<" and extraCrit_dict_plus[crit][i][0] >= float(extraCrit_dict_plus_values[crit]): matched[0] = False
                    elif extraCrit_dict_plus_comparitors[crit] == "==" and extraCrit_dict_plus[crit][i][0] != float(extraCrit_dict_plus_values[crit]): matched[0] = False


            #fill branch
            branch_dict_eta_plus[i].Fill()
            branch_dict_plus[i].Fill()
            branch_match_dict_plus[i].Fill()

        #write new tree
        newTreePlus_dict[i].Write("",TObject.kOverwrite)


        #minus tree loop
        n_events = newTreeMinus_dict[i].GetEntries()
        if verbose:
            InfoMsg( "Starting loop over minus tree for " + i + " method, " + str(n_events) + " entries!")
        for event in xrange(n_events):
            newTreeMinus_dict[i].GetEntry(event)
            if(event%10000)==0 and verbose:
                InfoMsg( "Processing event "+ str(event) + "/" + str(n_events))

            #calculate mother ETA from direction information
            PV_pos = TVector3(PV_X_dict[i][0],PV_Y_dict[i][0],PV_Z_dict[i][0])
            SV_pos = TVector3(SV_X_dict[i][0],SV_Y_dict[i][0],SV_Z_dict[i][0])
            direction = SV_pos - PV_pos
            Eta_mother[0] = direction.Eta()
            if direction.Z() < 1.:
            #if direction.Z() < 1. or Eta_mother[0] > 2.4:
                Eta_mother[0] = -999

            #set weight to 1 for data / mc without reasonable weight
            weight[0] = 1.0
            if not data and not noWeight:
                weight_bin = weight_dict[i].FindBin(mult_dict[i][0])
                weight_val = weight_dict[i].GetBinContent(weight_bin)
                weight_err = weight_dict[i].GetBinError(weight_bin)
                #only use weight if rel. error < 30%
                if weight_val != 0 and weight_err/weight_val < 0.3 and weight_val < 5.:
                    weight[0] = weight_val

            #check matching criteria
            matched[0] = False
            if match_dict[i][0]: matched[0] = True

            #check overlaps
            if i == "Long":
                if overlapTT_dict[i][0] <= 0. or overlapMuon_dict[i][0] <= 0.: matched[0] = False
            if i == "Velo":
                if overlapTT_dict[i][0] <= 0. or overlapT_dict[i][0] <= 0.: matched[0] = False
            if i == "T":
                if overlapVelo_dict[i][0] <= 0. or overlapMuon_dict[i][0] <= 0.: matched[0] = False

            if len(matchCritsMinus) > 1:
            #check all criteria one after another
                for crit in extraCrit_dict_minus.keys():
                    if extraCrit_dict_minus_comparitors[crit] == ">" and extraCrit_dict_minus[crit][i][0] <= float(extraCrit_dict_minus_values[crit]): matched[0] = False
                    elif extraCrit_dict_minus_comparitors[crit] == "<" and extraCrit_dict_minus[crit][i][0] >= float(extraCrit_dict_minus_values[crit]): matched[0] = False
                    elif extraCrit_dict_minus_comparitors[crit] == "==" and extraCrit_dict_minus[crit][i][0] != float(extraCrit_dict_minus_values[crit]): matched[0] = False


            #fill branch
            branch_dict_eta_minus[i].Fill()
            branch_dict_minus[i].Fill()
            branch_match_dict_minus[i].Fill()

        #write new tree
        newTreeMinus_dict[i].Write("",TObject.kOverwrite)

    #write output file
    outfile.Write("",TObject.kOverwrite)
    outfile.Close()
    InfoMsg("Preparation finished.")
