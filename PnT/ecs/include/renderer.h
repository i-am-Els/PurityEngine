//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#include "component.h"

namespace pnt::ecs{


//    class IRenderSystem;
    class PRenderComponent : public PComponent{
    public:
        explicit PRenderComponent(PEntity *entity);
        ~PRenderComponent() override { PLog::echoMessage("Destroying renderComponent"); }

        void update(float deltaTime) override;
        void start() override;

        void SetAddComponentCallback(Traits::AddComponentCallback callback) override;

        void SetGetComponentCallback(Traits::GetComponentCallback callback) override;

        void SetRemoveComponentCallback(Traits::RemoveComponentCallback callback) override;

    private:
        static unsigned int s_count; // All components must have this

    protected:
        static Traits::AddComponentCallback addComponentCallback;
        static Traits::GetComponentCallback getComponentCallback;
        static Traits::RemoveComponentCallback removeComponentCallback;

    };
}
