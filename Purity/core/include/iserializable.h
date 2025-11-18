//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once
#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>
#include "core_macros.h"
#include "uuid.h"


namespace purity
{
    // if serializable should have an id, then implement identifable alongside this.
    class PURITY_API ISerializable //: public std::enable_shared_from_this<ISerializable>
    {
    public:
        commons::PUUID id;

        ISerializable(): id(commons::PUUID()){}
        explicit ISerializable(const commons::PUUID& existing_id): id(existing_id){}

        PURE_NODISCARD virtual const commons::PUUID& getUUID() const { return id; }

        virtual ~ISerializable() = default;

        virtual void Serialize(cereal::JSONOutputArchive& ar) const = 0;
        virtual void Deserialize(cereal::JSONInputArchive& ar) = 0;
    };
}
