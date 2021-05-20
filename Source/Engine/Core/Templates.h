#pragma once

////////////////////////////////////////////////////////////////////////////////////

template<typename T> struct TIsLValueReference { enum { Value = false }; };
template<typename T> struct TIsLValueReference<T&> { enum { Value = true }; };

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