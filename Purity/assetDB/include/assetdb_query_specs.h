//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "core_macros.h"
#include "asset_enums.h"
#include "assets_types.h"

using AssetType = commons::AssetType;


namespace purity::assetDB
{
    // Base Spec
    template<class AssetTypeRef>
    class PURITY_API QuerySpec
    {
        friend class PAssetDatabase;
    public:
        explicit QuerySpec(const AssetRecord& record) : assetRecord(record)
        {
            m_type = record.assetType;
        }

        PURE_NODISCARD virtual AssetType getAssetType() const
        {
            return m_type;
        }


        virtual ~QuerySpec()
        {
            PLog::echoMessage("Destroying query spec.");
        }

        AssetRecord assetRecord;

    private:
        AssetType m_type;
    }; // BaseClass for the different AssetType
}
