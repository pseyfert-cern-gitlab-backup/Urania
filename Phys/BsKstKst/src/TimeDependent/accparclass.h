class accparclass {

  public:

  Double_t k1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.630829050491;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.477337550858;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.543488827595;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.45920766386;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.664330063681;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.484283783097;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.582762556084;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.453237797043;}
    return 0.;
    };

  Double_t k2(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.384611936852;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.513870771938;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.39129993408;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.31299152603;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.388012093055;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.484346311842;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.267595109348;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.271664654903;}
    return 0.;
    };

  Double_t k3(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.0373055730831;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0361157008687;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.0761423224406;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0567589137362;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.011460977359;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0572245801585;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0727459251545;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0244933747673;}
    return 0.;
    };

  Double_t k4(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.00998806911888;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.000540880790234;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.116283480861;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0866897361332;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0307883440808;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.0441336297641;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0444898600857;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0829619714491;}
    return 0.;
    };

  Double_t k5(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.0619797643837;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.018339942008;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0421829822025;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.0228512669274;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.0150098678115;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.00791668775891;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0266140481123;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.00493332208194;}
    return 0.;
    };

  Double_t p1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.000406853607661;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.00017197452507;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.000489030269452;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.000103812100091;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.000503891978177;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.00034356831298;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 6.42783506899e-05;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.000295422817489;}
    return 0.;
    };

  Double_t a_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.341966884455;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.363083035661;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.105060405495;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.145933326492;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.132916726056;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.232148974976;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.256347731481;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.184035606735;}
    return 0.;
    };

  Double_t b_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.0427565966635;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.00697240357917;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.453489557213;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.210256859897;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.303040753246;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0541905573134;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0606058023994;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.0542877273264;}
    return 0.;
    };

  Double_t c_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.00113992662034;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.0024059841366;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.0440914827964;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0191723457493;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.0303284820742;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.00676421050224;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.00267590249286;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.00842982551104;}
    return 0.;
    };

};