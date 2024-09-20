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

    class PEntity : public PEntityBase, public ManipulativeBehaviour {
    public:
        PEntity();
        explicit PEntity(const std::string& name);
        explicit PEntity(PUUID uuid);
//        PEntity(const PEntity& entity) ;
        ~PEntity() override = default; // Destructor destroys all components

    public:
        PTransformComponent* m_transform;

    private:
        std::string m_name{};
        ETags m_tags{ETags::Default};
        friend class PEntityRegistry;

//        static unsigned int s_count;
    };

}

