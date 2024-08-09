#pragma once
#include "GBox/Renderer/GraphicsContext.h"

struct GLFWwindow;      // Avoid reporting errors & Don't need include GLFW header file

namespace GBox
{
    
class GBOX_API OpenGLContext : public GraphicsContext {
public:
    OpenGLContext(GLFWwindow* windowHandle);

    void Init() override;
    void SwapBuffers() override;
private:
    GLFWwindow* _windowHandle;
};

} // namespace GBox
