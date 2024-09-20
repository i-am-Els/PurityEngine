//
// Created by Eniola Olawale on 9/20/2024.
//

#pragma once
#include "pnt.h"

namespace user_script {

    class QuadComp : private PBehaviourScriptComponent{
    public:
        ~QuadComp() override;

        void update(float deltaTime) override;

        void start() override;

    };

} // user_script
