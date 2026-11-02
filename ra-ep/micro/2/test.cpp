/* microbenchmark: where does ikos lose range information?
*
 * pattern from fmt_vformat_cstr:
 *   extern int get_result(...);  // unknown return, like fmt_format
 *   if (result >= 0 && (size_t)result < size)
 *       buf[result] = '\0';
 *
 * variants to isolate the cause:
 *   A. original pattern  (size_t cast + size is variable)
 *   B. no cast           (pure int comparison)
 *   C. size is constant  (no variable, cast still present)
 *   D. no cast + constant
 */

#include <stddef.h>

/* simulates fmt_format: extern, body unknown to ikos */
extern int get_result(char *buf, size_t size);

/* A. original pattern — (size_t) cast, size is a parameter (variable) */
void case_a(char *buf, size_t size) {
    int result = get_result(buf, size);
    if (result >= 0 && (size_t)result < size)
        buf[result] = '\0';  /* ikos-orig: warning? */
}

/* B. no cast — both sides are int */
void case_b(char *buf, int size) {
    int result = get_result(buf, (size_t)size);
    if (result >= 0 && result < size)
        buf[result] = '\0';  /* ikos-orig: warning? */
}

/* C. (size_t) cast present, but size is a constant (100) */
void case_c(char *buf) {
    size_t size = 100;
    int result = get_result(buf, size);
    if (result >= 0 && (size_t)result < size)
        buf[result] = '\0';  /* ikos-orig: warning? */
}

/* D. no cast, size is a constant */
void case_d(char *buf) {
    int result = get_result(buf, 100);
    if (result >= 0 && result < 100)
        buf[result] = '\0';  /* ikos-orig: warning? */
}

int main(void) {
    char buf[100];
    case_a(buf, 100);
    case_b(buf, 100);
    case_c(buf);
    case_d(buf);
    return 0;
}