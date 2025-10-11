//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once

#include "iservices.h"

namespace purity{

    class PURITY_API AAssetDBService : public IService, public IInitializableService, public ITerminableService{
    public:

        PURE_NODISCARD std::type_index getTypeIndex() const override {
            return {typeid(AAssetDBService)};
        }
        ~AAssetDBService() override = default;

    };
}
