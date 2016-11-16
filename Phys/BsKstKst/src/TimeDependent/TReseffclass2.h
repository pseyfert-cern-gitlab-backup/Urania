class TReseffclass {

  public:

  Double_t f1(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.88279675571;}
      else {return 0.881515492815;}
    }
    else {
      if (wide_window == 0) {return 0.897197203192;}
      else {return 0.909056680514;}
    }
  };

  Double_t sigma1(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.0305673786245;}
      else {return 0.030105737651;}
    }
    else {
      if (wide_window == 0) {return 0.0326031413896;}
      else {return 0.0327992816568;}
    }
  };

  Double_t sigma2(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.0758903475772;}
      else {return 0.0745848101949;}
    }
    else {
      if (wide_window == 0) {return 0.092395065138;}
      else {return 0.0952023863583;}
    }
  };

  Double_t off(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.0;}
      else {return 0.0;}
    }
    else {
      if (wide_window == 0) {return 0.0;}
      else {return 0.0;}
    }
  };

};