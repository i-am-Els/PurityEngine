//
// Created by Eniola Olawale on 10/10/2024.
//

#include "project_manager.h"

#include "cereal/cereal.hpp"

#include <string.h>


namespace project {

    ProjectDataStructure ProjectManager::validateProject(const char* projectFilePath)
    {
        if (projectFilePath == "")
            projectFilePath = "Game/Game.pproject";
        const char* p = "Game";
        projectFilePath = "%s/%s.pproject";
        
        // open_file
        return {};
    }
    bool ProjectManager::createProject(ProjectDataStructure pDS)
    {
        return false;
    }
    void ProjectManager::launchProject(ProjectDataStructure pDS)
    {
    }
}
