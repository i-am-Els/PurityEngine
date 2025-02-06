//
// Created by Eniola Olawale on 10/10/2024.
//

#pragma once
#define PURITY_ENTRY_POINT
#include "purity.h"

using namespace purity;

namespace gui {

    class PEditorApplication : public PApplication{
    public:
        PEditorApplication(const std::string &title, int width, int height);

        ~PEditorApplication() override;

        void init() override;

        void start() override;

        void process() override;

        void update(float deltaTime) override;

        void render() override;

        void destroy() override;

        void exit() override;
    };

} // gui
