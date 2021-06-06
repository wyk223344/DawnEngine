#pragma once

#include "Engine/Core/Types/BaseTypes.h"
#include "Engine/Platform/CreateWindowSettings.h"
#include "Engine/Platform/Types.h"



class PlatformBase
{

public:
    /// <summary>
    /// Initializes the runtime platform service. Called on very beginning pf the engine startup.
    /// </summary>
    /// <returns>True if failed ot initialize platform, otherwise false.</returns>
    static bool Init();

    /// <summary>
    /// Writes the platform info to the log. Called after platform and logging service init but before engine services initialization.
    /// </summary>
    static void LogInfo();

    /// <summary>
    /// Called just before main game loop start.
    /// </summary>
    static void BeforeRun();

    /// <summary>
    /// Tick platform from game loop by main thread.
    /// </summary>
    static void Tick();

    /// <summary>
    /// Called before engine exit to pre dispose platform service.
    /// </summary>
    static void BeforeExit();

    /// <summary>
    /// Called after engine exit to shutdown platform service.
    /// </summary>
    static void Exit();

public:

    /// <summary>
    /// Suspends the execution of the current thread until the time-out interval elapses
    /// </summary>
    /// <param name="milliseconds">The time interval for which execution is to be suspended, in milliseconds.</param>
    static void Sleep(int32 milliseconds) = delete;

    /// <summary>
    /// Creates the window.
    /// </summary>
    /// <param name="settings">The window settings</param>
    /// <returns></returns>
    //static Window* CreateWindow(const CreateWindowSettings& settings) = delete;

    /// <summary>
    /// Allocates memory on a specified alignment boundary.
    /// </summary>
    /// <param name="size">The size of the allocation (in bytes).</param>
    /// <param name="alignment">The memory alignment (in bytes). Must be an integer power of 2.</param>
    /// <returns>The pointer to the allocated chunk of the memory. The pointer is a multiple of alignment.</returns>
    static void* Allocate(uint64 size, uint64 alignment) = delete;

    /// <summary>
    /// Frees a block of allocated memory.
    /// </summary>
    /// <param name="ptr">A pointer to the memory block to deallocate.</param>
    static void Free(void* ptr) = delete;
};