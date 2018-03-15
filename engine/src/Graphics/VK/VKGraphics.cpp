
extern "C" {
	#include <SDl2/SDL_vulkan.h>
};

#include "VKGraphics.h"
#include "../../Application/STGame.h"
#include "../../Application/STSceneManager.h"
#include "../../Application/Util/STDebug.h"

VKGraphics::VKGraphics(STGame * game){
	RENDERER = VULKAN;
	init(game);
}


void VKGraphics::init(stUint w, stUint h) {

}

void VKGraphics::init(STGame * game)
{
	WIDTH = (stUint)game->getWidth();
	HEIGHT = (stUint)game->getHeight();
	m_instance = 0;
	m_device = VK_NULL_HANDLE;
	m_physicalDevice = VK_NULL_HANDLE;

	initInstance(game);
	initSurface(game);
	selectPhysicalDevice();
	initLogicalDevice();
	initSwapChain();
}

void VKGraphics::cleanup() {
	vkDestroySwapchainKHR(m_device, m_swapChain, nullptr);
	vkDestroyDevice(m_device, nullptr);

	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	vkDestroyInstance(m_instance, nullptr);
}
void VKGraphics::setScreenShader(const std::string &) {

}

void VKGraphics::initScene(STScene *scene) {
	scene->setRenderScene(new VKRenderScene());
}

void VKGraphics::drawScene(STScene *scene) {

}

void VKGraphics::enableBlend() {

}

void VKGraphics::disableBlend() {
	
}

void VKGraphics::loadFont(const std::string &string) {

}

void VKGraphics::swapBuffer(SDL_Window *window) {
    //TODO Implement this.
	STDebug::Log("Using VK Swap");
}

void VKGraphics::initInstance(STGame* game){
	//Initialize the Vulkan Instance
	stUint extensionCount = 0;
	VkApplicationInfo appInfo = {};
	appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	appInfo.pApplicationName = "STGame";
	appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.pEngineName = "SwingTech1";
	appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	appInfo.apiVersion = VK_API_VERSION_1_1;

	VkInstanceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	createInfo.pApplicationInfo = &appInfo;

	auto extensions = getExtensions(game, extensionCount);
	createInfo.enabledExtensionCount = extensionCount;
	createInfo.ppEnabledExtensionNames = extensions;

	if (vkCreateInstance(&createInfo, nullptr, &m_instance) != VK_SUCCESS) {
		STDebug::LogError("Failed to create Vulkan Instance");
	}
}

void VKGraphics::initSurface(STGame* game)
{
	//Initialize the Vulkan Surface
	SDL_Vulkan_CreateSurface(game->getWindow(), (SDL_vulkanInstance)m_instance, (SDL_vulkanSurface*)&m_surface);
	if (!m_surface) {
		STDebug::LogError("Failed to create Vulkan Surface");
	}
	STDebug::Log("Created Vulkan Surface");
}

void VKGraphics::selectPhysicalDevice(){
	//Initialize the Vulkan physical Devices
	stUint deviceCount = 0;
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
	if (deviceCount == 0) {
		STDebug::LogError("Failed to find Vulkan Ready GPU's");
		return;
	}

	std::vector<VkPhysicalDevice> devices(deviceCount);
	vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());
	for (const auto& device : devices) {
		if (isDeviceSuitable(device)) {
			m_physicalDevice = device;
			break;
		}
	}

	if (m_physicalDevice == VK_NULL_HANDLE) {
		STDebug::LogError("Failed to find Suitable GPU");
	}
}

