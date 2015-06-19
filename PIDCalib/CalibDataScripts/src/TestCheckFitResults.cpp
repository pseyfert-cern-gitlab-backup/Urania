/* Used to test that the CheckFitResults functions work correctly.
*/
#include <vector>
#include <string>
#include <iostream>

#include "RooFitResult.h"
#include "RooWorkspace.h"

#include "RooPhysFitter/RooDMassFitter.h"

// local
#include "CalibDataScripts/CheckFitResults.h"

static const std::vector<int> emptyVectI;
static const std::string sec(80, '*');

// returns "PASSED" if true, else "FAILED"
std::string testMessage(bool result) 
{
  if (result) return "PASSED";
  else return "FAILED";
}

// A dummy RooFitResult class that allows me to set the
// status code, covariance quality code and EDM,
// which are protected functions, doing some initialization
// in order to avoid segfaults
class TestRooFitResult : public RooFitResult 
{
public:
  TestRooFitResult(const char* name=0, const char* title=0) 
    : RooFitResult(name,title) {
    // fill initialization stuff
    RooArgList saveConstList;
    RooArgList saveFloatInitList;
    RooArgList saveFloatFinalList;
    this->setConstParList(saveConstList);
    this->setInitParList(saveFloatInitList);
    this->setStatus(-1);
    this->setCovQual(-1);
    this->setMinNLL(-1.0);
    this->setNumInvalidNLL(-1.0);
    this->setEDM(-1.0);
    this->setFinalParList(saveFloatFinalList);
    TMatrixDSym cov;
    this->setCovarianceMatrix(cov);
    std::vector< std::pair<std::string,int> > history;
    this->setStatusHistory(history); 
  }
  void SetStatus(const Int_t& val) 
  {
    this->setStatus(val);
  }
  void SetCovQual(const Int_t& val) 
  {
    this->setCovQual(val);
  }
  void SetEDM(const Double_t& val) 
  {
    this->setEDM(val);
  }
};
  
// Creates a "fake" fit result with name "fitName",
// with the MINUIT2, Minos and Hesse statuses set to 
// "minuit2Status", "minosStatus" and "hesseStatus"
// respectively (N.B. the minosStatus and hesseStatus
// are optional)
RooFitResult makeFitResWithStatus(const char* fitName,
                                  const Int_t& minuit2Status,
                                  const Int_t& minosStatus=0,
                                  const Int_t& hesseStatus=0) 
{
  TestRooFitResult res(fitName, "");
  Int_t status = (100*hesseStatus)+(10*minosStatus)+minuit2Status;
  res.SetStatus(status);
  return res;
}

// Creates a "fake" fit result with name "fitName",
// with the covariance quality set to "qual"
RooFitResult makeFitResWithCovQual(const char* fitName,
                                    const Int_t& qual) 
{
  TestRooFitResult res(fitName, "");
  res.SetCovQual(qual);
  return res;
}

// Creates a "fake" fit result with name "fitName",
// with the estimate distance to minimum (EDM) set to "edm"
RooFitResult makeFitResWithEDM(const char* fitName,
                                const Double_t& edm) 
{
  TestRooFitResult res(fitName, "");
  res.SetEDM(edm);
  return res;
}

