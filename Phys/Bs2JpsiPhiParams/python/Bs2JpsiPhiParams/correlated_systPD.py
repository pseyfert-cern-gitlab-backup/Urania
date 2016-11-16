from scipy import stats
import numpy as np
import syst_massPD, syst_accrewPD, syst_peak1PD, syst_peak2PD, syst_CSP1PD, syst_CSP2PD
names    = ['|\lambda^{0}|',	'|\lambda^{\parallel}/\lambda^0|',	'|\lambda^{\perp}/\lambda^0|',	'|\lambda^{\rmS}/\lambda^0|',	'\phi^{0}_s',	'\phi_s^{\parallel}-\phi_s^{0}',	'\phi_s^{\perp}-\phi_s^0',	'\phi_s^{\rmS}-\phi_s^0']
N = len(names)
stat_errors = [ .058, .12, .16, .12, .053, .043,.035, .086] ### Tab 38 ANA note

# This statistical correlation matrix is in the wrong order relative to the above names
# Therefore we need to convert
stat_rows = []
stat_rows.append([+1.00  ,-0.14  ,+0.13  ,+0.14  ,+0.01  ,+0.00  ,-0.02  ,-0.01])
stat_rows.append([+0.00  ,+1.00  ,+0.52  ,+0.11  ,-0.08  ,+0.31  ,+0.06  ,+0.07])
stat_rows.append([+0.00  ,+0.00  ,+1.00  ,+0.08  ,-0.06  ,+0.16  ,-0.29  ,+0.06])
stat_rows.append([+0.00  ,+0.00  ,+0.00  ,+1.00  ,+0.00  ,+0.10  ,-0.02  ,+0.22])
stat_rows.append([+0.00  ,+0.00  ,+0.00  ,+0.00  ,+1.00  ,-0.32  ,-0.59  ,-0.89])
stat_rows.append([+0.00  ,+0.00  ,+0.00  ,+0.00  ,+0.00  ,+1.00  ,-0.23  ,+0.27])
stat_rows.append([+0.00  ,+0.00  ,+0.00  ,+0.00  ,+0.00  ,+0.00  ,+1.00  ,+0.53])
stat_rows.append([+0.00  ,+0.00  ,+0.00  ,+0.00  ,+0.00  ,+0.00  ,+0.00  ,+1.00])
stat_corr = np.matrix( stat_rows )
for i in range(8):
	for j in range(8):
		if j < i:
			stat_corr[i,j] = stat_corr[j,i]

transform_rows = []
transform_rows.append([0, 0, 0, 0, 1, 0, 0, 0])
transform_rows.append([0, 0, 0, 0, 0, 1, 0, 0])
transform_rows.append([0, 0, 0, 0, 0, 0, 1, 0])
transform_rows.append([0, 0, 0, 0, 0, 0, 0, 1])
transform_rows.append([1, 0, 0, 0, 0, 0, 0, 0])
transform_rows.append([0, 1, 0, 0, 0, 0, 0, 0])
transform_rows.append([0, 0, 1, 0, 0, 0, 0, 0])
transform_rows.append([0, 0, 0, 1, 0, 0, 0, 0])
transform = np.matrix( transform_rows )

stat_correlation = (transform.T)*stat_corr*transform 
stat_covariance = np.matrix( np.zeros( (8,8) ) )

for i in range(8):
	for j in range(8):
		if j > i:
			stat_covariance[i,j] = stat_correlation[i,j]*stat_errors[i]*stat_errors[j]
		else:
			stat_covariance[i,j] = stat_correlation[j,i]*stat_errors[i]*stat_errors[j]

def convert_to_abs(fractional_errors):
	out = []
	for i in range(len(names)): out.append(fractional_errors[i]*stat_errors[i])
	return out

ferr1 = []
ferr2 = [ 0.5*(0.012+0.015), 0.0045, 0.0075, 0.0035, 0.5*(0.017+0.014), 0.011, 0.021, 0.0095, 0.006]

def print_correlation( covariance, total_err ):
        for i in range(N):
                for j in range(N):
                        rho = covariance[i,j]/(total_err[i]*total_err[j])
                        print "%+0.2f" % rho,
                print

def print_covariance( covariance ):
        for i in range(N):
                for j in range(N):
                        print "%+0.4g" % covariance[i,j],
                print

def print_correlation_latex( covariance, total_err, names ):
        for n in names: print "$%s$ & " % n,
        print
        for i in range(N):
                print "$%s$ & " % names[i],
                for j in range(N):
                        rho = covariance[i,j]/(total_err[i]*total_err[j])
                        if j >= i:
                                if abs(rho) > 0.3:
                                        print "$\\bf{%+0.2f}$ &" % rho,
                                else:
                                        print "$%+0.2f$ &" % rho,
                        else:
                                print " & ",
                print "\\\\"

#BREAK

