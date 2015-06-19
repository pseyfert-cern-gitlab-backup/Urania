#!/usr/bin/env python

#import os
#os.environ['ROOTSYS'] = '/afs/cern.ch/sw/lcg/app/releases/ROOT/5.28.00b/x86_64-slc5-gcc43-opt/root'

from ROOT  import TH1F, THStack, TCanvas, TFile, TFrame, TRandom2, TSystem
from ROOT  import TVector, TObjArray, TObjString, TLimit, TLimitDataSource
from ROOT  import TConfidenceLevel, kBlue, gSystem, TGraph, TVectorD, gROOT
from ROOT  import TLegend, TGraphAsymmErrors, TLine, TPaveText, TTree
from ROOT  import AddressOf, TF1, TFeldmanCousins, THStack

from array import array
from numpy.random import poisson, multinomial, normal, randn

from math import sqrt, exp, ceil, floor
import cPickle, sys

from datetime import date
datestamp = date.today().strftime('%Y%m%d')


from ROOT_settings_marco import *
#gROOT.ProcessLine(".x lhcbstyle.C")


def distribution_1BF( bf, list_of_dic, list_name='list_CLs', n_bins=100):
    
    
    list_val = []
    for item in list_of_dic:
        if item['BF'] == bf:
            list_val[:] = item[list_name][:]
    
    #print 
    histo = TH1F( 'histo', 'histo', n_bins, min(list_val), max(list_val) )
    for cl in list_val:
        histo.Fill( cl )
    
    return histo

def do_lhcb_label(x1,y1,x2,y2, prelim=False):
    l = TPaveText()
    l.SetTextSize(0.07)
    if prelim:
        l.AddText("#splitline{LHCb}{Preliminary}")
    else:
        l.AddText("LHCb")
    l.SetX1NDC(x1)
    l.SetY1NDC(y1)
    l.SetX2NDC(x2)
    l.SetY2NDC(y2)
    l.SetFillColor(0)
    l.SetFillStyle(0)
    l.SetBorderSize(0)
    return l.Clone()

def AlaCDF(bf_all, s_bf_all, mass_binning_all, mean_all, s_mean_all, channel, data, nb_toys=10000, cross_pollution=False):

    bf   = bf_all  [channel]
    s_bf = s_bf_all[channel]
    mean    = mean_all   [channel] 
    s_mean  = s_mean_all [channel]
    mass_binning = mass_binning_all[channel]
    
    misid_dic_full = get_misid_uncertainties(n_toys = nb_toys, verbose = True, AllPositive=True, TestAllPositive=True)
    sig_dic_full = get_signal_uncertainties(bf, s_bf, mean, s_mean, mass_binning, nb_toys,  True)
    bkg_dic_full = get_bkg_GL_uncertainties(n_toys= nb_toys, verbose=True )

    if cross_pollution:
        if channel != 'B0':
            print '****************\ncraoss-pollution only implemented for B0: ignoring.\n****************\n'
        else:
            import code; code.interact(local=locals())   
            sig_pollution_dic_full = get_signal_uncertainties(bf_all['Bs'], s_bf_all['Bs'], mean_all['Bs'], s_mean_all['Bs'], mass_binning_all['Bs'], n_toys=nb_toys, verbose=True, other_binning=mass_binning)
            import code; code.interact(local=locals())   
        
    

    #simplification of the dics
    misid_dic, sig_dic,bkg_dic  = [], [], []
    # keywd to be used
    value, errLo, errHi = 'sig median', 'sig -1sigma delta median', 'sig +1sigma delta median'
    for bin in range(len( sig_dic_full )):
        misid_dic.append({}); sig_dic.append({}); bkg_dic.append({})
        misid_dic[-1]['value'] = misid_dic_full[bin][value]
        misid_dic[-1]['errLo'] = misid_dic_full[bin][errLo]
        misid_dic[-1]['errHi'] = misid_dic_full[bin][errHi]
        sig_dic[-1]  ['value'] = sig_dic_full[bin][value]
        sig_dic[-1]  ['errLo'] = sig_dic_full[bin][errLo]
        sig_dic[-1]  ['errHi'] = sig_dic_full[bin][errHi]
        bkg_dic[-1]  ['value'] = bkg_dic_full[bin][value]
        bkg_dic[-1]  ['errLo'] = bkg_dic_full[bin][errLo]
        bkg_dic[-1]  ['errHi'] = bkg_dic_full[bin][errHi]
          
    #construction of histograms and Tgraphs
    misid_hist = [ TH1F( 'misid_1', 'misid_1', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'misid_2', 'misid_2', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'misid_3', 'misid_3', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'misid_4', 'misid_4', 6, mass_binning[0], mass_binning[-1] ) ]
    bkg_hist = [   TH1F( 'bkg_1', 'bkg_1', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'bkg_2', 'bkg_2', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'bkg_3', 'bkg_3', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'bkg_4', 'bkg_4', 6, mass_binning[0], mass_binning[-1] ) ]
    sig_hist = [   TH1F( 'sig_1', 'sig_1', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'sig_2', 'sig_2', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'sig_3', 'sig_3', 6, mass_binning[0], mass_binning[-1] )
                  ,TH1F( 'sig_4', 'sig_4', 6, mass_binning[0], mass_binning[-1] ) ]
    stacked  = [   THStack( 'stacked_1', 'stacked_1' )
                  ,THStack( 'stacked_2', 'stacked_2' )
                  ,THStack( 'stacked_3', 'stacked_3' )
                  ,THStack( 'stacked_4', 'stacked_4' ) ]


    # construction of a Histos for sig, misid, bkg and Tgraph for data and the sum of errors
    g_expec, g_obs =  [], []

    for binGL in range(4):
        for binMass in range(6):
            #print  'binGL ', binGL, 'binMass ', binMass , binGL*6+binMass+1
            
            misid_hist[binGL].SetBinContent(binMass+1, misid_dic[binGL*6+binMass]['value'])
            sig_hist[binGL]  .SetBinContent(binMass+1, sig_dic[binGL*6+binMass]['value'])
            bkg_hist[binGL]  .SetBinContent(binMass+1, bkg_dic[binGL*6+binMass]['value'])
            
        x, y, exl, eyl, exh, eyh = [], [], [], [], [], []
        for binMass in range(6):
            x.append( sig_hist[binGL].GetBinCenter (binMass+1) )
            y.append( misid_hist[binGL].GetBinContent(binMass+1) + bkg_hist[binGL].GetBinContent(binMass+1) + sig_hist[binGL].GetBinContent(binMass+1) )
            exl.append( (mass_binning[binMass+1]-mass_binning[binMass])/2. )
            exh.append( (mass_binning[binMass+1]-mass_binning[binMass])/2. )
            eyl.append( sqrt( misid_dic[binGL*6+binMass]['errLo']**2. + sig_dic[binGL*6+binMass]['errLo']**2. + bkg_dic[binGL*6+binMass]['errLo']**2. ) )
            eyh.append( sqrt( misid_dic[binGL*6+binMass]['errHi']**2. + sig_dic[binGL*6+binMass]['errHi']**2. + bkg_dic[binGL*6+binMass]['errHi']**2. ) )
            
        g_expec.append( TGraphAsymmErrors( 6 , array( 'd',  x), array( 'd', y ), array( 'd', exl), array( 'd', exh ), array( 'd',  eyl), array( 'd', eyh ) ) )

        # construction of a Tgraph from data
        x, y, exl, eyl, exh, eyh = [], [], [], [], [], []
        fc = TFeldmanCousins(0.68)
        for binMass in range(6):
            x.append( sig_hist[binGL].GetBinCenter (binMass+1) )
            y.append( data.GetBinContent(binGL*6+binMass+1) )
            exl.append( data.GetBinWidth(binGL*6+binMass+1)*0.5 )
            exh.append( data.GetBinWidth(binGL*6+binMass+1)*0.5 )
            if data.GetBinContent(binGL*6+binMass+1) < 20.:
                eyl.append( abs( data.GetBinContent(binGL*6+binMass+1) - fc.CalculateLowerLimit(data.GetBinContent(binGL*6+binMass+1), 0) ) )
                eyh.append( abs( data.GetBinContent(binGL*6+binMass+1) - fc.CalculateUpperLimit(data.GetBinContent(binGL*6+binMass+1), 0) ) )
            else:
                eyl.append( sqrt(data.GetBinContent(binGL*6+binMass+1) ) )
                eyh.append( sqrt(data.GetBinContent(binGL*6+binMass+1) ) )
        g_obs.append( TGraphAsymmErrors( 6 , array( 'd',  x), array( 'd', y ), array( 'd', exl), array( 'd', exh ), array( 'd',  eyl), array( 'd', eyh ) ) )

        
        stacked[binGL].Add(sig_hist[binGL])
        stacked[binGL].Add(misid_hist[binGL])
        stacked[binGL].Add(bkg_hist[binGL])
        

    #dealing with colors and filling
    for i in range(4):
        misid_hist[i].SetFillColor(3)
        misid_hist[i].SetLineWidth(0)
        misid_hist[i].SetLineColor(3)
        bkg_hist  [i].SetFillColor(kBlue-10)
        bkg_hist  [i].SetLineWidth(0)
        bkg_hist  [i].SetLineColor(kBlue-10)
        sig_hist  [i].SetFillColor(2)     
        sig_hist  [i].SetLineWidth(0)         
        sig_hist  [i].SetLineColor(2)

        g_expec[i].SetMarkerStyle(1)
        g_expec[i].SetFillStyle(3004)
        g_expec[i].SetFillColor(4)
        g_obs[i].SetMarkerStyle(8)
        #stacked[i].GetXaxis().SetTitle("m_{#mu#mu}(MeV/c^{2})")
        #import code; code.interact(local=locals())

    label_pos = [[0.173851, 0.104839, 0.316092, 0.354839]
                ,[0.605559, 0.701613, 0.743373, 0.956715] 
                ,[0.605559, 0.701613, 0.743373, 0.956715] 
                ,[0.605559, 0.701613, 0.743373, 0.956715]] 
    
    bdt_string = [  '0<BDT<0.25'
                   ,'0.25<BDT<0.5'
                   ,'0.5<BDT<0.75'
                   ,'0.75<BDT<1']

    labels = []
    for i in range(4):        
        l = TPaveText()
        l.SetTextSize(0.06)
        l.AddText('#splitline{'+bdt_string[i]+'}{LHCb}')
        l.SetX1NDC(label_pos[i][0])
        l.SetY1NDC(label_pos[i][1])
        l.SetX2NDC(label_pos[i][2])
        l.SetY2NDC(label_pos[i][3])
        l.SetFillColor(0)
        l.SetFillStyle(0)
        l.SetBorderSize(0)
        labels.append( l.Clone() )


    #plotting    
    canvas = TCanvas('results', 'results',-700,500)
    canvas.Divide(2,2, 0.005, 0.005)

    for i in range(4):
        canvas.cd(i+1)
        canvas.cd(i+1).SetTicks(1,1)

        stacked[i].Draw()
        g_expec[i].Draw("Zp2same")
        g_obs  [i].Draw("EZpsame")
        stacked[i].GetXaxis().SetTitle("m_{#mu#mu}(MeV/c^{2})")
        stacked[i].SetMaximum( max ( g_expec[i].GetYaxis().GetXmax(), g_obs[i].GetYaxis().GetXmax(), stacked[i].GetYaxis().GetXmax() ) )
        labels[i].Draw()

    canvas.Update()
    
    savename = 'AlaCDF_'+CHANNEL+'_'+discriminant+'_'+datestamp
    canvas.SaveAs(savename+'.pdf')
    canvas.SaveAs(savename+'.png')
    canvas.SaveAs(savename+'.root')
    
    #import code; code.interact(local=locals())
    

def build_lists_for_plots(results):
    
    list_of_bf = []
    list_of_mean_CLs, list_of_median_CLs, zero = [], [],  []
    list_of_pos_sigma_CLs_delta_mean, list_of_neg_sigma_CLs_delta_mean = [], []
    list_of_pos_sigma_CLs_delta_median, list_of_neg_sigma_CLs_delta_median = [], []
    list_of_mean_CLb = []
    list_of_pos_sigma_CLb_delta, list_of_neg_sigma_CLb_delta = [], []
    list_of_pos_sigma_CLs, list_of_neg_sigma_CLs = [], []
    list_of_pos_sigma_CLb, list_of_neg_sigma_CLb = [], []
    
    # http://scienceoss.com/sort-one-list-by-another-list/
    # to build Tgraph, it is important that the list are
    # sorted according to increasing bf
    #import code; code.interact(local=locals())
    tmp= []
    for i in range(len(results)):
        tmp.append( results[i]['BF'] )
    TrickToSort = zip(tmp, results)
    TrickToSort.sort()
    crap, results = zip(*TrickToSort)
    #import code; code.interact(local=locals())
    for i in range(len(results)):
        list_of_bf                        .append( results[i]['BF'] )
        list_of_median_CLs                .append( results[i]['CLs median'] )
        list_of_mean_CLs                  .append( results[i]['CLs mean'] )                                
        list_of_pos_sigma_CLs_delta_mean  .append( abs( results[i]['CLs mean']-results[i]['CLs +1sigma'] ))
        list_of_neg_sigma_CLs_delta_mean  .append( abs( results[i]['CLs mean']-results[i]['CLs -1sigma'] ))                                
        list_of_pos_sigma_CLs_delta_median.append( abs( results[i]['CLs median']-results[i]['CLs +1sigma'] ))
        list_of_neg_sigma_CLs_delta_median.append( abs( results[i]['CLs median']-results[i]['CLs -1sigma'] ))                               
        list_of_pos_sigma_CLs             .append( results[i]['CLs +1sigma'] )
        list_of_neg_sigma_CLs             .append( results[i]['CLs -1sigma'] )
        list_of_mean_CLb                  .append( results[i]['CLb mean'] )                               
        list_of_pos_sigma_CLb_delta       .append( abs( results[i]['CLb mean']-results[i]['CLb +1sigma'] ))
        list_of_neg_sigma_CLb_delta       .append( abs( results[i]['CLb mean']-results[i]['CLb -1sigma'] ))                            
        list_of_pos_sigma_CLb             .append( results[i]['CLb +1sigma'] )
        list_of_neg_sigma_CLb             .append( results[i]['CLb -1sigma'] )
        zero.append(0.)                       
    
    return  list_of_bf, list_of_median_CLs, list_of_mean_CLs, list_of_pos_sigma_CLs_delta_mean, list_of_neg_sigma_CLs_delta_mean, list_of_pos_sigma_CLs_delta_median, list_of_neg_sigma_CLs_delta_median, list_of_pos_sigma_CLs, list_of_neg_sigma_CLs, list_of_mean_CLb, list_of_pos_sigma_CLb_delta, list_of_neg_sigma_CLb_delta, list_of_pos_sigma_CLb, list_of_neg_sigma_CLb, zero        


