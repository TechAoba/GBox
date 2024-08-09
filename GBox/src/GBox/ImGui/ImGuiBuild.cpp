#include "gboxpch.h"

//------- Set default OpenGL loader to be gl3w -----
//#if !defined(IMGUI_IMPL_OPENGL_LOADER_GL3W)     \
// && !defined(IMGUI_IMPL_OPENGL_LOADER_GLEW)     \
// && !defined(IMGUI_IMPL_OPENGL_LOADER_GLAD)     \
// && !defined(IMGUI_IMPL_OPENGL_LOADER_CUSTOM)
//#define IMGUI_IMPL_OPENGL_LOADER_GL3W
//#endif
#define IMGUI_IMPL_OPENGL_LOADER_GLAD

#include "backends/imgui_impl_glfw.cpp"
#include "backends/imgui_impl_opengl3.cpp"