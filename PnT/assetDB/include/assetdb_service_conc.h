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

namespace pnt::assetDB{

    // TODO - Fill all the Derived Query Spec with their personalized information...
    // TODO - Implement the Specs GetAssetHandle methods...


    struct PNT_API PAssetDBQuery{
        PAssetDBQuery(const QuerySpec& spec, QueryOperation operation)
            : spec(spec),
              operation(operation)
        {
        }

        QuerySpec spec;
        QueryOperation operation;
    };

    class PNT_API PAssetDatabase final : public PServiceBase<IAssetDBService>{
    public:
        ~PAssetDatabase() override{
            PLog::echoMessage("Destroying AssetDB.");
        }

        void init() override;

        void start();

        void process();

        void render();

        void update(float deltaTime);

        void destroy() override;

        static PHandleBase* queryDBForAsset(const PAssetDBQuery& assetDBQuery);

        void setupAsset();


    private:
        [[nodiscard]]static PHandleBase* performGetOperation(const QuerySpec& spec);
        [[nodiscard]]static PHandleBase* performAddOperation(const QuerySpec& spec);
        [[nodiscard]]static PHandleBase* performUpdateOperation(const QuerySpec& spec);
        [[nodiscard]]static PHandleBase* performDeleteOperation(const QuerySpec& spec); // handle id is nullptr in this case if deletion succeeded...

        // Switch on QueryType...
        std::map<PUUID, PAsset*> m_AssetContainer;

    };
}



