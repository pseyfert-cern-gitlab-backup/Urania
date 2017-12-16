#include "limit_interface.h"

TString limit_interface::m_georefstring = "NaN";
TString limit_interface::m_cutstring2011 = "NaN";
TString limit_interface::m_cutstring2012 = "NaN";


//2012
//float pidbinning[6] = {0.4,0.54, 0.61, 0.71, 0.8,1.0001  };
//float geobinning[9] = {0.,0.26,0.34,0.45, 0.61 , 0.7, 0.83, 0.94 ,1.0001 };

//float pidbinning[6] = {0.4,0.54, 0.61, 0.71, 0.8,1.0001  };                  
//float geobinning[8] = {0.26,0.34,0.45, 0.61 , 0.7, 0.83, 0.94 ,1.0001 };


//2011
//float pidbinning[6] = {0.4,0.45, 0.54, 0.63, 0.75,1.0001  };
//float geobinning[8] = {0.,0.28,0.32,0.46, 0.54 , 0.65, 0.8, 1.0001 };

// 2011 not trashes
float pidbinning[6] = {0.4,0.45, 0.54, 0.63, 0.75,1.0001  };           
float geobinning[7] = {0.28,0.32,0.46, 0.54 , 0.65, 0.8, 1.0001 };   



//int limit_interface::GetGlobalMVAbin(float GeoMVA, float singlePID) {
//  TH1F* geobuffer = new TH1F("geotmp","geotmp",n_geobins,geobinning);
//  TH1F* pidbuffer = new TH1F("pidtmp","pidtmp",n_pidbins,pidbinning);
//
//  int retval =  GetGlobalMVAbin((int) pidbuffer->FindBin(GeoMVA),(int)geobuffer->FindBin(singlePID));
//  delete geobuffer;
//  delete pidbuffer;
//
//  return retval;
//}

/**
 * @example howto
 * @code
 * gSystem->Load("./libLimitROOT.so");
 *
 * limit_interface* li = new limit_interface();
 *
 * //loop over GeoMVA bins
 * for (int g = 0 ; g < li->GetNGeobins() ; ++g) {
 *   
 *   // loop over PID bins
 *   for (int p = 0 ; p < li->GetNPIDbins() ; ++p) {
 *   
 *     // get bin boarders
 *     float lowG = li->GetGeolow(g);
 *     float highG = li->GetGeohigh(g);
 *     float lowP = li->GetPIDlow(p);
 *     float highP = li->GetPIDhigh(p);
 *     
*     for (int m = 0 ; m < li->GetNMassbins() ; ++m) {
 *       float lowm = li->GetMasslow(m);
 *       float highm = li->GetMasshigh(m);
 *       // here your fits determine these three:
 *       float expectedBKG = value
 *       float expectedBKGplus = value+error
 *       float expectedBKGminus = value-error
 *     
 *       li->SetPrivate(g,p,(lowm+highm)*.5,expectedBKG,expectedBKGplus,expectedBKGminus);
 *     } // end mass loop
 *     
 *   } // end pid loop
 * } // end geo loop
 * 
 * TFile* f = new TFile("forJohannes.root","recreate");
 * f->WriteTObject(li->GetFilledHistogram("expected"));
 * f->WriteTObject(li->GetFilledHistogram_PLUS("expected_plus"));
 * f->WriteTObject(li->GetFilledHistogram_MINUS("expected_minus"));
 * f->Close();
 * 
 * 
 * @endcode
 */

int limit_interface::GetGlobalMVAbin(int geobin, int pidbin) {
  int thisbin = geobin + pidbin * n_geobins; 
  return thisbin;
}

void limit_interface::SetPrivate(int geobin, int pidbin, float mass, float content) {
  TH1F* massbuffer = new TH1F("massbuffer","massbuffer",n_massbins,lowmasslimit,highmasslimit);
  int thismass = massbuffer->FindBin(mass);
  private_histo->SetBinContent(private_histo->GetBin(1+GetGlobalMVAbin(geobin,pidbin),thismass),content) ;
  delete massbuffer;
  return;
}

void limit_interface::SetPrivate(int geobin, int pidbin, float mass, float content, float contentPLUS, float contentMINUS) {
  TH1F* massbuffer = new TH1F("massbuffer","massbuffer",n_massbins,lowmasslimit,highmasslimit);
  int thismass = massbuffer->FindBin(mass);
  int binnumber = private_histo->GetBin(1+GetGlobalMVAbin(geobin,pidbin),thismass);
  private_histo->SetBinContent(binnumber,content) ;
  private_histo_P->SetBinContent(private_histo->GetBin(1+GetGlobalMVAbin(geobin,pidbin),thismass),contentPLUS) ;
  private_histo_M->SetBinContent(private_histo->GetBin(1+GetGlobalMVAbin(geobin,pidbin),thismass),contentMINUS) ;
  delete massbuffer;
  return;
}


ClassImp(limit_interface);
