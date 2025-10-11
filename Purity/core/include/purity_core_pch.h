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
#include <variant>

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
#ifdef PURITY_PLATFORM_WINDOWS
#include "windows.h"
#endif

#include "uuid.h"
#include "serialize_utilities.h"
#include "core_macros.h"
#include "purity_exceptions.h"
#include "log.h"
#include "math/islemath.h"
#include "handle_base.h"
#include "color.h"

#include "data_hash_table.h"

#ifdef PURITY_SYSTEM_FINDER
#include "system_finder.h"
#endif
