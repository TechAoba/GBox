#include "gboxpch.h"
#include "GBox/Renderer/Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace GBox
{
Renderer::SceneData* Renderer::m_SceneData = new Renderer::SceneData();

void Renderer::BeginScene(OrthograpgicCamera& camera) {
    m_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
}

void Renderer::EndScene() {}

void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform) {
    shader->Bind();
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_ViewProjection", m_SceneData->ViewProjectionMatrix);
    std::dynamic_pointer_cast<OpenGLShader>(shader)->UploadUniformMat4("u_Transform", transform);

    vertexArray->Bind();
    RendererCommand::DrawIndexed(vertexArray);
}

}