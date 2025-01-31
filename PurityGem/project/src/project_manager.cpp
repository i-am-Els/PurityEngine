//
// Created by Eniola Olawale on 10/10/2024.
//

#include "project_manager.h"

#include "cereal/cereal.hpp"

#include <filesystem>



namespace project {

    ProjectDataStructure ProjectManager::validateProject(std::string projectFilePath, std::string fileName)
    {
        std::string projectName = fileName.substr(0, fileName.find(".pproject"));
        std::string projectDir = projectFilePath.substr(0, projectFilePath.rfind(fileName));

        if (projectDir.empty())
        {
            projectFilePath = std::filesystem::current_path().string() + "\\Game\\Game.pproject";
            projectDir = projectFilePath.substr(0, projectFilePath.rfind("Game.pproject"));
            projectName = "Game";
        }

        std::cout << projectFilePath << std::endl;
        std::cout << projectName << std::endl;
        std::cout << projectDir << std::endl;

        // open_file
        return {true, projectFilePath, projectName, projectDir};
    }

    bool ProjectManager::createProject(ProjectDataStructure pDS)
    {
        return false;
    }

    void ProjectManager::launchProject(ProjectDataStructure pDS)
    {

    }

    void ProjectManager::selectProjectFolderDialog()
    {
    }

    void ProjectManager::openProjectFromFileDialog()
    {
    }
}
