from ROOT import *
import time

#==============================
def Example1DPlot(colored = 1, stacked = 0):
    #
    # Call LHCb style file
    #
    gROOT.ProcessLine(".x lhcbStyle.C")
    
    #
    # Make some example histograms to use for plot
    #
    
    # define a function 
    myFunc1 = TF1("myFunc1","gaus(0)",0,10)
    
    # fill three 1D histograms
    myFunc1.SetParameters(10,4,1);
    h1fa = TH1F("h1fa","Example Plot A",20,0,10)
    h1fa.FillRandom("myFunc1",1050)
    
    myFunc1.SetParameters(9,3.9,0.9);
    h1fb = TH1F("h1fb","Example Plot B",20,0,10);
    h1fb.FillRandom("myFunc1",900);
    
    myFunc1.SetParameters(2,2,2);
    h1fc = TH1F("h1fc","Example Plot C",20,0,10);
    h1fc.FillRandom("myFunc1",1000);
    
    myFunc1.SetParameters(3,3,0.5);
    h1fd = TH1F("h1fd","Example Plot D",20,0,10);
    h1fd.FillRandom("myFunc1",100);
    
    #
    # The example plot
    #

    # Root fill colours and hatch styles at 
    # http://root.cern.ch/root/html/TAttFill.html#F1
    if (colored == 0):
        # black and white
        h1fb.SetFillColor(kGray+1);
        h1fc.SetFillColor(kGray+2);
        h1fd.SetFillColor(kGray+3);
    elif (colored == 1):
        # 'Primary' colors:
        h1fb.SetFillColor(kYellow-7);
        h1fc.SetFillColor(kGreen-7);
        h1fd.SetFillColor(kBlue-7);    
    
    # create canvas
    canvasWidth  = 400
    canvasHeight = 300
    c1 = TCanvas("c1","Canvas",canvasWidth,canvasHeight)
    
    # Stacked:
    if (stacked == 1):
        h1fa.Add(h1fc)
        h1fa.Add(h1fd)
        h1fb.Add(h1fc)
        h1fb.Add(h1fd)
        h1fc.Add(h1fd)
        h1fb.SetMaximum(350.) # set y maximum
    else:    
        h1fb.SetMaximum(250.) # set y maximum
    
    # Axis Titles
    h1fb.GetXaxis().SetTitle("#font[12]{m}(#font[12]{D}^{+}#pi^{#font[122]{-}}) [GeV/#font[12]{c}^{2}]")
    h1fb.GetYaxis().SetTitle("Entries / (0.5 GeV/#font[12]{c}^{2})")
    
    # Draw plots 
    # options described at http://root.cern.ch/root/html/THistPainter.html#HP01b
    h1fb.Draw("")
    h1fc.Draw("same")
    h1fd.Draw("same")
    h1fa.Draw("P0E1same")
    h1fa.Draw("P0Esame") # error bar through marker 
    h1fa.Draw("sameaxis")  # sameaxis: redraw axis hidden by the fill area

    # Don't hide the components:
    h1fb.SetFillStyle(0);
    h1fc.SetFillStyle(0);
    h1fd.SetFillStyle(0);
    h1fb.DrawCopy("SAME");
    h1fc.DrawCopy("SAME");
    h1fd.DrawCopy("SAME");

    # Put fill style back for the legend:
    h1fb.SetFillStyle(1001);
    h1fc.SetFillStyle(1001);
    h1fd.SetFillStyle(1001);
 
    # Write 'LHCb' label:
    lhcbName.Draw()
    
    # Example of adding a legend to plot
    # http://root.cern.ch/root/html528/TLegend.html#TLegend
    legend = TLegend(0.65,0.65,0.92,0.92)
    legend.SetFillColor(0)
    legend.SetTextSize(0.055)
    legend.AddEntry(h1fa, "Data", "P")
    legend.AddEntry(h1fb, "#font[12]{B^{0}_{s}#rightarrow D_{s}^{#font[122]{-}}K^{+}}", "F")
    legend.AddEntry(h1fc, "Background 1", "F")
    legend.AddEntry(h1fd, "Background 2", "F")
    legend.Draw("same")
    
    # update canvas
    c1.Update()
    
    # write out .pdf
    filename='Example1DPlot-python-'+str(colored)+'.pdf'
    c1.SaveAs(filename)
    time.sleep(10.)
  
    return

