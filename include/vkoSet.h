#pragma once

// sets are added/created by the manager

class VkoDescriptorManager;
class VkoDescriptor;

class VkoSet: public chainData {
public:
  uint32 index;                           // set number
  chainList descriptors;                  // [VkoDescriptor: chainData] all descriptors in this set

  VkDescriptorSetLayoutCreateFlags flags; // descriptor set flags
  VkDescriptorSetLayout layout;           // vulkan set layout - populated after calling any build func
  VkDescriptorSet set;                    // vulkan descriptor set - populated after calling any build func
  VkoDescriptorManager *parent;           // parent manager (pool) of this set

  inline operator VkDescriptorSet() { return set; }
  inline operator VkDescriptorSetLayout() { return layout; }


  // this func is mainly for descriptor push
  //  VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR - specifies that descriptor sets must not be allocated using this layout,
  //  and descriptors are instead pushed by vkCmdPushDescriptorSetKHR
  // In specs, it says there should be only one set with dynamic push, in an array of sets that are to be used
  void setDescriptorSetFlags(VkDescriptorSetLayoutCreateFlags in_flags);


  
  // creates a descriptor (a descriptor can be any kind of buffer, texture, sampler. it's a vague description of all those things)
  // <in_binding>: binding number (again, create them in order OR make sure prev number exists OR at least use in_count 0, if you skip it)
  // <in_type>:    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER / VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER / etc https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorType
  // <in_count>:   accessed in a shader as an array, when multiple. Can be 0, so it's reserved, and never accessed
  // <in_stages>:  shader stages that will use this descriptor https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap9.html#VkShaderStageFlagBits
  // <in_imutableSampler>: imutable / constant samplers, but i'd just not change them -.- imhho this ext is extra stuff that could be avoided. i think there's an extension for these
  // returns the created VkoDescriptor object.
  VkoDescriptor *addDescriptor(uint32 in_binding, VkDescriptorType in_type, uint32 in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler= null);



  bool buildLayout();
  void destroyLayout();

  VkoSet(): index(~0), flags(0), layout(null), set(null), parent(null) {}
  ~VkoSet();
};




























