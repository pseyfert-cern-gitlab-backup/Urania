#ifndef PHASESPACE_H 
#define PHASESPACE_H 1

// Include files

#include "TObject.h"

/** @class PhaseSpace PhaseSpace.h
 *  
 *
 *  @author Thomas Blake
 *  @date   2012-08-23
 */

class PhaseSpace 
{
public: 
  PhaseSpace();
  
  PhaseSpace( const PhaseSpace& other );
  
  PhaseSpace( const Double_t MM,
              const Double_t MA,
              const Double_t MB,
              const Double_t MC,
              const unsigned int LAB );
  
  inline virtual ~PhaseSpace(){} ;
  
  Double_t low() const ;
  
  Double_t upp() const ;
  
  Double_t q( const Double_t M ) const ;
  
  Double_t q( const Double_t M, 
              const Double_t M1, 
              const Double_t M2 ) const ;
  
  unsigned int spin() const ;

  Double_t MM() const;
  
  
  Double_t twobody( const Double_t M ) const ;
  

  Double_t triangle( const Double_t a , 
                     const Double_t b ,
                     const Double_t c ) const;

  Double_t triangle( const Double_t qsq ) const ;
  
    
private:
  
  Double_t MM_;
  Double_t MA_;
  Double_t MB_;
  Double_t MC_;
  unsigned int LAB_;
};


#endif // PHASESPACE_H
