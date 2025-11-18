//
// Created by Eniola Olawale on 09/07/2025.
//

#pragma once

namespace editor::layers {

    class GameLayer final : public PLayer {
    public:
        [[nodiscard]] GameLayer() : PLayer(){}

        [[nodiscard]] explicit GameLayer(const std::string& name)
            : PLayer(name)
        {
        }

        void update() override;
        void attached() override;
        void detached() override;
        void eventFired(Event& event) override;
        void render() override;
    };
}


