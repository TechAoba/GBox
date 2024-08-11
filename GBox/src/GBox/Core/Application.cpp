#include "gboxpch.h"
#include "GBox/Core/Application.h"
#include "GBox/Core/Input.h"
#include "GBox/Renderer/Renderer.h"

namespace GBox {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::_instance = nullptr;

Application::Application() {
    GBOX_CORE_ASSERT(!_instance, "Application already exists!");
    _instance = this;

    _window = std::unique_ptr<Window>(Window::Create());
    _window->SetEventCallback(BIND_EVENT_FN(OnEvent));

    _imGuiLayer = new ImGuiLayer();												//初始化 m_ImGuiLayer 为原始指针，并推入层栈
    PushOverlay(_imGuiLayer);

    // -------------- Triangle rendering ----------------
    float vertices[3 * 7] = {
        -0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
        0.5f,  -0.5f, 0.0f, 0.2f, 0.3f, 0.8f, 1.0f,
        0.0f,   0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f
    };
    BufferLayout layout = {	
        { ShaderDataType::Float3, "a_Position" },
        { ShaderDataType::Float4, "a_Color" }
    };
    unsigned int indices[3] = { 0, 1, 2 };

    m_IndexBuffer.reset(IndexBuffer::Create( indices, sizeof(indices) / sizeof(uint32_t) ));    
    m_VertexArray.reset(VertexArray::Create());
    m_VertexBuffer.reset(VertexBuffer::Create( vertices, sizeof(vertices) ) );

    m_VertexBuffer->SetLayout(layout);      // when we set the layout, we store the layout data in OpenGLBuffer.m_Layout by "SetLayout()" function, then delete layout.
    m_VertexArray->AddVertexBuffer(m_VertexBuffer);
    m_VertexArray->SetIndexBuffer(m_IndexBuffer);

    // -------------- Square rendering ----------------
    float squareVertices[3 * 4] = {
        -0.75f, -0.75f, 0.0f,
         0.75f, -0.75f, 0.0f,
         0.75f,  0.75f, 0.0f,
        -0.75f,  0.75f, 0.0f
    };
    BufferLayout squareLayout = {
        {ShaderDataType::Float3, "a_Position"}
    };
    uint32_t squareIndices[6] = { 0, 1, 2, 2, 3, 0 };

    m_SquareVA.reset(VertexArray::Create());
    std::shared_ptr<VertexBuffer> squareVB;
    std::shared_ptr<IndexBuffer> squareIB;
    squareVB.reset(VertexBuffer::Create(squareVertices, sizeof(squareVertices)));
    squareIB.reset(IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));

    squareVB->SetLayout(squareLayout);
    m_SquareVA->AddVertexBuffer(squareVB);
    m_SquareVA->SetIndexBuffer(squareIB);

    std::string vertexSrc = R"(
        #version 330 core
        
        layout(location = 0) in vec3 a_Position;
        layout(location = 1) in vec4 a_Color;

        out vec3 v_Position;
        out vec4 v_Color;

        void main()
        {
            v_Position = a_Position;
            v_Color = a_Color;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core

        in vec3 v_Position;
        in vec4 v_Color;
        layout(location = 0) out vec4 a_Color;

        void main()
        {
            a_Color = vec4(v_Position * 0.5 + 0.5, 1.0);
            a_Color = v_Color;
        }
    )";

    std::string blueShaderVertexSrc = R"(
        #version 330 core
        
        layout(location = 0) in vec3 a_Position;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string blueShaderFragmentSrc = R"(
        #version 330 core

        layout(location = 0) out vec4 color;
        in vec3 v_Position;

        void main()
        {
            a_Color = vec4(0.2, 0.3, 0.8, 1.0);
        }
    )";

    m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
    m_SquareShader.reset(new Shader(blueShaderVertexSrc, blueShaderFragmentSrc));
}
Application::~Application() {}

void Application::PushLayer(Layer* layer) {
    _layerStack.PushLayer(layer);
    layer->OnAttach();
}

void Application::PushOverlay(Layer* overlay) {
    _layerStack.PushOverlay(overlay);
    overlay->OnAttach();
}

// 回调函数传入Window类
void Application::OnEvent(Event& e) {
    EventDispatcher dispatcher(e);
    dispatcher.Dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));
    // GBOX_CORE_TRACE("{0}", e.ToString());

    for (auto it = _layerStack.rbegin(); it != _layerStack.rend(); ++it) {
        (*it)->OnEvent(e);
        if (e.Handled) break;
    }
}

void Application::Run() {
    while (_running) {

        RendererCommand::Clear();
        RendererCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Renderer::BeginScene();

        m_SquareShader->Bind();
        Renderer::Submit(m_SquareVA);

        m_Shader->Bind();
        Renderer::Submit(m_VertexArray);

        Renderer::EndScene();
        
        for (Layer* layer : _layerStack)
            layer->OnUpdate();

        _imGuiLayer->Begin();
        for (Layer* layer : _layerStack)
            layer->OnImGuiRender();
        _imGuiLayer->End();

        _window->OnUpdate();
    }
}

bool Application::onWindowClose(WindowCloseEvent& e) {
    _running = false;
    return true;
}

}