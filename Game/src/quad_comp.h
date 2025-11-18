//
// Created by Eniola Olawale on 9/20/2024.
//

#pragma once
#include "purity.h"

namespace user_script {

    class QuadComp : public PBehaviourScriptComponent{
    public:
        ~QuadComp() override;

        void update(float deltaTime) override;

        void start() override;

    };

} // user_script
