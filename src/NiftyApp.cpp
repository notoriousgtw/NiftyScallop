#include "NiftyApp.h"

NiftyApp::NiftyApp(std::string name)
{
	this->name = name;

	// Initialize GLFW
	if (!glfwInit())
		throw("Failed to initialize GLFW!");

	// Set GL Version
	const char* glsl_version = "#version 330";
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	// Create Window and Graphics Context
	window = glfwCreateWindow(1280, 720, name.c_str(), NULL, NULL);
	if (window == NULL)
		throw("Failed to create window!");
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	// Try to initialize GLAD
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
		throw("Failed to initialize GLAD!");

	int screen_width, screen_height;
	glfwGetFramebufferSize(window, &screen_width, &screen_height);
	glViewport(0, 0, screen_width, screen_height);

	//Initialize ImGui Context
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	io = ImGui::GetIO();

	// Setup Bindings
	ImGui_ImplGlfw_InitForOpenGL(window, true);
	ImGui_ImplOpenGL3_Init(glsl_version);

	// Setup Style
	ImGui::StyleColorsDark();
}

void NiftyApp::Loop()
{
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		BeginFrame();
		Update();
		EndFrame();
		Render();
		glfwSwapBuffers(window);
	}
}

NiftyApp::~NiftyApp()
{
	// Cleanup
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void NiftyApp::BeginFrame()
{
	// Start ImGui Frame
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();
	// Set the next window position and size to cover the entire display
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImGui::GetIO().DisplaySize);
	ImGui::Begin(this->name.c_str(), nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoTitleBar);
}

void NiftyApp::EndFrame()
{
	ImGui::End();
}

void NiftyApp::Render()
{
	// Render ImGui
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
