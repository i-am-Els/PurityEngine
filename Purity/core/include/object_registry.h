//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once

#include <memory>
#include <mutex>
#include <unordered_map>
#include "iserializable.h"
#include "uuid.h"


namespace purity
{
    class PURITY_API ObjectRegistry {
    public:
        static void registerObject(const std::shared_ptr<ISerializable>& obj){
            std::lock_guard<std::mutex> lock(s_mutex);
            s_registry[obj->id] = obj;
        }

        static void unregisterObject(const commons::PUUID& id)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            s_registry.erase(id);
        }

        static std::shared_ptr<ISerializable> findObject(const commons::PUUID& id)
        {
            std::lock_guard<std::mutex> lock(s_mutex);
            if (const auto it = s_registry.find(id); it != s_registry.end()) return it->second.lock();
            return nullptr;
        }

    private:
        static inline std::unordered_map<commons::PUUID, std::weak_ptr<ISerializable>> s_registry;
        static inline std::mutex s_mutex;

    };
}

