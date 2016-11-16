from FitnGen import *

ForceCompileLibs()

model, params = createSimPDF(TD_fit,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

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

# Structure to translate between extended index j1j2hj1pj2phppart and reduced index i.
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

def redindex(j1,j2,h,j1p,j2p,hp,part):
   return indexdictextred[str(j1)+str(j2)+str(h)+str(j1p)+str(j2p)+str(hp)+str(part)]

def extindex(i):
   stringlist = list(indexdictredext[i])
   intlist = []
   for s in stringlist: intlist.append(eval(s))
   return intlist

h1 = ROOT.TH1F("h1","h1",100,-25,25)
h2 = ROOT.TH1F("h2","h2",100,-25,25)
h3 = ROOT.TH1F("h3","h3",100,-25,25)
h4 = ROOT.TH1F("h4","h4",100,-25,25)

for i in range(380):
   h1.Fill(model[1].NWpull(*extindex(i)))
   h2.Fill(model[2].NWpull(*extindex(i)))
   h3.Fill(model[3].NWpull(*extindex(i)))
   h4.Fill(model[4].NWpull(*extindex(i)))
