//
//  Shader.hpp
//  learnopengl
//
//  Created by wangHao on 2021/2/6.
//  Copyright © 2021 wangHao. All rights reserved.
//

#ifndef Shader_hpp
#define Shader_hpp

#include <glad/glad.h>

#include <stdio.h>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
    unsigned int m_id;
    
    Shader(const char* vertex_path, const char* fragment_path);
    
    void Use();
    void SetBool(const std::string &name, bool value) const;
    void SetInt(const std::string &name, int value) const;
    void SetFloat(const std::string &name, float value) const;
};



#endif /* Shader_hpp */
