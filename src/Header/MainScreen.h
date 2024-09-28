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

#include <iostream>
#include <filesystem> 
#include "FileManager.h"

#include "Configs.h"



class MainScreen
{

public:

	static MainScreen* Instance();
	

	// ###############
	void Initialize(GLFWwindow* window);
	// ImGui Start
	void SetImGui(GLFWwindow* window);
	void NewImguiFrame(GLFWwindow* window);
	void RenderImGui(GLFWwindow* window);
	void MainDockSpace(bool* p_open); // docking space
	void MainScean(GLFWwindow* window); // Drawing to an ImGui Scean Window
	// void ImGuiElimentWindow(GLFWwindow* window);
	//void ImGuiPropertiesPanel(GLFWwindow* window);
	void ImGuiMainMenu(GLFWwindow* window);
	void ConsolPanel(GLFWwindow* window); // Content Browser / Explorer
	void AboutWindow(GLFWwindow* window); //About Window from the main menu
	// ImGui End

	void Creat_FrameBuffer();

	unsigned int LoadTextureFiles(const char* filename, GLuint* out_texture, int out_width, int out_height);

	void Bind_Framebuffer();
	void Unbinde_Frambuffer();
	void Rescale_frambuffer(float width, float height);

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
	// scale
	float m = 0.0f;


private:
	GLFWwindow* window;
	GLuint FBO;
	GLuint RBO;
	GLuint scean_texture_id;

	// For the textures
	int tex_image_width = 0;
	int tex_image_height = 0;
	int nrComponents = 0;
	GLuint texture_image_id;

	

	//std::filesystem::path  m_BaseDirectory;
	//std::filesystem::path  m_CurrentDirectory;


	float my_color[3] = { 0.0f, 0.0f, 0.0f };

	bool show_demo_window = false;
	bool show_another_window = false;
	bool show_about_window = false;
	

	const int CONSOLE_PANEL_HEIGHT = 200;


};

