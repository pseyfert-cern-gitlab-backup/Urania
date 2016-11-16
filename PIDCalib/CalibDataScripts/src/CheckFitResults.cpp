// Include files 
#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <algorithm>

#include "RooFitResult.h"
#include "RooPhysFitter/RooPhysFitter.h"

// local
#include "CalibDataScripts/CheckFitResults.h"

//-----------------------------------------------------------------------------
// Implementation file for: CheckFitResults
//
// 2013-11-18 : Philip Hunt (LHCB)
//-----------------------------------------------------------------------------

bool checkCovQual(const RooPhysFit::RooPhysFitter& fitter, 
                  const char* fitName, int& qual, int convLevel) 
{  
  const RooFitResult* fres = fitter.GetFitResult(fitName);
  qual = fres->covQual();
  if (qual>=convLevel) return true;
  return false;
}

const char* getCovQualMessage(const int& qual)
{
  if (qual==0) 
  {
    return "No error matrix calculated.";
  }
  else if (qual==1) 
  {
    return "Diagonal approximation only, not accurate.";
  }
  else if (qual==2)
  {
    return "Full error matrix, but forced positive definite.";
  }
  else if (qual==3) 
  {
    return "Full, accurate covariance matrix.";
  }
  else 
  {
    std::stringstream msg;
    msg << qual << " is not a valid covariance quality flag!";
    return msg.str().c_str();
  }
}

bool checkEDM(const RooPhysFit::RooPhysFitter& fitter, 
              const char* fitName, double& edm, double maxEDM)
{
  const RooFitResult* fres = fitter.GetFitResult(fitName);
  edm = fres->edm();
  if (edm<maxEDM) return true;
  return false;
}

bool checkFitStatus(const RooPhysFit::RooPhysFitter& fitter, 
                    const char* fitName, int& status,
                    const std::vector<int>& allowedMinuit2Errors,
                    const std::vector<int>& allowedMinosErrors,
                    const std::vector<int>& allowedHesseErrors)
{
  const RooFitResult* fres = fitter.GetFitResult(fitName);
  status = fres->status();
  if (status==0) return true;
  
  // return false unless certain errors are allowed
  if (allowedMinuit2Errors.empty()&&allowedMinosErrors.empty()&&allowedHesseErrors.empty()) 
  {
    return false;
  }
  else 
  {
    int minuit2Status = status%10;
    int minosStatus = status/10%10;
    int hesseStatus = status/100;

    // check Minuit2 status
    if (minuit2Status!=0) 
    {
      if (allowedMinuit2Errors.empty()) return false;
      else 
      {
        // return false if status not in allowed statuses
        if (std::count(allowedMinuit2Errors.begin(),
                       allowedMinuit2Errors.end(),
                       minuit2Status)==0) 
        {
          return false;
        }
      }
    }
    
    // check Minos status
    if (minosStatus!=0) 
    {
      if (allowedMinosErrors.empty()) return false;
      else 
      {
        // return false if status not in allowed statuses
        if (std::count(allowedMinosErrors.begin(),
                       allowedMinosErrors.end(),
                       minosStatus)==0) 
        {
          return false;
        }
      }
    }
    
    // check Hesse status
    if (hesseStatus!=0) 
    {
      if (allowedHesseErrors.empty()) return false;
      else 
      {
        // return false if status not in allowed statuses
        if (std::count(allowedHesseErrors.begin(),
                       allowedHesseErrors.end(),
                       hesseStatus)==0) 
        {
          return false;
        }
      }
    }
    
    // all checks done, so return true
    return true;
  } // end allow errors
}

const char* getFitStatusMessages(const int& status,
                                 std::string& minuit2Message,
                                 std::string& minosMessage,
                                 std::string& hesseMessage)
{
  // first, check if Minos or Hesse were run
  bool hasMinos = false;
  bool hasHesse = false;
  if (status>9) {
    hasMinos=true;
    if (status>99) hasHesse=true;
  }
  
  int minuit2Status = status%10;
  std::stringstream ss_msg;

  std::stringstream ss_minuit2Message;
  if (minuit2Status==0) {
    ss_minuit2Message << "OK.";
    ss_msg << "MINUIT2: OK";
  }
  else 
  {
    ss_msg << "MINUIT2: BAD";
    if (minuit2Status==1) {
      ss_minuit2Message << "Covariance matrix was made positive definite.";
    }
    else if (minuit2Status==2) 
    {
      ss_minuit2Message << "Hesse is invalid.";
    }
    else if (minuit2Status==3) 
    {
      ss_minuit2Message << "EDM is above maximum.";
    }
    else if (minuit2Status==4) 
    {
      ss_minuit2Message << "Reached call limit.";
    }
    else if (minuit2Status==5) 
    {
      ss_minuit2Message << "Miscellaneous error.";
    }
    else 
    {
      ss_minuit2Message << "Unknown status code "
                        << minuit2Status << "!";
    }
  }
  minuit2Message=ss_minuit2Message.str();

  std::stringstream ss_minosMessage;
  if (hasMinos) 
  {
    int minosStatus = status/10%10;
    
    if (minosStatus==0) {
      ss_minosMessage << "OK.";
      ss_msg << ", MINOS: OK";
    }
    else 
    {
      ss_msg << ", MINOS: BAD";
      if (minosStatus==1) {
        ss_minosMessage
          << "Reached call limit when searching for lower error.";
      }
      else if (minosStatus==2) 
      {
        ss_minosMessage 
          << "Reached call limit when searching for upper error.";
      }
      else if (minosStatus==3) 
      {
        ss_minosMessage 
          << "New minimum found when searching for lower error.";
      }
      else if (minosStatus==4) 
      {
        ss_minosMessage 
          << "New minimum found when searching for upper error.";
      }
      else if (minosStatus==5) 
      {
        ss_minosMessage << "Miscellaneous error.";
      }
      else 
      {
        ss_minosMessage << "Unknown status code " 
                        << minosStatus << "!";
      }
    }
  }
  else 
  {
    ss_minosMessage << "OK (or not run).";
    ss_msg << ", MINOS: OK";
  }
  minosMessage = ss_minosMessage.str();

  std::stringstream ss_hesseMessage;
  if (hasHesse) 
  {
    int hesseStatus = status/100;
    
    if (hesseStatus==0) {
      ss_hesseMessage << "OK.";
      ss_msg << ", HESSE: OK";
    }
    else 
    {
      ss_msg << ", HESSE: BAD";
      if (hesseStatus==1) {
        ss_hesseMessage
          << "Hesse failed.";
      }
      else if (hesseStatus==2) 
      {
        ss_hesseMessage 
          << "Matrix inversion failed.";
      }
      else if (hesseStatus==3)
      {
        ss_hesseMessage
          << "Matrix is not positive definite.";
      }
      else 
      {
        ss_hesseMessage << "Unknown status code " 
                        << hesseStatus << "!";
      }
    }
  }
  else 
  {
    ss_hesseMessage << "OK (or not run).";
    ss_msg << ", HESSE: OK";
  }
  hesseMessage = ss_hesseMessage.str();

  return ss_msg.str().c_str();
}
