cmake_minimum_required(VERSION 3.10)
project(Multithreading VERSION 0.1.0 LANGUAGES C CXX)

# include(CTest)
# enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
include(CPACK)

include_directories(./dep ./includes)
link_directories(../libs/glfw-3.3.9/build/src)

add_library(NBEvents source/Events.cpp)

add_library(NBWindows source/Window.cpp)

add_executable(main source/main.cpp source/funcs.cpp source/shader.cpp ../libs/glad/src/glad.c)
target_link_libraries(main NBWindows NBEvents glfw3)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)


find_package(OpenGL REQUIRED)
target_link_libraries(main OpenGL::GL)