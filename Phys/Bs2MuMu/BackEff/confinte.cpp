// ============================================================
// Confinte class 
// ============================================================

#include "confinte.h" 
//============================================================
// Constr
confinte::confinte(){
  // Default constructor and initializer
  m_obs_set = "observables" ; 
  m_POI_set = "POI";
  //  m_nbs_input = 0.;
  //  m_nbd_input = 0.;
  m_dir = "";
  m_prefix = "prefix";
  m_in_parallel = false;
  m_useConstr = false; 
  m_n_bin = 100; 
  m_out_file ="";
}

confinte::~confinte(){
}

//============================================================
// Setters

void confinte::setVName(TString bs, TString bd) // Obsolete 
{
  m_s_NBs = bs;
  m_s_NBs = bd;
  
}

void confinte::setWorkspace(TString fileName, TString workspaceName){
  TFile in_file(fileName);
  // use a RooWorkspace to store the pdf models, prior informations, list of parameters,...
  m_ws = (RooWorkspace*)in_file.Get(workspaceName);
  if(!m_ws){
    cerr << "ERROR: Workspace not found" << endl;
    return; 
  }
}

void confinte::setModelConfig(TString modelconfig){
  Info("setModelConfig", "Entering function");
  if(!m_ws){
    Error("setModelConfig","Workspace not set"); 
    exit(-1);
  }
  m_modelConfig = (ModelConfig*) m_ws->obj(modelconfig);
  Info("setModelConfig", " fottiti " );
  if(!m_modelConfig){
    Info("setModelConfig", "No model config in workspace, building it ");
    m_modelConfig = new ModelConfig("myProblem", m_ws);
    if(!m_model){
      Error("setModelConfig","model not set");
      exit(-1);
    }
    Info("setModelConfig", "Building pdf ");
    m_modelConfig->SetPdf(*m_model);
    Info("setModelConfig", "Getting poi and obs ");
    m_modelConfig->SetParametersOfInterest(*m_ws->set(m_POI_set));
    m_modelConfig->SetObservables(*(m_ws->set(m_obs_set)));
    if(m_ws->set("globObs")){
      Info("setModelConfig", "found set of global observables");
      m_modelConfig->SetGlobalObservables(*(m_ws->set("globObs")));
    }else{
      Info("setModelConfig", "NOT found set of global observables");
    }
    if(m_ws->set("nuisance")){
      Info("setModelConfig", "found set of nuisance parameters");
      m_modelConfig->SetNuisanceParameters(*(m_ws->set("nuisance")));
    }else{
      Info("setModelConfig", "NOT found set of nuisance");
    }
    if(m_ws->set("constrVars")){
      Info("setModelConfig", "found set of constraint observables");
      m_modelConfig->SetConstraintParameters(*(m_ws->set("constrVars")));
    }
    
    
    Info("setModelConfig", " fc importing model config " );
    m_ws->import(*m_modelConfig);  
  }
  //m_modelConfig->SetWorkspace(*m_ws);
  m_modelConfig->Print();
}

void confinte::setModel(RooAbsPdf *pdf){
  // Setting the model to be used 
  if(!pdf){
    Error("confinte::setModel", "No PDF found, quitting");
    exit(-1);
  }
  m_model = pdf;
}

    
void confinte::setObs(TString variables, TString obsname){
  // function to change the default observables to look at 
  m_obs_set = obsname;
  m_ws->defineSet(m_obs_set, variables);
  cout << "Setting observables set "<< m_obs_set << " with variables " << variables << endl;
  m_ws->set(m_obs_set)->Print();
}

void confinte::setPOI(TString variables){
  // function to change the default POI to use
  m_POI_set = "myPOI" ;
  m_ws->defineSet(m_POI_set, variables);
  cout << "Setting POI set "<< m_POI_set << " with variables " << variables << endl;
}


void confinte::setData(TString fileName){
  //Reading in the data from an ASCCII file
  cout << "Dataset read in from the ASCCII file: "<<fileName 
       << " observables from workspace " <<endl;
  m_data = RooDataSet::read(fileName,*(m_ws->set(m_obs_set)));
  if(!m_data){
    Error("confinte::setData", "Data not built from ASCII file");
  }
}

void confinte::setData(RooDataSet * dataset){
  if(!dataset){
    Error("confinte::setData","Error dataset provided does not exist");
    return;
  }
  m_data = dataset;
}

