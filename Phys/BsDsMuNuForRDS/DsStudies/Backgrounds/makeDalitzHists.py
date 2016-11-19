######################################################################
## Script to make all the Ds background veto histograms.
######################################################################
from ROOT import *
from HistPlotters import *
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
#M_phi   =  

######################################################################
## Some options.
######################################################################
numBins = 80
dataType = "data"
polarity = "up"

######################################################################
## Some dictionaries for the loop.
######################################################################
# One for the resonance index integer.
resFlagDict = { 'phi'    : 0,
                'KStar'  : 1,
                'NonRes' : 2 }

# One for the ranges of the mass windows.
massWindowDict = {

    'Lc_Kpasproton'  : (M_Lc - 80.0, M_Lc + 80.0)
    ,'Dp_Kpaspip'    : (M_Dp - 200.0, M_Dp + 130.0)

    ,'Dst_Kpaspip_fromDz'  : (0.0, 1200.0)
    ,'Dst_Kmaspim_fromDz'  : (0.0, 1200.0)
    ,'Dst_Kpaspip_fromDst' : (0.0, 1400.0)
    ,'Dst_Kmaspim_fromDst' : (0.0, 1400.0)
    
    ,'Kstar'         : (400.0, 1200.0)
    ,'Jpsi_pipasmup' : (M_Jpsi - 150.0, M_Jpsi + 150.0)
    ,'Jpsi_Kpasmup'  : (M_Jpsi - 150.0, M_Jpsi + 150.0)

    ,'psi2S_pipasmup' : (M_psi2S - 150, M_psi2S + 150)
    ,'psi2S_Kpasmup'  : (M_psi2S - 150, M_psi2S + 150)

    ,'psi3370_pipasmup'    : (M_psi3770 - 150, M_psi3770 + 150)
    ,'psi3370_Kpasmup'     : (M_psi3770 - 150, M_psi3770 + 150)

    ,'phi_pipasKp'         : [800, 2100]
    ,'f0_Kmaspim'          : [200, 1600]

    ,'Kstar_Kpaspip'       : [500, 1800]
    ,'Kstar_Kmaspim'       : [500, 1800]
    
    }

# One for the global vetoes for each resonance.
globalVetoes = {
    'phi'    : 'M_Ds > 1900' #(Kp_ProbNNK > 0.15)'
    ,'KStar'  : '(M_Ds > 1900 && Kp_ProbNNK > 0.2 && Km_ProbNNK > 0.2)'# && pip_PIDK < 8)'
    ,'NonRes' : '(M_Ds > 1900 && Kp_ProbNNK > 0.25 && Km_ProbNNK > 0.25 && pip_PIDK < 8)'
    }

branchDict = {

    'Lc_Kpasproton'        : 'WM_Lc_Kpasproton'
    ,'Dp_Kpaspip'          : 'WM_Dp_Kpaspip'

    ,'Dst_Kpaspip_fromDz'  : 'WM_Dst_Kpaspip_fromDz'
    ,'Dst_Kmaspim_fromDz'  : 'WM_Dst_Kmaspim_fromDz'
    ,'Dst_Kpaspip_fromDst' : 'WM_Dst_Kpaspip_fromDst'
    ,'Dst_Kmaspim_fromDst' : 'WM_Dst_Kmaspim_fromDst'

    ,'Jpsi_pipasmup'       : 'WM_Jpsi_pipasmup'
    ,'Jpsi_Kpasmup'        : 'WM_Jpsi_Kpasmup'

    ,'psi2S_pipasmup'      : 'WM_Jpsi_pipasmup'
    ,'psi2S_Kpasmup'       : 'WM_Jpsi_Kpasmup'

    ,'psi3370_pipasmup'    : 'WM_Jpsi_pipasmup'
    ,'psi3370_Kpasmup'     : 'WM_Jpsi_Kpasmup'
    
    ,'Kst_Kpaspip'         : 'WM_Kstar_Kpaspip'
    ,'Kst_Kpaspip'         : 'WM_Kstar_Kpaspip'

    ,'phi_pipasKp'         : 'WM_phi_pipasKp'
    ,'f0_Kmaspim'          : 'WM_f0_Kmaspim'

    ,'Kstar_Kpaspip'       : 'WM_Kstar_Kpaspip'
    ,'Kstar_Kmaspim'       : 'WM_Kstar_Kmaspim'
    
    }

