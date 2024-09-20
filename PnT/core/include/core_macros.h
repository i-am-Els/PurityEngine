//
// Created by Eniola Olawale on 9/4/2024.
//

#pragma once

#ifdef PNT_ENABLE_ASSERT
#include <cassert>
    #define PNT_ASSERT(expr) assert(expr)
    #define PNT_ASSERT_MSG(expr, msg) assert(( (void)(msg), (expr) ))
#else
    #define PNT_ASSERT(expr)
    #define PNT_ASSERT_MSG(expr, msg)
#endif
