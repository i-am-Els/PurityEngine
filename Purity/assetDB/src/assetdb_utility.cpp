//
// Created by Eniola Olawale on 9/13/2024.
//

#include "assetdb_utility.h"
#include <filesystem>

#include "papplication.h"
#include "system_finder.h"

namespace purity::assetDB{
    std::filesystem::path PAssetDBUtility::buildAbsolutePathFromRel(const std::string& relPath)
    {
        auto fullPath = PSystemFinder::GetApplication()->m_projectEditorInfo.projectDir + "/" + relPath;
        return fs_path(fullPath);
    }
}
