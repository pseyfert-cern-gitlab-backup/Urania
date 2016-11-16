##########################################
# The Combined fit with different combined
# variables
##########################################

from combine import *
print ' ====================== '
print ' Choose the fit:'

print ' ====================== '
#which = raw_input('Which fit? Enter nr: ')
#which = 'CMS_poly'

#Test the exponentials
#which = 'CMS_expo'
#which = 'CMS_expo_fixBs'
#which = 'CMS_expo_fixBd'
#which = '1_exp'
which = '1'
#which = 'Jack_EXP'
#which = '2'
#which = 'LHCb_fixBs'
#which = 'LHCb_fixBd'
#which = 'LHCb_fixBd_CombWS'

offset = 1
nCPU = 8
fit = 0
canv = 0




if which is '1':
    print ' o) Fitting CMS only '
    fit = Combination('CMSonly',False)
    fit.fitCMS(reFit = False)

    canv1 = fit.plot2DContour(fit.cms_fitRes,'BF_bs','BF_bd')

if which is '1_exp':
    print ' o) Fitting CMS only '
    fit = Combination('CMSonly_exp',False)
    fit.readCMS_exp('ws_revised_20140327_realvarnuisance.root')
    fit.fitCMS()
    canv = fit.plotCMS()


if which is 'Jack_EXP': #The CMS WS with exponents, gotten from Jack
    print ' o) Fitting CMS only, the proper EXPO shapes from CMS'
    fit = Combination('CMS_Only_JackEXP',False)
    fit.readCMS('ws_revised_20140504_expcomb.root')
    fit.fitCMS()
    canv = fit.plotCMS()

if which is 'CMS_poly':
    fit = Combination('Combined_CMS_poly',False)
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()
    #fit.prepareCombWorkspace()
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    fit.combName = 'Combined_CMS_poly_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'SharedChangedC_fit3'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

    #Save the workspace
    fit.saveCombWorkspace()
    canv1 = fit.plot2DContour()

    #Mass plot in bins
    #canv2 = fit.plotComb()


if which is 'CMS_expo':
    fit = Combination('Combined_CMS_expo',False)
    fit.fitLHCb()
    fit.importLHCb()
    fit.readCMS_exp('ws_revised_20140327_realvarnuisance.root')
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()
    #fit.prepareCombWorkspace()
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    fit.combName = 'Combined_CMS_expo_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'SharedChangedC_fit3'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)
    #Save the workspace
    fit.saveCombWorkspace()
    canv = fit.plotComb()

if which is 'CMS_expo_fixBd':
    fit = Combination('Combined_CMS_expo_fixBd',False)
    fit.fitLHCb()
    fit.importLHCb()
    fit.readCMS_exp('ws_revised_20140327_realvarnuisance.root')
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()
    #fit.prepareCombWorkspace()
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = False, fixBd = True)
    fit.combName = 'Combined_CMS_expo_fixBd_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = False, fixBd = True)
    fit.saveCombWorkspace()
    canv = fit.plotComb()

if which is 'CMS_expo_fixBs':
    fit = Combination('Combined_CMS_expo_fixBs',False)
    fit.fitLHCb()
    fit.importLHCb()
    fit.readCMS_exp('ws_revised_20140327_realvarnuisance.root')
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()
    #fit.prepareCombWorkspace()
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = True, fixBd = False)
    fit.combName = 'Combined_CMS_expo_fixBd_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = True, fixBd = False)
    fit.saveCombWorkspace()
    canv = fit.plotComb()


if which is '2':
    print ' o) Fitting LHCb only '
    fit = Combination('LHCbonly',False)
    fit.fitLHCb()
    canv = fit.plotLHCb()

if which is 'LHCb_fixBs':
    fit = Combination('LHCb_fixBs',False)
    fit.fitLHCbCustom(offset,  nCPU, fixBs = True, fixBd = False)
    canv = fit.plotLHCb()

if which is 'LHCb_fixBd':
    fit = Combination('LHCb_fixBd',False)
    fit.fitLHCbCustom(offset,  nCPU, fixBs = False, fixBd = True)
    canv = fit.plotLHCb()

#This is not easily done right now. But would be needed for fitting twice
#if which is 'LHCb_fixBd_CombWS':
#    fit = Combination('LHCb_fixBd_fitInComb',False)
#    fit.fitLHCb()
#    fit.importLHCb()
#    fit.importCMS_combined()
#    fit.buildCombModel()
#    fit.combineData()
#    fit.fitCombinedModeltoLHCb(offset,  nCPU, reFit = False, fixBd = True, fixBs = False)
#    #fit.fitCombinedModel(offset, nCPU, reFit = False, fixBs = False, fixBd = True, BsZero =True)
#    canv = fit.plotComb()

if which is '3':
    fit = Combination('Combined_20140403',False)
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()
    #fit.prepareCombWorkspace()
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    fit.combName = 'Combined_20140403_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False)
    #fit.combName = 'SharedChangedC_fit3'
    #fit.fitCombinedModel(offset,nCPU, reFit = False)

    #Save the workspace
    fit.saveCombWorkspace()

if which is '4':
    fit = Combination('Combined_20140403_fixBRd',False) #fix BRd
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()
    #fit.prepareCombWorkspace()
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = False, fixBd = True)
    fit.combName = 'Combined_20140403_fixBRd_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = False, fixBd = True)
    #Save the workspace
    fit.saveCombWorkspace()


if which is '5':
    fit = Combination('Combined_20140403_fixBRs',False) #fix BRs
    fit.fitLHCb()
    fit.importLHCb()
    fit.fitCMS()
    fit.importCMS_combined()
    fit.buildCombModel()
    fit.combineData()
    #fit.prepareCombWorkspace()
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = True, fixBd = False)
    fit.combName = 'Combined_20140403_fixBRs_fit2'
    fit.fitCombinedModel(offset,nCPU, reFit = False, fixBs = True, fixBd = False)
    #Save the workspace
    fit.saveCombWorkspace()



