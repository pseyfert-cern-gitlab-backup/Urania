from parameters import *
gROOT.ProcessLine('.x ../../src/TimeDependent/lhcbStyle.C')


# ################################################################
# V A R I A B L E S
# ################################################################

m1_name_MC = "B_s0_DTF_KST1_M"
m2_name_MC = "B_s0_DTF_KST2_M"
t_name_res = "B_s0_DTF_TAU"
ttrue_name_res = "B_s0_TRUETAU"
terr_name_res = "B_s0_DTF_TAUERR"

# Observables.
difft = ROOT.RooRealVar("difft","t_{rec}-t_{gen} (ps)",-0.2,0.2)
deltat = ROOT.RooRealVar("deltat","t_{err} (ps)",0.,0.08)

# Data.
data_difft_2011_wide = ROOT.RooDataSet("data_difft_2011_wide","data_difft_2011_wide",ROOT.RooArgSet(difft))
data_difft_2012_wide = ROOT.RooDataSet("data_difft_2012_wide","data_difft_2012_wide",ROOT.RooArgSet(difft))
data_difft_2011_narrow = ROOT.RooDataSet("data_difft_2011_narrow","data_difft_2011_narrow",ROOT.RooArgSet(difft))
data_difft_2012_narrow = ROOT.RooDataSet("data_difft_2012_narrow","data_difft_2012_narrow",ROOT.RooArgSet(difft))
data_2011_wide = ROOT.RooDataSet("data_2011_wide","data_2011_wide",ROOT.RooArgSet(difft,deltat))
data_2012_wide = ROOT.RooDataSet("data_2012_wide","data_2012_wide",ROOT.RooArgSet(difft,deltat))
data_2011_narrow = ROOT.RooDataSet("data_2011_narrow","data_2011_narrow",ROOT.RooArgSet(difft,deltat))
data_2012_narrow = ROOT.RooDataSet("data_2012_narrow","data_2012_narrow",ROOT.RooArgSet(difft,deltat))
data_difft_sim_2011_list = []
data_difft_sim_2012_list = []

# 1D time resolution parametrization.
sigma1_eff_2011_wide = ROOT.RooRealVar("sigma1_eff_2011_wide","sigma1_eff_2011_wide",0.03,0.01,0.06)
sigma2_eff_2011_wide = ROOT.RooRealVar("sigma2_eff_2011_wide","sigma2_eff_2011_wide",0.06,0.04,0.2)
f1_eff_2011_wide = ROOT.RooRealVar("f1_eff_2011_wide","f1_eff_2011_wide",0.6,0.5,1.)
sigma1_eff_2012_wide = ROOT.RooRealVar("sigma1_eff_2012_wide","sigma1_eff_2012_wide",0.03,0.01,0.06)
sigma2_eff_2012_wide = ROOT.RooRealVar("sigma2_eff_2012_wide","sigma2_eff_2012_wide",0.06,0.04,0.2)
f1_eff_2012_wide = ROOT.RooRealVar("f1_eff_2012_wide","f1_eff_2012_wide",0.6,0.5,1.)
sigma_eff_2011_wide = ROOT.RooFormulaVar("sigma_eff_2011_wide","sigma_eff_2011_wide","sqrt(-2.*log(@0*exp(-17.69*17.69*@1*@1/2.)+(1.-@0)*exp(-17.69*17.69*@2*@2/2.)))/17.69",ROOT.RooArgList(f1_eff_2011_wide,sigma1_eff_2011_wide,sigma2_eff_2011_wide))
sigma_eff_2012_wide = ROOT.RooFormulaVar("sigma_eff_2012_wide","sigma_eff_2012_wide","sqrt(-2.*log(@0*exp(-17.69*17.69*@1*@1/2.)+(1.-@0)*exp(-17.69*17.69*@2*@2/2.)))/17.69",ROOT.RooArgList(f1_eff_2012_wide,sigma1_eff_2012_wide,sigma2_eff_2012_wide))
sigma1_eff_2011_narrow = ROOT.RooRealVar("sigma1_eff_2011_narrow","sigma1_eff_2011_narrow",0.03,0.01,0.06)
sigma2_eff_2011_narrow = ROOT.RooRealVar("sigma2_eff_2011_narrow","sigma2_eff_2011_narrow",0.06,0.04,0.2)
f1_eff_2011_narrow = ROOT.RooRealVar("f1_eff_2011_narrow","f1_eff_2011_narrow",0.6,0.5,1.)
sigma1_eff_2012_narrow = ROOT.RooRealVar("sigma1_eff_2012_narrow","sigma1_eff_2012_narrow",0.03,0.01,0.06)
sigma2_eff_2012_narrow = ROOT.RooRealVar("sigma2_eff_2012_narrow","sigma2_eff_2012_narrow",0.06,0.04,0.2)
f1_eff_2012_narrow = ROOT.RooRealVar("f1_eff_2012_narrow","f1_eff_2012_narrow",0.6,0.5,1.)
sigma_eff_2011_narrow = ROOT.RooFormulaVar("sigma_eff_2011_narrow","sigma_eff_2011_narrow","sqrt(-2.*log(@0*exp(-17.69*17.69*@1*@1/2.)+(1.-@0)*exp(-17.69*17.69*@2*@2/2.)))/17.69",ROOT.RooArgList(f1_eff_2011_narrow,sigma1_eff_2011_narrow,sigma2_eff_2011_narrow))
sigma_eff_2012_narrow = ROOT.RooFormulaVar("sigma_eff_2012_narrow","sigma_eff_2012_narrow","sqrt(-2.*log(@0*exp(-17.69*17.69*@1*@1/2.)+(1.-@0)*exp(-17.69*17.69*@2*@2/2.)))/17.69",ROOT.RooArgList(f1_eff_2012_narrow,sigma1_eff_2012_narrow,sigma2_eff_2012_narrow))

# Simultaneous fit resolution parametrization.
sigma1_sim_2011_list = []
sigma2_sim_2011_list = []
sigma1_sim_2012_list = []
sigma2_sim_2012_list = []

