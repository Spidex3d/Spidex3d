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


bool gridNogrid = false;   // Show the grid or hide it

// #########################################  Cubes ########################################
struct Cube1 {
    glm::vec3 position;
    glm::mat4 model;
    glm::vec3 scale;
    unsigned int textureID;  
};

int objectUpdateIndex = -1;

bool shouldUpdateObject = false; // cube
bool shouldDeleteObject = false; // cube

//GLuint myNewTexture;
extern GLuint myTexture = 0;  // cube texture
extern unsigned int crateMap = 0;


bool rotateCube = false;     // rotate a cube 
bool shouldAddCube = false; // Add a cube with a button click
std::vector<Cube1> mycubes; // Add a cube with a button click

// #########################################  Lighting ########################################
float ambient_factor[1] = { 0.1f };
float amb_light[4] = {
    1.0f, 1.0f, 1.0f, 1.0f
};
float move_light[3] = {
    0.0f, 1.0f, 6.0f
};

struct LightData {
    std::string name;
    int LightId;
    int LightType; // Sun, Ambient, Spot
};

std::vector<LightData> myLights;
int LightId = 1;
int LightTypeID = 0;
LightData* selectedLightData = nullptr;
bool shouldAddLight = false;

// LightData* selectedLightData = nullptr;
// #########################################  End Lighting ########################################
// 
// #########################################  Camera       ########################################

    struct Camera1 {
        std::string name;
        int camId;
    };
    Camera1* selectedCamData = nullptr;
// #########################################  End Camera start Terrain ########################################

    struct Terrain {
        std::string name;
        int terrainId;
    };
// #########################################  End Terrain start Sky  ########################################
    bool addSky = false;
    struct SkyBox {
        std::string name;
    };
// #########################################  End Sky start Data1  ########################################

    struct Data1 {
        int index;
        std::string value;
        int objectIdx;
        int ObjectTypeID;       

    };
    
    Data1* selectedData = nullptr;
