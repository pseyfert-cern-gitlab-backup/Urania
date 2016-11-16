from GetAcc import *
from ROOT import *

mKp1_ext = RooRealVar(m1_name_MC+"_ext","M(K^{+}#pi^{-}) ", 630., 2000.,"MeV/c^{2}")
mKp2_ext = RooRealVar(m2_name_MC+"_ext","M(K^{-}#pi^{+}) ", 630., 2000.,"MeV/c^{2}")

PDF_wide = MCGenComb("PDF_wide","PDF_wide",opt_genmodel,year_MC,RooFit.RooConst(1),mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC,t_MC,RooFit.RooConst(1))
PDF_narrow = MCGenComb("PDF_narrow","PDF_narrow",opt_genmodel,year_MC,RooFit.RooConst(0),mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,RooFit.RooConst(1))
PDF_red = MCGenComb("PDF_red","PDF_red",opt_genmodel,year_MC,RooFit.RooConst(1),mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC,t_MC,RooFit.RooConst(1))
PDF_ext = MCGenComb("PDF_ext","PDF_ext",opt_genmodel,year_MC,RooFit.RooConst(1),mKp1_ext,mKp2_ext,cos1_MC,cos2_MC,phi_MC,t_MC,RooFit.RooConst(1))

Im_wide = PDF_wide.createIntegral(RooArgSet(mKp1_MC,mKp2_MC,cos1_MC,cos2_MC,phi_MC))
Im_narrow = PDF_narrow.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC))
Im_red = PDF_red.createIntegral(RooArgSet(mKp1_narrow_MC,mKp2_narrow_MC,cos1_MC,cos2_MC,phi_MC))
Im_ext = PDF_ext.createIntegral(RooArgSet(mKp1_ext,mKp2_ext))