def correct(files_list):
    
    for fname in files_list:
        f = open(fname, 'rb')
        #( bf_list, bf_solution,  CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution ) = cPickle.load(f)
        ( bf_solution,  CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution ) = cPickle.load(f); bf_list =  range(2,30,4)
        f.close()
        f = open(fname, 'wb')
        cPickle.dump( ( bf_list, bf_solution,  CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution ), f)
        f.close()

def import_and_build_dic(files_list):
    
    f = open(files_list[0], 'rb')
    ( bf_list, bf_solution,  CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution ) = cPickle.load(f)
    #( bf_solution,  CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution ) = cPickle.load(f); bf_list =  range(2,30,4)
    f.close()
    
    
    result = build_dic( bf_list, CLs_solution, CLb_solution )
    
    if len(files_list) >1:
        for fname in files_list:
            f = open(fname, 'rb')
            ( bf_list, bf_solution,  CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution ) = cPickle.load(f)
            #( bf_solution,  CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution ) = cPickle.load(f); bf_list =  range(2,30,4)
            f.close()
            res = build_dic( bf_list, CLs_solution, CLb_solution )
            result = add_results(res, result)
    
    result = compute_mean_median(result)
    return result




def build_dic( bf_list, CLs_solution, CLb_solution ):
    
    results = []
    for i in range(len(bf_list)):
        results.append({})
        results[-1]['BF'] = bf_list[i]        # bf hypo
        results[-1]['list_CLs']    = []       # list of CLs
        results[-1]['CLs mean']    = -99999.  # mean of CLs
        results[-1]['CLs median']  = -99999.  # median of CLs
        results[-1]['CLs -1sigma'] = -99999.  # -1sigma mean CLs
        results[-1]['CLs +1sigma'] = -99999.  # +1sigma mean CLs
        results[-1]['list_CLb']    = []       # list of CLb
        results[-1]['CLb mean']    = -99999.  # mean of CLb
        results[-1]['CLb median']  = -99999.  # median of CLb
        results[-1]['CLb -1sigma'] = -99999.  # -1sigma mean CLb
        results[-1]['CLb +1sigma'] = -99999.  # +1sigma mean CLb
        
        for trial in range(len(CLs_solution)):
            #print i, trial
            results[-1]['list_CLs'].append(CLs_solution[trial][i])
        for trial in range(len(CLb_solution)):
            results[-1]['list_CLb'].append(CLb_solution[trial][i])
    return results

def compute_mean_median(results):
    
    for i in range(len(results)):
        results[i]['CLs mean']    = sum( results[i]['list_CLs'] )/float(len( results[i]['list_CLs'] )) # mean CLs  
        tmp = [] ; tmp[:] = results[i]['list_CLs'][:]
        tmp.sort()
        if len(tmp) == 1:
            results[i]['CLs median']  = tmp[0]            # median CLs  
            results[i]['CLs -1sigma'] = tmp[0] # -1sigma mean CLs
            results[i]['CLs +1sigma'] = tmp[0] # +1sigma mean CLs
        else: 
            results[i]['CLs median']  = tmp[int(len(tmp)/2.)]            # median CLs  
            results[i]['CLs -1sigma'] = tmp[int(ceil(17*len(tmp)/100.))] # -1sigma mean CLs
            results[i]['CLs +1sigma'] = tmp[int(ceil(85*len(tmp)/100.))] # +1sigma mean CLs
        
        results[i]['CLb mean']    = sum( results[i]['list_CLb'] )/float(len( results[i]['list_CLb'] )) # mean CLb  
        tmp = [] ; tmp[:] = results[i]['list_CLb'][:]
        tmp.sort()
        if len(tmp) == 1:
            results[i]['CLb median']  = tmp[0]            # median CLs
            results[i]['CLb -1sigma'] = tmp[0] # -1sigma mean CLb
            results[i]['CLb +1sigma'] = tmp[0] # +1sigma mean CLb
        else:
            results[i]['CLb median']  = tmp[int(len(tmp)/2.)]            # median CLs
            results[i]['CLb -1sigma'] = tmp[int(ceil(17*len(tmp)/100.))] # -1sigma mean CLb
            results[i]['CLb +1sigma'] = tmp[int(ceil(85*len(tmp)/100.))] # +1sigma mean CLb
    return results



def add_results(res1, res2):
    
    bf_1, bf_2, results = [], [], []
    
    for item in res1:
        bf_1.append( item['BF'] )
    for item in res2:
        bf_2.append( item['BF'] )
    bf_all = list(set( bf_1 + bf_2 )) # remove duplicates
    
    for i in range(len( bf_all )):
        results.append({})
        results[-1]['BF'] = bf_all[i]         # bf hypo
        results[-1]['CLs mean']    = -99999.  # mean of CLs
        results[-1]['CLs median']  = -99999.  # median of CLs
        results[-1]['CLs -1sigma'] = -99999.  # -1sigma mean CLs
        results[-1]['CLs +1sigma'] = -99999.  # +1sigma mean CLs
        results[-1]['CLb mean']    = -99999.  # mean of CLb
        results[-1]['CLb median']  = -99999.  # median of CLb
        results[-1]['CLb -1sigma'] = -99999.  # -1sigma mean CLb
        results[-1]['CLb +1sigma'] = -99999.  # +1sigma mean CLb
        
        bf_in_res1, bf_in_res2 = False, False
        bf_res1_indx, bf_res2_indx = None, None
        if bf_all[i] in bf_1 :
            bf_in_res1 = True
            bf_res1_indx = bf_1.index( bf_all[i] )
        if bf_all[i] in bf_2 :
            bf_in_res2 = True
            bf_res2_indx = bf_2.index( bf_all[i] )
        
        if ( bf_in_res1 == True and bf_in_res2 == True) :
            results[-1]['list_CLs'] = res1[bf_res1_indx]['list_CLs'] + res2[bf_res2_indx]['list_CLs']# list of CLs
            results[-1]['list_CLb'] = res1[bf_res1_indx]['list_CLb'] + res2[bf_res2_indx]['list_CLb']# list of CLb
        elif bf_in_res1 == True : 
            results[-1]['list_CLs'] = res1[bf_res1_indx]['list_CLs'] # list of CLs
            results[-1]['list_CLb'] = res1[bf_res1_indx]['list_CLb'] # list of CLb
        else :
            results[-1]['list_CLs'] = res2[bf_res2_indx]['list_CLs'] # list of CLs
            results[-1]['list_CLb'] = res2[bf_res2_indx]['list_CLb'] # list of CLb
    
    return compute_mean_median(results)        



def do_GL_plot_sig_bkg(fgl, h_bkg):

    res_sig = get_signal_pdfs_uncertainties(n_toys= 15000, verbose=True )
    res_bkg = get_bkg_GL_uncertainties(n_toys= 15000, verbose=True )
    import code; code.interact(local=locals())


    exl, exh, eyl, eyh = [], [], [], []
    for bin in range(4):
        exl.append(0.125)
        exh.append(0.125)
        eyl.append( res_sig[bin]['-1sigma delta median'] )
        eyh.append( res_sig[bin]['+1sigma delta median'] )         
    graph_sig = TGraphAsymmErrors( 4 , array( 'd',  [0.125, 0.375, 0.625, 0.875]), array( 'd', fgl ), array( 'd', exl), array( 'd', exh ), array( 'd',  eyl), array( 'd', eyh ) )
      
    exl, exh, eyl, eyh, bkg = [],[],[],[],[]
    for bin in range(4):
        print bin
        exl.append(0.125)
        exh.append(0.125)
        eyl.append( res_bkg[bin*6]['sig -1sigma delta median'] + res_bkg[1+bin*6]['sig -1sigma delta median']
                 + res_bkg[2+bin*6]['sig -1sigma delta median'] + res_bkg[3+bin*6]['sig -1sigma delta median']
                 + res_bkg[4+bin*6]['sig -1sigma delta median'] + res_bkg[5+bin*6]['sig -1sigma delta median'])
        eyh.append( res_bkg[bin*6]['sig +1sigma delta median'] + res_bkg[1+bin*6]['sig +1sigma delta median']
                 + res_bkg[2+bin*6]['sig +1sigma delta median'] + res_bkg[3+bin*6]['sig +1sigma delta median']
                 + res_bkg[4+bin*6]['sig +1sigma delta median'] + res_bkg[5+bin*6]['sig +1sigma delta median'])
        bkg.append( h_bkg.GetBinContent(1+(bin)*6)+h_bkg.GetBinContent(2+(bin)*6)+h_bkg.GetBinContent(3+(bin)*6)+h_bkg.GetBinContent(4+(bin)*6)+h_bkg.GetBinContent(5+(bin)*6)+h_bkg.GetBinContent(6+(bin)*6) )         

    sum_ = sum( bkg )
    bkg  = map( lambda x: x/sum_, bkg )
    eyl  = map( lambda x: x/sum_, eyl )
    eyh  = map( lambda x: x/sum_, eyh )       
 
    graph_bkg = TGraphAsymmErrors( 4 , array( 'd',  [0.125, 0.375, 0.625, 0.875]), array( 'd', bkg ), array( 'd', exl), array( 'd', exh ), array( 'd',  eyl), array( 'd', eyh ) )    


    #graph_bkg.SetMinimum(0)
    graph_bkg.GetYaxis().SetTitle('Probability')
    graph_bkg.GetXaxis().SetTitle('BDT')#('GL')
    graph_bkg.GetXaxis().SetLabelFont(62)#(162)
    graph_bkg.GetYaxis().SetLabelFont(62)#(162)
    graph_bkg.GetXaxis().SetTitleFont(62)#(162)
    graph_bkg.GetYaxis().SetTitleFont(62)#(162)
    graph_bkg.GetXaxis().SetLimits(0.,1.)#(162)
    graph_bkg.GetYaxis().SetRangeUser(0.0001, 2)
    graph_bkg.SetLineWidth(3)
    graph_bkg.SetLineColor(4)
    graph_bkg.SetMarkerStyle(24)
    graph_bkg.SetMarkerColor(4)
    graph_bkg.SetMarkerSize(2)
    
    graph_sig.SetLineWidth(3)
    graph_sig.SetMarkerStyle(21)
    graph_sig.SetMarkerSize(2)

    canvas = TCanvas('can1', 'can1',-700,500)
    canvas.SetLogy()
    canvas.SetTicks(1,1)
    gStyle.SetOptStat(0)


    graph_bkg.Draw('AP')
    graph_sig.Draw('PSAME')

    
    leg1 = TLegend(0.610632, 0.512097, 0.920977, 0.711694)
    leg1.AddEntry( graph_sig, 'Signal', 'p')
    leg1.AddEntry( graph_bkg, 'Background', 'p')
    leg1.SetFillColor(0)
    leg1.SetLineColor(0)
    leg1.Draw()

    lhcb = do_lhcb_label( 0.173851, 0.104839, 0.316092, 0.354839, prelim=True ) 
    lhcb.Draw()

    import code; code.interact(local=locals())
    
    savename = 'BDT_sig_bkg_distribution'
    canvas.SaveAs(savename+'.pdf')
    canvas.SaveAs(savename+'.png')
    canvas.SaveAs(savename+'.root')


    

##     fgl_his            =  TH1F ( 'fgl_his        ', 'fgl_his        ', 4 , 0, 1)
##     for i in range(4):
##         fgl_his.SetBinContent(i+1, fgl[i] )
##     error_sig = [0.130, 0.096, 0.046, 0.036]
##     for i in range(4):
##         fgl_his.SetBinError(i+1, error_sig[i] )
    
        
##     fgl_bkg_his        =  TH1F ( 'fgl_bkg_his        ', 'fgl_bkg_his        ', 4 , 0, 1)
##     for i in range(1,5):
##         content = h_bkg.GetBinContent(1+(i-1)*6)+h_bkg.GetBinContent(2+(i-1)*6)+h_bkg.GetBinContent(3+(i-1)*6)+h_bkg.GetBinContent(4+(i-1)*6)+h_bkg.GetBinContent(5+(i-1)*6)+h_bkg.GetBinContent(6+(i-1)*6)
##         fgl_bkg_his.SetBinContent(i, content)

##     fgl_bkg_his.Scale(1./fgl_bkg_his.Integral() )
    
##     bs_gl = [[ 3.29187e+02,   6.40641e+00,  6.36622e+00,   6.44706e+00]
##          ,[7.35705e+00,   9.93963e-01,  9.52884e-01,   1.03580e+00]
##          ,[1.51084e+00,   3.77100e-01,  3.46432e-01,   4.08750e-01]
##          ,[8.09000e-02,   7.24835e-02,  5.02828e-02,   1.04361e-01]]
    
##     for i in range(4):
##         content = fgl_bkg_his.GetBinContent(i+1) * bs_gl[i][1] / bs_gl[i][0]
##         fgl_bkg_his.SetBinError(i+1, content)
    
##     print fgl_bkg_his.Print('all')
##     sum_ = bs_gl[0][0] + bs_gl[1][0] + bs_gl[2][0] + bs_gl[3][0] 
##     print bs_gl[0][0]/sum_, bs_gl[1][0]/sum_, bs_gl[2][0]/sum_, bs_gl[3][0]/sum_  
##     canvas = TCanvas('can1', 'can1',-700,500)
##     canvas.SetLogy()
##     canvas.SetTicks(1,1)
##     gStyle.SetOptStat(0)
    
    
    
##     fgl_bkg_his.GetYaxis().SetTitle('Probability')
##     fgl_bkg_his.GetXaxis().SetTitle('BDT')#('GL')
##     fgl_bkg_his.GetXaxis().SetLabelFont(62)#(162)
##     fgl_bkg_his.GetYaxis().SetLabelFont(62)#(162)
##     fgl_bkg_his.GetXaxis().SetTitleFont(62)#(162)
##     fgl_bkg_his.GetYaxis().SetTitleFont(62)#(162)
##     fgl_bkg_his.SetLineWidth(3)
##     fgl_bkg_his.SetLineColor(4)
##     #fgl_bkg_his.SetLineStyle(2)
##     fgl_bkg_his.SetMarkerStyle(24)
##     fgl_bkg_his.SetMarkerColor(4)
##     fgl_bkg_his.SetMarkerSize(2)
    
##     fgl_his    .SetLineWidth(3)
##     fgl_his    .SetMarkerStyle(21)
##     fgl_his    .SetMarkerSize(2)
    
##     fgl_bkg_his.Draw('PE')
##     fgl_his    .Draw('PESAME')
    
##     leg1 = TLegend(0.17, 0.20, 0.48 , 0.40 )#0.6,0.7,0.92,0.92)#
    
