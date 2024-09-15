#include "Header/MainScreen.h"
#include "../SpdLog/LogInternals.h"

#include "../Shader/Shader.h"

#include "Header/Textures.h"

#include "Header/GameInput.h"

#include "Header\FileManager.h"

#include "ECS\SolidComponents.h"
#include "ECS\EntityNode.h"
//#include "ECS\ObjectSelection.h"

#include "../Grid/Grid.h"
#include "../Objects/DefaultCube.h" // new class
#include "../SkyBox/skyBox.h"

#include "Windows\spxWindows.h"

#include <iostream>
#include <vector>
#include <string>

unsigned int loadTexture(const std::string& filePath);

//int fill = 20; // use this to change how many squares in the grid

    Shader defaultShader;
    Shader defaultGridShader;
    Shader defaultTestShader;
    Shader skyShader;

    unsigned int defaultMap; // cube map spidex
    unsigned int floorMap;  // floor map
    //unsigned int crateMap;    // crate

    GLuint vao;
    GLuint vbo;
    GLuint ebo;

   //  updateCubePosition(cubeIndexTM, newCubePosition, newCubeScale, newCubeRotation);

    // update cube position
    //void updateCubePosition(int index, glm::vec3 newPosition) {
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

    struct Transform {
        glm::vec3 postion;
        glm::vec3 rotation;
        glm::vec3 scale;

    }; 

    
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

        //################################ Load Shader Files #######################################
        //Shader defaultShader;
        defaultShader.Load("Shader/shaderFile/default.vert", "Shader/shaderFile/default.frag");
        defaultGridShader.Load("Shader/shaderFile/default_Grid.vert", "Shader/shaderFile/default_Grid.frag");
        defaultTestShader.Load("Shader/shaderFile/test.vert", "Shader/shaderFile/test.frag");

        skyShader.Load("Shader/shaderFile/sky.vert", "Shader/shaderFile/sky.frag");
        
       // flip image
        stbi_set_flip_vertically_on_load(true);

        //int width, height, nrChannels;

        std::string texPath = "Textures/";
        std::string texImg = "github.jpg";
        std::string floorImg = "black-limestone_s.jpg";
        std::string crateImg = "default.jpg";
        

        defaultMap = loadTexture((texPath + texImg).c_str());
        //################ floor Map ########################
        floorMap = loadTexture((texPath + floorImg).c_str());
        //################ Cube Map ########################
        crateMap = loadTexture((texPath + crateImg).c_str());
        std::string myTexturePath;

        


        glEnable(GL_DEPTH_TEST);
        //Creat_FrameBuffer(); which draws the image it to the imgui windoe
        MainScreen::Instance()->Creat_FrameBuffer();
        //############################################ Picking ########################################

        //ObjectSelection::Instance()->objInit(); // this works and creates the texture



        // get the current opengl version number.
        //std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

        // ################ Testing my ECS Stuff ##########################################

        defaultCube newCube; // new  green cube class ################### GO TO LINE 412 ##############################
        defaultCube::Instance()->MaindefaultCube();

        //SolidComponents::Instance()->defaultCube();   // draw the spidex cube
        // Mesh_Setup(); // Load the VBO Data


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

        SkyBox();

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

            // ############### ECS ######################
            //SolidComponents::Instance()->GuiEntityPanel(window); //  Eliments Panel left 
            
            MainScreen::Instance()->Bind_Framebuffer();  // Bind the new Frambuffer

            // ######################################## Render UI Vector or Linked List!!! ##################################
             // THIS IS THE NEW BIT Vector or Linked List!!! #############
            EntityNode::Instance()->renderPropertiesPanel();
            EntityNode::Instance()->renderUI(myVector, currentIndex, indexCube, indexPlane, indexSphere, EntityID);

            // ######################################## END Render UI  ########################################################
            // Object Selection
            //ObjectSelection::Instance()->ObjSelection();
            //ObjectSelection::Instance()->TestTexture();
          
           

            //############################# End ImGui #############################################

            // MainScreen::Instance()->BgColour();
            SolidComponents::Instance()->BgColour();


            defaultShader.Use();
            // ###################################### Camera Control ########################################

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.2f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            //view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
            defaultShader.SendUniformData("projection", projection);
            defaultShader.SendUniformData("view", view);
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            defaultShader.SendUniformData("model", model);

            MainScreen::Instance()->ClearScreen();

            // ######################################### Default Cube #######################################
            defaultShader.SendUniformData("projection", projection);
            defaultShader.SendUniformData("view", view);
            model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            //model = glm::translate(model, glm::vec3(pos_val[0], pos_val[1], pos_val[2])); // cubePositions[0]);
            model = glm::translate(model,glm::vec3(0.0f, 0.0f, 1.0f)); // cubePositions[0]);
            // if (selected) do this
            //model = glm::scale(model, glm::vec3(scale_val[0], scale_val[1], scale_val[2]));
            model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
            if (rotateCube) {
                model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.0f, 0.3f, 0.0f));
               // model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(scale_val[0], scale_val[1], scale_val[2]));
            }
            //model = glm::rotate(model, glm::radians(45.0f), glm::vec3(rot_val[0], rot_val[1], rot_val[2]));

            defaultShader.SendUniformData("model", model);


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, defaultMap);

            defaultCube::Instance()->draw();

            // ######################################### END Default Cube #######################################
            // click a button to add a new cube index 1
            //if (shouldAddCube) {
            //    // ################################ Test add cube 2 the rotating one ##########################

                //model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
                //model = glm::translate(model, glm::vec3(0.0f, 0.0f, 2.0f)); // cubePositions[0]);
                //model = glm::scale(model, glm::vec3(scale_val[0], scale_val[1], scale_val[2]));
                //model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.0f, 0.3f, 0.0f));

                //defaultShader.SendUniformData("model", model);

                //glActiveTexture(GL_TEXTURE0);
                //glBindTexture(GL_TEXTURE_2D, floorMap);

                //glBindVertexArray(VAO);
                //glDrawArrays(GL_TRIANGLES, 0, 36);
                //glBindVertexArray(0);
            //}

            //###################################### Test Render 10 multiple cubes Start ###############################

            for (int idxCube = 0; idxCube < 10; ++idxCube) {
                // this loops 10 times

                defaultShader.Use();
                defaultShader.SendUniformData("projection", projection);
                defaultShader.SendUniformData("view", view);

                glm::mat4 model = glm::mat4(1.0f);

                if (idxCube < 10) {
                    model = glm::translate(model, glm::vec3(idxCube * 2.0f, 0.0f, 0.0f));
                }
                //if (idxCube == 2) {
                //    model = glm::translate(model, glm::vec3(pos_val[0], pos_val[1], pos_val[2])); // cubePositions[0]);
                //}
                //if (idxCube == 2) {
                //    model = glm::scale(model, glm::vec3(scale_val[0], scale_val[1], scale_val[2]));
                //}
                else {
                    model = glm::scale(model, glm::vec3(1.0f, 1.0f, 1.0f));
                }
                defaultShader.SendUniformData("model", model);

                                
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_2D, floorMap);

                defaultCube::Instance()->draw();
            }
            
            //###################################### Render A New cubes on button click ###############################           

            if (shouldAddCube) {
                cubeIndex = mycubes.size(); // Use the size of the vector to determine the next index

                Cube1 newCube; // Assuming Cube is a struct or class with position, scale, model and textureID members

                // Set position and scale based on cubeIndex
                switch (cubeIndex) {
                case 0:
                    newCube.position = glm::vec3(0.0f, 0.0f, -3.0f); // Default position
                    newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f);  // Default scale
                    break;
                case 1:
                    newCube.position = glm::vec3(-4.0f, 0.5f, 0.0f); // Default position
                    newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f);  // Default scale                   
                    break;
                case 2:
                    newCube.position = glm::vec3(-6.0f, 0.0f, 0.0f); // Default position
                    newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f); // Default scale
                    break;
                case 3:
                    newCube.position = glm::vec3(-5.0f, 0.0f, 3.0f); // Default position
                    newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f); // Default scale
                    break;
                default: // cube No5
                    
                    newCube.position = glm::vec3(posy, 0.0f, -2.0f); // Default position for any additional cubes
                    newCube.scale = glm::vec3(1.0f, 1.0f, 1.0f); // Default scale
                    posy += 1.5;
                    break;
                }               
                // Initialize model matrix
                newCube.model = glm::mat4(1.0f);
                newCube.model = glm::translate(newCube.model, newCube.position);
                newCube.model = glm::scale(newCube.model, newCube.scale);
                
                newCube.textureID = loadTexture("Textures/default.jpg");
                // Add the new cube to the vector or a object obj or light, Texture
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
            // Update object position scale texture ect
            if (shouldUpdateObject) {
                
                if (objectUpdateIndex != -1) {
                    
                    glm::vec3 newCubePosition = glm::vec3(pos_val[0], pos_val[1], pos_val[2]); // The new position for the cube
                    glm::vec3 newCubeScale = glm::vec3(scale_val[0], scale_val[1], scale_val[2]);
                    updateCubePosition(objectUpdateIndex, newCubePosition, newCubeScale);
                    
                    std::cout << " you picked cube: " << objectUpdateIndex << std::endl;

                    shouldUpdateObject = false; // Reset the flag
                }
            }

            if (shouldDeleteObject) {
                if (objectUpdateIndex != -1) { // Check if a valid index is set
                    deleteCube(objectUpdateIndex);
                    objectUpdateIndex = -1; // Reset the index
                    shouldDeleteObject = false; // Reset the flag
                }
            }

            // Render all cubes
            for (auto& cube : mycubes) {
                defaultShader.Use();
                defaultShader.SendUniformData("projection", projection);
                defaultShader.SendUniformData("view", view);
                defaultShader.SendUniformData("model", cube.model);

                glActiveTexture(GL_TEXTURE0);
               
                glBindTexture(GL_TEXTURE_2D, cube.textureID);// so we know which cube has which texture
                //std::cout << "Rendering cube with texture ID: " << cube.textureID << std::endl;
                defaultCube::Instance()->draw();
            }
                      

            //######################### End Draw new cube on button click #############################
                

            //###################################### Test Grid Start ###############################

            defaultGridShader.Use();
            defaultGridShader.SendUniformData("projection", projection);
            defaultGridShader.SendUniformData("view", view);
            model = glm::mat4(1.0f);
            //model = glm::translate(model, glm::vec3(0.0f, -0.5f, 2.1f));
            model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); // this is better
            model = glm::scale(model, glm::vec3(20.0f, 0.0f, 20.0f));
            defaultGridShader.SendUniformData("model", model);

            glBindVertexArray(GridVAO);
            glDrawArrays(GL_LINES, 0, gridVertices.size());
            glBindVertexArray(0);

            //###################################### Grid End Start of Sky ###############################

            glDepthFunc(GL_LEQUAL);
            skyShader.Use();

            view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
            //projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.3f, 10000.0f);
            skyShader.SendUniformData("view", view);
            skyShader.SendUniformData("projection", projection);
            view = glm::mat4(1.0f);
            glBindVertexArray(skyVAO);
            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_CUBE_MAP, skyTextureID);
            glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
            glBindVertexArray(0);

            glDepthFunc(GL_LESS);

            // ######################################End SkyBox ##################################

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

       

        // close it all down and go to bed.
        // it includes the Imgui stuff
        glDeleteVertexArrays(1,&skyVAO);
        glDeleteBuffers(1, &skyVBO);


        MainScreen::Instance()->ShutDown();

        

        return 0;
    }
    
    
    
