#pragma once

namespace DawnEngine
{

    ////////////////////////////////////////////////////////////////////////////////////

    template<typename T> struct TIsLValueReference { enum { Value = false }; };
    template<typename T> struct TIsLValueReference<T&> { enum { Value = true }; };

    ////////////////////////////////////////////////////////////////////////////////////

    template<typename T>                           struct TIsFunction { enum { Value = false }; };
    template<typename RetType, typename... Params> struct TIsFunction<RetType(Params...)> { enum { Value = true }; };

    ////////////////////////////////////////////////////////////////////////////////////

    template<typename X, typename Y> struct TAreTypesEqual { enum { Value = false }; };
    template<typename T> struct TAreTypesEqual<T, T> { enum { Value = true }; };

    ////////////////////////////////////////////////////////////////////////////////////

    // Removes any reference qualifiers from a type.

    template<typename T> struct TRemoveReference { typedef T Type; };
    template<typename T> struct TRemoveReference<T&> { typedef T Type; };
    template<typename T> struct TRemoveReference<T&&> { typedef T Type; };

    ////////////////////////////////////////////////////////////////////////////////////

    template<typename T>
    inline T&& Forward(typename TRemoveReference<T>::Type& t) noexcept
    {
        return static_cast<T&&>(t);
    }

    template<typename T>
    inline T&& Forward(typename TRemoveReference<T>::Type&& t) noexcept
    {
        static_assert(!TIsLValueReference<T>::Value, "Can not forward an rvalue as an lvalue.");
        return static_cast<T&&>(t);
    }

    ////////////////////////////////////////////////////////////////////////////////////
}