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

    GBOX_CORE_INFO("OpenGL info: ");
    GBOX_CORE_INFO("Vendor: {0}",	(const char*)glGetString(GL_VENDOR));
    GBOX_CORE_INFO("Renderer: {0}", (const char*)glGetString(GL_RENDERER));
    GBOX_CORE_INFO("Version: {0}",	(const char*)glGetString(GL_VERSION));
}

void OpenGLContext::SwapBuffers() {
    glfwSwapBuffers(_windowHandle);
}

} // namespace GBox
