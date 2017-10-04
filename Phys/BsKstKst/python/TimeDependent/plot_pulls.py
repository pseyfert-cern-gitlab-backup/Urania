from ROOT import *

from _wide_nominal import par_result_dict as par_fit_results

gStyle.SetOptStat(0)
gStyle.SetOptFit(0111)

paramnames = ['reA00', 'reA01', 'reA10', 'reA02', 'reA20', 'reA11par', 'reA11perp', 'reA120', 'reA12par', 'reA12perp', 'reA210', 'reA21par', 'reA21perp', 'reA220', 'reA22par', 'reA22perp', 'reA22par2', 'reA22perp2', 'DCP', 'imA00', 'imA01', 'imA10', 'imA02', 'imA20', 'imA11par', 'imA11perp', 'imA120', 'imA12par', 'imA12perp', 'imA210', 'imA21par', 'imA21perp', 'imA220', 'imA22par', 'imA22perp', 'imA22par2', 'imA22perp2', 'phis', 'delta_m_Bs', 'gamma_Bs', 'delta_gamma_Bs', 'p0metac_SSK', 'p0metac_OS', 'Dp0half_SSK', 'Dp0half_OS', 'p1_SSK', 'p1_OS', 'Dp1half_SSK', 'Dp1half_OS', 'tres_p0_2012', 'tres_p1_2012', 'delta_220', 'f_10', 'delta_22perp', 'delta_210', 'delta_21perp', 'f_par2_22', 'f_01', 'f_00', 'f_02', 'f_12', 'f_L_12', 'f_L_11', 'f_11', 'delta_21par', 'f_perp_12', 'f_perp_11', 'delta_02', 'delta_20', 'f_par_12', 'delta_22perp2', 'f_par_11', 'f_perp_22', 'delta_10', 'f_perp_21', 'delta_22par2', 'f_22', 'f_21', 'f_20', 'f_L_22', 'f_par_22', 'f_par_21', 'f_L_21', 'delta_11perp', 'delta_12par', 'f_perp2_22', 'delta_00', 'delta_12perp', 'delta_01', 'delta_22par', 'delta_11par', 'delta_120']
#paramnames = ['reA00', 'reA01', 'reA10', 'reA11par', 'reA11perp', 'DCP', 'imA00', 'imA01', 'imA10', 'imA11par', 'imA11perp', 'phis', 'delta_m_Bs', 'gamma_Bs', 'delta_gamma_Bs', 'p0metac_SSK', 'p0metac_OS', 'Dp0half_SSK', 'Dp0half_OS', 'p1_SSK', 'p1_OS', 'Dp1half_SSK', 'Dp1half_OS', 'tres_p0_2012', 'tres_p1_2012', 'f_10', 'f_01', 'f_00', 'f_L_11', 'f_11', 'f_perp_11', 'f_par_11', 'delta_10', 'delta_11perp', 'delta_00', 'delta_01', 'delta_11par']
#paramnames = ['reA11par', 'reA11perp', 'DCP', 'imA11par', 'imA11perp', 'phis', 'delta_m_Bs', 'gamma_Bs', 'delta_gamma_Bs', 'p0metac_SSK', 'p0metac_OS', 'Dp0half_SSK', 'Dp0half_OS', 'p1_SSK', 'p1_OS', 'Dp1half_SSK', 'Dp1half_OS', 'tres_p0_2012', 'tres_p1_2012', 'f_L_11', 'f_perp_11', 'f_par_11', 'delta_11perp', 'delta_11par']

gROOT.Reset()
fout = TFile("pulls.root","RECREATE")
tout = TTree("Pulls","Pulls")
s = paramnames[0]+'_pull'
for i in range(1,len(paramnames)): s += ':'+paramnames[i]+'_pull'
tout.ReadFile("pulls_combined.dat",s)
tout.Write()

max_exps = 500
tred = tout.CloneTree(0)
for iexp in range(max_exps):
   tout.GetEntry(iexp)
   tred.Fill()

