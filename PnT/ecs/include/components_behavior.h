//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "component.h"
#include "entity_base.h"
#include "ecs_service_conc.h"
#include "system_finder.h"

namespace pnt::ecs{


    class PNT_API ManipulativeBehaviour{
    public:

        virtual ~ManipulativeBehaviour() = default;

        template<typename T>
        T *GetComponent();

        template<typename T>
        void RemoveComponent(T* component);

        template<typename T>
        bool HasComponent();

        template<typename T>
        T *AddComponent();

    private:
        class PNT_API PImpl_ComponentBehaviour{
        public:
            PEntity* getEntity(ManipulativeBehaviour* behaviourOwner);
            PEntity* getEntityFromBehaviour(ManipulativeBehaviour* behaviourOwner);
            PEntityBase* getEntityBase(PEntity *entity) const;

            template<typename T>
            T* getAddComponentResultIntoEntityContainer(ISystem<T> *pSystem, PEntity *entity, const char *exception_message);

            template<typename T>
            void removeComponentFromEntityContainer(PEntityBase *entity_base, T *component) const;

            template<typename T>
            inline T* getComponentFromEntityContainer(PEntity *entity);
        };

        PImpl_ComponentBehaviour behaviour;

    };

    template<typename T>
    bool ManipulativeBehaviour::HasComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");

        auto e = behaviour.getEntity(this);
        PEntity *entity = e != nullptr ? e :  behaviour.getEntityFromBehaviour(this);
        return std::any_of(
                behaviour.getEntityBase(entity)->m_components.begin(),
                behaviour.getEntityBase(entity)->m_components.end(),
                [](auto* comp) {
                    return dynamic_cast<T*>(comp) != nullptr;
                }
        );
    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponent(T *component) {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PSystemFinder::GetECSService()->getSystem<T>();

        auto e = behaviour.getEntity(this);
        PEntity *entity = e != nullptr ? e :  behaviour.getEntityFromBehaviour(this);
        if (entity != nullptr && component != nullptr) {
            pSystem->RemoveComponent(entity, component);
            behaviour.removeComponentFromEntityContainer(behaviour.getEntityBase(entity), component);
        }
    }

    template<typename T>
    T *ManipulativeBehaviour::GetComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");

        auto e = behaviour.getEntity(this);
        PEntity *entity = e != nullptr ? e :  behaviour.getEntityFromBehaviour(this);
        return behaviour.getComponentFromEntityContainer<T>(entity);
    }

    template<typename T>
    T *ManipulativeBehaviour::AddComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PSystemFinder::GetECSService()->getSystem<T>();

        try{
            auto e = behaviour.getEntity(this);
            PEntity *entity = e != nullptr ? e :  behaviour.getEntityFromBehaviour(this);

            T* found = behaviour.getComponentFromEntityContainer<T>(entity);
            if (found)
            {
                return found;
            }
            return behaviour.getAddComponentResultIntoEntityContainer<T>(pSystem, entity,
                                                                         "Component is not valid");
        }catch(const char* e) {
            PLog::echoMessage(LogLevel::Error, e);
            return nullptr;
        }
    }

    template<typename T>
    T *ManipulativeBehaviour::PImpl_ComponentBehaviour::getAddComponentResultIntoEntityContainer(ISystem<T> *pSystem, PEntity *entity, const char *exception_message) {
        auto comp = pSystem->AddComponent(entity);
        if (comp == nullptr)
            throw exception_message;
        auto entity_base = getEntityBase(entity);
        entity_base->m_components.push_back(comp);
        return comp;
    }

    template<typename T>
    void ManipulativeBehaviour::PImpl_ComponentBehaviour::removeComponentFromEntityContainer(PEntityBase *entity_base, T *component) const {
        auto it = std::find(entity_base->m_components.begin(), entity_base->m_components.end(), component);
        if (it != entity_base->m_components.end()) {
            entity_base->m_components.erase(it);
        }
    }

    template<typename T>
    inline T *ManipulativeBehaviour::PImpl_ComponentBehaviour::getComponentFromEntityContainer(PEntity *entity) {
        auto entityBase = getEntityBase(entity);
        try{
            for (const auto& component : entityBase->m_components) {
                auto derived = dynamic_cast<T*>(component);
                if (derived == nullptr) continue;
                return derived;
            }
        }catch(...){
            PLog::echoMessage(LogLevel::Error, "Get Generic Comp from Entity Container Assertion failed");
        }
        return nullptr;
    }

}

