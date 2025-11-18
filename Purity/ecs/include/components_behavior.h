//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "component.h"
#include "ecs_service_conc.h"
#include "entity_base.h"
#include "system_finder.h"

namespace purity::ecs{


    class PURITY_API ManipulativeBehaviour{
    public:

        virtual ~ManipulativeBehaviour() {
            PLog::echoMessage("Destroying Manipulative Behaviour Host.");
        }

        template<typename T>
        std::weak_ptr<T> GetComponent();

        template<typename T>
        void RemoveComponent(std::weak_ptr<T> component);

        template<typename T>
        bool HasComponent();

        template<typename T>
        std::weak_ptr<T> AddComponent();

    private:
        class PURITY_API PImpl_ComponentBehaviour{
        public:
            std::weak_ptr<PEntity> getEntity(ManipulativeBehaviour* behaviourOwner);
            std::weak_ptr<PEntity> getEntityFromBehaviour(ManipulativeBehaviour* behaviourOwner);
            PURE_NODISCARD PEntityBase* getEntityBase(const std::weak_ptr<PEntity>& entity) const;

            template<typename T>
            std::weak_ptr<T> getAddComponentResultIntoEntityContainer(ISystem<T> *pSystem, std::weak_ptr<PEntity>entity, const char *exception_message);

            template<typename T>
            void removeComponentFromEntityContainer(PEntityBase *entity_base, std::weak_ptr<T> component) const;

            template<typename T>
            std::weak_ptr<T> getComponentFromEntityContainer(std::weak_ptr<PEntity>entity);
        };

        PImpl_ComponentBehaviour behaviour;

    };

    template<typename T>
    bool ManipulativeBehaviour::HasComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");

        const auto e = behaviour.getEntity(this);
        const std::shared_ptr<PEntity> strongEntity = e.lock();
        const std::weak_ptr<PEntity> entity = (strongEntity != nullptr) ? strongEntity : behaviour.getEntityFromBehaviour(this);

        return std::any_of(
                behaviour.getEntityBase(entity)->m_components.begin(),
                behaviour.getEntityBase(entity)->m_components.end(),
                [](auto* comp) {
                    return dynamic_cast<T*>(comp) != nullptr;
                }
        );
    }

    template<typename T>
    void ManipulativeBehaviour::RemoveComponent(std::weak_ptr<T> component) {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PSystemFinder::GetECSService()->getSystem<T>();

        const auto e = behaviour.getEntity(this);
        const std::shared_ptr<PEntity> strongEntity = e.lock();
        std::weak_ptr<PEntity> entity = (strongEntity != nullptr) ? strongEntity : behaviour.getEntityFromBehaviour(this);
        if (strongEntity != nullptr && fetch(component) != nullptr) {
            pSystem->RemoveComponent(entity, component);
            behaviour.removeComponentFromEntityContainer<T>(behaviour.getEntityBase(entity), component);
        }
    }

    template<typename T>
    std::weak_ptr<T> ManipulativeBehaviour::GetComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");

        const auto e = behaviour.getEntity(this);
        const std::shared_ptr<PEntity> strongEntity = e.lock();
        const std::weak_ptr<PEntity> entity = (strongEntity != nullptr) ? strongEntity : behaviour.getEntityFromBehaviour(this);

        return behaviour.getComponentFromEntityContainer<T>(entity);
    }

    template<typename T>
    std::weak_ptr<T> ManipulativeBehaviour::AddComponent() {
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        ISystem<T>* pSystem = PSystemFinder::GetECSService()->getSystem<T>();

        try{
            const auto e = behaviour.getEntity(this);
            const std::shared_ptr<PEntity> strongEntity = e.lock();
            const std::weak_ptr<PEntity> entity = (strongEntity != nullptr) ? strongEntity : behaviour.getEntityFromBehaviour(this);


            if (auto found = fetch(behaviour.getComponentFromEntityContainer<T>(entity)))
            {
                return found;
            }
            return behaviour.getAddComponentResultIntoEntityContainer<T>(pSystem, entity,
                                                                         "Component is not valid");
        }catch(const char* e) {
            PLog::echoMessage(LogLevel::Error, e);
            return {};
        }
    }

    template<typename T>
    std::weak_ptr<T> ManipulativeBehaviour::PImpl_ComponentBehaviour::getAddComponentResultIntoEntityContainer(ISystem<T> *pSystem, std::weak_ptr<PEntity>entity, const char *exception_message) {
        auto comp = pSystem->AddComponent(entity);
        fetch_or_throw(comp, exception_message);
        const auto entity_base = getEntityBase(entity);
        entity_base->m_components.push_back(comp);
        return comp;
    }

    template<typename T>
    void ManipulativeBehaviour::PImpl_ComponentBehaviour::removeComponentFromEntityContainer(PEntityBase *entity_base, std::weak_ptr<T> component) const {
        auto it = std::find_if(entity_base->m_components.begin(), entity_base->m_components.end(), [&](const auto& c){ return weak_equal(c, component); });
        if (it != entity_base->m_components.end()) {
            entity_base->m_components.erase(it);
        }
    }

    template<typename T>
    std::weak_ptr<T> ManipulativeBehaviour::PImpl_ComponentBehaviour::getComponentFromEntityContainer(const std::weak_ptr<PEntity> entity) {
        const auto entityBase = getEntityBase(entity);
        try{
            for (auto& component : entityBase->m_components) {
                auto derived = ecs::fetch(component);
                if (derived == nullptr) continue;

                return std::static_pointer_cast<T>(derived);
            }
        }catch(...){
            PLog::echoMessage(LogLevel::Error, "Get Generic Comp from Entity Container Assertion failed");
        }
        return {};
    }

}

