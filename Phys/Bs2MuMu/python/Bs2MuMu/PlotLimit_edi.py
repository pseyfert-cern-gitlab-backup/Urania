from ROOT  import TH1F, THStack, TCanvas, TFile, TFrame, TRandom2, TSystem
from ROOT  import TVector, TObjArray, TObjString, TLimit, TLimitDataSource
from ROOT  import TConfidenceLevel, kBlue, gSystem, TGraph, TVectorD, gROOT
from ROOT  import TLegend, TGraphAsymmErrors, TLine, TPaveText, TTree
from ROOT  import AddressOf, TF1, TMath

from array import array
from numpy.random import poisson, multinomial, normal, randn
from ROOT_settings_marco import *
from math import sqrt, exp, ceil, floor
import cPickle

# import input values
from GetLimit_edi import GL_binning, N_sig_gl, Nsb, Nsb_range, Ntis_hh, a, b0mass_pdg, b_kpi, bf_SM, bsmass_pdg, c_bu, c_kpi, c_phi, fdfs, idx_gl, justine, mass_binning, mean, number_bin_GL, number_bin_mass, number_of_bins_1D, sN_sig_gl, sNtis_hh, s_Nsb, s_a, s_alpha, s_fdfs, s_idx, s_mean, s_sigma, sb_kpi, sc_bu, sc_kpi, sc_phi, sigma, sn_MC

# import methods
from GetLimit_edi import add_results, build_dic, build_lists_for_plots, compute_mean_median, convert_tofractions, do_GL_plot_sig_bkg, do_bkg_exp, do_kpi_coef, do_sig_pdf, fake_data_with_high_BF, from_Diego2D_to_mine, get_data_ntuple,  get_signal_pdfs_uncertainties, get_signal_uncertainties, list_to_tree, multinomial, multinomial_histo, normal, normal_, normal_signed, poisson, poisson_multinomial_histo, randn, split_in_bins_cbs, split_in_bins_cbs_roofit, import_and_build_dic

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





def get_cls_mean_exp_graph( list_of_bf, list_of_mean_CLs, list_of_neg_sigma_CLs_delta_mean , list_of_pos_sigma_CLs_delta_mean, zero ):
    
    g_mean = TGraphAsymmErrors(len( list_of_bf ), array( 'd',  list_of_bf), array( 'd', list_of_mean_CLs  )
                               , array( 'd',  zero ), array( 'd', zero  )
                               , array( 'd', list_of_neg_sigma_CLs_delta_mean  ), array( 'd', list_of_pos_sigma_CLs_delta_mean  ))
    
    
    g_mean.GetYaxis().SetTitle('CLs')
    g_mean.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-8}]')
    #g_mean.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-9}]')
    g_mean.GetYaxis().SetRangeUser(0., 0.6)
    g_mean.GetXaxis().SetRangeUser(10., 80.)
    if CHANNEL == 'B0':
        g_mean.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-8}]')
        #g_mean.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-9}]')
        g_mean.GetYaxis().SetRangeUser(0., 0.6)
        g_mean.GetXaxis().SetRangeUser(0., 18.)
    g_mean.GetYaxis().SetTitleOffset(1.4)
    g_mean.GetXaxis().SetLabelFont(62)#(162)
    g_mean.GetYaxis().SetLabelFont(62)#(162)
    g_mean.GetXaxis().SetTitleFont(62)#(162)
    g_mean.GetYaxis().SetTitleFont(62)#(162)
    g_mean.SetLineWidth(4)
    MarcoStyle.SetFillColor(3)
    g_mean.SetFillColor(3)
    g_mean.SetFillStyle(1001)
    g_mean.SetMarkerSize(2)
    g_mean.SetMarkerStyle(20)
    return g_mean



def get_clb_exp_graph( list_of_bf, list_of_mean_CLb, list_of_neg_sigma_CLb_delta, list_of_pos_sigma_CLb_delta, zero ):
    
    
    g_clb = TGraphAsymmErrors(len( list_of_bf ), array( 'd',  list_of_bf), array( 'd', list_of_mean_CLb  )
                               , array( 'd',  zero ), array( 'd', zero  )
                               , array( 'd', list_of_neg_sigma_CLb_delta  ), array( 'd', list_of_pos_sigma_CLb_delta  ) )
    
    g_clb.GetYaxis().SetTitle('CLb')
    g_clb.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-8}]')
    #g_clb.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-9}]')
    g_clb.GetYaxis().SetRangeUser(0., 1.)
    g_clb.GetXaxis().SetRangeUser(10., 62.)#(10., 80.)#
    if CHANNEL == 'B0':
        g_clb.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-8}]')
        #g_clb.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-9}]')
        g_clb.GetXaxis().SetRangeUser(2., 18.)
    
    g_clb.GetYaxis().SetTitleOffset(1.4)
    g_clb.GetXaxis().SetLabelFont(62)#(162)
    g_clb.GetYaxis().SetLabelFont(62)#(162)
    g_clb.GetXaxis().SetTitleFont(62)#(162)
    g_clb.GetYaxis().SetTitleFont(62)#(162)
    MarcoStyle.SetFillColor(3)
    g_clb.SetFillColor(407)
    g_clb.SetFillStyle(1001)
    g_clb.SetLineWidth(4)
    g_clb.SetMarkerSize(2)
    g_clb.SetMarkerStyle(20)
    return g_clb


def get_cls_median_exp_graph( list_of_bf, list_of_median_CLs , list_of_neg_sigma_CLs_delta_median , list_of_pos_sigma_CLs_delta_median , zero ):
    
    g_median = TGraphAsymmErrors(len( list_of_bf ), array( 'd',  list_of_bf), array( 'd', list_of_median_CLs  )
                               , array( 'd',  zero ), array( 'd', zero  )
                               , array( 'd', list_of_neg_sigma_CLs_delta_median  ), array( 'd', list_of_pos_sigma_CLs_delta_median  ))
    
    g_median.GetYaxis().SetTitle('CLs')
    g_median.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-8}]')
    #g_median.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-9}]')
    g_median.GetYaxis().SetRangeUser(0., 0.6)
    g_median.GetXaxis().SetRangeUser(10., 80.)
    if CHANNEL == 'B0':
        g_median.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-8}]')
        #g_median.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-9}]')
        g_median.GetYaxis().SetRangeUser(0., 0.6)
        g_median.GetXaxis().SetRangeUser(0., 18.)
    g_median.GetYaxis().SetTitleOffset(1.4)
    g_median.GetXaxis().SetLabelFont(62)#(162)
    g_median.GetYaxis().SetLabelFont(62)#(162)
    g_median.GetXaxis().SetTitleFont(62)#(162)
    g_median.GetYaxis().SetTitleFont(62)#(162)
    g_median.SetLineWidth(4)
    MarcoStyle.SetFillColor(3)
    g_median.SetFillColor(3)
    g_median.SetFillStyle(1001)
    g_median.SetMarkerSize(2)
    g_median.SetMarkerStyle(20)
    return g_median


def make_Diego_table( result, keys_to_print, file_name ):
    
    f = open( file_name, 'w')
    
    header = ''
    for key in keys_to_print:
        header += key + '\t'
    header += '\n' 
    f.write( header )
    
    for item in result:
        line = ''
        for key in keys_to_print:
            line += str( item[key] )+'\t'
        line += '\n' 
        f.write( line )
    f.close()

def get_graph_from_Diego(file_name, column_bf=2, column_val=4, skip_header=1, factor=1e+9, sep='\t', range=None, BFscaling=None):
    
    f = open( file_name, 'r')
    list_of_bf, list_of_val = [], []
    
    if BFscaling != None:
        print 'FURTHER SCALING BY ', BFscaling, ' OF THE BF.'
        factor *= float(BFscaling)
    
    for line in f.readlines()[skip_header:]:
        
        if (line.split(sep)[ column_val-1 ] == ''
            or line.split(sep)[ column_bf-1 ] == ''): break        #stop when column is finished
        if float( line.split(sep)[ column_bf-1 ]) == 0. : continue #remove entries with 0 that polute Diego's file
        #print line.split(sep)
        if range != None:
            print float( line.split(sep)[ column_bf-1 ])*factor,  range[0],  range[1]
            if ( float( line.split(sep)[ column_bf-1 ])*factor < range[0]
                 or float( line.split(sep)[ column_bf-1 ])*factor > range[1] ) : continue #out_of range
        #print 'kept ', float( line.split(sep)[ column_bf-1 ])*factor,  range[0],  range[1]
        list_of_bf .append( float( line.split(sep)[ column_bf-1 ])* factor )
        list_of_val.append( float( line.split(sep)[ column_val-1 ]) )
    
    #print  list_of_bf, list_of_val
    graph = TGraph(len( list_of_bf ), array( 'd',  list_of_bf), array( 'd', list_of_val  ) )
    
    #compare the values in the graph with the input values!
##     print list_of_bf
##     for i in range(graph.GetN() ):
##         print graph.GetX()[i],
##     print ''
    
    return graph

def fit_graph_trick_error( graph, function , verbose=True):
    
    l_x, l_y = [], []
    x_ = graph.GetX()
    y_ = graph.GetY()
    for i in range(graph.GetN()):
        l_x.append( x_[i] )
        l_y.append( y_[i] )
    
    
