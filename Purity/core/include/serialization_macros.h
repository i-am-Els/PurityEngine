//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once

// #include "object_registry.h"
#include "serializer.h"

#define PURITY_SERIALIZABLE_CLASS(name)\
class PURITY_API name : public ISerializable, public std::enable_shared_from_this<name>

#define PURITY_FINAL_IS_SERIALIZABLE_CLASS(name)\
class PURITY_API name final : public std::enable_shared_from_this<name>

#define PURITY_CLASS(name)\
class PURITY_API name : public std::enable_shared_from_this<name>

#define SERIALIZABLE(ClassName) \
    public: \
    static std::shared_ptr<ClassName> create() { \
        auto obj = std::make_shared<ClassName>(); \
        ObjectRegistry::registerObject(obj); \
        return obj; \
    }
