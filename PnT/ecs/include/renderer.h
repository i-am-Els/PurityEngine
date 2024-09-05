//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "component.h"

namespace pnt::ecs{

    struct SRenderProfile{
        bool CanBeRendered;
//        PMaterial material;
//        bool shouldSetUpLOD;
    };

//    class IRenderSystem;
    class PRenderComponent : public PComponent{
    public:
        explicit PRenderComponent(PEntity *entity, SRenderProfile profile);
        ~PRenderComponent() override { PLog::echoMessage("Destroying renderComponent"); }

        void update(float deltaTime) override;
        void start() override;

        P_GET_COMPONENT_TYPE(PComponentType::PRenderComponent)
        SRenderProfile m_RenderProfile;

    private:
        static unsigned int s_count; // All components must have this

    protected:

    };
}
