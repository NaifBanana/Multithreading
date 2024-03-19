cmake_minimum_required(VERSION 3.10)
project(Multithreading VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPACK)

include_directories(./dep ./includes)
link_directories(../libs/glfw-3.3.9/build/src)

add_executable(main source/main.cpp source/Window.cpp source/Events.cpp source/funcs.cpp source/shader.cpp ../libs/glad/src/glad.c)
target_link_libraries(main glfw3)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

find_package(OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)