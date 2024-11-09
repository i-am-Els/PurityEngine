//
// Created by Eniola Olawale on 9/5/2024.
//

#pragma once

// Common stuffs
#include <iostream>
#include <cstdio>
#include <functional>
#include <utility>
#include <algorithm>
#include <memory>
#include <limits>
#include <cmath>
#include <exception>
#include <random>
#include <mutex>
#include <stdexcept>
#include <typeindex>

// Data structures
#include <string>
#include <sstream>
#include <iomanip>
#include <vector>
#include <array>
#include <unordered_map>
#include <map>
#include <unordered_set>


// Windows Specific Includes
#ifdef PNT_PLATFORM_WINDOWS
#include "windows.h"
#endif

#include "uuid.h"
#include "core_macros.h"
#include "pnt_exceptions.h"
#include "log.h"
#include "math/islemath.h"
#include "handle_base.h"