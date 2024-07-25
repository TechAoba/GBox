#include "gboxpch.h"
#include "GBox/Core/Application.h"

#include <glad/glad.h>

namespace GBox {

#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

Application* Application::_instance = nullptr;

Application::Application() {
    GBOX_CORE_ASSERT(!_instance, "Application already exists!");
    _instance = this;

    _window = std::unique_ptr<Window>(Window::Create());
    _window->SetEventCallback(BIND_EVENT_FN(OnEvent));
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
        glClearColor(1, 0, 1, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        for (Layer* layer : _layerStack)
            layer->OnUpdate();

        _window->OnUpdate();
    }
}

bool Application::onWindowClose(WindowCloseEvent& e) {
    _running = false;
    return true;
}

}