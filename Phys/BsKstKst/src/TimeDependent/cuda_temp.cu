__device__ double KpiKpiSpectrumNW::P_trueBs(iev) {

  set_buffer_integral_vars();
  double yield_Bs = (1.+DCP_prod)*int_Bs(iev);
  double yield_Bsbar = (1.-DCP_prod)*int_Bsbar(iev);

  return yield_Bs/(yield_Bs+yield_Bsbar);

 }

 void KpiKpiSpectrumNW::Randomize6D() {

   if (wide_window == 1) {
      m1_ran = 750.+ran.Rndm()*(1600.-750.);
      m2_ran = 750.+ran.Rndm()*(1600.-750.);
      }
   else {
      m1_ran = 750.+ran.Rndm()*(1050.-750.);
      m2_ran = 750.+ran.Rndm()*(1050.-750.);
      }
   cos1_ran = -1.+ran.Rndm()*2.;
   cos2_ran = -1.+ran.Rndm()*2.;
   phi_ran = ran.Rndm()*2.*pi;
   t_ran = ran.Rndm()*12.;

   return;

 }

void KpiKpiSpectrumNW::SetGenerator(int compute_max_fun, int sample_size_7D) {

  // Setting of the mKpi generation range.
  Wide_Window_Gen = wide_window;

  // Randomization of the random number generator seed.
  ran.SetSeed(0);

  // Variable inicialization.
  dec_flavour = 0.;
  dec_SSK_tagged = 0.;
  dec_OS_tagged = 0.;
  dec_accepted = 0.;
  N_accepted = 0;

  // Computation of the maximum value for the considered distributions, if requested.
  if (compute_max_fun == 1) {

    cout << "Computing p.d.f.'s maxima.\n";

    max_fun_deltat = 0.;
    max_fun_etaSSK = 0.;
    max_fun_etaOS = 0.;
    max_fun_6DBs = 0.;
    max_fun_6DBsbar = 0.;

    // Decay time error distribution.
    for (int i=0; i<10000; i++) {
      t_err_ran = 0.01+ran.Rndm()*(0.04-0.01);
      fun_ran = P_deltat(t_err_ran);
      if (fun_ran > max_fun_deltat) {max_fun_deltat = fun_ran;}
      }

    // Mistag probability distributions.
    for (int i=0; i<10000; i++) {
      etamistag_SSK_ran = 0.3+ran.Rndm()*(0.5-0.3);
      fun_ran = P_eta_SSK(etamistag_SSK_ran);
      if (fun_ran > max_fun_etaSSK) {max_fun_etaSSK = fun_ran;}
      etamistag_OS_ran = 0.3+ran.Rndm()*(0.5-0.3);
      fun_ran = P_eta_OS(etamistag_OS_ran);
      if (fun_ran > max_fun_etaOS) {max_fun_etaOS = fun_ran;}
      }

    // Decay variable distributions.
    cout << "(Using a randomized sample of " << sample_size_7D << " 7D points to find the maximum of the Bs and Bs-bar PDFs).\n";
    for (int i=0; i<sample_size_7D; i++) {
      Randomize7D_fun_max();
      set_buffer_differential_vars(m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran,t_ran,t_err_ran,0,0,0.5,0.5);
      fun_ran = fun_Bs()*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
      if (fun_ran > max_fun_6DBs) {max_fun_6DBs = fun_ran;}
      Randomize7D_fun_max();
      set_buffer_differential_vars(m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran,t_ran,t_err_ran,0,0,0.5,0.5);
      fun_ran = fun_Bsbar()*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
      if (fun_ran > max_fun_6DBsbar) {max_fun_6DBsbar = fun_ran;}
      }

    // Providing the computed maxima with an extra safety range.
    max_fun_deltat *= 1.2;
    max_fun_etaSSK *= 1.2;
    max_fun_etaOS *= 1.2;
    max_fun_6DBs *= 1.2;
    max_fun_6DBsbar *= 1.2;

    cout << "max_fun_deltat = " << max_fun_deltat << "\n" << "max_fun_etaSSK = " << max_fun_etaSSK << "\n" << "max_fun_etaOS = " << max_fun_etaOS << "\n" << "max_fun_6DBs = " << max_fun_6DBs << "\n" << "max_fun_6DBsbar = " << max_fun_6DBsbar << "\n";

    }

  else {

    if (Wide_Window_Gen == 0) {
      cout << "Using previously obtained values for the maxima of the PDFs in the narrow mKpi window.\n";
      max_fun_deltat = 68.8064;
      max_fun_etaSSK = 0.276388;
      max_fun_etaOS = 1.03582;
      max_fun_6DBs = 202.432;
      max_fun_6DBsbar = 194.987;
      }

    else {
      cout << "Using previously obtained values for the maxima of the PDFs in the wide mKpi window.\n";
      max_fun_deltat = 68.8064;
      max_fun_etaSSK = 0.276483;
      max_fun_etaOS = 1.03582;
      max_fun_6DBs = 760.726;
      max_fun_6DBsbar = 790.697;
      }

    }

  return;

 }

int KpiKpiSpectrumNW::getGenerator(const RooArgSet& directVars, RooArgSet &generateVars, Bool_t /*staticInitOK*/) {

  // 11-D generation, corresponding to the full set of observables.
  if ( matchArgs(directVars,generateVars,m1,m2,cos1,cos2) && matchArgs(directVars,generateVars,phi,t,decision_SSK,decision_OS) && matchArgs(directVars,generateVars,etamistag_SSK,etamistag_OS,t_err) ) return 1 ;

  return 0 ;

 }

