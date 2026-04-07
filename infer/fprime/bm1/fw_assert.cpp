#include "../../../bm1/fw_assert.hpp"

unsigned int getIndex();
int* getBuffer();
int getVal();

// [BUFFER_OVERRUN_L2]
void processBuffer() {
    int arr[10];
    unsigned int idx = getIndex() % 20;  // InferBO가 범위를 [-19, 19]로 계산
    FW_ASSERT(idx < 10);                 // [[noreturn]] 없음 → Infer가 이후 경로를 제거하지 않음
    arr[idx] = 42;                       // idx 범위 [-19, 19], arr 크기 10 → BUFFER_OVERRUN_L2
}

// [NULL_DEREFERENCE]
void processPointer() {
    int* ptr = getBuffer();              // 외부 함수 → null 가능성 있음
    FW_ASSERT(ptr != nullptr);          // [[noreturn]] 없음 → null 경로가 제거되지 않음
    *ptr = 42;                           // Infer: ptr 이 null 일 수 있음 → NULL_DEREFERENCE
}

// [INTEGER_OVERFLOW_L2]
void processAdd() {
    int a = getVal() % 20;               // InferBO가 범위를 [-19, 19]로 계산
    FW_ASSERT(a < 10);                   // [[noreturn]] 없음 → Infer가 이후 경로를 제거하지 않음
    int b = a + 2147483640;              // a 범위 [-19,19], 최대 2147483659 > INT_MAX → INTEGER_OVERFLOW_L2
    (void)b;
}

// [USE_AFTER_DELETE]
void processDelete() {
    int* ptr = new int(42);
    delete ptr;                          // ptr 해제, 하지만 ptr 값은 여전히 non-null
    FW_ASSERT(ptr != nullptr);          // 항상 통과 → 체크 의미 없음
    *ptr = 99;                           // dangling pointer 접근 → USE_AFTER_DELETE
}

// [DEAD_STORE]
void processDeadStore() {
    int x = 5;                           // 초기값 할당 (사용 전에 덮어써짐) → DEAD_STORE
    x = getVal();                        // x = 5 를 읽지 않고 덮어씀
    FW_ASSERT(x >= 0);
    (void)x;
}