void VKGraphics::initLogicalDevice(){
	//Initialize the logical device
	auto indices = findQueueFamilies(m_physicalDevice);

	std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
	std::set<int> uniqueQueueFams = { indices.graphicsFamily, indices.presentFamily };

	stReal queuePriority = 1.f;
	for (auto queueFamily : uniqueQueueFams) {
		VkDeviceQueueCreateInfo queueCreateInfo = {};
		queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
		queueCreateInfo.queueFamilyIndex = queueFamily;
		queueCreateInfo.queueCount = 1;
		queueCreateInfo.pQueuePriorities = &queuePriority;
		queueCreateInfos.push_back(queueCreateInfo);
	}

	VkPhysicalDeviceFeatures deviceFeatures = {};
	VkDeviceCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	createInfo.queueCreateInfoCount = static_cast<stUint>(queueCreateInfos.size());
	createInfo.pQueueCreateInfos = queueCreateInfos.data();
	createInfo.pEnabledFeatures = &deviceFeatures;
	createInfo.enabledExtensionCount = static_cast<stUint>(m_deviceExtensions.size());
	createInfo.ppEnabledExtensionNames = m_deviceExtensions.data();

	if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
		STDebug::LogError("Failed to create Logical Device!");
	}
	STDebug::Log("Created Logical Device");
	vkGetDeviceQueue(m_device, indices.graphicsFamily, 0, &m_gfxQueue);
	vkGetDeviceQueue(m_device, indices.presentFamily, 0, &m_presentQueue);
}

void VKGraphics::initSwapChain() {
	STSwapChainSupportDetails swapChainSupport = querySwapChainSupport(m_physicalDevice);

	auto surfaceFormat = chooseSwapSurfaceFormat(swapChainSupport.formats);
	auto presentMode = chooseSwapPresentMode(swapChainSupport.presentModes);
	auto extent = chooseSwapExtent(swapChainSupport.capabilities);

	stUint imageCount = swapChainSupport.capabilities.minImageCount + 1;
	if (swapChainSupport.capabilities.maxImageCount > 0 && imageCount > swapChainSupport.capabilities.maxImageCount) {
		imageCount = swapChainSupport.capabilities.maxImageCount;
	}

	VkSwapchainCreateInfoKHR createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
	createInfo.pNext = nullptr;
	createInfo.surface = m_surface;
	createInfo.minImageCount = imageCount;
	createInfo.imageFormat = surfaceFormat.format;
	createInfo.imageColorSpace = surfaceFormat.colorSpace;
	createInfo.imageExtent = extent;
	createInfo.imageArrayLayers = 1;
	createInfo.imageUsage = VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;

	auto indices = findQueueFamilies(m_physicalDevice);
	stUint queueFamIndices[] = { (stUint)indices.graphicsFamily, (stUint)indices.presentFamily };
	if (indices.graphicsFamily != indices.presentFamily) {
		createInfo.imageSharingMode = VK_SHARING_MODE_CONCURRENT;
		createInfo.queueFamilyIndexCount = 2;
		createInfo.pQueueFamilyIndices = queueFamIndices;
	}
	else {
		createInfo.imageSharingMode = VK_SHARING_MODE_EXCLUSIVE;
	}

	createInfo.preTransform = swapChainSupport.capabilities.currentTransform;
	createInfo.compositeAlpha = VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
	createInfo.presentMode = presentMode;
	createInfo.clipped = VK_TRUE;
	createInfo.oldSwapchain = nullptr;

	if (vkCreateSwapchainKHR(m_device, &createInfo, nullptr, &m_swapChain) != VK_SUCCESS) {
		STDebug::LogError("Failed to Create SwapChain");
	}
	else {
		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, nullptr);
		m_swapChainImages.resize(imageCount);
		vkGetSwapchainImagesKHR(m_device, m_swapChain, &imageCount, m_swapChainImages.data());
		m_swapChainImageFormat = surfaceFormat.format;
		m_swapChainExtent = extent;
	}

}

const char ** VKGraphics::getExtensions(STGame* game, stUint & extensionsCount) const{
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
	const char** extNames = (const char**)malloc(sizeof(VkExtensionProperties) * extensionsCount);
	SDL_Vulkan_GetInstanceExtensions(game->getWindow(), &extensionsCount, extNames);
	STDebug::Log(std::to_string(extensionsCount) + " Vulkan Extensions Supported");
	return extNames;
}

bool VKGraphics::isDeviceSuitable(VkPhysicalDevice device){
	auto indices = findQueueFamilies(device);
	bool extensionSupported = checkDeviceExtensionSupport(device);
	bool swapChainAdequeate = false;
	if (extensionSupported) {
		auto swapChainSupport = querySwapChainSupport(device);
		swapChainAdequeate = !swapChainSupport.formats.empty() && !swapChainSupport.presentModes.empty();
	}
	return indices.isComplete() && extensionSupported && swapChainAdequeate;
}

