cmake_minimum_required(VERSION 3.16)
project(learnopengl LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(ENABLE_SANITIZERS "Enable ASan/UBSan" OFF)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(GLFW REQUIRED glfw3)

add_executable(learnopengl
  src/main.cpp
  src/gfx/Shader.cpp
  src/gfx/Mesh.cpp
  src/gfx/Renderer.cpp
  src/gfx/Texture.cpp
  src/gfx/Transform.cpp
  src/gfx/Camera.cpp
  src/app/App.cpp
  external/glad/src/glad.c
  external/stb/stb_image.cpp
)

target_include_directories(learnopengl PRIVATE
  ${GLFW_INCLUDE_DIRS}
  external/glad/include
  external
  external/stb
)

target_link_libraries(learnopengl PRIVATE
  ${GLFW_LIBRARIES}
  OpenGL::GL
)

target_link_directories(learnopengl PRIVATE ${GLFW_LIBRARY_DIRS})

if (ENABLE_SANITIZERS)
  target_link_options(learnopengl PRIVATE
    -fsanitize=address,leak,undefined
  )

  target_compile_options(learnopengl PRIVATE 
    -fsanitize=address,leak,undefined
    -g
    -O1
  )
else()
  target_compile_options(learnopengl PRIVATE -g -O1)
endif()

target_compile_options(learnopengl PRIVATE -Wall -Wextra -Wpedantic)