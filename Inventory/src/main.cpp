#include<iostream>

#include "Inventory.h"

#include<glew.h>
#include<glfw3.h>

//ImGui
#include "Vendors/Imgui/imgui.h"
#include "Vendors/Imgui/imgui_impl_glfw.h"
#include "Vendors/Imgui/imgui_impl_opengl3.h"


void option(Inventory inventory) 
{
	std::string nameToEdit = "Book";
	//std::cout << "1. Add Items" << std::endl << "2. View Inventory" << std::endl << "3. Update Item " << std::endl << "4. delete Item " << std::endl;
	if (ImGui::Button("Add Items")) {
		inventory.addItem("Book", 22, 12);
	}
	if (ImGui::Button("View Inventory")) {
		inventory.viewInventory();
	}
	if (ImGui::Button("Update Item")) {
		inventory.updateItem(nameToEdit);
	}
	if (ImGui::Button("Delete Item")) {
		inventory.deleteItem(nameToEdit);
	}
}

int main() 
{
	Inventory inventory;
	bool show_demo_window = true;

	if (!glfwInit())
		return -1;

	// Request OpenGL 3.3 core (change if you need another profile/version)
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	// glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // for macOS if needed

	GLFWwindow* window = glfwCreateWindow(960, 540, "Trial", nullptr, nullptr);
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

	// Setup Platform/Renderer backends
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui::StyleColorsDark();
	ImGui_ImplOpenGL3_Init("#version 330 core");

	ImGuiStyle& style = ImGui::GetStyle();
	style.WindowRounding = 5.0f;

	while (!glfwWindowShouldClose(window))
	{
		// Poll events first
		glfwPollEvents();

		// Start ImGui frame
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();

		//ImGui::ShowDemoWindow(&show_demo_window);
		ImGui::Begin("Inventory");
		option(inventory);
		ImGui::End();

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
// 
// 
// 	 Inventory inventory;
// 
// 	 while (true)
// 	 {
// 	     std::cout << "Using C++ version: " << __cplusplus << std::endl;
// 	     option();
// 	     int choice;
// 	     std::string name;
// 	     int quantity;
// 	     float price;
// 	     // std::cin >> choice;
// 
// 	     if (!(std::cin >> choice)) {
// 	         std::cout << "\nConsole closed or input ended. Exiting...\n";
// 	         break;  // exit loop
// 	     }
// 
// 	     std::string nameToUpdate;
// 	     std::string deletingName;
// 
// 	     switch (choice)
// 	     {
// 	     case 1:
// 	         std::cout << "Enter product name, quantity and price:" << std::endl;
// 	         std::cout << "Product name: ";
// 	         std::cin >> name;
// 	         std::cout << "Product Quantity: ";
// 	         std::cin >> quantity;
// 	         std::cout << "Product price: ";
// 	         std::cin >> price;
// 	         inventory.addItem( name, quantity, price );
// 	         break;
// 
// 	     case 2:
// 	         inventory.viewInventory();
// 	         break;
// 
// 	     case 3:
// 	         std::cout << "Which product do you want to update?" << std::endl;
// 	         std::cin >> nameToUpdate; 
// 	         inventory.updateItem(nameToUpdate);
// 	         break;
// 
// 	     case 4:
// 	         inventory.viewInventory();
// 	         std::cout << "Which product do you wish to delete?" << std::endl;
// 	         std::cin >> deletingName;
// 	         inventory.deleteItem(deletingName);
// 	         break;
// 
// 	     default:
// 	         std::cout << "Invalid Value" << std::endl;
// 	         break;
// 	     }
// 	 }
// 
// 
// 	 std::cin.get();
}