#include "GameManager.h"

GameManager::GameManager() :
        m_f0(cgj::Vector3(1.0f,1.0f,0.0f),45.0f,cgj::Vector3(2.0f,2.0f,0.1f)), // Big triangule
        m_f3(cgj::Vector3(2.42f,2.42f,0.0f),-45.0f,cgj::Vector3(2.0f,2.0f,0.1f)),  // Big triangule
        m_f4(cgj::Vector3(1.7f,-0.42f,0.0f),135.0f,cgj::Vector3(1.0f,1.0f,0.1f)), // small triangule
        m_f5(cgj::Vector3(3.13f,1.0f,0.0f),-135.0f,cgj::Vector3(1.0f,1.0f,0.1f)),  // small triangule
        m_f6(cgj::Vector3(3.16f,0.33f,0.0f),0.0f,cgj::Vector3(1.5f,1.5f,0.1f)), // medium triangule
        m_f1(cgj::Vector3(2.412f,0.288f,0.0f),45.0f,cgj::Vector3(1.0f,1.0f,0.1f)), // square
        m_f2(cgj::Vector3(3.52f,1.39f,0.0f),0.0f,cgj::Vector3(0.77f,0.65f,0.1f)), // paralel
        m_persp(cgj::MatrixFactory::Perspective(cgj::math::toRadians(90.0f),1280.0f/740.0f,0.1f,2000.0f)),
        m_ortho(cgj::MatrixFactory::Ortho(-2.0f, 2.0f, -2.0f, 2.0f, -10, 30)) {
    for (int i = 0; i < 349; ++i) {
        pressed[i] = 0;
    }
    m_proj = &m_persp;

    //createShaderProgram();
    //createBufferObjects();
}


GameManager::~GameManager() {
    destroyShaderProgram();
    destroyBufferObjects();
}

void GameManager::update(double elapsed_sec, GLFWwindow* win) {
    if (pressed[GLFW_KEY_ESCAPE]) {
        glfwSetWindowShouldClose(win, GLFW_TRUE);
        window_close_callback(win);
    }
    
    m_cam->setViewMatrix(m_cam->getViewMatrix());
    m_cam->setProjectionMatrix(*m_proj);
    if (pressed[GLFW_KEY_A]) {
        m_cam->computeKeyboardInputs(cgj::ICamera::LEFT,(float)elapsed_sec);
    }
    else if(pressed[GLFW_KEY_S]) {
        m_cam->computeKeyboardInputs(cgj::ICamera::BACKWARD,(float)elapsed_sec);
    }
    else if (pressed[GLFW_KEY_D]) {
        m_cam->computeKeyboardInputs(cgj::ICamera::RIGHT,(float)elapsed_sec);
    }
    else if (pressed[GLFW_KEY_W]){
        m_cam->computeKeyboardInputs(cgj::ICamera::FORWARD,(float)elapsed_sec);
    }


    m_cam->update();
}
// CALLBACKS

void GameManager::window_close_callback(GLFWwindow* win) {
    //destroyBufferObjects();
    std::cout << "closing..." << std::endl;
}

void GameManager::window_size_callback(GLFWwindow* win, int winx, int winy) {
    //std::cout << "size: " << winx << " " << winy << std::endl;
    glViewport(0, 0, winx, winy);
}

void GameManager::key_callback(GLFWwindow* win, int key, int scancode, int action, int mods) {
    //std::cout << "key: " << key << " " << scancode << " " << action << " " << mods << std::endl;
    if(action == GLFW_PRESS)
        pressed[key] = true;
    else if(action == GLFW_RELEASE) {
        pressed[key] = false;
    }

    if (key == GLFW_KEY_P && action == GLFW_PRESS) {
        m_proj = (!ortho) ? &m_ortho : &m_persp;
        ortho = !ortho;
    }
    
}

void GameManager::mouse_callback(GLFWwindow* win, double xpos, double ypos) {
    if (pressed[GLFW_MOUSE_BUTTON_1]){
        if (!m_cam->initiation)
            m_cam->setMousePosition(cgj::Vector2((float)xpos,(float)ypos));
        else
            m_cam->mousePosition = cgj::Vector2((float)xpos,(float)ypos);
        m_cam->initiation = true;
    }
    else 
        m_cam->initiation = false;

    m_cam->computeMouseMovement((float)xpos,(float)ypos);
    //std::cout << "mouse: " << xpos << " " << ypos << std::endl;
}

void GameManager::mouse_button_callback(GLFWwindow* win, int button, int action, int mods) {
    //std::cout << "button: " << button << " " << action << " " << mods << std::endl;
}

void GameManager::scroll_callback(GLFWwindow* win, double xoffset, double yoffset) {
    //std::cout << "scroll: " << xoffset << " " << yoffset << std::endl;
    m_cam->computeMouseScroll((float)yoffset);
}

void GameManager::joystick_callback(int jid, int event) {
    //std::cout << "joystick: " << jid << " " << event << std::endl;
    
}

void GameManager::draw(double elapsed_sec) {
    //glDisable(GL_CULL_FACE);
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
    //glEnable(GL_CULL_FACE);
    glBindVertexArray(0);
    glUseProgram(0);

}


