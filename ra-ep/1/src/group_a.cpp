#include "benchmark.h"

// GROUP A — FW_ASSERT constraint propagation: IKOS proves SAFE

// A1: Ordered unsigned subtraction
unsigned a1_ordered_sub(unsigned a, unsigned b) {
    FW_ASSERT(a >= b);
    return a - b;
}

// A2: Equality-narrowed enum dispatch
int a2_enum_equality(Tag t, int va, int vb) {
    FW_ASSERT(t == T_A);
    return (t == T_A) ? va : vb;
}

// A3: Single-variable upper-bound arithmetic
unsigned a3_range_arith(unsigned x) {
    FW_ASSERT(x < 1000000u);
    return x + 500000u;
}
