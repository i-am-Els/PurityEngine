//
// Created by Eniola Olawale on 3/10/2024.
//

#include "layer.h"

#include <utility>

namespace pnt {
    const unsigned int PLayerService::MAX_LAYER;
    const unsigned int PLayerService::BASE_LAYER_COUNT = 8;

    // =============================================================================================================
    // =============================================================================================================
    // ================================================= LAYER =====================================================
    // =============================================================================================================
    // =============================================================================================================

    void PLayerService::PLayer::update() {
        if (onUpdateCallback != nullptr) onUpdateCallback();
    }

    void PLayerService::PLayer::attached() {
        if (onAttachedCallback != nullptr) onAttachedCallback();
    }

    void PLayerService::PLayer::detached() {
        if (onDetachedCallback != nullptr) onDetachedCallback();
    }

    void PLayerService::PLayer::eventFired(Event &event) {
        if (onEventCallback != nullptr) onEventCallback(event);
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
        for (auto layer : layerStack){
            if (layer == nullptr) continue;
            delete layer;
        }
        std::cout << "Layer Manager Defeated" << std::endl;
    }

//    [[maybe_unused]] LayerManager &LayerManager::s_GetInstance() {
//        static LayerManager s_Instance;
//        return s_Instance;
//    }

    // Return type Layer* can be interpreted as an unsigned int*
    [[maybe_unused]] PLayerService::PLayer *PLayerService::fetchLayerByID(unsigned int id) {
        if (id > MAX_LAYER) return nullptr;
        return layerStack[id];
    }

    // Return type Layer* can be interpreted as an unsigned int*
    [[maybe_unused]] PLayerService::PLayer *PLayerService::fetchLayerByName(const std::string &name) {
        for (auto layer : layerStack){
            if (layer->m_name == name){
                return layer;
            }
        }
        return nullptr;
    }

    [[maybe_unused]] bool PLayerService::s_IsReservedLayer(unsigned int layerIndex) {
        return layerIndex < BASE_LAYER_COUNT; // Assuming the first 6 layers are system reserved
    }

    PLayerService::~PLayerService() noexcept {
        PLayerService::terminate();
    }

    /// @brief Creates a Layer and adds it to the Layer Holding Container.
    /// @return int - it signifies the Layer's ID and Index in the holding container.
    /// @note Method returns -1 only if the maxLayerCount is reached
    [[maybe_unused]] int PLayerService::s_CreateLayer(unsigned int id, const std::string& name, ELayerType layerType) {
        if (id >= MAX_LAYER) {
//            throw std::runtime_error("Maximum number of layers reached.");
            return -1; // TODO Error code will be substituted for this Later
        }

        if (layerStack[id] != nullptr) return -1;

        std::unique_ptr<PLayer> layer = PLayerService::s_MakeLayer(layerType, id, name);

        try {
            pushToStack(layer.get());
            // Ownership is transferred to layerStack, so release the smart pointer
            layer.release();
            return (int)id;
        } catch (...) {
            // Clean up in case of an exception
            delete layer.get();
            return -1;
//            throw; // Re-throw the exception
        }
    }

    [[maybe_unused]] bool PLayerService::deleteLayer(unsigned int id) {
        if (layerStack[id] != nullptr) return PLayerService::popFromStack(layerStack[id]);
        if (id < BASE_LAYER_COUNT) { return false; }
        return true;
    }

    void PLayerService::pushToStack(PLayer *layer) {
        layerStack[*layer] = layer;
    }

    bool PLayerService::popFromStack(PLayer *layer) {
        if (*layer < BASE_LAYER_COUNT) return false;
        layerStack[*layer] = nullptr;
        delete layer;
        return true;
    }

    std::unique_ptr<PLayerService::PLayer> PLayerService::s_MakeLayer(ELayerType layerType, unsigned int id, const std::string& name) {
        std::unique_ptr<PLayerService::PLayer> layer;
        switch (layerType) {
            case ELayerType::Layer:
                layer = std::unique_ptr<PLayer>(new PLayer(id, name));
                break;
            case ELayerType::ImGuiLayer:
                layer = std::unique_ptr<ImGuiLayer>(new ImGuiLayer(id, name));
                break;
        }
        return layer;
    }

    void PLayerService::init() {

    }

    void PLayerService::destroy() {

    }

} // pnt