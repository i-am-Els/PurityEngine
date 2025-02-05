//
// Created by Eniola Olawale on 10/10/2024.
//

#include "project_manager.h"

#include "cereal/cereal.hpp"

#include <filesystem>

#include <iostream>
#include <unordered_map>
#include <fstream>
#include <nlohmann/json.hpp>
#include <nlohmann/json-schema.hpp>

using json = nlohmann::json;
using json_schema_validator = nlohmann::json_schema::json_validator;
using ordered_json = nlohmann::basic_json<nlohmann::ordered_map>;


const ordered_json pProjectSchema = R"(
{
	"$schema": "http://json-schema.org/draft-04/schema#",
	"type" : "object",
	"properties" : {
		"project_name": {
			"type": "string"
		},
		"start_up_scene" : {
			"type": "string",
			"default": "assets/scene/SampleScene.pscene"
		},
		"projectDB" : {
			"type": "string"
		}
	}
	"required": ["project_name", "projectDB"],
})"_json;

const ordered_json pDatabaseSchema = R"(
{
	"$schema": "http://json-schema.org/draft-04/schema#",
	"type": "object",
	"properties": {
	  "id": {
	    "type": "integer"
	  },
	  "assets": {
	    "type": "array",
	    "items": {
	      "$ref": "#/definitions/Asset"
	    }
	  }
	},
	"required": ["id", "assets"],
	"definitions": {
	  "Asset": {
	    "type": "object",
	    "properties": {
	      "id": {
	        "type": "integer"
	      },
	      "path": {
	        "type": "string"
	      }
	    }
	  }
	}
})"_json;


namespace project {
	ProjectManager::ProjectManager() : m_window{ nullptr }, m_pms{ nullptr }
	{
	}

	ProjectManager::~ProjectManager()
	{
		delete m_window;
		delete m_pms;
	}

	ProjectDataStructure ProjectManager::validateProject(std::string projectDir, std::string projectName)
	{
		std::filesystem::path projectPath = { projectDir };
		if (!std::filesystem::is_directory(projectPath)) { return { false, "", "", "", "Project Directory does not exist.", "" }; }
		projectDir = projectDir + "\\" + projectName;
		std::string projectFilePath = projectDir + "\\" + projectName + ".pproject";
		return { true, projectFilePath, projectName, projectDir, "Okay", "" };
	}

	ProjectDataStructure ProjectManager::validateProject(std::string filePath)
	{
		std::filesystem::path _filepath = { filePath };
		if (!std::filesystem::exists(_filepath)) { return { false, "", "", "", "Project File path does not exist.", "" }; }
		std::string projectName = _filepath.stem().string();
		std::string projectDir = _filepath.parent_path().string();
		return { true, filePath, projectName, projectDir, "Okay", "" };
	}

	bool ProjectManager::createProject(ProjectDataStructure pDS)
	{
		m_pms->pDS = pDS;
		bool skipDirCreation = false;
		auto project_dir_path = std::filesystem::path(m_pms->pDS.projectDir);
		// Project Dir Path may or may not already exist
		// If it exists, then it must be an empty directory.
		if (std::filesystem::exists(project_dir_path))
		{
			if (!std::filesystem::is_directory(project_dir_path)) {
				m_pms->pDS.successfulValidation = false;
				m_pms->pDS.statusMessage = "Path is probably not a directory.";
				m_pms->pDS.Log();
				return false;
			}
			if (!std::filesystem::is_empty(project_dir_path)) {
				m_pms->pDS.successfulValidation = false;
				m_pms->pDS.statusMessage = "Path is not empty!, it is fine that the folder already exists, just keep it empty.";
				m_pms->pDS.Log();
				return false;
			}
			skipDirCreation = true;
		}

		if (!skipDirCreation) { std::filesystem::create_directory(project_dir_path); }
		// write pproject file, asset, script and config, assets/scene, and assets/prefabs folders, pedb and pscene files,
		// set startup scene in struct to default name 'assets/scene/SampleScene'

		m_pms->pDS.Log();
		return true;
	}

	bool ProjectManager::launchProject(ProjectDataStructure pDS)
	{
		m_pms->pDS = pDS;
		if (!_validateProjectFile()) { return false; }

		std::ifstream data(m_pms->pDS.filePath);
		json data_json = json::parse(data);
		if (data_json["project_name"] != m_pms->pDS.projectName) 
		{
			m_pms->pDS.successfulValidation = false;
			m_pms->pDS.statusMessage = "Project Name Mismatch!, Ensure that '.pproject' file, project folder and the internally stored projoct name share the same name.";
			m_pms->pDS.Log();
			return false;
		}

		std::string pDBfilePath = "assets\\" + m_pms->pDS.projectName + "\\.peDB";
		if (data_json["projectDB"] != pDBfilePath)
		{
			m_pms->pDS.successfulValidation = false;
			m_pms->pDS.statusMessage = "Project DataBase File Path Mismatch!, Ensure that '.peDB' file's relative path is correct.";
			m_pms->pDS.Log();
			return false;
		}
		if (!_validateDBFile()) { return false; }
		m_pms->pDS.startupScene = data_json["start_up_scene"];
		m_pms->pDS.Log();
		return true;
	}

