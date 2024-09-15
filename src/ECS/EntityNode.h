#pragma once
#include "../Header/Configs.h"
#include "../Header/Buttons.h"
#include <iostream>
#include <string>
#include <Windows.h>
#include <commdlg.h>
#include <locale>
#include <codecvt>
#include <vector>
#include <algorithm>

#include "../Windows/spxWindows.h"
#include "../Header/Textures.h"


struct Cube1 {
    glm::vec3 position;
    glm::mat4 model;
    glm::vec3 scale;
    unsigned int textureID;
    

};

int objectUpdateIndex = -1;

bool shouldUpdateObject = false;
bool shouldDeleteObject = false;

//GLuint myNewTexture;
extern GLuint myTexture = 0;
extern unsigned int crateMap = 0;

bool rotateCube = false;


std::vector<Cube1> mycubes; // Add a cube with a button click

struct Light {
    std::string name;
    int LightId;
};

    struct Camera1 {
        std::string name;
        int camId;
    };

    struct Terrain {
        std::string name;
        int terrainId;
    };

    struct SkyBox {
        std::string name;
    };

    struct Data1 {
        int index;
        std::string value;
        int objectIdx;
        int ObjectTypeID;       

    };
    
    

    Data1* selectedData = nullptr;

    class EntityNode {
    public:
        static EntityNode* Instance() {
            static EntityNode* component = new EntityNode;

            return component;
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
            /*else {
                std::cout << "Invalid index!" << std::endl;
            }*/
            
        }





        void renderUI(std::vector<Data1>& myVector, int& currentIndex,
            int& indexCube, int& indexPlane, int& indexSphere, int ObjectTypeID) {
            
            if (!cameraAdded) { // Default Camera
                ObjectTypeID = 1;
                myVector.push_back({ currentIndex++, defaultCamera.name, 0, ObjectTypeID }); // EntityID = 4
                cameraAdded = true;
            }
            if (!sunLightAdded) {
                ObjectTypeID = 2;
                myVector.push_back({ currentIndex++, sunLightMain.name, 0, ObjectTypeID });
                    sunLightAdded = true;

            }
            if (!LightAdded) {
                ObjectTypeID = 3;
                myVector.push_back({ currentIndex++, LightMain.name, 0, ObjectTypeID });
                LightAdded = true;

            }
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
                        
                        this->nodeButtons();
                        // Perform actions when the node is hovered
                       // ImGui::SetTooltip("Hovered over %s", data.value.c_str());
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

                    ImGui::EndChild();

                    ImGui::EndTabItem();

                }
                if (ImGui::BeginTabItem("Sky Lab"))
                {
                    ImGui::Text("ID: Sky Lab");
                    ImGui::Text("Spidex Engine New Sky Lab", nullptr);
                    ImGui::Button("Save");

                    ImGui::EndTabItem();

                }
                if (ImGui::BeginTabItem("Lighting Lab"))
                {
                    ImGui::Text("ID: Sky Lab");
                    ImGui::Text("Spidex Engine New Light Lab", nullptr);
                    ImGui::Button("Save");

                    ImGui::EndTabItem();

                }
                if (ImGui::BeginTabItem("Terraine Lab"))
                {
                    ImGui::Text("ID: Sky Lab");
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
        

        bool showObjectEditor = false;
        bool cameraAdded = false;
        Camera1 defaultCamera = { ICON_FA_VIDEO " MainCamera ", 0 };// maincamera with id 0
        
        bool sunLightAdded = false;
        Light sunLightMain = { ICON_FA_SUN " World Sun", 1 };

        bool LightAdded = false;
        Light LightMain = { ICON_FA_SUN " Light", 1 };

        char nameBuffer[128] = "";
       // Data1* selectedData = nullptr;
       

        void onRightClick() {
            if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
                ImGui::OpenPopup("NodePopup");
            }      
        }
        /*void IsHovered() {
            if (ImGui::IsItemHovered()) {
                this->nodeButtons();
            }
        }*/

        // ################################### Will come back to this ####################
        SPIDEX_INLINE void nodeButtons() {
            //ImVec2 size(getLineHeight() - 3.0f, getLineHeight() - 3.0f);
             ImVec2 size(getLineHeight() - 4.0f, - 0.0f); // could be done like this
            float offset = ImGui::GetWindowWidth() -50.0f;
            
            ImGui::SameLine(offset);
            
            if (IconButton(ICON_FA_TRASH_ALT, size)) {
                // delete
            }
            ImGui::SameLine(offset - 35.0f);
            if (IconButton(ICON_FA_COPY, size)) {
                // clone
            }
            ImGui::SameLine(offset - 75.0f);
            if (IconButton(ICON_FA_PEN_ALT, size)) { // :ICON_FA_EYE
                // Edit Name
               
            }

            // this is the little buttons on the entity node!
        }

        

    };

    