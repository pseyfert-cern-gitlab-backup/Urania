#from scipy import stats
import numpy as np
delta = [0.00322929584847786, 0.00360512599882656, 0.000463540286915198, -0.00792010411686717, 1.14999999999976e-5, 0.000602, -8.90000000000005e-5, 0.002379]

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
