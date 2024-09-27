#pragma once
// Draw a mesh to display on screen

#include <glad\glad.h>


#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <stb\stb_image.h>
#include <assimp\include\assimp\Importer.hpp>
#include <assimp\include\assimp\scene.h>
#include <assimp\include\assimp\postprocess.h>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <vector>

#include "Mesh.h"

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma = false);

class Model
{
public:
    // model data
    std::vector<Texture> textures_loaded;
    std::vector<Mesh> meshes;
    std::string directory;
    bool gammaCorection;








private:



};

unsigned int TextureFromFile(const char* path, const std::string &directory, bool gamma)
{
   
        std::string filename = std::string(path);
        filename = directory + '/' + filename;


        unsigned int modelTextureID;

        glGenTextures(1, &modelTextureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrComponents, 0); // new
        if (data)
        {
            GLenum i_format;

            if (nrComponents == 1)
                i_format = GL_RED;
            else if (nrComponents == 3) // jpg file
                i_format = GL_RGB;
            else if (nrComponents == 4) // png file
                i_format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, modelTextureID);
            glTexImage2D(GL_TEXTURE_2D, 0, i_format, width, height, 0, i_format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << filename << std::endl;
            stbi_image_free(data);
        }

        return modelTextureID;

}