##     leg1.AddEntry( fgl_his, 'BDT pdf for Signal', 'l')
##     ## leg1.AddEntry( g_npv2, 'nPV = 2', 'l')
##     leg1.AddEntry( fgl_bkg_his, 'BDT pdf for Bkg', 'l')
##     leg1.SetFillColor(0)
##     #leg1.SetTextSize(0.035)
    
##     #leg1.Draw()

##     lhcb = do_lhcb_label(0.234195, 0.155242, 0.375, 0.405, prelim=True)
##     lhcb.Draw()
    
##     savename = 'GL-BDT_sig_bkg_distribution'
##     canvas.SaveAs(savename+'.pdf')
##     canvas.SaveAs(savename+'.png')
##     canvas.SaveAs(savename+'.root')
    

def list_to_tree(l, t, leaf):
    
    # Create a strut
    gROOT.ProcessLine(\
        "struct MyStruct{\
        Double_t "+leaf+";\
        };")
    from ROOT import MyStruct
    
    # Create branches in the tree
    s = MyStruct()
    t.Branch(leaf,AddressOf(s,leaf),leaf+'/D')
    
    # Fill tree
    for i in range(len( l )):
        s.someDouble = l[i]
        t.Fill()
    
    return t

def normal_asym(mean, sigmaN, sigmaP):
    
    sigmaN, sigmaP =  abs(float( sigmaN )), abs(float( sigmaP ))
    if sigma == 0:
        print 'WARNING sigma == 0. in computation of normal distr.'
        return mean
    else:
        rand = randn()
        if rand<0:
            return mean + (rand * sigmaN)
        else:
            return mean + (rand * sigmaP)


def normal_noneg(mean, sigma):
    
    sigma =  abs(float( sigma ))
    if sigma == 0:
        print 'WARNING sigma == 0. in computation of normal distr.'
        return mean
    
    out = mean + (randn()*sigma)
    if out <0. :
        #print 'NEEEEGGATIVE'
        out = normal_noneg(mean, sigma)
    return out

def normal_(mean, sigma):
    
    sigma =  abs(float( sigma ))
    if sigma == 0:
        print 'WARNING sigma == 0. in computation of normal distr.'
        return mean
    else:
        return mean + (randn()*sigma)

def normal_signed(mean, sigma):
    """Signed gaussian distribution, gaussian like only on the side defined by the sign of sigma, null on the other side."""
    sigma =  float( sigma )
    if sigma == 0:
        print 'WARNING sigma == 0. in computation of normal distr.'
        return mean
    else:
        return mean + (abs(randn())*sigma)


def getDiego_output( signal_expected, background_expected, obs_expected, inputfile= "computecls.input", outputfile = "fort.15"):
    """\
    """
    from os import system as subshell
    
    h = [ signal_expected, background_expected, obs_expected ]
    Must_be_int = [0     , 0                  , 1]
    lines = []
    for i_histo in range(len( h) ):
        string=''
        for i in range( h[i_histo].GetNbinsX() ):
            number = h[i_histo].GetBinContent(i+1)
            if Must_be_int[i_histo]:
                number = int(round(number)) ## Fortran aplication expects int for data sample !!
            string += " " + str(number)
        lines.append(string)
    
    lines[0] = lines[0] + " --> s(i)\n"
    lines[1] = lines[1] + " --> b(i)\n"
    lines[2] = lines[2] + " --> d(i)\n"
    
    f = file(inputfile,"w")
    f.write( str( obs_expected.GetNbinsX() ) + " -->n\n")
    f.write( lines[0] )
    f.write( lines[1] )
    f.write( lines[2] )
    f.close()
    
    subshell("./computecls.exe < "+inputfile)
    if outputfile != "fort.15":
        subshell("mv fort.15 " + ouputfile)
           
    f = file(outputfile, "r")
    lines = f.readlines()
    things = lines[0].split()
    CLs = float(things[1])
    things = lines[1].split()
    CLsb = float(things[1])
    things = lines[2].split()
    CLb = float(things[1])
    f.close()
    
    return CLs, CLb, CLsb      

def poisson_multinomial_histo( h_sig, h_bkg, factor_sig, factor_bkg ):
    """
    (h) is a pdf,
    (factor) is the number of events to scale the pdf with.
    First a poisson draw is called with expectation = factor
    and then a multinomial draw is called so that the total number of event
    is the poisson result and the distribution is according to the pdf
    this histo is returned.  
    """
    
    # poisson draw
    exp_number_bkg = poisson( factor_bkg )
    if factor_sig != 0.:
        exp_number_sig = poisson( factor_sig )
        h_sig_obs  = multinomial_histo( h_sig, exp_number_sig )
    
    
    # multinomial according to pdf
    h_bkg_obs  = multinomial_histo( h_bkg, exp_number_bkg )  
    
    # adding the sig and the bkg
    h_obs = TH1F ( 'Obs_histogram_toy', 'Obs_histogram_toy'
                  , h_bkg_obs.GetNbinsX(), 0, h_bkg_obs.GetNbinsX() )
    
    #import code; code.interact(local=locals())
    h_obs.Add( h_bkg_obs )
    #import code; code.interact(local=locals())
    if factor_sig != 0.:
        h_obs.Add( h_sig_obs )
    
    #import code; code.interact(local=locals())
    
    return h_obs


def multinomial_histo( h, exp_number ):
    """
    (h) is a pdf,
    (exp_number) is the number of events to scale the pdf with.
    A multinomial draw is called so that the total number of event
    is (exp_number) and the distribution is according to the pdf.
    This histo is returned.
    """
    
    h_expected = h.Clone()  
    prob = []
    
    for bin in range(1,  h.GetNbinsX()+1 ):
        prob.append( h.GetBinContent(bin) )
    
    # make sure the sum(prob is 1)
    sum_ = sum (prob)
    prob = map(lambda x: x/sum_, prob)        
             
    draw = list( multinomial( exp_number, prob ) )
    for bin in range(1,  h.GetNbinsX()+1 ):
        h_expected.SetBinContent( bin, draw[bin-1] )
    return h_expected


def do_kpi_coef(b_kpi,sb_kpi,Ntis_hh, sNtis_hh):
    b_kpi,sb_kpi,Ntis_hh, sNtis_hh = float( b_kpi), float( sb_kpi), float( Ntis_hh), float( sNtis_hh )
    c_kpi = b_kpi / Ntis_hh 
    sc_kpi = sqrt(  (sb_kpi / Ntis_hh)**2. + ( b_kpi * sNtis_hh / Ntis_hh**2. )**2. )
    return c_kpi, sc_kpi

def printComponentsNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs):
    
    print 'c_bu  = ',c_bu, '  +- ', sc_bu
    print 'c_phi = ',c_phi,'  +- ', sc_phi
    print 'c_kpi = ',c_kpi,'  +- ', sc_kpi
    print 'fdfs = ', fdfs ,' +- ', s_fdfs


def print_inputs():

    print '\n\n\n'
    print 'Channel ', CHANNEL 
    print 'Inputs'
    print 'c_bu  =   ',c_bu, '  +- ', sc_bu
    print 'c_phi =   ',c_phi,'  +- ', sc_phi
    print 'b_kpi =   ',b_kpi,'  +- ', sb_kpi
    print 'c_kpi =   ',c_kpi,'  +- ', sc_kpi
    print 'fdfs =    ', fdfs ,' +- ', s_fdfs
    print 'alpha =   ', alpha,' +- ',  s_alpha
    print 'Ntis_hh   ', Ntis_hh, ' +- ', sNtis_hh

    print 'SIGNAL'
    print '   GL_binning    ',  GL_binning
    print '   N_sig_gl      ', N_sig_gl
    print '   GL sig pdf    ', fgl
    print ''
    print '   mass binning      ',  mass_binning[CHANNEL]
    print '   mass mean         ', mean[CHANNEL], ' +- ',  s_mean[CHANNEL]
    print '   mass signma       ',sigma , ' +- ', s_sigma
    print '   mass a            ', a,  ' +- ', s_a
    print '   mass sig pdf      ', pdf_mass
    print '   signal pdf        ', signal.Print('all')
    print 'BKG'
    print '   mass indx         ', idx_gl
    print '   mass indx sigma   ', s_idx
    print '   Nsb               ', Nsb
    print '   s_Nsb             ', s_Nsb
    print '   Nsb_range         ', Nsb_range
    print '   background_expected', background_expected.Print('all')
    print '\n\n\n'

    
def calculateNormalizationFactor( c_bu, c_phi, c_kpi,sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, channel):
    """return the wighted average of the norm channels. Different computation according to channel 'B0' or 'Bs'"""
    
    c_bu, c_phi, c_kpi, sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs = float(c_bu), float(c_phi), float(c_kpi), float(sc_bu), float(sc_phi), float(sc_kpi), float(fdfs), float(s_fdfs)
    
    if channel == 'B0':
        tmp = c_phi / fdfs 
        s_tmp = sqrt(  (sc_phi / fdfs)**2. + ( c_phi * s_fdfs / fdfs**2. )**2. )
        
        alpha = (c_bu/sc_bu**2. + tmp/s_tmp**2. + c_kpi/sc_kpi**2.) / (1./sc_bu**2. + 1./s_tmp**2. + 1./sc_kpi**2.)  
        s_alpha = sqrt( 1./ ( 1./sc_bu**2. + 1./s_tmp**2. + 1./sc_kpi**2. )  )
    
    elif channel == 'Bs':
##         tmp = c_bu * fdfs
##         s_tmp = sqrt(  (c_bu * s_fdfs)**2. + (fdfs * sc_bu )**2. )    
##         tmp2 = c_kpi * fdfs
##         s_tmp2 = sqrt(  (c_kpi * s_fdfs)**2. + (fdfs * sc_kpi )**2. )
##         alpha = (tmp/s_tmp**2. + c_phi/sc_phi**2. + tmp2/s_tmp2**2.) / (1./s_tmp**2. + 1./sc_phi**2. + 1./s_tmp2**2.)  
##         s_alpha = sqrt( 1./ ( 1./s_tmp**2. + 1./sc_phi**2. + 1./s_tmp2**2. )  )
        
        tmp = (c_bu/sc_bu**2. +c_kpi/sc_kpi**2.)/ (1./sc_bu**2. + 1./sc_kpi**2.)
        s_tmp = sqrt( 1./ ( 1./sc_bu**2. + 1./sc_kpi**2. )  )
        
        tmp2 = tmp * fdfs
        s_tmp2 = sqrt(  (tmp * s_fdfs)**2. + (fdfs * s_tmp )**2. )
        
        alpha = (c_phi/sc_phi**2. + tmp2/s_tmp2**2.) / (1./sc_phi**2. + 1./s_tmp2**2.)  
        s_alpha = sqrt( 1./ ( 1./sc_phi**2. + 1./s_tmp2**2. )  )
    
    else: print 'UNKNOWN CHANNEL'
    
    return alpha , s_alpha 


def split_in_bins_cbs(mean, sigma, a, binning):
    """ """
    if 'exp' not in dir():from math import exp
    if 'log' not in dir():from math import log
    if 'erf' not in dir():from scipy.special import erf
    
    mean, sigma, a = float(mean), float(sigma), float(a)
    abs_a = abs(a)
    m_a = mean - (a*sigma)
    result = []
    for i in range(len(binning)-1):
        #import code; code.interact(local=locals())
        if  m_a > binning[i+1]:  #tail part
            result.append( -sigma * exp(  -0.5 *abs_a* abs_a ) / abs_a * ( log( abs( binning[i+1] - mean - sigma/abs_a + sigma*abs_a )) - log( abs( binning[i] - mean - sigma/abs_a + sigma*abs_a ))  )  )
        
        elif  m_a > binning[i]:  #mixed part
            res1 =  -sigma * exp(  -0.5 *abs_a* abs_a ) / abs_a * (
                log(   abs( - sigma/abs_a  ))
                - log( abs( binning[i] - mean - sigma/abs_a + sigma*abs_a ))
                       )
            res2 = erf( ( binning[i+1] - mean) / sigma ) - erf( ( m_a - mean) / sigma )
            result.append( res1 + res2 )
            
        else: # gaussian part
            result.append(  erf( ( binning[i+1] - mean) / sigma ) - erf( ( binning[i] - mean) / sigma ) )
    
    #sum_ = sum (result)
    #return map(lambda x: x/sum_, result)
    return result


def split_in_bins_cbs_roofit(mean, sigma, a, binning, error = None , further_syst=None, other_binning=None ):
    """ compute the value according to the binning and assumeing a CB distribution.
    if error != None error = [s_mean, s_sigma, s_a] : fluctuate first those
    parameters before to compute the CB."""
    
    from ROOT import RooCBShape, RooRealVar, RooArgSet, RooFit
    
    mean, sigma, a = float(mean), float(sigma), float(a)
    if error != None:    # fluctuate the input variables.
        s_mean  = abs(float(error[0]))
        s_sigma = abs(float(error[1]))
        s_a     = abs(float(error[2]))
        mean  = normal_(mean,  s_mean)
        sigma = normal_(sigma, s_sigma)
        a     = normal_(a,     s_a)
    
    mass = RooRealVar('m', 'mass', mean-600.,mean+600. )
    roo_mean =  RooRealVar('mean', 'M', mean)
    roo_sigma = RooRealVar('resol', 'sigmaM', sigma)
    roo_alpha = RooRealVar('alpha', 'alpha', a)
    roo_n = RooRealVar('n', 'n', 1.)
    
    cbs = RooCBShape('cbs', 'cbs', mass, roo_mean, roo_sigma, roo_alpha, roo_n)
    
    result = []
    for i in range(len(binning)-1):
        
        mass.setRange('int_range_'+str(i), binning[i], binning[i+1])
        integral = cbs.createIntegral( RooArgSet(mass), RooFit.Range('int_range_'+str(i)))
        result.append( integral.getVal() )
        integral.Delete()
    
    sum_   = sum (result)
    result = map(lambda x: x/sum_, result)
    print 'in normal bins', result
    
    if further_syst != None:
        for i in range(len(result)):
            result[i] = normal_signed( result[i], result[i]*further_syst[i])
        sum_   = sum (result)
        result = map(lambda x: x/sum_, result)

    if other_binning != None:
        #distribution of mass in another binning such that integral in mass_binning==1
        result_other = []
        for i in range(len(other_binning)-1):
            mass.setRange('int_range_other_'+str(i), other_binning[i], other_binning[i+1])
            integral = cbs.createIntegral( RooArgSet(mass), RooFit.Range('int_range_other_'+str(i)))
            result_other.append( integral.getVal() )
            integral.Delete()
        result = map(lambda x: x/sum_, result_other)
        print 'in other bins', result
    
    return result

