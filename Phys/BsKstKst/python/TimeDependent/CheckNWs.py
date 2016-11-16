from ROOT import *

gROOT.ProcessLine('#include "../../src/TimeDependent/NWclass_2MCs.h"')

NWclass = NWclass_2MCs()

def boolj1j2h(j1,j2,h):
   if ((j1 == 0) and (j2 == 0) and (h == 0)): return 1
   if ((j1 == 0) and (j2 == 1) and (h == 0)): return 1
   if ((j1 == 0) and (j2 == 2) and (h == 0)): return 1
   if ((j1 == 1) and (j2 == 0) and (h == 0)): return 1
   if ((j1 == 1) and (j2 == 1) and (h == 0)): return 1
   if ((j1 == 1) and (j2 == 1) and (h == 1)): return 1
   if ((j1 == 1) and (j2 == 1) and (h == 2)): return 1
   if ((j1 == 1) and (j2 == 2) and (h == 0)): return 1
   if ((j1 == 1) and (j2 == 2) and (h == 1)): return 1
   if ((j1 == 1) and (j2 == 2) and (h == 2)): return 1
   if ((j1 == 2) and (j2 == 0) and (h == 0)): return 1
   if ((j1 == 2) and (j2 == 1) and (h == 0)): return 1
   if ((j1 == 2) and (j2 == 1) and (h == 1)): return 1
   if ((j1 == 2) and (j2 == 1) and (h == 2)): return 1
   if ((j1 == 2) and (j2 == 2) and (h == 0)): return 1
   if ((j1 == 2) and (j2 == 2) and (h == 1)): return 1
   if ((j1 == 2) and (j2 == 2) and (h == 2)): return 1
   if ((j1 == 2) and (j2 == 2) and (h == 3)): return 1
   if ((j1 == 2) and (j2 == 2) and (h == 4)): return 1
   return 0

def boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp): 
    return boolj1j2h(j1,j2,h)*boolj1j2h(j1p,j2p,hp)

indexdictextred = {}
indexdictredext = {}
index = 0
for j1 in range(3):
   for j2 in range(3):
      for h in range(5):
         for j1p in range(3):
            for j2p in range(3):
               for hp in range(5):
                  for part in range(2):
                     if ((boolj1j2hj1pj2php(j1,j2,h,j1p,j2p,hp) == 1) and ((j1p+3*j2p+9*hp) <= (j1+3*j2+9*h))):
                        indexdictextred[str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)] = index
                        indexdictredext[index] = str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)
                        index += 1

def extindex(i):
   stringlist = list(indexdictredext[i])
   intlist = []
   for s in stringlist: intlist.append(eval(s))
   return intlist

pull_lists_noD = [[[],[]],[[],[]]]
pull_lists_D = [[[],[]],[[],[]]]

for iyear in range(2):
   for itrigger in range(2):
      for inw in range(380):
         j1,j2,h,j1p,j2p,hp,part = extindex(inw)
         nw_PhSp_val = NWclass.comp_PhSp(iyear,itrigger,1,j1,j2,h,j1p,j2p,hp,part)
         nw_PhSp_err = NWclass.comp_PhSp_err(iyear,itrigger,1,j1,j2,h,j1p,j2p,hp,part)
         nw_VV_val = NWclass.comp_VV(iyear,itrigger,1,j1,j2,h,j1p,j2p,hp,part)
         nw_VV_err = NWclass.comp_VV_err(iyear,itrigger,1,j1,j2,h,j1p,j2p,hp,part)
         if (nw_PhSp_val!=0 or nw_VV_val!=0): pull = (nw_PhSp_val-nw_VV_val)/max(nw_PhSp_err,nw_VV_err)
         else: pull = 0
         if (j1==2 or j2==2 or j1p==2 or j2p==2): pull_lists_D[iyear][itrigger].append(pull)
         else: pull_lists_noD[iyear][itrigger].append(pull)

find_max(year,trigger):
   l1 = pull_lists_noD[year][trigger]
   l2 = pull_lists_D[year][trigger]
   return max([max(l1),-min(l1),max(l2),-min(l2)])

h_00_D = TH1F("h_00_D","2011, L0 Global TIS",50,-find_max(0,0),find_max(0,0))
h_01_D = TH1F("h_01_D","2011, L0 Hadron TOS",50,-find_max(0,0),find_max(0,0))
h_10_D = TH1F("h_10_D","2012, L0 Global TIS",50,-find_max(0,0),find_max(0,0))
h_11_D = TH1F("h_11_D","2012, L0 Hadron TOS",50,-find_max(0,0),find_max(0,0))
h_00_noD = TH1F("h_00_noD","2011, L0 Global TIS",50,-find_max(0,0),find_max(0,0))
h_01_noD = TH1F("h_01_noD","2011, L0 Hadron TOS",50,-find_max(0,0),find_max(0,0))
h_10_noD = TH1F("h_10_noD","2012, L0 Global TIS",50,-find_max(0,0),find_max(0,0))
h_11_noD = TH1F("h_11_noD","2012, L0 Hadron TOS",50,-find_max(0,0),find_max(0,0))

h_lists_D = [h_00_D,h_01_D],[h_10_D,h_11_D]
h_lists_noD = [h_00_noD,h_01_noD],[h_10_noD,h_11_noD]

for hist in h_lists_D+h_lists_noD: hist.GetXaxis().SetTitle("Pull")
for hist in h_lists_D+h_lists_noD: hist.GetYaxis().SetTitle("Number of NWs")
for hist in h_lists_noD: hist.SetLineColor(kRed)