# 2D time resolution parametrization.
q0A_2011_wide = ROOT.RooRealVar("q0A_2011_wide","q0A_2011_wide",0.,0.,0.01)
q1A_2011_wide = ROOT.RooRealVar("q1A_2011_wide","q1A_2011_wide",1.,0.4,1.6)
q2A_2011_wide = ROOT.RooRealVar("q2A_2011_wide","q2A_2011_wide",-25.,-32.,0.)
q0B_2011_wide = ROOT.RooRealVar("q0B_2011_wide","q0B_2011_wide",0.,0.,0.01)
q1B_2011_wide = ROOT.RooRealVar("q1B_2011_wide","q1B_2011_wide",0.,0.,0.5)
q2B_2011_wide = ROOT.RooRealVar("q2B_2011_wide","q2B_2011_wide",-11.,-20.,-6.)
q0A_2012_wide = ROOT.RooRealVar("q0A_2012_wide","q0A_2012_wide",0.,0.,0.01)
q1A_2012_wide = ROOT.RooRealVar("q1A_2012_wide","q1A_2012_wide",1.,0.4,1.6)
q2A_2012_wide = ROOT.RooRealVar("q2A_2012_wide","q2A_2012_wide",-25.,-32.,0.)
q0B_2012_wide = ROOT.RooRealVar("q0B_2012_wide","q0B_2012_wide",0.,0.,0.01)
q1B_2012_wide = ROOT.RooRealVar("q1B_2012_wide","q1B_2012_wide",0.,0.,0.5)
q2B_2012_wide = ROOT.RooRealVar("q2B_2012_wide","q2B_2012_wide",-11.,-20.,-6.)
deltat_mean_2011_wide = ROOT.RooRealVar("deltat_mean_2011_wide","deltat_mean_2011_wide",0.,0.08)
deltat_mean_2012_wide = ROOT.RooRealVar("deltat_mean_2012_wide","deltat_mean_2012_wide",0.,0.08)
off_2011_wide = ROOT.RooRealVar("off_2011_wide","off_2011_wide",0.,-0.1,0.1)
off_2012_wide = ROOT.RooRealVar("off_2012_wide","off_2012_wide",0.,-0.1,0.1)
f1_2011_wide = ROOT.RooRealVar("f1_2011_wide","f1_2011_wide",0.69,0.5,0.9)
f1_2012_wide = ROOT.RooRealVar("f1_2012_wide","f1_2012_wide",0.69,0.5,0.9)
sigmaA_2011_wide = ROOT.RooFormulaVar("sigmaA_2011_wide","sigmaA_2011_wide","@0+(@1+@2*(@3-@4))*@3",ROOT.RooArgList(q0A_2011_wide,q1A_2011_wide,q2A_2011_wide,deltat,deltat_mean_2011_wide))
sigmaB_2011_wide = ROOT.RooFormulaVar("sigmaB_2011_wide","sigmaB_2011_wide","@0+(@1+@2*(@3-@4))*@3",ROOT.RooArgList(q0B_2011_wide,q1B_2011_wide,q2B_2011_wide,deltat,deltat_mean_2011_wide))
sigmaA_2012_wide = ROOT.RooFormulaVar("sigmaA_2012_wide","sigmaA_2012_wide","@0+(@1+@2*(@3-@4))*@3",ROOT.RooArgList(q0A_2012_wide,q1A_2012_wide,q2A_2012_wide,deltat,deltat_mean_2012_wide))
sigmaB_2012_wide = ROOT.RooFormulaVar("sigmaB_2012_wide","sigmaB_2012_wide","@0+(@1+@2*(@3-@4))*@3",ROOT.RooArgList(q0B_2012_wide,q1B_2012_wide,q2B_2012_wide,deltat,deltat_mean_2012_wide))
sigma1_2011_wide = ROOT.RooFormulaVar("sigma1_2011_wide","sigma1_2011_wide","@0-sqrt(@1/(1.-@1))*@2",ROOT.RooArgList(sigmaA_2011_wide,f1_2011_wide,sigmaB_2011_wide))
sigma2_2011_wide = ROOT.RooFormulaVar("sigma2_2011_wide","sigma2_2011_wide","@0+sqrt((1.-@1)/@1)*@2",ROOT.RooArgList(sigmaA_2011_wide,f1_2011_wide,sigmaB_2011_wide))
sigma1_2012_wide = ROOT.RooFormulaVar("sigma1_2012_wide","sigma1_2012_wide","@0-sqrt(@1/(1.-@1))*@2",ROOT.RooArgList(sigmaA_2012_wide,f1_2012_wide,sigmaB_2012_wide))
sigma2_2012_wide = ROOT.RooFormulaVar("sigma2_2012_wide","sigma2_2012_wide","@0+sqrt((1.-@1)/@1)*@2",ROOT.RooArgList(sigmaA_2012_wide,f1_2012_wide,sigmaB_2012_wide))
q0A_2011_narrow = ROOT.RooRealVar("q0A_2011_narrow","q0A_2011_narrow",0.,0.,0.01)
q1A_2011_narrow = ROOT.RooRealVar("q1A_2011_narrow","q1A_2011_narrow",1.,0.8,1.2)
q2A_2011_narrow = ROOT.RooRealVar("q2A_2011_narrow","q2A_2011_narrow",-25.,-32.,0.)
q0B_2011_narrow = ROOT.RooRealVar("q0B_2011_narrow","q0B_2011_narrow",0.,0.,0.01)
q1B_2011_narrow = ROOT.RooRealVar("q1B_2011_narrow","q1B_2011_narrow",0.,0.,0.5)
q2B_2011_narrow = ROOT.RooRealVar("q2B_2011_narrow","q2B_2011_narrow",-11.,-20.,-6.)
q0A_2012_narrow = ROOT.RooRealVar("q0A_2012_narrow","q0A_2012_narrow",0.,0.,0.01)
q1A_2012_narrow = ROOT.RooRealVar("q1A_2012_narrow","q1A_2012_narrow",1.,0.8,1.2)
q2A_2012_narrow = ROOT.RooRealVar("q2A_2012_narrow","q2A_2012_narrow",-25.,-32.,0.)
q0B_2012_narrow = ROOT.RooRealVar("q0B_2012_narrow","q0B_2012_narrow",0.,0.,0.01)
q1B_2012_narrow = ROOT.RooRealVar("q1B_2012_narrow","q1B_2012_narrow",0.,0.,0.5)
q2B_2012_narrow = ROOT.RooRealVar("q2B_2012_narrow","q2B_2012_narrow",-11.,-20.,-6.)
deltat_mean_2011_narrow = ROOT.RooRealVar("deltat_mean_2011_narrow","deltat_mean_2011_narrow",0.,0.08)
deltat_mean_2012_narrow = ROOT.RooRealVar("deltat_mean_2012_narrow","deltat_mean_2012_narrow",0.,0.08)
off_2011_narrow = ROOT.RooRealVar("off_2011_narrow","off_2011_narrow",0.,-0.1,0.1)
off_2012_narrow = ROOT.RooRealVar("off_2012_narrow","off_2012_narrow",0.,-0.1,0.1)
f1_2011_narrow = ROOT.RooRealVar("f1_2011_narrow","f1_2011_narrow",0.69,0.,1.)
f1_2012_narrow = ROOT.RooRealVar("f1_2012_narrow","f1_2012_narrow",0.69,0.,1.)
sigmaA_2011_narrow = ROOT.RooFormulaVar("sigmaA_2011_narrow","sigmaA_2011_narrow","@0+(@1+@2*(@3-@4))*@3",ROOT.RooArgList(q0A_2011_narrow,q1A_2011_narrow,q2A_2011_narrow,deltat,deltat_mean_2011_narrow))
sigmaB_2011_narrow = ROOT.RooFormulaVar("sigmaB_2011_narrow","sigmaB_2011_narrow","@0+(@1+@2*(@3-@4))*@3",ROOT.RooArgList(q0B_2011_narrow,q1B_2011_narrow,q2B_2011_narrow,deltat,deltat_mean_2011_narrow))
sigmaA_2012_narrow = ROOT.RooFormulaVar("sigmaA_2012_narrow","sigmaA_2012_narrow","@0+(@1+@2*(@3-@4))*@3",ROOT.RooArgList(q0A_2012_narrow,q1A_2012_narrow,q2A_2012_narrow,deltat,deltat_mean_2012_narrow))
sigmaB_2012_narrow = ROOT.RooFormulaVar("sigmaB_2012_narrow","sigmaB_2012_narrow","@0+(@1+@2*(@3-@4))*@3",ROOT.RooArgList(q0B_2012_narrow,q1B_2012_narrow,q2B_2012_narrow,deltat,deltat_mean_2012_narrow))
sigma1_2011_narrow = ROOT.RooFormulaVar("sigma1_2011_narrow","sigma1_2011_narrow","@0-sqrt(@1/(1.-@1))*@2",ROOT.RooArgList(sigmaA_2011_narrow,f1_2011_narrow,sigmaB_2011_narrow))
sigma2_2011_narrow = ROOT.RooFormulaVar("sigma2_2011_narrow","sigma2_2011_narrow","@0+sqrt((1.-@1)/@1)*@2",ROOT.RooArgList(sigmaA_2011_narrow,f1_2011_narrow,sigmaB_2011_narrow))
sigma1_2012_narrow = ROOT.RooFormulaVar("sigma1_2012_narrow","sigma1_2012_narrow","@0-sqrt(@1/(1.-@1))*@2",ROOT.RooArgList(sigmaA_2012_narrow,f1_2012_narrow,sigmaB_2012_narrow))
sigma2_2012_narrow = ROOT.RooFormulaVar("sigma2_2012_narrow","sigma2_2012_narrow","@0+sqrt((1.-@1)/@1)*@2",ROOT.RooArgList(sigmaA_2012_narrow,f1_2012_narrow,sigmaB_2012_narrow))

