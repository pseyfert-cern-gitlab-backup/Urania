// Include files

#include "TGraph.h"
#include "TStyle.h"
#include "TH1F.h"
#include "TCanvas.h"
#include <cassert>
#include <cmath>



class FormFactor 
{
public:
  FormFactor( ) ;
  
  FormFactor( const Double_t MB, const Double_t MK, const Double_t Mstar );
  
  Double_t operator()( const Double_t M, const Double_t param ) const ;

  void model( const unsigned int num ) ;
  
private:

  void init();
  
  Double_t zfun( const Double_t qsq ) const ;
  
  Double_t shatfun( const Double_t M ) const ;
  
  Double_t BallParam( const Double_t M, const Double_t param ) const ;
  
  Double_t SimpleParam( const Double_t M, const Double_t param ) const ;
  
  Double_t ZParam( const Double_t M, const Double_t param ) const ;

  const Double_t MB_;
  const Double_t MK_;
  const Double_t Mstar_;

  Double_t TP_;
  Double_t TM_;
  Double_t T0_;
  Double_t Z0_;
  
  Double_t (FormFactor::*func)( const Double_t M, const Double_t param ) const ;
  
  
};

void FormFactor::model( const unsigned int num ) 
{
  assert( num < 3 );

  if ( 0 == num ) func = &FormFactor::SimpleParam;
  if ( 1 == num ) func = &FormFactor::BallParam;
  if ( 2 == num ) func = &FormFactor::ZParam;
  
}


void FormFactor::init()
{
  TP_ = std::pow(  MB_ + MK_ , 2 );
  TM_ = std::pow(  MB_ - MK_ , 2 );
  T0_ = TP_ -  sqrt( TP_*( TP_ - TM_ ) ) ;

  Z0_ = zfun( 0. );

  func = &FormFactor::SimpleParam;
}


FormFactor::FormFactor( const Double_t MB, 
                        const Double_t MK, 
                        const Double_t Mstar ) : 
  MB_(MB), MK_( MK ), Mstar_( Mstar ){ init(); } ;

FormFactor::FormFactor() : 
  MB_( 5279.) ,
  MK_( 493.7) , 
  Mstar_( 5412 ){ init(); } ;  


Double_t FormFactor::zfun( const Double_t qsq ) const 
{  
  return ( ( sqrt( TP_ - qsq ) - sqrt( TP_ - T0_ ) )/
           ( sqrt( TP_ - qsq ) + sqrt( TP_ - T0_ ) ) );
}

Double_t FormFactor::shatfun( const Double_t M ) const 
{
  return ( M*M )/( Mstar_*Mstar_ );
}


Double_t  FormFactor::BallParam( const Double_t M, const Double_t param ) const  
{
  Double_t shat = shatfun( M );
  
  return ( ( 1./( 1. - shat ) ) + 
           ( param/std::pow( 1. - shat, 2 ) ) )/( 1. + param );
}

Double_t FormFactor::SimpleParam( const Double_t M, const Double_t param ) const 
{
  Double_t qsq = M*M ;
  Double_t shat = qsq/(Mstar_*Mstar_);

  return ( 1. /std::pow( 1. - param*shat, 2 ) );
}

Double_t FormFactor::ZParam( const Double_t M, const Double_t param ) const 
{
  Double_t qsq = M*M; // in MeV^{2}  
  Double_t zq  = zfun( qsq );
  
  Double_t zterm = 1. + param*(zq - Z0_ + 0.5*( zq*zq - Z0_*Z0_ ) );
  
  return zterm/(1. - qsq/std::pow( Mstar_ ,2 ) );
}


Double_t FormFactor::operator() ( const Double_t M, const Double_t param ) const 
{
  return (this->*func)( M, param );
}

/*
  Double_t qsq = M*M; // in MeV^{2}
  
  Double_t zq = zfun( qsq );
  Double_t z0 = zfun( 0.  );
  
  Double_t zterm = 1. + param*(zq - z0 + 0.5*( zq*zq - z0*z0 ) );
  
  return zterm/(1. - qsq/std::pow( Mstar_ ,2 ) );
}
*/

