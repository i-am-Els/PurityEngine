//
// Created by Eniola Olawale on 10/6/2023.
//

#include "../include/log.h"

namespace pnt {

    void PLog::echoMessage(const char *message, LogLevel _level) {
        std::cout << "[" << stringifyLogLevel(_level) << "]" << " " << message << std::endl;
    }

    PLog& PLog::getInstance() {
        static PLog instance;
        PLog::echoMessage("Successfully Initialized PLog!", LogLevel::Info);
        return instance;
    }

    PLog::PLog() = default;

    void PLog::terminate() {
    }

    void PLog::echoMessage(LogLevel _level, const char *message, ...) {
        va_list args;
        va_start(args, message);
        printf("[%s]: ", stringifyLogLevel(_level).c_str());
        vprintf(message, args);
        printf("\n");
        va_end(args);
    }

    PLog::~PLog() = default;
} // pnt