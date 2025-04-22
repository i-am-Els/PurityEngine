//
// Created by Eniola Olawale on 06/04/2025.
//

#pragma once
#include "layer.h"
using namespace purity;

namespace editor
{
    class PEditorApplication;

    namespace gui {

        // ===============================================================================================
        // ======================================= START OF ImGuiLayer =====================================


        class ImGuiLayer : public PLayer{
        public:
            void update() override;
            void attached() override;
            void detached() override;
            void eventFired(Event& event) override;

        private:
            float m_time = 0.0f;
            friend class PLayerService;
            friend class PEditorApplication;
        protected:
            explicit ImGuiLayer(const std::string& name);
        public:
            ImGuiLayer() = delete;
            ~ImGuiLayer() override;

        };
        // ======================================== END OF ImGuiLayer ========================================
        // =================================================================================================

    } // purity
}