##     l_error = []
##     for i in range(graph.GetN() ):
##         l_error.append( .1 - 0.095 *(float(i) / graph.GetN())   )  
##     l_error = len(l_x)*[.1]
##     for i in range(graph.GetN()):
##         if l_y[i] < 0.11 and l_y[i] > 0.03 : l_error[i] = 0.05
    
    l_error = len(l_x)*[.1]
    for i in range(graph.GetN()):
        if CHANNEL == 'Bs':
            if ((l_y[i] < 0.11 and l_y[i] > 0.09)
                or (l_y[i] < 0.06 )):#and l_y[i] > 0.04)):
                l_error[i] = 0.01
        elif CHANNEL == 'B0':
            if ((l_y[i] < 0.11 and l_y[i] > 0.09)
                or (l_y[i] < 0.06 )
                or(l_y[i] < 0.27 and l_y[i] > 0.23)
                or(l_y[i] < 0.81 and l_y[i] > 0.75)
                or(l_y[i] < 0.27 and l_y[i] > 0.23) ):#and l_y[i] > 0.04)):
                l_error[i] = 0.05
    
    graph_error = TGraphErrors( graph.GetN(), array( 'd', l_x ),  array( 'd', l_y ), array( 'd', l_error ), array( 'd', l_error ) )
    
    
    fit_res = graph_error.Fit( function, 'SR0' )
    if verbose: fit_res.Print('v')
    
    # construction of a TGraph from the Fitted curves
    l_bf, l_val  = [], []
    
    tmp = []; tmp[:] = list_of_bf[:]; tmp.sort()
    
    l_bf = range( 10*floor(function.GetXmin()), 10*ceil(function.GetXmax()) )
    l_bf = map (lambda x : x/10., l_bf)
    
    print function.GetXmin(), function.GetXmax(), l_bf[0], l_bf[-1]
    
    for bf in l_bf:
        l_val   .append( function.Eval(bf ) )
    
    graph_fitted = TGraph(len( l_bf ), array( 'd',  l_bf ), array( 'd', l_val ))
    
    return graph_fitted 



def fit_graph( graph, function , verbose=True):
    
    fit_res = graph.Fit( function, 'SR0' )
    if verbose: fit_res.Print('v')
    
    # construction of a TGraph from the Fitted curves
    l_bf, l_val  = [], []
    
    tmp = []; tmp[:] = list_of_bf[:]; tmp.sort()
    
    l_bf = range( 10*floor(function.GetXmin()), 10*ceil(function.GetXmax()) )
    l_bf = map (lambda x : x/10., l_bf)
    
    print function.GetXmin(), function.GetXmax(), l_bf[0], l_bf[-1]
    
    for bf in l_bf:
        l_val   .append( function.Eval(bf ) )
    
    graph_fitted = TGraph(len( l_bf ), array( 'd',  l_bf ), array( 'd', l_val ))
    
    return graph_fitted 

    
def get_cls_median_fit_exp_graph( list_of_bf, list_of_median_CLs, list_of_neg_sigma_CLs, list_of_pos_sigma_CLs, list_of_neg_sigma_CLs_delta_median , list_of_pos_sigma_CLs_delta_median , zero , debug=False):
    
    g_median_toFit = TGraphAsymmErrors(len( list_of_bf ), array( 'd',  list_of_bf), array( 'd', list_of_median_CLs  )
                               , array( 'd',  zero ), array( 'd', zero  )
                               , array( 'd', list_of_neg_sigma_CLs_delta_median ), array( 'd', list_of_pos_sigma_CLs_delta_median ))
    
    g_pos_sigma_CLs_toFit = TGraph(len( list_of_bf ), array( 'd',  list_of_bf), array( 'd', list_of_pos_sigma_CLs ))
    g_neg_sigma_CLs_toFit = TGraph(len( list_of_bf ), array( 'd',  list_of_bf), array( 'd', list_of_neg_sigma_CLs ))
    
    #import code; code.interact(local=locals())
    tmp = [];tmp[:] = list_of_bf[:]; tmp.sort()
    
    fexp_CLs_median    = TF1( 'fun1_exp', 'expo' , tmp[0], tmp[-1] )
    fexp_pos_sigma_CLs = TF1( 'fun1_exp', 'expo' , tmp[0], tmp[-1] )
    fexp_neg_sigma_CLs = TF1( 'fun1_exp', 'expo' , tmp[0], tmp[-1] )
    
    g_median_toFit       .Fit( fexp_CLs_median    )  
    g_pos_sigma_CLs_toFit.Fit( fexp_pos_sigma_CLs )
    g_neg_sigma_CLs_toFit.Fit( fexp_neg_sigma_CLs )
    
    import code; code.interact(local=locals())
    if debug:
        canvas_debug = TCanvas('debug', 'debug',700,500)
        canvas_debug.cd()
        g_median_toFit.Draw('AL*')
        fexp_CLs_median.Draw('SAMEL')
        fexp_pos_sigma_CLs.Draw('SAMEL')
        fexp_neg_sigma_CLs.Draw('SAMEL')
    
    g_median_toFit.GetYaxis().SetTitle('CLs')
    g_median_toFit.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-8}]')
    #g_median_toFit.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-9}]')
    
    if CHANNEL == 'B0':
        g_median_toFit.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-8}]')
        #g_median_toFit.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-9}]')
    
    g_median_toFit.GetYaxis().SetTitleOffset(1.4)
    g_median_toFit.GetXaxis().SetLabelFont(62)#(162)
    g_median_toFit.GetYaxis().SetLabelFont(62)#(162)
    g_median_toFit.GetXaxis().SetTitleFont(62)#(162)
    g_median_toFit.GetYaxis().SetTitleFont(62)#(162)
    g_median_toFit.SetLineWidth(4)
    MarcoStyle.SetFillColor(3)
    g_median_toFit.SetFillColor(3)
    g_median_toFit.SetFillStyle(1001)
    g_median_toFit.SetMarkerSize(2)
    g_median_toFit.SetMarkerStyle(20)
    
    # construction of a TGraphErrorAsym from the Fitted curves
    
    l_bf, l_median, l_median_up, l_median_dw, l_zero = [], [], [], [], [] 
    tmp = []; tmp[:] = list_of_bf[:]; tmp.sort()
    l_bf = range( 10*floor(list_of_bf[0]), 10*ceil(list_of_bf[-1]) )
    l_bf = map (lambda x : x/10., l_bf)
    
    for bf in l_bf:
        l_median   .append( fexp_CLs_median.Eval(bf ) )
        l_median_up.append( fexp_pos_sigma_CLs.Eval(bf )  )
        l_median_dw.append( fexp_neg_sigma_CLs.Eval(bf ) )
        l_median_up[-1] = abs( l_median[-1] - l_median_up[-1] )
        l_median_dw[-1] = abs( l_median[-1] - l_median_dw[-1] )
        l_zero     .append( 0. )
    
    g_median_Fitted = TGraphAsymmErrors(len( l_bf ), array( 'd',  l_bf ), array( 'd', l_median )
                               , array( 'd',  l_zero ), array( 'd', l_zero  )
                               , array( 'd', l_median_dw ), array( 'd', l_median_up ))
    
    g_median_Fitted.GetYaxis().SetTitle('CLs')
    g_median_Fitted.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-8}]')
    #g_median_Fitted.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-9}]')
    g_median_Fitted.GetYaxis().SetRangeUser(0., 0.6)
    g_median_Fitted.GetXaxis().SetRangeUser(10., 80.)
    if CHANNEL == 'B0':
        g_median_Fitted.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-8}]')
        #g_median_Fitted.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-9}]')
        g_median_Fitted.GetYaxis().SetRangeUser(0., 0.8)
        g_median_Fitted.GetXaxis().SetRangeUser(0., 18.)
    g_median_Fitted.GetYaxis().SetTitleOffset(1.4)
    g_median_Fitted.GetXaxis().SetLabelFont(62)#(162)
    g_median_Fitted.GetYaxis().SetLabelFont(62)#(162)
    g_median_Fitted.GetXaxis().SetTitleFont(62)#(162)
    g_median_Fitted.GetYaxis().SetTitleFont(62)#(162)
    MarcoStyle.SetFillColor(3)
    g_median_Fitted.SetFillColor(407)
    g_median_Fitted.SetFillStyle(1001)
    g_median_Fitted.SetMarkerSize(2)
    g_median_Fitted.SetLineWidth(4)
    #g_median_Fitted.SetLineStyle(4)
    g_median_Fitted.SetMarkerStyle(20)
    return g_median_Fitted


