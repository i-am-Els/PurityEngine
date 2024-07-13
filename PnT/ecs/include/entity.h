//
// Created by Eniola Olawale on 4/30/2024.
//

//        template<typename T, typename = std::enable_if_t<std::is_base_of_v<PComponent, T>>>

#pragma once

#include <vector>
#include <memory>

#include "IEntity.h"
#include "tags.h"
#include "transform_ecs.h"
#include "mesh.h"

using namespace pnt::artifacts;

namespace pnt::ecs {

    class PEntity {
    public:
        PEntity();
        explicit PEntity(const char* name);
        PEntity(const PEntity& entity);
        ~PEntity() = default; // Destructor destroys all components

        template<typename T>
        T* GetComponent();

        template<typename T>
        T* AddComponent();

    public:
        std::unique_ptr<PTransformComponent> m_transform;
    private:
        std::string m_name{};
        ETags m_tags;
        unsigned int m_instanceID{};


        std::vector<std::unique_ptr<PComponent>> m_components;
        static unsigned int s_count;
    };

    template<>
    PTransformComponent* PEntity::GetComponent<PTransformComponent>();

    template<>
    PTransformComponent* PEntity::AddComponent();

    template<typename T>
    T* PEntity::GetComponent() {
        try{

        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");

        for (const auto& component : m_components) {
            if (auto derived = dynamic_cast<T*>(component.get())) {
                return derived;
            }
        }
        }catch(...){
            PLog::echoMessage(LogLevel::Error, "Get Comp Generic Assertion failed");
        }
        return nullptr; // Return null pointer if component not found
    }

    template<typename T>
    T* PEntity::AddComponent() {
    try{
        static_assert(std::is_base_of_v<PComponent, T>, "T must be a subclass of PComponent");
        m_components.emplace_back(std::make_unique<T>(std::forward<PEntity*>(this)));
        return static_cast<T*>(m_components.back().get());
    }catch(...){
        PLog::echoMessage(LogLevel::Error, "Add Comp Generic Assertion failed");
    }
//        return static_cast<T*>(m_components.back().get());
    return nullptr;
    }
}

