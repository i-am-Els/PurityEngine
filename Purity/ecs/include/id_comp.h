//
// Created by Eniola Olawale on 9/17/2024.
//

#pragma once

#include "component.h"
#include "uuid.h"


namespace purity{
    namespace scene{
        class PScene;
    }

    namespace  ecs{
        class PIDManager;

        class PURITY_API PIDComponent final: public PComponent, public std::enable_shared_from_this<PIDComponent>{
            friend class purity::scene::PScene;
        public:
            explicit PIDComponent(std::weak_ptr<PEntity> entity);

            PIDComponent(std::weak_ptr<PEntity> entity, PUUID id);

            ~PIDComponent() override { PLog::echoMessage("Destroying ID Component"); };

            void update(float deltaTime) override;

            void start() override;

            explicit operator PUUID() const  { return m_entityInstanceID; }

            P_GET_COMPONENT_TYPE(PComponentType::PIDComponent)

        private:
            PUUID m_entityInstanceID{0};
            void setID(PUUID id);

        public:
            void Serialize(cereal::JSONOutputArchive& ar) const override;
            void Deserialize(cereal::JSONInputArchive& ar) override;

        private:
            // All components must have this comm

            friend class PIDManager;
        };

    }
}