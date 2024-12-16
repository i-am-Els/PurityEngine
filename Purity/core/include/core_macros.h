//
// Created by Eniola Olawale on 9/4/2024.
//

#pragma once

#ifdef PURITY_PLATFORM_WINDOWS
    #ifdef PURITY_BUILD_DLL
        #define PURITY_API __declspec(dllexport)
    #else
        #define PURITY_API __declspec(dllimport)
    #endif
#else
    #error PNT only supports Windows right now
#endif

#define BIT(x) (1 << x) // Left Shift 1 For FlagEnums

#ifdef PURITY_ENABLE_ASSERT
#include <cassert>
    #define PURITY_ASSERT(expr) assert(expr)
    #define PURITY_ASSERT_MSG(expr, msg) assert(( (void)(msg), (expr) ))
#else
    #define PURITY_ASSERT(expr)
    #define PURITY_ASSERT_MSG(expr, msg)
#endif

#ifdef _WIN32
#include <windows.h>
#define PURITY_DEBUG_MT_LOG(msg) PLog::echoMessage(std::string("Thread_id: (") + std::to_string(GetCurrentThreadId()) + ") " + msg)
#else
#define PURITY_DEBUG_MT_LOG(msg) PLog::echoMessage(msg)
#endif