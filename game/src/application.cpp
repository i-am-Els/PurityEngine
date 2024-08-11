//
// Created by Eniola Olawale on 6/18/2024.
//

#include "application.h"
#ifdef HACK_
#include "render_system_conc.h"
#include "ecs_service.h"
#include "ecs_service_conc.h"

using namespace pnt;
#endif //HACK_

void Application::render() {
    PApplication::render();
}

void Application::process() {
    PApplication::process();
}

void Application::update(float deltaTime) {
    PApplication::update(deltaTime);
}

void Application::init() {
    PApplication::init();

    quad = new PEntity("Quad");

    auto mesh = quad->AddComponent<PMeshComponent>();
    auto render = quad->AddComponent<PRenderComponent>();
#ifdef HACK_
    try{
        auto item = dynamic_cast<PECSService *>(serviceLocator->getService<IECSService>().get());
        if (item == nullptr)
            throw "Invalid Service";
        auto r = PECSService::s_getSystem<PRenderComponent>();
        auto renderer = dynamic_cast<POpenGLRenderSS*>(r);
        renderer->SetHackMeshBuffers(mesh->getVBO(), mesh->getEBO());   // TODO - Prevent segfault caused because mesh is null at this point.
        // TODO - Implement the mesh systems functions for all Manipulative Behaviours
    }catch(const char* msg){
        std::cerr << "Error: " << msg << std::endl;
    }
#endif //HACK_
    PLog::echoValue(quad->GetComponent<PTransformComponent>()->m_up); // Segfault here too, transform is null

}

void Application::start() {
    PApplication::start();
}

void Application::destroy() {
    PApplication::destroy();
}

Application::Application(const std::string &title, int width, int height) : PApplication(title, width, height) {
    quad = nullptr;
}

void Application::exit() {
    PApplication::exit();
    delete quad;
}



