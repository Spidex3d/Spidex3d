#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\ImGuiAF.h>
//#include <imgui\imgui_internal.h>

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

//#include "../MeshObjects/Mesh.h"
#include "../Shader/Shader.h"
#include "../Header/Camera.h"

#include "ECS.h"
// This needs the name of the component ie Default Cube / Default Light / Default Sphere

//float pos_val[3] = { 0.0f, 0.0f, 2.0f };
//float rot_val[3] = { 0.3f, 0.3f, 0.3f };
//float scale_val[3] = { 1.0f, 1.0f, 1.0f };
//
//int fill = 20; // use this to change how many squares in the grid
//bool isSelected = false; // flag to check if a node is selected

// bool shouldAddCube = false;
//int cubeIndex = 0;

class SolidComponents
{
public:

      
   /* static SolidComponents* Instance() {
        static SolidComponents* component = new SolidComponents;

        return component;
    }*/

       


    
    /*int cubeIndex
    int typeID
    int cubeTextureID
    string cubeName (DefaultCube) but will need to be updated
    
    The same for every object
    Transition always starts at 0,0,0
    scale always starts at 1,1,1
    rotation always starts at 0,0,0  
    */

    //inline int defaultCube() { 
    //int defaultCube() { 
    //   // Mesh_Setup(); // setup the cube info
    //    d_CubeId = d_CubeId; // if its id = 1 its a cube
    //    cubeIndex = cubeIndex;
    //    TransformComponent trans;
    //    ScaleComponent scale;

    //    //return 0;
    //    return cubeIndex++;
    //    
    //}
     
   /* inline int defaultSphere() {
        d_SphereId = d_SphereId;
        SphereIndex = SphereIndex;
        TransformComponent trans;
        ScaleComponent scale;
        if (SphereIndex < MAX_ENTITIES) {
            std::cout << "Testing the default Sphere and Id: " << d_SphereId << " Type Index " << SphereIndex << std::endl;
        }
        return SphereIndex++;

    }*/

    //  put this in here and do the same for other control panels
    //void GuiEntityPanel(GLFWwindow* window) {
    //    
    //    float f = 0.0f;
    //    // ICON_FA_DICE_D6
    //    ImGui::Begin(ICON_FA_DICE_D6" NEW Eliments", nullptr); //Window Name

    //    if (show_demo_window)
    //        ImGui::ShowDemoWindow(&show_demo_window);

    //    if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
    //    {
    //        if (ImGui::BeginTabItem("Scene Eliments"))
    //        {

    //            ImGui::Text("Default Cube [%d] index [%d] ", d_CubeId, cubeIndex);
    //            ImGui::Text("Default Plane [%d] ", d_PlaneId);
    //            ImGui::Text("Default Sphere [%d] ", d_SphereId);

    //            if (ImGui::Button("Add Cube")) {
    //               // shouldAddCube = true;
    //                cubeIndex++; //add 1 to the index
    //               // std::cout << "Index is: " << cubeIndex << std::endl;
    //            }
    //            ImGui::SameLine();
    //            if (ImGui::Button("Remove Cube")) {
    //                //shouldAddCube = false;
    //                cubeIndex--; // remove 1 from index
    //                // will need a way to keep track of this cubeindex
    //            }
    //           
    //            //std::string name = "Cube";
    //            const char* name = "cube";

    //            ImGui::SeparatorText(ICON_FA_SPIDER" Seane Tree");

    //            // ######################## Tree Node Start ##########################
    //            

    //            //if (ImGui::TreeNodeEx(ICON_FA_CUBE" Spidex Scean"))
    //            if (ImGui::TreeNodeEx(ICON_FA_STREET_VIEW" Spidex Scean"))
    //            {
    //               
    //                static ImGuiTreeNodeFlags base_flags = ImGuiTreeNodeFlags_OpenOnArrow |
    //                    ImGuiTreeNodeFlags_OpenOnDoubleClick | ImGuiTreeNodeFlags_SpanAvailWidth;
    //                static bool align_label_with_current_x_position = false;
    //                static bool test_drag_and_drop = false;
    //                
    //                if (align_label_with_current_x_position)
    //                    ImGui::Unindent(ImGui::GetTreeNodeToLabelSpacing());