void GameManager::createBufferObjects() {
    const std::vector<GLfloat> vertices = {
        -0.5f, -0.5f,  0.5f, // 0
         0.5f, -0.5f,  0.5f, // 1
         0.5f,  0.5f,  0.5f, // 2
        -0.5f,  0.5f,  0.5f, // 3

        -0.5f, -0.5f, -0.5f, // 4
         0.5f, -0.5f, -0.5f, // 5
         0.5f,  0.5f, -0.5f, // 6
        -0.5f,  0.5f, -0.5f, // 7

        -0.5f, -0.5f,  0.5f, // 8
         0.5f, -0.5f,  0.5f, // 9
         0.5f,  0.5f,  0.5f, // 10
        -0.5f,  0.5f,  0.5f, // 11

        -0.5f, -0.5f+1.0f,  0.5f, // 12
         0.5f, -0.5f+1.0f,  0.5f, // 13
         0.5f,  0.5f+1.0f,  0.5f, // 14
        -0.5f,  0.5f+1.0f,  0.5f, // 15
        
        -0.5f, -0.5f+1.0f, -0.5f, // 16
         0.5f, -0.5f+1.0f, -0.5f, // 17
         0.5f,  0.5f+1.0f, -0.5f, // 18
        -0.5f,  0.5f+1.0f, -0.5f, // 19

        0.5f, -0.5f+1.0f,  0.5f, // 9 20
        0.5f, -0.5f+1.0f, -0.5f, // 5 21
        0.5f,  0.5f+1.0f, -0.5f, // 6 22
        0.5f,  0.5f+1.0f,  0.5f, // 10 23

        -0.5f, -0.5f-1.0f,  0.5f, // 24
         0.5f, -0.5f-1.0f,  0.5f, // 25
         0.5f,  0.5f-1.0f,  0.5f, // 26
        -0.5f,  0.5f-1.0f,  0.5f, // 27
        
        -0.5f, -0.5f-1.0f, -0.5f, // 28
         0.5f, -0.5f-1.0f, -0.5f, // 29
         0.5f,  0.5f-1.0f, -0.5f, // 30
        -0.5f,  0.5f-1.0f, -0.5f, // 31

        -0.5f, -0.5f-1.0f, -0.5f, // 4 // 32
        -0.5f, -0.5f-1.0f,  0.5f, // 8 // 33
        -0.5f,  0.5f-1.0f,  0.5f, // 11 // 34
        -0.5f,  0.5f-1.0f, -0.5f, // 7 // 35
    };


    const std::vector<GLuint> squareIndices = {
        0,1,2, // FRONT
        2,3,0,

        1,5,6, // RIGHT
        6,2,1,

        2,6,7, // TOP
        7,3,2,

        5,4,7, // BACK
        7,6,5,

        4,0,3, // LEFT
        3,7,4,

        0,4,5, // BOTTOM
        5,1,0,
    };

    const std::vector<GLuint> paralelIndices = {
        8,9,10, // FRONT
        10,11,8,

        9,5,6, // RIGHT
        6,10,9,

        /*10,6,7, // TOP
        7,11,10,*/

        5,4,7, // BACK
        7,6,5,

        4,8,11, // LEFT
        11,7,4,

        /*8,4,5, // BOTTOM
        5,9,8,*/

        12,13,14, //TOPFRONT
        /*14,15,12*/

        /*17,16,19,*/
        18,17,16, //TOPBACK
        /*17,16,19,*/

        20,21,22, // TOPLEFT
        22,23,20,

        16,23,22, // TOP
        7,11,23,

        //BOTTOMFRONT
        26,27,24,

        //BOTTOMBACK
        31,30,28,

        //BOTTOMLEFT
        32,33,34,
        34,35,32,

        //BOTTOM
        30,26,28,
        26,33,32


    };

    const std::vector<GLuint> triangleIndices = {
        0,1,2, // SIDES
        6,5,4,

        1,5,6, // RIGHT
        6,2,1,

        2,6,4, // DIAGONAL
        2,4,0,

        0,4,5, // BOTTOM
        5,1,0
    };

    const std::vector<GLfloat> textureV;

    m_f0.addData({vertices, textureV, triangleIndices});
    m_f3.addData({vertices, textureV, triangleIndices});
    
    m_f4.addData({vertices, textureV, triangleIndices});
    
    m_f5.addData({vertices, textureV, triangleIndices});
    m_f6.addData({vertices, textureV, triangleIndices});
    
    m_f1.addData({vertices, textureV, squareIndices});

    m_f2.addData({vertices, textureV, paralelIndices});
    m_cam = new cgj::FPSCamera(UBO_BP);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void GameManager::createShaderProgram() {
    
    m_shader.compileShaderFromFile("../shaders/figure.vert", cgj::ShaderType::VERTEX);
    m_shader.compileShaderFromFile("../shaders/figure.frag", cgj::ShaderType::FRAGMENT);
    m_shader.bindAttribLocation(VERTICES, "in_Position");
    m_shader.link();
    m_shader.addUniformBlock("SharedMatrices", UBO_BP);
    m_shader.detach();
}

void GameManager::destroyBufferObjects() {}

void GameManager::destroyShaderProgram() {}
