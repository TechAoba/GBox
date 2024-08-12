#include "gboxpch.h"
#include "GBox/Renderer/Renderer.h"

namespace GBox
{
Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

void Renderer::BeginScene(OrthograpgicCamera& camera) {
    m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const std::shared_ptr<Shader>& shader, const std::shared_ptr<VertexArray>& vertexArray, const glm::mat4& transform) {
    shader->Bind();
    shader->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    shader->UploadUniformMat4("u_Transform", transform);

    vertexArray->Bind();
    RendererCommand::DrawIndexed(vertexArray);
}

}