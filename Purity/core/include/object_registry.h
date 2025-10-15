//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once
#include <memory>
#include <mutex>
#include <unordered_map>
#include "uuid.h"


namespace purity
{
    class ObjectRegistry {
    public:
        static void registerObject(const std::shared_ptr<ISerializable>& obj){
            std::lock_guard<std::mutex> lock(s_mutex);
            s_registry[obj->id] = obj;
        }

        static void unregisterObject(const PUUID& id)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            s_registry.erase(id);
        }

        static std::shared_ptr<ISerializable> findObject(const PUUID& id)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            auto it = s_registry.find(id);
            if (it != s_registry.end()) return it->second.lock();
            return nullptr;
        }

    private:
        static PURE_INLINE std::unordered_map<PUUID, std::weak_ptr<ISerializable>> s_registry;
        static PURE_INLINE std::mutex s_mutex;

    };
}

