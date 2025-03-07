//
// Created by Eniola Olawale on 10/10/2024.
//

#include "project_manager.h"
#include "serialize_utilities.h"

#include "cereal/cereal.hpp"

#include <filesystem>
#include <windows.h>

#include <iostream>
#include <unordered_map>
#include <fstream>

using json = nlohmann::json;
using json_schema_validator = nlohmann::json_schema::json_validator;
using ordered_json = nlohmann::basic_json<nlohmann::ordered_map>;


namespace project {
	ProjectManager::ProjectManager() : m_window{ nullptr }
	{
		m_pms = new ProjectManagerState{ ProjectSelectionChoice::SelectFromTemplate, { false, "", "", "", "", "" }, {} };
	}

	ProjectManager::~ProjectManager()
	{
		delete m_pms;
	}

	bool ProjectManager::extractProjectInformation(std::string projectDir, std::string projectName)
	{
		fs_path projectPath = { projectDir };
		if (!std::filesystem::is_directory(projectPath)) 
		{ 
			m_pms->pDS = { false, "", "", "", "Project Directory does not exist.", "" };
			return false; 
		}
		projectDir = projectDir + "\\" + projectName;
		std::string projectFilePath = projectDir + "\\" + projectName + ".pproject";
		m_pms->pDS = { true, projectFilePath, projectName, projectDir, "Okay", "" };
		return true;
	}

	bool ProjectManager::extractProjectInformation(std::string filePath)
	{
		fs_path _filepath = { filePath };
		if (!std::filesystem::exists(_filepath)) 
		{ 
			m_pms->pDS = { false, "", "", "", "Project File path does not exist.", "" };
			return false; 
		}
		std::string projectName = _filepath.stem().string();
		std::string projectDir = _filepath.parent_path().string();
		m_pms->pDS = { true, filePath, projectName, projectDir, "Okay", "" };
		return true;
	}

	bool ProjectManager::_createProjectFile() 
	{
		// Define the default project JSON structure
		json project_json = {
			{"project_name", m_pms->pDS.projectName},
			{"start_up_scene", "Assets/Scenes/DefaultScene.pscene"},
			{"projectDB", "Assets/" + m_pms->pDS.projectName + ".peDB"}
		};
		
		std::fstream project_file(m_pms->pDS.filePath, std::ios::out | std::ios::trunc);
		if (project_file.is_open()) {
			project_file << project_json.dump(4); // Example placeholder
			project_file.close();
		}
		else {
			std::cerr << "Failed to create .pproject file!" << std::endl;
			return false;
		}
		return true;
	}

	bool ProjectManager::_createDBFile(fs_path assets_dir, commons::PUUID id)
	{
		// Define the default database JSON structure
		// Create the database JSON object with a unique id
		json db_json = {
			{"id", commons::PUUID()},  // Replace with your UUID generation function
			{"assets", json::array()}  // Initialize assets as an empty array
		};

		// Add an asset to the assets array
		db_json["assets"].push_back({
			{"id", id},  // Replace with your asset's unique id
			{"path", "Assets/Scenes/DefaultScene.pscene"}
			});

		// Output the JSON object
		std::cout << db_json.dump(4) << std::endl;

		std::string dbFileName = m_pms->pDS.projectName + ".peDB";
		fs_path pDBfilePath = assets_dir / dbFileName;
		std::fstream peDB_file(pDBfilePath.string(), std::ios::out | std::ios::trunc);
		if (peDB_file.is_open()) {
			peDB_file << db_json.dump(4); // Example placeholder
			peDB_file.close();
		}
		else {
			std::cerr << "Failed to create .peDB file!" << std::endl;
			return false;
		}
		return true;
	}

