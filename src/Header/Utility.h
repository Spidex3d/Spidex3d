#pragma once
#include <imgui\imgui.h>
#include <iostream>
#include <string>
#include <filesystem> // Don't forget about -std=c++17 flag.

using namespace std;
using namespace std::filesystem;




void getfiles();



    

    /*
{
    auto fileList = getDirectoryFiles(fs::current_path(), { ".jpg" });

    std::cout << "List of files in the current directory:" << std::endl;
    for (const auto &fileName : fileList)
    {
        std::cout << '\t' << fileName << std::endl;
    }
    std::cout << "The number of files in the current directory: " << fileList.size() << std::endl;
    

    const char* items[] = { "test", "test2", "Test3" };
    static int item_current_idx = 0;
    ImGui::Text("Texture List");

    ImGui::BeginListBox("##File_Listbox", ImVec2(-FLT_MIN, fileList.size() * ImGui::GetTextLineHeightWithSpacing()));
    
        for (int n = 0; n < item_current_idx; n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(items[n], is_selected))
                item_current_idx = n;
            // set the initial focus on opening the combo
            if (is_selected)
                ImGui::SetItemDefaultFocus();

        }
        ImGui::EndListBox();

        
    

}
*/