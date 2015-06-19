#include "cuts.h"

//ClassImp(cuts)

cuts::cuts():
  m_ncuts(0),
  m_lower(0),
  m_higher(0),
  m_step(0),
  m_location_max(0),
  m_cut_names(0),
  m_plot_names(0),
  m_plot_range(0),
  Pstr("!"),
  Cstr("#"),
  And("&&"),
  Not("!"),
  delimiters(" \t\n;"),
  cutchars(" =><!"),
  m_prepared(false)
{
}

cuts::cuts(const std::string& cutListName):
  m_ncuts(0),
  m_lower(0),
  m_higher(0),
  m_step(0),
  m_location_max(0),
  m_cut_names(0),
  m_plot_names(0),
  m_plot_range(0),
  Pstr("!"),
  Cstr("#"),
  And("&&"),
  Not("!"),
  delimiters(" \t\n;"),
  cutchars(" =><!&|"),
  m_prepared(false)
{
  readCutFile(cutListName);
  //loadTuples();
}

bool cuts::readCutFile(const std::string& cutListName)
{
  
  m_prepared=false;
  std::ifstream fileStream1;
  std::string lineread;
  TString line;
  UInt_t nlines =0;
  TString word;
  
  fileStream1.open(cutListName.c_str());
  if (!fileStream1)
  {
    std::cout << "Error in opening cutfile" << std::endl;
    return EXIT_FAILURE;
  }
  
  int cutnum = 0;
  //int nlines = 0;
  while(!line.ReadLine(fileStream1).eof())
  {
    nlines++;
    TObjArray* Strings = line.Tokenize(delimiters);
    TIter iString(Strings);
    TObjString* os=0;
    os=(TObjString*)iString(); //#, !, or cutname
    word = os->GetString();
    if(word.BeginsWith(Pstr))
    {
      //std::cout << "plot found " << word << decodeName(word) << std::endl;
      //word=word.Remove(Pstr[0]);
      bool ranged=true;
      TString lower="", upper="";
      m_plot_names.push_back(decodeName(word));
      os=(TObjString*)iString();
      if(os) lower=os->GetString();
      else ranged=false;
	  
      os=(TObjString*)iString();
      if(ranged && os ) upper=os->GetString();
      else ranged=false;
      //m_plot_range.push_back(ranged);
      if(ranged && atof(lower)>atof(upper)) swap(lower,upper);
      
      if(!ranged)
      {
        m_plot_range.push_back("(1)");
        m_plot_low.push_back(0.);
        m_plot_hi.push_back(0.);
        
      }
      else
	    {
        stringstream ss (stringstream::in | stringstream::out);
	      m_plot_range.push_back(m_plot_names.back()+">"+lower+And+m_plot_names.back()+"<"+upper);
        double low;
        ss << lower << std::endl;
        ss >> low;
        double hi;
        ss << upper << std::endl;
        ss >> hi;
        
        m_plot_low.push_back(low);
        m_plot_hi.push_back(hi);
        
	    }
	  
	  
    }
    else if(!word.BeginsWith(Cstr))
    {
      m_cut_names.push_back(word);
      os=(TObjString*)iString();
      m_lower.push_back(atof(os->GetString()));
      os=(TObjString*)iString();
      m_higher.push_back(atof(os->GetString()));
      os=(TObjString*)iString();
      m_step.push_back(atof(os->GetString()));
      //m_location_max.push_back(abs(int()));
      unsigned int location_max=int(fabs((m_higher[m_higher.size()-1]-m_lower[m_lower.size()-1])/m_step[m_step.size()-1])+0.5);
      m_location_max.loc.push_back(location_max);
      cutnum++;
	  
    }
  }

  
  
  fileStream1.close();
  m_prepared=(cutnum>0 && m_lower.size()==m_higher.size() &&  m_step.size()==m_lower.size() && m_lower.size()==m_cut_names.size() && m_location_max.loc.size()==m_cut_names.size());
  m_ncuts=cutnum;
  return m_prepared;
  
}


