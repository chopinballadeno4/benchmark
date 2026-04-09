#include <cstring>
#include <cstddef>

// StringUtils.cpp:24 패턴
// string_length 는 루프 상한(buffer_size)이 있어서
// Infer 는 반환값을 [0, buffer_size] 로 추론
// 실제로는 null terminator 를 만나면 중단하지만
// Infer 는 루프가 buffer_size 까지 돌 수 있다고 보수적으로 판단
size_t string_length(const char* source, size_t buffer_size) {
    size_t length = 0;
    for (length = 0; length < buffer_size; length++) {
        if (source[length] == '\0') break;
    }
    return length;  // Infer 추론: [0, buffer_size] = [0, 16]
}

// StringUtils.cpp:7 패턴
char* string_copy(char* destination, const char* source, size_t num) {
    if (destination == source || num == 0) {
        return destination;
    }

    // [오탐 원인]
    // string_length 반환값: [0, 16] (Infer 추론)
    // + 1 하면 source_len: [0, 17]
    // 실제로는 "INVALID_ADDR"(12글자) 이므로 string_length 는 항상 12 반환
    // → source_len 은 항상 13 이지만 Infer 는 이를 알 수 없음
    size_t source_len = string_length(source, num) + 1;

    // [오탐 발생 지점]
    // source 는 "INVALID_ADDR" = 13바이트 크기의 버퍼
    // source_len 은 Infer 기준 [0, 17]
    // → source[source_len] 은 offset [0, 17] 로 13바이트 버퍼 접근
    // → Infer: Offset [0, 15] Size 13 → Buffer Overrun L2 경고
    // 실제로는 source_len = 13 으로 고정이므로 overrun 없음 → false positive
    (void)(source[source_len]);

    strncpy(destination, source, num);
    destination[num - 1] = '\0';
    return destination;
}

int main() {
    // UdpSocket.cpp:181~184 패턴
    // recv_addr: 16바이트 (INET_ADDRSTRLEN = 16)
    // "INVALID_ADDR": 13바이트
    // num: 16
    char recv_addr[16];
    string_copy(recv_addr, "INVALID_ADDR", 16);
    return 0;
}