#########################################################################
# A module to contain functions to plot histograms in a nice way.
# Uses the entries in the Dicts/Hist module
#########################################################################
#from LcTophhBFStuff.Dicts.Hist import histDict
from ROOT import *
import sys

histDict = {
    'M_Ds' : { 'name'   : ''
               ,'units' : 'MeV/c^{2}'
               ,'label' : 'M(K^{+} K^{-} #pi^{+})'
               ,'range' : [1750.0, 2080.0] }

    ,'Beta_Kp' : { 'name'   : ''
                   ,'units' : ''
                   ,'label' : '#Beta'
                   ,'range' : [-1.0, 1.0] }

    ,'M_KmKp'  : { 'name' : ''
                   ,'units' : 'GeV/c^{2}'
                   ,'label' : 'M(K^{+} K^{-})'
                   ,'range' : [900e-3, 2000e-3] }

    ,'M_Kmpi' : { 'name' : ''
                   ,'units' : 'GeV/c^{2}'
                   ,'label' : 'M(#pi^{+} K^{-})'
                   ,'range' : [600e-3, 1600e-3] }

    ,'WM_Lc_Kpasproton' : { 'name' : ''
                            ,'units' : 'MeV/c^{2}'
                            ,'label' : 'M(p^{+}[K^{+}] K^{-} #pi^{+})'
                            ,'range' : [1980.0, 3600.0] }
    
    ,'WM_Dp_Kpaspip': { 'name' : ''
                        ,'units' : 'MeV/c^{2}'
                        ,'label' : 'M(#pi^{+}[K^{+}] K^{-} #pi^{+})'
                        ,'range' : [1000.0, 2000.0] }
    
    # Dstar WM vars.
    ,'WM_Dst_Kpaspip_fromDz'   : { 'name'   : ''
                                   ,'units' : 'MeV/c^{2}'
                                   ,'label' : 'M(#pi^{+}[K^{+}] K^{-} #pi^{+}) - M(#pi^{+}[K^{+}] K^{-})'
                                   ,'range' : [100.0, 1200.0] }
    ,'WM_Dst_Kmaspim_fromDz'   : { 'name'   : ''
                                   ,'units' : 'MeV/c^{2}'
                                   ,'label' : 'M(#pi^{-}[K^{-}] K^{+} #pi^{+}) - M(#pi^{-}[K^{-}] K^{+})'
                                   ,'range' : [100.0, 1200.0] }

    ,'WM_Dst_Kpaspip_fromDst'  : { 'name'   : ''
                                   ,'units' : 'MeV/c^{2}'
                                   ,'label' : 'M(#pi^{+} K^{-} #pi^{+}[K^{+}]) - M(#pi^{+} K^{-})'
                                   ,'range' : [0.0, 1200.0] }
    ,'WM_Dst_Kmaspim_fromDst'   : { 'name'   : ''
                                    ,'units' : 'MeV/c^{2}'
                                    ,'label' : 'M(K^{+} #pi^{+} #pi^{-}[K^{-}]) - M(K^{+} #pi^{+})'
                                    ,'range' : [100.0, 1200.0] }
    
    
    ,'WM_Jpsi_pipasmup'  : { 'name'   : ''
                              ,'units' : 'MeV/c^{2}'
                              ,'label' : 'M(#mu^{+}[#pi^{+}] #mu^{-})'
                              ,'range' : [500.0, 4000.0] }

    ,'WM_Jpsi_Kpasmup'  : { 'name'   : ''
                            ,'units' : 'MeV/c^{2}'
                            ,'label' : 'M(#mu^{+}[K^{+}] #mu^{-})'
                            ,'range' : [500.0, 4000.0] }
    
    ,'WM_Kstar_Kpaspip'  : {'name' : ''
                            ,'units' : 'MeV/c^{2}'
                            ,'label' : 'M(#pi^{+}[K^{+}] K^{-})'
                            ,'range' : [600.0, 1600.0] }

    ,'WM_Kstar_Kmaspim'  : {'name' : ''
                            ,'units' : 'MeV/c^{2}'
                            ,'label' : 'M(#pi^{-}[K^{-}] K^{+})'
                            ,'range' : [600.0, 1600.0] }

    ,'WM_phi_pipasKp'    : {'name' : ''
                            ,'units' : 'MeV/c^{2}'
                            ,'label' : 'M(K^{+}[#pi^{+}] K^{-})'
                            ,'range' : [600.0, 1600.0] }

    ,'WM_f0_Kmaspim'   :  {'name' : ''
                           ,'units' : 'MeV/c^{2}'
                           ,'label' : 'M(#pi^{+} #pi^{-}[K^{-}])'
                           ,'range' : [600.0, 1600.0] } 
    
    }

