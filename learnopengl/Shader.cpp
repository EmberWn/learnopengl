//
//  Shader.cpp
//  learnopengl
//
//  Created by wangHao on 2021/2/6.
//  Copyright © 2021 wangHao. All rights reserved.
//

#include "Shader.hpp"

Shader::Shader(const char* vertex_path, const char* fragment_path, const char* geometry_path)
{
    std::string vertex_code;
    std::string fragment_code;
//    std::string geometry_code;
    std::ifstream v_shader_file;
    std::ifstream f_shader_file;
//    std::ifstream g_shader_file;
    
    v_shader_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    f_shader_file.exceptions(std::ifstream::failbit | std::ifstream:: badbit);
//    g_shader_file.exceptions(std::ifstream::failbit | std::ifstream:: badbit);
    
    try {
        v_shader_file.open(vertex_path);
        f_shader_file.open(fragment_path);
//        g_shader_file.open(geometry_path);
        std::stringstream v_shader_stream, f_shader_stream, g_shader_stream;
        v_shader_stream << v_shader_file.rdbuf();
        f_shader_stream << f_shader_file.rdbuf();
//        g_shader_stream << g_shader_file.rdbuf();
        v_shader_file.close();
        f_shader_file.close();
//        g_shader_file.close();
        vertex_code = v_shader_stream.str();
        fragment_code = f_shader_stream.str();
//        geometry_code = g_shader_stream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ" << std::endl;
    }
    
    const char* v_shader_code = vertex_code.c_str();
    const char* f_shader_code = fragment_code.c_str();
//    const char* g_shader_code = geometry_code.c_str();
    
    // vertex shader
    unsigned int VertexShader;
    VertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(VertexShader, 1, &v_shader_code, NULL);
    glCompileShader(VertexShader);
    
    int success;
    char infoLog[512];
    glGetShaderiv(VertexShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(VertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
    // fragment shader
    unsigned int FragmentShader;
    FragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(FragmentShader, 1, &f_shader_code, NULL);
    glCompileShader(FragmentShader);
    
    glGetShaderiv(FragmentShader, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(FragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGEMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    
//    // geometry shader
//    unsigned int GeometryShader;
//    GeometryShader = glCreateShader(GL_GEOMETRY_SHADER);
//    glShaderSource(GeometryShader, 1, &g_shader_code, NULL);
//    glCompileShader(GeometryShader);
//
//    glGetShaderiv(GeometryShader, GL_COMPILE_STATUS, &success);
//    if(!success)
//    {
//        glGetShaderInfoLog(GeometryShader, 512, NULL, infoLog);
//        std::cout << "ERROR::SHADER::GEOMETRY::COMPILATION_FAILED\n" << infoLog << std::endl;
//    }
    // link shaders
    m_id = glCreateProgram();
    glAttachShader(m_id, VertexShader);
    glAttachShader(m_id, FragmentShader);
//    glAttachShader(m_id, GeometryShader);
    glLinkProgram(m_id);
    
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    
    glDeleteShader(VertexShader);
    glDeleteShader(FragmentShader);
//    glDeleteShader(GeometryShader);
}

void Shader::Use()
{
    glUseProgram(m_id);
}

void Shader::SetBool(const std::string &name, bool value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), int(value));
}

void Shader::SetInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(m_id, name.c_str()), value);
}

void Shader::SetMatrix4(const std::string &name, glm::mat4 matrix) const
{
    unsigned int transformLoc = glGetUniformLocation(m_id, name.c_str());
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));

}

void Shader::SetVec3(const std::string &name, float x, float y, float z) const
{
    unsigned int location = glGetUniformLocation(m_id, name.c_str());
    glUniform3f(location, x, y, z);
}

void Shader::SetVec3(const std::string &name, glm::vec3 vec) const
{
    SetVec3(name, vec.x, vec.y, vec.z);
}

void Shader::SetVec2(const std::string &name, glm::vec2 vec) const
{
    unsigned int location = glGetUniformLocation(m_id, name.c_str());
    glUniform2f(location, vec.x, vec.y);
}
