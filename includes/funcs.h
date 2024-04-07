#pragma once
#ifndef _FUNCS_HEADER
#define _FUNCS_HEADER

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "Window.h"
#include "Events.h"

enum EVENT : uint64_t {
    A_PRESSED = (uint64_t)0x1,
    B_PRESSED = (uint64_t)0x1 << 1,
    CLOSE_WIND_SIG = (uint64_t)0x1 << 2,
    CLOSE_PROG_SIG = (uint64_t)0x1 << 3,

    WINDOW_READY_A = (uint64_t)0x1 << 32,
    WINDOW_READY_B = (uint64_t)0x1 << 33,
    WINDOW_SHOULD_CLOSE = (uint64_t)0x1 << 34,
    PROGRAM_SHOULD_CLOSE = (uint64_t)0x1 << 35
};

void framebuffer_callback(GLFWwindow*, int, int);

void processInputsA();

void processInputsB();

void windowClosedUser(GLFWwindow*);

void stopWindows();

void waitForWindowClose();

int renderingProcessA();

int renderingProcessB();

#endif