// [UNINITIALIZED_VALUE]
// Infer 가 초기화되지 않은 변수 사용을 탐지하는 예제

int getFlag();
int getMode();  // 실제로는 0, 1, 2 만 반환하지만 Infer 는 알 수 없음

// [PULSE_UNINITIALIZED_VALUE] - Infer 가 조건절 분석에 실패하는 케이스
// 프로그래머 관점: getMode() 가 0/1/2 만 반환 → 모든 분기에서 x 초기화됨
// Infer 관점: getMode() 가 0/1/2 외의 값을 반환할 수 있음
//             → 세 조건 모두 false 인 경로 존재 → x 미초기화 가능
int branch_all_init() {
    int x;
    int mode = getMode();

    if (mode == 0) {
        x = 3;
    } else if (mode == 1) {
        x = 3;
    }

    return x;  // Infer: UNINITIALIZED_VALUE (false positive)
}