# Marginal PDF parametrization.
gamma_2011_wide_A = ROOT.RooRealVar("gamma_2011_wide_A","gamma_2011_wide_A",1.40444e+01,10.,20.)
beta_2011_wide_A = ROOT.RooRealVar("beta_2011_wide_A","beta_2011_wide_A",2.20383e-03,0.001,0.01)
gamma_2011_wide_B = ROOT.RooRealVar("gamma_2011_wide_B","gamma_2011_wide_B",2.90042e+00,1.,10.)
beta_2011_wide_B = ROOT.RooRealVar("beta_2011_wide_B","beta_2011_wide_B",1.14178e-02,0.0005,0.02)
gamma_2012_wide_A = ROOT.RooRealVar("gamma_2012_wide_A","gamma_2012_wide_A",1.43411e+01,10.,20.)
beta_2012_wide_A = ROOT.RooRealVar("beta_2012_wide_A","beta_2012_wide_A",2.17901e-03,0.0005,0.01)
gamma_2012_wide_B = ROOT.RooRealVar("gamma_2012_wide_B","gamma_2012_wide_B",3.32812e+00,1.,10.)
beta_2012_wide_B = ROOT.RooRealVar("beta_2012_wide_B","beta_2012_wide_B",9.99999e-03,0.0005,0.012)
f_marg_2011_wide_A = ROOT.RooRealVar("f_marg_2011_wide_A","f_marg_2011_wide_A",8.83992e-01,0.5,1.)
f_marg_2012_wide_A = ROOT.RooRealVar("f_marg_2012_wide_A","f_marg_2012_wide_A",8.41554e-01,0.5,1.)
gamma_2011_wide_A.setConstant(1)
beta_2011_wide_A.setConstant(1)
gamma_2012_wide_A.setConstant(1)
beta_2012_wide_A.setConstant(1)
gamma_2011_wide_B.setConstant(1)
beta_2011_wide_B.setConstant(1)
gamma_2012_wide_B.setConstant(1)
beta_2012_wide_B.setConstant(1)
f_marg_2011_wide_A.setConstant(1)
f_marg_2012_wide_A.setConstant(1)
gamma_2011_narrow_A = ROOT.RooRealVar("gamma_2011_narrow_A","gamma_2011_narrow_A",1.40444e+01,10.,20.)
beta_2011_narrow_A = ROOT.RooRealVar("beta_2011_narrow_A","beta_2011_narrow_A",2.20383e-03,0.001,0.01)
gamma_2011_narrow_B = ROOT.RooRealVar("gamma_2011_narrow_B","gamma_2011_narrow_B",2.90042e+00,1.,10.)
beta_2011_narrow_B = ROOT.RooRealVar("beta_2011_narrow_B","beta_2011_narrow_B",1.14178e-02,0.005,0.02)
gamma_2012_narrow_A = ROOT.RooRealVar("gamma_2012_narrow_A","gamma_2012_narrow_A",1.43411e+01,10.,20.)
beta_2012_narrow_A = ROOT.RooRealVar("beta_2012_narrow_A","beta_2012_narrow_A",2.17901e-03,0.0005,0.01)
gamma_2012_narrow_B = ROOT.RooRealVar("gamma_2012_narrow_B","gamma_2012_narrow_B",3.32812e+00,1.,10.)
beta_2012_narrow_B = ROOT.RooRealVar("beta_2012_narrow_B","beta_2012_narrow_B",9.99999e-03,0.0005,0.012)
f_marg_2011_narrow_A = ROOT.RooRealVar("f_marg_2011_narrow_A","f_marg_2011_narrow_A",8.83992e-01,0.5,1.)
f_marg_2012_narrow_A = ROOT.RooRealVar("f_marg_2012_narrow_A","f_marg_2012_narrow_A",8.41554e-01,0.5,1.)
gamma_2011_narrow_A.setConstant(1)
beta_2011_narrow_A.setConstant(1)
gamma_2012_narrow_A.setConstant(1)
beta_2012_narrow_A.setConstant(1)
gamma_2011_narrow_B.setConstant(1)
beta_2011_narrow_B.setConstant(1)
gamma_2012_narrow_B.setConstant(1)
beta_2012_narrow_B.setConstant(1)
f_marg_2011_narrow_A.setConstant(1)
f_marg_2012_narrow_A.setConstant(1)

# Effective 1D PDF.
gaus1_eff_2011_wide = ROOT.RooGaussian("gaus1_eff_2011_wide","gaus1_eff_2011_wide",difft,off_2011_wide,sigma1_eff_2011_wide)
gaus2_eff_2011_wide = ROOT.RooGaussian("gaus2_eff_2011_wide","gaus2_eff_2011_wide",difft,off_2011_wide,sigma2_eff_2011_wide)
gaus1_eff_2012_wide = ROOT.RooGaussian("gaus1_eff_2012_wide","gaus1_eff_2012_wide",difft,off_2012_wide,sigma1_eff_2012_wide)
gaus2_eff_2012_wide = ROOT.RooGaussian("gaus2_eff_2012_wide","gaus2_eff_2012_wide",difft,off_2012_wide,sigma2_eff_2012_wide)
res_eff_2011_wide = ROOT.RooAddPdf("res_eff_2011_wide","res_eff_2011_wide",gaus1_eff_2011_wide,gaus2_eff_2011_wide,f1_eff_2011_wide)
res_eff_2012_wide = ROOT.RooAddPdf("res_eff_2012_wide","res_eff_2012_wide",gaus1_eff_2012_wide,gaus2_eff_2012_wide,f1_eff_2012_wide)
gaus1_eff_2011_narrow = ROOT.RooGaussian("gaus1_eff_2011_narrow","gaus1_eff_2011_narrow",difft,off_2011_narrow,sigma1_eff_2011_narrow)
gaus2_eff_2011_narrow = ROOT.RooGaussian("gaus2_eff_2011_narrow","gaus2_eff_2011_narrow",difft,off_2011_narrow,sigma2_eff_2011_narrow)
gaus1_eff_2012_narrow = ROOT.RooGaussian("gaus1_eff_2012_narrow","gaus1_eff_2012_narrow",difft,off_2012_narrow,sigma1_eff_2012_narrow)
gaus2_eff_2012_narrow = ROOT.RooGaussian("gaus2_eff_2012_narrow","gaus2_eff_2012_narrow",difft,off_2012_narrow,sigma2_eff_2012_narrow)
res_eff_2011_narrow = ROOT.RooAddPdf("res_eff_2011_narrow","res_eff_2011_narrow",gaus1_eff_2011_narrow,gaus2_eff_2011_narrow,f1_eff_2011_narrow)
res_eff_2012_narrow = ROOT.RooAddPdf("res_eff_2012_narrow","res_eff_2012_narrow",gaus1_eff_2012_narrow,gaus2_eff_2012_narrow,f1_eff_2012_narrow)

