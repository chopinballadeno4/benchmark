#ifndef FW_ASSERT_HPP
#define FW_ASSERT_HPP

#include <cstddef>
#include <cstdint>

using FwSizeType = std::size_t;
using FwAssertArgType = std::intmax_t;

namespace Fw {

// [[noreturn]] 없음 → Infer 는 SwAssert 가 반환 가능하다고 가정
// 구현은 sw_assert.cpp 에 분리 → Infer 가 내부를 볼 수 없음
int SwAssert(const char* file, FwSizeType lineNo);
int SwAssert(const char* file, FwAssertArgType arg1, FwSizeType lineNo);
int SwAssert(const char* file, FwAssertArgType arg1, FwAssertArgType arg2, FwSizeType lineNo);
int SwAssert(const char* file, FwAssertArgType arg1, FwAssertArgType arg2, FwAssertArgType arg3, FwSizeType lineNo);
int SwAssert(const char* file, FwAssertArgType arg1, FwAssertArgType arg2, FwAssertArgType arg3, FwAssertArgType arg4, FwSizeType lineNo);
int SwAssert(const char* file, FwAssertArgType arg1, FwAssertArgType arg2, FwAssertArgType arg3, FwAssertArgType arg4, FwAssertArgType arg5, FwSizeType lineNo);
int SwAssert(const char* file, FwAssertArgType arg1, FwAssertArgType arg2, FwAssertArgType arg3, FwAssertArgType arg4, FwAssertArgType arg5, FwAssertArgType arg6, FwSizeType lineNo);

} // namespace Fw

#define FW_ASSERT(cond, ...) \
    ((void)((cond) ? 0 : Fw::SwAssert(__FILE__, ##__VA_ARGS__, static_cast<FwSizeType>(__LINE__))))

#endif // FW_ASSERT_HPP
