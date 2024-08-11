#include "gboxpch.h"
#include "GBox/Renderer/Renderer.h"

namespace GBox
{

void Renderer::BeginScene() {}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<VertexArray>& vertexArray) {
    vertexArray->Bind();
    RendererCommand::DrawIndexed(vertexArray);
}

}