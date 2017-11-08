from ROOT import *

from _syst_pulls import syst_dict

par_name_dict = {'reA22perp': 'Re(A^{TT}_{#perp1})', 'reA22par2': 'Re(A^{TT}_{#parallel2})', 'delta_210': '#delta^{TV}_{0}', 'tres_p1_2012': 'p_{1}^{#sigma_{t}}(2012)', 'tres_p1_2011': 'p_{1}^{#sigma_{t}}(2011)', 'delta_00': '#delta^{SS}', 'reA10': 'Re(A^{VS})', 'p0metac_OS': 'p_{0}^{OS}-<#eta^{OS}>', 'reA220': 'Re(A^{TT}_{L})', 'reA20': 'Re(A^{TS})', 'delta_10': '#delta^{VS}', 'imA21par': 'Im(A^{TV}_{#parallel})', 'reA11par': 'Re(A^{VV}_{#parallel})', 'delta_11par': '#delta^{VV}_{#parallel}', 'DCP': '#Delta^{CP}', 'imA22perp2': 'Im(A^{TT}_{#perp2})', 'delta_12par': '#delta^{VT}_{#parallel}', 'delta_01': '#delta^{SV}', 'imA22par': 'Im(A^{TT}_{#parallel1})', 'delta_02': '#delta^{ST}', 'reA22par': 'Re(A^{TT}_{#parallel1})', 'p1_SSK': 'p_{1}^{SSK}', 'delta_22perp': '#delta^{TT}_{#perp1}', 'reA21par': 'Re(A^{TV}_{#parallel})', 'delta_21par': '#delta^{TV}_{#parallel}', 'Dp1half_SSK': '1/2 #Delta p_{1}^{SSK}', 'delta_11perp': '#delta^{VV}_{#perp}', 'f_perp2_22': 'f_{#perp2}^{TT}', 'imA210': 'Im(A^{TV}_{L})', 'tres_p0_2011': 'p_{0}^{#sigma_{t}}(2011)', 'reA120': 'Re(A^{VT}_{L})', 'imA21perp': 'Im(A^{TV}_{#perp})', 'tres_p0_2012': 'p_{0}^{#sigma_{t}}(2012)', 'delta_22perp2': '#delta^{TT}_{#perp2}', 'reA22perp2': 'Re(A^{TT}_{#perp2})', 'imA10': 'Im(A^{VS})', 'delta_21perp': '#delta^{TV}_{#perp}', 'p1_OS': 'p_{1}^{OS}', 'delta_22par2': '#delta^{TT}_{#parallel2}', 'f_22': 'f_{TT}', 'f_21': 'f_{TV}', 'f_20': 'f_{TS}', 'f_L_22': 'f_L^{TT}', 'f_par_22': 'f_{#parallel1}^{TT}', 'f_par_21': 'f_{#parallel}^{TV}', 'f_L_21': 'f_L^{TV}', 'imA12perp': 'Im(A^{VT}_{#perp})', 'delta_12perp': '#delta^{VT}_{#perp}', 'imA220': 'Im(A^{TT}_{L})', 'delta_m_Bs': '#Delta m_{B_{s}^{0}}', 'reA12par': 'Re(A^{VT}_{#parallel})', 'f_par2_22': 'f_{#parallel2}^{TT}', 'Dp1half_OS': '1/2 #Delta p_{1}^{OS}', 'f_12': 'f_{VT}', 'f_10': 'f_{VS}', 'f_11': 'f_{VV}', 'imA02': 'Im(A^{ST})', 'imA00': 'Im(A^{SS})', 'imA01': 'Im(A^{SV})', 'f_par_12': 'f_{#parallel}^{VT}', 'f_par_11': 'f_{#parallel}^{VV}', 'reA01': 'Re(A^{SV})', 'Dp0half_OS': '1/2 #Delta p_{0}^{OS}', 'reA11perp': 'Re(A^{VV}_{#perp})', 'imA120': 'Im(A^{VT}_{L})', 'f_01': 'f_{SV}', 'f_00': 'f_{SS}', 'f_02': 'f_{ST}', 'gamma_Bs': '#Gamma_{B_{s}^{0}}', 'f_perp_22': 'f_{#perp1}^{TT}', 'f_perp_21': 'f_{#perp}^{TV}', 'p0metac_SSK': 'p_{0}^{SSK}-<#eta^{SSK}>', 'imA22perp': 'Im(A^{TT}_{#perp1})', 'delta_22par': '#delta^{TT}_{#parallel1}', 'imA22par2': 'Im(A^{TT}_{#parallel2})', 'reA210': 'Re(A^{TV}_{L})', 'imA20': 'Im(A^{TS})', 'imA11perp': 'Im(A^{VV}_{#perp})', 'f_L_12': 'f_L^{VT}', 'f_L_11': 'f_L^{VV}', 'f_perp_12': 'f_{#perp}^{VT}', 'f_perp_11': 'f_{#perp}^{VV}', 'delta_120': '#delta^{VT}_{0}', 'delta_220': '#delta^{TT}_{0}', 'reA21perp': 'Re(A^{TV}_{#perp})', 'imA11par': 'Im(A^{VV}_{#parallel})', 'reA12perp': 'Re(A^{VT}_{#perp})', 'Dp0half_SSK': '1/2 #Delta p_{0}^{SSK}', 'reA00': 'Re(A^{SS})', 'reA02': 'Re(A^{ST})', 'delta_gamma_Bs': '#Delta #Gamma_{B_{s}^{0}}', 'delta_20': '#delta^{TS}', 'imA12par': 'Im(A^{VT}_{#parallel})', 'phis': '#phi_{s}'}

