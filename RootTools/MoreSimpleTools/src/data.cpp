#include "data.h"

//ClassImp(data)

data::data():
  m_s_weights(0),
  m_b_weights(0),
  m_s_file_names(0),
  m_b_file_names(0),
  m_s_tuple_names(0),
  m_b_tuple_names(0),
  m_s_user_names(0),
  m_b_user_names(0),
  m_s_files(0),
  m_b_files(0),
  m_s_tuples(0),
  m_b_tuples(0),
  Bstr("B"),
  Sstr("S"),
  Estr("E"),
  Rstr("R"),
  Cstr("#"),
  delimiters(" \t\n;"),
  eventColumn(""),
  runColumn(""),
  m_prepared(false),
  m_weightBranch(false)
{
}

data::data(const std::string& weightListName):
  m_s_weights(0),
  m_b_weights(0),
  m_s_file_names(0),
  m_b_file_names(0),
  m_s_tuple_names(0),
  m_b_tuple_names(0),
  m_s_user_names(0),
  m_b_user_names(0),
  m_s_files(0),
  m_b_files(0),
  m_s_tuples(0),
  m_b_tuples(0),
  Bstr("B"),
  Sstr("S"),
  Estr("E"),
  Rstr("R"),
  Cstr("#"),
  delimiters(" \t\n;"),
  eventColumn(""),
  runColumn(""),
  m_prepared(false),
  m_weightBranch(false)
{
  readWeightFile(weightListName);
  loadTuples();
  //std::cout << "Initialised with eventColumn=" << eventColumn << " runColumn=" << runColumn << std::endl;
  
}

data::~data()
{
  
  for(UInt_t i = 0; i<m_s_files.size(); i++)
  {
    m_s_files[i]->Close();
  }

  for(UInt_t j = 0; j<m_b_files.size(); j++)
  {
    m_b_files[j]->Close();
  }
}

bool data::readWeightFile(const std::string& weightListName)
{
  
  m_prepared=false;
  std::ifstream fileStream2;
  std::string lineread;
  TString line;
  UInt_t nlines =0;
  TString word;
  
  fileStream2.open(weightListName.c_str());
  if (!fileStream2)
  {
    std::cout << "Error in opening weightfile" << std::endl;
    return EXIT_FAILURE;
  }
  
  int bnum = 0;
  int snum = 0; 
  //int nlines = 0;
  while(!line.ReadLine(fileStream2).eof())
  {
    nlines++;
    TObjArray* Strings = line.Tokenize(delimiters);
    TIter iString(Strings);
    TObjString* os=0;
    os=(TObjString*)iString(); //signal or background
    word = os->GetString();
    if(word == Bstr)
    {
      os=(TObjString*)iString(); //Username
      m_b_user_names.push_back(os->GetString());
      os=(TObjString*)iString(); //Filename
      m_b_file_names.push_back(os->GetString());
      os=(TObjString*)iString(); //Ntuplename
      m_b_tuple_names.push_back(os->GetString());
      os=(TObjString*)iString(); //Weight
      m_b_weights.push_back(atof(os->GetString()));
      bnum++;
    }
    else if(word == Sstr)
    {
      os=(TObjString*)iString(); //Username
      m_s_user_names.push_back(os->GetString());
      os=(TObjString*)iString(); //Filename
      m_s_file_names.push_back(os->GetString());
      os=(TObjString*)iString(); //Ntuplename
      m_s_tuple_names.push_back(os->GetString());
      os=(TObjString*)iString(); //Weight
      m_s_weights.push_back(atof(os->GetString()));
    }
    else if(word == Estr)
    {
      //Event number
      os=(TObjString*)iString();
      eventColumn=os->GetString();
	  
    }
    else if(word == Rstr)
    {
      //Run number
      os=(TObjString*)iString();
      runColumn=os->GetString();
	  
    }
    else if(word.BeginsWith(Cstr))
    {
    }
    else
    {
      cout << "Error in parsing weightfile" << endl;
      return EXIT_FAILURE;
    }
  }

  
  
  fileStream2.close();
  /*try
    {
    bintuple.resize(bnum);
    sintuple.resize(snum);
    bintuplecut.resize(bnum);
    sintuplecut.resize(snum);
    sinFile.resize(snum);
    binFile.resize(bnum);
    spreinit.resize(snum);
    dspreinit.resize(snum);
    bpreinit.resize(bnum);
    dbpreinit.resize(bnum);
    sinit.resize(snum);
    dsinit.resize(snum);
    binit.resize(bnum);
    dbinit.resize(bnum);
    }
  
    catch (bad_alloc& xa) 
    { // Catch block, for exceptions
    cerr << "An exception occurred: " << xa.what() << "\n";
    return 0;
    } // End of catch block
  */
  return (bnum>0 && snum>0 && m_b_file_names.size()==m_b_tuple_names.size() &&  m_s_file_names.size()==m_s_tuple_names.size()
          && m_b_user_names.size()==m_b_file_names.size() &&  m_s_user_names.size()==m_s_file_names.size() );
  
}

