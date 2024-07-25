#pragma once

#include "Core.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/ostr.h>

namespace GBox {

class GBOX_API Log {
private:
    static Ref<spdlog::logger> s_CoreLogger;
    static Ref<spdlog::logger> s_ClientLogger;

public:
    static void Init();
    inline static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
    inline static Ref<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
};

}

//core log macros
#define GBOX_CORE_TRACE(...)\
	::GBox::Log::GetCoreLogger()->trace(__VA_ARGS__);	//????why before the GBox needs "::",it seems doesn't matter just now( at Episode 6 )：表示在全局中调用这个GetCoreLogger
#define GBOX_CORE_INFO(...)\
	::GBox::Log::GetCoreLogger()->info(__VA_ARGS__);		//(...)表示宏函数可以接受任意个参数
#define GBOX_CORE_WARN(...)\
	::GBox::Log::GetCoreLogger()->warn(__VA_ARGS__);		//__VA_ARGS__是一个预定义的宏（前后的双下划线表示这是一个预定义的），可以用来动态的接收的未知个参数。
#define GBOX_CORE_ERROR(...)\
	::GBox::Log::GetCoreLogger()->error(__VA_ARGS__);
#define GBOX_CORE_CRITICAL(...)\
	::GBox::Log::GetCoreLogger()->critical(__VA_ARGS__);

//client log macros
#define GBOX_TRACE(...)\
	::GBox::Log::GetClientLogger()->trace(__VA_ARGS__);
#define GBOX_INFO(...)\
	::GBox::Log::GetClientLogger()->info(__VA_ARGS__);
#define GBOX_WARN(...)\
	::GBox::Log::GetClientLogger()->warn(__VA_ARGS__);
#define GBOX_ERROR(...)\
	::GBox::Log::GetClientLogger()->error(__VA_ARGS__);
#define GBOX_CRITICAL(...)\
	::GBox::Log::GetClientLogger()->critical(__VA_ARGS__);

