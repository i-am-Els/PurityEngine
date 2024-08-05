//
// Created by emman on 8/5/2024.
//

#include "components_behavior.h"
#include "entity.h"
#include "scripting.h"

namespace pnt::ecs{
    template<typename T>
    std::vector<T *>ManipulativeBehaviour::FindComponentsByTag(std::string tag) {
        return nullptr;
    }

    template<typename T>
    T *ManipulativeBehaviour::FindComponentByTag(std::string tag) {
        return nullptr;
    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponentsByTag(std::string tag) {

    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponentByTag(T *component, std::string tag) {

    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponents(T *component) {

    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponent(T *component) {

    }

    template<typename T>
    T *ManipulativeBehaviour::GetComponent() {
        return nullptr;
    }

    template<typename T>
    T *ManipulativeBehaviour::AddComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem* pSystem = PECSService::getSystem<T>();
        if (auto entity = dynamic_cast<PEntity*>(this)) {
            return pSystem->AddComponent(entity);
        }else {
            if (auto comp = dynamic_cast<PBehaviourScriptComponent*>(this)) {
                return pSystem->AddComponent(comp->m_entity);
            }
        }
        return nullptr;
    }
}