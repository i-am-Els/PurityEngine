//
// Created by Eniola Olawale on 4/30/2024.
//


#pragma once
#include "log.h"

namespace pnt::ecs {

    class PEntity; // Forward declaration


    class PComponent {
    public:

        explicit PComponent(PEntity *entity);
        virtual ~PComponent(){ PLog::echoMessage("Destroying component base"); }

        virtual void update(float deltaTime){}
        virtual void start(){}

        [[nodiscard]] inline unsigned int getID() const{ return m_id; }

        PEntity* m_entity;
    protected:
        unsigned int m_id;
    };

}
