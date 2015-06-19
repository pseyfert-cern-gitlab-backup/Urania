// Include files 



// local
#include "PhaseSpace.h"
#include "TMath.h"

//-----------------------------------------------------------------------------
// Implementation file for class : PhaseSpace
//-----------------------------------------------------------------------------


PhaseSpace::PhaseSpace() : 
  MM_ ( 0. ), 
  MA_ ( 0. ),
  MB_ ( 0. ),
  MC_ ( 0. ),
  LAB_( 0. ) {};

PhaseSpace::PhaseSpace( const PhaseSpace& other )  : 
  MM_ ( other.MM_ ),
  MA_ ( other.MA_ ),
  MB_ ( other.MB_ ),
  MC_ ( other.MC_ ),
  LAB_( other.LAB_ ){} ;  
  

PhaseSpace::PhaseSpace( const Double_t MM,
                        const Double_t MA,
                        const Double_t MB,
                        const Double_t MC,
                        const unsigned int LAB ) :
  MM_ ( MM  ), 
  MA_ ( MA  ), 
  MB_ ( MB  ), 
  MC_ ( MC  ),
  LAB_( LAB ){} ;


Double_t PhaseSpace::low() const { return ( MA_ + MB_ ); }

Double_t PhaseSpace::upp() const { return ( MM_ - MC_ ); }

Double_t PhaseSpace::triangle( const Double_t a , 
                               const Double_t b , 
                               const Double_t c ) const { 
  return a * a + b * b + c * c - 2 * a * b - 2 * b * c - 2 * a * c ; 
}

Double_t PhaseSpace::triangle( const Double_t qsq ) const {
  return triangle( qsq, MM_*MM_, MC_*MC_ );
}


Double_t PhaseSpace::q( const Double_t M, 
                        const Double_t M1, 
                        const Double_t M2 ) const 
{ 
  if ( M < 0 || M1 < 0 || M2 < 0 || M < ( M1 + M2 ) ) return 0 ;

  Double_t msq = M*M;
  Double_t qsq = ( (msq - (M1+M2)*(M1+M2))*(msq - (M1-M2)*(M1-M2)) )/(4*msq);

  return std::sqrt( qsq );
}


Double_t PhaseSpace::q( const Double_t M ) const 
{
  return q( M, MA_, MB_ );
}

Double_t PhaseSpace::twobody( const Double_t M ) const 
{
  Double_t vallow = low();
  Double_t valupp = upp();
  
  if ( M < vallow || M > valupp ) return 0.0;
  
  return 2*q( MM_, M, MC_ )/MM_ ;
}

unsigned int PhaseSpace::spin() const 
{
  return LAB_;
}

Double_t PhaseSpace::MM() const 
{
  return MM_;
}


