
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

	//stUint extensionCount = 0;
	//vkEnumerateInstanceExtensionProperties(nullptr, &extensionCount, nullptr);
	//const char** extNames = (const char**)malloc(sizeof(VkExtensionProperties) * extensionCount);
	//SDL_Vulkan_GetInstanceExtensions(game->getWindow(), &extensionCount, extNames);

	//std::cout << extensionCount << " Supported." << std::endl;
	//VkApplicationInfo appInfo = {};
	//appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
	//appInfo.pApplicationName = "SwingTech 1";
	//appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
	//appInfo.pEngineName = "SwingTech 1";
	//appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
	//appInfo.apiVersion = VK_API_VERSION_1_1;

	//VkInstanceCreateInfo createInfo = {};
	//createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
	//createInfo.pApplicationInfo = &appInfo;
	//createInfo.enabledLayerCount = 0;
	//createInfo.enabledExtensionCount = extensionCount;
	//createInfo.ppEnabledExtensionNames = (const char* const*)extNames;

	//VkResult res = vkCreateInstance(&createInfo, nullptr, &m_instance);
	//if (res != VK_SUCCESS) {
	//	STDebug::LogError("ERROR: Could not initialize Vulkan");
	//}
	//STDebug::Log("Vulkan Initialized Successfully");

	//VkPhysicalDevice device;
	//stUint deviceCount = 0;
	//vkEnumeratePhysicalDevices(m_instance, &deviceCount, nullptr);
	//if (deviceCount == 0) {
	//	STDebug::LogError("Failed to find GPU's with vulkan Support");
	//	return;
	//}
	//else {
	//	STDebug::Log("Found " + std::to_string(deviceCount) + " devices");
	//}
	//std::vector<VkPhysicalDevice> devices(deviceCount);
	//vkEnumeratePhysicalDevices(m_instance, &deviceCount, devices.data());
	//device = devices[0];

	//stUint queueCount = 0;
	//vkGetPhysicalDeviceQueueFamilyProperties(device, &queueCount, nullptr);
	//std::vector<VkQueueFamilyProperties> queueProps(queueCount);
	//vkGetPhysicalDeviceQueueFamilyProperties(device, &queueCount, queueProps.data());

	//m_nodeQueueIndex = UINT32_MAX;
	//stUint i = 0;
	//for (const auto& queue : queueProps) {
	//	if ((queue.queueFlags & VK_QUEUE_GRAPHICS_BIT) != 0) {
	//		if (m_nodeQueueIndex == UINT32_MAX) {
	//			m_nodeQueueIndex = i;
	//		}
	//	}
	//	i++;
	//}

	//SDL_Vulkan_CreateSurface(game->getWindow(), (SDL_vulkanInstance)m_instance, (SDL_vulkanSurface*)&m_surface);
	//STDebug::Log("Created Surface");

	//stReal queuePriorities[1] = { 0.0 };
	//VkDeviceQueueCreateInfo queueInfo;
	//queueInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
	//queueInfo.pNext = nullptr;
	//queueInfo.queueFamilyIndex = m_nodeQueueIndex;
	//queueInfo.queueCount = 1;
	//queueInfo.pQueuePriorities = queuePriorities;

	//VkPhysicalDeviceFeatures devFeatures = {};

	//VkDeviceCreateInfo deviceInfo;
	//deviceInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
	//deviceInfo.pNext = nullptr;
	//deviceInfo.pQueueCreateInfos = &queueInfo;
	//deviceInfo.queueCreateInfoCount = 1;
	//deviceInfo.enabledLayerCount = 0;
	//deviceInfo.enabledExtensionCount = extensionCount;
	//deviceInfo.ppEnabledExtensionNames = (const char* const*)extNames;
	//deviceInfo.pEnabledFeatures = &devFeatures;
	//deviceInfo.enabledExtensionCount = 0;

	//if (vkCreateDevice(device, &deviceInfo, nullptr, &m_device) != VK_SUCCESS) {
	//	STDebug::LogError("Failed to initialize Logical Device");
	//}
	//STDebug::Log("Created Logical Device");
	//
	//VkBool32 presentSupport = false;
	//vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);


}

void VKGraphics::cleanup() {
	vkDestroySurfaceKHR(m_instance, m_surface, nullptr);
	vkDestroyDevice(m_device, nullptr);
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
	createInfo.enabledExtensionCount = 0;

	if (vkCreateDevice(m_physicalDevice, &createInfo, nullptr, &m_device) != VK_SUCCESS) {
		STDebug::LogError("Failed to create Logical Device!");
	}
	vkGetDeviceQueue(m_device, indices.graphicsFamily, 0, &m_gfxQueue);
	vkGetDeviceQueue(m_device, indices.presentFamily, 0, &m_presentQueue);
}

const char ** VKGraphics::getExtensions(STGame* game, stUint & extensionsCount) const
{
	vkEnumerateInstanceExtensionProperties(nullptr, &extensionsCount, nullptr);
	const char** extNames = (const char**)malloc(sizeof(VkExtensionProperties) * extensionsCount);
	SDL_Vulkan_GetInstanceExtensions(game->getWindow(), &extensionsCount, extNames);
	STDebug::Log(std::to_string(extensionsCount) + " Vulkan Extensions Supported");
	return extNames;
}

bool VKGraphics::isDeviceSuitable(VkPhysicalDevice device){
	auto indices = findQueueFamilies(device);
	return indices.isComplete();
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

