#include "gboxpch.h"
#include "GBox/Renderer/Shader.h"
#include "GBox/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GBox
{

Shader* Shader::Create(const std::string& vertexSrc, const std::string& fragmentSrc) {
    switch (Renderer::GetAPI()) {
        case RendererAPI::API::None: GBOX_CORE_ASSERT(false, "RendererAPI::None is currently not supported! ")
            return nullptr;
        case RendererAPI::API::OpenGL:
            return new OpenGLShader(vertexSrc, fragmentSrc);
        case RendererAPI::API::DirectX: GBOX_CORE_ASSERT(false, "RendererAPI::DirectX is currently not supported! ")
            return nullptr;
    }

    GBOX_CORE_ASSERT(false, "Unknown Renderer API!")
    return nullptr;
}

}