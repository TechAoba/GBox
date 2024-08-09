#include <GBox.h>

class ExampleLayer : public GBox::Layer {
public:
    ExampleLayer() : Layer("Example") {
        
    }

    void OnUpdate() override {
        if (GBox::Input::IsKeyPressed(GBOX_KEY_TAB))
            GBOX_INFO("Tab key is pressed(poll)!");
    }

    void OnEvent(GBox::Event& event) override {
        if (event.GetEventType() == GBox::EventType::KeyPressed) {
            GBox::KeyPressedEvent& e = (GBox::KeyPressedEvent&)event;
            GBOX_TRACE("{0}", (char)e.GetKeyCode());
            if (GBox::Input::IsKeyPressed(GBOX_KEY_TAB))
                GBOX_INFO("Tab key is pressed(event)!");
        }
    }
};

class Sandbox : public GBox::Application {
public:
    Sandbox() {
        PushLayer(new ExampleLayer());
        // PushOverlay(new GBox::ImGuiLayer()); 将其作为 GBox 运行时 固定自动添加的图层
    }
    ~Sandbox() {
        
    }
};

GBox::Application* GBox::CreateApplication() {
    return new Sandbox();
}