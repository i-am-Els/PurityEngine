//
// Created by Eniola Olawale on 10/6/2023.
//

#pragma once
#include <iostream>
#include <cstdarg>
#include "global.h"

namespace pnt {
    enum class LogLevel{
        Error = 0, Warning, Info
    };

    inline static std::string stringifyLogLevel(LogLevel x)
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

    class PLog {
    private:
        PLog();
    public:
        static LogLevel level;
        [[nodiscard]] static PLog& getInstance();
        static void echoMessage(const char* message, LogLevel _level = LogLevel::Info);
        static void echoMessage(LogLevel _level = LogLevel::Info, const char* message = "", ...);

        template<class T>
        static void echoValue(T value){
            std::cout << "[Value] " << value << std::endl;
        }
        static void terminate();
        ~PLog();
    };

} // pnt


