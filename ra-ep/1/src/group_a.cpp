#include "benchmark.h"

// GROUP A — FW_ASSERT constraint propagation: IKOS proves SAFE
//
// Each function asserts a single-variable constraint before an operation.
// If IKOS understands FW_ASSERT as a path-narrowing assumption, the
// subsequent operation is provably safe.  Expected result: no warning.

// A1: Ordered unsigned subtraction
//   Models: Serializable.cpp LinearBufferBase::getDeserializeSizeLeft()
//           FW_ASSERT(m_serLoc >= m_deserLoc) → return m_serLoc - m_deserLoc
unsigned a1_ordered_sub(unsigned a, unsigned b) {
    FW_ASSERT(a >= b);
    return a - b;
}

// A2: Equality-narrowed enum dispatch
//   Models: PolyType::get(U8&) — FW_ASSERT(TYPE_U8 == m_dataType)
int a2_enum_equality(Tag t, int va, int vb) {
    FW_ASSERT(t == T_A);
    return (t == T_A) ? va : vb;
}

// A3: Single-variable upper-bound arithmetic
//   Models: TimeInterval::set() — FW_ASSERT(useconds < 1000000)
unsigned a3_range_arith(unsigned x) {
    FW_ASSERT(x < 1000000u);
    return x + 500000u;
}
