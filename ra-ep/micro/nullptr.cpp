#include <cstdlib>

extern int* getBuffer1();

int* getBuffer2() {
    return nullptr;
}

void guard_check(bool cond) {
    if (!cond) abort();
}

void test_guard(void) {
    int* ptr = getBuffer1();
    guard_check(ptr != nullptr);
    *ptr = 42;
}

int main() {
    test_guard();
    return 0;
}