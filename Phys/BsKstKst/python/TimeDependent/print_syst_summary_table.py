from math import *

from _syst_pulls import syst_dict as syst_dict_pulls
from _syst_highvectorreso import syst_dict as syst_dict_highvectorreso
from _syst_L import syst_dict as syst_dict_L
from _syst_nw import syst_dict as syst_dict_nw
from _syst_scalarmassamp import syst_dict as syst_dict_scalarmassamp
from _syst_vard import syst_dict as syst_dict_vard
from _syst_varDCPprod import syst_dict as syst_dict_varDCPprod
from _syst_varresonancepars import syst_dict as syst_dict_varresonancepars

syst_list = []
syst_list.append(['TD fit bias',syst_dict_pulls,1])
syst_list.append(['Meson radius, $d$',syst_dict_vard,1])
syst_list.append(['Resonance mass and width',syst_dict_varresonancepars,0])
syst_list.append(['S-wave mass model',syst_dict_scalarmassamp,1])
#syst_list.append(['Extra vector resonances',syst_dict_highvectorreso,0])
syst_list.append(['Orbital angular momentum, $L$',syst_dict_L,0])
syst_list.append(['Normalisation weights',syst_dict_nw,1])
syst_list.append(['Production asymmetry',syst_dict_varDCPprod,1])

par_name_lists = [["phis","f_par_12","DCP","f_21","delta_m_Bs"],["f_L_21","f_11","f_par_21","f_L_11","delta_120"],["f_par_11","delta_12par","delta_11par","delta_12perp","delta_11perp"],["delta_210","f_01","delta_21par","f_10","delta_21perp"],["delta_01","f_22","delta_10","f_L_22","f_00"],["f_par_22","delta_00","f_perp_22","f_02","f_par2_22"],["f_20","delta_220","delta_02","delta_22par","delta_20"],["delta_22perp","f_12","delta_22par2","f_L_12","delta_22perp2"]]

par_name_dict = {'mV': 'mV', 'gammaV': 'gammaV', 'mT': 'mT', 'gammaT': 'gammaT', 'c1_mass_swave': 'c_{1}^{mass}','c2_mass_swave': 'c_{2}^{mass}','c3_mass_swave': 'c_{3}^{mass}','c4_mass_swave': 'c_{4}^{mass}','c5_mass_swave': 'c_{5}^{mass}','c6_mass_swave': 'c_{6}^{mass}','c7_mass_swave': 'c_{7}^{mass}','c8_mass_swave': 'c_{8}^{mass}','c9_mass_swave': 'c_{9}^{mass}', 'reA22perp': 'Re(A^{TT}_{#perp1})', 'reA22par2': 'Re(A^{TT}_{#parallel2})', 'delta_210': '#delta^{TV}_{0}', 'tres_p1_2012': 'p_{1}^{#sigma_{t}}(2012)', 'tres_p1_2011': 'p_{1}^{#sigma_{t}}(2011)', 'delta_00': '#delta^{SS}', 'reA10': 'Re(A^{VS})', 'p0metac_OS': 'p_{0}^{OS}-<#eta^{OS}>', 'reA220': 'Re(A^{TT}_{L})', 'reA20': 'Re(A^{TS})', 'delta_10': '#delta^{VS}', 'imA21par': 'Im(A^{TV}_{#parallel})', 'reA11par': 'Re(A^{VV}_{#parallel})', 'delta_11par': '#delta^{VV}_{#parallel}', 'DCP': '#Delta^{CP}', 'DCP_SS': 'd#Delta^{CP}_{SS}', 'DCP_SV': 'd#Delta^{CP}_{SV}', 'DCP_VS': 'd#Delta^{CP}_{VS}', 'DCP_ST': 'd#Delta^{CP}_{ST}', 'DCP_TS': 'd#Delta^{CP}_{TS}', 'DCP_VT': 'd#Delta^{CP}_{VT}', 'DCP_TV': 'd#Delta^{CP}_{TV}', 'DCP_TT': 'd#Delta^{CP}_{TT}', 'imA22perp2': 'Im(A^{TT}_{#perp2})', 'delta_12par': '#delta^{VT}_{#parallel}', 'delta_01': '#delta^{SV}', 'imA22par': 'Im(A^{TT}_{#parallel1})', 'delta_02': '#delta^{ST}', 'reA22par': 'Re(A^{TT}_{#parallel1})', 'p1_SSK': 'p_{1}^{SSK}', 'delta_22perp': '#delta^{TT}_{#perp1}', 'reA21par': 'Re(A^{TV}_{#parallel})', 'delta_21par': '#delta^{TV}_{#parallel}', 'Dp1half_SSK': '1/2 #Delta p_{1}^{SSK}', 'delta_11perp': '#delta^{VV}_{#perp}', 'f_perp2_22': 'f_{#perp2}^{TT}', 'imA210': 'Im(A^{TV}_{L})', 'tres_p0_2011': 'p_{0}^{#sigma_{t}}(2011)', 'reA120': 'Re(A^{VT}_{L})', 'imA21perp': 'Im(A^{TV}_{#perp})', 'tres_p0_2012': 'p_{0}^{#sigma_{t}}(2012)', 'delta_22perp2': '#delta^{TT}_{#perp2}', 'reA22perp2': 'Re(A^{TT}_{#perp2})', 'imA10': 'Im(A^{VS})', 'delta_21perp': '#delta^{TV}_{#perp}', 'p1_OS': 'p_{1}^{OS}', 'delta_22par2': '#delta^{TT}_{#parallel2}', 'f_22': 'f_{TT}', 'f_21': 'f_{TV}', 'f_20': 'f_{TS}', 'f_L_22': 'f_L^{TT}', 'f_par_22': 'f_{#parallel1}^{TT}', 'f_par_21': 'f_{#parallel}^{TV}', 'f_L_21': 'f_L^{TV}', 'imA12perp': 'Im(A^{VT}_{#perp})', 'delta_12perp': '#delta^{VT}_{#perp}', 'imA220': 'Im(A^{TT}_{L})', 'delta_m_Bs': '#Delta m_{B_{s}^{0}}', 'reA12par': 'Re(A^{VT}_{#parallel})', 'f_par2_22': 'f_{#parallel2}^{TT}', 'Dp1half_OS': '1/2 #Delta p_{1}^{OS}', 'f_12': 'f_{VT}', 'f_10': 'f_{VS}', 'f_11': 'f_{VV}', 'imA02': 'Im(A^{ST})', 'imA00': 'Im(A^{SS})', 'imA01': 'Im(A^{SV})', 'f_par_12': 'f_{#parallel}^{VT}', 'f_par_11': 'f_{#parallel}^{VV}', 'reA01': 'Re(A^{SV})', 'Dp0half_OS': '1/2 #Delta p_{0}^{OS}', 'reA11perp': 'Re(A^{VV}_{#perp})', 'imA120': 'Im(A^{VT}_{L})', 'f_01': 'f_{SV}', 'f_00': 'f_{SS}', 'f_02': 'f_{ST}', 'gamma_Bs': '#Gamma_{B_{s}^{0}}', 'f_perp_22': 'f_{#perp1}^{TT}', 'f_perp_21': 'f_{#perp}^{TV}', 'p0metac_SSK': 'p_{0}^{SSK}-<#eta^{SSK}>', 'imA22perp': 'Im(A^{TT}_{#perp1})', 'delta_22par': '#delta^{TT}_{#parallel1}', 'imA22par2': 'Im(A^{TT}_{#parallel2})', 'reA210': 'Re(A^{TV}_{L})', 'imA20': 'Im(A^{TS})', 'imA11perp': 'Im(A^{VV}_{#perp})', 'f_L_12': 'f_L^{VT}', 'f_L_11': 'f_L^{VV}', 'f_perp_12': 'f_{#perp}^{VT}', 'f_perp_11': 'f_{#perp}^{VV}', 'delta_120': '#delta^{VT}_{0}', 'delta_220': '#delta^{TT}_{0}', 'reA21perp': 'Re(A^{TV}_{#perp})', 'imA11par': 'Im(A^{VV}_{#parallel})', 'reA12perp': 'Re(A^{VT}_{#perp})', 'Dp0half_SSK': '1/2 #Delta p_{0}^{SSK}', 'reA00': 'Re(A^{SS})', 'reA02': 'Re(A^{ST})', 'delta_gamma_Bs': '#Delta #Gamma_{B_{s}^{0}}', 'delta_20': '#delta^{TS}', 'imA12par': 'Im(A^{VT}_{#parallel})', 'phis': '#phi_{s}', 'dphi_SS': 'd#phi_{sSS}', 'dphi_SV': 'd#phi_{sSV}', 'dphi_VS': 'd#phi_{sVS}', 'dphi_ST': 'd#phi_{sST}', 'dphi_TS': 'd#phi_{sTS}', 'dphi_VT': 'd#phi_{sVT}', 'dphi_TV': 'd#phi_{sTV}', 'dphi_TT': 'd#phi_{sTT}'}

