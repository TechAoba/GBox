#include "gboxpch.h"
#include "GBox/Renderer/RendererCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace GBox
{
RendererAPI* RendererAPI::Create() {
    switch (RendererAPI::GetAPI()) {
        case RendererAPI::API::None: GBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLRendererAPI();
        case RendererAPI::API::DirectX: GBOX_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
            return nullptr;
    }
    GBOX_CORE_ASSERT(false, "Unknown Renderer API!");
    return nullptr;
}

RendererAPI* RendererCommand::s_RendererAPI = RendererAPI::Create();

//RendererAPI* RendererCommand::s_RendererAPI = new OpenGLRendererAPI;

}