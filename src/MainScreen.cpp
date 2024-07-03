#include "MainScreen.h"
#include "../SpdLog/LogInternals.h"



MainScreen* MainScreen::Instance()
{
    static MainScreen* screen = new MainScreen;

    return screen;
}

bool MainScreen::Initialize()
{
    LogInternals::Instance()->Initialize();
    // Initialize GLFW
    if (!glfwInit())
        return -1;


    // set up the window here
     window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Spidex 3d Engine", NULL, NULL);

    // Did we create a window
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    else {
        LogInternals::Instance()->Info("Window created successfully");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to loade glad" << std::endl;
    }
    else {
        LogInternals::Instance()->Info("Glad Loaded Correctly");
    }
    
    // add the Spidex Icon
    GLFWimage images[1];
    images[0].pixels = stbi_load("Textures/icon2.png", &images[0].width, &images[0].height, 0, 4); //rgba channels 
    glfwSetWindowIcon(window, 1, images);
    stbi_image_free(images[0].pixels);
    
    return true;
}

void MainScreen::SetImGui()
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

void MainScreen::NewImguiFrame()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

}

void MainScreen::RenderImGui()
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void MainScreen::ImGuiWindow()
{
    float f = 0.0f;
    ImGui::Begin("Spidex");
    ImGui::Text("Spidex Engine", nullptr);
    ImGui::Button("Save");

    ImGui::Text("string");
    ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    // Edit a color stored as 4 floats
    ImGui::ColorEdit4("Color", my_color);
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

void MainScreen::ConsolPanel()
{
    ImGui::Begin("Output Console", nullptr,
        ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);
    auto WindowPos = ImVec2(0, SCR_HEIGHT - CONSOLE_PANEL_HEIGHT - 25); // set the height of the concol window
    auto WindowSize = ImVec2(SCR_WIDTH, CONSOLE_PANEL_HEIGHT);

    ImGui::SetWindowPos("Output Console", WindowPos);
    ImGui::SetWindowSize("Output Console", WindowSize);
    ImGuiIO io = ImGui::GetIO();

    // ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate);
    ImGui::Text("Mouse pos X %.3f Mouse pos Y %.3f", io.MousePos.x, io.MousePos.y);

    ImGui::End();
    // needs to be resized on window resize



}

void MainScreen::Run()
{
    // do the while loop here
     while (!glfwWindowShouldClose(window))
    {

        MainScreen::Instance()->PollEvents();
       
        MainScreen::Instance()->Input();
       
        MainScreen::Instance()->NewImguiFrame(); // 1

        MainScreen::Instance()->ImGuiMainMenu(window);//2
        MainScreen::Instance()->ConsolPanel(); // 3
        MainScreen::Instance()->ImGuiWindow();  // 4

        MainScreen::Instance()->BgColour();

        MainScreen::Instance()->ClearScreen();
        
        Mesh::Instance()->Initialize(); // Draw a Triangel

        MainScreen::Instance()->RenderImGui(); // 5 Put them in this order


        MainScreen::Instance()->SplatBuffers();

    }


    
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
