#include "GameManager.h"

GameManager::GameManager() : m_f0(cgj::Vector3(),0.0f,2.0f),
        m_f3(cgj::Vector3(-0.5f,0,0),0.0f,2.0f),
        m_f4(cgj::Vector3(0.5f,0.5f,0.0f),0.0f,1.0f),
        m_f5(cgj::Vector3(-0.75f,0.0f,0.0f),0.0f,0.5f),
        m_f6(cgj::Vector3(-0.5f,0.5f,0.0f),0.0f,0.5f),
        m_f1(cgj::Vector3(0.0f,0.5f,0.0f),0.0f,1.0f),
        m_f2(cgj::Vector3(0.0f,-0.4f,0.0f),0.0f,1.0f) {

    //createShaderProgram();
    //createBufferObjects();
}


GameManager::~GameManager() {
    destroyShaderProgram();
    destroyBufferObjects();
}

void GameManager::update(double elapsed_sec, GLFWwindow* win) {}
// CALLBACKS

void GameManager::window_close_callback(GLFWwindow* win) {
    //destroyBufferObjects();
    std::cout << "closing..." << std::endl;
}

void GameManager::window_size_callback(GLFWwindow* win, int winx, int winy) {
    std::cout << "size: " << winx << " " << winy << std::endl;
    glViewport(0, 0, winx, winy);
}

void GameManager::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
    std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
}

void GameManager::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
    std::cout << "mouse: " << xpos << " " << ypos << std::endl;
}

void GameManager::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
    std::cout << "button: " << button << " " << action << " " << mods << std::endl;
}

void GameManager::scroll_callback(GLFWwindow* win, double xoffset, double yoffset) {
    std::cout << "scroll: " << xoffset << " " << yoffset << std::endl;
}

void GameManager::joystick_callback(int jid, int event) {
    std::cout << "joystick: " << jid << " " << event << std::endl;
}

void GameManager::draw(double elapsed_sec) {
    m_shader.use();
    m_shader.setUniform("ex_Color",1,0,0,1);
    m_f0.draw(m_shader);
    m_shader.setUniform("ex_Color",1,0,1,1);
    m_f1.draw(m_shader);
    m_shader.setUniform("ex_Color",1,0.5f,0.2f,1);
    m_f2.draw(m_shader);
    m_shader.setUniform("ex_Color",0,1,0,1);
    m_f3.draw(m_shader);
    m_shader.setUniform("ex_Color",0,0,1,1);
    m_f4.draw(m_shader);
    m_shader.setUniform("ex_Color",1,1,0,1);
    m_f5.draw(m_shader);
    m_shader.setUniform("ex_Color",0,1,1,1);
    m_f6.draw(m_shader);
    glBindVertexArray(0);
    glUseProgram(0);

}


void GameManager::createBufferObjects() {
    const std::vector<GLfloat> Square {
        0.00f, 0.00f, 0.0f,
        0.25f, 0.00f, 0.0f, 
        0.25f, 0.25f, 0.0f,
        0.00f, 0.25f, 0.0f
    };

    const std::vector<GLfloat> TrianguleV {
        0.0f, 0.0f, 0.0f,  
        0.25f, 0.0f, 0.0f, 
        0.25f, 0.25f, 0.0f,
    };
    std::vector<GLfloat> mtextureCoords;

    const std::vector<GLfloat> ParalelV {
        0.0f, 0.0f, 0.0f,  
        0.5f, 0.0f, 0.0f, 
        0.5f, 0.25f, 0.0f,
        0.0f, 0.25f, 0.0f,
    };

    const std::vector<GLuint> TrianguleIndices {
        0,1,2,
    };

    const std::vector<GLuint> SquareIndices {
        0,1,2,
        2,3,0
    };

    const std::vector<GLuint> ParalelIndices {
        0,1,2,
        2,3,0
    };


    m_f0.addData({TrianguleV, mtextureCoords, TrianguleIndices});
    m_f3.addData({TrianguleV, mtextureCoords, TrianguleIndices});
    
    m_f4.addData({TrianguleV, mtextureCoords, TrianguleIndices});
    
    m_f5.addData({TrianguleV, mtextureCoords, TrianguleIndices});
    m_f6.addData({TrianguleV, mtextureCoords, TrianguleIndices});
    
    m_f1.addData({Square, mtextureCoords, SquareIndices});

    m_f2.addData({ParalelV, mtextureCoords, ParalelIndices});
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GameManager::createShaderProgram() {
    
    m_shader.compileShaderFromFile("../shaders/figure.vert", cgj::ShaderType::VERTEX);
    m_shader.compileShaderFromFile("../shaders/figure.frag", cgj::ShaderType::FRAGMENT);
    m_shader.bindAttribLocation(VERTICES, "in_Position");
    m_shader.link();
    //m_shader.addUniformBlock("SharedMatrices", 0);
    m_shader.detach();
}

void GameManager::destroyBufferObjects() {}

void GameManager::destroyShaderProgram() {}
