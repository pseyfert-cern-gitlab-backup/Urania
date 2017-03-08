class accparclass {

  public:

  Double_t k1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.642257801087;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.476589315673;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.542818886141;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.44540436279;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.650909319885;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.471493547565;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.504187279307;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.408750120374;}
    return 0.;
    };

  Double_t k2(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.394530209299;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.515377865599;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.372234053383;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.322807984825;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.419383502006;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.51578667079;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.328916519691;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.32310456869;}
    return 0.;
    };

  Double_t k3(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.00116690301975;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0490323061613;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.115972640242;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0684919028418;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0556583201135;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0628024777366;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0798929630153;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0364703238556;}
    return 0.;
    };

  Double_t k4(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.000253974153548;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.0181486134797;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.09029272378;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0792821855131;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0182484420164;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.0316780498129;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.05840709391;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0777657607499;}
    return 0.;
    };

  Double_t k5(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.0588236363215;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0303396418224;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0349080974662;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.0106891916541;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.00615796820553;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0179705136705;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.00961010142265;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.0334588643507;}
    return 0.;
    };

  Double_t p1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.000512716395862;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.000158267352685;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.000442398401367;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -9.69773759172e-05;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 4.31969616184e-05;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.000152387245537;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.000392595843543;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -7.00188917457e-06;}
    return 0.;
    };

  Double_t a_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.245844430894;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.282187197437;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0817600356204;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.218707749442;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.151744631499;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.215496822803;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.227947717271;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.185244316093;}
    return 0.;
    };

  Double_t b_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.0380526428728;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0581658661088;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.60698161159;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.0502287275287;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.225797868635;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.092050386496;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0218052500013;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.0572047923328;}
    return 0.;
    };

  Double_t c_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.00554390136073;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.00806271401188;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.0591100777174;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.00486968626486;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.0232165747985;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.00884119846156;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.00145910288193;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.00815220390661;}
    return 0.;
    };

};