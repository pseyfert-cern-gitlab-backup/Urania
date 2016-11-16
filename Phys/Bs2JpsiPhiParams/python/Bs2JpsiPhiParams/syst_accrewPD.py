#from scipy import stats
import numpy as np
delta = [0.000461724533185270, -0.00320379994309739, -0.00134907865412137, 0.0179294463631163, 0.000937931000000031, -0.0016850200000000093, 0.000350242000000001, 0.007233889999999993]
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
