import BsMuMuPy.pyAna.CLtoyMCtools as CLtoyMCtools
from ROOT import *
from BsMuMuPy.pyMyRoot.smartpyROOT import *
import BsMuMuPy.pyAna.CLclass as CLmodule
import BsMuMuPy.pyAna.signalPDF as signalPDF
from BsMuMuPy.pyMyRoot.dataManage import rms
from array import array as afC
import os
WPATH = "/afs/cern.ch/user/d/diegoms/public/"
SIGNALDATA = os.environ["HOME"] + "/NTuples/merged/bsmumuMC09_lessevts"  ########################### NOT USED NOW
BACKGROUNDFILE = os.environ["HOME"] + "/NTuples/merged/Bs_GLs_toy2"
#BACKGROUNDFILE2 = WPATH + "jpsiXYZ"


config = "data"
output = XTuple("/afs/cern.ch/user/d/diegoms/DC04/py/Bbr90_moreL",["L/F","BR/F","RMS/F"])  ### OUTPUT FILE !!!!!!!!!
ULs = {"data":4.36}
Lo_Ls = { "data":0.11}
POINTS = 10 # Number of points in the curve
STEP = 0.05 # Luminosity Step
START = 0.05 # First luminosity point
SAMPLES_PER_POINT = 30  # Number of toyMC's to be done at a given luminosity
##Binning = {"x": afC("f",[0., 0.25 ,0.5 ,0.65 , 1.]) , "y":afC("f",[0.,1.]), "z":afC("f",[5309.6, 5333.6, 5357.6,5381.6, 5405.6, 5429.6 ]) } #### DC04 binning

Binning = {"x": afC("f",[0., 0.25 ,0.5 ,0.75 , 1.]) , "y":afC("f",[0.,1.]), "z":afC('f',[5302.3, 5322.3, 5342.3 ,5362.3, 5382.3, 5402.3, 5422.3]) } ## Bs KK based 



##### Describing signal PDF from Control Channels



#sGpdf = signalPDF.geometryDescriptor(697.3,-54.2,25.1,32.7) ## Linear parametrization of geomtry from Bs KK
#sMpdf = signalPDF.massDescriptor(mean = 5368.8, sigma = 21.7, a = 1.8, limits = [Binning["z"][0],Binning["z"][-1]]) ## TO DO: Add Errors
#sPIDpdf = signalPDF.pidDescriptor()
#hspdf = TH3F("signalPDF","signalPDF",len(Binning["x"]) - 1,Binning["x"], len(Binning["y"]) - 1 ,Binning["y"], len(Binning["z"]) -1 ,Binning["z"])

## for i in range(hspdf.GetNbinsX()):
##     for j in range(hspdf.GetNbinsY()):
##         for k in range(hspdf.GetNbinsZ()):
##             gi, gerr_i = sGpdf(Binning["x"][i],Binning["x"][i+1])
##             pj, perr_j = sPIDpdf(Binning["y"][j],Binning["y"][j+1])
##             mk, merr_k = sMpdf(Binning["z"][k],Binning["z"][k+1])
##             hspdf.SetBinContent(i+1, j+1, k+ 1, gi*pj*mk)

mean = 5362.3   ### PDG - 4
s_mean = 2.

sigma = 25.5
s_sigma = 1.

a = 1.9
s_a = 0.1

def glfs(N1,N2,N3,N4):
    N = 1.*(N1+N2+N3+N4)
    f = {0:N1/N, 1:N2/N, 2:N3/N, 3:N4/N}
    return f

N1 = 197
sN1 = 45
N2 = 129
sN2 = 25
N3 = 93
sN3 = 14
N4 = 50
sN4 = 9

fgl = glfs(N1,N2,N3,N4)
fs1p = glfs(N1+sN1,N2,N3,N4)


sMpdf = signalPDF.massDescriptor(mean, sigma, a, limits = [Binning["z"][0],Binning["z"][-1]])

def fillS(f, zpdf, name):
    hspdf = TH3F(name,name,len(Binning["x"])-1,Binning["x"],len(Binning["y"])-1,Binning["y"],  len(Binning["z"]) -1, Binning["z"])
    #f = {0:f1, 1:1-f1}
    for i in range(hspdf.GetNbinsX()):
        for k in range(hspdf.GetNbinsZ()):
            mk, merr_k = zpdf(Binning["z"][k],Binning["z"][k+1])
            hspdf.SetBinContent(i+1,1, k+ 1, f[i]*mk)
    hspdf.Scale(1./hspdf.GetSum())
    return hspdf

hspdf = fillS(fgl, sMpdf, "hspdf")
hs = hspdf
tb,fb = getTuple(BACKGROUNDFILE)

hb = CLmodule.FitInBinningByConvolution(tb, bins = Binning, name = "bmubmu")
##############################################
## Yields per fb -1 in the +- 60 Mev window ##
##############################################

SM_SIG = 13.7 ## very  roughly
B2DIM = 20./1.8e-03  ## Bkg sample of 1.8pb-1



#BREAK

hb2 = None
BMU = B2DIM
BC = 0

hbS = CLtoyMCtools.backgroundShifted(hb, BMU, hb2, BC, setB = ULs[config])  ## making shifted PDF
#alpha =
    
hbLo = CLtoyMCtools.backgroundShifted(hb, BMU, hb2, BC, setB = Lo_Ls[config])  ## making shifted PDF
    #alpha = 


#########################################
### giving PDF's for CLb computing
###
### hs : MC pdf
### hspdf: from B2hh pdf
### hb: bkg pdf
### hbS : bkg SHIFTED pdf
###
########################################
    
CL = CLmodule.CLcalculator(hs, hb)

hs.Scale(CLmodule.double(1.)/CLmodule.double(hs.GetSum()))

for i in range(POINTS):   #### Starting Loop
    luminosity = START + STEP*i
    bkgEvents = (BMU + BC)*luminosity
    sig_SM_Events = SM_SIG*luminosity
    brs =[]
    for k in range(SAMPLES_PER_POINT):
        data = CLtoyMCtools.generateSample(0., bkgEvents, hs, CL.bkg, opt = "multinomial")
        for br in range(1,3000,1):
            #data = CLtoyMCtools.generateSample(sig_SM_Events*br/3.5, bkgEvents, hs, CL.bkg, opt = "multinomial") ## generating toyMC sample, for the given luminosity and Bs --> mumu BR ( br )
            #CLb = CL.CLb(data, max(1.,sig_SM_Events*br/3.5), bkgEvents)  ## 
            CLs = CL.CLs(data, sig_SM_Events*br/3.5,bkgEvents)
            #if 1.-CLb < 2.7e-03 :# 3 sigma
            if CLs < 0.1 :# 90 % exclusion
                brs.append(br) ### add it to a list in order to get <br> +- rms(br)
                print "/0/0/0/0/0/",br
                break

    BR, RMS = rms(brs)
    print "---------------------/o/o/o/o/o/o/o/o/", luminosity, BR,RMS
    output.fillItem("L",luminosity)
    output.fillItem("BR",BR)
    output.fillItem("RMS",RMS)
    output.fill()
    
output.close()
    
     
