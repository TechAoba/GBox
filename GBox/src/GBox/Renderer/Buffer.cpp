#include "gboxpch.h"
#include "GBOX/Renderer/Buffer.h"

#include "GBox/Renderer/RendererAPI.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GBox
{

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None: GBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ") 
            return nullptr;
        case RendererAPI::API::OpenGL: 
            return new OpenGLVertexBuffer(vertices, size);
        case RendererAPI::API::DirectX: GBOX_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
            return nullptr;
    }
    GBOX_CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
    switch (RendererAPI::GetAPI()) {
		case RendererAPI::API::None:	GBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ") 
            return nullptr;
		case RendererAPI::API::OpenGL:	
            return new OpenGLIndexBuffer(indices, count);
		case RendererAPI::API::DirectX:	GBOX_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ") 
            return nullptr;
		}

    GBOX_CORE_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}

}