//
// Created by Eniola Olawale on 10/10/2024.
//
#pragma once
#include "glad/glad.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include "ImGuiFileDialog.h"

#include <iostream>
#include <string.h>


using fs_path = std::filesystem::path;


namespace project {

	struct ProjectManagerProperties {
		const char* win_name;
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
		std::string filePath = "";
		std::string projectName = "";
		std::string projectDir = "";
		std::string statusMessage = "";
		std::string startupScene = "";

		void Log() const {
			std::cout << "Status: " << statusMessage << std::endl;
		}
	};

	std::ostream& operator<<(std::ostream& os, const ProjectDataStructure& pDS) {
		os << "Project Data Structure \n{ \n\tValidated: " << pDS.successfulValidation << ", \n\tFile Path: \"" << pDS.filePath << "\", \n\tProject Name: \"" << pDS.projectName << "\", \n\tProject Dir: \"" << pDS.projectDir << "\", \n\tStartup Scene: \"" << pDS.startupScene << "\", \n\tStatus Message: \"" << pDS.statusMessage << "\"\n}" << std::endl;
		return os;  // Return the stream to allow chaining
	}

	struct ProjectManagerState {
		ProjectSelectionChoice selectionChoice = ProjectSelectionChoice::SelectFromTemplate;
		ProjectDataStructure pDS{};
		ProjectManagerProperties pmp{};
	};

	enum class JsonSchemaType
	{
		PProjectSchema = 0, PDatabaseSchema
	};

	class ProjectManager {
	public:
		ProjectManager();
		~ProjectManager();
		bool extractProjectInformation(std::string projectDir, std::string fileName);
		bool extractProjectInformation(std::string filePath);
		bool createProject(std::string projectDir, std::string fileName);
		bool launchProject(std::string filePath);
		GLFWwindow* m_window;
		ProjectManagerState* m_pms
			;
	private:
		// Existing Project
		bool _validateProjectFile();
		bool _validateDBFile();
		bool _validateFileExistence(std::string path) const;
		bool _validateSchemaAdherence(std::string path, JsonSchemaType type) const;
		bool _createProjectFile();
		bool _createDBFile(fs_path assets_dir);
		bool _createDefaultSceneFile(fs_path scenes_dir);
	};
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}
