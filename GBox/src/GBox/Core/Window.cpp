#include "gboxpch.h"
#include "GBox/Core/Window.h"

#ifdef GBOX_PLATFORM_WINDOWS
	#include "Platform/Windows/WindowsWindow.h"
#endif

namespace GBox {

	Scope<Window> Window::Create(const WindowProps& props) {
		#ifdef GBOX_PLATFORM_WINDOWS
			return CreateScope<WindowsWindow>(props);
		#elif defined GBOX_PLATFORM_MACOS
			return CreateScope<MacosWindow>(props);
		#elif defined GBOX_PLATFORM_LINUX
			return CreateScope<LinuxWindow>(props);
		#else
			GBOX_CORE_ASSERT(false, "Unknown platform!");
			return nullptr;
		#endif
	}

}