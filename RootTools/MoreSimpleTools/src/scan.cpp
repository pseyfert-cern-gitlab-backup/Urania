#include "scan.h"

//ClassImp(scan)

scan::scan():
  m_ndataS(0),
  m_ndataB(0),
  m_data(0),
  m_ncuts(0),
  m_cuts(0),
  m_plots(0),
  last(),
  zero(),
  m_S_sum(-1),
  m_B_sum(-1),
  m_Sw_sum(-1.),
  m_Bw_sum(-1.),
  m_dSw_sum(-1.),
  m_dBw_sum(-1.),
  m_S0_sum(-1),
  m_B0_sum(-1),
  m_Sw0_sum(-1.),
  m_Bw0_sum(-1.),
  m_scanned(false),
  m_useCustom(false)
{

}

scan::scan(data* tuples, const cuts* mycuts, plots* myplots):
  m_ndataS(0),
  m_ndataB(0),
  m_data(tuples),
  m_ncuts(0),
  m_cuts(mycuts),
  m_plots(myplots),
  last(),
  zero(),
  m_S_sum(-1),
  m_B_sum(-1),
  m_Sw_sum(-1.),
  m_Bw_sum(-1.),
  m_dSw_sum(-1.),
  m_dBw_sum(-1.),
  m_S0_sum(-1),
  m_B0_sum(-1),
  m_Sw0_sum(-1.),
  m_Bw0_sum(-1.),
  m_scanned(false),
  m_useCustom(false)
{
  if(m_cuts==NULL || m_data==NULL) std::cout << "You can't perform a scan without cuts or data!" << std::endl;
  else
  {
    m_ncuts=m_cuts->NCuts();
    m_ndataS=m_data->NSFiles();
    m_ndataB=m_data->NBFiles();
    
    last=cutresult(m_ndataS,m_ndataB,m_ncuts);
    m_cuts->cut_result(m_data,last);
    zero=last;
    save();
    S0(); B0(); Sw0(); Bw0();
  }
  //std::cout << "constructor OK" << std::endl;
  
}

scan::scan(const cuts* mycuts, data* tuples, plots* myplots):
  m_ndataS(0),
  m_ndataB(0),
  m_data(tuples),
  m_ncuts(0),
  m_cuts(mycuts),
  m_plots(myplots),
  last(),
  zero(),
  m_S_sum(-1),
  m_B_sum(-1),
  m_Sw_sum(-1.),
  m_Bw_sum(-1.),
  m_dSw_sum(-1.),
  m_dBw_sum(-1.),
  m_S0_sum(-1),
  m_B0_sum(-1),
  m_Sw0_sum(-1.),
  m_Bw0_sum(-1.),
  m_scanned(false),
  m_useCustom(false)
{
  if(m_cuts==NULL || m_data==NULL) std::cout << "You can't perform a scan without cuts or data!" << std::endl;
  else
  {
    m_ncuts=m_cuts->NCuts();
    m_ndataS=m_data->NSFiles();
    m_ndataB=m_data->NBFiles();
    
    last=cutresult(m_ndataS,m_ndataB,m_ncuts);
    m_cuts->cut_result(m_data,last);
    zero=last;
    save();
    S0(); B0(); Sw0(); Bw0();
  }
  //std::cout << "constructor OK" << std::endl;
  
}

bool scan::cutResult(const cutlocation & location, const bool force)
{
  //std::cout << "doing the cut " << location << " forced? " << force << std::endl;
  if(!force)
  {
    //load(last);
    if(location == last.location()) return true;
    if(load(location)) return true;
    if(m_scanned) return(load(constructResult(location)));
  }
  else
  {
    load(zero);
    //m_data->setEntries(m_s0_ents,m_b0_ents);
  }
  
  //load(last);
  cutresult next=cutresult(location,m_ndataS,m_ndataB);
  //cutresult next=last;
  m_cuts->cut_result(m_data,last,next);
  //load(next);
  
  return load(next);

}


int scan::S()
{
  if(m_S_sum >-1)  return m_S_sum;
  m_S_sum=last.S();
  
  return m_S_sum;
  
}

int scan::B()
{
  if(m_B_sum >-1) return m_B_sum;
  m_B_sum=last.B();
  
  return m_B_sum;
}

int scan::S0()
{
  if(m_S0_sum >-1)  return m_S0_sum;
  m_S0_sum=zero.S();
  
  return m_S0_sum;
  
}

int scan::B0()
{
  if(m_B0_sum >-1) return m_B0_sum;
  m_B0_sum=zero.B();
  
  return m_B0_sum;
}

int scan::S(const unsigned int i)
{
  return last.S(i);
}

int scan::B(const unsigned int i)
{
  return last.B(i);
}

int scan::S0(const unsigned int i)
{
  return zero.S(i);
}

int scan::B0(const unsigned int i)
{
  return zero.B(i);
}

double scan::Sw0(const unsigned int i)
{
  return S0(i)*m_data->s_weights(i)/S_C_E0(i);
}

double scan::Bw0(const unsigned int i)
{
  return B0(i)*m_data->b_weights(i)/B_C_E0(i);
}
double scan::Sw(const unsigned int i)
{
  return S(i)*m_data->s_weights(i)/S_C_E(i);
}

double scan::Bw(const unsigned int i)
{
  return B(i)*m_data->b_weights(i)/B_C_E(i);
}
double scan::Sw()
{
  if(m_Sw_sum >-0.1) return m_Sw_sum;

  m_Sw_sum=0;
  
  for(unsigned int i=0; i<m_ndataS; i++) m_Sw_sum+=Sw(i);

  return m_Sw_sum;
}

double scan::Bw()
{
  if(m_Bw_sum >-0.1) return m_Bw_sum;

  m_Bw_sum=0;
  
  for(unsigned int i=0; i<m_ndataB; i++) m_Bw_sum+=Bw(i);

  return m_Bw_sum;
}
double scan::Sw0()
{
  if(m_Sw0_sum >-0.1) return m_Sw0_sum;

  m_Sw0_sum=0;
  
  for(unsigned int i=0; i<m_ndataS; i++) m_Sw0_sum+=Sw0(i);

  return m_Sw0_sum;
}

double scan::Bw0()
{
  if(m_Bw0_sum >-0.1) return m_Bw0_sum;

  m_Bw0_sum=0;
  
  for(unsigned int i=0; i<m_ndataB; i++) m_Bw0_sum+=Bw(i);

  return m_Bw0_sum;
}
double scan::S_C_E(const unsigned int adata)
{
  return last.S_C_E(adata);
}
double scan::B_C_E(const unsigned int adata)
{
  return last.B_C_E(adata);
}

double scan::S_C_E0(const unsigned int adata)
{
  return zero.S_C_E(adata);
}
double scan::B_C_E0(const unsigned int adata)
{
  return zero.B_C_E(adata);
}

double scan::Sw_C_E()
{
  double Sw_C_Esum=0;
  double Sw_C_Eden=0;
  
  for(unsigned int i=0; i<m_ndataS; i++) Sw_C_Esum+=S(i)*m_data->s_weights(i)*S_C_E(i);
  
  for(unsigned int i=0; i<m_ndataS; i++) Sw_C_Eden+=S(i)*m_data->s_weights(i);
  return Sw_C_Esum/Sw_C_Eden;
}
double scan::Bw_C_E()
{
  double Bw_C_Esum=0;
  double Bw_C_Eden=0;
  
  for(unsigned int i=0; i<m_ndataB; i++) Bw_C_Esum+=B(i)*m_data->b_weights(i)*B_C_E(i);
  
  for(unsigned int i=0; i<m_ndataB; i++) Bw_C_Eden+=B(i)*m_data->b_weights(i);
  return Bw_C_Esum/Bw_C_Eden;
}