void confinte::addRandom(double n_events, TString pdf_name){
  // Function to add a certain number of events from given pdf to the existing dataset 
  //  if(pdf_name.Contains("Bs"))m_nbs_input = n_events;  
  //  if(pdf_name.Contains("Bd"))m_nbd_input = n_events; 
  cout << "debug:  will generate "<< n_events << " from " << pdf_name << endl; 
  RooAbsPdf* pdf_sig = m_ws->pdf(pdf_name); // get the model
  if(!pdf_sig){
    Error("confinte::addRandom","PDF not found");
    return;
  }
  
  cout << "debug:  got pdf "<< pdf_name << endl; 
  // Add some fake signal to data 
  RooDataSet * datasig = 
    pdf_sig->generate(*m_ws->set(m_obs_set), n_events, 
                      Name("mysignal"+pdf_name), Extended()); // add Extended() for poisson fluct
  //pdf_sig->generate(*m_ws->set(m_obs_set), 0, 
  //Name("mysignal"+pdf_name), Extended()); // add Extended() for poisson fluct
  if(!datasig){
    Error("confinte::addRandom","Problems generating the dataset");
  }
  cout << "debug:  generated!"<< endl; 
  m_data->append(*datasig);
  cout << "debug:  appended"<< endl; 
}


//============================================================
// Methods to get the Feldman Cousins interval 

PointSetInterval *confinte::FC_interval(double testSize){
  cout << " ====== Feldman & Cousins construction ========" << endl;
  // Feldman Cousins
  if(! m_ws ) {
    cerr << "ERROR: workspace not set... " << endl;
    exit(-1);
  }
  m_ws->Print();
  if(!m_modelConfig){
    Error("FC_interval", "Model Config not set ");
    exit(-1);
  }
  cout<< " model config" << endl;
  //  m_modelConfig->Print();
  
  cout << " === Stating  FC === " << endl;
 
  m_fc = new RooStats::FeldmanCousins(*m_data, *m_modelConfig);
  m_fc->SetTestSize(testSize); // set size of test
  // Next: file name is hard coded in roostat
  // the name is: "SamplingDistributions.root"

  m_fc->SaveBeltToFile(false);
  
  //  m_fc->UseAdaptiveSampling(true);
  m_fc->FluctuateNumDataEntries(false); 
  // number counting analysis: dataset always has 1 entry with N events observed

  m_fc->CreateConfBelt(true);
  //  m_fc->AdditionalNToysFactor(0.5);// WARNING!!!!!
  cout << " FC : set points to test" << endl;
  
  // Set number of points to test per parameter
  m_fc->SetNBins(m_n_bin); 

  // Specify points to test, otherwise fixed grid will be built 
  if(m_points_histo ) m_fc->SetPOIPointsToTest(*m_points_histo);

  // Configure ToyMCSampler for the given test statistics   
  ToyMCSampler*  toymcsampler = (ToyMCSampler*) m_fc->GetTestStatSampler();
  if(m_modelConfig->GetGlobalObservables()){
    cout << "will use global observables for unconditional ensemble"<<endl;
    m_modelConfig->GetGlobalObservables()->Print();
    toymcsampler->SetGlobalObservables(*m_modelConfig->GetGlobalObservables());
  }

  // Set parallel computing 
  if (m_in_parallel){
    ProofConfig pc(*m_ws, 4, "workers=4",false); 
    Info("confinte::FC_interval","Setting parallel running");
    toymcsampler->SetProofConfig(&pc);	// enable proof
  }
      
  // use the Feldman-Cousins tool
  cout << " Get interval " << endl; 
  m_interval = (PointSetInterval*)m_fc->GetInterval();

  return m_interval; 
}


void confinte::plotFC(PointSetInterval *interval, TString parameter){
  // Macro to plot FC results... not complete
  // make a canvas for plots
  RooRealVar *s = m_ws->var(parameter);  
  std::cout << "interval is ["<<  
    interval->LowerLimit(*s)  << ", "  <<
    interval->UpperLimit(*s) << "]" << endl;
    
  cout << " Starting parameter scan " << endl;
  RooDataHist* parameterScan = (RooDataHist*) m_fc->GetPointsToScan();
  TH1F* hist = (TH1F*) parameterScan->createHistogram(parameter,100);
  hist->Draw();
      
      
  RooArgSet* tmpPoint;
  // loop over points to test
  cout << " loop over test points " << endl;
  for(Int_t i=0; i<parameterScan->numEntries(); ++i){
    //    cout << "on parameter point " << i << " out of " << parameterScan->numEntries() << endl;
    // get a parameter point from the list of points to test.
    tmpPoint = (RooArgSet*) parameterScan->get(i)->clone("temp");
	
    //cout << " Adding marker " << endl;
    TMarker* mark = new TMarker(tmpPoint->getRealValue(parameter), 1, 25);
    if (interval->IsInInterval( *tmpPoint ) ) 
      mark->SetMarkerColor(kBlue);
    else
      mark->SetMarkerColor(kRed);
	
    mark->Draw("s");
    //delete tmpPoint;
    //    delete mark;
  }
}

