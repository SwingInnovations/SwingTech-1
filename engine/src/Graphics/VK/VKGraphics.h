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

struct STSwapChainSupportDetails {
	VkSurfaceCapabilitiesKHR capabilities;
	std::vector<VkSurfaceFormatKHR> formats;
	std::vector<VkPresentModeKHR> presentModes;
};

class VKGraphics : public STGraphics{
public:
    explicit VKGraphics(STGame*);
	void init(STGame* game) override;
    void cleanup() override ;
    void setScreenShader(const std::string&) override;
    void initScene(STScene* scene) override ;
    void drawScene(STScene* scene) override;

    void enableBlend() override;
    void disableBlend() override;
    void loadFont(const std::string &string) override;

    void swapBuffer(SDL_Window* window) override;

	VkInstance getInstance() const;
	VkDevice getDevice() const;

private:
	const std::vector<const char*> m_deviceExtensions = { 
		VK_KHR_SWAPCHAIN_EXTENSION_NAME
#if defined(VK_USE_PLATFORM_WIN32_KHR)
		,VK_KHR_WIN32_SURFACE_NAME
		#elseif defined(VK_USE_PLATFORM_XCB_KHR)
		, VK_KHR_XCB_SURFACE_NAME
		#elseif defined(VK_USE_PLATFORM_XLIB_KHR)
		, VK_KHR_XLIB_SURFACE_NAME
#endif
	};
    VkInstance m_instance;
	VkPhysicalDevice m_physicalDevice;
	VkDevice m_device;
    VkSurfaceKHR  m_surface;
	VkSwapchainKHR m_swapChain;
	stUint m_nodeQueueIndex;
	VkQueue	m_gfxQueue;
	VkQueue m_presentQueue;
	std::vector<VkImage> m_swapChainImages;
	std::vector<VkImageView> m_swapChainImageViews;
	VkFormat m_swapChainImageFormat;
	VkExtent2D m_swapChainExtent;
	VkRenderPass m_primaryRenderPass;
	VkPipelineLayout m_primaryPipelineLayout;

	void initInstance(STGame* game);
	void initSurface(STGame* game);
	void selectPhysicalDevice();
	void initLogicalDevice();
	void initSwapChain();
	void initImageViews();
	void initRenderPass();
	void initGraphicsPipeline();
	const char** getInstanceExtensions(STGame* game, stUint& extensionsCount) const;

	bool isDeviceSuitable(VkPhysicalDevice device);
	bool checkDeviceExtensionSupport(VkPhysicalDevice device);
	STQueueFamilyIndices findQueueFamilies(VkPhysicalDevice device);
	STSwapChainSupportDetails querySwapChainSupport(VkPhysicalDevice device);

	VkSurfaceFormatKHR chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats);
	VkPresentModeKHR chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes);
	VkExtent2D chooseSwapExtent(const VkSurfaceCapabilitiesKHR& capabilities);
};


#endif //WAHOO_VKGRAPHICS_H