# Here is the table of systematic uncertainties
errs = [i for i in range(16)]
names    = ['|\lambda^{0}|',	'|\lambda^{\parallel}/\lambda^0|',	'|\lambda^{\perp}/\lambda^0|',	'|\lambda^{\rmS}/\lambda^0|',	'\phi^{0}_s',	'\phi_s^{\parallel}-\phi_s^{0}',	'\phi_s^{\perp}-\phi_s^0',	'\phi_s^{\rmS}-\phi_s^0']
errs[0]  = [ 0.01,      0.043,    0.011,        0.030,    0.0033 	 ,0.0052 	,0.0028	         ,0.016]#MassFactorisation
errs[1]  = [0.0030, 0.0068, 0.00072, 0.00070, 0.00025, 0.00014, 0.00022, 0.0064]#SignalWeights
errs[2]  = map(abs, syst_peak1PD.delta)#ResonantBackground_1
errs[14] = map(abs, syst_peak2PD.delta)#ResonantBackground_2
errs[3]  = len(names)*[0.]#BcBackground
errs[4]  = len(names)*[0.]#AngularResolution 
errs[5]  = [ 0.00094,    0.0031,  0.00095,      0.019,    0.00077,       0.0017,          0.0014,         0.0073]#AngEfficiencyReweighting
errs[6]  = [ 0.0038,     0.015, 0.0054, 0.011, 0.0036, 0.0070, 0.0053, 0.0037    ]#AngEfficiencyStat
errs[7]  = [ 0.0064,     0.0062, 0.0048, 0.011,0.0026, 0.0018, 0.0010, 0.0015]#DecayTimeResolution
errs[8]  = len(names)*[0.] #TriggerEfficiencyStat 	
errs[9]  = len(names)*[0.] #TrackReconstructionSimul
errs[10] = len(names)*[0.] #TrackReconstructionStat
errs[11] = len(names)*[0.] #LengthScale
errs[12] =  map(abs, syst_CSP1PD.delta) #CSP1
errs[13] = len(names)*[0.]#FitBias
errs[15] =  map(abs, syst_CSP2PD.delta) #CSP1

# Define some matrices that we need later
identity = np.identity( N )
one  = np.ones(  (N,N) )
zero = np.zeros( (N,N) )
minusone  = zero - one
for i in range(N):
	minusone[i,i] = 1.

# Now define the correlations between the parameters for each systematic
correlations = [i for i in range(len(errs))] 
# We state that correlations for comparing two sets of fits are 100% correlated
correlations[0]  = syst_massPD.correlation#np.matrix(one)#MassFactorisation 

#correlations[2]  = np.matrix(one)#ResonantBackground ## This is more complicated, 2 sources are evaluated
correlations[14]  = syst_peak1PD.correlation#ResonantBackground_1
correlations[2]  = syst_peak2PD.correlation#ResonantBackground_2
correlations[5]  = syst_accrewPD.correlation#AngEfficiencyReweighting 
#correlations[12] = np.matrix(one)#SPCouplingFactors ## This is more complicated, 2 sources are evaluated(same problem as in peaking bkg
correlations[12] = syst_CSP1PD.correlation#CSP_1
correlations[15] = syst_CSP2PD.correlation#CSP_2


# Correlations that are already in the statistical

# Correlations that are ignored, so just use identity
correlations[1]  = np.matrix(identity)#SignalWeights 
correlations[3]  = np.matrix(identity)#BcBackground
correlations[4]  = np.matrix(identity)#AngularResolution
correlations[6]  = np.matrix(identity)#AngEfficiencyStat
correlations[7]  = np.matrix(identity)#DecayTimeResolution
correlations[8]  = np.matrix(identity)#TriggerEfficiencyStat
correlations[9]  = np.matrix(identity)#TrackReconstructionSimul 
correlations[10] = np.matrix(identity)#TrackReconstructionStat
correlations[11] = np.matrix(identity)#LengthScale 
correlations[13] = np.matrix(identity)#FitBias

# For each systematic, compute the covariance and add it to the total
covariance = np.matrix( zero )
for k in range(len(correlations)):
	for i in range(N):
		for j in range(N):
			covariance[i,j] += errs[k][i]*errs[k][j]*correlations[k][i,j]

print "Here is the systematic covariance matrix"
print covariance

# Sanity check to print out the quadrature sum of systematics for each parameter
from math import sqrt
total_syst = []
for i in range(N):
	total_syst.append(sqrt(covariance[i,i]))
print
print "Here are the total systematics, summed in quadrature (should match the second-last line of Table 37)"
print total_syst
print
print "Here is the corresponding systematic correlation matrix"
print_correlation( covariance, total_syst )
print_correlation_latex( covariance, total_syst, names )

# Now add the systematic and statistical correlation matrices
print "Here is the statistical correlation"
print_correlation( stat_covariance, stat_errors )
print_correlation_latex( stat_covariance, stat_errors, names )
tot_cov = covariance + stat_covariance
print "Here is the sum of systematic and statistical covariance matrices"
print tot_cov
print
print_covariance(tot_cov)

# Sanity check to print out the quadrature sum of statistical + systematics for each parameter
total_err = []
for i in range(8):
	total_err.append(sqrt(tot_cov[i,i]))
print "Here are the total uncertainties, summed in quadrature (should match the last line of Table 37)"
print total_err
print
print "Here is the total statistical + systematic correlation matrix"
print_correlation( tot_cov, total_err )
print_correlation_latex( tot_cov, total_err, names )

