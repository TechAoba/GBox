#include "gboxpch.h"
#include "GBox/Core/Application.h"
#include "GBox/Core/Input.h"
#include "GBox/Renderer/Renderer.h"

#include <glfw/glfw3.h>

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

        float time = (float)glfwGetTime(); // TODO Platform::GetTime()
        TimeStep timestep = time - m_LastFrameTime;
        m_LastFrameTime = time;

        for (Layer* layer : _layerStack)
            layer->OnUpdate(timestep);

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