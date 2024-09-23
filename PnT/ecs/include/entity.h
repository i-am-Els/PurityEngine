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

using namespace pnt::artifacts;

namespace pnt::ecs {

    class PNT_API PEntity : public PEntityBase, public ManipulativeBehaviour {
    public:
        PEntity();
        explicit PEntity(const std::string& name);
        explicit PEntity(PUUID uuid);
//        PEntity(const PEntity& entity);
        ~PEntity() override{
            PLog::echoMessage("Destroying Entity...");
        } // Destructor destroys all components

        [[nodiscard]] inline PUUID getInstanceID(){
            return m_instanceID;
        }

    private:
        std::string m_name{};
        ETags m_tags{ETags::Default};
        friend class PEntityRegistry;
    };

}

