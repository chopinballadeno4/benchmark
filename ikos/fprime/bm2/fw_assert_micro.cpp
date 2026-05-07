#include <cstddef>
#include <cstdint>

using FwSizeType    = std::size_t;
using FwAssertArgType = std::intmax_t;

// Declaration only — implementation in a separate TU (sw_assert.cpp).
// Missing [[noreturn]] is intentional: this mirrors the real FPrime header.
int SwAssert(const char* file, FwSizeType lineNo);
int SwAssert(const char* file, FwAssertArgType arg1, FwSizeType lineNo);

#define FW_ASSERT(cond, ...) \
((void)((cond) ? 0 \
: SwAssert(__FILE__, ##__VA_ARGS__, \
static_cast<FwSizeType>(__LINE__))))

// External sources — return values are unknown to the analyzer.
extern int*          getBuffer();
extern unsigned int  getIndex();

// [NULL_DEREFERENCE false positive]
// FW_ASSERT(ptr != nullptr) is a guard: ptr is non-null on the line below.
// Without [[noreturn]], the analyzer keeps the null path alive → false positive.
void test_null(void) {
    int* ptr = getBuffer();
    FW_ASSERT(ptr != nullptr);
    *ptr = 42;
}

// [BUFFER_OVERRUN false positive]
// FW_ASSERT(idx < 10) narrows idx to [0, 9].
// Without [[noreturn]], the analyzer retains idx in [0, 19] → false positive.
void test_bounds(void) {
    int arr[10];
    unsigned int idx = getIndex() % 20;
    FW_ASSERT(idx < 10);
    arr[idx] = 42;
}

int main() {
    test_null();
    test_bounds();
    return 0;
}