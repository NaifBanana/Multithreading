#pragma once
#ifndef _NB_WINDOW
#define _NB_WINDOW

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <array>
#include <string>
#include <iostream>
namespace NB {

class NBWindow {
public:
    NBWindow(const std::array<uint16_t, 2>, const char* initName, GLFWmonitor* initMonitor=NULL, GLFWwindow* initWindow=NULL);
    NBWindow(const uint16_t, const uint16_t, const char* initName, GLFWmonitor* initMonitor=NULL, GLFWwindow* initWindow=NULL);

    int init();
    GLFWwindow* getWindow() const;
    std::array<uint16_t, 2> getSize() const;
    std::string getName() const;
    void resize(const std::array<uint16_t, 2>);
    void resize(const uint16_t x, const uint16_t y);

private:
    std::array<uint16_t, 2> windowSize;
    std::string windowName;
    bool ready=false, running=false;
    GLFWwindow* window;
    GLFWmonitor* monitor;
    GLFWwindow* shareWindow;
};

};
#endif