# Full 2D PDF.
marg_pdf_2011_wide_A = ROOT.RooGamma("marg_pdf_2011_wide_A","marg_pdf_2011_wide_A",deltat,gamma_2011_wide_A,beta_2011_wide_A,zero)
marg_pdf_2012_wide_A = ROOT.RooGamma("marg_pdf_2012_wide_A","marg_pdf_2012_wide_A",deltat,gamma_2012_wide_A,beta_2012_wide_A,zero)
marg_pdf_2011_wide_B = ROOT.RooGamma("marg_pdf_2011_wide_B","marg_pdf_2011_wide_B",deltat,gamma_2011_wide_B,beta_2011_wide_B,zero)
marg_pdf_2012_wide_B = ROOT.RooGamma("marg_pdf_2012_wide_B","marg_pdf_2012_wide_B",deltat,gamma_2012_wide_B,beta_2012_wide_B,zero)
marg_pdf_2011_wide = ROOT.RooAddPdf("marg_pdf_2011_wide","marg_pdf_2011_wide",marg_pdf_2011_wide_A,marg_pdf_2011_wide_B,f_marg_2011_wide_A)
marg_pdf_2012_wide = ROOT.RooAddPdf("marg_pdf_2012_wide","marg_pdf_2012_wide",marg_pdf_2012_wide_A,marg_pdf_2012_wide_B,f_marg_2012_wide_A)
gaus1_2011_wide = ROOT.RooGaussian("gaus1_2011_wide","gaus1_2011_wide",difft,off_2011_wide,sigma1_2011_wide)
gaus2_2011_wide = ROOT.RooGaussian("gaus2_2011_wide","gaus2_2011_wide",difft,off_2011_wide,sigma2_2011_wide)
gaus1_2012_wide = ROOT.RooGaussian("gaus1_2012_wide","gaus1_2012_wide",difft,off_2012_wide,sigma1_2012_wide)
gaus2_2012_wide = ROOT.RooGaussian("gaus2_2012_wide","gaus2_2012_wide",difft,off_2012_wide,sigma2_2012_wide)
res_2011_wide = ROOT.RooAddPdf("res_2011_wide","res_2011_wide",gaus1_2011_wide,gaus2_2011_wide,f1_2011_wide)
res_2012_wide = ROOT.RooAddPdf("res_2012_wide","res_2012_wide",gaus1_2012_wide,gaus2_2012_wide,f1_2012_wide)
full_pdf_2011_wide = ROOT.RooProdPdf("full_pdf_2011_wide","full_pdf_2011_wide",ROOT.RooArgSet(res_2011_wide),ROOT.RooFit.Conditional(ROOT.RooArgSet(marg_pdf_2011_wide),ROOT.RooArgSet(deltat)))
full_pdf_2012_wide = ROOT.RooProdPdf("full_pdf_2012_wide","full_pdf_2012_wide",ROOT.RooArgSet(res_2012_wide),ROOT.RooFit.Conditional(ROOT.RooArgSet(marg_pdf_2012_wide),ROOT.RooArgSet(deltat)))
marg_pdf_2011_narrow_A = ROOT.RooGamma("marg_pdf_2011_narrow_A","marg_pdf_2011_narrow_A",deltat,gamma_2011_narrow_A,beta_2011_narrow_A,zero)
marg_pdf_2012_narrow_A = ROOT.RooGamma("marg_pdf_2012_narrow_A","marg_pdf_2012_narrow_A",deltat,gamma_2012_narrow_A,beta_2012_narrow_A,zero)
marg_pdf_2011_narrow_B = ROOT.RooGamma("marg_pdf_2011_narrow_B","marg_pdf_2011_narrow_B",deltat,gamma_2011_narrow_B,beta_2011_narrow_B,zero)
marg_pdf_2012_narrow_B = ROOT.RooGamma("marg_pdf_2012_narrow_B","marg_pdf_2012_narrow_B",deltat,gamma_2012_narrow_B,beta_2012_narrow_B,zero)
marg_pdf_2011_narrow = ROOT.RooAddPdf("marg_pdf_2011_narrow","marg_pdf_2011_narrow",marg_pdf_2011_narrow_A,marg_pdf_2011_narrow_B,f_marg_2011_narrow_A)
marg_pdf_2012_narrow = ROOT.RooAddPdf("marg_pdf_2012_narrow","marg_pdf_2012_narrow",marg_pdf_2012_narrow_A,marg_pdf_2012_narrow_B,f_marg_2012_narrow_A)
gaus1_2011_narrow = ROOT.RooGaussian("gaus1_2011_narrow","gaus1_2011_narrow",difft,off_2011_narrow,sigma1_2011_narrow)
gaus2_2011_narrow = ROOT.RooGaussian("gaus2_2011_narrow","gaus2_2011_narrow",difft,off_2011_narrow,sigma2_2011_narrow)
gaus1_2012_narrow = ROOT.RooGaussian("gaus1_2012_narrow","gaus1_2012_narrow",difft,off_2012_narrow,sigma1_2012_narrow)
gaus2_2012_narrow = ROOT.RooGaussian("gaus2_2012_narrow","gaus2_2012_narrow",difft,off_2012_narrow,sigma2_2012_narrow)
res_2011_narrow = ROOT.RooAddPdf("res_2011_narrow","res_2011_narrow",gaus1_2011_narrow,gaus2_2011_narrow,f1_2011_narrow)
res_2012_narrow = ROOT.RooAddPdf("res_2012_narrow","res_2012_narrow",gaus1_2012_narrow,gaus2_2012_narrow,f1_2012_narrow)
full_pdf_2011_narrow = ROOT.RooProdPdf("full_pdf_2011_narrow","full_pdf_2011_narrow",ROOT.RooArgSet(res_2011_narrow),ROOT.RooFit.Conditional(ROOT.RooArgSet(marg_pdf_2011_narrow),ROOT.RooArgSet(deltat)))
full_pdf_2012_narrow = ROOT.RooProdPdf("full_pdf_2012_narrow","full_pdf_2012_narrow",ROOT.RooArgSet(res_2012_narrow),ROOT.RooFit.Conditional(ROOT.RooArgSet(marg_pdf_2012_narrow),ROOT.RooArgSet(deltat)))


# ################################################################
# F U N C T I O N S
# ################################################################

def DefineParams(bin_sim):

	r = range(bin_sim)
	sigma1_2011_l = map(ROOT.RooRealVar,map(lambda x:"sigma1_"+str(x)+"_sim_2011",r),map(lambda x:"sigma1_"+str(x)+"_sim_2011",r),map(lambda x:0.03,r),map(lambda x:0.01,r),map(lambda x:0.06,r))
	sigma2_2011_l = map(ROOT.RooRealVar,map(lambda x:"sigma2_"+str(x)+"_sim_2011",r),map(lambda x:"sigma2_"+str(x)+"_sim_2011",r),map(lambda x:0.06,r),map(lambda x:0.04,r),map(lambda x:0.1,r))
	sigma1_2012_l = map(ROOT.RooRealVar,map(lambda x:"sigma1_"+str(x)+"_sim_2012",r),map(lambda x:"sigma1_"+str(x)+"_sim_2012",r),map(lambda x:0.03,r),map(lambda x:0.01,r),map(lambda x:0.06,r))
	sigma2_2012_l = map(ROOT.RooRealVar,map(lambda x:"sigma2_"+str(x)+"_sim_2012",r),map(lambda x:"sigma2_"+str(x)+"_sim_2012",r),map(lambda x:0.06,r),map(lambda x:0.04,r),map(lambda x:0.1,r))
	for i in sigma1_2011_l: sigma1_sim_2011_list.append(i)
	for i in sigma2_2011_l: sigma2_sim_2011_list.append(i)
	for i in sigma1_2012_l: sigma1_sim_2012_list.append(i)
	for i in sigma2_2012_l: sigma2_sim_2012_list.append(i)

def InvCdf(x,cdf):

	step = (deltat.getMax()-deltat.getMin())/10000.
	for i in range(10000):
		deltat.setVal(i*step)
		if cdf.getVal() >= x: return i*step
	return deltat.getMax()

def GetBinning(nbins):

	cdf_marg_2011 = marg_pdf_2011.createCdf(ROOT.RooArgSet(deltat))
	cdf_marg_2012 = marg_pdf_2012.createCdf(ROOT.RooArgSet(deltat))
	bin_step = 1./nbins
	binning_2011 = [0.]
	binning_2012 = [0.]
	for i in range(nbins):
		binning_2011.append(InvCdf((i+1.)*bin_step,cdf_marg_2011))
		binning_2012.append(InvCdf((i+1.)*bin_step,cdf_marg_2012))
	return binning_2011, binning_2012

def adaptiveBinning(var,nbins,applyweights,data):

	nhistobins = 2000
	histo_aux = ROOT.TH1F("histo_aux","histo_aux",nhistobins,var.getMin(),var.getMax())
	for i in range(data.numEntries()):
		x = data.get(i).getRealValue(var.GetName())
		w = data.weight()
		if applyweights: histo_aux.Fill(x,w)
		else: histo_aux.Fill(x)
	bincontent = histo_aux.Integral()/float(nbins)
	cumulative = 0
	for i in range(nhistobins):
		cumulative += histo_aux.GetBinContent(i+1)
		Ni = cumulative
		while Ni>bincontent: Ni -= bincontent
		histo_aux.SetBinContent(i+1,Ni)
	histo_aux.SetBinContent(nhistobins,bincontent)

	binningscheme = [var.getMin()]
	for i in range(nhistobins-1):
		if (histo_aux.GetBinContent(i+1)>histo_aux.GetBinContent(i+2)) and (len(binningscheme)<nbins): binningscheme.append(histo_aux.GetBinCenter(i+1))
	binningscheme.append(var.getMax())

	return binningscheme