    //                // 'selection_mask' is dumb representation of what may be user-side selection state.
    //                //  You may retain selection state inside or outside your objects in whatever format you see fit.
    //                // 'node_clicked' is temporary storage of what node we have clicked to process selection at the end
    //                /// of the loop. May be a pointer to your own node type, etc.
    //                static int selection_mask = (1 << 2);
    //                int node_clicked = -1;
    //                for (int i = 0; i < 6; i++)
    //                {
    //                    // Disable the default "open on single-click behavior" + set Selected flag according to our selection.
    //                    // To alter selection we use IsItemClicked() && !IsItemToggledOpen(), so clicking on an arrow doesn't alter selection.
    //                    ImGuiTreeNodeFlags node_flags = base_flags;
    //                    const bool is_selected = (selection_mask & (1 << i)) != 0;
    //                    if (is_selected)
    //                        node_flags |= ImGuiTreeNodeFlags_Selected;
    //                    if (i < cubeIndex) //#######
    //                    {
    //                        // ICON_FA_LANDMARK ICON_FA_MOON  ICON_FA_PUZZLE_PIECE ICON_FA_UNDO_ALT ICON_FA_STREET_VIEW
    //                        // Items 0..2 are Tree Node ICON_FA_VIDEO ICON_FA_CUBE ICON_FA_SUN ICON_FA_CLOUD_MOON ICON_FA_BOX_OPEN
    //                        bool node_open = ImGui::TreeNodeEx((void*)(intptr_t)i, node_flags, ICON_FA_CUBE "Scene Object %d", i);
    //                        if (ImGui::IsItemClicked() && !ImGui::IsItemToggledOpen())
    //                            node_clicked = i;
    //                        if (test_drag_and_drop && ImGui::BeginDragDropSource())
    //                        {
    //                            ImGui::SetDragDropPayload("_TREENODE", NULL, 0);
    //                            ImGui::Text("This is a drag and drop source");
    //                            ImGui::EndDragDropSource();
    //                        }
    //                        if (i == 2)
    //                        {
    //                            // Item 2 has an additional inline button to help demonstrate SpanTextWidth.
    //                            ImGui::SameLine();
    //                            if (ImGui::SmallButton("X")) {}
    //                            ImGui::SameLine();
    //                            if (ImGui::SmallButton("X")) {}
    //                            
    //                        }
    //                        if (node_open)
    //                        {
    //                        //    ImGui::BulletText("Blah blah\nBlah Blah");
    //                            ImGui::TreePop();
    //                        }
    //                    }
    //                    
    //                }
    //                /*
    //                if (node_clicked != -1)
    //                {
    //                    // Update selection state
    //                    // (process outside of tree loop to avoid visual inconsistencies during the clicking frame)
    //                    if (ImGui::GetIO().KeyCtrl)
    //                        selection_mask ^= (1 << node_clicked);          // CTRL+click to toggle
    //                    else //if (!(selection_mask & (1 << node_clicked))) // Depending on selection behavior you want, may want to preserve selection when clicking on item that is part of the selection
    //                        selection_mask = (1 << node_clicked);           // Click to single-select
    //                }
    //                if (align_label_with_current_x_position)
    //                    ImGui::Indent(ImGui::GetTreeNodeToLabelSpacing());
    //                    */
    //                ImGui::TreePop();
    //            }
    //            
    //            // ######################## Tree Node End ##########################

    //            
    //                
    //           
    //           

    //            ImGui::Text("Spidex Engine", nullptr);
    //            ImGui::Button("Save");
    //            ImGui::Checkbox("Demo Window", &show_demo_window);

    //            ImGui::EndTabItem();

    //        }

    //        if (ImGui::BeginTabItem("Render"))
    //        {
    //            ImGui::Text("Spidex Engine Render Settings", nullptr);
    //            ImGui::Button("Save Render Settings");


    //            ImGui::Text("string");
    //            ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
    //            // Edit a color stored as 4 floats
    //            ImGui::ColorEdit4("Color", my_color);
    //            ImGui::Spacing();
    //            //ImGui::DragFloat3("Scale", scale_value, 0.3f, 0.3f, 0.3f);
    //            //ImGuiIO io = ImGui::GetIO();
    //            //ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

    //            ImGui::EndTabItem();

    //        }
    //        if (ImGui::BeginTabItem("Scene Objects"))
    //        {
    //            ImGui::Text("Spidex Engine Objects", nullptr);




    //            
    //            ImGui::EndTabItem();

    //        }

    //        ImGui::EndTabBar();

    //    }
    //    ImGui::End();
    //}

