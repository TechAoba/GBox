#include "gboxpch.h"
#include "GBox/Renderer/VertexArray.h"
#include "GBox/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace GBox
{

VertexArray* VertexArray::Create() {
    switch (Renderer::GetAPI()) {
        case RendererAPI::None: GBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ")
            return nullptr;
        case RendererAPI::OpenGL:
            return new OpenGLVertexArray();
        case RendererAPI::DirectX: GBOX_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
            return nullptr;
    }

    GBOX_CORE_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}

}