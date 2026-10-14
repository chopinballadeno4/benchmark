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

// ── GROUP B: propagation FAILURE ─────────────────────────────────────────────
// Inter-variable constraints — interval domain tracks variables independently
// and loses the relation expressed by FW_ASSERT / __ikos_assume.
unsigned b1_relational_sub(unsigned amount, unsigned m_size);
void     b2_ptr_overlap(char* d, unsigned ds, const char* s, unsigned ss);
void     b3_sum_bound(char* base, unsigned offset, unsigned size, unsigned capacity);

#endif /* BENCHMARK_H */
