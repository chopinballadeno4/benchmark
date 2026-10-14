#include "benchmark.h"

// GROUP B — FW_ASSERT constraint propagation: IKOS warns despite assert
//
// Each function asserts a relation between two or more variables.
// The interval domain tracks variables independently, so inter-variable
// constraints expressed by FW_ASSERT cannot be represented as box
// constraints.  Expected result: warning remains.

// B1: Relational unsigned subtraction
//   Models: Buffer::advance() — FW_ASSERT(amount <= m_size) → m_size -= amount
unsigned b1_relational_sub(unsigned amount, unsigned m_size) {
    FW_ASSERT(amount <= m_size);
    return m_size - amount;
}

// B2: Pointer non-overlap assertion
//   Models: StringUtils::string_copy()
//           FW_ASSERT((dest+dest_size <= src) || (src+src_size <= dest))
void b2_ptr_overlap(char* d, unsigned ds, const char* s, unsigned ss) {
    FW_ASSERT((d + ds <= s) || (s + ss <= d));
    d[0] = s[0];
}

// B3: Two-variable sum-bound check
//   Models: Buffer bounds check — FW_ASSERT(offset + size <= capacity)
void b3_sum_bound(char* base, unsigned offset, unsigned size, unsigned capacity) {
    FW_ASSERT(offset + size <= capacity);
    char* end = base + offset + size;
    (void)end;
}
