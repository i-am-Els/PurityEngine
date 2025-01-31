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


namespace project{

	struct ProjectManagerProperties {
		const char* win_name;
		ImVec4 clear_color;
		int win_w, win_h;
	};

	enum class ProjectSelectionChoice
	{
		SelectFromTemplate,
		OpenExisting
	};

	struct ProjectDataStructure
	{
		bool successfulValidation;
		std::string filePath;
		std::string projectName;
		std::string projectDir;
	};

	struct ProjectManagerState {
		ProjectSelectionChoice selectionChoice = ProjectSelectionChoice::SelectFromTemplate;
		ProjectDataStructure pDS;
	};

	class ProjectManager {
	public:
		ProjectDataStructure validateProject(std::string projectFilePath, std::string fileName="");
		bool createProject(ProjectDataStructure pDS);
		void launchProject(ProjectDataStructure pDS);

		GLFWwindow* window;
	private:
		//void loadTemplates();
		//void loadRecentProjects();
		void selectProjectFolderDialog();
		void openProjectFromFileDialog();
	}; 
}

static void glfw_error_callback(int error, const char* description)
{
	fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int main() {
	project::ProjectManager projectManager;
	project::ProjectManagerProperties pmp{ "Purity Gem", ImVec4(0.45f, 0.55f, 0.60f, 1.00f), 600, 480};
	project::ProjectManagerState pms;

	glfwSetErrorCallback(glfw_error_callback);
	if (glfwInit() != GLFW_TRUE) {
		return 1;
	}

	const char* glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);          
	
	projectManager.window = glfwCreateWindow(pmp.win_w, pmp.win_h, pmp.win_name, nullptr, nullptr);
	if (projectManager.window == nullptr){
		return 1;
	}

	glfwMakeContextCurrent(projectManager.window);
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

	// Setup Dear ImGui style
	ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight(); // Light Mode

	ImGui_ImplGlfw_InitForOpenGL(projectManager.window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	while (!glfwWindowShouldClose(projectManager.window)) {
		glfwPollEvents();
		if (glfwGetWindowAttrib(projectManager.window, GLFW_ICONIFIED) != 0)
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
			ImGui::Begin("Hello, Purity Gem!");
			ImGuiTabBarFlags tab_bar_flags = ImGuiTabBarFlags_None;
			if (ImGui::BeginTabBar("MyTabBar", tab_bar_flags))
			{
				// Select New Project
				if (ImGui::BeginTabItem("New Project"))
				{
					pms.selectionChoice = project::ProjectSelectionChoice::SelectFromTemplate;
					ImGui::Text("Create a new empty project or start with a template.");
					if (ImGui::Button("Select Save Directory")) {
						IGFD::FileDialogConfig config; config.path = ".";
						config.countSelectionMax = 1;
						config.flags = ImGuiFileDialogFlags_Modal;
						// Select Directory, "uses nullptr as filter"
						ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose Project Directory", nullptr, config);
					}

					// Render the file dialog
					if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
						if (ImGuiFileDialog::Instance()->IsOk()) {
							// User selected a file
							std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();

							// Validate the file or use it to create the project
							pms.pDS = projectManager.validateProject(filePath);
							projectManager.createProject(pms.pDS);
						}

						// Close the dialog after processing the result
						ImGuiFileDialog::Instance()->Close();
					}
					ImGui::EndTabItem();
				}

				// Open Recent Tab
				if (ImGui::BeginTabItem("Open Recent"))
				{
					pms.selectionChoice = project::ProjectSelectionChoice::OpenExisting; 
					ImGui::Text("Select existing projects from drive.");
					ImGui::SameLine();
					if (ImGui::Button("Choose")) {
						IGFD::FileDialogConfig config; config.path = ".";
						config.countSelectionMax = 1;
						config.flags = ImGuiFileDialogFlags_Modal;
						ImGuiFileDialog::Instance()->OpenDialog("ChooseFileDlgKey", "Choose Purity Project File(*.pproject)", ".pproject", config);
					}
					
					if (!pms.pDS.filePath.empty())
						ImGui::Text("%s", pms.pDS.filePath.c_str());

					// Render the file dialog
					if (ImGuiFileDialog::Instance()->Display("ChooseFileDlgKey")) {
						if (ImGuiFileDialog::Instance()->IsOk()) {
							// User selected a file
							std::string filePath = ImGuiFileDialog::Instance()->GetFilePathName();
							std::string fileName = ImGuiFileDialog::Instance()->GetCurrentFileName();

							// Validate the file or use it to create the project
							pms.pDS = projectManager.validateProject(filePath);
							projectManager.launchProject(pms.pDS);
							std::cout << pms.pDS.filePath << std::endl;
						}

						// Close the dialog after processing the result
						ImGuiFileDialog::Instance()->Close();
					}
					ImGui::EndTabItem();
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
		glfwGetFramebufferSize(projectManager.window, &display_w, &display_h);
		// Use that size to set the viewport
		glViewport(0, 0, display_w, display_h);
		glClearColor(pmp.clear_color.x, pmp.clear_color.y, pmp.clear_color.z, pmp.clear_color.w);
		glClear(GL_COLOR_BUFFER_BIT);
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(projectManager.window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(projectManager.window);
	glfwTerminate();

	return 0;
}