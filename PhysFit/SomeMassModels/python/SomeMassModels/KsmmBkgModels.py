from ROOT import *
from FiterBasis import *

def expo_and_powerLaw (fiter):
     fiter.mean_bkg  =RooRealVar("mean_bkg", "mean_bkg", 448., -1., 470.)
     fiter.ind_bkg   =RooRealVar("ind_bkg",  "ind_bkg" , 11.,1.,50.)
     fiter.indx  = RooRealVar("k", "k", -1.e-04, -1., 0.1)
     fiter.f_expo= RooRealVar("f_expo"  ,"f_expo"  ,0.5, 0., 1.)
     fiter.peakbg=RooGenericPdf ('poln',"1/(abs("+fiter.var+"-mean_bkg)^ind_bkg)",RooArgList(fiter.mass, fiter.ind_bkg, fiter.mean_bkg))
     fiter.expbkg=RooExponential("expbkg", " exp background pdf", fiter.mass, fiter.indx)

     fiter.bkg  =RooAddPdf( 'peak_expo',  'peak_expo',  fiter.peakbg, fiter.expbkg, fiter.f_expo  )

     return 1

