//
// Created by emman on 7/25/2024.
//

#pragma once

#include "ecs_service.h"
#include "service_base.h"

namespace pnt{
    class PECSService : public PServiceBase<IECSService>{
    public:
        PECSService() = default;

        explicit PECSService(PWindow* _window){
            renderSystem = std::make_shared<POpenGLRenderSS>(_window->getWindow());
        }

        ~PECSService() override = default;

        void init() override {
            renderSystem->init();
        }

        void process() override {
            renderSystem->process();
        }

        void render() override {
            renderSystem->render();
        }

        void update(float deltaTime) override{
            renderSystem->update(deltaTime);
        }

        void destroy() override{
            renderSystem->destroy();
        }

        void start() override {
            renderSystem->start();
        }

        std::shared_ptr<IRenderSystem> renderSystem;

    };

}
