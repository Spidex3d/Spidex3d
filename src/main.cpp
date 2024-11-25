#include "Header/MainScreen.h"
#include "../SpdLog/LogInternals.h"

#include "../Shader/Shader.h"
//#include "../Shader/ShaderManager.h" this is in app.h

#include "Header/Textures.h"

#include "Header/GameInput.h"

#include "Header\FileManager.h"

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

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>
#include <thread>


//#include "../Lighting/Lights.h"

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
        if (index >= 0 && index < myGameObject.size()) {
            myGameObject[index].position = newPosition, myGameObject[index].scale = newScale;

            // Update the model matrix
            myGameObject[index].model = glm::mat4(1.0f);
            myGameObject[index].model = glm::translate(myGameObject[index].model, myGameObject[index].position);
            myGameObject[index].model = glm::scale(myGameObject[index].model, myGameObject[index].scale);
        }
        else {
            std::cout << "Invalid cube index" << std::endl;
        }
    }
    // delete a selected cube
    void deleteCube(int index) {
        if (index >= 0 && index < myGameObject.size()) {
            myGameObject.erase(myGameObject.begin() + index);
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
        


        defaultMap = loadTexture((texPath + texImg).c_str());
        //################ floor Map ########################
        floorMap = loadTexture((texPath + floorImg).c_str());
        

        //                       ############ OBJ loder ############     

        /*const int numModels = 5;
        spxObjLoader M_mesh[numModels];
        unsigned int M_texture[numModels];*/

        // add a light mesh on need for a texture    
        


        unsigned int M_texture[numInitialModels];
        spxObjLoader M_mesh[numInitialModels];

        spxObjLoader lightMesh;
        lightMesh.loadOBJ("Lighting/Light_Obj/light.obj");

        // Load models M_mesh = obj file
        M_mesh[0].loadOBJ("Models/floor.obj");
        M_mesh[1].loadOBJ("Models/robot.obj");  
        //M_mesh[2].loadOBJ("Object_loader/models/bowling_pin.obj");
        //M_mesh[3].loadOBJ("Object_loader/models/woodcrate.obj");
        //M_mesh[3].loadOBJ("Object_loader/models/bunny.obj");

        
        // Load textures M_texture = obj texture
        M_texture[0] = loadTexture("Models/floor.jpg");
        M_texture[1] = loadTexture("Models/robot.jpg");
        //M_texture[2] = loadTexture("Object_loader/models/bowling_pin.jpg");  // bowling pin with .jpg small file
        //M_texture[3] = loadTexture("Object_loader/models/woodcrate.jpg");
        //M_texture[3] = loadTexture("Object_loader/models/bunny.jpg");
        //M_texture[4] = loadTexture("Object_loader/models/AMF.tga"); // bowling pin with .tga big file
        
       
        //glm::vec3 modPos[] = {
        //    glm::vec3(-4.5f, 0.5f, 1.0f), // wooden crate
        //    glm::vec3(-2.0f, -0.5f, -3.0f),  // robot
        //    glm::vec3(0.0f, -0.5f, 0.0f), // floor
        //    glm::vec3(-7.0f, -0.5f, 2.0f), // bunny
        //    glm::vec3(3.0f, -0.5f, 2.0f)  // bowling pin

        //};
        //glm::vec3 modScale[] = {
        //    glm::vec3(1.0f, 1.0f, 1.0f), // wooden crate
        //    glm::vec3(1.0f, 1.0f, 1.0f), // robot
        //    glm::vec3(20.0f, 0.5f, 20.0f), // floor
        //    glm::vec3(0.7f, 0.7f, 0.7f), // bunny
        //    glm::vec3(0.1f, 0.1f, 0.1f)  // bowling pin

        //};        

        // Add initial models to vectors  this is to do with obj
        for (int i = 0; i < numInitialModels; ++i) {  
            models.push_back(M_mesh[i]);
            textures.push_back(M_texture[i]);
            modelPositions.push_back(initialModPos[i]);
            modelScales.push_back(initialModScale[i]);
        }
       
 
        glEnable(GL_DEPTH_TEST);
       
        //Creat_FrameBuffer(); which draws the image in to the main imgui window
        MainScreen::Instance()->Creat_FrameBuffer();
        //############################################ Picking ########################################

        //ObjectSelection::Instance()->objInit(); // this works and creates the texture



        // get the current opengl version number.
        //std::cout << "GL_VERSION: " << glGetString(GL_VERSION) << std::endl;


        defaultCube newCube; // new  green cube class ################### GO TO LINE 412 ##############################
        defaultCube::Instance()->MaindefaultCube();

        std::string name;
        int camId = 0;


        std::vector<GameData> myVector;  // this is the game Object main VECTOR ##############
        //std::vector<LightData> myLightObject; // this is the Light object main VECTOR ##############
        int currentIndex = 0;
        int indexCube = 0;
        int indexPlane = 0;
        int indexSphere = 0;
        int ObjectTypeID = 0;
        int indexLight = 0;


        float posx = 2.0f; // move the 10 cubes + 2 on the x

        SkyBox();

        float angel = 0.0f;  // to do with the light movment

        App::Instance()->appInIt();
        // ################################   Lighting ######################
              
              
        glm::vec3 lightPos; // start of light positionglm::vec3

                     
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

            ImGui::NewFrame();
            // MainScreen::Instance()->ImGuiInit(windowManager.GetWindow());

            bool doc = true;
            MainScreen::Instance()->MainDockSpace(&doc); // Docking
            MainScreen::Instance()->MainScean(windowManager.GetWindow()); // This is the ImGui Scene Window which we are drawing are cube in
            MainScreen::Instance()->ImGuiMainMenu(windowManager.GetWindow());//2 Main Window Menu
            MainScreen::Instance()->ConsolPanel(windowManager.GetWindow()); // 3
            //MainScreen::Instance()->ImGuiElimentWindow(window);  
            MainScreen::Instance()->AboutWindow(windowManager.GetWindow()); // About Window

            MainScreen::Instance()->Bind_Framebuffer();  // Bind the new Frambuffer to draw the main screen

            // ######################################## Render UI Vector  ##################################
             //################################### THIS IS THE NEW BIT Vector #############
            //EntityNode::Instance()->renderPropertiesPanel();
            EntityNode::Instance()->renderProperties(myVector, currentIndex, indexCube, indexPlane, indexSphere, indexLight, ObjectTypeID);
            EntityNode::Instance()->renderUI(myVector, currentIndex, indexCube, indexPlane, indexSphere, indexLight, ObjectTypeID);
            //EntityNode::Instance()->renderCameraUI(myCamera, name, camId);

            // ######################################## END Render UI  ########################################################          

            //############################# End ImGui #############################################

             MainScreen::Instance()->BgColour();
             
            
            //################################ Lighting New ################################
             float ambientFactor(ambient_factor[0]);
             glm::vec3 lightColor(amb_light[0], amb_light[1], amb_light[2]);

            ShaderManager::LightCubeShader->Use();
            ShaderManager::LightCubeShader->setVec3("light.position", lightPos);
            ShaderManager::LightCubeShader->setVec3("viewPos", camera.Position);
            ShaderManager::LightCubeShader->setVec3("light.ambient", 1.8f, 1.8f, 1.8f);
            ShaderManager::LightCubeShader->setVec3("light.diffuse", 1.5f, 1.5f, 1.5f);
            ShaderManager::LightCubeShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
           
            ShaderManager::LightCubeShader->setVec3("matirial.specular", 0.5f, 0.5f, 0.5f);
            ShaderManager::LightCubeShader->setFloat("matirial.shininess", 60.0f);
                    

             

            glm::vec3 viewPos;

            glm::vec3 lightPos(0.0f, 1.0f, 1.0f);
           
            //glm::vec3 lightColor(amb_light[0], amb_light[1], amb_light[2]);

            angel += (float)deltaTime * 50.0f;
            lightPos.x = 4.0f * sinf(glm::radians(angel));

            // ################################## End lighting #############################



            // ###################################### Camera Control ########################################

            glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.2f, 100.0f);
            glm::mat4 view = camera.GetViewMatrix();

            ShaderManager::LightCubeShader->setMat4("projection", projection);
            ShaderManager::LightCubeShader->setMat4("view", view);
            glm::mat4 model = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            ShaderManager::LightCubeShader->setMat4("model", model);

            MainScreen::Instance()->ClearScreen();

            
            //             ################### draw all obj Model mesh ###################

            ShaderManager::LightCubeShader->Use();
            for (size_t i = 0; i < models.size(); ++i)  // Robot and Floor
            
            {
                //model = glm::translate(glm::mat4(1.0f), modPos[i]) * glm::scale(glm::mat4(1.0f), modScale[i]);
                //glm::mat4 model = glm::translate(glm::mat4(1.0f), modelPositions[i]) * glm::scale(glm::mat4(1.0f), modelScales[i]);
                model = glm::translate(glm::mat4(1.0f), modelPositions[i]) * glm::scale(glm::mat4(1.0f), modelScales[i]);
                ShaderManager::LightCubeShader->setMat4("model", model);
                //glBindTexture(GL_TEXTURE_2D, M_texture[i]);
                glBindTexture(GL_TEXTURE_2D, textures[i]);

                // Debugging: check if the texture and model are correctly bound
                //std::cout << "Drawing model at index " << i << " with texture ID " << textures[i] << std::endl;
               // M_mesh[i].objDraw();
                models[i].objDraw();
                //glBindTexture(M_texture[i], 0);
               // glBindTexture(GL_TEXTURE_2D, 0);
                glBindVertexArray(0);
                glBindBuffer(GL_ARRAY_BUFFER, 0);
                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
                glBindTexture(GL_TEXTURE_2D, 0);

            }
            // ######################################### END Obj model Rendering #######################################

            //###################################### Render Start up Objects ###############################   
            if (addStartUpObject) {
                cubeIndex = myGameObject.size();

                gameObject startUp;
                startUp.position = glm::vec3(0.0f, 0.0f, 0.0f); // Default position 
                startUp.scale = glm::vec3(1.0f, 1.0f, 1.0f); // Default scale

                // Initialize model matrix
                startUp.model = glm::mat4(1.0f);
                startUp.model = glm::translate(startUp.model, startUp.position);
                startUp.model = glm::scale(startUp.model, startUp.scale);
                // default cube texture
                startUp.textureID = loadTexture("Textures/default.jpg");
                // Add the new cube to the vector or a object obj or light, Texture
                myGameObject.push_back(startUp);

                LightObject lightStartUp;
                myLightObject.push_back(lightStartUp);

                addStartUpObject = false;

            }
            //###################################### End Start up Objects ###############################   

            ShaderManager::LightCubeShader->Use();
            ShaderManager::LightCubeShader->setMat4("view", view);
            ShaderManager::LightCubeShader->setMat4("projection", projection);
            ShaderManager::LightCubeShader->setVec3("viewPos", viewPos);
            ShaderManager::LightCubeShader->setVec3("lightColor", lightColor);
            ShaderManager::LightCubeShader->setVec3("lightPos", lightPos);
            ShaderManager::LightCubeShader->setFloat("ambientFactor", ambientFactor);

                                  
            
            // ################################ Draw light obj ###############################
           /* model = glm::translate(model = glm::mat4(1.0f), lightPos);
            model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
            ShaderManager::LightBulbShader->Use();
           
            ShaderManager::LightBulbShader->setVec3("lightColor", amb_light[0], amb_light[1], amb_light[2]);
            ShaderManager::LightBulbShader->setMat4("model", model);
            ShaderManager::LightBulbShader->setMat4("view", view);
            ShaderManager::LightBulbShader->setMat4("projection", projection);
           
            lightMesh.objDraw();*/
                      

                // ############################### Add a Light OBJ model with a button ##########   
                if (shouldAddLight) {
                    
                    lightIndex = myLightObject.size();

                    LightObject newLight;
                    
                                            
                    switch (lightIndex) {
                    case 0:
                        // add light = 1
                        newLight.position = glm::vec3(1.0f, 2.0f, 1.0f);
                        newLight.scale = glm::vec3(0.5f, 0.5f, 0.5f);

                        std::cout << "Drawing light at position: " << glm::to_string(newLight.position) << std::endl;
                        std::cout << "Drawing light with scale of: " << glm::to_string(newLight.scale) << std::endl;

                        break;
                    case 1:
                        // add light = 2
                        newLight.position = glm::vec3(1.5f, 3.0f, 1.0f);
                        newLight.scale = glm::vec3(1.5f, 1.5f, 1.5f);
                        std::cout << "Drawing light at position: " << glm::to_string(newLight.position) << std::endl;
                        std::cout << "Drawing light with scale of: " << glm::to_string(newLight.scale) << std::endl;
                        break;

                    default:
                        newLight.position = glm::vec3(posx, 4.0f, 1.0f);
                        newLight.scale = glm::vec3(1.5f, 1.5f, 1.5f);
                        std::cout << "Drawing light at position: " << glm::to_string(newLight.position) << std::endl;
                        std::cout << "Drawing light with scale of: " << glm::to_string(newLight.scale) << std::endl;
                        posx += 1.5;
                        break;
                    }
                    newLight.model = glm::mat4(1.0f);
                    newLight.model = glm::translate(newLight.model, newLight.position);
                    newLight.model = glm::scale(newLight.model, newLight.scale);

                    //myGameObject.push_back(newLight); // push the light in to the vector
                    myLightObject.push_back(newLight); // push the light in to the Lights vector
                   
                    std::cout << "Light Index " << lightIndex << std::endl;

                    shouldAddLight = false;

                }

                /*
                model = glm::translate(model, light.position);
                model = glm::scale(model, light.scale); 
                */
                    //for (auto& light : myGameObject) {
                    for (const auto& light : myLightObject) {
                        //glm::mat4 model = glm::translate(glm::mat4(1.0f), lightPos);
                        glm::mat4 model = glm::translate(glm::mat4(1.0f), light.position); // new
                        //model = glm::scale(model, glm::vec3(0.5f, 0.5f, 0.5f));
                        model = glm::scale(model, glm::vec3(light.scale));  // new
                        //model = glm::translate(model, light.position);
                        //model = glm::scale(model, light.scale);
                        ShaderManager::LightBulbShader->Use();
                        ShaderManager::LightBulbShader->setVec3("lightColor", amb_light[0], amb_light[1], amb_light[2]);
                        ShaderManager::LightBulbShader->setMat4("model", model);
                        ShaderManager::LightBulbShader->setMat4("view", view);
                        ShaderManager::LightBulbShader->setMat4("projection", projection);
                       
                        //std::cout << "Drawing light at position: " << glm::to_string(light.position) << std::endl;
                        lightMesh.objDraw(); //Just draws one the light?

                       

                    }

                    //std::this_thread::sleep_for(std::chrono::milliseconds(200));
                                                    
                    
                                  
                   
                //###################################### Render A New cubes on button click ###############################                    

                if (shouldAddCube) {
                    cubeIndex = myGameObject.size(); // Use the size of the vector to determine the next index

                    gameObject newCube; // Assuming Cube is a struct or class with position, scale, model and textureID members

                    // Set position and scale based on cubeIndex
                    switch (cubeIndex) {
                    case 0:
                        newCube.position = glm::vec3(0.0f, 0.5f, -3.0f); // Default position
                        newCube.scale = glm::vec3(1.0f, 1.0f, 1.0f);  // Default scale
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

                        newCube.position = glm::vec3(posx, 0.0f, -2.0f); // Default position for any additional cubes
                        newCube.scale = glm::vec3(1.0f, 1.0f, 1.0f); // Default scale
                        posx += 1.5;
                        break;
                    }
                    // Initialize model matrix
                    newCube.model = glm::mat4(1.0f);
                    newCube.model = glm::translate(newCube.model, newCube.position);
                    newCube.model = glm::scale(newCube.model, newCube.scale);

                    newCube.textureID = loadTexture("Textures/default.jpg");
                    // Add the new cube to the vector or a object obj or light, Texture
                    myGameObject.push_back(newCube);

                    shouldAddCube = false;
                    std::cout << "Cube Index " << cubeIndex << std::endl;
                }
                // Update positions and models for all cubes ## redundent code
                //for (auto& cube : myGameObject) {

                //    cube.model = glm::mat4(1.0f); // Reset to identity matrix
                //    cube.model = glm::translate(cube.model, cube.position); // Apply new translation
                //    cube.model = glm::scale(cube.model, cube.scale);
                //}
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

                if (shouldDeleteObject) { // ### NOT WORKING ###
                    if (objectUpdateIndex != -1) { // Check if a valid index is set
                        deleteCube(objectUpdateIndex);
                        objectUpdateIndex = -1; // Reset the index
                        shouldDeleteObject = false; // Reset the flag
                    }
                }
               
                // Render all cubes
                for (auto& cube : myGameObject) {
                    ShaderManager::LightCubeShader->Use();
                    ShaderManager::LightCubeShader->setMat4("projection", projection);
                    ShaderManager::LightCubeShader->setMat4("view", view);
                    ShaderManager::LightCubeShader->setMat4("model", cube.model);

                    glActiveTexture(GL_TEXTURE0);

                    glBindTexture(GL_TEXTURE_2D, cube.textureID);// so we know which cube has which texture
                    //std::cout << "Rendering cube with texture ID: " << cube.textureID << std::endl;
                    defaultCube::Instance()->draw();
                    glBindTexture(GL_TEXTURE_2D, 0);
                }

                //######################### End Draw new cube on button click #############################

                 //###################################### Grid Start ###############################
                 
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
                MainScreen::Instance()->RenderImGui(windowManager.GetWindow()); // Put them in this order this one last

                glfwSwapBuffers(windowManager.GetWindow());
                glfwPollEvents();

        }
            // close it all down and go to bed.
            glDeleteTextures(1, &skyTextureID);
            glDeleteVertexArrays(1, &skyVAO);
            glDeleteBuffers(1, &skyVBO);

            // it includes the Imgui stuff
            MainScreen::Instance()->ShutDown();


            return 0;
    }

    
    
