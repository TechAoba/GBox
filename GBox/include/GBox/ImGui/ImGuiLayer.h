#pragma once

#include "GBox/Core/Layer.h"
#include "GBox/Events/KeyEvent.h"
#include "GBox/Events/MouseEvent.h"
#include "GBox/Events/ApplicationEvent.h"

namespace GBox
{

class GBOX_API ImGuiLayer : public Layer {
public:
    ImGuiLayer();
    ~ImGuiLayer();

    void OnAttach() override;
    void OnDetach() override;
    void OnUpdate() override;
    void OnEvent(Event& event) override;
public:
    bool OnMouseButtonPressedEvent(MouseButtonPressedEvent& e);
    bool OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e);
    bool OnMouseMovedEvent(MouseMovedEvent& e);
    bool OnMouseScrolledEvent(MouseScrolledEvent& e);
    bool OnKeyPressedEvent(KeyPressedEvent& e);
    bool OnKeyReleasedEvent(KeyReleasedEvent& e);
    bool OnKeyTypedEvent(KeyTypedEvent& e);
    bool OnWindowResizeEvent(WindowResizeEvent& e);
private:
    float _time = 0.0f;
};

} // namespace GBox
