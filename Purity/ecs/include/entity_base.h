//
// Created by Eniola Olawale on 8/8/2024.
//

#pragma once

#include "purity_core_pch.h"
//#include "component.h"

namespace purity::ecs{
    class ManipulativeBehaviour;
    class PEntityRegistry;
    class PIDManager;
    class PIDComponent;


    class PURITY_API PEntityBase{
    public:
        PEntityBase() = default;
        virtual ~PEntityBase() = default;
        explicit PEntityBase(PUUID mInstanceId) : m_instanceID(mInstanceId) {}

    protected:
        PUUID m_instanceID{0};
        std::vector<PComponent*> m_components = {};

        friend class ManipulativeBehaviour;
        friend class PIDManager;
        friend class PIDComponent;
        friend class PEntityRegistry;
    };
}