// Run various tests of the functionality of checking the
// fit status for the given MINUIT2, Minos and Hesse 
// statuses: "minuit2Status", "minosStatus" and "hesseStatus"
//
// Returns false if one of the tests failed.
// If "returnOnFailure" is true, then stop further testing
// after a test has failed.
bool DoFitStatusTests(const Int_t& minuit2Status, 
                      const Int_t& minosStatus,
                      const Int_t& hesseStatus,
                      Bool_t returnOnFailure=kTRUE) 
{
  std::cout << "Running status tests for "
            << "(minuit2Status, minosStatus, hesseStatus) = ("
            << minuit2Status << ", " << minosStatus << ", "
            << hesseStatus << ")" << std::endl;
  
  // expected combined status
  Int_t expectedStatus = (100*hesseStatus)+(10*minosStatus)+minuit2Status;
  
  // flags indicating whether the status check should pass or fail
  Bool_t expectedRes = kTRUE;
  expectedRes &= (minuit2Status==0);
  expectedRes &= (minosStatus==0);
  expectedRes &= (hesseStatus==0);

  // have we passed all tests?
  Bool_t test = kTRUE;

  // allowed status codes, excl, 0
  Bool_t testAllowErrors = kFALSE;
  
  std::vector<int> allowedMinuit2Errors;
  if (minuit2Status!=0) {
    testAllowErrors=kTRUE;
    allowedMinuit2Errors.push_back(minuit2Status);
  }
  std::vector<int> allowedMinosErrors;
  if (minosStatus!=0) {
    testAllowErrors=kTRUE;
    allowedMinosErrors.push_back(minosStatus);
  }
  std::vector<int> allowedHesseErrors; 
  if (hesseStatus!=0) {
    testAllowErrors=kTRUE;
    allowedHesseErrors.push_back(hesseStatus);
  }
  
  // make the "fake" fitter and workspace
  RooPhysFit::RooPhysFitter fitter("fitter","");

  RooWorkspace ws("ws", "");
  fitter.SetWS(&ws);
  
  // get the fake fit result for the specific status codes
  RooFitResult rfres = makeFitResWithStatus("rfres_fitRes", minuit2Status,
                                            minosStatus, hesseStatus);
  ws.import(rfres);
  
  // check the result and status are correct
  Int_t status=-1;
  Bool_t res = checkFitStatus(fitter, "fitRes", status);
  
  // check result is correct
  Bool_t passed = (res==expectedRes);
  test&=passed;
  std::cout << "Test checkFitStatus: " << testMessage(passed) << std::endl;
  if (!passed) 
  {
    std::cerr << "checkFitStatus returned " << std::boolalpha << res 
              << ", expected " << std::boolalpha << expectedRes << std::endl;
    if (returnOnFailure) return kFALSE;
  }
  
  // check status is correct
  passed = (status==expectedStatus);
  test&=passed;
  std::cout << "Test checkFitStatus status code: "
            << testMessage(passed) << std::endl;
  if (!passed) 
  {
    std::cerr << "checkFitStatus status code is " << status 
              << ", expected " << expectedStatus << std::endl;
    if (returnOnFailure) return kFALSE;
  }
  
  // print the status messages (user needs to check that these are correct)
  std::string minuit2Message="";
  std::string minosMessage="";
  std::string hesseMessage="";
  const char* msg = getFitStatusMessages(status, minuit2Message,
                                         minosMessage, hesseMessage);
  
  std::cout << "getFitStatusMessage: \"" << msg << "\"" << std::endl;
  std::cout << "Minuit2 message: \"" << minuit2Message << "\"" << std::endl;
  std::cout << "Minos message: \"" << minosMessage << "\"" << std::endl;
  std::cout << "Hesse message: \"" << hesseMessage << "\"" << std::endl;

  // check that the "allowed" errors functionality works
  if (testAllowErrors) 
  {
    // first, try allowing the specific Minuit2, Minos and Hesse messages
    expectedRes = kTRUE;
  
    res = checkFitStatus(fitter, "fitRes", status,
                         allowedMinuit2Errors,
                         allowedMinosErrors,
                         allowedHesseErrors);
  
    // check result is correct
    passed = (res==expectedRes);
    test&=passed;
    std::cout << "Test checkFitStatus (allow errors): " 
              << testMessage(passed) << std::endl;
    if (!passed) 
    {
      std::cerr << "checkFitStatus (allow errors) returned " 
                << std::boolalpha << res 
                << ", expected " << std::boolalpha << expectedRes << std::endl;
      if (returnOnFailure) return kFALSE;
    }

    // check status is correct
    passed = (status==expectedStatus);
    test&=passed;
    std::cout << "Test checkFitStatus (allow errors) status code: "
              << testMessage(passed) << std::endl;
    if (!passed) 
    {
      std::cerr << "checkFitStatus (allow errors) status code is " << status 
                << ", expected " << expectedStatus << std::endl;
      if (returnOnFailure) return kFALSE;
    }

    // now check individual errors
    if ( !(allowedMinuit2Errors.empty()) ) 
    {
       expectedRes = kTRUE;
       if ( !(allowedMinosErrors.empty()) || !(allowedHesseErrors.empty()) ) 
       {
         expectedRes = kFALSE;
       }
       
       res = checkFitStatus(fitter, "fitRes", status,
                            allowedMinuit2Errors,
                            emptyVectI,
                            emptyVectI);
         
       // check result is correct
       passed = (res==expectedRes);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minuit2 error): " 
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minuit2 error) returned " 
                   << std::boolalpha << res 
                   << ", expected " << std::boolalpha
                   << expectedRes << std::endl;
         if (returnOnFailure) return kFALSE;
       }
  
       // check status is correct
       passed = (status==expectedStatus);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minuit2 error) status code: "
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minuit2 error) status code is "
                   << status << ", expected " << expectedStatus << std::endl;
         if (returnOnFailure) return kFALSE;
       }
    }
    if ( !(allowedMinosErrors.empty()) ) 
    {
       expectedRes = kTRUE;
       if ( !(allowedMinuit2Errors.empty()) || !(allowedHesseErrors.empty()) ) 
       {
         expectedRes = kFALSE;
       }

       res = checkFitStatus(fitter, "fitRes", status,
                            emptyVectI,
                            allowedMinosErrors,
                            emptyVectI);
  
       // check result is correct
       passed = (res==expectedRes);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minos error): " 
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minos error) returned " 
                   << std::boolalpha << res 
                   << ", expected " << std::boolalpha
                   << expectedRes << std::endl;
         if (returnOnFailure) return kFALSE;
       }
  
       // check status is correct
       passed = (status==expectedStatus);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minos error) status code: "
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minos error) status code is "
                   << status << ", expected " << expectedStatus << std::endl;
         if (returnOnFailure) return kFALSE;
       }
    }
    if ( !(allowedHesseErrors.empty()) ) 
    {
       expectedRes = kTRUE;
       if ( !(allowedMinosErrors.empty()) || !(allowedMinuit2Errors.empty()) ) 
       {
         expectedRes = kFALSE;
       }

       res = checkFitStatus(fitter, "fitRes", status,
                            emptyVectI,
                            emptyVectI,
                            allowedHesseErrors);
  
       // check result is correct
       passed = (res==expectedRes);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Hesse error): " 
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Hesse error) returned " 
                   << std::boolalpha << res 
                   << ", expected " << std::boolalpha
                   << expectedRes << std::endl;
         if (returnOnFailure) return kFALSE;
       }
  
       // check status is correct
       passed = (status==expectedStatus);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Hesse error) status code: "
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Hesse error) status code is "
                   << status << ", expected " << expectedStatus << std::endl;
         if (returnOnFailure) return kFALSE;
       }
    }

    // now check "double" errors
    if ( !(allowedMinuit2Errors.empty()) && !(allowedMinosErrors.empty()) ) 
    {
      expectedRes = kTRUE;
      if ( !(allowedHesseErrors.empty()) ) 
      {
        expectedRes = kFALSE;
      }

      res = checkFitStatus(fitter, "fitRes", status,
                           allowedMinuit2Errors,
                           allowedMinosErrors,
                           emptyVectI);
  
       // check result is correct
       passed = (res==expectedRes);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minuit2+Minos error): " 
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minuit2+Minos error) returned " 
                   << std::boolalpha << res 
                   << ", expected " << std::boolalpha
                   << expectedRes << std::endl;
         if (returnOnFailure) return kFALSE;
       }
  
       // check status is correct
       passed = (status==expectedStatus);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minuit2+Minos error) status code: "
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minuit2+Minos error) status code is "
                   << status << ", expected " << expectedStatus << std::endl;
         if (returnOnFailure) return kFALSE;
       }
    }
    
    if ( !(allowedMinuit2Errors.empty()) && !(allowedHesseErrors.empty()) )
    {
      expectedRes = kTRUE;
      if ( !(allowedMinosErrors.empty()) ) 
      {
        expectedRes = kFALSE;
      }

      res = checkFitStatus(fitter, "fitRes", status,
                           allowedMinuit2Errors,                           
                           emptyVectI,
                           allowedHesseErrors);
  
       // check result is correct
       passed = (res==expectedRes);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minuit2+Hesse error): " 
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minuit2+Hesse error) returned " 
                   << std::boolalpha << res 
                   << ", expected " << std::boolalpha
                   << expectedRes << std::endl;
         if (returnOnFailure) return kFALSE;
       }
  
       // check status is correct
       passed = (status==expectedStatus);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minuit2+Hesse error) status code: "
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minuit2+Hesse error) status code is "
                   << status << ", expected " << expectedStatus << std::endl;
         if (returnOnFailure) return kFALSE;
       }
    }
    
    if ( !(allowedMinosErrors.empty()) && !(allowedHesseErrors.empty()) )
    {
      expectedRes = kTRUE;
      if ( !(allowedMinuit2Errors.empty()) ) 
      {
        expectedRes = kFALSE;
      }

      res = checkFitStatus(fitter, "fitRes", status,
                           emptyVectI,
                           allowedMinosErrors,                           
                           allowedHesseErrors);
  
       // check result is correct
       passed = (res==expectedRes);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minos+Hesse error): " 
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minos+Hesse error) returned " 
                   << std::boolalpha << res 
                   << ", expected " << std::boolalpha
                   << expectedRes << std::endl;
         if (returnOnFailure) return kFALSE;
       }
  
       // check status is correct
       passed = (status==expectedStatus);
       test&=passed;
       std::cout << "Test checkFitStatus (allow Minos+Hesse error) status code: "
                 << testMessage(passed) << std::endl;
       if (!passed) 
       {
         std::cerr << "checkFitStatus (allow Minos+Hesse error) status code is "
                   << status << ", expected " << expectedStatus << std::endl;
         if (returnOnFailure) return kFALSE;
       }
    }
  } // test allow errors
  return test;
}