print 'Using',tred.GetEntries(),'experiments.'

par_name_dict = {'reA22perp': 'Re(A^{TT}_{#perp1})', 'reA22par2': 'Re(A^{TT}_{#parallel2})', 'delta_210': '#delta^{TV}_{0}', 'tres_p1_2012': 'p_{1}^{#sigma_{t}}(2012)', 'tres_p1_2011': 'p_{1}^{#sigma_{t}}(2011)', 'delta_00': '#delta^{SS}', 'reA10': 'Re(A^{VS})', 'p0metac_OS': 'p_{0}^{OS}-<#eta^{OS}>', 'reA220': 'Re(A^{TT}_{L})', 'reA20': 'Re(A^{TS})', 'delta_10': '#delta^{VS}', 'imA21par': 'Im(A^{TV}_{#parallel})', 'reA11par': 'Re(A^{VV}_{#parallel})', 'delta_11par': '#delta^{VV}_{#parallel}', 'DCP': '#Delta^{CP}', 'imA22perp2': 'Im(A^{TT}_{#perp2})', 'delta_12par': '#delta^{VT}_{#parallel}', 'delta_01': '#delta^{SV}', 'imA22par': 'Im(A^{TT}_{#parallel1})', 'delta_02': '#delta^{ST}', 'reA22par': 'Re(A^{TT}_{#parallel1})', 'p1_SSK': 'p_{1}^{SSK}', 'delta_22perp': '#delta^{TT}_{#perp1}', 'reA21par': 'Re(A^{TV}_{#parallel})', 'delta_21par': '#delta^{TV}_{#parallel}', 'Dp1half_SSK': '1/2 #Delta p_{1}^{SSK}', 'delta_11perp': '#delta^{VV}_{#perp}', 'f_perp2_22': 'f_{#perp2}^{TT}', 'imA210': 'Im(A^{TV}_{L})', 'tres_p0_2011': 'p_{0}^{#sigma_{t}}(2011)', 'reA120': 'Re(A^{VT}_{L})', 'imA21perp': 'Im(A^{TV}_{#perp})', 'tres_p0_2012': 'p_{0}^{#sigma_{t}}(2012)', 'delta_22perp2': '#delta^{TT}_{#perp2}', 'reA22perp2': 'Re(A^{TT}_{#perp2})', 'imA10': 'Im(A^{VS})', 'delta_21perp': '#delta^{TV}_{#perp}', 'p1_OS': 'p_{1}^{OS}', 'delta_22par2': '#delta^{TT}_{#parallel2}', 'f_22': 'f_{TT}', 'f_21': 'f_{TV}', 'f_20': 'f_{TS}', 'f_L_22': 'f_L^{TT}', 'f_par_22': 'f_{#parallel1}^{TT}', 'f_par_21': 'f_{#parallel}^{TV}', 'f_L_21': 'f_L^{TV}', 'imA12perp': 'Im(A^{VT}_{#perp})', 'delta_12perp': '#delta^{VT}_{#perp}', 'imA220': 'Im(A^{TT}_{L})', 'delta_m_Bs': '#Delta m_{B_{s}^{0}}', 'reA12par': 'Re(A^{VT}_{#parallel})', 'f_par2_22': 'f_{#parallel2}^{TT}', 'Dp1half_OS': '1/2 #Delta p_{1}^{OS}', 'f_12': 'f_{VT}', 'f_10': 'f_{VS}', 'f_11': 'f_{VV}', 'imA02': 'Im(A^{ST})', 'imA00': 'Im(A^{SS})', 'imA01': 'Im(A^{SV})', 'f_par_12': 'f_{#parallel}^{VT}', 'f_par_11': 'f_{#parallel}^{VV}', 'reA01': 'Re(A^{SV})', 'Dp0half_OS': '1/2 #Delta p_{0}^{OS}', 'reA11perp': 'Re(A^{VV}_{#perp})', 'imA120': 'Im(A^{VT}_{L})', 'f_01': 'f_{SV}', 'f_00': 'f_{SS}', 'f_02': 'f_{ST}', 'gamma_Bs': '#Gamma_{B_{s}^{0}}', 'f_perp_22': 'f_{#perp1}^{TT}', 'f_perp_21': 'f_{#perp}^{TV}', 'p0metac_SSK': 'p_{0}^{SSK}-<#eta^{SSK}>', 'imA22perp': 'Im(A^{TT}_{#perp1})', 'delta_22par': '#delta^{TT}_{#parallel1}', 'imA22par2': 'Im(A^{TT}_{#parallel2})', 'reA210': 'Re(A^{TV}_{L})', 'imA20': 'Im(A^{TS})', 'imA11perp': 'Im(A^{VV}_{#perp})', 'f_L_12': 'f_L^{VT}', 'f_L_11': 'f_L^{VV}', 'f_perp_12': 'f_{#perp}^{VT}', 'f_perp_11': 'f_{#perp}^{VV}', 'delta_120': '#delta^{VT}_{0}', 'delta_220': '#delta^{TT}_{0}', 'reA21perp': 'Re(A^{TV}_{#perp})', 'imA11par': 'Im(A^{VV}_{#parallel})', 'reA12perp': 'Re(A^{VT}_{#perp})', 'Dp0half_SSK': '1/2 #Delta p_{0}^{SSK}', 'reA00': 'Re(A^{SS})', 'reA02': 'Re(A^{ST})', 'delta_gamma_Bs': '#Delta #Gamma_{B_{s}^{0}}', 'delta_20': '#delta^{TS}', 'imA12par': 'Im(A^{VT}_{#parallel})', 'phis': '#phi_{s}'}