def makeHist(**kwargs):
    '''
    Function to make a histogram from a chain or tree.
    Can make either 1D or 2D histograms.
    Takes the chain object, xKey and name as required keyword arguments.
    Then takes keyword arguments to specify the dimensionality of the histogram
    and any other options to do with the filling.
    Required keywords:
      chain     - the TChain or TTree object.
      xKey      - x axis key.
    Optional histogram maker keywords:
      name       - histogram name. Defaults to "h".
      yKey       - y axis key.
      title      - histogram title, can be used for automated legend labels etc.
      cutString  - optional preselection, default = "1".
    Optional histogram formatting keywords: 
      numBinsX   - number of hist bins in x, default = 80.
      numBinsY   - number of hist bins in y, default = 80.
      rangeX     - override the x-axis ranges from the dictionary.
      rangeY     - override the y-axis ranges from the dictionary.
      zeroYaxis  - set the y-axis to go from zero to 1.2 times the max hist value.
      normalise  - normalise the histogram, default = False.
      decPlaces  - decimal places in axes labels, default = 3.
      lineColour - change lineColour, default = kBlack.
    '''
            
    # Unpack the command line args.        
    validKeys = kwargs.keys()        
    if ('xKey' not in validKeys):
        print 'HistPlotters ERROR: xKey not provided.'
        return None
    if ('chain' not in validKeys):
        print 'HistPlotters ERROR: chain not provided.'
        return None
    xKey  = kwargs['xKey']
    chain = kwargs['chain']

    # Now figure out the histogram dimensionality.
    dim = 1
    yKey = ''
    if 'yKey' in validKeys:
        dim = 2
        yKey = kwargs['yKey']

    # Now configure the number of bins.
    numBinsX = 80
    if 'numBinsX' in validKeys:
        numBinsXRaw = kwargs['numBinsX']
        if type(numBinsXRaw) != int:
            print 'WARNING: number of X bins is not an integer. Rounding may be problematic'
            numBinsX = int(numBinsXRaw)
        else:    
            numBinsX = numBinsXRaw

    numBinsY = 80
    if 'numBinsY' in validKeys:
        numBinsYRaw = kwargs['numBinsY']
        if type(numBinsYRaw) != int:
            print 'WARNING: number of Y bins is not an integer. Rounding may be problematic'
            numBinsY = int(numBinsYRaw)
        else:
            numBinsY = numBinsYRaw

    # Configure the cuts.        
    cutString = '1'        
    if 'cutString' in validKeys:
        cutString = kwargs['cutString']

    # Make sure the right border is the right size.    
    if dim == 1:
        gStyle.SetPadRightMargin(0.05)
    elif dim == 2:
        gStyle.SetPadRightMargin(0.12)

    # Now get the settings in X and Y.
    xSettings = histDict[xKey]
    ySettings = None
    if dim == 2:
        ySettings = histDict[yKey]

    # Process all the ranges.
    xMin = xSettings['range'][0]
    xMax = xSettings['range'][1]
    yMin = None
    yMax = None
    if dim == 2:
        yMin = ySettings['range'][0]
        yMax = ySettings['range'][1]

    # Override the ranges if requested.
    if 'rangeX' in validKeys:
        xRanges = kwargs['rangeX']
        xMin = xRanges[0]
        xMax = xRanges[1]
    if 'rangeY' in validKeys:
        yRanges = kwargs['rangeY']
        yMin = yRanges[0]
        yMax = yRanges[1]
        
    # Draw the histogram from the Tree to the gDirectory.
    histName = 'h'
    if 'name' in validKeys:
        histName = kwargs['name']
    if dim == 1:
        drawString = '%s>>%s(%i, %f, %f)' %(xKey, histName, numBinsX, xMin, xMax)
                                            
    elif dim == 2:
        # NOTE!!! The x and y keys are switched in the drawstring because ROOT is stupid
        # and treats the variables in this order.
        drawString = '%s:%s>>%s(%i, %f, %f, %i, %f, %f)' %(yKey, xKey, histName,
                                                           numBinsX, xMin, xMax,
                                                           numBinsY, yMin, yMax)
    # Now draw the hist to memory.    
    chain.Draw(drawString, cutString)

    # Now get the histogram from the memory, and normalise if necessary.
    h = gDirectory.Get(histName)
    h.SetName(histName)
    
    toNormalise = False
    if 'normalise' in validKeys:
        if kwargs['normalise'] == True:
            toNormalise = True
        elif kwargs['normalise'] == False:
            pass
        else:
            print 'WARNING: noramlisation instruction not recognised. Not normalising.'
    if toNormalise:
        h.Scale(1/h.Integral())

    # Figure out the bin width.
    fullWidthX = abs(xMin - xMax)
    binWidthX  = fullWidthX / float(numBinsX)

    # Format the title.
    title = ''
    if 'title' in validKeys:
        title = kwargs['title']
    h.SetTitle(title)    
    
    # Now format the axes.
    xTitle = xSettings['label']
    if xSettings['units'] != '':
        xTitle = '%s [%s]' %(xSettings['label'], xSettings['units'])
    h.GetXaxis().SetTitle(xTitle)

    # If requested set the y axis to go down to zero.
    zeroYaxis = False
    if 'zeroYaxis' in validKeys:
        zeroYaxis = kwargs['zeroYaxis']
    if zeroYaxis:
        h.GetYaxis().SetRangeUser(0.0, 1.2*h.GetMaximum())
    
    # If 1D format the bin width to y-axis
    decPlaces = '3'
    if 'decPlaces' in validKeys:
        decPlaces = str(kwargs['decPlaces'])

    # Want entries per X or population per X if normalised.    
    valueWord = 'Entries'
    if toNormalise:
        valueWord = 'Population'
        
    yTitleBase = valueWord + ' per %0.0' + decPlaces + 'f'
    if xSettings['units'] != '':
        yTitleBase = valueWord + ' per %0.0' + decPlaces + 'f' + '[' + xSettings['units'] + ']'

    yTitle = yTitleBase %binWidthX    
    h.GetYaxis().SetTitle(yTitle)

    if dim == 2:
        yTitle = ySettings['label']
        if ySettings['units'] != '':
            yTitle = '%s [%s]' %(ySettings['label'], ySettings['units'])
            h.GetYaxis().SetTitle(yTitle)

    if xSettings['name'] == '':        
        h.SetName(xKey)
    else:
        h.SetName(xSettings['name'])

    if dim == 2:
        xPart = xKey
        if xSettings['name'] != '':
            xPart = xSettings['name']
        yPart = yKey
        if ySettings['name'] != '':
            yPart = ySettings['name']
        h.SetName('%s_vs_%s' %(xPart, yPart))    

    # Set line properties
    lineColour = kBlack
    if 'lineColour' in validKeys:
        lineColour = kwargs['lineColour']
    h.SetLineColor(lineColour)    

    # Now return the filled and formatted histogram.    
    return h    

