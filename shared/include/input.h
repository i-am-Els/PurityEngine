//
// Created by Eniola Olawale on 10/6/2023.
//

#pragma once
#include "log.h"
#include "input_def.h"

namespace pnt {

    class Input {
    public:
        ~Input();
        static Input* instance;

        static void init();
        static void terminate();
        static bool isKeyPressed(int keyCode);
    private:
        Input();
    };

} // pnt

