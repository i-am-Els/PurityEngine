//
// Created by emman on 7/25/2024.
//

#pragma once

/*
#include <complex.h>
#include <map>
#include <utility>
#include "content_index.h"*/

#include "ipools.h"
#include "tag_comp.h"
#include "mesh.h"
#include "transform_ecs.h"
#include "renderer.h"

using namespace purity::ecs;

namespace purity::scene {
    class PScene;
}

namespace purity::ecs {
    class PURITY_API PECSService{
    public:
        PECSService(scene::PScene* owner) : m_ownerScene(owner) {}
        PECSService(const PECSService& service) = delete;
        PECSService operator=(const PECSService& service) = delete;

        void initialize() {
            registerPoolManager<PTagComponent>(std::make_unique<ecs::PoolManager<PTagComponent>>());
            registerPoolManager<PTransformComponent>(std::make_unique<ecs::PoolManager<PTransformComponent>>());
            registerPoolManager<PMeshComponent>(std::make_unique<ecs::PoolManager<PMeshComponent>>());
            registerPoolManager<PRendererComponent>(std::make_unique<ecs::PoolManager<PRendererComponent>>());
        }

        ~PECSService() {
            PLog::echoMessage("Destroying ECS.");
        }


        void destroy() {
            unregisterPoolManager<PTagComponent>();
            unregisterPoolManager<PTransformComponent>();
            unregisterPoolManager<PMeshComponent>();
            unregisterPoolManager<PRendererComponent>();

            poolManagersMap.clear();
        }

    protected:
		scene::PScene* m_ownerScene;
        // Map
        std::unordered_map<std::type_index, std::unique_ptr<ecs::IPoolBase>> poolManagersMap;

    public:
        PNT_TYPE_INDEX_DEF()

        template<typename T>
        PURE_NODISCARD ecs::PoolManager<T>* getPoolManager()
        {
            auto index = s_getTypeIndex<T>();
            
            auto it = poolManagersMap.find(index);
            if (it == poolManagersMap.end()){
                PLog::echoMessage(LogLevel::Error, "PoolManger not Found! Returning nullptr.");
                return nullptr;
            }            
            return static_cast<PoolManager<T>*>(it->second.get());
        }



        template<typename T>
        PURE_NODISCARD std::weak_ptr<T> GetComponent(PEntityIndex index) {
            PoolManager<T>* manager = getPoolManager<T>();
            if (manager == nullptr) 
            {
                PLog::echoMessage(LogLevel::Error, "Component Pool Manager returned null reference.");
                return {};
            }
            return manager->getComponent(index);
        }

        template<typename T>
        PURE_NODISCARD std::weak_ptr<T> AddComponent(PEntityIndex index) {
            PoolManager<T>* manager = getPoolManager<T>();
            if (manager == nullptr)
            {
                PLog::echoMessage(LogLevel::Error, "Component Pool Manager returned null reference.");
                return {};
            }
            return manager->addComponent(index);
        }

        template<typename T>
        PURE_NODISCARD void RemoveComponent(PEntityIndex index) {
            PoolManager<T>* manager = getPoolManager<T>();
            if (manager == nullptr)
            {
                PLog::echoMessage(LogLevel::Error, "Component Pool Manager returned null reference.");
                return;
            }
            manager->removeComponent(index);
        }

        template<typename T>
        PURE_NODISCARD bool HasComponent(PEntityIndex index) {
            PoolManager<T>* manager = getPoolManager<T>();
            if (manager == nullptr)
            {
                PLog::echoMessage(LogLevel::Error, "Component Pool Manager returned null reference.");
                return false;
            }
            return manager->contains(index);
        }

        template<typename T>
        void registerPoolManager(std::unique_ptr<ecs::PoolManager<T>> poolManager){
            static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
            const std::type_index index = s_getTypeIndex<T>();
            if(poolManagersMap.find(index) != poolManagersMap.end()){
                PLog::echoMessage(LogLevel::Warning, "PoolManger already registered!, Overwriting previous Manager.");
            }
            poolManagersMap[index] = std::move(poolManager);
        }

        template<typename T>
        void unregisterPoolManager(){
            static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
            const std::type_index index = s_getTypeIndex<T>();
            if(poolManagersMap.find(index) == poolManagersMap.end()){
                PLog::echoMessage(LogLevel::Error, "PoolManger was never registered! Throwing a runtime error.");
                throw std::runtime_error("System not registered!");
            }
            poolManagersMap.erase(index);
        }

        const std::unordered_map<std::type_index, std::unique_ptr<ecs::IPoolBase>> &getPoolManagerMap() {
            return poolManagersMap;
        }
    };
}
