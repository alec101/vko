#pragma once


// descriptors are added/created by the VkoDescriptorManager
class VkoDescriptor: public chainData {
public:
  uint32_t set, binding;                // set and binding number
  VkDescriptorType type;              // type of descriptor
  uint32_t arrayCount;                  // if an array, the number of elements
  VkShaderStageFlags shaderStages;    // shader stages that can access this descriptor
  VkSampler *pImutableSamplers;
  
  VkoSet *parent;                     // parent set of this descriptor

  inline VkoDescriptor(): set(~0), binding(~0), type(VK_DESCRIPTOR_TYPE_MAX_ENUM), arrayCount(0), shaderStages(0), pImutableSamplers(nullptr), parent(nullptr) {}
};




























