#include "Header/MainScreen.h"
#include "../SpdLog/LogInternals.h"

#include "../Shader/Shader.h"

#include "../MeshObjects/Mesh.h"
#include "Header/Textures.h"

#include "Header/GameInput.h"

#include "Header\FileManager.h"

#include "ECS\SolidComponents.h"



Shader defaultShader;

unsigned int defaultMap;
unsigned int floorMap;



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

    
     //Mesh_Setup(); // Load the VBO Data


    // flip image
    stbi_set_flip_vertically_on_load(true);

    //int width, height, nrChannels;

    std::string texPath = "Textures/";
    std::string texImg = "github.jpg";
    std::string floorImg = "black-limestone_s.jpg";

    defaultMap = loadTexture((texPath + texImg).c_str());
    //################ floor Map ########################
    floorMap = loadTexture((texPath + floorImg).c_str());
   

    glEnable(GL_DEPTH_TEST);
    //Creat_FrameBuffer();
    MainScreen::Instance()->Creat_FrameBuffer();
    
    // get the current opengl version number.
    //std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

    // ################ Testing my ECS Stuff ##########################################
    
    // need to creat a scean manager class to sort this lot out
    SolidComponents::Instance()->defaultPlane();
    SolidComponents::Instance()->defaultCube();
    SolidComponents::Instance()->defaultCube();
    SolidComponents::Instance()->defaultCube();
    SolidComponents::Instance()->defaultCube();
    

    // do the while loop here
    while (!glfwWindowShouldClose(window))
    {
        
        float currentFrame = static_cast<float>(glfwGetTime());
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        float time = glfwGetTime();
        
        processInput(window);

        MainScreen::Instance()->PollEvents();

       
        // ################## Start ImGui ####################################
        MainScreen::Instance()->NewImguiFrame(window); // 1 New ImGui Frame

       // MainScreen::Instance()->ClearScreen();

        ImGui::NewFrame();

        bool doc = true;
        MainScreen::Instance()->MainDockSpace(&doc); // Docking

        MainScreen::Instance()->MainScean(window); // This is the ImGui Scene Window which we are drawing are cube in

        MainScreen::Instance()->ImGuiMainMenu(window);//2 Main Window Menu
        MainScreen::Instance()->ImGuiPropertiesPanel(window); // New Prop Panel right of screen
        MainScreen::Instance()->ConsolPanel(window); // 3
        //MainScreen::Instance()->ImGuiElimentWindow(window);  // 4 Eliments Panel left 
        MainScreen::Instance()->AboutWindow(window); // About Window

        // ############### ECS ######################
        SolidComponents::Instance()->GuiEntityPanel(window);
        
        MainScreen::Instance()->Bind_Framebuffer();  // Bind the new Frambuffer
        
        //############################# End ImGui #############################################

        // MainScreen::Instance()->BgColour();
        SolidComponents::Instance()->BgColour();




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
        model = glm::translate(model,glm::vec3(0.0f, 0.5f, 0.0f)); // cubePositions[0]);
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

        //#################################### FLOOR #################################
        defaultShader.Use();
        defaultShader.SendUniformData("projection", projection);
        defaultShader.SendUniformData("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.7f, 2.1f));
        model = glm::scale(model, glm::vec3(20.0f, 0.05f, 20.0f));
        defaultShader.SendUniformData("model", model);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, floorMap);

        glBindVertexArray(planeVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);
        glBindVertexArray(0);

        //################################## END FLOOR ##############################
            
       
        
        MainScreen::Instance()->Unbinde_Frambuffer();

        // ############ ImGui Render ######################
        MainScreen::Instance()->RenderImGui(window); // 5 Put them in this order


        glfwSwapBuffers(window);
        glfwPollEvents();

    }

    Mesh_CleanUp();

    // close it all down and go to bed.
    // it includes the Imgui stuff
    MainScreen::Instance()->ShutDown();
    
    glDeleteVertexArrays(1, &planeVAO);
    glDeleteVertexArrays(1, &VAO);
    //glDeleteFramebuffers(1, &FBO);
    //glDeleteTextures(1, &texture_id);
   // glDeleteRenderbuffers(1, &RBO);

    return 0;
}
