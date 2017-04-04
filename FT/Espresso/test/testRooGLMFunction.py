import ROOT
from ROOT import *
from ROOT import RooFit

import Espresso
from Espresso import *

gROOT.SetBatch(True)

def printSomeVals(calib, eta):
    print "===> Some values for "+str(calib.GetName())
    eta.setVal(0.1)
    print "eta=0.1 => omega = "+str(calib.getVal())
    eta.setVal(0.2)
    print "eta=0.2 => omega = "+str(calib.getVal())
    eta.setVal(0.3)
    print "eta=0.3 => omega = "+str(calib.getVal())
    eta.setVal(0.4)
    print "eta=0.4 => omega = "+str(calib.getVal())
    eta.setVal(0.45)
    print "eta=0.45 => omega = "+str(calib.getVal())
    eta.setVal(0.499)
    print "eta=0.499 => omega = "+str(calib.getVal())

if __name__ == '__main__':

    #Create calibration
    eta = RooRealVar("eta","#eta",0.04,0.5)
    calName = "OS_Combination_Calibration"
    calFileName = "OS_Combination_Calibration_NSpline_RLogitLink.xml"
    glm = ROOT.Espresso.GLMBuilder("OS","OS",eta,calName,calFileName)
    coeffs = glm.coefficients()
    deltacoeffs = glm.delta_coefficients()
    constraint = glm.covariance_matrix()
    eta_b = glm.b_mistag()
    eta_bbar = glm.bbar_mistag()
    
    printSomeVals(eta_b, eta)
    printSomeVals(eta_bbar, eta)
    
    #Make plot
    f = eta.frame(RooFit.Title("Calibration plots"))
    eta_b.plotOn(f)
    eta_bbar.plotOn(f,RooFit.LineColor(kRed))
    c = TCanvas("testRooGLMFunction","testRooGLMFunction",800,600)
    c.cd()
    f.Draw()
    c.SaveAs("testRooGLMFunction.png","png")
    
    #############################################################################
    #Generate a calibrated mistag distribution starting with a non-calibrated one
    #############################################################################

    #Import histogam PDF for eta (was generated from sWeighted Bd->Dpi data)
    file = TFile.Open("templates_mistag.root")
    workspace = file.Get("workspace")
    etadist = workspace.pdf("eta_pdf")
    print "===> Uncalibrated mistag pdf"
    etadist.Print("v")

    #Generate eta distribution
    obs = RooArgSet(eta)
    nEvts = 50000
    data_uncalib = etadist.generate(obs,
                                    nEvts,
                                    RooFit.Name("data_uncalib"),
                                    RooFit.AutoBinned(False))
    
    #Add toy tagging decision (+1 or -1 with 50% probability each)
    tagdec = RooCategory("tagdec", "d")
    tagdec.defineType("bbar",-1)
    tagdec.defineType("b",1)
    generator = TRandom3(7326495)
    dec_obs = RooArgSet(tagdec)
    dec_data = RooDataSet("dec_data","dec_data",dec_obs)
    for evt in range(0, nEvts):
        r = generator.Uniform(0.0,1.0)
        if r<0.5:
            dec_obs.find("tagdec").setIndex(-1)
        else:
            dec_obs.find("tagdec").setIndex(+1)
        dec_data.add( dec_obs )

    data_uncalib.merge( dec_data )
    print "===> Uncalibrated mistag distribution:"
    data_uncalib.Print("v")
    
    #Generate calibrated mistag distribution
    obs.add(tagdec)
    data_calib = RooDataSet("data_calib","data_calib",obs)
    for evt in range(0, nEvts):
        decval = data_uncalib.get(evt).getCatIndex("tagdec")
        etaval = data_uncalib.get(evt).getRealValue("eta")
        obs.find("eta").setVal(etaval)
        obs.find("tagdec").setIndex(decval)
        if decval < 0:
            obs.find("eta").setVal( glm.b_mistag().getVal() )
        else:
            obs.find("eta").setVal( glm.bbar_mistag().getVal() )
        data_calib.add( obs )
    print "===> Calibrated mistag distribution:"
    data_uncalib.Print("v")

    #Plot original and calibrated distributions
    f = eta.frame(RooFit.Title("Mistag distributions (calibrated vs uncalibrated)"))
    data_uncalib.plotOn(f)
    data_calib.plotOn(f,RooFit.MarkerColor(kRed),RooFit.LineColor(kRed))
    c = TCanvas("testMistagPlot","testMistagPlot",800,600)
    c.cd()
    f.Draw()
    c.SaveAs("testMistagPlot.png","png")

    ######
    #Done!
    ######
    
    #Play with coefficients (just to check that we can "act" on them)
    print "===> Modify randomly some coefficients..."
    for i in range(0, glm.coefficients().getSize()):
        glm.coefficients().at(i).setVal(0.01)
        glm.coefficients().at(i).setConstant(True)
        glm.delta_coefficients().at(i).setVal(0.01)
        glm.delta_coefficients().at(i).setConstant(True)
        
    printSomeVals(eta_b, eta)
    printSomeVals(eta_bbar, eta)
        
    #Plot again
    f = eta.frame(RooFit.Title("Calibration plots"))
    eta_b.plotOn(f)
    eta_bbar.plotOn(f,RooFit.LineColor(kRed))
    c = TCanvas("testRooGLMFunctionAfter","testRooGLMFunctionAfter",800,600)
    c.cd()
    f.Draw()
    c.SaveAs("testRooGLMFunctionAfter.png","png")
    
