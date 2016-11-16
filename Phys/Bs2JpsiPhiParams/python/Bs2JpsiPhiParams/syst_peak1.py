#from scipy import stats
import numpy as np
my_matrix  = np.ones(  (9,9) )
#case_A = []
#case_B = []
#names    = ['Gamma_s',	'DeltaGamma_s',	'Aperp_sq',	'Azero_sq',	'delta_para',	'delta_perp',	'phi_s',	'lambda',	'Deltam_s']
delta = [-0.047, -0.028 , 0.068 , -0.054 , -0.188, -0.126, -0.023, 0.147 , -0.027]
correlation = np.matrix(my_matrix)
for i in range(9):
    dx = delta[i]#case_A[i] - case_B[i]
    
    for j in range(9):
        dy = delta[j]#case_A[j] - case_B[j]
        slope = dx/dy
        correlation[i,j] = slope/abs(slope)
