#include "MainScreen.h"
#include "../SpdLog/LogInternals.h"
//#include "GameInput.h"




MainScreen* MainScreen::Instance()
{
    static MainScreen* screen = new MainScreen;

    return screen;
}

void MainScreen::Initialize(GLFWwindow* window)
{   
   


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to loade glad" << std::endl;
    }
    else {
        LogInternals::Instance()->Info("Glad Loaded Correctly");
    }

    // Load an icon
    GLFWimage images[1];
    images[0].pixels = stbi_load("Textures/Icon.png", &images[0].width, &images[0].height, 0, 4); // rgba = png
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);

}

void MainScreen::SetImGui(GLFWwindow* window)
{
    
    // ImGui set up
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO io = ImGui::GetIO();
    io.KeyMap[ImGuiKey_H] = GLFW_KEY_HOME;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 460");
    // Set up my own Fonts
    ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/comic.ttf", 16.0f);
    ImGui::GetIO().Fonts->Build();
    
}

void MainScreen::NewImguiFrame(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void MainScreen::RenderImGui(GLFWwindow* window)
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainScreen::ImGuiWindow(GLFWwindow* window)
{
    float f = 0.0f;
    ImGui::Begin("Spidex");
    ImGui::Text("Spidex Engine", nullptr);
    ImGui::Button("Save");

    ImGui::Text("string");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    // Edit a color stored as 4 floats
    ImGui::ColorEdit4("Color", my_color);
    ImGui::Spacing();
    ImGui::DragFloat3("Scale", scale_value, 0.3f, 0.3f, 0.3f);
    //ImGuiIO io = ImGui::GetIO();
    //ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
    ImGui::End();
}
void MainScreen::ImGuiMainMenu(GLFWwindow* window)
{
    // This is my main window menu
    ImGui::BeginMainMenuBar();
    if (ImGui::BeginMenu("File"))
    {
        if (ImGui::MenuItem("Creat Scean"))
        {

        }
        if (ImGui::MenuItem("Open Scean"))
        {

        }
        ImGui::Separator();
        if (ImGui::MenuItem("Save Scean"))
        {

        }
        if (ImGui::MenuItem("Creat Scean"))
        {

        }
        ImGui::Separator();
        if (ImGui::MenuItem("Exit"))
        {
            glfwSetWindowShouldClose(window, true);
        }
        ImGui::EndMenu();

    }
    if (ImGui::BeginMenu("Edit"))
    {
        if (ImGui::MenuItem("Cut"))
        {

        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("View"))
    {
        if (ImGui::MenuItem("Hi"))
        {

        }
        ImGui::EndMenu();
    }
    if (ImGui::BeginMenu("Help"))
    {
        if (ImGui::MenuItem("Hi"))
        {

        }
        ImGui::EndMenu();
    }

    ImGui::EndMainMenuBar();
}

void MainScreen::ConsolPanel(GLFWwindow* window)
{
    ImGui::Begin("Output Console", nullptr,
        ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);
    auto WindowPos = ImVec2(0, SCR_HEIGHT - CONSOLE_PANEL_HEIGHT - 5); // set the height of the consol window
   
    auto WindowSize = ImVec2(SCR_WIDTH, CONSOLE_PANEL_HEIGHT);

    ImGui::SetWindowPos("Output Console", WindowPos);
    ImGui::SetWindowSize("Output Console", WindowSize);
    ImGuiIO io = ImGui::GetIO();

    // ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate);
    ImGui::Text("Mouse pos X %.3f Mouse pos Y %.3f", io.MousePos.x, io.MousePos.y);

    ImGui::End();
    // needs to be resized on window resize



}

void MainScreen::SetViewPort(GLint x, GLint y, GLsizei width, GLsizei height)
{
    glViewport(x, y, width, height);
}

void MainScreen::ClearScreen()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void MainScreen::SplatBuffers()
{
    glfwSwapBuffers(window);
}

void MainScreen::PollEvents()
{
    glfwPollEvents();
    
}

void MainScreen::ShutDown()
{  
    
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwTerminate();

    LogInternals::Instance()->Info("Engine shutdown successfully");
}

void MainScreen::BgColour()
{
    glClearColor(my_color[0], my_color[1], my_color[2], 1.0f);

}

// get the keyboard and mouse input
void MainScreen::Input()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        //std::cout << "KEY ESCAPE PRESSED" << std::endl;
        glfwSetWindowShouldClose(window, GLFW_TRUE);

}
