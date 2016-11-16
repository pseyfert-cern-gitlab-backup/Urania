from ROOT import *
from math import *
import os
import sys
import time
import mass_params as mass_parameters
import angular_params as angular_parameters
from Lb_yields import Lb_yield
from PDF_2013_Asym_toys import Aprod_s, Aprod_d, A_D 
from parameters import KpiBins4 as KpiBins

debug = True

nLHCb = 1
print"nLHCb =",nLHCb

doACPS = 1

half = 0.5

l_years = ["2011","2012"]
l_signs = ["neg","pos"]
l_bins = []
for ibin in range(len(KpiBins)-1):
    l_bins.append(ibin)

if len(l_bins) != 4:
    print "ERROR:: Using %s mKpi bins, while the code is defined only for 4 bins..."%len(l_bins)
    exit(1)

# -----------------------------------------
# --------------- YIELDS ------------------
# -----------------------------------------

gRandom = TRandom3()
seed = 0 # see http://root.cern.ch/root/html/TRandom3.html#TRandom3:SetSeed
gRandom.SetSeed(seed)

if not seed == 0:
    for i in range(0,20):
        print "parameters_toys.py::WARNING:: Random seed is constant !!!!"

# --- from fit to data
yields_data = {}
for name in ("Bs","Bd","Combi","Lb2JpsipK","Lb2JpsipPi"):
    yields_data[name]={}
    
for name in ("Bd2Jpsipipi","Bs2Jpsipipi","Bs2JpsiKK"):
    yields_data[name]={}
    for year in l_years:
        yields_data[name][year]={}


tmpSumYield = 0
factorAmplif = 1.
yields_data["Combi"]["2011"]        = {0:  factorAmplif*(1.15625e+02 + 7.31822e+01), 
                                       1:  factorAmplif*(1.08370e+02 + 1.11515e+02), 
                                       2:  factorAmplif*(1.12093e+02 + 9.85924e+01), 
                                       3:  factorAmplif*(1.07394e+02 + 1.18068e+02), 
                                       4:              4*tmpSumYield}

yields_data["Combi"]["2012"]        = {0:  factorAmplif*(2.05350e+02 + 1.11787e+02),                                  
                                       1:  factorAmplif*(2.87821e+02 + 2.58925e+02),  
                                       2:  factorAmplif*(2.19580e+02 + 2.65683e+02), 
                                       3:  factorAmplif*(2.06519e+02 + 2.66019e+02), 
                                       4:              4*tmpSumYield}

yields_data["Bd"]["2011"]           = {0:  3.62756e+03 + 3.84802e+03, 
                                       1:  1.34010e+04 + 1.36133e+04, 
                                       2:  1.19630e+04 + 1.22911e+04, 
                                       3:  3.93704e+03 + 3.91114e+03, 
                                       4:              4*tmpSumYield}

yields_data["Bd"]["2012"]           = {0:  6.21675e+03 + 6.42600e+03, 
                                       1:  2.91272e+04 + 2.96251e+04, 
                                       2:  2.60963e+04 + 2.63947e+04, 
                                       3:  8.39308e+03 + 8.59159e+03, 
                                       4:              4*tmpSumYield}

factorAmplif = 1.
yields_data["Bs"]["2011"]           = {0:  factorAmplif*(2.46842e+01 + 4.36737e+01), 
                                       1:  factorAmplif*(9.20347e+01 + 1.05430e+02), 
                                       2:  factorAmplif*(1.12781e+02 + 1.21597e+02), 
                                       3:  factorAmplif*(3.95276e+01 + 5.02357e+01), 
                                       4:              4*tmpSumYield}

yields_data["Bs"]["2012"]           = {0:  factorAmplif*(4.77489e+01 + 6.72210e+01), 
                                       1:  factorAmplif*(2.21264e+02 + 2.25429e+02), 
                                       2:  factorAmplif*(2.81690e+02 + 2.82513e+02), 
                                       3:  factorAmplif*(9.92477e+01 + 1.26692e+02), 
                                       4:              4*tmpSumYield}


yields_data["Lb2JpsipK"]["2011"]    = {0:  Lb_yield['LbK']["2011"][0],#4.31468e+00 + 3.94029e+00, 
                                       1:  Lb_yield['LbK']["2011"][1],#4.02070e+00 + 3.96266e+00, 
                                       2:  Lb_yield['LbK']["2011"][2],#4.01468e+00 + 4.03171e+00, 
                                       3:  Lb_yield['LbK']["2011"][3],#4.23089e+00 + 3.88151e+00, 
                                       4:              4*tmpSumYield}

