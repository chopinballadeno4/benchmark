#include <cstdlib>

extern "C" unsigned __ikos_nondet_uint(void);

// opaque: 정의를 IKOS 가 볼 수 없어 bool 인자로 d 를 좁히지 못함
extern "C" void guard_check(int cond);

/*
 * result: warning
 * guard_check 가 opaque 하여 d != 0 이 보장되지 않음
 */
unsigned test_guard_call(void) {
    unsigned d = __ikos_nondet_uint();
    guard_check(d != 0u);
    return 100u / d;
}

/*
 * result: safe
 * if (d == 0) abort() 인라인 → d ∈ [1, UINT_MAX]
 */
unsigned test_guard_inline_safe(void) {
    unsigned d = __ikos_nondet_uint();
    if (d == 0u) abort();
    return 100u / d;
}

/*
 * result: warning
 * a > 0 이므로 a ∈ [1, UINT_MAX] 이지만 나누는 값은 a - 1 ∈ [0, UINT_MAX-1]
 * a == 1 일 때 a - 1 == 0 이므로 division by zero 가능
 */
unsigned test_off_by_one(void) {
    unsigned a = __ikos_nondet_uint();
    if (a == 0u) abort();
    return 100u / (a - 1u);
}

/*
 * result: warning
 * 조건은 확인하지만 abort 를 호출하지 않아 IKOS 가 d 를 좁히지 못함
 */
unsigned test_weak_guard(void) {
    unsigned d = __ikos_nondet_uint();
    if (d == 0u) { (void)d; }
    return 100u / d;
}

int main(void) {
    volatile unsigned sink = 0u;
    sink += test_guard_call();
    sink += test_guard_inline_safe();
    sink += test_off_by_one();
    sink += test_weak_guard();
    return (int)sink;
}
