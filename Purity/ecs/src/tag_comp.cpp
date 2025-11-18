//
// Created by Eniola Olawale on 9/17/2024.
//

#include "tag_comp.h"

namespace purity::ecs{
    PTagComponent::PTagComponent(std::weak_ptr<PEntity> entity) : PComponent(entity) {

    }


    void PTagComponent::update(float deltaTime) {

    }

    void PTagComponent::start(){

    }

    void PTagComponent::Serialize(cereal::JSONOutputArchive& ar) const
    {
    }

    void PTagComponent::Deserialize(cereal::JSONInputArchive& ar)
    {
    }
}