bool VKGraphics::checkDeviceExtensionSupport(VkPhysicalDevice device){

	stUint extensionCount = 0;
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, nullptr);

	std::vector<VkExtensionProperties> availableExtensions(extensionCount);
	vkEnumerateDeviceExtensionProperties(device, nullptr, &extensionCount, availableExtensions.data());

	std::set<std::string> requiredExtensions(m_deviceExtensions.begin(), m_deviceExtensions.end());
	for (const auto& ext : availableExtensions) {
		requiredExtensions.erase(ext.extensionName);
	}
	return requiredExtensions.empty();

}

STQueueFamilyIndices VKGraphics::findQueueFamilies(VkPhysicalDevice device){
	STQueueFamilyIndices indices;
	stUint queueFamilyCount = 0;
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);
	std::vector<VkQueueFamilyProperties> queueFamProps(queueFamilyCount);
	vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamProps.data());

	stInt i = 0;
	for (const auto& queueFam : queueFamProps) {
		if (queueFam.queueCount > 0 && queueFam.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
			indices.graphicsFamily = i;
		}
		VkBool32 presentSupport = false;
		vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

		if (queueFam.queueCount > 0 && presentSupport) {
			indices.presentFamily = i;
		}
		if (indices.isComplete()) break;
		i++;
	}
	return indices;
}

STSwapChainSupportDetails VKGraphics::querySwapChainSupport(VkPhysicalDevice device)
{
	STSwapChainSupportDetails details;
	stUint formatCount = 0, presentModeCount = 0;
	vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, nullptr);
	if (formatCount != 0) {
		details.formats.resize(formatCount);
		vkGetPhysicalDeviceSurfaceFormatsKHR(device, m_surface, &formatCount, details.formats.data());
	}

	vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, nullptr);
	if (presentModeCount != 0) {
		details.presentModes.resize(presentModeCount);
		vkGetPhysicalDeviceSurfacePresentModesKHR(device, m_surface, &presentModeCount, details.presentModes.data());
	}

	return details;
}

VkSurfaceFormatKHR VKGraphics::chooseSwapSurfaceFormat(const std::vector<VkSurfaceFormatKHR>& availableFormats)
{
	if (availableFormats.size() == 1 && availableFormats[0].format == VK_FORMAT_UNDEFINED) {
		return { VK_FORMAT_B8G8R8A8_UNORM, VK_COLOR_SPACE_SRGB_NONLINEAR_KHR };
	}

	for (const auto& availableFormat : availableFormats) {
		if (availableFormat.format == VK_FORMAT_B8G8R8A8_UNORM && availableFormat.colorSpace == VK_COLOR_SPACE_SRGB_NONLINEAR_KHR) {
			return availableFormat;
		}
	}

	return availableFormats[0];
}

VkPresentModeKHR VKGraphics::chooseSwapPresentMode(const std::vector<VkPresentModeKHR> availablePresentModes)
{
	VkPresentModeKHR bestMode = VK_PRESENT_MODE_FIFO_KHR;
	for (const auto& availPresentMode : availablePresentModes) {
		if (availPresentMode == VK_PRESENT_MODE_MAILBOX_KHR) {
			return availPresentMode;
		}
		else if (availPresentMode == VK_PRESENT_MODE_IMMEDIATE_KHR) {
			bestMode = availPresentMode;
		}
	}
	return bestMode;
}

VkExtent2D VKGraphics::chooseSwapExtent(const VkSurfaceCapabilitiesKHR & capabilities)
{
	if (capabilities.currentExtent.width != UINT32_MAX) {
		return capabilities.currentExtent;
	}
	else {
		VkExtent2D actualExtents = { WIDTH, HEIGHT };
		actualExtents.width = std::max(capabilities.minImageExtent.width, std::min(capabilities.maxImageExtent.width, actualExtents.width));
		actualExtents.height = std::max(capabilities.minImageExtent.height, std::min(capabilities.maxImageExtent.height, actualExtents.height));
		return actualExtents;
	}
}

