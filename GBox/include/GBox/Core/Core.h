#pragma once

#include <memory>

// Platform detection using predefined macros
#ifdef _WIN32
	/* Windows x64/x86 */
	#ifdef _WIN64
		/* Windows x64  */
		#define GBOX_PLATFORM_WINDOWS
	#else
		/* Windows x86 */
		#error "x86 Builds are not supported!"
	#endif
#elif defined(__ANDROID__)						/* We also have to check __ANDROID__ before __linux__.  Since android is based on the linux kernel , and it has __linux__ defined */
	#define GBOX_PLATFORM_ANDROID
	#error "Android is not supported!"
#elif defined(__Linux__)
	#define GBOX_PLATFORM_LINUX
	#error "Linux is not supported!"
#elif defined(__APPLE__) || defined(__MACH__)
	#include <TargetConditionals.h>				// Apple 有很多种形式，我们需要确定对应的平台，并进行对应的定义
	#if TARGET_IPHONE_SIMULATOR == 1
		#error "IOS Simulator is not supported!"
	#elif TARGET_OS_IPHONE == 1
		#define GBOX_PLATFORM_IOS
		#error "IOS is not supported!"
	#elif TARGET_OS_MAC
		#define GBOX_PLATFORM_MACOS
		#error "MacOS is not supported!"
	#else
		#error "Unknown Apple platform!"
	#endif
#else
	#error "Unknown platform!"
#endif

#ifdef GBOX_PLATFORM_WINDOWS
	#ifdef GBOX_BUILD_DLL
		#define GBOX_API __declspec(dllexport)
	#else
		#define GBOX_API __declspec(dllimport)
	#endif
#else
	#error GBOX only supports Windows!
#endif

#ifdef GBOX_DEBUG
	#define GBOX_ENABLE_ASSERTS
#endif

#ifdef GBOX_ENABLE_ASSERTS
	// 断言（如果x表示错误则语句运行，{0}占位的"__VA_ARGS__"代表"..."所输入的语句）
	#define GBOX_CORE_ASSERT(x, ...) \
		{if(!x){\
			GBOX_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);\
			__debugbreak();}\
		}
	#define GBOX_ASSERT(x, ...)\
		{if(!x){\
			GBOX_ERROR("Assertion Failed: {0}", __VA_ARGS__);\
			__debugbreak();}\
		}
#else
	#define GBOX_CORE_ASSERT(x, ...)
	#define GBOX_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)
// 绑定一个成员函数，并占位参数
#define GBOX_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)

namespace GBox {
	template<typename T>
	using Ref = std::shared_ptr<T>;
    // make_shared 的参数是 根据CreateRef所填参数 所动态调整的参数。这些来自CreateRef中的模版参数会被 std::forward 所完美转发
	template<typename T, typename ... Args>
	constexpr Ref<T> CreateRef(Args&& ... args) {
		return std::make_shared<T>( std::forward<Args>(args)... );							
	}

	template<typename T>
	using Scope = std::unique_ptr<T>;
	template<typename T, typename ... Args>
	constexpr Scope<T> CreateScope(Args&& ... args) {
		return std::make_unique<T>( std::forward<Args>(args)... );
	}

}