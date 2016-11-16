class TReseffclass {

  public:

  Double_t f1(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.809518997962;}
      else {return 0.888141803723;}
    }
    else {
      if (wide_window == 0) {return 0.908441844739;}
      else {return 0.921968261051;}
    }
  };

  Double_t sigma1(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.0281956459342;}
      else {return 0.0296731705203;}
    }
    else {
      if (wide_window == 0) {return 0.0318672582679;}
      else {return 0.0319090616859;}
    }
  };

  Double_t sigma2(Int_t year_opt, Int_t wide_window) {
    if (year_opt == 0) {
      if (wide_window == 0) {return 0.0603818355683;}
      else {return 0.0686937765182;}
    }
    else {
      if (wide_window == 0) {return 0.0800043114231;}
      else {return 0.0847801461389;}
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