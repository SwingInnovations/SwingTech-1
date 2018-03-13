#ifndef WAHOO_VKGRAPHICS_H
#define WAHOO_VKGRAPHICS_H

// Handle Vulkan based rendering here.
#include <vulkan/vulkan.h>
#include <vulkan/vk_platform.h>

#include "../STGraphics.h"

class VKGraphics : public STGraphics{
public:
    explicit VKGraphics(STGame*);
    void init(stUint w, stUint h) override;
    void cleanup() override ;
    void setScreenShader(const std::string&) override;
    void initScene(STScene* scene) override ;
    void drawScene(STScene* scene) override;

    void enableShadow(bool b) override;
    void enableBlend() override;
    void disableBlend() override;
    void loadFont(const std::string &string) override;

    void swapBuffer(SDL_Window* window) override;

private:
    VkInstance m_instance;
    VkSurfaceKHR  m_surface;
};


#endif //WAHOO_VKGRAPHICS_H
