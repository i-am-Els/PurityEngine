//
// Created by Eniola Olawale on 4/30/2024.
//

#pragma once

#include <vector>
#include <memory>

#include "components_behavior.h"
#include "tags.h"
#include "entity_base.h"
#include "transform_ecs.h"
#include "mesh.h"

using namespace purity::artifacts;

namespace purity::ecs {

    class PURITY_API PEntity : public PEntityBase, public ManipulativeBehaviour {
    public:
        PEntity();
        explicit PEntity(const std::string& name);
        explicit PEntity(PUUID uuid);
//        PEntity(const PEntity& entity);
        ~PEntity() override{
            for (auto comp : m_components) {
                RemoveComponent(comp);
            }
            PLog::echoMessage("Destroying Entity...");
        } // Destructor destroys all components

        PURE_NODISCARD inline PUUID getInstanceID(){
            return m_instanceID;
        }

        // Callbacks
        // OnInit, OnDestroy etc...
    private:
        std::string m_name{};
        friend class PEntityRegistry;
    };

}

