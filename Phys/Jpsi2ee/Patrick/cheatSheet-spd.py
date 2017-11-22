from AllMacroes import *
from ROOT import *
gROOT.ProcessLine(".x lhcbStyle.C")

_small = TFile.Open("Jpsi2017-1548-1554-Small.root")
smallEE = _small.Get("Jpsi2ee") # data ee

smallEE.Show(0) # all leaves of the Tree
r=SandB(smallEE,0,"mass","spd<15","","fabs(epPT-emPT)/(epPT+emPT)<0.7","N",2000,4000)
png("mass below and above 15 spd")

r=SandB(smallEE,0,"spd","pt>3000","","fabs(epPT-emPT)/(epPT+emPT)<0.7","IM",0,50)
gPad.SetLogy()
png("low spd region")

r=SandB(smallEE,0,"mass","spd<15","","fabs(epPT-emPT)/(epPT+emPT)<0.7","N",2000,4000)
png("mass below and above 15 spd")

r=SandB(smallEE,0,"mass","spd<10","spd>=10 && spd<15","fabs(epPT-emPT)/(epPT+emPT)<0.7","N",2000,4000)
png("mass up to 10 and 15")

r=SandB(smallEE,0,"mass","spd<6","spd>=6 && spd<10","fabs(epPT-emPT)/(epPT+emPT)<0.7","",2000,4000)
png("mass up to 6 and 10")



