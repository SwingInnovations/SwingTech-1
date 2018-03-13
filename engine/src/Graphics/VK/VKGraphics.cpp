
#include <SDl2/SDL_vulkan.h>

#include "VKGraphics.h"
#include "../../Application/STGame.h"

VKGraphics::VKGraphics(STGame * game){
    VkInstanceCreateInfo info;
    m_instance = 0;
    VkResult res;

    info.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    info.pNext = NULL;
    info.pApplicationInfo = NULL;
    info.enabledLayerCount = 0;
    info.ppEnabledLayerNames = NULL;
    info.enabledExtensionCount = 0;
    info.ppEnabledExtensionNames = NULL;
    res = vkCreateInstance(&info, NULL, &m_instance);
    if(res != VK_SUCCESS){
        std::cout << "Error! Could not initialize vulkan" << std::endl;
    }
    std::cout << "Vulkan Device Created" << std::endl;

    SDL_Vulkan_CreateSurface(game->getWindow(), m_instance, &m_surface);

    vkDestroyInstance(m_instance, NULL);
}



void VKGraphics::init(stUint w, stUint h) {

}

void VKGraphics::cleanup() {

}

void VKGraphics::setScreenShader(const std::string &) {

}

void VKGraphics::initScene(STScene *scene) {

}

void VKGraphics::drawScene(STScene *scene) {

}

void VKGraphics::enableShadow(bool b) {

}

void VKGraphics::enableBlend() {

}

void VKGraphics::disableBlend() {

}

void VKGraphics::loadFont(const std::string &string) {

}

void VKGraphics::swapBuffer(SDL_Window *window) {
    //TODO Implement this.

}