void confinte::plotFC2D(){
  // Macro to plot FC results in case of 2 POI... not complete
  cout << " Starting parameter scan " << endl;
  if(!m_interval){
    Error("confinte::plotFC2D", "Interval no found, not going to plot anything");
    return;

  }
  RooDataHist* parameterScan = (RooDataHist*) m_fc->GetPointsToScan();
  

  TIterator* iter =m_ws->set(m_POI_set)->createIterator();
  RooRealVar* first_poi  = (RooRealVar*)iter->Next();
  RooRealVar* second_poi = (RooRealVar*)iter->Next();
  TCanvas * cm = new TCanvas("2d", "2d");
  TString name = first_poi->GetName(); name+= ","; name+=second_poi->GetName();
  cout << "DEBUG: histogram for " << name << endl;
  TH2D* hist = (TH2D*) parameterScan->createHistogram(name,100,100);  
  hist->Draw();
  RooArgSet* tmpPoint;
  // loop over points to test
  for(Int_t i=0; i<parameterScan->numEntries(); ++i){
    //    cout << "on parameter point " << i << " out of " << parameterScan->numEntries() << endl;
    // get a parameter point from the list of points to test.
    tmpPoint = (RooArgSet*) parameterScan->get(i)->clone("temp");

    cout << " Adding marker " << endl;
    TMarker* mark = new TMarker(tmpPoint->getRealValue(first_poi->GetName()), 
				tmpPoint->getRealValue(second_poi->GetName()), 25);
    if (m_interval->IsInInterval( *tmpPoint ) ) 
      mark->SetMarkerColor(kBlue);
    else
      mark->SetMarkerColor(kRed);
    
    mark->Draw("s");
    //delete tmpPoint;
    //    delete mark;
  }
  cm->SaveAs(m_dir+"plots/"+m_prefix+"_2Dhisto.pdf");

}



//============================================================
// Methods to use the CLs limit calculator 
HypoTestInverterResult *confinte::CLs_interval(){
  // to be worked out... 
  ModelConfig *bModel = new ModelConfig("bModel", m_ws);
  bModel->SetPdf(*m_ws->pdf("simBkgPdf"));
  bModel->SetParametersOfInterest(*m_ws->set(m_POI_set));
  bModel->SetObservables(*(m_ws->set(m_obs_set)));
  bModel->Print();
  ModelConfig *sbModel = new ModelConfig("bModel", m_ws);
  sbModel->SetPdf( *m_ws->pdf("simPdf"));
  sbModel->SetParametersOfInterest(*m_ws->set(m_POI_set));
  sbModel->SetObservables(*(m_ws->set(m_obs_set)));
  sbModel->Print();
   if (!sbModel) {
      Error("StandardHypoTestDemo","Not existing ModelConfig ");
      return 0;
   }
   // check the model 
   if (!sbModel->GetPdf()) { 
      Error("StandardHypoTestDemo","Model has no pdf ");
      return 0;
   }
   if (!sbModel->GetParametersOfInterest()) {
      Error("StandardHypoTestDemo","Model  has no poi ");
      return 0;
   }
   if (!sbModel->GetObservables()) {
      Error("StandardHypoTestInvDemo","Model  has no observables ");
      return 0;
   }
   if (!sbModel->GetSnapshot() ) { 
      Info("StandardHypoTestInvDemo","Model  has no snapshot  - make one using model poi");
      sbModel->SetSnapshot( *sbModel->GetParametersOfInterest() );
   }
   if (!bModel->GetSnapshot() ) { 
     Info("StandardHypoTestInvDemo","Model  has no snapshot  - make one using model poi and 0 values ");
     RooRealVar * var = dynamic_cast<RooRealVar*>(bModel->GetParametersOfInterest()->first());
     cout << "bella lì" << endl;
     if (var) { 
       double oldval = var->getVal();
       var->setVal(0);
       bModel->SetSnapshot( RooArgSet(*var)  );
       var->setVal(oldval);
     }
     else { 
       Error("StandardHypoTestInvDemo","Model has no valid poi");
       return 0;
     } 
   }        
   cout << ">>  CLs debug: Start" << endl;
   
  SimpleLikelihoodRatioTestStat * testStat = 
    new SimpleLikelihoodRatioTestStat(*sbModel->GetPdf(), *bModel->GetPdf());
  RooArgSet nullParams(*sbModel->GetSnapshot());
  if (sbModel->GetNuisanceParameters()) nullParams.add(*sbModel->GetNuisanceParameters());
  if (sbModel->GetSnapshot()) testStat->SetNullParameters(nullParams);
  RooArgSet altParams(*bModel->GetSnapshot());
  if (bModel->GetNuisanceParameters()) altParams.add(*bModel->GetNuisanceParameters());
  if (bModel->GetSnapshot()) testStat->SetAltParameters(altParams);


  cout << ">>  CLs debug: HybridCalculator" << endl;

  HybridCalculator * hypoCalc = new HybridCalculator(*m_data, *bModel, *sbModel);
  bModel->SetGlobalObservables(RooArgSet() );
  sbModel->SetGlobalObservables(RooArgSet() );
  hypoCalc->SetToys(100, 100);

  // fix for using multigen (does not work in this case)
  //toymcs->SetUseMultiGen(false);
  RooAbsPdf * nuisPdf = 0; 
  ToyMCSampler::SetAlwaysUseMultiGen(false);
  if (bModel->GetPdf() && bModel->GetObservables() ) 
    nuisPdf = RooStats::MakeNuisancePdf(*bModel,"nuisancePdf_bmodel");
  else 
    nuisPdf = RooStats::MakeNuisancePdf(*sbModel,"nuisancePdf_sbmodel");
  if (!nuisPdf ) {
    if (bModel->GetPriorPdf())  { 
      nuisPdf = bModel->GetPriorPdf();
      Info("StandardHypoTestInvDemo",
           "No nuisance pdf given - try to use %s that is defined as a prior pdf in the B model",
           nuisPdf->GetName());            
    }
    else { 
      Error("StandardHypoTestInvDemo",
            "Cannnot run Hybrid calculator because\
 no prior on the nuisance parameter is specified or can be derived");
      return 0;
    }
  }

  hypoCalc->ForcePriorNuisanceAlt(*nuisPdf);
  hypoCalc->ForcePriorNuisanceNull(*nuisPdf);


  cout << ">>  CLs debug: ToyMCSampler " << endl;
  ToyMCSampler * sampler = (ToyMCSampler *)hypoCalc->GetTestStatSampler();
  sampler->SetNEventsPerToy(0); 
  sampler->SetTestStatistic(testStat); 
  sampler->SetUseMultiGen(false);
  ToyMCSampler::SetAlwaysUseMultiGen(false);
      
  cout << ">>  CLs debug: HypoTestInverter" << endl;
  HypoTestInverter calc(*hypoCalc);
  calc.SetConfidenceLevel(0.95);
  calc.UseCLs(true);
  calc.SetVerbose(true);
  cout << ">>  CLs debug: getinterval " << endl;
  HypoTestInverterResult * r = calc.GetInterval();
  return r; 
}


