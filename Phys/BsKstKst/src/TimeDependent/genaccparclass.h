Double_t knots_gen_wide[6] = {0.0,0.9,1.3,1.9,3.0,12.0};
Double_t knots_gen_narrow[6] = {0.0,0.9,1.3,1.9,3.0,12.0};

Double_t a_gen_wide[5][4] = {{0.0,-0.00138436998913,2.5481847953,-1.45909728079},
{-1.6653800648,5.54988251268,-3.61988951878,0.82537468739},
{-0.289336418837,2.37439717584,-1.17720849044,0.199046218586},
{0.993185871959,0.349361979846,-0.111400492548,0.0120623593064},
{1.32606052325,0.0164873285591,-0.000442275452223,-0.000266331481965}};

Double_t a_gen_narrow[5][4] = {{0.0,0.00101382530285,4.89487359849,-2.83048035352},
{-3.54249846114,11.8093420291,-8.22549107238,2.02891396902},
{1.06333885612,1.18048668157,-0.0494484973637,-0.0675072040589},
{-0.421082535913,3.52430993215,-1.28303968188,0.148912301997},
{3.78015377185,-0.67692637561,0.117372420705,-0.006689042735}};

class genaccparclass {

  public:

  Double_t k1_gen(Int_t wide_window) {
    if (wide_window) {return -0.40631262195;}
    else {return -0.505556252411;}
    };

  Double_t k2_gen(Int_t wide_window) {
    if (wide_window) {return -0.39861379722;}
    else {return -0.404368705592;}
    };

  Double_t k3_gen(Int_t wide_window) {
    if (wide_window) {return -0.0363987194893;}
    else {return -0.0483750503137;}
    };

  Double_t k4_gen(Int_t wide_window) {
    if (wide_window) {return -0.0644151228873;}
    else {return -0.0175772310185;}
    };

  Double_t k5_gen(Int_t wide_window) {
    if (wide_window) {return 0.0270906873059;}
    else {return 0.0389936024545;}
    };

  Double_t p1_gen(Int_t wide_window) {
    if (wide_window) {return -0.000100573256821;}
    else {return 4.35273527839e-05;}
    };

  Double_t knot_gen(Int_t wide_window,Int_t i) {
    if (wide_window == 0) {return knots_gen_narrow[i];}
    else {return knots_gen_wide[i];}
    }

  Double_t coef_gen(Int_t wide_window,Int_t ibin,Int_t deg) {
    if (wide_window == 0) {return a_gen_narrow[ibin][deg];}
    else {return a_gen_wide[ibin][deg];}
    }

};