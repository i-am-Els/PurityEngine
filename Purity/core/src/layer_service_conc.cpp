//
// Created by Eniola Olawale on 06/04/2025.
//

#include "layer_service_conc.h"

using namespace purity::exceptions;

namespace purity
{
    int PLayerService::MAX_SIZE = 32;

    void PLayerService::exit() {
        for (auto& layer : m_layers){
            if (layer == nullptr) continue;
            delete layer;
            layer = nullptr;
        }

    }

    // Return type Layer* can be interpreted as an unsigned int*
    [[maybe_unused]] PLayer *PLayerService::fetchLayerByName(const std::string &name) const
    {
        for (const auto layer : m_layers){
            if (layer != nullptr && static_cast<std::string>(*layer) == name){
                return layer;
            }
        }
        return nullptr;
    }

    PLayerService::PLayerService()
    {
        m_layers.reserve(MAX_SIZE);
        m_layerInsert = m_layers.begin();
    }

    void PLayerService::PushLayer(PLayer* layer)
    {
        if (m_layers.size() == MAX_SIZE)
        {
            throw MaxArraySizeExceededError();
        }
        m_layerInsert = m_layers.emplace(m_layerInsert, layer);
        layer->attached();
    }

    void PLayerService::PushOverlay(PLayer* overlay)
    {
        if (m_layers.size() == MAX_SIZE)
        {
            throw MaxArraySizeExceededError();
        }
        m_layers.emplace_back(overlay);
        overlay->attached();
    }

    void PLayerService::PopLayer(PLayer* layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            layer->detached();
            m_layers.erase(it);
            --m_layerInsert;
        }
    }

    void PLayerService::PopOverlay(PLayer* overlay)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (it != m_layers.end())
        {
            overlay->detached();
            m_layers.erase(it);
        }
    }

    PLayerService::~PLayerService() noexcept {
        PLog::echoMessage("Destroying Layer Manager.");
        PLayerService::exit();
    }

    void PLayerService::preInit(std::any data)
    {
    }

    void PLayerService::postInit()
    {
    }

    void PLayerService::update(float deltaTime)
    {
        for (const auto layer : m_layers){
            if (layer == nullptr) continue;
            layer->update();
        }
    }

    void PLayerService::init() {

    }

    void PLayerService::destroy() {

    }
}
