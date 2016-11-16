#ifndef EFFICIENCY_DRAWUTILS_H 
#define EFFICIENCY_DRAWUTILS_H 1

// Include files
#include "TCanvas.h"
#include "RooPlot.h"

/** @class DrawUtils DrawUtils.h 
 *  
 *
 *  @author Francesco Dettori
 *  @date   2013-04-22
 */
namespace DrawUtils{
  
  RooPlot *PlotResiduals(const RooPlot *frame);
  TCanvas *PlotFitAndResiduals(RooPlot * frame,  const char *name="cFit", 
			       const char *title="Fit Results",
                               const char* tag="", int xSize = 600, int ySize = 640, bool log = true); 
    
};



#endif // EFFICIENCY_DRAWUTILS_H
