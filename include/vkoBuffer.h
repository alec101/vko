#pragma once


class VkoBuffer;

class VkoBufferManager {
public:



  VkoBuffer *addBuffer();
  chainList list;   // chainList with all the buffers created


  VkoBufferManager();
  ~VkoBufferManager();


private:

  vkObject *_parent;
  friend class vkObject;
  friend class VkoBuffer;
};






///=============------------------------///
// Buffer class ======================== //
///=============------------------------///

class VkoBuffer: public chainData {

public:
  VkBuffer buffer;
  inline operator VkBuffer() { return buffer; }
  VkMemoryRequirements memRequirements;           // populated after build
  uint32_t offset;                                  // memory offset, it's advised to manually populate this, and use it when allocating memory

  // settings - set all these before building

  void setSize(uint32_t in_bytes);                  // [def:0] size, in bytes of the buffer
  void setUsage(VkBufferUsageFlagBits in_usage);  // [def:VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferUsageFlagBits
  void setFlags(VkBufferCreateFlagBits in_flags); // [def:0] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferCreateFlagBits
  void setSharingMode(VkSharingMode in_sharing);  // [def:VK_SHARING_MODE_EXCLUSIVE] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkSharingMode
  void addFamily(uint32_t in_family); // when sharing mode is CONCURRENT, all queueFamilies that can access this buffer must be added.
  void setFamilies(uint32_t in_nrFamilies, const uint32_t *in_families); // same as addFamily, but sets all families in one go


  // build / destroy

  bool build();
  inline bool rebuild() { destroy(); return build(); }
  void destroy();

  
  inline bool isMemoryCompatible(const VkoMemory *in_memory) { return (memRequirements.memoryTypeBits& (1 << in_memory->typeIndex)); }
  inline bool isMemoryCompatibleIndex(uint32_t in_index) { return (memRequirements.memoryTypeBits& (1<< in_index)); }

  // memory asignment IF NEEDED?????/ bindBufferMemory seems straightforward, dono if i'd need another func

  bool allocMem(); // wip




  VkoBuffer();
  ~VkoBuffer();

private:

  VkBufferCreateInfo _createInfo;

  VkoBufferManager *_parent;
  //vkObject *_parent;
  friend class vkObject;
  friend class VkoBufferManager;
};





















