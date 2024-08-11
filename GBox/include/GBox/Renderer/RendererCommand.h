#pragma once

#include "GBox/Renderer/RendererAPI.h"

namespace GBox
{

class RendererCommand {
public:
    // static variable frmm Create(), which returns virtual funcs already overrided in Platform
    // So bind the functions form corresponding interface in OpenGL/DirectX/Metal/Valkan
    inline static void Clear() {
        s_RendererAPI->Clear();
    }
    inline static void SetClearColor(const glm::vec4& color) {
        s_RendererAPI->SetClearColor(color);
    }

    inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray) {
        s_RendererAPI->DrawIndexed(vertexArray);
    }
private:
    static RendererAPI* s_RendererAPI;
};

}