from parameters import myCsp23 as myCsp

params={}
paramsError={}
for name in ("Bs","Bd"):
    params[name]={}
    paramsError[name]={}

# Note that here only the 'ds' and 'As2' parameters have values function of the mKpi bin.
# Therefore, the other parameters are just copied from the values of bin0...

params["Bd"][0] = {'fL': 0.552,                 'fpa': 0.213,                  'dpa': -2.97,                  'dpe': 2.92,                   'ds': 3.148, 'As2': 0.125, 'CSP': 1.0, "ACPL" : 0.0}
params["Bd"][1] = {'fL': params["Bd"][0]['fL'], 'fpa': params["Bd"][0]['fpa'], 'dpa': params["Bd"][0]['dpa'], 'dpe': params["Bd"][0]['dpe'], 'ds': 2.661, 'As2': 0.038, 'CSP': 1.0, 'ACPL': params["Bd"][0]['ACPL']}
params["Bd"][2] = {'fL': params["Bd"][0]['fL'], 'fpa': params["Bd"][0]['fpa'], 'dpa': params["Bd"][0]['dpa'], 'dpe': params["Bd"][0]['dpe'], 'ds': 1.768, 'As2': 0.037, 'CSP': 1.0, 'ACPL': params["Bd"][0]['ACPL']}
params["Bd"][3] = {'fL': params["Bd"][0]['fL'], 'fpa': params["Bd"][0]['fpa'], 'dpa': params["Bd"][0]['dpa'], 'dpe': params["Bd"][0]['dpe'], 'ds': 1.301, 'As2': 0.111, 'CSP': 1.0, 'ACPL': params["Bd"][0]['ACPL']}

params["Bs"][0] = {'fL': 0.510,                 'fpa': 0.172,                  'dpa': -2.619,                 'dpe': 0.053,                  'ds':  0.836, 'As2': 0.468, 'CSP': myCsp[0], 'ACPL': 0.0, 'ACPpa': 0.0, 'ACPpe': 0.0, 'ACPS': 0.0}
params["Bs"][1] = {'fL': params["Bs"][0]['fL'], 'fpa': params["Bs"][0]['fpa'], 'dpa': params["Bs"][0]['dpa'], 'dpe': params["Bs"][0]['dpe'], 'ds': -0.603, 'As2': 0.068, 'CSP': myCsp[1], 'ACPL': params["Bs"][0]['ACPL'], 'ACPpa': params["Bs"][0]['ACPpa'], 'ACPpe': params["Bs"][0]['ACPpe'], 'ACPS': params["Bs"][0]['ACPS']}
params["Bs"][2] = {'fL': params["Bs"][0]['fL'], 'fpa': params["Bs"][0]['fpa'], 'dpa': params["Bs"][0]['dpa'], 'dpe': params["Bs"][0]['dpe'], 'ds': -1.748, 'As2': 0.073, 'CSP': myCsp[2], 'ACPL': params["Bs"][0]['ACPL'], 'ACPpa': params["Bs"][0]['ACPpa'], 'ACPpe': params["Bs"][0]['ACPpe'], 'ACPS': params["Bs"][0]['ACPS']}
params["Bs"][3] = {'fL': params["Bs"][0]['fL'], 'fpa': params["Bs"][0]['fpa'], 'dpa': params["Bs"][0]['dpa'], 'dpe': params["Bs"][0]['dpe'], 'ds': -1.819, 'As2': 0.591, 'CSP': myCsp[3], 'ACPL': params["Bs"][0]['ACPL'], 'ACPpa': params["Bs"][0]['ACPpa'], 'ACPpe': params["Bs"][0]['ACPpe'], 'ACPS': params["Bs"][0]['ACPS']}


paramsError["Bd"][0] = {'fL': 0.002,                      'fpa': 0.002,                       'dpa':  0.01,                       'dpe': 0.01,                        'ds': 0.052, 'As2': 0.005, "ACPL" : 0.0}
paramsError["Bd"][1] = {'fL': paramsError["Bd"][0]['fL'], 'fpa': paramsError["Bd"][0]['fpa'], 'dpa': paramsError["Bd"][0]['dpa'], 'dpe': paramsError["Bd"][0]['dpe'], 'ds': 0.039, 'As2': 0.002, "ACPL" : 0.0}
paramsError["Bd"][2] = {'fL': paramsError["Bd"][0]['fL'], 'fpa': paramsError["Bd"][0]['fpa'], 'dpa': paramsError["Bd"][0]['dpa'], 'dpe': paramsError["Bd"][0]['dpe'], 'ds': 0.018, 'As2': 0.003, "ACPL" : 0.0}
paramsError["Bd"][3] = {'fL': paramsError["Bd"][0]['fL'], 'fpa': paramsError["Bd"][0]['fpa'], 'dpa': paramsError["Bd"][0]['dpa'], 'dpe': paramsError["Bd"][0]['dpe'], 'ds': 0.019, 'As2': 0.007, "ACPL" : 0.0}

