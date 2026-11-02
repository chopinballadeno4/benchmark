#include <cstdint>

extern int get_id();
extern std::uint64_t get_descriptor();

static std::uint64_t unpack_type(std::uint64_t descriptor, int index) {
    int shift = index * 4;  // signed overflow / underflow 검사
    return (descriptor >> shift) & 15u;  // shift-count 검사
}

static std::uint64_t get_type(std::uint64_t descriptor, int id) {
    if (unsigned(id) >= 15u) {
        return 0;
    }

    // unsigned(id) < 15이므로 실제 signed id도 [0,14].
    return unpack_type(descriptor, id);
}

int main() {
    return static_cast<int>(get_type(get_descriptor(), get_id()));
}