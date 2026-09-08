//
// Created by Eniola Olawale on 10/10/2024.
//
#pragma once
#include "uuid.h"
#include "glad/glad.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include "ImGuiFileDialog.h"
#include <iostream>
#include <cstring>

#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

#include "content_index.h"
#include "serialize_utilities.h"
#include "common_macros.h"

using fs_path = std::filesystem::path;
using Database = commons::database::ContentIndex;

namespace project
{

	struct ProjectManagerProperties
	{
		const char *win_name;
		ImVec4 clear_color;
		int win_w, win_h;
		bool show_error_popup = false;
	};

	enum class ProjectSelectionChoice
	{
		SelectFromTemplate,
		OpenExisting
	};

	struct ProjectDataStructure
	{
		bool successfulValidation = false;
		std::string filePath;
		std::string projectName;
		std::string projectDir;
		std::string statusMessage;
		std::string startupScene;

		void Log() const
		{
			std::cout << "Status: " << statusMessage << std::endl;
		}
	};

	inline std::ostream &operator<<(std::ostream &os, const ProjectDataStructure &pDS)
	{
		os << "Project Data Structure \n{ \n\tValidated: " << pDS.successfulValidation << ", \n\tFile Path: \"" << pDS.filePath << "\", \n\tProject Name: \"" << pDS.projectName << "\", \n\tProject Dir: \"" << pDS.projectDir << "\", \n\tStartup Scene: \"" << pDS.startupScene << "\", \n\tStatus Message: \"" << pDS.statusMessage << "\"\n}" << std::endl;
		return os; // Return the stream to allow chaining
	}

	struct ProjectManagerState
	{
		ProjectSelectionChoice selectionChoice = ProjectSelectionChoice::SelectFromTemplate;
		ProjectDataStructure pDS{};
		ProjectManagerProperties pmp{};
	};

	class ProjectManager
	{
	public:
		ProjectManager();
		~ProjectManager();
		CMMN_NODISCARD bool extractProjectInformation(std::string projectDir, const std::string &fileName) const;
		CMMN_NODISCARD bool extractProjectInformation(const std::string &filePath) const;
		CMMN_NODISCARD bool createProject(const std::string &projectDir, const std::string &fileName) const;
		void failureReport(const char *message) const;
		CMMN_NODISCARD bool launchProject(const std::string &filePath) const;
		GLFWwindow *m_window;
		ProjectManagerState *m_pms;
		CMMN_NODISCARD bool _createEditorProcess() const;

	private:
		CMMN_NODISCARD bool _validateProjectFile() const;
		CMMN_NODISCARD bool _validateDBFile() const;
		CMMN_NODISCARD bool _createProjectFile() const;
		CMMN_NODISCARD fs_path _getDatabaseFilepath(const fs_path &assets_dir) const;
		CMMN_NODISCARD bool _createDBFile(const fs_path &assets_dir, Database &database, const std::string &query) const;
		// commons::PUUID _createDefaultSceneFile(fs_path scenes_dir);
		static std::string create_new_asset_map_table_query;
	};
}

static void glfw_error_callback(int error, const char *description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