    // #####################  Property panel ##################################

    //void ImGuiPropertiesPanel(GLFWwindow* window)
    //{
    //    // To Replace demo window
    //    // 4 Tabs Properties, Textures Lab, Terraine Lab, Sky Lab
    //    ImGui::Begin(ICON_FA_CUBES" Properties", nullptr);

    //    if (ImGui::BeginTabBar("##Main", ImGuiTabBarFlags_None))
    //    {
    //        if (ImGui::BeginTabItem("Property Lab"))
    //        {
    //            ImGui::Text("ID: Textures");
    //            ImGui::Text("Spidex Engine Textures", nullptr);
    //            // ImGui::Text("pointer = %x", texture_image_id);
    //            // ImGui::Text("Size = %d x %d", tex_image_width, tex_image_height);

    //            ImGui::Spacing();
    //            // ################################# File ###########################

    //            //Utility::Instance()->getDirectoryFiles();
    //            //Utility::Instance()->Initialize();


    //            // ################################# End File ###########################

    //           // I need to loop thought all images in the texture folder
    //              //int ret = LoadTextureFiles("Textures/github.jpg", &texture_image_id, tex_image_width, tex_image_height);

    //            // ######################## Show the texture

    //              //ImVec2 pos = ImGui::GetCursorScreenPos();

    //              //ImGui::GetWindowDrawList()->AddImage((void*)texture_image_id, ImVec2(pos.x, pos.y),
    //              //ImVec2(pos.x + 100, pos.y + 100), ImVec2(0, 1), ImVec2(1, 0));

    //            //#########################
    //            ImGui::SeparatorText(ICON_FA_SPIDER" Settings");

    //            ImGui::BeginChild("Chlid");
    //            //################################################




    //            // ###################################################
    //            static ImGuiTableFlags flags = ImGuiTableFlags_Reorderable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders;

    //            static bool selected;

    //            if (ImGui::CollapsingHeader(ICON_FA_INFO" Entity info", ImGuiTreeNodeFlags_DefaultOpen))
    //            {
    //                ImGui::BeginTable("Test Table", 2, flags);

    //                bool test = true;
    //                const char* label = "Default Cube";
    //                ImGui::TableNextColumn();
    //                ImGui::TextUnformatted("Entity Name");
    //                ImGui::TableNextColumn();
    //                ImGui::TextUnformatted(label); 
    //                ImGui::TableNextRow();
    //                ImGui::TableNextColumn();
    //                ImGui::TextUnformatted("Enabeled");
    //                ImGui::TableNextColumn();
    //             
    //                if (ImGui::Checkbox("##test", &test)) {
    //                    // do somthing
    //                   
    //                }
    //                //ImGui::TextUnformatted("Checkbox");

    //                

    //                /*
    //                for (int i = 0; i < 10; i++)
    //                {
    //                    char label[32];
    //                    sprintf_s(label, "Item %d", i);
    //                    ImGui::TableNextColumn();
    //                    ImGui::Selectable(label, &selected[i]);

    //                }
    //                */
    //                ImGui::EndTable();

    //            }
    //            
    //            // ICON_FA_SPINNER
    //            if (ImGui::CollapsingHeader(ICON_FA_STREET_VIEW" Transform", ImGuiTreeNodeFlags_DefaultOpen))
    //            {
    //                ImGui::BeginTable("Test Table", 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders);
    //                
    //                ImGui::TableNextColumn();
    //                ImGui::Text("Position:  ");
    //                ImGui::SameLine();
    //                if (ImGui::Button("Reset")) {
    //                    pos_val[0] = 0.0f, pos_val[1] = 0.0f, pos_val[2] = 2.0f;
    //                }// Reset to 0,0,0
    //                ImGui::SameLine();
    //                ImGui::DragFloat3("##pos", pos_val, 1.0f, 1.0f, 2.0f);
    //                ImGui::TableNextRow();
    //                ImGui::TableNextColumn();
    //                ImGui::Text("Rotation:  ");
    //                ImGui::SameLine();
    //                if (ImGui::Button("Reset")) {
    //                    rot_val[0] = 0.0f, rot_val[1] = 0.0f, rot_val[2] = 0.0f;
    //                }
    //                ImGui::SameLine();
    //                ImGui::DragFloat3("##Rot", rot_val, 1.0f, 1.0f, 1.0f);
    //               
    //                ImGui::TableNextRow();
    //                ImGui::TableNextColumn();
    //                ImGui::Text("Scale:       ");
    //                ImGui::SameLine();                   
    //                if (ImGui::Button("SReset")) {
    //                    scale_val[0] = 1.0f, scale_val[1] = 1.0f, scale_val[2] = 1.0f;
    //                }// 1,1,1
    //                ImGui::SameLine();
    //                ImGui::DragFloat3("##Scale", scale_val, 1.0f, 1.0f, 1.0f);