double scan::Sw_C_E0()
{
  double Sw_C_Esum0=0;
  double Sw_C_Eden0=0;
  
  for(unsigned int i=0; i<m_ndataS; i++) Sw_C_Esum0+=S0(i)*m_data->s_weights(i)*S_C_E0(i);
  
  for(unsigned int i=0; i<m_ndataS; i++) Sw_C_Eden0+=S0(i)*m_data->s_weights(i);
  return Sw_C_Esum0/Sw_C_Eden0;
}
double scan::Bw_C_E0()
{
  double Bw_C_Esum0=0;
  double Bw_C_Eden0=0;
  
  for(unsigned int i=0; i<m_ndataB; i++) Bw_C_Esum0+=B0(i)*m_data->b_weights(i)*B_C_E0(i);
  
  for(unsigned int i=0; i<m_ndataB; i++) Bw_C_Eden0+=B0(i)*m_data->b_weights(i);
  return Bw_C_Esum0/Bw_C_Eden0;
}

double scan::BoS() {  return (Bw()/Sw()); }

double scan::SoB() { return (Sw()/Bw()); }

double scan::SoRSB() {  if(Sw()+Bw()>0) return (Sw()/sqrt(Sw()+Bw())); return 0;}

double scan::CustomSoRSB() {  if(Sw(0)+Bw(0)>0) return (CustomS()/sqrt(Sw(0)+Bw(0))); return 0;}
//                                          RSSB         WSSB * (RSBB/WSBB)  
double scan::CustomS(){ if (Bw(2)>0) return Sw(0)-double(Bw(1)*Bw(0))/Bw(2); return Sw(0);}

double scan::dCustomS()
{ 
  if (Bw(2)>0)
  {
    double ercorr=dBw(1)*dBw(1)/(Bw(1)*Bw(1))+dBw(2)*dBw(2)/(Bw(2)*Bw(2))+dBw(0)*dBw(0)/(Bw(0)*Bw(0));
    ercorr=dSw(0)*dSw(0)+((Bw(1)*Bw(0))/Bw(2))*ercorr;
    return sqrt(ercorr); 
  }
  
  return 0.;
}

double scan::dCustomB()
{ 
  if (Bw(2)>0)
  {
    double ercorr=dBw(1)*dBw(1)/(Bw(1)*Bw(1))+dBw(2)*dBw(2)/(Bw(2)*Bw(2));
    ercorr=dBw(0)*dBw(0)+((Bw(1)*Bw(0))/Bw(2))*ercorr;
    return sqrt(ercorr); 
  }
  
  return 0.;
}

/*double scan::dCustomSoRSB()
{
  return 0;
  //difficult calculation!
  double SoRSBi=CustomSoRSB();
  if(SoRSBi<=0) return 0;
  double RSB=Sw(0)+Bw(0);
  if(RSB>0) RSB=sqrt(RSB);
  else return 0;
  double dRSB2=(dSw()+dBw())/(4*RSB*RSB);
  double dSoRSB2=SoRSBi*SoRSBi*(dSw()*dSw()/(Sw()*Sw()) + dRSB2/(RSB*RSB));
  if(dSoRSB2>0) return sqrt(dSoRSB2) ;
  return 0;
}
*/


double scan::CustomB(){ if (Bw(2)>0) return Bw(0)+double(Bw(1)*Bw(0))/Bw(2); return Sw(1);}


double scan::Eff() { return (double(Sw())/double(Sw0())); }

double scan::Eff(const unsigned int adata) 
{ 
  if(adata > m_ndataS) return 0.; 
  return (double(last.S(adata))/double(zero.S(adata))); 
}

double scan::EffB() { return (Bw()/Bw0()); }

double scan::EffB(const unsigned int adata) 
{ 
  if(adata > m_ndataB) return 0.; 
  return (double(last.B(adata))/double(zero.B(adata))); 
}

double scan::dS() {  if(S()>0) return sqrt(double (S())); return 0; }

double scan::dB() {  if(B()>0) return sqrt(double (B())); return 0; }

double scan::dS(const unsigned int i) {  if(S(i)>0) return sqrt(double (S(i))); return 0; }

double scan::dB(const unsigned int i) {  if(B(i)>0)  return sqrt(double (B(i))); return 0;}

double scan::dSw(const unsigned int i) {  if(S(i)>0) return Sw(i)/dS(i); return 0;}

double scan::dBw(const unsigned int i) {  if(B(i)>0) return Bw(i)/dB(i); return 0; }

double scan::dSw() 
{
  if (m_dSw_sum > -0.1) return m_dSw_sum;
  m_dSw_sum=0;
  for(unsigned int i=0; i<m_ndataS; i++) m_dSw_sum+=dSw(i)*dSw(i);
  if(m_dSw_sum>0) m_dSw_sum=sqrt(m_dSw_sum);
  else m_dSw_sum=0;
  return m_dSw_sum;
  
}

double scan::dBw() 
{
  if (m_dBw_sum > -0.1) return m_dBw_sum;
  m_dBw_sum=0;
  for(unsigned int i=0; i<m_ndataB; i++) m_dBw_sum+=dBw(i)*dBw(i);
  if(m_dBw_sum>0)  m_dBw_sum=sqrt(m_dBw_sum);
  else m_dBw_sum=0;
  return m_dBw_sum;
  
}

double scan::dBoS()
{  
  double dBoS2=0.;
  if(S()>0) dBoS2 += (dSw()*dSw()/(Sw()*Sw()));
  if (B()>0) dBoS2+=(dBw()*dBw()/(Bw()*Bw()));
  if (dBoS2>0) return BoS()*sqrt(dBoS2);
  return 0;
  
}

double scan::dSoB()
{
  double dSoB2=0.;
  if(S()>0) dSoB2 += (dSw()*dSw()/(Sw()*Sw()));
  if (B()>0) dSoB2+=(dBw()*dBw()/(Bw()*Bw()));
  if (dSoB2>0) return SoB()*sqrt(dSoB2);
  return 0; 
}

double scan::dSoRSB()
{
  double SoRSBi=SoRSB();
  if(SoRSBi<=0) return 0;
  double RSB=sqrt(Sw()+Bw());
  if(RSB>0) RSB=sqrt(RSB);
  else return 0;
  double dRSB2=(dSw()+dBw())/(4*RSB*RSB);
  double dSoRSB2=SoRSBi*SoRSBi*(dSw()*dSw()/(Sw()*Sw()) + dRSB2/(RSB*RSB));
  if(dSoRSB2>0) return sqrt(dSoRSB2) ;
  return 0;
}

double scan::dEff()
{
  double deff2=0;//last.S()*(double(zero.S()-last.S())/double(zero.S()-1.0));
  for(unsigned int k=0; k< m_ndataS; k++) 
    deff2+=dEff(k)*dEff(k)*m_data->s_weights(k)*m_data->s_weights(k)*zero.S(k)*zero.S(k)/(S_C_E(k)*S_C_E(k));
  //for(unsigned int k=0; k< m_ndataS; k++) deff2+=dEff(k)*dEff(k)*zero.S(k)*zero.S(k);
  if(deff2>0) return (sqrt(deff2)/double(Sw0()));
  return 0;
}

