#########################################################################
# A module to contain functions to plot histograms in a nice way.
# Uses the entries in the Dicts/Hist module
#########################################################################
#from Hist import histDict
histDict = {
    'mu_iso_MinBDT_Long' : { 'name'   : ''
                             ,'units' : ''
                             ,'label' : '#mu iso MinBDT Long' }
    }
    
#########################################################################
# Imports
from ROOT import *
#from TruthCuts import *
import TruthCuts
import numpy, array, datetime
gROOT.ProcessLine('.x ~/lhcbStyle.C')
gROOT.SetBatch()
import sys

#########################################################################
# Seed a random number generator with the OS time.
timeNow          = datetime.datetime.now()
timeSum          = timeNow.microsecond + timeNow.second
randomGenerator  = TRandom3(timeSum)
histIndexCounter = randomGenerator.Uniform(10e10)

#########################################################################
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
      yKey       - y axis key.
      name       - histogram name. Defaults to "h".
      scaleX     - scale the histogram X-axis by this factor.
      scaleY     - scale the histogram Y-axis by this factor.
      title      - histogram title, can be used for automated legend labels etc.
      cutString  - optional preselection, default = "1".
    Optional histogram formatting keywords: 
      numBinsX   - number of hist bins in x, default = 80.
      numBinsY   - number of hist bins in y, default = 80.
      rangeX     - override the automatic axis limit setting on X.
      rangeY     - override the automatic axis limit setting on Y.
      labelX     - x axis label
      labelY     - y axis label
      unitsX     - x axis units
      unitsY     - y axis units
      zeroYaxis  - set the y-axis to go from zero to 1.2 times the max hist value.
      normalise  - normalise the histogram, default = False.
      decPlaces  - decimal places in axes labels, default = 3.
      lineColour - change lineColour, default = kBlack.
    '''
    # Unpack the required command line args.        
    validKeys = kwargs.keys()        
    if ('xKey' not in validKeys):
        print 'HistPlotters ERROR: xKey not provided.'
        return None
    if ('chain' not in validKeys):
        print 'HistPlotters ERROR: chain not provided.'
        return None
    xKey  = kwargs['xKey']
    chain = kwargs['chain']

    # Check that all the arguments given are valid keywords - it's easy to mis this out.
    recognisedKeyList = ['xKey', 'yKey', 'chain', 'name', 'scaleX', 'scaleY', 'yKey',
                         'title', 'cutString', 'numBinsX', 'numBinsY', 'rangeX', 'rangeY',
                         'zeroYaxis', 'normalise', 'decPlaces', 'lineColour', 'labelX', 'unitsX'
                         'labelY', 'unitsY']
    for theKey in validKeys:
        if theKey not in recognisedKeyList:
            sys.exit('HistPlotters.makeHist ERROR: keyword "%s" not recognised.' %theKey)

    # Now unpack the command line arguments which go in the variable settings if
    # it isn't already in the histDict.
    histName = ''
    if 'name' in validKeys:
        histName = kwargs['name']
    labelX  = ''
    if 'labelX' in validKeys:
        labelX   = kwargs['labelX']
    unitsX  = ''
    if 'unitsX' in validKeys:
        unitsX   = kwargs['unitsX']

    labelY  = ''
    if 'labelY' in validKeys:
        labelY   = kwargs['labelY']
    unitsY  = ''
    if 'unitsY' in validKeys:
        unitsY   = kwargs['unitsY']
    
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
    # If they're not there then make some dummy settings.
    xSettings = {}
    if not xKey in histDict.keys():
        xSettings = { 'name'   : histName
                      ,'units' : unitsX
                      ,'label' : labelX
                      }
    else:    
        xSettings = histDict[xKey]
    if 'labelX' in validKeys:
        xSettings['label'] = 'labelX'
    if 'unitsX' in validKeys:
        xsettings['units'] = 'unitsX'
    # Y settings if needed.    
    ySettings = None
    if dim == 2:
        ySettings = {}
        if not yKey in histDict.keys():
            ySettings = { 'name'   : histName
                          ,'units' : unitsY
                          ,'label' : labelY
                          }
        else:
            ySettings = histDict[yKey]
        if 'labelY' in validKeys:
            ySettings['label'] = 'labelY'
        if 'unitsY' in validKeys:
            ysettings['units'] = 'unitsY'
            
    # Process all the ranges.
    # If it's set then use that. If not then use default ranges.
    xMin = chain.GetMinimum(xKey) #xSettings['range'][0]
    xMax = chain.GetMaximum(xKey) #xSettings['range'][1]
    yMin = None
    yMax = None
    if dim == 2:
        yMin = chain.GetMinimum(yKey) #ySettings['range'][0]
        yMax = chain.GetMaximum(yKey) #ySettings['range'][1]

    # Override the ranges if requested.
    if 'rangeX' in validKeys:
        xRanges = kwargs['rangeX']
        xMin = xRanges[0]
        xMax = xRanges[1]
    if 'rangeY' in validKeys:
        yRanges = kwargs['rangeY']
        yMin = yRanges[0]
        yMax = yRanges[1]

    # Get the scalings.    
    scaleX = 1.0
    scaleY = 1.0
    if 'scaleX' in validKeys:
        scaleX = kwargs['scaleX']
    if 'scaleY' in validKeys:
        scaleY = kwargs['scaleY']
    
    # Draw the histogram from the Tree to the gDirectory.
    # Give it a unique name with the random module seeded to
    # the OS time.
    global histIndexCounter
    histNameInMemory = 'h' + str(histIndexCounter)
    histIndexCounter += 1
    if dim == 1:
        drawString = '%s*%f>>%s(%i, %f, %f)' %(xKey, scaleX, histNameInMemory, numBinsX, xMin, xMax)
                                            
    elif dim == 2:
        # NOTE!!! The x and y keys are switched in the drawstring because ROOT is stupid
        # and treats the variables in this order.
        drawString = '%s*%f:%s*%f>>%s(%i, %f, %f, %i, %f, %f)' %(yKey, scaleY, xKey, scaleX,
                                                                 histNameInMemory,
                                                                 numBinsX, xMin, xMax,
                                                                 numBinsY, yMin, yMax)
    # Now draw the hist to memory.    
    chain.Draw(drawString, cutString)

    # Now get the histogram from the memory, and normalise if necessary.
    h = gDirectory.Get(histNameInMemory)
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
        h.Sumw2()
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
        h.GetYaxis().SetRangeUser(0.0001, 1.2*h.GetMaximum())
    
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
    h.SetMarkerColor(lineColour)

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
      autoSetColours - override the previous line/pointer colours of the histograms 
    '''
    # First check some command line arguments.
    validKeys = kwargs.keys()
    if not 'hist' in validKeys:
        print 'HistPlotters ERROR: specify hist key word argument.'
        return None
    hListInput = kwargs['hist']

    # Check that all the arguments given are valid keywords - it's easy to mis this out.
    recognisedKeyList = ['hist', 'cx', 'cy', 'cName', 'setLog', 'drawOption', 'gfxType',
                         'plotNameOpts', 'setLegend', 'nameOverride', 'legendPositions']
    for theKey in validKeys:
        if theKey not in recognisedKeyList:
            sys.exit('HistPlotters.plotHist ERROR: keyword "%s" not recognised.' %theKey)
            
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
        if not ( (type(legendPositions) is tuple) or (type(legendPositions) is list) ):
            sys.exit('HistPlotters ERROR: legendPositions should be a list or a tuple.')
        # Recast to a tuple if list.
        if type(legendPositions) is list:
            legendPositions = tuple(legendPositions)
        if len(legendPositions) != 4:
            sys.exit('HistPlotters ERROR: legendPositions requires four elements.')
        for i in legendPositions:
            if type(i) is not float:
                sys.exit('HistPlotters ERROR: legendPositions should be floats.')
            if not (i >= 0.0 and i <= 1.0):
                sys.exit('HistPlotters ERROR: legendPositions should be between zero and one.')
        #legendPositions = x1, y1, x2, y2

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

