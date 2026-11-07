#include <stddef.h>

/* simulates fmt_format: extern, body unknown to ikos */
extern int get_result(char *buf, size_t size);

/*
 * A. original pattern — (size_t) cast, size is a parameter (variable)
 *   case_a(buf, 100);
 */
void case_a(char *buf, size_t size) {
    int result = get_result(buf, size);
    if (result >= 0 && (size_t)result < size)
        /*
         * (size_t) result = result mod 2^64
         * 양수: 값이 그대로 유지
         *   result = 5 -> 5 mod 2^64 = 5
         * 음수: 2^64 를 더하는 것과 동일
         *   result = -5 -> -5 + 2^64 = 1844....
         */

        // result = [0, 100]
        buf[result] = '\0';  // warning: possible buffer overflow, accessing index between 0 and 2147483647 of local variable 'buf' of 100 elements

    /*
     %3 = alloca i8*   → char* ptr
     %4 = alloca i64   → size_t len
     %5 = alloca i32   → int result

     %8 = call get_result(ptr, len)   → result = get_result(ptr, len)
     %10 = icmp sge %9, 0             → result >= 0

     %13 = sext i32 → i64             → (int64_t)result
     %15 = icmp ult %13, %14          → (size_t)result < len

     %20 = getelementptr ptr[result]  → ptr[result]
     store i8 0                       → ptr[result] = '\0'
     */
}

/*
 * B. no cast — both sides are int
 *   case_b(buf, 100);
 */
void case_b(char *buf, int size) {
    int result = get_result(buf, (size_t)size);
    if (result >= 0 && result < size)
        buf[result] = '\0';  // safe
}

/*
 * C. (size_t) cast present, but size is a constant (100)
 *   case_c(buf);
 */
void case_c(char *buf) {
    size_t size = 100;
    int result = get_result(buf, size);
    if (result >= 0 && (size_t)result < size)
        buf[result] = '\0';  // warning: possible buffer overflow, accessing index between 0 and 2147483647 of local variable 'buf' of 100 elements
}

/*
 * D. no cast, size is a constant
 *   case_d(buf);
 */
void case_d(char *buf) {
    int result = get_result(buf, 100);
    if (result >= 0 && result < 100)
        buf[result] = '\0';  // safe
}

int main(void) {
    char buf[100];
    case_a(buf, 100);
    case_b(buf, 100);
    case_c(buf);
    case_d(buf);
    return 0;
}