bool data::loadTuples(void)
{
  if(m_s_file_names.size()==0 || m_b_file_names.size()==0 || m_s_file_names.size()!=m_s_tuple_names.size() || m_b_file_names.size()!=m_b_tuple_names.size() )
  {
    std::cout << "No files to load or badly parsed input file" << std::endl;
    return false;
  }
  
  
  for(UInt_t i = 0; i<m_s_file_names.size(); i++)
  {
    m_s_files.push_back(TFile::Open(m_s_file_names[i]));
    m_s_tuples.push_back( (TTree*)m_s_files[i]->Get(m_s_tuple_names[i]) );
  }

  for(UInt_t j = 0; j<m_b_file_names.size(); j++)
  {
    m_b_files.push_back(TFile::Open(m_b_file_names[j]));
    m_b_tuples.push_back( (TTree*)m_b_files[j]->Get(m_b_tuple_names[j]) );
  }
  fillEventVector();
  m_prepared=true;

  return true;
  
}

//bool data::entries(TString & cut, std::vector<int> & s, std::vector<int> b, std::vector<double>& sw, std::vector<double> & bw );
bool data::entries(TString & cut, cutresult & output)
{
  //std::cout<< "in entries with output only" <<std::endl;
  if(!m_prepared) return false;
  
  output.clear();
  
  for(UInt_t i = 0; i<m_s_tuples.size(); i++)
	{
	  m_s_tuples[i]->Draw(">>elist_s",cut,"entrylist");
	  TEntryList * elist=(TEntryList *)gDirectory->Get("elist_s");
	  //std::vector<long unsigned int> vec(0);
	  //elisttovec(elist,vec);
	  output.set_S_Ents(i,elist);
	  m_s_tuples[i]->SetEntryList(0);
	  if(elist) elist->SetDirectory(0);
	  if(elist) delete elist;
	}
      
  for(UInt_t i = 0; i<m_b_tuples.size(); i++)
	{
	  m_b_tuples[i]->Draw(">>elist_b",cut,"entrylist");
	  TEntryList * elist=(TEntryList *)gDirectory->Get("elist_b");
	  //std::vector<long unsigned int> vec(0);
	  //elisttovec(elist,vec);
	  output.set_B_Ents(i,elist);
	  m_b_tuples[i]->SetEntryList(0);
	  if(elist) elist->SetDirectory(0);
	  if(elist) delete elist;
	}

  if(eventColumn!="" && runColumn !="") calculateEventWeights(output);
  
  return true;
  
  
}