def get_cls_median_fit_exp_graph_nobands( list_of_bf, list_of_median_CLs ):
    
    g_median_toFit = TGraph(len( list_of_bf ), array( 'd',  list_of_bf), array( 'd', list_of_median_CLs  ))
    
    
    #import code; code.interact(local=locals())
    tmp = [];tmp[:] = list_of_bf[:]; tmp.sort()
    fexp_CLs_median    = TF1( 'fun1_exp', 'expo' , tmp[0], tmp[-1] )
    
    fit_res = g_median_toFit       .Fit( fexp_CLs_median, 'S')  
    fit_res.Print('v')
    
    # construction of a TGraphErrorAsym from the Fitted curves
    
    l_bf, l_median = [], []
    tmp = []; tmp[:] = list_of_bf[:]; tmp.sort()
    l_bf = range( 10*floor(list_of_bf[0]), 10*ceil(list_of_bf[-1]) )
    l_bf = map (lambda x : x/10., l_bf)
    
    for bf in l_bf:
        l_median   .append( fexp_CLs_median.Eval(bf ) )
    
    g_median_Fitted = TGraph(len( l_bf ), array( 'd',  l_bf ), array( 'd', l_median ))
    g_median_Fitted.GetYaxis().SetTitle('CLs')
    g_median_Fitted.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-8}]')
    #g_median_Fitted.GetXaxis().SetTitle('B(B^{0}_{s}#rightarrow#mu#mu) [10^{-9}]')
    g_median_Fitted.GetYaxis().SetRangeUser(0., 0.6)
    g_median_Fitted.GetXaxis().SetRangeUser(10., 80.)
    if CHANNEL == 'B0':
        g_median_Fitted.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-8}]')
        #g_median_Fitted.GetXaxis().SetTitle('B(B^{0}#rightarrow#mu#mu) [10^{-9}]')
        g_median_Fitted.GetYaxis().SetRangeUser(0., 0.8)
        g_median_Fitted.GetXaxis().SetRangeUser(0., 18.)
    g_median_Fitted.GetYaxis().SetTitleOffset(1.4)
    g_median_Fitted.GetXaxis().SetLabelFont(62)#(162)
    g_median_Fitted.GetYaxis().SetLabelFont(62)#(162)
    g_median_Fitted.GetXaxis().SetTitleFont(62)#(162)
    g_median_Fitted.GetYaxis().SetTitleFont(62)#(162)
    MarcoStyle.SetFillColor(3)
    g_median_Fitted.SetFillColor(407)
    g_median_Fitted.SetFillStyle(1001)
    g_median_Fitted.SetMarkerSize(2)
    g_median_Fitted.SetLineWidth(4)
    #g_median_Fitted.SetLineStyle(4)
    g_median_Fitted.SetMarkerStyle(20)
    return g_median_Fitted, fit_res


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
    return l


def do_GL_plot_sig_bkg(fgl, h_bkg):
    fgl_his            =  TH1F ( 'fgl_his        ', 'fgl_his        ', 4 , 0, 1)
    for i in range(4):
        fgl_his.SetBinContent(i+1, fgl[i] )
    error_sig = [0.130, 0.096, 0.046, 0.036]
    for i in range(4):
        fgl_his.SetBinError(i+1, error_sig[i] )
    
        
    fgl_bkg_his        =  TH1F ( 'fgl_bkg_his        ', 'fgl_bkg_his        ', 4 , 0, 1)
    for i in range(1,5):
        content = h_bkg.GetBinContent(1+(i-1)*6)+h_bkg.GetBinContent(2+(i-1)*6)+h_bkg.GetBinContent(3+(i-1)*6)+h_bkg.GetBinContent(4+(i-1)*6)+h_bkg.GetBinContent(5+(i-1)*6)+h_bkg.GetBinContent(6+(i-1)*6)
        fgl_bkg_his.SetBinContent(i, content)
    
    bs_gl = [[ 3.29187e+02,   6.40641e+00,  6.36622e+00,   6.44706e+00]
         ,[7.35705e+00,   9.93963e-01,  9.52884e-01,   1.03580e+00]
         ,[1.51084e+00,   3.77100e-01,  3.46432e-01,   4.08750e-01]
         ,[8.09000e-02,   7.24835e-02,  5.02828e-02,   1.04361e-01]]
       
    fgl_bkg_his.Scale(1./fgl_bkg_his.Integral() )
    
    for i in range(4):
        content = fgl_bkg_his.GetBinContent(i+1) * bs_gl[i][1] / bs_gl[i][0]
        fgl_bkg_his.SetBinError(i+1, content)
    
    print fgl_bkg_his.Print('all')
    sum_ = bs_gl[0][0] + bs_gl[1][0] + bs_gl[2][0] + bs_gl[3][0] 
    print bs_gl[0][0]/sum_, bs_gl[1][0]/sum_, bs_gl[2][0]/sum_, bs_gl[3][0]/sum_  
    canvas = TCanvas('can1', 'can1',-700,500)
    canvas.SetLogy()
    gStyle.SetOptStat(0)
    ## MarcoStyle.SetPadTickX(1)
    ## MarcoStyle.SetPadTickY(1)
    
    
    fgl_bkg_his.GetYaxis().SetTitle('probability')
    fgl_bkg_his.GetXaxis().SetTitle('GL')
    fgl_bkg_his.GetXaxis().SetLabelFont(62)#(162)
    fgl_bkg_his.GetYaxis().SetLabelFont(62)#(162)
    fgl_bkg_his.GetXaxis().SetTitleFont(62)#(162)
    fgl_bkg_his.GetYaxis().SetTitleFont(62)#(162)
    fgl_bkg_his.SetLineWidth(3)
    fgl_bkg_his.SetLineColor(4)
    #fgl_bkg_his.SetLineStyle(2)
    fgl_bkg_his.SetMarkerStyle(24)
    fgl_bkg_his.SetMarkerColor(4)
    fgl_bkg_his.SetMarkerSize(2)
    
    fgl_his    .SetLineWidth(3)
    fgl_his    .SetMarkerStyle(21)
    fgl_his    .SetMarkerSize(2)
    
    fgl_bkg_his.Draw('PE')
    fgl_his    .Draw('PESAME')
    do_lhcb_label(0.8,0.8,0.99,0.99)
    
    leg1 = TLegend(0.17, 0.20, 0.48 , 0.40 )#0.6,0.7,0.92,0.92)#
    
    leg1.AddEntry( fgl_his, 'GL pdf for Signal', 'l')
    ## leg1.AddEntry( g_npv2, 'nPV = 2', 'l')
    leg1.AddEntry( fgl_bkg_his, 'GL pdf for Bkg', 'l')
    leg1.SetFillColor(0)
    #leg1.SetTextSize(0.035)
    
    #leg1.Draw()
    
    lhcb = do_lhcb_label(0.234195, 0.155242, 0.375, 0.405)
    lhcb.Draw()
    
    import code; code.interact(local=locals())
    


 



########################
#     INPUTS           #    
########################

CHANNEL = 'Bs' #'B0'  #'Bs' #
import code; code.interact(local=locals())



# loading 

