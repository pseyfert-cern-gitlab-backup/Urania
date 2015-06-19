# --------------------------------------------------------------------------- #
#                                                                             #
#   Python script to plot background shapes                                   #
#                                                                             #
#   Example usage:                                                            #
#      python plotShapes.py --file work_dspi.root --work workspace            #
#                           --mode BsDsPi  --obs lab1_PIDK  --debug           #
#                                                                             #
#   Author: Agnieszka Dziurda                                                 #
#   Date  : 06 / 10 / 2013                                                    #
#                                                                             #
# --------------------------------------------------------------------------- #
# -----------------------------------------------------------------------------
# settings for running without GaudiPython
# -----------------------------------------------------------------------------
""":"
# This part is run by the shell. It does some setup which is convenient to save
# work in common use cases.

# make sure the environment is set up properly
if test -n "$CMTCONFIG" \
         -a -f $B2DXFITTERSROOT/$CMTCONFIG/libB2DXFittersDict.so \
         -a -f $B2DXFITTERSROOT/$CMTCONFIG/libB2DXFittersLib.so; then
    # all ok, software environment set up correctly, so don't need to do
    # anything
    true
else
    if test -n "$CMTCONFIG"; then
        # clean up incomplete LHCb software environment so we can run
        # standalone
        echo Cleaning up incomplete LHCb software environment.
        PYTHONPATH=`echo $PYTHONPATH | tr ':' '\n' | \
            egrep -v "^($User_release_area|$MYSITEROOT/lhcb)" | \
            tr '\n' ':' | sed -e 's/:$//'`
        export PYTHONPATH
        LD_LIBRARY_PATH=`echo $LD_LIBRARY_PATH | tr ':' '\n' | \
            egrep -v "^($User_release_area|$MYSITEROOT/lhcb)" | \
            tr '\n' ':' | sed -e 's/:$//'`
	export LD_LIBRARY_PATH
        exec env -u CMTCONFIG -u B2DXFITTERSROOT "$0" "$@"
    fi
    # automatic set up in standalone build mode
    if test -z "$B2DXFITTERSROOT"; then
        cwd="$(pwd)"
        if test -z "$(dirname $0)"; then
            # have to guess location of setup.sh
            cd ../standalone
            . ./setup.sh
            cd "$cwd"
        else
            # know where to look for setup.sh
            cd "$(dirname $0)"/../standalone
            . ./setup.sh
            cd "$cwd"
        fi
        unset cwd
    fi
fi
# figure out which custom allocators are available
# prefer jemalloc over tcmalloc
for i in libjemalloc libtcmalloc; do
    for j in `echo "$LD_LIBRARY_PATH" | tr ':' ' '` \
            /usr/local/lib /usr/lib /lib; do
        for k in `find "$j" -name "$i"'*.so.?' | sort -r`; do
            if test \! -e "$k"; then
                continue
            fi
            echo adding $k to LD_PRELOAD
            if test -z "$LD_PRELOAD"; then
                export LD_PRELOAD="$k"
                break 3
            else
                export LD_PRELOAD="$LD_PRELOAD":"$k"
                break 3
            fi
        done
    done
done
# set batch scheduling (if schedtool is available)
schedtool="`which schedtool 2>/dev/zero`"
if test -n "$schedtool" -a -x "$schedtool"; then
    echo "enabling batch scheduling for this job (schedtool -B)"
    schedtool="$schedtool -B -e"
else
    schedtool=""
fi

# set ulimit to protect against bugs which crash the machine: 2G vmem max,
# no more then 8M stack
ulimit -v $((2048 * 1024))
ulimit -s $((   8 * 1024))

# trampoline into python
exec $schedtool /usr/bin/time -v env python -O -- "$0" "$@"
"""
__doc__ = """ real docstring """
# -----------------------------------------------------------------------------
# Load necessary libraries
# -----------------------------------------------------------------------------
from B2DXFitters import *
from ROOT import *

from ROOT import RooFit
from optparse import OptionParser
from math     import pi, log
from  os.path import exists
import os, sys, gc
gROOT.SetBatch()



