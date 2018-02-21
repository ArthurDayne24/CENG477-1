cmake_minimum_required(VERSION 3.8)
project(hw4)

set(CMAKE_CXX_STANDARD 11)
add_compile_options("-c")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR})


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

include_directories(${OPENGL_INCLUDE_DIR} ${GLEW_INCLUDE_DIR} ${GLFW_INCLUDE_DIR} )

file(GLOB source_files
        "*.cpp"
        "*.h")

add_executable(hw4 ${source_files} )
target_link_libraries(hw4 ${OPENGL_GL_LIBRARY} glfw ${GLEW_LIBRARIES} ${OPENGL_LIBRARIES} jpeg GLU -I .)
#add_compile_options(-I .)
