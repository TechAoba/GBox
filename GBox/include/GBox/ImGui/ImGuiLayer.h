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

    virtual void OnAttach() override;
    virtual void OnDetach() override;
    virtual void OnImGuiRender() override;

    void Begin();
    void End();
private:
    float _time = 0.0f;
};

} // namespace GBox