# One for the vetoes.
vetoDict = {

    'phi'    : {  'Lc_Kpasproton'        : '(TMath::Abs(%f - WM_Lc_Kpasproton) > 30 || (Kp_PIDK - Kp_PIDp) > 0)' %M_Lc
                  ,'Dp_Kpaspip'          : '1' #'(TMath::Abs(%f - WM_Dp_Kpaspip) > 30 || Kp_PIDK > 8)' %M_Dp
                  
                  #,'Dst_Kpaspip_fromDz'  : '1'
                  #,'Dst_Kmaspim_fromDz'  : '1'
                  ,'Dst_Kpaspip_fromDst' : '(WM_Dst_Kpaspip_fromDst > 190)'
                  #,'Dst_Kmaspim_fromDst' : '1'

                  ,'Jpsi_pipasmup'    : '(TMath::Abs(%f - WM_Jpsi_pipasmup) > 50.0 || pip_isMuon==0)' %M_Jpsi
                  ,'Jpsi_Kpasmup'     : '(TMath::Abs(%f - WM_Jpsi_Kpasmup) > 50.0  || Kp_isMuon==0)' %M_Jpsi

                  #,'psi2S_pipasmup' : '1'
                  #,'psi2S_Kpasmup'  : '1'

                  #,'psi3370_pipasmup' : '1'
                  #,'psi3370_Kpasmup'  : '1'

                  #,'phi_pipasKp'         : '1' #(Kp_PIDK > 10 && TMath::Abs() < 30)'
                  #,'f0_Kmaspim'          : '1' #'Km_PIDK > 12'
                  
                  #,'Kstar_Kpaspip'       : '1' #((TMath::Abs(%f - WM_Kstar_Kpaspip) > 25.0 || Kp_PIDK > 5) && (WM_Kstar_Kpaspip > 800 || Kp_PIDK > 4))' %M_Kstar
                  #,'Kstar_Kmaspim'       : '1'

                 }

    ,'KStar'  : {  'Lc_Kpasproton'        : '(TMath::Abs(%f - WM_Lc_Kpasproton) > 30 || (Kp_PIDK - Kp_PIDp) > 5)' %M_Lc
                   ,'Dp_Kpaspip'          : '((TMath::Abs(%f - WM_Dp_Kpaspip) > 30 && TMath::Abs(%f - WM_Dp_Kpaspip) > 30 ) || Kp_PIDK > 14) ' %(M_Dp, M_Ds)

                   ,'Dst_Kpaspip_fromDz'  : '(WM_Dst_Kpaspip_fromDz > 190)'
                   ,'Dst_Kmaspim_fromDz'  : '(WM_Dst_Kmaspim_fromDz > 190)'
                   ,'Dst_Kpaspip_fromDst' : '(WM_Dst_Kpaspip_fromDst > 190)'
                   #,'Dst_Kmaspim_fromDst' : '1'

                   ,'Jpsi_pipasmup'    : '(TMath::Abs(%f - WM_Jpsi_pipasmup) > 50.0 || pip_isMuon==0)' %M_Jpsi
                   ,'Jpsi_Kpasmup'     : '(TMath::Abs(%f - WM_Jpsi_Kpasmup) > 50.0  || Kp_isMuon==0)' %M_Jpsi

                   #,'psi2S_pipasmup' : '1'
                   #,'psi2S_Kpasmup'  : '1'

                   #,'phi_pipasKp'         : '1'
                   #,'f0_Kmaspim'          : '1'

                   ,'Kstar_Kpaspip'       : '((TMath::Abs(%f - WM_Kstar_Kpaspip) > 25.0 || Kp_PIDK > 5) && (WM_Kstar_Kpaspip > 800 || Kp_PIDK > 4))' %M_Kstar
                   #,'Kstar_Kmaspim'       : '1'

                   }
    ,'NonRes' : {  'Lc_Kpasproton'        : '(TMath::Abs(%f - WM_Lc_Kpasproton) > 30 || (Kp_PIDK - Kp_PIDp) > 5)' %M_Lc
                   ,'Dp_Kpaspip'          : '((TMath::Abs(%f - WM_Dp_Kpaspip) > 40 && TMath::Abs(%f - WM_Dp_Kpaspip) > 40 ) || Kp_PIDK > 14) ' %(M_Dp, M_Ds)

                   ,'Dst_Kpaspip_fromDz'  : '(WM_Dst_Kpaspip_fromDz > 190)'
                   ,'Dst_Kmaspim_fromDz'  : '(WM_Dst_Kmaspim_fromDz > 190)'
                   ,'Dst_Kpaspip_fromDst' : '(WM_Dst_Kpaspip_fromDst > 190)'
                   #,'Dst_Kmaspim_fromDst' : '1'

                   ,'Jpsi_pipasmup'    : '(TMath::Abs(%f - WM_Jpsi_pipasmup) > 50.0 || pip_isMuon==0)' %M_Jpsi
                   ,'Jpsi_Kpasmup'     : '(TMath::Abs(%f - WM_Jpsi_Kpasmup) > 50.0  || Kp_isMuon==0)' %M_Jpsi

                   #,'psi2S_pipasmup' : '1'
                   #,'psi2S_Kpasmup'  : '1'

                   #,'phi_pipasKp'         : '1'
                   #,'f0_Kmaspim'          : '1'

                   ,'Kstar_Kpaspip'       : '((TMath::Abs(%f - WM_Kstar_Kpaspip) > 25.0 || Kp_PIDK > 5) && (WM_Kstar_Kpaspip > 800 || Kp_PIDK > 4))' %M_Kstar
                   #,'Kstar_Kmaspim'       : '1'

                   }
    
#                 ,'Kstar' : { 'cut'     : '((TMath::Abs(%f - WM_Kstar) > 25.0 || Kp_PIDK > 8) && (WM_Kstar > 800 || Kp_PIDK > 7))' %M_Kstar
#                              ,'branch' : 'WM_Kstar' }
#                 ,'Jpsi'   : { 'cut'     : '(TMath::Abs(%f - WM_Jpsi) > 50.0 || pip_isMuon==0)' %M_Jpsi
#                              ,'branch' : 'WM_Jpsi' }
#                 }

    }

