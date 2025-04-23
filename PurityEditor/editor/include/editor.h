//
// Created by Eniola Olawale on 10/6/2024.
//

#pragma once
#include "events.h"
#include "layer.h"

using namespace purity;

namespace editor::gui{

    class ExampleLayer : public purity::PLayer
    {
    public:
        ExampleLayer() : purity::PLayer("Example")
        {}

        void update() override
        {
            // PLog::echoMessage(LogLevel::Info, "ExampleLayer::Update");
        }

        void eventFired(Event& event) override
        {
            PLog::echoMessage(LogLevel::Info, event.getName());
        }
    };

    class Editor : public purity::PLayer{


    };

}

