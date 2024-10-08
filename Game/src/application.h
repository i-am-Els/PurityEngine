//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#define PNT_ENTRY_POINT
#include "pnt.h"

using namespace pnt;
using namespace pnt::ecs;

class Application : public PApplication{
public:

    Application(const std::string &title, int width, int height);

    void render() override;

    void process() override;

    void update(float deltaTime) override;

    void init() override;

    void destroy() override;

    void exit() override;

    void start() override;

    PEntity* quad;
};