#==========================
def ExampleMultiplePlots():
    #
    # Call LHCb style file
    #
    gROOT.ProcessLine(".x lhcbStyle.C")

    # Reduce linewidth for multi-figure:
    lhcbStyle.SetLineWidth(1)


    # define a function 
    myFunc1 = TF1("myFunc1","gaus(0)",0,10)
    
    # fill three 1D histograms
    myFunc1.SetParameters(10,4,1);
    h1fa = TH1F("h1fa","Example Plot A",20,0,10)
    h1fa.FillRandom("myFunc1",1100)

    # create canvas
    canvasWidth  = 600
    canvasHeight = 450

    c2 = TCanvas("c2","multipads",canvasWidth,canvasHeight)
    npx   = 3
    npy   = 3 
    npads = npx*npy

    # First, make one large pad to allow fpr space for axis titles:
    pad = TPad("pad","pad", 0.07, 0.07, 0.95, 0.95)
    # Subdivide the pad, with no space between the pads:
    pad.Divide(npx,npy,0,0)
    pad.Draw()

    # Best is to make titles ourselves:
    tyax = TLatex(0.06, 0.52, "Entries / (0.5 GeV/#font[12]{c}^{2})")
    tyax.SetNDC(kTRUE)    
    tyax.SetTextSize(0.05)      
    tyax.SetTextAngle(90.)
    tyax.Draw()
    txax = TLatex( 0.68, 0.03, "#font[12]{m}(#font[12]{D}^{+}#pi^{#font[122]{-}}) [GeV/#font[12]{c}^{2}]")
    txax.SetNDC(kTRUE)    
    txax.SetTextSize(0.05)      
    txax.Draw()      

    # Prepare the labels (a), (b), etc:
    labelList = []
    labelList.append(TLatex(0.,0.,"(a)"))
    labelList.append(TLatex(0.,0.,"(b)"))
    labelList.append(TLatex(0.,0.,"(c)"))
    labelList.append(TLatex(0.,0.,"(d)"))
    labelList.append(TLatex(0.,0.,"(e)"))
    labelList.append(TLatex(0.,0.,"(f)"))
    labelList.append(TLatex(0.,0.,"(g)"))
    labelList.append(TLatex(0.,0.,"(h)"))
    labelList.append(TLatex(0.,0.,"(i)"))

    # Define edges of the histogram:
    x1=h1fa.GetXaxis().GetXmin()
    x2=h1fa.GetXaxis().GetXmax()  
    dx=x2-x1
    y1=h1fa.GetMinimum()
    y2=h1fa.GetMaximum()    
    dy=y2-y1

    # Plot the plots:
    for ipad in range(0,npads):
        pad.cd(ipad+1)
        #gPad.SetTickx(0)
        #gPad.SetTicky(0)
        icol = ipad % npx
        irow = ipad / npx

        # We need 'pixel font' to ensure same size of labels/titles in multipad!
        h1fa.SetMaximum(299.)
        h1fa.GetXaxis().SetLabelFont(133)    
        h1fa.GetXaxis().SetLabelSize(15)    
        h1fa.GetYaxis().SetLabelFont(133)    
        h1fa.GetYaxis().SetLabelSize(15)    
        h1fa.GetYaxis().SetNdivisions(410) # Reduce the number ot ticks
        h1fa.SetLineWidth(1)  
        h1fa.SetMarkerSize(0.7)  
        h1fa.GetXaxis().SetTitleSize(0.0) # Only write title for top/right pads
        h1fa.GetYaxis().SetTitleSize(0.0) # Only write title for top/right pads

        # Hack the limits of the axis to avoid 'half-cut-off' labels:
        if (irow == (npx-1)):
            h1fa.SetMinimum(y1)      
        else :
            h1fa.SetMinimum(y1+1.E-5*dy)

        if (icol == 0):
            h1fa.GetXaxis().SetLimits(x1,         x2-1.E-5*dx)
        else :
            h1fa.GetXaxis().SetLimits(x1+1.E-5*dx,x2-1.E-5*dx)

        # Draw your plot:
        h1fa.DrawCopy("P0E1");

        tekst = labelList[ipad]
        tekst.SetTextFont(133)    
        tekst.SetTextSize(15)    
        tekst.SetX(x1+0.80*dx)
        tekst.SetY(y1+1.10*dy)    
        tekst.Draw()


    # update canvas
    c2.Update()
    
    # write out .pdf
    c2.SaveAs("ExampleMultipad-python.pdf")
    time.sleep(10.)

    return

#-------------------------------------------------------------------

Example1DPlot(1,0)
ExampleMultiplePlots() 
