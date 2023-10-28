//
// Created by Eniola Olawale on 10/6/2023.
//


#include "input.h"

namespace pnt {
    Input* Input::instance = nullptr;

    Input::Input()= default;

    void Input::init() {
        if (instance == nullptr){
            instance = new Input();
            Log::echoMessage("Successfully Initialized Input!", LogLevel::Info);
        }
    }

    void Input::terminate() {

        delete instance;
        instance = nullptr;
    }

    Input::~Input() = default;

    bool Input::isKeyPressed(int keyCode) {
        /// @brief  Code Example
        /// @code
        /// while(!Input::isKeyPressed(P_KEY_A)){
        ///        std::cout << "A";
        ///    }
        ///
        /// @endcode
        /// Continuously prints A until the key A is clicked...
        return (GetAsyncKeyState(keyCode) & 0x8000) != 0;
    }


} // pnt