//bool cuts::entries(TString & cut, std::vector<int> & s, std::vector<int> b, std::vector<double>& sw, std::vector<double> & bw );
bool cuts::print() const
{
  //std::cout<< "in print" <<std::endl;
  if(!m_prepared) return 0;
  //std::cout<< "in print" <<std::endl;
  
  for(UInt_t k = 0; k<m_cut_names.size(); k++)
  {
    std::cout << "\t" << k << " " << decodeCuts(k,0) << endl;
  }
  std::cout << " ---> extra plots" << std::endl;
  for(UInt_t k = 0; k<m_plot_names.size(); k++)
  {
    std::cout << "\t" << k << " " << m_plot_names[k] << endl;
  }
  
  return true;
    
}

bool cuts::print(data* tuples) const
{
  //std::cout<< "in print" <<std::endl;
  if(!m_prepared) return 0;
  //std::cout<< "in print" <<std::endl;
  
  cutresult output(tuples->NSFiles(),tuples->NBFiles(),NCuts());
  
  for(UInt_t k = 0; k<m_cut_names.size(); k++)
  {
    TString thisCut = decodeCuts(k,0);
      
    tuples->print(thisCut,output);
      
  }
  
  return true;
    
}

double cuts::decodeValue(const unsigned int ncut, const unsigned int location) const
{
  if(!m_prepared) return 0;
  //char dtoc[20];
  if(location > m_location_max.loc[ncut]) return (m_lower[ncut]+m_step[ncut]*m_location_max.loc[ncut]);
  else return (m_lower[ncut]+m_step[ncut]*location);
  
}

TString cuts::decodeName(const unsigned int ncut) const
{
  if(!m_prepared) return "";
  if(ncut>=m_cut_names.size()) return "";
  //char dtoc[20];
  TString ret=m_cut_names[ncut];
  //loop twice to catch != and ==, and <= etc
  //for(int i=0; cutchars[i]!='\0'; i++) {
  //  char* chars="i";
  //  chars[0]=cutchars[i];
  //  ret.ReplaceAll(chars,1,NULL,0);
  //}
  //ret.ReplaceAll(cutchars[i]//ret=TString(ret.Strip(TString::kTrailing,cutchars[i]));
  for(int i=0; cutchars[i]!='\0'; i++) ret=TString(ret.Strip(TString::kTrailing,cutchars[i]));
  for(int i=0; cutchars[i]!='\0'; i++) ret=TString(ret.Strip(TString::kTrailing,cutchars[i]));
  //ret=ret.ReplaceAll("(",1,NULL,0);
  //ret=ret.ReplaceAll(")",1,NULL,0);
  //ret=TString(ret.Strip(TString::kTrailing,')'));
  return ret;
  
  //TObjArray* Strings = m_cut_names[ncut].Tokenize(cutchars);
  //TIter iString(Strings);
  //TObjString* os=0;
  //os=(TObjString*)iString(); 
  //return(os->GetString());
  
}
TString cuts::decodeName(const TString acut) const
{
  //std::cout << "decodeName " << acut << std::endl;
  
  //if(!m_prepared) return "";
  //if(ncut>=m_cut_names.size()) return "";
  //char dtoc[20];
  TObjArray* Strings = acut.Tokenize(cutchars);
  if(!Strings) return acut;
  
  TIter iString(Strings);
  if (Strings->IsEmpty()) return acut;

  
  TObjString* os=0;
  os=(TObjString*)iString(); 
  if(os->GetString()!=Pstr) return os->GetString();
  
  os=(TObjString*)iString(); 
  //std::cout << "decoded to " <<  os->GetString()<< std::endl; 
  return(os->GetString());
  
}
TString cuts::decodeCuts(const unsigned int ncut, const unsigned int location) const
{
  if(!m_prepared) return "";
  TString cutstring=m_cut_names[ncut];
  std::stringstream ss (stringstream::in | stringstream::out);
  std::string dtoc;
  ss << decodeValue(ncut,location);
  ss >> dtoc;
  
  //char dtoc[20];
  //if(location > m_location_max[ncut]) sprintf(dtoc,"%f",decodeValue(ncut,m_location_max[ncut]));
  //else 
  //sprintf(dtoc,"%f",decodeValue(ncut,location));
  
  cutstring.Append(dtoc);
  return cutstring;
  
}
TString cuts::decodeCuts(const cutresult& location) const
{
  return decodeCuts(location.location());
}

