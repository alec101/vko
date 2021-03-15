#pragma once



///=============------------------------///
// Buffer class ======================== //
///=============------------------------///

class VkoBuffer: public chainData {

public:
  VkBuffer buffer;
  inline operator VkBuffer() { return buffer; }
  VkMemoryRequirements memRequirements;           // populated after build
  VkDeviceSize offset;                            // [def:0] memory offset, it's advised to manually populate this, and use it when allocating memory
  VkBufferCreateInfo createInfo;                  // createInfo struct that will be used on build (size of buffer is inside, use pNext if required)

  // settings - set all these before building

  void cfgSize(VkDeviceSize in_bytes, VkDeviceSize in_offset= 0); // [def:0] set size, in bytes of the buffer, and the offset (offset/place in the memory object)
  void cfgUsage(VkBufferUsageFlags in_usage);     // [def:VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferUsageFlagBits
  void cfgFlags(VkBufferCreateFlagBits in_flags); // [def:0] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferCreateFlagBits
  void cfgSharingMode(VkSharingMode in_sharing);  // [def:VK_SHARING_MODE_EXCLUSIVE] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkSharingMode
  void cfgAddFamily(uint32_t in_family);             // when sharing mode is CONCURRENT, all queueFamilies that can access this buffer must be added.
  void cfgFamilies(uint32_t in_nrFamilies, const uint32_t *in_families); // same as addFamily, but sets all families in one go

  inline bool isMemoryCompatible(const VkoMemory *in_memory) { return (memRequirements.memoryTypeBits& (1 << in_memory->typeIndex)); }
  inline bool isMemoryCompatibleIndex(uint32_t in_index) { return (memRequirements.memoryTypeBits& (1<< in_index)); }

  // build / destroy

  bool build();
  inline bool rebuild() { destroy(); return build(); }
  void destroy();

  VkoBuffer(vkObject *in_parent);
  virtual ~VkoBuffer();
  void delData();

private:

  vkObject *_vko;
  friend class vkObject;
};













