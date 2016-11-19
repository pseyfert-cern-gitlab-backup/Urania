######################################################################
## Script to make all the Ds background veto histograms.
######################################################################
from ROOT import *
from HistPlotters import *
from BsDsMuNuForRDS.DataRetrieval import *
gROOT.SetBatch()
gROOT.ProcessLine('.x ~/lhcbStyle.C')
######################################################################
## Some constants.
######################################################################
M_Dp    = 1869.57
M_Ds    = 1968.30
M_Lc    = 2286.46
M_Kstar = 891.66
M_Jpsi  = 3096.916
M_psi2S = 3686.109
M_psi3770 = 3773.15

######################################################################
## Some options.
######################################################################
numBins = 80
dataType = "data"
polarity = "up"

dataTag = 'RDS_FromTauMu'
polarity = 'MagUp'

######################################################################
## Some dictionaries for the loop.
######################################################################
# One for the resonance index integer.
resFlagDict = { 'phi'    : 0,
                'KStar'  : 1,
                'NonRes' : 2 }

# One for the ranges of the mass windows.
massWindowDict = {

    'Lc_SSKasproton' : (M_Lc - 80.0, M_Lc + 80.0)
    ,'Dp_SSKaspi'    : (M_Dp - 200.0, M_Dp + 130.0)

    ,'Dst_FullReco'     : (0.0, 1200.0)
    ,'Dst_SSKaspi_fromDz'  : (0.0, 1200.0)
    ,'Dst_SSKaspi_fromDst' : (0.0, 1200.0)
    
    ,'Jpsi_piasmu'   : (M_Jpsi - 150.0, M_Jpsi + 150.0)
    ,'Jpsi_SSKasmu'  : (M_Jpsi - 150.0, M_Jpsi + 150.0)

    #    ,'psi2S_pipasmup' : (M_psi2S - 150, M_psi2S + 150)
    #    ,'psi2S_Kpasmup'  : (M_psi2S - 150, M_psi2S + 150)
    
    #    ,'psi3370_pipasmup'    : (M_psi3770 - 150, M_psi3770 + 150)
    #    ,'psi3370_Kpasmup'     : (M_psi3770 - 150, M_psi3770 + 150)
    
    ,'phi_piasK'           : [800, 2100]
    ,'KS_OSKaspi'          : [200, 1600]

    ,'Kstar_SSKaspi'       : [500, 1800]
    ,'Kstar_OSKaspi'       : [500, 1800]
    
    }

# One for the global vetoes for each resonance.
globalVetoes = {
    'phi'     : '(1)' #(Kp_ProbNNK > 0.15)'
    ,'KStar'  : '(SSK_ProbNNk > 0.25 && OSK_ProbNNk > 0.25)'# && pip_PIDK < 8)'
    ,'NonRes' : '(SSK_ProbNNk > 0.3 && OSK_ProbNNk > 0.3 && pi_PIDK < 8)'
    }

branchDict = {

    'Lc_SSKasproton'  : 'WM_Lc_SSKasproton'
    ,'Dp_SSKaspi'     : 'WM_Dp_SSKaspi'

    ,'Dst_FullReco' : 'WM_Dst_FullReco'
    ,'Dst_SSKaspi_fromDz'  : 'WM_Dst_SSKaspi_fromDz'
    ,'Dst_SSKaspi_fromDst' : 'WM_Dst_SSKaspi_fromDst'

    ,'Jpsi_piasmu'         : 'WM_Jpsi_piasmu'
    ,'Jpsi_SSKasmu'        : 'WM_Jpsi_SSKasmu'
    
    #   ,'psi2S_pipasmup'      : 'WM_Jpsi_pipasmup'
    #   ,'psi2S_Kpasmup'       : 'WM_Jpsi_Kpasmup'
    
    #   ,'psi3370_pipasmup'    : 'WM_Jpsi_pipasmup'
    #   ,'psi3370_Kpasmup'     : 'WM_Jpsi_Kpasmup'
    
    ,'phi_piasK'           : 'WM_phi_piasK'
    ,'KS_OSKaspi'          : "WM_KS_OSKaspi"

    ,'Kstar_SSKaspi'       : "WM_Kstar_SSKaspi"
    ,'Kstar_OSKaspi'       : "WM_Kstar_OSKaspi"
    
    }

