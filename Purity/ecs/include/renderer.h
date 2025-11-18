//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "component.h"

namespace purity::ecs{

    struct SRenderProfile{
        bool CanBeRendered;
//        PMaterial material;
//        bool shouldSetUpLOD;
    };

//    class IRenderSystem;
    class PURITY_API PRenderComponent final : public PComponent,  public std::enable_shared_from_this<PRenderComponent>{
    public:
        explicit PRenderComponent(std::weak_ptr<PEntity> entity, SRenderProfile profile);
        ~PRenderComponent() override { PLog::echoMessage("Destroying renderComponent"); }

        void update(float deltaTime) override;
        void start() override;

        P_GET_COMPONENT_TYPE(PComponentType::PRenderComponent)
        void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
        SRenderProfile m_RenderProfile;

    private:
        static unsigned int s_count; // All components must have this

    protected:

    };
}
