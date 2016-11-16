#ifndef V0HHFITTER_LIKESRATIOPLOT_H
#define V0HHFITTER_LIKESRATIOPLOT_H 1

// STL include
#include <vector>

// ROOT
#include "TString.h"
#include "TH1F.h"

// Local include
#include "V0hhFitter/LHCbStyle.h"


class TH1F;

namespace V0hhFit {

    class FitterLikesRatioPlot {

        public:
            FitterLikesRatioPlot(TString compThatsRatioNumerator);
            virtual ~FitterLikesRatioPlot();

            virtual void dataVsToyPlot(TH1F DataHisto, std::vector<TH1F> componentToyHistos, Double_t scaleFactor,
                    UInt_t numBins = 50, Double_t startRange = 0.0, Double_t endRange = 1.0,
                    Bool_t drawDataVsToyLeg = kTRUE, Bool_t doLog = kTRUE,
                    Bool_t useROOTDefaultYAxisRange = kTRUE, Double_t minYAxisValue = 0.9);

            virtual void toyCompsPlot(std::vector<TH1F> componentToyHistos, std::vector<TString> componentNames, Int_t numComps, Int_t numeratorComp,
                    Double_t scaleFactor, UInt_t numBins = 50, Double_t startRange = 0.0, Double_t endRange = 1.0,
                    Double_t toyCompsLegTextSize = 0.045, Double_t toyCompsLegPosXStart = 0.30,
                    Double_t toyCompsLegPosYStart = 0.40, Double_t toyCompsLegPosXEnd = 0.75,
                    Double_t toyCompsLegPosYEnd = 0.85, Bool_t drawToyCompsLeg = kTRUE, Bool_t doLog = kTRUE,
                    Bool_t useROOTDefaultYAxisRange = kTRUE, Double_t minYAxisValue = 0.9);

            virtual void swap(Int_t& x, Int_t& y);

        protected:

        private:
            TString m_likeRatNum; // Likelihood ratio numerator component
            LHCbStyle m_lhcbStyle;

            ClassDef(FitterLikesRatioPlot,1);
    };

}
#endif // V0HHFITTER_LIKESRATIOPLOT_H


