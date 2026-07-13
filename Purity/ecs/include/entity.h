//
// Created by Eniola Olawale on 4/30/2024.
//

#pragma once

#include <memory>
#include <vector>

#include "mesh.h"
#include "tags.h"
#include "transform_ecs.h"
#include "entity_index.h"

using namespace purity::artifacts;

namespace purity::ecs {
   
    // PURITY_CLASS(PEntity) , public PEntityBase, public ManipulativeBehaviour
    class PURITY_API PEntity final : public ISerializable, public std::enable_shared_from_this<PEntity>
    {
    public:
        PUUID getUUID() const { return m_id; }

        std::shared_ptr<PEntity> getSharedPtr() { return shared_from_this(); }
        std::weak_ptr<PEntity> getWeakPtr() { return weak_from_this(); }
        PEntity();
        explicit PEntity(const std::string& name, PUUID uuid);
        explicit PEntity(PUUID uuid);
//        PEntity(const PEntity& entity);
        ~PEntity() override{
            PLog::echoMessage(LogLevel::Info, "Destroying Entity - %s", PUUID::to_string(m_id).c_str());
        } // Destructor destroys all components

        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
        // Callbacks
        // OnInit, OnDestroy etc...
        std::string m_name{};

        PURE_INLINE void setIndex(PEntityIndex index) { m_index = index; }
        PURE_INLINE void setParent(PEntityIndex parentIndex) { m_parentIndex = parentIndex; }
    private:
        PUUID m_id;
        PEntityIndex m_index;
        PEntityIndex m_parentIndex;
        std::vector<PEntityIndex> childrenIndices;
        friend class PEntityRegistry;
        friend class PEntityHandle;
    };

}