bool data::entries(TString & cut, const cutresult & input, cutresult & output)
{
  //std::cout<< "in entries with input&output" <<std::endl;
  if(!m_prepared) return false;
  
  output.clear();
  
  for(UInt_t i = 0; i<m_s_tuples.size(); i++)
	{
	  //std::cout<< "signal loop " << i <<std::endl;
	  //iterate over input
	  m_s_tuples[i]->SetEntryList(0);
	  TEntryList * elist=input.S_Ents(i,m_s_tuples[i]);
	  if(elist) m_s_tuples[i]->SetEntryList(elist);

	  m_s_tuples[i]->Draw(">>elist_s",cut,"entrylist");
	  TEntryList * elist_s=(TEntryList *)gDirectory->Get("elist_s");
	  //std::cout<< "ready to set_S_Ents " << i <<std::endl;
	  output.set_S_Ents(i,elist_s);
	  //std::cout<< "set_S_Ents " << i <<std::endl;
	  m_s_tuples[i]->SetEntryList(0);
	  if(elist) elist->SetDirectory(0);
	  if(elist) delete elist;
	  if(elist_s) elist_s->SetDirectory(0);
	  if(elist_s) delete elist_s;
	}
      
  for(UInt_t i = 0; i<m_b_tuples.size(); i++)
	{
	  //std::cout<< "bg loop " << i <<std::endl;
	  //iterate over input
	  m_b_tuples[i]->SetEntryList(0);
	  TEntryList * elist=input.B_Ents(i,m_b_tuples[i]);
	  if(elist) m_b_tuples[i]->SetEntryList(elist);
	  
	  m_b_tuples[i]->Draw(">>elist_b",cut,"entrylist");
	  TEntryList * elist_b=(TEntryList *)gDirectory->Get("elist_b");
	  output.set_B_Ents(i,elist_b);
	  
	  m_b_tuples[i]->SetEntryList(0);
	  if(elist) elist->SetDirectory(0);
	  if(elist) delete elist;
	  if(elist_b) elist_b->SetDirectory(0);
	  if(elist_b) delete elist_b;
	}

  if(eventColumn!="" && runColumn !="") calculateEventWeights(output);
  
  return true;
  
  
}


bool data::print(TString cut,cutresult & output)
{
  if(!m_prepared) return 0;
  //std::cout<< "in print, with no output" <<std::endl;
  //cutresult output(m_s_tuples.size(),m_b_tuples.size(),0);
  
  if (!entries(cut,output)) return 0;
  //if (!calculateEventWeights(output)) return 0;
  std::cout<< "cut \t\t\t Tuple \t\t entries \t weighted \t C/ev" <<std::endl;
  
  for(UInt_t i = 0; i<m_s_tuples.size(); i++)
  {
    std::cout<< cut << "\tS " << i << " " << m_s_user_names[i] << "\t" << output.S(i) << "\t" << output.S(i)*m_s_weights[i]/output.S_C_E(i);
    if(runColumn!="" && eventColumn!="") std::cout << "\t" << output.S_C_E(i);
    std::cout <<std::endl;
  }

  for(UInt_t j = 0; j<m_b_tuples.size(); j++)
  {
    std::cout<< cut << "\tB " << j << " " << m_b_user_names[j] << "\t" << output.B(j) << "\t" << output.B(j)*m_b_weights[j]/output.B_C_E(j);
    if(runColumn!="" && eventColumn!="") std::cout << "\t" << output.B_C_E(j);
    std::cout <<std::endl;
  }

  return true;
    
}
bool data::print(TString cut)
{
  if(!m_prepared) return 0;
  
  cutresult output(m_s_tuples.size(),m_b_tuples.size(),0);
  return print(cut,output);  
}


