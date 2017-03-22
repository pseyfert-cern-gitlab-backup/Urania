#include "Calibration.hh"

#include <iostream>
#include <iomanip>

namespace Espresso 
{
  
  std::ostream& operator<< (std::ostream& os, const Calibration& cal) 
  {
    cal.print(os);
    return os;
  }
  
}

using namespace Espresso;

void Calibration::print(std::ostream& os) const {
  os << std::right;
  int numParams = this->NumParams();
  os << " -- PARAMETER VALUES -- " << std::endl;
  for (int i = 0; i < numParams; i++) 
  {
    os << "p" << i << " = " << std::setprecision(5) << this->GetCoeff(i)
       << " +-" << std::setprecision(5) << this->GetError(i)
       << std::endl;
  }
  os << std::endl;
  os << " -- PARAMETER DELTA VALUES -- " << std::endl;  
  for (int i = 0; i < numParams; i++) 
  {
    os << "Δp" << i << " = " << std::setprecision(5) << this->GetDeltaCoeff(i)
       << " +-" << std::setprecision(5) << this->GetDeltaError(i)
       << std::endl;
  }
  os << std::endl;
  os << " -- CORRELATION MATRIX -- " << std::endl;
  for (int n = -1; n < 2*numParams; n++) {
    for (int m = -1; m < 2*numParams; m++) {
      // default widths
      if (m == -1)
        os << std::setw(5) << std::setprecision(5);
      else if (m == 0)
        os << std::setw(5) << std::setprecision(5);
      else
        os << std::setw(16) << std::setprecision(5);

      // values
      if (n == -1 and m == -1)
        os << std::setw(5) << "";
      else if (n == -1 and m == 0)
        os << std::setw(4) << "p" << std::setw(1) << m;
      else if (n == -1 and m < numParams)
        os << std::setw(15) << "p" << std::setw(1) << m;
      else if (n == -1)
        os << std::setw(16) << "Δp" << std::setw(1) << (m-numParams);
      else if (m == -1 and n < numParams)
        os << std::setw(4) << "p" << std::setw(1) << n;
      else if (m == -1)
        os << std::setw(5) << "Δp" << std::setw(1) << (n-numParams);
      else if (m < n)
        os << " ---";
      else if (m == n)
        os << "1";
      else if (m < numParams)
        os << this->GetCorrelation(n,m);
      else if (n < numParams)
        os << this->GetCrossCorrelation(n,m-numParams);
      else
        os << this->GetDeltaCorrelation(n-numParams,m-numParams);
    }
    os << std::endl;
  }
  os << std::endl;
    
}
