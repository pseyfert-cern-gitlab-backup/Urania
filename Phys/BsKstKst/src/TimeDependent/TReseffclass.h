class TReseffclass {

  public:

  Double_t f1(Int_t year_opt) {
    if (year_opt == 0) {return 0.920394119915;}
    else if (year_opt == 1) {return 0.920394119915;}
    return 0.;
    };

  Double_t sigma1(Int_t year_opt) {
    if (year_opt == 0) {return 0.0382719899719;}
    else if (year_opt == 1) {return 0.0382719899719;}
    return 0.;
    };

  Double_t sigma2(Int_t year_opt) {
    if (year_opt == 0) {return 0.199999997666;}
    else if (year_opt == 1) {return 0.199999997666;}
    return 0.;
    };

  Double_t off(Int_t year_opt) {
    if (year_opt == 0) {return 0.0;}
    else if (year_opt == 1) {return 0.0;}
    return 0.;
    };

};