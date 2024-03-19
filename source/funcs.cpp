#include "funcs.h"

void framebuffer_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInputs(GLFWwindow* window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }
}

int renderingProcess(std::atomic<bool>& shouldStop) {
    std::cout << "Howdy from rendering!\n";
    NB::NBWindow mywindow(800, 600, "Multithreading?");
    mywindow.init();
    GLFWwindow* window = mywindow.getWindow();

    glfwSetFramebufferSizeCallback(window, framebuffer_callback);

    while(!glfwWindowShouldClose(window) && !shouldStop) {
        processInputs(window);
        
        // glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwPollEvents();
        glfwSwapBuffers(window);
    }
    shouldStop = true;
    glfwSetWindowShouldClose(window, true);

    glfwTerminate();
    return 0;
}

/*
int consoleProcess(std::atomic<bool>& shouldStop) {
    char controlInput;
    while(!shouldStop) {
        std::cin >> controlInput;
        switch (controlInput) {
        case 'r':
            r = (r==51)?0:51;
            break;
        case 'g':
            g = (g==77)?0:77;
            break;
        case 'b':
            b = (b==77)?0:77;
            break;
        default:
            break;
        }
    }
}*/