#########################################################################################
def makeROC(**kwargs):
    '''
    A function to make a TGraph which may be interpretted as a ROC curve.
    Needs as argument two trees containing the different species.
    Needs a variable to scan over, and an indication of "lessthan" or "morethan"
    for the cut.
    Required key word arguments:
        t1      - TTree containing the "signal" species.
        t2      - TTree containing the "background" species.
        scanVar - Variable name to scan over.
        cutDir  - Direction for the cut. Must be "<" or ">".
    Optional key word arguments:
        numScanPoints - number of cuts to scan over. Defaults to 50.
        verbose       - extra verbosity flag. Defaults to true.
        name          - name for the TGraph object and for the plot.
        gfxType       - specify the graphics type for the 
        sigName       - name for the signal species.
        bkgName       - name for the background species.
    '''
    # Unpack args and determine verbosity.
    validKeys = kwargs.keys()
    verbose = True
    if ['verbose'] in validKeys:
        verbose = False
    if verbose: print '-- makeROC called!'    
    # Get all the necessary CL args first.
    # First get the trees.
    if not 't1' in validKeys:
        print 'HistPlotters ERROR: specify t1 key word argument.'
        return None
    t1 = kwargs['t1']
    if not 't2' in validKeys:
        print 'HistPlotters ERROR: specify t2 key word argument.'
        return None
    t2 = kwargs['t2']

    # Now get the variable name and check it is in each tree.
    if not 'scanVar' in kwargs.keys():
        print 'HistPlotters ERROR: specify scanVar key word argument.'
        return None
    scanVar = kwargs['scanVar']
    l1 = t1.GetListOfBranches().Clone()
    l2 = t2.GetListOfBranches().Clone()
    if not l1.Contains(scanVar):
        print 'HistPlotters ERROR: scanVar not found in t1.'
        return None
    if not l2.Contains(scanVar):
        print 'HistPlotters ERROR: scanVar not found in t2.'
        return None
    if verbose: print '-- makeROC - Scanning across variable: %s' %scanVar

    # Determine if the cut is greater than or less than.
    if not 'cutDir' in validKeys:
        print 'HistPlotters ERROR: specify cutDir key word argument.'
        return None
    cutDir = kwargs['cutDir']
    if not ( (cutDir=='<') or (cutDir=='>') ):
        print 'HistPlotters ERROR: cutDir not recognised. Please give "<" or ">".'
        return None
    
    # Now check that all the arguments given are valid keywords.
    # It's easy to get tricky to debug behaviour if you mispell an argument.
    recognisedKeyList = ['t1', 't2', 'scanVar', 'cutDir', 'name', 'gfxType',
                         'sigName', 'bkgName', 'cut1', 'cut2']
    for theKey in validKeys:
        if theKey not in recognisedKeyList:
            sys.exit('HistPlotters.plotHist ERROR: keyword "%s" not recognised.' %theKey)

    # Apply some selection to each of the species.
    cut1 = '1'
    cut2 = '1'
    if 'cut1' in validKeys:
        cut1 = kwargs['cut1']
    if 'cut2' in validKeys:
        cut2 = kwargs['cut2']
        
    # Get the total numbers in each species.
    nTot1 = float(t1.GetEntries(cut1))
    if nTot1 == 0:
        sys.exit('ERROR: no events in t1 survive preselection!')
    nTot2 = float(t2.GetEntries(cut2))
    if nTot2 == 0:
        sys.exit('ERROR: no events in t1 survive preselection!')

    # Now we need to make a list of cut values to scan over.
    # Going to assume all the tree entries I care about are not arrays for now.
    # First get the maximum and minimum of the variable.
    minValue = t1.GetMinimum(scanVar)
    if t2.GetMinimum(scanVar) < minValue:
        minValue = t2.GetMinimum(scanVar)
    maxValue = t1.GetMaximum(scanVar)
    if t2.GetMaximum(scanVar) > maxValue:
        maxValue = t2.GetMaximum(scanVar)

    # Now make a list of cut values.    
    numScanPoints = 50
    listOfValues = numpy.linspace(minValue, maxValue, numScanPoints)
    if verbose:
        print '-- makeROC - list of values in scan:'
        print listOfValues

    # Now populate a list of corresponding efficiencies of this cut
    # for each species.
    valueList1 = []
    valueList2 = []
    for cutValue in listOfValues:
        cut1Full = '(%s) && (%s %s %f)' %(cut1, scanVar, cutDir, cutValue)
        valueList1.append(t1.GetEntries(cut1Full)/nTot1)
        cut2Full = '(%s) && (%s %s %f)' %(cut2, scanVar, cutDir, cutValue)
        valueList2.append(1 - (t2.GetEntries(cut2Full)/nTot2) )

    # Now make some array.array objects.
    print '-- makeROC - cut efficiencies:'
    print valueList1
    print valueList2
    array1 = array.array('d', valueList1)
    array2 = array.array('d', valueList2)


    # Make a name for the graph.
    name  = 'ROC_%s' %(scanVar)
    
    # Sort out axes names.
    sigName = 'Signal'
    bkgName = 'Background'
    if 'sigName' in validKeys:
        sigName = kwargs['sigName']
    if 'bkgName' in validKeys:
        bkgName = kwargs['bkgName']
    name += '_%svs%s' %(sigName, bkgName)    
    # Make the TGraph and do some formatting.
    g = TGraph(len(array1), array1, array2)
    g.GetXaxis().SetTitle('%s #epsilon' %sigName)
    g.GetXaxis().SetRangeUser(0, 1)
    g.GetYaxis().SetTitle('%s (1-#epsilon)' %bkgName)
    g.GetYaxis().SetRangeUser(0, 1)

    g.GetXaxis().SetNdivisions(20)
    g.GetYaxis().SetNdivisions(10)

    g.SetLineWidth(3)
    
    # Make a name for the graph.
    #name  = 'ROC_%s' %(scanVar)

    if cutDir == '>':
        dirString = 'Min'
    elif cutDir == '<':
        dirString = 'Max'
    title = '%s %s' %(dirString, scanVar)
    #if 'name' in validKeys:
    #    name = kwargs['name']
    g.SetName(name)
    g.SetTitle(title)
    
    return g