yields_data["Lb2JpsipK"]["2012"]    = {0:  Lb_yield['LbK']["2012"][0],#7.88926e+00 + 7.93866e+00, 
                                       1:  Lb_yield['LbK']["2012"][1],#8.04136e+00 + 8.19463e+00, 
                                       2:  Lb_yield['LbK']["2012"][2],#9.07751e+00 + 8.90059e+00, 
                                       3:  Lb_yield['LbK']["2012"][3],#9.28469e+00 + 9.46206e+00, 
                                       4:              4*tmpSumYield}

yields_data["Lb2JpsipPi"]["2011"]   = {0:  Lb_yield['Lbpi']["2011"][0],#2.19878e+00 + 1.99668e+00, 
                                       1:  Lb_yield['Lbpi']["2011"][1],#3.01251e+00 + 2.98596e+00, 
                                       2:  Lb_yield['Lbpi']["2011"][2],#2.96800e+00 + 3.09700e+00, 
                                       3:  Lb_yield['Lbpi']["2011"][3],#3.12209e+00 + 3.05047e+00, 
                                       4:              4*tmpSumYield}

yields_data["Lb2JpsipPi"]["2012"]   = {0:  Lb_yield['Lbpi']["2012"][0],#5.94276e+00 + 5.93652e+00, 
                                       1:  Lb_yield['Lbpi']["2012"][1],#5.99146e+00 + 6.10997e+00, 
                                       2:  Lb_yield['Lbpi']["2012"][2],#6.09226e+00 + 6.01749e+00, 
                                       3:  Lb_yield['Lbpi']["2012"][3],#7.20404e+00 + 7.33642e+00, 
                                       4:              4*tmpSumYield}

yields_data["Bd2Jpsipipi"]["2011"]={0:	6,
                                    1:	12,
                                    2:	14,
                                    3:	22,
                                    4:	54}

yields_data["Bd2Jpsipipi"]["2012"]={0:	15,
                                    1:	24,
                                    2:	36,
                                    3:	49,
                                    4:	123}

yields_data["Bs2Jpsipipi"]["2011"]={0:	2,
                                    1:	2,
                                    2:	3,
                                    3:	3,
                                    4:	10}

yields_data["Bs2Jpsipipi"]["2012"]={0:	4,
                                    1:	5,
                                    2:	8,
                                    3:	10,
                                    4:	28}

yields_data["Bs2JpsiKK"]["2011"]={0:	7,
                                  1:	3,
                                  2:	1,
                                  3:	0,
                                  4:	12}

yields_data["Bs2JpsiKK"]["2012"]={0:	14,
                                  1:	5,
                                  2:	3,
                                  3:	1,
                                  4:	23}

# --- Get total yields
for name in ("Bs","Bd","Combi","Lb2JpsipK","Lb2JpsipPi"):
    for year in l_years:
        for ibin in l_bins:
            yields_data[name][year][4] += yields_data[name][year][ibin]

# --- Poissonized yields
yields_data_Poissonized = {}
for name in ("Bs","Bd","Combi","Lb2JpsipK","Lb2JpsipPi","Bd2Jpsipipi","Bs2Jpsipipi","Bs2JpsiKK"):
    yields_data_Poissonized[name]={}
    for year in l_years:
        yields_data_Poissonized[name][year] = gRandom.Poisson(yields_data[name][year][4]*nLHCb)

# --- Usefull fractions
yieldsFraction = {}
for name in ("Bs","Bd","Combi","Lb2JpsipK","Lb2JpsipPi","Bd2Jpsipipi","Bs2Jpsipipi","Bs2JpsiKK"):
    yieldsFraction[name]={}
    for year in l_years:
        yieldsFraction[name][year]={}
        for ibin in l_bins:
            yieldsFraction[name][year][ibin] = float(yields_data[name][year][ibin])/float(yields_data[name][year][4])
            
