//
// Created by Eniola Olawale on 4/30/2024.
//

#include <sstream>
#include "entity.h"

namespace pnt::ecs{

    unsigned int PEntity::s_count = 0;

    PEntity::PEntity() : m_tags(ETags::Default), m_instanceID(++s_count) {
        std::stringstream ss;
        ss << m_instanceID;
        m_name = "PEntity" + ss.str() ;
        PLog::echoMessage(m_name.c_str());
        AddComponent<PTransformComponent>(); // sets m_transform implicitly
    }

    PEntity::PEntity(const char* name) : m_name(name), m_tags(ETags::Default), m_instanceID(++s_count) {
        AddComponent<PTransformComponent>(); // sets m_transform implicitly
    }

    PEntity::PEntity(const PEntity &entity) {
        // Implement Cloning
    }

    // Explicit instantiation of GetComponent for PTransformComponent
    template<>
    PTransformComponent* PEntity::GetComponent<PTransformComponent>(){
        return m_transform.get();
    }

    // Explicit instantiation of AddComponent for PTransformComponent
    template<>
    PTransformComponent* PEntity::AddComponent() {
        static_assert(std::is_base_of_v<PComponent, PTransformComponent>, "T must be a subclass of PComponent");
        m_transform = std::make_unique<PTransformComponent>(std::forward<PEntity*>(this));
        return m_transform.get();
    }
}

