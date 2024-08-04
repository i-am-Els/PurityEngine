//
// Created by Eniola Olawale on 4/30/2024.
//


#pragma once
#include "log.h"
#include "isystems.h"
#include "component_traits.h"

namespace pnt::ecs {

    class PEntity; // Forward declaration


    class PComponent {
    public:

        using Traits = ComponentTraits<PComponent>;

        explicit PComponent(PEntity *entity);
        virtual ~PComponent(){ PLog::echoMessage("Destroying component base"); }

        virtual void update(float deltaTime){}
        virtual void start(){}


        PEntity* m_entity;
    protected:
        unsigned int m_id;

    public:
        virtual void SetAddComponentCallback(typename Traits::AddComponentCallback callback) = 0;
        virtual void SetGetComponentCallback(typename Traits::GetComponentCallback callback) = 0;
        virtual void SetRemoveComponentCallback(typename Traits::RemoveComponentCallback callback) = 0;
    };

}
