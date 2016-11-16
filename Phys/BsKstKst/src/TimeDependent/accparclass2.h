class accparclass {

  public:

  Double_t k1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.615082938672;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.38282100039;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.343925660826;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.20603496637;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.619662142392;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.264010442757;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.424232027545;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.262076614284;}
    return 0.;
    };

  Double_t k2(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.384839396315;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.610409698953;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.331369879406;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.339139045086;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.629276852943;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.459224706764;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.434840501572;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.168128929456;}
    return 0.;
    };

  Double_t k3(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.04368338269;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.0508569791832;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.0999999999768;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0005242506485;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.0999998267509;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -3.37087996405e-10;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0993377571706;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.00164096273977;}
    return 0.;
    };

  Double_t k4(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.0166500863646;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.000264271570832;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.0999999999861;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0397780357276;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -6.01819101498e-08;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.0708416493724;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.00187720280542;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0658213488936;}
    return 0.;
    };

  Double_t p1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.000408969334901;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.000148394596195;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.000568097999574;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -2.48717713092e-13;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.000401030910642;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.000122809351757;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -4.54652981929e-12;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -2.95450746856e-05;}
    return 0.;
    };

  Double_t a_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 1.00932710687;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 1.75156864383;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 1.99993435949;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 1.01629219973;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.540525700884;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 1.67418121884;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.269628447417;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.87812550777;}
    return 0.;
    };

  Double_t b_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.0999998549717;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0999808323779;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0999999998336;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.0809133305913;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0999997499086;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0748649085907;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.000413425575652;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.00368293389419;}
    return 0.;
    };

};