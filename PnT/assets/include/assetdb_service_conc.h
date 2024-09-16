//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "service_base.h"
#include "handle_base.h"
#include "assetdb_enums.h"
#include "assetdb_service.h"
#include "assetdb_query_specs.h"

namespace pnt::assetDB{

    // TODO - Fill all the Derived Query Spec with their personalized information...
    // TODO - Implement the Specs GetAssetHandle methods...


    struct PAssetDBQuery{
        PAssetDBQuery(const QuerySpec& spec, QueryOperation operation)
            : spec(spec),
              operation(operation)
        {
        }


        QuerySpec spec;
        QueryOperation operation;
    };

    class PAssetDatabase final : public PServiceBase<IAssetDBService>{
    public:
        ~PAssetDatabase() override = default;

        void init() override;

        void start() override;

        void process() override;

        void render() override;

        void update(float deltaTime) override;

        void destroy() override;

        static PHandleBase* queryDBForAsset(const PAssetDBQuery& assetDBQuery);


    private:
        static PHandleBase* performGetOperarion(const QuerySpec& spec);
        static PHandleBase* performAddOperarion(const QuerySpec& spec);
        static PHandleBase* performUpdateOperarion(const QuerySpec& spec);
        static PHandleBase* performDeleteOperarion(const QuerySpec& spec); // handle id is nullptr in this case if deletion suceeded...
        // Switch on QueryType...

    };
}



