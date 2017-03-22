/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief Regression link functions and their inverses and derivatives
 */

#ifndef ESPRESSO_REGRESSIONFUNCTIONS_HH 
#define ESPRESSO_REGRESSIONFUNCTIONS_HH 1

// Include files

namespace Espresso 
{
  namespace Regression 
  {
    enum class LinkType {
      Mistag,   ///< in basis &eta;
      Logit,    ///< in basis log(1-&eta;) - log(&eta;)
      Probit,   ///< in basis &radic;2 erf<sup>-1</sup>(1-2&eta;)
      Cauchit    ///< in basis -cot(&pi;(1-&eta;))
    };
    constexpr Regression::LinkType DefaultLinkType = Regression::LinkType::Mistag;
    
    /**
     */
    double Link(double p, LinkType link = DefaultLinkType);

    /**
     */
    double DLink(double p, LinkType link = DefaultLinkType);

    /**
     */
    double InvLink(double p, LinkType link = DefaultLinkType);

    /**
     */
    double DInvLink(double p, LinkType link = DefaultLinkType);

  }
    
}

#endif // ESPRESSO_REGRESSIONFUNCTIONS_HH

/**
 * @}
 */