# One for the vetoes.
vetoDict = {

    'phi'    : {  'Lc_SSKasproton'        : '(TMath::Abs(%f - %s) > 33 || (SSK_PIDK - SSK_PIDp) > 7)' %(M_Lc, branchDict['Lc_SSKasproton'])
                  ,'Dp_SSKaspi'          : '1' #'(TMath::Abs(%f - WM_Dp_Kpaspip) > 30 || Kp_PIDK > 8)' %M_Dp
                  
                  ,'Dst_FullReco'        : '(%s > 190)' %branchDict['Dst_FullReco']
                  ,'Dst_SSKaspi_fromDz'  : '(%s > 190)' %branchDict['Dst_SSKaspi_fromDz']
                  ,'Dst_SSKaspi_fromDst' : '(%s > 190)' %branchDict['Dst_SSKaspi_fromDst']
                  
                  ,'Jpsi_piasmu'    : '(TMath::Abs(%f - %s) > 50.0 || pi_isMuon==0)' %(M_Jpsi, branchDict['Jpsi_piasmu'])
                  ,'Jpsi_SSKasmu'   : '(TMath::Abs(%f - %s) > 50.0  || SSK_isMuon==0)' %(M_Jpsi, branchDict['Jpsi_SSKasmu'])

                  #,'psi2S_pipasmup' : '1'
                  #,'psi2S_Kpasmup'  : '1'

                  #,'psi3370_pipasmup' : '1'
                  #,'psi3370_Kpasmup'  : '1'

                  #,'phi_piasK'           : '1'
                  #,'KS_OSKaspi'          : '1'

                  #,'Kstar_SSKaspi'       : '1'
                  #,'Kstar_OSKaspi'       : '1'
                 }

    ,'KStar'  : {  'Lc_SSKasproton'     : '(TMath::Abs(%f - %s) > 33 || (SSK_PIDK - SSK_PIDp) > 10)' %(M_Lc, branchDict['Lc_SSKasproton'])
                   ,'Dp_SSKaspi'        : '((TMath::Abs(%f - %s) > 30 && TMath::Abs(%f - %s) > 30 ) || SSK_PIDK > 8) ' %(M_Dp, branchDict['Dp_SSKaspi'], M_Ds, branchDict['Dp_SSKaspi'])

                   ,'Dst_FullReco'        : '(%s > 190)' %branchDict['Dst_FullReco']
                   ,'Dst_SSKaspi_fromDz'  : '(%s > 190)' %branchDict['Dst_SSKaspi_fromDz']
                   ,'Dst_SSKaspi_fromDst' : '(%s > 190)' %branchDict['Dst_SSKaspi_fromDst']

                   ,'Jpsi_piasmu'    : '(TMath::Abs(%f - %s) > 50.0 || pi_isMuon==0)' %(M_Jpsi, branchDict['Jpsi_piasmu'])
                   ,'Jpsi_SSKasmu'   : '(TMath::Abs(%f - %s) > 50.0  || SSK_isMuon==0)' %(M_Jpsi, branchDict['Jpsi_SSKasmu'])
                   
                   #,'psi2S_pipasmup' : '1'
                   #,'psi2S_Kpasmup'  : '1'

                   #,'phi_piasK'           : '1'
                   #,'KS_OSKaspi'          : '1'
                   
                   #,'Kstar_SSKaspi'       : '1'
                   #,'Kstar_OSKaspi'       : '1'

                   }
    
    ,'NonRes' : {  'Lc_SSKasproton'   : '(TMath::Abs(%f - %s) > 33 || (SSK_PIDK - SSK_PIDp) > 12)' %(M_Lc, branchDict['Lc_SSKasproton'])
                   ,'Dp_SSKaspi'      : '((TMath::Abs(%f - %s) > 30 && TMath::Abs(%f - %s) > 30 ) || SSK_PIDK > 8) ' %(M_Dp, branchDict['Dp_SSKaspi'], M_Ds, branchDict['Dp_SSKaspi'])

                   ,'Dst_FullReco'        : '(%s > 190)' %branchDict['Dst_FullReco']
                   ,'Dst_SSKaspi_fromDz'  : '(%s > 190)' %branchDict['Dst_SSKaspi_fromDz']
                   ,'Dst_SSKaspi_fromDst' : '(%s > 190)' %branchDict['Dst_SSKaspi_fromDst']
                   
                   ,'Jpsi_piasmu'  : '(TMath::Abs(%f - %s) > 50.0 || pi_isMuon==0)' %(M_Jpsi, branchDict['Jpsi_piasmu'])
                   ,'Jpsi_SSKasmu' : '(TMath::Abs(%f - %s) > 50.0  || SSK_isMuon==0)' %(M_Jpsi, branchDict['Jpsi_SSKasmu'])
                   
                   #,'psi2S_pipasmup' : '1'
                   #,'psi2S_Kpasmup'  : '1'

                   #,'phi_piasK'           : '1'
                   #,'KS_OSKaspi'          : '1'
                   
                   #,'Kstar_SSKaspi'       : '1'
                   #,'Kstar_OSKaspi'       : '1'
                   }
    
    }

