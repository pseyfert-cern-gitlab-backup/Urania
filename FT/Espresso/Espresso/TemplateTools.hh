/**
 * @addtogroup gr_espresso
 * @{
 */

/**
 * @file
 * @brief Utility template functions related mostly to smart pointers
 */

#ifndef ESPRESSO_TEMPLATETOOLS_HH 
#define ESPRESSO_TEMPLATETOOLS_HH 1

// Include files
#include <memory>

template<typename A, typename B>
using disable_if_same_or_derived =
  typename std::enable_if<
  !std::is_base_of<
    A,
    typename std::decay<B>::type
    >::value
  >::type;

#endif // ESPRESSO_TEMPLATETOOLS_HH


/**
 * @}
 */