void compare() 
{
  
  double qsq = 1.0;
  
  
  TGraph* graph_0_1 = new TGraph();
  TGraph* graph_0_2 = new TGraph();
  TGraph* graph_0_3 = new TGraph();
  TGraph* graph_1_1 = new TGraph();
  TGraph* graph_1_2 = new TGraph();
  TGraph* graph_1_3 = new TGraph();
  TGraph* graph_2_1 = new TGraph();
  TGraph* graph_2_2 = new TGraph();
  TGraph* graph_2_3 = new TGraph();
  
  FormFactor FF;
  
  int ipoint = 0;

  while ( qsq < 22. ){

    FF.model( 0 );
    
    graph_0_1->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 0.7 ) );
    graph_0_2->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 0.8 ) );
    graph_0_3->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 0.9 ) );
    

    FF.model( 1 );
    
    graph_1_1->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 0.0 ) );
    graph_1_2->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 1.0 ) );
    graph_1_3->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 2.0 ) );
    
    
    FF.model( 2 ) ;
    
    graph_2_1->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , -1. ) );
    graph_2_2->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , -2. ) );
    graph_2_3->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , -3. ) );
        
    ipoint++;
    
    qsq += 0.1;
  }
  

  TH1F* frame = new TH1F("frame","frame",22,0.,22.);
  frame->SetMaximum( 6. );
  frame->SetMinimum( 0. );
  frame->SetXTitle( "#it{q}^{2} [ GeV^{2}/#it{c}^{4} ]" );
  frame->SetYTitle( "f(#it{q}^{2})" );

  frame->Draw() ;

  gStyle->SetHistLineWidth( 2. );
  

  graph_0_1->Draw("l");

  graph_0_2->SetLineStyle( kDashed );
  graph_0_3->SetLineStyle( 9 );
  
  graph_1_1->SetLineColor( kBlue );
  graph_1_2->SetLineColor( kBlue ); 
  graph_1_3->SetLineColor( kBlue ); 
  graph_1_2->SetLineStyle( kDashed );
  graph_1_3->SetLineStyle( 9 );
  
  graph_2_1->SetLineColor( kOrange + 2 );
  graph_2_2->SetLineColor( kOrange + 2 );
  graph_2_3->SetLineColor( kOrange + 2 );
  graph_2_2->SetLineStyle( kDashed );
  graph_2_3->SetLineStyle( 9 );


  graph_0_2->Draw("l");
  graph_0_3->Draw("l");
  graph_1_1->Draw("l");
  graph_1_2->Draw("l");
  graph_1_3->Draw("l");
  graph_2_1->Draw("l");
  graph_2_2->Draw("l");
  graph_2_3->Draw("l");
  
  return ;
  
}




void draw()
{
  double qsq = 1.0;
  
  
  TGraph* graph1= new TGraph();
  TGraph* graph2= new TGraph();
  TGraph* graph3= new TGraph();
  TGraph* graph4= new TGraph();
  TGraph* graph0= new TGraph();
  TGraph* graphp1 = new TGraph();
  TGraph* graphp2 = new TGraph();

  FormFactor FF;
  
  int ipoint = 0;

  while ( qsq < 22. ){
    graphp1->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 1.0 ) );
    graphp2->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 2.0 ) );
    graph0->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , 0.0 ) );
    graph1->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , -1. ) );
    graph2->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , -2. ) );
    graph3->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , -3. ) );
    graph4->SetPoint( ipoint, qsq, FF( 1000.*sqrt( qsq ) , -4. ) );
        
    ipoint++;
    
    qsq += 0.1;
  }
  

  graph2->Draw("al");
  graph1->SetLineColor( kRed );
  graph3->SetLineColor( kBlue );
  graph4->SetLineColor( kOrange + 2 );
  graph0->SetLineColor( kGreen );
  graphp1->SetLineColor( kMagenta );  
  graphp2->SetLineColor( kCyan + 2 );
  
  graph0->Draw("l+");
  graph1->Draw("l+");
  graph3->Draw("l+");
  graph4->Draw("l+");
  graphp1->Draw("l+");
  graphp2->Draw("l+");
  
  
  return ;
}
