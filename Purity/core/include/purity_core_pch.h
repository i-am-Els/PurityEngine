//
// Created by Eniola Olawale on 9/5/2024.
//

#pragma once

// Common stuffs
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <exception>
#include <functional>
#include <iostream>
#include <limits>
#include <memory>
#include <mutex>
#include <random>
#include <stdexcept>
#include <typeindex>
#include <utility>
#include <variant>

// Data structures
#include <array>
#include <iomanip>
#include <map>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>


// Windows Specific Includes
#ifdef PURITY_PLATFORM_WINDOWS
#include "windows.h"
#endif

#include "color.h"
#include "handle_base.h"
#include "iserializable.h" // already includes uuid.h, and core_macros.h
#include "log.h"
#include "purity_exceptions.h"
#include "serialize_utilities.h"
#include "math/islemath.h"

#include "data_hash_table.h"

#ifdef PURITY_SYSTEM_FINDER
#include "system_finder.h"
#endif
