#ifndef CONVERT_H
#define CONVERT_H

#include <iostream>
#include <sstream>
#include <string>
#include <stdexcept>

using namespace std;
 
class BadConversion : public runtime_error 
{
 public:
  BadConversion(string const& s)
    : runtime_error(s)
    { }
};

inline string stringify(double x, int y)
{
   ostringstream o;
   o.setf(ios::fixed,ios::floatfield);
   o.precision(y);
   if (!(o << x))
     throw BadConversion("stringify(double)");
   return o.str();
} 

#endif
