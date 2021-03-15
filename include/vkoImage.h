#pragma once



///============------------------------///
// Image class ======================== //
///============------------------------///

class VkoImage: public chainData {

public:
  VkImage image;
  inline operator VkImage() { return image; }
  VkMemoryRequirements memRequirements;           // populated after build
  VkDeviceSize offset;                            // [def:0] memory offset, it's advised to manually populate this, and use it when allocating memory
  VkImageCreateInfo createInfo;                   // settings struct (use pNext pointer if required)

  // settings - set all these before building

  void cfgSize(uint32_t in_dx, uint32_t in_dy, uint32_t in_depth, uint32_t in_mipLevels, uint32_t in_layers); // [def:all 0] set image's various sizes
  void cfgSize2(VkExtent3D in_size, uint32_t in_mipLevels, uint32_t in_layers);                               // [def:all 0] set image's various sizes
  void cfgFlags(VkImageCreateFlags in_flags);        // [def:0] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageCreateFlagBits
  void cfgType(VkImageType in_type);                 // [def:VK_IMAGE_TYPE_2D] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageType
  void cfgFormat(VkFormat in_format);                // [def:VK_FORMAT_UNDEFINED] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageType
  void cfgSamples(VkSampleCountFlagBits in_samples); // [def:VK_SAMPLE_COUNT_1_BIT] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap35.html#VkSampleCountFlagBits  
  void cfgTiling(VkImageTiling in_tiling);           // [def:VK_IMAGE_TILING_OPTIMAL] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageTiling
  void cfgUsage(VkImageUsageFlags in_usage);         // !! [def:0] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageUsageFlagBits

  void cfgSharingMode(VkSharingMode in_sharing);  // [def:VK_SHARING_MODE_EXCLUSIVE] exclusive may be faster https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkSharingMode
  void cfgAddFamily(uint32_t in_family);             // when sharing mode is CONCURRENT, all queueFamilies that can access this buffer must be added.
  void cfgFamilies(uint32_t in_nrFamilies, const uint32_t *in_families); // same as addFamily, but sets all families in one go

  void cfgInitialLayout(VkImageLayout in_initial); // [def:VK_IMAGE_LAYOUT_UNDEFINED] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageLayout

  // funcs

  inline bool isMemoryCompatible(const VkoMemory *in_memory) { return (memRequirements.memoryTypeBits& (1 << in_memory->typeIndex)); }
  inline bool isMemoryCompatibleIndex(uint32_t in_index) { return (memRequirements.memoryTypeBits& (1<< in_index)); }

  // build / destroy

  bool build();
  inline bool rebuild() { destroy(); return build(); }
  void destroy();

  VkoImage(vkObject *in_parent);
  virtual ~VkoImage();
  void delData();

private:

  vkObject *_vko;
  friend class vkObject;
};













