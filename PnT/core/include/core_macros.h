//
// Created by Eniola Olawale on 9/4/2024.
//

#pragma once

#ifdef PNT_PLATFORM_WINDOWS
    #ifdef PNT_BUILD_DLL
        #define PNT_API __declspec(dllexport)
    #else
        #define PNT_API __declspec(dllimport)
    #endif
#else
    #error PNT only supports Windows right now
#endif

#define BIT(x) (1 << x) // Left Shift 1 For FlagEnums

#ifdef PNT_ENABLE_ASSERT
#include <cassert>
    #define PNT_ASSERT(expr) assert(expr)
    #define PNT_ASSERT_MSG(expr, msg) assert(( (void)(msg), (expr) ))
#else
    #define PNT_ASSERT(expr)
    #define PNT_ASSERT_MSG(expr, msg)
#endif
