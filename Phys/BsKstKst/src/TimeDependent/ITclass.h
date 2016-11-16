class ITclass {

  public:

  Double_t IT_cosh(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 1.0;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 1.0;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 1.0;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 1.0;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 1.0;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 1.0;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 1.0;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 1.0;}
    return 0.;
    };

  Double_t IT_sinh(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.0964702864863;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0978982669514;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.095043778779;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.096120054139;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0971343496154;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0981694349091;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.09372704182;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.0948582425703;}
    return 0.;
    };

  Double_t IT_cos(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.00765711444155;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.00542385353322;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0090786648959;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.00259546730544;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.000872463167652;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.000934530985826;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.00239458523586;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.000892320652937;}
    return 0.;
    };

  Double_t IT_sin(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.0116151093554;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.00451240284928;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.00948746407882;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.007326823941;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.00308383776102;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.00320629377135;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.00903013475872;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.00207653752368;}
    return 0.;
    };

};