def printwithsign(x,symmetric):
   if symmetric: return '{:.4f}'.format(x)
   else:
      if x>=0: return '+'+'{:.4f}'.format(x)
      else: return '-'+'{:.4f}'.format(-x)

def increasesyst(par,deviation,symmetric):
   sigma2 = deviation**2
   if symmetric:
      par_syst_up_quad[par] += sigma2
      par_syst_down_quad[par] += sigma2
   else:
      if deviation>=0: par_syst_up_quad[par] += sigma2
      else: par_syst_down_quad[par] += sigma2

for itable in range(len(par_name_lists)):
   print '\\begin{table}\n\\centering\n\\begin{tabular}{|c|ccccc|}'
   print '\\hline'
   par_names = par_name_lists[itable]
   line = 'Parameter'
   par_syst_up_quad = {}
   par_syst_down_quad = {}
   for par in par_names:
      line += ' & $' + par_name_dict[par].replace('#','\\') + '$'
      par_syst_up_quad[par] = 0.
      par_syst_down_quad[par] = 0.
   line += ' \\\\'
   print line
   print '\\hline'
   for isyst in range(len(syst_list)):
      line = syst_list[isyst][0]
      syst_dict = syst_list[isyst][1]
      symmeterised = syst_list[isyst][2]
      for par in par_names:
         line += ' & $' + printwithsign(syst_dict[par][0],symmeterised)+'$'
         increasesyst(par,syst_dict[par][0],symmeterised)
      line += ' \\\\'
      print line
   print '\\hline'
   line = ''
   for par in par_names:
      line += ' & $+' + '{:.4f}'.format(sqrt(par_syst_up_quad[par])) + '$'
   line += ' \\\\'
   print line
   line = 'Total'
   for par in par_names:
      line += ' & $-' + '{:.4f}'.format(sqrt(par_syst_down_quad[par])) + '$'
   line += ' \\\\'
   print line
   print '\\hline'
   print '\\end{tabular}\n\\caption{Summary of the systematic uncertainties of the fit parameters.}\n\\end{table}\n'
