#include "gboxpch.h"
#include "Platform/Windows/WindowsWindow.h"
#include "GBox/Events/MouseEvent.h"
#include "GBox/Events/ApplicationEvent.h"
#include "GBox/Events/KeyEvent.h"

#include "Platform/OpenGL/OpenGLContext.h"

#include <glad/glad.h>

namespace GBox{

static bool s_GLFWInitialized = false;

static void GLFWErrorCallback(int error_code, const char* description) {
    GBOX_CORE_ERROR("GLFW Error ({0}):{1}", error_code, description);
}

WindowsWindow::WindowsWindow(const WindowProps& props) {
    Init(props);
}
WindowsWindow::~WindowsWindow() {
    Shutdown();
}

void WindowsWindow::Init(const WindowProps& props) {
    _windowdata.Title = props.Title;
    _windowdata.Width = props.Width;
    _windowdata.Height = props.Height;

    GBOX_CORE_INFO("Creating window: {0} ({1} , {2})", props.Title, props.Width, props.Height);

    if (!s_GLFWInitialized) {
        // TODO: glfwTerminate on system shutdown
        int success = glfwInit();
        GBOX_CORE_ASSERT(success, "Could not initialize GLFW!");

        //If Initalized successfully but get the wrong on run time
        glfwSetErrorCallback(GLFWErrorCallback);
        s_GLFWInitialized = true;
    }

    _gwindow = glfwCreateWindow((int)props.Width, (int)props.Height, _windowdata.Title.c_str(), nullptr, nullptr);
    
    _context = new OpenGLContext(_gwindow);
    _context->Init();

    glfwSetWindowUserPointer(_gwindow, &_windowdata);
    SetVSync(true);

    // Set GLFW callbacks
    glfwSetWindowSizeCallback(_gwindow, [](GLFWwindow* window, int width, int height) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        data.Height = height;
        data.Width = width;

        WindowResizeEvent event(width, height);
        data.EventCallback(event);
    });

    glfwSetWindowCloseCallback(_gwindow, [](GLFWwindow* window) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        WindowCloseEvent event;
        data.EventCallback(event);
    });

    glfwSetKeyCallback(_gwindow, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: {KeyPressedEvent event(key, 0); data.EventCallback(event); break;}
            case GLFW_RELEASE: {KeyReleasedEvent event(key); data.EventCallback(event); break;}
            case GLFW_REPEAT: {KeyPressedEvent event(key, 1); data.EventCallback(event); break;}
        }
    });

    glfwSetCharCallback(_gwindow, [](GLFWwindow* window, unsigned int keycode) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        KeyTypedEvent event(keycode);
        data.EventCallback(event);
    });

    glfwSetMouseButtonCallback(_gwindow, [](GLFWwindow* window, int button, int action, int mods) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        switch (action) {
            case GLFW_PRESS: { MouseButtonPressedEvent event(button);	data.EventCallback(event);	break; }
            case GLFW_RELEASE: { MouseButtonReleasedEvent event(button);	data.EventCallback(event);	break; }
        }
    });

    glfwSetScrollCallback(_gwindow, [](GLFWwindow* window, double xOffset, double yOffset) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseScrolledEvent event((float)xOffset, (float)yOffset);
        data.EventCallback(event);
    });

    glfwSetCursorPosCallback(_gwindow, [](GLFWwindow* window, double xpos, double ypos) {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

        MouseMovedEvent event((float)xpos, (float)ypos);
        data.EventCallback(event);
    });
    
}

void WindowsWindow::Shutdown() {
    glfwDestroyWindow(_gwindow);
}

void WindowsWindow::OnUpdate() {
    glfwPollEvents();
    _context->SwapBuffers();
}

void WindowsWindow::SetVSync(bool enabled) {
    if (enabled) {
        glfwSwapInterval(1);        // wait 1 frame to run
    }
    else {
        glfwSwapInterval(0);
    }
    _windowdata.VSync = enabled;
}

bool WindowsWindow::IsVSync() const {
    return _windowdata.VSync;
}

}