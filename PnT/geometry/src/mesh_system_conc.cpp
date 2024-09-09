//
// Created by emman on 7/14/2024.
//

#include "mesh_system_conc.h"
#include "entity.h"
#include "system_finder.h"

namespace pnt::mesh{
    void P3DGeometricMeshSS::init() {
    }

    void P3DGeometricMeshSS::process() {

    }

    void P3DGeometricMeshSS::render() {

    }

    void P3DGeometricMeshSS::update(float deltaTime) {

    }

    void P3DGeometricMeshSS::destroy() {

    }

    void P3DGeometricMeshSS::start() {

    }

    P3DGeometricMeshSS::P3DGeometricMeshSS() {

    }

    PMeshComponent *P3DGeometricMeshSS::AddComponent(PEntity *entity) {
        try {
            // Avoid multiple mesh components on one entity
            for (const auto& component : meshComponents){
                if (component != nullptr && component->getID() == entity->getInstanceId()) {
                    return component.get();
                }
            }
            SMeshProfile profile = {true};
            meshComponents.emplace_back(std::make_unique<PMeshComponent>(entity, profile));

            // Will only render one mesh in the scene, that of the most recently added mesh component.
            VBO = {meshComponents.back().get()->m_vertices, (unsigned int)(meshComponents.back().get()->m_vertices.size()) };
            EBO = {meshComponents.back().get()->m_indices, (unsigned int)meshComponents.back().get()->m_indices.size() };

            VBO.initBuffer();
            EBO.initBuffer();
            //

            SendBuffersToRenderSystem();

            return meshComponents.back().get();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Mesh Comp Generic Assertion failed");
        }
        return nullptr;
    }

    void P3DGeometricMeshSS::SendBuffersToRenderSystem() {
        auto renderSystem = dynamic_cast<POpenGLRenderSS*>(PSystemFinder::PGetECSService()->getSystem<PRenderComponent>());
        if (renderSystem)  { renderSystem->SetUpBuffers(&VBO, &EBO); }
    }

    PMeshComponent *P3DGeometricMeshSS::GetComponent(unsigned int id) {
        try{
            for (const auto& component : meshComponents) {
                if (component->getID() == id) {
                    return component.get();
                }
            }
        }catch(...){
            PLog::echoMessage(LogLevel::Error, "Get Mesh Comp Generic Assertion failed");
        }
        return nullptr; // Return null pointer if component not found
    }

    void P3DGeometricMeshSS::RemoveComponent(PEntity *entity, PMeshComponent *component) {

    }

    void P3DGeometricMeshSS::RemoveComponentByTag(PEntity *entity, PMeshComponent *component, std::string tag) {

    }

    void P3DGeometricMeshSS::RemoveComponentsByTag(PEntity *entity, std::string tag) {

    }

    PMeshComponent *P3DGeometricMeshSS::FindComponentByTag(PEntity *entity, std::string tag) {
        return nullptr;
    }

    std::vector<PMeshComponent *> P3DGeometricMeshSS::FindComponentsByTag(PEntity *entity, std::string tag) {
        return std::vector<PMeshComponent *>();
    }
}