double scan::dEff(const unsigned int adata)
{
  //error        = error on getting R out of N in a binomial = SQRT(R(N-R)/(N-1))/N
  double deff2=last.S(adata)*(double(zero.S(adata)-last.S(adata))/double(zero.S(adata)-1.0));

  if(deff2>0) return sqrt(deff2)/double(zero.S(adata));
  return 0;
}

double scan::dEffB()
{
  double deffb2=0.;
  for(unsigned int k=0; k< m_ndataB; k++) 
    deffb2+=dEffB(k)*dEffB(k)*m_data->b_weights(k)*m_data->b_weights(k)*zero.B(k)*zero.B(k)/(B_C_E(k)*B_C_E(k));
  if(deffb2>0) return (sqrt(deffb2)/Bw0());
  return 0;
}

double scan::dEffB(unsigned int adata)
{
  if (adata > m_ndataB) return 0.;
  //error        = error on getting R out of N in a binomial = SQRT(R(N-R)/(N-1))/N
  double deffb2=last.B(adata)*(double(zero.B(adata)-last.B(adata))/double(zero.B(adata)-1.0));
  if(deffb2>0) return (sqrt(deffb2)/double(zero.B(adata)));
  return 0;
}

bool scan::stats()
{
  if(m_cuts==NULL || m_data==NULL) return false;
  
  std::cout << "Type File \t\t S0---->S \t\t Eff" <<std::endl;
  for(unsigned int k=0; k<m_ndataS; k++)
  {
    std::cout<< "S   " << k << "\t" << m_data->s_names(k) << "\t" << zero.S(k) 
             << "->" << last.S(k) << "\t\t" << Eff(k) << "+/-" << dEff(k) << std::endl;
      
  }
  for(unsigned int k=0; k<m_ndataB; k++)
  {
    std::cout<< "B   " << k << "\t" << m_data->b_names(k) << "\t" << zero.B(k) 
             << "->" << last.B(k) << "\t\t" << EffB(k) << "+/-" << dEffB(k) << std::endl;
      
  }
  std::cout << "Total" <<std::endl;
  if(m_useCustom) std::cout<< "CustomS  " << CustomS() << "\tCustomB   " << CustomB() << std::endl;
  std::cout<< "Sw  " << Sw() << "+/-" << dSw() << "\tBw   " << Bw() << "+/-" << dBw()<< std::endl;
  std::cout<< "Sw C/E " << Sw_C_E() <<         "\t\t\tBw C/E " << Bw_C_E() << std::endl;
  std::cout<< "Eff " << Eff() << "+/-" << dEff() << "\tEff " << EffB() << "+/-" << dEffB()<< std::endl;
  std::cout<< "S/B " << SoB() << "+/-" << dSoB() << "\tB/S " << BoS() << "+/-" << dBoS()<< std::endl;
  std::cout<< "S/r(S+B) \t" << SoRSB() << "+/-" << dSoRSB() << std::endl;
  if(m_useCustom) std::cout<< "Custom S/r(S+B) \t" << CustomSoRSB() << std::endl;
  return true;
  
}

bool scan::shortstats()
{
  if(m_cuts==NULL || m_data==NULL) return false;
  
  std::cout<< "S   " << Sw() << "+/-" << dSw() << " Eff " << Eff() << "+/-" << dEff() 
           << "\tB   " << Bw() << "+/-" << dBw() << " \tS/r(S+B) " << SoRSB() << "+/-" << dSoRSB() 
           << "\tC/Ev (Bg) " << Bw_C_E();
  if(m_useCustom) std::cout << " \tCustomS " << CustomS() << " \tCustomB " << CustomB() << " \tCustomSoRSB " << CustomSoRSB() ;
  std::cout << std::endl;
  return true;
  
}

