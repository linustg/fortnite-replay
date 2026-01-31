/* Windows compatibility header for endian.h */
#ifndef _ENDIAN_H_COMPAT_
#define _ENDIAN_H_COMPAT_

#ifdef _WIN32

#include <stdint.h>

/* Define byte order macros for Windows */
#define __LITTLE_ENDIAN 1234
#define __BIG_ENDIAN    4321
#define __BYTE_ORDER    __LITTLE_ENDIAN

/* Byte swap functions */
#if defined(_MSC_VER)
    #include <stdlib.h>
    #define htobe16(x) _byteswap_ushort(x)
    #define htole16(x) (x)
    #define be16toh(x) _byteswap_ushort(x)
    #define le16toh(x) (x)

    #define htobe32(x) _byteswap_ulong(x)
    #define htole32(x) (x)
    #define be32toh(x) _byteswap_ulong(x)
    #define le32toh(x) (x)

    #define htobe64(x) _byteswap_uint64(x)
    #define htole64(x) (x)
    #define be64toh(x) _byteswap_uint64(x)
    #define le64toh(x) (x)
#else
    /* GCC/MinGW */
    #define htobe16(x) __builtin_bswap16(x)
    #define htole16(x) (x)
    #define be16toh(x) __builtin_bswap16(x)
    #define le16toh(x) (x)

    #define htobe32(x) __builtin_bswap32(x)
    #define htole32(x) (x)
    #define be32toh(x) __builtin_bswap32(x)
    #define le32toh(x) (x)

    #define htobe64(x) __builtin_bswap64(x)
    #define htole64(x) (x)
    #define be64toh(x) __builtin_bswap64(x)
    #define le64toh(x) (x)
#endif

#endif /* _WIN32 */

#endif /* _ENDIAN_H_COMPAT_ */