#------------------------------------------------------------------------------
def plotShapes( debug, fileName, workName, obs, mode, data ) :

    obsTS = TString(obs)
    modeTS = TString(mode)
    print obs
    print mode
    print fileName
    work = GeneralUtils.LoadWorkspace(TString(fileName),TString(workName),debug)
    obs   = GeneralUtils.GetObservable(work,obsTS, debug)
    t = TString(" ")

    modesDs = ["nonres", "", "phipi", "kstk", "kpipi", "pipipi"]
    ModesDs = ["NonRes", "PhiPi", "KstK", "KPiPi", "PiPiPi"]
    capDs   = ["NonRes", "#phi #pi","K*K", "K #pi #pi", "#pi #pi #pi"] 
        
    if modeTS.Contains("DsPi") == true:
        modes =["Bd2DsPi","Bs2DsstPi","Bd2DPi","Lb2LcPi","Bs2DsK"]
        color = [kBlue-8, kBlue-8, kOrange-3, kRed, kGreen+3 ]
        modes5M = "Bs2DsPi"
        modesSig = "Sig"
        style = [1,1,1,1,1]
        color5M = [kBlue-2, kWhite, kBlue-2, kBlue-2, kBlue-2, kBlue-2]
        style5M = [1,1, 2,3,6, 4]
        
        ranType = 4
        ran = 5

              
    elif modeTS.Contains("DsK") == true:
        modes = ["Bs2DsRho","Bs2DsstPi", "Lb2Dsp","Lb2Dsstp", "Bd2DK","Lb2LcK"]
        modes5M = "Bs2DsPi"
        modesSig = "Sig"
        color = [kBlue-2, kBlue-2, kYellow+1, kYellow+1, kRed, kGreen+3] 
        style = [1, 2, 1, 2, 1, 2, 1, ]
        color5M = [kBlue-2, kWhite, kBlue-2, kBlue-2, kBlue-2, kBlue-2]
        style5M = [1,1, 2,3,6,9]
        ranType = 4
        ran = 6
                                                                  
    namePrefix = "PhysBkg"
    nameSufix1  = "Pdf_m_both"
    nameSufix2  = "Tot"
    p = "_"
    pTS = TString(p)
    
    names = []
    names5M = []
    namesLatex = []
    pdf = []
    pdf5M = []
    pdfSig = []
    pdfSig2 = []
    namesLatex5M = []
    namesSig = []
        
    for m in modes:
        if m =="Bd2DK" or m == "Lb2LcK" or m == "Bd2DPi" or m == "Lb2LcPi":
            n = namePrefix+m+nameSufix1+p+nameSufix2
        else:
            n = namePrefix+m+nameSufix1+p+modesDs[0]+p+nameSufix2
        names.append(n)
        namesLatex.append(GeneralUtils.GetLabel(TString(n),true,false,false,debug))
        
    for m in modesDs:
        if m != "":
            n = namePrefix+modes5M+nameSufix1+p+m+p+nameSufix2
            s = "SigProdPDF_both_"+m
        else:
            n = ""
            s = ""
        names5M.append(n)
        namesSig.append(s)
        namesLatex5M.append(GeneralUtils.GetLabel(TString(n),false,true,false,debug))
                
    print names
    print namesLatex
    print namesLatex5M
    
    for n in names:
        print n
        pdf.append(Bs2Dsh2011TDAnaModels.GetRooAbsPdfFromWorkspace(work,TString(n), debug))

    for n in names5M:
        print n
        if n != "":
            pdf5M.append(Bs2Dsh2011TDAnaModels.GetRooAbsPdfFromWorkspace(work,TString(n), debug))
                        
    for n in namesSig:
        print n
        if n != "":
            pdfSig2.append(Bs2Dsh2011TDAnaModels.GetRooAbsPdfFromWorkspace(work,TString(n), debug))
                                
                        
    canv = []
    frame = []
    legend = []
    line = []
    line5M = []
    lhcbtext = []
    padbkg = []
    for i in range(0, ranType+5):

        nameCanv =  "can_"+str(i)
        if (i == ranType+1):
            canv.append(TCanvas(nameCanv,nameCanv, 1800,1000))
        else:
            canv.append(TCanvas(nameCanv,nameCanv, 1200,1000))
            
        if ((i == ranType+1 or i == ranType+2 )and obsTS == "lab0_MassFitConsD_M"):
            if (modeTS.Contains("DsPi") == true):
                obs.setRange(5800, 7000)
            else:
                obs.setRange(5800, 7000)
        frame.append(obs.frame())
        frame[i].SetTitle("")
        frame[i].SetLabelFont(132);
        frame[i].SetTitleFont(132);

        label = GeneralUtils.CheckObservable(obsTS,debug)
        if( modeTS.Contains("DsPi") == true and obsTS == "lab1_PIDK"):
            label = TString("bachelor -PIDK [1]")
            
        frame[i].GetXaxis().SetTitle(label.Data())
        frame[i].GetYaxis().SetTitle(' ')
        frame[i].GetXaxis().SetLabelFont( 132 );
        frame[i].GetYaxis().SetLabelFont( 132 );
        frame[i].GetXaxis().SetLabelSize( 0.04 );
        frame[i].GetYaxis().SetLabelSize( 0.04 );
        frame[i].GetXaxis().SetTitleFont( 132 );
        frame[i].GetYaxis().SetTitleFont( 132 );
        frame[i].GetXaxis().SetTitleSize( 0.04 );
        frame[i].GetYaxis().SetTitleSize( 0.04 );
        
                                         
           
        if i == ranType:
            if( obsTS == "lab2_MM"):
                legend.append(TLegend( 0.12, 0.53, 0.38, 0.88 ))
            else:
                legend.append(TLegend( 0.55, 0.53, 0.88, 0.88 ))
        elif (i == ranType+1):
            legend.append(TLegend( 0.12, 0.63, 0.42, 0.88 ))
            #legend.append(TLegend( 0.58, 0.65, 0.88, 0.88 ))
        elif (i == ranType+3 and obsTS == "lab1_PIDK"):
            if modeTS.Contains("DsPi") == true:
                legend.append(TLegend( 0.12, 0.12, 0.38, 0.38 ))
            else:
                legend.append(TLegend( 0.12, 0.12, 0.40, 0.38 ))
        else:
            if ( obsTS == "lab2_MM"):
                #legend.append(TLegend( 0.60, 0.22, 0.88, 0.32 ))
                legend.append(TLegend( 0.60, 0.15, 0.88, 0.32 ))
            else:
                #legend.append(TLegend( 0.60, 0.72, 0.88, 0.82 ))
                legend.append(TLegend( 0.60, 0.68, 0.88, 0.82 ))
        legend[i].SetTextSize(0.06)
        legend[i].SetTextFont(12)
        legend[i].SetFillColor(4000)
        legend[i].SetShadowColor(0)
        legend[i].SetBorderSize(0)
        legend[i].SetTextFont(132)

        lhcbtext.append(TLatex())
        lhcbtext[i].SetTextFont(132)
        lhcbtext[i].SetTextColor(1)
        lhcbtext[i].SetTextSize(0.06)
        lhcbtext[i].SetTextAlign(12)

        namePad =  "pad_"+str(i)
        padbkg.append(TPad(namePad, namePad,  0.005, 0.005, 0.995, 0.995))
        padbkg[i].SetBorderMode(0)
        padbkg[i].SetBorderSize(-1)
        padbkg[i].SetFillStyle(0)
        padbkg[i].SetTickx(0)
                
                                
        
    for i in range(0, ran):
        line.append(TLine())
        line[i].SetLineColor(color[i])
        line[i].SetLineWidth(4)
        line[i].SetLineStyle(style[i])

    for i in range(0,6):
        line5M.append(TLine())
        line5M[i].SetLineColor(color5M[i])
        line5M[i].SetLineWidth(2)
        line5M[i].SetLineStyle(style5M[i])
        
       
     
    canv[0].cd()
    padbkg[0].Draw()
    padbkg[0].cd()
    
    if(obsTS == "lab1_PIDK" and modeTS.Contains("DsPi") == true):
        padbkg[0].SetLogy(1)
        gStyle.SetOptLogy(1)
    padbkg[0].cd()                                                                        
    pdf[0].plotOn(frame[0], RooFit.LineColor(color[0]), RooFit.LineStyle(style[0]), RooFit.LineWidth(5))
    pdf[1].plotOn(frame[0], RooFit.LineColor(color[1]), RooFit.LineStyle(style[1]), RooFit.LineWidth(5))
    legend[0].AddEntry(line[0], namesLatex[0].Data() , "L")
    legend[0].AddEntry(line[1], namesLatex[1].Data() , "L")
    frame[0].Draw()
    legend[0].Draw("same")
    if ( obsTS == "lab2_MM"):
        lhcbtext[i].DrawTextNDC( 0.62 , 0.54, "LHCb")
    else:
        lhcbtext[i].DrawTextNDC( 0.62 , 0.84, "LHCb")
    nameSavePdf = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString("Bs2DsstPiRho.pdf")
    nameSaveRoot = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString("Bs2DsstPiRho.root")
    padbkg[0].Update()
    canv[0].Print(nameSavePdf.Data())
    canv[0].Print(nameSaveRoot.Data())
    
    if modeTS.Contains("DsPi") == true:
        for i in range(1,ranType):
            canv[i].cd()
            padbkg[i].Draw()
            padbkg[i].cd()
            
            if(obsTS == "lab1_PIDK"):
                padbkg[i].SetLogy(1)
                gStyle.SetOptLogy(1)
            padbkg[i].cd()
                                        
                        
            pdf[i+1].plotOn(frame[i],RooFit.LineColor(color[i+1]), RooFit.LineStyle(style[i+1]),  RooFit.LineWidth(5))
            legend[i].AddEntry(line[i+1], namesLatex[i+1].Data() , "L")
            frame[i].Draw()
            legend[i].Draw("same")
            if ( obsTS == "lab2_MM"):
                lhcbtext[i].DrawTextNDC( 0.62 , 0.34, "LHCb")
            else:
                lhcbtext[i].DrawTextNDC( 0.62 , 0.84, "LHCb")
            nameSavePdf = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString(modes[i+1])+TString(".pdf")
            nameSaveRoot = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString(modes[i+1])+TString(".root")
            padbkg[i].Update()
            canv[i].Print(nameSavePdf.Data())
            canv[i].Print(nameSaveRoot.Data())
                    
    else:
        canv[1].cd()
        pdf[2].plotOn(frame[1], RooFit.LineColor(color[2]), RooFit.LineStyle(style[2]), RooFit.LineWidth(5))
        pdf[3].plotOn(frame[1], RooFit.LineColor(color[3]), RooFit.LineStyle(style[3]), RooFit.LineWidth(5))
        legend[1].AddEntry(line[2], namesLatex[2].Data() , "L")
        legend[1].AddEntry(line[3], namesLatex[3].Data() , "L")
        frame[1].Draw()
        legend[1].Draw("same")
        if ( obsTS == "lab2_MM"):
            lhcbtext[1].DrawTextNDC( 0.62 , 0.34, "LHCb")
        else:
            lhcbtext[1].DrawTextNDC( 0.62 , 0.84, "LHCb")
        nameSavePdf = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString("Lb2Dsstp.pdf")
        nameSaveRoot = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString("Lb2Dsstp.root")
        canv[1].Print(nameSavePdf.Data())
        canv[1].Print(nameSaveRoot.Data())

        if ( obsTS == "lab1_PIDK" or obsTS == "lab2_MM"):
            canv[2].cd()
            pdf[4].plotOn(frame[2], RooFit.LineColor(color[4]), RooFit.LineStyle(style[4]), RooFit.LineWidth(5))
            pdf[5].plotOn(frame[2], RooFit.LineColor(color[5]), RooFit.LineStyle(style[5]), RooFit.LineWidth(5))
            legend[2].AddEntry(line[4], namesLatex[4].Data() , "L")
            legend[2].AddEntry(line[5], namesLatex[5].Data() , "L")
            frame[2].Draw()
            legend[2].Draw("same")
            if ( obsTS == "lab2_MM"):
                lhcbtext[2].DrawTextNDC( 0.62 , 0.34, "LHCb")
            else:
                lhcbtext[2].DrawTextNDC( 0.62 , 0.84, "LHCb")
            nameSavePdf = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString("BachK.pdf")
            nameSaveRoot = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString("BachK.root")
            canv[2].Print(nameSavePdf.Data())
            canv[2].Print(nameSaveRoot.Data())
            
        else:
            for i in range(2,ranType):
                canv[i].cd()
                pdf[i+2].plotOn(frame[i],RooFit.LineColor(color[i+2]), RooFit.LineStyle(style[i+2]), RooFit.LineWidth(5))
                legend[i].AddEntry(line[i+2], namesLatex[i+2].Data() , "L")
                frame[i].Draw()
                legend[i].Draw("same")
                if ( obsTS == "lab2_MM"):
                    lhcbtext[i].DrawTextNDC( 0.62 , 0.34, "LHCb")
                else:
                    lhcbtext[i].DrawTextNDC( 0.62 , 0.84, "LHCb")
                nameSavePdf = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString(modes[i+2])+TString(".pdf")
                nameSaveRoot = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString(modes[i+2])+TString(".root")
                canv[i].Print(nameSavePdf.Data())
                canv[i].Print(nameSaveRoot.Data())
                    
        canv[ranType].cd()
        legend[ranType].SetTextSize(0.05)
        lhcbtext[ranType].SetTextSize(0.05)
        frame[ranType].GetXaxis().SetLabelSize( 0.04 );
        frame[ranType].GetYaxis().SetLabelSize( 0.04 );
        frame[ranType].GetXaxis().SetTitleSize( 0.04 );
        frame[ranType].GetYaxis().SetTitleSize( 0.04 );
        namesLatex5M[0].ReplaceAll("(Non Resonant)","") 
        namesLatex5M[1] = TString("(Non Resonant)")

        pdf5M[0].plotOn(frame[ranType],RooFit.LineColor(color5M[0]), RooFit.LineStyle(style5M[0]))
        for i in range (2,6):
            pdf5M[i-1].plotOn(frame[ranType],RooFit.LineColor(color5M[i]), RooFit.LineStyle(style5M[i]))
        
        for i in range(0,6):
            legend[ranType].AddEntry(line5M[i], namesLatex5M[i].Data() , "L")
        frame[ranType].Draw()
        legend[ranType].Draw("same")
        lhcbtext[ranType].DrawTextNDC( 0.45 , 0.85, "LHCb")
        #lhcbtext[ranType].DrawTextNDC( 0.35 , 0.75, "LHCb")
        nameSavePdf = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString(modes5M)+TString(".pdf")
        nameSaveRoot = TString("template")+pTS+modeTS+pTS+obsTS+pTS+TString(modes5M)+TString(".root")
        canv[ranType].Print(nameSavePdf.Data())
        canv[ranType].Print(nameSaveRoot.Data())

    
    ###### Signal PIDK ####    
    if obsTS == "lab1_PIDK":
        canv[ranType+3].cd()
        pidpad = TPad("pidPad", "pidPad",  0.005, 0.005, 0.995, 0.995)

        pidpad.SetBorderMode(0)
        pidpad.SetBorderSize(-1)
        pidpad.SetFillStyle(0)
        pidpad.SetTickx(0);
        pidpad.Draw()
        
        if modeTS.Contains("DsPi") == true:
            pidpad.SetLogy(1)
            gStyle.SetOptLogy(1)
        pidpad.cd()
                
        
        namesLatex5M[0].ReplaceAll("(Non Resonant)","")
        namesLatex5M[1] = TString("(Non Resonant)")
                
        legend[ranType+3].SetTextSize(0.05)
        lhcbtext[ranType+3].SetTextSize(0.06)
        frame[ranType+3].GetXaxis().SetLabelSize( 0.04 );
        frame[ranType+3].GetYaxis().SetLabelSize( 0.04 );
        frame[ranType+3].GetXaxis().SetTitleSize( 0.04 );
        frame[ranType+3].GetYaxis().SetTitleSize( 0.04 );

        pdfSig2[0].plotOn(frame[ranType+3],RooFit.LineColor(color5M[0]), RooFit.LineStyle(style5M[0]))
        for i in range (2,6):
            pdfSig2[i-1].plotOn(frame[ranType+3],RooFit.LineColor(color5M[i]), RooFit.LineStyle(style5M[i]))
            
        for i in range(0,6):
            legend[ranType+3].AddEntry(line5M[i], namesLatex5M[i].Data() , "L")
        frame[ranType+3].Draw()
        legend[ranType+3].Draw("same")
        lhcbtext[ranType+3].DrawTextNDC( 0.75 , 0.85, "LHCb")
        #lhcbtext[ranType+3].DrawTextNDC( 0.35 , 0.75, "LHCb")
        pidpad.Update()
        nameSavePdf = TString("template_Signal_")+obsTS+pTS+TString(mode)+TString(".pdf")
        nameSaveRoot = TString("template_Signal_")+obsTS+pTS+TString(mode)+TString(".root")
        canv[ranType+3].Print(nameSavePdf.Data())
        canv[ranType+3].Print(nameSaveRoot.Data())
                                                                                                        
    #exit(0)
    
    canv[ranType+1].cd()
    pad1 = TPad("upperPad", "upperPad",  0.005, 0.005, 0.5, 0.99)
    
    pad1.SetBorderMode(0)
    pad1.SetBorderSize(-1)
    pad1.SetFillStyle(0)
    pad1.SetBottomMargin(0.13)
    pad1.SetTopMargin(0.99)
    pad1.SetTickx(0);
    pad1.Draw()
