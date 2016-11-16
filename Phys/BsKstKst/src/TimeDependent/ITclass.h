class ITclass {

  public:

  Double_t IT_cosh(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return 1.0;}
    else if ((year_opt == 0) && (wide_window == 0)) {return 1.0;}
    else if ((year_opt == 1) && (wide_window == 1)) {return 1.0;}
    else if ((year_opt == 1) && (wide_window == 0)) {return 1.0;}
    return 0.;
    };

  Double_t IT_sinh(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return 0.0814508269587;}
    else if ((year_opt == 0) && (wide_window == 0)) {return 0.0814089198428;}
    else if ((year_opt == 1) && (wide_window == 1)) {return 0.0814508269587;}
    else if ((year_opt == 1) && (wide_window == 0)) {return 0.0814089198428;}
    return 0.;
    };

  Double_t IT_cos(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return 0.00229467337373;}
    else if ((year_opt == 0) && (wide_window == 0)) {return 0.00238304465941;}
    else if ((year_opt == 1) && (wide_window == 1)) {return 0.00229467337373;}
    else if ((year_opt == 1) && (wide_window == 0)) {return 0.00238304465941;}
    return 0.;
    };
  Double_t IT_sin(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return 0.00194620712691;}
    else if ((year_opt == 0) && (wide_window == 0)) {return 0.00165738073741;}
    else if ((year_opt == 1) && (wide_window == 1)) {return 0.00194620712691;}
    else if ((year_opt == 1) && (wide_window == 0)) {return 0.00165738073741;}
    return 0.;
    };

};