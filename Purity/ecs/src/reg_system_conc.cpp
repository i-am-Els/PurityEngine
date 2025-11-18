//
// Created by Eniola Olawale on 9/17/2024.
//

#include "reg_system_conc.h"
#include "entity.h"

namespace purity::ecs{

    void PIDManager::init() {

    }

    void PIDManager::start() {

    }

    void PIDManager::process() {

    }

    void PIDManager::render() {

    }

    void PIDManager::update(float deltaTime) {

    }

    void PIDManager::destroy() {

    }

    std::weak_ptr<PIDComponent> PIDManager::AddComponent(std::weak_ptr<PEntity> entity) {
        try {
            idComponents.emplace_back(std::make_shared<PIDComponent>(entity));
            return idComponents.back();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Transform Comp Generic Assertion failed");
        }
        return {};
    }

    void PIDManager::RemoveComponent(std::weak_ptr<PEntity> entity, std::weak_ptr<PIDComponent> component) {

    }

    void PTagManager::init() {

    }

    void PTagManager::start() {

    }

    void PTagManager::process() {

    }

    void PTagManager::render() {

    }

    void PTagManager::update(float deltaTime) {

    }

    void PTagManager::destroy() {

    }

    std::weak_ptr<PTagComponent> PTagManager::AddComponent(std::weak_ptr<PEntity> entity) {
        try {
            auto tagComponent = std::make_shared<PTagComponent>(entity);
            tagComponents.emplace_back(tagComponent);
            ObjectRegistry::registerObject(tagComponent);
            return tagComponents.back();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Transform Comp Generic Assertion failed");
        }
        return {};
    }

    void PTagManager::RemoveComponent(std::weak_ptr<PEntity> entity, std::weak_ptr<PTagComponent> component) {

    }

}