#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include <math.h>

#undef PI
#define PI 3.1415926535897932f
#define TWO_PI 6.28318530718f
#define PI_INV 0.31830988618f
#define PI_OVER_2 1.57079632679f
#define PI_OVER_4 0.78539816339f
#define PI_HALF PI_OVER_2
#define GOLDEN_RATIO 1.6180339887f

// The value for which all absolute numbers smaller than are considered equal to zero.
#define ZeroTolerance 1e-6f

// Converts radians to degrees.
#define RadiansToDegrees (180.0f / PI)

// Converts degrees to radians.
#define DegreesToRadians (PI / 180.0f)


namespace DawnEngine::Math
{
    static float Trunc(float value)
    {
        return truncf(value);
    }

    static float Round(float value)
    {
        return roundf(value);
    }

    static float Floor(float value)
    {
        return floorf(value);
    }

    static float Ceil(float value)
    {
        return ceilf(value);
    }

    static float Sin(float value)
    {
        return sinf(value);
    }

    static float Asin(float value)
    {
        return asinf(value < -1.f ? -1.f : value < 1.f ? value : 1.f);
    }

    static float Sinh(float value)
    {
        return sinhf(value);
    }

    static float Cos(float value)
    {
        return cosf(value);
    }

    static float Acos(float value)
    {
        return acosf(value < -1.f ? -1.f : value < 1.f ? value : 1.f);
    }

    static float Tan(float value)
    {
        return tanf(value);
    }

    static float Atan(float value)
    {
        return atanf(value);
    }

    static float Atan2(float y, float x)
    {
        return atan2f(y, x);
    }

    static float InvSqrt(float value)
    {
        return 1.0f / sqrtf(value);
    }

    static float Log(const float value)
    {
        return logf(value);
    }

    static float Log2(const float value)
    {
        return log2f(value);
    }

    static float Log10(const float value)
    {
        return log10f(value);
    }

    static float Pow(const float base, const float exponent)
    {
        return powf(base, exponent);
    }

    static float Sqrt(const float value)
    {
        return sqrtf(value);
    }

    static float Exp(const float value)
    {
        return expf(value);
    }

    static float Exp2(const float value)
    {
        return exp2f(value);
    }

    static double Abs(const double value)
    {
        return fabs(value);
    }

    static float Abs(const float value)
    {
        return fabsf(value);
    }

    static int32 Abs(const int32 value)
    {
        return value < 0 ? -value : value;
    }

    static int64 Abs(const int64 value)
    {
        return value < 0 ? -value : value;
    }

    static double Mod(const double a, const double b)
    {
        return fmod(a, b);
    }

    static float Mod(const float a, const float b)
    {
        return fmodf(a, b);
    }

    static float ModF(const float a, float* b)
    {
        return modff(a, b);
    }

    template<class T>
    static bool IsInRange(const T value, const T min, const T max)
    {
        return value >= min && value <= max;
    }

    template<class T>
    static bool IsNotInRange(const T value, const T min, const T max)
    {
        return value < min || value > max;
    }

    static bool IsPowerOfTwo(uint32 value)
    {
        return (value & value - 1) == 0;
    }

    // Clamp value to be between minimum and maximum values, inclusive
    template<class T>
    static T Clamp(const T value, const T min, const T max)
    {
        return value < min ? min : value < max ? value : max;
    }

    // Clamp value to be between 0 and 1 range, inclusive
    template<class T>
    static T Saturate(const T value)
    {
        return value < 0 ? 0 : value < 1 ? value : 1;
    }

    template<class T>
    static float AverageArithmetic(const T a, const T b)
    {
        return (a + b) * 0.5f;
    }

    template<class T>
    static T Max(const T a, const T b)
    {
        return a > b ? a : b;
    }

    template<class T>
    static T Min(const T a, const T b)
    {
        return a < b ? a : b;
    }

    template<class T>
    static T Max(const T a, const T b, const T c)
    {
        return Max(Max(a, b), c);
    }

    template<class T>
    static T Max(const T a, const T b, const T c, const T d)
    {
        return Max(Max(Max(a, b), c), d);
    }

    template<class T>
    static T Min(const T a, const T b, const T c)
    {
        return Min(Min(a, b), c);
    }

    template<class T>
    static T Min(const T a, const T b, const T c, const T d)
    {
        return Min(Min(Min(a, b), c), d);
    }

    template<class T>
    static T Square(const T a)
    {
        return a * a;
    }

    template<class T, class U>
    static T Lerp(const T& a, const T& b, const U& alpha)
    {
        return (T)(a + alpha * (b - a));
    }

    static float SmoothStep(float amount)
    {
        return amount <= 0 ? 0 : amount >= 1 ? 1 : amount * amount * (3 - 2 * amount);
    }

    inline bool IsZero(float a)
    {
        return Abs(a) < ZeroTolerance;
    }

    inline bool IsOne(float a)
    {
        return IsZero(a - 1.0f);
    }

    template<typename T>
    static T AlignUpWithMask(T value, T mask)
    {
        return (T)(value + mask & ~mask);
    }

    template<typename T>
    static T AlignDownWithMask(T value, T mask)
    {
        return (T)(value & ~mask);
    }

    /// <summary>
    /// Checks if a and b are not even almost equal, taking into account the magnitude of floating point numbers
    /// </summary>
    /// <param name="a">The left value to compare</param>
    /// <param name="b">The right value to compare</param>
    /// <returns>False if a almost equal to b, otherwise true</returns>
    static bool NotNearEqual(float a, float b)
    {
        // Check if the numbers are really close - needed when comparing numbers near zero
        if (IsZero(a - b))
            return false;

        // Original from Bruce Dawson: http://randomascii.wordpress.com/2012/02/25/comparing-floating-point-numbers-2012-edition/
        const int32 aInt = *(int32*)&a;
        const int32 bInt = *(int32*)&b;

        // Different signs means they do not match
        if (aInt < 0 != bInt < 0)
            return true;

        // Find the difference in ULPs
        const int ulp = Abs(aInt - bInt);

        // Choose of maxUlp = 4
        // according to http://code.google.com/p/googletest/source/browse/trunk/include/gtest/internal/gtest-internal.h
        const int maxUlp = 4;
        return ulp > maxUlp;
    }

    static uint32 FloorLog2(uint32 value)
    {
        uint32 pos = 0;
        if (value >= 1 << 16)
        {
            value >>= 16;
            pos += 16;
        }
        if (value >= 1 << 8)
        {
            value >>= 8;
            pos += 8;
        }
        if (value >= 1 << 4)
        {
            value >>= 4;
            pos += 4;
        }
        if (value >= 1 << 2)
        {
            value >>= 2;
            pos += 2;
        }
        if (value >= 1 << 1)
        {
            pos += 1;
        }
        return value == 0 ? 0 : pos;
    }
}