def CreateDatasets(bin_sim):

	r = range(bin_sim)
	data_2011_l = map(ROOT.RooDataSet,map(lambda x:"data_difft_"+str(x)+"_sim_2011",r),map(lambda x:"data_difft_"+str(x)+"_sim_2011",r),map(lambda x:ROOT.RooArgSet(difft),r))
	data_2012_l = map(ROOT.RooDataSet,map(lambda x:"data_difft_"+str(x)+"_sim_2012",r),map(lambda x:"data_difft_"+str(x)+"_sim_2012",r),map(lambda x:ROOT.RooArgSet(difft),r))
	for i in data_2011_l: data_difft_sim_2011_list.append(i)
	for i in data_2012_l: data_difft_sim_2012_list.append(i)

def MCsetcut(year_aux,set_aux):
	if year_aux == 0:
		if set_aux == 0: cut_aux = "itype==-73"
		elif set_aux == 1: cut_aux = "itype==-70"
		else: cut_aux = "(itype==-73 || itype==-70)"
	else:
		if set_aux == 0: cut_aux = "itype==-83"
		elif set_aux == 1: cut_aux = "itype==-80"
		else: cut_aux = "(itype==-83 || itype==-80)"
	return cut_aux

def MCtruth(ev):
	if abs(ev.B_s0_TRUEID) == 531:
		if ev.Kplus_TRUEID == 321:
			if ev.Kminus_TRUEID == -321:
				if ev.Piplus_TRUEID == 211:
					if ev.Piminus_TRUEID == -211: return 1
	return 0

def LoadData_1D(data_file, data_tree, datatype, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if datatype == 0: print 'MC sample: PhSp.'
	elif datatype == 1: print 'MC sample: VV.'
	else: print 'MC sample: PhSp + VV.'
	if (evnum_limit == 0): print 'All events selected.'
	else: print 'Maximum of '+str(evnum_limit)+' events selected per data sample.'

	# Input data.
	file_in = ROOT.TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = ROOT.TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_2011_wide = tree_full.CopyTree(t_name_res+">=0. && "+t_name_res+"<=12. && "+m1_name_MC+"<"+str(mHlimit)+" && "+m2_name_MC+"<"+str(mHlimit)+" && "+MCsetcut(0,datatype))
	tree_2012_wide = tree_full.CopyTree(t_name_res+">=0. && "+t_name_res+"<=12. && "+m1_name_MC+"<"+str(mHlimit)+" && "+m2_name_MC+"<"+str(mHlimit)+" && "+MCsetcut(1,datatype))
	tree_2011_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_res+">=0. && "+t_name_res+"<=12. && "+MCsetcut(0,datatype))
	tree_2012_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_res+">=0. && "+t_name_res+"<=12. && "+MCsetcut(1,datatype))

	ev_counter_total = 0
	ev_counter = 0
	for i in tree_2011_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i) and eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.:
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			data_difft_2011_wide.add(ROOT.RooArgSet(difft))
			ev_counter += 1
			ev_counter_total += 1
	ev_counter = 0
	for i in tree_2012_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i) and eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.:
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			data_difft_2012_wide.add(ROOT.RooArgSet(difft))
			ev_counter += 1
			ev_counter_total += 1
	ev_counter = 0
	for i in tree_2011_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i) and eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.:
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			data_difft_2011_narrow.add(ROOT.RooArgSet(difft))
			ev_counter += 1
			ev_counter_total += 1
	ev_counter = 0
	for i in tree_2012_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i) and eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.:
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			data_difft_2012_narrow.add(ROOT.RooArgSet(difft))
			ev_counter += 1
			ev_counter_total += 1

	print str(ev_counter_total)+' events loaded.'

	return

def LoadData_sim(name_2011,name_2012,binning_2011,binning_2012):

	print "Creating the datasets for 2011 ..."
	f_2011 = ROOT.TFile(NTUPLE_PATH + name_2011 + ".root")
	t_2011 = f_2011.Get("DecayTree")
	for i in t_2011:
		if (1000.*eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.):
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			for j in range(len(binning_2011)-1):
				if (eval("i."+terr_name_res) >= binning_2011[j] and eval("i."+terr_name_res) < binning_2011[j+1]): data_difft_sim_2011_list[j].add(ROOT.RooArgSet(difft))
	print "Datasets created."

	print "Creatings the dataset for 2012 ..."
	f_2012 = ROOT.TFile(NTUPLE_PATH + name_2012 + ".root")
	t_2012 = f_2012.Get("DecayTree")
	for i in t_2012:
		if (1000.*eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.):
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			for j in range(len(binning_2012)-1):
				if (eval("i."+terr_name_res) >= binning_2012[j] and eval("i."+terr_name_res) < binning_2012[j+1]): data_difft_sim_2012_list[j].add(ROOT.RooArgSet(difft))
	print "Datasets created."

	return

def LoadData_2D(data_file, data_tree, datatype, evnum_limit = 0):

	# Information.
	print 'Loading data file ' + data_file + ' ...'
	if datatype == 0: print 'MC sample: PhSp.'
	elif datatype == 1: print 'MC sample: VV.'
	else: print 'MC sample: PhSp + VV.'
	if (evnum_limit == 0): print 'All events selected.'
	else: print 'Maximum of '+str(evnum_limit)+' events selected per data sample.'

	# Input data.
	file_in = ROOT.TFile(NTUPLE_PATH + data_file)
	tree_full = file_in.Get(data_tree)
	file_out = ROOT.TFile(NTUPLE_PATH + "trash.root","RECREATE")
	tree_2011_wide = tree_full.CopyTree(t_name_res+">=0. && "+t_name_res+"<=12. && "+m1_name_MC+"<"+str(mHlimit)+" && "+m2_name_MC+"<"+str(mHlimit)+" && "+MCsetcut(0,datatype))
	tree_2012_wide = tree_full.CopyTree(t_name_res+">=0. && "+t_name_res+"<=12. && "+m1_name_MC+"<"+str(mHlimit)+" && "+m2_name_MC+"<"+str(mHlimit)+" && "+MCsetcut(1,datatype))
	tree_2011_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_res+">=0. && "+t_name_res+"<=12. && "+MCsetcut(0,datatype))
	tree_2012_narrow = tree_full.CopyTree("abs("+m1_name_MC+"-900.)<150. && abs("+m2_name_MC+"-900.)<150. && "+t_name_res+">=0. && "+t_name_res+"<=12. && "+MCsetcut(1,datatype))

	ev_counter_total = 0
	ev_counter = 0
	for i in tree_2011_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i) and eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.:
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			deltat.setVal(eval("i."+terr_name_res))
			data_2011_wide.add(ROOT.RooArgSet(difft,deltat))
			ev_counter += 1
			ev_counter_total += 1
	ev_counter = 0
	for i in tree_2012_wide:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i) and eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.:
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			deltat.setVal(eval("i."+terr_name_res))
			data_2012_wide.add(ROOT.RooArgSet(difft,deltat))
			ev_counter += 1
			ev_counter_total += 1
	ev_counter = 0
	for i in tree_2011_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i) and eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.:
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			deltat.setVal(eval("i."+terr_name_res))
			data_2011_narrow.add(ROOT.RooArgSet(difft,deltat))
			ev_counter += 1
			ev_counter_total += 1
	ev_counter = 0
	for i in tree_2012_narrow:
		if ((evnum_limit == 0) or ((evnum_limit != 0) and (ev_counter < evnum_limit))) and MCtruth(i) and eval("i."+ttrue_name_res) >= 0. and eval("i."+terr_name_res) >= 0.:
			difft.setVal(eval("i."+t_name_res)-1000.*eval("i."+ttrue_name_res))
			deltat.setVal(eval("i."+terr_name_res))
			data_2012_narrow.add(ROOT.RooArgSet(difft,deltat))
			ev_counter += 1
			ev_counter_total += 1

	deltat_mean_2011_wide.setVal(data_2011_wide.mean(deltat))
	deltat_mean_2011_wide.setConstant(1)
	deltat_mean_2012_wide.setVal(data_2012_wide.mean(deltat))
	deltat_mean_2012_wide.setConstant(1)
	deltat_mean_2011_narrow.setVal(data_2011_narrow.mean(deltat))
	deltat_mean_2011_narrow.setConstant(1)
	deltat_mean_2012_narrow.setVal(data_2012_narrow.mean(deltat))
	deltat_mean_2012_narrow.setConstant(1)

	print str(ev_counter_total)+' events loaded.'

	return

