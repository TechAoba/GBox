#include "gboxpch.h"
#include "GBox/Renderer/Renderer.h"

#include "GBox/Renderer/Texture.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace GBox
{

Ref<Texture2D> Texture2D::Create(const std::string& path) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None: GBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return std::make_shared<OpenGLTexture2D>(path);
        case RendererAPI::API::DirectX: GBOX_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
            return nullptr;
    }

    GBOX_CORE_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}



} // namespace GBox
