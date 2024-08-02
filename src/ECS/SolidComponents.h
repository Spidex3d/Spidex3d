#pragma once

#include <glad\glad.h>
#include <GLFW\glfw3.h>
#include <imgui\ImGuiAF.h>
//#include <imgui\imgui_internal.h>

#include <iostream>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "../MeshObjects/Mesh.h"

#include "ECS.h"
// This needs the name of the component ie Default Cube / Default Light / Default Sphere


class SolidComponents
{
public:
   
    static SolidComponents* Instance() {
        static SolidComponents* component = new SolidComponents;

        return component;
    }

    

    inline int defaultPlane() { // if its id = 0 its a Plane
        d_PlaneId = d_PlaneId;
        PlaneIndex = PlaneIndex;
        TransformComponent trans;
        ScaleComponent scale;
        Mesh_Setup(); // temp in here
        FloorMesh();  // temp in here

        
        


        // will need a way to keep track of the Plane index
        return PlaneIndex++;
    }

    inline int defaultCube() { // if its id = 1 its a cube
        d_CubeId = d_CubeId;
        CubeIndex = CubeIndex;
        TransformComponent trans;
        ScaleComponent scale;

        if (PlaneIndex < MAX_ENTITIES) {
            std::cout << "Testing the default Cube with Id: " << d_CubeId << " Index " << CubeIndex <<
                " PosX " << trans.position_x << " PosY " << trans.position_y << " PosZ " << trans.position_z << " : " <<
                " ScaleX " << scale.scale_x << " ScaleY " << scale.scale_y << " ScaleZ " << scale.scale_z << std::endl;
        }
        // will need a way to keep track of the cube index
        return CubeIndex++;
    }
     
    

    
    void TestPanel(GLFWwindow* window) {

        ImGui::Begin("Test Window", nullptr);

        ImGui::BeginListBox("Test");

        ImGui::EndListBox();

        ImGui::End();

    }


    //  put this in here and do the same for other control panels
    void GuiEntityPanel(GLFWwindow* window) {
        
        float f = 0.0f;
        // ICON_FA_DICE_D6
        ImGui::Begin(ICON_FA_DICE_D6" NEW Eliments", nullptr); //Window Name

        if (ImGui::BeginTabBar("##Tabs", ImGuiTabBarFlags_None))
        {
            if (ImGui::BeginTabItem("Scene Eliments"))
            {

                ImGui::Text("Default Cube [%d] index [%d] ", d_CubeId, CubeIndex);
                ImGui::Text("Default Plane [%d] ", d_PlaneId);
                ImGui::Text("Default Sphere [%d] ", d_SphereId);
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
                // ###################  End List box ##################    

                ImGui::Text("Spidex Engine", nullptr);
                ImGui::Button("Save");
               // ImGui::Checkbox("Demo Window", &show_demo_window);

                ImGui::EndTabItem();

            }

            if (ImGui::BeginTabItem("Render"))
            {
                ImGui::Text("Spidex Engine Render Settings", nullptr);
                ImGui::Button("Save Render Settings");


                ImGui::Text("string");
                ImGui::SliderFloat("float", &f, 0.0f, 1.0f);
                // Edit a color stored as 4 floats
                ImGui::ColorEdit4("Color", my_color);
                ImGui::Spacing();
                //ImGui::DragFloat3("Scale", scale_value, 0.3f, 0.3f, 0.3f);
                //ImGuiIO io = ImGui::GetIO();
                //ImGui::Text("App average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);

                ImGui::EndTabItem();

            }
            if (ImGui::BeginTabItem("Scene Objects"))
            {
                ImGui::Text("Spidex Engine Objects", nullptr);




                
                ImGui::EndTabItem();

            }

            ImGui::EndTabBar();

        }
        ImGui::End();
    }

    void BgColour()
    {
        glClearColor(my_color[0], my_color[1], my_color[2], 1.0f);

    }


    inline int defaultSphere() {
        d_SphereId = d_SphereId;
        SphereIndex = SphereIndex;
        TransformComponent trans;
        ScaleComponent scale;
        if (SphereIndex < MAX_ENTITIES) {
            std::cout << "Testing the default Sphere and Id: " << d_SphereId << " Index " << SphereIndex << std::endl;
        }
        return SphereIndex++;

    }

    

    
    
    
private:
    // ** d_ = Default - Index is How many objects
    // list of Solid objects - Components - lights / sky box / terraine in seperate class
    int d_PlaneId = 0, PlaneIndex = 0;
    int d_CubeId = 1, CubeIndex = 0;
    int d_SphereId = 2, SphereIndex = 0;

    float my_color[3] = { 0.0f, 0.0f, 0.0f };
    
    struct Colour { // RGBA
        float col_r{ 0.0f }; // 0 to 1
        float col_g{ 0.0f };
        float col_b{ 0.0f };
        float col_a{ 1.0f };
    };
    struct TransformComponent {  // starting position of objects
        float position_x{ 0.0f };
        float position_y{ 0.0f };
        float position_z{ 0.0f };
    };
    struct ScaleComponent { // starting Scale of objects
        float scale_x{ 1.0f };
        float scale_y{ 1.0f };
        float scale_z{ 1.0f };
    };
    
    
    
    
    


};

