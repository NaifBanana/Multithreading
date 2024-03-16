#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "Window.h"
#include "funcs.h"
#include "shader.h"


int main() {
    std::cout << "Hello World!\n";
    
    NB::NBWindow mywindow(800, 600, "Classy!");
    mywindow.resize(50, 50);
    mywindow.init();
    GLFWwindow* window = mywindow.getWindow();

    glfwSetFramebufferSizeCallback(window, framebuffer_callback);

    while(!glfwWindowShouldClose(window)) {
        processInputs(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }

    glfwTerminate();
    return 0;
}