######################################################################
## Get the file and tuple.
######################################################################
#f = TFile('DalitzTuple_%s_%s.root' %(dataType, polarity), 'read')
inFileDir  = getPostSelDataDirectory()
inFileName = inFileDir + outPutFileNameDict[dataTag][polarity]
f = TFile(inFileName, 'read')
t = f.Get('B2DsMuNuTuple/DecayTree')
hList = []

######################################################################
## Make the histograms for the whole region.
######################################################################
h = makeHist(chain=t, xKey='Ds_M', name = 'AllData_MDs', numBinsX = numBins)
plotHist(hist = h, nameOverride="Hist_%s_%s_AllData_MDs_NoVetoes" %(dataType, polarity))
hList.append(h)

h = makeHist(chain=t, xKey="Beta_SSK", yKey='Ds_M', name = 'AllData_BetaKpVsMDs', numBinsX = numBins)
plotHist(hist = h, nameOverride="Hist_%s_%s_AllData_BetaSSKVsMDs_NoVetoes" %(dataType, polarity))
hList.append(h)

# A total cut string list.
masterCutList = []

######################################################################
## Now loop over all the configurations.
######################################################################
for res in vetoDict.keys():

    # Plot the M_Ds and M_Ds vs Beta first for the resonance region.
    h = makeHist(chain=t, xKey='Ds_M', name = '%s_MDs' %res, title = '%s_MDs' %res,
                 numBinsX = numBins, cutString = 'resFlag == %i' %resFlagDict[res])
    plotHist(hist = h, nameOverride="Hist_%s_%s_%sRegion_MDs_NoVetoes" %(dataType, polarity, res))    
    hList.append(h)

    h = makeHist(chain=t, xKey="Beta_SSK", yKey='Ds_M', name = '%s_BetaKpVsMDs' %res, numBinsX = numBins, cutString = 'resFlag == %i' %resFlagDict[res])
    plotHist(hist = h, nameOverride="Hist_%s_%s_%sRegion_BetaKpVsMDs_NoVetoes" %(dataType, polarity, res))
    hList.append(h)
    
    # A list for cuts.
    cutList = []
    cutStringBase = ('(resFlag == %i && (' %resFlagDict[res])
    
    # Now iterate over the backgrounds.
    for background in vetoDict[res].keys():
        
        bgCut = vetoDict[res][background]
        
        # Plot the background without vetoes.
        h1 = makeHist(chain=t, xKey=branchDict[background], name='%s_%s_NoVetoes' %(res, background),
                     numBinsX=numBins, cutString='resFlag == %i' %resFlagDict[res], title = 'No vetoes',
                     rangeX=massWindowDict[background], zeroYaxis=True, lineColour = 2)
        #plotHist(hist=h1, nameOverride="Hist_%s_%s_%sRegion_%sBackground_NoVetoes" %(dataType, polarity, res, background))
        hList.append(h1)
        
        # And now with vetoes.
        fullCutstring = 'resFlag == %i && %s' %(resFlagDict[res], bgCut)
        print fullCutstring
        h2 = makeHist(chain=t, xKey=branchDict[background], name='%s_%s_WithVetoes' %(res, background),
                     numBinsX=numBins, cutString=fullCutstring, title = 'With vetoes', #bgsettings['cut'],
                     rangeX=massWindowDict[background], zeroYaxis=True, lineColour = 4)
        #plotHist(hist=h2, nameOverride="Hist_%s_%s_%sRegion_%sBackground_WithVetoes" %(dataType, polarity, res, background))
        hList.append(h2)

        # Now plot a before and after comparison.
        plotHist(hist=[h1, h2], nameOverride="Hist_%s_%s_%sRegion_%sBackground_Comparison" %(dataType, polarity, res, background),
                 setLegend=True)
        
        # Make a cut string for this background.
        cutToAdd = '(%s)' %bgCut
        cutList.append(cutToAdd)

    # Now make a cutstring for this resonance region.
    for i in range(len(cutList)):
        toAdd = cutList[i]
        if i+1 != len(cutList):
            cutStringBase += '%s && ' %toAdd
        else:
            cutStringBase += '%s )' %toAdd

    # Now add the global cuts.
    cutStringBase += ' && (%s) )' %globalVetoes[res]
    
    print 'CUTSTRINGBASE says:'
    print '\t', cutStringBase

    # Now make the mass plot and m vs beta plot after cuts.
    h = makeHist(chain=t, xKey='Ds_M', name = '%s_MDs_WithVetoes' %res, numBinsX = numBins, cutString = cutStringBase)
    plotHist(hist = h, nameOverride="Hist_%s_%s_%sRegion_MDs_WithVetoes" %(dataType, polarity, res))
    hList.append(h)
    
    h = makeHist(chain=t, xKey="Beta_SSK", yKey='Ds_M', name = '%s_BetaKpVsMDs_WithVetoes' %res,
                 numBinsX = numBins, cutString = cutStringBase)
    plotHist(hist = h, nameOverride="Hist_%s_%s_%sRegion_BetaKpVsMDs_WithVetoes" %(dataType, polarity, res))
    hList.append(h)
    
    # Add the cutStringBase to the masterCutList.
    masterCutList.append(cutStringBase)

# Make the master cut string.
masterCutString = ' || '.join(masterCutList)
print masterCutString

# Now plot the whole dataset MDs andBeta vs MDs after cuts.
h = makeHist(chain=t, xKey='Ds_M', name = 'AllData_MDs_WithVetoes', numBinsX = numBins, cutString = masterCutString)
plotHist(hist = h, nameOverride="Hist_%s_%s_AllData_MDs_WithVetoes" %(dataType, polarity))
hList.append(h)

h = makeHist(chain=t, xKey="Beta_SSK", yKey='Ds_M', name = 'AllData_BetaKpVsMDs_WithVetoes', numBinsX = numBins, cutString=masterCutString)
plotHist(hist = h, nameOverride="Hist_%s_%s_AllData_BetaKpVsMDs_WithVetoes" %(dataType, polarity))
hList.append(h)

# Now save all this histograms to file.
outFile = TFile('Hists_%s_%s.root' %(dataType, polarity), 'recreate')
for h in hList:
    h.Write()
outFile.Close()    
print hList
