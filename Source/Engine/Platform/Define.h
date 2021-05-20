#pragma once


enum class PlatformType
{
    /// <summary>
    /// Running on Windows.
    /// </summary>
    Windows = 1,

    /// <summary>
    /// Running on Xbox One.
    /// </summary>
    XboxOne = 2,

    /// <summary>
    /// Running Windows Store App (Universal Windows Platform).
    /// </summary>
    UWP = 3,

    /// <summary>
    /// Running on Linux system.
    /// </summary>
    Linux = 4,

    /// <summary>
    /// Running on PlayStation 4.
    /// </summary>
    PS4 = 5,

    /// <summary>
    /// Running on Xbox Series X.
    /// </summary>
    XboxScarlett = 6,

    /// <summary>
    /// Running on Android.
    /// </summary>
    Android = 7,

    /// <summary>
    /// Running on Switch.
    /// </summary>
    Switch = 8,
};


#if defined( _WIN32 ) || defined( __WIN32__ ) || defined( _WIN64 )
#  define PLATFORM_WINDOWS 1
#else
#  define PLATFORM_WINDOWS 0
#endif


// Unicode text macro
#if !defined(TEXT)
#if PLATFORM_TEXT_IS_CHAR16
#define _TEXT(x) u ## x
#else
#define _TEXT(x) L ## x
#endif
#define TEXT(x) _TEXT(x)
#endif