if CHANNEL == 'Bs':
    files_GL = ['output_GLc13a4bebc9f5401db2b8c772e7e56f2f.marco'
             ,'output_GL404ee7f175cd488a8d9931caa030c9be.marco'
             ,'output_GLd49dd1071c234d279c9dcbd55e0eff9b.marco'
             ,'output_GL7f3f0e451e7f4be9bf9fc4bd0e7ad57a.marco'
             ,'output_GLfad7dda46847405e9be78313a5bb3e35.marco'
             ,'output_GL9fd9a0e631924094a83128d252a5a623.marco'
             ,'output_GLc412cbd23d21487795d095be8d76344e.marco'
             ,'output_GL13f50047c1e04e049d7081ac0309ade1.marco'
             ,'output_GL0ed3c5ab07404500b6e76908b76f6ca6.marco'
             ,'output_GL526ea0c10b2c421987f1b788d7e1db73.marco'
             ,'output_GL6a5e9432090c42ecb21bdb674daa25e0.marco'
             ,'output_GL7ccfa2fac6724790a35c247f4fec750c.marco'
             ,'output_GLa22b55e234354f0ea3a39d2120436202.marco'
             ,'output_GL7fb9984d4903457aa32cf5323e405723.marco'
             ,'output_GL606b98129e86464da0870426b4189d56.marco'
             ,'output_GL9876e057baa643cbbd7207987f7fd488.marco'
             ,'output_GL92396107db8a4cf3bd02e34a005d754f.marco'
             ,'output_GL8d103433c0174b26b0839766cf351b24.marco'
             ,'output_GL9120082d5877463d863ed3c35264c53f.marco'
             ,'output_GL0483895657ac45efb05862dd07a1b46e.marco'
             ,'output_GLff6bbb287f00402f8df1b5812f1166e4.marco'
             ,'output_GL9d92daa2f3364eef9176b17f51ee0806.marco'
             ,'output_GL5afb163ef9a8415c9059ee1c12049963.marco'
             ,'output_GL31ec5470f84a4465a2b2d0d6a671c37b.marco'
             ,'output_GL30aa10b41e704f83a011bc628e38efdd.marco'
             ,'output_GL5dc932f227934b37b52e4ea6e03813c2.marco'
             ,'output_GLe888fc9dff654c78ba5b7465435e85ce.marco'
             ,'output_GL94cb5adf5f09449ba79102bde4b5cd1b.marco'
             ,'output_GL54f8f4baf36b45cf822cf816b4f17f89.marco'    
             ,'output_GL56b50c29ff9d4e8289920af44ada4ebf.marco'
             ,'output_GLb745f268215a47f08803d1ad142e197d.marco'
             ,'output_GLaab8dcaed4db428e8f0c082dfd2c3e3a.marco'
             ,'output_GLa40e19274e5f42d9a7334fa7a345263d.marco'
             ,'output_GL87c8f3eb94a2479eb7f5e2969dde9dc1.marco'
             ,'output_GL6344cbac0e344be1916a74c7c6630ec2.marco'
             ,'output_GLcc603b1309494d5783523b6111bf5e0b.marco'
             ,'output_GL33390b9b3c3945a29a391986ef5d98b3.marco'
             ,'output_GL48da2ddda71a462da86302bd24be1308.marco'
             ,'output_GLf309a130490241718536e30d064103a2.marco'
             ,'output_GLbf81447bd6fd475cb2dd5f065f3c12ad.marco'
             ,'output_GL5feb3327e5cb4939965095af555071ef.marco'
             ,'output_GL34594953f0e1474c91c438ad977540eb.marco'
             ,'output_GL1aee5aa6b58f4ccaaddda391c1b8d7f7.marco'
             ,'output_GL21e0759eb83640e1ac7d510aa510c4ad.marco'
             ,'output_GLa1d30ef8db94475385749f21c1d13ce9.marco'
             ,'output_GLfa16f1a9028a4477862b10698305c12f.marco'
             ,'output_GL1461801528354801a23080a5322c0c35.marco'
             ,'output_GL82fdab17d01e478ca735088646f76034.marco'
             ,'output_GL93224c50f19748a3b8c1c42bc3d2074e.marco'
             ,'output_GL02a31aeff02f4d95858eb527a28d4b63.marco'
             ,'output_GL6f622fbef013446b86413a1089218f8a.marco']
  
    files_BDT = ['output_BDT5fa179ae809f4b3293cb795e9feb62d3.marco'
                 ,'output_BDT4ad10fb44b074041bb89fcd5a6129492.marco'
                 ,'output_BDTc10308b767c84ff4b11da2f4d426521f.marco'
                 ,'output_BDTb57084371a6949f687732544779fe6fa.marco'
                 ,'output_BDT6aa7514ca9614d48b619102163bbd13d.marco'
                 ,'output_BDTec21628c61204a3b82df1446058b8ced.marco'
                 ,'output_BDT308fb0f85ed64ad0a5d814be98c2780e.marco'
                 ,'output_BDT42df111980574e639c1b7b5707859c1b.marco'
                 ,'output_BDT5e8cfc56cac24cb9b807a7c3bf36bab9.marco'
                 ,'output_BDT039e3198d1a146c091f501b18d2fbf8d.marco'
                 ,'output_BDT01d5fe992f784201ad50576a9aa787d7.marco'
                 ,'output_BDTaa041f64d215441d8d0500759e19dd92.marco'
                 ,'output_BDTc92a7eafbcd54e6ba171fe6af5c8ed7b.marco'
                 ,'output_BDT68943c40e2db427fb36bb5ef7244930a.marco'
                 ,'output_BDTd82d5527abd74e049ab88520691c322d.marco'
                 ,'output_BDT9efb295eab474eb99882839495b807f2.marco'
                 ,'output_BDT64f66f69df4d4fddb7751fe693b29713.marco'
                 ,'output_BDTe10ffe8ae53a4458ac83e05204836095.marco'
                 ,'output_BDT32205a99d95a4377836b39b42d31b9ab.marco'
                 ,'output_BDTb1c77279df2944dfb01a03f84c88d3cc.marco'
                 ,'output_BDT6952398285d14f14829963fadf233348.marco'
                 ,'output_BDTeef1306162f743599f96e8152226b59b.marco'
                 ,'output_BDT0f901e94df994402a473ab9fe77ae0f8.marco'
                 ,'output_BDT98e1327934c346359b912ca758d73325.marco'
                 ,'output_BDTb24a81dcfec0487b960d1bef86ea92b2.marco'
                 ,'output_BDTa675c405a12742e29575b5df46a20927.marco'
                 ,'output_BDTee7b6f976c9549e3be93f12afeb8a6f1.marco'
                 ,'output_BDT2019c5f333aa413f82e06b64da522d42.marco'
                 ,'output_BDT62a87b22026d4ae38857889d401b3618.marco']

    
    f_expexted = open( 'Bs_expectation_20110209_all', 'r' )
    expected_res = cPickle.load( f_expexted )
    expected_res = compute_mean_median( expected_res )
    list_of_bf_expec, list_of_median_CLs_expec, list_of_mean_CLs_expec, list_of_pos_sigma_CLs_delta_mean_expec, list_of_neg_sigma_CLs_delta_mean_expec, list_of_pos_sigma_CLs_delta_median_expec, list_of_neg_sigma_CLs_delta_median_expec, list_of_pos_sigma_CLs_expec, list_of_neg_sigma_CLs_expec, list_of_mean_CLb_expec, list_of_pos_sigma_CLb_delta_expec, list_of_neg_sigma_CLb_delta_expec, list_of_pos_sigma_CLb_expec, list_of_neg_sigma_CLb, zero_expec  = build_lists_for_plots( expected_res )
    
    f_obs = open( 'Bs_obs_20110209_1to18', 'r' )#( 'Bs_obs_20110209_1to14', 'r' )#( 'tue_bs', 'r' )
    obs_res = cPickle.load( f_obs )
    list_of_bf, list_of_median_CLs, list_of_mean_CLs, list_of_pos_sigma_CLs_delta_mean, list_of_neg_sigma_CLs_delta_mean, list_of_pos_sigma_CLs_delta_median, list_of_neg_sigma_CLs_delta_median, list_of_pos_sigma_CLs, list_of_neg_sigma_CLs, list_of_mean_CLb, list_of_pos_sigma_CLb_delta, list_of_neg_sigma_CLb_delta, list_of_pos_sigma_CLb, list_of_neg_sigma_CLb, zero  = build_lists_for_plots( obs_res )
    f_obs_noSyst = open( 'Bs_obs_20110209_noSyst', 'r' )
    obs_res_noSyst = cPickle.load( f_obs_noSyst )
    list_of_bf_noSyst, list_of_median_CLs_noSyst, list_of_mean_CLs_noSyst, list_of_pos_sigma_CLs_delta_mean_noSyst, list_of_neg_sigma_CLs_delta_mean_noSyst, list_of_pos_sigma_CLs_delta_median_noSyst, list_of_neg_sigma_CLs_delta_median_noSyst, list_of_pos_sigma_CLs_noSyst, list_of_neg_sigma_CLs_noSyst, list_of_mean_CLb_noSyst, list_of_pos_sigma_CLb_delta_noSyst, list_of_neg_sigma_CLb_delta_noSyst, list_of_pos_sigma_CLb_noSyst, list_of_neg_sigma_CLb_noSyst, zero_noSyst  = build_lists_for_plots( obs_res_noSyst )
    Diego_results = 'experiments_Bs_For_marco.DAT' #'experimentsBs_syst.DAT'
    
    print '\n\n***** SACALING OF BF AXIS ACCORDING TO fd/fs UPDATE\n\n'
    list_of_bf_expec  = map(lambda x: x*8.58/8.36 , list_of_bf_expec )
    list_of_bf_noSyst = map(lambda x: x*8.58/8.36 , list_of_bf_noSyst )
    list_of_bf        = map(lambda x: x*8.58/8.36 , list_of_bf )
    
