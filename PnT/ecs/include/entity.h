//
// Created by Eniola Olawale on 4/30/2024.
//

#pragma once

#include <vector>
#include <memory>

#include "components_behavior.h"
#include "tags.h"
#include "transform_ecs.h"
#include "mesh.h"

using namespace pnt::artifacts;

namespace pnt::ecs {

    class PEntity : public ManipulativeBehaviour {
    public:
        PEntity();
        explicit PEntity(const char* name);
        PEntity(const PEntity& entity);
        ~PEntity() override = default; // Destructor destroys all components

    public:
        std::unique_ptr<PTransformComponent> m_transform;
    private:
        std::string m_name{};
        ETags m_tags;
        unsigned int m_instanceID{};


        std::vector<std::unique_ptr<PComponent>> m_components;
        static unsigned int s_count;
    };
}

