//
// Created by Eniola Olawale on 9/4/2024.
//

#pragma once

#include <cassert>
#ifdef PNT_ENABLE_ASSERT
#define PNT_ASSERT(expr) assert(expr)
    #define PNT_ASSERT_MSG(expr, msg) assert(( (void)(msg), (expr) ))
#else
    #define PNT_ASSERT(expr) assert(expr)
    #define PNT_ASSERT_MSG(expr, msg) assert(( (void)(msg), (expr) ))
#endif
