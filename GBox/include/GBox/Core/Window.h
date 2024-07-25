#pragma once

#include "gboxpch.h"
#include "Core.h"
#include "GBox/Events/Event.h"

namespace GBox
{
// window properties
struct WindowProps {
    std::string Title;
    unsigned int Width;
    unsigned int Height;
    WindowProps(const std::string& title = "GBox Engine",
        unsigned int width = 1280,
		unsigned int height = 720)
        : Title(title), Width(width), Height(height) {}
};

// An interface for the desktop system which based on Window
class GBOX_API Window {
public:
    static Scope<Window> Create(const WindowProps& props = WindowProps());

    using EventCallbackFn = std::function<void(Event&)>;
    virtual ~Window() = default;

    virtual void OnUpdate() = 0;

    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;

    virtual void SetEventCallback(const EventCallbackFn& callback) = 0;
    virtual void SetVSync(bool enabled) = 0;
    virtual bool IsVSync() const = 0;

    virtual void* GetNativeWindow() const = 0;
};

} // namespace GBox
