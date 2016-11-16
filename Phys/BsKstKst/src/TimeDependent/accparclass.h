class accparclass {

  public:

  Double_t k1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.651677447459;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.449219027035;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.544224451617;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.422400739511;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.661180689195;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.443237668934;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.513349634178;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.390530175092;}
    return 0.;
    };

  Double_t k2(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.372467678206;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.484745868136;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.350669651905;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.307859518836;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.376242353422;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.485392736477;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.288045105057;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.294096976455;}
    return 0.;
    };

  Double_t k3(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.00192709186462;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0445000277142;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.139123654784;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0416618214954;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0240106429292;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0691924669652;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0988471699949;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0196559485138;}
    return 0.;
    };

  Double_t k4(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.0174110747758;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.0247977321378;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.100595675276;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.08710244229;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.0242919018577;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.0257713584997;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.048192060889;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0859818760058;}
    return 0.;
    };

  Double_t k5(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.0575967421494;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.0234826507439;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0490745646912;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.0129870759683;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.0200986854347;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.0165321135545;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.0260773625916;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.0385445927391;}
    return 0.;
    };

  Double_t p1(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.000657483476143;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.000148459439037;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.000412482954798;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -8.00272699797e-05;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -6.96524249832e-07;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.00012761929741;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.000365134496047;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 1.52895904271e-05;}
    return 0.;
    };

  Double_t a_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.231465720545;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.299473609608;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.0851127917575;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.165751503106;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.133635705448;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.202605408499;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.22288145909;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.169933966526;}
    return 0.;
    };

  Double_t b_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return 0.106819396075;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return 0.121731459784;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return 0.954241613426;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return 0.229781702412;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return 0.384228305524;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return 0.191834358591;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return 0.026005310298;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return 0.161333585376;}
    return 0.;
    };

  Double_t c_acc(Int_t year_opt, Int_t trig_opt, Int_t wide_window) {
    if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 0)) {return -0.00871593432454;}
    else if ((year_opt == 0) && (trig_opt == 0) && (wide_window == 1)) {return -0.010530939883;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 0)) {return -0.0869682954118;}
    else if ((year_opt == 0) && (trig_opt == 1) && (wide_window == 1)) {return -0.0163314262659;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 0)) {return -0.0343549105901;}
    else if ((year_opt == 1) && (trig_opt == 0) && (wide_window == 1)) {return -0.0140212062961;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 0)) {return -0.00376827687161;}
    else if ((year_opt == 1) && (trig_opt == 1) && (wide_window == 1)) {return -0.0150755424108;}
    return 0.;
    };

};