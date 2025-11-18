//
// Created by Eniola Olawale on 04/04/2025.
//

#pragma once

#include "purity_core_pch.h"

namespace purity::fileIO {

    class PURITY_API PImporter {
    public:
        virtual bool importFile(const std::string& filePath) = 0;
        virtual ~PImporter() = default;
    };

} // fileIO
// purity