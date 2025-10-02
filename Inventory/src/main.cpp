#include<iostream>

#include "Inventory.h"

#include<glew.h>
#include<glfw3.h>

//ImGui
#include "Vendors/Imgui/imgui.h"
#include "Vendors/Imgui/imgui_impl_glfw.h"
#include "Vendors/Imgui/imgui_impl_opengl3.h"


void static option(Inventory &inventory) 
{
	//std::cout << "1. Add Items" << std::endl << "2. View Inventory" << std::endl << "3. Update Item " << std::endl << "4. delete Item " << std::endl;
	if (ImGui::Button("Add Items")) {
		inventory.showAddItemWindow = true;
	}
	if (ImGui::Button("View Inventory")) {
		inventory.showViewInventoryWindow = true;
	}
	if (ImGui::Button("Update Item")) {
		inventory.showUpdateItemWindow = true;
	}
	if (ImGui::Button("Delete Item")) {
		inventory.showdeleteItemWindow = true;
	}
}

int main() 
{
	Inventory inventory;
	int windowWidth = 960;
	int windowHeight = 540;

	if (!glfwInit())
		return -1;

	// Request OpenGL 3.3 core (change if you need another profile/version)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS if needed

	GLFWwindow* window = glfwCreateWindow(960, 540, "Inventory", nullptr, nullptr);
	//glfwSetWindowAttrib(window, GLFW_DECORATED, GLFW_FALSE);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	// Init GLEW (must be after context creation)
	glewExperimental = GL_TRUE; // important for core profiles
	GLenum glewStatus = glewInit();
	if (glewStatus != GLEW_OK)
	{
		std::cerr << "GLEW init failed: " << glewGetErrorString(glewStatus) << std::endl;
		return -1;
	}

	std::cout << "GL version: " << glGetString(GL_VERSION) << std::endl;

	// Setup Dear ImGui context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330 core");

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.0f;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		inventory.showViewInventoryWindow = true;		

		inventory.addItem();
		inventory.viewInventory(windowWidth, windowHeight);
		inventory.updateItem();

		// Rendering
		ImGui::Render();

		int display_w, display_h;
		glfwGetFramebufferSize(window, &display_w, &display_h);
		glViewport(0, 0, display_w, display_h);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		glfwSwapBuffers(window);
	}

	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}