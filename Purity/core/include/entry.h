//
// Created by Eniola Olawale on 9/21/2024.
//

#pragma once

#include "papplication.h"


//extern purity::PApplication * purity::CreateApplication();

#ifdef PURITY_PLATFORM_WINDOWS
PURITY_API int main(){
    auto application = purity::CreateApplication();

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
