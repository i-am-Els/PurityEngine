//
// Created by Eniola Olawale on 10/10/2024.
//

#include "p_editor_application.h"


namespace gui {

    PEditorApplication::~PEditorApplication() {

    }

    void PEditorApplication::init() {
        PApplication::init();
    }

    void PEditorApplication::start() {
        PApplication::start();
    }

    void PEditorApplication::process() {
        PApplication::process();
    }

    void PEditorApplication::update(float deltaTime) {
        PApplication::update(deltaTime);
    }

    void PEditorApplication::render() {
        PApplication::render();
    }

    void PEditorApplication::destroy() {
        PApplication::destroy();
    }

    void PEditorApplication::exit() {
        PApplication::exit();
    }

    PEditorApplication::PEditorApplication(const std::string &title, int width, int height) : PApplication(title, width, height) {
    }
} // gui



pnt::PApplication* pnt::CreateApplication(){
    return new gui::PEditorApplication("PnT", 700, 500);
}
