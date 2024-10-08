//
// Created by Eniola Olawale on 10/6/2023.
//


#include "input.h"
#include "GLFW/glfw3.h"

namespace pnt {

    PInput::PInput()= default;

    PInput& PInput::getInstance() {
        static PInput instance;
        PLog::echoMessage("Successfully Initialized PInput!", LogLevel::Info);
        return instance;
    }

    void PInput::terminate() {
    }

    PInput::~PInput() {
        PLog::echoMessage("Destroying Input.");
    }

    bool PInput::isKeyPressed(int keyCode) {
        /// @brief  Code Example
        /// @code
        /// while(!PInput::isKeyPressed(P_KEY_A)){
        ///        std::cout << "A";
        ///    }
        ///
        /// @endcode
        /// Continuously prints A until the key A is clicked...
        return (GetAsyncKeyState(keyCode) & 0x8000) != 0;
    }

    void PInput::PollEvents() {
        glfwPollEvents();
    }


} // pnt