std::vector<TH1F*> data::graphThis(const std::string xname, const cutresult & output, const TString cuts)
{
  //std::cout << "in graphThis" <<std::endl;
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1); 
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  
  stringstream ss (stringstream::in | stringstream::out);
  

  TCanvas* plotCanvasTemp = new TCanvas(xname.c_str());
  std::vector<TH1F*> some_plots(0);
  
  std::string acuts="";
  acuts.append(cuts);
  acuts.insert(0,"*(");
  acuts.append(")");
  
  //std::cout << "ready for loop" <<std::endl;
  
  
  for(UInt_t i = 0; i<m_s_tuples.size(); i++)
  {
    TEntryList *elist=output.S_Ents(i,m_s_tuples[i]);
    m_s_tuples[i]->SetEntryList(elist);
    ss << i << std::endl;
    std::string dtoc;
    ss >> dtoc;
      
    std::string aname=xname;
    aname.append(dtoc);
      
    std::string thiscut=acuts;
      
    ss << m_s_weights[i]/output.S_C_E(i) << std::endl;
    std::string dtoc2;
    ss >> dtoc2;
      
    thiscut.insert(0,dtoc2);
      
    m_s_tuples[i]->Draw(xname.c_str(),thiscut.c_str());
    TH1F *htemp = (TH1F*)gPad->GetPrimitive("htemp");
    //if(!htemp) std::cout<<"ERROR: No signal histogram???" << std::endl;
    //else
    if(htemp)
    {
	  
      TH1F *h_s=(TH1F*)htemp->Clone(aname.c_str());
      //std::cout << "3" << xname <<std::endl;
      some_plots.push_back(h_s);
    }
      
    m_s_tuples[i]->SetEntryList(0);
    if(elist) delete elist;
  }

  for(UInt_t j = 0; j<m_b_tuples.size(); j++)
  {
    TEntryList *elist=output.B_Ents(j,m_b_tuples[j]);
    // TEntryList *elist=vectoelist(output.B_Ents_begin(j),output.B_Ents_end(j),m_b_tuples[j]);
    m_b_tuples[j]->SetEntryList(elist);
    ss << j << std::endl;
    std::string dtoc;
    ss >> dtoc;
    std::string aname=xname;
    aname.append(dtoc);
      
    std::string thiscut=acuts;
      
    ss << m_b_weights[j]/output.B_C_E(j) << std::endl;
    std::string dtoc2;
    ss >> dtoc2;
      
    thiscut.insert(0,dtoc2);
      
    m_b_tuples[j]->Draw(xname.c_str(),thiscut.c_str());
    TH1F *htemp = (TH1F*)gPad->GetPrimitive("htemp");
    //if(!htemp) std::cout<<"ERROR: No background histogram???" << std::endl;
    //else
    if(htemp)
    {
	  
      TH1F *h_b=(TH1F*)htemp->Clone(aname.c_str());
      some_plots.push_back(h_b);
    }
      
    m_b_tuples[j]->SetEntryList(0);
    if(elist) delete elist;
  }
  delete plotCanvasTemp;
  return some_plots;
  
  
}