//============================================================
// Methods to use the Profile Likelihood calculator
ConfInterval *confinte::PL_interval(double testSize){
  // .........
  cout << " Calculate interval " << endl;
  // Calculate limit 
  ProfileLikelihoodCalculator plc(*m_data, *m_model, *m_ws->set(m_POI_set)); //  CL = 0.05 by default
  plc.SetTestSize(testSize);
  ConfInterval* lrint = plc.GetInterval();  // that was easy.
  cout << "Profile likelihood interval calculated " << endl;

  return lrint; 
}

void confinte::plotPL(ConfInterval *lrint){
  LikelihoodIntervalPlot plotInt((LikelihoodInterval*)lrint);
  plotInt.SetTitle("Profile Likelihood Ratio and Posterior for S");
  plotInt.Draw();
}

//============================================================
// Simple fit of the model to the data
RooFitResult*  confinte::fitData(){
  
  if(m_useConstr) { // Do we use constraints? 
    if(!(RooArgSet*)m_ws->set("constraints")){
      cerr << "ERROR no constraints present" << endl;
      exit(-1);
    }
    cout << "about to fit with constraints " << endl;
    return m_model->fitTo(*m_data, Minos(kTRUE),
                          Verbose(kFALSE), Constrained(), 
                          Extended(kTRUE), 
                          ExternalConstraints(*(RooArgSet*)m_ws->set("constraints")));
  }
  else   return m_model->fitTo(*m_data, Minos(kTRUE),Verbose(kFALSE), Constrained(), Extended(kTRUE));
}

// Plot function, quick and dirty for bsmumu case 
void confinte::plot(TString prefix){
  TCanvas * cm = new TCanvas("cm", "cm");
  cout << "plot stuff " << endl;
  TIterator* iter =m_ws->set(m_obs_set)->createIterator();
  
  RooRealVar* first_obs = (RooRealVar*)iter->Next();
  RooPlot* plot = first_obs->frame();
  m_data->plotOn(plot);
  m_model->plotOn(plot);
  m_model->plotOn(plot, Components("*sig*"),
                  LineColor(kRed), Name("Sig"));
  m_model->plotOn(plot, Components("*misid*"),
                  LineColor(kGreen), Name("Mis-ID"));
  plot->SetMinimum(0.01);
  plot->Draw();
  //gPad->SetLogy();
  
  cm->SaveAs(prefix+"_mass.pdf");
  if (m_ws->set(m_obs_set)->getSize()>1){
    TCanvas * cb = new TCanvas("cb", "cb");
    RooRealVar* second_obs = (RooRealVar*)iter->Next();
    //    RooRealVar* second_obs = (RooRealVar*) m_ws->set(m_obs_set)->second();
    RooPlot* plotb = second_obs->frame();
    m_data->plotOn(plot);
    m_model->plotOn(plot);
    m_data->plotOn(plotb);
    m_model->plotOn(plotb);
    //   m_model->plotOn(plotb, Components("pdf_Bs_sig"),
    //                   LineColor(kRed), Name("Bs"));
    //   m_model->plotOn(plotb, Components("pdf_Bd_sig"),
    //                   LineColor(kGreen), Name("Bd"));
    plotb->SetMinimum(0.01);
    
    plotb->Draw();
    gPad->SetLogy();
    cb->SaveAs(prefix+"_bdt.pdf");
  }
  

}

