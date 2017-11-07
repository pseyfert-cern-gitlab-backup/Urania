
import argparse
import sys
import os.path
import time
import math
from math import sqrt
from array import array
from TrackCalib.Utils import do1DPlot, do2DPlot, ErrorMsg, InfoMsgList, InfoMsg, WarnMsg
from ROOT import TFile, TColor, TGraph,TGraphAsymmErrors, gStyle, kFALSE, kTRUE, gROOT


def set_palette(name="palette", ncontours=999):
    """Set a color palette from a given RGB list
    stops, red, green and blue should all be lists of the same length
    see set_decent_colors for an example"""

    if name == "gray" or name == "grayscale":
        stops = [0.00, 0.34, 0.61, 0.84, 1.00]
        red   = [1.00, 0.84, 0.61, 0.34, 0.00]
        green = [1.00, 0.84, 0.61, 0.34, 0.00]
        blue  = [1.00, 0.84, 0.61, 0.34, 0.00]
    # elif name == "whatever":
        # (define more palettes)
    else:
        # default palette, looks cool
        stops = [0.00, 0.34, 0.61, 0.84, 1.00]
        red   = [0.00, 0.00, 0.87, 1.00, 0.51]
        green = [0.00, 0.81, 1.00, 0.20, 0.00]
        blue  = [0.51, 1.00, 0.12, 0.00, 0.00]

    s = array('d', stops)
    r = array('d', red)
    g = array('d', green)
    b = array('d', blue)

    npoints = len(s)
    TColor.CreateGradientColorTable(npoints, s, r, g, b, ncontours)
    gStyle.SetNumberContours(ncontours)



