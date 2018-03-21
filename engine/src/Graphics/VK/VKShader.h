#ifndef SWINGTECH_VKSHADER_H
#define SWINGTECH_VKSHADER_H

#include <vulkan/vulkan.h>

#include "../Shader.h"

class VKShader : Shader {
public:
	VKShader();
	VKShader(const std::string& filePath);
	void save(std::ofstream& out) override;
	void load(std::ifstream& in) override;
private:
	std::vector<char> readFile(const std::string& fileName);
	VkShaderModule createShaderModule(const std::vector<char>& code);
	VkShaderModule m_vertShader;
	VkShaderModule m_fragShader;
};
#endif