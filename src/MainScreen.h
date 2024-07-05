#pragma once
// Only Stuff to do with the Main Window in here
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include "../MeshObjects/Mesh.h"
#include "pch.h"

const int SCR_WIDTH = 1920;
const int SCR_HEIGHT = 1080;

class MainScreen
{

public:

	static MainScreen* Instance();

	bool Initialize();
	// ImGui Start
	void SetImGui();
	void NewImguiFrame();
	void RenderImGui();
	void ImGuiWindow();
	void ImGuiMainMenu(GLFWwindow* window);
	void ConsolPanel();
	// ImGui End
	void Run();

	void ClearScreen();
	void SplatBuffers();
	void PollEvents();
	void ShutDown();

	// framebuffer_size_callback needs Adding

	void BgColour();

	void Input();

private:
	GLFWwindow* window;
	float my_color[3] = { 0.0f, 0.0f, 0.0f };

	const int CONSOLE_PANEL_HEIGHT = 200;


};

