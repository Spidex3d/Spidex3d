#include "Header/MainScreen.h"
#include "../SpdLog/LogInternals.h"

#include "../Shader/Shader.h"

#include "Header/Textures.h"
#include "../Objects/DefaultCube.h"

#include "Header/GameInput.h"

#include "Header\FileManager.h"

#include "ECS\SolidComponents.h"
#include "ECS\EntityNode.h"

#include "../Grid/Grid.h"

#include <vector>



Shader defaultShader;
Shader defaultGridShader;

unsigned int defaultMap; // cube map
unsigned int floorMap;  // floor map
unsigned int crateMap;    // crate

GLuint vao;
GLuint vbo;
GLuint ebo;

// update cube position
void updateCubePosition(int index, glm::vec3 newPosition, glm::vec3 newScale) {
    if (index >= 0 && index < mycubes.size()) {
        mycubes[index].position = newPosition, mycubes[index].scale = newScale;

        // Update the model matrix
        mycubes[index].model = glm::mat4(1.0f);
        mycubes[index].model = glm::translate(mycubes[index].model, mycubes[index].position);
        mycubes[index].model = glm::scale(mycubes[index].model, mycubes[index].scale);
    }
    else {
        std::cout << "Invalid cube index" << std::endl;
    }
}
// delete a selected cube
void deleteCube(int index) {
    if (index >= 0 && index < mycubes.size()) {
        mycubes.erase(mycubes.begin() + index);
        std::cout << "Cube at index " << index << " deleted." << std::endl;
    }
    else {
        std::cout << "Invalid cube index" << std::endl;
    }
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
     defaultGridShader.Load("Shader/shaderFile/default_Grid.vert", "Shader/shaderFile/default_Grid.frag");

    
     defaultCube newCube; // new  green cube class ################### GO TO LINE 412 ##############################
     defaultCube::Instance()->MaindefaultCube();


    // flip image
    stbi_set_flip_vertically_on_load(true);

    //int width, height, nrChannels;

    std::string texPath = "Textures/";
    std::string texImg = "github.jpg";
    std::string floorImg = "black-limestone_s.jpg";
    std::string crateImg = "crate.jpg";

    defaultMap = loadTexture((texPath + texImg).c_str());
    //################ floor Map ########################
    floorMap = loadTexture((texPath + floorImg).c_str());
    //################# Crate Map #######################
    crateMap = loadTexture((texPath + crateImg).c_str());
   

    glEnable(GL_DEPTH_TEST);
    //Creat_FrameBuffer();
    MainScreen::Instance()->Creat_FrameBuffer();
    
    // get the current opengl version number.
    //std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

    // ################ Testing my ECS Stuff ##########################################
    
    // need to creat a scean manager class to sort this lot out
    SolidComponents::Instance()->defaultPlane();
    SolidComponents::Instance()->defaultCube();
    
   // SolidComponents::Instance()->defaultCube();
   // SolidComponents::Instance()->defaultCube();
   // SolidComponents::Instance()->defaultCube();

    
    
    // ################################################## grid ########################
    const auto FILL = fill; // 20 x 20 Grid do something with this at runtime
    float SIZE = 1.0f;
    
    //std::vector<float> gridVertices = createGridVertices(1.0f, 20);
    std::vector<float> gridVertices = createGridVertices(SIZE, FILL);
    
    glGenVertexArrays(1, &GridVAO);
    glGenBuffers(1, &GridVBO);

    glBindVertexArray(GridVAO);
    glBindBuffer(GL_ARRAY_BUFFER, GridVBO);
    glBufferData(GL_ARRAY_BUFFER, gridVertices.size() * sizeof(float), gridVertices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    
    // ################################################## grid End ########################
    
    std::vector<Data1> myVector;
    //Node* head = nullptr;
    int currentIndex = 0;
    int indexCube = 0;
    int indexPlane = 0;
    int indexSphere = 0;
    int EntityID = 0; // Example EntityID
    
    float posy = 2.0f;
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
        MainScreen::Instance()->ConsolPanel(window); // 3
        //MainScreen::Instance()->ImGuiElimentWindow(window);  
        MainScreen::Instance()->AboutWindow(window); // About Window

        // ############### Object manegment system ######################
        SolidComponents::Instance()->GuiEntityPanel(window); //  Eliments Panel left 
       
        
        EntityNode::Instance()->renderPropertiesPanel();
        EntityNode::Instance()->renderUI(myVector, currentIndex, indexCube, indexPlane, indexSphere, EntityID);
        
        MainScreen::Instance()->Bind_Framebuffer();  // Bind the new Frambuffer
        //############################# End ImGui #############################################

        // MainScreen::Instance()->BgColour();
        SolidComponents::Instance()->BgColour();

        // ##################################### Camera Control ############################
        defaultShader.Use();
        glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.3f, 100.0f);
        glm::mat4 view = camera.GetViewMatrix();
        //view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
        defaultShader.SendUniformData("projection", projection);
        defaultShader.SendUniformData("view", view);
        glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        defaultShader.SendUniformData("model", model);
        
        MainScreen::Instance()->ClearScreen();
        
        // ##################################### Default Cube ############################
        
        defaultShader.SendUniformData("projection", projection);
        defaultShader.SendUniformData("view", view);
        model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f)); // cubePositions[0]);
        // if (selected) do this
        //model = glm::scale(model, glm::vec3(scale_val[0], scale_val[1], scale_val[2]));
        model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
        if (rotateCube) {
            model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.0f, 0.3f, 0.0f));
            // model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(scale_val[0], scale_val[1], scale_val[2]));
        }
       
        defaultShader.SendUniformData("model", model);


        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, defaultMap);

        defaultCube::Instance()->draw();


            // click a button to add a new cube index 1
        //if (shouldAddCube) {
        //    // ################################ add cube 2 ##########################

        //    model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        //    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f)); // cubePositions[0]);
        //    model = glm::scale(model, glm::vec3(scale_val[0], scale_val[1], scale_val[2]));
        //    model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.0f, 0.3f, 0.0f));

        //    defaultShader.SendUniformData("model", model);

        //    glActiveTexture(GL_TEXTURE0);
        //    glBindTexture(GL_TEXTURE_2D, floorMap);

        //    glBindVertexArray(VAO);
        //    glDrawArrays(GL_TRIANGLES, 0, 36);
        //    glBindVertexArray(0);         
        //   
        //}

        //###################################### Render 10 multiple cubes Start ###############################

        for (int idxCube = 0; idxCube < 10; ++idxCube) {
            // this loops 10 times

            //defaultTestShader.Use();
            defaultShader.Use();
            defaultShader.SendUniformData("projection", projection);
            defaultShader.SendUniformData("view", view);

            glm::mat4 model = glm::mat4(1.0f);

            if (idxCube < 10) {
                model = glm::translate(model, glm::vec3(idxCube * 2.0f, 0.0f, 0.0f));
            }

            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));

            defaultShader.SendUniformData("model", model);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, floorMap);

            defaultCube::Instance()->draw();

        }
        
        //###################################### Render A New cubes on button click ###############################           

        if (shouldAddCube) {
            cubeIndex = mycubes.size(); // Use the size of the vector to determine the next index

            Cube1 newCube; // Assuming Cube is a struct or class with position, scale, and model members

            // Set position and scale based on cubeIndex
            switch (cubeIndex) {
            case 0:
                newCube.position = glm::vec3(0.0f, 0.0f, -3.0f);
                newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f);
                break;
            case 1:
                newCube.position = glm::vec3(-4.0f, 0.5f, 0.0f);
                newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f);
                break;
            case 2:
                newCube.position = glm::vec3(-6.0f, 0.0f, 0.0f);
                newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f); // Default scale
                break;
            case 3:
                newCube.position = glm::vec3(-5.0f, 0.0f, 3.0f);
                newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f); // Default scale
                break;
            default: // cube No5

                newCube.position = glm::vec3(0.0f, posy, 0.0f); // Default position for any additional cubes
                newCube.scale = glm::vec3(0.5f, 0.5f, 0.5f); // Default scale
                posy += 1.0;
                break;
            }

            // Initialize model matrix
            newCube.model = glm::mat4(1.0f);
            newCube.model = glm::translate(newCube.model, newCube.position);
            newCube.model = glm::scale(newCube.model, newCube.scale);

            // Add the new cube to the vector
            mycubes.push_back(newCube);

            shouldAddCube = false;

            std::cout << "Cube Index " << cubeIndex << std::endl;
        }

        // Update positions and models for all cubes
        for (auto& cube : mycubes) {

            cube.model = glm::mat4(1.0f); // Reset to identity matrix
            cube.model = glm::translate(cube.model, cube.position); // Apply new translation
            cube.model = glm::scale(cube.model, cube.scale);
        }

        // Update cube position if needed
        if (shouldMoveCube) {
            //int cubeIndexToMove = cubeIndexTM; // The index of the cube you want to move
            if (cubeIndexTM != -1) {
                //glm::vec3 newCubePosition = glm::vec3(5.0f, 2.0f, 3.0f); // The new position for the cube
                glm::vec3 newCubePosition = glm::vec3(pos_val[0], pos_val[1], pos_val[2]); // The new position for the cube
                glm::vec3 newCubeScale = glm::vec3(scale_val[0], scale_val[1], scale_val[2]);
                //updateCubePosition(cubeIndexTM, newCubePosition);
                updateCubePosition(cubeIndexTM, newCubePosition, newCubeScale);
                std::cout << " you picked cube: " << cubeIndexTM << std::endl;

                shouldMoveCube = false; // Reset the flag
            }
        }

        if (shouldDeleteCube) {
            if (cubeIndexTM != -1) { // Check if a valid index is set
                deleteCube(cubeIndexTM);
                cubeIndexTM = -1; // Reset the index
                shouldDeleteCube = false; // Reset the flag
            }
        }

        // Render all cubes
        for (auto& cube : mycubes) {
            defaultShader.Use();
            defaultShader.SendUniformData("projection", projection);
            defaultShader.SendUniformData("view", view);
            defaultShader.SendUniformData("model", cube.model);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, crateMap);
            defaultCube::Instance()->draw();
        }

        //######################### End Draw new cube on button click #############################

        
            
        //###################################### Grid Start ###############################

        defaultGridShader.Use();
        defaultGridShader.SendUniformData("projection", projection);
        defaultGridShader.SendUniformData("view", view);
        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f));
        model = glm::scale(model, glm::vec3(20.0f, 0.0f, 20.0f));
        defaultGridShader.SendUniformData("model", model);

        glBindVertexArray(GridVAO);
        glDrawArrays(GL_LINES, 0, gridVertices.size());
        glBindVertexArray(0);
        
        //###################################### Grid End ###############################

        //#################################### FLOOR #################################
        /*
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
          */  
       
        
        MainScreen::Instance()->Unbinde_Frambuffer();

        // ############ ImGui Render ######################
        MainScreen::Instance()->RenderImGui(window); // 5 Put them in this order


        glfwSwapBuffers(window);
        glfwPollEvents();

        

    }

    //Mesh_CleanUp();

    // close it all down and go to bed.
    // it includes the Imgui stuff
    MainScreen::Instance()->ShutDown();
    
    return 0;
}
