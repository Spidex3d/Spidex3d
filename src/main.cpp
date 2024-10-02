#include "Header/MainScreen.h"
#include "../SpdLog/LogInternals.h"

#include "../Shader/Shader.h"
//#include "../Shader/ShaderManager.h" this is in app.h

#include "Header/Textures.h"

#include "Header/GameInput.h"

#include "Header\FileManager.h"

#include "ECS\SolidComponents.h"
#include "ECS\EntityNode.h"
#include "../Objects/spxObjLoader.h"

#include "../Grid/Grid.h"
#include "../Objects/DefaultCube.h" // new class
#include "../SkyBox/skyBox.h"

#include "Windows\spxWindows.h"

#include "Windows\WindowManager.h"

#include <iostream>
#include <vector>
#include <string>

#include "App.h"

unsigned int loadTexture(const std::string& filePath);

    unsigned int defaultMap; // cube map spidex
    unsigned int floorMap;  // floor map

    // #################  Lights ######
  //  glm::vec3 lightPos(1.2f, 1.5f, 2.0f);

    unsigned int lightMap;
    //unsigned int crateMap;    // crate

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

    struct Transform {
        glm::vec3 postion;
        glm::vec3 rotation;
        glm::vec3 scale;

    }; 

    
    int main(void)
    {
       

        LogInternals::Instance()->Initialize();
        // set up the glfw window
        WindowManager windowManager(SCR_WIDTH, SCR_HEIGHT, "Spidex 3d Engine");
        if (!windowManager.GLFWInitialize()) {
            return -1;
        }
        // needed for the camera
        glfwSetCursorPosCallback(windowManager.GetWindow(), mouse_callback);
        glfwSetScrollCallback(windowManager.GetWindow(), scroll_callback);

        // load a icon on the main window
        MainScreen::Instance()->Initialize(windowManager.GetWindow()); //  window icon

        MainScreen::Instance()->SetImGui(windowManager.GetWindow()); // ImGui setup
        
        
       // flip image
        stbi_set_flip_vertically_on_load(true);

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

        //                       ############ OBJ loder ############     

        const int numModels = 5;
        spxObjLoader mesh[numModels];
        unsigned int texture[numModels];

        // Load models
        mesh[0].loadOBJ("Object_loader/models/woodcrate.obj");
        mesh[1].loadOBJ("Object_loader/models/robot.obj");
        mesh[2].loadOBJ("Object_loader/models/floor.obj");
        mesh[3].loadOBJ("Object_loader/models/bunny.obj");
        mesh[4].loadOBJ("Object_loader/models/bowling_pin.obj");

        // Load textures
        texture[0] = loadTexture("Object_loader/models/woodcrate_diffuse.jpg");
        texture[1] = loadTexture("Object_loader/models/robot_diffuse.jpg");
        texture[2] = loadTexture("Object_loader/models/tile_floor.jpg");
        texture[3] = loadTexture("Object_loader/models/bunny_diffuse.jpg");
        //texture[4] = loadTexture("Object_loader/models/AMF.tga"); // bowling pin with .tga big file
        texture[4] = loadTexture("Object_loader/models/Pin.jpg");  // bowling pin with .jpg small file
        // add a light mesh on need for a texture
        spxObjLoader lightMesh;
        lightMesh.loadOBJ("Object_loader/models/light.obj");

        //############################## Assimp Test ####################################
        //Assimp::Importer imp;
        //############################## End Assimp Test #####################################

        glm::vec3 modPos[] = {
            glm::vec3(-4.5f, 0.5f, 1.0f), // wooden crate
            glm::vec3(-2.0f, -0.5f, -3.0f),  // robot
            glm::vec3(0.0f, -0.5f, 0.0f), // floor
            glm::vec3(-7.0f, -0.5f, 2.0f), // bunny
            glm::vec3(3.0f, -0.5f, 2.0f)  // bowling pin

        };
        glm::vec3 modScale[] = {
            glm::vec3(1.0f, 1.0f, 1.0f), // wooden crate
            glm::vec3(1.0f, 1.0f, 1.0f), // robot
            glm::vec3(20.0f, 0.5f, 20.0f), // floor
            glm::vec3(0.7f, 0.7f, 0.7f), // bunny
            glm::vec3(0.1f, 0.1f, 0.1f)  // bowling pin

        };


        glEnable(GL_DEPTH_TEST);
        //Creat_FrameBuffer(); which draws the image it to the imgui windoe
        MainScreen::Instance()->Creat_FrameBuffer();
        //############################################ Picking ########################################

        //ObjectSelection::Instance()->objInit(); // this works and creates the texture



        // get the current opengl version number.
        //std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;

      
        defaultCube newCube; // new  green cube class ################### GO TO LINE 412 ##############################
        defaultCube::Instance()->MaindefaultCube();

        
        std::vector<Camera1> myCamera;
        std::string name;
        int camId = 0;
           

        std::vector<Data1> myVector;
        //Node* head = nullptr;
        int currentIndex = 0;
        int indexCube = 0;
        int indexPlane = 0;
        int indexSphere = 0;
        int EntityID = 0; // Example EntityID
        
        float posy = 2.0f;

        SkyBox();

        float angel = 0.0f;  // to do with the light

               
        App::Instance()->appInIt();
        myLights.push_back({ ICON_FA_SUN" Ambient_Light", 0, LightTypeID });
        
        glm::vec3 viewPos;
        glm::vec3 lightPos(0.0f, 1.0f, 6.0f);
     
        

    // do the while loop here
        
        while (!glfwWindowShouldClose(windowManager.GetWindow()))
        {
            
            float currentFrame = static_cast<float>(glfwGetTime());
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            float time = glfwGetTime();

            processInput(windowManager.GetWindow());

            MainScreen::Instance()->PollEvents();


            // ################## Start ImGui ####################################
            MainScreen::Instance()->NewImguiFrame(windowManager.GetWindow()); // 1 New ImGui Frame

            // MainScreen::Instance()->ClearScreen();

            ImGui::NewFrame();

            bool doc = true;
            MainScreen::Instance()->MainDockSpace(&doc); // Docking
            MainScreen::Instance()->MainScean(windowManager.GetWindow()); // This is the ImGui Scene Window which we are drawing are cube in
            MainScreen::Instance()->ImGuiMainMenu(windowManager.GetWindow());//2 Main Window Menu
            MainScreen::Instance()->ConsolPanel(windowManager.GetWindow()); // 3
            //MainScreen::Instance()->ImGuiElimentWindow(window);  
            MainScreen::Instance()->AboutWindow(windowManager.GetWindow()); // About Window

            // ############### ECS ######################
            //SolidComponents::Instance()->GuiEntityPanel(window); //  Eliments Panel left 
            
            MainScreen::Instance()->Bind_Framebuffer();  // Bind the new Frambuffer to draw the main screen

            // ######################################## Render UI Vector  ##################################
             //################################### THIS IS THE NEW BIT Vector #############
            EntityNode::Instance()->renderPropertiesPanel();
            EntityNode::Instance()->renderUI(myVector, currentIndex, indexCube, indexPlane, indexSphere, EntityID);
            EntityNode::Instance()->renderCameraUI(myCamera, name, camId);
           
            // ######################################## END Render UI  ########################################################          

            //############################# End ImGui #############################################

            // MainScreen::Instance()->BgColour();
            SolidComponents::Instance()->BgColour();

            // ############################### Lighting ###############################
           // App::Instance()->AppRuning();
                                         
           
          
           // glm::vec3 viewPos;
            
           // glm::vec3 lightPos(0.0f, 1.0f, 6.0f);
          //  glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
            glm::vec3 lightColor(amb_light[0], amb_light[1], amb_light[2]);

            angel += (float)deltaTime * 50.0f;
            lightPos.x = 4.0f * sinf(glm::radians(angel));

            





            // ###################################### Camera Control ########################################

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.2f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();
            //view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
            //defaultShader.SendUniformData("projection", projection);
            //defaultShader.setMat4("projection", projection);
            ShaderManager::LightCubeShader->setMat4("projection", projection);
            
            //defaultShader.SendUniformData("view", view);
            ShaderManager::LightCubeShader->setMat4("view", view);
            //defaultShader.setMat4("view", view);
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            ShaderManager::LightCubeShader->setMat4("model", model);
            //defaultShader.setMat4("model", model);

            MainScreen::Instance()->ClearScreen();

            
            

           

            // ######################################### Default Cube #######################################
            ShaderManager::LightCubeShader->Use();
            ShaderManager::LightCubeShader->setMat4("projection", projection);
            ShaderManager::LightCubeShader->setMat4("view", view);
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

            ShaderManager::LightCubeShader->setMat4("model", model);


            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, defaultMap);
            

            defaultCube::Instance()->draw();

            // ######################################### END Default Cube #######################################
            
            ShaderManager::LightCubeShader->Use();
            ShaderManager::LightCubeShader->setMat4("view", view);
            ShaderManager::LightCubeShader->setMat4("projection", projection);
            ShaderManager::LightCubeShader->setVec3("viewPos", viewPos);
            ShaderManager::LightCubeShader->setVec3("lightColor", lightColor);
            ShaderManager::LightCubeShader->setVec3("lightPos", lightPos);

            //             ################### draw obj mesh ###################
            for (int i = 0; i < numModels; i++)
            {
                model = glm::translate(glm::mat4(1.0f), modPos[i]) * glm::scale(glm::mat4(1.0f), modScale[i]);
                ShaderManager::LightCubeShader->setMat4("model", model);
                glBindTexture(GL_TEXTURE_2D, texture[i]);
                mesh[i].objDraw();
                glBindTexture(texture[i], 0);
            }        

             //                           ### Light OBJ ######   
                
                model = glm::translate(model = glm::mat4(1.0f), lightPos);
                ShaderManager::LightBulbShader->Use();
                //LightBulbShader.setVec3("lightColor", lightColor);
                ShaderManager::LightBulbShader->setVec3("lightColor", amb_light[0], amb_light[1], amb_light[2]);
                ShaderManager::LightBulbShader->setMat4("model", model);
                ShaderManager::LightBulbShader->setMat4("view", view);
                ShaderManager::LightBulbShader->setMat4("projection", projection);
                lightMesh.objDraw();
            
            //###################################### Test Render 10 multiple cubes Start ###############################

            for (int idxCube = 0; idxCube < 10; ++idxCube) {
                // this loops 10 times

                ShaderManager::LightCubeShader->Use();
                ShaderManager::LightCubeShader->setMat4("projection", projection);
                ShaderManager::LightCubeShader->setMat4("view", view);

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
                ShaderManager::LightCubeShader->setMat4("model", model);

                                
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
                    newCube.position = glm::vec3(0.0f, 0.5f, -3.0f); // Default position
                    newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f);  // Default scale
                    break;
                case 1:
                    newCube.position = glm::vec3(-4.0f, 0.5f, 0.0f); // Default position
                    newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f);  // Default scale                   
                    break;
                case 2:
                    newCube.position = glm::vec3(-6.0f, 0.5f, 0.0f); // Default position
                    newCube.scale = glm::vec3(2.0f, 2.0f, 2.0f); // Default scale
                    break;
                case 3:
                    newCube.position = glm::vec3(-5.0f, 0.5f, 3.0f); // Default position
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
                ShaderManager::defaultShader->Use();
                ShaderManager::defaultShader->setMat4("projection", projection);
                ShaderManager::defaultShader->setMat4("view", view);
                ShaderManager::defaultShader->setMat4("model", cube.model);

                glActiveTexture(GL_TEXTURE0);
               
                glBindTexture(GL_TEXTURE_2D, cube.textureID);// so we know which cube has which texture
                //std::cout << "Rendering cube with texture ID: " << cube.textureID << std::endl;
                defaultCube::Instance()->draw();
            }
                      
            //######################### End Draw new cube on button click #############################
                
             //###################################### Grid Start ###############################
             // app->getDefaultGridShader().Use();
            if (!gridNogrid) {   // Show the grid or hide it

                ShaderManager::defaultGridShader->Use();
                
                ShaderManager::defaultGridShader->setMat4("projection", projection);
                ShaderManager::defaultGridShader->setMat4("view", view);
                model = glm::mat4(1.0f);
                model = glm::translate(model, glm::vec3(0.0f, -0.5f, 0.0f)); // this is better
                model = glm::scale(model, glm::vec3(20.0f, 0.0f, 20.0f));
                ShaderManager::defaultGridShader->setMat4("model", model);

                Grid::Instance()->gridRender();
            }
            //###################################### Grid End Start of Sky ###############################
            if (addSky) {
                glDepthFunc(GL_LEQUAL);
                ShaderManager::skyShader->Use();

                view = glm::mat4(1.0f);
                view = glm::mat4(glm::mat3(camera.GetViewMatrix()));
                model = glm::rotate(model, glm::radians(45.0f) * time, glm::vec3(0.0f, 0.3f, 0.0f));
                //projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / SCR_HEIGHT, 0.3f, 10000.0f);
                ShaderManager::skyShader->setMat4("view", view);
                ShaderManager::skyShader->setMat4("projection", projection);
                glBindVertexArray(skyVAO);
                glActiveTexture(GL_TEXTURE0);
                glBindTexture(GL_TEXTURE_CUBE_MAP, skyTextureID);
                glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
                glBindVertexArray(0);

                glDepthFunc(GL_LESS);

            }
            // ###################################### End SkyBox ################################## 

            MainScreen::Instance()->Unbinde_Frambuffer();

            // ############ ImGui Render ######################
            MainScreen::Instance()->RenderImGui(windowManager.GetWindow()); // 5 Put them in this order

            glfwSwapBuffers(windowManager.GetWindow());
            glfwPollEvents();

        }
        // close it all down and go to bed.
        glDeleteTextures(1, &skyTextureID);
        glDeleteVertexArrays(1,&skyVAO);
        glDeleteBuffers(1, &skyVBO);

        // it includes the Imgui stuff
        MainScreen::Instance()->ShutDown();   

        
        return 0;
    }
    
    
    
