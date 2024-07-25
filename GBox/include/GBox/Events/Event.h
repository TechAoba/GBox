#pragma once

#include "gboxpch.h"
#include "GBox/Core/Core.h"

namespace GBox {
	/**
     * The events we set in Nut now are currently blocking.
     * When event occurs,it immediately gets dispatched（得到调度） and must be dealt there right now.
     * we might be to buffer events in a event bus (事件总线) ,so we can process them during event part stage.
     */

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved
	};

	enum EventCategory {
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

#define EVENT_CLASS_TYPE(type)\
			static EventType GetStaticType() { return EventType::type; }\
			virtual EventType GetEventType() const override { return GetStaticType(); }\
			virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category)\
			virtual int GetCategoryFlags() const override { return category; }

	class GBOX_API Event {
		friend class EventDispatcher;
		inline friend std::ostream& operator<<(std::ostream& os, const Event& ev) {
			return os << ev.ToString();
		}
	public:
		bool Handled = false;
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }

		inline bool IsInCategory(EventCategory category) {
			return GetCategoryFlags() & category;
		}
	};

    class GBOX_API EventDispatcher {
    private:
        Event& m_Event;

        template <typename T>
        using EventFn = std::function<bool(T&)>;
    
    public:
        EventDispatcher(Event& event) : m_Event(event) {}
        template <typename T>
        bool Dispatch(EventFn<T> func) {
            if (m_Event.GetEventType() == T::GetStaticType()) {
                m_Event.Handled = func( static_cast<T&>(m_Event) );
                return true;
            }
            return false;
        }
    };

}