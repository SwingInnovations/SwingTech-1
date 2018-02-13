# **SwingTech 1**

SwingTech 1 is a multi-platform game engine designed to be portable and flexible, while also being minimal. SwingTech 1 has been developed and tested to work on Windows and Linux OS. 

### **SwingTech 1 Currently Supports**
* Imports of Common 3D File Types( Such as .fbx, .obj, ..etc)
* File IO
* JSON Serialization
* Lua Scripting
* Physics
* Extended GLSL Language
* Deferred and Forward Rendering
* Physically Based Rendering Shading Network
* Post-Processing Effects(Bloom / Motion Blur / Tone Mapping / FXAA)

## **Getting Started**

**Dev Environment**
* MinGW(on Windows) or g++(on Unix Systems) Version 5.4.0 x64bit.
* CLion or other IDE that can open CMake Projects.

## **Building SwingTech 1**
1. Clone the project into the directory of your choice.
2. In CLion, select Open Project and select the CMakelist.txt
3. Select Build

## **Running SwingTech1**
To run the SwingTech1 Demo, you will first need to copy the .dll (On Windows) to the Build Directory.

* Copy all files from `\engine\lib\windows\MinGW\dlls` to your build directory. (Default is at `\engine\Build\Debug` )

## **Libraries Used**
* SDL
* OpenGL
* Bullet Physics
* sol
* Freetype
* Assimp





