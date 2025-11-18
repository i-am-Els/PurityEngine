//
// Created by Eniola Olawale on 4/30/2024.
//

#pragma once

#include <memory>
#include <vector>

#include "components_behavior.h"
#include "entity_base.h"
#include "mesh.h"
#include "tags.h"
#include "transform_ecs.h"

using namespace purity::artifacts;

namespace purity::ecs {

    // PURITY_CLASS(PEntity) , public PEntityBase, public ManipulativeBehaviour
    class PURITY_API PEntity final : public PEntityBase, public ManipulativeBehaviour, public std::enable_shared_from_this<PEntity>
    {
    public:
        std::shared_ptr<PEntity> getSharedPtr() { return shared_from_this(); }
        std::weak_ptr<PEntity> getWeakPtr() { return weak_from_this(); }
        SERIALIZABLE(PEntity)
        PEntity();
        explicit PEntity(const std::string& name);
        explicit PEntity(PUUID uuid);
//        PEntity(const PEntity& entity);
        ~PEntity() override{
            for (auto comp : m_components) {
                RemoveComponent(comp);
                comp.reset();
            }
            m_components.clear();
            // Deleting weak pointers?
            PLog::echoMessage("Destroying Entity...");
        } // Destructor destroys all components

        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
        // Callbacks
        // OnInit, OnDestroy etc...
    private:
        std::string m_name{};
        friend class PEntityRegistry;
    };

}

