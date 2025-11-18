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

     std::weak_ptr<PMeshComponent> P3DGeometricMeshSS::AddComponent(std::weak_ptr<PEntity> entity) {
        try {
            SMeshProfile profile = {true};
            meshComponents.emplace_back(std::make_shared<PMeshComponent>(entity, profile));
            return meshComponents.back();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Mesh Comp Generic Assertion failed");
        }
        return {};
    }

    void P3DGeometricMeshSS::RemoveComponent(std::weak_ptr<PEntity> entity, std::weak_ptr<PMeshComponent> component) {

    }

}

