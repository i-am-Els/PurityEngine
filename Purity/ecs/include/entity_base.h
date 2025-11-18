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


    class PURITY_API PEntityBase : public ISerializable
    {
    public:
        PEntityBase() = default;

        ~PEntityBase() override = default;

        explicit PEntityBase(const PUUID& mInstanceId) : ISerializable(mInstanceId) {}

    protected:
        std::vector<std::weak_ptr<PComponent>> m_components = {};

        friend class ManipulativeBehaviour;
        friend class PIDManager;
        friend class PIDComponent;
        friend class PEntityRegistry;
    };
}