# --- Yields for the toy studies
yields_toys_bins_True = {}
yields_toys_bins_Poissonized = {}
for name in ("Bs","Bd","Combi","Lb2JpsipK","Lb2JpsipPi","Bd2Jpsipipi","Bs2Jpsipipi","Bs2JpsiKK"):
    yields_toys_bins_True[name]={}
    yields_toys_bins_Poissonized[name]={}
    for year in l_years:
        yields_toys_bins_True[name][year]={}
        yields_toys_bins_Poissonized[name][year]={}
        for sign in l_signs:
            yields_toys_bins_True[name][year][sign]={}
            yields_toys_bins_Poissonized[name][year][sign]={}
        for ibin in l_bins:
            if name == "Bs":
                fACPp_Bs = (angular_parameters.params[name][ibin]["fL"]*angular_parameters.params[name][ibin]["ACPL"] + 
                            angular_parameters.params[name][ibin]["fpa"]*angular_parameters.params[name][ibin]["ACPpa"] + 
                            (1 - angular_parameters.params[name][ibin]["fL"] - angular_parameters.params[name][ibin]["fpa"])*angular_parameters.params[name][ibin]["ACPpe"])
                ACPN_Bs = (angular_parameters.params[name][ibin]["As2"]*angular_parameters.params[name][ibin]["ACPS"] + 
                           (1 - angular_parameters.params[name][ibin]["As2"])*fACPp_Bs)
                
                if doACPS:
                    psACP_Bs = half*(1+ACPN_Bs)
                else:
                    psACP_Bs = half*(1 + angular_parameters.params[name][ibin]["fL"]*angular_parameters.params[name][ibin]["ACPL"] + 
                                     angular_parameters.params[name][ibin]["fpa"]*angular_parameters.params[name][ibin]["ACPpa"] + 
                                     (1 - angular_parameters.params[name][ibin]["fL"] - angular_parameters.params[name][ibin]["fpa"])*angular_parameters.params[name][ibin]["ACPpe"])
                
                yields_toys_bins_Poissonized[name][year]["neg"][ibin] = int(round(gRandom.Poisson(float(yields_data[name][year][ibin]*
                                                                                            (1 - psACP_Bs)*
                                                                                            (1 - A_D.getVal() + Aprod_s.getVal())))))
                yields_toys_bins_Poissonized[name][year]["pos"][ibin] = int(round(gRandom.Poisson(float(yields_data[name][year][ibin]*
                                                                                            (psACP_Bs)*
                                                                                            (1 + A_D.getVal() - Aprod_s.getVal())))))
                yields_toys_bins_True[name][year]["neg"][ibin] = int(round(yields_data[name][year][ibin]*
                                                                      (1 - psACP_Bs)*
                                                                      (1 - A_D.getVal() + Aprod_s.getVal())))
                yields_toys_bins_True[name][year]["pos"][ibin] = int(round(yields_data[name][year][ibin]*
                                                                      (psACP_Bs)*
                                                                      (1 + A_D.getVal() - Aprod_s.getVal())))
            elif name == "Bd":
                psACP_Bd = half #BY CONSTRUCTION

                yields_toys_bins_Poissonized[name][year]["neg"][ibin] = int(round(gRandom.Poisson(float(yields_data[name][year][ibin]*
                                                                                            (1 - psACP_Bs)*
                                                                                            (1 + A_D.getVal() - Aprod_d.getVal())))))
                yields_toys_bins_Poissonized[name][year]["pos"][ibin] = int(round(gRandom.Poisson(float(yields_data[name][year][ibin]*
                                                                                            (psACP_Bs)*
                                                                                            (1 - A_D.getVal() + Aprod_d.getVal())))))
                yields_toys_bins_True[name][year]["neg"][ibin] = int(round(yields_data[name][year][ibin]*
                                                                      (1 - psACP_Bs)*
                                                                      (1 + A_D.getVal() - Aprod_d.getVal())))
                yields_toys_bins_True[name][year]["pos"][ibin] = int(round(yields_data[name][year][ibin]*
                                                                      (psACP_Bs)*
                                                                      (1 - A_D.getVal() + Aprod_d.getVal())))
            else:
                yields_toys_bins_Poissonized[name][year]["neg"][ibin] = int(round(gRandom.Poisson(float(yields_data[name][year][ibin]*half))))
                yields_toys_bins_Poissonized[name][year]["pos"][ibin] = int(round(gRandom.Poisson(float(yields_data[name][year][ibin]*half))))
                yields_toys_bins_True[name][year]["neg"][ibin] = int(round(yields_data[name][year][ibin]*half))
                yields_toys_bins_True[name][year]["pos"][ibin] = int(round(yields_data[name][year][ibin]*half))

