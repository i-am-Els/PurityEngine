//
// Created by Eniola Olawale on 10/6/2023.
//

#include "log.h"

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

    /// @brief This function allows logging multiple strings together
    /// @example PLog::echoMessage(LogLevel::Info, "%s %s %s", "Entity", "in Scene with ID:", static_cast<std::string>(id->m_entityInstanceID).c_str());
    /// @note like in printf, you need to specify the format(%s) first before providing the data("some text");
    /// You then need to concatenate the format...
    void PLog::echoMessage(LogLevel _level, const char *message, ...) {
        va_list args;
        va_start(args, message);
        printf("[%s] ", stringifyLogLevel(_level).c_str());
        vprintf(message, args);
        va_end(args);
        printf("\n");
    }


    PLog::~PLog() = default;
} // pnt