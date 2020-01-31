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
    srand(static_cast<unsigned>(time(0)));
    
    for (int i = 0; i < 10; ++i) {

        std::cout << "___________________________________________\n";
        cgj::Matrix3 A(static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),
                            static_cast<float> (rand()%19-9), static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),
                            static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9));
        cgj::Matrix3 B(static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),
                            static_cast<float> (rand()%19-9), static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),
                            static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9));
        cgj::Matrix3 C(static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),
                            static_cast<float> (rand()%19-9), static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),
                            static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9));
        cgj::Matrix3 D(static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),
                            static_cast<float> (rand()%19-9), static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),
                            static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9),static_cast<float> (rand()%19-9));
            
        cgj::Matrix3 AB = A*B;
        cgj::Matrix3 CD = C*D;
        
        if (AB.determinant() != 0 && CD.determinant() != 0 && D.determinant() !=0 && C.determinant() !=0 && B.determinant() != 0 && A.determinant() !=0) {
            cgj::Matrix3 R0 = ((AB.inverse()*CD.inverse()).transpose());
            cgj::Matrix3 R1 = ((D.inverse()*C.inverse()).transpose() * (B.inverse()*A.inverse()).transpose());
            std::cout << R0;
            std::cout << "-------------------------------------------\n";
            std::cout << R1;
        }
        else {
            std::cout << "Not invertible\n";
        }

    }

    std::cout << "___________________________________________\n";
}

void GameManager::createShaderProgram() {}

void GameManager::destroyBufferObjects() {}

void GameManager::destroyShaderProgram() {}