def Fit1DPDF(offset):

	if offset == 0:
		off_2011_wide.setConstant(1)
		off_2012_wide.setConstant(1)
		off_2011_narrow.setConstant(1)
		off_2012_narrow.setConstant(1)
		print "\n*** INFO: Mean offset set to 0. ***"
	elif offset == 1: print "\n*** INFO: Mean offset floated during fitting. ***"
	else:
		print "ERROR: wrong value for the mean offset parameter."
		return

	fit_2011_wide = res_eff_2011_wide.fitTo(data_difft_2011_wide,ROOT.RooFit.NumCPU(8),ROOT.RooFit.Minos(1),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE))
	fit_2012_wide = res_eff_2012_wide.fitTo(data_difft_2012_wide,ROOT.RooFit.NumCPU(8),ROOT.RooFit.Minos(1),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE))
	fit_2011_narrow = res_eff_2011_narrow.fitTo(data_difft_2011_narrow,ROOT.RooFit.NumCPU(8),ROOT.RooFit.Minos(1),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE))
	fit_2012_narrow = res_eff_2012_narrow.fitTo(data_difft_2012_narrow,ROOT.RooFit.NumCPU(8),ROOT.RooFit.Minos(1),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE))

	return fit_2011_wide, fit_2012_wide, fit_2011_narrow, fit_2012_narrow

def PrintTReseffPars():

	trespars = "class TReseffclass {\n\n  public:\n\n  Double_t f1(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(f1_eff_2011_narrow.getVal())+";}\n      else {return "+str(f1_eff_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(f1_eff_2012_narrow.getVal())+";}\n      else {return "+str(f1_eff_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t sigma1(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(sigma1_eff_2011_narrow.getVal())+";}\n      else {return "+str(sigma1_eff_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(sigma1_eff_2012_narrow.getVal())+";}\n      else {return "+str(sigma1_eff_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t sigma2(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(sigma2_eff_2011_narrow.getVal())+";}\n      else {return "+str(sigma2_eff_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(sigma2_eff_2012_narrow.getVal())+";}\n      else {return "+str(sigma2_eff_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t off(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(off_2011_narrow.getVal())+";}\n      else {return "+str(off_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(off_2012_narrow.getVal())+";}\n      else {return "+str(off_2012_wide.getVal())+";}\n    }\n  };\n\n};"

	fpar = open('../../src/TimeDependent/TReseffclass.h','w')
	fpar.write(trespars)
	fpar.close()

def FitMargPDF():

	gamma_2011_wide_A.setConstant(0)
	beta_2011_wide_A.setConstant(0)
	gamma_2012_wide_A.setConstant(0)
	beta_2012_wide_A.setConstant(0)
	gamma_2011_wide_B.setConstant(0)
	beta_2011_wide_B.setConstant(0)
	gamma_2012_wide_B.setConstant(0)
	beta_2012_wide_B.setConstant(0)
	f_marg_2011_wide_A.setConstant(0)
	f_marg_2012_wide_A.setConstant(0)
	gamma_2011_narrow_A.setConstant(0)
	beta_2011_narrow_A.setConstant(0)
	gamma_2012_narrow_A.setConstant(0)
	beta_2012_narrow_A.setConstant(0)
	gamma_2011_narrow_B.setConstant(0)
	beta_2011_narrow_B.setConstant(0)
	gamma_2012_narrow_B.setConstant(0)
	beta_2012_narrow_B.setConstant(0)
	f_marg_2011_narrow_A.setConstant(0)
	f_marg_2012_narrow_A.setConstant(0)

	marg_pdf_2011_wide.fitTo(data_2011_wide,ROOT.RooFit.Minos(1),ROOT.RooFit.NumCPU(8))
	marg_pdf_2012_wide.fitTo(data_2012_wide,ROOT.RooFit.Minos(1),ROOT.RooFit.NumCPU(8))
	marg_pdf_2011_narrow.fitTo(data_2011_narrow,ROOT.RooFit.Minos(1),ROOT.RooFit.NumCPU(8))
	marg_pdf_2012_narrow.fitTo(data_2012_narrow,ROOT.RooFit.Minos(1),ROOT.RooFit.NumCPU(8))

	gamma_2011_wide_A.setConstant(1)
	beta_2011_wide_A.setConstant(1)
	gamma_2012_wide_A.setConstant(1)
	beta_2012_wide_A.setConstant(1)
	gamma_2011_wide_B.setConstant(1)
	beta_2011_wide_B.setConstant(1)
	gamma_2012_wide_B.setConstant(1)
	beta_2012_wide_B.setConstant(1)
	f_marg_2011_wide_A.setConstant(1)
	f_marg_2012_wide_A.setConstant(1)
	gamma_2011_narrow_A.setConstant(1)
	beta_2011_narrow_A.setConstant(1)
	gamma_2012_narrow_A.setConstant(1)
	beta_2012_narrow_A.setConstant(1)
	gamma_2011_narrow_B.setConstant(1)
	beta_2011_narrow_B.setConstant(1)
	gamma_2012_narrow_B.setConstant(1)
	beta_2012_narrow_B.setConstant(1)
	f_marg_2011_narrow_A.setConstant(1)
	f_marg_2012_narrow_A.setConstant(1)

def Fit2DPDF(pol_order,q0_term,offset):

	if pol_order == 0:
		q1A_2011_wide.setVal(0.)
		q1B_2011_wide.setVal(0.)
		q1A_2012_wide.setVal(0.)
		q1B_2012_wide.setVal(0.)
		q2A_2011_wide.setVal(0.)
		q2B_2011_wide.setVal(0.)
		q2A_2012_wide.setVal(0.)
		q2B_2012_wide.setVal(0.)
		q1A_2011_narrow.setVal(0.)
		q1B_2011_narrow.setVal(0.)
		q1A_2012_narrow.setVal(0.)
		q1B_2012_narrow.setVal(0.)
		q2A_2011_narrow.setVal(0.)
		q2B_2011_narrow.setVal(0.)
		q2A_2012_narrow.setVal(0.)
		q2B_2012_narrow.setVal(0.)
		q1A_2011_wide.setConstant(1)
		q1B_2011_wide.setConstant(1)
		q1A_2012_wide.setConstant(1)
		q1B_2012_wide.setConstant(1)
		q2A_2011_wide.setConstant(1)
		q2B_2011_wide.setConstant(1)
		q2A_2012_wide.setConstant(1)
		q2B_2012_wide.setConstant(1)
		q1A_2011_narrow.setConstant(1)
		q1B_2011_narrow.setConstant(1)
		q1A_2012_narrow.setConstant(1)
		q1B_2012_narrow.setConstant(1)
		q2A_2011_narrow.setConstant(1)
		q2B_2011_narrow.setConstant(1)
		q2A_2012_narrow.setConstant(1)
		q2B_2012_narrow.setConstant(1)
		print "\n*** INFO: Constant parametrization for sigma_eff(t_error). ***"
	elif pol_order == 1:
		q2A_2011_wide.setVal(0.)
		q2B_2011_wide.setVal(0.)
		q2A_2012_wide.setVal(0.)
		q2B_2012_wide.setVal(0.)
		q2A_2011_narrow.setVal(0.)
		q2B_2011_narrow.setVal(0.)
		q2A_2012_narrow.setVal(0.)
		q2B_2012_narrow.setVal(0.)
		q2A_2011_wide.setConstant(1)
		q2B_2011_wide.setConstant(1)
		q2A_2012_wide.setConstant(1)
		q2B_2012_wide.setConstant(1)
		q2A_2011_narrow.setConstant(1)
		q2B_2011_narrow.setConstant(1)
		q2A_2012_narrow.setConstant(1)
		q2B_2012_narrow.setConstant(1)
		print "\n*** INFO: Linear parametrization for sigma_eff(t_error). ***"
	elif pol_order == 2: print "\n*** INFO: Quadratic parametrization for sigma_eff(t_error). ***"
	else:
		print "ERROR: wrong order of the polinomial."
		return

	if q0_term == 0:
		q0A_2011_wide.setVal(0.)
		q0B_2011_wide.setVal(0.)
		q0A_2012_wide.setVal(0.)
		q0B_2012_wide.setVal(0.)
		q0A_2011_narrow.setVal(0.)
		q0B_2011_narrow.setVal(0.)
		q0A_2012_narrow.setVal(0.)
		q0B_2012_narrow.setVal(0.)
		q0A_2011_wide.setConstant(1)
		q0B_2011_wide.setConstant(1)
		q0A_2012_wide.setConstant(1)
		q0B_2012_wide.setConstant(1)
		q0A_2011_narrow.setConstant(1)
		q0B_2011_narrow.setConstant(1)
		q0A_2012_narrow.setConstant(1)
		q0B_2012_narrow.setConstant(1)
		print "\n*** INFO: Order-0 in the width parametrization set to 0. ***"
	elif q0_term == 1: print "\n*** INFO: Order-0 in the width parametrization floated during fitting. ***"
	else:
		print "ERROR: wrong value for the order-0 parameter."
		return

	if offset == 0:
		off_2011_wide.setConstant(1)
		off_2012_wide.setConstant(1)
		off_2011_narrow.setConstant(1)
		off_2012_narrow.setConstant(1)
		print "\n*** INFO: Mean offset set to 0. ***"
	elif offset == 1: print "\n*** INFO: Mean offset floated during fitting. ***"
	else:
		print "ERROR: wrong value for the mean offset parameter."
		return

	fit_2011_wide = full_pdf_2011_wide.fitTo(data_2011_wide,ROOT.RooFit.Minos(1),ROOT.RooFit.NumCPU(8),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE))
	fit_2012_wide = full_pdf_2012_wide.fitTo(data_2012_wide,ROOT.RooFit.Minos(1),ROOT.RooFit.NumCPU(8),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE))
	fit_2011_narrow = full_pdf_2011_narrow.fitTo(data_2011_narrow,ROOT.RooFit.Minos(1),ROOT.RooFit.NumCPU(8),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE))
	fit_2012_narrow = full_pdf_2012_narrow.fitTo(data_2012_narrow,ROOT.RooFit.Minos(1),ROOT.RooFit.NumCPU(8),ROOT.RooFit.Timer(kTRUE),ROOT.RooFit.Save(kTRUE))

	return fit_2011_wide, fit_2012_wide, fit_2011_narrow, fit_2012_narrow

