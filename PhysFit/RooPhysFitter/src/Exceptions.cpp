// $Id: $
// Include files
#include <sstream>
#include <iostream>

// local
#include "RooPhysFitter/Exceptions.h"


//-----------------------------------------------------------------------------
// Implementation file for class : Exceptions
//
// 2011-04-08 : Philip Hunt (LHCB)
//-----------------------------------------------------------------------------

RooPhysFit::TDirectoryError::TDirectoryError(const std::string& func,
        const TFile& f,
        const std::string& name) throw()
{
    std::stringstream ss;
    ss << func << ":  " << " unable to retrieve  "
    << name << " from file " << f.GetName();
    m_fullMsg=ss.str();
}

RooPhysFit::TDirectoryError::~TDirectoryError() throw()
{}

const char* RooPhysFit::TDirectoryError::what() const throw()
{
    return m_fullMsg.c_str();
}


RooPhysFit::WSImportCodeFailure::WSImportCodeFailure(const std::string& func,
        const RooWorkspace& ws, const std::string& type) throw()
{
    std::stringstream ss;
    ss << func << ":  " << " unable to import code for class or search pattern "
    << type << " into RooWorkspace " << ws.GetName();
    m_fullMsg=ss.str();
}

RooPhysFit::WSImportCodeFailure::~WSImportCodeFailure() throw()
{}

const char* RooPhysFit::WSImportCodeFailure::what() const throw()
{
    return m_fullMsg.c_str();
}


RooPhysFit::WSImportFailure::WSImportFailure(const std::string& func,
        const RooWorkspace& ws, const TObject& obj) throw()
{
    std::stringstream ss;
    ss << func << ":  " << " unable to import TObject "
    << obj.GetName() << " into RooWorkspace "
    << ws.GetName();
    m_fullMsg=ss.str();
}

RooPhysFit::WSImportFailure::WSImportFailure(const std::string& func,
        const RooWorkspace& ws, const RooAbsArg& arg) throw()
{
    std::stringstream ss;
    ss << func << ":  " << " unable to import RooAbsArg "
    << arg.GetName() << " into RooWorkspace "
    << ws.GetName();
    m_fullMsg=ss.str();
}

RooPhysFit::WSImportFailure::WSImportFailure(const std::string& func,
        const RooWorkspace& ws, const RooArgSet& args) throw()
{
    std::stringstream ss;
    ss << func << ":  " << " unable to import RooArgSet "
    << args.GetName() << " into RooWorkspace "
    << ws.GetName();
    m_fullMsg=ss.str();
}

RooPhysFit::WSImportFailure::WSImportFailure(const std::string& func,
        const RooWorkspace& ws, const RooArgSet& args,
        const std::string& name, bool isSnapshot) throw()
{
    std::stringstream ss;
    if (!isSnapshot)
    {
        ss << func << ":  " << " unable to import named RooArgSet "
        << name << " with original name " << args.GetName()
        << " into RooWorkspace " << ws.GetName();
    }
    else
    {
        ss << func << ":  " << " unable to save snapshot " << name
        << " for RooArgSet " << args.GetName()
        << " to RooWorkspace " << ws.GetName();
    }
    m_fullMsg=ss.str();
}

RooPhysFit::WSImportFailure::WSImportFailure(const std::string& func,
        const RooWorkspace& ws, const std::string& name,
        const std::string& newContents, bool isNewSet) throw()
{
    std::stringstream ss;
    if (!isNewSet)
    {
        ss << func << ":  " << " unable to extend named RooArgSet "
        << name << " with new contents " << newContents
        << " in RooWorkspace " << ws.GetName();
    }
    else
    {
        ss << func << ":  " << " unable to import named RooArgSet "
        << name << " with contents " << newContents
        << " in RooWorkspace " << ws.GetName();
    }
    m_fullMsg=ss.str();
}

RooPhysFit::WSImportFailure::WSImportFailure(const std::string& func,
        const RooWorkspace& ws, const RooAbsData& data) throw()
{
    std::stringstream ss;
    ss << func << ":  " << " unable to import RooAbsData "
    << data.GetName() << " into RooWorkspace "
    << ws.GetName();
    m_fullMsg=ss.str();
}

RooPhysFit::WSImportFailure::~WSImportFailure() throw()
{}

const char* RooPhysFit::WSImportFailure::what() const throw()
{
    return m_fullMsg.c_str();
}


RooPhysFit::WSRetrievalFailure::WSRetrievalFailure(const std::string& func,
        const RooWorkspace& ws, const std::string& name,
        const std::string& type) throw()
{
    std::stringstream ss;
    ss << func << ":  " << " Unable to retrieve " << type
    << " with name " << name << " from RooWorkspace "
    << ws.GetName();
    m_fullMsg=ss.str();
}
RooPhysFit::WSRetrievalFailure::~WSRetrievalFailure() throw()
{}

const char* RooPhysFit::WSRetrievalFailure::what() const throw()
{
    return m_fullMsg.c_str();
}

RooPhysFit::IOFailure::IOFailure( const std::string& funcName,
                                  const std::string& fname,
                                  const std::fstream& stream ) throw()
{
    std::stringstream fullMsg;
    fullMsg << funcName << ":  unable to perform I/O operations for filename "
    << fname << ". ";
    if (!stream.is_open())
    {
        fullMsg << "Unable to open file for reading/writing";
    }
    else if (stream.bad())
    {
        fullMsg << "Got bad bit.";
    }
    else if (stream.fail())
    {
        fullMsg << "Got fail bit.";
    }
    else if (stream.eof())
    {
        fullMsg << "Reached end-of-file";
    }
    else
    {
        fullMsg << "Last I/O operation failed with unknown error";
    }
    m_fullMsg=fullMsg.str();
}

RooPhysFit::IOFailure::IOFailure(const std::string& func,
                                 const char* fname,
                                 const char* opts) throw()
{
    std::stringstream ss;
    ss << func << ":  " << " unable to open file "
    << fname << " with access mode "
    << opts;
    m_fullMsg=ss.str();
}

RooPhysFit::IOFailure::~IOFailure() throw()
{}

const char* RooPhysFit::IOFailure::what() const throw()
{
    return m_fullMsg.c_str();
}

RooPhysFit::GeneralException::GeneralException(const std::string& func,
        const std::string& msg) throw()
{
    std::stringstream ss;
    ss << func << ":  " << msg;
    m_fullMsg=ss.str();
}

RooPhysFit::GeneralException::~GeneralException() throw()
{}

const char* RooPhysFit::GeneralException::what() const throw()
{
    return m_fullMsg.c_str();
}
