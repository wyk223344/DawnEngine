#pragma once

typedef unsigned char byte; // Unsigned 8 bits

// Unsigned base types
typedef unsigned char uint8; // 8-bit  unsigned
typedef unsigned short uint16; // 16-bit unsigned
typedef unsigned int uint32; // 32-bit unsigned
typedef unsigned long long uint64; // 64-bit unsigned

// Signed base types
typedef signed char int8; // 8-bit  signed
typedef signed short int16; // 16-bit signed
typedef signed int int32; // 32-bit signed
typedef long long int64; // 64-bit signed


/// <summary>
/// Defines 16-bit Unicode character for UTF-16 Little Endian.
/// </summary>
#if PLATFORM_TEXT_IS_CHAR16
typedef char16_t Char;
#else
typedef wchar_t Char;
#endif


// Limits
#define MIN_uint8 ((uint8)0x00)
#define	MIN_uint16 ((uint16)0x0000)
#define	MIN_uint32 ((uint32)0x00000000)
#define MIN_uint64 ((uint64)0x0000000000000000)
#define MIN_int8 ((int8)-128)
#define MIN_int16 ((int16)-32768)
#define MIN_int32 -((int32)2147483648)
#define MIN_int64 -((int64)9223372036854775808)
#define MIN_float -(3.402823466e+38f)
#define MIN_double -(1.7976931348623158e+308)
#define MAX_uint8 ((uint8)0xff)
#define MAX_uint16 ((uint16)0xffff)
#define MAX_uint32 ((uint32)0xffffffff)
#define MAX_uint64 ((uint64)0xffffffffffffffff)
#define MAX_int8 ((int8)127)
#define MAX_int16 ((int16)32767)
#define MAX_int32 ((int32)2147483647)
#define MAX_int64 ((int64)9223372036854775807)
#define MAX_float (3.402823466e+38f)
#define MAX_double (1.7976931348623158e+308)