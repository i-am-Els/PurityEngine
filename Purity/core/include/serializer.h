//
// Created by Eniola Olawale on 14/10/2025.
//

#pragma once

#include <fstream>
#include <functional>
#include <vector>
#include <cereal/archives/json.hpp>
#include "assetdb_utility.h"
#include "asset_registry.h"

namespace purity
{
    namespace assetDB {
        class PAsset;
    }

    class PURITY_API Serializer {
        friend class assetDB::PAssetDatabase;
        template<class AssetTypeRef>
        friend class assetDB::AssetOperationStrategy;
    private:
        template <typename T>
        static void resolvePendingLinks()
        {
            for (auto& fn : s_pendingLinks) fn();
            s_pendingLinks.clear();
        }

        template <typename T>
        static std::shared_ptr<T> load(const std::string& path)
        {
            std::filesystem::path f_path = assetDB::PAssetDBUtility::ResolveProjectPath_TC(path);
            std::ifstream file(f_path);
            cereal::JSONInputArchive ar(file);

            static_assert(std::is_base_of_v<ISerializable, T>);
            static_assert(std::is_base_of_v<assetDB::PAsset, T>);
            auto obj = std::make_shared<T>();
            obj->Deserialize(ar);
            assetDB::AssetRegistry::registerObject(obj);

            return obj;
        }

        template<typename T>
        static void save(const std::shared_ptr<T>& obj, const std::string& path)
        {
            std::filesystem::path f_path = assetDB::PAssetDBUtility::ResolveProjectPath_TC(path);
            std::ofstream file(f_path.string());
            cereal::JSONOutputArchive ar(file);
            obj->Serialize(ar);
        }

        static void addLinkTask(std::function<void()> fn)
        {
            s_pendingLinks.push_back(std::move(fn));
        }

    private:
        static inline std::vector<std::function<void()>> s_pendingLinks;

    public:
        template <typename T>
        static std::shared_ptr<T> createObject(commons::PUUID asset_uuid){
            using CleanType = std::decay_t<T>;
            static_assert(std::is_base_of_v<ISerializable, CleanType>, "Serializer Error: Object is not of a type derived from ISerializable.");
            static_assert(std::is_base_of_v<assetDB::PAsset, CleanType>, "Serializer Error: Object is not of a type derived from PAsset.");

            auto obj = std::make_shared<T>();
            obj->setUUID(asset_uuid);
            assetDB::AssetRegistry::registerObject(obj);
            return obj;
        }
    };
}

