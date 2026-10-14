#ifndef FW_STRINGUTILS_HPP
#define FW_STRINGUTILS_HPP

#include <Fw/FPrimeBasicTypes.hpp>

namespace Fw {
namespace StringUtils {
char* string_copy(char* destination, const char* source, FwSizeType num);
FwSizeType string_length(const char* source, FwSizeType maxlen);
}  // namespace StringUtils
}  // namespace Fw

#endif  // FW_STRINGUTILS_HPP