#execution
def Plot(year, WGProduct, method="", simVer = "Sim09b", polarity = "", variables = "", vartitles = "", verbose = False, matchCrit = "",  maxError = 0.03, maxDeviation = 0.3, ignoreBins = "P-ETA:1-2,5-1"):


    # declare path with fitted distributions / root files
    if matchCrit == "":
        datapath    = "results/"+year
        if (WGProduct): datapath +="_WG"
        if polarity != "": datapath +="_" + polarity
        datapath += "/"
        mcpath    = datapath +simVer+"/"
        # output path
        path = "plots/"+year+"_"+simVer
        if polarity != "": path +="_" + polarity
        if (WGProduct): path += "_WG"
        path += "/"
    else:
        datapath    = "results/"+year
        if (WGProduct): datapath +="_WG"
        datapath += "_tight/"
        if polarity != "": datapath +="_" + polarity
        mcpath    = datapath +simVer+"/"
        # output path
        path = "plots/"+year+"_"+simVer
        if (WGProduct): path += "_WG"
        if polarity != "": path +="_" + polarity
        path += "_tight/"
    if not os.path.exists(path):
        if verbose: InfoMsgList("Creating new folder for plots:", path)
        os.makedirs(path)

    tmpConds = year.split("_")
    dataver = tmpConds[0]+" Data, "+tmpConds[1]
    if WGProduct: dataver = tmpConds[0]+" Data WG, "+tmpConds[1]
    mcver   = tmpConds[0]+" MC, "+simVer


    # start printout
    print '##########################################################'
    print '#               Welcome to TrackEff Plotter              #'
    print '##########################################################'


    #set custom colour palette for smoother 2d scaling
    set_palette()
    #set LHCb style
    #gROOT.ProcessLine(".x lhcbStyle.C")
    gStyle.SetOptTitle(kFALSE);
    gStyle.SetOptStat(0);



    #default axis titles, anything else needs to be parsed
    title_dict = {
            'P'         : '#it{p} [MeV/#it{c}]',
            'ETA'       : '#eta',
        #    'Mother_ETA': 'Mother #eta',
            'nSPDHits'  : '#it{N}_{SPD hits}',
            'nPVs'      : '#it{N}_{PV}',
            }
    #default variable list
    var_list = [ i for i in sorted(title_dict.keys()) ]

    #default axis titles, anything else needs to be parsed
    title_dict_2d = {
            'P-ETA'         : ['#it{p} [MeV/#it{c}]','#eta'],
            }
    #default variable list
    var_list_2d = [ i for i in sorted(title_dict_2d.keys()) ]


    #check if custom variables are requested, use instead of defaults
    if variables != "":
        var_custom = variables
        var_custom = var_custom.split(',')

        var_list = var_custom
        if verbose: InfoMsgList( "Custom set of variables requested:", var_list)

    #check if custom titles are defined, require if custom variables
    if vartitles != "":
        title_custom = vartitles
        #title_custom = title_custom[1:-1].split(';')
        title_custom = title_custom.split(';')


        for var_string in title_custom:
            tmpvar = var_string.split(':')

            #fill dictionary
            title_dict[tmpvar[0]] = tmpvar[1]
        if verbose: InfoMsgList( "Custom variable axis titles defined:", title_dict)

    #read in method options, only plot requested methods, combine when appropriate
    valid_methods = ["T","Velo","Long"]
    if method == "": method_list = valid_methods
    else:
        method_list = method.split(",")

    #check if valid methods given, remove otherwise
    for meth in method_list:
        if meth not in valid_methods:
            WarnMsg( "Invalid method " + meth + " given, must be one of 'Long', 'T', 'Velo'. Will be ignored!")
            method_list.remove(meth)

    #create dictionary holding all necessary TGraphAsymmErrors
    graph_dict = {}

    for var in var_list:
        graph_dict[var] = {}

        for meth in method_list:

            #list to check if all requested files exist
            file_list = []
            #read in the fit results files
            data_file_string = datapath+"trackEff_Data_"+var+"_"+meth+"_method.root"
            mc_file_string   = mcpath+"trackEff_MC_"+var+"_"+meth+"_method.root"
            file_list.append(data_file_string)
            file_list.append(mc_file_string)


            #check if all requested files are available
            missing_file = False
            for i in file_list:
                if not os.path.isfile(i):
                    WarnMsg("File " + i + " missing, please produce using the fit script! Skipping variable "+ var + " for now.")
                    missing_file = True
                    break
            if missing_file:
                continue #if files for a requested variable and method are missing, skip the variable

            data_file = TFile(data_file_string)
            mc_file = TFile(mc_file_string)

            #add graphs
            graph_data = data_file.Get("Efficiency "+var)
            graph_mc   = mc_file.Get("Efficiency "+var)
            graph_dict[var][meth] = [graph_data, graph_mc]

            if verbose:
                InfoMsg("Creating plots in " + var + " for method " + meth)
            do1DPlot(path, var, title_dict[var], meth, graph_data, graph_mc, data_version = dataver, mc_version = mcver, verbose=verbose, polarity = polarity)

        #combine T and Velo method if given
        if (graph_dict[var] == {}):
            print ErrorMsg("No files found! Please produce them using the fit script!")
            return
        if "T" and "Velo" in method_list:
            graph_data_T = graph_dict[var]["T"][0]
            graph_mc_T = graph_dict[var]["T"][1]
            graph_data_Velo = graph_dict[var]["Velo"][0]
            graph_mc_Velo = graph_dict[var]["Velo"][1]
            #if also "Long", create average of both combined and Long
            if "Long" in method_list:
                graph_data_Long = graph_dict[var]["Long"][0]
                graph_mc_Long = graph_dict[var]["Long"][1]

            #get the x points and errors from graphs; this is really tedious, but TGraphs don't seem to have a Clone function
            x_size = graph_data_T.GetN()
            x_arr_buf = graph_data_T.GetX()
            x_arr_buf.SetSize(x_size)
            arr_x = array('d', x_arr_buf)
            xU_arr_buf = graph_data_T.GetEXhigh()
            xU_arr_buf.SetSize(x_size)
            arr_xEU = array('d', xU_arr_buf)
            xL_arr_buf = graph_data_T.GetEXlow()
            xL_arr_buf.SetSize(x_size)
            arr_xEL = array('d', xL_arr_buf)
            xmin = arr_x[0] - arr_xEL[0]
            xmax = arr_x[x_size-1] + arr_xEU[x_size-1]

            #same for data effs
            eff_T_buf = graph_data_T.GetY()
            eff_T_buf.SetSize(x_size)
            eff_T = array('d', eff_T_buf)
            errU_T_buf = graph_data_T.GetEYhigh()
            errU_T_buf.SetSize(x_size)
            errU_T = array('d', errU_T_buf)
            errL_T_buf = graph_data_T.GetEYlow()
            errL_T_buf.SetSize(x_size)
            errL_T = array('d', errL_T_buf)
            eff_Velo_buf = graph_data_Velo.GetY()
            eff_Velo_buf.SetSize(x_size)
            eff_Velo = array('d', eff_Velo_buf)
            errU_Velo_buf = graph_data_Velo.GetEYhigh()
            errU_Velo_buf.SetSize(x_size)
            errU_Velo = array('d', errU_Velo_buf)
            errL_Velo_buf = graph_data_Velo.GetEYlow()
            errL_Velo_buf.SetSize(x_size)
            errL_Velo = array('d', errL_Velo_buf)
            eff_comb_data = array('d', [0]*x_size)
            errU_comb_data = array('d', [0]*x_size)
            errL_comb_data = array('d', [0]*x_size)
            if "Long" in method_list:
                eff_Long_buf = graph_data_Long.GetY()
                eff_Long_buf.SetSize(x_size)
                eff_Long = array('d', eff_Long_buf)
                errU_Long_buf = graph_data_Long.GetEYhigh()
                errU_Long_buf.SetSize(x_size)
                errU_Long = array('d', errU_Long_buf)
                errL_Long_buf = graph_data_Long.GetEYlow()
                errL_Long_buf.SetSize(x_size)
                errL_Long = array('d', errL_Long_buf)
                average_data = array('d', [0]*x_size)
                averageU_data = array('d', [0]*x_size)
                averageL_data = array('d', [0]*x_size)

            #same for mc effs
            eff_mc_T_buf = graph_mc_T.GetY()
            eff_mc_T_buf.SetSize(x_size)
            eff_mc_T = array('d', eff_mc_T_buf)
            errU_mc_T_buf = graph_mc_T.GetEYhigh()
            errU_mc_T_buf.SetSize(x_size)
            errU_mc_T = array('d', errU_mc_T_buf)
            errL_mc_T_buf = graph_mc_T.GetEYlow()
            errL_mc_T_buf.SetSize(x_size)
            errL_mc_T = array('d', errL_mc_T_buf)
            eff_mc_Velo_buf = graph_mc_Velo.GetY()
            eff_mc_Velo_buf.SetSize(x_size)
            eff_mc_Velo = array('d', eff_mc_Velo_buf)
            errU_mc_Velo_buf = graph_mc_Velo.GetEYhigh()
            errU_mc_Velo_buf.SetSize(x_size)
            errU_mc_Velo = array('d', errU_mc_Velo_buf)
            errL_mc_Velo_buf = graph_mc_Velo.GetEYlow()
            errL_mc_Velo_buf.SetSize(x_size)
            errL_mc_Velo = array('d', errL_mc_Velo_buf)
            eff_comb_mc = array('d', [0]*x_size)
            errU_comb_mc = array('d', [0]*x_size)
            errL_comb_mc = array('d', [0]*x_size)
            if "Long" in method_list:
                eff_mc_Long_buf = graph_mc_Long.GetY()
                eff_mc_Long_buf.SetSize(x_size)
                eff_mc_Long = array('d', eff_mc_Long_buf)
                errU_mc_Long_buf = graph_mc_Long.GetEYhigh()
                errU_mc_Long_buf.SetSize(x_size)
                errU_mc_Long = array('d', errU_mc_Long_buf)
                errL_mc_Long_buf = graph_mc_Long.GetEYlow()
                errL_mc_Long_buf.SetSize(x_size)
                errL_mc_Long = array('d', errL_mc_Long_buf)
                average_mc = array('d', [0]*x_size)
                averageU_mc = array('d', [0]*x_size)
                averageL_mc = array('d', [0]*x_size)



            for k in xrange(x_size):
                i = k
                eff_comb_data[i] = eff_T[i]*eff_Velo[i]
                eff_comb_mc[i] = eff_mc_T[i]*eff_mc_Velo[i]
                if eff_T[i]!=0 and eff_Velo[i]!=0:
                    errU_comb_data[i] = eff_comb_data[i] * sqrt ( (errU_T[i]/eff_T[i])**2 + (errU_Velo[i]/eff_Velo[i])**2 )
                    errL_comb_data[i] = eff_comb_data[i] * sqrt ( (errL_T[i]/eff_T[i])**2 + (errL_Velo[i]/eff_Velo[i])**2 )
                else:
                    errU_comb_data[i]=0
                    errL_comb_data[i]=0
                if eff_mc_T[i]!=0 and eff_mc_Velo!=0:
                    errU_comb_mc[i] = eff_comb_mc[i] * sqrt ( (errU_mc_T[i]/eff_mc_T[i])**2 + (errU_mc_Velo[i]/eff_mc_Velo[i])**2 )
                    errL_comb_mc[i] = eff_comb_mc[i] * sqrt ( (errL_mc_T[i]/eff_mc_T[i])**2 + (errL_mc_Velo[i]/eff_mc_Velo[i])**2 )
                else:
                    errU_comb_mc[i]=0
                    errL_comb_mc[i]=0

                if "Long" in method_list:
                    err_comb_data = 0.5*(errU_comb_data[i] + errL_comb_data[i])
                    err_comb_mc = 0.5*(errU_comb_mc[i] + errL_comb_mc[i])
                    err_long_data = 0.5*(errU_Long[i] + errL_Long[i])
                    err_long_mc = 0.5*(errU_mc_Long[i] + errL_mc_Long[i])

                    weight_comb_data = 1./(err_comb_data**2) if err_comb_data!=0 else 0
                    weightU_comb_data = 1./(errU_comb_data[i]**2) if errU_comb_data[i]!=0 else weight_comb_data
                    weightL_comb_data = 1./(errL_comb_data[i]**2) if errL_comb_data[i]!=0 else weight_comb_data
                    weight_long_data = 1./(err_long_data**2) if err_long_data!=0 else 0
                    weightU_long_data = 1./(errU_Long[i]**2) if errU_Long[i]!=0 else weight_long_data
                    weightL_long_data = 1./(errL_Long[i]**2) if errL_Long[i]!=0 else weight_long_data
                    average_data[i] = (eff_comb_data[i]*weight_comb_data + eff_Long[i]*weight_long_data)/(weight_comb_data + weight_long_data)
                    if errU_comb_data[i]==0:
                        averageU_data[i] = 1./sqrt(weightU_long_data)
                    elif errU_Long[i]==0:
                        averageU_data[i] = 1./sqrt(weightU_comb_data)
                    else:
                        averageU_data[i] = 1./sqrt(weightU_comb_data + weightU_long_data)
                    if average_data[i]+averageU_data[i] > 1.: averageU_data[i]=1.-average_data[i] #to fix effs > 1
                    averageL_data[i] = 1./sqrt(weightL_comb_data + weightL_long_data)

                    weight_comb_mc = 1./(err_comb_mc**2) if err_comb_mc!=0 else 0
                    weightU_comb_mc = 1./(errU_comb_mc[i]**2) if errU_comb_mc[i]!=0 else weight_comb_mc
                    weightL_comb_mc = 1./(errL_comb_mc[i]**2) if errL_comb_mc[i]!=0 else weight_comb_mc
                    weight_long_mc = 1./(err_long_mc**2) if err_long_mc!=0 else 0
                    weightU_long_mc = 1./(errU_mc_Long[i]**2) if errU_mc_Long[i]!=0 else weight_long_mc
                    weightL_long_mc = 1./(errL_mc_Long[i]**2) if errL_mc_Long[i]!=0 else weight_long_mc
                    average_mc[i] = (eff_comb_mc[i]*weight_comb_mc + eff_mc_Long[i]*weight_long_mc)/(weight_comb_mc + weight_long_mc)
                    if errU_comb_mc[i]==0:
                        averageU_mc[i] = 1./sqrt(weightU_long_mc)
                    elif errU_mc_Long[i]==0:
                        averageU_mc[i] = 1./sqrt(weightU_comb_mc)
                    else:
                        averageU_mc[i] = 1./sqrt(weightU_comb_mc + weightU_long_mc)
                    if average_mc[i]+averageU_mc[i] > 1.: averageU_mc[i]=1.-average_mc[i]
                    averageL_mc[i] = 1./sqrt(weightL_comb_mc + weightL_long_mc)


            graph_Comb_data = TGraphAsymmErrors(x_size, arr_x, eff_comb_data, arr_xEL, arr_xEU, errL_comb_data, errU_comb_data)
            graph_Comb_mc = TGraphAsymmErrors(x_size, arr_x, eff_comb_mc, arr_xEL, arr_xEU, errL_comb_mc, errU_comb_mc)

            if verbose:
                InfoMsg("Creating plots in "+ var + " for combination of T and Velo methods")
            do1DPlot(path, var, title_dict[var], "Combined", graph_Comb_data, graph_Comb_mc, data_version = dataver, mc_version = mcver, polarity = polarity)

            if "Long" in method_list:
                graph_final_data = TGraphAsymmErrors(x_size, arr_x, average_data, arr_xEL, arr_xEU, averageL_data, averageU_data)
                graph_final_mc = TGraphAsymmErrors(x_size, arr_x, average_mc, arr_xEL, arr_xEU, averageL_mc, averageU_mc)
                if verbose:
                    InfoMsg("Creating plots in " + var + " for average of Long and combined methods")
                do1DPlot(path, var, title_dict[var], "Final", graph_final_data, graph_final_mc, data_version = dataver, mc_version = mcver, polarity = polarity)


    InfoMsg("All 1D variable plots done!")


    for var2d in var_list_2d:
        graph_dict[var2d] = {}

        for meth in method_list:

            #list to check if all requested files exist
            file_list = []
            #read in the fit results files
            data_file_string = datapath+"trackEff_Data_"+var2d+"_"+meth+"_method.root"
            mc_file_string   = mcpath+"trackEff_MC_"+var2d+"_"+meth+"_method.root"
            file_list.append(data_file_string)
            file_list.append(mc_file_string)


            #check if all requested files are available
            missing_file = False
            for i in file_list:
                if not os.path.isfile(i):
                    WarnMsg("File " + i + " missing, please produce using the fit script! Skipping 2D variable " + var2d + " for now.")
                    missing_file = True
                    break
            if missing_file:
                continue #if files for a requested variable and method are missing, skip the variable

            data_file = TFile.Open(data_file_string,"read")
            mc_file = TFile.Open(mc_file_string,"read")

            #add graphs
            gROOT.cd()
            graph_data = data_file.Get("Efficiency "+var2d).Clone()
            graph_mc   = mc_file.Get("Efficiency "+var2d).Clone()
            graph_dict[var2d][meth] = [graph_data, graph_mc]


            if verbose:
                InfoMsg("Creating plots in " + var2d + " for method " + meth)
            do2DPlot(path, var2d, title_dict_2d[var2d], meth, graph_dict[var2d][meth][0], graph_dict[var2d][meth][1], maxError=maxError,maxDeviation= maxDeviation, ignoreBins = ignoreBins, data_version = dataver, mc_version = mcver)

            #combine T and Velo method if given
        if (graph_dict[var] == {}):
            print ErrorMsg("No files found! Please produce them using the fit script!")
            return
        if "T" and "Velo" in method_list:

            graph_data_T = graph_dict[var2d]["T"][0]
            graph_mc_T = graph_dict[var2d]["T"][1]
            graph_data_Velo = graph_dict[var2d]["Velo"][0]
            graph_mc_Velo = graph_dict[var2d]["Velo"][1]
            graph_data_Comb = graph_data_T.Clone("")
            graph_mc_Comb = graph_mc_T.Clone("")
            #if also "Long", create average of both combined and Long
            if "Long" in method_list:
                graph_data_Long = graph_dict[var2d]["Long"][0]
                graph_mc_Long = graph_dict[var2d]["Long"][1]
                graph_data_Final = graph_data_Long.Clone()
                graph_mc_Final = graph_mc_Long.Clone()


            for k in xrange(graph_data_T.GetNbinsX()):
                i = k+1
                for l in xrange(graph_data_T.GetNbinsY()):
                    j = l+1
                    eff_comb_data = graph_data_T.GetBinContent(i,j)*graph_data_Velo.GetBinContent(i,j)
                    eff_comb_mc   = graph_mc_T.GetBinContent(i,j)*graph_mc_Velo.GetBinContent(i,j)
                    if not (graph_data_T.GetBinContent(i,j)==0):
                        if not (graph_data_Velo.GetBinContent(i,j)==0):
                            err_comb_data = eff_comb_data * sqrt ( (graph_data_T.GetBinError(i,j)/graph_data_T.GetBinContent(i,j))**2 + (graph_data_Velo.GetBinError(i,j)/graph_data_Velo.GetBinContent(i,j))**2 )
                        else: err_comb_data = eff_comb_data * sqrt ( (graph_data_T.GetBinError(i,j)/graph_data_T.GetBinContent(i,j))**2)
                    elif not (graph_data_Velo.GetBinContent(i,j)==0):
                            err_comb_data = eff_comb_data * sqrt ( (graph_data_Velo.GetBinError(i,j)/graph_data_Velo.GetBinContent(i,j))**2 )
                    else: err_comb_data = 0
                    err_comb_mc   = eff_comb_mc * sqrt ( (graph_mc_T.GetBinError(i,j)/graph_mc_T.GetBinContent(i,j))**2 + (graph_mc_Velo.GetBinError(i,j)/graph_mc_Velo.GetBinContent(i,j))**2 )


                    graph_data_Comb.SetBinContent(i,j,eff_comb_data)
                    graph_data_Comb.SetBinError(i,j,err_comb_data)
                    graph_mc_Comb.SetBinContent(i,j,eff_comb_mc)
                    graph_mc_Comb.SetBinError(i,j,err_comb_mc)

                    if "Long" in method_list:
                        weight_comb_data = 1./(err_comb_data**2) if err_comb_data!=0 else 0.
                        weight_long_data = 1./(graph_data_Long.GetBinError(i,j)**2)
                        average_data = (eff_comb_data*weight_comb_data + graph_data_Long.GetBinContent(i,j)*weight_long_data)/(weight_comb_data + weight_long_data)
                        average_err_data = sqrt(1./(weight_comb_data + weight_long_data))

                        graph_data_Final.SetBinContent(i,j,average_data)
                        graph_data_Final.SetBinError(i,j,average_err_data)


                        weight_comb_mc = 1./(err_comb_mc**2)
                        weight_long_mc = 1./(graph_mc_Long.GetBinError(i,j)**2)
                        average_mc = (eff_comb_mc*weight_comb_mc + graph_mc_Long.GetBinContent(i,j)*weight_long_mc)/(weight_comb_mc + weight_long_mc)
                        average_err_mc = sqrt(1./(weight_comb_mc + weight_long_mc))

                        graph_mc_Final.SetBinContent(i,j,average_mc)
                        graph_mc_Final.SetBinError(i,j,average_err_mc)


            if verbose:
                InfoMsg("Creating plots in " + var2d + " for combination of T and Velo methods")
            do2DPlot(path, var2d, title_dict_2d[var2d], "Combined", graph_data_Comb, graph_mc_Comb, maxError=maxError,maxDeviation= maxDeviation, ignoreBins = ignoreBins, data_version = dataver, mc_version = mcver)

            if "Long" in method_list:
                if verbose:
                    InfoMsg("Creating plots in " + var2d + " for average of Long and combined methods")
                do2DPlot(path, var2d, title_dict_2d[var2d], "Final", graph_data_Final, graph_mc_Final, maxError=maxError,maxDeviation= maxDeviation, ignoreBins = ignoreBins, data_version = dataver, mc_version = mcver)


    InfoMsg("All 2D variable plots and tables done!")


    InfoMsg("All plots and tables done!")
