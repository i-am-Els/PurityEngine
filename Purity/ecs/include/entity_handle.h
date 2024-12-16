//
// Created by Eniola Olawale on 10/8/2024.
//

#pragma once

#include "purity_core_pch.h"
#include "entity.h"


namespace purity::ecs {

    /// @brief This class is an Entity Handle that exposes only operations that is expected of client code on the entity
    /// class without exposing the raw-pointer, giving the client less control over the lifetime of the actual object.
    /// @param m_handleID - This is a uuid that identifies the handle, note that it doesn't refer to that of the
    /// underlying entity's instance id(uuid).
    /// @note If EntityHandle is passed into a set or map, the entity's instance id is used to hash it and not that of the
    /// Handle itself. Therefore, 2 or more handles pointing to the same entity have the same hash.
    class PURITY_API PEntityHandle final : public fileIO::PHandleBase {
    public:
        PEntityHandle() : PHandleBase(), m_data(nullptr) {}

        // Constructor to initialize with an existing PEntity pointer
        explicit PEntityHandle(PEntity* entity) : PHandleBase(), m_data(entity) {}

        bool operator==(PEntityHandle & handle) const{
            return m_data->getInstanceID() == handle.m_data->getInstanceID();
        }

//        PEntityHandle(PEntityHandle&& handle) noexcept ;
//        PEntityHandle& operator=(PEntityHandle&& handle) noexcept ;

        // Destructor
        ~PEntityHandle() override {
            // Prevent dangling pointer usage after destruction
            m_data = nullptr;
            PLog::echoMessage("Destroying PEntityHandle.");
        }

        template<typename T>
        T *GetComponent() {
            return m_data->GetComponent<T>();
        }

        template<typename T>
        void RemoveComponent(T* component) {
            m_data->RemoveComponent(component);
        }

        template<typename T>
        bool HasComponent() {
            return m_data->HasComponent<T>();
        }

        template<typename T>
        T *AddComponent() {
            return m_data->AddComponent<T>();
        }

        [[nodiscard]] inline PUUID getInstanceID() const {
            return m_data->getInstanceID();
        }

        // Optionally, provide access to the PEntity
//        PEntity* getEntity() const { return m_data; }
//        void setEntity(PEntity* entity) { m_data = entity; }
        friend bool operator==(const PEntityHandle & l_handle, const  PEntityHandle & r_handle);
    private:
        PEntity* m_data; // Raw pointer; the handle does not own this data

        // Other entity operations...

    // Allow move constructor and move assignment operator
    };

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
        return l_handle.m_data->getInstanceID() == r_handle.m_data->getInstanceID();
    }
}

namespace std{
    template<>
    struct hash<purity::ecs::PEntityHandle>{
        std::size_t operator()(const purity::ecs::PEntityHandle& handle) const{
            return hash<uint64_t>()((uint64_t)handle.getInstanceID());
        }
    };
}