paramsError["Bs"][0] = {'fL': 0.025,                      'fpa': 0.025,                       'dpa': 0.158,                       'dpe': 0.118,                       'ds': 0.152, 'As2': 0.124, 'ACPL': 0.0, 'ACPpa': 0.0, 'ACPpe': 0.0, 'ACPS': 0.0}
paramsError["Bs"][1] = {'fL': paramsError["Bs"][0]['fL'], 'fpa': paramsError["Bs"][0]['fpa'], 'dpa': paramsError["Bs"][0]['dpa'], 'dpe': paramsError["Bs"][0]['dpe'], 'ds': 0.250, 'As2': 0.027, 'ACPL': paramsError["Bs"][0]['ACPL'], 'ACPpa': paramsError["Bs"][0]['ACPpa'], 'ACPpe': paramsError["Bs"][0]['ACPpe'], 'ACPS': paramsError["Bs"][0]['ACPS']}
paramsError["Bs"][2] = {'fL': paramsError["Bs"][0]['fL'], 'fpa': paramsError["Bs"][0]['fpa'], 'dpa': paramsError["Bs"][0]['dpa'], 'dpe': paramsError["Bs"][0]['dpe'], 'ds': 0.171, 'As2': 0.050, 'ACPL': paramsError["Bs"][0]['ACPL'], 'ACPpa': paramsError["Bs"][0]['ACPpa'], 'ACPpe': paramsError["Bs"][0]['ACPpe'], 'ACPS': paramsError["Bs"][0]['ACPS']}
paramsError["Bs"][3] = {'fL': paramsError["Bs"][0]['fL'], 'fpa': paramsError["Bs"][0]['fpa'], 'dpa': paramsError["Bs"][0]['dpa'], 'dpe': paramsError["Bs"][0]['dpe'], 'ds': 0.145, 'As2': 0.108, 'ACPL': paramsError["Bs"][0]['ACPL'], 'ACPpa': paramsError["Bs"][0]['ACPpa'], 'ACPpe': paramsError["Bs"][0]['ACPpe'], 'ACPS': paramsError["Bs"][0]['ACPS']}

# -- angular params 
for name in ("Bs","Bd"):
    print"INFO: Note that here only the 'ds' and 'As2' parameters have values function of the mKpi bin."
    print"      Therefore, the other parameters are just copied from the values of bin0..."
    for ibin in range(0,4):
        print"Angular param for %s in bin %i = "%(name,ibin),params[name][ibin]


for name in ("Bs","Bd"):
    for i in range(4,23):  
        params[name][i] = params[name][3]
        paramsError[name][i] = paramsError[name][3]

# Parametric acceptance parameters
paramsAcc={}
paramsAccError={}
for name in ("Bs","Bd"):
    paramsAcc[name]={}
    paramsAccError[name]={}

paramsAcc["Bd"]["2011"] = {'c1_psi':  -5.20101e-01,
                           'c2_psi':  -7.33299e-01,
                           'c3_psi':  -2.90606e-01,
                           'c4_psi':   2.69475e-01,
                           'c2_theta': 2.76201e-01}
paramsAcc["Bs"]["2011"] = {'c1_psi':   paramsAcc["Bd"]["2011"]['c1_psi'],
                           'c2_psi':   paramsAcc["Bd"]["2011"]['c2_psi'], 
                           'c3_psi':   paramsAcc["Bd"]["2011"]['c3_psi'], 
                           'c4_psi':   paramsAcc["Bd"]["2011"]['c4_psi'], 
                           'c2_theta': paramsAcc["Bd"]["2011"]['c2_theta']}

paramsAcc["Bd"]["2012"] = {'c1_psi':  -5.20101e-01,
                           'c2_psi':  -7.33299e-01,
                           'c3_psi':  -2.90606e-01,
                           'c4_psi':   2.69475e-01,
                           'c2_theta': 2.76201e-01}
paramsAcc["Bs"]["2012"] = {'c1_psi':   paramsAcc["Bd"]["2012"]['c1_psi'], 
                           'c2_psi':   paramsAcc["Bd"]["2012"]['c2_psi'], 
                           'c3_psi':   paramsAcc["Bd"]["2012"]['c3_psi'], 
                           'c4_psi':   paramsAcc["Bd"]["2012"]['c4_psi'], 
                           'c2_theta': paramsAcc["Bd"]["2012"]['c2_theta']}