bool scan::RateScan(bool statsscan, double freq)
{
  if(freq>0.5) { std::cout << "error freq should be <0.5" << std::endl; return false;}
  //if(freq > 1.) freq=1/freq; 
  if(m_cuts==NULL || m_data==NULL) return false;

  std::cout << "---------------------------------------------------------------" << std::endl;
  std::cout << "        RATE SCAN           " << std::endl;
  std::cout << "---------------------------------------------------------------" << std::endl;
  
  if(m_plots) m_plots->mkdir("RateScan");
  
  std::vector<double> effs(0);
  std::vector<double> csw(0);
  std::vector<double> deffs(0);
  std::vector<double> bws(0);
  std::vector<double> dbws(0);
  std::vector<double> bces(0);
  std::vector<double> sorsb(0);
  std::vector<double> dsorsb(0);
  std::vector<double> csorsb(0);
  //std::vector< std::vector<unsigned int> > locations(0);
  std::vector< cutresult > tagged_locations(0);
  std::vector< std::string > tagged_location_name(0);

  //const std::vector<unsigned int> location_top = m_location;
  //save();
  cutresult location_top = last;
  unsigned int asize=0;
  for(unsigned int i=0; i< last.location().loc.size(); i++) asize+=m_cuts->location_max(i);
  
  //locations.reserve(asize);
  tagged_locations.reserve(20);
  tagged_location_name.reserve(20);
  effs.reserve(asize);
  csw.reserve(asize);
  deffs.reserve(asize);
  bws.reserve(asize);
  bces.reserve(asize);
  dbws.reserve(asize);
  sorsb.reserve(asize);
  dsorsb.reserve(asize);
  csorsb.reserve(asize);
  
  
  //locations.push_back(location_top);
  effs.push_back(Eff());
  deffs.push_back(dEff());
  if(m_useCustom) csw.push_back(CustomS());
  bws.push_back(Bw());
  bces.push_back(Bw_C_E());
  dbws.push_back(dBw());
  sorsb.push_back(SoRSB());
  dsorsb.push_back(dSoRSB());
  if(m_useCustom) csorsb.push_back(CustomSoRSB());
  
  std::cout << " --> highest:" << std::endl;
  std::cout << m_cuts->decodeCuts(last) << std::endl;
  shortstats();
  
  double nextprinthigh=1.0;
  double nextprintlow=freq;
  int nextprintrate=O(Bw()); 
  //std::cout<< " --> nextprint rate" << nextprintrate <<std::endl; 
  
  
  std::cout<< " --> iterating" <<std::endl; 
  
  std::stringstream ss (stringstream::in | stringstream::out);
  
  cutresult last_1;//, last_2;
  last_1=last;
  
  
  while(last!=m_cuts->location_max() && Eff() > (freq*freq) && nextByRate())
  {
    //std::cout << m_cuts->decodeCuts(m_location) << std::endl;
    //std::cout << "eff " << Eff() << "+/-" << dEff() << " Bw " << Bw() << "+/-" << dBw() << std::endl;
    //std::cout << "eff " << Eff() << "+/-" << dEff() << " Bw " << Bw() << "+/-" << dBw() << std::endl;
    //locations.push_back(m_location);
    effs.push_back(Eff());
    deffs.push_back(dEff());
    bws.push_back(Bw());
    bces.push_back(Bw_C_E());
    dbws.push_back(dBw());
    sorsb.push_back(SoRSB());
    dsorsb.push_back(dSoRSB());
    if(m_useCustom) csorsb.push_back(CustomSoRSB());
    if(m_useCustom) csw.push_back(CustomS());
    if(O(Bw())<nextprintrate)
    {
      if(bws.size()>1 && //push back the previous one, if it is less than 2x10^whatever
         O(bws[bws.size()-2]/2.)<nextprintrate) tagged_locations.push_back(last_1);
      else tagged_locations.push_back(last);
	
      ss << "Rate_10^" << nextprintrate << std::endl;	  
      std::string dtoc;
      ss >> dtoc;
      //std::cout << "below nextprintrate of " << dtoc << std::endl;
        
      //char dtoc[20];
      //sprintf(dtoc,"%.4f",nextprintlow);
      tagged_location_name.push_back(dtoc);
      //nextprintrate--; 
      while(O(Bw())<nextprintrate) nextprintrate--; //100, 10, 1, 0.1
      shortstats();
    }
    if(Eff()<nextprintlow)
    {
      tagged_locations.push_back(last_1);
      ss << "Eff_" << nextprintlow << std::endl;	  
      std::string dtoc;
      ss >> dtoc;
      //sprintf(dtoc,"%.4f",nextprintlow);
      tagged_location_name.push_back(dtoc);
      while(Eff()<nextprintlow) nextprintlow*=freq; //10, 1, 0.1
      shortstats();
      //don't add it twice
      if(Eff()<nextprinthigh && nextprinthigh > 1.0-freq*freq*freq) nextprinthigh =1.0-freq*freq*freq; //99.9,
      while(Eff()<nextprinthigh && nextprinthigh > 0.5) nextprinthigh =1.0-((1.0-nextprinthigh)/freq); //99.9, 99, 90
      if (Eff()<nextprinthigh && nextprinthigh < 0.5) nextprinthigh =0.0; //0.0
    }
    else if(Eff()<nextprinthigh)
    {
      tagged_locations.push_back(last_1);
      ss << "Eff_" << nextprinthigh << std::endl;	  
      std::string dtoc;
      ss >> dtoc;
      //char dtoc[20];
      //sprintf(dtoc,"%.4f",nextprinthigh);
      tagged_location_name.push_back(dtoc);
      //don't add it twice
      while(Eff()<nextprintlow) nextprintlow*=freq; //10, 1, 0.1
      if(Eff()<nextprinthigh && nextprinthigh > 1.0-freq*freq*freq) nextprinthigh =1.0-freq*freq*freq; //99.9,
      while(Eff()<nextprinthigh && nextprinthigh > 0.5) nextprinthigh =1.0-((1.0-nextprinthigh)/freq); //99.9, 99, 90
      if (Eff()<nextprinthigh && nextprinthigh < 0.5) nextprinthigh =0.0; //0.0
      //std::cout << m_cuts->decodeCuts(m_location) << std::endl;
      shortstats();
    }
      
    //last_2=last_1;
    last_1=last;
      
      
  }
  
  std::cout << " --> lowest: " << std::endl; 
  std::cout << m_cuts->decodeCuts(last) << std::endl;
  stats();
  //save();
  tagged_locations.push_back(last);
  tagged_location_name.push_back("Last");
  //locations.push_back(m_location);
  effs.push_back(Eff());
  deffs.push_back(dEff());
  bws.push_back(Bw());
  bces.push_back(Bw_C_E());
  dbws.push_back(dBw());
  sorsb.push_back(SoRSB());
  dsorsb.push_back(dSoRSB());
  if(m_useCustom) csorsb.push_back(CustomSoRSB());
  if(m_useCustom) csw.push_back(CustomS());
  
  effs.push_back(0.);
  deffs.push_back(0.);
  bws.push_back(0.);
  bces.push_back(Bw_C_E());
  dbws.push_back(0.);
  sorsb.push_back(0.);
  dsorsb.push_back(0.);
  if(m_useCustom) csorsb.push_back(0.);
  if(m_useCustom) csw.push_back(0.);
  
  if(m_plots)
  {
    std::vector<double> efficacy(0);
    std::vector<double> efficacy_b(0);
    double bws0=bws[0];
    double effs0=effs[0];
    for(unsigned int j=1; j<effs.size(); j++)
    {
      if (bws0==bws[j]) continue;
      if (effs0==effs[j]) continue;
      if (bws0==0.0) break;
      if (effs0==0.0) break;
      
      double efficacy_val=(bws0-bws[j])*effs0/((effs0-effs[j])*bws0);
      efficacy_b.push_back(bws[j]);
      efficacy.push_back(efficacy_val);
      bws0=bws[j];
      effs0=effs[j];
      
    }
    efficacy.push_back(0.);
    efficacy_b.push_back(0.);
    
    //m_plots->mkdir("RateScan");
    m_plots->plot(0, bws, effs, dbws, deffs, "RateScan","B","Efficiency","RateScan" );
    m_plots->plot(0, bws, sorsb, dbws, dsorsb, "RateScan_SoRSB","B","S/sqrt(S+B)","RateScan" );
    if(m_useCustom) m_plots->plot(0, bws, csorsb, "RateScan_Custom_SoRSB","B","S/sqrt(S+B)","RateScan" );
    if(m_useCustom) m_plots->plot(0, bws, csw, "RateScan_Custom_S","B","Custom S/sqrt(S+B)","RateScan" );
    m_plots->plot(0, bws, bces, "RateScan_B_C_E","B","Cands/Event","RateScan" );
    m_plots->plot(0, efficacy_b, efficacy, "RateScan_Efficacy","B","(b1-b2)s1/((s1-s2)b1)","RateScan" );
    
    if(statsscan) std::cout<< " --> stats scans at tagged locations: may take some time." <<std::endl;
    for(unsigned int k=0; k<tagged_locations.size(); k++)
    {     
      save(tagged_locations[k]);
      load(tagged_locations[k]);
      
      if(statsscan)
	    {
	      std::string dir="RateScan/";
	      dir.append(tagged_location_name[k]);
	      m_plots->mkdir(dir);
	      std::cout << " --> Tagged location: " << m_cuts->decodeCuts(last) << std::endl;
	      StatsScan(dir);
	      //std::cout << " --> Tagged location: " << m_cuts->decodeCuts(last) << std::endl;
	      //shortstats();
	      PlotAllClever(dir);
	      //std::cout << m_cuts->decodeCuts(last) << std::endl;
	      //shortstats();
	    }
    }
    
    
  }
  
  
  std::cout << "---------------------------------------------------------------" << std::endl;
  
  return load(location_top); //back to the top
  
}


