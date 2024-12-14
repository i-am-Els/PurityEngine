//
// Created by Eniola Olawale on 10/6/2023.
//

#include "log.h"

namespace pnt {

    void PLog::echoMessage(const char *message, LogLevel _level) {

        switch (_level) {
            case LogLevel::Error:
                std::cout << "[Error]: \033[91m" << message << "\033[0m" << std::endl;
                break;
            case LogLevel::Warning:
                std::cout << "[Warning]: \033[93m" << message << "\033[0m" << std::endl;
                break;
            case LogLevel::Info:
                std::cout << "[Info]: \033[94m" << message << "\033[0m" <<std::endl;
                break;
        }
    }

    PLog& PLog::getInstance() {
        static PLog instance;
        PLog::echoMessage("Successfully Initialized PLog!", LogLevel::Info);
        return instance;
    }

    PLog::PLog() = default;

    void PLog::terminate() {
    }

    std::string PLog::stringifyLogLevel(LogLevel x)
    {
        std::string outString;
        switch(x)
        {
            case LogLevel::Error:
                outString = "Error";
                break;
            case LogLevel::Warning:
                outString = "Warning";
                break;
            case LogLevel::Info:
                outString = "Info";
                break;
        }
        return outString;
    }

    /// @brief This function allows logging multiple strings together
    /// @example PLog::echoMessage(LogLevel::Info, "%s %s %s", "Entity", "in Scene with ID:", static_cast<std::string>(id->m_entityInstanceID).c_str());
    /// @note like in printf, you need to specify the format(%s) first before providing the data("some text");
    /// You then need to concatenate the format...
    void PLog::echoMessage(LogLevel _level, const char *message, ...) {
        va_list args;
        va_start(args, message);
        switch (_level) {

            case LogLevel::Error:
                printf("[%s] \033[91m", stringifyLogLevel(_level).c_str());
                break;
            case LogLevel::Warning:
                printf("[%s] \033[93m", stringifyLogLevel(_level).c_str());
                break;
            case LogLevel::Info:
                printf("[%s] \033[94m", stringifyLogLevel(_level).c_str());
                break;
        }
        vprintf(message, args);
        va_end(args);
        printf("\n\033[0m");
    }


    PLog::~PLog() = default;
} // pnt