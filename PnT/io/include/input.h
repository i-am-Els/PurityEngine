//
// Created by Eniola Olawale on 10/6/2023.
//

#pragma once
#include "log.h"
#include "input_def.h"

namespace pnt {

    class PNT_API PInput {
    private:
        PInput();
    public:
        ~PInput();

        [[nodiscard]] static PInput& getInstance();
        static void terminate();
        static void PollEvents();
        static bool isKeyPressed(int keyCode);
    };

} // pnt

