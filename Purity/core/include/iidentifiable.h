//
// Created by Eniola Olawale on 14/10/2025.
//
#pragma once
#include "uuid.h"


namespace purity::assetDB
{
    // if serializable should have an id, then implement identifable alongside this.
    class PURITY_API IIdentifiable //: public std::enable_shared_from_this<ISerializable>
    {/// TODO: We expect that serialisables should be created by the create() function call
    public:

        IIdentifiable() = default;

        virtual ~IIdentifiable() = default;
        PUUID getUUID() const { return m_id; }
    protected:
        PUUID m_id;
    };
}
