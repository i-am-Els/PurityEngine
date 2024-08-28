//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "component.h"
#include "ecs_service_conc.h"
#include "entity_base.h"

namespace pnt::ecs{


    class ManipulativeBehaviour{
    public:

        virtual ~ManipulativeBehaviour() = default;

        template<typename T>
        T *GetComponent();

        template<typename T>
        void RemoveComponent(T* component);

        template<typename T>
        void RemoveComponentByTag(T* component, const std::string &tag);

        template<typename T>
        void RemoveComponentsByTag(const std::string &tag);

        template<typename T>
        T* FindComponentByTag(const std::string &tag);

        template<typename T>
        std::vector<T*> FindComponentsByTag(const std::string &tag);

        template<typename T>
        T *AddComponent();

    private:
        class PImpl_ComponentBehaviour{
        public:
            PEntity* getEntity(ManipulativeBehaviour* behaviourOwner);
            unsigned int getIDFromEntity(PEntity* entity);
            PEntity* getEntityFromBehaviour(ManipulativeBehaviour* behaviourOwner);
            PEntityBase* getEntityBase(PEntity *entity) const;
            PTransformComponent* getTransform(PEntity* entity) const;

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
    std::vector<T *>ManipulativeBehaviour::FindComponentsByTag(const std::string &tag) {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PECSService::s_getSystem<T>();
        auto entity = behaviour.getEntity(this);
        if (entity != nullptr) {
            return pSystem->FindComponentsByTag(entity, tag);
        }else {
            entity = behaviour.getEntityFromBehaviour(this);
            if (entity != nullptr) {
                return pSystem->FindComponentsByTag(entity, tag);
            }
        }
        return nullptr;
    }

    template<typename T>
    T *ManipulativeBehaviour::FindComponentByTag(const std::string & tag) {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PECSService::s_getSystem<T>();
        auto entity = behaviour.getEntity(this);
        if (entity != nullptr) {
            return pSystem->FindComponentByTag(entity, tag);
        }else {
            entity = behaviour.getEntityFromBehaviour(this);
            if (entity != nullptr) {
                return pSystem->FindComponentByTag(entity, tag);
            }
        }
        return nullptr;
    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponentsByTag(const std::string & tag) {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PECSService::s_getSystem<T>();
        auto entity = behaviour.getEntity(this);
        if (entity != nullptr) {
            pSystem->RemoveComponentsByTag(entity, tag);
        }else {
            entity = behaviour.getEntityFromBehaviour(this);
            if (entity != nullptr) {
                pSystem->RemoveComponentsByTag(entity, tag);
            }
        }
    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponentByTag(T *component, const std::string &tag) {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PECSService::s_getSystem<T>();
        auto entity = behaviour.getEntity(this);
        if (entity != nullptr) {
            pSystem->RemoveComponentByTag(entity, component, tag);
            removeComponentFromEntityContainer(behaviour.getEntityBase(entity), component);
        }else {
            entity = behaviour.getEntityFromBehaviour(this);
            if (entity != nullptr) {
                pSystem->RemoveComponentByTag(entity, component, tag);
                removeComponentFromEntityContainer(behaviour.getEntityBase(entity), component);
            }
        }
    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponent(T *component) {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PECSService::s_getSystem<T>();
        auto entity = behaviour.getEntity(this);
        if (entity != nullptr && component != nullptr) {
            pSystem->RemoveComponent(entity, component);
            removeComponentFromEntityContainer(behaviour.getEntityBase(entity), component);
        }else {
            entity = behaviour.getEntityFromBehaviour(this);
            if (entity != nullptr && component != nullptr) {
                pSystem->RemoveComponent(entity, component);
                removeComponentFromEntityContainer(behaviour.getEntityBase(entity), component);
            }
        }
    }

    template<typename T>
    T *ManipulativeBehaviour::GetComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        auto entity = behaviour.getEntity(this);
        if (entity != nullptr) {
            return behaviour.getComponentFromEntityContainer<T>(entity);
        }else {
            entity = behaviour.getEntityFromBehaviour(this);
            if (entity != nullptr) {
                return behaviour.getComponentFromEntityContainer<T>(entity);
            }
        }
        return nullptr;

    }

    template<typename T>
    T *ManipulativeBehaviour::AddComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PECSService::s_getSystem<T>();

        try{
            PEntity *entity;
            entity = behaviour.getEntity(this);
            if (entity != nullptr) {
                return behaviour.getAddComponentResultIntoEntityContainer<T>(pSystem, entity,
                                                                   "Component from entity call is not valid");
            }
            else {
                entity = behaviour.getEntityFromBehaviour(this);
                if (entity != nullptr) {
                    return behaviour.getAddComponentResultIntoEntityContainer<T>(pSystem, entity,
                                                                       "Component from script call is not valid");
                }
            }
        }catch(const char* e) {
            PLog::echoMessage(LogLevel::Error, e);
            return nullptr;
        }
        return nullptr;
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

    template<>
    inline PTransformComponent *ManipulativeBehaviour::PImpl_ComponentBehaviour::getComponentFromEntityContainer(PEntity *entity) {
        PTransformComponent* transform = getTransform(entity);
        if (transform != nullptr)
        {
            return transform;
        }

        auto entityBase = getEntityBase(entity);
        try{
            for (const auto& component : entityBase->m_components) {
                auto derived = dynamic_cast<PTransformComponent*>(component);
                if (derived == nullptr) continue;
                return derived;
            }
        }catch(...){
            PLog::echoMessage(LogLevel::Error, "Get Generic Comp from Entity Container Assertion failed");
        }
        return nullptr;
    }
}

