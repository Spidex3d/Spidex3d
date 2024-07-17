#include "pch.h"
#include "MainScreen.h"
#include "../SpdLog/LogInternals.h"

#include "../Shader/Shader.h"

#include "../MeshObjects/Mesh.h"
#include "Textures.h"

#include "GameInput.h"

// ImGui docking test Sat 13/07/24

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);
GLuint FBO;
GLuint RBO;
GLuint texture_id;


Shader defaultShader;

unsigned int defaultMap;

void Creat_FrameBuffer()
{

    glGenFramebuffers(1, &FBO);
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);

    glGenTextures(1, &texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGBA, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);

    glGenRenderbuffers(1, &RBO);
    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, SCR_WIDTH, SCR_HEIGHT);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);

    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
        std::cout << "ERROR FRAMBUFFER:: framebuffer is not compleate!" << std::endl;

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glBindTexture(GL_TEXTURE_2D, 0);
    glBindRenderbuffer(GL_RENDERBUFFER, 0);

}
void Bind_Framebuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, FBO);
}
void Unbinde_Frambuffer()
{
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

}
void Rescale_frambuffer(float width, float height)
{
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texture_id, 0);


    glBindRenderbuffer(GL_RENDERBUFFER, RBO);
    glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
    glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, RBO);
}


int main(void)
{
    LogInternals::Instance()->Initialize();
    
    if (!glfwInit())
        return -1;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // set up the window here
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Spidex 3d Engine", NULL, NULL);

    // Did we create a window
    if (!window)
    {
        glfwTerminate();
        return -1;
    }
    else {
        LogInternals::Instance()->Info("Window created successfully");
    }

    int bufferWidth, bufferHeight;
    glfwGetFramebufferSize(window, &bufferWidth, &bufferHeight);
    
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1); // Enable vsync

    //glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    
    MainScreen::Instance()->Initialize(window); // MakeContextCurrent - glad and window icon
    
    glViewport(0, 0, bufferWidth, bufferHeight);


    MainScreen::Instance()->SetImGui(window); // ImGui setup
    
    //########################
    //Shader defaultShader;
     defaultShader.Load("Shader/shaderFile/default.vert", "Shader/shaderFile/default.frag");

    
     Mesh_Setup(); // Load the VBO Data


    // flip image
    stbi_set_flip_vertically_on_load(true);

    //int width, height, nrChannels;

    std::string texPath = "Textures/";
    std::string texImg = "github.jpg";

    defaultMap = loadTexture((texPath + texImg).c_str());
    //########################
   

    glEnable(GL_DEPTH_TEST);
    Creat_FrameBuffer();

    //SetViewPort(0, CONSOLE_PANEL_HEIGHT, SCR_WIDTH, SCR_HEIGHT - CONSOLE_PANEL_HEIGHT);


    // get the current opengl version number.
    std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

    // do the while loop here
    while (!glfwWindowShouldClose(window))
    {
        
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float time = glfwGetTime();
        
        processInput(window);

        MainScreen::Instance()->PollEvents();

       

        MainScreen::Instance()->NewImguiFrame(window); // 1

       // MainScreen::Instance()->ClearScreen();

        ImGui::NewFrame();

        bool doc = true;
        MainScreen::Instance()->MainDockSpace(&doc); // Docking


        //MainScreen::Instance()->MainScean(window); // This is the ImGui Window which we are trying to draw are cube in
        // ########################## IMGUI ##################
        
        ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));
        ImGui::Begin("Main Scean");
        const float window_width = ImGui::GetContentRegionAvail().x;
        const float window_height = ImGui::GetContentRegionAvail().y;

        Rescale_frambuffer(window_width, window_height);
        glViewport(0, 0, window_width, window_height);

        ImVec2 pos = ImGui::GetCursorScreenPos();

        ImGui::GetWindowDrawList()->AddImage((void *)texture_id, ImVec2(pos.x, pos.y),
             ImVec2(pos.x + window_width, pos.y + window_height), ImVec2(0, 1), ImVec2(1, 0));

        ImGui::End();
        ImGui::PopStyleVar();
        
        // ########################## END IMGUI ##############

        MainScreen::Instance()->ImGuiMainMenu(window);//2
        MainScreen::Instance()->ConsolPanel(window); // 3
        MainScreen::Instance()->ImGuiWindow(window);  // 4
        
        Bind_Framebuffer();

        MainScreen::Instance()->BgColour();


        //#########################################


        defaultShader.Use();
       
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.3f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        //view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        defaultShader.SendUniformData("projection", projection);
        defaultShader.SendUniformData("view", view);
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        defaultShader.SendUniformData("model", model);

      
        defaultShader.SendUniformData("projection", projection);
        defaultShader.SendUniformData("view", view);
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, cubePositions[0]);
        //model = glm::scale(model, glm::vec3(scale_value[0], scale_value[1], scale_value[2]));
        model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(1.0f, 0.3f, 0.5f));
        defaultShader.SendUniformData("model", model);

        MainScreen::Instance()->ClearScreen();
        

        defaultShader.Use();

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, defaultMap);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);
            
       
        
        Unbinde_Frambuffer();

        MainScreen::Instance()->RenderImGui(window); // 5 Put them in this order


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    Mesh_CleanUp();

    // close it all down and go to bed.
    // it includes the Imgui stuff
    MainScreen::Instance()->ShutDown();
    glDeleteFramebuffers(1, &FBO);
    glDeleteTextures(1, &texture_id);
    glDeleteRenderbuffers(1, &RBO);

    return 0;
}
