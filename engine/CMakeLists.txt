cmake_minimum_required(VERSION 3.2)
project(SwingTech1)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/Build/Debug")
if(WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lmingw32")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
else()
set(CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -std=c++14")
set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
endif()

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if (WIN32)
include_directories(${PROJECT_SOURCE_DIR}/include)
link_directories(${PROJECT_SOURCE_DIR}/lib/windows/)
set(LUA ${PROJECT_SOURCE_DIR}/lib/windows/liblua.a)
else()
    find_package(SDL2 REQUIRED)
endif()

set(SOURCE_FILES src/Math/Shape/Shape.h src/Math/Shape/Rect.h src/STSceneManager.h src/Entity/STLight.h src/Graphics/Interface/STInterWidget.h src/STResourceManager.cpp src/STResourceManager.h src/Graphics/STMaterial.h src/Graphics/STColor.h src/Math/Shape/Quad.h src/Entity/Util/STMesh.h src/Graphics/VK/VKGraphics.cpp src/Graphics/VK/VKGraphics.h src/Graphics/GL/GLMesh.cpp src/Graphics/GL/GLMesh.h src/Math/Shape/Cube.h src/Entity/Components/STScriptComponent.cpp src/Entity/Components/STScriptComponent.h src/Entity/Components/STEventComponent.cpp src/Entity/Components/STEventComponent.h src/Graphics/Interface/STLabel.cpp src/Graphics/Interface/STLabel.h src/Entity/Util/STMesh.cpp src/Graphics/STFontMetrics.h src/Graphics/Interface/STButton.cpp src/Graphics/Interface/STButton.h src/STGame.cpp src/STGame.h src/Math/STCore.h src/Math/Vector.h src/Math/Matrix.h src/Input.cpp src/Input.h src/STGameState.cpp src/STGameState.h src/Math/Quaternion.h src/Graphics/STGraphics.cpp src/Graphics/STGraphics.h src/Graphics/GL/GLGraphics.cpp src/Graphics/GL/GLGraphics.h src/Math/Transform.h src/Graphics/Camera.cpp src/Graphics/Camera.h src/Graphics/Shader.cpp src/Graphics/Shader.h src/Graphics/GL/GLShader.cpp src/Graphics/GL/GLShader.h src/Graphics/Texture.h src/Graphics/GL/GLTexture.cpp src/Graphics/GL/GLTexture.h src/Entity/STEntity.cpp src/Entity/STEntity.h src/Entity/Components/STComponent.h src/Entity/Components/STGraphicsComponent.cpp src/Entity/Components/STGraphicsComponent.h src/Entity/Components/STMeshComponent.cpp src/Entity/Components/STMeshComponent.h src/Math/Vertex.h src/STGlobal.h src/Entity/Components/STRectBoundsComponent.cpp src/Entity/Components/STRectBoundsComponent.h src/Graphics/Interface/STLabel.cpp src/Graphics/Interface/STLabel.h "src/Math/2D Bounds/BoundShape.h" "src/Math/2D Bounds/BoundRect.h" src/Entity/Util/STMesh.cpp src/Entity/STActor.cpp src/Entity/STActor.h src/Graphics/Interface/STPanel.cpp src/Graphics/Interface/STPanel.h src/Math/Euler.h src/Graphics/Interface/STMenu.cpp src/Graphics/Interface/STMenu.h src/Graphics/Interface/STButtonGroup.cpp src/Graphics/Interface/STButtonGroup.h src/Graphics/Interface/STEntry.cpp src/Graphics/Interface/STEntry.h src/STSceneManager.cpp src/Graphics/STMaterial.cpp src/Entity/Components/STAABBComponent.cpp src/Entity/Components/STAABBComponent.h src/Entity/Components/STBoundsComponent.h src/SwingTech1.h src/Entity/Components/STShadowComponent.h src/Entity/Util/Loaders/STOBJLoader.cpp src/Entity/Util/Loaders/STOBJLoader.h src/Entity/Util/Loaders/STMeshCommon.h src/Entity/Util/Loaders/STFBXLoader.cpp src/Entity/Util/Loaders/STFBXLoader.h src/Entity/Util/Loaders/STMeshLoader.h src/Math/Transform.cpp src/Entity/Util/Loaders/OpenGEX/OpenDDL/OpenDDL.h src/Entity/Util/Loaders/OpenGEX/OpenDDL/OpenDDL.cpp src/Entity/Util/Loaders/OpenGEX/OpenDDL/ODDLTypes.h src/Entity/Util/Loaders/OpenGEX/OpenDDL/ODDLTree.h src/Entity/Util/Loaders/OpenGEX/OpenDDL/ODDLTree.cpp src/Entity/Util/Loaders/OpenGEX/OpenDDL/ODDLString.h src/Entity/Util/Loaders/OpenGEX/OpenDDL/ODDLString.cpp src/Entity/Util/Loaders/OpenGEX/OpenDDL/ODDLMap.h src/Entity/Util/Loaders/OpenGEX/OpenDDL/ODDLMap.cpp src/Entity/Util/Loaders/OpenGEX/OpenDDL/ODDLArray.h src/Entity/Util/Loaders/OpenGEX/OpenGEX/OpenGEX.h src/Entity/Util/Loaders/OpenGEX/OpenGEX/OpenGEX.cpp src/Entity/Util/Loaders/STOGEXLoader.cpp src/Entity/Util/Loaders/STOGEXLoader.h)

add_executable(SwingTech1 main.cpp ${SOURCE_FILES} )
if(WIN32)
target_link_libraries(SwingTech1 SDL2main SDL2 SDL2_image glew32 opengl32 FREETYPE; ${LUA})
endif()

add_executable(demoSwing demo/demo_main.cpp ${SOURCE_FILES})
if(WIN32)
target_link_libraries(demoSwing SDL2main SDL2 SDL2_image glew32 opengl32 FREETYPE; ${LUA})
else()
target_link_libraries(demoSwing SDL2 SDL2_image GL GLU GLEW freetype lua5.1)
endif()