def transform_2D_in_1D( h_2D ):

    h_1D = TH1F( h_2D.GetName()+'_1D', h_2D.GetName()+'_1D', h_2D.GetNbinsX()*h_2D.GetNbinsY() , 0, h_2D.GetNbinsX()*h_2D.GetNbinsY())
    for bin_gl in range(h_2D.GetNbinsX()):
            for bin_mass in range(h_2D.GetNbinsY()):
                bin = bin_gl*h_2D.GetNbinsY()  + bin_mass + 1
                h_1D.SetBinContent( bin, h_2D.GetBinContent( bin_gl+1, bin_mass+1 ) )
    return h_1D
        

def misid_asym( h, h_negative, h_positive, rand, AllPositive=False):

    
    if rand < 0:
        h_temp = h_negative.Clone()
    else:
        h_temp = h_positive.Clone()
        
    for bin in range(h.GetNbinsX()):
        content = h.GetBinContent(bin+1) + ( rand *  h_temp.GetBinContent(bin+1))
        if AllPositive and content<0:
            content = 0.
        h.SetBinContent( bin+1, content )
        
    return h


def misid_asym_truncated( h, h_negative, h_positive, rand, AllPositive=False):

    
    if rand < 0:
        h_temp = h_negative.Clone()
    else:
        h_temp = h_positive.Clone()

    # truncated version. values allowed only inbetween up and down hostograms.
    if rand >1 or rand <1 :
        for bin in range(h.GetNbinsX()):
            h.SetBinContent( bin+1, h_temp.GetBinContent(bin+1))
    else:
        for bin in range(h.GetNbinsX()):    
            content = h.GetBinContent(bin+1) + ( rand *  h_temp.GetBinContent(bin+1))
            h.SetBinContent( bin+1, content )
        
    return h
      

def do_misID_exp_2011(misIDN, misIDf,  misID_hist_central_1D, error = None, number_bin_GL =4, number_bin_mass=6, AllPositive=False, TestAllPositive=False):
    """compute the expected misid in 24 bins.
    if Error != None [ s_misIDN, s_misIDf,  misID_hist_ErrN_1D, misID_hist_ErrP_1D ]
    then fluuctuate the input according to the errors
    error = [ s_misIDN, s_misIDf,  misID_hist_ErrN_2D, misID_hist_ErrP_2D ]
    """

    misIDN, misIDf = float( misIDN ), float( misIDf )

    h_misid_expected = misID_hist_central_1D.Clone()

    if error == None:    
        h_misid_expected.Scale( 1./h_misid_expected.GetSum() )
        h_misid_expected.Scale( misIDN * misIDf )
     
    else:
        s_misIDN = float(error[0])
        s_misIDf = float(error[1])
        misID_hist_ErrN_1D = error[2]
        misID_hist_ErrP_1D = error[3]
        
        if TestAllPositive: #try until all misid bins are >=0
            AllPositive = False
            ok_to_exit=False
        else: ok_to_exit=True
        
        loop_counter =0
        while loop_counter<10000 and ok_to_exit==False:
            loop_counter += 1
                
            misIDN = normal_noneg( misIDN, s_misIDN )
            #misIDN = normal_( misIDN, s_misIDN )
            if misIDN<0 : print 'NEGGGGGGGGGGative'

            normal_draw =  randn()
            misIDf = misIDf + ( normal_draw*s_misIDf )
        
            h_misid_expected = misid_asym_truncated( h_misid_expected, misID_hist_ErrN_1D, misID_hist_ErrP_1D, normal_draw, AllPositive=AllPositive )

            h_misid_expected.Scale( 1./h_misid_expected.GetSum() )
            h_misid_expected.Scale( misIDN * misIDf )
            
            #import code; code.interact(local=locals())

            if h_misid_expected.GetBinContent( h_misid_expected.GetMinimumBin() ) >= 0.:
                ok_to_exit=True

            print 'min ', h_misid_expected.GetBinContent( h_misid_expected.GetMinimumBin() ),
            print 'ok? ', ok_to_exit

    #l = []
    #for bin in range( h_misid_expected.GetNbins() ):
    #    l.append( h_misid_expected.GetBinContent( bin+1 ) )
                

    #return h_misid_expected, l
    return h_misid_expected


def ___do_misID_exp_2011(misIDN, misIDf,  misID_hist_central_1D, error = None, number_bin_GL =4, number_bin_mass=6, AllPositive=False, TestAllPositive=False):
    """compute the expected misid in 24 bins.
    if Error != None [ s_misIDN, s_misIDf,  misID_hist_ErrN_1D, misID_hist_ErrP_1D ]
    then fluuctuate the input according to the errors
    error = [ s_misIDN, s_misIDf,  misID_hist_ErrN_2D, misID_hist_ErrP_2D ]
    """

    misIDN, misIDf = float( misIDN ), float( misIDf )

    h_misid_expected = misID_hist_central_1D.Clone()
    
    if error != None:
        s_misIDN = float(error[0])
        s_misIDf = float(error[1])
        misID_hist_ErrN_1D = error[2]
        misID_hist_ErrP_1D = error[3]
        
        if TestAllPositive: #try until all misid bins are >=0
            AllPositive = False
            ok_to_exit=False
        else: ok_to_exit=True
        
        loop_counter =0
        while loop_counter<10000 and ok_to_exit==False:
            loop_counter += 1
                
            misIDN = normal_noneg( misIDN, s_misIDN )
            #misIDN = normal_( misIDN, s_misIDN )
            if misIDN<0 : print 'NEGGGGGGGGGGative'

            normal_draw =  randn()
            misIDf = misIDf + ( normal_draw*s_misIDf )
        
            h_misid_expected = misid_asym_truncated( h_misid_expected, misID_hist_ErrN_1D, misID_hist_ErrP_1D, normal_draw, AllPositive=AllPositive )

            h_misid_expected.Scale( 1./h_misid_expected.GetSum() )
            h_misid_expected.Scale( misIDN * misIDf )
            
            #import code; code.interact(local=locals())

            if h_misid_expected.GetBinContent( h_misid_expected.GetMinimumBin() ) >= 0.:
                ok_to_exit=True

            print 'min ', h_misid_expected.GetBinContent( h_misid_expected.GetMinimumBin() ),
            print 'ok? ', ok_to_exit

    #l = []
    #for bin in range( h_misid_expected.GetNbins() ):
    #    l.append( h_misid_expected.GetBinContent( bin+1 ) )
                

    #return h_misid_expected, l
    return h_misid_expected


def do_bkg_exp_2011(Nsb, idx_gl, Nsb_range, mass_binning, histo, number_bin_GL =4, number_bin_mass=6, error = None, only_hist=True):
    """compute the 2D expected nuimbers of background events.
    if Error != None then fluuctuate the input according to the errors
    changes: poisson for bins 2,3,4
    asym error idx
    """
    
    
    Nsb, idx_gl = map(lambda x: float(x), Nsb), map(lambda x: float(x), idx_gl)
    if error != None:    # fluctuate the input variables.
        s_Nsb    = error[0]
        s_idx_glN = error[1][0]
        s_idx_glP = error[1][1]
        s_Nsb    = map(lambda x: abs(float(x)), s_Nsb)
        s_idx_glN = map(lambda x: abs(float(x)), s_idx_glN)
        s_idx_glP = map(lambda x: abs(float(x)), s_idx_glP)

        Nsb[0]    = normal_(Nsb[0], s_Nsb[0])
        for i in range(1, len(Nsb)):
            # poisson from mean such that most-prob-value is as observed
            # http://ajp.aapt.org/resource/1/ajpias/v38/i5/p658_s2
            Nsb[i] = poisson( Nsb[i]* exp ( 1./(2*Nsb[i]) - 1./(12.*Nsb[i]**2)) )
            
        s_idx_gl = []
        for i in range(len(Nsb)):
            idx_gl.append( normal_asym(idx_gl[i], s_idx_glN[i], s_idx_glP[i]) )

    
    for bin_gl in range(1, number_bin_GL+1):
        for bin_mass in range(1, number_bin_mass+1):
            
            #import code; code.interact(local=locals()) 
            content = ( Nsb[bin_gl-1]
                        * ( exp( idx_gl[bin_gl-1] * mass_binning[bin_mass] ) - exp( idx_gl[bin_gl-1] * mass_binning[bin_mass-1] ))
                        / ( exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) ) )
            
            histo.SetBinContent( (bin_gl-1)*( number_bin_mass ) + bin_mass  , content)
            #print 'bin gl', bin_gl, 'bin m', bin_mass, 'bin1D', (bin_gl-1)*( number_bin_mass ) + bin_mass, 'cont.', content

                
    if True and error != None:
        s_idx_gl =  [(s_idx_glN[0]+s_idx_glP[0])*0.5, (s_idx_glN[1]+s_idx_glP[1])*0.5, (s_idx_glN[2]+s_idx_glP[2])*0.5, (s_idx_glN[3]+s_idx_glP[3])*0.5]
        #print 
        for bin_gl in range(1, number_bin_GL+1):
            #print bin_gl
            #import code; code.interact(local=locals()) 

            content = Nsb[bin_gl-1] * ( exp( idx_gl[bin_gl-1] * mass_binning[-1] ) - exp( idx_gl[bin_gl-1] * mass_binning[0] )) / ( exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) )
                      
            stat_error = sqrt(
                ( s_idx_gl[bin_gl-1]
                 * Nsb[bin_gl-1]
                 * (
                ( mass_binning[-1]*exp( idx_gl[bin_gl-1] * mass_binning[-1] ) - mass_binning[0]*exp( idx_gl[bin_gl-1] * mass_binning[0] ))
                * ( exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) )

                
                + ( exp( idx_gl[bin_gl-1] * mass_binning[-1] ) - exp( idx_gl[bin_gl-1] * mass_binning[0] )) 
                * ( Nsb_range[bin_gl-1][1]*exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - Nsb_range[bin_gl-1][0]*exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + Nsb_range[bin_gl-1][3]*exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - Nsb_range[bin_gl-1][2]*exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) ))
                / (exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ))**2.
                )**2. )
                
            
            syst_error = sqrt(
                ( s_Nsb[bin_gl-1]
                   * ( exp( idx_gl[bin_gl-1] * mass_binning[-1] ) - exp( idx_gl[bin_gl-1]* mass_binning[0] ))
                   / ( exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) )
                  )**2.
                )
            
            print content, ' +- ', stat_error, ' +- ', syst_error
        #compare to
        print histo.GetBinContent(1)+histo.GetBinContent(2)+histo.GetBinContent(3)+histo.GetBinContent(4)+histo.GetBinContent(5)+histo.GetBinContent(6), histo.GetBinContent(1+6)+histo.GetBinContent(2+6)+histo.GetBinContent(3+6)+histo.GetBinContent(4+6)+histo.GetBinContent(5+6)+histo.GetBinContent(6+6), histo.GetBinContent(1+12)+histo.GetBinContent(2+12)+histo.GetBinContent(3+12)+histo.GetBinContent(4+12)+histo.GetBinContent(5+12)+histo.GetBinContent(6+12), histo.GetBinContent(1+18)+histo.GetBinContent(2+18)+histo.GetBinContent(3+18)+histo.GetBinContent(4+18)+histo.GetBinContent(5+18)+histo.GetBinContent(6+18)

    if only_hist:
        return histo
    else:
       return histo, Nsb, idx_gl 



def do_bkg_exp(Nsb, idx_gl, Nsb_range, mass_binning, histo, number_bin_GL =4, number_bin_mass=6, error = None, only_hist=True):
    """compute the 2D expected nuimbers of background events.
    if Error != None then fluuctuate the input according to the errors"""
    
    
    Nsb, idx_gl = map(lambda x: float(x), Nsb), map(lambda x: float(x), idx_gl)
    if error != None:    # fluctuate the input variables.
        s_Nsb    = error[0]
        s_idx_gl = error[1]
        s_Nsb    = map(lambda x: abs(float(x)), s_Nsb)
        s_idx_gl = map(lambda x: abs(float(x)), s_idx_gl)
        
        for i in range(len(Nsb)):
            Nsb[i]    = normal_(Nsb[i], s_Nsb[i])
            idx_gl[i] = normal_(idx_gl[i], s_idx_gl[i])

    
    for bin_gl in range(1, number_bin_GL+1):
        for bin_mass in range(1, number_bin_mass+1):
            
            #import code; code.interact(local=locals()) 
            content = ( Nsb[bin_gl-1]
                        * ( exp( idx_gl[bin_gl-1] * mass_binning[bin_mass] ) - exp( idx_gl[bin_gl-1] * mass_binning[bin_mass-1] ))
                        / ( exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) ) )
            
            histo.SetBinContent( (bin_gl-1)*( number_bin_mass ) + bin_mass  , content)
            #print 'bin gl', bin_gl, 'bin m', bin_mass, 'bin1D', (bin_gl-1)*( number_bin_mass ) + bin_mass, 'cont.', content

                
    if True and error != None:
        #print 
        for bin_gl in range(1, number_bin_GL+1):

            content = Nsb[bin_gl-1] * ( exp( idx_gl[bin_gl-1] * mass_binning[-1] ) - exp( idx_gl[bin_gl-1] * mass_binning[0] )) / ( exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) )
                      
            stat_error = sqrt(
                ( s_idx_gl[bin_gl-1]
                 * Nsb[bin_gl-1]
                 * (
                ( mass_binning[-1]*exp( idx_gl[bin_gl-1] * mass_binning[-1] ) - mass_binning[0]*exp( idx_gl[bin_gl-1] * mass_binning[0] ))
                * ( exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) )

                
                + ( exp( idx_gl[bin_gl-1] * mass_binning[-1] ) - exp( idx_gl[bin_gl-1] * mass_binning[0] )) 
                * ( Nsb_range[bin_gl-1][1]*exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - Nsb_range[bin_gl-1][0]*exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + Nsb_range[bin_gl-1][3]*exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - Nsb_range[bin_gl-1][2]*exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) ))
                / (exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ))**2.
                )**2. )
                
            
            syst_error = sqrt(
                ( s_Nsb[bin_gl-1]
                   * ( exp( idx_gl[bin_gl-1] * mass_binning[-1] ) - exp( idx_gl[bin_gl-1]* mass_binning[0] ))
                   / ( exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][1] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][0] ) + exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][3] ) - exp( idx_gl[bin_gl-1] * Nsb_range[bin_gl-1][2] ) )
                  )**2.
                )
            
            print content, ' +- ', stat_error, ' +- ', syst_error
        #compare to
        print histo.GetBinContent(1)+histo.GetBinContent(2)+histo.GetBinContent(3)+histo.GetBinContent(4)+histo.GetBinContent(5)+histo.GetBinContent(6), histo.GetBinContent(1+6)+histo.GetBinContent(2+6)+histo.GetBinContent(3+6)+histo.GetBinContent(4+6)+histo.GetBinContent(5+6)+histo.GetBinContent(6+6), histo.GetBinContent(1+12)+histo.GetBinContent(2+12)+histo.GetBinContent(3+12)+histo.GetBinContent(4+12)+histo.GetBinContent(5+12)+histo.GetBinContent(6+12), histo.GetBinContent(1+18)+histo.GetBinContent(2+18)+histo.GetBinContent(3+18)+histo.GetBinContent(4+18)+histo.GetBinContent(5+18)+histo.GetBinContent(6+18)

    if only_hist:
        return histo
    else:
       return histo, Nsb, idx_gl 

