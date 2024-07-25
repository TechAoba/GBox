#pragma once

#include "GBox/Events/Event.h"

namespace GBox
{

class GBOX_API MouseMovedEvent : public Event {
public:
    MouseMovedEvent(float x, float y) : _mouseX(x), _mouseY(y) {}
    EVENT_CLASS_TYPE(MouseMoved)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseMovedEvent: (" << _mouseX << ", " << _mouseY << ")";
        return ss.str();
    }

    inline float GetX() const { return _mouseX; }
    inline float GetY() const { return _mouseY; }
private:
    float _mouseX, _mouseY;
};

class GBOX_API MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(float xOffset, float yOffset)
        : _XOffset(xOffset), _YOffset(yOffset) {}

    EVENT_CLASS_TYPE(MouseScrolled)
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseScrolledEvent: " << _XOffset << ", " << _YOffset;
        return ss.str();
    }

    inline float GetXOffset() const { return _XOffset; }
    inline float GetYOffset() const { return _YOffset; }

private:
    float _XOffset, _YOffset;
};

// MouseButton
//////////////////////////////////////////////////////////////
class GBOX_API MouseButtonEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategoryMouse | EventCategoryInput)
    inline int GetMouseButton() const { return _button; }

protected:
    int _button;
    MouseButtonEvent(int button) : _button(button) {}
};

class GBOX_API MouseButtonPressedEvent : public MouseButtonEvent {
public:
    MouseButtonPressedEvent(int button) : MouseButtonEvent(button) {}
    EVENT_CLASS_TYPE(MouseButtonPressed)

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonPressedEvent: " << _button;
        return ss.str();
    }
};

class GBOX_API MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    MouseButtonReleasedEvent(int button) : MouseButtonEvent(button) {}
    EVENT_CLASS_TYPE(MouseButtonReleased)

    std::string ToString() const override {
        std::stringstream ss;
        ss << "MouseButtonReleasedEvent: " << _button;
        return ss.str();
    }
};


} // namespace GBox