TString cuts::decodeCuts(const cutlocation& location) const
{
  if(!m_prepared) return "";
  if(m_cut_names.size()!=location.loc.size()) return "";
  
  TString cutstring="";
  for(UInt_t k = 0; k<(m_cut_names.size()-1); k++)
  {
    cutstring.Append(decodeCuts(k, location.loc[k]));
    cutstring.Append(And);
  }
  cutstring.Append(decodeCuts(m_cut_names.size()-1, location.loc[m_cut_names.size()-1])); //last one with no And
  
  return cutstring;
  
}

bool cuts::arrangeList(data* tuples)
{
  if(!m_prepared) return 0;
  
  for(UInt_t k = 0; k<m_cut_names.size(); k++)
  {
    cutresult lower(tuples->NSFiles(),tuples->NBFiles(),m_ncuts);
      
    //unsigned int location_max=abs(int((m_higher[i]-m_lower[i])/m_step[i]))+1;
    //      m_location_max.push_back(abs(int((m_higher[i]-m_lower[i])/m_step[i])+1));
    TString lowcut=decodeCuts(k,0);
      
    if(!tuples->entries(lowcut,lower)) {swap(m_higher[k],m_lower[k]); continue;};

    cutresult higher(tuples->NSFiles(),tuples->NBFiles(),m_ncuts);
    TString highcut=decodeCuts(k,m_location_max.loc[k]);
    if(!tuples->entries(highcut,higher)) continue;

    //std::cout << m_cut_names[k] << " sl " << sl << " sh " << sh <<std::endl;
    //std::cout << m_cut_names[k] << " bl " << bl << " bh " << bh <<std::endl;
    if(higher.S()>lower.S()) swap(m_higher[k],m_lower[k]); //wrong way round
    else if(higher.S()==lower.S() && higher.B()>lower.B()) swap(m_higher[k],m_lower[k]); //still wrong way round
    if(m_lower[k]<m_higher[k]) m_step[k]=fabs(m_step[k]);//correct stepping direction
    else m_step[k]=-1*fabs(m_step[k]);//correct stepping direction
  }
  return true;
  
}

bool cuts::swap(double &l, double&h)
{
  double k=l;
  l=h;
  h=k;
  return true;
}

bool cuts::swap(TString &l, TString&h)
{
  TString k=l;
  l=h;
  h=k;
  return true;
}


bool cuts::cut_result(data* tuples, cutresult &output) const
{
  if(!m_prepared) return false;
  if(output.location().loc.size()!=m_cut_names.size()) return false;
  if(output.location()>m_location_max) return false;
  TString thisCut=decodeCuts(output.location());
  return tuples->entries(thisCut,output);
}
bool cuts::cut_result(data* tuples, const cutresult &input, cutresult &output) const
{
  if(!m_prepared) return false;
  if(output.location().loc.size()!=m_cut_names.size()) return false;
  if(output.location()>m_location_max) return false;
  TString thisCut=decodeCuts(output.location());
  return tuples->entries(thisCut,input,output);
}

bool cuts::choose_cuts(cutlocation &res) const
{
  for(int i=0; i<m_ncuts; i++)
  {
    unsigned int choice=0;
    if (m_location_max.loc[i]>0)
    {
      
      std::cout << "----------------------------- Choose a cut  --------------------------" << std::endl;
      for(unsigned int v=0; v<=m_location_max.loc[i]; v++)
      {
        std::cout << v << " : " << decodeCuts(i, v) << std::endl;
      }
      std::cout << "Choice? : ";
      std::cin >> choice;
      if(choice > m_location_max.loc[i]) 
      {
        std::cout << "error, try again " << std::endl;
        i--;
        continue;
      }
    }
    
    res.loc[i]=choice;
    
  }
  return true;
  
}

