from ROOT import *
gROOT.SetBatch(True)
from readData import *
from array import *
import cutStrings as cs
from valAndErr import *




# a) Read in the histograms with MuPlus and MuMinus GO efficiencies
# b) Read in the histogram with Bsmm signal, apply fiducial cuts
# c) Loop over the events in the histogram and add weights
# d) Sum over weights and get the weighted average GP MuMu efficiency

#Global variables
directory = 'GPEff'
cutPlus = 'GP_MuPlus_03'
cutMinus = 'GP_MuMinus_03'
varsPlus = ['muplus_PT', 'muplus_PZ']
varsMinus = ['muminus_PT', 'muminus_PZ']
nBins = [6,4]

def weighGPeff(nTuple, MCname = 'MC2012_BsMuMu'):

    outputFile= directory + '/' + nTuple +'_MuMu_nBins_muonpT_'+str(nBins[0])+'_muonpZ_'+str(nBins[1])+'_cutEff_WEIGHED.txt'

    #Read in the MuPlus and MuMinus eff hists and return a multiplied histogram
    fPlusName = nTuple +'_cut_'+cutPlus+'_nBins_'+varsPlus[0]+'_'+str(nBins[0])+'_'+varsPlus[1]+'_'+str(nBins[1])+'_cutEff.root'
    fMinusName = nTuple +'_cut_'+cutMinus+'_nBins_'+varsMinus[0]+'_'+str(nBins[0])+'_'+varsMinus[1]+'_'+str(nBins[1])+'_cutEff.root'

    fPlus  = TFile(directory+'/'+fPlusName)
    fMinus = TFile(directory+'/'+fMinusName)

    hPlus= fPlus.Get('hist_eff')
    hMinus= fMinus.Get('hist_eff')

    hMuMu = hPlus.Clone()
    hMuMu.Multiply(hMinus)

    # Print before and after multiplying
    for x in range(nBins[0]):
        x+=1
        for y in range(nBins[1]):
           y+=1
           val = hPlus.GetBinContent(x,y)
           e_hi = hPlus.GetBinErrorUp(x,y)
           e_lo = hPlus.GetBinErrorLow(x,y)
           print '        MuPlus   : [%i,%i]: %.5f (+%.5f /- %.5f)' % (x,y,val,e_hi,e_lo)
           val = hMinus.GetBinContent(x,y)
           e_hi = hMinus.GetBinErrorUp(x,y)
           e_lo = hMinus.GetBinErrorLow(x,y)
           print '        MuMinus  : [%i,%i]: %.5f (+%.5f /- %.5f)' % (x,y,val,e_hi,e_lo)
           val = hMuMu.GetBinContent(x,y)
           e_hi = hMuMu.GetBinErrorUp(x,y)
           e_lo = hMuMu.GetBinErrorLow(x,y)
           print '        MuMu     : [%i,%i]: %.5f (+%.5f /- %.5f)' % (x,y,val,e_hi,e_lo)

    #Get the binning from the histograms
    binning_x = []
    binning_y = []
    binning_x.append(hMuMu.GetXaxis().GetBinLowEdge(1))
    binning_y.append(hMuMu.GetXaxis().GetBinLowEdge(1))

    for x in range(nBins[0]):
        x+=1
        binning_x.append(hMuMu.GetXaxis().GetBinUpEdge(x))
    for y in range(nBins[1]):
        y+=1
        binning_y.append(hMuMu.GetYaxis().GetBinUpEdge(y))

    print ' Bins for x: ', binning_x
    print ' Bins for y: ', binning_y

    #-----------------------------------------------------#
    h_eff =  hMuMu

    #Get hist after fid cuts, take N_events
    d = readData(MCname, {'channel':'Bmumu'})
    t_raw = d.get('tree')
    n_raw = valAndErr(t_raw.GetEntries(),'P')
    print '  Before cutting: ', n_raw.getVal()


    #Define the fiducial cuts
    #fidcut = cs.minimalNormBu_lnf
    fidcut = cs.bsmumu_cuts
    print ' >> CUT:', fidcut

    # Draw events on muPlus_pT and pZ grid
    h_sig_plus = TH2F("h_sig_plus", "n_fid", len(binning_x)-1, array('d',binning_x), len(binning_y)-1, array('d',binning_y))
    t_raw.Draw(str(varsPlus[1]) + ':'+ str(varsPlus[0]) + ' >> h_sig_plus' , fidcut )
    # Draw events on muminus_pT and pZ grid
    h_sig_minus = TH2F("h_sig_minus", "n_fid", len(binning_x)-1, array('d',binning_x), len(binning_y)-1, array('d',binning_y))
    t_raw.Draw(str(varsMinus[1]) + ':'+ str(varsMinus[0]) + ' >> h_sig_minus' , fidcut )

    #Get the yields after fiducial cuts
    n_sig_plus = valAndErr(h_sig_plus.GetEntries(),'P')
    print ' h_sig_plus content after cutting:', h_sig_plus.GetEntries()
    n_sig_minus = valAndErr(h_sig_minus.GetEntries(),'P')
    print ' h_sig_minus content after cutting:', h_sig_minus.GetEntries()

    #Multiply it with the efficiency, get the N_events
    hists = [h_sig_plus, h_sig_minus]


    #Loop over bins and do the multiplication
    sum_effsig_loop = []  #The sum of eff*sig in the hist
    for i,h in enumerate(hists):
        sum_effsig = valAndErr(0,0)
        for x in range(nBins[0]):
            x+=1
            for y in range(nBins[1]):
                y+=1
                n_fid = valAndErr(h.GetBinContent(x,y), h.GetBinError(x,y))
                eff_gp = valAndErr(h_eff.GetBinContent(x,y), h_eff.GetBinError(x,y))
                sum_i = eff_gp.times(n_fid)
                print '   For [%s,%s]: sum_i = %.3e +- %.3e' % (x,y,sum_i.getVal() , sum_i.getErr())
                sum_effsig = sum_effsig.plus(sum_i)
                print ' Sum so far:', sum_effsig.getVal()
        #Add the sum for the hist to the list
        sum_effsig_loop.append(sum_effsig)
    print ' Sum loop array:', sum_effsig_loop

    #Calculate efficiency
    eff_plus= sum_effsig_loop[0].over(n_sig_plus,True)
    eff_minus= sum_effsig_loop[1].over(n_sig_minus,True)
    eff_av = eff_plus.plus(eff_minus).over(valAndErr(2,0))

    #Store the results in a txt file
    f = open(outputFile,'w')
    print >> f, ' nTuple for the weighing:', nTuple
    print >> f, ' .root efficiency table(muPlus) :', fPlusName
    print >> f, ' .root efficiency table(muMinus) :', fMinusName
    print >> f, ' MC signal to be weighed with:', MCname
    print >> f, '  ----------------'
    print >> f, '   Raw number of events before cutting: ', n_raw.getVal()
    print >> f, '   Fiducial cut applied:' , fidcut
    print >> f, '   Number of events after cutting(muplus pTpZ axis)    : ', n_sig_plus.getVal()
    print >> f, '   Number of events after cutting(muminus pTpZ axis)   : ', n_sig_minus.getVal()
    print >> f, '       ..supposed to be the same    '
    print >> f, '  ----------------'
    print >> f, '   Compare TH1.Multiply against looping over events'
    print >> f, '   MuPlus grid:'
    print >> f, '     Looping gives sum eff*sig: %f +- %f'% (sum_effsig_loop[0].getVal(), sum_effsig_loop[0].getErr())
    print >> f, '  ----------------'
    print >> f, '   MuMinus grid:'
    print >> f, '     Looping gives sum eff*sig: %f +- %f'% (sum_effsig_loop[1].getVal(), sum_effsig_loop[1].getErr())
    print >> f, ' ---------------------- '
    print >> f, '   The average weighed efficiency eff = sum(n_i*eff_i) / N_afterFidCut :'
    print >> f, '   MuPlus grid:'
    print >> f, '      (Looping)        Eff: %.5e +- %.5e' % (eff_plus.getVal(), eff_plus.getErr())
    print >> f, '   MuMinus grid:'
    print >> f, '      (Looping)        Eff: %.5e +- %.5e' % (eff_minus.getVal(), eff_minus.getErr())
    print >> f, ' ---------------------- '
    print >> f, '   Using the average eff of the two (muMinus and muPlus phace space binning)'
    print >> f, '   Average Weighted GP Eff: %.5e +- %.5e' % (eff_av.getVal(),eff_av.getErr())
    print >> f, ' ---------------------- '
    return 0


