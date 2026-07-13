//
// Created by Eniola Olawale on 5/8/2024.
//

#pragma once

#include <vector>

#include "component.h"
#include "buffer.h"
#include "assets_types.h"

using namespace purity::graphics;

namespace purity::ecs {
    //class P3DGeometricMeshSS;

    struct SRendererProfile {
        bool isVisible;
    };

    class PURITY_API PRendererComponent final : public PComponent, public std::enable_shared_from_this<PRendererComponent> {
    public:
        PRendererComponent();
        explicit PRendererComponent(SRendererProfile profile);
        ~PRendererComponent() override { PLog::echoMessage("Destroying mesh renderer"); }

        void update(float deltaTime) override;
        void start() override;


        P_GET_COMPONENT_TYPE(PComponentType::PRendererComponent)
            void Serialize(cereal::JSONOutputArchive& ar) const override;
        void Deserialize(cereal::JSONInputArchive& ar) override;
        SRendererProfile m_RendererProfile;

    private:
        static unsigned int s_count; // All components must have this

    protected:
        

        //friend class P3DGeometricMeshSS;

    };
}
