##########################################
# The Combined fit with different combined
# variables
##########################################

from combine import *
print ' ====================== '
print ' Choose the fit:'

print ' ====================== '

#which = 'original_offset'
#which = 'original_NOoffset'
#offset = 0

#which = 'fit_ratio'
#offset = 1

which = 'fit_ratio_noOff'


nCPU = 8
fit = 0
canv = 0

# Original combined fit (to compare the yields and parameters against)
if which is 'original_offset':
    offset = True
    fit = Combination('Combined_CMS_poly',False)
    fit.fitLHCb()
    fit.importLHCb(fixBRs = False, fixBRd = False, fitRatio = False)
    fit.fitCMS()
    fit.importCMS_combined(change2MeV=False)
    fit.buildCombModel()
    fit.combineData()
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    fit.combName = 'Combined_CMS_poly_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    fit.getBRRatio() #Take those from the ws.Print('v')

# Original combined fit (to compare the yields and parameters against)
if which is 'original_NOoffset':
    offset = False
    fit = Combination('Combined_CMS_poly_NOoffset',False)
    fit.fitLHCb()
    fit.importLHCb(fixBRs = False, fixBRd = False, fitRatio = False)
    fit.fitCMS()
    fit.importCMS_combined(change2MeV=False)
    fit.buildCombModel()
    fit.combineData()

    fit.combName = 'Combined_noOffset_OldMinuitMinimize'
    fit.fitCombinedModel(offset,nCPU, reFit = False)

    #fit.combName = 'Combined_noOffset_Minuit2Minimize'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

    #fit.combName = 'Combined_noOffset_Minuit2'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_noOffset_Minuit2_2'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

    #fit.combName = 'Combined_noOffset_MinuitMigrad'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

#    fit.combName = 'Combined_CMS_poly_NOoffset_fit2'
#    fit.fitCombinedModel(offset,nCPU, reFit = False)
#    fit.getBRRatio() #Take those from the ws.Print('v')
#    fit.plotComb()

# Fit the ratio by removing the normalization and fitting only the yields. Then later combine the yields and fsfd to a BR ratio
if which is 'fit_ratio':
    fit = Combination('Combined_Ratio',False)
    #fit = Combination('Combined_Unnormalised',False)
    fit.fitLHCb()

    #Fit ratio prepates the workspace for fitting only the BRsOverBRd and not BRs and BRd separately
    fit.importLHCb(fixBRs = False, fixBRd = False, fitRatio = True)
    fit.fitCMS()
    fit.importCMS_fitRatio() #Import CMS with yields unnormalised
    fit.buildCombModel()
    fit.combineData()
    fit.fitCombinedModel(offset,nCPU, reFit = False, fitRatio = True)

    fit.combName = 'Combined_Ratio_2'
    fit.fitCombinedModel(offset,nCPU, reFit = False)

   # fit.combName = 'Combined_Ratio_3'
   # fit.fitCombinedModel(offset,nCPU, reFit = False)


#    #Combined mass, signal combined for LHCb and CMS, All bins
#    fit.plotComb()
   # fit.getBRRatio() #Take those from the ws.Print('v')

if which is 'fit_ratio_noOff':

    offset = 0
    fit = Combination('Combined_RatioNoOffset',False)
    #fit = Combination('Combined_Unnormalised',False)
    fit.fitLHCb()

    #Fit ratio prepates the workspace for fitting only the BRsOverBRd and not BRs and BRd separately
    fit.importLHCb(fixBRs = False, fixBRd = False, fitRatio = True)
    fit.fitCMS()
    fit.importCMS_fitRatio() #Import CMS with yields unnormalised
    fit.buildCombModel()
    fit.combineData()

    #fit.combName = 'Combined_RatioNoOffset_Minuit2Migrad'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

    #fit.combName = 'Combined_RatioNoOffset_Minuit2Migrad'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_RatioNoOffset_Minuit2Migrad_fit2'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_RatioNoOffset_Minuit2Migrad_fit3'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

    #fit.combName = 'Combined_RatioNoOffset_Minuit2Minimize'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_RatioNoOffset_Minuit2Minimize_fit2'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_RatioNoOffset_Minuit2Minimize_fit3'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_RatioNoOffset_Minuit2Minimize_fit4'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

    #fit.combName = 'Combined_RatioNoOffset_Minuit2Scan'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_RatioNoOffset_Minuit2Scan_fit2'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_RatioNoOffset_Minuit2Scan_fit3'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)


    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'Combined_RatioNoOffset_Minuit2Migrad_Mix'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)


    #fit.fitCombinedModel(offset,nCPU, reFit = False, fitRatio = True)
    #fit.combName = 'Combined_RatioNoOffset_2'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.plotComb()