//============================================================
// Methods to save information 
// Obsolete 
TTree* confinte::getTree(){
  TTree *t = new TTree("fitres","fitres");
  double nbsfit, nbsfiterr,nbdfit, nbdfiterr;
  double Bs_low_lim(0.), Bs_up_lim(0.); 
  double Bd_low_lim(0.), Bd_up_lim(0.); 
  t->Branch("N_Bs_in", &m_nbs_input, "N_Bs_in/D");
  t->Branch("N_Bs_fit", &nbsfit, "N_Bs_fit/D");
  t->Branch("N_Bs_fit_err", &nbsfiterr, "N_Bs_fit_err/D");
  t->Branch("N_Bd_in", &m_nbd_input, "N_Bd_in/D");
  t->Branch("N_Bd_fit", &nbdfit, "N_Bd_fit/D");
  t->Branch("N_Bd_fit_err", &nbdfiterr, "N_Bd_fit_err/D");
  t->Branch("Bs_low_lim", &Bs_low_lim, "Bs_low_lim/D");
  t->Branch("Bs_up_lim", &Bs_up_lim, "Bs_up_lim/D");
  t->Branch("Bd_low_lim", &Bd_low_lim, "Bd_low_lim/D");
  t->Branch("Bd_up_lim", &Bd_up_lim, "Bd_up_lim/D");
  if(m_interval){
    RooRealVar  *vnbs = m_ws->var(m_s_NBs);
    RooRealVar  *vnbd = m_ws->var(m_s_NBd);
    Bs_low_lim = m_interval->LowerLimit(*vnbs);
    Bs_up_lim  = m_interval->UpperLimit(*vnbs);
    Bd_low_lim = m_interval->LowerLimit(*vnbd);
    Bd_up_lim  = m_interval->UpperLimit(*vnbd);
    
  }
  
  nbsfit = m_ws->var(m_s_NBs)->getVal();
  nbdfit = m_ws->var(m_s_NBd)->getVal();
  nbsfiterr = m_ws->var(m_s_NBs)->getError();
  nbdfiterr = m_ws->var(m_s_NBd)->getError();
  cout << " Filling tree " << endl;
  t->Fill();
  cout << " Savint tree " << endl;
  //t->SaveAs(m_dir+"rootfiles/"+m_prefix+"_tree.root");
  return t;
   
}


void confinte::saveInterval(){
  // Method to save the interval information 
  cout << " Going to save interval" << endl;
  if (!m_interval) {
    cout << "ERROR:Confidence interval not found" << endl;
    exit(-1);
  }else{
    TString name = m_dir+"rootfiles/"+m_prefix+"_interval.root";
    cout << m_dir << m_prefix << endl;
    cout << "OK: Wil save Confidence interval in " << name << endl;
    m_interval->SaveAs(name);
  }
}


void confinte::saveBelt(){
  // Method to save the confidence "belt"
  cout << " Going to save belt" << endl;
  ConfidenceBelt* confbelt = (ConfidenceBelt*)m_fc->GetConfidenceBelt();
  if (!confbelt) {
    cout << "ERROR:Confidence belt not created" << endl;
    exit(-1);
  }else{
    TString _name = m_dir+"rootfiles/"+m_prefix+"_belt.root";
    cout << "OK: Will save Confidence belt in " << _name << endl;
    confbelt->SaveAs(_name);
  }
}




void confinte::saveInfo(){
  TString name = m_dir+"rootfiles/"+m_prefix+"_fc.root";
  TFile *f = TFile::Open(name, "RECREATE");
  RooDataSet* parameterScan = (RooDataSet*) m_fc->GetPointsToScan();
  parameterScan->Write();
  m_interval->Write();
  TTree *infoTree = getTree();
  infoTree->Write();
  
  ConfidenceBelt* confbelt = (ConfidenceBelt*)m_fc->GetConfidenceBelt();
  confbelt->Write();
  f->Close();
}

