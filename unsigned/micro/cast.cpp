#include <stddef.h>
#include <stdint.h>

extern "C" int                __ikos_nondet_int(void);
extern "C" unsigned           __ikos_nondet_uint(void);
extern "C" long long          __ikos_nondet_llong(void);
extern "C" unsigned long long __ikos_nondet_ullong(void);
extern "C" short              __ikos_nondet_short(void);
extern "C" unsigned short     __ikos_nondet_ushort(void);
extern "C" size_t             __ikos_nondet_size_t(void);

// =======================================
// int - unsigned int
// int - [0, 2,147,483,647] 일 때 safe
// =======================================
void t1_1(char *buf) {
    int s = __ikos_nondet_int();
    if (s < 100u)
        buf[s] = '\0'; //
}

void t1_2(char *buf) {
    int s = __ikos_nondet_int();
    if (unsigned(s) < 100u)
        buf[s] = '\0'; //
}

void t1_3(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int su = signed(s);
    if (su < 100u)
        buf[s] = '\0'; //
}

void t1_4(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int u = 100u;
    if (s < u)
        buf[s] = '\0'; //
}

void t1_5(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int u = 100u;
    if (unsigned(s) < u)
        buf[s] = '\0'; //
}

void t1_6(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int u = 100u;
    unsigned int su = signed(s);
    if (su < u)
        buf[s] = '\0'; //
}

// =======================================
// unsigned -> int
// unsigned - [0, 2,147,483,647] 일 때 safe
// =======================================
void t3(char *buf) {
    unsigned int s = __ikos_nondet_int();
    int u = (int)s;
    if (u < 100)
        buf[s] = '\0'; // warning: possible buffer overflow // ikos-dev 도 warning.
}

void t4(char *buf) {
    unsigned int s = __ikos_nondet_int();
    if ((int)s < 100)
        buf[s] = '\0'; // warning: possible buffer overflow // ikos-dev 도 warning.
}

// =======================================
// int -> size_t
// int - [0, 2,147,483,647] 일 때 safe
// =======================================
void t5(char *buf) {
    int s = __ikos_nondet_int();
    size_t u = (size_t)s;
    if (u < 100)
        // 음수는 (size_t) 변환 후 100 초과 → 조건 불통과
        // → s ∈ [0, 99] 보장 → 실제 안전 (오탐)
        buf[s] = '\0'; // warning: possible buffer overflow
}

void t6(char *buf) {
    int s = __ikos_nondet_int();
    if (s >= 0 && (size_t)s < 100)
        // 음수는 (size_t) 변환 후 100 초과 → 조건 불통과
        // → s ∈ [0, 99] 보장 → 실제 안전 (오탐)
        buf[s] = '\0'; // warning: possible buffer overflow
}

// =======================================
// size_t -> int
// size_t - [0, 2,147,483,647] 일 때 safe
// =======================================
void t7(char *buf) {
    size_t s = __ikos_nondet_size_t();
    if ((int)s >= 0 && (int)s < 100)
        // → buf[2^32+50] 실제 오버플로우 (진탐)
        buf[s] = '\0'; // warning: possible buffer overflow
}

void t8(char *buf) {
    size_t s = __ikos_nondet_size_t();
    int i = (int)s;
    if (i >= 0 && i < 100)
        // → buf[2^32+50] 실제 오버플로우 (진탐)
        buf[s] = '\0'; // warning: possible buffer overflow
}

int main(void) {
    char buf[100];
    t1(buf);
    t2(buf);
    t2_2(buf);
    t3(buf);
    t4(buf);
    t5(buf);
    t6(buf);
    t7(buf);
    t8(buf);

    return 0;
}