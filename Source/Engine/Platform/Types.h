#pragma once


#if PLATFORM_WINDOWS

class WindowsPlatform;
typedef WindowsPlatform Platform;
class WindowsWindow;
typedef WindowsWindow Window;

#else

#error Missing Types implementation!

#endif 
