//
// Created by Eniola Olawale on 10/8/2024.
//

#pragma once

#include "entity.h"
#include "purity_core_pch.h"
// #include "scene.h"


 //namespace purity::scene {
 //    class PScene;
 //}


namespace purity::ecs {


	class PEntityRegistry;
	class PECSService;

    /// @brief This class is an Entity Handle that exposes only operations that is expected of client code on the entity
    /// class without exposing the raw-pointer, giving the client less control over the lifetime of the actual object.
    /// @param m_handleID - This is a uuid that identifies the handle, note that it doesn't refer to that of the
    /// underlying entity's instance id(uuid).
    /// @note If EntityHandle is passed into a set or map, the entity's instance id is used to hash it and not that of the
    /// Handle itself. Therefore, 2 or more handles pointing to the same entity have the same hash.
    class PURITY_API PEntityHandle final : public fileIO::PHandleBase {
    public:
        PEntityHandle(PEntityRegistry* registry) : PHandleBase(), m_data({}), m_registry(registry) {}

        // Constructor to initialize with an existing PEntity pointer
        explicit PEntityHandle(std::weak_ptr<PEntity> entity, PEntityRegistry* registry) : PHandleBase(), m_data(entity), m_registry(registry) {}

        PURE_INLINE PEntityIndex& getEntityIndex() const { return m_data.lock()->m_index; }


        bool operator==(PEntityHandle & handle) const{
            auto entity = m_data.lock();
            auto handle_entity = handle.m_data.lock();
            if (!entity || !handle_entity) { return false; }
            return entity->getUUID() == handle_entity->getUUID() && entity == handle_entity;
        }

//        PEntityHandle(PEntityHandle&& handle) noexcept ;
//        PEntityHandle& operator=(PEntityHandle&& handle) noexcept ;

        bool isValidHandle() const {
            auto entity = m_data.lock();
            if (!entity) return false;
            return true;
        }

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
            return getECSService().GetComponent<T>(entity->m_index);
        }

        template<typename T>
        void RemoveComponent() {
            const auto entity = m_data.lock();
            if (!entity) { return; }
            return getECSService().RemoveComponent<T>(entity->m_index);
        }

        template<typename T>
        bool HasComponent() const
        {
            const auto entity = m_data.lock();
            if (!entity) { return false; }
            return getECSService().HasComponent<T>(entity->m_index);
        }

        template<typename T>
        std::weak_ptr<T> AddComponent() {
            const auto entity = m_data.lock();
            if (!entity) { return {}; }
            return getECSService().AddComponent<T>(entity->m_index);
        }

        PURE_NODISCARD PURE_INLINE PUUID getInstanceID() const {
            const auto entity = m_data.lock();
            if (!entity) { return PUUID(0); }
            return entity->getUUID();
        }

        PECSService& getECSService();
        // Optionally, provide access to the PEntity
//        PEntity* getEntity() const { return m_data; }
//        void setEntity(PEntity* entity) { m_data = entity; }
        friend bool operator==(const PEntityHandle & l_handle, const  PEntityHandle & r_handle);
    private:
        std::weak_ptr<PEntity> m_data; // Raw pointer; the handle does not own this data
        PEntityRegistry* m_registry;
        
        // Other entity operations..

    };

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