# params["Bd"][0] = {'fL': 0.510,                 'fpa': 0.172,                  'dpa': -2.619,                 'dpe': 0.053,                  'ds':  0.836, 'As2': 0.468}
# params["Bd"][1] = {'fL': params["Bd"][0]['fL'], 'fpa': params["Bd"][0]['fpa'], 'dpa': params["Bd"][0]['dpa'], 'dpe': params["Bd"][0]['dpe'], 'ds': -0.603, 'As2': 0.068}
# params["Bd"][2] = {'fL': params["Bd"][0]['fL'], 'fpa': params["Bd"][0]['fpa'], 'dpa': params["Bd"][0]['dpa'], 'dpe': params["Bd"][0]['dpe'], 'ds': -1.748, 'As2': 0.073}
# params["Bd"][3] = {'fL': params["Bd"][0]['fL'], 'fpa': params["Bd"][0]['fpa'], 'dpa': params["Bd"][0]['dpa'], 'dpe': params["Bd"][0]['dpe'], 'ds': -1.819, 'As2': 0.591}

# params["Bs"][0] = {'fL': 0.510,                 'fpa': 0.172,                  'dpa': -2.619,                 'dpe': 0.053,                  'ds':  0.836, 'As2': 0.468}
# params["Bs"][1] = {'fL': params["Bs"][0]['fL'], 'fpa': params["Bs"][0]['fpa'], 'dpa': params["Bs"][0]['dpa'], 'dpe': params["Bs"][0]['dpe'], 'ds': -0.603, 'As2': 0.068}
# params["Bs"][2] = {'fL': params["Bs"][0]['fL'], 'fpa': params["Bs"][0]['fpa'], 'dpa': params["Bs"][0]['dpa'], 'dpe': params["Bs"][0]['dpe'], 'ds': -1.748, 'As2': 0.073}
# params["Bs"][3] = {'fL': params["Bs"][0]['fL'], 'fpa': params["Bs"][0]['fpa'], 'dpa': params["Bs"][0]['dpa'], 'dpe': params["Bs"][0]['dpe'], 'ds': -1.819, 'As2': 0.591}


# paramsError["Bd"][0] = {'fL': 2.2256,                     'fpa': 3.05666,                     'dpa': 2.531878,                    'dpe': -2.82822,                    'ds': 0.9126, 'As2': 0.91264}
# paramsError["Bd"][1] = {'fL': paramsError["Bd"][0]['fL'], 'fpa': paramsError["Bd"][0]['fpa'], 'dpa': paramsError["Bd"][0]['dpa'], 'dpe': paramsError["Bd"][0]['dpe'], 'ds': 0.9126, 'As2': 0.91264}
# paramsError["Bd"][2] = {'fL': paramsError["Bd"][0]['fL'], 'fpa': paramsError["Bd"][0]['fpa'], 'dpa': paramsError["Bd"][0]['dpa'], 'dpe': paramsError["Bd"][0]['dpe'], 'ds': 0.9126, 'As2': 0.91264}
# paramsError["Bd"][3] = {'fL': paramsError["Bd"][0]['fL'], 'fpa': paramsError["Bd"][0]['fpa'], 'dpa': paramsError["Bd"][0]['dpa'], 'dpe': paramsError["Bd"][0]['dpe'], 'ds': 0.9126, 'As2': 0.91264}

# paramsError["Bs"][0] = {'fL': 2.2256,                     'fpa': 3.05666,                     'dpa': 2.531878,                    'dpe': -2.82822,                    'ds': 0.9126, 'As2': 0.91264}
# paramsError["Bs"][1] = {'fL': paramsError["Bs"][0]['fL'], 'fpa': paramsError["Bs"][0]['fpa'], 'dpa': paramsError["Bs"][0]['dpa'], 'dpe': paramsError["Bs"][0]['dpe'], 'ds': 0.9126, 'As2': 0.91264}
# paramsError["Bs"][2] = {'fL': paramsError["Bs"][0]['fL'], 'fpa': paramsError["Bs"][0]['fpa'], 'dpa': paramsError["Bs"][0]['dpa'], 'dpe': paramsError["Bs"][0]['dpe'], 'ds': 0.9126, 'As2': 0.91264}
# paramsError["Bs"][3] = {'fL': paramsError["Bs"][0]['fL'], 'fpa': paramsError["Bs"][0]['fpa'], 'dpa': paramsError["Bs"][0]['dpa'], 'dpe': paramsError["Bs"][0]['dpe'], 'ds': 0.9126, 'As2': 0.91264}