	commons::PUUID ProjectManager::_createDefaultSceneFile(fs_path scenes_dir)
	{
		// Define the scene database JSON structure
		commons::PUUID id{};
		json scene_json = {
			{"id", id},
			{"source", "scene"},
			{"parentID", "0"},
			{"type_", "LevelAsset"},
			{"data_", json::object()},
			{"ref_assets", json::array() }
		};

		fs_path psceneFilePath = scenes_dir / "DefaultScene.pscene";
		std::fstream pscene_file(psceneFilePath.string(), std::ios::out | std::ios::trunc);
		if (pscene_file.is_open()) {
			pscene_file << scene_json.dump(4); // Example placeholder
			pscene_file.close();
		}
		else {
			std::cerr << "Failed to create .pscene file!" << std::endl;
			return commons::PUUID(0);
		}

		return id;
	}

	bool ProjectManager::_createEditorProcess()
	{
		char path[MAX_PATH];
		GetModuleFileName(NULL, path, MAX_PATH);

		std::filesystem::path exeDir = std::filesystem::path(std::string(path)).parent_path();

		std::string editorName = "PurityEditor.exe";

		auto editorPath = (exeDir / editorName).string();

		if (!std::filesystem::exists(editorPath)) {
			std::cerr << "Editor not found at: " << editorPath << std::endl;
			return false;
		}

		// Validate project file and scene
		if (!std::filesystem::exists(m_pms->pDS.filePath)) {
			std::cerr << "Project file not found: " << m_pms->pDS.filePath << std::endl;
			return false;
		}
		if (!std::filesystem::exists(m_pms->pDS.projectDir + "/" + m_pms->pDS.startupScene)) {
			std::cerr << "Startup scene not found: " << m_pms->pDS.startupScene << std::endl;
			return false;
		}

		std::string commandLine = editorPath + " -p \"" + m_pms->pDS.filePath + "\" -s \"" + m_pms->pDS.startupScene + "\"";
		//std::string commandLine = "\"" + editorPath + "\"";
		/*for (const auto& arg : args) {
			commandLine += " " + arg;
		}*/
		/*std::string commandLine = "\"" + editorPath + "\""
			+ " -p \"" + m_pms->pDS.filePath + "\""
			+ " -s \"" + m_pms->pDS.startupScene + "\"";
		std::cout << commandLine << std::endl;*/

		STARTUPINFO si = { sizeof(si) };
		PROCESS_INFORMATION pi;

		if (CreateProcess(
			NULL,
			&commandLine[0],
			NULL,
			NULL,
			FALSE,
			0,
			NULL,
			NULL,
			&si,
			&pi
		)) {
			CloseHandle(pi.hProcess);
			CloseHandle(pi.hThread);
		}
		else {
			std::cerr << "CreateProcess failed (" << GetLastError() << ")." << std::endl;
			return false;
		}
		return true;
	}

	bool ProjectManager::createProject(std::string projectDir, std::string fileName)
	{
		if (!extractProjectInformation(projectDir, fileName)) 
		{ 
			m_pms->pDS.Log(); 
			return false; 
		}
		bool skipDirCreation = false;
		auto project_dir_path = fs_path(m_pms->pDS.projectDir);
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
		// create asset folder and inner folders
		auto asset_dir = project_dir_path / "Assets";
		auto prefabs_dir = asset_dir / "Prefabs";
		auto scene_dir = asset_dir / "Scenes";
		auto script_dir = project_dir_path / "Scripts";
		auto config_dir = project_dir_path / "Config";

		std::filesystem::create_directory(asset_dir);
		std::filesystem::create_directory(prefabs_dir);
		std::filesystem::create_directory(scene_dir);
		std::filesystem::create_directory(script_dir);
		std::filesystem::create_directory(config_dir);

		// write pproject file, pedb and pscene files.
		_createProjectFile();
		auto id = _createDefaultSceneFile(scene_dir);
		if (!id) { 
			m_pms->pDS.successfulValidation = false;
			m_pms->pDS.statusMessage = "Scene ID is invalid";
			
			return false; 
		}
		_createDBFile(asset_dir, id);

		// set startup scene in struct to default name 'Assets/Scenes/DefaultScene.pscene'
		m_pms->pDS.startupScene = "Assets/Scenes/DefaultScene.pscene";

		m_pms->pDS.Log();
		return true;
	}

