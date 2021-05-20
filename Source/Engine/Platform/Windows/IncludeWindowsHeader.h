#pragma once

#if PLATFORM_WINDOWS

// Include Windows headers
#include <Windows.h>

// Remove some Windows definitions
//#undef MemoryBarrier
//#undef DeleteFile
//#undef MoveFile
//#undef CopyFile
//#undef CreateDirectory
//#undef GetComputerName
//#undef GetUserName
//#undef MessageBox
//#undef GetCommandLine
#undef CreateWindow
//#undef SetWindowText
//#undef DrawText
//#undef CreateFont
//#undef IsMinimized
//#undef IsMaximized
//#undef LoadIcon
//#undef InterlockedOr
//#undef InterlockedAnd
//#undef InterlockedExchange
//#undef InterlockedCompareExchange
//#undef InterlockedIncrement
//#undef InterlockedDecrement
//#undef InterlockedAdd
//#undef GetObject
//#undef GetClassName
//#undef GetMessage
//#undef CreateMutex
//#undef DrawState
//#undef LoadLibrary
//#undef GetEnvironmentVariable
//#undef SetEnvironmentVariable



#endif