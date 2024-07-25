#pragma once

#include "GBox/Core/Core.h"
#include "GBox/Core/Layer.h"

#include <vector>

namespace GBox
{

class GBOX_API LayerStack {
public:
    LayerStack() = default;
    ~LayerStack();

    // Layer:   普通层，处于vector的前部分
    // Overlay: 覆盖层，处于vector的后部分。渲染方式从前往后，从而覆盖。_layerInsertIndex为二类别的分界线
    void PushLayer(Layer* layer);
    void PushOverlay(Layer* overlay);
    void PopLayer(Layer* layer);
    void PopOverlay(Layer* layer);
    // 
    std::vector<Layer*>::iterator begin() { return _layers.begin(); }
    std::vector<Layer*>::iterator end() { return _layers.end(); }
    std::vector<Layer*>::const_iterator begin() const { return _layers.begin(); }
    std::vector<Layer*>::const_iterator end() const { return _layers.end(); }
    
    std::vector<Layer*>::reverse_iterator rbegin() { return _layers.rbegin(); }
    std::vector<Layer*>::reverse_iterator rend() { return _layers.rend(); }
    std::vector<Layer*>::const_reverse_iterator rbegin() const { return _layers.rbegin(); }
    std::vector<Layer*>::const_reverse_iterator rend() const { return _layers.rend(); }
public:
    std::vector<Layer*> _layers;
    unsigned int _layerInsertIndex = 0;
};

} // namespace GBox
