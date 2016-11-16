// Include files 



// local
#include "Measurement.h"
#include <iostream>
#include <sstream>
#include <cmath>

using namespace std;

//-----------------------------------------------------------------------------
// Measurement
// A class to handle authomatic error propagation with normal operations
// 2013-03-24 : Francesco Dettori
// 2013-05-29 : Maximilian Schlupp
//-----------------------------------------------------------------------------

//=============================================================================
// Standard constructor, initializes variables
//=============================================================================
Measurement::Measurement(double value, double error){
  m_value = value;
  m_errors[0] = m_errors[1] = abs( error );
  m_errors[2] = m_errors[3] = 0;
  m_scheme = 0;
}

//=============================================================================
// Overloaded constructors
Measurement::Measurement(double value, double first_error, double second_error, int scheme){
  //  scheme = 1  - Asymmetric errors
  //  scheme = 2  - statistical and systematic errors
  m_value = value;
  m_scheme = scheme;
  if(m_scheme & 1){
    m_errors[0] = abs( first_error );
    m_errors[1] = abs( second_error );
    m_errors[2] = m_errors[3] = 0;
  }else{
    m_errors[0] = abs( first_error );
    m_errors[1] = abs( first_error );
    m_errors[2] = abs( second_error );
    m_errors[3] = abs( second_error );
  }
  
}

Measurement::Measurement(double value, 
			 double first_error, double second_error, 
			 double third_error, double fourth_error){
  m_value = value;
  m_errors[0] = abs( first_error ) ;
  m_errors[1] = abs( second_error );
  m_errors[2] = abs( third_error );
  m_errors[3] = abs( fourth_error );
  m_scheme = 3;
}

Measurement Measurement::AMeasurement(double value, double first_error, double second_error){
  // Asymmetric measurement constructor 
  return Measurement(value, first_error, second_error, 1);
}

Measurement Measurement::SMeasurement(double value, double first_error, double second_error){
  // Systematic error measurement constructor 
  return Measurement(value, first_error, second_error, 2);
}

Measurement Measurement::Efficiency(double eff, double n_tot){
  // Special case for a measurement of an efficiency, 
  // Takes the efficiency and the total number from which it is derived and sets value and error
  if(eff > 1 || eff < 0) {
    cerr << "Error efficiency not in [0,1] " << endl;
    return Measurement();
  }
  double _err = sqrt(eff * (1 - eff) / n_tot );
  return Measurement(eff, _err);
}

Measurement Measurement::GetEfficiency(double n_sel, double n_tot){
  // Special case for a measurement of an efficiency, 
  // Takes the numbers in input and calculates the efficiency
  if(n_sel > n_tot){
    cerr << "Warning efficiency could be > 1 " << endl;
  }
  double _eff = n_sel / n_tot;
  return Measurement::Efficiency(_eff, n_tot);
}

Measurement Measurement::GetEfficiency(Measurement n_sel, Measurement n_tot){
  // Special case for a measurement of an efficiency, 
  // Takes the numbers in input and calculates the efficiency
  // This method adds also the error on the numerator.
  // The error on the denominator is considered zero. 
  if(n_sel > n_tot){
    cerr << "Warning efficiency could be > 1 " << endl;
  }
  // The following could be rewritten.... 
  Measurement eff = n_sel / n_tot.m_value;
  eff.add_to_errors( sqrt(eff.m_value * (1 - eff.m_value) / n_tot.m_value ));
  return eff;
}

//============================================================
// Setters and getters not defined in the header 
 
void Measurement::set_errors(double first_error, double second_error, int scheme){
  m_scheme = scheme;
  if(m_scheme & 1){ // Set it to stat error 
      m_errors[0] = abs(first_error);
      m_errors[1] = abs(second_error);
      m_errors[2] = m_errors[3] = 0;
  }else{ // interpret it as stat and syst errors
      m_errors[0] = m_errors[1] = first_error;
      m_errors[2] = m_errors[3] = second_error;
  }
}




//=============================================================================
// Operators with measurements
Measurement Measurement::operator+(const Measurement &meas) const
{
  Measurement _result;
  _result.m_value = this->m_value + meas.m_value;

  sum_err_quad(*this, meas, _result);
  
  return _result;
}

