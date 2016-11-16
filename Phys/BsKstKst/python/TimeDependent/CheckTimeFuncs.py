from ROOT import *
from FitnGen import *

ForceCompileLibs()

model, params = createSimPDF(TD_fit,Blinding,No_CP_Switch,No_dirCP_Switch,Same_CP_Switch,acc_type,\
inf_t_res,wide_window,data_file,fix_wave_fractions,fix_dirCP_asyms,fix_strong_phases,fix_weak_phases,fix_mixing_params,fix_calib_params,\
pw_alternative_model,f_Kst1410_rel2_Kst892,delta_Kst1410_rel2_Kst892,f_Kst1680_rel2_Kst892,delta_Kst1680_rel2_Kst892)

nbins = 1000

h_cosh_ideal = TH1F("h_cosh_ideal","h_cosh_ideal",nbins,0,12)
h_sinh_ideal = TH1F("h_sinh_ideal","h_sinh_ideal",nbins,0,12)
h_cos_ideal = TH1F("h_cos_ideal","h_cos_ideal",nbins,0,12)
h_sin_ideal = TH1F("h_sin_ideal","h_sin_ideal",nbins,0,12)
h_cosh_old = TH1F("h_cosh_old","h_cosh_old",nbins,0,12)
h_sinh_old = TH1F("h_sinh_old","h_sinh_old",nbins,0,12)
h_cos_old = TH1F("h_cos_old","h_cos_old",nbins,0,12)
h_sin_old = TH1F("h_sin_old","h_sin_old",nbins,0,12)
h_cosh_spl = TH1F("h_cosh_spl","h_cosh_spl",nbins,0,12)
h_sinh_spl = TH1F("h_sinh_spl","h_sinh_spl",nbins,0,12)
h_cos_spl = TH1F("h_cos_spl","h_cos_spl",nbins,0,12)
h_sin_spl = TH1F("h_sin_spl","h_sin_spl",nbins,0,12)

for h in [h_cosh_ideal,h_sinh_ideal,h_cos_ideal,h_sin_ideal]:
   h.SetLineColor(kBlue)
for h in [h_cosh_old,h_sinh_old,h_cos_old,h_sin_old]:
   h.SetLineColor(kGreen+3)
   h.SetLineStyle(2)
for h in [h_cosh_spl,h_sinh_spl,h_cos_spl,h_sin_spl]:
   h.SetLineColor(kRed)
   h.SetLineStyle(7)

c = TCanvas("c","c")
c.Divide(2,2)

def plothistos(terrval):

   for i in range(nbins):
      h_cosh_ideal.SetBinContent(i+1,model[1].T_cosh_ideal(h_cosh_ideal.GetBinCenter(i+1)))
      h_sinh_ideal.SetBinContent(i+1,model[1].T_sinh_ideal(h_sinh_ideal.GetBinCenter(i+1)))
      h_cos_ideal.SetBinContent(i+1,model[1].T_cos_ideal(h_cos_ideal.GetBinCenter(i+1)))
      h_sin_ideal.SetBinContent(i+1,model[1].T_sin_ideal(h_sin_ideal.GetBinCenter(i+1)))
      h_cosh_old.SetBinContent(i+1,model[1].T_cosh(h_cosh_old.GetBinCenter(i+1),terrval))
      h_sinh_old.SetBinContent(i+1,model[1].T_sinh(h_sinh_old.GetBinCenter(i+1),terrval))
      h_cos_old.SetBinContent(i+1,model[1].T_cos(h_cos_old.GetBinCenter(i+1),terrval))
      h_sin_old.SetBinContent(i+1,model[1].T_sin(h_sin_old.GetBinCenter(i+1),terrval))
      h_cosh_spl.SetBinContent(i+1,model[1].T_cosh_spl(h_cosh_spl.GetBinCenter(i+1),terrval))
      h_sinh_spl.SetBinContent(i+1,model[1].T_sinh_spl(h_sinh_spl.GetBinCenter(i+1),terrval))
      h_cos_spl.SetBinContent(i+1,model[1].T_cos_spl(h_cos_spl.GetBinCenter(i+1),terrval))
      h_sin_spl.SetBinContent(i+1,model[1].T_sin_spl(h_sin_spl.GetBinCenter(i+1),terrval))

   c.cd(1)
   h_cosh_ideal.Draw()
   h_cosh_old.Draw("same")
   h_cosh_spl.Draw("same")
   c.cd(2)
   h_sinh_ideal.Draw()
   h_sinh_old.Draw("same")
   h_sinh_spl.Draw("same")
   c.cd(3)
   h_cos_ideal.Draw()
   h_cos_old.Draw("same")
   h_cos_spl.Draw("same")
   c.cd(4)
   h_sin_ideal.Draw()
   h_sin_old.Draw("same")
   h_sin_spl.Draw("same")
   c.cd(1).SetLogx(1)
   c.cd(2).SetLogx(1)
   c.cd(3).SetLogx(1)
   c.cd(4).SetLogx(1)
