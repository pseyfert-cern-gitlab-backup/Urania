// $Id: $
#ifndef V0HHFITTER_EXCEPTIONS_H
#define V0HHFITTER_EXCEPTIONS_H 1

// STL include
#include <exception>
#include <fstream>

// ROOT include
#include "TObject.h"
#include "TFile.h"

// RooFit include
#include "RooAbsData.h"
#include "RooDataSet.h"
#include "RooAbsArg.h"
#include "RooFitResult.h"
#include "RooWorkspace.h"

// forward declarations

/** @class Exceptions Exceptions.h V0hhFitter/Exceptions.h
 *  
 *
 *  @author Matthew M Reid
 *  @date   2014-01-08
 */
namespace V0hhFit
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
	
    // exception when using importClassCode method of RooWorkspace
    // 'type' should be the class type you are tying to import the code for,
    // or the search pattern
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

            // for a named set (using 'defineSet')
            // set isSnapshot to true if this is a snapshot of the parameters,
            // rather than a named set
            explicit WSImportFailure(const std::string& func,
                    const RooWorkspace& ws,
                    const RooArgSet& args,
                    const std::string& name,
                    bool isSnapshot=false) throw();

            // for extending or defining a named set (using 'extendSet')
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

    class RFRRetrievalFailure : public std::exception
		{
		public:
			explicit RFRRetrievalFailure(const std::string& func,
										 const RooFitResult& fitRes,
										 const std::string& name) throw();
            virtual ~RFRRetrievalFailure() throw();
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

#endif // V0HHFITTER_EXCEPTIONS_H
