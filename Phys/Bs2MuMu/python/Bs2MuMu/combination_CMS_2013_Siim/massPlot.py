##############################
# Credits                   #
# Author: Siim Tolk         #
# Date: Autumn 2014         #
# Mail: siim.tolk@cern.ch   #
#############################

#########################################
# The Combined fit with different combined
# variables
##########################################

from combine import *
print ' ====================== '
print ' Choose the fit:'

print ' ====================== '

#which = 'Jack_EXP'
#which = 'exp'
#which = '0'

which = '1'  #for top 6 bins and S/S+B weighted plot
#which = 'nullHyp'  #for top 6 bins and Null hypo
#which = '2' #for all the bins

offset = 1
nCPU = 8
fit = 0
canv = 0

if which is 'Jack_EXP': #The CMS WS with exponents, gotten from Jack
    print ' o) Fitting CMS only, the proper EXPO shapes from CMS'
    fit = Combination('CMS_Only_JackEXP',False)
    fit.readCMS('ws_revised_20140504_expcomb.root')
    fit.fitCMS()
    #canv = fit.plotCMS()
    fit.plotCMSMassInOneBin(binNr=8, bins = 50,change2MeV = False, sigFillStyle = 1001, bkgFillStyle = 3003, CMSonlyWS = True)

#Plot the separate LHCb and CMS mass plots in best bins
if which is 'exp':
    fit = Combination('Combined_CMS_expo',False)
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    fit.combName = 'Combined_CMS_expo_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False)

    #massBsCMS = fit.getCMSMassMean(ch='bs', suf = '_CMS')
    #massBdCMS = fit.getCMSMassMean(ch='bd', suf = '_CMS')

    #c1 = fit.plotLHCbMassBestBins(bins = 25,rangeMax = 6000, sigFillStyle = 1001, bkgFillStyle = 3003)
    #c2 = fit.plotCMSMassBestBins(bins = 25,change2MeV = False, sigFillStyle = 1001, bkgFillStyle = 3003)

    fit.plotCMSMassInOneBin(binNr=8, bins = 50,change2MeV = False, sigFillStyle = 1001, bkgFillStyle = 3003)


#Plot the separate LHCb and CMS mass plots in best bins
if which is 'nullHyp':
    fit = Combination('Combined_CMS_poly',False)
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()

    #Plot the top 6 bins with bkg for the null hyp
    fit.combName = 'Combined_CMS_poly_NullHypo'
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = 1, fixBd = 1)
    canv4 = fit.plotCombinedMassBestBins(bins = 25,separateSignal=False,rangeMax = 5900,sepBkg=True, noSignal = True)

    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_CMS_poly_fit2'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

    #massBsCMS = fit.getCMSMassMean(ch='bs', suf = '_CMS')
    #massBdCMS = fit.getCMSMassMean(ch='bd', suf = '_CMS')

    #c1 = fit.plotLHCbMassBestBins(bins = 25,rangeMax = 6000, sigFillStyle = 1001, bkgFillStyle = 3003)
    #c2 = fit.plotCMSMassBestBins(bins = 25,change2MeV = False, sigFillStyle = 1001, bkgFillStyle = 3003)

    #fit.plotCMSMassInOneBin(binNr=8, bins = 50,change2MeV = False, sigFillStyle = 1001, bkgFillStyle = 3003, CMSonlyWS = False)
    #fit.plotCMSMassInOneBin(binNr=8, bins = 50,change2MeV = False, sigFillStyle = 1001, bkgFillStyle = 3003, CMSonlyWS = True)

