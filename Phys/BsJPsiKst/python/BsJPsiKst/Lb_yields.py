from math import *

debug = True#False

Lb_yieldTmp={}
Lb_yieldErr={}

for name in ("LbK","Lbpi"):
    Lb_yieldTmp[name]={}
    Lb_yieldErr[name]={}
    for year in ("2011","2012"):
        Lb_yieldTmp[name][year]={}
        Lb_yieldErr[name][year]={}
    	

Lb_yieldTmp["LbK"]["2012"][0] = 4
Lb_yieldTmp["LbK"]["2012"][1] = 5
Lb_yieldTmp["LbK"]["2012"][2] = 9
Lb_yieldTmp["LbK"]["2012"][3] = 6

Lb_yieldTmp["LbK"]["2011"][0] = 2
Lb_yieldTmp["LbK"]["2011"][1] = 2
Lb_yieldTmp["LbK"]["2011"][2] = 4
Lb_yieldTmp["LbK"]["2011"][3] = 3

Lb_yieldTmp["Lbpi"]["2012"][0] = 6
Lb_yieldTmp["Lbpi"]["2012"][1] = 6
Lb_yieldTmp["Lbpi"]["2012"][2] = 6
Lb_yieldTmp["Lbpi"]["2012"][3] = 7

Lb_yieldTmp["Lbpi"]["2011"][0] = 2
Lb_yieldTmp["Lbpi"]["2011"][1] = 3
Lb_yieldTmp["Lbpi"]["2011"][2] = 3
Lb_yieldTmp["Lbpi"]["2011"][3] = 3


Lb_estimated_val={}
Lb_estimated_err={}
for name in ("LbK","Lbpi"):
        Lb_estimated_val[name]={}
        Lb_estimated_err[name]={}

# Latest estimated values taken from the ANA note
Lb_estimated_val["LbK"]["2012"] = 20
Lb_estimated_err["LbK"]["2012"] = 18
Lb_estimated_val["LbK"]["2011"] = 5
Lb_estimated_err["LbK"]["2011"] = 3

Lb_estimated_val["Lbpi"]["2012"] = 33
Lb_estimated_err["Lbpi"]["2012"] = 8
Lb_estimated_val["Lbpi"]["2011"] = 16
Lb_estimated_err["Lbpi"]["2011"] = 5

Lb_yield_PosNeg={}
Lb_yield_PosNeg_err={}
Lb_yield={}
Lb_yield_err={}
for name in ("LbK","Lbpi"):
    Lb_yield_PosNeg[name]={}
    Lb_yield_PosNeg_err[name]={}
    Lb_yield[name]={}
    Lb_yield_err[name]={}
    for year in ("2011","2012"):
        Lb_yield_PosNeg[name][year]={}
        Lb_yield_PosNeg_err[name][year]={}
        Lb_yield[name][year]={}
        Lb_yield_err[name][year]={}
        for ibin in range(0,4):
            Lb_yield[name][year][ibin] = (Lb_estimated_val[name][year] * (float(Lb_yieldTmp[name][year][ibin]) / float(sum(Lb_yieldTmp[name][year].values()))))
            Lb_yield_err[name][year][ibin] = (Lb_estimated_err[name][year] * (float(Lb_yieldTmp[name][year][ibin]) / float(sum(Lb_yieldTmp[name][year].values()))))
            if debug: print "Lb_yield of %5s in %s_bin%s = %f +/- %f"%(name, year, ibin, Lb_yield[name][year][ibin], Lb_yield_err[name][year][ibin])
            for sign in ("neg","pos"):
                Lb_yield_PosNeg[name][year][sign]={}
                Lb_yield_PosNeg_err[name][year][sign]={}
                for ibin in range(0,4):
                    Lb_yield_PosNeg[name][year][sign][ibin] = (0.5 * Lb_estimated_val[name][year] * (float(Lb_yieldTmp[name][year][ibin]) / float(sum(Lb_yieldTmp[name][year].values()))))
                    Lb_yield_PosNeg_err[name][year][sign][ibin] = (0.5 * Lb_estimated_err[name][year] * (float(Lb_yieldTmp[name][year][ibin]) / float(sum(Lb_yieldTmp[name][year].values()))))
                    if debug: print "Lb_yield of %5s in %s%s_bin%s = %f +/- %f"%(name, year, sign, ibin, Lb_yield_PosNeg[name][year][sign][ibin], Lb_yield_PosNeg_err[name][year][sign][ibin])