std::vector<TH1F*> data::graphThis(const std::string xname, const cutresult & output, double Rmin, double Rmax, const TString cuts)
{
  //std::cout << "in graphThis" <<std::endl;
  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1); 
  gStyle->SetOptStat(0);
  gStyle->SetOptFit(0);
  
  stringstream ss (stringstream::in | stringstream::out);
  

  TCanvas* plotCanvasTemp = new TCanvas(xname.c_str());
  std::vector<TH1F*> some_plots(0);
  
  std::string acuts="";
  acuts.append(cuts);
  acuts.insert(0,"*(");
  acuts.append(")");
  
  //std::cout << "ready for loop" <<std::endl;
  
  
  for(UInt_t i = 0; i<m_s_tuples.size(); i++)
  {
    TEntryList *elist=output.S_Ents(i,m_s_tuples[i]);
    m_s_tuples[i]->SetEntryList(elist);
    ss << i << "_SR" << std::endl;
    std::string dtoc;
    ss >> dtoc;
      
    std::string aname=xname;
    aname.append(dtoc);
      
    std::string thiscut=acuts;
      
    ss << m_s_weights[i]/output.S_C_E(i) << std::endl;
    std::string dtoc2;
    ss >> dtoc2;
      
    thiscut.insert(0,dtoc2);
    dtoc2="";
    ss << ">>+" << aname << std::endl;
    ss >> dtoc2;
    
    //thiscut.append(dtoc2);
    
    std::string anx=xname;
    anx.append(dtoc2);

    TH1F *old = (TH1F*)gDirectory->FindObject(aname.c_str());
    if (old && old->IsOnHeap()) {
      //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
    }
    
    TH1F *htemp;
    if(Rmin<Rmax) htemp= new TH1F(aname.c_str(),xname.c_str(),100,Rmin,Rmax);
    else htemp= new TH1F(aname.c_str(),xname.c_str(),100,Rmax,Rmin);
    
    //std::cout << "histoing: new TH1F(" << aname << "," << xname.c_str()<< "," <<"100," << Rmin << "," << Rmax << " );" 
    //          << " m_s_tuples[i]->Draw(" << anx << "," << thiscut << ")" << std::endl;
    

    m_s_tuples[i]->Draw(anx.c_str(),thiscut.c_str());
    //TH1F *htemp = (TH1F*)gPad->GetPrimitive("htemp");
    //if(!htemp) std::cout<<"ERROR: No signal histogram???" << std::endl;
    //else
    if(htemp)
    {
	  //
    //  TH1F *h_s=(TH1F*)htemp->Clone(aname.c_str());
    // //std::cout << "3" << xname <<std::endl;
      some_plots.push_back(htemp);
    }
      
    m_s_tuples[i]->SetEntryList(0);
    if(elist) delete elist;
  }

  for(UInt_t j = 0; j<m_b_tuples.size(); j++)
  {
    TEntryList *elist=output.B_Ents(j,m_b_tuples[j]);
    // TEntryList *elist=vectoelist(output.B_Ents_begin(j),output.B_Ents_end(j),m_b_tuples[j]);
    m_b_tuples[j]->SetEntryList(elist);
    ss << j << "_BR" << std::endl;
    std::string dtoc;
    ss >> dtoc;
    std::string aname=xname;
    aname.append(dtoc);
      
    std::string thiscut=acuts;
      
    ss << m_b_weights[j]/output.B_C_E(j) << std::endl;
    std::string dtoc2;
    ss >> dtoc2;
      
    thiscut.insert(0,dtoc2);
      
    dtoc2="";
    ss << ">>+" << aname << std::endl;
    ss >> dtoc2;
    
    //thiscut.append(dtoc2);
    
    std::string anx=xname;
    anx.append(dtoc2);
    
    //std::cout << "histoing: new TH1F(" << aname << "," << xname.c_str()<< "," <<"100," << Rmin << "," << Rmax << " );" 
    //          << " m_s_tuples[i]->Draw(" << anx << "," << thiscut << ")" << std::endl;
    
    TH1F *old = (TH1F*)gDirectory->FindObject(aname.c_str());
    if (old && old->IsOnHeap()) {
      //Warning("Constructor","Deleting canvas with same name: %s",name);
      delete old;
    }
    
    TH1F *htemp = new TH1F(aname.c_str(),xname.c_str(),100,Rmin,Rmax);
    
    m_b_tuples[j]->Draw(anx.c_str(),thiscut.c_str());
    //TH1F *htemp = (TH1F*)gPad->GetPrimitive("htemp");
    //if(!htemp) std::cout<<"ERROR: No background histogram???" << std::endl;
    //else
    if(htemp)
    {
	  
      //TH1F *h_b=(TH1F*)htemp->Clone(aname.c_str());
      some_plots.push_back(htemp);
    }
      
    m_b_tuples[j]->SetEntryList(0);
    if(elist) delete elist;
  }
  delete plotCanvasTemp;
  return some_plots;
  
  
}

