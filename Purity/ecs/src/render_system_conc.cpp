//
// Created by Eniola Olawale on 6/17/2024.
//
#include "render_system_conc.h"
#include "entity.h"
#include "fileio.h"
#include "log.h"


using namespace purity::fileIO;

namespace purity::ecs {

    void POpenGLRenderSS::init() {

    }

    void POpenGLRenderSS::start() {

    }

    void POpenGLRenderSS::process() {
    }

    void POpenGLRenderSS::update(float deltaTime) {

    }

    void POpenGLRenderSS::render() {
    }

    void POpenGLRenderSS::destroy() {

    }

    POpenGLRenderSS::POpenGLRenderSS() {
        renderComponents.reserve(128);
    }

    POpenGLRenderSS::~POpenGLRenderSS() {
        PLog::echoMessage("Destroying OpenGL Render System.");
    }

    std::weak_ptr<PRenderComponent> POpenGLRenderSS::AddComponent(std::weak_ptr<PEntity> entity) {
        try {
            SRenderProfile profile = {true}; // Set the profile of the render component, through the DTO
            renderComponents.emplace_back(std::make_shared<PRenderComponent>(entity, profile));
            return renderComponents.back();
        } catch (...) {
            PLog::echoMessage(LogLevel::Error, "Add Render Comp Generic Assertion failed");
        }
        return {};
    }

    void POpenGLRenderSS::RemoveComponent(std::weak_ptr<PEntity> entity, std::weak_ptr<PRenderComponent> component) {

    }

}
