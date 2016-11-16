#ifndef CALIBDATASCRIPTS_CHECKFITRESULTS_H 
#define CALIBDATASCRIPTS_CHECKFITRESULTS_H 1

// Include files
#include <vector>

// forward declarations
class RooFitResult;
namespace RooPhysFit 
{
  class RooPhysFitter;
}

/** @class CheckFitResults CheckFitResults.h CalibDataScripts/CheckFitResults.h
 *  
 *
 *  Helper functions used to check the quality of the fit results from
 *  RooPhysFitter fits.
 *  
 *  @author Philip Hunt (LHCB)
 *  @date   2013-11-17
 */

/** Checks the covariance quality of the fit.

    The possible covariance quality status codes are:
    0: No error matrix calculated (FAILED);
    1: Diagonal approximation (NOT ACCURATE);
    2: Full error matrix, but forced positive definite (NOT ACCURATE);
    3: Full, accurate c0variance matrix (CONVERGED).

    N.B. The mass fitter will raise an exception if the fit snapshot
    can't be found.

    @param fitter A pointer to the mass fitter.
    @param fitName The name of the fit result snapshot to check.
    @param qual A reference to the covariance quality return code.
    @param convLevel If the covariance quality is >= to this number, the
    fit will be deemed 'converged' (by this function). Usually, you'll want
    to leave this at the default value of 3.
    @return true if the fit has coverged, else false.
*/
bool checkCovQual(const RooPhysFit::RooPhysFitter& fitter, 
                  const char* fitName, int& qual, int convLevel=3);

/** Given a covariance quality status code, returns a message indicating
    the quality according to MINUIT
*/
const char* getCovQualMessage(const int& qual);

/** Checks the estimated distance to the minimum (EDM) of the fit.

    N.B. The mass fitter will raise an exception if the fit snapshot
    can't be found.

    @param fitter A pointer to the mass fitter.
    @param fitName The name of the fit result snapshot to check.
    @param edm A reference to the EDM.
    @param maxEDM If the EDM is less than to this number, the
    fit will be deemed 'converged' (by this function).
    @return true if the fit has coverged, else false.
*/
bool checkEDM(const RooPhysFit::RooPhysFitter& fitter, 
              const char* fitName, double& edm, double maxEDM=1e-2);

/** Checks the status code of the fit.

    Any non-zero value will be deemed a failure, unless a list of
    allowed status codes are given.

    The status code statisfies:
    
    status = 100*hesseStatus + 10*minosStatus + minuit2Status
    
    where the possible muint2Status codes are:

    0: OK.
    1: Covariance matrix was made positive definite.
    2: Hesse is invalid.
    3: EDM is above maximum.
    4: Reached call limit.
    5: Miscellanous failure.
    
    the possible minosStatus codes are:
    
    0: OK.
    1: Reached call limit when searching for lower error.
    2: Reached call limit when searching for upper error.
    3: New minimum found when searching for lower error.
    4: New minimum found when searching for upper error.
    5: Miscellaneous failure.

    and the possible hesseStatus codes are:
    
    O: OK.
    1: Hesse failed.
    2: Matrix inversion failed.
    3: Matrix is not positive definite.

    N.B. The mass fitter will raise an exception if the fit snapshot
    can't be found.

    @param fitter A pointer to the mass fitter.
    @param fitName The name of the fit result snapshot to check.
    @param status A reference to the status code.
    @param allowedMinuit2Errors An optional list of allowed Minuit2 errors.
    @param allowedMinosErrors An optional list of allowed Minos errors.
    @param allowedHesseErrors An optional list of allowed Hesse errors.
    @return true if the fit has coverged, else false.
*/
bool checkFitStatus(const RooPhysFit::RooPhysFitter& fitter, 
                    const char* fitName, int& status,
                    const std::vector<int>& allowedMinuit2Errors
                    = std::vector<int>(),
                    const std::vector<int>& allowedMinosErrors
                    = std::vector<int>(),
                    const std::vector<int>& allowedHesseErrors
                    = std::vector<int>());

/** Given a fit status code, returns a message indicating
    whether or not there was an error in Minuit2, Minos or Hesse.
    
    The additional arguments are references to strings containing 
    verbose messages about the Minuit2, Minos and Hesse statuses
    respectively.
*/
const char* getFitStatusMessages(const int& status,
                                 std::string& minuit2Message,
                                 std::string& minosMessage,
                                 std::string& hesseMessage
                                 );

#endif // CALIBDATASCRIPTS_CHECKFITRESULTS_H