def PrintTResPars():

	trespars = "class TResclass {\n\n  public:\n\n  Double_t f1(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(f1_2011_narrow.getVal())+";}\n      else {return "+str(f1_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(f1_2012_narrow.getVal())+";}\n      else {return "+str(f1_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t mean(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(deltat_mean_2011_narrow.getVal())+";}\n      else {return "+str(deltat_mean_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(deltat_mean_2012_narrow.getVal())+";}\n      else {return "+str(deltat_mean_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t q0A(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(q0A_2011_narrow.getVal())+";}\n      else {return "+str(q0A_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(q0A_2012_narrow.getVal())+";}\n      else {return "+str(q0A_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t q0B(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(q0B_2011_narrow.getVal())+";}\n      else {return "+str(q0B_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(q0B_2012_narrow.getVal())+";}\n      else {return "+str(q0B_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t q1A(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(q1A_2011_narrow.getVal())+";}\n      else {return "+str(q1A_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(q1A_2012_narrow.getVal())+";}\n      else {return "+str(q1A_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t q1B(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(q1B_2011_narrow.getVal())+";}\n      else {return "+str(q1B_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(q1B_2012_narrow.getVal())+";}\n      else {return "+str(q1B_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t q2A(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(q2A_2011_narrow.getVal())+";}\n      else {return "+str(q2A_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(q2A_2012_narrow.getVal())+";}\n      else {return "+str(q2A_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t q2B(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(q2B_2011_narrow.getVal())+";}\n      else {return "+str(q2B_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(q2B_2012_narrow.getVal())+";}\n      else {return "+str(q2B_2012_wide.getVal())+";}\n    }\n  };\n\n  Double_t off(Int_t year_opt, Int_t wide_window) {\n    if (year_opt == 0) {\n      if (wide_window == 0) {return "+str(off_2011_narrow.getVal())+";}\n      else {return "+str(off_2011_wide.getVal())+";}\n    }\n    else {\n      if (wide_window == 0) {return "+str(off_2012_narrow.getVal())+";}\n      else {return "+str(off_2012_wide.getVal())+";}\n    }\n  };\n\n};"

	fpar = open('../../src/TimeDependent/TResclass2.h','w')
	fpar.write(trespars)
	fpar.close()

def Make1DPlot(nbins_difft):

	fdifft11wide = difft.frame()
	fdifft12wide = difft.frame()
	fdifft11narrow = difft.frame()
	fdifft12narrow = difft.frame()
	data_difft_2011_wide.plotOn(fdifft11wide,ROOT.RooFit.Binning(nbins_difft))
	res_eff_2011_wide.plotOn(fdifft11wide,ROOT.RooFit.LineColor(kRed))
	data_difft_2012_wide.plotOn(fdifft12wide,ROOT.RooFit.Binning(nbins_difft))
	res_eff_2012_wide.plotOn(fdifft12wide,ROOT.RooFit.LineColor(kRed))
	data_difft_2011_narrow.plotOn(fdifft11narrow,ROOT.RooFit.Binning(nbins_difft))
	res_eff_2011_narrow.plotOn(fdifft11narrow,ROOT.RooFit.LineColor(kRed))
	data_difft_2012_narrow.plotOn(fdifft12narrow,ROOT.RooFit.Binning(nbins_difft))
	res_eff_2012_narrow.plotOn(fdifft12narrow,ROOT.RooFit.LineColor(kRed))

	leg11wide = ROOT.TLegend(0.7,0.8,0.9,0.9)
	leg11wide.SetFillColor(kWhite)
	leg11wide.SetBorderSize(0)
	leg11wide.SetHeader("2011 MC data")
	#leg11wide.AddEntry(fdifft11wide.findObject("h_data_difft_2011_wide"),"Data","epl")
	#leg11wide.AddEntry(fdifft11wide.findObject("res_eff_2011_wide_Norm[difft]"),"2-Gaussian fit","epl")
	leg12wide = ROOT.TLegend(0.7,0.8,0.9,0.9)
	leg12wide.SetFillColor(kWhite)
	leg12wide.SetBorderSize(0)
	leg12wide.SetHeader("2012 MC data")
	#leg12wide.AddEntry(fdifft12wide.findObject("h_data_difft_2012_wide"),"Data","epl")
	#leg12wide.AddEntry(fdifft12wide.findObject("res_eff_2012_wide_Norm[difft]"),"2-Gaussian fit","epl")
	leg11narrow = ROOT.TLegend(0.7,0.8,0.9,0.9)
	leg11narrow.SetFillColor(kWhite)
	leg11narrow.SetBorderSize(0)
	leg11narrow.SetHeader("2011 MC data")
	#leg11narrow.AddEntry(fdifft11narrow.findObject("h_data_difft_2011_narrow"),"Data","epl")
	#leg11narrow.AddEntry(fdifft11narrow.findObject("res_eff_2011_narrow_Norm[difft]"),"2-Gaussian fit","epl")
	leg12narrow = ROOT.TLegend(0.7,0.8,0.9,0.9)
	leg12narrow.SetFillColor(kWhite)
	leg12narrow.SetBorderSize(0)
	leg12narrow.SetHeader("2012 MC data")
	#leg12narrow.AddEntry(fdifft12narrow.findObject("h_data_difft_2012_narrow"),"Data","epl")
	#leg12narrow.AddEntry(fdifft12narrow.findObject("res_eff_2012_narrow_Norm[difft]"),"2-Gaussian fit","epl")

	c1Dwide = ROOT.TCanvas("c1Dwide","c1Dwide",1600,600)
	c1Dwide.Divide(2)
	c1Dwide.cd(1)
	fdifft11wide.Draw()
	leg11wide.Draw()
	c1Dwide.cd(2)
	fdifft12wide.Draw()
	leg12wide.Draw()
	c1Dwide.Print("TimeRes1DplotWideWindow.root")
	c1Dwide.Print("TimeRes1DplotWideWindow.pdf")
	c1Dnarrow = ROOT.TCanvas("c1Dnarrow","c1Dnarrow",1600,600)
	c1Dnarrow.Divide(2)
	c1Dnarrow.cd(1)
	fdifft11narrow.Draw()
	leg11narrow.Draw()
	c1Dnarrow.cd(2)
	fdifft12narrow.Draw()
	leg12narrow.Draw()
	c1Dnarrow.Print("TimeRes1DplotnarrowWindow.root")
	c1Dnarrow.Print("TimeRes1DplotnarrowWindow.pdf")

