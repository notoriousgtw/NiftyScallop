#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iomanip>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

class NiftyApp
{
public:
	NiftyApp() = delete;
	NiftyApp(std::string name);

    void Loop();
	
	~NiftyApp();
private:
	std::string name;
	ImGuiIO io;
	GLFWwindow* window;

	void BeginFrame();
	virtual void Update() = 0;  
	void EndFrame();
	void Render();
};