elif CHANNEL == 'B0':

    files_BDT = ['output_B0_BDT_f10c6ab119f24e869b91fef9688fafc5.marco'
                 ,'output_B0_BDT_ee272a6844dc4c3da25ce99f5a925659.marco'
                 ,'output_B0_BDT_dff384f32dec48a78bd6a371d4e723a3.marco'
                 ,'output_B0_BDT_d684bc37260a4943afe673a89ab287e4.marco'
                 ,'output_B0_BDT_d515ec478cac4832bbcd7269a03f252f.marco'
                 ,'output_B0_BDT_cd90853a9aac49c6a4b1695a8db5e108.marco'
                 ,'output_B0_BDT_b8725f370537420e943f5863262e21c0.marco'
                 ,'output_B0_BDT_b1b6cd70406e42458f7f43278e0ebfa1.marco'
                 ,'output_B0_BDT_a692e2b860dc45be9054d8ed67437f60.marco'
                 ,'output_B0_BDT_a4e09f5e13fa459180925a72990d8690.marco'
                 ,'output_B0_BDT_a217e777fbda4a2cbe328d470dde0712.marco'
                 ,'output_B0_BDT_a1df24a0fd6f494db73e508295031ebb.marco'
                 ,'output_B0_BDT_8c6544f71ad84f76af99b464a73becaa.marco'
                 ,'output_B0_BDT_7521b923498a4a92ad12cd962ada52b7.marco'
                 ,'output_B0_BDT_724e8fdae0c249de923452cfb44048c4.marco'
                 ,'output_B0_BDT_6fe55ab7f9fa4ea3bcc57a86eac87656.marco'
                 ,'output_B0_BDT_6d9303ec215e46f3ad35880ca7189942.marco'
                 ,'output_B0_BDT_646e55a70df34b1aa59c7c9a1eefb5ed.marco'
                 ,'output_B0_BDT_5bb7154f4425471d960ffe6cce300447.marco'
                 ,'output_B0_BDT_5ba01d87d6b6408185149a7826d8419a.marco'
                 ,'output_B0_BDT_475ffdb09b074f23b12cbc5f04d97a88.marco'
                 ,'output_B0_BDT_41ffc395d6144ac8a534afb34345a7e1.marco'
                 ,'output_B0_BDT_416e005f768a449abb1d6180ca274726.marco'
                 ,'output_B0_BDT_3c15f162898643eaa09f50a0e7a6d757.marco'
                 ,'output_B0_BDT_26eb0e089fb843d1bf784bf11ba00ca8.marco'
                 ,'output_B0_BDT_25c2cb0c2c2a4103a2becb0796d1290f.marco'
                 ,'output_B0_BDT_168aae5c7cc14a88abdf44215095c55e.marco'
                 ,'output_B0_BDT_14dc8730fda24540b91835c42f9ae605.marco'
                 ,'output_B0_BDT_00d0e83e08334917bb78f093a6359adc.marco'
                 ,'output_B0_BDT_f789950d445a4278b4608d72610ed928.marco'
                 ,'output_B0_BDT_f747fcf698f94f60967442e2f5a94210.marco'
                 ,'output_B0_BDT_f0b48e34bc9e4643a7dc4953c1c24f17.marco'
                 ,'output_B0_BDT_e946ab594a3e4078a21aea2871bdf5a7.marco'
                 ,'output_B0_BDT_dff7eac9db1d45ceb4776e0c603eed5d.marco'
                 ,'output_B0_BDT_d91ed61f0ae74a739dd410f27df8bde4.marco'
                 ,'output_B0_BDT_b615f142312b483e8313a095eefa76a8.marco'
                 ,'output_B0_BDT_947958d800934b8b896c8c3458a9de30.marco'
                 ,'output_B0_BDT_9394bafd2a5f4df3af79925edcdc9d99.marco'
                 ,'output_B0_BDT_92fed2fab8334b0fbb4aef0dd68edc35.marco'
                 ,'output_B0_BDT_8bf32f8259594b68999d2f96adafad5a.marco'
                 ,'output_B0_BDT_88ef7cfb9f4e4cb895849b09a6ffc5e1.marco'
                 ,'output_B0_BDT_840baf19ef384a8495ba5cf5e3605724.marco'
                 ,'output_B0_BDT_77bb141a098049c29cb3e5928b1c6443.marco'
                 ,'output_B0_BDT_73dbda9272904bf3908d24e8bf2e0168.marco'
                 ,'output_B0_BDT_72fcf60940a04065bc562131655b4ebf.marco'
                 ,'output_B0_BDT_6f7b30b073194526b23ebfb29926af29.marco'
                 ,'output_B0_BDT_578c6d5e65024ef891b47625b6812402.marco'
                 ,'output_B0_BDT_54af3c5c9e374f4488af9c5df58428ca.marco'
                 ,'output_B0_BDT_43d468f46ac9411981942a143e6f1ec7.marco'
                 ,'output_B0_BDT_425cf4e9cdbf4b0daa2b933fbd8f459c.marco'
                 ,'output_B0_BDT_3d27c42eb5de4b7aa0c7fcff43d9b288.marco'
                 ,'output_B0_BDT_3c4ca208216a478fb947c7da7c6b2b0a.marco'
                 ,'output_B0_BDT_2e3af1dd8699458fbd581b760ccc879c.marco'
                 ,'output_B0_BDT_292022660c9647db8a1de3a21df2525d.marco'
                 ,'output_B0_BDT_245eb6301be74bc995004e19c03a75af.marco'
                 ,'output_B0_BDT_1adad7bdb54f4ff9a91afa1d6a828107.marco'
                 ,'output_B0_BDT_043594c3d382440997e215138d1aa9bf.marco'
                 ,'output_B0_BDT_02ebfedc285c40b9b4908e87088d25df.marco'
                 ,'output_B0_BDT_4f8b5d9084894fd3b7e3dc34e05e5b24.marco'
                 ,'output_B0_BDT_c1adb4029d9141089183f630d1fef6a6.marco'
                 ,'output_B0_BDT_e08c19a598b741f5981d4e74f26d6e84.marco'
                 ,'output_B0_BDT_dc934b37b7f542aa88324c5c08c4a1bc.marco'
                 ,'output_B0_BDT_d219d3b0ccf84420a5daf7c79d329bac.marco'
                 ,'output_B0_BDT_bccdcf47049c443b89226fdd700409b7.marco'
                 ,'output_B0_BDT_bbc31582862745ffa4ea89b5828205da.marco'
                 ,'output_B0_BDT_b689f1df63a44c86a889572803c0387c.marco'
                 ,'output_B0_BDT_a3f556b7cfa44ca881c39744dccac546.marco'
                 ,'output_B0_BDT_a138b09dd0724c43b2174e8ccec01c79.marco'
                 ,'output_B0_BDT_805e6ddc16f7431c8d313061354c58ce.marco'
                 ,'output_B0_BDT_7b48bb0817af4a998c2d4099cdcddac1.marco'
                 ,'output_B0_BDT_789f0c226ca44943890e32d9b65936d8.marco'
                 ,'output_B0_BDT_788dd903159e4153a7e6ca829f61e8e7.marco'
                 ,'output_B0_BDT_5a2432ddcb5042f3b1c9b4dcfebd8318.marco'
                 ,'output_B0_BDT_4ebe49a88cdf4788bdd3abee3d9fcfef.marco'
                 ,'output_B0_BDT_3a5396ddf6f142cfb3277640407ae269.marco'
                 ,'output_B0_BDT_35e41f9856d0437a82c5c4c56fcff34b.marco'
                 ,'output_B0_BDT_32a54f0691254206abd916bcb65a9840.marco'
                 ,'output_B0_BDT_3077000e8dbc4188af8fd192c355ca66.marco'
                 ,'output_B0_BDT_25cfc0fdfc874c61936615eae1d080e0.marco'
                 ,'output_B0_BDT_08165e46992e46f2b9e3dc81ebac8646.marco'
                 ,'output_B0_BDT_d89d669003d8455eaf2feadd488427e6.marco'
                 ,'output_B0_BDT_b9aa6164d8a140cca2b4005a54d7a782.marco'
                 ,'output_B0_BDT_b8c186a5291a4a20b74f3b991d2b1f93.marco'
                 ,'output_B0_BDT_a8e48568a63b49c78af07418524a664c.marco'
                 ,'output_B0_BDT_9e846c3b4b8343168e41291d8c01f2e8.marco'
                 ,'output_B0_BDT_974582ca89dd46a59fee567b4b26ee3d.marco'
                 ,'output_B0_BDT_94a5a4e7745c46da9649506460be6d99.marco'
                 ,'output_B0_BDT_8563b9c8d3214c03a6981fe47887b3b4.marco'
                 ,'output_B0_BDT_7ce6b417899543d498a8094dbb361a01.marco'
                 ,'output_B0_BDT_4a857f82dea04a97af399f06b67018d9.marco'
                 ,'output_B0_BDT_258eb014fdf44182beeeac90456d1b08.marco'
                 ,'output_B0_BDT_14c54c2293be4b5bad9d5daa2ede2c16.marco'
                 ,'output_B0_BDT_0b18b557d9c74c4984a7471132c58eb9.marco'
                 ,'output_B0_BDT_05a2508377a14c0cb51e280d908ecbae.marco']




    files_GL = ['output_B0_GL_f41890472d3a44bda48ed71153162312.marco'
                ,'output_B0_GL_f2b625d19c0d4759bd9ca22f3be7222e.marco'
                ,'output_B0_GL_f1d6fe9ea61a460a99db7c1b993ea138.marco'
                ,'output_B0_GL_da6ed3903ada47cd99e99573fad0c61b.marco'
                ,'output_B0_GL_d7d0e905c74846ebb96c95db6d5013cd.marco'
                ,'output_B0_GL_d47d55e6541343e6abd6cbdaad101ce9.marco'
                ,'output_B0_GL_cf0193953a0e4feda001ec0bbef8434b.marco'
                ,'output_B0_GL_ccd56f33bb0f42a7bffd99f150b94c98.marco'
                ,'output_B0_GL_c5301536645c48a5877887f975338e2f.marco'
                ,'output_B0_GL_c193c6bab9e94a978cb8d13a42f20101.marco'
                ,'output_B0_GL_bfa2f5f8dda94f13b1c7ff251daf8f38.marco'
                ,'output_B0_GL_ba56213b8870438cb846c2829fdbe4ca.marco'
                ,'output_B0_GL_ab18e58ed577447d97630677de1f04fa.marco'
                ,'output_B0_GL_8e23c3726d634e668868534249eca300.marco'
                ,'output_B0_GL_85ab1a8f6eb3459e8e1d6adba2011461.marco'
                ,'output_B0_GL_77b99f1097e04e7f9c2e1b413790627c.marco'
                ,'output_B0_GL_282323f18e734bdcb86ea29f94569e92.marco'
                ,'output_B0_GL_1a48e91746c54c25aa04024c2e2f3cce.marco'
                ,'output_B0_GL_17ddea389c9f4311aad13c89a6222169.marco'
                ,'output_B0_GL_14a9b2dd64954cd0a44287917b279d27.marco'
                ,'output_B0_GL_104e6eb743824ddd8cfb8f214ce5685c.marco'
                ,'output_B0_GL_0c8b2aa6a1c44cb0a4a455232e3c2963.marco'
                ,'output_B0_GL_04cd8b788f444ccd8b278349e5d66ae3.marco'
                ,'output_B0_GL_fa14738c89a34480b5ff05036f86c0fe.marco'
                ,'output_B0_GL_f86f4293347e44ed87047fe1294d63d0.marco'
                ,'output_B0_GL_f76dc426cfc6426f8661d03970ab5da0.marco'
                ,'output_B0_GL_f57ceef22ee547b5b1c405aa57aaecbf.marco'
                ,'output_B0_GL_e65bac31b7a2491b9e0072fc49a95acd.marco'
                ,'output_B0_GL_e5373a1aeaa44ac885c81dc4ad23482a.marco'
                ,'output_B0_GL_e4fd2797f59f4f38afcf86ec9ae3bc81.marco'
                ,'output_B0_GL_e461a961d8154946b28b3c6806aebf12.marco'
                ,'output_B0_GL_e29d9f4cd2ac4ec6a4e6543cd7823f51.marco'
                ,'output_B0_GL_e0824ff941fb4ad1ba61cbc3545cb81c.marco'
                ,'output_B0_GL_d96f53baea0d4ed68a53aa61883deb65.marco'
                ,'output_B0_GL_d8d848d5703c4a00b8ba960851ee86a7.marco'
                ,'output_B0_GL_d56c0219350644318f52b46e687f877b.marco'
                ,'output_B0_GL_d29b5effe0814f328fbeb528cf5ffe42.marco'
                ,'output_B0_GL_d288b51fe71e46e295f160f8cb47dbce.marco'
                ,'output_B0_GL_d056d130ed8a445c9f184984fadf35d0.marco'
                ,'output_B0_GL_ceeab89b8ce441f589dfd82f8d19684d.marco'
                ,'output_B0_GL_ccfa6f19aaf74cb6bfb55df4fe273fc6.marco'
                ,'output_B0_GL_ccb6ca28b25b4f12ad08411dbc7b6457.marco'
                ,'output_B0_GL_cbec3f1f687c4ef38da97adf9475ecf8.marco'
                ,'output_B0_GL_c8bbf42005f748dfa9ea881d6d100f16.marco'
                ,'output_B0_GL_c3e41e610996453f891fae5b1c64c307.marco'
                ,'output_B0_GL_c29536dfab7f4ea193ab60cf37158ddf.marco'
                ,'output_B0_GL_c1bac906fb7043d4b94313536cb155c5.marco'
                ,'output_B0_GL_c03049f6835645b3ba4fb030bc9c5f0c.marco'
                ,'output_B0_GL_be9d96c9588b4d029d12125dcc693856.marco'
                ,'output_B0_GL_b88f3401787e4aa983c2d862040a12b6.marco'
                ,'output_B0_GL_b72e4500059e4f139b923dfac1def762.marco'
                ,'output_B0_GL_b55a83377fac4f0bb09b25ebf3b93f84.marco'
                ,'output_B0_GL_b36538369dbf4e13a6df74bc4bf44f5d.marco'
                ,'output_B0_GL_b183384b29c6458098d2699e0b8ec23f.marco'
                ,'output_B0_GL_af2a77d21ca647f8ba3a09652b4d8f62.marco'
                ,'output_B0_GL_ac6d2a70129844609de3fee8106cd23d.marco'
                ,'output_B0_GL_a2d407c545d54ddb9f5234af239e3316.marco'
                ,'output_B0_GL_9c3d9a25f78a4f6b813cc0b8358b77e6.marco'
                ,'output_B0_GL_9b42d16b67784550b695ee67dc9146eb.marco'
                ,'output_B0_GL_9b1ec1bc06f14c2a9e74fa1c4b28d86c.marco'
                ,'output_B0_GL_9ab73aa7b6f84af180545d630ad369e3.marco'
                ,'output_B0_GL_9a35109118ef460fbf9ea085ed73c51b.marco'
                ,'output_B0_GL_99df22840da648a6be94e67b0b69c151.marco'
                ,'output_B0_GL_97187f5a76774fad9798e290d2539132.marco'
                ,'output_B0_GL_9559eb7c383245b29929a36ddbc6367e.marco'
                ,'output_B0_GL_942e94233e4d4b87a6742873ee367da3.marco'
                ,'output_B0_GL_8d9e731239df4647a3c71078e8ad5d6f.marco'
                ,'output_B0_GL_8cd3012d6e774626b3c308504f25cdac.marco'
                ,'output_B0_GL_8bd822a6ab9b4167bb7adb8433298949.marco'
                ,'output_B0_GL_8a7c415d170e4dffa1024528a55c6491.marco'
                ,'output_B0_GL_88c53d54370c4be980d63f75246d9d2b.marco'
                ,'output_B0_GL_87f8b5ff2c2e405f84829ba7cdca9db4.marco'
                ,'output_B0_GL_87681788943f4b2a92f148d40937b3e6.marco'
                ,'output_B0_GL_8752ebe67f3e4f8d86345d095061c64b.marco'
                ,'output_B0_GL_850c294dbeff4c7baf78f510b73cbc0e.marco'
                ,'output_B0_GL_844910a030de46e0a01c92c1bcfda033.marco'
                ,'output_B0_GL_82f67f02a86b4a7d9e0802353d3a4bd7.marco'
                ,'output_B0_GL_824fb5d9ca69466cb17d44b3b34696d4.marco'
                ,'output_B0_GL_824d85ea45c6431193a0d4e23a3c0402.marco'
                ,'output_B0_GL_7fc4041f3e1045bba53b3719fc9ac266.marco'
                ,'output_B0_GL_7f88d058aa4745e28690776312797a02.marco'
                ,'output_B0_GL_7efa7a20f6964fab85b65023610d23c0.marco'
                ,'output_B0_GL_7974ebcbc2024bddae8dfa6a51e4717e.marco'
                ,'output_B0_GL_795157a9e6b9411a961260872f1cfdd6.marco'
                ,'output_B0_GL_75b611799247416983d05518dcd98ffc.marco'
                ,'output_B0_GL_6d841561e22143ba95c18ba0d98716f1.marco'
                ,'output_B0_GL_69782bbd27bf49a39d7a4f0ff55c27d4.marco'
                ,'output_B0_GL_6830631f2487489c8a60052ccd2e6237.marco'
                ,'output_B0_GL_666a45c055f54393877cec5e1b59dda7.marco'
                ,'output_B0_GL_634607561ecc4d9eaec6f752ed97c433.marco'
                ,'output_B0_GL_5f865a4a41024e179faf3b55441482c4.marco'
                ,'output_B0_GL_5c98dd4ce7584144a089cc90f9f117ca.marco'
                ,'output_B0_GL_590be73477e64a7a990c08a801b5a83a.marco'
                ,'output_B0_GL_56ed06df2de74ae9a788ae76fd2810ba.marco'
                ,'output_B0_GL_5435cafc7f174dd68ecae87eb088a3da.marco'
                ,'output_B0_GL_4de05cae66764a1d9f47bbc6198caf6b.marco'
                ,'output_B0_GL_4d3852273cbe412496bf644341dbdeed.marco'
                ,'output_B0_GL_4c2686e6f1ae420f83abd2c0c898f858.marco'
                ,'output_B0_GL_4bbcb0eb9622419f9417cb3821ad7e76.marco'
                ,'output_B0_GL_48f4a295951c4d7facdff772a7ad5d46.marco'
                ,'output_B0_GL_48999386abbf4e98ba0fa3c815e576ac.marco'
                ,'output_B0_GL_4893b6ea294c44219c32f968c2242ff8.marco'
                ,'output_B0_GL_481946149d0242d1afbc4a49b839d07b.marco'
                ,'output_B0_GL_3f06c9477ffe4e39993dbc6e7d893d61.marco'
                ,'output_B0_GL_3c659154058e45d889217b63772a14b1.marco'
                ,'output_B0_GL_38257a2e774d4f3ab5471d1c48c575f0.marco'
                ,'output_B0_GL_37b79c3b9c9f49a9828b2b1b56042be7.marco'
                ,'output_B0_GL_3679d2d531394733a83a25750e919439.marco'
                ,'output_B0_GL_34664f8945c046bfbc7af090c3cb1be2.marco'
                ,'output_B0_GL_32124359f57f4523bfd39c8e8fc38d47.marco'
                ,'output_B0_GL_29aa6f063480408fbafd4692a09289ec.marco'
                ,'output_B0_GL_2829d20411ce4587ab687e51cd501604.marco'
                ,'output_B0_GL_244975582aff4082bd368c6076d88bc2.marco'
                ,'output_B0_GL_22b8eabcd20c4a7b8863a6bb33f6e07e.marco'
                ,'output_B0_GL_217c1ff7a293474880f5cd187ba2a9c3.marco'
                ,'output_B0_GL_21477330f35e485ba4a4fe551f4fd398.marco'
                ,'output_B0_GL_1d2f41765509419ca1fae78188ffbfdb.marco'
                ,'output_B0_GL_19861e59b70749718877cc67a8494076.marco'
                ,'output_B0_GL_184d605f4cfd46f582c9c22de50f3230.marco'
                ,'output_B0_GL_18130655c51b49079e5adddb83de83a9.marco'
                ,'output_B0_GL_12f99f0a3a824ff1a7adcee6dbb1e396.marco'
                ,'output_B0_GL_11922bde83574f6b9ec2977b17a38662.marco'
                ,'output_B0_GL_0b19dae75ba44591af28faa6d52f4faf.marco'
                ,'output_B0_GL_06ba11c8445e48c3ac884b239fe46de3.marco'
                ,'output_B0_GL_039500d90de84a368c0eea4ab0cb3df8.marco'
                ,'output_B0_GL_017bed4567d54fd09af29363e93f55f4.marco'
                ,'output_B0_GL_f753f0e59aa244d5bf57b811656a7aae.marco'
                ,'output_B0_GL_f560d66666834790886f42d724dc40f7.marco'
                ,'output_B0_GL_ededf9a3648a4b30a384153e02836fc8.marco'
                ,'output_B0_GL_ec018f8bf7234748b7bb75f78d2c073b.marco'
                ,'output_B0_GL_cfff5f91e23e413b8748604fea60530f.marco'
                ,'output_B0_GL_c9577aead98f4707b0d832b9576e3120.marco'
                ,'output_B0_GL_b7346a869af84d2f863dea66a8909210.marco'
                ,'output_B0_GL_b54d95f8a7c54be29e705a983f0603ed.marco'
                ,'output_B0_GL_b20404e8dd5c4cb39a18476393ade8f8.marco'
                ,'output_B0_GL_ac375eeb1cbb4f32abdf397427c33fe2.marco'
                ,'output_B0_GL_976e7d4cc51447dba2be9f1191770876.marco'
                ,'output_B0_GL_8ba5f829174548599e26a4c5ec64771e.marco'
                ,'output_B0_GL_8472c67afeb748f7974b6a37fd7dba77.marco'
                ,'output_B0_GL_662c387947d440319edd6f0e51428981.marco'
                ,'output_B0_GL_55688f01f78f4950946a035e4f4c1a61.marco'
                ,'output_B0_GL_4a3b99d31f934a88b3a8653e3be09d33.marco'
                ,'output_B0_GL_404f92a6b25a4544bd07ea9c35ed9cc8.marco'
                ,'output_B0_GL_22c7cdda05534b0e802867705c1e98f1.marco'
                ,'output_B0_GL_21768a164ad94f9490237a77009330da.marco'
                ,'output_B0_GL_169ed62ff205429ba3d6ebf20651f986.marco'
                ,'output_B0_GL_090d909450d44db2ab361473b242d3ce.marco'
                ,'output_B0_GL_090b2bdb0cd44049a596bd8c413dad12.marco']

        
    f_expexted = open('B0_expectation_20110209_all', 'r')  #( 'B0_expectation_20110130_all', 'r' )
    expected_res = cPickle.load( f_expexted  )
    expected_res = compute_mean_median( expected_res )
    list_of_bf_expec, list_of_median_CLs_expec, list_of_mean_CLs_expec, list_of_pos_sigma_CLs_delta_mean_expec, list_of_neg_sigma_CLs_delta_mean_expec, list_of_pos_sigma_CLs_delta_median_expec, list_of_neg_sigma_CLs_delta_median_expec, list_of_pos_sigma_CLs_expec, list_of_neg_sigma_CLs_expec, list_of_mean_CLb_expec, list_of_pos_sigma_CLb_delta_expec, list_of_neg_sigma_CLb_delta_expec, list_of_pos_sigma_CLb_expec, list_of_neg_sigma_CLb_expec, zero_expec  = build_lists_for_plots( expected_res )
    
    f_obs = open('B0_obs_20110209_1to12', 'r' )#('B0_obs_20110209_1to10', 'r' )#( 'obs_tue_B0', 'r' )
    obs_res = cPickle.load( f_obs )
    list_of_bf, list_of_median_CLs, list_of_mean_CLs, list_of_pos_sigma_CLs_delta_mean, list_of_neg_sigma_CLs_delta_mean, list_of_pos_sigma_CLs_delta_median, list_of_neg_sigma_CLs_delta_median, list_of_pos_sigma_CLs, list_of_neg_sigma_CLs, list_of_mean_CLb, list_of_pos_sigma_CLb_delta, list_of_neg_sigma_CLb_delta, list_of_pos_sigma_CLb, list_of_neg_sigma_CLb, zero  = build_lists_for_plots( obs_res )
    f_obs_noSyst = open( 'B0_obs_20110209_noSyst', 'r' )
    obs_res_noSyst = cPickle.load( f_obs_noSyst )
    list_of_bf_noSyst, list_of_median_CLs_noSyst, list_of_mean_CLs_noSyst, list_of_pos_sigma_CLs_delta_mean_noSyst, list_of_neg_sigma_CLs_delta_mean_noSyst, list_of_pos_sigma_CLs_delta_median_noSyst, list_of_neg_sigma_CLs_delta_median_noSyst, list_of_pos_sigma_CLs_noSyst, list_of_neg_sigma_CLs_noSyst, list_of_mean_CLb_noSyst, list_of_pos_sigma_CLb_delta_noSyst, list_of_neg_sigma_CLb_delta_noSyst, list_of_pos_sigma_CLb_noSyst, list_of_neg_sigma_CLb_noSyst, zero_noSyst  = build_lists_for_plots( obs_res_noSyst )
    Diego_results = 'experimentsBd_syst.DAT'


