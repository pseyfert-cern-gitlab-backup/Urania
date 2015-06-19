#include "cutlocation.h"
#include "cutresult.h"

//ClassImp(cutlocation)

cutlocation::cutlocation():
  loc(0)
{
}

cutlocation::cutlocation(const unsigned int & ncuts, const unsigned int & nval):
  loc(int(ncuts),nval)
{
}

cutlocation::cutlocation(const unsigned int & ncuts):
  loc(int(ncuts),0)
{
}

cutlocation::cutlocation(const std::vector<unsigned int > & location):
  loc(location)
{
}

cutlocation::cutlocation(const cutresult & location):
  loc(location.location().loc)
{
}

cutlocation& cutlocation::operator=(const cutresult & newloc) {  return (*this)=newloc.location(); };

bool cutlocation::operator>(const  cutlocation & compare) const 
{
  //std::cout << *this << ">" << compare << "=";
  if(sum()<compare.sum())return false; //{std::cout << false << std::endl; return false;};
  
  if(loc==compare.loc) return false; //{std::cout << false << std::endl; return false;};
  
  if(loc.size()!=compare.loc.size()) return false; //{std::cout << false << std::endl; return false;};
  
  for(unsigned int i=0;i<loc.size();i++)
    {
      if(loc[i]<compare.loc[i]) return false; //{std::cout << false << std::endl; return false;};
    }
  //std::cout << true << std::endl;
  return true;
  
}
bool cutlocation::operator==(const std::vector<unsigned int> & compare) const 
{
  if(loc.size()!=compare.size()) return false; //{std::cout << false << std::endl;return false;};
  for(unsigned int i=0;i<loc.size();i++)
    {
      if(loc[i]!=compare[i]) return false; //{std::cout << false << std::endl;return false;};
    }
  //std::cout << true << std::endl;
  return true;
}
bool cutlocation::operator!=(const std::vector<unsigned int> & compare) const 
{
  return (!((*this)==compare)); 
}
bool cutlocation::operator<(const  cutlocation & compare) const 
{
  //std::cout << *this << "<" << compare << "=";
  if(sum()>compare.sum()) return false; //{std::cout << false << std::endl;return false;};
  
  if(loc==compare.loc) return false; //{std::cout << false << std::endl;return false;};
  if(loc.size()!=compare.loc.size()) return false; //{std::cout << false << std::endl;return false;};
  for(unsigned int i=0;i<loc.size();i++)
    {
      if(loc[i]>compare.loc[i]) return false; //{std::cout << false << std::endl;return false;};
    }
  //std::cout << true << std::endl;
  return true;
}
cutlocation cutlocation::operator^(const std::vector<unsigned int > & compare) const 
{
  if(compare.size()!=loc.size()) return cutlocation();
  cutlocation toreturn(loc.size());
  for(unsigned int i=0;i<loc.size();i++)
    {
      if(loc[i]>compare[i]) toreturn.loc[i]=loc[i];
      else toreturn.loc[i]=compare[i];
    }
  return toreturn;
}

bool cutlocation::operator!=(const cutresult& compare) const 
{
  return (*this)!=compare.location();
}

bool cutlocation::operator==(const cutresult& compare) const 
{
  return (*this)==compare.location();
}
