#pragma once

class VkoDescriptorPool;

class VkoSet: public chainData {
public:
  
  VkDescriptorSet set;                 // vulkan descriptor set - populated after calling any build func
  VkoDescriptorSetLayout *layout;      // vulkan set layout
  VkoDescriptorPool *parent;           // parent pool of this set

  struct PNext {
    void *VkDescriptorSetAllocateInfo;
    void delData() { VkDescriptorSetAllocateInfo= nullptr; }
  } pNext;

  //VkDescriptorSet and VkDescriptorSetLayout are defined differently on 32/64 ... lovely...
  //inline operator VkDescriptorSet() { return set; }
  //inline operator VkDescriptorSetLayout() { return layout; }

  bool alloc();
  void free();

  inline bool build() { return alloc(); }
  inline void destroy() { free(); }
  inline bool rebuild() { destroy(); return rebuild(); }

  inline VkoSet(VkoDescriptorPool *in_parent): parent(in_parent), set(0) { delData(); }
  inline ~VkoSet() { free(); }
  inline void delData() { layout= nullptr; pNext.delData(); }
};






