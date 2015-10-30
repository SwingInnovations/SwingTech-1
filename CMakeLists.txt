cmake_minimum_required(VERSION 3.2)
project(Wahoo)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

find_package(SDL2)
find_package(OpenGL REQUIRED)

set(SOURCE_FILES main.cpp)
set(SDL2main ${PROJECT_SOURCE_DIR}/lib/libSDL2main.a)
set(SDL2 ${PROJECT_SOURCE_DIR}/lib/libSDL2.a)
set(glew32 ${PROJECT_SOURCE_DIR}/lib/libglew32.lib)
add_executable(Wahoo ${SOURCE_FILES} src/STechWindow.cpp src/STechWindow.h src/Math/STech_Core.h src/Math/Vector.h src/Math/Matrix.h src/Input.cpp src/Input.h src/SGameState.cpp src/SGameState.h src/Math/Quaternion.h src/Graphics/GL/GLGraphics.cpp src/Graphics/GL/GLGraphics.h src/Graphics/STechGraphics.cpp src/Graphics/STechGraphics.h src/Math/Transform.h src/Graphics/Camera.cpp src/Graphics/Camera.h)
target_link_libraries(Wahoo SDL2main SDL2 glew32 opengl32)