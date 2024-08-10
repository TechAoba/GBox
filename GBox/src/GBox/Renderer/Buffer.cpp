#include "gboxpch.h"
#include "GBOX/Renderer/Buffer.h"

#include "GBox/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLBuffer.h"

namespace GBox
{

VertexBuffer* VertexBuffer::Create(float* vertices, uint32_t size) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::None: GBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ") 
            return nullptr;
        case RendererAPI::OpenGL: 
            return new OpenGLVertexBuffer(vertices, size);
        case RendererAPI::DirectX: GBOX_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
            return nullptr;
    }
    GBOX_CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}

IndexBuffer* IndexBuffer::Create(uint32_t* indices, uint32_t count) {
    switch (Renderer::GetAPI()) {
		case RendererAPI::None:	GBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ") 
            return nullptr;
		case RendererAPI::OpenGL:	
            return new OpenGLIndexBuffer(indices, count);
		case RendererAPI::DirectX:	GBOX_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ") 
            return nullptr;
		}

    GBOX_CORE_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}

}