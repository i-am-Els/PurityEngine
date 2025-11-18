//
// Created by Eniola Olawale on 08/07/2025.
//

#pragma once

#include "iservices.h"

namespace purity
{
    class PURITY_API ARendererService : public IService, public IInitializableService, public IUpdatableService,
                                        public IRunnableService, public IRenderableService, public ITerminableService
    {
    public:
        PURE_NODISCARD std::type_index getTypeIndex() const override {
            return {typeid(ARendererService)};
        }
        ~ARendererService() override = default;
    };
}


