#pragma once
#include "../Header/Configs.h"
#include "../Header/Buttons.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <commdlg.h>
#include <filesystem>
#include <locale>
#include <codecvt>
#include <vector>
#include <algorithm>

#include "../Windows/spxWindows.h"
#include "../Header/Textures.h"
#include "../SkyBox/skyBox.h"
#include "../Objects/spxObjLoader.h"

// ################################ This is my Entity Manager Sytem ####################################

bool gridNogrid = false;   // Show the grid or hide it

// #########################################  New Game Objects  ########################################


int objectUpdateIndex = -1;

bool shouldUpdateObject = false; // Object
bool shouldDeleteObject = false; // Object

//GLuint myNewTexture;
extern GLuint myTexture = 0;  // cube texture
extern unsigned int crateMap = 0;

int cubeIndex = 0; // ??????? This needs looking at ????????

float pos_val[3] = { 0.0f, 0.0f, 2.0f };
float rot_val[3] = { 0.3f, 0.3f, 0.3f };
float scale_val[3] = { 1.0f, 1.0f, 1.0f };



bool rotateCube = false;     // rotate a cube 
bool shouldAddCube = false; // Add a cube with a button click
bool addStartUpObject = true; // add the start up objects

struct gameObject { // this was cube1
    glm::vec3 position;
    glm::mat4 model;
    glm::vec3 scale;
    unsigned int textureID;
};

std::vector<gameObject> myGameObject; // Add a Object to the main VECTOR ##############

struct GameData { // change from Data1, This is now the main Data for all objects
    int index;  
    std::string objectName; 
    int objectIndex;
    int ObjectTypeID;

};

GameData* selectedData = nullptr;


// #########################################  Lighting ########################################

float ambient_factor[1] = { 0.1f };
float amb_light[4] = {
    1.0f, 1.0f, 1.0f, 1.0f
};
float move_light[3] = {
    0.0f, 1.0f, 6.0f
};
float lightPos[3] = {
    0.0f, 1.0f, 1.0f
};

struct LightObject { // this the new light vector
    glm::vec3 position;
    glm::mat4 model;
    glm::vec3 scale;

};

std::vector<LightObject> myLightObject; // Add a Light to the main VECTOR ##############


struct LightData { // change from Data1, This is now the main Data for all objects
    int index;
    //std::string objectName;
    std::string LightName;
    //int objectIndex;
    int LightIndex;
    //int ObjectTypeID;
    int LightTypeID;

};

int lightIndex = 0; // this is the index of how many lights we have

bool lightGUIShow = false; // this shows the ;ight control panel

bool shouldAddLight = false; // this is to add a new light on button click


// #########################################  End Lighting ########################################

    struct Terrain {
        std::string name;
        int terrainId;
    };
// #########################################  End Terrain start Sky  ########################################
    bool addSky = false;
    struct SkyBox {
        std::string name;
    };
// #########################################  End Sky start GameData  ########################################

   
// #########################################  End GameData Start of Obj Model loading  ########################################
    // Store loaded models and textures

    const int numInitialModels = 2;
    std::vector<spxObjLoader> models;
    std::vector<unsigned int> textures;
    std::vector<glm::vec3> modelPositions;
    std::vector<glm::vec3> modelScales;

    glm::vec3 initialModPos[] = {
         glm::vec3(0.0f, -0.7f, 0.0f), // floor
         glm::vec3(-3.0f, -0.5f, -3.0f)  // robot
         //glm::vec3(3.0f, -0.5f, 2.0f)  // bowling pin     
         //glm::vec3(-4.5f, 0.0f, 1.0f) // wooden crate
         //glm::vec3(-7.0f, -0.5f, 2.0f), // bunny

    };
    glm::vec3 initialModScale[] = {
        glm::vec3(100.0f, 0.2f, 100.0f), // floor
        glm::vec3(0.5f, 0.5f, 0.5f) // robot
        //glm::vec3(0.1f, 0.1f, 0.1f)  // bowling pin   
        //glm::vec3(1.0f, 1.0f, 1.0f) // wooden crate
        //glm::vec3(0.7f, 0.7f, 0.7f), // bunny

    };