#########################################################################
def plotROC(g):
    c = TCanvas('c', 'c', 800, 600)
    c.SetGrid()
    c.cd()
    g.Draw('AL')
    gfxType='png'
    name = g.GetName()

    # Title is always the scanVar and max/min.
    # Plot this on the plot.
    l = TPaveText(0.1, 0.1, 0.45, 0.25)
    l.AddText(g.GetTitle())
    l.SetFillColor(0)
    l.Draw()

    # Add a dashed line indicating an agnostic selection.
    line = TLine()
    line.SetLineColor(2)
    line.SetLineWidth(3)
    line.SetLineStyle(kDashed)
    line.DrawLine(0,1,1,0)
    c.SaveAs('Plot_%s.%s' %(name, gfxType))
    return None

#########################################################################
# For testing.
if __name__ == '__main__':

    from BsDsMuNuForRDS.DataRetrieval import *
    c = getProcessedChain('MC_Signal', 'MagDown')
    #c2 = getProcessedChain('MC_LbLcDs', 'MagDown')
    #g = makeROC(t1=c, t2=c2, scanVar='mu_iso_MinBDT_Long',
    #            cutDir='>', bkgName = 'B2CC', cut1=TruthCuts.isSignal)
    h1 = makeHist(chain=c, xKey='Ds_M')
    h2 = makeHist(chain=c, xKey='mu_iso_MinBDT_Long')
    plotHist(hist=h1)
    plotHist(hist=h2)
    #plotROC(g)
