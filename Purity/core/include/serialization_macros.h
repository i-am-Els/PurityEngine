//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once

#include "serializer.h"

#define PURITY_SERIALIZABLE_CLASS(name)\
class PURITY_API name : public ISerializable

#define PURITY_SERIALIZABLE_SHARED_CLASS(name)\
class PURITY_API name : public ISerializable, public std::enable_shared_from_this<name>

#define PURITY_FINAL_SERIALIZABLE_SHARED_CLASS(name)\
class PURITY_API name final : public std::enable_shared_from_this<name>

#define PURITY_SHARED_CLASS(name)\
class PURITY_API name : public std::enable_shared_from_this<name>

#define CAN_CREATE_AS_SERIALIZABLE(ClassName) \
    public: \
    static std::shared_ptr<ClassName> create() { \
        return Serializer::SerializerBehaviour::createObjectT<ClassName>(); \
    }
