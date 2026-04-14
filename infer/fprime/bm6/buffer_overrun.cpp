#include <cstring>

int main() {
    const char* src = "INVALID_ADDR";  // 13바이트, 'A'는 index 3
    for (size_t i = 0 ; i < 16 ; i++) {
        if (src[i] != 'A') break;
    }
}