	bool ProjectManager::launchProject(std::string filePath)
	{
		if (!extractProjectInformation(filePath))
		{
			m_pms->pDS.Log();
			return false;
		}
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

		std::string pDBfilePath = "Assets/" + m_pms->pDS.projectName + ".peDB";
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
		if (!commons::_validateFileExistence(m_pms->pDS.filePath) && !commons::_validateSchemaAdherence(m_pms->pDS.filePath, commons::pProjectSchema))
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
		std::string pDBfilePath = m_pms->pDS.projectDir + "/Assets/" + m_pms->pDS.projectName + ".peDB";
		std::cout << pDBfilePath << std::endl;
		if (!commons::_validateFileExistence(pDBfilePath) || !commons::_validateSchemaAdherence(pDBfilePath, commons::pDatabaseSchema))
		{
			m_pms->pDS.successfulValidation = false;
			m_pms->pDS.statusMessage = "Project Database File Validation Failed!, Ensure the database file path exists in '/Assets/' and that the '.peDB' file adheres to its schema specifications.";
			m_pms->pDS.Log();
			return false; 
		}
		return true;
	}
}

// Call this function inside your ImGui render loop
void RaiseErrorMessageBox(project::ProjectManager* projectManager) {
	ImGui::OpenPopup("Error");

	// Center the pop-up in the application window
	ImVec2 center = ImGui::GetMainViewport()->GetCenter();
	ImGui::SetNextWindowPos(center, ImGuiCond_Appearing, ImVec2(0.5f, 0.5f)); // Centered

	// Set a minimum and maximum size for the pop-up
	ImGui::SetNextWindowSize(ImVec2(400, 0), ImGuiCond_Appearing); // 400 width, auto height

	if (ImGui::BeginPopupModal("Error", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
		// Ensure text wraps properly
		ImGui::PushTextWrapPos(380); // Wrap text at ~380 pixels
		ImGui::Text("%s", projectManager->m_pms->pDS.statusMessage.c_str());
		ImGui::PopTextWrapPos();

		ImGui::Separator();

		if (ImGui::Button("OK", ImVec2(120, 0))) {
			projectManager->m_pms->pmp.show_error_popup = false;
			ImGui::CloseCurrentPopup();
		}

		ImGui::SetItemDefaultFocus(); // Auto-focus on the OK button

		ImGui::EndPopup();
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

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1.0f, 0.8f, 0.8f));
		if (ImGui::Button("Clear")) {
			projectManager->m_pms->pDS = { false, "", "", "", "", "" };
			buf[0] = '\0';
		}
		ImGui::PopStyleColor(3);

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

		if (buf[0] != '\0' && !projectManager->m_pms->pDS.projectDir.empty())
		{
			if (ImGui::Button("Create"))
			{
				if (!projectManager->createProject(projectManager->m_pms->pDS.projectDir, buf))
				{
					projectManager->m_pms->pmp.show_error_popup = true;
					ImGui::EndTabItem(); 
					return; 
				}
				std::cout << projectManager->m_pms->pDS << std::endl;
				buf[0] = '\0';
				if (projectManager->_createEditorProcess()) {
					glfwSetWindowShouldClose(projectManager->m_window, true);
				}
				else {
					std::cout << "Could not create process." << std::endl;
				}
			}
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

		ImGui::SameLine();
		ImGui::PushStyleColor(ImGuiCol_Button, (ImVec4)ImColor::HSV(1.0f, 0.6f, 0.6f));
		ImGui::PushStyleColor(ImGuiCol_ButtonHovered, (ImVec4)ImColor::HSV(1.0f, 0.7f, 0.7f));
		ImGui::PushStyleColor(ImGuiCol_ButtonActive, (ImVec4)ImColor::HSV(1.0f, 0.8f, 0.8f));
		if (ImGui::Button("Clear")) {
			projectManager->m_pms->pDS = { false, "", "", "", "", "" };
		}
		ImGui::PopStyleColor(3);

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
			ImGui::TextColored(ImVec4(0.7f, 0.1f, 0.6f, 1.f), "Project File: "); ImGui::SameLine();
			ImGui::Text("%s", projectManager->m_pms->pDS.filePath.c_str());
			if (ImGui::Button("Open"))
			{
				if (!projectManager->launchProject(projectManager->m_pms->pDS.filePath))
				{
					projectManager->m_pms->pmp.show_error_popup = true;
					ImGui::EndTabItem(); 
					return; 
				}
				std::cout << projectManager->m_pms->pDS << std::endl;
				if (projectManager->_createEditorProcess()) {
					glfwSetWindowShouldClose(projectManager->m_window, true);
				}
				else {
					std::cout << "Could not create process." << std::endl;
				}
			}
		}
		ImGui::EndTabItem();
	}
}

