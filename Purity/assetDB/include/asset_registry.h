//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>
#include "uuid.h"
#include "iidentifiable.h"
#include "assets_types.h"

namespace purity {
    class Serializer;
}

namespace purity::assetDB
{
    template<class AssetTypeRef>
    class AssetOperationStrategy;

    class PURITY_API AssetRegistry {
        friend class PAssetDatabase;
        template<class AssetTypeRef>
        friend class AssetOperationStrategy;
        friend class Serializer;
    private:
        AssetRegistry(const AssetRegistry&) = delete;
        AssetRegistry(AssetRegistry&&) = delete;
        void operator=(const AssetRegistry&) = delete;
        void operator=(AssetRegistry&&) = delete;

        PURE_INLINE static AssetRegistry* GetAssetRegistry() {
            if (s_instance == nullptr) s_instance = new AssetRegistry();
            return s_instance;
        }

        PURE_INLINE static void registerObject(const std::shared_ptr<PAsset>& obj){
            std::lock_guard<std::mutex> lock(s_mutex);
			static_assert(std::is_base_of_v<IIdentifiable, PAsset>, "PAsset must inherit from IIdentifiable");
            GetAssetRegistry()->s_registry[obj->getUUID()] = obj;
        }

        PURE_INLINE static void unregisterObject(const commons::PUUID& id)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            GetAssetRegistry()->s_registry.erase(id);
        }

        PURE_INLINE static std::shared_ptr<PAsset> findObject(const commons::PUUID& id)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            auto& registry = GetAssetRegistry()->s_registry;
            if (const auto it = registry.find(id); it != registry.end()) return fetch_or_throw(it->second);
            return nullptr;
        }

        PURE_INLINE static void Shutdown() {
            std::lock_guard<std::mutex> lock(s_mutex);
            delete s_instance;
            s_instance = nullptr;
        }
        

    private:
        static inline AssetRegistry* s_instance = nullptr;
        // no custom destructor at all
        std::unordered_map<commons::PUUID, std::weak_ptr<PAsset>> s_registry;
        static inline std::mutex s_mutex;
        AssetRegistry() = default;
    };
}

