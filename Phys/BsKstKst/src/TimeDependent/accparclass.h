class accparclass {

  public:

  Double_t k1(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return -0.33876727865;}
    else if ((year_opt == 0) && (wide_window == 0)) {return -0.631741307569;}
    else if ((year_opt == 1) && (wide_window == 1)) {return -0.324208124959;}
    else if ((year_opt == 1) && (wide_window == 0)) {return -0.512332266792;}
    return 0.;
    };

  Double_t k2(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return -0.363258275096;}
    else if ((year_opt == 0) && (wide_window == 0)) {return -0.404112585196;}
    else if ((year_opt == 1) && (wide_window == 1)) {return -0.377659332671;}
    else if ((year_opt == 1) && (wide_window == 0)) {return -0.365394529996;}
    return 0.;
    };

  Double_t k3(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return -0.0427236337835;}
    else if ((year_opt == 0) && (wide_window == 0)) {return -0.000874674740211;}
    else if ((year_opt == 1) && (wide_window == 1)) {return -0.000808215990131;}
    else if ((year_opt == 1) && (wide_window == 0)) {return -0.0960005562634;}
    return 0.;
    };

  Double_t k4(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return -0.0501407664411;}
    else if ((year_opt == 0) && (wide_window == 0)) {return -0.000119319291944;}
    else if ((year_opt == 1) && (wide_window == 1)) {return -0.0595237474563;}
    else if ((year_opt == 1) && (wide_window == 0)) {return -3.61834520222e-05;}
    return 0.;
    };

  Double_t p1(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return -0.000133830420682;}
    else if ((year_opt == 0) && (wide_window == 0)) {return -0.00020738714103;}
    else if ((year_opt == 1) && (wide_window == 1)) {return -0.000111249749808;}
    else if ((year_opt == 1) && (wide_window == 0)) {return -4.4516630973e-06;}
    return 0.;
    };

  Double_t a_acc(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return 0.343323262462;}
    else if ((year_opt == 0) && (wide_window == 0)) {return 1.99888457747;}
    else if ((year_opt == 1) && (wide_window == 1)) {return 0.321265208012;}
    else if ((year_opt == 1) && (wide_window == 0)) {return 1.99953196353;}
    return 0.;
    };

  Double_t b_acc(Int_t year_opt, Int_t wide_window) {
    if ((year_opt == 0) && (wide_window == 1)) {return 0.0197170574547;}
    else if ((year_opt == 0) && (wide_window == 0)) {return 0.0911740974584;}
    else if ((year_opt == 1) && (wide_window == 1)) {return 0.0143445240582;}
    else if ((year_opt == 1) && (wide_window == 0)) {return 0.0999999874117;}
    return 0.;
    };

};