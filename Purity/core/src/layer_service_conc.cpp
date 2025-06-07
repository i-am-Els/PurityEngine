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

    PLayer* PLayerService::getLayerByPUUID(const PUUID& id)
    {
        const auto it = m_layerMap.find(id);
        return it != m_layerMap.end() ? it->second : nullptr;
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

    PUUID PLayerService::PushLayer(PLayer* layer)
    {
        if (m_layers.size() == MAX_SIZE)
        {
            throw MaxArraySizeExceededError();
        }
        m_layerInsert = m_layers.emplace(m_layerInsert, layer);
        PUUID id = layer->getID();
        m_layerMap[id] = layer;
        layer->attached();
        return id;
    }

    PUUID PLayerService::PushOverlay(PLayer* overlay)
    {
        if (m_layers.size() == MAX_SIZE)
        {
            throw MaxArraySizeExceededError();
        }
        m_layers.emplace_back(overlay);
        PUUID id = overlay->getID();
        m_layerMap[id] = overlay;
        overlay->attached();
        return id;
    }

    void PLayerService::PopLayer(PLayer* layer)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), layer);
        if (it != m_layers.end())
        {
            PUUID id = layer->getID();
            layer->detached();
            m_layerMap.erase(id);
            m_layers.erase(it);
            --m_layerInsert;
        }
    }

    void PLayerService::PopOverlay(PLayer* overlay)
    {
        auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
        if (it != m_layers.end())
        {
            PUUID id = overlay->getID();
            overlay->detached();
            m_layerMap.erase(id);
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
