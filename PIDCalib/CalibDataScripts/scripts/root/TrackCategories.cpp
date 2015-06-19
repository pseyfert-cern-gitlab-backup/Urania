// $Id: $
// Include files
#include <vector>

// local

//-----------------------------------------------------------------------------
// Implementation file for class : TrackCategories
//
// 2011-06-09 : Andrew Powell (LHCb)04
//-----------------------------------------------------------------------------
void TrackCategories(const char* file = "../KaonMinus_Strip13bMagDown.root")
{
  TFile* f = new TFile(file);
  
  if(!f)
  {
    cout<<"No such file"<<endl;
    return EXIT_FAILURE;
  }
  
  if(!f->Get("RSDStCalib"))
    //if(!f->Get("Lam0Calib"))
  {
    cout<<"No such workspace"<<endl;
    return EXIT_FAILURE;
  }
  
  RooWorkspace* Myws = (RooWorkspace*)f->Get("RSDStCalib");
  //RooWorkspace* Myws = (RooWorkspace*)f->Get("Lam0Calib");
  Myws->Print("v");
  
  if(!Myws->data("data"))
  {
    cout<<"No such dataset"<<endl;
    return EXIT_FAILURE;
  }
  
  RooDataSet* Mydata = (RooDataSet*)Myws->data("data");
  Mydata->Print("v");
  
  vector<RooCategory*> cat_vec;
  
  if(Myws->cat("Rich_Threshold"))
    cat_vec.push_back(Myws->cat("Rich_Threshold"));
  if(Myws->cat("Aerogel_Info"))
    cat_vec.push_back(Myws->cat("Aerogel_Info"));
  if(Myws->cat("Rich1Gas_Info"))
    cat_vec.push_back(Myws->cat("Rich1Gas_Info"));
  if(Myws->cat("Rich2Gas_Info"))
    cat_vec.push_back(Myws->cat("Rich2Gas_Info"));
  if(Myws->cat("Charge"))
    cat_vec.push_back(Myws->cat("Charge"));
  if(Myws->cat("Rich_Info"))
    cat_vec.push_back(Myws->cat("Rich_Info"));
  if(Myws->cat("IsMuon"))
    cat_vec.push_back(Myws->cat("IsMuon"));
  
  vector<RooCategory*>::iterator itr_cat;
  for(itr_cat=cat_vec.begin(); itr_cat!=cat_vec.end(); ++itr_cat)
  {
    if(Mydata->table(**itr_cat))
    {
       (Mydata->table(**itr_cat))->Print();
    }
  }
  
  /*
  RooSuperCategory RadCat("RadCat",
                          "RadCat",
                          RooArgSet(*Thresh,
                                    *Aero_info,
                                    *R1Gas_info,
                                    *R2Gas_info));
  
  RooTable* table_RadCat = (RooTable*)Mydata->table(RadCat);
  
  table_RadCat->Print("v");

  if(table_charge!=NULL)
  {
    table_charge->Print("v");
  }
  */
  
}
