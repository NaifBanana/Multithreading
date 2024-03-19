#pragma once
#ifndef _FUNCS_HEADER
#define _FUNCS_HEADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
#include "Events.h"

void framebuffer_callback(GLFWwindow* window, int width, int height);

void processInputs(GLFWwindow* window);

int renderingProcess(std::atomic<bool>&);

int consoleProcess(std::atomic<bool>&);

#endif