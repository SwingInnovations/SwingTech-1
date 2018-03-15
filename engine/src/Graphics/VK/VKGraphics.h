#ifndef WAHOO_VKGRAPHICS_H
#define WAHOO_VKGRAPHICS_H

// Handle Vulkan based rendering here.
#include <vulkan/vulkan.h>
#include <vulkan/vk_platform.h>
#include <set>

#include "../STGraphics.h"

struct VKRenderScene : public STRenderScene {
	VKRenderScene() {
		//Default Constructor

	}
	inline void initSkybox(const std::string& shdr, const std::string& map) {

	}

	inline void drawSkybox(STCamera* camera) override {
	
	}

	void dispose() override {
	}
};

struct STQueueFamilyIndices {
	int graphicsFamily = -1;
	int presentFamily = -1;
	bool isComplete() { return graphicsFamily >= 0 && presentFamily >= 0; }
};

class VKGraphics : public STGraphics{
public:
    explicit VKGraphics(STGame*);
    void init(stUint w, stUint h) override;
	void init(STGame* game) override;
    void cleanup() override ;
    void setScreenShader(const std::string&) override;
    void initScene(STScene* scene) override ;
    void drawScene(STScene* scene) override;

    void enableBlend() override;
    void disableBlend() override;
    void loadFont(const std::string &string) override;

    void swapBuffer(SDL_Window* window) override;

private:
    VkInstance m_instance;
	VkPhysicalDevice m_physicalDevice;
	VkDevice m_device;
    VkSurfaceKHR  m_surface;
	stUint m_nodeQueueIndex;
	VkQueue	m_gfxQueue;
	VkQueue m_presentQueue;

	void initInstance(STGame* game);
	void initSurface(STGame* game);
	void selectPhysicalDevice();
	void initLogicalDevice();
	const char** getExtensions(STGame* game, stUint& extensionsCount) const;

	bool isDeviceSuitable(VkPhysicalDevice device);
	STQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
};


#endif //WAHOO_VKGRAPHICS_H
