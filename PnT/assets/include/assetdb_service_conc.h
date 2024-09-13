//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include <service_base.h>
#include <handle_base.h>
#include <pobject.h>
#include "assetdb_service.h"

namespace pnt{
    enum class QueryType{
        LoadFile,
        WriteFile,
        WriteBinary,
        LoadBinary
    }; // These are placeholders

    struct PAssetDBQuery{
        PObject* invoker;
        QueryType query;
    };

    class PAssetDatabase : public PServiceBase<IAssetDBService>{
    public:
        ~PAssetDatabase() override = default;

        void init() override;

        void start() override;

        void process() override;

        void render() override;

        void update(float deltaTime) override;

        void destroy() override;

    public:
        void queryDBForAssetHandle();

        void returnQueriedHandleToInvoker();

    private:
    };
}



