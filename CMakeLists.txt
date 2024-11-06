cmake_minimum_required(VERSION 3.10)
project(RivalGrounds)

# Set C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)  # Disable compiler-specific extensions

# Set output directory for binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/bin)

# Set glad sources dir
set(GLAD_SOURCES_DIR "${PROJECT_SOURCE_DIR}/external/glad/")

# For LSP
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add external libraries
add_subdirectory(external/glad/cmake)
add_subdirectory(external/glm)
add_subdirectory(external/glfw)

glad_add_library(glad STATIC API gl:core=4.6)

find_package(PythonInterp REQUIRED)

# Include the shaders
execute_process(
    COMMAND ${PYTHON_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/src/Graphics/Shaders/shader_include_generator.py
)

# Add your source files here
file(GLOB_RECURSE SOURCES 
    "src/*.cpp" 
)

# Create the executable
add_executable(RivalGrounds ${SOURCES})

# Include directories for external libraries
target_include_directories(RivalGrounds PRIVATE
    external/glm
    external/glfw/include
    build/gladsources/glad/include
    external/incbin
    external/stb

    src
)

# Link external libraries
target_link_libraries(RivalGrounds glad glm glfw)
