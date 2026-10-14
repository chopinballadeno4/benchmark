#ifndef FPRIME_BASIC_TYPES_HPP
#define FPRIME_BASIC_TYPES_HPP

#include <limits>
extern "C" {
#include <Fw/FPrimeBasicTypes.h>
}
#include <Fw/Types/BasicTypes.hpp>

// Size of assert message buffer (mirrors FwAssertTextSize from FppConstantsAc.hpp).
#ifndef FW_ASSERT_TEXT_SIZE
#define FW_ASSERT_TEXT_SIZE 256
#endif

#endif  // FPRIME_BASIC_TYPES_HPP
