//
// Created by Eniola Olawale on 10/6/2023.
//

#pragma once
#include "entity.h"
#include "vector2.h"
#include "window_purity.h"
#include "vertex_array.h"
#include "buffer.h"
#include "log.h"
#include "input.h"
#include "data_hash_table.h"
#include "papplication.h"
#include "islemath.h"

// ecs
#include "mesh.h"
#include "transform_ecs.h"
#include "camera.h"
#include "renderer.h"
#include "id_comp.h"
#include "tag_comp.h"
#include "scripting.h"

#ifdef PURITY_ENTRY_POINT
#include "entry.h"
#endif


using namespace purity;
using namespace purity::graphics;

namespace purity{
//    graphics::PWindow pRenderer;
//    PLog pLog;
//    PInput pInput;
//
//    void purity_init(){
//        // Initialize every subsystem here
//        pRenderer = graphics::PWindow::getInstance();
//        pLog = PLog::getInstance();
//        pInput = PInput::getInstance();
//    }
//
//    void purity_terminate(){
//        // Terminate every subsystem here
//        PInput::terminate();
//        graphics::PWindow::terminate();
//        PLog::terminate();
//
//        delete pInput;
//    }
}