def from_Diego2D_to_mine(histo1D, t_file, h_name, number_bin_GL =4, number_bin_mass=6):
    
    
    f = TFile(t_file, 'r')
    histo2D = f.Get(h_name)
    
    for bin_gl in range(1, number_bin_GL+1):
        for bin_mass in range(1, number_bin_mass+1):
            
            content = histo2D.GetBinContent(bin_gl, bin_mass)
            histo1D.SetBinContent( (bin_gl-1)*( number_bin_mass ) + bin_mass  , content)
            print bin_gl, bin_mass, (bin_gl-1)*( number_bin_mass ) + bin_mass  , content
    #import code; code.interact(local=locals())      
    
    #f.Close()
    return histo1D

def do_sig_pdf( mass_pdf, gl_pdf, histo, number_bin_GL =4, number_bin_mass=6):
    
    for bin_gl in range(1, number_bin_GL+1):
        for bin_mass in range(1, number_bin_mass+1):
            
            #import code; code.interact(local=locals())
            content = gl_pdf[bin_gl-1] * mass_pdf[bin_mass-1]
            
            histo.SetBinContent( (bin_gl-1)*( number_bin_mass ) + bin_mass  , content)
            #print 'bin gl', bin_gl, 'bin m', bin_mass, 'bin1D', (bin_gl-1)*( number_bin_mass ) + bin_mass, 'cont.', content
    
    while histo.Integral()>1.0:
        #print 'not yet', histo.Integral()
        histo. Scale(.99999/histo.Integral())
    #print 'aft', histo.Integral()
    return histo


def convert_tofractions(N_sig_gl, Ntis_hh, error = None):
    
    N_sig_gl= map(lambda x: float(x), N_sig_gl)
    Ntis_hh = float(Ntis_hh)
    
    if error != None:
        s_N_sig_gl = error[0]
        s_Ntis_hh  = error[1]
        s_N_sig_gl = map(lambda x: abs(float(x)), s_N_sig_gl)
        s_Ntis_hh  = abs(float( s_Ntis_hh ))
        
        Ntis_hh  = normal_(Ntis_hh, s_Ntis_hh)
        for i in range(len(N_sig_gl)):
            N_sig_gl[i]    = normal_(N_sig_gl[i], s_N_sig_gl[i])
    
    result = []
    result[:] = N_sig_gl[:]
    result[0] = max(0., Ntis_hh - N_sig_gl[1] - N_sig_gl[2]- N_sig_gl[3])
    
    #print result   
    sum_ = sum (result)
    return map(lambda x: x/sum_, result)

def fake_data_with_high_BF(histo, bf_fake):

    fgl__ = convert_tofractions(N_sig_gl, Ntis_hh)
    pdf_mass__ = split_in_bins_cbs_roofit(mean[CHANNEL], sigma, a, mass_binning[CHANNEL])
    signal__ = do_sig_pdf( pdf_mass__, fgl__, h_sig.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)
    
    background_expected__  = do_bkg_exp(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)

    factor_sig = bf_fake* 1e-9 / alpha
    signal__    .Scale( factor_sig )

    histo.Add( background_expected__  )
    histo.Add( signal__  )
    print histo.Integral()
    signal__.Delete()
    background_expected__.Delete()
    print histo.Integral()
    import code; code.interact(local=locals())
    return histo

def get_data_ntuple(histo, tree, mass_binning, GL_binning, gl_name, mass_name, ismu_name1='mu1ismu', ismu_name2='mu2ismu', verbose=False):

    number_bin_mass = len(mass_binning)-1
    
    for entry in range(tree.GetEntries()):
        tree.GetEntry(entry)
        for bin_gl in range(len(GL_binning)-1):
            for bin_mass in range(len(mass_binning)-1):
                
                #print bin_gl, bin_mass, bin_gl* number_bin_mass  + bin_mass +1
                #import code; code.interact(local=locals())  
                if (     getattr(tree, gl_name)    >   GL_binning[ bin_gl ]
                     and getattr(tree, gl_name)    <=  GL_binning[ bin_gl+1 ]
                     and getattr(tree, mass_name)  >   mass_binning[ bin_mass ]
                     and getattr(tree, mass_name)  <=  mass_binning[ bin_mass+1 ]
                     and getattr(tree, ismu_name1) and getattr(tree, ismu_name2)) :

                    bin = bin_gl*number_bin_mass  + bin_mass + 1
                    histo.SetBinContent( bin,  1 + histo.GetBinContent( bin ) )
                    #print bin
                #else: print ''

    
    if verbose:
        table = ''
        for i in range(1, number_bin_mass+1):
            table+='& $%(n1)i$ & $%(n2)i$ & $%(n3)i$ & $%(n4)i$ \\TTstrut\\\\\n' %\
                    { 'n1':   histo.GetBinContent( i )
                     ,'n2':   histo.GetBinContent( i+   number_bin_mass )
                     ,'n3':   histo.GetBinContent( i+ 2*number_bin_mass )
                     ,'n4':   histo.GetBinContent( i+ 3*number_bin_mass )}
        print '\ntable of observed event, channel ', CHANNEL,'\n', table, '\n'
    return histo



def print_data( h, number_bin_GL = 4, number_bin_mass=6 ):
    
    table = ''
    for i in range( number_bin_mass ):
        table+='& $%(n1).i$ & $%(n2).i$ & $%(n3).i$ & $%(n4).i$  \\TTstrut\\\\' %\
                { 'n1':   h.GetBinContent( 0*number_bin_mass + i + 1)
                 ,'n2':   h.GetBinContent( 1*number_bin_mass + i + 1)
                 ,'n3':   h.GetBinContent( 2*number_bin_mass + i + 1)
                 ,'n4':   h.GetBinContent( 3*number_bin_mass + i + 1)}
        table+='\n'
    print table
 


def get_signal_pdfs_uncertainties(n_toys= 10000, verbose=True):

    l_m, l_gl = [],[]

    for i in range(n_toys):
        print '\n trial number ', i
        fgl = convert_tofractions(N_sig_gl, Ntis_hh, error = [sN_sig_gl, sNtis_hh])
        pdf_mass = split_in_bins_cbs_roofit(mean[CHANNEL], sigma, a, mass_binning[CHANNEL], error = [s_mean[CHANNEL], s_sigma, s_a])#, further_syst=sn_MC)
        print fgl
        print pdf_mass   

        l_m.append( pdf_mass )
        l_gl.append( fgl )
        
    #compute the median, average, and sigmas
    res_m,res_gl = [], []
    for i in range( len(l_m[-1] )):
        res_m.append( {} )
        res_m[-1]['bin'] = i
        res_m[-1]['list_bin'] = []
        for j in range(n_toys):
            res_m[-1]['list_bin'].append( l_m[j][i] )
    for i in range( len(l_gl[-1] )):
        res_gl.append( {} )
        res_gl[-1]['bin'] = i
        res_gl[-1]['list_bin'] = []
        for j in range(n_toys):
            res_gl[-1]['list_bin'].append( l_gl[j][i] )

    for item in res_m:
        item['mean']    = sum( item['list_bin'] )/float(len( item['list_bin'] )) # mean  
        tmp = [] ; tmp[:] = item['list_bin'][:]
        tmp.sort()
        item['median']  = tmp[int(len(tmp)/2.)]            # median CLs  
        item['-1sigma'] = tmp[int(ceil(17*len(tmp)/100.))] # -1sigma mean CLs
        item['+1sigma'] = tmp[int(ceil(85*len(tmp)/100.))] # +1sigma mean CLs
        item['-1sigma delta mean'] = abs( item['mean'] - item['-1sigma'] ) # 
        item['+1sigma delta mean'] = abs( item['mean'] - item['+1sigma'] ) # 
        item['-1sigma delta median'] = abs( item['median'] - item['-1sigma'] ) # 
        item['+1sigma delta median'] = abs( item['median'] - item['+1sigma'] ) # 
    for item in res_gl:
        item['mean']    = sum( item['list_bin'] )/float(len( item['list_bin'] )) # mean  
        tmp = [] ; tmp[:] = item['list_bin'][:]
        tmp.sort()
        item['median']  = tmp[int(len(tmp)/2.)]            # median CLs  
        item['-1sigma'] = tmp[int(ceil(17*len(tmp)/100.))] # -1sigma mean CLs
        item['+1sigma'] = tmp[int(ceil(85*len(tmp)/100.))] # +1sigma mean CLs
        item['-1sigma delta mean'] = abs( item['mean'] - item['-1sigma'] ) # 
        item['+1sigma delta mean'] = abs( item['mean'] - item['+1sigma'] ) # 
        item['-1sigma delta median'] = abs( item['median'] - item['-1sigma'] ) # 
        item['+1sigma delta median'] = abs( item['median'] - item['+1sigma'] ) # 

    if verbose:
        print 'reference'
        fgl = convert_tofractions(N_sig_gl, Ntis_hh)
        pdf_mass = split_in_bins_cbs_roofit(mean[CHANNEL], sigma, a, mass_binning[CHANNEL])
        print fgl, sum(fgl)
        print pdf_mass , sum(pdf_mass) 

        print 'gl'
        __mean, __median = 0., 0.
        for bin in range(len(fgl)):
            __mean   += abs( fgl[ bin ]- res_gl[bin]['mean'] )
            __median += abs( fgl[ bin ]- res_gl[bin]['median'] )
            print 'bin   ', bin, '  ', fgl[bin], '  ', res_gl[bin]['mean'], ' + ', res_gl[bin]['+1sigma'], ' - ', res_gl[bin]['-1sigma'], fgl[bin]- res_gl[bin]['mean'], fgl[bin]- res_gl[bin]['median']  
        print 'delta mean = ', __mean
        print 'delta median = ', __median

        print 'mass'
        __mean, __median = 0., 0.
        for bin in range(len(pdf_mass)):
            __mean   += abs( pdf_mass[bin]- res_m[bin]['mean'] )
            __median += abs( pdf_mass[bin]- res_m[bin]['median'] )
            print 'bin   ', bin, '  ', pdf_mass[bin], '  ', res_m[bin]['mean'], ' + ', res_m[bin]['+1sigma'], ' - ', res_m[bin]['-1sigma'], pdf_mass[bin]- res_m[bin]['mean'], pdf_mass[bin]- res_m[bin]['median'] 
        print 'delta mean = ', __mean
        print 'delta median = ', __median
        
    if verbose:
        table = ''
        table+='& $%(n1).5f^{+%(n1_u).5f}_{-%(n1_d).5f}$ & $%(n2).5f^{+%(n2_u).5f}_{-%(n2_d).5f}$ & $%(n3).5f^{+%(n3_u).5f}_{-%(n3_d).5f}$ & $%(n4).5f^{+%(n4_u).5f}_{-%(n4_d).5f}$ & $%(n5).5f^{+ %(n5_u).5f}_{-%(n5_d).5f}$ & $%(n6).5f^{+%(n6_u).5f}_{-%(n6_d).5f}$ \\TTstrut\\\\' %\
                    { 'n1':   res_m[0]['median']
                     ,'n2':   res_m[1]['median']
                     ,'n3':   res_m[2]['median']
                     ,'n4':   res_m[3]['median']
                     ,'n5':   res_m[4]['median']
                     ,'n6':   res_m[5]['median']
                     ,'n1_u': res_m[0]['+1sigma delta median']
                     ,'n2_u': res_m[1]['+1sigma delta median']
                     ,'n3_u': res_m[2]['+1sigma delta median']
                     ,'n4_u': res_m[3]['+1sigma delta median']
                     ,'n5_u': res_m[4]['+1sigma delta median']
                     ,'n6_u': res_m[5]['+1sigma delta median']
                     ,'n1_d': res_m[0]['-1sigma delta median']
                     ,'n2_d': res_m[1]['-1sigma delta median']
                     ,'n3_d': res_m[2]['-1sigma delta median']
                     ,'n4_d': res_m[3]['-1sigma delta median']
                     ,'n5_d': res_m[4]['-1sigma delta median']
                     ,'n6_d': res_m[5]['-1sigma delta median']}
        table+='\n'
        print '\n\nTable mass pdf signal with errors\n'
        print table
        
        table = ''
        table+='& $%(n1).5f^{+%(n1_u).5f}_{-%(n1_d).5f}$ & $%(n2).5f^{+%(n2_u).5f}_{-%(n2_d).5f}$ & $%(n3).5f^{+%(n3_u).5f}_{-%(n3_d).5f}$ & $%(n4).5f^{+%(n4_u).5f}_{-%(n4_d).5f}$ \\TTstrut\\\\' %\
                    { 'n1':   res_gl[0]['median']
                     ,'n2':   res_gl[1]['median']
                     ,'n3':   res_gl[2]['median']
                     ,'n4':   res_gl[3]['median']
                     ,'n1_u': res_gl[0]['+1sigma delta median']
                     ,'n2_u': res_gl[1]['+1sigma delta median']
                     ,'n3_u': res_gl[2]['+1sigma delta median']
                     ,'n4_u': res_gl[3]['+1sigma delta median']
                     ,'n1_d': res_gl[0]['-1sigma delta median']
                     ,'n2_d': res_gl[1]['-1sigma delta median']
                     ,'n3_d': res_gl[2]['-1sigma delta median']
                     ,'n4_d': res_gl[3]['-1sigma delta median']}
        table+='\n'
        print '\n\nTable gl pdf signal with errors\n'
        print table


    return res_gl