print '***************************'
print '* Initialisation finished *'
print '***************************'

#get_signal_pdfs_uncertainties()
print 'Channel is ', CHANNEL
import code; code.interact(local=locals())




#########################
#  median fitted CLs    #
#########################



canvas_CLs_median_toFit = TCanvas('can_CLs_median_toFit', 'can_CLs_median_toFit',700,500)
#canvas_CLs_median_toFit.SetGrid(1,1)
canvas_CLs_median_toFit.SetTicks(1,1)

#g_median_Fitted = get_cls_median_fit_exp_graph( list_of_bf_expec, list_of_median_CLs_expec, list_of_neg_sigma_CLs_delta_median_expec, list_of_pos_sigma_CLs_delta_median_expec, zero_expec )
g_median_Fitted = get_cls_median_fit_exp_graph( list_of_bf_expec, list_of_median_CLs_expec, list_of_neg_sigma_CLs_expec, list_of_pos_sigma_CLs_expec, list_of_neg_sigma_CLs_expec, list_of_pos_sigma_CLs_expec, zero_expec , debug = False)

g_median_Fitted.GetYaxis().SetRangeUser(0., 0.7)
g_median_Fitted.GetXaxis().SetRangeUser(1., 62.)#(10., 80.)#
if CHANNEL == 'B0':
    g_median_Fitted.GetYaxis().SetRangeUser(0., 0.7)
    g_median_Fitted.GetXaxis().SetRangeUser(.5, 12.)

