#include <cstdlib>

// Case 1: intra-procedural
void test_intra(void) {
    int* ptr = nullptr;
    if (ptr == nullptr) abort();
    *ptr = 42;
}

// Case 2: inter-procedural
void guard_check(bool cond) {
    if (!cond) abort();
}

void test_inter(void) {
    int* ptr = nullptr;
    guard_check(ptr != nullptr);
    *ptr = 42;
}

// main
int main() {
    test_intra();
    test_inter();
    return 0;
}