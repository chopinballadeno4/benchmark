#include <cstdlib>

extern int* getBuffer();

// Case 1: intra-procedural
// abort() 가 같은 함수 안에 있어 IKOS 가 forward 로 직접 전파 가능.
// if (ptr == nullptr) 분기 이후 ptr 이 non-null 임을 전파할 수 있음.
void test_direct(void) {
    int* ptr = getBuffer();
    if (ptr == nullptr) abort();
    *ptr = 42;
}

// Case 2: inter-procedural
// 동일한 로직이지만 guard_check() 함수 경계 너머에 있음.
// IKOS 는 guard_check() 가 반환됐다는 사실을 호출자 문맥에 반영하지 못함.
void guard_check(bool cond) {
    if (!cond) abort();
}

void test_guard(void) {
    int* ptr = getBuffer();
    guard_check(ptr != nullptr);
    *ptr = 42;
}

int main() {
    test_guard();
    //test_direct();
    return 0;
}
