//
// Created by Eniola Olawale on 10/8/2024.
//

#pragma once

#include "entity.h"
#include "purity_core_pch.h"
// #include "scene.h"


// namespace purity::scene {
//     class PScene;
// }


namespace purity::ecs {

    /// @brief This class is an Entity Handle that exposes only operations that is expected of client code on the entity
    /// class without exposing the raw-pointer, giving the client less control over the lifetime of the actual object.
    /// @param m_handleID - This is a uuid that identifies the handle, note that it doesn't refer to that of the
    /// underlying entity's instance id(uuid).
    /// @note If EntityHandle is passed into a set or map, the entity's instance id is used to hash it and not that of the
    /// Handle itself. Therefore, 2 or more handles pointing to the same entity have the same hash.
    class PURITY_API PEntityHandle final : public fileIO::PHandleBase {
    public:
        PEntityHandle() : PHandleBase(), m_data({}) {}

        // Constructor to initialize with an existing PEntity pointer
        explicit PEntityHandle(std::weak_ptr<PEntity> entity) : PHandleBase(), m_data(entity) {}

        bool operator==(PEntityHandle & handle) const{
            auto entity = m_data.lock();
            auto handle_entity = handle.m_data.lock();
            if (!entity || !handle_entity) { return false; }
            return entity->getUUID() == handle_entity->getUUID() && entity == handle_entity;
        }

//        PEntityHandle(PEntityHandle&& handle) noexcept ;
//        PEntityHandle& operator=(PEntityHandle&& handle) noexcept ;

        // Destructor
        ~PEntityHandle() override {
            // Prevent dangling pointer usage after destruction
            // auto entity = m_data.lock();
            // entity = nullptr;
            PLog::echoMessage("Destroying PEntityHandle.");
        }

        void destroy();

        template<typename T>
        std::weak_ptr<T> GetComponent() {
            const auto entity = m_data.lock();
            if (!entity) { return {}; }
            return entity->GetComponent<T>();
        }

        template<typename T>
        void RemoveComponent(T* component) {
            const auto entity = m_data.lock();
            if (!entity) { return; }
            entity->RemoveComponent(component);
        }

        template<typename T>
        bool HasComponent() const
        {
            const auto entity = m_data.lock();
            if (!entity) { return false; }
            return entity->HasComponent<T>();
        }

        template<typename T>
        std::weak_ptr<T> AddComponent() {
            const auto entity = m_data.lock();
            if (!entity) { return {}; }
            return entity->AddComponent<T>();
        }

        PURE_NODISCARD PURE_INLINE PUUID getInstanceID() const {
            const auto entity = m_data.lock();
            if (!entity) { return PUUID(0); }
            return entity->getUUID();
        }

        // Optionally, provide access to the PEntity
//        PEntity* getEntity() const { return m_data; }
//        void setEntity(PEntity* entity) { m_data = entity; }
        friend bool operator==(const PEntityHandle & l_handle, const  PEntityHandle & r_handle);
    private:
        std::weak_ptr<PEntity> m_data; // Raw pointer; the handle does not own this data

        // Other entity operations...

    };

    // Allow move constructor and move assignment operator
//    PEntityHandle::PEntityHandle(PEntityHandle &&handle) noexcept {
//        m_handleId = handle.m_handleId;
//        m_data = handle.m_data;
//        handle.m_data = nullptr;
//        handle.m_handleId = PUUID(0);
//    }
//
//    PEntityHandle &PEntityHandle::operator=(PEntityHandle &&handle) noexcept {
//        m_handleId = handle.m_handleId;
//        m_data = handle.m_data;
//        handle.m_data = nullptr;
//        handle.m_handleId = PUUID(0);
//
//        return *this;
//    }

    inline bool operator==(const PEntityHandle & l_handle, const  PEntityHandle & r_handle){
        const auto l_entity = l_handle.m_data.lock();
        const auto r_entity = r_handle.m_data.lock();
        if (!l_entity || !r_entity) { return false; }
        return l_entity->getUUID() == r_entity->getUUID();
    }
}

namespace std{
    template<>
    struct hash<purity::ecs::PEntityHandle>{
        std::size_t operator()(const purity::ecs::PEntityHandle& handle) const noexcept
        {
            return hash<uint64_t>()((uint64_t)handle.getInstanceID());
        }
    };
}
