//
// Created by Eniola Olawale on 10/6/2023.
//

#include "log.h"

namespace pnt {

    Log* Log::instance = nullptr;

    void Log::echoMessage(const char *message, LogLevel _level) {
        std::cout << "[" << LogLevelText[_level] << "]" << " " << message << std::endl;
    }


    void Log::init() {
        if (instance == nullptr)
        {
            instance = new Log();
            Log::echoMessage("Successfully Initialized Log!", LogLevel::Info);
        }
    }

    Log::Log() = default;

    void Log::terminate() {
        delete instance;
        instance = nullptr;
    }

    Log::~Log() = default;
} // pnt