//=============================================================================
Measurement Measurement::operator-(const Measurement &meas) const 
{
  Measurement _result;
  _result.m_value = this->m_value - meas.m_value;
  
  sum_err_quad(*this, meas, _result);
  
  return _result;
}

//=============================================================================
Measurement Measurement::operator*(const Measurement &meas) const 
{
  Measurement _result;
  _result.m_value = this->m_value * meas.m_value;

  product_err(*this, meas,_result);
  
  return _result;
}

//=============================================================================
Measurement Measurement::operator/(const Measurement &meas) const
{
  Measurement _result;
  _result.m_value = this->m_value / meas.m_value;

  division_err(*this, meas,_result);
  
  return _result;
}

// Symmetric operators 
Measurement operator+(double b, const Measurement &a){
  return a + b;
}
Measurement operator*(double b, const Measurement &a){
  return a * b;
}
// Asymmetric operators
Measurement operator-(double b, const Measurement &a){
  // This is a trick, maybe it is faster if reimplemented
  return -1*a + b;
}

Measurement operator/(double b, const Measurement &a){
  return b*a.inverse();
}




//=============================================================================
// Operators with numbers
Measurement Measurement::operator+(double a) const
{
  Measurement _result(*this);
  _result.m_value = this->m_value + a;
  // No error propagation needed
  return _result;
}

Measurement Measurement::operator-(double a) const
{
  Measurement _result(*this);
  _result.m_value = this->m_value - a;
  // No error propagation needed
  return _result;
}

Measurement Measurement::operator*(double a) const
{
  Measurement _result(*this);
  _result.m_value = this->m_value * a;
  _result.scale_error(a);
  return _result;
}

Measurement Measurement::operator/(double a) const
{
  Measurement _result(*this);
  _result.m_value = this->m_value / a;
  _result.scale_error(1/a);
  return _result;
}

bool Measurement::operator==(double b) const 
{
  return (m_value == b);
}

bool Measurement::operator!=(double b) const 
{
  return (m_value != b);
}

bool Measurement::operator>(double b) const 
{
  return (m_value > b);
}

bool Measurement::operator<(double b) const 
{
  return (m_value < b);
}

//=============================================================================
// Mathematical functions
Measurement Measurement::inverse() const
{
  Measurement _result(*this);
  _result.m_value = 1/m_value;
  for(int i=0;i<MAXERRORS; i++){
    _result.m_errors[i] = m_errors[i]/pow(m_value,2);
  }
  return _result;
}




//=============================================================================
ostream& operator<<(ostream& os, const Measurement& a)
{
  stringstream ss;
  os <<   a._sstr(ss).str();
  return os;
}

stringstream& Measurement::_sstr(stringstream &out) const
{
 
  if(m_scheme == 0){
    out << m_value << " +- " << m_errors[0];
  }else if(m_scheme == 1){
    out << m_value << " +" << m_errors[0] << " -" << m_errors[1];
  }else if(m_scheme == 2){
    out << m_value << " +- " << m_errors[0] << " +- " << m_errors[2];
  }else if(m_scheme == 3){
    out << m_value << " +" << m_errors[0] << " -" << m_errors[1] 
       << " +" << m_errors[2] << " -" << m_errors[3];  
  }else{
    cerr << " Something bad with error scheme..." << m_scheme << endl;
    out << m_value << " + " << m_errors[0] << " - " << m_errors[1] 
        << " + " << m_errors[2] << " - " << m_errors[3];  
  }    
  return out;
}

string Measurement::str() const
{
  stringstream ss;
  return _sstr(ss).str();
}


