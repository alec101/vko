#pragma once

class VkoSet;


// DESCRIPTOR POOL class
///=====================

class VkoDescriptorPool: public chainData {
public:

  VkDescriptorPool descriptorPool;
  inline operator VkDescriptorPool() { return descriptorPool; }

  chainList sets;              // [VkoSet: chainData] list with all managed VkoSets created from this pool

  // configuration

  // [def:0] can be VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT, allowing the use of vkFreeDescriptorSets;
  //         a pool without this flag up, will reset fast, and work faster, in general.
  inline void setPoolFlags(VkDescriptorPoolCreateFlags in_flags) { _createInfo.flags= in_flags; }

  // [def:0] set the maximum number of descriptor sets that can be allocated from the pool
  // if left 0, it will automatically count them from the descriptor sets added in this pool, before calling build() func
  inline void setPoolMaxSets(uint32_t in_maxSets) { _createInfo.maxSets= in_maxSets; }


  // manually set the maximum amount of a certain descriptor type, the pool can handle. 
  // if this func is not used, the maximum amounts is auto-calculated from the added VkoSets;
  void addDescriptors(VkDescriptorType in_type, uint32_t in_maxDescriptors);

  // Enlarges the pool, so one or more sets with the specified layout can be allocated from it
  // <in_layout>: specify what set layout the pool should make sure can be allocated
  // <in_nrSets>: specify how many of those sets can be alocated from this pool
  void addDescriptorsFromLayout(VkoDescriptorSetLayout *in_layout, uint32_t in_nrSets);

  // Enlarges the pool, so one or more sets with the specified layout can be allocated from it;
  // same as addDescriptorsFromLayout(..) but you specify a shader and a set index from that shader
  // <in_shader>: specify the shader
  // <in_setIndex>: specify the shader's set index
  // <in_nrSetsToAdd>: specify how many of that set you intend to allocate from the pool
  inline void addDescriptorsFromLayout2(VkoShader *in_shader, uint32_t in_setIndex, uint32_t in_nrSetsToAdd) { return addDescriptorsFromLayout(in_shader->descSet[in_setIndex], in_nrSetsToAdd); }

  struct PNext {
    void *VkDescriptorPoolCreateInfo;
    void delData() { VkDescriptorPoolCreateInfo= nullptr; }
  } pNext;


  // alloc funcs


  // this func should be used to allocate a big array of non-managed VkDescriptorSets, from this pool
  // if you wish to allocate from an array of different layouts, just use the normal vulkan func
  void allocateSets(VkDescriptorSet *out_sets, uint32_t in_nrSets, VkoDescriptorSetLayout *in_layout, void *pNext= nullptr);

  // creates and allocates a managed VkoSet class, with it's own VkDescriptorSet
  // best used for single descriptor sets, that you want to manage better
  VkoSet *allocVkoSet(VkoDescriptorSetLayout *in_layout, void *pNext= nullptr);


  // free funcs

  void freeSets(VkDescriptorSet *out_sets, uint32_t in_nrSets);
  inline void freeVkoSet(VkoSet *out_set) { out_set->free(); }


  void resetPool();

  // build / destroy / constructor / destructor

  bool build();
  void destroy();
  //bool rebuild() { destroy(); return rebuild(); }

  inline VkoDescriptorPool(vkObject *in_parent): _vko(in_parent), descriptorPool(0) { delData(); }
  inline virtual ~VkoDescriptorPool() { destroy(); delData(); }
  void delData();

private:

  VkDescriptorPoolCreateInfo _createInfo;

  void _addDescriptorTypeToList(VkDescriptorType in_type, uint32_t in_nr);

  vkObject *_vko;
  friend class vkObject;
  friend class VkoSet;
};





// DESCRIPTOR SET class
///====================

class VkoSet: public chainData {
public:
  
  VkoDescriptorPool *pool;             // parent pool of this set
  VkDescriptorSet set;                 // vulkan descriptor set
  VkoDescriptorSetLayout *layout;      // vulkan set layout

  struct PNext {
    void *VkDescriptorSetAllocateInfo;
    void delData() { VkDescriptorSetAllocateInfo= nullptr; }
  } pNext;

  bool alloc();
  void free();

  inline VkoSet(VkoDescriptorPool *in_parent): pool(in_parent), set(0), layout(nullptr) { pNext.delData(); }
};