def get_signal_uncertainties(bf, s_bf, _mean, _s_mean, _binning, n_toys=100, verbose=False, other_binning=None ):#, _CHANNEL=CHANNEL, mass_binning=mass_binning[CHANNEL]):

    
    print '   BF = ', bf * 1e-9, ' +/- ', s_bf * 1e-9
    
    l_sig = []
        
    for i in range(n_toys):
        print '\n trial number ', i
        fgl = convert_tofractions(N_sig_gl, Ntis_hh, error = [sN_sig_gl, sNtis_hh])
        pdf_mass = split_in_bins_cbs_roofit(_mean, sigma, a, _binning, error = [_s_mean, s_sigma, s_a], other_binning=other_binning)#, further_syst=sn_MC)
        print fgl
        print pdf_mass   
        signal = do_sig_pdf( pdf_mass, fgl, h_sig.Clone(), number_bin_GL =4, number_bin_mass=6)
        alpha_ = normal_(alpha, s_alpha)
        print 'norm ',  alpha_
        bf_ = normal_(bf, s_bf)
        print 'bf ',  bf_
        factor_sig = bf_* 1e-9 / alpha_
        signal_expected     = signal   .Clone()
        signal_expected    .Scale( factor_sig )
        print 'signal total ',  signal_expected.Integral()
        
        l_sig.append( [] )
        #import code; code.interact(local=locals())
        for bin in range(signal_expected.GetNbinsX()):
            l_sig[-1].append(  signal_expected.GetBinContent( bin+1 )  )
        
        signal_expected.Delete()
    
    #compute the median, average, and sigmas
    res = []
    for i in range( len(l_sig[-1] )):
        res.append( {} )
        res[-1]['bin'] = i
        res[-1]['list_bin'] = []
        for j in range(n_toys):
            res[-1]['list_bin'].append( l_sig[j][i] )
    
    for item in res:
        item['sig mean']    = sum( item['list_bin'] )/float(len( item['list_bin'] )) # mean  
        tmp = [] ; tmp[:] = item['list_bin'][:]
        tmp.sort()
        item['sig median']  = tmp[int(len(tmp)/2.)]            # median CLs  
        item['sig -1sigma'] = tmp[int(ceil(17*len(tmp)/100.))] # -1sigma mean CLs
        item['sig +1sigma'] = tmp[int(ceil(85*len(tmp)/100.))] # +1sigma mean CLs
        item['sig -1sigma delta mean'] = abs( item['sig mean'] - item['sig -1sigma'] ) # 
        item['sig +1sigma delta mean'] = abs( item['sig mean'] - item['sig +1sigma'] ) # 
        item['sig -1sigma delta median'] = abs( item['sig median'] - item['sig -1sigma'] ) # 
        item['sig +1sigma delta median'] = abs( item['sig median'] - item['sig +1sigma'] ) # 
    
    
    if verbose:
        print 'reference'
        fgl = convert_tofractions(N_sig_gl, Ntis_hh)
        pdf_mass = split_in_bins_cbs_roofit(_mean, sigma, a, _binning, other_binning=other_binning)
        print fgl, sum(fgl)
        print pdf_mass , sum(  pdf_mass) 
        signal = do_sig_pdf( pdf_mass, fgl, h_sig.Clone(), number_bin_GL =4, number_bin_mass=6)    
        print 'norm ',  alpha   
        factor_sig = bf* 1e-9 / alpha
        signal_expected     = signal   .Clone()
        signal_expected    .Scale( factor_sig )
        print 'signal tot ',  signal_expected    .   Integral()
        __mean, __median = 0., 0.
        for bin in range(signal_expected.GetNbinsX()):
            __mean   += abs( signal_expected.GetBinContent( bin+1 )- res[bin]['sig mean'] )
            __median += abs( signal_expected.GetBinContent( bin+1 )- res[bin]['sig median'] )
            print 'bin   ', bin+1, '  ', signal_expected.GetBinContent( bin+1 ), '  ', res[bin]['sig mean'], ' + ', res[bin]['sig +1sigma'], ' - ', res[bin]['sig -1sigma'], signal_expected.GetBinContent( bin+1 )- res[bin]['sig mean'], signal_expected.GetBinContent( bin+1 )- res[bin]['sig median'] 
        
            
        print 'delta mean = ', __mean
        print 'delta median = ', __median
    
    
        table = ''
        for i in range(6):
            if CHANNEL == 'Bs':
                table+='& $%(n1).5f^{+%(n1_u).5f}_{-%(n1_d).5f}$ & $%(n2).5f^{+%(n2_u).5f}_{-%(n2_d).5f}$ & $%(n3).5f^{+%(n3_u).5f}_{-%(n3_d).5f}$ & $%(n4).5f^{+%(n4_u).5f}_{-%(n4_d).5f}$ \\TTstrut\\\\' %\
                    { 'n1':   res[i   ]['sig median']#signal_expected.GetBinContent( i+1 )
                     ,'n2':   res[i+6 ]['sig median']#signal_expected.GetBinContent( i+7 )
                     ,'n3':   res[i+12]['sig median']#signal_expected.GetBinContent( i+13)
                     ,'n4':   res[i+18]['sig median']#signal_expected.GetBinContent( i+19)
                     ,'n1_u': res[i]   ['sig +1sigma delta median']
                     ,'n2_u': res[i+6 ]['sig +1sigma delta median']
                     ,'n3_u': res[i+12]['sig +1sigma delta median']
                     ,'n4_u': res[i+18]['sig +1sigma delta median']
                     ,'n1_d': res[i]   ['sig -1sigma delta median']
                     ,'n2_d': res[i+6 ]['sig -1sigma delta median']
                     ,'n3_d': res[i+12]['sig -1sigma delta median']
                     ,'n4_d': res[i+18]['sig -1sigma delta median']}
            else:
                table+='& $%(n1).5f^{+%(n1_u).5f}_{-%(n1_d).5f}$ & $%(n2).5f^{+%(n2_u).5f}_{-%(n2_d).5f}$ & $%(n3).5f^{+ %(n3_u).5f}_{-%(n3_d).5f}$ & $%(n4).5f^{+%(n4_u).5f}_{-%(n4_d).5f}$ \\TTstrut\\\\' %\
                    { 'n1':   res[i   ]['sig median']#signal_expected.GetBinContent( i+1 )
                     ,'n2':   res[i+6 ]['sig median']#signal_expected.GetBinContent( i+7 )
                     ,'n3':   res[i+12]['sig median']#signal_expected.GetBinContent( i+13)
                     ,'n4':   res[i+18]['sig median']#signal_expected.GetBinContent( i+19)
                     ,'n1_u': res[i]   ['sig +1sigma delta median']
                     ,'n2_u': res[i+6 ]['sig +1sigma delta median']
                     ,'n3_u': res[i+12]['sig +1sigma delta median']
                     ,'n4_u': res[i+18]['sig +1sigma delta median']
                     ,'n1_d': res[i]   ['sig -1sigma delta median']
                     ,'n2_d': res[i+6 ]['sig -1sigma delta median']
                     ,'n3_d': res[i+12]['sig -1sigma delta median']
                     ,'n4_d': res[i+18]['sig -1sigma delta median']}
                
            table+='\n'
        print table
        signal_expected    .Delete()    
    
    return res



def get_misid_uncertainties(n_toys= 100, verbose=False, AllPositive=False, TestAllPositive=False):
    
    l_sig = []
    
    for i in range(n_toys):
        print '\n trial number ', i
        misid_expected = do_misID_exp_2011(misIDN, misIDf,  misID_hist_central_1D, error = [s_misIDN, s_misIDf,  misID_hist_ErrN_1D, misID_hist_ErrP_1D], number_bin_GL =4, number_bin_mass=6, AllPositive=AllPositive, TestAllPositive=TestAllPositive )
        
        l_sig.append( [] )
        #import code; code.interact(local=locals())
        for bin in range(misid_expected.GetNbinsX()):
            l_sig[-1].append(  misid_expected.GetBinContent( bin+1 )  )
        
        misid_expected.Delete()
    
    #compute the median, average, and sigmas
    res = []
    for i in range( len(l_sig[-1] )):
        res.append( {} )
        res[-1]['bin'] = i
        res[-1]['list_bin'] = []
        for j in range(n_toys):
            res[-1]['list_bin'].append( l_sig[j][i] )
    
    for item in res:
        item['sig mean']    = sum( item['list_bin'] )/float(len( item['list_bin'] )) # mean  
        tmp = [] ; tmp[:] = item['list_bin'][:]
        tmp.sort()
        item['sig median']  = tmp[int(len(tmp)/2.)]            # median CLs  
        item['sig -1sigma'] = tmp[int(ceil(17*len(tmp)/100.))] # -1sigma mean CLs
        item['sig +1sigma'] = tmp[int(ceil(85*len(tmp)/100.))] # +1sigma mean CLs
        item['sig -1sigma delta mean'] = abs( item['sig mean'] - item['sig -1sigma'] ) # 
        item['sig +1sigma delta mean'] = abs( item['sig mean'] - item['sig +1sigma'] ) # 
        item['sig -1sigma delta median'] = abs( item['sig median'] - item['sig -1sigma'] ) # 
        item['sig +1sigma delta median'] = abs( item['sig median'] - item['sig +1sigma'] ) # 
    
    
    if verbose:
        print 'reference'
        misid_expected = do_misID_exp_2011(misIDN, misIDf,  misID_hist_central_1D, number_bin_GL =4, number_bin_mass=6 )

        print 'bin       ref         mean    +1sigma    -1 sigma    diff wrt mean     diff wrt median '
        __mean, __median, tot_mean, tot_median = 0., 0., 0., 0.
        for bin in range(misid_expected.GetNbinsX()):
            tot_median      += res[bin]['sig median']
            tot_mean        += res[bin]['sig mean']
            __mean   += abs( misid_expected.GetBinContent( bin+1 )- res[bin]['sig mean'] )
            __median += abs( misid_expected.GetBinContent( bin+1 )- res[bin]['sig median'] )
            print 'bin   ', bin+1, '  ', misid_expected.GetBinContent( bin+1 ), '  ', res[bin]['sig mean'], ' + ', res[bin]['sig +1sigma'], ' - ', res[bin]['sig -1sigma'], misid_expected.GetBinContent( bin+1 )- res[bin]['sig mean'], misid_expected.GetBinContent( bin+1 )- res[bin]['sig median'] 
        
            
        print 'delta mean = ', __mean
        print 'delta median = ', __median
    
        

        print 'ref  tot   ',  misid_expected.Integral()
        print 'mean  tot  ',  tot_mean 
        print 'median tot ',  tot_median 
       
        table = ''
        for i in range(6):
            if CHANNEL == 'Bs':
                table+='& $%(n1).5f^{+%(n1_u).5f}_{-%(n1_d).5f}$ & $%(n2).5f^{+%(n2_u).5f}_{-%(n2_d).5f}$ & $%(n3).5f^{+%(n3_u).5f}_{-%(n3_d).5f}$ & $%(n4).5f^{+%(n4_u).5f}_{-%(n4_d).5f}$ \\TTstrut\\\\' %\
                    { 'n1':   res[i   ]['sig median']#misid_expected.GetBinContent( i+1 )
                     ,'n2':   res[i+6 ]['sig median']#misid_expected.GetBinContent( i+7 )
                     ,'n3':   res[i+12]['sig median']#misid_expected.GetBinContent( i+13)
                     ,'n4':   res[i+18]['sig median']#misid_expected.GetBinContent( i+19)
                     ,'n1_u': res[i]   ['sig +1sigma delta median']
                     ,'n2_u': res[i+6 ]['sig +1sigma delta median']
                     ,'n3_u': res[i+12]['sig +1sigma delta median']
                     ,'n4_u': res[i+18]['sig +1sigma delta median']
                     ,'n1_d': res[i]   ['sig -1sigma delta median']
                     ,'n2_d': res[i+6 ]['sig -1sigma delta median']
                     ,'n3_d': res[i+12]['sig -1sigma delta median']
                     ,'n4_d': res[i+18]['sig -1sigma delta median']}
            else:
                table+='& $%(n1).5f^{+%(n1_u).5f}_{-%(n1_d).5f}$ & $%(n2).5f^{+%(n2_u).5f}_{-%(n2_d).5f}$ & $%(n3).5f^{+ %(n3_u).5f}_{-%(n3_d).5f}$ & $%(n4).5f^{+%(n4_u).5f}_{-%(n4_d).5f}$ \\TTstrut\\\\' %\
                    { 'n1':   res[i   ]['sig median']#misid_expected.GetBinContent( i+1 )
                     ,'n2':   res[i+6 ]['sig median']#misid_expected.GetBinContent( i+7 )
                     ,'n3':   res[i+12]['sig median']#misid_expected.GetBinContent( i+13)
                     ,'n4':   res[i+18]['sig median']#misid_expected.GetBinContent( i+19)
                     ,'n1_u': res[i]   ['sig +1sigma delta median']
                     ,'n2_u': res[i+6 ]['sig +1sigma delta median']
                     ,'n3_u': res[i+12]['sig +1sigma delta median']
                     ,'n4_u': res[i+18]['sig +1sigma delta median']
                     ,'n1_d': res[i]   ['sig -1sigma delta median']
                     ,'n2_d': res[i+6 ]['sig -1sigma delta median']
                     ,'n3_d': res[i+12]['sig -1sigma delta median']
                     ,'n4_d': res[i+18]['sig -1sigma delta median']}
                
            table+='\n'
        print table
        misid_expected    .Delete()    
    
    return res