bool scan::nextByRate()
{
  int mode=0; //0 == by dSw, 1 == by dBw, 2== by dSw_dBw
  std::vector<double> dsw(0);
  std::vector<int> this_s(0);
  std::vector<double> dbw(0);
  cutresult location_top=last;
  cutlocation location_next=last.location();
  int Stop=S();
  int Btop=B();
  double Swtop=Sw();
  if(m_useCustom) Swtop=CustomS();

  double Bwtop=Bw();
  if(m_useCustom) Bwtop=CustomB();
  
  
  dsw.reserve(m_ncuts);
  this_s.reserve(m_ncuts);
  dbw.reserve(m_ncuts);
  
  
  for(unsigned int k=0; k<m_ncuts; k++)
  {
    if(int(location_next.loc[k])>=m_cuts->location_max(k)) //at the end of the cut
    {
      this_s.push_back(0);
      dsw.push_back(Swtop*1.1); //don't go there!
      dbw.push_back(0.); //same 
      continue;
    }
    load(location_top);
    
    location_next=last.location();
    location_next.loc[k]+=1;
    cutResult(location_next);//go quickly when rate-finding
    if(Stop==S()) return true; //rush to the edge of the signal region
    else if(Btop>B() && mode !=1 ) mode=2; //there's some separating power
    //else mode will stay at 0, choose the cut with the lowest signal degradation
    this_s.push_back(S()); //always positive
    if(m_useCustom) 
    {
      dsw.push_back(Swtop-CustomS()); //always positive
      dbw.push_back(Bwtop-CustomB()); //always positive
    }
    else
    {
      dsw.push_back(Swtop-Sw()); //always positive
      dbw.push_back(Bwtop-Bw()); //always positive
    }
    
  }
  
  load(location_top);
  unsigned int lowk=0;
  while(int(last.location().loc[lowk])>=m_cuts->location_max(lowk) && (lowk+1)<m_ncuts) lowk++; //kill cuts that overrun
  if(mode==0 || mode==1) //choose the cut with the lowest signal degradation
  {    
    for(unsigned int k=(lowk+1); k<m_ncuts; k++)
    {
      if(int(last.location().loc[k])>=m_cuts->location_max(lowk)) continue; //kill cuts that overrun
      if(dsw[k]<dsw[lowk]) lowk=k;
      else if(dsw[k]==dsw[lowk] && dbw[k]>dbw[lowk]) lowk=k; //mode =1, probably
    }
  }
  else if(mode==2) //choose the cut with the flattest curve
  {    
    while((this_s[lowk]==0 || int(last.location().loc[lowk])>=m_cuts->location_max(lowk)) && (lowk+1)<m_ncuts) 
    {lowk++;} //kill cuts that remove all signal
    for(unsigned int k=(lowk+1); k<m_ncuts; k++)
    {
      if(int(last.location().loc[k])>=m_cuts->location_max(lowk) || this_s[k]==0) continue;//kill cuts that overrun
      if((dsw[k]/dbw[k])<(dsw[lowk]/dbw[lowk]) ) lowk=k; //flattest curve
      else if((dsw[k]/dbw[k])==(dsw[lowk]/dbw[lowk]) && dsw[k]<dsw[lowk]) lowk=k; //equal flatness, highest signal
    }
  }
  
  //load(location_top);
  location_next=last.location();
  location_next.loc[lowk]+=1;
  if(int(location_next.loc[lowk]) > m_cuts->location_max(lowk) || this_s[lowk]==0) 
  { 
    std::cout << "No next cut by rate" << std::endl;
    return false;
  };
  return cutResult(location_next);  //will always be tighter
  
  
}

double scan::nextByAllVal(const unsigned int ncut, double (scan::* valPointer)(void), char mode )
{
  if(ncut > m_ncuts) return 0;
  if(mode != 'h' && mode != 'l') return 0;
  //cutresult location_top=last;
  //save();
  //location_next.loc[ncut]=0;
  //cutResult(location_next);
  double val_chosen=(*this.*valPointer)();
  double Sw_top=Sw();
  cutresult location_chosen=last;
  cutlocation location_next=last.location();
  
  for(location_next.loc[ncut]=0; int(location_next.loc[ncut])<=m_cuts->location_max(ncut); location_next.loc[ncut]++)
  {
    cutResult(location_next);
    if(location_next.loc[ncut]==0) Sw_top=Sw();
    //std::cout << "loc " << location_next.loc[ncut] << " val " << ((*this.*valPointer)()) << " SoRSB " << SoRSB() << std::endl;
    if(mode=='h')
    {
      if((*this.*valPointer)()>=val_chosen)
	    {
	      location_chosen=last;
	      val_chosen=(*this.*valPointer)();
	    }
    }
    else if(mode == 'l')
    {
      if((*this.*valPointer)()<=val_chosen)
	    {
	      location_chosen=last;
	      val_chosen=(*this.*valPointer)();
	    }
    }
    
    
  }
  save(location_chosen);
  load(location_chosen);
  
  //std::cout << "chosen " << location_chosen[ncut] << " val " << val_chosen << " SoRSB " << SoRSB() << std::endl;
  
  return (Sw_top-Sw());  
  
  
}

bool scan::nextByVal(const unsigned int ncut, double (scan::* valPointer)(void), char mode )
{
  if(ncut > m_ncuts) return false;
  if(mode != 'h' && mode != 'l') return false;
  const cutlocation location_top=last.location();
  //save();
  //location_next.loc[ncut]=0;
  //cutResult(location_next);
  double val_top=(*this.*valPointer)();
  double val_chosen_up=val_top;
  double val_chosen_down=val_top;
  cutresult location_chosen_up=last;
  cutresult location_chosen_down=last;
  cutlocation location_next=last;
  const unsigned int location_cut_top=location_top.loc[ncut];
  bool flag=false; //will do at least 2 steps up and down
  
  for(location_next.loc[ncut]=(location_cut_top+1); 
      int(location_next.loc[ncut])<=m_cuts->location_max(ncut); 
      location_next.loc[ncut]++)//go right
  {
    cutResult(location_next);
    if(mode=='h')
    {
      if((*this.*valPointer)()>=val_chosen_up)
	    {
	      location_chosen_up=last;
	      val_chosen_up=(*this.*valPointer)();
	    }
      else if(flag) break;
      else flag=true;
    }
    else if(mode == 'l')
    {
      if((*this.*valPointer)()<=val_chosen_up)
	    {
	      location_chosen_up=last;
	      val_chosen_up=(*this.*valPointer)();
	    }
      else if(flag) break;
      else flag=true;
    }
      

  }
  flag=false; //will do at least 2 steps down
  //save minimum point
  save(location_chosen_up);
  location_next.loc[ncut]=0;
  //load();
  cutResult(location_next);
  //save();
  //cutresult lowest=last;
  for(location_next.loc[ncut]=(location_cut_top-1); int(location_next.loc[ncut])>=0; location_next.loc[ncut]--)//go left
  {
    //load(lowest);
    cutResult(location_next);
    if(mode=='h')
    {
      if((*this.*valPointer)()>val_chosen_down)
	    {
	      location_chosen_down=last;
	      val_chosen_down=(*this.*valPointer)();
	    }
      else if(flag) break;
      else flag=true;
    }
    else if(mode == 'l')
    {
      if((*this.*valPointer)()<val_chosen_down)
	    {
	      location_chosen_down=last;
	      val_chosen_down=(*this.*valPointer)();
	    }
      else if(flag) break;
      else flag=true;
    }
      

  }
  save(location_chosen_down);
  if(mode == 'l')  
  {
    if(val_chosen_down < val_chosen_up) return load(location_chosen_down);
    else return load(location_chosen_up);
  }
  else if(mode == 'h')  
  {
    if(val_chosen_down > val_chosen_up) return load(location_chosen_down);
    else return load(location_chosen_up);
  }
  
  return false;  
  
  
}

