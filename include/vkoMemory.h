#pragma once

// vulkan memory object

class VkoMemory: public chainData {
public:
  VkDeviceMemory memory;
  inline operator VkDeviceMemory() { return memory; }

  VkDeviceSize size;                // size, in bytes of this memory block
  uint32_t typeIndex;               // index of this type, in the vulkan physical device memory list
  VkMemoryPropertyFlags typeFlags;  // memory flags

  // settings
  

  // this function will search for the required memory, then the prefered flags it should have, or, if specified, the required index
  // if succeeds, this->typeIndex will be populated with the found index, this->typeFlags will be populated with the found flags
  // <in_size>: size, in bytes of the block of memory to be allocated
  // <in_required>: memory property flags that the memory MUST have
  // <in_preffered>: extra memory flags, that the memory idealy should have, but NOT required
  // <in_typeBits>: [def:~0] specific memory index. if left ~0, only the flags will be used in search
  // return value: true - the type of memory requested exists on the system
  //               false- the type of memory requested does not exist on the system
  //bool configure(VkDeviceSize in_size, VkMemoryPropertyFlagBits in_required, VkMemoryPropertyFlagBits in_prefered, uint32_t in_typeBits= ~0u);
  bool configure(VkDeviceSize in_size, VkMemoryPropertyFlags in_required, VkMemoryPropertyFlags in_prefered, uint32_t in_typeBits= ~0u);

  // inport / export / extensions (vulkan 1.1, KHR only)
  
  void addVkExportMemoryAllocateInfo(VkExternalMemoryHandleTypeFlags handleTypes); // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkExportMemoryAllocateInfo
  void addVkExportMemoryWin32HandleInfoKHR(const SECURITY_ATTRIBUTES *pAttributes, DWORD dwAccess, LPCWSTR name); // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkExportMemoryWin32HandleInfoKHR
  void addVkImportMemoryFdInfoKHR(VkExternalMemoryHandleTypeFlagBits handleType, int fd); // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkImportMemoryFdInfoKHR
  void addVkImportMemoryWin32HandleInfoKHR(VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, LPCWSTR name); // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkImportMemoryWin32HandleInfoKHR
  void addVkMemoryAllocateFlagsInfo(VkMemoryAllocateFlags flags, uint32_t deviceMask); // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryAllocateFlagsInfo
  void addVkMemoryDedicatedAllocateInfo(VkImage image, VkBuffer buffer); // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryDedicatedAllocateInfo

  // or use this for your custom pNext in VkMemoryAllocateInfo
  struct PNext {
    void *VkMemoryAllocateInfo;
    void delData() { VkMemoryAllocateInfo= nullptr; }
  } pNext;


  // build / destroy

  bool build();                       // build the memory block - allocates the desired memory type. returns true if succeeded.
  void destroy();
  inline bool rebuild() { destroy(); return build(); }

  // constructors / destructors

  VkoMemory(vkObject *);
  virtual ~VkoMemory();
  void delData();                     // clears all data

private:

  VkExportMemoryAllocateInfo       *_exportInfo;
  VkExportMemoryWin32HandleInfoKHR *_exportWin32;
  VkImportMemoryFdInfoKHR          *_importFd;
  VkImportMemoryWin32HandleInfoKHR *_importWin32;
  VkMemoryAllocateFlagsInfo        *_flagsInfo;
  VkMemoryDedicatedAllocateInfo    *_dedicatedInfo;

  vkObject *_vko;
  friend class vkObject;
};

























