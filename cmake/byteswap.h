/* Windows compatibility header for byteswap.h */
#ifndef _BYTESWAP_H
#define _BYTESWAP_H

#ifdef _WIN32

#include <stdint.h>

#if defined(_MSC_VER)
    #include <stdlib.h>
    #define bswap_16(x) _byteswap_ushort(x)
    #define bswap_32(x) _byteswap_ulong(x)
    #define bswap_64(x) _byteswap_uint64(x)
#else
    /* GCC/MinGW builtin functions */
    #define bswap_16(x) __builtin_bswap16(x)
    #define bswap_32(x) __builtin_bswap32(x)
    #define bswap_64(x) __builtin_bswap64(x)
#endif

#endif /* _WIN32 */

#endif /* _BYTESWAP_H */
