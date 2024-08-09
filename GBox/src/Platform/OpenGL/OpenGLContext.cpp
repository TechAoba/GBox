#include "gboxpch.h"
#include "Platform/OpenGL/OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>	    // ---- glad is OpenGL specific ----

namespace GBox
{
OpenGLContext::OpenGLContext(GLFWwindow* windowHandle) : _windowHandle(windowHandle)
{
    GBOX_CORE_ASSERT(windowHandle, "Window handle is null ! ( But it shouldn't be )")
}

void OpenGLContext::Init() {
    
    glfwMakeContextCurrent(_windowHandle);
    int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    GBOX_CORE_ASSERT(status, "Failed to initialize Glad!");
}

void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(_windowHandle);
}

} // namespace GBox