// ============================================================
//
// Feldman & Cousins by hand... 
// 
void confinte::FeldmanCousinsInt(int nth_point, int n_points){
  Info("FeldmanCousinsInf","Starting from scratch");
  // Check parameters: 
  if(nth_point!= -1){
    if(nth_point<0) {
      Error("FedlmandCousinsInt","nth_point cannot be negative");
      exit(-1);
    }
    if(n_points<1) {
      Error("FedlmandCousinsInt","n_points cannot be less then 1");
      exit(-1);
    }
  }
  if(!m_ws){
    Error("FedlmandCousinsInt"," workspace not set");
    exit(-1);
  }
  
  
  const char * modelSBName = "myProblem";
  const char * modelBName = "";
  if(!m_modelConfig)setModelConfig(modelSBName);
  
  ModelConfig* bModel = (ModelConfig*) m_ws->obj(modelBName);
  ModelConfig* sbModel = m_modelConfig; //(ModelConfig*) m_ws->obj(modelSBName);
  sbModel->Print();
  
  
   if (!sbModel) {
      Error("FeldmanCousinsInf","Not existing ModelConfig %s",modelSBName);
      m_ws->Print();
      return;
   }
   // check the model 
   if (!sbModel->GetPdf()) { 
      Error("FeldmanCousinsInf","Model %s has no pdf ",modelSBName);
      m_ws->Print();
      return;
   }
   if (!sbModel->GetParametersOfInterest() || sbModel->GetParametersOfInterest()->getSize() == 0) {
      Error("FeldmanCousinsInf","Model %s has no poi ",modelSBName);
      m_ws->Print();
      return;
   }
   if (!sbModel->GetObservables() || sbModel->GetObservables()->getSize() == 0) {
      Error("FeldmanCousinsInt","Model %s has no observables ",modelSBName);
      m_ws->Print();
      return;
   }
   // assume exists only one parameter of interest
   TIterator* iter = (TIterator *) sbModel->GetParametersOfInterest()->createIterator();
   const Int_t npoi = sbModel->GetParametersOfInterest()->getSize();
   RooRealVar* poi  = (RooRealVar*)iter->Next();

   if (!sbModel->GetSnapshot() ) { 
      Info("StandardHypoTestInvDemo",
           "Model %s has no snapshot  - make one using model poi",modelSBName);
      sbModel->SetSnapshot( *poi );
   }
    
   if (!bModel || bModel == sbModel) { 
     // This is not generalized to Npois>1
      Info("StandardHypoTestInvDemo","The background model %s does not exist",modelBName);
      Info("StandardHypoTestInvDemo","Copy it from ModelConfig %s and set POI to zero",modelSBName);
      bModel = (ModelConfig*) sbModel->Clone();
      bModel->SetName(TString(modelSBName)+TString("_with_poi_0"));      
      double oldval = poi->getVal();
      poi->setVal(0);
      bModel->SetSnapshot( *poi  );
      poi->setVal(oldval);
   }


    
   // Set calculator type 
  FrequentistCalculator *  fc  = new FrequentistCalculator(*m_data, *bModel, *sbModel);
  fc->SetToys(300,0);    // 1000 for null (S+B) , 50 for alt (B)
  //  fc->SetNToysInTails(10,10);    // 1000 for null (S+B) , 50 for alt (B)
  
  // configure  ToyMCSampler to get test statistics distribution 
  ToyMCSampler *toymcs = (ToyMCSampler*)fc->GetTestStatSampler();
  // for number counting (otherwise need to use extended pdf)
  toymcs->SetNEventsPerToy(0); // this means fluctuate according to Poisson 

  
  
  // Systematics treatment through global observables: i.e. auxiliary measurements. 
  // Global observables are fluctuated (not randomized) during the test statistics
  // ensamble construction
  
  if(sbModel->GetGlobalObservables()){
    cout << "will use global observables for unconditional ensemble"<<endl;
    sbModel->GetGlobalObservables()->Print();
    toymcs->SetGlobalObservables(*sbModel->GetGlobalObservables());
  }
//   if(sbModel->GetNuisanceParameters()){
//     //    cout << "will use global observables for unconditional ensemble"<<endl;
//     sbModel->GetNuisanceGlobalObservables()->Print();
//     toymcs->SetGlobalObservables(*sbModel->GetGlobalObservables());
//   }
  
  // profile likelihood test statistics 
  ProfileLikelihoodTestStat profll(*sbModel->GetPdf());
  
  // set the test statistic to use 
  toymcs->SetTestStatistic(&profll);
  m_toymcs = new ToyMCSampler(*toymcs);
  Info("FeldmanCousinsInt","Everything set");
  // control message 
  // Maybe put back for performance
  //RooMsgService::instance().getStream(1).removeTopic(RooFit::NumIntegration);
  // suppress info and progress messages
  //RooMsgService::instance().setGlobalKillBelow(RooFit::WARNING) ;
  
  
  //calc.SetFixedScan(npoints,poimin,poimax);
  
  cout << " first try " << endl;
  iter->Reset();
  
  int *npoints = new int[npoi];
  double step[npoi], poimin[npoi], poimax[npoi];
  for(Int_t i=0; i<npoi; i++){
    npoints[i] = m_n_bin;
    RooRealVar* poi  = (RooRealVar*)iter->Next();
    poimin[i] = poi->getMin();
    poimax[i] = poi->getMax();
    step[i] = (poimax[i] - poimin[i]) / npoints[i];
    
  }
  
  
  // Setup the histos 
  TH1D * h_cl = new TH1D("hcl", "hcl", npoints[0], poimin[0], poimax[0]);
  TH2D * h_cl2D; 
  RooRealVar * second_poi; 
  if(npoi==2 ){
    h_cl2D  = new TH2D("h_cl2D","h_c2D", npoints[0], poimin[0], poimax[0], 
                       npoints[1], poimin[1], poimax[1]);
    iter->Reset();
    iter->Next();
    second_poi = (RooRealVar*)iter->Next();// this is really a stupid way to get the second element...
  }

  Info("FeldmanCousinsInf","Starting the parameter scan");
  CreateParameterPoints();


  // Create dataset for points in interval (we will add the confidence level here) 
  RooDataSet* pointsInInterval = new RooDataSet("pointsInInterval", 
                                                "points in interval", 
                                                *(m_pointsToTest->get(0)) );
  RooRealVar *conf_level = new RooRealVar("cl","cl",0,1);
  pointsInInterval->addColumn(*conf_level);
  
  
  
  RooArgSet* point; 
  RooArgSet* thispoi = new RooArgSet(*sbModel->GetParametersOfInterest());
  cout << " Points to test " << m_pointsToTest->numEntries() << endl;
  
  for(Int_t i=0; i<m_pointsToTest->numEntries(); ++i){
    cout << " test point " << i <<  " " << nth_point << " " << n_points << endl;
    
    // test the nth_point and the n_points subsequent ones 
    ///if(nth_point!=-1 && (i<nth_point || i>=nth_point+ n_points))continue; 
    // get a parameter point from the list of points to test.
    point = (RooArgSet*) m_pointsToTest->get(i);
    *thispoi = *point;
    const_cast<ModelConfig*>(sbModel)->SetSnapshot(*thispoi);

    //============================================================
    // CORE 
    
    HypoTestResult *  hcResult = fc->GetHypoTest();
    debugSampling(thispoi);

    hcResult->SetBackgroundAsAlt(true);
    double clsplusb =  hcResult->CLsplusb();
    //============================================================

    cout << " point " << i << " first poi " << poi->getVal()  <<  " CL " << clsplusb << endl;
    cout << " poi range " << poi->GetName() << " " << poi->getMin()  << " " << poi->getMax() << endl;
    // print value of global observables 
    Info("FeldmanCousinsInt", "Global Observables");
    if(sbModel->GetGlobalObservables()){
      TIterator* globiter = (TIterator *)sbModel->GetGlobalObservables()->createIterator();
      const int nglob = sbModel->GetGlobalObservables()->getSize();
      for(int ig=0;ig<nglob;ig++){
        RooRealVar * thisglob = (RooRealVar*)globiter->Next();
        thisglob->Print();
      }
    }else{
      Info("...", "NO Global Observables");
    }
    
    
    

    
    // Fill some output 
    if(npoi ==1 ){
      h_cl->Fill(poi->getVal(), clsplusb); 
    }else if(npoi ==2){
      h_cl2D->Fill(poi->getVal(), second_poi->getVal(), clsplusb); 
    }
    conf_level->setVal(clsplusb);
    pointsInInterval->add(RooArgSet(*point, *conf_level));
    Info("FeldmanCousinsInt", "Printing some debug info");
    // Some debug information
    TIter      itr = point->createIterator();
    RooRealVar* myarg;
    cout  << " ";
    while ((myarg = (RooRealVar *)itr.Next())) { 
      cout  << myarg->GetName() << "=" << myarg->getVal() << " ";
    }
    cout << endl;
  }
  
  // Save some output, for npoi=1 or 2 save also histogram 
  if(npoi ==1 ){
    h_cl->SaveAs("mycl.root");
  }else if(npoi ==2){
    h_cl2D->SaveAs("mycl.root");
  }
  TString suffix = ""; 
  if(nth_point !=-1){
    suffix += "n"; suffix+=nth_point; 
    suffix += "_"; suffix+=(nth_point+n_points); 
  }
  if(m_out_file != "")
    pointsInInterval->SaveAs(m_out_file);
  else 
    pointsInInterval->SaveAs("myConfInterval"+suffix+".root");

  
  
}// end of feldman cousins by hand


