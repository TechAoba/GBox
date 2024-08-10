#include "gboxpch.h"
#include "GBox/Core/Application.h"
#include "GBox/Core/Input.h"

#include <glad/glad.h>

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

    float vertices[3 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };
    glGenBuffers(1, &_vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, _vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &_vertexArray);
    glBindVertexArray(_vertexArray);

    glEnableVertexAttribArray(0);
    // attribute type 0: position; 3 dimension point; value type; no normalize; 
    // stride: the byte cnt between points; step len: the byte cnt between point's position.
    // if there is texture behind postion, and 3 floats denote texture, last parm should be `(const void*) 8`.
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

    unsigned int indices[3]{
        0, 1, 2
    };

    glGenBuffers(1, &_indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    std::string vertexSrc = R"(
        #version 330 core
        
        layout(location = 0) in vec3 a_Position;

        out vec3 v_Position;

        void main()
        {
            v_Position = a_Position;
            gl_Position = vec4(a_Position, 1.0);
        }
    )";

    std::string fragmentSrc = R"(
        #version 330 core
        
        layout(location = 0) out vec4 color;

        in vec3 v_Position;

        void main()
        {
            color = vec4(v_Position * 0.5 + 0.5, 1.0);
        }
    )";

    m_Shader.reset(new Shader(vertexSrc, fragmentSrc));
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
        glClearColor(0.1f, 0.1f, 0.1f, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        m_Shader->Bind();
        glBindVertexArray(_vertexArray);
        glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

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