def printSigmaEff(fit_2011_wide,fit_2012_wide,fit_2011_narrow,fit_2012_narrow):

	print '********************************'
	print 'Wide window'
	print '********************************'
	print 'Year 2011:'
	print 'sigma_eff = %.2f' % (1000.*sigma_eff_2011_wide.getVal())+' +- %.2f' % (1000.*sigma_eff_2011_wide.getPropagatedError(fit_2011_wide))+' fs'
	print '--------------------------------'
	print 'Year 2012:'
	print 'sigma_eff = %.2f' % (1000.*sigma_eff_2012_wide.getVal())+' +- %.2f' % (1000.*sigma_eff_2012_wide.getPropagatedError(fit_2012_wide))+' fs'
	print '********************************'
	print 'Narrow window'
	print '********************************'
	print 'Year 2011:'
	print 'sigma_eff = %.2f' % (1000.*sigma_eff_2011_narrow.getVal())+' +- %.2f' % (1000.*sigma_eff_2011_narrow.getPropagatedError(fit_2011_narrow))+' fs'
	print '--------------------------------'
	print 'Year 2012:'
	print 'sigma_eff = %.2f' % (1000.*sigma_eff_2012_narrow.getVal())+' +- %.2f' % (1000.*sigma_eff_2012_narrow.getPropagatedError(fit_2012_narrow))+' fs'
	print '********************************'

def Make2DPlot(nbins_difft,nbins_deltat):

	h11widedata = data_2011_wide.createHistogram(difft,deltat,nbins_difft,nbins_deltat)
	h12widedata = data_2012_wide.createHistogram(difft,deltat,nbins_difft,nbins_deltat)
	h11widepdf = full_pdf_2011_wide.createHistogram("h_pdf_2011_wide",difft,ROOT.RooFit.Binning(nbins_difft),ROOT.RooFit.YVar(deltat,ROOT.RooFit.Binning(nbins_deltat)))
	h12widepdf = full_pdf_2012_wide.createHistogram("h_pdf_2012_wide",difft,ROOT.RooFit.Binning(nbins_difft),ROOT.RooFit.YVar(deltat,ROOT.RooFit.Binning(nbins_deltat)))
	h11widepdf.SetLineColor(kRed)
	h12widepdf.SetLineColor(kRed)
	h11widedata.GetXaxis().SetTitle("t_{rec}-t_{gen} (ps)")
	h12widedata.GetXaxis().SetTitle("t_{rec}-t_{gen} (ps)")
	h11widedata.GetYaxis().SetTitle("t_{err} (ps)")
	h12widedata.GetYaxis().SetTitle("t_{err} (ps)")
	h11narrowdata = data_2011_narrow.createHistogram(difft,deltat,nbins_difft,nbins_deltat)
	h12narrowdata = data_2012_narrow.createHistogram(difft,deltat,nbins_difft,nbins_deltat)
	h11narrowpdf = full_pdf_2011_narrow.createHistogram("h_pdf_2011_narrow",difft,ROOT.RooFit.Binning(nbins_difft),ROOT.RooFit.YVar(deltat,ROOT.RooFit.Binning(nbins_deltat)))
	h12narrowpdf = full_pdf_2012_narrow.createHistogram("h_pdf_2012_narrow",difft,ROOT.RooFit.Binning(nbins_difft),ROOT.RooFit.YVar(deltat,ROOT.RooFit.Binning(nbins_deltat)))
	h11narrowpdf.SetLineColor(kRed)
	h12narrowpdf.SetLineColor(kRed)
	h11narrowdata.GetXaxis().SetTitle("t_{rec}-t_{gen} (ps)")
	h12narrowdata.GetXaxis().SetTitle("t_{rec}-t_{gen} (ps)")
	h11narrowdata.GetYaxis().SetTitle("t_{err} (ps)")
	h12narrowdata.GetYaxis().SetTitle("t_{err} (ps)")

	fdifft11wide = difft.frame()
	fdifft12wide = difft.frame()
	data_2011_wide.plotOn(fdifft11wide,ROOT.RooFit.Binning(nbins_difft))
	full_pdf_2011_wide.plotOn(fdifft11wide,ROOT.RooFit.LineColor(kRed))
	data_2012_wide.plotOn(fdifft12wide,ROOT.RooFit.Binning(nbins_difft))
	full_pdf_2012_wide.plotOn(fdifft12wide,ROOT.RooFit.LineColor(kRed))
	fdifft11narrow = difft.frame()
	fdifft12narrow = difft.frame()
	data_2011_narrow.plotOn(fdifft11narrow,ROOT.RooFit.Binning(nbins_difft))
	full_pdf_2011_narrow.plotOn(fdifft11narrow,ROOT.RooFit.LineColor(kRed))
	data_2012_narrow.plotOn(fdifft12narrow,ROOT.RooFit.Binning(nbins_difft))
	full_pdf_2012_narrow.plotOn(fdifft12narrow,ROOT.RooFit.LineColor(kRed))

	fdeltat11wide = deltat.frame()
	fdeltat12wide = deltat.frame()
	data_2011_wide.plotOn(fdeltat11wide,ROOT.RooFit.Binning(nbins_deltat))
	full_pdf_2011_wide.plotOn(fdeltat11wide,ROOT.RooFit.LineColor(kRed))
	data_2012_wide.plotOn(fdeltat12wide,ROOT.RooFit.Binning(nbins_deltat))
	full_pdf_2012_wide.plotOn(fdeltat12wide,ROOT.RooFit.LineColor(kRed))
	fdeltat11narrow = deltat.frame()
	fdeltat12narrow = deltat.frame()
	data_2011_narrow.plotOn(fdeltat11narrow,ROOT.RooFit.Binning(nbins_deltat))
	full_pdf_2011_narrow.plotOn(fdeltat11narrow,ROOT.RooFit.LineColor(kRed))
	data_2012_narrow.plotOn(fdeltat12narrow,ROOT.RooFit.Binning(nbins_deltat))
	full_pdf_2012_narrow.plotOn(fdeltat12narrow,ROOT.RooFit.LineColor(kRed))

	c2Dwide = ROOT.TCanvas("c2Dwide","c2Dwide",1200,800)
	c2Dwide.Divide(3,2)
	c2Dwide.cd(1)
	h11widedata.Draw("lego")
	h11widepdf.Draw("surfsame")
	c2Dwide.cd(2)
	fdifft11wide.Draw()
	c2Dwide.cd(3)
	fdeltat11wide.Draw()
	c2Dwide.cd(4)
	h12widedata.Draw("lego")
	h12widepdf.Draw("surfsame")
	c2Dwide.cd(5)
	fdifft12wide.Draw()
	c2Dwide.cd(6)
	fdeltat12wide.Draw()
	c2Dwide.Print("TimeRes2DplotWideWindow.root")
	c2Dwide.Print("TimeRes2DplotWideWindow.pdf")
	c2Dnarrow = ROOT.TCanvas("c2Dnarrow","c2Dnarrow",1200,800)
	c2Dnarrow.Divide(3,2)
	c2Dnarrow.cd(1)
	h11narrowdata.Draw("lego")
	h11narrowpdf.Draw("surfsame")
	c2Dnarrow.cd(2)
	fdifft11narrow.Draw()
	c2Dnarrow.cd(3)
	fdeltat11narrow.Draw()
	c2Dnarrow.cd(4)
	h12narrowdata.Draw("lego")
	h12narrowpdf.Draw("surfsame")
	c2Dnarrow.cd(5)
	fdifft12narrow.Draw()
	c2Dnarrow.cd(6)
	fdeltat12narrow.Draw()
	c2Dnarrow.Print("TimeRes2DplotNarrowWindow.root")
	c2Dnarrow.Print("TimeRes2DplotNarrowWindow.pdf")
