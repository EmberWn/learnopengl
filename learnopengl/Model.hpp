//
//  Model.hpp
//  learnopengl
//
//  Created by wangHao on 2021/3/6.
//  Copyright © 2021 wangHao. All rights reserved.
//

#ifndef Model_hpp
#define Model_hpp

#include "Mesh.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <stdio.h>
#include <vector>
#include <string>


class Model
{
public:
    Model(char* path)
    {
        LoadModel(path);
    }
    
    void Draw(Shader &shader);
    
private:
    std::vector<Mesh> meshs;
    std::string directory;
    std::vector<Texture> textures_loaded;
    
    void LoadModel(std::string path);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string type_name);
    
    unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);
    
};

#endif /* Model_hpp */
