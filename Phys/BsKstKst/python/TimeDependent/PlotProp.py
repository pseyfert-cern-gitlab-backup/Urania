from FitnGen import *

ForceCompileLibs()

model, params = createSimPDF(TD_fit,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,data_file,fix_re_amps,fix_dirCP_asyms,fix_im_amps,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

from ROOT import *

xl = [750.]
for i in range(1,101): xl.append(750.+i*(1600.-750.)/100.)

ymod2l = []
yargl = []
for i in xl:
   ymod2l.append(model[1].Prop_Stheo(i,mV.getVal()).Rho2())
   yargl.append(model[1].Prop_Stheo(i,mV.getVal()).Theta())

from array import array

x = array('d',xl)
ymod2 = array('d',ymod2l)
yarg = array('d',yargl)

gmod2 = TGraph(len(x),x,ymod2)
garg = TGraph(len(x),x,yarg)

c = TCanvas("c","c",2000,800)
c.Divide(2)
c.cd(1)
gmod2.Draw()
c.cd(2)
garg.Draw()

c.Print("Prop_mod2_arg.root")
c.Print("Prop_mod2_arg.pdf")
