#ifndef ROOGLMFUNCTION_H 
#define ROOGLMFUNCTION_H

// Include files

#include <tuple>

#include "RooAbsReal.h"
#include "RooRealProxy.h"
#include "RooListProxy.h"
#include "RooMultiVarGaussian.h"

#include "GLMCalibration.hh"
#include "GLMCalibrationFunction.hh"
#include "Vector.hh"

/** @class RooGLMFunction RooGLMFunction.h B2DXFitters/RooGLMFunction.h
 *  
 *
 *  @author Vincenzo Battista, Jack Wimberley
 *  @date   2016-11-30
 */

namespace Espresso
{

  class RooGLMFunction : public RooAbsReal {
  public: 
    /// Standard constructor
    RooGLMFunction() {} 
    RooGLMFunction(const char *name, const char *title,
                   RooAbsReal& _eta,
                   Int_t _flavour,
		   std::unique_ptr<Espresso::GLMCalibrationFunction> _calfun,
		   const RooArgList& _coeffList,
		   const RooArgList& _deltacoeffList) ;
    RooGLMFunction(const RooGLMFunction& other, const char* name=0) ;
    virtual TObject* clone(const char* newname
			   ) const { return new RooGLMFunction(*this,newname);  }
    virtual ~RooGLMFunction() { }; ///< Destructor

    std::size_t getNumCoeffs() const;

  protected:
    
    RooRealProxy m_eta;
    RooListProxy m_coeffListProxy;
    RooListProxy m_deltacoeffListProxy;
    Espresso::Flavour m_flavour;
    std::unique_ptr<Espresso::GLMCalibrationFunction> m_calfun;
    std::size_t m_numCoeffs;
    
    Double_t evaluate() const ;
    
  private:
    
    ClassDef(RooGLMFunction,1)
    
  };
  
  /// Static multi-object constructor
  std::tuple<RooArgList,RooArgList,RooMultiVarGaussian,
	     RooGLMFunction,RooGLMFunction> createRooGLMCalibration(const char *name, const char *title,
								    RooAbsReal& _eta,
								    std::string _calName,
								    std::string _calFileName) ;
}

BOOST_CLASS_EXPORT_KEY(Espresso::RooGLMFunction)

#endif // ROOGLMFUNCTION_H