// #########################################  End of Obj Model loading  ########################################

    namespace fs = std::filesystem;

    class EntityNode {
    public:
        static EntityNode* Instance() {
            static EntityNode* component = new EntityNode;

            return component;
        }
        // get the path for obj textures
        std::string getTexturePath(const std::string& modelPath) {
            std::string texturePath = modelPath;
            size_t lastDot = texturePath.find_last_of('.');
            if (lastDot != std::string::npos) {
                texturePath.replace(lastDot, texturePath.length() - lastDot, ".jpg");
            }
            return texturePath;
        }

        // get the sky folders
        std::vector<std::string> getDirectories(const std::string& path) {
            std::vector<std::string> directories;
            for (const auto& entry : fs::directory_iterator(path)) {
                if (entry.is_directory()) {
                    directories.push_back(entry.path().filename().string());
                }
            }
            return directories;
        }


        // chang this name renderObjectEditor  renderNameEditor
        void renderObjectEditor(GameData* selectedData, bool& showObjectEditor) {
            ImGui::Begin("Mesh Object Editor", &showObjectEditor);

            if (selectedData) {
                ImGui::InputText("Object Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));

                ImGui::BeginTable("Test Table", 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders);

                ImGui::TableNextColumn();
                ImGui::Text("Position:  ");
                ImGui::SameLine();
                if (ImGui::Button("Reset")) {
                    pos_val[0] = 0.0f, pos_val[1] = 0.0f, pos_val[2] = 2.0f;
                }
                ImGui::SameLine();
                ImGui::DragFloat3("##pos", pos_val, 1.0f, 1.0f, 2.0f);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Rotation:  ");
                ImGui::SameLine();
                if (ImGui::Button("Reset")) {
                    rot_val[0] = 0.0f, rot_val[1] = 0.0f, rot_val[2] = 0.0f;
                }
                ImGui::SameLine();
                ImGui::DragFloat3("##Rot", rot_val, 1.0f, 1.0f, 1.0f);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                ImGui::Text("Scale:       ");
                ImGui::SameLine();
                if (ImGui::Button("SReset")) {
                    scale_val[0] = 1.0f, scale_val[1] = 1.0f, scale_val[2] = 1.0f;
                }
                ImGui::SameLine();
                ImGui::DragFloat3("##Scale", scale_val, 0.0f, 0.0f, 0.0f);

                ImGui::EndTable();

                if (ImGui::Button("Set New Texture")) {
                    std::string myTexturePath = openFileDialog();
                    if (!myTexturePath.empty()) {
                        std::cout << "Texture path selected: " << myTexturePath << std::endl;
                        objectUpdateIndex = selectedData->objectIndex; // just added
                        if (objectUpdateIndex != -1) {
                            std::cout << "Updating texture for cube index: " << objectUpdateIndex << std::endl;
                            myGameObject[objectUpdateIndex].textureID = loadTexture(myTexturePath);
                            std::cout << "New texture ID: " << myGameObject[objectUpdateIndex].textureID << std::endl;

                            crateMap = loadTexture((myTexturePath).c_str());

                        }
                        else {
                            std::cout << "objectUpdateIndex is not set correctly." << std::endl;
                        }
                    }
                    else {
                        std::cout << "No texture path selected." << std::endl;
                    }
                }


                if (crateMap != 0) {
                    ImGui::Text("Here is your texture:");

                    ImGui::Image((void*)(intptr_t)crateMap, ImVec2(65, 65)); // show image selected

                }
                else {
                    ImGui::Text("No texture loaded.");
                }

                if (ImGui::Button("Update Object")) {
                    selectedData->objectName = nameBuffer;
                    shouldUpdateObject = true;
                    objectUpdateIndex = selectedData->objectIndex; // Ensure this is set correctly
                    std::cout << "Object update index set to: " << objectUpdateIndex << std::endl;
                    showObjectEditor = false;
                }
            }
            else {
                ImGui::Text("No object selected.");
            }

            ImGui::End();
        }

        void renderLightEditor(GameData* selectedData, bool& showLightEditor) {
            ImGui::Begin("Lighting Editor", &showLightEditor);
            
            if (selectedData) {
                ImGui::InputText("Object Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));

            ImGui::SeparatorText(ICON_FA_SPIDER" Light Settings");
            ImGui::Text("Change Ambient Factor");
            ImGui::DragFloat("Ambient", ambient_factor, 0.0f);
            ImGui::Text("Light Position");
            ImGui::DragFloat3("Position", move_light, 0.0f, 1.0f, 6.0f);
            ImGui::Text("Change light color");
            ImGui::ColorEdit4("Color", amb_light);

                if (ImGui::Button("Update Light")) {
                    selectedData->objectName = nameBuffer;
                    //selectedData->currentlightIndex();
                    //objectUpdateIndex = selectedData->objectIndex; // Ensure this is set correctly
                    std::cout << "update Lighting : " << objectUpdateIndex << std::endl;
                    showLightEditor = false;
                }


            }
            ImGui::End();
        }
          // NOT Working correctly yet
            void cloneSelectedItem(std::vector<GameData>&myVector, GameData * selectedData, int& currentIndex) {
                if (selectedData) {
                    GameData clonedItem = *selectedData;
                    clonedItem.index = currentIndex++;
                    myVector.push_back(clonedItem);
                }
            }
            // NOT Working correctly yet
            void deleteObject(std::vector<GameData>&myVector, GameData * selectedData, int& currentIndex, int& indexCube,
                int& indexPlane, int& indexSphere) {
                // will need to see if the index is in the vector and not at the end           
                if (selectedData->index > 1 && selectedData->index < myVector.size()) {

                    myVector.erase(myVector.begin() + selectedData->index);

                }

                else if (selectedData->index == 0) {
                    std::cout << "You can't delete the Camera silly!!" << std::endl;
                }
                else if (selectedData->index == 1) {
                    std::cout << "You can't delete the Sun silly!!" << std::endl;
                }

            }


            void renderUI(std::vector<GameData>&myVector, int& currentIndex,
                int& indexCube, int& indexPlane, int& indexSphere, int& indexLight, int ObjectTypeID) {

                // ICON_FA_DICE_D6
                ImGui::Begin(ICON_FA_OBJECT_GROUP" Dynamic Spidex Object Management system");
                ImGui::Checkbox("Rotate Cube", &rotateCube); // make the cube rotate

                if (addStartUpObject) { // set up the startup Camera and and default cube, light
                    ObjectTypeID = OBJ_CAMERA;
                    myVector.push_back({ currentIndex++, ICON_FA_VIDEO" Main Camera", OBJ_CAMERA, ObjectTypeID });
                    ObjectTypeID = OBJ_CUBE;
                    myVector.push_back({ currentIndex++, ICON_FA_CUBE" DefaultCube_", indexCube++, OBJ_CUBE });
                    ObjectTypeID = OBJ_LIGHT_0;
                    myVector.push_back({ currentIndex++, ICON_FA_CUBE" DefaultLight_", indexLight++, OBJ_LIGHT_0 });
                    //myLightObject.push_back({ currentIndex++, ICON_FA_CUBE" DefaultLight_", indexLight++, OBJ_LIGHT_0 });

                }

                // The buttons to add game objects ect;
                if (ImGui::Button(ICON_FA_CUBE" Add Cube    ")) {
                    ObjectTypeID = OBJ_CUBE; // Cube

                    myVector.push_back({ currentIndex++, ICON_FA_CUBE" DefaultCube_", indexCube++, OBJ_CUBE });

                    shouldAddCube = true;
                }
                ImGui::SameLine();
                if (ImGui::Button(ICON_FA_LIGHTBULB " Add Light   ")) {
                    ObjectTypeID = OBJ_LIGHT_0; // Light
                    myVector.push_back({ currentIndex++, ICON_FA_LIGHTBULB" DefaultLight_", indexLight++, OBJ_LIGHT_0 });
                    
                    shouldAddLight = true;
                }

                if (ImGui::Button(ICON_FA_H_SQUARE " Add Plane   ")) {
                    ObjectTypeID = OBJ_PLANE; // Plane
                    myVector.push_back({ currentIndex++, "DefaultPlane_", indexPlane++, OBJ_PLANE });
                }

                if (ImGui::Button(ICON_FA_PLUS_CIRCLE" Add Sphere ")) {
                    ObjectTypeID = OBJ_SPHERE; // Sphere
                    myVector.push_back({ currentIndex++, "DefaultSphere_", indexSphere++, OBJ_SPHERE });
                }
                //                      ##################  Load an Obj file #################
                if (ImGui::Button(ICON_FA_ROBOT " Add OBJ File")) {
                    ObjectTypeID = OBJ_OBJ_MODEL; // obj files
                    std::string SPXModelPath = openFileDialog();
                    if (!SPXModelPath.empty()) {
                        std::cout << "Model path selected: " << SPXModelPath << std::endl;

                    //    spxObjLoader newModel;
                    //    newModel.loadOBJ(SPXModelPath);
                    //    models.push_back(newModel);

                    //    std::string texturePath = getTexturePath(SPXModelPath);
                    //    unsigned int newTexture = loadTexture(texturePath);
                    //    textures.push_back(newTexture);
                    //    std::cout << "Texture path selected: " << texturePath << std::endl;

                    //    modelPositions.push_back(glm::vec3(0.0f, 2.0f, 0.0f)); // Default position, adjust as needed
                    //    modelScales.push_back(glm::vec3(1.0f));    // Default Scale, adjust as needed

                    }
                    else
                    {
                        std::cout << "No File selected." << std::endl;
                    }
                    myVector.push_back({ currentIndex++, ICON_FA_ROBOT" Obj_Model_", indexSphere++, OBJ_OBJ_MODEL });
                }



                ImGui::SeparatorText(ICON_FA_SPIDER" Scene Colection");

                auto flags = ROOT_SELECTED_FLAGS; // in config
                if (ImGui::TreeNodeEx(ICON_FA_STREET_VIEW" Spidex Scean", flags))
                {


                    for (auto& data : myVector) {
                        ImGuiTreeNodeFlags nodeFlags = flags | (selectedData == &data ? ImGuiTreeNodeFlags_Selected : 0);
                        bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)data.index, nodeFlags,
                            " Object: %d : %s %d : Type ID : %d ",
                            data.index, data.objectName.c_str(), data.objectIndex, data.ObjectTypeID);

                        if (ImGui::IsItemClicked()) {
                            selectedData = &data;
                                                       

                            switch (data.ObjectTypeID) { // select which editor we need
                            case 0: // Main camera
                                lightGUIShow = false;
                                std::cout << " you selected the Camera " << data.ObjectTypeID << std::endl;
                                break;
                            case 1: // Default Global Light
                                lightGUIShow = true;
                                std::cout << " you selected the Light1 " << data.ObjectTypeID << std::endl;
                                break;
                            case 2: // Ambiant Light

                                std::cout << " you selected the Light2 " << data.ObjectTypeID << std::endl;
                                break;
                            case 3: // Point Light
                                std::cout << " you selected the Light3 " << data.ObjectTypeID << std::endl;
                                break;
                            case 4: // Cube
                                lightGUIShow = false;
                                std::cout << " you selected the Light3 " << data.ObjectTypeID << std::endl;
                               // this->showObjectEditor = true;
                                break;

                            default:
                                break;
                            }

                        }
                        // ################################## SAVE THIS FOR USE LATER USE ##################
                        if (nodeOpen) {
                             this->onRightClick();

                            if (ImGui::IsItemHovered()) {

                                // this->nodeButtons();
                                 // Perform actions when the node is hovered
                                ImGui::SetTooltip("Right click to Edit %s", data.objectName.c_str());
                            }

                            
                            if (ImGui::BeginPopup("NodePopup")) {
                                ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_EDIT "  Entity");
                                ImGui::Separator();

                                //if (ImGui::Selectable(ICON_FA_PEN_ALT " Edit")) {
                                //    selectedData = &data;
                                //    strncpy_s(nameBuffer, data.objectName.c_str(), sizeof(nameBuffer));
                                //    nameBuffer[sizeof(nameBuffer) - 1] = '\0'; // ensure null-termination

                                //    switch (data.ObjectTypeID) { // select which editor we need
                                //    case 0: // camera
                                //        std::cout << " you selected the Camera " << data.ObjectTypeID << std::endl;
                                //        break;
                                //    case 1: // Default Global Light
                                //        this->showLightEditor = true;
                                //        std::cout << " you selected the Light1 " << data.ObjectTypeID << std::endl;
                                //        break;
                                //    case 2: // Ambiant Light
                                //        
                                //        std::cout << " you selected the Light2 " << data.ObjectTypeID << std::endl;
                                //        break;
                                //    case 3: // Point Light
                                //        std::cout << " you selected the Light3 " << data.ObjectTypeID << std::endl;
                                //        break;
                                //    case 4: // Cube
                                //        this->showObjectEditor = true;
                                //        break;

                                //    default:
                                //        break;
                                //    }

                                //}

                                //if (ImGui::Selectable(ICON_FA_PLUS " New")) {
                                //    // Not sure yet
                                //}
                                if (ImGui::Selectable(ICON_FA_COPY " Clone")) {
                                    // clone current object
                                    cloneSelectedItem(myVector, selectedData, currentIndex);
                                }

                                if (ImGui::Selectable(ICON_FA_TRASH_ALT " Delete")) {
                                    selectedData = &data;
                                    deleteObject(myVector, selectedData, currentIndex, indexCube, indexPlane, indexSphere);
                                    objectUpdateIndex = data.objectIndex; // The index of the cube you want to Delete

                                    shouldDeleteObject = true;
                                }

                                ImGui::EndPopup();
                            }

                            ImGui::TreePop();
                        }
                    }
                    ImGui::TreePop();
                }

                //############################################### START ##############################################
                
                // ########################################## END ##############################################

                if (showObjectEditor) {
                    renderObjectEditor(selectedData, showObjectEditor); // Render the name editor window
                }
                if (showLightEditor) {
                    //renderLightEditor(selectedData, showLightEditor); // Render the light editor window
                    //lightGUIShow = true;
                }
               

                

                ImGui::End();
            }

            void renderProperties(std::vector<GameData>& myVector, int& currentIndex,
                int& indexCube, int& indexPlane, int& indexSphere, int& indexLight, int ObjectTypeID) { // new one

                ImGui::Begin(ICON_FA_CUBES" Properties");
                if (ImGui::BeginTabBar("##Main", ImGuiTabBarFlags_None))
                {
                                        
                    if (ImGui::BeginTabItem("Properties"))
                    {

                        ImGui::SeparatorText(ICON_FA_SPIDER" Settings");
                        if (selectedData) {
                          //ImGui::InputText("Object Name", selectedData->objectName.data(), selectedData->objectName.size());
                            ImGui::InputText("Object Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
                            //ImGui::InputText("Object Name", selectedData->objectName.data(), selectedData->objectName.size(), IM_ARRAYSIZE(nameBuffer));
                        }
                        else {
                            ImGui::Text("No data selected");
                        }

                            //only showe button if a valid index is selected
                        if (ImGui::Button("Update Object")) {
                            //only update if a valid index is selected
                            selectedData->objectName = nameBuffer;
                            shouldUpdateObject = true;
                            objectUpdateIndex = selectedData->objectIndex; // Ensure this is set correctly
                            std::cout << "Object update index set to: " << objectUpdateIndex << std::endl;
                            //showObjectEditor = false;
                        }

                        ImGui::Text("ID: Textures");
                        ImGui::Text("Spidex Engine Textures", nullptr);

                        ImGui::Spacing();

                        //#########################
                        ImGui::SeparatorText(ICON_FA_SPIDER" Settings");

                        ImGui::BeginChild("Chlid");
                        //################################################
                        // 
                       // ###################################################
                        static ImGuiTableFlags flags = ImGuiTableFlags_Reorderable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders;

                        static bool selected;


                        if (ImGui::CollapsingHeader(ICON_FA_INFO" Object info", ImGuiTreeNodeFlags_DefaultOpen))
                        {

                            ImGui::BeginTable("Test Table", 2, flags);

                            

                            ImGui::TableNextColumn();
                            ImGui::TextUnformatted("Object Name");
                            ImGui::TableNextColumn();
                            // this displays the info from the Node list for editing
                            if (selectedData) {
                                ImGui::InputText("##Selected objectName", selectedData->objectName.data(), selectedData->objectName.size());
                            }
                            else {
                                ImGui::Text("No data selected");
                            }



                            ImGui::SameLine();

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            ImGui::TextUnformatted("Hide Object");
                            ImGui::TableNextColumn();

                            if (ImGui::Checkbox("##test", &hideObject)) {
                                // do somthing
                            }

                            ImGui::EndTable();

                        }
                        // ICON_FA_SPINNER
                        if (ImGui::CollapsingHeader(ICON_FA_STREET_VIEW" Transform", ImGuiTreeNodeFlags_DefaultOpen))
                        {
                            ImGui::BeginTable("Test Table", 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders);

                            ImGui::TableNextColumn();
                            
                            ImGui::SameLine();
                            if (ImGui::Button("Reset")) {
                                pos_val[0] = 0.0f, pos_val[1] = 0.0f, pos_val[2] = 2.0f;
                            }
                            ImGui::SameLine();
                            
                            ImGui::DragFloat3("Position",pos_val, 1.0f, 1.0f, 2.0f);
                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                           
                            ImGui::SameLine();
                            if (ImGui::Button("Reset")) {
                                rot_val[0] = 0.0f, rot_val[1] = 0.0f, rot_val[2] = 0.0f;
                            }
                            ImGui::SameLine();
                            ImGui::DragFloat3("Rotation", rot_val, 1.0f, 1.0f, 1.0f);

                            ImGui::TableNextRow();
                            ImGui::TableNextColumn();
                            
                            ImGui::SameLine();
                            if (ImGui::Button("Reset")) {
                                scale_val[0] = 1.0f, scale_val[1] = 1.0f, scale_val[2] = 1.0f;
                            }// 1,1,1
                            ImGui::SameLine();
                            ImGui::DragFloat3("Scale", scale_val, 1.0f, 1.0f, 1.0f);

                            //ImGui::Selectable(label, &selected);

                            ImGui::EndTable();

                        }
                                                // ##### TEXTURE #####
                        if (ImGui::CollapsingHeader(ICON_FA_PHOTO_VIDEO" Texture", ImGuiTreeNodeFlags_DefaultOpen))
                        {
                            if (ImGui::Button("Set New Texture")) {
                                std::string myTexturePath = openFileDialog();
                                if (!myTexturePath.empty()) {
                                    std::cout << "Texture path selected: " << myTexturePath << std::endl;
                                    objectUpdateIndex = selectedData->objectIndex; // just added
                                    if (objectUpdateIndex != -1) {
                                        std::cout << "Updating texture for cube index: " << objectUpdateIndex << std::endl;
                                        myGameObject[objectUpdateIndex].textureID = loadTexture(myTexturePath);
                                        std::cout << "New texture ID: " << myGameObject[objectUpdateIndex].textureID << std::endl;

                                        crateMap = loadTexture((myTexturePath).c_str());

                                    }
                                    else {
                                        std::cout << "objectUpdateIndex is not set correctly." << std::endl;
                                    }
                                }
                                else {
                                    std::cout << "No texture path selected." << std::endl;
                                }
                            }
                            if (crateMap != 0) {
                                ImGui::Text("Here is your texture:");

                                ImGui::Image((void*)(intptr_t)crateMap, ImVec2(65, 65)); // show image selected

                            }
                            else {
                                ImGui::Text("No texture loaded.");
                            }
                            
                        }
                                            // ##### LIGHTING #####
                        if (lightGUIShow) { 
                            if (ImGui::CollapsingHeader(ICON_FA_LIGHTBULB" Lighting", ImGuiTreeNodeFlags_DefaultOpen))
                            {
                                
                                
                                ImGui::SeparatorText(ICON_FA_SPIDER" Light Settings");
                                ImGui::Text("Change Ambient Factor");
                                ImGui::DragFloat("Ambient", ambient_factor, 0.0f);
                                ImGui::Text("Light Position");
                                ImGui::DragFloat3("Position", lightPos, 0.0f, 0.0f, 0.0f);
                                ImGui::Text("Change light color");                         
                            
                                ImGui::ColorEdit4("Color", amb_light);

                                // we need to store any info enterd here
                            }
                            
                        }

                        if (ImGui::CollapsingHeader(ICON_FA_BARS" Grid", ImGuiTreeNodeFlags_DefaultOpen))
                        {
                            ImGui::Checkbox("Hide Grid", &gridNogrid); // make the cube rotate
                        }
                        ImGui::EndChild();

                        ImGui::EndTabItem();

                    }

                    if (ImGui::BeginTabItem("Sky Lab"))
                    {
                        ImGui::Text("ID: Sky Lab"); // ###################  Sky Lab ##############

                        // add a selection of skys to pick from maybe a folder or an image showing the type sky
                        ImGui::Columns(3);

                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset());// BlueSky
                        if (ImGui::ImageButton((void*)(intptr_t)texture1, ImVec2(135, 135))) {
                            // some sort of SkyID to set a different sky
                            selectedSkyboxIndex = 0;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            if (!addSky) {
                                addSky = true;
                            }
                        }

                        ImGui::NextColumn();
                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset()); // BlueSky_2
                        if (ImGui::ImageButton((void*)(intptr_t)texture2, ImVec2(135, 135))) {
                            selectedSkyboxIndex = 1;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            if (!addSky) {
                                addSky = true;
                            }
                        }
                        ImGui::NextColumn();
                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset()); // DarkSky
                        if (ImGui::ImageButton((void*)(intptr_t)texture3, ImVec2(135, 135))) {
                            selectedSkyboxIndex = 2;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            addSky = true;
                        }

                        ImGui::Columns(1); // Reset columns
                        ImGui::Separator(); // Optional: Add a separator line
                        ImGui::Columns(3); // Start new set of columns

                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset()); //RedSky
                        if (ImGui::ImageButton((void*)(intptr_t)texture4, ImVec2(135, 135))) {
                            // some sort of SkyID to set a different sky
                            selectedSkyboxIndex = 3;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            if (!addSky) {
                                addSky = true;
                            }
                        }

                        ImGui::NextColumn();
                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset()); //MistySky
                        if (ImGui::ImageButton((void*)(intptr_t)texture5, ImVec2(135, 135))) {
                            selectedSkyboxIndex = 4;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            if (!addSky) {
                                addSky = true;
                            }
                        }
                        ImGui::NextColumn();
                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset()); //MistyBlue
                        if (ImGui::ImageButton((void*)(intptr_t)texture6, ImVec2(135, 135))) {
                            selectedSkyboxIndex = 5;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            addSky = true;
                        }
                        ImGui::Columns(1); // Reset columns
                        ImGui::Separator(); // Optional: Add a separator line
                        ImGui::Columns(3); // Start new set of columns

                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset()); //GreenSky
                        if (ImGui::ImageButton((void*)(intptr_t)texture7, ImVec2(135, 135))) {
                            // some sort of SkyID to set a different sky
                            selectedSkyboxIndex = 6;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            if (!addSky) {
                                addSky = true;
                            }
                        }

                        ImGui::NextColumn();
                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset()); //NightSky
                        if (ImGui::ImageButton((void*)(intptr_t)texture8, ImVec2(135, 135))) {
                            selectedSkyboxIndex = 7;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            if (!addSky) {
                                addSky = true;
                            }
                        }
                        ImGui::NextColumn();
                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset()); //SifiSky
                        if (ImGui::ImageButton((void*)(intptr_t)texture9, ImVec2(135, 135))) {
                            selectedSkyboxIndex = 8;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            addSky = true;
                        }
                        
                        ImGui::EndColumns();

                        ImGui::Text("Spidex Engine New Sky Lab! well its a start", nullptr);

                        if (ImGui::Button("Add a Sky   ")) {
                            selectedSkyboxIndex = 2;
                            skyTextureID = LoadSkybox(skyboxSets[selectedSkyboxIndex]);
                            addSky = true;
                        }
                        ImGui::SameLine();
                        if (ImGui::Button("Remove a Sky")) {
                            addSky = false;
                        }
                        ImGui::EndTabItem();
                    }
                    if (ImGui::BeginTabItem("Particel Lab"))
                    {
                        ImGui::Text("ID: Particel Lab");
                        ImGui::Text("Spidex Engine New Particel Lab", nullptr);
                        ImGui::Button("Save");

                        ImGui::EndTabItem();

                    }
                    if (ImGui::BeginTabItem("Terraine Lab"))
                    {
                        ImGui::Text("ID: Terraine Lab");
                        ImGui::Text("Spidex Engine New Terrain Lab", nullptr);
                        ImGui::Button("Save");

                        ImGui::EndTabItem();

                    }

                    ImGui::EndTabBar();

                ImGui::Text("This all seemes to be working");

                }

                ImGui::End();
            }           
            
    private:   

        bool showObjectEditor = false; // for editing the cubes
        bool showLightEditor = false; // for editing lighting
        //bool cameraAdded = false;

        bool hideObject = false;    // not used yet 

        char nameBuffer[128] = ""; // for renaming the cubes
        
        bool isSelected = false; // flag to check if a node is selected

        void onRightClick() {
            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                ImGui::OpenPopup("NodePopup");
            }
        }

        int selectedSkyboxIndex = 0;

        GLuint texture1 = loadTexture("Textures/skybox/BlueSky/front.jpg");
        GLuint texture2 = loadTexture("Textures/skybox/BlueSky_2/front.jpg");
        GLuint texture3 = loadTexture("Textures/skybox/DarkSky/back.jpg");
        GLuint texture4 = loadTexture("Textures/skybox/RedSky/front.jpg");
        GLuint texture5 = loadTexture("Textures/skybox/MistySky/front.jpg");
        GLuint texture6 = loadTexture("Textures/skybox/MistyBlueSky/front.jpg");
        GLuint texture7 = loadTexture("Textures/skybox/GreenSky/front.jpg");
        GLuint texture8 = loadTexture("Textures/skybox/NightSky/front.jpg");
        GLuint texture9 = loadTexture("Textures/skybox/SifiSky/front.jpg");


    };

    