#Plot the mass plots on one scale, MeV
#LHCb, CMS, and combined
if which is '1':
    print ' o) Same mass scale'
    fit = Combination('Combined_MeV')
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined(change2MeV=True)
    fit.buildCombModel()
    fit.combineData()

    #Reading in the fit parameters from the Separate independent mass fit.
    #The different mass range does not permit to perform a combined fit on the same mass variable
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = False, fixBd = False)

    #Combined mass, signal combined for LHCb and CMS, All bins together
    #canv3 = fit.plotCombinedMassAllBins(bins = 25)

    #Combined mass, signal combined for LHCb and CMS, best bins
    # Plot best 6 bins
    #canv4 = fit.plotCombinedMassBestBins(bins = 25,separateSignal=False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003, fcErr = True)
    canv4 = fit.plotCombinedMassBestBins(bins = 25,separateSignal=False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003, fcErr = True, noXErr = True, sepBkg = True)

    #Beautified!
    #canv4 = fit.plotCombinedMassBestBins(bins = 25,separateSignal=False,rangeMax = 5900)
    #canv4 = fit.plotCombinedMassBestBins(bins = 25,separateSignal=False,rangeMax = 5900,sepBkg=True)


    # Plot best 8 bins
    #canv42 = fit.plotCombinedMassBestBins8(bins = 25,separateSignal=False,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003)

    #Combined mass, signal separate for LHCb and CMS, 6 best biins
    #canv5 = fit.plotCombinedMassBestBins(bins = 25,separateSignal=True,rangeMax = 5900, sigFillStyle = 1001, bkgFillStyle = 3003)

    #LHCb mass plot in common range
    #canv6 = fit.plotLHCbMassBestBins( bins = 25, rangeMax = 6000, sigFillStyle = 1001, bkgFillStyle = 3003)
    #CMS mass plot in common range, MeV
    #canv7 = fit.plotCMSMassBestBins( bins = 25, change2MeV = True, sigFillStyle = 1001, bkgFillStyle = 3003)

    #c = fit.plotCMSMassInOneBin(binNr=8, bins = 50,change2MeV = True, sigFillStyle = 1001, bkgFillStyle = 3003, CMSonlyWS=False)

    #Plot the weights per bins mass plot
    #fit.getSBweights()
    #fit.plotBinWeights(fit.rawSBWeights,1,'rawWeights')
    #fit.plotBinWeights(fit.normWeights,0.15,'normalized')

    #Plot mass fit in ALL categories separately
    #No go...:(( bin 12 norm. is off with MeV scale
    #canv1 = fit.plotComb(separateLHCbSemiLep=False ,cmsInMeV = True, lhcbMax = 6000, sigFillStyle = 1001, bkgFillStyle = 3003, printWeights = False, separateLHCbbkg = False, separateCMSbkg=False, linew = 1)

    #cW1 = fit.plotWeightedMass(bins = 25, separateSignal = False,rangeMax = 5900, fcErr = True) #ok!
    #cW1 = fit.plotWeightedMass(bins = 25, separateSignal = False,rangeMax = 5900, SMexpected = True) #the signal pdf BR at SM values
    #cW1 = fit.plotWeightedMass(bins = 25, separateBkg = True, separateSignal = False,rangeMax = 5900, SMexpected = True) #the signal pdf BR at SM values
    #cW1 = fit.plotWeightedMass(bins = 25, separateBkg = True, separateSignal = False,rangeMax = 5900, SMexpected = False) #the signal pdf BR at SM values


if which is '2':
    print ' o) CMS in GeV'
    fit = Combination('Combined_MeV')
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined(change2MeV=False)
    fit.buildCombModel()
    fit.combineData()

    #Reading in the fit parameters from the Separate independent mass fit.
    #I think the different mass range does not permit to perform a combined fit on the same mass variable
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = False, fixBd = False)

    #Plot all the bins
    #canv1 = fit.plotComb(separateLHCbSemiLep=False ,cmsInMeV = False)
    #canv1 = fit.plotComb(separateLHCbbkg=True,separateCMSbkg=True,cmsInMeV = False)
    #canv1 = fit.plotComb(separateLHCbbkg=True,separateCMSbkg=True,cmsInMeV = False, addLegend = False)
    canv1 = fit.plotComb(separateLHCbbkg=True,separateCMSbkg=True,cmsInMeV = False, addLegend = False, lowerYmax = True, addLegBinOne = True, fcErr = True)
    #canv1 = fit.plotComb(separateLHCbbkg=True,separateCMSbkg=True,cmsInMeV = False, addLegend = False, lowerYmax = True, addLegBinOne = True, fcErr = False)


    #Plot all the LHCb bins, and components
    #canv2 = fit.plotComb(separateLHCbbkg = True,separateLHCbSemiLep=True ,cmsInMeV = False, onlyLHCb = True)

    #Plot all the CMS bins, and components
    #canv2 = fit.plotComb(separateCMSbkg = True,cmsInMeV = False, onlyCMS = True)

    #Plot a simple lego plot with LHCb and CMS data, summed over all or best bins
    #canv2 = fit.plotStackPlot(bins=50,cmsInMeV=False)

#    fit.combName = 'Combined_MeV_fit2'
#    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = False, fixBd = False)
#
#    fit.saveCombWorkspace()
#    canv = fit.plotComb()

if which is '3':
    print ' o) Same mass scale and refitted' #WRONG! the zero events in 5.9-6.0 will skew the CMS pdf!
    fit = Combination('Combined_MeV')
    #fit = Combination('Combined_MeV2') #Fitted with the comb model.
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined(change2MeV=True)
    fit.buildCombModel()
    fit.combineData()

    #Reading in the fit parameters from the Separate independent mass fit.
    #I think the different mass range does not permit to perform a combined fit on the same mass variable
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = False, fixBd = False)

    canv1 = fit.plotComb(separateLHCbSemiLep=False ,cmsInMeV = True)

    #Plot a simple lego plot with LHCb and CMS data, summed over all or best bins
    canv2 = fit.plotStackPlot(bins=50,cmsInMeV=True)


