#pragma once

#include "GBox/Core/Window.h"
#include "GBox/Renderer/GraphicsContext.h"

#include <GLFW/glfw3.h>

namespace GBox {

class GBOX_API WindowsWindow : public Window {
public:
    WindowsWindow(const WindowProps& props);

    virtual ~WindowsWindow();
    // 每帧运行一次，更新GLFW，缓冲区会轮询输入时间
    void OnUpdate() override;

    inline unsigned int GetWidth() const override { return _windowdata.Width; }
    inline unsigned int GetHeight() const override { return _windowdata.Height; }
    // Window attributes
    inline void SetEventCallback(const EventCallbackFn& callback) override { _windowdata.EventCallback = callback; }
    void SetVSync(bool enabled) override;
    bool IsVSync() const override;

    inline void* GetNativeWindow() const override { return _gwindow; }
private:
    virtual void Init(const WindowProps& props);
    virtual void Shutdown();

private:
    GLFWwindow* _gwindow;
    GraphicsContext* _context;

    struct WindowData {
        std::string Title;
        unsigned int Width;
        unsigned int Height;
        bool VSync;
        EventCallbackFn EventCallback;
    };

    WindowData _windowdata;
};

}