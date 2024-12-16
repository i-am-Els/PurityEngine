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

    PIDComponent *PIDManager::AddComponent(PEntity *entity) {
        try {
            idComponents.emplace_back(std::make_unique<PIDComponent>(entity));
            return idComponents.back().get();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Transform Comp Generic Assertion failed");
        }
        return nullptr;
    }

    void PIDManager::RemoveComponent(PEntity *entity, PIDComponent *component) {

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

    PTagComponent *PTagManager::AddComponent(PEntity *entity) {
        try {
            tagComponents.emplace_back(std::make_unique<PTagComponent>(entity));
            return tagComponents.back().get();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Transform Comp Generic Assertion failed");
        }
        return nullptr;
    }

    void PTagManager::RemoveComponent(PEntity *entity, PTagComponent *component) {

    }

}