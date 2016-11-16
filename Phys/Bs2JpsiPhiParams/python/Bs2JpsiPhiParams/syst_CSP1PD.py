#from scipy import stats
import numpy as np
delta = [-0.000941493974776719, 0.000246289044014247, 0.00277265690985651, 0.00218530732354716, -6.72500000000048e-5, -4.2999999999999995e-05, -0.000381500000000000, 0.005917]
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
