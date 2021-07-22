#pragma once

#include "Engine/Core/Include.h"

namespace DawnEngine
{
    // 常量缓冲区槽位
    enum class GPUConstantBufferSlot
    {
        Global = 0,

        Mesh = 1,

        Material = 2,
    };

    enum class GPUResourceUsage
    {
        /// <summary>
        /// A resource that requires read and write access by the GPU. 
        /// This is likely to be the most common usage choice. 
        /// Memory will be used on device only, so fast access from the device is preferred. 
        /// It usually means device-local GPU (video) memory.
        /// </summary>
        /// <remarks>
        /// Usage:
        /// - Resources written and read by device, e.g. images used as render targets.
        /// - Resources transferred from host once (immutable) or infrequently and read by
        ///   device multiple times, e.g. textures to be sampled, vertex buffers, constant
        ///   buffers, and majority of other types of resources used on GPU.
        /// </remarks>
        Default = 0,

        /// <summary>
        /// A resource that is accessible by both the GPU (read only) and the CPU (write only). 
        /// A dynamic resource is a good choice for a resource that will be updated by the CPU at least once per frame. 
        /// Dynamic buffers or textures are usually used to upload data to GPU and use it within a single frame.
        /// </summary>
        /// <remarks>
        /// Usage:
        /// - Resources written frequently by CPU (dynamic), read by device. 
        ///   E.g. textures, vertex buffers, uniform buffers updated every frame or every draw call.
        /// </remarks>
        Dynamic = 1,

        /// <summary>
        /// A resource that supports data transfer (copy) from the CPU to the GPU.  
        /// It usually means CPU (system) memory. Resources created in this pool may still be accessible to the device, but access to them can be slow.
        /// </summary>
        /// <remarks>
        /// Usage:
        /// - Staging copy of resources used as transfer source.
        /// </remarks>
        StagingUpload = 2,

        /// <summary>
        /// A resource that supports data transfer (copy) from the GPU to the CPU. 
        /// </summary>
        /// <remarks>
        /// Usage:
        /// - Resources written by device, read by host - results of some computations, e.g. screen capture, average scene luminance for HDR tone mapping.
        /// - Any resources read or accessed randomly on host, e.g. CPU-side copy of vertex buffer used as source of transfer, but also used for collision detection.
        /// </remarks>
        StagingReadback = 3,
    };

    /// <summary>
    /// Multisample count level.
    /// </summary>
    enum class MSAALevel : int32
    {
        /// <summary>
        /// Disabled multisampling.
        /// </summary>
        None = 1,

        /// <summary>
        /// Two samples per pixel.
        /// </summary>
        X2 = 2,

        /// <summary>
        /// Four samples per pixel.
        /// </summary>
        X4 = 4,

        /// <summary>
        /// Eight samples per pixel.
        /// </summary>
        X8 = 8,
    };

    DECLARE_ENUM_EX_6(ShaderStage, int32, 0, Vertex, Hull, Domain, Geometry, Pixel, Compute);

    /// <summary>
    /// Describes how a mapped GPU resource will be accessed.
    /// </summary>
    enum class GPUResourceMapMode
    {
        /// <summary>
        /// The resource is mapped for reading.
        /// </summary>
        Read = 0x01,

        /// <summary>
        /// The resource is mapped for writing.
        /// </summary>
        Write = 0x02,

        /// <summary>
        /// The resource is mapped for reading and writing.
        /// </summary>
        ReadWrite = Read | Write,
    };

    /// <summary>
    /// Primitives types.
    /// </summary>
    enum class PrimitiveTopologyType
    {
        /// <summary>
        /// Unknown topology.
        /// </summary>
        Undefined = 0,

        /// <summary>
        /// Points list.
        /// </summary>
        Point = 1,

        /// <summary>
        /// Line list.
        /// </summary>
        Line = 2,

        /// <summary>
        /// Triangle list.
        /// </summary>
        Triangle = 3,
    };

    /// <summary>
    /// Primitives culling mode.
    /// </summary>
    enum class CullMode : byte
    {
        /// <summary>
        /// Cull back-facing primitives only.
        /// </summary>
        Normal = 0,

        /// <summary>
        /// Cull front-facing primitives only.
        /// </summary>
        Inverted = 1,

        /// <summary>
        /// Disable face culling.
        /// </summary>
        TwoSided = 2,
    };

    /// <summary>
    /// Comparison function modes
    /// </summary>
    enum class ComparisonFunc : byte
    {
        // Never pass the comparison.
        Never = 1,
        // If the source data is less than the destination data, the comparison passes.
        Less = 2,
        // If the source data is equal to the destination data, the comparison passes.
        Equal = 3,
        // If the source data is less than or equal to the destination data, the comparison passes.
        LessEqual = 4,
        // If the source data is greater than the destination data, the comparison passes.
        Greater = 5,
        // If the source data is not equal to the destination data, the comparison passes.
        NotEqual = 6,
        // If the source data is greater than or equal to the destination data, the comparison passes.
        GreaterEqual = 7,
        // Always pass the comparison.
        Always = 8,
    };

    /// <summary>
    /// Rendering quality levels.
    /// </summary>
    enum class Quality : byte
    {
        /// <summary>
        /// The low quality.
        /// </summary>
        Low = 0,

        /// <summary>
        /// The medium quality.
        /// </summary>
        Medium = 1,

        /// <summary>
        /// The high quality.
        /// </summary>
        High = 2,

        /// <summary>
        /// The ultra, mega, fantastic quality!
        /// </summary>
        Ultra = 3,
    };
}