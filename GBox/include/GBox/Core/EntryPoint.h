#pragma once

#include "GBox/Core/Application.h"
#include "GBox/Core/Core.h"
#include "GBox/Core/Log.h"
#include <iostream>

#ifdef GBOX_PLATFORM_WINDOWS

extern GBox::Application* GBox::CreateApplication();

// 将其设置为windows平台上的win main函数，可能会要求其返回一些状态信息（Handled）
int main(int argc, char** argv) {
	GBox::Log::Init();
	GBOX_CORE_WARN("Initialized Log!");
	int a = 100;
	GBOX_INFO("Goodbye World! a = {0}", a);

	// GBOX_PROFILE_BEGIN_SESSION("Startup", "GBOXProfile-Startup.json");
	// auto app = GBOX::CreateApplication();
	// GBOX_PROFILE_END_SESSION();

	// GBOX_PROFILE_BEGIN_SESSION("Runtime", "GBOXProfile-Runtime.json");
	// app->Run();
	// GBOX_PROFILE_END_SESSION();

	// GBOX_PROFILE_BEGIN_SESSION("Shutdown", "GBOXProfile-Shutdown.json");
	// delete app;
	// GBOX_PROFILE_END_SESSION();
	auto app = GBox::CreateApplication();
	app->Run();
	delete app;
	
	return 0;
}

#endif