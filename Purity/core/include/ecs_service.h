//
// Created by emman on 7/25/2024.
//

#pragma once

#include "iservices.h"

namespace purity{

    class PURITY_API AECSService : public IService, public IInitializableService, public IRunnableService, public IUpdatableService, public IRenderableService, public ITerminableService{
    public:
        PURE_NODISCARD std::type_index getTypeIndex() const override {
            return {typeid(AECSService)};
        }

        ~AECSService() override = default;

    };
}
