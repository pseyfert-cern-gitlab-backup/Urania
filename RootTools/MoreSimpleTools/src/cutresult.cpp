#include "cutresult.h"
#include "cutlocation.h"

//ClassImp(cutresult)

cutresult::cutresult():
 m_location(0),
 m_cs(0),
 m_cb(0),
 m_s_ents(0),
 m_b_ents(0)
{

}
cutresult::cutresult(size_t s_size, size_t b_size, size_t c_size):
 m_location(c_size, 0),
 m_cs(s_size,1.),
 m_cb(b_size,1.),
 m_s_ents(s_size, std::vector<unsigned long>(0)),
 m_b_ents(b_size, std::vector<unsigned long>(0))
{

}
cutresult::cutresult(const cutlocation& location,size_t s_size,size_t b_size):
 m_location(location),
 m_cs(s_size,1.),
 m_cb(b_size,1.),
 m_s_ents(s_size, std::vector<unsigned long>(0)),
 m_b_ents(b_size, std::vector<unsigned long>(0))
{
  
}
cutresult::cutresult(const cutlocation & location,
	    const std::vector< std::vector<unsigned long> > & ents_s,
            const std::vector< std::vector<unsigned long> > & ents_b,
	    const std::vector<double> & cand_s,
	    const std::vector<double> & cand_b):
 m_location(location),
 m_cs(cand_s),
 m_cb(cand_b),
 m_s_ents(ents_s),
 m_b_ents(ents_b)
{
}

//void cutresult::copyFrom(const cutresult& other)
//{
//  m_location=other.m_location;
//  m_cs=other.m_cs;
//  m_cb=other.m_cb;
//  m_s_ents=other.m_s_ents;
//  m_b_ents=other.m_b_ents;
//}

int cutresult::S() const
{
  int m_S_sum=0;
  
  for(unsigned int k=0; k<m_s_ents.size(); k++)
    {
      m_S_sum+=m_s_ents[k].size();
    }
  
  //std::cout << "calc S " << m_S_sum << std::endl;
  return m_S_sum;
  
}

int cutresult::B() const
{
  int m_B_sum=0;
  
  for(unsigned int k=0; k<m_b_ents.size(); k++)
    {
      m_B_sum+=m_b_ents[k].size();
    }
  
  return m_B_sum;
}

bool cutresult::clear()
{
  for(unsigned int i=0; i< m_s_ents.size(); i++) m_s_ents[i].clear();
  for(unsigned int i=0; i< m_b_ents.size(); i++) m_b_ents[i].clear();
  for(unsigned int i=0; i< m_cs.size(); i++) m_cs[i]=1.;
  for(unsigned int i=0; i< m_cb.size(); i++) m_cb[i]=1.;
  return true;
}

cutresult& cutresult::intersect(const cutresult& other)
{
  if ((*this)==(other)) return *this;
  if(other.m_location.loc.size()!=m_location.loc.size() ||
     other.m_s_ents.size()!=m_s_ents.size() ||
     other.m_b_ents.size()!=m_b_ents.size())
    {
      std::cout << "error in intersection, mismatched results" << std::endl;
      clear();
      return *this;
    }
  for(unsigned int i=0; i<m_s_ents.size(); i++)
    {
      std::vector<unsigned long> intersection(0);
      std::set_intersection(m_s_ents[i].begin(),m_s_ents[i].end(),
			    other.m_s_ents[i].begin(), other.m_s_ents[i].end(),
			    std::insert_iterator< std::vector<unsigned long> >(intersection,intersection.begin()));
      m_s_ents[i]=intersection;
    }
  
  for(unsigned int i=0; i<m_b_ents.size(); i++)
    {
      std::vector<unsigned long> intersection(0);
      std::set_intersection(m_b_ents[i].begin(),m_b_ents[i].end(),
			    other.m_b_ents[i].begin(), other.m_b_ents[i].end(),
			    std::insert_iterator< std::vector<unsigned long> >(intersection,intersection.begin()));
      m_b_ents[i]=intersection;
    }
  m_location=m_location^other.m_location;
  return *this;
}
bool cutresult::elisttovec(TEntryList * elist, std::vector<unsigned long> & avec) 
{
  if(!elist) {std::cout <<"error finding elist"<<std::endl; return false; };
  avec.clear();
  avec.reserve(elist->GetN());
  
  for(unsigned long ent=0; ent< (unsigned long) elist->GetN(); ent++)
    {
      if(!ent) avec.push_back(elist->GetEntry(ent));
      else avec.push_back(elist->Next());
    }
  elist->GetEntry(0);
  return (avec.size()==(unsigned long) elist->GetN());
}

TEntryList * cutresult::vectoelist(const std::vector<unsigned long> & avec, const TTree* atree) const
{
  return vectoelist(avec.begin(),avec.end(),atree);
}
TEntryList * cutresult::vectoelist(const std::vector<unsigned long> * avec, const TTree* atree) const
{
  return vectoelist(avec->begin(),avec->end(),atree);
}
TEntryList * cutresult::vectoelist(const std::vector<unsigned long>::const_iterator & beg,
                                   const std::vector<unsigned long>::const_iterator & end, 
                                   const TTree* atree) const
{
  TEntryList * elist=new TEntryList(atree);
  if(!elist) {std::cout <<"error creating elist"<<std::endl; return NULL; };
  
  elist->SetDirectory(0);
  for(std::vector<unsigned long>::const_iterator ent=beg; ent<end; ent++)
    {
      elist->Enter(*ent);
    }
  return elist;
}

bool cutresult::elisttoset(TEntryList * elist, std::set<unsigned long> & aset) 
{
  if(!elist) {std::cout <<"error finding elist"<<std::endl; return false; };
  aset.clear();
  //aset.reserve(elist->GetN());
  
  for(unsigned long ent=0; ent< (unsigned long) elist->GetN(); ent++)
    {
      if(!ent) aset.insert(elist->GetEntry(ent));
      else aset.insert(elist->Next());
    }
  elist->GetEntry(0);
  return (aset.size()==(unsigned long) elist->GetN());
}

TEntryList * cutresult::settoelist(const std::set<unsigned long> & aset, const TTree* atree) const
{
  return settoelist(aset.begin(),aset.end(),atree);
}
TEntryList * cutresult::settoelist(const std::set<unsigned long> * aset, const TTree* atree) const
{
  return settoelist(aset->begin(),aset->end(),atree);
}
TEntryList * cutresult::settoelist(const std::set<unsigned long>::const_iterator & beg,
                                   const std::set<unsigned long>::const_iterator & end, 
                                   const TTree* atree) const
{
  TEntryList * elist=new TEntryList(atree);
  if(!elist) {std::cout <<"error creating elist"<<std::endl; return NULL; };
  
  elist->SetDirectory(0);
  for(std::set<unsigned long>::const_iterator ent=beg; ent!=end; ent++)
    {
      elist->Enter(*ent);
    }
  return elist;
}
