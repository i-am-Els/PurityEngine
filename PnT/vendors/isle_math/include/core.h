//
// Created by Eniola Olawale on 12/28/2023.
//

#pragma once

#include <cassert>

// will contain some basic macros
#ifdef ISLE_PLATFORM_WINDOWS
    #ifdef ISLE_BUILD_DLL
        #define ISLE_API __declspec(dllexport)
    #else
        #define ISLE_API __declspec(dllimport)
    #endif
#else
    #error Isle only supports Windows right now
#endif

#define BIT(x) (1 << x) // Left Shift 1 For FlagEnums

#ifdef ISLE_ENABLE_ASSERT
    #define ISLE_ASSERT(expr) assert(expr)
    #define ISLE_ASSERT_MSG(expr, msg) assert(( (void)(msg), (expr) ))
#else
    #define ISLE_ASSERT(expr) //; printf("assert off")
    #define ISLE_ASSERT_MSG(expr, msg)  //; printf("assert off")
#endif