bool scan::StatsScan(const unsigned int ncut, const std::string & directory, bool saveAll)
{
  if(!m_data || !m_cuts || ncut>m_ncuts) return false;
  const cutlocation location_top = last.location().loc;
  //save();
  cutresult top_result=last;
  cutlocation location_next=last.location().loc;
  location_next.loc[ncut]=0;
  
  
  //std::vector<int> ses(0);
  //std::vector<double> dses(0);
  //std::vector<int> bes(0);
  //std::vector<double> dbes(0);
  std::vector<double> val(0);
  std::vector<double> sw(0);
  std::vector<double> csw(0);
  std::vector<double> dsw(0);
  std::vector<double> bw(0);
  std::vector<double> cbw(0);
  std::vector<double> dbw(0);
  std::vector<double> bce(0);
  std::vector<double> bos(0);
  std::vector<double> dbos(0);
  std::vector<double> sob(0);
  std::vector<double> dsob(0);
  std::vector<double> eff(0);
  std::vector<double> deff(0);
  std::vector<double> effb(0);
  std::vector<double> deffb(0);
  std::vector<double> sorsb(0);
  std::vector<double> dsorsb(0);
  std::vector<double> csorsb(0);
  
  //load();
  cutResult(location_next);//force the loosest
  if(saveAll) save();
  
  val.reserve(m_cuts->location_max(ncut)+1);
  sw.reserve(m_cuts->location_max(ncut)+1);
  csw.reserve(m_cuts->location_max(ncut)+1);
  dsw.reserve(m_cuts->location_max(ncut)+1);
  bce.reserve(m_cuts->location_max(ncut)+1);
  bw.reserve(m_cuts->location_max(ncut)+1);
  cbw.reserve(m_cuts->location_max(ncut)+1);
  dbw.reserve(m_cuts->location_max(ncut)+1);
  sob.reserve(m_cuts->location_max(ncut)+1);
  dsob.reserve(m_cuts->location_max(ncut)+1);
  bos.reserve(m_cuts->location_max(ncut)+1);
  dbos.reserve(m_cuts->location_max(ncut)+1);
  eff.reserve(m_cuts->location_max(ncut)+1);
  deff.reserve(m_cuts->location_max(ncut)+1);
  effb.reserve(m_cuts->location_max(ncut)+1);
  deffb.reserve(m_cuts->location_max(ncut)+1);
  sorsb.reserve(m_cuts->location_max(ncut)+1);
  dsorsb.reserve(m_cuts->location_max(ncut)+1);
  csorsb.reserve(m_cuts->location_max(ncut)+1);
  
  //ses.push_back(S());
  //dses.push_back(dS());
  //bes.push_back(B());
  //dbes.push_back(dB());
  val.push_back(m_cuts->decodeValue(ncut,last.location().loc[ncut]));
  sw.push_back(Sw());
  if(m_useCustom) csw.push_back(CustomS());
  bw.push_back(Bw());
  dbw.push_back(dBw());
  if(m_useCustom) cbw.push_back(CustomB());
  bce.push_back(Bw_C_E());
  sob.push_back(SoB());
  dsob.push_back(dSoB());
  bos.push_back(BoS());
  dbos.push_back(dBoS());
  eff.push_back(Eff());
  deff.push_back(dEff());
  effb.push_back(EffB());
  deffb.push_back(dEffB());
  sorsb.push_back(SoRSB());
  dsorsb.push_back(dSoRSB());
  if(m_useCustom) csorsb.push_back(CustomSoRSB());
  
  //std::cout << " --> scanning" << std::flush;
  
  while(int(last.location().loc[ncut])<=m_cuts->location_max(ncut) && nextByDiff(ncut))
  {
    if(saveAll) save();
    //std::cout << "." << std::flush;
    //ses.push_back(S());
    //dses.push_back(dS());
    //bes.push_back(B());
    //dbes.push_back(dB());
    val.push_back(m_cuts->decodeValue(ncut,last.location().loc[ncut]));
    sw.push_back(Sw());
    dsw.push_back(dSw());
    if(m_useCustom) csw.push_back(CustomS());
    bce.push_back(Bw_C_E());
    bw.push_back(Bw());
    dbw.push_back(dBw());
    if(m_useCustom) cbw.push_back(CustomB());
    sob.push_back(SoB());
    dsob.push_back(dSoB());
    bos.push_back(BoS());
    dbos.push_back(dBoS());
    eff.push_back(Eff());
    deff.push_back(dEff());
    effb.push_back(EffB());
    deffb.push_back(dEffB());
    sorsb.push_back(SoRSB());
    dsorsb.push_back(dSoRSB());
    if(m_useCustom) csorsb.push_back(CustomSoRSB());
  }
  
  //std::cout << "done" << std::endl;

  if(m_plots)
  {
    
    std::vector<double> efficacy(0);
    std::vector<double> efficacy_x(0);
    int loc_e=-1;
    double bws0=bw[0];
    double effs0=eff[0];
    for(unsigned int j=1; j<eff.size(); j++)
    {
      if (bws0==bw[j]) continue;
      if (effs0==eff[j]) continue;
      if (bws0==0.0) break;
      if (effs0==0.0) break;
      
      double efficacy_val=(bws0-bw[j])*effs0/((effs0-eff[j])*bws0);
      efficacy_x.push_back(val[j]);
      efficacy.push_back(efficacy_val);
      bws0=bw[j];
      effs0=eff[j];
      if (loc_e<0 and j>=location_top.loc[ncut]) loc_e=efficacy.size()-1;
      
    }
    unsigned int loc_j=(unsigned int) loc_e;
    
    
    std::vector<double> none(0);
    std::string name=directory;
    std::string acut="";
    name.append("/");
    name.append(m_cuts->cut_name(ncut));
    acut.append(m_cuts->cut_name(ncut));
    m_plots->mkdir(name);
    m_plots->cd(name);
      
    m_plots->plot(location_top.loc[ncut],bw, eff, dbw, deff, "RateScan","B","Efficiency",name);
    m_plots->plot(location_top.loc[ncut],eff, effb, deff, deffb, "RoC","Signal Efficiency","Background Efficiency",name);
    m_plots->plot(location_top.loc[ncut],val, sorsb, none, dsorsb, "SoRSB",acut,"S/sqrt(S+B)",name);
    if(m_useCustom) m_plots->plot(location_top.loc[ncut],val, csorsb, "CustomSoRSB",acut,"Custom S/sqrt(S+B)",name);
    if(m_useCustom) m_plots->plot(location_top.loc[ncut],val, csw, "CustomS",acut,"Custom S",name);
    if(m_useCustom) m_plots->plot(location_top.loc[ncut],val, cbw, "CustomB",acut,"Custom B",name);
    m_plots->plot(location_top.loc[ncut],val, sw, none, dsw, "Signal",acut,"S (weighted)",name);
    m_plots->plot(location_top.loc[ncut],val, bce, "BCE",acut,"B Cands/Event",name);
    m_plots->plot(location_top.loc[ncut],val, bw, none, dbw, "Background",acut,"B (weighted)",name);
    m_plots->plot(location_top.loc[ncut],val, eff, none, deff, "Eff",acut,"Signal Efficiency",name);
    m_plots->plot(location_top.loc[ncut],val, bos, none, dbos, "BoS",acut,"BoS",name);
    m_plots->plot(loc_j,efficacy_x, efficacy, "Efficacy",acut,"(b1-b2)s1/((s1-s2)b1)",name);
      
  }
  //return cutResult(location_top);
  //std::cout << "finished one scan loop, should now go back to zero " << std::endl;
  
  return load(top_result);
  
  
}

bool scan::Select100pc(void) 
{ 
  
  std::cout << "---------------------------------------------------------------" << std::endl;
  std::cout << "        FINDING 100% CUTS           " << std::endl;
  std::cout << "---------------------------------------------------------------" << std::endl;

  

  const cutlocation location_top=last.location();
  //save();
  load();
  //for(unsigned int k=0; k<m_location.size() ; k++) location_zero.push_back(0);
  std::cout << " --> iterating" << std::flush;

  for(unsigned int k=0; k<m_ncuts ; k++) {std::cout << "." << std::flush; if(!find100pc(k)) break;} 
  std::cout << "done" << std::endl;
  //cutResult(m_location,true);
  std::cout <<" ---> 100 % cuts are: " << std::endl;
  std::cout << m_cuts->decodeCuts(last) << std::endl;
  shortstats();
  save();
  
  std::cout << "---------------------------------------------------------------" << std::endl;
  return true; 
}

bool scan::find100pc(unsigned int ncut) 
{ 
  if(!m_data || !m_cuts || ncut>m_ncuts ) return false;
  if(S() != S0()) std::cout << "cannot find the 100%, you must relax the location to all the data first!" << std::endl;
  
  //const cut location_top=last.location();
  //save();
  cutresult tight_location = last;
  
  //location[ncut]=0;
  while(nextByDiff(ncut) && S() == S0())
  {
    tight_location=last;
  }
  
  save(tight_location);
  return load(tight_location);//will always be tighter
  
  //return true; 
}



