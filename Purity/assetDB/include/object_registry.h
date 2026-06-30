//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>
#include "iserializable.h"
#include "uuid.h"

namespace purity {
    class Serializer;
}

namespace purity::assetDB
{
    template<class AssetTypeRef>
    class AssetOperationStrategy;

    class PURITY_API ObjectRegistry {
        friend class PAssetDatabase;
        template<class AssetTypeRef>
        friend class AssetOperationStrategy;
        friend class Serializer;
    private:
        ObjectRegistry(const ObjectRegistry&) = delete;
        ObjectRegistry(ObjectRegistry&&) = delete;
        void operator=(const ObjectRegistry&) = delete;
        void operator=(ObjectRegistry&&) = delete;

        static ObjectRegistry* GetObjectRegistry() {
            if (s_instance == nullptr) s_instance = new ObjectRegistry();
            return s_instance;
        }

        static void registerObject(const std::shared_ptr<ISerializable>& obj){
            std::lock_guard<std::mutex> lock(s_mutex);
            GetObjectRegistry()->s_registry[obj->getUUID()] = obj;
        }

        static void unregisterObject(const commons::PUUID& id)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            GetObjectRegistry()->s_registry.erase(id);
        }

        static std::shared_ptr<ISerializable> findObject(const commons::PUUID& id)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            auto registry = GetObjectRegistry()->s_registry;
            if (const auto it = registry.find(id); it != registry.end()) return fetch_or_throw(it->second);
            return nullptr;
        }

        ~ObjectRegistry() {
            delete s_instance;
        }

    private:
        std::unordered_map<commons::PUUID, std::weak_ptr<ISerializable>> s_registry;
        static inline std::mutex s_mutex;
        static inline ObjectRegistry* s_instance;
        ObjectRegistry() = default;
    };
}

