import ROOT

mu_tres_p0_2011_wide = ROOT.RooConstVar("mu_tres_p0_2011_wide","mu_tres_p0_2011_wide",0.0348103179641)
mu_tres_p1_2011_wide = ROOT.RooConstVar("mu_tres_p1_2011_wide","mu_tres_p1_2011_wide",1.15751565448)
muvector_tres_p0_tres_p1_2011_wide = ROOT.RooArgList(mu_tres_p0_2011_wide,mu_tres_p1_2011_wide)
cov_tres_p0_tres_p1_2011_wide = ROOT.TMatrixDSym(2)
cov_tres_p0_tres_p1_2011_wide[0][0] = 6.61286236704e-08
cov_tres_p0_tres_p1_2011_wide[0][1] = 4.86030881198e-06
cov_tres_p0_tres_p1_2011_wide[1][0] = 4.86030881198e-06
cov_tres_p0_tres_p1_2011_wide[1][1] = 0.00264377717167
mu_tres_p0_2012_wide = ROOT.RooConstVar("mu_tres_p0_2012_wide","mu_tres_p0_2012_wide",0.0366133620443)
mu_tres_p1_2012_wide = ROOT.RooConstVar("mu_tres_p1_2012_wide","mu_tres_p1_2012_wide",1.26694253268)
muvector_tres_p0_tres_p1_2012_wide = ROOT.RooArgList(mu_tres_p0_2012_wide,mu_tres_p1_2012_wide)
cov_tres_p0_tres_p1_2012_wide = ROOT.TMatrixDSym(2)
cov_tres_p0_tres_p1_2012_wide[0][0] = 7.63043551548e-08
cov_tres_p0_tres_p1_2012_wide[0][1] = 6.12341419148e-06
cov_tres_p0_tres_p1_2012_wide[1][0] = 6.12341419148e-06
cov_tres_p0_tres_p1_2012_wide[1][1] = 0.00333600930576
mu_tres_p0_2011_narrow = ROOT.RooConstVar("mu_tres_p0_2011_narrow","mu_tres_p0_2011_narrow",0.0351250190673)
mu_tres_p1_2011_narrow = ROOT.RooConstVar("mu_tres_p1_2011_narrow","mu_tres_p1_2011_narrow",1.16999860101)
muvector_tres_p0_tres_p1_2011_narrow = ROOT.RooArgList(mu_tres_p0_2011_narrow,mu_tres_p1_2011_narrow)
cov_tres_p0_tres_p1_2011_narrow = ROOT.TMatrixDSym(2)
cov_tres_p0_tres_p1_2011_narrow[0][0] = 1.28832684544e-07
cov_tres_p0_tres_p1_2011_narrow[0][1] = 8.72930308506e-06
cov_tres_p0_tres_p1_2011_narrow[1][0] = 8.72930308506e-06
cov_tres_p0_tres_p1_2011_narrow[1][1] = 0.00416406362959
mu_tres_p0_2012_narrow = ROOT.RooConstVar("mu_tres_p0_2012_narrow","mu_tres_p0_2012_narrow",0.0368417277473)
mu_tres_p1_2012_narrow = ROOT.RooConstVar("mu_tres_p1_2012_narrow","mu_tres_p1_2012_narrow",1.22442275034)
muvector_tres_p0_tres_p1_2012_narrow = ROOT.RooArgList(mu_tres_p0_2012_narrow,mu_tres_p1_2012_narrow)
cov_tres_p0_tres_p1_2012_narrow = ROOT.TMatrixDSym(2)
cov_tres_p0_tres_p1_2012_narrow[0][0] = 1.0029571496e-07
cov_tres_p0_tres_p1_2012_narrow[0][1] = 7.91692629562e-06
cov_tres_p0_tres_p1_2012_narrow[1][0] = 7.91692629562e-06
cov_tres_p0_tres_p1_2012_narrow[1][1] = 0.0040802490262
