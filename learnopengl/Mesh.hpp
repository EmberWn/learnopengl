//
//  Mesh.hpp
//  learnopengl
//
//  Created by wangHao on 2021/3/6.
//  Copyright © 2021 wangHao. All rights reserved.
//

#ifndef Mesh_hpp
#define Mesh_hpp

#include "glm/glm.hpp"
#include "Shader.hpp"

#include <iostream>
#include <string>
#include <vector>

struct Vertex
{
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 tex_coords;
};

struct Texture
{
    unsigned int id;
    std::string type;
    std::string path;
};

class Mesh
{
public:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture> textures;
    
    Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures);
    void Draw(Shader &shader);
    
    unsigned int GetVAO() const { return VAO; }
    
private:
    unsigned int VAO, VBO, EBO;
    
    void SetUpMesh();
    
};

#include <stdio.h>

#endif /* Mesh_hpp */
