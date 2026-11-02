#include <cstdlib>

extern int* getBuffer1();

int* getBuffer2() {
    return nullptr;
}

void guard_check(bool cond) {
    if (!cond) abort();
}

void test_guard_call(void) {
    int* ptr = getBuffer1();
    guard_check(ptr != nullptr);
    *ptr = 42;
}

/*
 * result: safe
 */
void test_guard_inline1(void) {
    int* ptr = getBuffer1();
    if (ptr == nullptr) abort();
    *ptr = 42;
}

/*
 * result: warning
 */
void test_guard_inline2(void) {
    int* ptr = getBuffer1();
    if (ptr == nullptr) true;
    *ptr = 42;
}

int main() {
    test_guard_call();
    return 0;
}