// #########################################  End Data1  ########################################

   
   

    namespace fs = std::filesystem;

    class EntityNode {
    public:
        static EntityNode* Instance() {
            static EntityNode* component = new EntityNode;

            return component;
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
        void renderObjectEditor(Data1* selectedData, bool& showObjectEditor) {
            ImGui::Begin("Object Editor", &showObjectEditor);

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
                        objectUpdateIndex = selectedData->objectIdx; // just added
                        if (objectUpdateIndex != -1) {
                            std::cout << "Updating texture for cube index: " << objectUpdateIndex << std::endl;
                            mycubes[objectUpdateIndex].textureID = loadTexture(myTexturePath);
                            std::cout << "New texture ID: " << mycubes[objectUpdateIndex].textureID << std::endl;
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
                    ImGui::Image((void*)(intptr_t)crateMap, ImVec2(65, 65));
                    //ImGui::Image((void*)(intptr_t)myTexture, ImVec2(65, 65));
                    
                }
                else {
                    ImGui::Text("No texture loaded.");
                }

                if (ImGui::Button("Update Object")) {
                    selectedData->value = nameBuffer;
                    shouldUpdateObject = true;
                    objectUpdateIndex = selectedData->objectIdx; // Ensure this is set correctly
                    std::cout << "Object update index set to: " << objectUpdateIndex << std::endl;
                    showObjectEditor = false;
                }
            }
            else {
                ImGui::Text("No object selected.");
            }

            ImGui::End();
        }

        void cloneSelectedItem(std::vector<Data1>& myVector, Data1* selectedData, int& currentIndex) {
            if (selectedData) {
                Data1 clonedItem = *selectedData;
                clonedItem.index = currentIndex++;
                myVector.push_back(clonedItem);
            }
        }
        void deleteObject(std::vector<Data1>& myVector, Data1* selectedData, int& currentIndex, int& indexCube,
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


        void renderUI(std::vector<Data1>& myVector, int& currentIndex,
            int& indexCube, int& indexPlane, int& indexSphere, int ObjectTypeID) {
            
            // ICON_FA_DICE_D6
            ImGui::Begin(ICON_FA_OBJECT_GROUP" Dynamic Spidex Object Management system");
            ImGui::Checkbox("Rotate Cube", &rotateCube); // make the cube rotate

            if (ImGui::Button("Add Cube    ")) {
                //ObjectTypeID = 6;
                
                myVector.push_back({ currentIndex++, ICON_FA_CUBE" DefaultCube_", indexCube++, ObjectTypeID });
                
                shouldAddCube = true;
            }
            
            if (ImGui::Button("Add Plane   ")) {
                ObjectTypeID = 7;
                myVector.push_back({ currentIndex++, "DefaultPlane_", indexPlane++, ObjectTypeID });
            }
            
            if (ImGui::Button("Add Sphere ")) {
                ObjectTypeID = 8;
                myVector.push_back({ currentIndex++, "DefaultSphere_", indexSphere++, ObjectTypeID });
            }

            ImGui::SeparatorText(ICON_FA_SPIDER" Scene Tree");

            auto flags = ROOT_SELECTED_FLAGS;
            if (ImGui::TreeNodeEx(ICON_FA_STREET_VIEW" Spidex Scean", flags))
            {
                
                /*if (is_selected)
                    node_flags |= ImGuiTreeNodeFlags_Selected;*/

            for (auto& data : myVector) {
               ImGuiTreeNodeFlags nodeFlags = flags | (selectedData == &data ? ImGuiTreeNodeFlags_Selected : 0);
                 bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)data.index, nodeFlags,
                    " Object: %d : %s %d  ",
                    data.index, data.value.c_str(), data.objectIdx);

                 if (ImGui::IsItemClicked()) {
                     selectedData = &data;
                     //objectUpdateIndex = data.objectIdx;
                     //objectUpdateIndex = selectedData->objectIdx;
                    // cubeIndex = data.objectIdx; // get the index of the cube selected
                     //shouldMoveCube = true; // set the move cube
                     //cubeIndexTM = data.objectIdx; // The index of the cube you want to move
                     //std::cout << " you did it " << data.objectIdx << std::endl;
                 }

                if (nodeOpen) {
                    this->onRightClick();
                    
                    if (ImGui::IsItemHovered()) {
                        
                       // this->nodeButtons();
                        // Perform actions when the node is hovered
                        ImGui::SetTooltip("Right click to Edit %s", data.value.c_str());
                    }

                    if (ImGui::BeginPopup("NodePopup")) {
                        ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_EDIT "  Entity");
                        ImGui::Separator();

                        if (ImGui::Selectable(ICON_FA_PEN_ALT " Edit")) {
                            selectedData = &data;
                            strncpy_s(nameBuffer, data.value.c_str(), sizeof(nameBuffer));
                            nameBuffer[sizeof(nameBuffer) - 1] = '\0'; // ensure null-termination
                            this->showObjectEditor = true;
                        }

                        if (ImGui::Selectable(ICON_FA_PLUS " New")) {
                            // Not sure yet
                        }
                        if (ImGui::Selectable(ICON_FA_COPY " Clone")) {
                            // clone current object
                            cloneSelectedItem(myVector, selectedData, currentIndex);
                        }

                        if (ImGui::Selectable(ICON_FA_TRASH_ALT " Delete")) {
                            selectedData = &data;
                            deleteObject(myVector, selectedData, currentIndex, indexCube, indexPlane, indexSphere);
                            objectUpdateIndex = data.objectIdx; // The index of the cube you want to Delete

                            shouldDeleteObject = true;
                        }

                        ImGui::EndPopup();
                    }

                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
            }

            if (showObjectEditor) {
                renderObjectEditor(selectedData, showObjectEditor); // Render the name editor window
            }

            ImGui::End();
        }
        // ######################################### Camera #####################################
        void renderCameraUI(std::vector<Camera1>& myCamera, std::string &name, int &camId)
        {

            ImGui::Begin(ICON_FA_VIDEO" Camera");
            // cameras types perspective, top down left, right, first person ie; player

            if (!cameraAdded) { // Default Camera
                camId = 1;
                myCamera.push_back({ name, camId }); // EntityID = 4
                cameraAdded = true;
            }
            auto flags = ROOT_SELECTED_FLAGS;
            if (ImGui::TreeNodeEx(ICON_FA_STREET_VIEW" Spidex Camera", flags))
            {

                /*if (is_selected)
                    node_flags |= ImGuiTreeNodeFlags_Selected;*/

                for (auto& data : myCamera) {
                    ImGuiTreeNodeFlags nodeFlags = flags | (selectedCamData == &data ? ImGuiTreeNodeFlags_Selected : 0);
                    bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)data.camId, nodeFlags,
                        " Camera: %s : %d ",
                        data.name.c_str(), data.camId);

                    if (ImGui::IsItemClicked()) {
                        selectedCamData = &data;
                        //objectUpdateIndex = data.objectIdx;
                        //objectUpdateIndex = selectedData->objectIdx;
                       // cubeIndex = data.objectIdx; // get the index of the cube selected
                        //shouldMoveCube = true; // set the move cube
                        //cubeIndexTM = data.objectIdx; // The index of the cube you want to move
                        //std::cout << " you did it " << data.objectIdx << std::endl;
                    }
                    ImGui::TreePop();
                    
                }
                ImGui::TreePop();
            }

            ImGui::End();
        }

        // ###### Properties Window
        void renderPropertiesPanel()
        //void renderPropertiesPanel(std::vector<Data1>& myVector, Data1* selectedData, int& currentIndex)
        {
            
            
            // To Replace demo window
            // 4 Tabs Properties, Textures Lab, Terraine Lab, Sky Lab
            ImGui::Begin(ICON_FA_CUBES" Properties", nullptr);

            if (ImGui::BeginTabBar("##Main", ImGuiTabBarFlags_None))
            {
                if (ImGui::BeginTabItem("Property Lab"))
                {
                    if (selectedData) {
                        ImGui::InputText("Selected Value", selectedData->value.data(), selectedData->value.size());
                    }
                    else {
                        ImGui::Text("No data selected");
                    }

                    ImGui::Text("ID: Textures");
                    ImGui::Text("Spidex Engine Textures", nullptr);
                     /*ImGui::Text("pointer = %x", texture_image_id);
                     ImGui::Text("Size = %d x %d", tex_image_width, tex_image_height);*/

                    ImGui::Spacing();
                    // ################################# File ###########################

                   /* Utility::Instance()->getDirectoryFiles();
                    Utility::Instance()->Initialize();*/


                    // ################################# End File ###########################

                   // I need to loop thought all images in the texture folder
                      //int ret = LoadTextureFiles("Textures/github.jpg", &texture_image_id, tex_image_width, tex_image_height);

                    // ######################## Show the texture

                      //ImVec2 pos = ImGui::GetCursorScreenPos();

                      //ImGui::GetWindowDrawList()->AddImage((void*)texture_image_id, ImVec2(pos.x, pos.y),
                      //ImVec2(pos.x + 100, pos.y + 100), ImVec2(0, 1), ImVec2(1, 0));

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

                            bool test = true;

                            ImGui::TableNextColumn();
                            ImGui::TextUnformatted("Object Name");
                            ImGui::TableNextColumn();
                            // this displays the info from the Node list for editing
                            if (selectedData) {
                                ImGui::InputText("##Selected Value", selectedData->value.data(), selectedData->value.size());
                            }
                            else {
                                ImGui::Text("No data selected");
                            }
                        
                        

                        ImGui::SameLine();

                        ImGui::TableNextRow();
                        ImGui::TableNextColumn();
                        ImGui::TextUnformatted("Hide Object");
                        ImGui::TableNextColumn();

                        if (ImGui::Checkbox("##test", &test)) {
                            // do somthing
                        }

                        ImGui::EndTable();
                        
                }
                    // ICON_FA_SPINNER
                    if (ImGui::CollapsingHeader(ICON_FA_STREET_VIEW" Transform", ImGuiTreeNodeFlags_DefaultOpen))
                    {
                        ImGui::BeginTable("Test Table", 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders);

                        ImGui::TableNextColumn();
                        ImGui::Text("Position:  ");
                        ImGui::SameLine();
                        if (ImGui::Button("Reset")) {
                            pos_val[0] = 0.0f, pos_val[1] = 0.0f, pos_val[2] = 2.0f;
                        }// Reset to 0,0,0
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
                        }// 1,1,1
                        ImGui::SameLine();
                        ImGui::DragFloat3("##Scale", scale_val, 1.0f, 1.0f, 1.0f);

                        //ImGui::Selectable(label, &selected);

                        ImGui::EndTable();

                    }
                    ImGui::Checkbox("Hide Grid", &gridNogrid); // make the cube rotate

                    ImGui::EndChild();

                    ImGui::EndTabItem();


                }
                if (ImGui::BeginTabItem("Sky Lab"))
                {
                    /*std::string path = "Textures/skybox";

                    std::vector<std::string> directories = getDirectories(path);

                    std::cout << "Directories in " << path << ":\n";
                    for (const auto& dir : directories) {
                        std::cout << dir << std::endl;
                    }*/



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
                    /*for (int i = 0; i < 3; ++i) {
                        ImGui::SetCursorPosX((ImGui::GetColumnWidth() - 135) * 0.5f + ImGui::GetColumnOffset());
                        if (ImGui::ImageButton((void*)(intptr_t)crateMap, ImVec2(135, 135))) {
                            addSky = true;
                        }
                        ImGui::NextColumn();
                    }*/
                    
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
                //   ####################################### Lighting Lab #################################
               

                    if (ImGui::BeginTabItem("Lighting Lab"))
                    {
                  
                       
                        ImGui::Text("ID: Light Lab");
                        ImGui::Text("Spidex Engine New Light Lab", nullptr);

                        if (ImGui::Button("Add Light"))
                        {
                            myLights.push_back({ " Default_Light", LightId++, LightTypeID });
                            shouldAddLight = true;
                        }

                        ImGui::SeparatorText(ICON_FA_SPIDER" Lights in Scean");

                        auto flags = ROOT_SELECTED_FLAGS;
                        if (ImGui::TreeNodeEx(ICON_FA_STREET_VIEW" Spidex Lights", flags))
                        {

                            static bool align_label_with_current_x_position = false;
                            static bool test_drag_and_drop = false;

                            if (align_label_with_current_x_position)
                                ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

                            static int selection_mask = (1 << 2);
                            int node_clicked = -1;

                            for (auto& data : myLights) {
                                ImGuiTreeNodeFlags nodeFlags = flags | (selectedLightData == &data ? ImGuiTreeNodeFlags_Selected : 0);
                                bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)data.LightId, nodeFlags,
                                    " Lights: %s : %d : %d ",
                                    data.name.c_str(), data.LightId, data.LightType);

                                if (ImGui::IsItemClicked()) {
                                    selectedLightData = &data;
                                    // Handle selection logic here
                                }

                                if (nodeOpen) {
                                    this->onRightClick();

                                    if (ImGui::IsItemHovered()) {

                                        // this->nodeButtons();
                                         // Perform actions when the node is hovered
                                        ImGui::SetTooltip("Right click to Edit %s", data.name.c_str());
                                    }

                                    if (ImGui::BeginPopup("NodePopup")) {
                                        ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_EDIT "  Entity");
                                        ImGui::Separator();

                                        if (ImGui::Selectable(ICON_FA_PEN_ALT " Edit")) {
                                            //selectedData = &data;
                                            strncpy_s(nameBuffer, data.name.c_str(), sizeof(nameBuffer));
                                            nameBuffer[sizeof(nameBuffer) - 1] = '\0'; // ensure null-termination
                                            //this->showObjectEditor = true;
                                        }

                                        if (ImGui::Selectable(ICON_FA_PLUS " New")) {
                                            // Not sure yet
                                        }
                                        

                                        if (ImGui::Selectable(ICON_FA_TRASH_ALT " Delete")) {
                                            //selectedData = &data;
                                            //deleteObject(myVector, selectedData, currentIndex, indexCube, indexPlane, indexSphere);
                                            //objectUpdateIndex = data.objectIdx; // The index of the cube you want to Delete

                                            //shouldDeleteObject = true;
                                        }

                                        ImGui::EndPopup();
                                    }

                                    ImGui::TreePop();
                                    //ImGui::TreePop();
                                }
                            }

                            ImGui::TreePop();
                        }
                        ImGui::SeparatorText(ICON_FA_SPIDER" Light Settings");
                        ImGui::Text("Change Ambient Factor");
                        ImGui::DragFloat("Ambient", ambient_factor, 0.0f);
                        ImGui::Text("Light Position");
                        ImGui::DragFloat3("Position", move_light, 0.0f, 1.0f, 6.0f);
                       // ImGui::DragFloat3("Position", lighPos, 0.5f, 1.0f, 5.0f);
                       // ImGui::DragFloat3("Position", lighPos, 0.5f, 1.0f, 5.0f);



                        ImGui::Text("Change light color"); 
                        ImGui::ColorEdit4("Color", amb_light); // change the Light colour

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
            }

            ImGui::End();
        }
       

    private:
       // Data1* selectedData = nullptr;      

        bool showObjectEditor = false; // for editing the cubes
        bool cameraAdded = false;
        Camera1 defaultCamera = { ICON_FA_VIDEO " MainCamera ", 0 };// maincamera with id 0       

        char nameBuffer[128] = ""; // for renaming the cubes
      
       

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

    