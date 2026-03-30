//
// Created by Eniola Olawale on 9/13/2024.
//

#pragma once
#include "purity_core_pch.h"

// TODO - Rather than have so many of the asset operation classes implement so many utility I/O operations, all of thwm are done via thhis utility.
// This is the part of the system that communicates with the FileI/O system.
namespace purity::assetDB
{
    class PURITY_API PAssetDBUtility {
        public:
        PAssetDBUtility() = default;
        ~PAssetDBUtility() = default;

        static std::filesystem::path resolveProjectPath(const std::string& relPath);

        static PAssetDBUtility* instance;
    };
}

