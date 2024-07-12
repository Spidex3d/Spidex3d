#include "pch.h"
#include "MainScreen.h"
#include "../SpdLog/LogInternals.h"

#include "../Shader/Shader.h"

#include "../MeshObjects/Mesh.h"
#include "Textures.h"

#include "GameInput.h"

//void framebuffer_size_callback(GLFWwindow* window, int width, int height);
//void mouse_callback(GLFWwindow* window, double xpos, double ypos);
//void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
//void processInput(GLFWwindow* window);

Shader defaultShader;

unsigned int defaultMap;

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
    
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
   

    MainScreen::Instance()->SetImGui(window); // ImGui setup

    MainScreen::Instance()->Initialize(window); // MakeContextCurrent - glad and window icon
    
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
        MainScreen::Instance()->ImGuiMainMenu(window);//2
        MainScreen::Instance()->ConsolPanel(window); // 3
        MainScreen::Instance()->ImGuiWindow(window);  // 4

        MainScreen::Instance()->BgColour();

        MainScreen::Instance()->ClearScreen();

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


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, defaultMap);

        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        //#########################################
        

        MainScreen::Instance()->RenderImGui(window); // 5 Put them in this order


        glfwSwapBuffers(window);

    }

    Mesh_CleanUp();

    // close it all down and go to bed.
    // it includes the Imgui stuff
    MainScreen::Instance()->ShutDown();

    return 0;
}