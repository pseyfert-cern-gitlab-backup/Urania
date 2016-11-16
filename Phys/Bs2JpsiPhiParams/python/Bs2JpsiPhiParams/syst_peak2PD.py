#from scipy import stats
import numpy as np
delta = [-0.00383512581021295, 0.00770241687445417, 0.00323355185080065, 0.0124460381266825, -0.00339800000000000, 0.00086, -0.000529999999999999, -0.008296]
N = len(delta)
my_matrix  = np.ones(  (N,N) )
#case_A = []
#case_B = []
#names    = ['Gamma_s',	'DeltaGamma_s',	'Aperp_sq',	'Azero_sq',	'delta_para',	'delta_perp',	'phi_s',	'lambda',	'Deltam_s']

correlation = np.matrix(my_matrix)
for i in range(N):
    dx = delta[i]#case_A[i] - case_B[i]
    
    for j in range(N):
        dy = delta[j]#case_A[j] - case_B[j]
        slope = dx/dy
        correlation[i,j] = slope/abs(slope)
