#pragma once

// will contain some basic macros
#ifdef PURITY_PLATFORM_WINDOWS
#ifdef COMMON_BUILD_DLL
#define COMMON_API __declspec(dllexport)
#else
#define COMMON_API __declspec(dllimport)
#endif
#else
#error Commons only supports Windows right now
#endif