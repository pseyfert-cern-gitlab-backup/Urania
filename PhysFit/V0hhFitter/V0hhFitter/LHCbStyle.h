#ifndef V0HHFITTER_LHCBSTYLE_H
#define V0HHFITTER_LHCBSTYLE_H 1

#include <iostream>

#include "TROOT.h"
#include "TPaveText.h"
#include "TStyle.h"
#include "TText.h"
#include "TLatex.h"

namespace V0hhFit {// Fiting Analysis Simulataneous Toys

    class LHCbStyle {
        public:
            explicit LHCbStyle();
            virtual ~LHCbStyle();

            TStyle* getStyle() const { return m_lhcbStyle;};
            TStyle* getStyle(const std::string& name) const;
            TStyle* getStyle(const TString& name) const;
            TText* lhcbLabel() const;
            TLatex* lhcbLatex() const;
            TPaveText* lhcbName() const;
            TPaveText* addText( const std::string& optLR = "L",
       const std::string& optText = "LHCb" ) const;
            static const Int_t m_lhcbFont; 
            static const Double_t m_lhcbWidth; 
            static const Double_t m_lhcbTSize; 
        private:
            ClassDef(LHCbStyle,1);
            TStyle* m_lhcbStyle;
    };
}

#endif // V0HHFITTER_LHCBSTYLE_H
