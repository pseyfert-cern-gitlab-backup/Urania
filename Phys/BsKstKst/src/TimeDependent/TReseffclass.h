class TReseffclass {

  public:

  Double_t f1(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.80591382873;}
      else {return 0.80809597051;}
    }
    else {
      if (wide_window == 0) {return 0.90816579119;}
      else {return 0.917150881204;}
    }
  };

  Double_t sigma1(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.0279064976284;}
      else {return 0.0280763589568;}
    }
    else {
      if (wide_window == 0) {return 0.0318481405934;}
      else {return 0.0320901761742;}
    }
  };

  Double_t sigma2(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.0610675845714;}
      else {return 0.0604139639268;}
    }
    else {
      if (wide_window == 0) {return 0.0802360421915;}
      else {return 0.0837791692517;}
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