//
// Created by Eniola Olawale on 6/18/2024.
//

#pragma once

#define PURITY_ENTRY_POINT
#include "purity.h"

using namespace purity;
using namespace purity::ecs;

class Application : public PApplication{
public:

    Application();

    void render() override;

    void process() override;

    void update(float deltaTime) override;

    void init() override;

    void destroy() override;

    void exit() override;

    void start() override;
};