bool data::calculateEventWeights(cutresult & result)
{
  //runEventWeight blank;
  //runEventCount a_runEventCount;
  //std::vector<runEventCount> runEventCounts_s(m_s_tuples.size());
  //std::vector<runEventCount> runEventCounts_b(m_b_tuples.size());
  
  //std::cout << "calculate cand/event called " << std::endl;
  if(eventColumn=="" || runColumn == "") { return false;}//return blank;
  //std::cout << "calculate cand/event running " << std::endl;
  
  //loop over signal
  for(unsigned int i=0; i< m_s_tuples.size(); i++)
  {
    //std::cout << "signal candidates " << result.S(i) << std::endl;
    runEventSet runEventSet_si;
    if(result.S(i)<2) {result.set_S_C_E(i,1.); continue;};
      
    for(std::vector<unsigned long int>::const_iterator evt=result.S_Ents_begin(i); evt<result.S_Ents_end(i); evt++)
    {
      if(*evt>=runEventVector_s[i].size()) break;// || tentry>=entmax) break;

      runEventSet_si.insert(runEventVector_s[i][*evt]);
    }
    result.set_S_C_E(i,double(result.S(i))/double(runEventSet_si.size()));
    //std::cout << "calculate cand/event should be " << double(result.S(i))/double(runEventSet_si.size());
    //std::cout << " it is " << result.S_C_E(i) << std::endl;
      
  }
  
  //loop over b/g
  for(unsigned int i=0; i< m_b_tuples.size(); i++)
  {
    runEventSet runEventSet_bi;
    if(result.B(i)<2) {result.set_B_C_E(i,1.); continue;};
      
    for(std::vector<unsigned long int>::const_iterator evt=result.B_Ents_begin(i); evt<result.B_Ents_end(i); evt++)
    {
      if(*evt>=runEventVector_b[i].size()) break;// || tentry>=entmax) break;

      runEventSet_bi.insert(runEventVector_b[i][*evt]);
    }
    result.set_B_C_E(i,double(result.B(i))/double(runEventSet_bi.size()));
    //std::cout << "calculate cand/event should be " << double(result.B(i))/double(runEventSet_bi.size());
    //std::cout << " it is " << result.B_C_E(i) << std::endl;
      
  }
  

  return true;


}
//in an effort to improve runtime, I'll preload a vector with all the run/event numbers
bool data::fillEventVector()
{
  if(eventColumn=="" || runColumn == "") return false;//return blank;
  
  std::cout << " --->Preloading event/run numbers" << std::flush;
  
  runEventVector_s=std::vector<runEventVector>(m_s_file_names.size());
  runEventVector_b=std::vector<runEventVector>(m_b_file_names.size());

  //loop over signal
  for(unsigned int i=0; i< m_s_tuples.size(); i++)
  {
    std::cout << "."<< std::flush;
    if(!m_s_tuples[i]) break;
      
    //loop over the tree
    unsigned long int entmax=m_s_tuples[i]->GetEntries();

    runEventVector runEventVector_si(entmax);
      
    Int_t runNum=0;
    Int_t evtNum=0;
    m_s_tuples[i]->SetBranchAddress(runColumn, &runNum);
    m_s_tuples[i]->SetBranchAddress(eventColumn, &evtNum);
      
    //std::cout << "testing line 425" <<std::endl;

    for(unsigned long int evt=0; evt<entmax; evt++)
    {
      if(evt>=runEventVector_si.size()) break;
      if(m_s_tuples[i]->GetEntry(evt) <=0) break;
      if(!runNum || !evtNum) break;

      runEventVector_si[evt]=runEvent(runNum,evtNum);
    }
    //std::cout << "testing line 448" <<std::endl;
    runEventVector_s[i]=runEventVector_si;
      
  }
  //std::cout << "testing line 452" <<std::endl;
        
  //loop over background
  for(unsigned int i=0; i< m_b_tuples.size(); i++)
  {
    std::cout << "."<< std::flush;
    if(!m_b_tuples[i]) break;
      
    //loop over the tree
    unsigned long int entmax=m_b_tuples[i]->GetEntries();

    runEventVector runEventVector_bi(entmax);
      
    Int_t runNum=0;
    Int_t evtNum=0;
    m_b_tuples[i]->SetBranchAddress(runColumn, &runNum);
    m_b_tuples[i]->SetBranchAddress(eventColumn, &evtNum);
      
    //std::cout << "testing line 425" <<std::endl;

    for(unsigned long int evt=0; evt<entmax; evt++)
    {
      if(evt>=runEventVector_bi.size()) break;
      if(m_b_tuples[i]->GetEntry(evt) <=0) break;
      if(!runNum || !evtNum) break;

      runEventVector_bi[evt]=runEvent(runNum,evtNum);
    }
    //std::cout << "testing line 448" <<std::endl;
    runEventVector_b[i]=runEventVector_bi;
      
  }
  std::cout << "done" << std::endl;
  return true;

}