toyMC_syst_gaus_pars = {}

hlist = []
for ipar in range(len(paramnames)):
   par = paramnames[ipar]
   hlist.append(TH1F('h_'+par,'h_'+par,200,-10,10))
   tred.Draw(par+'_pull>>h_'+par)
   hlist[ipar].Fit("gaus")
   fun = hlist[ipar].GetFunction("gaus")
   toyMC_syst_gaus_pars[par] = [fun.GetParameter(1),fun.GetParError(1),fun.GetParameter(2),fun.GetParError(2)]
   hlist[ipar].SetTitle("")
   hlist[ipar].GetXaxis().SetTitle(par_name_dict[par]+' pull')
   hlist[ipar].GetYaxis().SetTitle('Number of experiments')
   c = TCanvas("c","c")
   hlist[ipar].Draw()
   c.Print('pulls_widetmp/'+par+'_pull.pdf')

def stringline_CUDA(par):
   mean = toyMC_syst_gaus_pars[par][0]
   mean_err = toyMC_syst_gaus_pars[par][1]
   sigma = toyMC_syst_gaus_pars[par][2]
   sigma_err = toyMC_syst_gaus_pars[par][3]
   return ('$'+par_name_dict[par]+'$ & $'+'{:.3f}'.format(mean) + '\\pm' + '{:.3f}'.format(mean_err) + '$ & $'+'{:.3f}'.format(sigma) + '\\pm' + '{:.3f}'.format(sigma_err) + '$ \\\\').replace('#','\\')

for par in paramnames: print stringline_CUDA(par)

syst_bias_dict = {}
for par in paramnames:
   mean = toyMC_syst_gaus_pars[par][0]
   mean_err = toyMC_syst_gaus_pars[par][1]
   stat_sigma = par_fit_results[par][1]
   bias = mean*stat_sigma
   bias_err = mean_err*stat_sigma
   bias_sigma = max(abs(bias),bias_err)
   syst_bias_dict[par] = (bias,bias_sigma)

systfile = open('_syst_pulls.py','w')
systfile.write('syst_dict = '+str(syst_bias_dict))
systfile.close()

fout.Close()
