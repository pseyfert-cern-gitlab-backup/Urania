from ROOT import *

from _wide_Pelaez_varnw import par_result_dict as dict0 # default
from _wide_ModInd_varnw import par_result_dict as dict1
from _wide_Lass_varnw import par_result_dict as dict2

def stringline_CUDA(par):
   deviation1 = dict1[par][0]-dict0[par][0]
   deviation2 = dict2[par][0]-dict0[par][0]
   sigma = abs(deviation1)
   return '$'+dict0[par][2]+'$ & $'+'{:.4f}'.format(deviation1)+'$ & $'+'{:.4f}'.format(deviation2)+'$ & $'+'{:.4f}'.format(sigma)+'$'

partext = '\\documentclass[11pt,a4paper]{article}\n\\usepackage[left=2.5cm,top=2.5cm,right=2.5cm,bottom=2.5cm]{geometry}\n\n\\begin{document}\n\n\\begin{table}[h]\n\\centering\n\\begin{tabular}{|cccc|cccc|}\n\hline\nParam. & $\\Delta$ & $\\Delta$ & $\sigma$ & Param. & $\\Delta$ & $\\Delta$ & $\sigma$ \\\\\n& (Mod. Ind.) & (LASS) & & & (Mod. Ind.) & (LASS) &\\\\\n\\hline\n'
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

texfile = open('syst_scalarmassamp.tex','w')
texfile.write(partext)
texfile.close()

syst_dict = {}
for par in ["phis","f_par_12","DCP","f_21","delta_m_Bs","f_L_21","f_11","f_par_21","f_L_11","delta_120","f_par_11","delta_12par","delta_11par","delta_12perp","delta_11perp","delta_210","f_01","delta_21par","f_10","delta_21perp","delta_01","f_22","delta_10","f_L_22","f_00","f_par_22","delta_00","f_perp_22","f_02","f_par2_22","f_20","delta_220","delta_02","delta_22par","delta_20","delta_22perp","f_12","delta_22par2","f_L_12","delta_22perp2"]:
   syst_dict[par] = [abs(dict1[par][0]-dict0[par][0]),dict0[par][2]]
systfile = open('_syst_scalarmassamp.py','w')
systfile.write('syst_dict = '+str(syst_dict))
systfile.close()
