#include <cstdint>
#include <cstdbool>

static const uint32_t TABLE_SIZE = 150;

struct Entry {
    bool used;
    uint32_t opcode;
    uint32_t port;
};

static Entry table[TABLE_SIZE];

int dispatch(uint32_t opcode) {
    uint32_t entry = 0;
    bool entryFound = false;

    // CommandDispatcherImpl.cpp:104 패턴
    // 루프 종료 시 entry = TABLE_SIZE(150) 까지 증가 가능
    // Infer 는 루프 탈출 후 entry 범위를 [0, 150] 으로 추론
    for (entry = 0; entry < TABLE_SIZE; entry++) {
        if (table[entry].used && table[entry].opcode == opcode) {
            entryFound = true;
            break;  // entryFound=true 이면 entry 는 반드시 [0, 149]
        }
    }

    // CommandDispatcherImpl.cpp:110 패턴
    // [오탐 원인] Infer 가 entryFound=true 와 entry<150 의 관계를 전파하지 못함
    // entryFound=true 이면 entry 는 항상 유효 범위이지만
    // Infer 는 entry=[0, 150] 으로 보고 table[150] 접근 가능 → Buffer Overrun L2
    if (entryFound && table[entry].port > 0) {  // Buffer Overrun 예상 지점
        return 1;
    }

    return 0;
}

int main() {
    return dispatch(42);
}