cmake_minimum_required(VERSION 3.16)
project(HW)

set(CMAKE_CXX_STANDARD 17)

set(MY_LIBS GLEW glfw GL assimp SOIL)

add_compile_definitions(GLEW_STATIC)

add_executable(HW src/vertex.h src/texture.h src/shader.cpp src/shader.h src/mesh.cpp src/mesh.h src/constants.h src/constants.cpp src/model.cpp src/model.h src/main.cpp src/object.h)

target_link_libraries(HW ${MY_LIBS})