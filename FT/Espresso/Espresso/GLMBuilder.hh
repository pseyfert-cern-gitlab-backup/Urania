#ifndef ESPRESSO_GLMBUILDER_HH 
#define ESPRESSO_GLMBUILDER_HH 1

#include <tuple>
#include "RooAbsReal.h"
#include "RooMultiVarGaussian.h"

#include "RooGLMFunction.hh"

namespace Espresso {

  /// Static multi-object constructor
  std::tuple<RooArgList,RooArgList,RooMultiVarGaussian,
             RooGLMFunction,RooGLMFunction> createRooGLMCalibration(const char *name, const char *title,
                                                                              RooAbsReal& _eta,
                                                                              std::string _calName,
                                                                              std::string _calFileName);
  
  class GLMBuilder {
  public: 
    
    GLMBuilder(const char *name, const char *title,
               RooAbsReal& _eta,
               std::string _calName,
               std::string _calFileName) ;

    virtual ~GLMBuilder( ); ///< Destructor

    RooArgList coefficients() {
      return std::get<0>(components); 
    }

    RooArgList delta_coefficients() {
        return std::get<1>(components);
    }

    RooMultiVarGaussian covariance_matrix() {
      return std::get<2>(components);
    }

    RooGLMFunction b_mistag() {
      return std::get<3>(components);
    }

    RooGLMFunction bbar_mistag() {
      return std::get<4>(components);
    }

  protected:

  private:
    std::tuple<RooArgList,RooArgList,RooMultiVarGaussian,
               RooGLMFunction,RooGLMFunction> components;
  };

}

#endif // ESPRESSO_GLMBUILDER_HH
