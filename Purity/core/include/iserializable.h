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
    {/// TODO: We expect that serialisables should be created by the create() function call
    public:
        //commons::PUUID id;

        ISerializable() = default;

        virtual ~ISerializable() = default;

        virtual commons::PUUID getUUID() const = 0;

        virtual void Serialize(cereal::JSONOutputArchive& ar) const = 0;
        virtual void Deserialize(cereal::JSONInputArchive& ar) = 0;
    };
}
