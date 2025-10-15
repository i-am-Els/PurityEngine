//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once
#include "object_registry.h"
#include <cereal/archives/json.hpp>
#include <fstream>
#include <functional>
#include <vector>

namespace purity
{
    class Serializer {
    public:
        template <typename T>
        static void resolvePendingLinks()
        {
            for (auto& fn : s_pendingLinks) fn();
            s_pendingLinks.clear();
        }

        template <typename T>
        static std::shared_ptr<T> load(const std::string& path)
        {
            std::ifstream file(path);
            cereal::JSONInputArchive ar(file);

            static_assert(std::is_base_of_v<ISerializable, T>);
            auto obj = std::make_shared<T>();
            obj->Deserialize(ar);
            ObjectRegistry::registerObject(obj);

            return obj;
        }

        template<typename T>
        static void save(const std::shared_ptr<T>& obj, const std::string& path)
        {
            std::ofstream file(path);
            cereal::JSONOutputArchive ar(file);
            obj->Serialize(ar);
        }

        static void addLinkTask(std::function<void()> fn)
        {
            s_pendingLinks.push_back(std::move(fn));
        }

    private:
        static PURE_INLINE std::vector<std::function<void()>> s_pendingLinks;
    };
}

