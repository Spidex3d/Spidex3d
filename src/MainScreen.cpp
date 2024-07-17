#include "MainScreen.h"
#include "../SpdLog/LogInternals.h"
//#include "GameInput.h"
//#include "../MeshObjects/Mesh.h"



static bool show_app_dockspace = false;

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
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    //io.KeyMap[ImGuiKey_H] = GLFW_KEY_HOME;
    ImGui::StyleColorsDark();
    
    ImGui_ImplOpenGL3_Init("#version 460");
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    // Set up my own Fonts
    ImGui::GetIO().Fonts->AddFontFromFileTTF("Fonts/comic.ttf", 16.0f);
    ImGui::GetIO().Fonts->Build();
    
}

void MainScreen::NewImguiFrame(GLFWwindow* window)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    //ImGui::NewFrame();

}

void MainScreen::RenderImGui(GLFWwindow* window)
{
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
    {
        GLFWwindow* backup_context = glfwGetCurrentContext(); // Get the current window conttext
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_context);
    }

}

void MainScreen::MainDockSpace(bool* p_open)
{
        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        //static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_PassthruCentralNode;// I changed this so my scean shows up on start up

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", p_open, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Spidex Options"))
            {
                // Disabling fullscreen would allow the window to be moved to the front of other windows,
                // which we can't undo at the moment without finer window depth/z control.
                ImGui::MenuItem("Fullscreen", NULL, &opt_fullscreen);
                ImGui::MenuItem("Padding", NULL, &opt_padding);
                ImGui::Separator();

                if (ImGui::MenuItem("Flag: NoDockingOverCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingOverCentralNode) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingOverCentralNode; }
                if (ImGui::MenuItem("Flag: NoDockingSplit", "", (dockspace_flags & ImGuiDockNodeFlags_NoDockingSplit) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoDockingSplit; }
                if (ImGui::MenuItem("Flag: NoUndocking", "", (dockspace_flags & ImGuiDockNodeFlags_NoUndocking) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoUndocking; }
                if (ImGui::MenuItem("Flag: NoResize", "", (dockspace_flags & ImGuiDockNodeFlags_NoResize) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_NoResize; }
                if (ImGui::MenuItem("Flag: AutoHideTabBar", "", (dockspace_flags & ImGuiDockNodeFlags_AutoHideTabBar) != 0)) { dockspace_flags ^= ImGuiDockNodeFlags_AutoHideTabBar; }
                if (ImGui::MenuItem("Flag: PassthruCentralNode", "", (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode) != 0, opt_fullscreen)) { dockspace_flags ^= ImGuiDockNodeFlags_PassthruCentralNode; }
                  
                 ImGui::Separator();

                if (ImGui::MenuItem("Close", NULL, false, p_open != NULL))
                    *p_open = false;
                ImGui::EndMenu();
            }


            ImGui::EndMenuBar();
        }

        ImGui::End();

}

// Main ImGui Scean Window To Draw to
void MainScreen::MainScean(GLFWwindow* window)
{
    /*
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
    ImGui::Begin("Main Scean");
    const float window_width = ImGui::GetContentRegionAvail().x;
    const float window_height = ImGui::GetContentRegionAvail().y;

    Rescale_frambuffer(window_width, window_height);
    glViewport(0, 0, window_width, window_height);

    ImVec2 pos = ImGui::GetCursorScreenPos();

    ImGui::GetWindowDrawList()->AddImage((void*)texture_id, ImVec2(pos.x, pos.y),
        ImVec2(pos.x + window_width, pos.y + window_height), ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();
    ImGui::PopStyleVar();
    */
}

void MainScreen::ImGuiWindow(GLFWwindow* window)
{

    if (show_demo_window)
        ImGui::ShowDemoWindow(&show_demo_window);

    float f = 0.0f;
    
        ImGui::Begin("Spidex Property Panel");
        ImGui::Text("Spidex Engine", nullptr);
        ImGui::Button("Save");
        ImGui::Checkbox("Demo Window", &show_demo_window);

        ImGui::Text("string");
        ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
        // Edit a color stored as 4 floats
        ImGui::ColorEdit4("Color", my_color);
        ImGui::Spacing();
        ImGui::DragFloat3("Scale", scale_value, 0.3f, 0.3f, 0.3f);
        ImGuiIO io = ImGui::GetIO();
        ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

        

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
    if (ImGui::BeginMenu("Docking"))
    {
        if (ImGui::MenuItem("Dockspace off"))
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
    ImGui::Begin("Output Console");
        //ImGuiWindowFlags_::ImGuiWindowFlags_NoResize |
        //ImGuiWindowFlags_::ImGuiWindowFlags_NoMove |
        //ImGuiWindowFlags_::ImGuiWindowFlags_NoCollapse);
    //auto WindowPos = ImVec2(0, SCR_HEIGHT - CONSOLE_PANEL_HEIGHT - 5); // set the height of the consol window
   
   
    //auto WindowSize = ImVec2(SCR_WIDTH, CONSOLE_PANEL_HEIGHT);
   // auto WindowSize = ImVec2(SCR_WIDTH, CONSOLE_PANEL_HEIGHT);

    //ImGui::SetWindowPos("Output Console", WindowPos);
    //ImGui::SetWindowSize("Output Console", WindowSize);
    ImGuiIO io = ImGui::GetIO();
    ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

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





