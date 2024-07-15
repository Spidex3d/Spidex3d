#pragma once
// Only Stuff to do with the Main Window in here
#include <imgui\imgui.h>
#include <imgui\imgui_impl_glfw.h>
#include <imgui\imgui_impl_opengl3.h>

#include <glad\glad.h>
#include <GLFW\glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <stb\stb_image.h>
//#include "../MeshObjects/Mesh.h"

#include "pch.h"
#include "Common.h"

//const int SCR_WIDTH = 1920;
//const int SCR_HEIGHT = 1080;

class MainScreen
{

public:

	static MainScreen* Instance();

	void Initialize(GLFWwindow* window);
	// ImGui Start
	void SetImGui(GLFWwindow* window);
	void NewImguiFrame(GLFWwindow* window);
	void RenderImGui(GLFWwindow* window);
	
	void MainDockSpace(bool* p_open);
	
	void MainScean(GLFWwindow* window);

	void ImGuiWindow(GLFWwindow* window);
	void ImGuiMainMenu(GLFWwindow* window);
	
	void ConsolPanel(GLFWwindow* window);
	// ImGui End

	

	void SetViewPort(GLint x, GLint y, GLsizei width, GLsizei height);
	//void ScreenResize();

	void ClearScreen();
	void SplatBuffers();
	void PollEvents();
	void ShutDown();

	// framebuffer_size_callback needs Adding

	void BgColour();

	void Input();
	float scale_value[3] = { 0.3f, 0.3f, 0.3f };



private:
	GLFWwindow* window;

	float my_color[3] = { 0.0f, 0.0f, 0.0f };

	bool show_demo_window = true;
	bool show_another_window = false;
	
	glm::vec2 mSize;

	const int CONSOLE_PANEL_HEIGHT = 200;


};

