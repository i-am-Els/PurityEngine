//
// Created by Eniola Olawale on 06/04/2025.
//

#pragma once
#include "purity_core_pch.h"

#include "layer.h"
#include "layer_service.h"

namespace purity
{
    class PURITY_API PLayerService final : public ALayerService{
        friend class PApplication;
        // ==================================================================================================
        // ====================================== START OF LAYER CLASS ======================================
        // ==================================================================================================
    public:

        PNT_TYPE_INDEX_DEF()
        PLayerService();
        ~PLayerService() noexcept override;

        // ================================== LAYER MANAGER CLASS DETAILS ================================

        [[maybe_unused]] PURE_NODISCARD PLayer* fetchLayerByName(const std::string &name) const;

        PUUID PushLayer(PLayer* layer);
        PUUID PushOverlay(PLayer* overlay);
        void PopLayer(PLayer* layer);
        void PopOverlay(PLayer* overlay);

        void preInit(const std::any& data) override;
        void init() override;
        void postInit() override;
        void update(float deltaTime) override;
        void preRender() override;
        void render() override;
        void postRender() override;
        void destroy() override;
        void exit() override;

        PLayer* getLayerByPUUID(const PUUID& id) override;

        std::vector<PLayer*>::iterator begin() { return m_layers.begin(); }
        std::vector<PLayer*>::iterator end() { return m_layers.end(); }

    private:
        /// Use this as interface
        std::vector<PLayer*> m_layers;
        std::unordered_map<PUUID, PLayer*> m_layerMap;

        static int START_SIZE;

        PUUID m_sceneLayerID;
    };
}


