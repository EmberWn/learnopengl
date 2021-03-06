//
//  main.cpp
//  learnopengl
//
//  Created by wangHao on 2020/7/12.
//  Copyright © 2020 wangHao. All rights reserved.
//


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Shader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "Camera.hpp"
#include "Model.hpp"

#include <iostream>
#include <cmath>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
void mouse_callback(GLFWwindow* window, double posx, double posy);
void scroll_callback(GLFWwindow* window, double offsetx, double offsety);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;


Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

float delta_time = 0.0f;
float last_frame = 0.0f;

bool first_mouse = true;
float lastX = 400, lastY = 300;
float fov = 45.0f;

int main(int argc, const char * argv[])
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
    
    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    
    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    int NumAttrbutes;
    glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &NumAttrbutes);
    std::cout << "maximum num of vertex attributes supported: " << NumAttrbutes << std::endl;
    
    stbi_set_flip_vertically_on_load(true);

    Shader our_shader("shader/shader.vs", "shader/shader.ps");
    our_shader.Use(); // don't forget to activate the shader before setting uniforms!
    Model model("model/backpack/backpack.obj");


    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // render loop
    // -----------
    while(!glfwWindowShouldClose(window))
    {
        
        float  current_frame = glfwGetTime();
        delta_time = current_frame - last_frame;
        last_frame = current_frame;
        // input
        // -----
        processInput(window);
        
        // update positon matrix
        // -----


        glm::mat4 projection;
        projection = glm::perspective(glm::radians(camera.Zoom), 800.0f / 600.0f, 0.1f, 100.0f);
        

        // render
        // ------
        glEnable(GL_DEPTH_TEST);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glm::vec3 light_color;
        light_color = glm::vec3(1.0f, 1.0f, 1.0f);
        
        our_shader.Use();

        glm::vec3 diffuse_color = light_color * glm::vec3(0.8f);
        glm::vec3 ambient_color = diffuse_color * glm::vec3(0.1f);
        
        our_shader.SetFloat("material.shininess", 64.0f);
        
        our_shader.SetVec3("dir_light.direction", -0.2f, -1.0f, -0.3f);
        our_shader.SetVec3("dir_light.specular", 1.0f, 1.0f, 1.0f);
        our_shader.SetVec3("dir_light.ambient", ambient_color);
        our_shader.SetVec3("dir_light.diffuse", diffuse_color); // darken diffuse light a bit
        
        our_shader.SetVec3("spot_light.specular", 1.0f, 1.0f, 1.0f);
        our_shader.SetVec3("spot_light.ambient", ambient_color);
        our_shader.SetVec3("spot_light.diffuse", diffuse_color); // darken diffuse light a bit
        our_shader.SetVec3("spot_light.direction", camera.Front);
        our_shader.SetVec3("spot_light.position", camera.Position);
        our_shader.SetFloat("spot_light.cut_off", glm::cos(glm::radians(12.5f)));
        our_shader.SetFloat("spot_light.outer_cut_off", glm::cos(glm::radians(17.5f)));
        
        our_shader.SetMatrix4("view", camera.GetViewMatrix());
        our_shader.SetMatrix4("projection", projection);
        our_shader.SetVec3("view_pos", camera.Position);
        our_shader.SetMatrix4("model", glm::mat4(1.0f));
        
        model.Draw(our_shader);

        
        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
void processInput(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
    
    const float camera_speed = 4.5f * delta_time;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        camera.ProcessKeyboard(FORWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        camera.ProcessKeyboard(BACKWARD, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        camera.ProcessKeyboard(LEFT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        camera.ProcessKeyboard(RIGHT, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) {
        camera.ProcessKeyboard(UP, delta_time);
    }
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) {
        camera.ProcessKeyboard(DOWN, delta_time);
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double posx, double posy)
{
    if (first_mouse) {
        lastX = posx;
        lastY = posy;
        first_mouse = false;
    }
    
    float xoffset = posx - lastX;
    float yoffset = posy - lastY;
    lastX = posx;
    lastY = posy;
    
    camera.ProcessMouseMovement(xoffset, yoffset);
}

void scroll_callback(GLFWwindow* window, double offsetx, double offsety)
{
    camera.ProcessMouseScroll(offsety);
}

