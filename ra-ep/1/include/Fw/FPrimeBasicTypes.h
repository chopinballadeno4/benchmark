#ifndef FPRIME_BASIC_TYPES_H
#define FPRIME_BASIC_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <Fw/Types/BasicTypes.h>

// Fw-level type aliases (mirrors what the generated Fw*AliasAc.h files produce).
typedef I32 FwAssertArgType;
typedef U64 FwSizeType;
typedef U64 FwSignedSizeType;  // only sign differs; sufficient for benchmark
typedef I32 FwIndexType;

#define PRI_FwAssertArgType PRI_I32
#define PRI_FwSizeType      PRI_U64

#ifdef __cplusplus
}
#endif

#endif  // FPRIME_BASIC_TYPES_H
