//
// Created by Eniola Olawale on 10/6/2023.
//

#pragma once
#include <iostream>
#include <cstdarg>
#include "global.h"

namespace pnt {
    enum LogLevel{
        Error = 0, Warning, Info
    };

    class Log {
    public:
        static Log* instance;
        static LogLevel level;
        static void init();
        static void echoMessage(const char* message, LogLevel _level = LogLevel::Info);
        static void echoMessage(LogLevel _level = LogLevel::Info, const char* message = "", ...) {
            va_list args;
            va_start(args, message);
            printf("%s: ", LogLevelText[_level]);
            vprintf(message, args);
            printf("\n");
            va_end(args);
        }

        template<class T>
        static void echoValue(T value){
            std::cout << "[Value] " << value << std::endl;
        }
        static void terminate();

        ~Log();
    private:
        Log();
    };

} // pnt


