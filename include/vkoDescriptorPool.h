#pragma once

/*
There are 3 ways to configure the descriptor pool:
1. use addDescriptorsFromLayout & addDescriptorsFromLayout2 funcs
2. use addManualDescriptors & setManualPoolMaxSets funcs
3. just populate _createInfo struct, yourself

- It's best to use the first method:
  create the layouts (blueprints) and just specify to VkoDescriptorPool, how many of those sets you're going to use.
  the layouts have to exist in the shader or somewhere, anyway;

*/



class VkoDescriptorPool;

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



  // Enlarges the pool, so one or more sets with the specified layout can be allocated from it
  // <in_layout>: specify what set layout the pool should make sure can be allocated
  // <in_nrSets>: specify how many of those sets can be alocated from this pool
  // pool max sets is auto-updated
  void addDescriptorsFromLayout(VkoDescriptorSetLayout *in_layout, uint32_t in_nrSets);

  // Enlarges the pool, so one or more sets with the specified layout can be allocated from it;
  // same as addDescriptorsFromLayout(..) but you specify a shader and a set index from that shader
  // <in_shader>: specify the shader
  // <in_setIndex>: specify the shader's set index
  // <in_nrSetsToAdd>: specify how many of that set you intend to allocate from the pool
  // pool max sets is auto-updated
  inline void addDescriptorsFromLayout2(VkoShader *in_shader, uint32_t in_setIndex, uint32_t in_nrSetsToAdd) { return addDescriptorsFromLayout(in_shader->descSet[in_setIndex], in_nrSetsToAdd); }



  // Manual add descriptors, you must specify max sets too, if you do.
  // you can always just populate _createInfo struct, manually, as another option to configure the pool

  // manually set the maximum amount of a certain descriptor type, the pool can handle. 
  // if you use this func, you MUST use setManualPoolMaxSets() too
  void addManualDescriptors(VkDescriptorType in_type, uint32_t in_maxDescriptors);

  // [def:0] set the maximum number of descriptor sets that can be allocated from the pool
  // if left 0, it will automatically count them from the descriptor sets added in this pool, before calling build() func
  inline void setManualPoolMaxSets(uint32_t in_maxSets) { _createInfo.maxSets= in_maxSets; }

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

  inline VkoDescriptorPool(vkObject *in_parent): descriptorPool(0), _vko(in_parent) { delData(); }
  inline virtual ~VkoDescriptorPool() { destroy(); delData(); }
  void delData();

private:

  VkDescriptorPoolCreateInfo _createInfo;

  void _addDescriptorTypeToList(VkDescriptorType in_type, uint32_t in_nr);

  vkObject *_vko;
  friend class vkObject;
  friend class VkoSet;
};













