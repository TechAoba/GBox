#pragma once

#include "GBox/Renderer/Buffer.h"

namespace GBox
{

//////////////////////////////////////////////////////
/////////////////// VertexBuffer /////////////////////
//////////////////////////////////////////////////////
class OpenGLVertexBuffer : public VertexBuffer {
public:
    OpenGLVertexBuffer(float* vertices, uint32_t size);
    ~OpenGLVertexBuffer();

    void Bind() const override;
    void Unbind() const override;

    const BufferLayout& GetLayout() const override { return m_Layout; };
    void SetLayout(const BufferLayout& layout) override { m_Layout = layout; };
private:
    uint32_t m_RendererID;
    BufferLayout m_Layout;
};

//////////////////////////////////////////////////////
/////////////////// IndexBuffer //////////////////////
//////////////////////////////////////////////////////
class OpenGLIndexBuffer : public IndexBuffer {
public:
    OpenGLIndexBuffer(uint32_t* indices, uint32_t count);
    ~OpenGLIndexBuffer();

    void Bind() const override;
    void Unbind() const override;
    uint32_t GetCount() const override { return m_Count; };
private:
    uint32_t m_RendererID;
    uint32_t m_Count;
};

}