bool scan::StatsScan(const std::string & directory, bool saveAll) 
{ 
  
  std::cout << "---------------------------------------------------------------" << std::endl;
  std::cout << "        STATS SCAN           " << std::endl;
  std::cout << "---------------------------------------------------------------" << std::endl;
  shortstats();
  std::cout << " --> scanning" << std::flush;
  if(saveAll) save();
  //bool saveAll=
  for(unsigned int k=0; k<m_ncuts ; k++)  {std::cout << "." << std::flush; if(!StatsScan(k,directory,saveAll)) break;}
  if(saveAll) m_scanned=true;
  std::cout << "done" << std::endl;
  std::cout << "---------------------------------------------------------------" << std::endl;
  return true; 
}

bool scan::nextByDiff(const unsigned int ncut, const int step)
{
  if(!m_data || !m_cuts || ncut>m_ncuts || step==0) return false;
  if((int(last.location().loc[ncut])+step)<0) return false;
  if(int(last.location().loc[ncut])+step>m_cuts->location_max(ncut)) return false;
  
  cutlocation location_next=last.location();
  location_next.loc[ncut]+=step;
  
  return cutResult(location_next);
  /*else 
    {
    load();
    return cutResult(location_next);
    }*/
  
  
}
		      
bool scan::PlotAll(const std::string & directory)
{
  if(!m_data || !m_cuts || !m_plots) return false;
  std::vector<TString> allnames=m_data->s_names();
  std::vector<TString> bnames=m_data->b_names();
  allnames.insert(allnames.end(), bnames.begin(), bnames.end());
  load(last);
  std::cout << " --> plotting" << std::flush;
  for(unsigned int k=0; k<m_ncuts;k++)
  {
    std::string thisname="";
    thisname.append(m_cuts->decodeName(k));
    //std::cout << "plotting " << thisname << std::endl;
      
    std::cout << "."<< std::flush;
      
    m_plots->plot(m_data->graphThis(thisname,last),allnames,thisname,directory);
  }
  for(unsigned int k=0; k<m_cuts->NPlots();k++)
  {
    std::string thisname="";
    thisname.append(m_cuts->plot_name(k));
    //std::cout << "plotting " << thisname << std::endl;
      
    std::cout << "."<< std::flush;
      
    m_plots->plot(m_data->graphThis(thisname,last),allnames,thisname,directory);
  }
  
  std::cout << "done" << std::endl;
  
  return true;
  
}

bool scan::PlotAllClever(const std::string & directory)
{
  if(!m_data || !m_cuts || !m_plots) return false;
  std::vector<TString> allnames=m_data->s_names();
  std::vector<TString> bnames=m_data->b_names();
  allnames.insert(allnames.end(), bnames.begin(), bnames.end());
  load(last);
  if(S()==0 || B()==0) return true;
  double min=min_weight()/2.;
  double max=max_weight();
  
  std::cout << " --> plotting" << std::flush;
  m_plots->cd(directory);
  for(unsigned int k=0; k<m_ncuts;k++)
  {
    std::string thisname="";
    thisname.append(m_cuts->decodeName(k));
    //std::cout << "plotting " << thisname << std::endl;
      
    std::cout << "." << std::flush;
      
    m_plots->plot(m_data->graphThis(thisname,last),allnames,"Full_"+thisname,min,max,true,directory);
    //std::cout << m_cuts->cut_range(k) << std::endl;
      
    if(m_cuts->location_max(k)>0
       && int(last.location().loc[k])!=int(m_cuts->location_max(k))
       ) m_plots->plot(m_data->graphThis(thisname,last,m_cuts->decodeValue(k,0),m_cuts->decodeValue(k,m_cuts->location_max(k))),
                  allnames,"Range_"+thisname,min,max,true,directory);
    //m_plots->plot(m_data->graphThis(thisname,last,m_cuts->cut_range(k)),allnames,"Range_"+thisname,min,max,true,directory);
      
  }
  for(unsigned int k=0; k<m_cuts->NPlots();k++)
  {
    std::string thisname="";
    thisname.append(m_cuts->plot_name(k));
    //std::cout << "plotting " << thisname << std::endl;
      
    std::cout << "."<< std::flush;
      
    m_plots->plot(m_data->graphThis(thisname,last),allnames,"Full_"+thisname,min,max,true,directory);


    if(m_cuts->plot_low(k)!=m_cuts->plot_hi(k)) m_plots->plot(
                                                              m_data->graphThis(thisname,last,
                                                                                m_cuts->plot_low(k),
                                                                                m_cuts->plot_hi(k)),
                                                              allnames,"Range_"+thisname,min,max,true,directory);
    //m_plots->plot(m_data->graphThis(thisname,last,m_cuts->plot_range(k)),allnames,"Range_"+thisname,min,max,true,directory);
  }
  std::cout << "done" << std::endl;
  return true;
  
}

double scan::min_weight()
{
  double retmin=m_data->s_weights(0)/S_C_E(0);
  for(unsigned int k=1; k<m_ndataS; k++)
  {
    if(m_data->s_weights(k)/S_C_E(k) < retmin) retmin=m_data->s_weights(k)/S_C_E(k);
  }
  for(unsigned int k=0; k<m_ndataB; k++)
  {
    if(m_data->b_weights(k)/B_C_E(k) < retmin) retmin=m_data->b_weights(k)/B_C_E(k);
  }
  return retmin;
}

double scan::max_weight()
{
  double retmax=last.S(0)*m_data->s_weights(0)/S_C_E(0);
  for(unsigned int k=1; k<m_ndataS; k++)
  {
    if(last.S(k)*m_data->s_weights(k)/S_C_E(k) > retmax) retmax=last.S(k)*m_data->s_weights(k)*S_C_E(k);
  }
  for(unsigned int k=0; k<m_ndataB; k++)
  {
    if(last.B(k)*m_data->b_weights(k)/B_C_E(k) > retmax) retmax=last.B(k)*m_data->b_weights(k)/B_C_E(k);
  }
  return retmax;
}

