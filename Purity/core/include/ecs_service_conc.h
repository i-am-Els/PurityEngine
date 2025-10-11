//
// Created by emman on 7/25/2024.
//

#pragma once

#include <map>
#include <utility>

#include "ecs_service.h"
#include "id_comp.h"
#include "mesh_system_conc.h"
#include "reg_system_conc.h"
#include "render_system_conc.h"
#include "tag_comp.h"
#include "transform_system_conc.h"
#include "window_purity.h"

namespace purity{
    class PURITY_API PECSService final : public AECSService{
    public:
        PECSService() = default;
        PECSService(const PECSService& service) = delete;
        PECSService operator=(const PECSService& service) = delete;

        explicit PECSService(PWindow* _window){
            setSystem<PIDComponent>(std::make_unique<ecs::PIDManager>());
            setSystem<PTagComponent>(std::make_unique<ecs::PTagManager>());
            setSystem<PTransformComponent>(std::make_unique<ecs::PTransformSS>());
            setSystem<PMeshComponent>(std::make_unique<ecs::P3DGeometricMeshSS>());
            setSystem<PRenderComponent>(std::make_unique<ecs::POpenGLRenderSS>());
        }

        ~PECSService() override {
            PLog::echoMessage("Destroying ECS Service.");
        }

        void init() override {
            getSystem<PIDComponent>()->init();
            getSystem<PTagComponent>()->init();
            getSystem<PTransformComponent>()->init();
            getSystem<PMeshComponent>()->init();
            getSystem<PRenderComponent>()->init();
        }

        void start() override {
            getSystem<PIDComponent>()->start();
            getSystem<PTagComponent>()->start();
            getSystem<PTransformComponent>()->start();
            getSystem<PMeshComponent>()->start();
            getSystem<PRenderComponent>()->start();
        }

        void process() override {
            getSystem<PIDComponent>()->process();
            getSystem<PTagComponent>()->process();
            getSystem<PTransformComponent>()->process();
            getSystem<PMeshComponent>()->process();
            getSystem<PRenderComponent>()->process();
        }

        void render() override {
            getSystem<PRenderComponent>()->render();
        }

        void update(float deltaTime) override {
            getSystem<PIDComponent>()->update(deltaTime);
            getSystem<PTagComponent>()->update(deltaTime);
            getSystem<PTransformComponent>()->update(deltaTime);
            getSystem<PMeshComponent>()->update(deltaTime);
            getSystem<PRenderComponent>()->update(deltaTime);
        }

        void destroy() override{
            getSystem<PIDComponent>()->destroy();
            getSystem<PTagComponent>()->destroy();
            getSystem<PTransformComponent>()->destroy();
            getSystem<PMeshComponent>()->destroy();
            getSystem<PRenderComponent>()->destroy();

            unsetSystem<PIDComponent>();
            unsetSystem<PTagComponent>();
            unsetSystem<PTransformComponent>();
            unsetSystem<PMeshComponent>();
            unsetSystem<PRenderComponent>();

            system_map.clear();
        }

    protected:
        // Map
        std::map<std::type_index, std::unique_ptr<ecs::ISystemBase>> system_map;

    public:
        PNT_TYPE_INDEX_DEF()

//        template<typename T>
//        PURE_NODISCARD static ISystem<T>* s_getSystem(){
//            auto index = s_getTypeIndex<T>();
//            auto it = system_map.find(index);
//            if (it == system_map.end()){
//                throw std::runtime_error("System not found!");
//            }
//            return dynamic_cast<ISystem<T>*>(it->second.get());
//        }

        template<typename T>
        PURE_NODISCARD ISystem<T>* getSystem(){
            auto index = s_getTypeIndex<T>();
            auto it = system_map.find(index);
            if (it == system_map.end()){
                throw std::runtime_error("System not found!");
            }
            return dynamic_cast<ISystem<T>*>(it->second.get());
        }

        template<typename T>
        void setSystem(std::unique_ptr<ISystem<T>> system){
            static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
            const std::type_index index = s_getTypeIndex<T>();
            if(system_map.find(index) != system_map.end()){
                throw std::runtime_error("System already registered!");
            }
            system_map[index] = std::move(system);
        }

        template<typename T>
        void unsetSystem(){
            static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
            const std::type_index index = s_getTypeIndex<T>();
            if(system_map.find(index) == system_map.end()){
                throw std::runtime_error("System not registered!");
            }
            system_map.erase(index);
        }

        const std::map<std::type_index, std::unique_ptr<ISystemBase>> &getSystemMap() {
            return system_map;
        }

        void preInit(const std::any& data) override;
        void postInit() override;
        void preRender() override;
        void postRender() override;
        void exit() override;
    };
}
