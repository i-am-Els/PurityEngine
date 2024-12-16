//
// Created by emman on 8/8/2024.
//

#include "transform_system_conc.h"
#include "entity.h"

namespace purity::ecs{


    void PTransformSS::init() {

    }

    void PTransformSS::start() {

    }

    void PTransformSS::process() {

    }

    void PTransformSS::render() {

    }

    void PTransformSS::update(float deltaTime) {

    }

    void PTransformSS::destroy() {

    }

    PTransformComponent *PTransformSS::AddComponent(PEntity *entity) {
        try {
            transformComponents.emplace_back(std::make_unique<PTransformComponent>(
                    entity,
                    STransformProfile{
                    Transform(Vector3f::zero, Quaternion<float>::s_createIdentity(), Vector3f::one),
                    Transform()
                    }
                    ));
            return transformComponents.back().get();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Transform Comp Generic Assertion failed");
        }
        return nullptr;
    }

    void PTransformSS::RemoveComponent(PEntity *entity, PTransformComponent *component) {

    }

}
