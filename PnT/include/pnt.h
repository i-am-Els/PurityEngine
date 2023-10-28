//
// Created by Eniola Olawale on 10/6/2023.
//

#pragma once
#include "math/entity.h"
#include "math/vector2.h"
#include "math/transform.h"
#include "renderer/renderer.h"
#include "log.h"
#include "input.h"


namespace pnt{
    void pnt_init(){
        // Initialize every subsystem here
        graphics::Renderer::init();
        Log::init();
        Input::init();
    }

    void pnt_terminate(){
        // Terminate every subsystem here
    }
}