// [BUFFER_OVERRUN false positive]
//
// string_length 루프에서 length < buffer_size(=16) 이므로
// IKOS 는 source[length] 의 접근 범위를 index [0, 15] 로 추론.
// source 는 "INVALID_ADDR"(13바이트) 이므로 index 13~15 접근 가능성 경고.
// 실제로는 source[12] == '\0' 에서 break 하여 index 13~15 는 접근하지 않음 → false positive.

#include <cstddef>

size_t string_length(const char* source, size_t buffer_size) {
    size_t length = 0;
    for (length = 0; length < buffer_size; length++) {
        if (source[length] == '\0') break;  // IKOS: index [0, buffer_size-1] on 13-byte buffer
    }
    return length;
}

int main() {
    const char* source = "INVALID_ADDR";  // 13바이트 (12글자 + null)
    (void)string_length(source, 16);      // buffer_size=16 > 13 → IKOS 오탐
    return 0;
}
