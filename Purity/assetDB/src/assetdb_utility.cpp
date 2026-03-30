//
// Created by Eniola Olawale on 9/13/2024.
//

#include "assetdb_utility.h"
#include <filesystem>

#include "papplication.h"
#include "system_finder.h"

namespace purity::assetDB{
    /// @brief This method builds the indexed relative paths into absolute paths that is reliable for runtime use.
    /// @note Your path must follow the constraints of the Project's Canonical form "Asset/Scene/DefaultProjectScene.pscene" instead of
    /// forms like:
    /// - "/Asset/Scene/DefaultProjectScene.pscene"
    /// - "./Asset/Scene/DefaultProjectScene.pscene"
    /// - "../Asset/Scene/DefaultProjectScene.pscene"
    std::filesystem::path PAssetDBUtility::resolveProjectPath(const std::string& relPath)
    {
#ifdef PURITY_DEBUG
        if (std::filesystem::path(projectRelativePath).is_absolute())
        {
            throw std::logic_error(
                "resolveProjectPath expects a project-relative path"
            );
        }
#endif

        const auto& projectDir =
            PSystemFinder::GetApplication()->m_projectEditorInfo.projectDir;

        return std::filesystem::path(projectDir)
            / std::filesystem::path(relPath).lexically_normal();
    }
}
