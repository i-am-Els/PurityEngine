//
// Created by emman on 8/8/2024.
//

#include "transform_system_conc.h"

void pnt::scene::PTransformSS::init() {

}

void pnt::scene::PTransformSS::start() {

}

void pnt::scene::PTransformSS::process() {

}

void pnt::scene::PTransformSS::render() {

}

void pnt::scene::PTransformSS::update(float deltaTime) {

}

void pnt::scene::PTransformSS::destroy() {

}

PTransformComponent *pnt::scene::PTransformSS::AddComponent(PEntity *entity) {
    return nullptr;
}

PTransformComponent *pnt::scene::PTransformSS::GetComponent(unsigned int id) {
    return nullptr;
}

void pnt::scene::PTransformSS::RemoveComponent(PEntity *entity, PTransformComponent *component) {

}

void pnt::scene::PTransformSS::RemoveComponentByTag(PEntity *entity, PTransformComponent *component, std::string tag) {

}

void pnt::scene::PTransformSS::RemoveComponentsByTag(PEntity *entity, std::string tag) {

}

PTransformComponent *pnt::scene::PTransformSS::FindComponentByTag(PEntity *entity, std::string tag) {
    return nullptr;
}

std::vector<PTransformComponent *> pnt::scene::PTransformSS::FindComponentsByTag(PEntity *entity, std::string tag) {
    return std::vector<PTransformComponent *>();
}
