#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <thread>

#include "Window.h"
#include "Events.h"
#include "funcs.h"
#include "shader.h"


int main() {
    std::cout << "Hello World!\n";

    // std::shared_ptr<std::atomic<bool>> shouldClose(new std::atomic<bool>);
    // *shouldClose = false;
    //std::atomic<uint16_t> r=51, g=77, b=77;
    std::atomic<bool> shouldClose= false;

    std::thread renderingThread(renderingProcess, std::ref(shouldClose));

    renderingThread.join();    
    return 0;
}