#pragma once

#include "GBox/Core/Core.h"
#include "Window.h"
#include "GBox/Events/ApplicationEvent.h"
#include "GBox/Core/LayerStack.h"

#include "GBox/ImGui/ImGuiLayer.h"
#include "GBox/Renderer/Shader.h"

// int main(int argc, char** argv);

namespace GBox {

class GBOX_API Application {
public:
    Application();
    virtual ~Application();

    void Run();

    void OnEvent(Event& e);

    void PushLayer(Layer* Layer);
    void PushOverlay(Layer* Layer);

    inline static Application& Get() { return *_instance; }
    inline Window& GetWindow() { return *_window; }
private:
    bool onWindowClose(WindowCloseEvent& e);
    std::unique_ptr<Window> _window;
    ImGuiLayer* _imGuiLayer;
    bool _running = true;
    LayerStack _layerStack;

    unsigned int _vertexArray, _vertexBuffer, _indexBuffer;
    std::unique_ptr<Shader> m_Shader;
private:
    static Application* _instance;					//! ! !唯一实例的静态成员（static类型，需要初始化定义）
//     friend int ::main(int argc, char** argv);		// 通过将 main 声明为友元函数，便可以在外部通过 main 来访问私有的 Run 函数
};

//To be defined in CLIENT
Application* CreateApplication();

}