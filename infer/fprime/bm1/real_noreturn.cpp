  // real_noreturn.cpp

#include <cstdlib>

[[noreturn]] void real_abort() { abort(); }

#define REAL_ASSERT(cond) \
do { if (!(cond)) real_abort(); } while(0)

struct Buffer {
    unsigned int m_serLoc;
    unsigned int m_deserLoc;
};

unsigned int get_size_left_safe(Buffer* b) {
    REAL_ASSERT(b->m_serLoc >= b->m_deserLoc);  // guard
    return b->m_serLoc - b->m_deserLoc;          // Infer가 여기서 안전하다고 인식 예상
}