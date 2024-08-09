#pragma once

namespace GBox
{
// ---- An Interface for rendering context ----
class GBOX_API GraphicsContext {
public:
    virtual void Init() = 0;
    virtual void SwapBuffers() = 0;
    
};

} // namespace GBox