    //                ImGui::Selectable(label, &selected);

    //                ImGui::EndTable();

    //            }

    //            ImGui::EndChild();

    //            ImGui::EndTabItem();

    //        }
    //        if (ImGui::BeginTabItem("Sky Lab"))
    //        {
    //            ImGui::Text("ID: Sky Lab");
    //            ImGui::Text("Spidex Engine New Sky Lab", nullptr);
    //            ImGui::Button("Save");

    //            ImGui::EndTabItem();

    //        }
    //        if (ImGui::BeginTabItem("Lighting Lab"))
    //        {
    //            ImGui::Text("ID: Sky Lab");
    //            ImGui::Text("Spidex Engine New Light Lab", nullptr);
    //            ImGui::Button("Save");

    //            ImGui::EndTabItem();

    //        }
    //        if (ImGui::BeginTabItem("Terraine Lab"))
    //        {
    //            ImGui::Text("ID: Sky Lab");
    //            ImGui::Text("Spidex Engine New Terrain Lab", nullptr);
    //            ImGui::Button("Save");

    //            ImGui::EndTabItem();

    //        }


    //        ImGui::EndTabBar();
    //    }

    //    ImGui::End();
    //}

    /*void BgColour()
    {
        glClearColor(my_color[0], my_color[1], my_color[2], 1.0f);

    }
    */
    
    
private:
    // ** d_ = Default - Index is How many objects
    // list of Solid objects - Components - lights / sky box / terraine in seperate class
    //int d_PlaneId = 0, PlaneIndex = 0;
    //int d_CubeId = 1; //cubeIndex = 0;
    //int d_SphereId = 2, SphereIndex = 0;
    //
    //

    //bool show_demo_window = false;

    //float my_color[3] = { 0.0f, 0.0f, 0.0f };

    ////float pos_val[3] = { 0.3f, 0.3f, 0.3f };
    ////float rot_val[3] = { 0.3f, 0.3f, 0.3f };
    ////float scale_val[3] = { 0.3f, 0.3f, 0.3f };

    //struct Colour { // RGBA
    //    float col_r{ 0.0f }; // 0 to 1
    //    float col_g{ 0.0f };
    //    float col_b{ 0.0f };
    //    float col_a{ 1.0f };
    //};
    //struct TransformComponent {  // starting position of objects
    //    float position_x{ 0.0f };
    //    float position_y{ 0.0f };
    //    float position_z{ 0.0f };
    //};
    //struct ScaleComponent { // starting Scale of objects
    //    float scale_x{ 1.0f };
    //    float scale_y{ 1.0f };
    //    float scale_z{ 1.0f };
    //};
    
    
    
    
    /*
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("Position");
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("X");
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("Y");
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("Z");

                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("Rotation");
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("X");
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("Y");
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("Z");
                    ImGui::TableNextRow();
                    ImGui::TableNextColumn();
                    ImGui::TextUnformatted("Scale");
                    ImGui::TableNextColumn();

                    */


};

/*
               // ###########  List Box ##################
               const char* itm = "test_1";
               const char* itm1 = "test_2";
               const char* itm2 = "test_3";

               //int itm = 1;
              // int itm1 = 2;
               //int itm2 = 3;

               const char* items[] = { itm, itm1, itm2 };
               static int item_current_idx = 0;
               ImGui::Text("Scean Eliments");
               if (ImGui::BeginListBox("##Eliments_Listbox", ImVec2(-FLT_MIN, 5 * ImGui::GetTextLineHeightWithSpacing())))
               {
                   for (int n = 0; n < IM_ARRAYSIZE(items); n++)
                   {
                        const bool is_selected = (item_current_idx == n);
                       if (ImGui::Selectable(items[n], is_selected))
                          item_current_idx = n;
                        //set the initial focus on opening the combo
                       if (is_selected)
                           ImGui::SetItemDefaultFocus();

                   }
                   ImGui::EndListBox();
               }
               */
               // ###################  End List box ##################    