######################################################################
## Get the file and tuple.
######################################################################
f = TFile('DalitzTuple_%s_%s.root' %(dataType, polarity), 'read')
t = f.Get('DalitzTuple')
hList = []

######################################################################
## Make the histograms for the whole region.
######################################################################
h = makeHist(chain=t, xKey='M_Ds', name = 'AllData_MDs', numBinsX = numBins)
plotHist(hist = h, nameOverride="Hist_%s_%s_AllData_MDs_NoVetoes" %(dataType, polarity))
hList.append(h)

h = makeHist(chain=t, xKey="Beta_Kp", yKey='M_Ds', name = 'AllData_BetaKpVsMDs', numBinsX = numBins)
plotHist(hist = h, nameOverride="Hist_%s_%s_AllData_BetaKpVsMDs_NoVetoes" %(dataType, polarity))
hList.append(h)

# A total cut string list.
masterCutList = []

######################################################################
## Now loop over all the configurations.
######################################################################
for res in vetoDict.keys():

    # Plot the M_Ds and M_Ds vs Beta first for the resonance region.
    h = makeHist(chain=t, xKey='M_Ds', name = '%s_MDs' %res, title = '%s_MDs' %res,
                 numBinsX = numBins, cutString = 'resFlag == %i' %resFlagDict[res])
    plotHist(hist = h, nameOverride="Hist_%s_%s_%sRegion_MDs_NoVetoes" %(dataType, polarity, res))    
    hList.append(h)

    h = makeHist(chain=t, xKey="Beta_Kp", yKey='M_Ds', name = '%s_BetaKpVsMDs' %res, numBinsX = numBins, cutString = 'resFlag == %i' %resFlagDict[res])
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
    h = makeHist(chain=t, xKey='M_Ds', name = '%s_MDs_WithVetoes' %res, numBinsX = numBins, cutString = cutStringBase)
    plotHist(hist = h, nameOverride="Hist_%s_%s_%sRegion_MDs_WithVetoes" %(dataType, polarity, res))
    hList.append(h)
    
    h = makeHist(chain=t, xKey="Beta_Kp", yKey='M_Ds', name = '%s_BetaKpVsMDs_WithVetoes' %res,
                 numBinsX = numBins, cutString = cutStringBase)
    plotHist(hist = h, nameOverride="Hist_%s_%s_%sRegion_BetaKpVsMDs_WithVetoes" %(dataType, polarity, res))
    hList.append(h)
    
    # Add the cutStringBase to the masterCutList.
    masterCutList.append(cutStringBase)

# Make the master cut string.
masterCutString = ' || '.join(masterCutList)
print masterCutString

# Now plot the whole dataset MDs andBeta vs MDs after cuts.
h = makeHist(chain=t, xKey='M_Ds', name = 'AllData_MDs_WithVetoes', numBinsX = numBins, cutString = masterCutString)
plotHist(hist = h, nameOverride="Hist_%s_%s_AllData_MDs_WithVetoes" %(dataType, polarity))
hList.append(h)

h = makeHist(chain=t, xKey="Beta_Kp", yKey='M_Ds', name = 'AllData_BetaKpVsMDs_WithVetoes', numBinsX = numBins, cutString=masterCutString)
plotHist(hist = h, nameOverride="Hist_%s_%s_AllData_BetaKpVsMDs_WithVetoes" %(dataType, polarity))
hList.append(h)

# Now save all this histograms to file.
outFile = TFile('Hists_%s_%s.root' %(dataType, polarity), 'recreate')
for h in hList:
    h.Write()
outFile.Close()    
print hList
