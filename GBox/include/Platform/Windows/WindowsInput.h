#pragma once

#include "GBox/Core/Input.h"

namespace GBox {

class WindowsInput : public Input {
protected:
    /*virtual*/ bool IsKeyPressedImpl(int keyCode) override;
    /*virtual*/ bool IsMouseButtonPressedImpl(int button) override;
    /*virtual*/ std::pair<float, float> GetMousePosImpl() override;
    /*virtual*/ bool GetMouseXImpl() override;
    /*virtual*/ bool GetMouseYImpl() override;
};

}