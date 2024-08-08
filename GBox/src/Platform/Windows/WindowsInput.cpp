#include "gboxpch.h"
#include "Platform/Windows/WindowsInput.h"

#include "GBox/Core/Application.h"
#include <GLFW/glfw3.h>

namespace GBox {

Input* Input::s_Instance = new WindowsInput();

bool WindowsInput::IsKeyPressedImpl(int keyCode) {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetKey(window, keyCode);
    return (state == GLFW_PRESS || state == GLFW_REPEAT);
}

bool WindowsInput::IsMouseButtonPressedImpl(int button) {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    auto state = glfwGetMouseButton(window, button);
    return state == GLFW_PRESS;
}

std::pair<float, float> WindowsInput::GetMousePosImpl() {
    auto window = static_cast<GLFWwindow*>(Application::Get().GetWindow().GetNativeWindow());
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    return { (float)xpos, (float)ypos };
}

bool WindowsInput::GetMouseXImpl() {
    auto [x, y] = GetMousePosImpl();
    return x;
}

bool WindowsInput::GetMouseYImpl() {
    auto [x, y] = GetMousePosImpl();
	return y;
}

}