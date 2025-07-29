#include "ImGUIHandler.h"
#include "glad/glad.h"
#include "GLFW/glfw3.h"

using namespace std;

int main() {
	// Initialize GLFW
	if (!glfwInit())
	{
		return -1;
	}

	// Set GL Version
	const char* glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Create Window and Graphics Context
	GLFWwindow* window = glfwCreateWindow(1280, 720, "Nifty Scallop", NULL, NULL);
	if (window == NULL)
		return 1;
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Try to initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw("Failed to initialize GLAD");

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	ImGuiHandler imgui_handler;
	imgui_handler.Init(window, glsl_version);
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		imgui_handler.BeginFrame();
		imgui_handler.Update();
		imgui_handler.Render();
		glfwSwapBuffers(window);
	}
	imgui_handler.Shutdown();

	return 0;
}