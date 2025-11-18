//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "component.h"
#include "tags.h"

namespace purity::ecs{
    class PURITY_API PTagComponent final : public PComponent, public std::enable_shared_from_this<PTagComponent>{
    public:
        explicit PTagComponent(std::weak_ptr<PEntity> entity);
        ~PTagComponent() override { PLog::echoMessage("Destroying Tag Component"); };

        void update(float deltaTime) override;

        void start() override;

        P_GET_COMPONENT_TYPE(PComponentType::PTagComponent)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;

        artifacts::ETags tag;
    };
}