def get_bkg_GL_uncertainties(n_toys= 10000, verbose=False, other_error=None, no_errors=False):
    

    l_bkg = []
    l_N, l_k = [],  []
    
    if other_error:
        error_ = other_error
    else:
        error_ = [s_Nsb, [s_idxN, s_idxP]]
        
    for i in range(n_toys):
        print '\n trial number ', i

        if no_errors:
            background_expected, N_, k_  = do_bkg_exp_2011(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass, only_hist=False)
        else:
            background_expected, N_, k_  = do_bkg_exp_2011(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass, error = error_ , only_hist=False)
        l_N.append( N_[-1] )
        l_k.append( k_[-1] )
        
        l_bkg.append( [] )
        #import code; code.interact(local=locals())
        for bin in range( background_expected.GetNbinsX() ):
            l_bkg[-1].append( background_expected.GetBinContent( bin+1 ) )#expected.GetBinContent( bin )+ background_expected.GetBinContent( bin+1 )+ background_expected.GetBinContent( bin+2 )+ background_expected.GetBinContent( bin+3 )+ background_expected.GetBinContent( bin+4 )+ background_expected.GetBinContent( bin+5 )  )
        
        background_expected.Delete()
    
    #compute the median, average, and sigmas
    res = []
    for i in range( len(l_bkg[-1] )):
        res.append( {} )
        res[-1]['bin'] = i
        res[-1]['list_bin'] = []
        for j in range(n_toys):
            res[-1]['list_bin'].append( l_bkg[j][i] )
    
    for item in res:
        item['sig mean']    = sum( item['list_bin'] )/float(len( item['list_bin'] )) # mean  
        tmp = [] ; tmp[:] = item['list_bin'][:]
        tmp.sort()
        item['sig median']  = tmp[int(len(tmp)/2.)]            # median CLs  
        item['sig -1sigma'] = tmp[int(ceil(17*len(tmp)/100.))] # -1sigma mean CLs
        item['sig +1sigma'] = tmp[int(ceil(85*len(tmp)/100.))] # +1sigma mean CLs
        item['sig -1sigma delta mean'] = abs( item['sig mean'] - item['sig -1sigma'] ) # 
        item['sig +1sigma delta mean'] = abs( item['sig mean'] - item['sig +1sigma'] ) # 
        item['sig -1sigma delta median'] = abs( item['sig median'] - item['sig -1sigma'] ) # 
        item['sig +1sigma delta median'] = abs( item['sig median'] - item['sig +1sigma'] ) # 



    list_val = []
    for val in res[3]['list_bin']:
        list_val.append( val )
    
    
    histo = TH1F( 'histo', 'histo', 101, min(list_val), max(list_val) )
    for cl in list_val:
        histo.Fill( cl )
    
    histo.Draw()

    #import code; code.interact(local=locals())

    print l_N
    histo_N = TH1F( 'histoN', 'histoN', 101, min(l_N), max(l_N) )
    for cl in l_N:
        histo_N.Fill( cl )
    
    histo_N.Draw()

    #import code; code.interact(local=locals())

    histo_k = TH1F( 'histo_k', 'histo_k', 101, min(l_k), max(l_k) )
    for cl in l_k:
        histo_k.Fill( cl )
    
    histo_k.Draw()
    
    #import code; code.interact(local=locals())
    
    if verbose:
        print 'reference'

        background_expected  = do_bkg_exp(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)
        __mean, __median = 0., 0.

        background_expected_gl = [background_expected.GetBinContent( 1 )+ background_expected.GetBinContent( 2 )+ background_expected.GetBinContent( 3 )+ background_expected.GetBinContent( 4 )+ background_expected.GetBinContent( 5 )+ background_expected.GetBinContent( 6 )
                                  ,background_expected.GetBinContent( 6+1 )+ background_expected.GetBinContent( 6+2 )+ background_expected.GetBinContent( 6+3 )+ background_expected.GetBinContent( 6+4 )+ background_expected.GetBinContent( 6+5 )+ background_expected.GetBinContent( 6+6 )
                                  ,background_expected.GetBinContent( 12+1 )+ background_expected.GetBinContent( 12+2 )+ background_expected.GetBinContent( 12+3 )+ background_expected.GetBinContent( 12+4 )+ background_expected.GetBinContent( 12+5 )+ background_expected.GetBinContent( 12+6 )
                                  ,background_expected.GetBinContent( 18+1 )+ background_expected.GetBinContent( 18+2 )+ background_expected.GetBinContent( 18+3 )+ background_expected.GetBinContent( 18+4 )+ background_expected.GetBinContent( 18+5 )+ background_expected.GetBinContent( 18+6 )]

##         for bin in range(4):
##             __mean   += abs( background_expected_gl[bin]- res[bin]['sig mean'] )
##             __median += abs( background_expected_gl[bin]- res[bin]['sig median'] )
##             print 'bin   ', bin+1, '  ', background_expected_gl[bin], '  ', res[bin]['sig mean'], res[bin]['sig median'], ' + ', res[bin]['sig +1sigma']-res[bin]['sig mean'], ' - ', res[bin]['sig mean']-res[bin]['sig -1sigma'], background_expected_gl[bin]- res[bin]['sig mean'], background_expected_gl[bin]- res[bin]['sig median'] 


        print 'bin        expec_central    mean     median      mean+1sigma     mean-1sigma          expec-mean         expec-median '
        for bin in range(len(res)):
            __mean   += abs( background_expected[bin+1]- res[bin]['sig mean'] )
            __median += abs( background_expected[bin+1]- res[bin]['sig median'] )
            
            print 'bin   ', bin+1, '  ', background_expected[bin+1], '  ', res[bin]['sig mean'], res[bin]['sig median'], ' + ', res[bin]['sig +1sigma']-res[bin]['sig mean'], ' - ', res[bin]['sig mean']-res[bin]['sig -1sigma'], background_expected[bin+1]- res[bin]['sig mean'], background_expected[bin+1]- res[bin]['sig median'] 
        
        print 'delta mean = ', __mean
        print 'delta median = ', __median

        table = ''
        for i in range(6):
            #if CHANNEL == 'Bs':
                table+='& $%(n1).5f^{+%(n1_u).5f}_{-%(n1_d).5f}$ & $%(n2).5f^{+%(n2_u).5f}_{-%(n2_d).5f}$ & $%(n3).5f^{+%(n3_u).5f}_{-%(n3_d).5f}$ & $%(n4).5f^{+%(n4_u).5f}_{-%(n4_d).5f}$ \\TTstrut\\\\' %\
                    { 'n1':   res[i   ]['sig median']#background_expected.GetBinContent( i+1 )
                     ,'n2':   res[i+6 ]['sig median']#background_expected.GetBinContent( i+7 )
                     ,'n3':   res[i+12]['sig median']#background_expected.GetBinContent( i+13)
                     ,'n4':   res[i+18]['sig median']#background_expected.GetBinContent( i+19)
                     ,'n1_u': res[i]   ['sig +1sigma delta median']
                     ,'n2_u': res[i+6 ]['sig +1sigma delta median']
                     ,'n3_u': res[i+12]['sig +1sigma delta median']
                     ,'n4_u': res[i+18]['sig +1sigma delta median']
                     ,'n1_d': res[i]   ['sig -1sigma delta median']
                     ,'n2_d': res[i+6 ]['sig -1sigma delta median']
                     ,'n3_d': res[i+12]['sig -1sigma delta median']
                     ,'n4_d': res[i+18]['sig -1sigma delta median']}
                table+='\n'
        print '\n\n'+table+'\n'

        i=0
        table='& $%(n1).5f^{+%(n1_u).5f}_{-%(n1_d).5f}$ & $%(n2).5f^{+%(n2_u).5f}_{-%(n2_d).5f}$ & $%(n3).5f^{+%(n3_u).5f}_{-%(n3_d).5f}$ & $%(n4).5f^{+%(n4_u).5f}_{-%(n4_d).5f}$ \\TTstrut\\\\' %\
                    { 'n1':   background_expected.GetBinContent( i+1 ) + background_expected.GetBinContent( i+2 )+ background_expected.GetBinContent( i+3 ) + background_expected.GetBinContent( i+4 ) + background_expected.GetBinContent( i+5 ) + background_expected.GetBinContent( i+6 )
                     ,'n2':   background_expected.GetBinContent( i+7 ) + background_expected.GetBinContent( i+6+2 )+ background_expected.GetBinContent( i+6+3 ) + background_expected.GetBinContent( i+6+4 ) + background_expected.GetBinContent( i+6+5 ) + background_expected.GetBinContent( i+6+6 )
                     ,'n3':   background_expected.GetBinContent( i+13) + background_expected.GetBinContent( i+12+2 )+ background_expected.GetBinContent( i+12+3 ) + background_expected.GetBinContent( i+12+4 ) + background_expected.GetBinContent( i+12+5 ) + background_expected.GetBinContent( i+12+6 )#res[i+12]['sig median']
                     ,'n4':   background_expected.GetBinContent( i+19) + background_expected.GetBinContent( i+18+2 )+ background_expected.GetBinContent( i+18+3 ) + background_expected.GetBinContent( i+18+4 ) + background_expected.GetBinContent( i+18+5 ) + background_expected.GetBinContent( i+18+6 )#res[i+18]['sig median']
                     ,'n1_u': res[i]   ['sig +1sigma delta median']+res[i+1]['sig +1sigma delta median']+res[i+2]['sig +1sigma delta median']+res[i+3]['sig +1sigma delta median']+res[i+4]['sig +1sigma delta median']+res[i+5]['sig +1sigma delta median']
                     ,'n2_u': res[i+6 ]['sig +1sigma delta median']+res[i+6+1]['sig +1sigma delta median']+res[i+6+2 ]['sig +1sigma delta median']+res[i+6+3 ]['sig +1sigma delta median']+res[i+6+4 ]['sig +1sigma delta median']+res[i+6+5 ]['sig +1sigma delta median']
                     ,'n3_u': res[i+12]['sig +1sigma delta median']+res[i+12+1]['sig +1sigma delta median']+res[i+12+2]['sig +1sigma delta median']+res[i+12+3]['sig +1sigma delta median']+res[i+12+4]['sig +1sigma delta median']+res[i+12+5]['sig +1sigma delta median']
                     ,'n4_u': res[i+18]['sig +1sigma delta median']+res[i+18+1]['sig +1sigma delta median']+res[i+18+2]['sig +1sigma delta median']+res[i+18+3]['sig +1sigma delta median']+res[i+18+4]['sig +1sigma delta median']+res[i+18+5]['sig +1sigma delta median']
                     ,'n1_d': res[i]['sig -1sigma delta median']+res[i+1]['sig -1sigma delta median']+res[i+2]['sig -1sigma delta median']+res[i+3]['sig -1sigma delta median']+res[i+4]['sig -1sigma delta median']+res[i+5]['sig -1sigma delta median']
                     ,'n2_d': res[i+6 ]['sig -1sigma delta median']+res[i+6 +1]['sig -1sigma delta median']+res[i+6+2 ]['sig -1sigma delta median']+res[i+6+3 ]['sig -1sigma delta median']+res[i+6+4 ]['sig -1sigma delta median']+res[i+6+5 ]['sig -1sigma delta median']
                     ,'n3_d': res[i+12]['sig -1sigma delta median']+res[i+12+1]['sig -1sigma delta median']+res[i+12+2]['sig -1sigma delta median']+res[i+12+3]['sig -1sigma delta median']+res[i+12+4]['sig -1sigma delta median']+res[i+12+5]['sig -1sigma delta median']
                     ,'n4_d': res[i+18]['sig -1sigma delta median']+res[i+18+1]['sig -1sigma delta median']+res[i+18+2]['sig -1sigma delta median']+res[i+18+3]['sig -1sigma delta median']+res[i+18+4]['sig -1sigma delta median']+res[i+18+5]['sig -1sigma delta median']}

        #import code; code.interact(local=locals()) 
        background_expected    .Delete()    
    
    return res


##C choose the decay you want to consider

CHANNEL =    'B0' #    'Bs' #
discriminant =  'BDT' #'GL' #
path_to_input = '/afs/cern.ch/user/m/mbettler/cmtuser/Phys/Bs2MuMuParams/'
input_table = 'toytable_eps_bdt'


sys.path.append(path_to_input+'/python/Bs2MuMuParams/')
Input = __import__(input_table)


###  INPUTS  ############

bsmass_pdg = 5366.3
b0mass_pdg = 5279.5

### data

##C choose the inputfile for the data
if CHANNEL == 'Bs':
    data_file_name = path_to_input+'histos/DataBs.root'
    data_hist_name = 'data 2011'
if CHANNEL == 'B0':
    data_file_name = path_to_input+'histos/DataBd.root'
    data_hist_name = 'data 2011'
    


### Normalization ############

c_bu   = Input.NormBu      #(normalization factor of B+->JPsiK+ for B_*d* ->mumu) 
sc_bu  = Input.NormBuErr 

c_phi  = Input.NormPhi    #(normalization factor of Bs->JPsiPhi for B_*s* ->mumu)
sc_phi = Input.NormPhiErr 

b_kpi  = Input.NormKPi   
sb_kpi = Input.NormKPiErr

Ntis_hh  = Input.TisTot
sNtis_hh = Input.TisErrTot

fdfs   = Input.fsfd    # (sic!)
s_fdfs = Input.fsfdErr

c_kpi, sc_kpi = do_kpi_coef( b_kpi, sb_kpi, Ntis_hh, sNtis_hh )

alpha, s_alpha = calculateNormalizationFactor( c_bu, c_phi, c_kpi, sc_bu, sc_phi, sc_kpi, fdfs, s_fdfs, CHANNEL)


### Signal GL pdf ############ 

GL_binning   = [ 0., 0.25, 0.5, 0.75, 1. ]

N_sig_gl =  [0., Input.Tis2, Input.Tis3, Input.Tis4]
sN_sig_gl = [0., Input.TisErr2, Input.TisErr3, Input.TisErr4]

justine =   [Input.Justine1, Input.Justine2, Input.Justine3, Input.Justine4]

for i  in range(1,4):
    N_sig_gl[i] =  N_sig_gl[i]/justine[i]


### Signal Mass pdf parameters ############ 

bf_SM =  { 'Bs' : 3.2,                  'B0' : 0.1 }
s_bf_SM= { 'Bs' : 0.2,                  'B0' : 0.01}
mean =   { 'Bs' : Input.MassMeanBs,    'B0' : Input.MassMeanBd }
s_mean = { 'Bs' : Input.MassMeanErrBs, 'B0' : Input.MassMeanErrBd }

mass_binning = {
     'Bs': [mean['Bs']-60., mean['Bs']-40., mean['Bs']-20., mean['Bs'], mean['Bs']+20., mean['Bs']+40., mean['Bs']+60.]
    ,'B0': [mean['B0']-60., mean['B0']-40., mean['B0']-20., mean['B0'], mean['B0']+20., mean['B0']+40., mean['B0']+60.]} 

sigma   = Input.MassReso
s_sigma = Input.MassResoErr

a   = Input.CBTrans
s_a = Input.CBTransErr

#sn_MC = [0.063, -0.054, 0.018, 0.033, -0.037, -0.056] #todo


### exponential index in sidebands

idx_gl =  [ Input.BkgMassk1,  Input.BkgMassk2,  Input.BkgMassk3,  Input.BkgMassk4 ]

s_idxP =  [ Input.BkgMasskErrP1, Input.BkgMasskErrP2, Input.BkgMasskErrP3, Input.BkgMasskErrP4 ]
s_idxN =  [ Input.BkgMasskErrN1, Input.BkgMasskErrN2, Input.BkgMasskErrN3, Input.BkgMasskErrN4 ]
s_idx =   [ (Input.BkgMasskErrP1-Input.BkgMasskErrN1)*0.5,  (Input.BkgMasskErrP2-Input.BkgMasskErrN2)*0.5
           ,(Input.BkgMasskErrP3-Input.BkgMasskErrN3)*0.5,  (Input.BkgMasskErrP4-Input.BkgMasskErrN4)*0.5 ]

Nsb   =   [ Input.SbGL1, Input.SbGL2, Input.SbGL3, Input.SbGL4 ]
#s_Nsb   = map ( lambda x : sqrt(x), Nsb )
s_Nsb =  [sqrt(Input.SbGL1+ (Input.SystBkgBin1 * Input.SbGL1)**2), -999., -999., -999.]

Nsb_range = [[ Input.GL1MassSb1, Input.GL1MassSb2, Input.GL1MassSb3, Input.GL1MassSb4]
             ,[Input.GL2MassSb1, Input.GL2MassSb2, Input.GL2MassSb3, Input.GL2MassSb4]
             ,[Input.GL3MassSb1, Input.GL3MassSb2, Input.GL3MassSb3, Input.GL3MassSb4]
             ,[Input.GL4MassSb1, Input.GL4MassSb2, Input.GL4MassSb3, Input.GL4MassSb4]]


