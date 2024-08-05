//
// Created by emman on 7/25/2024.
//

#pragma once

#include <utility>
#include <map>

#include "ecs_service.h"
#include "service_base.h"
#include "mesh_data_system.h"
#include "window_pnt.h"
#include "renderer.h"
#include "opengl_renderer.h"

namespace pnt{
    class PECSService : public PServiceBase<IECSService>{
    public:
        PECSService() = default;

        explicit PECSService(PWindow* _window){
            setSystem<PRenderComponent>(std::make_unique<graphics::POpenGLRenderSS>(_window->getWindow()));
            setSystem<PMeshComponent>(std::make_unique<mesh::P3DGeometricMeshSS>());
        }

        ~PECSService() override = default;

        void init() override {
            getSystem<PRenderComponent>()->init();
            getSystem<PMeshComponent>()->init();
        }

        void process() override {
            getSystem<PRenderComponent>()->process();
            getSystem<PMeshComponent>()->process();
        }

        void render() override {
            getSystem<PRenderComponent>()->render();
            getSystem<PMeshComponent>()->render();
        }

        void update(float deltaTime) override{
            getSystem<PRenderComponent>()->update(deltaTime);
            getSystem<PMeshComponent>()->update(deltaTime);
        }

        void destroy() override{
            getSystem<PRenderComponent>()->destroy();
            getSystem<PMeshComponent>()->destroy();
        }

        void start() override {
            getSystem<PRenderComponent>()->start();
            getSystem<PMeshComponent>()->start();
        }

    protected:
        // Map
        static std::map<std::type_index, std::unique_ptr<ISystem>> system_map;

    public:
        template<typename T>
        [[nodiscard]] static std::type_index getTypeIndex() {
            return std::type_index(typeid(T));
        }

        template<typename T>
        [[nodiscard]] static ISystem* getSystem(){
            auto index = getTypeIndex<T>();
            auto it = system_map.find(index);
            if (it == system_map.end()){
                throw std::runtime_error("System not found!");
            }
            return system_map[index].get();
        }

        template<typename T>
        static void setSystem(std::unique_ptr<ISystem> system){
            static_assert(std::is_base_of<PComponent, T>::value, "T must be a subclass of PComponent");
            std::type_index index = getTypeIndex<T>();
            if(system_map.find(index) != system_map.end()){
                throw std::runtime_error("System already registered!");
            }
            system_map[index] = std::move(system);
        }

        template<typename T>
        static void unsetSystem(std::unique_ptr<ISystem> system){
            static_assert(std::is_base_of<PComponent, T>::value, "T must be a subclass of PComponent");
            std::type_index index = getTypeIndex<T>();
            if(system_map.find(index) == system_map.end()){
                throw std::runtime_error("System not registered!");
            }
            system_map.erase(index);
        }

        static const std::map<std::type_index, std::unique_ptr<ISystem>> &getSystemMap() {
            return system_map;
        }
    };
}
