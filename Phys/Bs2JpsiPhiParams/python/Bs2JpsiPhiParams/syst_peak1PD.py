#from scipy import stats
import numpy as np
delta = [0.000779531330403982, -0.000865447845721956, -0.00222787795162871, 0.000319679636504366, -0.00135137500000000, 0.0006235, 0.000266750000000000, 0.0008845]
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
