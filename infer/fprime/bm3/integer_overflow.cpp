#include <cstdint>
using SizeType = uint64_t;

// Infer는 extern 함수의 반환값을 [0, +oo] 로 모델링
// → src_size 의 상한을 알 수 없음
extern SizeType get_src_size();

// 루프 상한(5)이 있어서 Infer는 반환값을 [0, 5] 로 추론
// 실제 코드: Fw::StringUtils::string_length(DP_EXT, sizeof(DP_EXT))
// sizeof(".fdp") = 5 이므로 동일한 범위
SizeType get_sub_size() {
    SizeType n = 0;
    while (n < 5) n++;
    return n;  // Infer: [0, 5]
}

// 실제 코드: Fw::StringUtils::substring_find (StringUtils.cpp:35)
int find(SizeType src, SizeType sub) {
    // [오탐 원인 1] 가드 조건
    // src >= sub 가 보장되어 src - sub 는 underflow 불가
    // 그러나 Infer는 이 가드를 함수 경계(inter-procedural) 넘어서
    // 루프 조건까지 전파하지 못함
    if (src < sub) return -1;

    // [오탐 발생 지점] src - sub + 1
    // Infer는 src=[0,+oo], sub=[0,5] 로만 보고
    // "src < sub 일 때 이미 return" 이라는 사실을 루프 조건 분석 시 망각
    // → src=0, sub=5 케이스가 여전히 가능하다고 판단
    // → 0 - 5 + 1 = underflow → Integer Overflow L2 경고 발생
    for (SizeType i = 0; i < src - sub + 1; i++) {}

    return 0;
}

int main() {
    return find(get_src_size(), get_sub_size());
}