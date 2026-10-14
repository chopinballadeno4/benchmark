#include "benchmark.h"

// Benchmark entry point — mirrors analysis/ref_harness.cpp in the F Prime experiment.
//
// Inputs are derived from argc so that IKOS treats them as unknown integers
// rather than concrete constants, forcing the analyzer to consider the full
// input range and making FW_ASSERT the only source of constraint narrowing.
//
// Group A call sites are engineered so that the single-variable assume IS
// sufficient: one operand is a compile-time constant, or the variable is
// bounded by a single-variable inequality.
//
// Group B call sites use two independently-unknown variables so that the
// inter-variable relation in FW_ASSERT cannot be expressed in the interval
// domain after __ikos_assume.

int main(int argc, char** argv) {
    (void)argv;

    // Two uncorrelated unknown values.
    // ua: argc viewed as unsigned — IKOS interval [0, UINT_MAX].
    // ub: non-linear expression of argc; interval domain loses precision
    //     and approximates it as [0, UINT_MAX], independent of ua.
    const unsigned ua = static_cast<unsigned>(argc);
    const unsigned ub = static_cast<unsigned>(argc * argc);

    // ── GROUP A: expect SAFE (no IKOS warning) ──────────────────────────────

    // A1: a is unknown [0, UINT_MAX]; b is the constant 5.
    //     __ikos_assume(a >= 5) narrows a to [5, UINT_MAX] → a - 5 >= 0.
    (void)a1_ordered_sub(ua, 5u);

    // A2: t ∈ {T_A=0, T_B=1, T_C=2}.
    //     __ikos_assume(t == T_A) collapses t to {0} → branch always true.
    (void)a2_enum_equality(static_cast<Tag>(ua % 3u), 1, 2);

    // A3: x is unknown [0, UINT_MAX].
    //     __ikos_assume(x < 1000000) narrows x to [0, 999999]
    //     → x + 500000 ∈ [500000, 1499999], no overflow.
    (void)a3_range_arith(ua);

    // ── GROUP B: expect WARNING (IKOS warning despite assume) ───────────────

    // B1: amount=ua, m_size=ub — both [0, UINT_MAX], no trivial ordering.
    //     __ikos_assume(ua <= ub) cannot narrow either interval independently
    //     → ub - ua still appears to underflow.
    (void)b1_relational_sub(ua, ub);

    // B2: dst and src are distinct stack objects; IKOS cannot order them.
    //     The non-overlap assume is not representable → pointer warning.
    char dst[16] = {};
    const char src[] = "hello fprime";
    b2_ptr_overlap(dst, static_cast<unsigned>(sizeof(dst)),
                   src, static_cast<unsigned>(sizeof(src)));

    // B3: offset=ua%30 ∈ [0,29], size=ub%40 ∈ [0,39].
    //     __ikos_assume(offset+size <= 64) cannot narrow each individually
    //     → base + offset + size still appears to exceed the buffer.
    char buf[64] = {};
    b3_sum_bound(buf,
                 ua % 30u,
                 ub % 40u,
                 64u);

    return 0;
}
