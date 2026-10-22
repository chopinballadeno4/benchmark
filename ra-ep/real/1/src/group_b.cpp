#include "benchmark.h"

// GROUP B — IKOS reports a warning after FW_ASSERT

// B1: Relational unsigned subtraction
//   Models: Buffer::advance() — FW_ASSERT(amount <= m_size) → m_size -= amount
unsigned b1_relational_sub(unsigned amount, unsigned m_size) {
    FW_ASSERT(amount <= m_size);
    return m_size - amount;
}

// B2: Insufficient lower bound
//   FW_ASSERT(a >= 5) permits a == 5, so a - 6 can underflow.
unsigned b2_boundary_underflow(unsigned a) {
    FW_ASSERT(a >= 5u);
    return a - 6u;
}

// B3: Pointer nullity after FW_ASSERT
//   Models: FW_ASSERT(buffAddr != nullptr) followed by buffer stores.
//   The harness deliberately passes either a valid two-byte buffer or nullptr.
void b3_asserted_pointer_store(unsigned char* buffAddr) {
    FW_ASSERT(buffAddr != nullptr);
    buffAddr[0] = 42u;
    buffAddr[1] = 0u;
}
