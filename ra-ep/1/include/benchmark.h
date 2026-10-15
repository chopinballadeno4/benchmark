#ifndef BENCHMARK_H
#define BENCHMARK_H

#include <Fw/Types/Assert.hpp>

// Tag enum shared between group_a.cpp and harness.cpp.
// Models the integer-typed discriminants used in PolyType / FilePacket.
enum Tag { T_A = 0, T_B = 1, T_C = 2 };

// ── GROUP A: propagation SUCCESS ─────────────────────────────────────────────
// Single-variable constraints — interval domain can narrow one variable's range.
unsigned a1_ordered_sub(unsigned a, unsigned b);
int      a2_enum_equality(Tag t, int va, int vb);
unsigned a3_range_arith(unsigned x);

// ── GROUP B: warning cases ──────────────────────────────────────────────
// Includes both a relational-domain precision loss and a real boundary error.
unsigned b1_relational_sub(unsigned amount, unsigned m_size);
unsigned b2_boundary_underflow(unsigned a);

#endif /* BENCHMARK_H */
