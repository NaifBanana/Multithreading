#include "Window.h"
namespace NB {

NBWindow::NBWindow(const uint16_t x, const uint16_t y, const char* initName, GLFWmonitor* initMonitor, GLFWwindow* initWindow) {
    windowSize = {x, y};
    windowName = std::string(initName);
    monitor = initMonitor;
    shareWindow = initWindow;

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 4);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    ready = true;
}

NBWindow::NBWindow(const std::array<uint16_t, 2> initSize, const char* initName, GLFWmonitor* initMonitor, GLFWwindow* initWindow) :
    NBWindow(initSize[0], initSize[1], initName, initMonitor, initWindow){}

int NBWindow::init() {
    if (!ready) {
        std::cout << "NB::NBWINDOW::NOT READY\n";
        return -1;
    }

    window = glfwCreateWindow(windowSize[0], windowSize[0], windowName.c_str(), monitor, shareWindow);
    if (window == NULL) {
        std::cout << "NB::NBWINDOW::COULD NOT CREATE WINDOW\n";
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "NB::NBWINDOW::COULD NOT INITIALIZE GLAD\n";
        glfwTerminate();
        return -1;
    }

    std::cout << windowSize[0] << " by " << windowSize[1] << "\n";
    glViewport(0, 0, windowSize[0], windowSize[1]);
    running=true;
    return 0;
}

GLFWwindow* NBWindow::getWindow() const {
    return window;
}

std::array<uint16_t, 2> NBWindow::getSize() const {
    return windowSize;
}

std::string NBWindow::getName() const {
    return windowName;
}

void NBWindow::resize(const std::array<uint16_t, 2> newSize) {
    windowSize = newSize;
    if (running) {
        glViewport(0, 0, windowSize[0], windowSize[1]);
        glfwSetWindowSize(window, windowSize[0], windowSize[1]);
    }
}

void NBWindow::resize(const uint16_t x, const uint16_t y) {
    windowSize = {x, y};
    if (running) {
        glViewport(0, 0, windowSize[0], windowSize[1]);
        glfwSetWindowSize(window, windowSize[0], windowSize[1]);
    }
}

};