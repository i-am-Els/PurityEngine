//
// Created by Eniola Olawale on 9/21/2024.
//

#pragma once

#include "papplication.h"

#define PURITY_MODE_DEBUG

//extern purity::PApplication * purity::CreateApplication();

#ifdef PURITY_PLATFORM_WINDOWS
PURITY_API int main(int argc, const char* argv[]){
    purity::PApplication* application;

#ifndef PURITY_MODE_DEBUG
    if (argc == 5) {
        if ((
                std::string(argv[1]) != "--projectFile" 
                && std::string(argv[1]) != "-p"
            )
            || 
                std::string(argv[2]).empty()
            || 
            (
                std::string(argv[3]) != "--startUpScene"
                && std::string(argv[3]) != "-s"
            ) 
            || 
                std::string(argv[4]).empty()
            )
        {
            std::cout << "Unknown token" << std::endl;
            std::cout << argv[0] << " | " << argv[1] << " | " << argv[2] << " | " << argv[3] << " | " << argv[4] << " | " << std::endl;
            return 1;
        }

        auto projectFilePath = std::string(argv[2]);
        auto startUpScene = std::string(argv[4]);
        purity::PApplication::ProjectEditorInfo peInfo(projectFilePath, startUpScene);
        purity::PApplication::ApplicationInfo appInfo(peInfo.getProjectName(), 1280, 720);
        std::cout << "Project Name: " << appInfo.title << std::endl;
        application = purity::CreateApplication();
        application->m_applicationInfo = appInfo;
        application->m_projectEditorInfo = peInfo;
    }
    else {
        std::cout << "Cannot Instantiate Editor" << std::endl;
        std::cout << argc << " ==== " << argv << std::endl;
        return 1;
    }
#else
    purity::PApplication::ProjectEditorInfo peInfo("C:\\Dev\\PurityEngine\\TestGame\\TestGame.pproject", "Assets/Scenes/DefaultScene.pscene");
    purity::PApplication::ApplicationInfo appInfo(peInfo.getProjectName(), 1280, 720);
    std::cout << "Project Name: " << appInfo.title << std::endl;
    application = purity::CreateApplication();
    application->m_applicationInfo = appInfo;
    application->m_projectEditorInfo = peInfo;
#endif

    if (!application->verify()) {
        purity::PLog::echoMessage("Verification Process Failed", purity::LogLevel::Error);
        return 1;
    }

    application->init();
    application->start();
    while(!application->window->windowClose())
    {
        // Poll PInput
        application->process();
        // update State
        application->update(1.f);
        // render Scene
        application->render();
    }
    application->destroy();
    // TODO - [Optionally] Make use of a defined game state monitor
    application->exit();

    delete application;
    return 0;
}

// TODO Implement PCameraComponent
// TODO Introduce transformations
// TODO Rendering textures and more shader abstractions

#endif
//#ifdef _WIN32
//#include <windows.h>

//int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd) {
//    return main(__argc, __argv);  // Call your main function
//}

//#endif // _WIN32


//#endif // PURITY_PLATFORM_WINDOWS
