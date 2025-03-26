//
// Created by emman on 7/14/2024.
//

#include "mesh_system_conc.h"
#include "entity.h"

namespace purity::ecs{
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
            SMeshProfile profile = {true};
            meshComponents.emplace_back(std::make_unique<PMeshComponent>(entity, profile));
            return meshComponents.back().get();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Mesh Comp Generic Assertion failed");
        }
        return nullptr;
    }

    void P3DGeometricMeshSS::RemoveComponent(PEntity *entity, PMeshComponent *component) {

    }

}

