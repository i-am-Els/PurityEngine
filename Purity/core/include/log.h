//
// Created by Eniola Olawale on 10/6/2023.
//

#pragma once

#include "core_macros.h"
#include <iostream>
#include <cstdarg>

namespace purity {
    enum class LogLevel{
        Error = 0, Warning, Info
    };

    class PURITY_API PLog {
    private:
        PLog();
        static std::string stringifyLogLevel(LogLevel x);
    public:
        static LogLevel level;
        [[nodiscard]] static PLog& getInstance();
        static void echoMessage(const char* message, LogLevel _level = LogLevel::Info);
        static void echoMessage(LogLevel _level = LogLevel::Info, const char* message = "", ...);

        template<class T>
         static void echoValue(T value){
            std::cout << "[Value] \033[92m" << value << "\033[0m" << std::endl;
        }
        static void terminate();
        ~PLog();
    };

} // purity


