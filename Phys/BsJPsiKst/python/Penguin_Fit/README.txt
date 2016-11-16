Required python packages:
=========================
- Minuit
- Matplotlib
- Numpy

Overview:
=========
Inputs:
  Input.py: Base-file; Collects all experimental and theoretical inputs and defines some basic functions
  Branching_Ratio_Calculations.py: Helper-file; calculates the H observables

Fitting:
  aRe_aIm_fit.py: Main fitter: defines chi^2, minimises it and performs a scan over the Re[a]-Im[a] plane to determine the confidence level contours
  aRe_aIm_fit_allB2VV.py: Same as above, but including Bd->JpsiRho
  aRe_aIm_fit_withSU3.py: Include SU(3)-breaking as Gaussian constraints to the fit

Plotting: (requires CL contours from fit)
  Plot_a_theta_contours_Bs2JpsiKstar.py: Plots contour bands from the individual observables and overlays the CL from the fit
  Plot_a_theta_contours_B2VV.py: Same as above, but including Bd->JpsiRho
  Plot_SU3_Dependence.py: Plots DeltaPhis as a function of the SU(3)-breaking parameter xi

  Complex_Circle.py: Helper-file; contains all the details about the contour bands