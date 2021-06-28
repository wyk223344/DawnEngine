#pragma once

#include "Engine/Core/Include.h"
#include "Engine/Graphics/Enums.h"
#include "Engine/Graphics/PixelFormat.h"

namespace DawnEngine
{
	enum class GPUBufferFlags
	{
        // Nothing
        None = 0x000,

        // Create a buffer that can be bound as a shader resource.
        ShaderResource = 0x001,

        // Create a buffer that can be bound as a vertex buffer.
        VertexBuffer = 0x002,

        // Create a buffer that can be bound as a index buffer.
        IndexBuffer = 0x004,

        // Create a buffer that can be bound as a unordered access.
        UnorderedAccess = 0x008,

        // Flag for unordered access buffers that will use append feature.
        Append = 0x010,

        // Flag for unordered access buffers that will use counter feature.
        Counter = 0x020,

        // Flag for unordered access buffers that will be used as draw indirect argument buffer.
        Argument = 0x040,

        // Flag for structured buffers.
        Structured = 0x080,

        // Flag for raw buffers.
        RawBuffer = 0x100,

        // Creates a structured buffer that supports unordered access and append.
        StructuredAppendBuffer = UnorderedAccess | Structured | Append,

        // Creates a structured buffer that supports unordered access and counter.
        StructuredCounterBuffer = UnorderedAccess | Structured | Counter
	};

    DECLARE_ENUM_OPERATORS(GPUBufferFlags);

    struct GPUBufferDescription
    {
    public:
        // The buffer total size.
        uint32 Size;

        // The buffer structure stride (size in bytes per element).
        uint32 Stride;

        // The buffer flags.
        GPUBufferFlags Flags;

        // The format of the data in a buffer.
        PixelFormat Format;

        // The pointer to location of initial resource data. Null if not used.
        const void* InitData;

        // Value that identifies how the buffer is to be read from and written to. The most common value is <see cref="GPUResourceUsage.Default"/>; see <strong><see cref="GPUResourceUsage"/></strong> for all possible values.
        GPUResourceUsage Usage;

    public:

        // Gets the number elements in the buffer.
        uint32 GetElementsCount() const
        {
            return Stride > 0 ? Size / Stride : 0;
        }

        // Gets a value indicating whether this instance is a shader resource.
        bool IsShaderResource() const
        {
            return (Flags & GPUBufferFlags::ShaderResource) != 0;
        }

        // Gets a value indicating whether this instance is a unordered access.
        bool IsUnorderedAccess() const
        {
            return (Flags & GPUBufferFlags::UnorderedAccess) != 0;
        }
    };
}