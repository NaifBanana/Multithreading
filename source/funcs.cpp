#include "funcs.h"

void aPressAlert() {
    std::cout << "A PRESSED!\n";
}

void bPressAlert() {
    std::cout << "B PRESSED\n";
}

void windowCloseAlert() {
    std::cout << "WINDOW SHOULD CLOSE\n";
}

NB::NBEventBasic aKeyEvent(A_PRESSED, aPressAlert, "A_PRESSED");
NB::NBEventBasic bKeyEvent(B_PRESSED, bPressAlert, "B_PRESSED");
NB::NBEventBasic windowCloseEvent(CLOSE_WIND_SIG, stopWindows, "CLOSE_WINDOWS_SIG");

NB::NBEventState windowAIsReadyState(WINDOW_READY_A, "WINDOW_A_READY");
NB::NBEventState windowBIsReadyState(WINDOW_READY_B, "WINDOW_B_READY");
NB::NBEventState windowShouldCloseState(WINDOW_SHOULD_CLOSE, windowCloseAlert, "WINDOW_CLOSING_STATE");
NB::NBEventState programCloseState(PROGRAM_SHOULD_CLOSE, "PROGRAM_CLOSING_STATE");

// std::array<NB::NBEventContainer, 7> event_list= {
//     windowCloseEvent,
//     bKeyEvent,
//     aKeyEvent,

//     windowAIsReadyState,
//     windowBIsReadyState,
//     windowShouldCloseState,
//     programCloseState
// };
std::array<NB::NBEvents*, 7> event_list= {
    &windowCloseEvent,
    &bKeyEvent,
    &aKeyEvent,
    
    &windowAIsReadyState,
    &windowBIsReadyState,
    &windowShouldCloseState,
    &programCloseState
};
NB::NBEventListener my_listener(event_list);

NB::NBWindow* aWindow;
NB::NBWindow* bWindow;

void framebuffer_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void processInputsA() {
    GLFWwindow* window = aWindow->getWindow();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        my_listener.raiseFlags(CLOSE_WIND_SIG);
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        my_listener.raiseFlags(A_PRESSED);
    }
}

void processInputsB() {
    GLFWwindow* window = bWindow->getWindow();
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        my_listener.raiseFlags(CLOSE_WIND_SIG);
    }
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
        my_listener.raiseFlags(B_PRESSED);
    }
}

void windowClosedUser(GLFWwindow* windowToClose) {
    my_listener.raiseFlags(CLOSE_WIND_SIG);
}

void stopWindows() {
    my_listener.raiseFlags(WINDOW_SHOULD_CLOSE);
}

int renderingProcessA() {
    std::cout << "Howdy from rendering A!\n";
    std::cout << "FROM RENDERING A I SEE IN EVENT LIST " << event_list[3]->getName() << "\n";
    if ( aWindow->init() ) { return -1; }

    my_listener.raiseFlags(WINDOW_READY_A);

    glfwSetFramebufferSizeCallback(aWindow->getWindow(), framebuffer_callback);
    glfwSetWindowCloseCallback(aWindow->getWindow(), windowClosedUser);

    uint64_t count = 0;

    while(!my_listener.snoop(WINDOW_SHOULD_CLOSE)) {
        glfwMakeContextCurrent(aWindow->getWindow());
        processInputsA();
        
        // glClearColor(r/255.0f, g/255.0f, b/255.0f, 1.0f);
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glfwPollEvents();
        glfwSwapBuffers(aWindow->getWindow());
        count++;
    }
    my_listener.dropFlags(WINDOW_READY_A);
    while(my_listener.snoop(WINDOW_READY_B)) {}
    my_listener.raiseFlags(programCloseState);

    return 0;
}

int renderingProcessB() {
    std::cout << "Howdy from rendering B!\n";

    if ( bWindow->init() ) { return -1; }

    my_listener.raiseFlags(WINDOW_READY_B);

    glfwSetFramebufferSizeCallback(bWindow->getWindow(), framebuffer_callback);
    glfwSetWindowCloseCallback(bWindow->getWindow(), windowClosedUser);

    uint64_t count = 0;

    while(!my_listener.snoop(WINDOW_SHOULD_CLOSE)) {
        //std::cout << "WINDOW B FRAME\t" << count << "\n";
        glfwMakeContextCurrent(bWindow->getWindow());
        processInputsB();

        glClearColor(0.3f, 0.2f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        //glfwPollEvents();
        glfwSwapBuffers(bWindow->getWindow());
        count++;
    }
    my_listener.dropFlags(WINDOW_READY_B);
    std::cout << "DONE RENDERING B\n";
    while(my_listener.snoop(WINDOW_READY_A)) {}
    my_listener.raiseFlags(programCloseState);

    return 0;
}