// Run various tests of the functionality of checking the
// covariance quality for the given covariance quality status code
//
// Returns false if one of the tests failed.
// If "returnOnFailure" is true, then stop further testing
// after a test has failed.
bool DoCovQualTests(const Int_t& qual, Bool_t returnOnFailure=kTRUE) 
{
  std::cout << "Running status tests for covariance quality code = "
            << qual << std::endl;

  // flags indicating whether the status check should pass or fail
  Bool_t expectedRes = (qual==3);

  // have we passed all tests?
  Bool_t test = kTRUE;

  // make the "fake" fitter and workspace
  RooPhysFit::RooPhysFitter fitter("fitter","");

  RooWorkspace ws("ws", "");
  fitter.SetWS(&ws);
  
  // get the fake fit result for the specific status codes
  RooFitResult rfres = makeFitResWithCovQual("rfres_fitRes", qual);
  ws.import(rfres);
  
  // check the result and status are correct
  Int_t returnedQual=-1;
  Bool_t res = checkCovQual(fitter, "fitRes", returnedQual);
  
  // check result is correct
  Bool_t passed = (res==expectedRes);
  test&=passed;
  std::cout << "Test checkCovQual: " << testMessage(passed) << std::endl;
  if (!passed) 
  {
    std::cerr << "checkCovQual returned " << std::boolalpha << res 
              << ", expected " << std::boolalpha << expectedRes << std::endl;
    if (returnOnFailure) return kFALSE;
  }
  
  // check covariance quality status is correct
  passed = (returnedQual==qual);
  test&=passed;
  std::cout << "Test checkCovQual status code: "
            << testMessage(passed) << std::endl;
  if (!passed) 
  {
    std::cerr << "checkCovQual status code is " << returnedQual 
              << ", expected " << qual << std::endl;
    if (returnOnFailure) return kFALSE;
  }
  
  // print the status messages (user needs to check that this is correct)
  const char* msg = getCovQualMessage(returnedQual);
  
  std::cout << "getFitCovQualMessage: \"" << msg << "\"" << std::endl;

  // check that the result is true if the convergence level is reduced
  if (qual!=3) 
  {
    expectedRes=kTRUE;
    returnedQual=-1;
    res = checkCovQual(fitter, "fitRes", returnedQual, qual);
  
    // check result is correct
    passed = (res==expectedRes);
    test&=passed;
    std::cout << "Test checkCovQual (min converge level = " << qual << "): "
              << testMessage(passed) << std::endl;
    if (!passed) 
    {
      std::cerr << "checkCovQual  (min converge level = "
                << qual << ") returned " << std::boolalpha << res 
                << ", expected " << std::boolalpha << expectedRes << std::endl;
      if (returnOnFailure) return kFALSE;
    }
  }
  
  return test;
}
  
