#from scipy import stats
import numpy as np


delta = [-0.00903054535910330, 0.0440618969328708, -0.0102738376404037, -0.00755979314421928, 0.00105375000000000, 0.005288999999999999, 0.00117450000000000, 0.01586]
N = len(delta)
my_matrix  = np.ones(  (N,N) )

correlation = np.matrix(my_matrix)
for i in range(N):
    dx = delta[i]#case_A[i] - case_B[i]
    
    for j in range(N):
        dy = delta[j]#case_A[j] - case_B[j]
        slope = dx/dy
        correlation[i,j] = slope/abs(slope)
