//
// Created by Eniola Olawale on 10/10/2024.
//
#pragma once
#include "glad/glad.h"

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "GLFW/glfw3.h"

#include <iostream>


namespace project{
	class ProjectManager {
	public:
		ProjectDataStructure validateProject(const char* projectFilePath);
		bool createProject(ProjectDataStructure pDS);
		void launchProject(ProjectDataStructure pDS);
		/*void loadTemplates();
		void loadRecentProjects();
		void loadFileDialog();*/

		GLFWwindow* window;
	private:
	}; 

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

	struct ProjectManagerState {
		ProjectSelectionChoice selectionChoice = ProjectSelectionChoice::SelectFromTemplate;
	};
	
	struct ProjectDataStructure
	{
		bool successfulValidation;
		const char* filePath;
		const char* projectDir;
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
	/*
	projectManager.loadTemplates();
	projectManager.loadRecentProjects();
	*/

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
			if (ImGui::BeginMainMenuBar()) {
				if (ImGui::BeginMenu("Selection Choice")) {
					if (ImGui::MenuItem("New Project", "Ctrl+N", false, true)) 
					{ 
						pms.selectionChoice = project::ProjectSelectionChoice::SelectFromTemplate;  
					}
					if (ImGui::MenuItem("Open Recent", "Ctrl+O", false, true))
					{
						pms.selectionChoice = project::ProjectSelectionChoice::OpenExisting;
					}
					ImGui::EndMenu();
				}
				ImGui::EndMainMenuBar();
			}

			// All widgets go in here
			switch (pms.selectionChoice)
			{
			case project::ProjectSelectionChoice::OpenExisting:
				ImGui::Text("Open existing projects from drive.");
				ImGui::Text("Select from Recent projects.");
				if (ImGui::Button("Launch")) {
					projectManager.launchProject(projectManager.validateProject(""));
				}
				break;
			case project::ProjectSelectionChoice::SelectFromTemplate:
				ImGui::Text("Create a new project from template.");
				if (ImGui::Button("Start")) {
					projectManager.createProject(projectManager.validateProject(""));
				}
				break;
			default:
				break;
			}

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