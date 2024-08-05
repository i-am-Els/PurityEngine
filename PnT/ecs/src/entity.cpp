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
}

