#ifndef FW_BASIC_TYPES_H
#define FW_BASIC_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif

#include <inttypes.h>

typedef int8_t   I8;
typedef uint8_t  U8;
typedef uint8_t  BYTE;
typedef int16_t  I16;
typedef uint16_t U16;
typedef int32_t  I32;
typedef uint32_t U32;
typedef int64_t  I64;
typedef uint64_t U64;
typedef float    F32;
typedef double   F64;
typedef char     CHAR;

#define PRI_I8  PRIi8
#define PRI_U8  PRIu8
#define PRI_I16 PRIi16
#define PRI_U16 PRIu16
#define PRI_I32 PRId32
#define PRI_U32 PRIu32
#define PRI_I64 PRId64
#define PRI_U64 PRIu64
#define PRI_F64 "lf"

// Assert level constants — must match Fw/Types/Assert.hpp comparisons.
#define FW_NO_ASSERT            (1)
#define FW_FILEID_ASSERT        (2)
#define FW_FILENAME_ASSERT      (3)
#define FW_RELATIVE_PATH_ASSERT (4)

#ifdef __cplusplus
}
#endif

#endif  // FW_BASIC_TYPES_H
