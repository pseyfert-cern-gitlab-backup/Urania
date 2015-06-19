Lb11 = 1520
Lb11Err = 190

Bd11 = 731
Bd11Err = 227

Lb12 = 3339
Lb12Err = 354

Bd12 =  1041
Bd12Err = 313

#############################
## Weighting dictionaries  ##
#############################

from SomeUtils.numericFunctionClass import NF
def makeXaxis(l):
    """take a list of bins and make an 'x' axis with points at the bin center
    assuming a flat density inside the bin
    """
    out = (len(l)-1)*[0.]
    for i in range(len(l) -1 ):
        out[i] = 0.5*(l[i]+l[i+1])
    return out

omegabins = [0,.125,.25,.375,.49, .51]
omega = makeXaxis(omegabins) 
womega_os_Bd11 = [5.227/4.,60.18/48.,0.,104.15/154.,607.726/1073. ]
womega_ss_Bd11 = [0., 6.652/6.,68.87/72.,383.59/782.,279.42/710.]

DCBd11 = {}
DCBd11["tagomega_ss_nn"] = NF(omega,womega_ss_Bd11)
DCBd11["tagomega_os_cb"] = NF(omega,womega_os_Bd11)
DCBd11["tagdecision_os_cb"] = NF([-1,1], [82.8534/242., 57.2092/255.])
DCBd11["tagdecision_ss_nn"] = NF([-1,1], [148.216/414., 283.070/446.])
DCBd12 = DCBd11

from math import pi
cthetaKbins = [-1,-0.5, 0,0.5,1]
cthetaLbins = [-1,-0.5, 0,0.5,1]
phibins = [-pi,-pi*0.5, 0,0.5*pi,pi]


cthetaK = makeXaxis(cthetaKbins)
cthetaL = makeXaxis(cthetaLbins)
phi = makeXaxis(phibins)

wthetaKLb11 = [ 1.,1.7915/0.8873,1.7836/.9782,1.5184/.9814 ]
wthetaLLb11 = [ 1., .9309/1.0175,1.6953/.8276,.5963/.9468]
wphiLb11 = [ 1.,.9200/.9527,.6850/1.0991,.8145/1.0251]

womega_os_Lb11 = [0./18,145.84/223.,359.38/495.,490.20/808.,2592.68/3601. ]
womega_ss_Lb11 = [0.,5.347/19.,148.01/202.,1775.89/2577.,1529.01/2347.]
DCLb11 = {}
DCLb11["tagomega_ss_nn"] = NF( omega, womega_ss_Lb11)
DCLb11["tagomega_os_cb"] = NF( omega, womega_os_Lb11)
DCLb11["tagdecision_ss_nn"] = NF([-1,1], [812.760/1384.,1094.42/1414.])
DCLb11["tagdecision_os_cb"] = NF([-1,1], [513.839/804., 522.751/740.])
DCLb11["helcosthetaL"] = NF(cthetaK,wthetaKLb11)
DCLb11["helcosthetaK"] = NF(cthetaL,wthetaLLb11)
DCLb11["helphi"] = NF(phi,wphiLb11)

DCLb12 = DCLb11