gStyle.SetLineStyleString(11,"60 50")
g_median_Fitted.SetLineStyle(11)#(1)#
g_median_Fitted.SetLineWidth(5)
g_median_Fitted.Draw('A3')
g_median_Fitted.Draw('LX')

g_median_obs = get_cls_median_exp_graph( list_of_bf, list_of_median_CLs , list_of_neg_sigma_CLs_delta_median , list_of_pos_sigma_CLs_delta_median , zero )
#g_median_obs.SetLineStyle(1)
#g_median_obs.Draw('LX')

g_median_obs_FITTED, fit_res = get_cls_median_fit_exp_graph_nobands( list_of_bf, list_of_median_CLs )
g_median_obs_FITTED.SetLineStyle(1)
#g_median_obs_FITTED.Draw('L')

if CHANNEL == 'Bs':
    g_Diego = get_graph_from_Diego( Diego_results, factor=10, BFscaling=8.58/8.36)
elif CHANNEL == 'B0':
    g_Diego = get_graph_from_Diego( Diego_results  , range= [3., 18.])


#g_Diego.Draw('A*')

if False:
    g_Diego_fit = fit_graph( g_Diego, TF1( 'fun1_exp', 'expo' , TMath.MinElement( g_Diego.GetN(), g_Diego.GetX() ), TMath.MaxElement( g_Diego.GetN(), g_Diego.GetX())))
    g_Diego_fit_expo  = fit_graph( g_Diego, TF1( 'fun1_exp', 'expo' , 4., 60.7))
    g_Diego_fit_expo_trick  = fit_graph_trick_error( g_Diego, TF1( 'fun1_exp', 'expo' , 4., 60.7))
    
    if CHANNEL == 'B0':
        g_Diego_fit_expo  = fit_graph( g_Diego, TF1( 'fun1_exp', 'expo' , 1.2, 18.))
        g_Diego_fit_expo_trick  = fit_graph_trick_error( g_Diego, TF1( 'fun1_exp', 'expo' , 1.2, 18.))
    
    if CHANNEL == 'B0':
        g_Diego_fit_popol = fit_graph( g_Diego, TF1( 'popol', 'pol3'    , 1., 18.))
        g_Diego_fit_popol_trick = fit_graph_trick_error( g_Diego, TF1( 'popol', 'pol3'    , 1., 18.))
    
    erf__ = TF1( 'erf', '[0]+[1]*TMath::Erfc([2]+[3]*x)' , 5., 60.92)
    if CHANNEL == 'B0':
        erf__ = TF1( 'erf', '[0]+[1]*TMath::Erfc([2]+[3]*x)' , 2., 18.)
    
    erf__.SetParLimits(1, 0., 80.)
    g_Diego_fit_erf = fit_graph( g_Diego, erf__ )
    g_Diego_fit_erf_trick = fit_graph_trick_error( g_Diego, erf__ )
    
    g_Diego_fit_popol_trick.SetLineColor(2)
    g_Diego_fit_popol_trick.SetLineStyle(7)
    g_Diego_fit_expo.SetLineColor(2)
    g_Diego_fit_expo_trick.SetLineColor(6)
    g_Diego_fit_popol.SetLineColor(3)
    g_Diego_fit_erf.SetLineColor(4)
    g_Diego_fit_erf_trick.SetLineColor(5)
    
    ## g_Diego_fit_popol_trick.Draw('L')
    ## g_Diego_fit_expo.Draw('L')
    ## g_Diego_fit_expo_trick.Draw('L')
    ## g_Diego_fit.Draw('L')
    ## g_Diego_fit_popol.Draw('L')
    ## g_Diego_fit_erf.Draw('L')
    ## g_Diego_fit_erf_trick.Draw('L')

#fixing the fitted values
if CHANNEL == 'Bs':
    pol_fit_fixed = TF1( 'popol', 'pol5'    , 14., 59. )
    pol_fit_fixed.SetParameters( 1.0305 , -0.046077, 0.0003296, 2.0511e-05, -4.8355e-07, 3.113e-09)
    pol_fit_fixed.SetLineWidth(4)
    
    # shifting the BF
    l_bf, l_val = [], []
    l_bf = range( 10*floor(14.), 10*ceil(59.) )
    l_bf = map (lambda x : x/10., l_bf)
    for bf in l_bf:
        l_val   .append( pol_fit_fixed.Eval(bf ) )
    l_bf = map (lambda x : x*8.58/8.36, l_bf)
    g_new_fit = TGraph(len( l_bf ), array( 'd',  l_bf ), array( 'd', l_val ))
    #pol_fit_fixed.Draw('SAMEL')
    g_new_fit.SetLineWidth(5)
    g_new_fit.Draw('SAMEL')

