cmake_minimum_required(VERSION 3.10)
project(HelloTriangle_Ex1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Disable building GLFW examples, tests, and docs to speed up your build
set(GLFW_BUILD_EXAMPLES OFF CACHE INTERNAL "")
set(GLFW_BUILD_TESTS OFF CACHE INTERNAL "")
set(GLFW_BUILD_DOCS OFF CACHE INTERNAL "")

# Add GLFW subdirectory; this exposes the "glfw" target
add_subdirectory(ext/glfw)

# Find OpenGL
find_package(OpenGL REQUIRED)

# Add your target executable
add_executable(${PROJECT_NAME} 
    src/main.cpp 
    src/glad.c
)

target_include_directories(${PROJECT_NAME} PRIVATE include)

# Link directly against the local glfw target and system OpenGL
target_link_libraries(${PROJECT_NAME} PRIVATE 
    glfw 
    OpenGL::GL
)
