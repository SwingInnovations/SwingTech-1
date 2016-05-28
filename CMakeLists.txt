cmake_minimum_required(VERSION 3.2)
project(Wahoo)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build/Debug")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib)

find_package(SDL2)
message("${FreeType}")
set(SOURCE_FILES main.cpp src/Math/Shape/Shape.h src/Math/Shape/Rect.h src/STSceneManager.h src/STLight.h src/Graphics/Interface/STInterWidget.h src/STResourceManager.cpp src/STResourceManager.h src/Graphics/STMaterial.h src/Graphics/STColor.h src/Math/Shape/Quad.h src/STMesh.h src/Graphics/VK/VKGraphics.cpp src/Graphics/VK/VKGraphics.h src/Graphics/GL/GLMesh.cpp src/Graphics/GL/GLMesh.h src/Math/Shape/Cube.h src/STScriptComponent.cpp src/STScriptComponent.h src/STEventComponent.cpp src/STEventComponent.h)
set(SDL2main ${PROJECT_SOURCE_DIR}/lib/libSDL2main.a)
set(SDL2_image ${PROJECT_SOURCE_DIR}/lib/libSDL2_image.a)
set(SDL2 ${PROJECT_SOURCE_DIR}/lib/libSDL2.a)
set(glew32 ${PROJECT_SOURCE_DIR}/lib/libglew32.lib)
set(freetype ${PROJECT_SOURCE_DIR}/lib/libfreetype.a)
set(lua ${PROJECT_SOURCE_DIR}/lib/liblua.a)

add_executable(Wahoo ${SOURCE_FILES} src/STGame.cpp src/STGame.h src/Math/STCore.h src/Math/Vector.h src/Math/Matrix.h src/Input.cpp src/Input.h src/SGameState.cpp src/SGameState.h src/Math/Quaternion.h src/Graphics/STGraphics.cpp src/Graphics/STGraphics.h src/Graphics/GL/GLGraphics.cpp src/Graphics/GL/GLGraphics.h src/Math/Transform.h src/Graphics/Camera.cpp src/Graphics/Camera.h src/Graphics/Shader.cpp src/Graphics/Shader.h src/Graphics/GL/GLShader.cpp src/Graphics/GL/GLShader.h src/Graphics/Texture.cpp src/Graphics/Texture.h src/Graphics/GL/GLTexture.cpp src/Graphics/GL/GLTexture.h src/STEntity.cpp src/STEntity.h src/STComponent.cpp src/STComponent.h src/STGraphicsComponent.cpp src/STGraphicsComponent.h src/STMeshComponent.cpp src/STMeshComponent.h src/Math/Vertex.h src/STGlobal.h)
target_link_libraries(Wahoo SDL2main SDL2 SDL2_image glew32 opengl32 freetype lua)