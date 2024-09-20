//
// Created by Eniola Olawale on 10/6/2023.
//

#pragma once
#include "entity.h"
#include "vector2.h"
#include "transform_ecs.h"
#include "window_pnt.h"
#include "vertex_array.h"
#include "buffer.h"
#include "log.h"
#include "input.h"
#include "data_hash_table.h"
#include "islemath.h"
#include "papplication.h"

// ecs
#include "mesh.h"
#include "transform_ecs.h"
#include "camera.h"
#include "renderer.h"
#include "id_comp.h"
#include "scripting.h"


using namespace pnt;
using namespace pnt::graphics;



namespace pnt{
//    graphics::PWindow pRenderer;
//    PLog pLog;
//    PInput pInput;
//
//    void pnt_init(){
//        // Initialize every subsystem here
//        pRenderer = graphics::PWindow::getInstance();
//        pLog = PLog::getInstance();
//        pInput = PInput::getInstance();
//    }
//
//    void pnt_terminate(){
//        // Terminate every subsystem here
//        PInput::terminate();
//        graphics::PWindow::terminate();
//        PLog::terminate();
//
//        delete pInput;
//    }
}