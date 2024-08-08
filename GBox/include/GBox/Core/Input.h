#pragma once

#include "GBox/Core/Core.h"
// #include "GBox/Core/Base.h"

namespace GBox
{

class GBOX_API Input {
public:
    inline static bool IsKeyPressed(int keyCode) { return s_Instance->IsKeyPressedImpl(keyCode); }
    inline static bool IsMouseButtonPressed(int button) { return s_Instance->IsMouseButtonPressedImpl(button); }
    inline static std::pair<float, float> GetMousePos() { return s_Instance->GetMousePosImpl(); }
    inline static bool GetMouseX() { return s_Instance->GetMouseXImpl(); }
    inline static bool GetMouseY() { return s_Instance->GetMouseYImpl(); }

protected:
    virtual bool IsKeyPressedImpl(int keyCode) = 0;
    virtual bool IsMouseButtonPressedImpl(int button) = 0;
    virtual std::pair<float, float> GetMousePosImpl() = 0;
    virtual bool GetMouseXImpl() = 0;
    virtual bool GetMouseYImpl() = 0;
private:
    static Input* s_Instance;

};


} // namespace GBox