if CHANNEL == 'B0':
    erf_fit_fixed = TF1(  'erf', '[0]+[1]*TMath::Erfc([2]+[3]*x)' , 3., 18.)
    erf_fit_fixed.SetParameters(0.02158, 80 ,1.7558,  0.051036 )#( 0.020208, 10.109, 1.1716, 0.061985 )
    #erf_fit_fixed.SetParameters(0.02158, 80 ,1.7558-x,  0.051036 )
    erf_fit_fixed.SetLineWidth(5)
    erf_fit_fixed.SetLineColor(1)
    erf_fit_fixed.Draw('SAMEL')

## g_median_obs_noSyst = get_cls_median_exp_graph( list_of_bf_noSyst, list_of_median_CLs_noSyst , list_of_neg_sigma_CLs_delta_median_noSyst , list_of_pos_sigma_CLs_delta_median_noSyst , zero_noSyst )
## #g_median_obs.SetLineStyle(1)
## #g_median_obs.Draw('LX')


## g_median_obs       .SetLineWidth(1)
## g_median_obs_FITTED.SetLineWidth(1)
## g_Diego            .SetLineWidth(1)
## g_median_obs_noSyst.SetLineWidth(1)

## g_median_obs       .SetLineColor(1)
## g_median_obs_FITTED.SetLineColor(2)
## g_Diego            .SetLineColor(3)
## g_median_obs_noSyst.SetLineColor(4)

## g_median_obs       .Draw('AL')
## g_median_obs_FITTED.Draw('L')
## g_Diego            .Draw('L')
## g_median_obs_noSyst.Draw('L')


line90_h = TLine(10.  ,0.1   ,42.8  ,0.1)#(10.  ,0.1   ,42.  ,0.1)#(10.  ,0.1   ,40.1  ,0.1)
line90_v = TLine(42.8 ,0.    ,42.8  ,0.1)#(42. ,0.    ,42.  ,0.1)#(40.1 ,0.    ,40.1  ,0.1)
if CHANNEL == 'B0':
    line90_h = TLine(2.   ,0.1  ,11.4  ,0.1)#(2.   ,0.1  ,12.  ,0.1)#(2.   ,0.1  ,11.48  ,0.1)#(2.   ,0.1  ,13.64  ,0.1)#(0.   ,0.1  ,11.5  ,0.1)
    line90_v = TLine(11.5 ,0.  ,11.5  ,0.099)#(12.   ,0.   ,12.  ,0.1)#(11.48,0.   ,11.48  ,0.1)#(13.64,0.   ,13.64  ,0.1)#(11.5 ,0.   ,11.5  ,0.1)

line90_h.SetLineWidth(4)
line90_h.Draw()
line90_v.SetLineWidth(4)
line90_v.Draw()

line95_h = TLine(10.   ,0.05 ,55.7  ,0.05)#(10.   ,0.05  ,54.  ,0.05)
line95_v = TLine(55.7  ,0.    ,55.7  ,0.05)#(54.  ,0.    ,54.  ,0.05)
if CHANNEL == 'B0':
    line95_h = TLine(2.   ,0.05  ,15.  ,0.05)#(2.   ,0.05  ,17.5  ,0.05)#(0.   ,0.05  ,14.8  ,0.05)
    line95_v = TLine(15.  ,0.    ,15.  ,0.05)#(17.5  ,0.    ,17.5  ,0.05)#(14.8  ,0.    ,14.8  ,0.05)

line95_h.SetLineWidth(4)
line95_h.SetLineStyle(7)
line95_h.Draw()
line95_v.SetLineWidth(4)
line95_v.SetLineStyle(7)
line95_v.Draw()

lhcb = do_lhcb_label(.76, .72, .9, .97)
lhcb.Draw()

canvas_CLs_median_toFit.RedrawAxis('')

#canvas_CLs_median_toFit.SaveAs('result_cls_median_'+CHANNEL+'_fitted.pdf')



#########################
#          CLb          #
#########################


canvas_CLb = TCanvas('can_CLb', 'can_CLb',700,500)
canvas_CLb.SetGrid(1,1)
canvas_CLb.SetTicks(1,1)
canvas_CLb.cd()

clb_exp =  get_clb_exp_graph( list_of_bf_expec, list_of_mean_CLb_expec, list_of_neg_sigma_CLb_delta_expec, list_of_pos_sigma_CLb_delta_expec, zero_expec )
clb_exp.SetMarkerStyle(20)
clb_exp.SetMarkerSize(1.5)
clb_exp.SetLineWidth(4)
gStyle.SetLineStyleString(11,"60 50")
clb_exp.SetLineStyle(11)

clb_obs = get_clb_exp_graph(  list_of_bf, list_of_mean_CLb , list_of_neg_sigma_CLb_delta, list_of_pos_sigma_CLb_delta, zero )
clb_obs.SetLineWidth(4)

if CHANNEL == 'Bs':
    g_Diego = get_graph_from_Diego( Diego_results, column_val=5, factor=10 , range=[14., 10.0e+50] , BFscaling=8.58/8.36)
    g_expect_fit  = fit_graph( clb_exp, TF1( 'popol', 'pol1' , 14., 62.))
    g_obs_fit  = fit_graph( g_Diego, TF1( 'popol', 'pol1' , 14., 62.))
    
elif CHANNEL == 'B0':
    g_Diego = get_graph_from_Diego( Diego_results, column_val=5 , range=[3., 17.8] )
    g_expect_fit  = fit_graph( clb_exp, TF1( 'popol', 'pol1' , 3., 18.))
    g_obs_fit  = fit_graph( g_Diego, TF1( 'popol', 'pol1' , 3., 18.))

g_Diego.SetLineWidth(4)

g_expect_fit.SetLineWidth(4)
g_expect_fit.SetLineStyle(11)
g_obs_fit   .SetLineWidth(4)

clb_exp.Draw('A3')
clb_exp.Draw('PX')#('PX')
#clb_obs.Draw('CX')#('PX')
#g_Diego.Draw('C')
#g_Diego.Draw('*')


g_expect_fit.Draw('L')
g_obs_fit   .Draw('L')

lhcb = do_lhcb_label(.76, .72, .9, .97)
lhcb.Draw()

canvas_CLb.RedrawAxis('')

#canvas_CLb.SaveAs('result_clb_'+CHANNEL+'.pdf')


#########################
#       mean CLs        #
#########################


canvas_CLs = TCanvas('can_CLs', 'can_CLs',-700,500)
canvas_CLs.SetGrid(1,1)
canvas_CLs.SetTicks(1,1)


g_expec_mean = get_cls_mean_exp_graph( list_of_bf_expec, list_of_mean_CLs_expec, list_of_neg_sigma_CLs_delta_mean_expec , list_of_pos_sigma_CLs_delta_mean_expec, zero_expec )

g_expec_mean.Draw('A3')
g_expec_mean.Draw('LX')

line90_h = TLine(10.,0.1,53.,0.1)
line90_v = TLine(53.,0., 53., 0.1)
if CHANNEL == 'B0':
    line90_h = TLine(0.,0.1,14.9,0.1)
    line90_v = TLine(14.9,0., 14.9, 0.1)

line90_h.SetLineWidth(4)
line90_h.Draw()
line90_v.SetLineWidth(4)
line90_v.Draw()

line95_h = TLine(10.,0.05,70.,0.05)
line95_v = TLine(70.,0., 70., 0.05)
if CHANNEL == 'B0':
    line95_h = TLine(0.,0.05,19.3,0.05)
    line95_v = TLine(19.3,0., 19.3, 0.05)

line95_h.SetLineWidth(4)
line95_h.SetLineStyle(7)
line95_h.Draw()
line95_v.SetLineWidth(4)
line95_v.SetLineStyle(7)
line95_v.Draw()

#canvas_CLs.SaveAs('result_cls_mean_'+CHANNEL+'.pdf')



#########################
#      median CLs       #
#########################

canvas_CLs_median = TCanvas('can_CLs_median', 'can_CLs_median',-700,500)
canvas_CLs_median.SetGrid(1,1)
canvas_CLs_median.SetTicks(1,1)

cls_expec_median = get_cls_median_exp_graph( list_of_bf, list_of_median_CLs , list_of_neg_sigma_CLs_delta_median , list_of_pos_sigma_CLs_delta_median , zero )

cls_expec_median.Draw('A3')
cls_expec_median.Draw('LX')

line90_h = TLine(10.,0.1,47.88,0.1)
line90_v = TLine(47.88 ,0.,47.88, 0.1)
if CHANNEL == 'B0':
    line90_h = TLine(0.,0.1,11.8,0.1)
    line90_v = TLine(11.8,0., 11.8, 0.1)

line90_h.SetLineWidth(4)
line90_h.Draw()
line90_v.SetLineWidth(4)
line90_v.Draw()

line95_h = TLine(10.,0.05,62.3,0.05)
line95_v = TLine(62.3,0., 62.3, 0.05)
if CHANNEL == 'B0':
    line95_h = TLine(0.,0.05,14.7,0.05)
    line95_v = TLine(14.7,0., 14.7, 0.05)

line95_h.SetLineWidth(4)
line95_h.SetLineStyle(7)
line95_h.Draw()
line95_v.SetLineWidth(4)
line95_v.SetLineStyle(7)
line95_v.Draw()

lhcb = do_lhcb_label(.64, .72, .9, .76)
lhcb.Draw()

#canvas_CLs_median.SaveAs('result_cls_median_'+CHANNEL+'.pdf')


