#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <CGJ/Maths.h>
#include "Figure.h"
#define VERTICES 0

class GameManager {
    public:
        GameManager(void);
        ~GameManager(void);

    private:
        bool pressed[349];
        const GLuint UBO_BP = 0;
        
        cgj::ShaderProgram m_shader;

        // big triangles
        Figure m_f0;
        Figure m_f3;

        // medium triangle
        Figure m_f4;

        // small triangles
        Figure m_f5;
        Figure m_f6;

        // square
        Figure m_f1;

        // pararelogram
        Figure m_f2;

        cgj::ICamera* m_cam;

        cgj::Matrix4* m_proj;
        cgj::Matrix4 m_persp;
        cgj::Matrix4 m_ortho;
        
    public:
        void update(double elapsed_sec, GLFWwindow* win);
        // CALLBACKS
        void window_close_callback(GLFWwindow* win);
        void window_size_callback(GLFWwindow* win, int winx, int winy);
        void key_callback(GLFWwindow* win, int key, int scancode, int action, int mods);
        void mouse_callback(GLFWwindow* win, double xpos, double ypos);
        void mouse_button_callback(GLFWwindow* win, int button, int action, int mods);
        void scroll_callback(GLFWwindow* win, double xoffset, double yoffset);
        void joystick_callback(int jid, int event);
        void createShaderProgram();
        void createBufferObjects();
        void destroyBufferObjects();
        void destroyShaderProgram();
        void draw(double elapsed_sec);
        
};