stringstream& Measurement::_stex(stringstream &out) const
{
  // TODO: implement the number of significant digits
  // - the number of the smallest exponent within the errors?  
  if(m_scheme == 0){
    out << "$" << m_value << " \\pm " << m_errors[0] << "$";
  }else if(m_scheme == 1){
    out << "$" << m_value << "^{+" << m_errors[0] << "}_{-" 
        << m_errors[1] <<"}$";
  }else if(m_scheme == 2){
    out << "$" << m_value << " \\pm " << m_errors[0] 
        << " \\pm " << m_errors[2] << "$" ;
  }else if(m_scheme == 3){
    out << "$" << m_value << "^{+" << m_errors[0] << "}_{-" << m_errors[1] 
        << "}^{+" << m_errors[2] << "}_{-" << m_errors[3] << "}$";  
  }else{
    cerr << " Something bad with error scheme..." << m_scheme << endl;
    out << m_value << " + " << m_errors[0] << " - " << m_errors[1] 
        << " + " << m_errors[2] << " - " << m_errors[3];  
  }    
  return out;
}
string Measurement::tex() const
{
  stringstream ss;
  return _stex(ss).str();
}


//=============================================================================
void Measurement::add_to_errors(double err, int to_scheme){
  if(m_scheme & 2){// If systematic error is present add this to it (symmetrically) 
    m_errors[2] = sqrt(pow(m_errors[2],2) + pow(err,2));
    m_errors[3] = sqrt(pow(m_errors[3],2) + pow(err,2));
  }else{
    if(to_scheme==0){ // Add it to stat error 
      m_errors[0] = sqrt(pow(m_errors[0],2) + pow(err,2));
      m_errors[1] = sqrt(pow(m_errors[1],2) + pow(err,2));
    }else{
      m_errors[2] = err;
      m_errors[3] = err;
      m_scheme = 2;
    }
  }
}
void Measurement::add_to_errors(double first_error, double second_error, int to_scheme){
  if(m_scheme & 2){// If systematic error is present add them to it  
    m_errors[2] = sqrt(pow(m_errors[2],2) + pow(first_error,2));
    m_errors[3] = sqrt(pow(m_errors[3],2) + pow(second_error,2));
  }else{ 
    if(to_scheme == 1){ // Add it to stat error 
      m_errors[0] = sqrt(pow(m_errors[0],2) + pow(first_error,2));
      m_errors[1] = sqrt(pow(m_errors[1],2) + pow(second_error,2));
    }else{
      m_errors[2] = sqrt(pow(m_errors[2],2) + pow(first_error,2));
      m_errors[3] = sqrt(pow(m_errors[3],2) + pow(second_error,2));
      m_scheme = 3;
    }
  }

}


void Measurement::add_to_syst_errors(double err){
  add_to_errors(err,2);
}
void Measurement::add_to_syst_errors(double first_error, double second_error){
  add_to_errors(first_error, second_error, 3);
}

//=============================================================================
void Measurement::symmetrize(){
  if(m_scheme & 1){ // check is indeed asymmetric
    if(m_scheme ==3 ){ // check stat and syst are separated
      m_errors[0] = (m_errors[0]+m_errors[1])/2; // Stat average
      m_errors[1] = (m_errors[2]+m_errors[3])/2; // Syst average
      m_scheme = 2;
    }else{
      m_errors[0] = (m_errors[0]+m_errors[1])/2;
      m_scheme = 1;
    }
  }
  return;
}

//=============================================================================
void Measurement::compress(){
  if(m_scheme & 2){ // check it was splitted in the first place
    if(m_scheme & 1){ // check we have asymmetric errors
      m_errors[0] = sqrt(pow(m_errors[0],2)+pow(m_errors[2],2)); // Upper stat+syst
      m_errors[1] = sqrt(pow(m_errors[1],2)+pow(m_errors[3],2)); // Lower stat+syst
      m_scheme = 1;
    }else{
      m_errors[0] = sqrt(pow(m_errors[0],2)+pow(m_errors[1],2)); 
      m_scheme = 0;
    }
  }
  return;
}


int Measurement::common_scheme(Measurement a){
  // Function to evaluate the common scheme between the element
  // and a second element 
  // -  -  -  -  - 
  // Finds the more general one between the two
  return (this->m_scheme | a.m_scheme) ; // bit OR to get common scheme 
}

void Measurement::debug(){
  // Debug function 
  // Prints all the member variables of the element 
  cout << "Meas debug  " << m_value << " + " <<  m_errors[0] 
       << " - " << m_errors[1] 
       << " + " << m_errors[2] 
       << " - " << m_errors[3] 
       << " Scheme " << m_scheme << endl;  

}