	bool ProjectManager::_validateProjectFile()
	{
		if (!_validateFileExistence(m_pms->pDS.filePath) && !_validateSchemaAdherence(m_pms->pDS.filePath, JsonSchemaType::PProjectSchema))
		{ 
			m_pms->pDS.successfulValidation = false;
			m_pms->pDS.statusMessage = "Project File Validation Failed!, Ensure the file path exists and the '.pproject' file adheres to its schema specifications.";
			m_pms->pDS.Log();
			return false; 
		}
		return true;
	}

	bool ProjectManager::_validateDBFile()
	{
		std::string pDBfilePath = m_pms->pDS.projectDir + "\\assets\\" + m_pms->pDS.projectName + "\\.peDB";
		std::cout << pDBfilePath << std::endl;
		if (!_validateFileExistence(pDBfilePath) || !_validateSchemaAdherence(pDBfilePath, JsonSchemaType::PDatabaseSchema))
		{
			m_pms->pDS.successfulValidation = false;
			m_pms->pDS.statusMessage = "Project Database File Validation Failed!, Ensure the database file path exists in '.\\assets\\' and that the '.peDB' file adheres to its schema specifications.";
			m_pms->pDS.Log();
			return false; 
		}
		return true;
	}

	bool ProjectManager::_validateFileExistence(std::string path) const
	{
		std::filesystem::path _filepath = { path };
		return std::filesystem::exists(_filepath);
	}

	bool ProjectManager::_validateSchemaAdherence(std::string path, JsonSchemaType type) const {
		
		std::ifstream data(path); 
		json data_json = json::parse(data);
		if (!data && !data_json) { return false; }
		json schema;
		switch (type)
		{
		case project::JsonSchemaType::PProjectSchema:
			schema = pProjectSchema;
			break;
		case project::JsonSchemaType::PDatabaseSchema:
			schema = pDatabaseSchema;
			break;
		default:
			break;
		}

		json_schema_validator validator;
		validator.set_root_schema(schema);
		try {
			validator.validate(data_json);
			std::cout << "Validation succeeded\n";
		}
		catch (const std::exception& e) {
			std::cerr << "Validation failed, here is why: " << e.what() << "\n";
			return false;
		}
		// Further schema validation logic can go here
		return true;
	}

}


void ShowNewProjectTab(project::ProjectManager* projectManager) {
	if (ImGui::BeginTabItem("New Project"))
	{
		projectManager->m_pms->selectionChoice = project::ProjectSelectionChoice::SelectFromTemplate;

		// Enter Project Name
		static char buf[24];
		ImGui::Text("Create a new empty project or start with a template.");
		ImGui::Text("Enter Project Name"); ImGui::SameLine();
		ImGui::PushItemWidth(200);  // Set the width to 100 pixels
		ImGui::InputText("##Input", buf, 24, ImGuiInputTextFlags_CharsNoBlank);
		ImGui::PopItemWidth();      // Restore the previous item width

		ImGui::SameLine();
		if (ImGui::Button("Select Location")) {
			IGFD::FileDialogConfig config; config.path = ".";
			config.countSelectionMax = 1;
			config.flags = ImGuiFileDialogFlags_Modal;
			// Select Directory, "uses nullptr as filter"
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose Project Directory", nullptr, config);
		}

		if (!projectManager->m_pms->pDS.projectDir.empty())
		{
			ImGui::TextColored(ImVec4(0.7f, 0.1f, 0.6f, 1.f), "Project Location: ");
			ImGui::SameLine();
			ImGui::Text("%s", projectManager->m_pms->pDS.projectDir.c_str());
		}

		// Render the file dialog for Selecting Project Location
		if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
			if (ImGuiFileDialog::Instance()->IsOk()) {
				// User selected Dir
				projectManager->m_pms->pDS.projectDir = ImGuiFileDialog::Instance()->GetCurrentPath();
			}
			// Close the dialog after processing the result
			ImGuiFileDialog::Instance()->Close();
		}
		if (buf[0] != '\0')
		{
			ImGui::TextColored(ImVec4(0.7f, 0.1f, 0.6f, 1.f), "Project Name: ");
			ImGui::SameLine();
			ImGui::Text("%s", buf);
		}
		if (ImGui::Button("Create") && buf[0] != '\0' && !projectManager->m_pms->pDS.projectDir.empty())
		{
			// Validate the file or use it to create the project
			projectManager->m_pms->pDS = projectManager->validateProject(projectManager->m_pms->pDS.projectDir, buf);
			if (!projectManager->createProject(projectManager->m_pms->pDS)) { return; }
			std::cout << projectManager->m_pms->pDS << std::endl;
			buf[0] = '\0';
		}
		ImGui::EndTabItem();
	}
}

