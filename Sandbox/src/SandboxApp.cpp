#include <GBox.h>

class ExampleLayer : public GBox::Layer {
public:
    ExampleLayer() : Layer("Example") {}

    void OnUpdate() override {
        GBOX_INFO("ExampleLayer::Update");
    }

    void OnEvent(GBox::Event& event) override {
        GBOX_TRACE("{0}", event.ToString());
    }
};

class Sandbox : public GBox::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        PushOverlay(new GBox::ImGuiLayer());
    }
    ~Sandbox() {
        
    }
};

GBox::Application* GBox::CreateApplication() {
    return new Sandbox();
}