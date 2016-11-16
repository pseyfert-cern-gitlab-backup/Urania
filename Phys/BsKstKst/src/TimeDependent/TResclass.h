class TResclass {

  public:

  Double_t f1(Int_t year_opt) {
    if (year_opt == 0) {return 0.660612414358;}
    else if (year_opt == 1) {return 0.622497344426;}
    return 0.;
    };

  Double_t mean(Int_t year_opt) {
    if (year_opt == 0) {return 0.0332645173861;}
    else if (year_opt == 1) {return 0.0332645173861;}
    return 0.;
    };

  Double_t q0A(Int_t year_opt) {
    if (year_opt == 0) {return 0.00311507914321;}
    else if (year_opt == 1) {return 2.9296685168e-05;}
    return 0.;
    };

  Double_t q0B(Int_t year_opt) {
    if (year_opt == 0) {return 0.00583845664591;}
    else if (year_opt == 1) {return 0.00396115850728;}
    return 0.;
    };

  Double_t q1A(Int_t year_opt) {
    if (year_opt == 0) {return 1.01201050914;}
    else if (year_opt == 1) {return 1.05933635604;}
    return 0.;
    };

  Double_t q1B(Int_t year_opt) {
    if (year_opt == 0) {return 0.153395412264;}
    else if (year_opt == 1) {return 0.225848996813;}
    return 0.;
    };

  Double_t q2A(Int_t year_opt) {
    if (year_opt == 0) {return -22.6530843367;}
    else if (year_opt == 1) {return -21.8338927627;}
    return 0.;
    };

  Double_t q2B(Int_t year_opt) {
    if (year_opt == 0) {return -10.2939651658;}
    else if (year_opt == 1) {return -12.3636624434;}
    return 0.;
    };

  Double_t off(Int_t year_opt) {
    if (year_opt == 0) {return 0.0;}
    else if (year_opt == 1) {return 0.0;}
    return 0.;
    };

};