void ShowOpenExistingProjectTab(project::ProjectManager* projectManager)
{
	if (ImGui::BeginTabItem("Open Recent"))
	{
		projectManager->m_pms->selectionChoice = project::ProjectSelectionChoice::OpenExisting;
		ImGui::Text("Select existing projects from drive.");
		ImGui::SameLine();
		if (ImGui::Button("Choose")) {
			IGFD::FileDialogConfig config; config.path = ".";
			config.countSelectionMax = 1;
			config.flags = ImGuiFileDialogFlags_Modal;
			ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose Purity Project File(*.pproject)", ".pproject", config);
		}

		// Render the file dialog
		if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
			if (ImGuiFileDialog::Instance()->IsOk()) {
				// User selected a file
				projectManager->m_pms->pDS.filePath = ImGuiFileDialog::Instance()->GetFilePathName();
			}
			// Close the dialog after processing the result
			ImGuiFileDialog::Instance()->Close();
		}

		if (!projectManager->m_pms->pDS.filePath.empty())
		{
			ImGui::Text("%s", projectManager->m_pms->pDS.filePath.c_str());
			if (ImGui::Button("Open"))
			{
				// Validate the file or use it to create the project
				projectManager->m_pms->pDS = projectManager->validateProject(projectManager->m_pms->pDS.filePath);
				if (!projectManager->launchProject(projectManager->m_pms->pDS)) { return; }
				std::cout << projectManager->m_pms->pDS << std::endl;
			}
		}
		ImGui::EndTabItem();
	}
}

void ShowTemplateWindow(project::ProjectManager* projectManager)
{
	if (ImGui::Begin("Templates"))
	{
		ImGui::Text("I am fulfilled today");
		ImGui::End();
	}
}


int main() {
	project::ProjectManager projectManager;
	project::ProjectManagerProperties pmp{ "Purity Gem", ImVec4(0.45f, 0.55f, 0.60f, 1.00f), 600, 480 };
	bool showTemplate;

	glfwSetErrorCallback(glfw_error_callback);
	if (glfwInit() != GLFW_TRUE) {
		return 1;
	}

	const char* glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	projectManager.m_window = glfwCreateWindow(pmp.win_w, pmp.win_h, pmp.win_name, nullptr, nullptr);
	if (projectManager.m_window == nullptr) {
		glfwTerminate();
		return 1;
	}

	glfwMakeContextCurrent(projectManager.m_window);
	int status = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
	if (!status)
		std::cout << "Failed to load Glad." << std::endl;
	glfwSwapInterval(1); // Enable vsync

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO(); (void)io;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;		  // Enable Docking
	io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
	//io.ConfigViewportsNoAutoMerge = true;
	io.ConfigViewportsNoTaskBarIcon = true;

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight(); // Light Mode

	// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.0f;
		style.Colors[ImGuiCol_WindowBg].w = 1.0f;
	}

	ImGui_ImplGlfw_InitForOpenGL(projectManager.m_window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	while (!glfwWindowShouldClose(projectManager.m_window)) {
		glfwPollEvents();
		if (glfwGetWindowAttrib(projectManager.m_window, GLFW_ICONIFIED) != 0)
		{
			ImGui_ImplGlfw_Sleep(10);
			continue;
		}
		// Start the Dear ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		// ImGui Window Widget Rendering
		{
			ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_None);

			ImGui::Begin("Project Manager", nullptr, ImGuiWindowFlags_NoMove);
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
			{
				// Select New Project
				ShowNewProjectTab(&projectManager);
				// Open Recent Tab
				ShowOpenExistingProjectTab(&projectManager);

				if (showTemplate = projectManager.m_pms->selectionChoice == project::ProjectSelectionChoice::SelectFromTemplate ? true : false)
				{
					ShowTemplateWindow(&projectManager);
				}
				ImGui::EndTabBar();
			}
			ImGui::Separator();

			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
			ImGui::End();
		}

		// Rendering
		ImGui::Render();
		int display_w, display_h;
		// Get the real-time size of the window
		glfwGetFramebufferSize(projectManager.m_window, &display_w, &display_h);
		// Use that size to set the viewport
		glViewport(0, 0, display_w, display_h);
		glClearColor(pmp.clear_color.x, pmp.clear_color.y, pmp.clear_color.z, pmp.clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}

		glfwSwapBuffers(projectManager.m_window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(projectManager.m_window);
	glfwTerminate();

	return 0;
}