// Run various tests of the functionality of checking the
// EDM for a given max EDM
//
// Returns false if one of the tests failed.
// If "returnOnFailure" is true, then stop further testing
// after a test has failed.
bool DoEDMTests(const Double_t& edm, Bool_t returnOnFailure=kTRUE) 
{
  const Double_t maxEDM=1e-2;
  
  std::cout.precision(3);
  std::cout << "Running EDM tests for EDM = "
            << edm << ", maxEDM = " << maxEDM << std::endl;

  // flags indicating whether the status check should pass or fail
  Bool_t expectedRes = (edm<maxEDM);

  // have we passed all tests?
  Bool_t test = kTRUE;

  // make the "fake" fitter and workspace
  RooPhysFit::RooPhysFitter fitter("fitter","");

  RooWorkspace ws("ws", "");
  fitter.SetWS(&ws);
  
  // get the fake fit result for the specific status codes
  RooFitResult rfres = makeFitResWithEDM("rfres_fitRes", edm);
  ws.import(rfres);
  
  // check the result and status are correct
  Double_t returnedEDM=-1.0;
  Bool_t res = checkEDM(fitter, "fitRes", returnedEDM);
  
  // check result is correct
  Bool_t passed = (res==expectedRes);
  test&=passed;
  std::cout << "Test checkEDM: " << testMessage(passed) << std::endl;
  if (!passed) 
  {
    std::cerr << "checkEDM returned " << std::boolalpha << res 
              << ", expected " << std::boolalpha << expectedRes << std::endl;
    if (returnOnFailure) return kFALSE;
  }
  
  // check EDM is correct (user should check manually because of limitations
  // of float comparison
  std::cout << "checkCovQual: EDM = " << returnedEDM 
            << " (expected EDM = " << edm << ")" << std::endl;
  std::cout << "checkCovQual: EDM below max? " << std::boolalpha << res 
            << " (expected " << std::boolalpha << expectedRes << ")" << std::endl;
  return test;
}

