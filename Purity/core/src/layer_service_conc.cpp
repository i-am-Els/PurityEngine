//
// Created by Eniola Olawale on 06/04/2025.
//

#include "layer_service_conc.h"
#include "scene_layer.h"

using namespace purity::exceptions;

namespace purity
{
    int PLayerService::START_SIZE = 32;

    void PLayerService::exit() {
        for (auto& layer : m_layers){
            if (layer == nullptr) continue;
            delete layer;
            layer = nullptr;
        }
        m_layers.clear();
        m_layerMap.clear();
    }

    PLayer* PLayerService::getLayerByPUUID(const PUUID& id)
    {
        const auto it = m_layerMap.find(id);
        return it != m_layerMap.end() ? it->second : nullptr;
    }

    // Return type Layer* can be interpreted as an unsigned int*
    PURE_MAYBE_UNUSED PLayer *PLayerService::fetchLayerByName(const std::string &name) const
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
        m_layers.reserve(START_SIZE);
    }

    PUUID PLayerService::PushLayer(PLayer* layer)
    {
        const auto first_overlay_it = std::find_if(begin(), end(), [](PLayer* item)
        {
            return item->isOverlay();
        });
        m_layers.emplace(first_overlay_it, layer);
        PUUID id = layer->getID();
        m_layerMap[id] = layer;
        layer->attached();
        return id;
    }

    PUUID PLayerService::PushOverlay(PLayer* overlay)
    {
        m_layers.emplace_back(overlay);
        PUUID id = overlay->getID();
        m_layerMap[id] = overlay;
        overlay->attached();
        return id;
    }

    void PLayerService::PopLayer(PLayer* layer)
    {
        if (const auto it = std::ranges::find(m_layers, layer); it != m_layers.end())
        {
            const PUUID id = layer->getID();
            layer->detached();
            m_layerMap.erase(id);
            delete *it;
            m_layers.erase(it);
        }
    }

    void PLayerService::PopOverlay(PLayer* overlay)
    {
        PopLayer(overlay);
    }


    PLayerService::~PLayerService() noexcept {
        PLog::echoMessage("Destroying Layer Manager.");
        PLayerService::exit();
    }

    void PLayerService::preInit(const std::any& data)
    {
    }

    void PLayerService::postInit()
    {
        // TODO : Have your Scene Layer initialize the Project default scene.

        // dynamic_cast<scene::SceneLayer*>(getLayerByPUUID(m_sceneLayerID))->switchScene();
    }

    void PLayerService::update(float deltaTime)
    {
        for (const auto layer : m_layers){
            if (layer == nullptr) continue;
            layer->update();
        }
    }

    void PLayerService::preRender()
    {
    }

    void PLayerService::render()
    {
        for (const auto layer : m_layers){
            if (layer == nullptr) continue;
            layer->render();
        }
    }

    void PLayerService::postRender()
    {
    }

    void PLayerService::init()
    {
        m_sceneLayerID = PushLayer(new scene::SceneLayer(purity::artifacts::builtInLayerNames["scene"]));
    }

    void PLayerService::destroy() {

    }
}
