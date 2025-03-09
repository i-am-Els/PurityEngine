//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "service_base.h"
#include "handle_base.h"
#include "assetdb_enums.h"
#include "assetdb_service.h"
#include "assetdb_query_specs.h"
#include "assets_types.h"

namespace purity::assetDB{

    // TODO - Fill all the Derived Query Spec with their personalized information...
    // TODO - Implement the Specs GetAssetHandle methods...


    class PURITY_API PAssetDatabase final : public PServiceBase<IAssetDBService>{
    public:
        ~PAssetDatabase() override{
            PLog::echoMessage("Destroying AssetDB.");
        }

        void preInit(std::any data) override;
        void init() override;
        void postInit() override;

        void start() override;

        void process() override;

        void preRender() override;
        void render() override;
        void postsRender() override;

        void update(float deltaTime) override;

        void destroy() override;

        template<typename T>
        static Ref<T> queryDBForAsset(const QuerySpec<T>& spec, QueryOperation operation);

        /*void setupAsset();*/


    private:
        template<typename T>
        [[nodiscard]]static Ref<T> performGetOperation(const QuerySpec<T>& spec);
        template<typename T>
        [[nodiscard]]static Ref<T> performAddOperation(const QuerySpec<T>& spec);
        template<typename T>
        [[nodiscard]]static Ref<T> performUpdateOperation(const QuerySpec<T>& spec);
        template<typename T>
        [[nodiscard]]static Ref<T> performDeleteOperation(const QuerySpec<T>& spec); // handle id is nullptr in this case if deletion succeeded...

        // Switch on QueryType...
        std::map<PUUID, AssetMetadata> m_AssetContainer;
        std::map<PUUID, Ref<PAsset>> m_LoadedAssetContainer;

    };

    template<typename T>
    Ref<T> PAssetDatabase::queryDBForAsset(const QuerySpec<T>& spec, QueryOperation operation) {

        switch (operation)
        {
        case QueryOperation::Read:
            return performGetOperation(spec);
        case QueryOperation::Write:
            return performAddOperation(spec);
        case QueryOperation::Update:
            return performUpdateOperation(spec);
        case QueryOperation::Delete:
            return performDeleteOperation(spec);
        default:
            break;
        }
        return nullptr;
    }

    template<typename T>
    Ref<T> PAssetDatabase::performGetOperation(const QuerySpec<T>& spec)
    {
        return spec.strategy->ReadOperation();
    }

    template<typename T>
    Ref<T> PAssetDatabase::performAddOperation(const QuerySpec<T>& spec)
    {
        return spec.strategy->WriteOperation();
    }

    template<typename T>
    Ref<T> PAssetDatabase::performUpdateOperation(const QuerySpec<T>& spec)
    {
        return spec.strategy->UpdateOperation();
    }

    template<typename T>
    Ref<T> PAssetDatabase::performDeleteOperation(const QuerySpec<T>& spec)
    {
        return spec.strategy->DeleteOperation();
    }
}



