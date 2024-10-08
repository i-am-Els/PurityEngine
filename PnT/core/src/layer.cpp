//
// Created by Eniola Olawale on 3/10/2024.
//

#include "layer.h"

using namespace pnt::exceptions;

namespace pnt {

    const unsigned int PLayerService::BASE_LAYER_COUNT = 8;
    const unsigned int PLayerService::MAX_LAYER;

    // =============================================================================================================
    // =============================================================================================================
    // ================================================= LAYER =====================================================
    // =============================================================================================================
    // =============================================================================================================

    void PLayerService::PLayer::update() {
        if (onUpdateCallback != nullptr) onUpdateCallback();
        else throw NullCallbackError();
    }

    void PLayerService::PLayer::attached() {
        if (onAttachedCallback != nullptr) onAttachedCallback();
        else throw NullCallbackError();
    }

    void PLayerService::PLayer::detached() {
        if (onDetachedCallback != nullptr) onDetachedCallback();
        else throw NullCallbackError();
    }

    void PLayerService::PLayer::eventFired(Event &event) {
        if (onEventCallback != nullptr) onEventCallback(event);
        else throw NullCallbackError();
    }

    [[maybe_unused]] void PLayerService::PLayer::setAttachedCallback(PLayerService::PLayer::CallbackFn callback) {
        onAttachedCallback = std::move(callback);
    }

    [[maybe_unused]] void PLayerService::PLayer::setDetachedCallback(PLayerService::PLayer::CallbackFn callback) {
        onDetachedCallback = std::move(callback);
    }

    [[maybe_unused]] void PLayerService::PLayer::setUpdateCallback(PLayerService::PLayer::CallbackFn callback) {
        onUpdateCallback = std::move(callback);
    }

    [[maybe_unused]] void PLayerService::PLayer::setEventFireCallback(PLayerService::PLayer::CallbackFnWithEventArg1 callback) {
        onEventCallback = std::move(callback);
    }

    PLayerService::PLayer::PLayer(const PLayerService::PLayer &layer) : m_id (layer.m_id), m_name(layer.m_name), m_enabled(layer.isEnabled()){
    }

    PLayerService::PLayer::PLayer(unsigned int id, const std::string& name) : m_id (id), m_name(name), m_enabled(true){

    }

    // =============================================================================================================
    // =============================================================================================================
    // ================================================== OverLay ==================================================
    // =============================================================================================================
    // =============================================================================================================


    PLayerService::ImGuiLayer::ImGuiLayer(unsigned int id, const std::string &name) : PLayer(id, name){
    }

    // =============================================================================================================
    // =============================================================================================================
    // =============================================== LAYER MANAGER ===============================================
    // =============================================================================================================
    // =============================================================================================================

    void PLayerService::terminate() {
        for (auto& layer : layerStack){
            if (layer == nullptr) continue;
            delete layer;
            layer = nullptr;
        }

    }

    // Return type Layer* can be interpreted as an unsigned int*
    [[maybe_unused]] PLayerService::PLayer *PLayerService::fetchLayerByID(unsigned int id) {
        if (id >= MAX_LAYER) return nullptr;
        return layerStack[id];
    }

    // Return type Layer* can be interpreted as an unsigned int*
    [[maybe_unused]] PLayerService::PLayer *PLayerService::fetchLayerByName(const std::string &name) {
        for (auto layer : layerStack){
            if (layer != nullptr && layer->m_name == name){
                return layer;
            }
        }
        return nullptr;
    }

    [[maybe_unused]] bool PLayerService::s_IsReservedLayer(unsigned int layerIndex) {
        return layerIndex < BASE_LAYER_COUNT; // Assuming the first 6 layers are system reserved
    }

    PLayerService::~PLayerService() noexcept {
        PLog::echoMessage("Destroying Layer Manager.");
        PLayerService::terminate();
    }

    /// @brief Creates a Layer and adds it to the Layer Holding Container.
    /// @return int - it signifies the Layer's ID and Index in the holding container.
    /// @note Method returns -1 only if the maxLayerCount is reached
    [[maybe_unused]]unsigned int PLayerService::s_CreateLayer(unsigned int id, const std::string& name, ELayerType layerType) {
        if (id >= MAX_LAYER) {
//            throw std::runtime_error("Maximum number of layers reached.");
            return (int)IndexOutOfBoundsError(); // TODO Error code will be substituted for this Later
        }

        if (layerStack[id] != nullptr) return (int)NullPointerError();

        MakeLayer(layerType, id, name);

        return id;
    }

    [[maybe_unused]] bool PLayerService::deleteLayer(unsigned int id) {
        if (layerStack[id] == nullptr || id >= MAX_LAYER) return false;
        if (id < BASE_LAYER_COUNT) return false;

        delete layerStack[id];
        layerStack[id] = nullptr;
        return true;
    }

    void PLayerService::MakeLayer(ELayerType layerType, unsigned int id, const std::string& name)
    {
        switch (layerType) {
            case ELayerType::Layer:
                layerStack[id] = new PLayer(id, name);
                break;
            case ELayerType::OverlayLayer:
                layerStack[id] = new ImGuiLayer(id, name);
                break;
            default:
                break;
        }
    }

    void PLayerService::init() {

    }

    void PLayerService::destroy() {

    }

} // pnt