#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <iomanip>
#include "NiftyCalc.h"
#include "NiftyNum.h"
#include "NiftyUtil.h"

class ImGuiHandler
{
public:
	void Init(GLFWwindow* window, const char* glsl_version);
	void BeginFrame();
	void UpdateSvg(double scale_length, int fret_count, double fret_width, double fret_height, double scallop_depth, bool show_scallop);
	virtual void Update();
	void Render();
	void Shutdown();
	Nifty::ScallopOffsetTable router_offsets;
	Nifty::SvgHandler handler;
};