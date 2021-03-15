#pragma once


class VkoDescriptorLayout: public chainData {
public:
  uint32_t set, binding;              // set and binding number
  VkDescriptorType type;              // type of descriptor
  uint32_t arrayCount;                // if an array, the number of elements
  VkShaderStageFlags shaderStages;    // shader stages that can access this descriptor
  VkSampler *pImutableSamplers;
  
  VkoDescriptorSetLayout *parent;     // parent set of this descriptor

  inline VkoDescriptorLayout(VkoDescriptorSetLayout *in_parent):
    binding(~0),
    type(VK_DESCRIPTOR_TYPE_MAX_ENUM),
    arrayCount(0),
    shaderStages(0),
    pImutableSamplers(nullptr),
    parent(in_parent) {}
};




class VkoDescriptorSetLayout: public chainData {
public:
  chainList descriptors;              // [VkoDescriptorLayout: chainData] all descriptors in this set
  VkDescriptorSetLayout layout;       // Vulkan handle

  // configuration

  // creates a descriptor (a descriptor can be any kind of buffer, texture, sampler. it's a vague description of all those things)
  // <in_binding>: binding number (again, create them in order OR make sure prev number exists OR at least use in_count 0, if you skip it)
  // <in_type>:    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER / VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER / etc https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorType
  // <in_count>:   accessed in a shader as an array, when multiple. Can be 0, so it's reserved, and never accessed
  // <in_stages>:  shader stages that will use this descriptor https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap9.html#VkShaderStageFlagBits
  // <in_imutableSampler>: imutable / constant samplers, but i'd just not change them -.- imhho this ext is extra stuff that could be avoided. i think there's an extension for these
  // returns the created VkoDescriptor object.
  VkoDescriptorLayout *cfgAddDescriptor(uint32_t in_binding, VkDescriptorType in_type, uint32_t in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler= nullptr);

  // this func is mainly for descriptor push
  //  VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR - specifies that descriptor sets must not be allocated using this layout,
  //  and descriptors are instead pushed by vkCmdPushDescriptorSetKHR
  // In specs, it says there should be only one set with dynamic push, in an array of sets that are to be used
  inline void cfgDescriptorSetFlags(VkDescriptorSetLayoutCreateFlags in_flags) { _flags= in_flags; }

  struct PNext {
    void *VkDescriptorSetLayoutCreateInfo;
    void delData() { VkDescriptorSetLayoutCreateInfo= nullptr; }
  } pNext;


  // build / destroy / constructor / destructor

  bool build();
  void destroy();
  inline bool rebuild() { destroy(); return build(); }
  
  VkoDescriptorSetLayout(vkObject *in_parent);
  ~VkoDescriptorSetLayout() { destroy(); }
  void delData();

private:
  VkDescriptorSetLayoutCreateFlags _flags;

  vkObject *_vko;
  friend class vkObject;
};