void ShowTemplateWindow(project::ProjectManager* projectManager)
{
	if (ImGui::Begin("Templates"))
	{
		ImGui::Text("This window is meant to contain a list of Templates to select from.");
		ImGui::End();
	}
}


int main(int argc, char* argv[]) {
	project::ProjectManager projectManager;

	if (argc == 2) {
		if (std::string(argv[1]) == "--help" || std::string(argv[1]) == "-h")
		{
			std::cout << "PurityGem Command-Line Utilities." << std::endl;
			std::cout << "\tFor help                    \"--help\" or \"-h\"." << std::endl;
			std::cout << "\tCreate New Project          \"--create\" or \"-c\" followed by Project Save Directory and Project Name." << std::endl;
			std::cout << "\tLaunch Existing project     \"--launch\" or \"-l\" followed by '.pproject' file path." << std::endl;
			std::cout << "Note: String Arguments should be passed in order stated here. e.g." << std::endl;
			std::cout << "\t>.\\PurityGem.exe --create \"C:\\Dev\\TestFolder\" \"CMDTestProject\"" << std::endl;
			std::cout << "\t>.\\PurityGem.exe --launch \"C:\\Dev\\TestFolder\\CMDTestProject\\CMDTestProject.pproject\"" << std::endl;
			return 0;
		}
		std::cout << "Invalid Command Line Arguements!" << std::endl;
		return 1;
	}
	if (argc >= 3) {
		if ((std::string(argv[1]) == "--create" || std::string(argv[1]) == "-c") && argc == 4) {
			projectManager.createProject(std::string(argv[2]), std::string(argv[3]));
			std::cout << "Project Created Successfully!" << std::endl; 
			return 0;
		}
		else if ((std::string(argv[1]) == "--launch" || std::string(argv[1]) == "-l") && argc == 3) {
			projectManager.launchProject(std::string(argv[2]));
			std::cout << "Project Launched Successfully!" << std::endl;
			return 0;
		}
		std::cout << "Invalid Command Line Arguements!" << std::endl;
		return 1;
	}

	projectManager.m_pms->pmp = { "Purity Gem", ImVec4(0.45f, 0.55f, 0.60f, 1.00f), 600, 480 };
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

	projectManager.m_window = glfwCreateWindow(projectManager.m_pms->pmp.win_w, projectManager.m_pms->pmp.win_h, projectManager.m_pms->pmp.win_name, nullptr, nullptr);
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
			ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport());
			//ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), ImGuiDockNodeFlags_None);

			ImGui::Begin("Project Manager");
			//ImGui::Begin("Project Manager", nullptr, ImGuiWindowFlags_NoMove);
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
				if (projectManager.m_pms->pmp.show_error_popup){
					RaiseErrorMessageBox(&projectManager);
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
		glClearColor(projectManager.m_pms->pmp.clear_color.x, projectManager.m_pms->pmp.clear_color.y, projectManager.m_pms->pmp.clear_color.z, projectManager.m_pms->pmp.clear_color.w);
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