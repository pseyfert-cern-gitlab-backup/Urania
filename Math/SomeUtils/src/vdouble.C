#include <vector>

//std::vector<double> vdouble(Int_t n){ return std::vector<double>(n);};

//double vdouble(double &n){ return n*n;};

class vdouble 
{
public: 
  vdouble(int);
  ~vdouble();
  std::vector<double> V;
};

//creator
  vdouble::vdouble(int n) {
    V = std::vector<double>(n);
  };
//destructor
vdouble::~vdouble() {};