#########################################################################################

def plotHist(**kwargs):
    '''
    Function to plot histograms on a canvas.
    Can plot any number of histograms.
    Required key word arguments:
      hist - Individual histogram or list of histogram objects to be plotted.
    Optional key word arguments:
      h2            - second histogram to be plotted as a comparison, default = None
      cx            - number of x pixels on canvas, default = 800.
      cy            - number of y pixels on canvas, default = 600.
      cName         - name of canvas, defaults to h1.GetTitle().
      setLog        - plot with a log scale. Default = False
      drawOption    - THistPainter option. Default is "HIST" for TH1, "COLZ" for TH2.
      gfxType       - the graphics format for the plot. Default = .eps
      plotNameOpts  - a tag added to the plot name. For example, can supply the mode, stream etc.
      setLegend     - option to set the legend on the histogram. Default = False
      nameOverride  - totally override any automated file naming and call the file this,
                      plus the graphics extension.
    '''
    # First check some command line arguments.
    validKeys = kwargs.keys()
    if not 'hist' in validKeys:
        print 'HistPlotters ERROR: specify hist key word argument.'
        return None
    hListInput = kwargs['hist']

    # Is hListInput a histogram or a list of histograms?
    isList = False
    if type(hListInput) is list:
        isList = True
        
    # If not, populate a new list with the one histogram we have.
    hList = [hListInput]
    if isList:
        hList = hListInput

    # Find the histogram dimensionality.
    dim = None
    h1 = hList[0]
    if 'TH1' in type(h1).__name__:
        dim = 1
    elif 'TH2' in type(h1).__name__:
        dim = 2
    else:
        print 'ERROR: histogram class not recognised.'
        return None

    # Set up the canvas as needed.    
    cName = h1.GetName()
    if 'cName' in validKeys:
        cName = kwargs['cName']
    cx = 800
    if 'cx' in validKeys:
        cx = kwargs['cx']
    cy = 600
    if 'cy' in validKeys:
        cy = kwargs['cy']
    c = TCanvas(cName, cName, cx, cy)

    # Set Log option.
    setLog = False
    if 'setLog' in validKeys:
        #setLogString = kwargs['setLog']
        #if setLogString == 'True':
        setLog = kwargs['setLog']

    if setLog:        
        if dim == 1:
            c.SetLogy()
        elif dim == 2:
            c.SetLogz()

    # Now draw it. 
    drawOption = 'HIST'
    if dim == 2:
        drawOption = 'COLZ'

    if 'drawOption' in validKeys:
        drawOption = kwargs['drawOption']

    # Draw the histograms. Order them so the maximum gets draw first.
    maxIndex = 0
    maxIndexValue = 0
    for i in range(len(hList)):
        h = hList[i]
        if h.GetMaximum() > maxIndexValue:
            maxIndex = i
            maxIndexValue = h.GetMaximum()
            
    # Now get the max hist from the list, draw it first,
    # then plot the rest of the histograms in the list.
    maxHist = hList[maxIndex]
    maxHist.Draw(drawOption)
    for i in range(len(hList)):
        if i == maxIndex: continue
        hList[i].Draw(drawOption + ' SAME')
    
    # Now draw the legend.
    # Might be helpful if the titles are the legend.
    # Means less arguments in this function, but more in makeHist().
    setLegend = False
    if 'setLegend' in validKeys:
        setLegend = kwargs['setLegend']

    # Handle the location of the legend on the plot.    
    x1, y1, x2, y2 = (0.15, 0.8, 0.33, 0.9)
    legendPositions = (x1, y1, x2, y2)
    if 'legendPositions' in validKeys:
        legendPositions = kwargs['legendPositions']
        if not ( (type[legendPositions] is tuple) or (type[legendPositions] is list) ):
            sys.exit('HistPlotters ERROR: legendPositions should be a list or a tuple.')
        # Recast to a tuple if list.
        if type(legendPostions) is list:
            legendPositions = tuple(legendPositions)
        if len(legendPositions) != 4:
            sys.exit('HistPlotters ERROR: legendPositions requires four elements.')
        for i in legendPositions:
            if type(i) is not float:
                sys.exit('HistPlotters ERROR: legendPositions should be floats.')
            if not (i >= 0.0 and i <= 1.0):
                sys.exit('HistPlotters ERROR: legendPositions should be between zero and one.')
        legendPositions = x1, y1, x2, y2

    # Set the legend if requested.    
    if setLegend:
        l = TLegend(legendPositions[0], legendPositions[1],
                    legendPositions[2], legendPositions[3])
        for h in hList:
            l.AddEntry(h, h.GetTitle(), 'l')
        l.Draw()    
        
    # Now save the TCanvas.        
    gfxType = '.png'
    if 'gfxType' in validKeys:
        gfxType = kwargs['gfxType']

    plotNameOpts = ''
    if 'plotNameOpts' in validKeys:
        plotNameOpts = kwargs['plotNameOpts']
    if plotNameOpts != '':    
        plotNameBase  = 'Hist_%s_%s' %(plotNameOpts, cName)
    else:
        plotNameBase  = 'Hist_%s' %(cName)
    if len(hList)>1:
        plotNameBase = '%sComparison_%s' %(plotNameOpts, cName)

    # But if we have a nameOverride requested, use that for the name.
    if 'nameOverride' in validKeys:
        plotNameBase = kwargs['nameOverride']

    plotNameFull = plotNameBase + gfxType
    c.SaveAs(plotNameFull)
    return None
