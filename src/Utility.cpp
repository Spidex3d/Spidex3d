#include "Header/Utility.h"


namespace fs = std::filesystem;

std::vector<std::string>getDirectoryFiles(const path& directory, const std::vector<std::string> extensions)
{
    // List of file names.
    std::vector<std::string> files{};

    for (const auto& file : recursive_directory_iterator(directory))
    {
        if (is_regular_file(file))
        {
            if (extensions.empty() ||
                std::find(extensions.begin(), extensions.end(), file.path().extension().string()) != (extensions.end()))
            {
                files.push_back(file.path().filename().string());
            }
        }
    }
    return files;

    return std::vector<std::string>();
}


void getfiles()
{


    int file_count = 0;
    string path = "Textures";
    string extension = ".jpg";

    //auto fileList = getDirectoryFiles(current_path(), { ".jpg" });
    auto fileList = getDirectoryFiles(current_path(), { extension });

    for (const auto& entry : directory_iterator(path))
    {

        if (entry.path().extension() == extension) {
           // cout << entry.path().filename() << endl;
            file_count++;
        }


    }


    //std::cout << "The number of files in the current directory is: " << file_count << std::endl;

    //return true;
}

    

/*

 for (int n = 0; n < IM_ARRAYSIZE(items); n++)
        {
            const bool is_selected = (item_current_idx == n);
            if (ImGui::Selectable(items[n], is_selected))
                item_current_idx = n;
            // set the initial focus on opening the combo
            if (is_selected)
                ImGui::SetItemDefaultFocus();

        }
        ImGui::EndListBox();

*/
