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
// int -> unsigned
// int - [0, 2,147,483,647] 일 때 safe
// =======================================
void t1(char *buf) {
    int s = __ikos_nondet_int();
    unsigned int u = 100u;

    if (s < u)
        buf[s] = '\0'; // safe
}

int main(void) {
    char buf[100];
    t1(buf);

    return 0;
}