#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>

#include "Window.h"
#include "Events.h"
#include "funcs.h"
#include "shader.h"

extern NB::NBWindow* aWindow;
extern NB::NBWindow* bWindow;
extern NB::NBEventListener my_listener;

int main() {
    std::cout << "Hello World!\n";

    NB::NBWindow windowa(800, 600, "Multithreading?");
    NB::NBWindow windowb(800, 600, "Multithreading!");
    aWindow = &windowa;
    bWindow = &windowb;

    glfwMakeContextCurrent(NULL);
    std::thread renderingThreadA(renderingProcessA);
    std::thread renderingThreadB(renderingProcessB);

    renderingThreadB.detach();
    renderingThreadA.detach();

    while(!my_listener.snoop(PROGRAM_SHOULD_CLOSE)) {
        glfwPollEvents();
        my_listener.listen();
    }
    std::cout << "YOUVE REACHED THE END OF THE MAIN THREAD!\n";


    state_register* state = my_listener.getStatePtr();
    delete state;
    return 0;
}