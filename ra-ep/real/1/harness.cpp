#include "benchmark.h"

int main(int argc, char** argv) {
    (void)argv;

    const unsigned ua = static_cast<unsigned>(argc);
    const unsigned ub = ua % 7u;

    // ── GROUP A ──────────────────────────────────────────────────────────────

    // A1: b=5 (상수) → FW_ASSERT(a >= 5) → a ∈ [5,∞] → SAFE
    (void)a1_ordered_sub(ua, 5u);

    // A2: t ∈ {0,1,2} → FW_ASSERT(t == 0) → t = 0 → SAFE
    (void)a2_enum_equality(static_cast<Tag>(ua % 3u), 1, 2);

    // A3: x ∈ [0,∞] → FW_ASSERT(x < 1000000) → x ∈ [0,999999] → SAFE
    (void)a3_range_arith(ua);

    // ── GROUP B ──────────────────────────────────────────────────────────────

    // B1: 두 변수의 관계를 interval이 보존하지 못함 → WARNING
    (void)b1_relational_sub(ua, ub);

    // B2: a >= 5이지만 a - 6은 a=5에서 underflow → WARNING
    (void)b2_boundary_underflow(ua);

    return 0;
}