//=============================================================================
// Sum errors in quadrature 

void Measurement::sum_err_quad(Measurement a, Measurement b, Measurement &result) const 
{
  for(int i=0;i<MAXERRORS; i++){
    result.m_errors[i] = sqrt(pow(a.m_errors[i],2)+pow(b.m_errors[i],2));
    result.m_scheme = a.common_scheme(b);
  }
}

//=============================================================================
// Propagation of errors "log" formula 
void Measurement::sum_err_log(Measurement a, Measurement b, Measurement &result)const
{
  for(int i=0;i<MAXERRORS; i++){
    result.m_errors[i] = result.m_value * sqrt(pow(a.m_errors[i] / a.m_value ,2)
					       +pow(b.m_errors[i] / b.m_value ,2));
    result.m_scheme = a.common_scheme(b);
  }
}

void Measurement::product_err(Measurement a, Measurement b, Measurement &result)const
{
  for(int i=0;i<MAXERRORS; i++){
    result.m_errors[i] = sqrt(pow(a.m_errors[i] * b.m_value ,2)
                              +pow(b.m_errors[i] * a.m_value ,2));
    result.m_scheme = a.common_scheme(b);
  }
}

void Measurement::division_err(Measurement a, Measurement b, Measurement &result)const
{
  for(int i=0;i<MAXERRORS; i++){
    result.m_errors[i] = sqrt(pow(a.m_errors[i] / b.m_value ,2)
                              +pow(b.m_errors[i] * a.m_value/pow(b.m_value,2) ,2));
    result.m_scheme = a.common_scheme(b);
  }
}




void Measurement::scale_error(double scale){
  // Scales all errors of a given amount
  for(int i=0;i<MAXERRORS; i++){
    m_errors[i] *= scale;
  }
}


double Measurement::total_error() const 
{
  // Calculates total error without storing the result 
  if(m_scheme ==0){ 
    return m_errors[0];
  }else if(m_scheme == 1){
    // If asymmetric return the average
    return (m_errors[0] + m_errors[1]) / 2; 
  }else if(m_scheme == 2){
    // Sum in quadrature stat and syst 
    return sqrt(pow(m_errors[0],2) + pow(m_errors[2],2));
  }else {
    return   sqrt( pow ( (m_errors[0] + m_errors[1]) / 2, 2)+
		   pow ( (m_errors[2] + m_errors[3]) / 2, 2));
		   
  }
  
}


const char* Measurement::getLaTeX() const {
  return tex().c_str();
}
///> function to print latex number, like: a^{+x}_{-y} or a\pm b
/*char* Measurement::getLaTeX(){
  char* latex = new char[100];
  if(m_scheme == 0){
      sprintf(latex,"$%.3e \\pm %.3e$",m_value,m_errors[0]);
    }else if(m_scheme == 1){
      sprintf(latex,"$%.3e^{+%.3e}_{-%.3e}$",m_value,m_errors[0],m_errors[1]);
    }else if(m_scheme == 2){
      sprintf(latex,"$%.3e \\pm %.3e (\\text{stat}) \\pm %.3e (\\text{sys})$",m_value,m_errors[0],m_errors[1]);
    }else if(m_scheme == 3){
      sprintf(latex,"$%.3e^{%.3e}_{%.3e} (\\text{stat})^{%.3e}_{%.3e} (\\text{sys})$",
              m_value,m_errors[0],m_errors[1],m_errors[2],m_errors[3]);
    }else{
      cerr << " Something bad with error scheme..." << m_scheme << endl;
    }    
    return latex;
    };*/


Measurement Measurement::average(Measurement b) const
{
  // Weighted average between two elements
  // Only total errors are considered here 
  // The returned average has only one symmetric total error
  double wa = 1/pow(total_error(),2);
  double wb = 1/pow(b.total_error(),2);
  double sumw = wa + wb;
  double val = (m_value*wa + b.value()*wb)/sumw;
  double err = sqrt(1/sumw);
  
  return Measurement(val, err);
}


//=============================================================================
// Destructor
//=============================================================================
Measurement::~Measurement() {} 

//=============================================================================
