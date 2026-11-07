#include <stddef.h>
#include <stdint.h>

extern "C" int                __ikos_nondet_int(void);
extern "C" unsigned int       __ikos_nondet_uint(void);
extern "C" long long          __ikos_nondet_llong(void);
extern "C" unsigned long long __ikos_nondet_ullong(void);
extern "C" short              __ikos_nondet_short(void);
extern "C" unsigned short     __ikos_nondet_ushort(void);
extern "C" size_t             __ikos_nondet_size_t(void);

// ── int → unsigned int ──────────────────────────
void t_i32_u32_1(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i32_u32_2(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && (unsigned int)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (uint)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_u32_3(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int alias = (unsigned int)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}
void t_i32_u32_4(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (uint)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_u32_5(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int u = 100;
    if (s >= 0 && (unsigned int)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (uint)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_u32_6(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int u = 100;
    unsigned int alias = (unsigned int)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}

// ── int → long long ──────────────────────────
void t_i32_i64_1(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i32_i64_2(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && (long long)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i32_i64_3(char *buf) {
    int s = __ikos_nondet_int();
    long long alias = (long long)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_i32_i64_4(char *buf) {
    int s = __ikos_nondet_int();
    long long u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i32_i64_5(char *buf) {
    int s = __ikos_nondet_int();
    long long u = 100;
    if (s >= 0 && (long long)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i32_i64_6(char *buf) {
    int s = __ikos_nondet_int();
    long long u = 100;
    long long alias = (long long)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── int → unsigned long long ──────────────────────────
void t_i32_u64_1(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i32_u64_2(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && (unsigned long long)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_u64_3(char *buf) {
    int s = __ikos_nondet_int();
    unsigned long long alias = (unsigned long long)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_u64_4(char *buf) {
    int s = __ikos_nondet_int();
    unsigned long long u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_u64_5(char *buf) {
    int s = __ikos_nondet_int();
    unsigned long long u = 100;
    if (s >= 0 && (unsigned long long)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_u64_6(char *buf) {
    int s = __ikos_nondet_int();
    unsigned long long u = 100;
    unsigned long long alias = (unsigned long long)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}

// ── int → short ──────────────────────────
void t_i32_i16_1(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i32_i16_2(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && (short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i32_i16_3(char *buf) {
    int s = __ikos_nondet_int();
    short alias = (short)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i32_i16_4(char *buf) {
    int s = __ikos_nondet_int();
    short u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0';
}
void t_i32_i16_5(char *buf) {
    int s = __ikos_nondet_int();
    short u = 100;
    if (s >= 0 && (short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i32_i16_6(char *buf) {
    int s = __ikos_nondet_int();
    short u = 100;
    short alias = (short)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── int → unsigned short ──────────────────────────
void t_i32_u16_1(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i32_u16_2(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && (unsigned short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i32_u16_3(char *buf) {
    int s = __ikos_nondet_int();
    unsigned short alias = (unsigned short)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i32_u16_4(char *buf) {
    int s = __ikos_nondet_int();
    unsigned short u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // safe
        // unsigned short 가 int 로 승격
}
void t_i32_u16_5(char *buf) {
    int s = __ikos_nondet_int();
    unsigned short u = 100;
    if (s >= 0 && (unsigned short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i32_u16_6(char *buf) {
    int s = __ikos_nondet_int();
    unsigned short u = 100;
    unsigned short alias = (unsigned short)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── int → size_t ──────────────────────────
void t_i32_sz_1(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i32_sz_2(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && (size_t)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_sz_3(char *buf) {
    int s = __ikos_nondet_int();
    size_t alias = (size_t)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_sz_4(char *buf) {
    int s = __ikos_nondet_int();
    size_t u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_sz_5(char *buf) {
    int s = __ikos_nondet_int();
    size_t u = 100;
    if (s >= 0 && (size_t)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i32_sz_6(char *buf) {
    int s = __ikos_nondet_int();
    size_t u = 100;
    size_t alias = (size_t)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}

// ── unsigned int → int ──────────────────────────
void t_u32_i32_1(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if (s < 100)
        buf[s] = '\0';
}
void t_u32_i32_2(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if ((int)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^31+50 → (int)s=-2^31+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u32_i32_3(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    int alias = (int)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^31+50 → (int)s=-2^31+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u32_i32_4(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    int u = 100;
    if (s < u)
        buf[s] = '\0'; // safe
        // int 가 unsigned int 로 승격
}
void t_u32_i32_5(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    int u = 100;
    if ((int)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^31+50 → (int)s=-2^31+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u32_i32_6(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    int u = 100;
    int alias = (int)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^31+50 → (int)s=-2^31+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}

// ── unsigned int → long long ──────────────────────────
void t_u32_i64_1(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if (s < 100)
        buf[s] = '\0';
}
void t_u32_i64_2(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if ((long long)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_i64_3(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    long long alias = (long long)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_u32_i64_4(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    long long u = 100;
    if (s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_i64_5(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    long long u = 100;
    if ((long long)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_i64_6(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    long long u = 100;
    long long alias = (long long)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── unsigned int → unsigned long long ──────────────────────────
void t_u32_u64_1(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if (s < 100)
        buf[s] = '\0';
}
void t_u32_u64_2(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if ((unsigned long long)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_u64_3(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    unsigned long long alias = (unsigned long long)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_u32_u64_4(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    unsigned long long u = 100;
    if (s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_u64_5(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    unsigned long long u = 100;
    if ((unsigned long long)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_u64_6(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    unsigned long long u = 100;
    unsigned long long alias = (unsigned long long)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── unsigned int → short ──────────────────────────
void t_u32_i16_1(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if (s < 100)
        buf[s] = '\0';
}
void t_u32_i16_2(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if ((short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u32_i16_3(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    short alias = (short)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u32_i16_4(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    short u = 100;
    if (s < u)
        buf[s] = '\0'; // safe
        // short -> int -> unsigned 로 승격
}
void t_u32_i16_5(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    short u = 100;
    if ((short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u32_i16_6(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    short u = 100;
    short alias = (short)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── unsigned int → unsigned short ──────────────────────────
void t_u32_u16_1(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if (s < 100)
        buf[s] = '\0';
}
void t_u32_u16_2(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if ((unsigned short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u32_u16_3(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    unsigned short alias = (unsigned short)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u32_u16_4(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    unsigned short u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_u32_u16_5(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    unsigned short u = 100;
    if ((unsigned short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u32_u16_6(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    unsigned short u = 100;
    unsigned short alias = (unsigned short)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── unsigned int → size_t ──────────────────────────
void t_u32_sz_1(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if (s < 100)
        buf[s] = '\0';
}
void t_u32_sz_2(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    if ((size_t)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_sz_3(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    size_t alias = (size_t)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_u32_sz_4(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    size_t u = 100;
    if (s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_sz_5(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    size_t u = 100;
    if ((size_t)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u32_sz_6(char *buf) {
    unsigned int s = __ikos_nondet_uint();
    size_t u = 100;
    size_t alias = (size_t)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── long long → int ──────────────────────────
void t_i64_i32_1(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i64_i32_2(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && (int)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_i32_3(char *buf) {
    long long s = __ikos_nondet_llong();
    int alias = (int)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_i32_4(char *buf) {
    long long s = __ikos_nondet_llong();
    int u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0';
}
void t_i64_i32_5(char *buf) {
    long long s = __ikos_nondet_llong();
    int u = 100;
    if (s >= 0 && (int)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_i32_6(char *buf) {
    long long s = __ikos_nondet_llong();
    int u = 100;
    int alias = (int)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── long long → unsigned int ──────────────────────────
void t_i64_u32_1(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i64_u32_2(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && (unsigned int)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_u32_3(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned int alias = (unsigned int)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_u32_4(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned int u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0';
}
void t_i64_u32_5(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned int u = 100;
    if (s >= 0 && (unsigned int)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_u32_6(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned int u = 100;
    unsigned int alias = (unsigned int)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── long long → unsigned long long ──────────────────────────
void t_i64_u64_1(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i64_u64_2(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && (unsigned long long)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i64_u64_3(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned long long alias = (unsigned long long)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}
void t_i64_u64_4(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned long long u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i64_u64_5(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned long long u = 100;
    if (s >= 0 && (unsigned long long)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i64_u64_6(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned long long u = 100;
    unsigned long long alias = (unsigned long long)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}

// ── long long → short ──────────────────────────
void t_i64_i16_1(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i64_i16_2(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && (short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_i16_3(char *buf) {
    long long s = __ikos_nondet_llong();
    short alias = (short)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_i16_4(char *buf) {
    long long s = __ikos_nondet_llong();
    short u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0';
}
void t_i64_i16_5(char *buf) {
    long long s = __ikos_nondet_llong();
    short u = 100;
    if (s >= 0 && (short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_i16_6(char *buf) {
    long long s = __ikos_nondet_llong();
    short u = 100;
    short alias = (short)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── long long → unsigned short ──────────────────────────
void t_i64_u16_1(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i64_u16_2(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && (unsigned short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_u16_3(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned short alias = (unsigned short)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_u16_4(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned short u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0';
}
void t_i64_u16_5(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned short u = 100;
    if (s >= 0 && (unsigned short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_i64_u16_6(char *buf) {
    long long s = __ikos_nondet_llong();
    unsigned short u = 100;
    unsigned short alias = (unsigned short)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── long long → size_t ──────────────────────────
void t_i64_sz_1(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && s < 100)
        buf[s] = '\0';
}
void t_i64_sz_2(char *buf) {
    long long s = __ikos_nondet_llong();
    if (s >= 0 && (size_t)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i64_sz_3(char *buf) {
    long long s = __ikos_nondet_llong();
    size_t alias = (size_t)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}
void t_i64_sz_4(char *buf) {
    long long s = __ikos_nondet_llong();
    size_t u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i64_sz_5(char *buf) {
    long long s = __ikos_nondet_llong();
    size_t u = 100;
    if (s >= 0 && (size_t)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i64_sz_6(char *buf) {
    long long s = __ikos_nondet_llong();
    size_t u = 100;
    size_t alias = (size_t)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}

// ── unsigned long long → int ──────────────────────────
void t_u64_i32_1(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if (s < 100)
        buf[s] = '\0';
}
void t_u64_i32_2(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if ((int)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_i32_3(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    int alias = (int)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_i32_4(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    int u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_u64_i32_5(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    int u = 100;
    if ((int)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_i32_6(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    int u = 100;
    int alias = (int)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── unsigned long long → unsigned int ──────────────────────────
void t_u64_u32_1(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if (s < 100)
        buf[s] = '\0';
}
void t_u64_u32_2(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if ((unsigned int)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_u32_3(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    unsigned int alias = (unsigned int)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_u32_4(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    unsigned int u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_u64_u32_5(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    unsigned int u = 100;
    if ((unsigned int)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_u32_6(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    unsigned int u = 100;
    unsigned int alias = (unsigned int)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── unsigned long long → long long ──────────────────────────
void t_u64_i64_1(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if (s < 100)
        buf[s] = '\0';
}
void t_u64_i64_2(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if ((long long)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^63+50 → (llong)s=-2^63+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u64_i64_3(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    long long alias = (long long)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^63+50 → (llong)s=-2^63+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u64_i64_4(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    long long u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_u64_i64_5(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    long long u = 100;
    if ((long long)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^63+50 → (llong)s=-2^63+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u64_i64_6(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    long long u = 100;
    long long alias = (long long)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^63+50 → (llong)s=-2^63+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}

// ── unsigned long long → short ──────────────────────────
void t_u64_i16_1(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if (s < 100)
        buf[s] = '\0';
}
void t_u64_i16_2(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if ((short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_i16_3(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    short alias = (short)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_i16_4(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    short u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_u64_i16_5(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    short u = 100;
    if ((short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_i16_6(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    short u = 100;
    short alias = (short)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── unsigned long long → unsigned short ──────────────────────────
void t_u64_u16_1(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if (s < 100)
        buf[s] = '\0';
}
void t_u64_u16_2(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if ((unsigned short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_u16_3(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    unsigned short alias = (unsigned short)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_u16_4(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    unsigned short u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_u64_u16_5(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    unsigned short u = 100;
    if ((unsigned short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_u64_u16_6(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    unsigned short u = 100;
    unsigned short alias = (unsigned short)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── unsigned long long → size_t ──────────────────────────
void t_u64_sz_1(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if (s < 100)
        buf[s] = '\0';
}
void t_u64_sz_2(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    if ((size_t)s < 100)
        buf[s] = '\0';
}
void t_u64_sz_3(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    size_t alias = (size_t)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}
void t_u64_sz_4(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    size_t u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_u64_sz_5(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    size_t u = 100;
    if ((size_t)s < u)
        buf[s] = '\0';
}
void t_u64_sz_6(char *buf) {
    unsigned long long s = __ikos_nondet_ullong();
    size_t u = 100;
    size_t alias = (size_t)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}

// ── short → int ──────────────────────────
void t_i16_i32_1(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_i32_2(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && (int)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_i32_3(char *buf) {
    short s = __ikos_nondet_short();
    int alias = (int)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_i16_i32_4(char *buf) {
    short s = __ikos_nondet_short();
    int u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_i32_5(char *buf) {
    short s = __ikos_nondet_short();
    int u = 100;
    if (s >= 0 && (int)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_i32_6(char *buf) {
    short s = __ikos_nondet_short();
    int u = 100;
    int alias = (int)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── short → unsigned int ──────────────────────────
void t_i16_u32_1(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_u32_2(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && (unsigned int)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (uint)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u32_3(char *buf) {
    short s = __ikos_nondet_short();
    unsigned int alias = (unsigned int)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (uint)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u32_4(char *buf) {
    short s = __ikos_nondet_short();
    unsigned int u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (uint)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u32_5(char *buf) {
    short s = __ikos_nondet_short();
    unsigned int u = 100;
    if (s >= 0 && (unsigned int)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (uint)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u32_6(char *buf) {
    short s = __ikos_nondet_short();
    unsigned int u = 100;
    unsigned int alias = (unsigned int)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (uint)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}

// ── short → long long ──────────────────────────
void t_i16_i64_1(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_i64_2(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && (long long)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_i64_3(char *buf) {
    short s = __ikos_nondet_short();
    long long alias = (long long)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_i16_i64_4(char *buf) {
    short s = __ikos_nondet_short();
    long long u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_i64_5(char *buf) {
    short s = __ikos_nondet_short();
    long long u = 100;
    if (s >= 0 && (long long)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_i64_6(char *buf) {
    short s = __ikos_nondet_short();
    long long u = 100;
    long long alias = (long long)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── short → unsigned long long ──────────────────────────
void t_i16_u64_1(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_u64_2(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && (unsigned long long)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u64_3(char *buf) {
    short s = __ikos_nondet_short();
    unsigned long long alias = (unsigned long long)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u64_4(char *buf) {
    short s = __ikos_nondet_short();
    unsigned long long u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u64_5(char *buf) {
    short s = __ikos_nondet_short();
    unsigned long long u = 100;
    if (s >= 0 && (unsigned long long)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u64_6(char *buf) {
    short s = __ikos_nondet_short();
    unsigned long long u = 100;
    unsigned long long alias = (unsigned long long)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (ull)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}

// ── short → unsigned short ──────────────────────────
void t_i16_u16_1(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_u16_2(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && (unsigned short)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (ushort)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u16_3(char *buf) {
    short s = __ikos_nondet_short();
    unsigned short alias = (unsigned short)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_i16_u16_4(char *buf) {
    short s = __ikos_nondet_short();
    unsigned short u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (ushort)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u16_5(char *buf) {
    short s = __ikos_nondet_short();
    unsigned short u = 100;
    if (s >= 0 && (unsigned short)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 (ushort)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_u16_6(char *buf) {
    short s = __ikos_nondet_short();
    unsigned short u = 100;
    unsigned short alias = (unsigned short)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 (ushort)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}

// ── short → size_t ──────────────────────────
void t_i16_sz_1(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_i16_sz_2(char *buf) {
    short s = __ikos_nondet_short();
    if (s >= 0 && (size_t)s < 100)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_sz_3(char *buf) {
    short s = __ikos_nondet_short();
    size_t alias = (size_t)s;
    if (s >= 0 && alias < 100)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_sz_4(char *buf) {
    short s = __ikos_nondet_short();
    size_t u = 100;
    if (s >= 0 && s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_sz_5(char *buf) {
    short s = __ikos_nondet_short();
    size_t u = 100;
    if (s >= 0 && (size_t)s < u)
        buf[s] = '\0'; // warning 오탐 (ikos)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}
void t_i16_sz_6(char *buf) {
    short s = __ikos_nondet_short();
    size_t u = 100;
    size_t alias = (size_t)s;
    if (s >= 0 && alias < u)
        buf[s] = '\0'; // warning 오탐 (ikos, frama-C)
        // s≥0이면 sext 후 (size_t)s=s로 값 동일, 조건이 s<100을 보장하나 IKOS 역전파 실패 → 오탐
}

// ── unsigned short → int ──────────────────────────
void t_u16_i32_1(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if (s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i32_2(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if ((int)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i32_3(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    int alias = (int)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_u16_i32_4(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    int u = 100;
    if (s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i32_5(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    int u = 100;
    if ((int)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i32_6(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    int u = 100;
    int alias = (int)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── unsigned short → unsigned int ──────────────────────────
void t_u16_u32_1(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if (s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_u32_2(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if ((unsigned int)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_u32_3(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    unsigned int alias = (unsigned int)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_u16_u32_4(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    unsigned int u = 100;
    if (s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_u32_5(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    unsigned int u = 100;
    if ((unsigned int)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_u32_6(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    unsigned int u = 100;
    unsigned int alias = (unsigned int)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── unsigned short → long long ──────────────────────────
void t_u16_i64_1(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if (s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i64_2(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if ((long long)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i64_3(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    long long alias = (long long)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_u16_i64_4(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    long long u = 100;
    if (s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i64_5(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    long long u = 100;
    if ((long long)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i64_6(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    long long u = 100;
    long long alias = (long long)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── unsigned short → unsigned long long ──────────────────────────
void t_u16_u64_1(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if (s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_u64_2(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if ((unsigned long long)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_u64_3(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    unsigned long long alias = (unsigned long long)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_u16_u64_4(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    unsigned long long u = 100;
    if (s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_u64_5(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    unsigned long long u = 100;
    if ((unsigned long long)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_u64_6(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    unsigned long long u = 100;
    unsigned long long alias = (unsigned long long)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── unsigned short → short ──────────────────────────
void t_u16_i16_1(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if (s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_i16_2(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if ((short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^15+50 → (short)s=-2^15+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u16_i16_3(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    short alias = (short)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^15+50 → (short)s=-2^15+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u16_i16_4(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    short u = 100;
    if (s < u)
        buf[s] = '\0'; // warning 진탐 (GPT 피셜 오탐)
        // s=2^15+50 → (short)s=-2^15+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u16_i16_5(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    short u = 100;
    if ((short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^15+50 → (short)s=-2^15+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_u16_i16_6(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    short u = 100;
    short alias = (short)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^15+50 → (short)s=-2^15+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}

// ── unsigned short → size_t ──────────────────────────
void t_u16_sz_1(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if (s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_sz_2(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    if ((size_t)s < 100)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_sz_3(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    size_t alias = (size_t)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}
void t_u16_sz_4(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    size_t u = 100;
    if (s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_sz_5(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    size_t u = 100;
    if ((size_t)s < u)
        buf[s] = '\0'; // SimplifyUpcastComparisonPass
}
void t_u16_sz_6(char *buf) {
    unsigned short s = __ikos_nondet_ushort();
    size_t u = 100;
    size_t alias = (size_t)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C) // SimplifyUpcastComparisonPass
}

// ── size_t → int ──────────────────────────
void t_sz_i32_1(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if (s < 100)
        buf[s] = '\0';
}
void t_sz_i32_2(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if ((int)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_i32_3(char *buf) {
    size_t s = __ikos_nondet_size_t();
    int alias = (int)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_i32_4(char *buf) {
    size_t s = __ikos_nondet_size_t();
    int u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_sz_i32_5(char *buf) {
    size_t s = __ikos_nondet_size_t();
    int u = 100;
    if ((int)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_i32_6(char *buf) {
    size_t s = __ikos_nondet_size_t();
    int u = 100;
    int alias = (int)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (int)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── size_t → unsigned int ──────────────────────────
void t_sz_u32_1(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if (s < 100)
        buf[s] = '\0';
}
void t_sz_u32_2(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if ((unsigned int)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_u32_3(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned int alias = (unsigned int)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_u32_4(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned int u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_sz_u32_5(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned int u = 100;
    if ((unsigned int)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_u32_6(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned int u = 100;
    unsigned int alias = (unsigned int)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^32+50 → (uint)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── size_t → long long ──────────────────────────
void t_sz_i64_1(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if (s < 100)
        buf[s] = '\0';
}
void t_sz_i64_2(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if ((long long)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^63+50 → (llong)s=-2^63+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_sz_i64_3(char *buf) {
    size_t s = __ikos_nondet_size_t();
    long long alias = (long long)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^63+50 → (llong)s=-2^63+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_sz_i64_4(char *buf) {
    size_t s = __ikos_nondet_size_t();
    long long u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_sz_i64_5(char *buf) {
    size_t s = __ikos_nondet_size_t();
    long long u = 100;
    if ((long long)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^63+50 → (llong)s=-2^63+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}
void t_sz_i64_6(char *buf) {
    size_t s = __ikos_nondet_size_t();
    long long u = 100;
    long long alias = (long long)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^63+50 → (llong)s=-2^63+50 < 100, 부호 비트 반전으로 조건 통과 → 실제 OOB
}

// ── size_t → unsigned long long ──────────────────────────
void t_sz_u64_1(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if (s < 100)
        buf[s] = '\0';
}
void t_sz_u64_2(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if ((unsigned long long)s < 100)
        buf[s] = '\0';
}
void t_sz_u64_3(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned long long alias = (unsigned long long)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}
void t_sz_u64_4(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned long long u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_sz_u64_5(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned long long u = 100;
    if ((unsigned long long)s < u)
        buf[s] = '\0';
}
void t_sz_u64_6(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned long long u = 100;
    unsigned long long alias = (unsigned long long)s;
    if (alias < u)
        buf[s] = '\0'; // warning 오탐 (frama-C)
}

// ── size_t → short ──────────────────────────
void t_sz_i16_1(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if (s < 100)
        buf[s] = '\0';
}
void t_sz_i16_2(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if ((short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_i16_3(char *buf) {
    size_t s = __ikos_nondet_size_t();
    short alias = (short)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_i16_4(char *buf) {
    size_t s = __ikos_nondet_size_t();
    short u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_sz_i16_5(char *buf) {
    size_t s = __ikos_nondet_size_t();
    short u = 100;
    if ((short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_i16_6(char *buf) {
    size_t s = __ikos_nondet_size_t();
    short u = 100;
    short alias = (short)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (short)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

// ── size_t → unsigned short ──────────────────────────
void t_sz_u16_1(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if (s < 100)
        buf[s] = '\0';
}
void t_sz_u16_2(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if ((unsigned short)s < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_u16_3(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned short alias = (unsigned short)s;
    if (alias < 100)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_u16_4(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned short u = 100;
    if (s < u)
        buf[s] = '\0';
}
void t_sz_u16_5(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned short u = 100;
    if ((unsigned short)s < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}
void t_sz_u16_6(char *buf) {
    size_t s = __ikos_nondet_size_t();
    unsigned short u = 100;
    unsigned short alias = (unsigned short)s;
    if (alias < u)
        buf[s] = '\0'; // warning 진탐 (ikos, frama-C)
        // s=2^16+50 → (ushort)s=50 < 100, 상위 비트 무시로 조건 통과 → 실제 OOB
}

int main(void) {
    char buf[100];
    t_i32_u32_1(buf);
    t_i32_u32_2(buf);
    t_i32_u32_3(buf);
    t_i32_u32_4(buf);
    t_i32_u32_5(buf);
    t_i32_u32_6(buf);
    t_i32_i64_1(buf);
    t_i32_i64_2(buf);
    t_i32_i64_3(buf);
    t_i32_i64_4(buf);
    t_i32_i64_5(buf);
    t_i32_i64_6(buf);
    t_i32_u64_1(buf);
    t_i32_u64_2(buf);
    t_i32_u64_3(buf);
    t_i32_u64_4(buf);
    t_i32_u64_5(buf);
    t_i32_u64_6(buf);
    t_i32_i16_1(buf);
    t_i32_i16_2(buf);
    t_i32_i16_3(buf);
    t_i32_i16_4(buf);
    t_i32_i16_5(buf);
    t_i32_i16_6(buf);
    t_i32_u16_1(buf);
    t_i32_u16_2(buf);
    t_i32_u16_3(buf);
    t_i32_u16_4(buf);
    t_i32_u16_5(buf);
    t_i32_u16_6(buf);
    t_i32_sz_1(buf);
    t_i32_sz_2(buf);
    t_i32_sz_3(buf);
    t_i32_sz_4(buf);
    t_i32_sz_5(buf);
    t_i32_sz_6(buf);
    t_u32_i32_1(buf);
    t_u32_i32_2(buf);
    t_u32_i32_3(buf);
    t_u32_i32_4(buf);
    t_u32_i32_5(buf);
    t_u32_i32_6(buf);
    t_u32_i64_1(buf);
    t_u32_i64_2(buf);
    t_u32_i64_3(buf);
    t_u32_i64_4(buf);
    t_u32_i64_5(buf);
    t_u32_i64_6(buf);
    t_u32_u64_1(buf);
    t_u32_u64_2(buf);
    t_u32_u64_3(buf);
    t_u32_u64_4(buf);
    t_u32_u64_5(buf);
    t_u32_u64_6(buf);
    t_u32_i16_1(buf);
    t_u32_i16_2(buf);
    t_u32_i16_3(buf);
    t_u32_i16_4(buf);
    t_u32_i16_5(buf);
    t_u32_i16_6(buf);
    t_u32_u16_1(buf);
    t_u32_u16_2(buf);
    t_u32_u16_3(buf);
    t_u32_u16_4(buf);
    t_u32_u16_5(buf);
    t_u32_u16_6(buf);
    t_u32_sz_1(buf);
    t_u32_sz_2(buf);
    t_u32_sz_3(buf);
    t_u32_sz_4(buf);
    t_u32_sz_5(buf);
    t_u32_sz_6(buf);
    t_i64_i32_1(buf);
    t_i64_i32_2(buf);
    t_i64_i32_3(buf);
    t_i64_i32_4(buf);
    t_i64_i32_5(buf);
    t_i64_i32_6(buf);
    t_i64_u32_1(buf);
    t_i64_u32_2(buf);
    t_i64_u32_3(buf);
    t_i64_u32_4(buf);
    t_i64_u32_5(buf);
    t_i64_u32_6(buf);
    t_i64_u64_1(buf);
    t_i64_u64_2(buf);
    t_i64_u64_3(buf);
    t_i64_u64_4(buf);
    t_i64_u64_5(buf);
    t_i64_u64_6(buf);
    t_i64_i16_1(buf);
    t_i64_i16_2(buf);
    t_i64_i16_3(buf);
    t_i64_i16_4(buf);
    t_i64_i16_5(buf);
    t_i64_i16_6(buf);
    t_i64_u16_1(buf);
    t_i64_u16_2(buf);
    t_i64_u16_3(buf);
    t_i64_u16_4(buf);
    t_i64_u16_5(buf);
    t_i64_u16_6(buf);
    t_i64_sz_1(buf);
    t_i64_sz_2(buf);
    t_i64_sz_3(buf);
    t_i64_sz_4(buf);
    t_i64_sz_5(buf);
    t_i64_sz_6(buf);
    t_u64_i32_1(buf);
    t_u64_i32_2(buf);
    t_u64_i32_3(buf);
    t_u64_i32_4(buf);
    t_u64_i32_5(buf);
    t_u64_i32_6(buf);
    t_u64_u32_1(buf);
    t_u64_u32_2(buf);
    t_u64_u32_3(buf);
    t_u64_u32_4(buf);
    t_u64_u32_5(buf);
    t_u64_u32_6(buf);
    t_u64_i64_1(buf);
    t_u64_i64_2(buf);
    t_u64_i64_3(buf);
    t_u64_i64_4(buf);
    t_u64_i64_5(buf);
    t_u64_i64_6(buf);
    t_u64_i16_1(buf);
    t_u64_i16_2(buf);
    t_u64_i16_3(buf);
    t_u64_i16_4(buf);
    t_u64_i16_5(buf);
    t_u64_i16_6(buf);
    t_u64_u16_1(buf);
    t_u64_u16_2(buf);
    t_u64_u16_3(buf);
    t_u64_u16_4(buf);
    t_u64_u16_5(buf);
    t_u64_u16_6(buf);
    t_u64_sz_1(buf);
    t_u64_sz_2(buf);
    t_u64_sz_3(buf);
    t_u64_sz_4(buf);
    t_u64_sz_5(buf);
    t_u64_sz_6(buf);
    t_i16_i32_1(buf);
    t_i16_i32_2(buf);
    t_i16_i32_3(buf);
    t_i16_i32_4(buf);
    t_i16_i32_5(buf);
    t_i16_i32_6(buf);
    t_i16_u32_1(buf);
    t_i16_u32_2(buf);
    t_i16_u32_3(buf);
    t_i16_u32_4(buf);
    t_i16_u32_5(buf);
    t_i16_u32_6(buf);
    t_i16_i64_1(buf);
    t_i16_i64_2(buf);
    t_i16_i64_3(buf);
    t_i16_i64_4(buf);
    t_i16_i64_5(buf);
    t_i16_i64_6(buf);
    t_i16_u64_1(buf);
    t_i16_u64_2(buf);
    t_i16_u64_3(buf);
    t_i16_u64_4(buf);
    t_i16_u64_5(buf);
    t_i16_u64_6(buf);
    t_i16_u16_1(buf);
    t_i16_u16_2(buf);
    t_i16_u16_3(buf);
    t_i16_u16_4(buf);
    t_i16_u16_5(buf);
    t_i16_u16_6(buf);
    t_i16_sz_1(buf);
    t_i16_sz_2(buf);
    t_i16_sz_3(buf);
    t_i16_sz_4(buf);
    t_i16_sz_5(buf);
    t_i16_sz_6(buf);
    t_u16_i32_1(buf);
    t_u16_i32_2(buf);
    t_u16_i32_3(buf);
    t_u16_i32_4(buf);
    t_u16_i32_5(buf);
    t_u16_i32_6(buf);
    t_u16_u32_1(buf);
    t_u16_u32_2(buf);
    t_u16_u32_3(buf);
    t_u16_u32_4(buf);
    t_u16_u32_5(buf);
    t_u16_u32_6(buf);
    t_u16_i64_1(buf);
    t_u16_i64_2(buf);
    t_u16_i64_3(buf);
    t_u16_i64_4(buf);
    t_u16_i64_5(buf);
    t_u16_i64_6(buf);
    t_u16_u64_1(buf);
    t_u16_u64_2(buf);
    t_u16_u64_3(buf);
    t_u16_u64_4(buf);
    t_u16_u64_5(buf);
    t_u16_u64_6(buf);
    t_u16_i16_1(buf);
    t_u16_i16_2(buf);
    t_u16_i16_3(buf);
    t_u16_i16_4(buf);
    t_u16_i16_5(buf);
    t_u16_i16_6(buf);
    t_u16_sz_1(buf);
    t_u16_sz_2(buf);
    t_u16_sz_3(buf);
    t_u16_sz_4(buf);
    t_u16_sz_5(buf);
    t_u16_sz_6(buf);
    t_sz_i32_1(buf);
    t_sz_i32_2(buf);
    t_sz_i32_3(buf);
    t_sz_i32_4(buf);
    t_sz_i32_5(buf);
    t_sz_i32_6(buf);
    t_sz_u32_1(buf);
    t_sz_u32_2(buf);
    t_sz_u32_3(buf);
    t_sz_u32_4(buf);
    t_sz_u32_5(buf);
    t_sz_u32_6(buf);
    t_sz_i64_1(buf);
    t_sz_i64_2(buf);
    t_sz_i64_3(buf);
    t_sz_i64_4(buf);
    t_sz_i64_5(buf);
    t_sz_i64_6(buf);
    t_sz_u64_1(buf);
    t_sz_u64_2(buf);
    t_sz_u64_3(buf);
    t_sz_u64_4(buf);
    t_sz_u64_5(buf);
    t_sz_u64_6(buf);
    t_sz_i16_1(buf);
    t_sz_i16_2(buf);
    t_sz_i16_3(buf);
    t_sz_i16_4(buf);
    t_sz_i16_5(buf);
    t_sz_i16_6(buf);
    t_sz_u16_1(buf);
    t_sz_u16_2(buf);
    t_sz_u16_3(buf);
    t_sz_u16_4(buf);
    t_sz_u16_5(buf);
    t_sz_u16_6(buf);
    return 0;
}