bool scan::ScanForBest(const unsigned int iterate, const char mode)
{
  if(mode != 'r' && mode != 's' && mode != 'b' && mode != 'c') { std::cout << "error, wrong mode" << std::endl; return false;}
  //if(freq > 1.) freq=1/freq; 
  if(m_cuts==NULL || m_data==NULL) return false;

  std::cout << "---------------------------------------------------------------" << std::endl;
  std::cout << "        SCAN FOR BEST           " << std::endl;
  std::cout << "---------------------------------------------------------------" << std::endl;
  
  std::cout << " --> chosen to look for best ";
  switch(mode)
  {
  case 'r' : std::cout << "S/sqrt(S+B)" <<std::endl; break;
  case 'c' : std::cout << "Custom S/sqrt(S+B)" <<std::endl; break;
  case 's' : std::cout << "SoB" <<std::endl; break;
  case 'b' : std::cout << "BoS" <<std::endl; break;
  }
  
  //save();
  cutresult top=last;
  
  const cutlocation location_top = top.location();
  //std::vector<unsigned int> location_last = location_top;
  cutlocation location_start= location_top;
  
  std::vector<double> dsws(m_ncuts,0);
  
  std::cout << " --> first:" << std::endl;
  std::cout << m_cuts->decodeCuts(location_top) << std::endl;
  shortstats();
  
  std::cout<< " --> find starting point" <<std::endl; 
  
  for(unsigned int k=0; k<m_ncuts; k++)
  {
    cutResult(location_top);
    switch(mode)
    {
    case 'r' : dsws[k]=nextByAllVal(k,& scan::SoRSB);  break;
    case 'c' : dsws[k]=nextByAllVal(k,& scan::CustomSoRSB);  break;
    case 's' : dsws[k]=nextByAllVal(k,& scan::SoB); break;
    case 'b' : dsws[k]=nextByAllVal(k,& scan::BoS,'l'); break;
    }
    location_start.loc[k]=last.location().loc[k];
    std::cout << k << " " 
              << int(location_start.loc[k])-int(location_top.loc[k]) 
              << "  " << m_cuts->decodeCuts(k, location_start.loc[k]) << "  ";
    shortstats();
  }
  
  std::cout<< " --> found starting point" <<std::endl; 
  cutResult(location_start);//will be tighter
  save();
  std::cout << m_cuts->decodeCuts(last) << std::endl;
  stats();
  
  std::cout<< " --> Iterating " << iterate <<std::endl; 
  
  for(unsigned int i=0; i<iterate; i++)
  {
    std::vector<unsigned int> location_order = orderHighest(dsws);
    cutlocation location_global=last.location().loc;
    cutlocation location_local=last.location().loc;

    for(unsigned int j=1; i>0 && j<iterate; j++) //local scan
    {
      std::cout<< "   +--> local iteration" <<std::endl; 
      const cutlocation location_last_local=last.location().loc;
      for(unsigned int k=0; k<location_order.size(); k++) //local scan
	    {
	      //location_last_local==last.location().loc;
	      unsigned int ncut = location_order[k];
	      switch(mode)
        {
        case 'r' : nextByVal(ncut,& scan::SoRSB); break;
        case 'c' : nextByVal(ncut,& scan::CustomSoRSB); break;
        case 's' : nextByVal(ncut,& scan::SoB); break;
        case 'b' : nextByVal(ncut,& scan::BoS,'l'); break;
        }
	      
	      std::cout << ncut << " " << int(location_last_local.loc[ncut])-int(last.location().loc[ncut]) 
                  << "  " << m_cuts->decodeCuts(ncut, last.location().loc[ncut]) << "  ";
	      shortstats();
	    }
      location_local=last.location().loc;
      if(location_local==location_last_local) {std::cout<< "   +--> local optimum" <<std::endl;  break; }
      
	  
    }
    if(i>0 && location_local==location_global)  
    {std::cout<< "   +--> optimum" <<std::endl;  break; } //if local gives same result as global, then this is an optimum
      
    //location_order = orderHighest(dsws);
    std::cout<< "   +--> global iteration" <<std::endl; 
    if(i>0) location_order = orderHighest(dsws);
    for(unsigned int k=0; k<location_order.size(); k++) //full scan
    {
      unsigned int ncut = location_order[k];
      switch(mode)
	    {
	    case 'r' : dsws[ncut]=nextByAllVal(ncut,& scan::SoRSB); break;
	    case 'c' : dsws[ncut]=nextByAllVal(ncut,& scan::CustomSoRSB); break;
	    case 's' : dsws[ncut]=nextByAllVal(ncut,& scan::SoB); break;
	    case 'b' : dsws[ncut]=nextByAllVal(ncut,& scan::BoS,'l'); break;
	    }
	  
      std::cout << ncut << " " 
                << int(location_local.loc[ncut])-int(last.location().loc[ncut]) 
                << "  " << m_cuts->decodeCuts(ncut, last.location().loc[ncut]) << "  ";
      shortstats();
    }
    location_global=last.location().loc;
    if(i>0 && location_local==location_global)  
    {std::cout<< "   +--> global optimum" <<std::endl;  break; } //if global gives same result as local, then this is an optimum
      
  }
  
  std::cout<< " --> done iteration, check convergence by randomising cuts" <<std::endl; 
  location_start=last.location().loc;
  cutresult found=last;
  save();
  
  std::vector<unsigned int> location_order = orderRandom();
  
  for(unsigned int k=0; k<location_order.size(); k++)
  {
    //location_last=location_best;
    unsigned int ncut = location_order[k];
    //if(int(last.location().loc[ncut])==m_cuts->location_max(ncut)) continue;
    switch(mode)
    {
    case 'r' : nextByAllVal(ncut,& scan::SoRSB); break;
    case 'c' : nextByAllVal(ncut,& scan::CustomSoRSB); break;
    case 's' : nextByAllVal(ncut,& scan::SoB); break;
    case 'b' : nextByAllVal(ncut,& scan::BoS,'l'); break;
    }
      
    std::cout << ncut << " " << int(location_start.loc[ncut])-int(last.location().loc[ncut]) 
              << "  " << m_cuts->decodeCuts(ncut, last.location().loc[ncut]) << "  ";
    shortstats();
  }
  if(last.location() != location_start) {std::cout << " --> DID NOT CONVERGE, check ranges and try again" << std::endl;}
  else std::cout << " --> Converged" << std::endl;;
  
  std::cout << m_cuts->decodeCuts(last) << std::endl;
  stats();
  
  std::cout << "---------------------------------------------------------------" << std::endl;
  return load(found); //do not return to the top
  
}


std::vector<unsigned int> scan::orderHighest(const std::vector<double> & values)
{ 
  //orders cuts with highest in the vector first
  std::vector<bool> used(values.size(),false);
  std::vector<unsigned int> cutorder(values.size(),0);
  Double_t h = values[0];
  UInt_t min = values.size()+1;
  for(UInt_t j=0; j<values.size(); j++)
  {
    for(min =0; min < values.size() && used[min]; min++); //move min to the lowest unused value
    h=values[min]; //check if this is the lowest
    for(UInt_t i=min; i<values.size(); i++)
    {
      //std::cout << "ordering " << i << " " << values[i] << std::endl;
	  
      if(used[i]==false && values[i]>h)
	    {
	      h = values[i];
	      min = i;
	    }
    }
      
    cutorder[j] = min;
    used[min]=true;
    //std::cout << "order " << j << " points to " << cutorder[j] << std::endl;;
      
  }
  //std::cout << "order highest is returning " << cutorder.size() << " " << cutorder[0] << std::endl;
  return cutorder;
  
}

std::vector<unsigned int> scan::orderRandom()
{ //randomises cut order
  TRandom3 rndGen(0);
  UInt_t randcut = UInt_t(rndGen.Rndm()*m_ncuts);
  
  std::vector<unsigned int> cutorder(m_ncuts,0);
  
  std::vector<bool> used(m_ncuts,false);
  for(UInt_t j=0; j<m_ncuts; j++)
  {
    while(used[randcut]==true) randcut = UInt_t(rndGen.Rndm()*m_ncuts);
    cutorder[j] = randcut;
    used[randcut]=true;
  }
  return cutorder;
}
bool scan::clean(std::vector<TEntryList *> & me)
{
  
  for(unsigned int i=0;i<me.size();i++) if(me[i]) 
  {
    me[i]->SetDirectory(0);
    delete me[i];
    me[i]=NULL;
  }
  return true;
  
}

bool scan::ChooseCuts(void)
{
  cutlocation dest=last.location();
  m_cuts->choose_cuts(dest);
  cutResult(dest);
  //load(dest);
  std::cout << "--------------------------" << std::endl;
  std::cout << m_cuts->decodeCuts(last) << std::endl;
  stats();
  //last=dest;
  //stats();
  return true;
  
}
