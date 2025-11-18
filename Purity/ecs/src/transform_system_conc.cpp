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

    std::weak_ptr<PTransformComponent> PTransformSS::AddComponent(std::weak_ptr<PEntity> entity) {
        try {
            transformComponents.emplace_back(std::make_shared<PTransformComponent>(
                    entity,
                    STransformProfile{
                    Transform(Vector3f::zero, Quaternion<float>::s_createIdentity(), Vector3f::one),
                    Transform()
                    }
                    ));
            return transformComponents.back();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Transform Comp Generic Assertion failed");
        }
        return {};
    }

    void PTransformSS::RemoveComponent(std::weak_ptr<PEntity> entity, std::weak_ptr<PTransformComponent> component) {

    }

}
