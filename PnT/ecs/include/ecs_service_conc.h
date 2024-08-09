//
// Created by emman on 7/25/2024.
//

#pragma once

#include <utility>
#include <map>

#include "ecs_service.h"
#include "service_base.h"
#include "window_pnt.h"
#include "mesh_system_conc.h"
#include "transform_system_conc.h"
#include "render_system_conc.h"

namespace pnt{
    class PECSService : public PServiceBase<IECSService>{
    public:
        PECSService() = default;

        explicit PECSService(PWindow* _window){
            setSystem<PTransformComponent>(std::make_unique<scene::PTransformSS>());
            setSystem<PMeshComponent>(std::make_unique<mesh::P3DGeometricMeshSS>());
            setSystem<PRenderComponent>(std::make_unique<graphics::POpenGLRenderSS>(_window->getWindow()));
        }

        ~PECSService() override = default;

        void init() override {
            s_getSystem<PTransformComponent>()->init();
            s_getSystem<PMeshComponent>()->init();
            s_getSystem<PRenderComponent>()->init();
        }

        void start() override {
            s_getSystem<PTransformComponent>()->start();
            s_getSystem<PMeshComponent>()->start();
            s_getSystem<PRenderComponent>()->start();
        }

        void process() override {
            s_getSystem<PTransformComponent>()->process();
            s_getSystem<PMeshComponent>()->process();
            s_getSystem<PRenderComponent>()->process();
        }

        void render() override {
            s_getSystem<PTransformComponent>()->render();
            s_getSystem<PMeshComponent>()->render();
            s_getSystem<PRenderComponent>()->render();
        }

        void update(float deltaTime) override{
            s_getSystem<PTransformComponent>()->update(deltaTime);
            s_getSystem<PMeshComponent>()->update(deltaTime);
            s_getSystem<PRenderComponent>()->update(deltaTime);
        }

        void destroy() override{
            s_getSystem<PTransformComponent>()->destroy();
            s_getSystem<PMeshComponent>()->destroy();
            s_getSystem<PRenderComponent>()->destroy();
        }

    protected:
        // Map
        static std::map<std::type_index, std::unique_ptr<ISystemBase>> system_map;

    public:
        template<typename T>
        [[nodiscard]] static std::type_index s_getTypeIndex() {
            return std::type_index(typeid(T));
        }

        template<typename T>
        [[nodiscard]] static ISystem<T>* s_getSystem(){
            auto index = s_getTypeIndex<T>();
            auto it = system_map.find(index);
            if (it == system_map.end()){
                throw std::runtime_error("System not found!");
            }
            return dynamic_cast<ISystem<T>*>(it->second.get());
        }

        template<typename T>
        [[nodiscard]] ISystem<T>* getSystem(){
            auto index = s_getTypeIndex<T>();
            auto it = system_map.find(index);
            if (it == system_map.end()){
                throw std::runtime_error("System not found!");
            }
            return dynamic_cast<ISystem<T>*>(it->second.get());
        }

//        template<typename T>
//        [[nodiscard]] ISystem<T>* getSystem() const {
//            auto index = s_getTypeIndex<T>();
//            auto it = system_map.find(index);
//            if (it == system_map.end()) {
//                throw std::runtime_error("System not found!");
//            }
//            // Ensure that the cast is valid; use dynamic_cast if necessary.
//            return dynamic_cast<ISystem<T>*>(it->second.get());
//        }

        template<typename T>
        static void setSystem(std::unique_ptr<ISystem<T>> system){
            static_assert(std::is_base_of<PComponent, T>::value, "T must be a subclass of PComponent");
            std::type_index index = s_getTypeIndex<T>();
            if(system_map.find(index) != system_map.end()){
                throw std::runtime_error("System already registered!");
            }
            system_map[index] = std::move(system);
        }

        template<typename T>
        static void unsetSystem(std::unique_ptr<ISystem<T>> system){
            static_assert(std::is_base_of<PComponent, T>::value, "T must be a subclass of PComponent");
            std::type_index index = s_getTypeIndex<T>();
            if(system_map.find(index) == system_map.end()){
                throw std::runtime_error("System not registered!");
            }
            system_map.erase(index);
        }

        static const std::map<std::type_index, std::unique_ptr<ISystemBase>> &getSystemMap() {
            return system_map;
        }
    };
}
