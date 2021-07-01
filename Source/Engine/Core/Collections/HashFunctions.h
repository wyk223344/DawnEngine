#pragma once
#include "Engine/Core/Types/BaseTypes.h"

inline uint32 GetHash(const uint8 key)
{
    return key;
}

inline uint32 GetHash(const int8 key)
{
    return key;
}

inline uint32 GetHash(const uint16 key)
{
    return key;
}

inline uint32 GetHash(const int16 key)
{
    return key;
}

inline uint32 GetHash(const int32 key)
{
    return key;
}

inline uint32 GetHash(const uint32 key)
{
    return key;
}

inline uint32 GetHash(const uint64 key)
{
    return (uint32)key + ((uint32)(key >> 32) * 23);
}

inline uint32 GetHash(const int64 key)
{
    return (uint32)key + ((uint32)(key >> 32) * 23);
}

inline uint32 GetHash(const char key)
{
    return key;
}

inline uint32 GetHash(const Char key)
{
    return key;
}

inline uint32 GetHash(const float key)
{
    return *(uint32*)&key;
}

inline uint32 GetHash(const double key)
{
    return GetHash(*(uint64*)&key);
}

inline uint32 GetHash(const void* key)
{
    static const int64 shift = 3;
    return (uint32)((int64)(key) >> shift);
}

inline uint32 GetHash(void* key)
{
    static const int64 shift = 3;
    return (uint32)((int64)(key) >> shift);
}

inline void CombineHash(uint32& hash, const uint32 value)
{
    // Reference: Boost lib
    hash ^= value + 0x9e3779b9 + (hash << 6) + (hash >> 2);
}