int main(int /*argc*/, char** /*argv*/) 
{

  // OK
  std::cout << sec << std::endl;
  std::cout << "Testing all OK" << std::endl;
  DoFitStatusTests(0, 0, 0);

  /*** run minuit2 status checks ***/

  // Covariance matrix made +ve definite
  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status 1 (+ve definite)" << std::endl;
  DoFitStatusTests(1, 0, 0);

  // Invalid Hesse
  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status 2 (invalid Hesse)" << std::endl;
  DoFitStatusTests(2, 0, 0);

  // EDM above max
  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status 3 (EDM above max)" << std::endl;
  DoFitStatusTests(3, 0, 0);

  // Reached max call
  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status 4 (reached max call)" << std::endl;
  DoFitStatusTests(4, 0, 0);

  // Misc
  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status 5 (misc.)" << std::endl;
  DoFitStatusTests(5, 0, 0);

  // doesn't exist
  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status -1 (invalid status code)" << std::endl;
  DoFitStatusTests(-1, 0, 0);

  /*** run minos status checks ***/

  // Reached max call when searching for lower limit
  std::cout << sec << std::endl;
  std::cout << "Testing Minos status 1 (reach max call - lower)" << std::endl;
  DoFitStatusTests(0, 1, 0);

  // Reached max call when searching for upper limit
  std::cout << sec << std::endl;
  std::cout << "Testing Minos status 2 (reach max call - upper)" << std::endl;
  DoFitStatusTests(0, 2, 0);

  // New min found when searching for lower limit
  std::cout << sec << std::endl;
  std::cout << "Testing Minos status 3 (new min - lower)" << std::endl;
  DoFitStatusTests(0, 3, 0);

  // New min found when searching for upper limit
  std::cout << sec << std::endl;
  std::cout << "Testing Minos status 4 (new min - upper)" << std::endl;
  DoFitStatusTests(0, 4, 0);

  // Misc
  std::cout << sec << std::endl;
  std::cout << "Testing Minos status 5 (misc.)" << std::endl;
  DoFitStatusTests(0, 5, 0);

  // doesn't exist
  std::cout << sec << std::endl;
  std::cout << "Testing Minos status 6 (invalid status code)" << std::endl;
  DoFitStatusTests(0, 6, 0);

  /*** run hesse status checks ***/

  // Hesse failed
  std::cout << sec << std::endl;
  std::cout << "Testing Hesse status 1 (Hesse failed)" << std::endl;
  DoFitStatusTests(0, 0, 1);

  // Matrix inversion failed
  std::cout << sec << std::endl;
  std::cout << "Testing Hesse status 2 (inversion failed)" << std::endl;
  DoFitStatusTests(0, 0, 2);

  // Matrix inversion failed
  std::cout << sec << std::endl;
  std::cout << "Testing Hesse status 3 (not +ve definite)" << std::endl;
  DoFitStatusTests(0, 0, 3);

  /*** run double error status checks ***/
  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status 1, Minos status 2" << std::endl;
  DoFitStatusTests(1, 2, 0);

  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status 1, Hesse status 3" << std::endl;
  DoFitStatusTests(1, 0, 3);

  std::cout << sec << std::endl;
  std::cout << "Testing Minos status 3, Hesse status 2" << std::endl;
  DoFitStatusTests(0, 3, 2);

  /*** run triple error status checks ***/
  std::cout << sec << std::endl;
  std::cout << "Testing Miniut2 status 4, Minos status 1, Hesse status 1" 
            << std::endl;
  DoFitStatusTests(4, 1, 1);

  // doesn't exist
  std::cout << sec << std::endl;
  std::cout << "Testing Hesse status 4 (invalid status code)" << std::endl;
  DoFitStatusTests(0, 0, 4);

  /*** run covariance quality status checks ***/

  // OK
  std::cout << sec << std::endl;
  std::cout << "Testing covariance quality 3 (OK)" 
            << std::endl;
  DoCovQualTests(3);

  // Forced +ve definite
  std::cout << sec << std::endl;
  std::cout << "Testing covariance quality 2 (forced +ve definite)" 
            << std::endl;
  DoCovQualTests(2);

  // Diagonal approximation
  std::cout << sec << std::endl;
  std::cout << "Testing covariance quality 1 (diagonal approximation)" 
            << std::endl;
  DoCovQualTests(1);

  // No error matrix
  std::cout << sec << std::endl;
  std::cout << "Testing covariance quality 0 (no error matrix)" 
            << std::endl;
  DoCovQualTests(0);

  // doesn't exist
  std::cout << sec << std::endl;
  std::cout << "Testing covariance quality -1 (invalid status code)" 
            << std::endl;
  DoCovQualTests(-1);

  /*** run EDM checks ***/
  std::cout << sec << std::endl;
  std::cout << "Testing EDM 1e-7 (close to minimum)" 
            << std::endl;
  DoEDMTests(1e-7);

  std::cout << sec << std::endl;
  std::cout << "Testing EDM 0.1 (far from minimum)" 
            << std::endl;
  DoEDMTests(0.1);
}
