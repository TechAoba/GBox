#pragma once

#include "GBox/Events/Event.h"

namespace GBox
{
class GBOX_API KeyEvent : public Event {
public:
    EVENT_CLASS_CATEGORY(EventCategoryKeyboard | EventCategoryInput);
    inline int GetKeyCode() const { return _KeyCode; }
protected:
    int _KeyCode;
    KeyEvent(int keycode) : _KeyCode(keycode) {}
};

class GBOX_API KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(int keycode, int repeatCount)
        : KeyEvent(keycode), _RepeatCount(repeatCount) {}

    EVENT_CLASS_TYPE(KeyPressed)
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyPressedEvent: " << _KeyCode << "(" << _RepeatCount << ")";
        return ss.str();
    }

    inline int GetRepeatCount() const { return _RepeatCount; }
private:
    int _RepeatCount;
};

class GBOX_API KeyReleasedEvent : public KeyEvent {
public:
    KeyReleasedEvent(int keycode) : KeyEvent(keycode) {}
    EVENT_CLASS_TYPE(KeyReleased);
    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyReleasedEvent: " << _KeyCode;
        return ss.str();
    }
};

class GBOX_API KeyTypedEvent : public KeyEvent {
public:
    KeyTypedEvent(int keycode) : KeyEvent(keycode) {}
    EVENT_CLASS_TYPE(KeyTyped);

    std::string ToString() const override {
        std::stringstream ss;
        ss << "KeyTypedEvent: " << _KeyCode;
        return ss.str();
    }
};

} // namespace GBox
