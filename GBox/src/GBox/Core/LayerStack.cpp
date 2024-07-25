#include "gboxpch.h"
#include "GBox/Core/LayerStack.h"

namespace GBox
{

LayerStack::~LayerStack() {
    for (Layer* layer : _layers) {
        layer->OnDetach();
        delete layer;
    }
}

void LayerStack::PushLayer(Layer* layer) {
   _layers.emplace(_layers.begin() + _layerInsertIndex, layer);
   _layerInsertIndex++;
}

void LayerStack::PopLayer(Layer* layer) {
    auto iter = std::find(_layers.begin(), _layers.begin() + _layerInsertIndex, layer);
    if (iter != _layers.begin() + _layerInsertIndex) {
        layer->OnDetach();
        _layers.erase(iter);
        _layerInsertIndex--;
    }
}

void LayerStack::PushOverlay(Layer* overlay) {
    _layers.emplace_back(overlay);
}

void LayerStack::PopOverlay(Layer* overlay) {
    auto iter = std::find(_layers.begin() + _layerInsertIndex, _layers.end(), overlay);
    if (iter != _layers.end()) {
        overlay->OnDetach();
        _layers.erase(iter);
    }
}

} // namespace GBox
