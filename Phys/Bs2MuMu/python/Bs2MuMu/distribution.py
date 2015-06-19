from ROOT import *
from array import array as afC
from triggerTools import *

def do_distribution(t, fiter, var, bins, cuts, mass="Bmass", weight_var = 0, first = 0, tsel = 0):
    h = TH1F(var, var, len(bins)-1, afC('f',bins))
    #f = TFile("eraseme","recreate")
    if tsel and first:
        print "ERROR"
        return 
    
    for i in range(len(bins)-1):
        x0 = bins[i]
        x1 = bins[i+1]
        ct = cuts + " && "+ var + " > " + str(x0) + " && " +  var + "< " + str(x1)
       # print ct
       
        op = fiter(t, mass, ct, weight_var)
        N = op.nsig.getVal()
        sN = op.nsig.getError()

        h.SetBinContent(i+1,N)
        h.SetBinError(i+1,sN)
        h.SetMinimum(0)
        if first:
            op = fiter(t,mass,cuts,weight_var)
            N,sN2 = 0, 0
            for i in range(2,h.GetNbinsX()+1):
                N+= h.GetBinContent(i)
                sN2 += h.GetBinError(i)
        
            h.SetBinContent(1, op.nsig.getVal()-N)
            print "Error on first bin is not fully correct"
            h.SetBinError(1, sqrt(op.nsig.getError() **2 + sN2))
        if tsel:
            op = fiter(t,mass,cuts + "&& DOCA<0.06 && Bips<3 && lessIPSmu>9 && Bdissig>25",weight_var)
            eff = 0.61*.68/.65
            N, sN2 = 0, 0 
            for i in range(2,h.GetNbinsX()+1):
                N+= h.GetBinContent(i)
                sN2 += h.GetBinError(i)
            h.SetBinContent(1, op.nsig.getVal()/eff-N)
            print "Error on first bin is not fully correct"
            h.SetBinError(1, sqrt(op.nsig.getError() **2/(eff**2) + sN2))
            
    return h


def do_trigger_bias(t, fiter, var, bins, cuts, mass="Bmass", weight_var = 0, TIS = "(L0Tis && Hlt1Tis)", TOS = "(L0Tos && Hlt1Tos)", first = 0, tsel = 0):
    print "Very rough errors"

    h = do_distribution(t, fiter, var, bins, cuts, mass, weight_var , first, tsel)
    htis = do_distribution(t, fiter, var, bins, cuts + "&& " + TIS, mass, weight_var, first, tsel )
    htos = do_distribution(t, fiter, var, bins, cuts + "&& " + TOS, mass, weight_var , first, tsel)
    htistos = do_distribution(t, fiter, var, bins, cuts + "&& " + TIS + "&&" + TOS, mass, weight_var , first, tsel)

    out = h.Clone()

    out.Divide(htis)
    out.Divide(htos)
    
    for i in range(out.GetNbinsX()):
        out.SetBinContent(i+1, out.GetBinContent(i+1)*htistos.GetBinContent(i+1))
        out.SetBinError(i+1, out.GetBinContent(i+1)*htistos.GetBinError(i+1)*1./htistos.GetBinContent(i+1))    
    return out
    
    
def vs_mc(t,tmc, fiter, var, bins, cuts, mass="Bmass", weight_var = 0, first = 0, cutsInMC = 1, tsel= 0):
    c = TCanvas()
    h = do_distribution(t, fiter, var, bins, cuts, mass, weight_var, first, tsel)
    hmc = TH1F(var + "MC", var+"MC", len(bins)-1, afC('f',bins))
    
    if cutsInMC:
        f2 = TFile("eraseme","recreate")
        tmc2 = tmc.CopyTree(cuts)
    else: tmc2 = tmc
    for entry in tmc2:
        hmc.Fill(getattr(tmc, var))
    hmc.SetLineColor(kRed)
    hmc.Scale(h.GetSum()*1./hmc.GetSum())
    f2.Close()
    c.Divide(2,1)
    c.cd(1)
    h.Draw()
    hmc.Draw("same")
    h2 = h.Clone()
    h2.Divide(hmc)
    c.cd(2)
    h2.Draw()
    return c, h ,hmc, h2
               


def do_tis_eff(t, fiter, var, bins, cuts, mass="Bmass", weight_var = 0, TIS = "(L0Tis && Hlt1Tis)", TOS = "(L0Tos && Hlt1Tos)", first = 0, tsel = 0):
    print "Very rough errors"

    #h = do_distribution(t, fiter, var, bins, cuts, mass, weight_var , first, tsel)

    #htis = do_distribution(t, fiter, var, bins, cuts + "&& " + TIS, mass, weight_var, first, tsel )
    htos = do_distribution(t, fiter, var, bins, cuts + "&& " + TOS, mass, weight_var , first, tsel)
    htistos = do_distribution(t, fiter, var, bins, cuts + "&& " + TIS + "&&" + TOS, mass, weight_var , first, tsel)

    out = htistos.Clone()

    #out.Divide(htis)
    out.Divide(htos)
    
    #for i in range(out.GetNbinsX()):
     #   out.SetBinContent(i+1, out.GetBinContent(i+1)*htistos.GetBinContent(i+1))
      #  out.SetBinError(i+1, out.GetBinContent(i+1)*htistos.GetBinError(i+1)*1./htistos.GetBinContent(i+1))    
    return out, htos, htistos

def distribution_by_tck(t, fiter, var, bins, cuts, mass="Bmass", weight_var = 0, first = 0, tsel = 0):
    tcks = []
    for entry in t:
        if entry.TCK not in tcks: tcks.append(entry.TCK)

    out = {}
    for tck in tcks:
        out[tck] = do_distribution(t,fiter,var,bins,cuts + "&& TCK == " + str(tck), mass, weight_var, first, tsel)
        out[tck].GetXaxis().SetTitle(cnvTCK(tck) + "_" + str(int(round(out[tck].GetSum()))))
    return out
