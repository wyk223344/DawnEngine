#pragma once


#include "Engine/Graphics/GPUContext.h"


class GPUDevice
{
public:
	static GPUDevice* Instance;

public:
    // virtual GPUContext* GetMainContext() = 0;

public:

    /// <summary>
    /// Init device resources
    /// </summary>
    /// <returns>True if cannot init, otherwise false.</returns>
    virtual bool Init();

    /// <summary>
    /// Checks if GPU can render frame now (all data is ready), otherwise will skip frame rendering.
    /// </summary>
    /// <returns>True if skip rendering, otherwise false.</returns>
   /* virtual bool CanDraw()
    {
        return true;
    }*/

    /// <summary>
    /// Call frame rendering and process data using GPU
    /// </summary>
    virtual void Draw();

    /// <summary>
    /// Clean all allocated data by device
    /// </summary>
    virtual void Dispose();

    /// <summary>
    /// Wait for GPU end doing submitted work
    /// </summary>
    // virtual void WaitForGPU() = 0;

protected:

    ///// <summary>
    ///// Called during Draw method before any frame rendering initialization. Cannot be used to submit commands to GPU.
    ///// </summary>
    //virtual void DrawBegin();

    ///// <summary>
    ///// Called during Draw method after rendering. Cannot be used to submit commands to GPU.
    ///// </summary>
    //virtual void DrawEnd();
};