def stringline_CUDA(par):
   bias = syst_dict[par][0]
   bias_sigma = syst_dict[par][1]
   return '$'+par_name_dict[par]+'$ & $'+'{:.4f}'.format(bias)+'$ & $'+'{:.4f}'.format(bias_sigma)+'$'

partext = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\n\\begin{document}\n\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|ccc|ccc|}\n\hline\nParameter & Bias & $\\sigma$ & Parameter & Bias & $\\sigma$ \\\\\n\\hline\n'
partext += stringline_CUDA("phis") + ' & ' + stringline_CUDA("f_par_12") + ' \\\\\n'
partext += stringline_CUDA("DCP") + ' & ' + stringline_CUDA("f_21") + ' \\\\\n'
partext += stringline_CUDA("delta_m_Bs") + ' & ' + stringline_CUDA("f_L_21") + ' \\\\\n'
partext += stringline_CUDA("f_11") + ' & ' + stringline_CUDA("f_par_21") + ' \\\\\n'
partext += stringline_CUDA("f_L_11") + ' & ' + stringline_CUDA("delta_120") + ' \\\\\n'
partext += stringline_CUDA("f_par_11") + ' & ' + stringline_CUDA("delta_12par") + ' \\\\\n'
partext += stringline_CUDA("delta_11par") + ' & ' + stringline_CUDA("delta_12perp") + ' \\\\\n'
partext += stringline_CUDA("delta_11perp") + ' & ' + stringline_CUDA("delta_210") + ' \\\\\n'
partext += stringline_CUDA("f_01") + ' & ' + stringline_CUDA("delta_21par") + ' \\\\\n'
partext += stringline_CUDA("f_10") + ' & ' + stringline_CUDA("delta_21perp") + ' \\\\\n'
partext += stringline_CUDA("delta_01") + ' & ' + stringline_CUDA("f_22") + ' \\\\\n'
partext += stringline_CUDA("delta_10") + ' & ' + stringline_CUDA("f_L_22") + ' \\\\\n'
partext += stringline_CUDA("f_00") + ' & ' + stringline_CUDA("f_par_22") + ' \\\\\n'
partext += stringline_CUDA("delta_00") + ' & ' + stringline_CUDA("f_perp_22") + ' \\\\\n'
partext += stringline_CUDA("f_02") + ' & ' + stringline_CUDA("f_par2_22") + ' \\\\\n'
partext += stringline_CUDA("f_20") + ' & ' + stringline_CUDA("delta_220") + ' \\\\\n'
partext += stringline_CUDA("delta_02") + ' & ' + stringline_CUDA("delta_22par") + ' \\\\\n'
partext += stringline_CUDA("delta_20") + ' & ' + stringline_CUDA("delta_22perp") + ' \\\\\n'
partext += stringline_CUDA("f_12") + ' & ' + stringline_CUDA("delta_22par2") + ' \\\\\n'
partext += stringline_CUDA("f_L_12") + ' & ' + stringline_CUDA("delta_22perp2") + ' \\\\\n'
partext += '\\hline\n'
partext += '\\end{tabular}\n\\end{table}\n\n'
partext += '\\end{document}'
partext = partext.replace('#','\\')

texfile = open('syst_pulls.tex','w')
texfile.write(partext)
texfile.close()
