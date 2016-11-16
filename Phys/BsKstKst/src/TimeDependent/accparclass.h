class accparclass {

  public:

  Double_t k1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.590812844716;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.4603557383;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.413878890849;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.365249769437;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.58442115297;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.453680878478;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.417769245934;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.369767111416;}
    return 0.;
    };

  Double_t k2(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.385692122735;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.475238750012;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.341433800708;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.322607930124;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.373430700015;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.472525374623;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.365219929919;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.299756542965;}
    return 0.;
    };

  Double_t k3(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.0559084985255;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.0198890369342;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.163842939787;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.11334494964;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.0386028686514;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.00139552672085;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.119463687174;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.100326172355;}
    return 0.;
    };

  Double_t k4(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.00364796760187;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.0220563300788;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.0875315529186;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0913255791353;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0611086584856;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.0279585169953;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0582892028018;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0850908374537;}
    return 0.;
    };

  Double_t k5(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.0630940659953;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0340908479961;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0180209325142;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.0134190150301;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0181694463352;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0431535515229;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.00292110438224;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.0334297878538;}
    return 0.;
    };

  Double_t p1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.00042394835386;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.000104594382928;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.000353244271559;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -6.44595245403e-05;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.000199723627464;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.000146866255079;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.000790107359973;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 2.46842398732e-05;}
    return 0.;
    };

  Double_t a_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.256860737191;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.293414123935;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.190454803858;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.252060563334;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.200332792337;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.281209598544;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.204848435724;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.201042461055;}
    return 0.;
    };

  Double_t b_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.00209742812327;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.000295213067323;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0284753505486;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0385617037126;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.132381110007;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0182050179477;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.0192809565368;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.0250467245389;}
    return 0.;
    };

  Double_t c_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.00115415045094;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.00177242534145;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.00320904811577;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.00263544183155;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.0141439968138;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.00272077481844;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.00433263265215;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0043583964678;}
    return 0.;
    };

};