# -------------------------------------------------
# --------------- Fit parameters ------------------
# -------------------------------------------------

# ---------- MASS ----------
mass_params = {}
mass_params_error = {}
for name in ("Bs","Bd","Combi"):
    mass_params[name]={}
    mass_params_error[name]={}
    for year in l_years:
        mass_params[name][year]={}
        mass_params_error[name][year]={}
        for sign in l_signs:
            mass_params[name][year][sign]={}
            mass_params_error[name][year][sign]={}
            for ibin in l_bins:
                mass_params[name][year][sign][ibin]       = mass_parameters.paramsDATA[name][ibin]
                mass_params_error[name][year][sign][ibin] = mass_parameters.paramsDATAError[name][ibin]

for name in ("Lb2JpsipK","Lb2JpsipPi"):
    mass_params[name]={}
    mass_params_error[name]={}
    for year in l_years:
        mass_params[name][year]={}
        mass_params_error[name][year]={}
        for sign in l_signs:
            mass_params[name][year][sign]={}
            mass_params_error[name][year][sign]={}
            for ibin in l_bins:
                mass_params[name][year][sign][ibin]       = mass_parameters.paramsMC[name][ibin]
                mass_params_error[name][year][sign][ibin] = mass_parameters.paramsMCError[name][ibin]

# ---------- ANGLES ----------
angular_params = {}
angular_params_error = {}
for name in ("Bs","Bd"):
    angular_params[name]={}
    angular_params_error[name]={}
    for ibin in l_bins:
        angular_params[name][ibin]       = angular_parameters.params[name][ibin]
        angular_params_error[name][ibin] = angular_parameters.paramsError[name][ibin]

parametric_angular_acceptance = {}
parametric_angular_acceptance_error = {}
for name in ("Bs","Bd"):
        parametric_angular_acceptance[name]       = angular_parameters.paramsAcc[name]
        parametric_angular_acceptance_error[name] = angular_parameters.paramsAccError[name]

# ---------- ACP for non zero tests ---------
gRandom.SetSeed(1) # Seed different from 0 will always give the same results 

rounded = False
precision = 10000.0

l_ACP = ["ACPL","ACPpa","ACPpe","ACPS"]

l_sets = []
for i in range(10):
    l_sets.append("set_%s"%i)

d_ACPs = {}
for set in l_sets:
    d_ACPs[set] = {}
    for acp in l_ACP:
        if rounded:
            d_ACPs[set][acp] = round(precision*gRandom.Uniform(-1,1))/precision
        else:
            d_ACPs[set][acp] = gRandom.Uniform(-1,1)

if debug:
    for set in l_sets:
        print d_ACPs[set]

gRandom.SetSeed(0) # Put back the seed to zero

# --------------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------------
# --------------------------------------------------------------------------------------------------

#----------- DEBUGGING -----------
if(debug):

    # -- yields 
    for name in ("Bs","Bd","Combi","Lb2JpsipK","Lb2JpsipPi","Bd2Jpsipipi","Bs2Jpsipipi","Bs2JpsiKK"):
        for year in l_years:
            for sign in l_signs:
                for ibin in l_bins:
                    print"Yield for %s in %s_%s in bin %i ="%(name,year,sign,ibin),yields_toys_bins_Poissonized[name][year][sign][ibin]

    # -- mass params 
    for name in ("Bs","Bd","Combi"):
        for year in l_years:
            for sign in l_signs:
                for ibin in l_bins:
                    print"Mass param for %s in %s_%s in bin %i ="%(name,year,sign,ibin),mass_params[name][year][sign][ibin]

    for name in ("Lb2JpsipK","Lb2JpsipPi"):
        for year in l_years:
            for sign in l_signs:
                for ibin in l_bins:
                    print"Mass param for %s in %s_%s in bin %i ="%(name,year,sign,ibin),mass_params[name][year][sign][ibin]

    # -- angular params 
    for name in ("Bs","Bd"):
        print"INFO: Note that here only the 'ds' and 'As2' parameters have values function of the mKpi bin."
        print"      Therefore, the other parameters are just copied from the values of bin0..."
        for ibin in l_bins:
            print"Angular param for %s in bin %i = "%(name,ibin),angular_params[name][ibin]


