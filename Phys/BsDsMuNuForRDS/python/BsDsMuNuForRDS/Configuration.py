################################################################################
## Module to hold all the configuration information for each particular
## data type. This includes the information for data retrieval, selections
## to be employed, truth matching for MC, etc.
################################################################################
# First some objects which we can reuse.
# These are the locations of the tuples in each file to be processed.
tupleListStandard = [ 'B2DsMuNuTuple/DecayTree' ,'B2DsMuNuSSTuple/DecayTree'
                      ,'B2DsMuNuTupleFake/DecayTree', 'B2DsMuNuSSTupleFake/DecayTree' ]
tupleListNoFake   = [ 'MB2DsMuNuTuple/DecayTree'
                      ,'B2DsMuNuTuple/DecayTree'
                      ,'B2DsMuNuSSTuple/DecayTree' ]
tupleListFakeOnly = [ 'B2DsMuNuTupleFake/DecayTree', 'B2DsMuNuSSTupleFake/DecayTree' ] 

################################################################################
# For each dataTag we have a configuration dictionary.
# In my experience it's better to be explicit about the configuration,
# so we have several mandatory entries to be filled out.
################################################################################
configurationDict = {}

# The signal mu+tau MC as example to describe the required fields.
configurationDict['MC09_Mu'] = {
    # The tuple locations resident in the file.
    'tNames'      : tupleListStandard 
    # The list of input, non-processed files.
    ,'inputFiles' : [ 'TupleRDS_MCSignal_MCPhotonInfo.root' ]
    # The name of the single output file.
    ,'outputFile' : 'MC09_DsMuNu.root'
    # One of either 'signal' or 'doubleCharm' if we want MC matching.
    ,'truthMatch' : 'signal'
    # Optional entry for when the input file is residing in
    # another location, and not the shared repository.
    ,'inputDir'   : '/eos/lhcb/user/r/rvazquez/RDS/'
    }

configurationDict['MC09_Tau'] = { 'tNames'      : tupleListStandard
                                  ,'inputFiles' : [ 'MC09_DsTauNu_MagUp.root', 'MC09_DsTauNu_MagDown.root']
                                  ,'outputFile' : 'MC09_DsTauNu.root'
                                  ,'truthMatch' : 'signal'
                                  ,'inputDir'   : '/eos/lhcb/user/r/rvazquez/RDS/'
                                  }

# Now add the data tags.
# This is the data for the RDs primary analysis.
configurationDict['Data15'] = { 'tNames'      : tupleListStandard
                                ,'inputFiles' : ['TupleRDS_DataUp_1_allNeutrals_iso.root'
                                                 ,'TupleRDS_DataUp_2_allNeutrals_iso.root'
                                                 ,'TupleRDS_DataDown_1_allNeutrals_iso.root'
                                                 ,'TupleRDS_DataDown_2_allNeutrals_iso.root']
                                ,'outputFile' : 'Data15_RDs.root'
                                ,'inputDir'   : '/eos/lhcb/user/r/rvazquez/RDS/'
                                }

# The dataset for the Ds*mu/Ds*pi branching ratio analysis.
configurationDict['Data15_BR'] = { 'tNames'      : tupleListFakeOnly
                                   ,'inputFiles' : ['TupleRDS_DataUp_1_allNeutrals_iso.root'
                                                    ,'TupleRDS_DataUp_2_allNeutrals_iso.root'
                                                    ,'TupleRDS_DataDown_1_allNeutrals_iso.root'
                                                    ,'TupleRDS_DataDown_2_allNeutrals_iso.root']
                                   ,'outputFile' : 'Data15_BR.root'
                                   ,'inputDir'   : '/eos/lhcb/user/r/rvazquez/RDS/'
                                   }

# The MC08 double charm are all the same except for one string, so loop over these.
for doubleCharmTag in ['LbLcDs', 'BdDstDs', 'BsDsDs', 'BuD0Ds']:
    theDict = { 'tNames'      : tupleListNoFake
                ,'inputFiles' : [ 'TupleRDS_%s_Up_iso.root' %doubleCharmTag
                                  ,'TupleRDS_%s_Down_iso.root' %doubleCharmTag ]
                ,'outputFile' : 'MC08_%s.root' %doubleCharmTag
                ,'truthMatch' : 'doubleCharm'
                ,'inputDir'   : '/eos/lhcb/user/r/rvazquez/RDS/'
                }
    configurationDict['MC08_%s' %doubleCharmTag] = theDict

################################################################################
# Dump the information if the module is run directly.
################################################################################
if __name__=='__main__':
    print '- Dumping configuration settings.'
    for tag, configDict in configurationDict.iteritems():
        print '*'*20
        print '- For tag %s:' %tag
        for setting, value in configDict.iteritems():
            print '-- {:20s}'.format(setting), value
        
