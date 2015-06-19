// $Id: $
#ifndef ROOPHYSFITTER_EXCEPTIONS_H
#define ROOPHYSFITTER_EXCEPTIONS_H 1

// Include files
#include <exception>
#include <fstream>
#include "TObject.h"
#include "TFile.h"
#include "RooAbsData.h"
#include "RooDataSet.h"
#include "RooAbsArg.h"
#include "RooWorkspace.h"
#include "TFile.h"

// forward declarations

/** @class Exceptions Exceptions.h DstarD0ForXSecRooFitter/Exceptions.h
 *  
 *
 *  @author Philip Hunt (LHCB)
 *  @date   2011-04-08
 */
namespace RooPhysFit
{
  class TDirectoryError: public std::exception
  {
  public:
    explicit TDirectoryError(const std::string& func,
                             const TFile& f,
                             const std::string& name) throw();
    virtual ~TDirectoryError() throw();
    virtual const char* what() const throw();
    
  private:
    std::string m_fullMsg;
  };
  
  /** Exception when using importClassCode method of RooWorkspace
      'type' should be the class type you are tying to import the code for,
      or the search pattern.
  */
  class WSImportCodeFailure : public std::exception
  {
  public:
    explicit WSImportCodeFailure(const std::string& func,
                                 const RooWorkspace& ws,
                                 const std::string& type="*") throw();
    virtual ~WSImportCodeFailure() throw();
    virtual const char* what() const throw();
  private:
    std::string m_fullMsg;
  };

  class WSImportFailure : public std::exception
  {
  public:
    explicit WSImportFailure(const std::string& func,
                             const RooWorkspace& ws,
                             const TObject& obj) throw();
    explicit WSImportFailure(const std::string& func,
                             const RooWorkspace& ws,
                             const RooAbsArg& arg) throw();
    explicit WSImportFailure(const std::string& func,
                             const RooWorkspace& ws,
                             const RooArgSet& args) throw();

    /** For a named set (using 'defineSet').
        Set isSnapshot to true if this is a snapshot of the parameters,
        rather than a named set.
    */
    explicit WSImportFailure(const std::string& func,
                             const RooWorkspace& ws,
                             const RooArgSet& args,
                             const std::string& name,
                             bool isSnapshot=false) throw();

    /// For extending or defining a named set (using 'extendSet').
    explicit WSImportFailure(const std::string& func,
                             const RooWorkspace& ws,
                             const std::string& name,
                             const std::string& newContents,
                             bool isNewSet=false) throw();

    explicit WSImportFailure(const std::string& func,
                             const RooWorkspace& ws,
                             const RooAbsData& data) throw();
    virtual ~WSImportFailure() throw();
    virtual const char* what() const throw();

  private:
    std::string m_fullMsg;
  };

  class WSRetrievalFailure : public std::exception
  {
  public:
    explicit WSRetrievalFailure(const std::string& func,
                                const RooWorkspace& ws,
                                const std::string& name,
                                const std::string& type) throw();
    virtual ~WSRetrievalFailure() throw();
    virtual const char* what() const throw();

  private:
    std::string m_fullMsg;
  };


  class IOFailure : public std::exception
  {
  public:
    explicit IOFailure( const std::string& funcName,
                        const std::string& fname,
                        const std::fstream& stream ) throw() ;
    explicit IOFailure(const std::string& func,
                       const char* fname,
                       const char* opts) throw();
    virtual ~IOFailure() throw();
    virtual const char* what() const throw();

  private:
    std::string m_fullMsg;
  };
  
  class GeneralException : public std::exception
  {
  public:
    explicit GeneralException(const std::string& func,
                              const std::string& msg) throw();
    virtual ~GeneralException() throw();
    virtual const char* what() const throw();
    
  private:
    std::string m_fullMsg;
  };
}
#endif // ROOPHYSFITTER_EXCEPTIONS_H