#    if obsTS == "lab0_MassFitConsD_M":  
#        pad1.SetLogy(1)
#        gStyle.SetOptLogy(1)
    pad1.cd()
    
    legend[ranType+1].SetTextSize(0.05)
    namesLatex5M[0].ReplaceAll("(Non Resonant)","")
    namesLatex5M[1] = TString("(Non Resonant)")
        
    fileNamesSig = []
    #dirNameSig = "/afs/cern.ch/work/a/adudziak/public/workspace/MDFitter/Signal/"
    dirNameSig = "/afs/cern.ch/work/a/adudziak/public/workspace/MDFitter/CombBkg/"
    workNameSig = "FitMeToolWS"
    workSig = []
    dataSig = []
    pullHist = []
    if obsTS == "lab0_MassFitConsD_M":
        sufSig = "Bs"
    elif obsTS == "lab2_MM":
        sufSig = "Ds"
    else:
        sufSig = ""

    sufSig == ""    
    if sufSig != "":
        if modeTS.Contains("DsPi") == true:
            midSig = "DsPi"
        else:
            midSig = "DsK"

        for m in ModesDs:
            if m !="":
                #fileNamesSig.append(dirNameSig+"WS_MC_"+midSig+"_"+m+"_"+sufSig+"_BDTGA.root")
                fileNamesSig.append(dirNameSig+"WS_CombBkg_"+midSig+"_"+m+"_"+sufSig+"_BDTGA.root")
            else:
                fileNamesSig.append("")
                
        for i in range(0,5):
            if fileNamesSig != "":
                workSig.append(GeneralUtils.LoadWorkspace(TString(fileNamesSig[i]),TString(workNameSig),debug))
                #workSig[i].factory("SUM:FullPdf(nSigEvts_both*SigEPDF_both)")
                workSig[i].factory("SUM:FullPdf(nCombBkgEvts_both*CombBkgEPDF_both)")
                dataSig.append(GeneralUtils.GetDataSet(workSig[i], TString("combData"), debug))
                pdfSig.append(workSig[i].pdf("FullPdf")) 
                print "data contains: %d"%(dataSig[i].numEntries())
                
        pullname2TS = TString("h_combData_Cut[sample==sample::both]")
        pullname3TS = TString("SigEPDF_both")
        pullnameTS = TString("FullPdf_Norm[")+obsTS+TString("]")
        frame[ranType+2].GetXaxis().SetLabelSize( 0.04 );
        frame[ranType+2].GetXaxis().SetTitleSize( 0.05 );

        dataSig[0].plotOn(frame[ranType+2],RooFit.Cut("sample==sample::both"),
                            RooFit.MarkerStyle(22), RooFit.MarkerColor(color5M[i]),
                            RooFit.Binning(20), RooFit.MarkerSize(2), RooFit.Invisible())
        
        dataSig[0].plotOn(frame[ranType+1],RooFit.Cut("sample==sample::both"),RooFit.Invisible())
        pdfSig[0].plotOn(frame[ranType+1],RooFit.LineColor(color5M[0]), RooFit.LineStyle(style5M[0]))
        pdfSig[0].plotOn(frame[ranType+2],RooFit.LineColor(color5M[0]), RooFit.LineStyle(style5M[0]), RooFit.LineWidth(2))
        pullHist.append(frame[ranType+1].pullHist(pullname2TS.Data(),pullnameTS.Data()))
         
        for i in range (2,6):
            dataSig[i-1].plotOn(frame[ranType+1],RooFit.Cut("sample==sample::both"),RooFit.Invisible())
            pdfSig[i-1].plotOn(frame[ranType+1],RooFit.LineColor(color5M[i]), RooFit.LineStyle(style5M[i]))

            scaleA = dataSig[0].sumEntries()/dataSig[i-1].sumEntries()
            dataSig[i-1].plotOn(frame[ranType+2],RooFit.Cut("sample==sample::both"),
                                RooFit.MarkerStyle(21+i), RooFit.MarkerColor(color5M[i]),
                                RooFit.Rescale(scaleA), RooFit.Binning(20), RooFit.MarkerSize(2), RooFit.Invisible())
            pdfSig[i-1].plotOn(frame[ranType+2],RooFit.LineColor(color5M[i]),
                               RooFit.LineStyle(style5M[i]), RooFit.LineWidth(2), RooFit.Normalization(scaleA))
            frame[ranType+1].Print()
            pullHist.append(frame[ranType+1].pullHist(pullname2TS.Data(),pullnameTS.Data()))
            
        for i in range(0,6):
            legend[ranType+1].AddEntry(line5M[i], namesLatex5M[i].Data() , "L")
        
        legend[ranType+1].SetTextSize(0.04)
        frame[ranType+2].Draw()
        legend[ranType+1].Draw("same")
        lhcbtext[ranType+1].DrawTextNDC( 0.72 , 0.85, "LHCb")
        #lhcbtext[ranType+1].DrawTextNDC( 0.42, 0.85, "LHCb")
        pad1.Update()
        
        canv[ranType+1].cd()
        gStyle.SetOptLogy(0)
        pad2 = []
        text = []
        frame_p = []
        graph1 = []
        graph2 = []
        graph3 = []
        x = [.5, 1.0]
        y1 = [ 0.005, 0.195, 0.385, 0.575, 0.765]
        y2 = [ 0.190, 0.380, 0.570, 0.760, 0.950]
        y  = [ ]
        for i in range (0,5):
            canv[ranType+1].cd()
            namepad = "lowerPad"+str(i)
            if i == 4:
                y1A = y1[4-i]+0.01
                y2A = y2[4-i]+0.07
            elif i == 2:
                y1A = y1[4-i]-0.03
                y2A = y2[4-i]+0.03
            elif i == 0:
                y1A = y1[4-i]-0.06
                y2A = y2[4-i]
            elif i == 1:
                y1A = y1[4-i]-0.04
                y2A = y2[4-i]+0.02
            elif i == 3:
                y1A = y1[4-i]-0.01
                y2A = y2[4-i]+0.045
                                                   
            else:
                y1A = y1[4-i]
                y2A = y2[4-i]
                
            
            '''
            if i == 4:
                y1A = y1[4-i]
            else:
                y1A = y1[4-i]-0.05
            if i == 0:
                y2A = y2[4-i]
            else:
                y2A = y2[4-i]+0.05
            '''
            pad2.append(TPad(namepad, namepad,  x[0], y1A, x[1], y2A))
            
            pad2[i].SetBorderMode(0)
            pad2[i].SetBorderSize(-1)
            pad2[i].SetFillStyle(0)
            pad2[i].SetBottomMargin(0.35)
            pad2[i].SetTickx(0);
            pad2[i].Draw()
            pad2[i].SetLogy(0)
            pad2[i].cd()

                                             
            frame_p.append(obs.frame(RooFit.Title("pull_frame")))
            frame_p[i].Print("v")
            frame_p[i].SetTitle("")
            frame_p[i].GetYaxis().SetTitle("")
            frame_p[i].GetXaxis().SetTitle(label.Data())
            frame_p[i].GetYaxis().SetTitleSize(0.09)
            frame_p[i].GetYaxis().SetTitleOffset(0.26)
            frame_p[i].GetYaxis().SetTitleFont(62)
            frame_p[i].GetYaxis().SetNdivisions(106)
            frame_p[i].GetYaxis().SetLabelSize(0.15)
            frame_p[i].GetYaxis().SetLabelOffset(0.006)
            frame_p[i].GetXaxis().SetTitleSize(0.17)
            frame_p[i].GetXaxis().SetTitleFont(132)
            frame_p[i].GetXaxis().SetTitleOffset(0.85)
            #frame_p[i].GetXaxis().SetNdivisions(5)
            frame_p[i].GetYaxis().SetNdivisions(5)
            frame_p[i].GetXaxis().SetLabelSize(0.12)
            frame_p[i].GetXaxis().SetLabelFont( 132 )
            frame_p[i].GetYaxis().SetLabelFont( 132 )
            if i != 4:
                frame_p[i].GetXaxis().SetLabelColor( kWhite)
                frame_p[i].GetXaxis().SetTitle("")
            frame_p[i].addPlotable(pullHist[i],"P")

            frame_p[i].Draw()

            axisY = pullHist[i].GetYaxis()
            max = axisY.GetXmax()
            min = axisY.GetXmin()

            range_dw = obs.getMin()
            range_up = obs.getMax()
            
            graph1.append(TGraph(2))
            graph1[i].SetMaximum(max)
            graph1[i].SetMinimum(min)
            graph1[i].SetPoint(1,range_dw,0)
            graph1[i].SetPoint(2,range_up,0)
            
            graph2.append(TGraph(2))
            graph2[i].SetMaximum(max)
            graph2[i].SetMinimum(min)
            graph2[i].SetPoint(1,range_dw,-3)
            graph2[i].SetPoint(2,range_up,-3)
            graph2[i].SetLineColor(kRed)
            
            graph3.append(TGraph(2))
            graph3[i].SetMaximum(max)
            graph3[i].SetMinimum(min)
            graph3[i].SetPoint(1,range_dw,3)
            graph3[i].SetPoint(2,range_up,3)
            graph3[i].SetLineColor(kRed)

            graph1[i].Draw("same")
            graph2[i].Draw("same")
            graph3[i].Draw("same")

            text.append(TLatex())
            text[i].SetTextFont(132)
            text[i].SetTextColor(1)
            text[i].SetTextSize(0.20)
            text[i].SetTextAlign(22)
            text[i].SetTextAngle(90)
            text[i].DrawTextNDC(0.03, 0.605, ModesDs[i])
            pad2[i].Update()
        
        canv[ranType+1].Update() 
        nameSavePdf = TString("template_CombBkg")+pTS+obsTS+pTS+TString(mode)+TString(".pdf")
        nameSaveRoot = TString("template_CombBkg")+pTS+obsTS+pTS+TString(mode)+TString(".root")
        canv[ranType+1].Print(nameSavePdf.Data())
        canv[ranType+1].Print(nameSaveRoot.Data())

    if obsTS == "lab1_PIDK":
        p
        canv[ranType+4].cd()
        pidcomb = TPad("pidcombPad", "pidcombPad",  0.005, 0.005, 0.995, 0.995)
        
        pidcomb.SetBorderMode(0)
        pidcomb.SetBorderSize(-1)
        pidcomb.SetFillStyle(0)
        pidcomb.SetTickx(0);
        pidcomb.Draw()
        
        if modeTS.Contains("DsPi") == true:
            pidcomb.SetLogy(1)
            gStyle.SetOptLogy(1)
        pidcomb.cd()
        
        colorComb = [kBlue-2, kBlue-2, kBlue-2, kBlue-2, kBlue-2, kBlue-2]
        styleComb = [1,2,3,6,9]
        
                
        if modeTS.Contains("DsPi") == true:
            combNames = ["PIDKShape_Comb_both","PIDKShape_CombK_both"]
            size = 2
        else:
            combNames = ["PIDKShape_CombPi_both","PIDKShape_CombK_both","PIDKShape_CombP_both"]
            size = 3
            
        combLegend = ["Combinatorial pion component",
                      "Combinatorial kaon component",
                      "Combinatorial proton component"]

        lineComb = []
        for i in range(0, size):
            lineComb.append(TLine())
            lineComb[i].SetLineColor(colorComb[i])
            lineComb[i].SetLineWidth(4)
            lineComb[i].SetLineStyle(styleComb[i])
            
        
        pdfcomb = []
        for i in range(0,size):
            pdfcomb.append(Bs2Dsh2011TDAnaModels.GetRooAbsPdfFromWorkspace(work,TString(combNames[i]), debug))

        legendComb = TLegend( 0.20, 0.72, 0.88, 0.88 )
        legendComb.SetTextSize(0.06)
        legendComb.SetTextFont(12)
        legendComb.SetFillColor(4000)
        legendComb.SetShadowColor(0)
        legendComb.SetBorderSize(0)
        legendComb.SetTextFont(132)
        legendComb.SetTextSize(0.05)

        lhcbtext[ranType+4].SetTextSize(0.06)
        frame[ranType+4].GetXaxis().SetLabelSize( 0.04 );
        frame[ranType+4].GetYaxis().SetLabelSize( 0.04 );
        frame[ranType+4].GetXaxis().SetTitleSize( 0.04 );
        frame[ranType+4].GetYaxis().SetTitleSize( 0.04 );
        
        for i in range (0,size):
            pdfcomb[i].plotOn(frame[ranType+4],RooFit.LineColor(colorComb[i]), RooFit.LineStyle(styleComb[i]))
             
        for i in range(0,size):
            legendComb.AddEntry(lineComb[i], combLegend[i] , "L")

            
        frame[ranType+4].Draw()
        if modeTS.Contains("DsPi") == true:
            frame[ranType+4].GetYaxis().SetRangeUser(0.005,frame[ranType+4].GetMaximum()*1.0)
        legendComb.Draw("same")
        
        lhcbtext[ranType+4].DrawTextNDC( 0.76 , 0.70, "LHCb")
        #lhcbtext[ranType+3].DrawTextNDC( 0.35 , 0.75, "LHCb")
        pidcomb.Update()
        nameSavePdf = TString("template_CombBkg_")+obsTS+pTS+TString(mode)+TString(".pdf")
        nameSaveRoot = TString("template_CombBkg_")+obsTS+pTS+TString(mode)+TString(".root")
        canv[ranType+4].Print(nameSavePdf.Data())
        canv[ranType+4].Print(nameSaveRoot.Data())
        
                
#------------------------------------------------------------------------------
_usage = '%prog [options]'

parser = OptionParser( _usage )

parser.add_option( '-d', '--debug',
                   action = 'store_true',
                   dest = 'debug',
                   default = False,
                   help = 'print debug information while processing'
                   )

parser.add_option( '--file',
                   dest = 'file',
                   default = 'WS_Mass_DsPi_5M_BDTGA.root')

parser.add_option( '--work',
                   dest = 'work',
                   default = 'FitMeToolWS')
parser.add_option( '--obs',
                   dest = 'obs',
                   default = 'lab1_PIDK')
parser.add_option( '--mode',
                   dest = 'mode',
                   default = 'BsDsPi')

parser.add_option( '--data',
                   dest = 'data',
                   action = 'store_true',
                   default = False)


# -----------------------------------------------------------------------------

if __name__ == '__main__' :
    ( options, args ) = parser.parse_args()
    
    if len( args ) > 0 :
        parser.print_help()
        exit( -1 )
        
        
    import sys
    sys.path.append("../data/")

    plotShapes( options.debug,
                options.file, options.work, 
                options.obs, options.mode,
                options.data
                )                                
# -----------------------------------------------------------------------------
                                
