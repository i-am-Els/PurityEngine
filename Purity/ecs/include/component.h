//
// Created by Eniola Olawale on 4/30/2024.
//


#pragma once
#include "log.h"
#include "uuid.h"

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

    class PURITY_API PComponent {
    public:

        explicit PComponent(PEntity *entity);
        virtual ~PComponent(){ PLog::echoMessage("Destroying component base"); }

        virtual void update(float deltaTime){}
        virtual void start(){}

        [[nodiscard]] inline PUUID getID() const{ return m_id; }

        virtual PComponentType getComponentType() const = 0;

        virtual const char* getName() const = 0;

        PEntity* m_entity;

    protected:
        PUUID m_id;
    };

}