# bhh misid

misIDN   = Input.MisIDN
s_misIDN = Input.MisIDNErr

if CHANNEL == 'Bs':
    misIDf   = Input.MisIDfBs
    s_misIDf = Input.MisIDfErrBs
    file_misIDhist = TFile(path_to_input+'histos/misidBs.root', 'READ')
    misID_hist_central_2D = file_misIDhist.Get('missid 2011')
    misID_hist_ErrN_2D    = file_misIDhist.Get('missid 2011 u')
    misID_hist_ErrP_2D    = file_misIDhist.Get('missid 2011 o')
    misID_hist_central_1D = transform_2D_in_1D( misID_hist_central_2D )
    misID_hist_ErrN_1D    = transform_2D_in_1D( misID_hist_ErrN_2D )
    misID_hist_ErrP_1D    = transform_2D_in_1D( misID_hist_ErrP_2D )
    
elif CHANNEL == 'B0':
    misIDf   = Input.MisIDfBd
    s_misIDf = Input.MisIDfErrBd
    file_misIDhist = TFile(path_to_input+'histos/misidBd.root', 'READ')
    misID_hist_central_2D = file_misIDhist.Get('missid 2011')
    misID_hist_ErrN_2D    = file_misIDhist.Get('missid 2011 o')
    misID_hist_ErrP_2D    = file_misIDhist.Get('missid 2011 u')
    misID_hist_central_1D = transform_2D_in_1D( misID_hist_central_2D )
    misID_hist_ErrN_1D    = transform_2D_in_1D( misID_hist_ErrN_2D )
    misID_hist_ErrP_1D    = transform_2D_in_1D( misID_hist_ErrP_2D )



number_bin_GL     = len(GL_binning)-1
number_bin_mass   = len(mass_binning[CHANNEL])-1
number_of_bins_1D = number_bin_GL * number_bin_mass

h_sig = TH1F ( 'Sig_histogram', 'Sig_histogram'
                  , number_of_bins_1D , 0, number_of_bins_1D)
h_bkg = TH1F ( 'Bkg_histogram', 'Bkg_histogram'
                  , number_of_bins_1D , 0, number_of_bins_1D)

test_error = False
if test_error == True:

    fgl_err = convert_tofractions(N_sig_gl, Ntis_hh, error = [sN_sig_gl, sNtis_hh])#, further_syst=sn_MC)
    pdf_mass_err = split_in_bins_cbs_roofit(mean[CHANNEL], sigma, a, mass_binning[CHANNEL], error = [s_mean[CHANNEL], s_sigma, s_a])
    background_expected_err  = do_bkg_exp_2011(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg, number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass, error = [s_Nsb, [s_idxN, s_idxP]])
    #background_expected_err  = do_bkg_exp(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg, number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass, error = [s_Nsb, s_idx])
    alpha_err = normal_(alpha, s_alpha)
    signal_err = do_sig_pdf( pdf_mass_err, fgl_err, h_sig, number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)
    
    fgl = convert_tofractions(N_sig_gl, Ntis_hh)
    pdf_mass = split_in_bins_cbs_roofit(mean[CHANNEL], sigma, a, mass_binning[CHANNEL])
    h_bkg__ = h_bkg.Clone()
    background_expected  = do_bkg_exp(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg__, number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)
    h_sig__ = h_sig.Clone()
    signal = do_sig_pdf( pdf_mass, fgl, h_sig__, number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)

    print 'fgl' 
    for i in range(len(fgl)):
        print fgl_err[i] - fgl[i]
    print 'pdf_mass' 
    for i in range(len(pdf_mass)):
        print pdf_mass_err[i] - pdf_mass[i]
    print 'Signal 2D pdf' 
    for i in range(signal_err.GetNbinsX()):
        print signal_err.GetBinContent(i+1) - signal.GetBinContent(i+1)
        
    print 'Back 2D pdf' 
    for i in range(background_expected.GetNbinsX()):
        print background_expected_err.GetBinContent(i+1) - background_expected.GetBinContent(i+1)
        
    import code; code.interact(local=locals())


if __name__ == '__main__':
        
    use_stat =  True ; use_error = False   # stat only
    #use_stat =  False; use_error = True    # syst only
    #use_stat =  True ; use_error = True    # both
    use_stat =  False; use_error = False   # neither
    
    type = 'limit' #'sensitivity' #
    mode = 'exclusion' # 'observation' #
    get_all_CLs = True #False #
    get_Diego_CLs = False #True #
        
    trials_number = 100
    
    if CHANNEL == 'Bs':
        bf_list =  range(1,30,2)#range(2,30,4)#range(35,57,4)# range(14,80,2)#range(16,80,4)#range(78,100,3)#
    if CHANNEL == 'B0':
        bf_list =  map(lambda x: x*0.5, range(1,40,1)) #range(3,40,1)#range(6,30,4)#
    
    lumi_list = [1.]
    
    if type == 'limit' :
        data = TH1F ( 'Obs_histogram', 'Obs_histogram', number_bin_GL*number_bin_mass, 0, number_bin_GL*number_bin_mass )
        data = from_Diego2D_to_mine( data, data_file_name, data_hist_name )
        # data = fake_data_with_high_BF(data, 50)
        #data = get_data_ntuple(data, t, mass_binning[CHANNEL], GL_binning, 'GLKsm_MC10sb.', 'Bmass', ismu_name1='mu1ismu', ismu_name2='mu2ismu', verbose=True )        
        print 'data'
        #import code; code.interact(local=locals())      
    
    fgl      = convert_tofractions(N_sig_gl, Ntis_hh)
    pdf_mass = split_in_bins_cbs_roofit(mean[CHANNEL], sigma, a, mass_binning[CHANNEL])
    signal   = do_sig_pdf( pdf_mass, fgl, h_sig.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)
    background_expected  = do_bkg_exp(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)
    
    print '\n\n'; print_inputs();print '\n\n'
    #import code; code.interact(local=locals())
    
##     error_bkg = TVectorD(1)
##     error_sig = TVectorD(1)
##     name1 = TObjString('sig uncertainty')
##     #name2 = TObjString('bkg uncertainty')

##     error_names  = TObjArray()
##     error_names.AddLast(name1)
##     #error_names.AddLast(name2)

##     error_bkg[0]=0. ## error source 1: 5%
##     error_sig[0]=0.5## error source 2: 0%
    
    
    
    bf_solution, CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution = [], [], [], [], []
    print '*************************************************'
    print '* Initialisation finished iterations will begin *'
    print '*************************************************'

    # todo
    #void = get_bkg_GL_uncertainties( n_toys= 15000, verbose=True )
    #void = get_misid_uncertainties( n_toys = 15000, verbose = True, AllPositive=True, TestAllPositive=True)
    #void = get_signal_uncertainties( bf_SM[CHANNEL], s_bf_SM[CHANNEL], mean[CHANNEL], s_mean[CHANNEL], mass_binning[CHANNEL], n_toys = 15000,  verbose=True)
    
    #do_GL_plot_sig_bkg(fgl,background_expected )
    #get_signal_pdfs_uncertainties()
    #AlaCDF(bf_SM, s_bf_SM, mass_binning, mean, s_mean, CHANNEL, data, nb_toys=15000, cross_pollution=False)
    AlaCDF(bf_SM, s_bf_SM, mass_binning, mean, s_mean, CHANNEL, data, nb_toys=150, cross_pollution=False)
    
    #print_data(data)    
    
    import code; code.interact(local=locals())
    
    ## background_expected = do_bkg_exp(Nsb[:-1]+[13.], idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg, number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)
    
##     background_expected_gl = [background_expected.GetBinContent( 1 )+ background_expected.GetBinContent( 2 )+ background_expected.GetBinContent( 3 )+ background_expected.GetBinContent( 4 )+ background_expected.GetBinContent( 5 )+ background_expected.GetBinContent( 6 )
##                                   ,background_expected.GetBinContent( 6+1 )+ background_expected.GetBinContent( 6+2 )+ background_expected.GetBinContent( 6+3 )+ background_expected.GetBinContent( 6+4 )+ background_expected.GetBinContent( 6+5 )+ background_expected.GetBinContent( 6+6 )
##                                   ,background_expected.GetBinContent( 12+1 )+ background_expected.GetBinContent( 12+2 )+ background_expected.GetBinContent( 12+3 )+ background_expected.GetBinContent( 12+4 )+ background_expected.GetBinContent( 12+5 )+ background_expected.GetBinContent( 12+6 )
##                                   ,background_expected.GetBinContent( 18+1 )+ background_expected.GetBinContent( 18+2 )+ background_expected.GetBinContent( 18+3 )+ background_expected.GetBinContent( 18+4 )+ background_expected.GetBinContent( 18+5 )+ background_expected.GetBinContent( 18+6 )]
##     for bin in range(4):
##         print 'bin   ', bin+1, '  ', background_expected_gl[bin]
        
##    import code; code.interact(local=locals())
    
    
    # loop on Lumi
    for lumi in lumi_list :
    
        print 'Assessing luminosity = ', lumi
        
        for trial in range( trials_number ):
        
            print '++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++'
            print '  trial ', trial, ' on ', trials_number
            
            tmp_bf, tmp_CLs, tmp_CLb, tmp_CLs_D, tmp_CLb_D = [], [], [], [], []
            
            # loop on BF hypotheses
            for bf in bf_list:
            
                print '---------------------------------------'
                print '   BF = ', bf * 1e-9
                
                alpha_ = alpha
                
                if use_error:
                    fgl = convert_tofractions(N_sig_gl, Ntis_hh, error = [sN_sig_gl, sNtis_hh])
                    pdf_mass = split_in_bins_cbs_roofit(mean[CHANNEL], sigma, a, mass_binning[CHANNEL], error = [s_mean[CHANNEL], s_sigma, s_a])
                    background_expected  = do_bkg_exp(Nsb, idx_gl, Nsb_range, mass_binning[CHANNEL], h_bkg.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass, error = [s_Nsb, s_idx])
                    signal = do_sig_pdf( pdf_mass, fgl, h_sig.Clone(), number_bin_GL =number_bin_GL, number_bin_mass=number_bin_mass)
                    
                    alpha_ = normal_( alpha, s_alpha )
                    #print '\n\nATTENTION GROS HACK!!'; alpha_ = normal_(alpha, 0.5*alpha)
                    print 'norm ',  alpha_
                    
                
                factor_bkg = float( background_expected.Integral() )
                background = background_expected.Clone()
                background.Scale( 1./factor_bkg )
                
                factor_sig = bf* 1e-9 / alpha_
                signal_expected = signal.Clone()
                signal_expected.Scale( factor_sig )

                CMS = False
                if CMS:
                    factor_sig = bf/3.2
                    signal_expected = TH1F('CMS sig', 'CMS sig', 2, 0,1)
                    signal_expected.SetBinContent(1, 0.76 )
                    signal_expected.SetBinContent(2, 0.34 )
                    signal_expected.Scale( factor_sig )
                    background_expected.Delete()
                    background_expected = TH1F('CMS bkg', 'CMS bkg', 2, 0,1)
                    background_expected.SetBinContent(1, 0.67 )
                    background_expected.SetBinContent(2, 0.84 )
                    data.Delete()
                    data = TH1F('CMS bkg', 'CMS bkg', 2, 0,1)
                    data.SetBinContent(1, 2 )
                    data.SetBinContent(2, 1 )
                    
                
##              if use_stat:
##                     s_tmp = signal_expected.Clone()
##                     b_tmp = background_expected.Clone()
##                     multinomial_histo( h, exp_number )
                
                if type == 'sensitivity':
                    if mode == 'exclusion': 
                        observation    = poisson_multinomial_histo( signal, background, 0.        , factor_bkg )
                    elif mode == 'observation':
                        observation    = poisson_multinomial_histo( signal, background, factor_sig, factor_bkg )
                elif type == 'limit':
                    observation = data.Clone()
                
                print '       Yields sig ', signal_expected.Integral(), ' bkg', background_expected.Integral(), ' obs', observation.Integral()
                
                mydatasource = TLimitDataSource( signal_expected, background_expected, observation)
                #mydatasource = TLimitDataSource( signal_expected, background_expected, observation, error_sig, error_bkg, error_names )
                
                myconfidence = TLimit.ComputeLimit( mydatasource, 75000, use_stat )
                
                
                CLs = myconfidence.CLs()
                CLb = myconfidence.CLb()
                
                print "       CLs    : "  , myconfidence.CLs()  
                print "       CLsb   : "  , myconfidence.CLsb() 
                print "       CLb    : "  , myconfidence.CLb()  
                print "       < CLs >  : ", myconfidence.GetExpectedCLs_b()  
                print "       < CLsb > : ", myconfidence.GetExpectedCLsb_b() 
                print "       < CLb >  : ", myconfidence.GetExpectedCLb_b()  
                
                if get_Diego_CLs:
                    CLs_D, CLb_D, CLsb_D  = getDiego_output( signal_expected, background_expected, observation )
                    print "       CLsD    : "  , CLs_D
                    print "       CLsbD   : "  , CLsb_D
                    print "       CLbD    : "  , CLb_D
                
                signal_expected    .Delete()
                #background_expected.Delete()
                observation        .Delete()
                mydatasource       .Delete()
                myconfidence       .Delete()
                
                tmp_CLs.append(CLs)
                tmp_CLb.append(CLb)
                if get_Diego_CLs:
                    tmp_CLs_D.append(CLs_D)
                    tmp_CLb_D.append(CLb_D)
                
                #import code; code.interact(local=locals())
                
                if ( ( ( mode == 'exclusion' and CLs < 0.1 )
                     or (mode == 'observation' and 1-CLb > 2.7e-3 ) )
                     and get_all_CLs == False):# 90 % exclusion or observation or veto
                    
                    tmp_bf  .append( bf   )
                    print "----> ",lumi, bf
                    break
                
            bf_solution  .append( tmp_bf  )
            CLs_solution .append( tmp_CLs )
            CLb_solution .append( tmp_CLb )
            
            if get_Diego_CLs:
                CLs_D_solution .append( tmp_CLs_D )
                CLb_D_solution .append( tmp_CLb_D )
                #print 'CLs_D_solution', CLs_D_solution
                #print 'CLb_D_solution', CLb_D_solution
            
    print bf_solution

    import uuid, cPickle
    suffix = uuid.uuid4().hex
    file = open('output_'+CHANNEL+'_'+discriminant+'_'+suffix+'.marco', 'wb')
    cPickle.dump( ( bf_list, bf_solution,  CLs_solution, CLb_solution, CLs_D_solution, CLb_D_solution ), file )
    file.close()

    #import commands
    #commands.getoutput('rfcp output_'+suffix+'.marco /castor/cern.ch/user/m/mbettler/output_'+suffix+'.marco')
    #import code; code.interact(local=locals())
    
