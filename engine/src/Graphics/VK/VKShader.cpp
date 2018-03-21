#include "VKShader.h"
#include "VKGraphics.h"
#include "../../Application/STGame.h"
#include "../../Application/Util/STDebug.h"

VKShader::VKShader()
{
}

VKShader::VKShader(const std::string & filePath)
{
}

void VKShader::save(std::ofstream & out)
{
}

void VKShader::load(std::ifstream & in)
{

}

std::vector<char> VKShader::readFile(const std::string & fileName)
{
	std::ifstream file(fileName.c_str(), std::ios::ate | std::ios::binary);

	if (!file.is_open()) {
		STDebug::LogError("Failed to open Shader File!");
	}

	size_t fileSize = (size_t)file.tellg();
	std::vector<char> buffer(fileSize);
	file.seekg(0);
	file.read(buffer.data(), fileSize);
	file.close();
	return buffer;
}

VkShaderModule VKShader::createShaderModule(const std::vector<char>& code)
{
	auto vkgfx = dynamic_cast<VKGraphics*>(STGame::Get()->getGraphics());
	VkShaderModuleCreateInfo createInfo = {};
	createInfo.sType = VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
	createInfo.codeSize = code.size();
	createInfo.pCode = reinterpret_cast<const stUint*>(code.data());
	VkShaderModule ret;
	if (VK_SUCCESS != vkCreateShaderModule(vkgfx->getDevice(), &createInfo, nullptr, &ret)) {
		STDebug::LogError("Could not create Shader Module");
		return NULL;
	}
	return ret;
}
