#pragma once


class VkoDescriptorPool: public chainData {
public:

  VkDescriptorPool descriptorPool;
  inline operator VkDescriptorPool() { return descriptorPool; }

  chainList sets;              // [VkoSet: chainData] list with all sets created from this pool

  // configuration

  // [def:0] can be VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT, allowing the use of vkFreeDescriptorSets;
  inline void setPoolFlags(VkDescriptorPoolCreateFlags in_flags) { _flags= in_flags; }

  // [def:0] set the maximum number of descriptor sets that can be allocated from the pool
  // if left 0, it will automatically count them from the descriptor sets added in this manager/pool, before calling build() func
  inline void setPoolMaxSets(uint32_t in_maxSets) { _maxSets= in_maxSets; }

  // manually set the maximum amount of a certain descriptor type, the pool can handle. 
  // if this func is not used, the maximum amounts is auto-calculated from the added sets, when calling build() func;
  // if this func is called ONCE, then ALL maximum amounts must be set manually by calling this func for all types
  void setPoolMaxDescriptorType(VkDescriptorType in_type, uint32_t in_maxDescriptors);

  struct PNext {
    void *VkDescriptorPoolCreateInfo;
    void delData() { VkDescriptorPoolCreateInfo= nullptr; }
  } pNext;

  // funcs

  VkoSet *addDescriptorSet(VkoDescriptorSetLayout *in_layout);

  // adds a set, and takes the layout from a specific shader's set layout index
  inline VkoSet *addDescriptorSet2(VkoShader *in_shader, uint32_t in_setIndex) { return addDescriptorSet(in_shader->descSet[in_setIndex]); }

  void addCustomDescriptorSet(VkoSet *in_set, VkoDescriptorSetLayout *p) { sets.add(in_set); in_set->layout= p; }
  inline void addCustomDescriptorSet2(VkoSet *in_set, VkoShader *in_shader, uint32_t in_setIndex) { return addCustomDescriptorSet(in_set, in_shader->descSet[in_setIndex]); }

  inline void freeSet(VkoSet *in_s) { in_s->free(); }
  inline bool allocSet(VkoSet *in_s) { return in_s->alloc(); }
  void resetPool();

  // build / destroy / constructor / destructor

  bool build();
  void destroy();
  bool rebuild() { destroy(); return rebuild(); }

  inline VkoDescriptorPool(vkObject *in_parent): _vko(in_parent), descriptorPool(0) { delData(); }
  inline virtual ~VkoDescriptorPool() { destroy(); delData(); }
  void delData();

private:
  VkDescriptorPoolCreateFlags _flags;
  uint32_t _maxSets;
  chainList _maxDescriptors;    // [_DescriptorMax: chainData]

  // used for manually setting the maximum number of descriptor types that a pool can handle
  class _DescriptorMax: public chainData {
  public:
    VkDescriptorType type;      // type of descriptor
    uint32_t descriptorCount;   // number of descriptors of that type
  };
  _DescriptorMax *_getDescMaxForType(VkDescriptorType in_type);
  _DescriptorMax *_addDescMax(VkDescriptorType in_type);
  void _computeMaxPoolNumbers();


  vkObject *_vko;
  friend class vkObject;
  friend class VkoSet;
};