// ============================================================
// Copy-paste from RooStats::FeldmanCousins class
void confinte::CreateParameterPoints() const{
  // specify the parameter points to perform the construction.
  // allow ability to profile on some nuisance paramters
  if(!m_modelConfig){
    Error("CreateParameterPoints", "No ModelConfig set " );
    return;
  }
  m_modelConfig->GuessObsAndNuisance(*m_data);

  // get ingredients
  RooAbsPdf* pdf   = m_modelConfig->GetPdf(); 
  if (!pdf ){
    Error("CreateParameterPoints","No PDF found");
    return;
  }

  // get list of all paramters
  RooArgSet* parameters = new RooArgSet(*m_modelConfig->GetParametersOfInterest());
  if(m_modelConfig->GetNuisanceParameters()){
    parameters->add(*m_modelConfig->GetNuisanceParameters());
    Info("CreateParameterPoints", "Getting nuisance parameters");
  }else{
    Info("CreateParameterPoints", "NOT Getting nuisance parameters");
  }
  
  bool fDoProfileConstruction = true;
  
  if( m_modelConfig->GetNuisanceParameters() && 
      ! m_modelConfig->GetParametersOfInterest()->equals(*parameters) && 
      fDoProfileConstruction) {
    // if parameters include nuisance parameters, do profile construction
    Info("CreateParameterPoints","Doing profile construction " );
    
    // set nbins for the POI
    TIter it2 = m_modelConfig->GetParametersOfInterest()->createIterator();
    RooRealVar *myarg2; 
    while ((myarg2 = dynamic_cast<RooRealVar*>(it2.Next()))) { 
      myarg2->setBins(m_n_bin);
    }
    
    // get dataset for POI scan
    //     RooDataHist* parameterScan = NULL;
    RooAbsData* parameterScan = NULL;
    if(m_points_histo){
      Info("CreateParameterPoints", "Points to scan from histo ");
      parameterScan = m_points_histo;
    }else{
      Info("CreateParameterPoints", "Points to scan from variables ");
      parameterScan = new RooDataHist("parameterScan", "", 
                                      *m_modelConfig->GetParametersOfInterest());
    }
    


    //    ooccoutP(m_modelConfig,CreateParameterPoints) 
    //<< "FeldmanCousins: # points to test = " << parameterScan->numEntries() << endl;
    // make profile construction
    RooFit::MsgLevel previous  = RooMsgService::instance().globalKillBelow();
    RooMsgService::instance().setGlobalKillBelow(RooFit::FATAL) ;
    RooAbsReal* nll = pdf->createNLL(*m_data,RooFit::CloneData(false));
    RooAbsReal* profile = nll->createProfile(*m_modelConfig->GetParametersOfInterest());
    
    RooDataSet* profileConstructionPoints = new RooDataSet("profileConstruction",
							   "profileConstruction",
							   *parameters);
    
    Info("CreateParameterPoints", "Number of entries to scan: %i ", parameterScan->numEntries());
    for(Int_t i=0; i<parameterScan->numEntries(); ++i){
      cout << "profile construction  " <<i << endl;
      
      // here's where we figure out the profiled value of nuisance parameters
      *parameters = *parameterScan->get(i);
      profile->getVal(); // here it fits... 
      profileConstructionPoints->add(*parameters);
    }   
    RooMsgService::instance().setGlobalKillBelow(previous) ;
    delete profile; 
    delete nll;
    //if(!fPOIToTest) delete parameterScan;

    // done
    m_pointsToTest = profileConstructionPoints;

  } else{
    // Do full construction
    //    ooccoutP(m_modelConfig,CreateParameterPoints) 
    //<< "FeldmanCousins: Model has no nuisance parameters" << endl;
    Info("CreateParameterPoints","Doing full construction " );
    TIter it = parameters->createIterator();
    RooRealVar *myarg; 
    while ((myarg = dynamic_cast<RooRealVar*>(it.Next()))) { 
      myarg->setBins(m_n_bin);
    }

    RooDataHist* parameterScan = new RooDataHist("parameterScan", "", *parameters);
    //ooccoutP(m_modelConfig,CreateParameterPoints) 
    //<< "FeldmanCousins: # points to test = " << parameterScan->numEntries() << endl;
    
    m_pointsToTest = parameterScan;
  }
  
  delete parameters;
  
}


// ============================================================
// ============================================================
// ============================================================


// Generate data (given model config and input parameters ) 
RooAbsData *confinte::generateData(RooArgSet *pointToTest){

  RooAbsData* data = m_toymcs->GenerateToyData(*pointToTest);
  // TODO: save this toys if needed 

  return data;
}



// ============================================================

void confinte::debugSampling(RooArgSet *pointToTest){
  Info("debugSampling", "getSampling distribution");
  if(!m_toymcs){
    Error("debugSampling", "toymcs not set " );
    return;
    
  }
  
  RooAbsData * data = m_toymcs->GetSamplingDistributions(*pointToTest);

  
  data->Print();
}