void KpiKpiSpectrumNW::generateEvent(int code)
{

  assert(code==1);

  // Generation is performed in four steps:
  //    1. The per event decay time error is determined.
  //    2. A flavour, Bs or Bsbar, is assigned to the event.
  //    3. Tagging decisions and mistag probabilities are obtained.
  //    4. Decay variables (angles, invariant masses and decay time) are determined.

  // Determination of the per event decay time error.
  event_accepted = 0;
  max_fun = max_fun_deltat;
  while (event_accepted == 0) {
    t_err_ran = ran.Rndm()*0.1;
    fun_ran = P_deltat(t_err_ran);
    dec_accepted = max_fun*ran.Rndm();
    if (fun_ran > dec_accepted) {event_accepted = 1;}
  }
  t_err = t_err_ran;

  // Generation of a Bs or a Bsbar event.
  dec_flavour = ran.Rndm();
  if (dec_flavour < P_trueBs()) {true_ID = 1;} // Bs-like event.
  else {true_ID = -1;} // Bsbar-like event.

  // Determination of the SSK mistag probability.
  dec_SSK_tagged = ran.Rndm();
  if (dec_SSK_tagged < tag_eff_SSK) {
    // If the event is tagged, the accept-reject method is used to generate eta.
    event_accepted = 0;
    max_fun = max_fun_etaSSK;
    while (event_accepted == 0) {
      etamistag_SSK_ran = 0.5*ran.Rndm();
      fun_ran = P_eta_SSK(etamistag_SSK_ran);
      dec_accepted = max_fun*ran.Rndm();
      if (fun_ran > dec_accepted) {event_accepted = 1;}
      }
    etamistag_SSK = etamistag_SSK_ran;
    }
  else {
    // If the event is not tagged, eta is set to 0.5.
    etamistag_SSK = 0.5;
    }

  // Determination of the SSK tagging decision.
  if (etamistag_SSK < 0.5) {
    dec_right_tagged = ran.Rndm();
    if (true_ID == 1) {
      prob_right_tagged = 1.-omega_SSK(etamistag_SSK);
      if (dec_right_tagged < prob_right_tagged) {decision_SSK = 1;} // Right tagged Bs.
      else {decision_SSK = -1;} // Wrong tagged Bs.
      }
    else {
      prob_right_tagged = 1.-omegabar_SSK(etamistag_SSK);
      if (dec_right_tagged < prob_right_tagged) {decision_SSK = -1;} // Right tagged Bsbar.
      else {decision_SSK = 1;} // Wrong tagged Bsbar.
      }
    }
  else {
    decision_SSK = 0;
    }

  // Determination of the OS mistag probability.
  dec_OS_tagged = ran.Rndm();
  if (dec_OS_tagged < tag_eff_OS) {
    // If the event is tagged, the accept-reject method is used to generate eta.
    event_accepted = 0;
    max_fun = max_fun_etaOS;
    while (event_accepted == 0) {
      etamistag_OS_ran = 0.5*ran.Rndm();
      fun_ran = P_eta_OS(etamistag_OS_ran);
      dec_accepted = max_fun*ran.Rndm();
      if (fun_ran > dec_accepted) {event_accepted = 1;}
      }
    etamistag_OS = etamistag_OS_ran;
    }
  else {
    // If the event is not tagged, eta is set to 0.5.
    etamistag_OS = 0.5;
    }

  // Determination of the OS tagging decision.
  if (etamistag_OS < 0.5) {
    dec_right_tagged = ran.Rndm();
    if (true_ID == 1) {
      prob_right_tagged = 1.-omega_OS(etamistag_OS);
      if (dec_right_tagged < prob_right_tagged) {decision_OS = 1;} // Right tagged Bs.
      else {decision_OS = -1;} // Wrong tagged Bs.
      }
    else {
      prob_right_tagged = 1.-omegabar_OS(etamistag_OS);
      if (dec_right_tagged < prob_right_tagged) {decision_OS = -1;} // Right tagged Bsbar.
      else {decision_OS = 1;} // Wrong tagged Bsbar.
      }
    }
  else {
    decision_OS = 0;
    }

  // Determination of the decay observables, using the accept-reject method in 6-D, taking t_err as a conditional variable.
  event_accepted = 0;
  if (true_ID == 1) {max_fun = max_fun_6DBs;}
  else {max_fun = max_fun_6DBsbar;}
  while (event_accepted == 0) {
    Randomize6D(Wide_Window_Gen);
    set_buffer_differential_vars(m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran,t_ran,t_err,0,0,0.5,0.5);
    dec_accepted = max_fun*ran.Rndm();
    if (true_ID == 1) {
      fun_ran = fun_Bs()*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
      }
    else {
      fun_ran = fun_Bsbar()*accGen(t_ran,m1_ran,m2_ran,cos1_ran,cos2_ran,phi_ran);
      }
    if (fun_ran > dec_accepted) {event_accepted = 1;}
    }
  m1 = m1_ran;
  m2 = m2_ran;
  cos1 = cos1_ran;
  cos2 = cos2_ran;
  phi = phi_ran;
  t = t_ran;

  N_accepted += 1;
  if (N_accepted%100 == 0) {cout << N_accepted << " events generated\n";}

  return;

 }
