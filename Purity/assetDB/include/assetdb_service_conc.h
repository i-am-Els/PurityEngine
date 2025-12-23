//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "asset_enums.h"
#include "assetdb_service.h"
#include "assetdb_query_specs.h"
#include "assetdb_type_strategy.h"
#include "assets_types.h"
#include "asset_record.h"

using QueryOperation = commons::QueryOperation;

namespace purity::assetDB{

    // TODO - Fill all the Derived Query Spec with their personalized information...
    // TODO - Implement the Specs GetAssetHandle methods...


    class PURITY_API PAssetDatabase final : public AAssetDBService{
    public:
        ~PAssetDatabase() override{
            PLog::echoMessage("Destroying AssetDB.");
        }

        void preInit(std::any& data) override;
        void init() override;
        void postInit() override;

        void destroy() override;

        template<typename T>
        static std::shared_ptr<T> queryDBForAsset(const QuerySpec<T>& spec, QueryOperation operation);

        /*void setupAsset();*/


    private:
        template<typename T>
        PURE_NODISCARD static std::shared_ptr<T> performGetOperation(AssetOperationStrategy<T>& strategy);
        template<typename T>
        PURE_NODISCARD static std::shared_ptr<T> performAddOperation(AssetOperationStrategy<T>& strategy);
        template<typename T>
        PURE_NODISCARD static std::shared_ptr<T> performUpdateOperation(AssetOperationStrategy<T>& strategy);
        template<typename T>
        PURE_NODISCARD static std::shared_ptr<T> performDeleteOperation(AssetOperationStrategy<T>& strategy);
    public:
        void exit() override;

        PNT_TYPE_INDEX_DEF()

    private:
        // Switch on QueryType...
        std::map<PUUID, AssetRecord> m_AssetContainer;
        // std::map<PUUID, std::shared_ptr<PAsset>> m_LoadedAssetContainer;

    };

    template<typename T>
    std::shared_ptr<T> PAssetDatabase::queryDBForAsset(const QuerySpec<T>& spec, QueryOperation operation) {

        AssetOperationStrategy<T> assetStrategy = AssetOperationStrategy<T>(spec);
        switch (operation)
        {
        case QueryOperation::Read:
            return performGetOperation(assetStrategy);
        case QueryOperation::Write:
            return performAddOperation(assetStrategy);
        case QueryOperation::Update:
            return performUpdateOperation(assetStrategy);
        case QueryOperation::Delete:
            return performDeleteOperation(assetStrategy);
        default:
            break;
        }
        return nullptr;
    }

    template<typename T>
    std::shared_ptr<T> PAssetDatabase::performGetOperation(AssetOperationStrategy<T>& strategy)
    {
        return strategy.ReadOperation();
    }

    template<typename T>
    std::shared_ptr<T> PAssetDatabase::performAddOperation(AssetOperationStrategy<T>& strategy)
    {
        auto asset = strategy.WriteOperation();

        // Get Database Instance
        const auto assetDB = PSystemFinder::GetAssetDatabase();
        if (!assetDB) { throw exceptions::NullPointerError("AssetDB is null"); }
        // tell AssetContainers of new addition.
        assetDB->m_AssetContainer[strategy.spec.assetRecord.uuid] = strategy.spec.assetRecord;
        // assetDB->m_LoadedAssetContainer[strategy.spec.assetRecord.uuid] = asset;
        // It is perceived that objects/assets must be created using the create() method which in turn
        // adds created asset to ObjectRegistry.
        // Index file in DB.
        if(!assetDB->m_Database.insertAsset(strategy.spec.assetRecord))
        {
            PLog::echoMessage("Failed to add asset to database.", LogLevel::Error);
            return nullptr;
        }

        return asset;
    }

    template<typename T>
    std::shared_ptr<T> PAssetDatabase::performUpdateOperation(AssetOperationStrategy<T>& strategy)
    {
        return strategy.UpdateOperation();
    }

    template<typename T>
    std::shared_ptr<T> PAssetDatabase::performDeleteOperation(AssetOperationStrategy<T>& strategy)
    {
        return strategy.DeleteOperation();
    }
}



