//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once

#include "serializer.h"
#include "object_registry.h"

#define SERIALIZABLE(ClassName) \
    public: \
    static std::shared_ptr<ClassName> create() { \
        auto obj = std::make_shared<ClassName>(); \
        ObjectRegistry::registerObject(obj); \
        return obj; \
    }
