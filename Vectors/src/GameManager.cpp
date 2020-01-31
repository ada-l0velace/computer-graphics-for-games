#include "GameManager.h"

GameManager::GameManager() {
    createShaderProgram();
    createBufferObjects();
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
    glBindBuffer(GL_UNIFORM_BUFFER, 0);    
    glUseProgram(0);

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}


void GameManager::createBufferObjects() {
    cgj::Vector3 w0(2.0f,-4.0f,1);
    cgj::Vector3 w1(1.0f,2.0f,3.0f);
    cgj::Vector3 w2(2.0f,2.0f,3.0f);
    cgj::Vector3 w3(1,2,3);

    std::cout << "\n--------------VECTOR3--------------\n";
    cgj::Vector3 vs[3] = {cgj::Vector3(2,0,0),cgj::Vector3(0,3,0),cgj::Vector3(0,0,4)};
    for (int i = 0; i < 3; ++i) {
        std::cout << vs[i].rotate(90.0f,vs[0].normalize());
        std::cout << vs[i].rotate(90.0f,vs[1].normalize());
        std::cout << vs[i].rotate(90.0f,vs[2].normalize());
        std::cout << "-----------------------------------\n";
    }
    std::cout << "\n--------------VECTOR2--------------\n";
    cgj::Vector2 vs2[3] = {cgj::Vector2(2,0),cgj::Vector2(0,3)};
    for (int i = 0; i < 2; ++i) {
        std::cout << vs2[i].rotate(90.0f);
        std::cout << "-----------------------------------\n";
    }
}

void GameManager::createShaderProgram() {}

void GameManager::destroyBufferObjects() {}

void GameManager::destroyShaderProgram() {}
