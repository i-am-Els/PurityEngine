//
// Created by Eniola Olawale on 9/22/2024.
//

#pragma once

#include "iservices.h"

namespace purity{

    class PURITY_API ALayerService : public IService, public IInitializableService, public IUpdatableService, public ITerminableService{
    public:

        [[nodiscard]] std::type_index getTypeIndex() const override {
            return {typeid(ALayerService)};
        }
        ~ALayerService() override = default;
    };
}

