#include "funcs.h"

void framebuffer_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInputs(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}