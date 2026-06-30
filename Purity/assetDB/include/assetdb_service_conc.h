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

        PURE_NODISCARD AssetRecord getAssetRecordFromRelPath(const std::string& relPath) const;

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

        static void RegisterProjectUpdate(const purity::PApplication::ProjectEditorInfo& editorInfo);
    private:
        // Switch on QueryType...
        std::unordered_map<PUUID, AssetRecord> m_AssetContainer;
        ObjectRegistry* registry = ObjectRegistry::GetObjectRegistry();
        // std::unordered_map<PUUID, std::shared_ptr<PAsset>> m_LoadedAssetContainer; // Substitute for Object Registry


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
        std::shared_ptr<T> asset;
        /// if asset id is found get the asset tied to it.
        /// else if it is not found return nullptr
        try
        {
            if (!strategy.spec.assetRecord) {
                throw exceptions::NullPointerError("This is an invalid object");
            }

            // Get Database Instance
            const auto assetDB = PSystemFinder::GetAssetDatabase();
            if (!assetDB) { throw exceptions::NullPointerError("AssetDB is null"); }

            if (!assetDB->m_AssetContainer.contains(strategy.spec.assetRecord.uuid)) {
                PLog::echoMessage("The queried asset is not found in the runtime asset container, checking the database...", commons::LogLevel::Warning);

                auto assetRecordOpt = assetDB->m_Database.readAssetByUUID(strategy.spec.assetRecord.uuid);
                if (assetRecordOpt.has_value()) {
                    assetDB->m_AssetContainer[strategy.spec.assetRecord.uuid] = assetRecordOpt.value();
                    strategy.spec.assetRecord = assetRecordOpt.value();
                }
            }

            if (!assetDB->m_AssetContainer[strategy.spec.assetRecord.uuid]) { throw exceptions::NullPointerError("AssetRecord is invalid object"); }

            // get the asset obj
            asset = strategy.ReadOperation();
            if (asset == nullptr) { throw exceptions::NullPointerError("The queried asset returns null"); }
        }
        catch (const std::exception& e) {
            PLog::echoMessage(e.what(), commons::LogLevel::Error);
            return nullptr;
        }

        return asset;
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

    inline void PAssetDatabase::RegisterProjectUpdate(const purity::PApplication::ProjectEditorInfo& editorInfo)
    {
        auto project_rel_path = commons::to_project_relative(editorInfo.projectFilePath, editorInfo.projectDir);
        if (!project_rel_path.has_value()) {
            throw exceptions::EmptyPathString();
        }
        auto project_record = PSystemFinder::GetAssetDatabase()->getAssetRecordFromRelPath(project_rel_path.value().string());
        assetDB::PAssetDatabase::queryDBForAsset(QuerySpec<PProjectAsset>(project_record, editorInfo.startUpSceneRelPath), QueryOperation::Update);
    }
}



