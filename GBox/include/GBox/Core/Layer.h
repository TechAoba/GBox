#pragma once

#include "GBox/Core/Core.h"
#include "GBox/Events/Event.h"
#include "GBox/Core/TimeStep.h"

namespace GBox {

class GBOX_API Layer {
public:
    Layer(const std::string& name = "Layer");
    virtual ~Layer() = default;
    
    virtual void OnAttach() {}
    virtual void OnDetach() {}
    virtual void OnUpdate(TimeStep ts) {}
    virtual void OnImGuiRender() {}
    virtual void OnEvent(Event& event) {}
    
    inline const std::string& GetName() const { return _debugName; }
protected:
    std::string _debugName;
};

} // namespace GBox
