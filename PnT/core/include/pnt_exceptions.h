//
// Created by Eniola Olawale on 9/14/2024.
//

#pragma once
#include "pnt_core_pch.h"

namespace pnt::exceptions
{
    class PNT_API NullBufferError final : public std::exception
    {
    public:
        [[nodiscard]] const char* what() const noexcept override{
            return "Buffer pointer is a null pointer";
        }
    };
}
