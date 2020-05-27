#pragma once

class VkoDynamicSetSegment;


// VkoDynamicSet
///=============
struct VkoDynamicSet: public chainData {
  VkDescriptorSet set;
  VkoDynamicSetSegment *segment;       // segment this set is part of; a segment has the VkDescriptorSet pool inside it
  //VkoDescriptorSetLayout *layout;
  //inline VkoDescriptorSetLayout *getLayout() { return segment-> ;} THIS CAN HAPPEN WITH A POINTER IN THE SEGMENT
  inline VkDescriptorPool getPool() { return segment->pool; }
};





///=======================///
// VkoDynamicSetPool class //
///=======================///

class VkoDynamicSetPool: public chainData {
public:

  VkoDescriptorSetLayout *layout;   // the layout all sets will be based on
  uint32_t poolSize;                // how many sets one pool should handle

  // configuration:
  
  // <in_layout>: the set's layout that will be used;
  // <in_number>: set the number of sets you _think_ you are going to use;
  //              if this number is exceeded, another pool will be created;
  void configure(VkoDescriptorSetLayout *in_layout, uint32_t in_nr);

  struct PNext {
    void *VkDescriptorPoolCreateInfo;
    void *VkDescriptorSetAllocateInfo;
    void delData() { VkDescriptorPoolCreateInfo= VkDescriptorSetAllocateInfo= nullptr; }
  } pNext;


  // add / delete sets

  VkoDynamicSet *addSet();
  void delSet(VkoDynamicSet *);


  // class handling

  void trimPools();              // WIP <<< TRIM THE SEGMENTS, COMPACT THEM, DELETE EMPTY SEGMENTS

  bool build();
  void destroy();

  VkoDynamicSetPool(vkObject *in_parent);
  ~VkoDynamicSetPool();

private:


  // list with all added descriptor pools; there is ALWAYS one;
  // this list will grow if the user requests a set above the limits imposed
  // in theory, it's best to be only one pool - if the user choosed the pool size well
  chainList _segments;

  uint32_t _nrDescriptorTypes;               // the size of _descriptorType; it's basically VkDescriptorPoolCreateInfo::poolSizeCount
  VkDescriptorPoolSize *_descriptorType;    // how much of every descriptor in the pool; VkDescriptorPoolCreateInfo::pPoolSizes is static/fixed, and created on class configuration()
  
  VkoDynamicSetSegment *_addSegment();
  void _delSegment(VkoDynamicSetSegment *);

  vkObject *_vko;
};




// VkoDynamicSetSegment
///====================


// each segment has a VkDescriptorPool
class VkoDynamicSetSegment: public chainData {
public:
  VkDescriptorPool pool;            // the Vulkan descriptor pool;
  chainList sets;                   // list with all the sets
  //VkoDynamicSet *sets;              // array with all the sets

  uint32_t freeSpcPeak;             // free space amount; if reaches 0, the pool is full
  VkDescriptorSet *freeSpc;         // list will all free set slots in pool
};





