#include <cstdint>

extern int get_id();
extern std::uint64_t get_descriptor();

static std::uint64_t unpack_type(std::uint64_t descriptor, int index) {
    int shift = index * 4;  // possible signed integer overflow / underflow 검사
    return (descriptor >> shift) & 15u;  // shift count might be invalid / shift-count 검사
    /*
     * a >> b 에서 b 는 반드시 0 ≤ b < 비트 수
     */
}

static std::uint64_t get_type(std::uint64_t descriptor, int id) {
    if (unsinged(id) >= 15u) {
        return 0;
    }
ㅈ
    // unsigned(id) < 15 이므로 실제 signed id도 [0,14].
    return unpack_type(descriptor, id);
}

int main() {
    return static_cast<int>(get_type(get_descriptor(), get_id()));
}