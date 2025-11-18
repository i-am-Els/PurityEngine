//
// Created by Eniola Olawale on 4/30/2024.
//


#pragma once
#include "log.h"
#include "serialization_macros.h"
#include "uuid.h"

using namespace commons;


#define P_GET_COMPONENT_TYPE(type) static PComponentType s_GetStaticType() { return type; } \
                                virtual PComponentType getComponentType() const override { return s_GetStaticType(); } \
                                virtual const char* getName() const override { return #type; }  \



namespace purity::ecs {

    class PEntity; // Forward declaration

    enum class PComponentType{
        PTransformComponent,
        PRenderComponent,
        PMeshComponent,
        PBehaviourScriptComponent,
        PIDComponent,
        PTagComponent,
        PCameraComponent
    };

    class PURITY_API PComponent: public ISerializable
    // PURITY_SERIALIZABLE_CLASS(PComponent)
    {
    public:
        explicit PComponent(std::weak_ptr<PEntity> entity);
        ~PComponent() override{ PLog::echoMessage("Destroying component base"); }

        virtual void update(float deltaTime){}
        virtual void start(){}
        virtual void destroy(){}

        virtual PComponentType getComponentType() const = 0;

        virtual const char* getName() const = 0;

        std::weak_ptr<PEntity> m_entity;
    };

}
