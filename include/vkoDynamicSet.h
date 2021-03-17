#pragma once

/*
VkoDynamicSetPool class is meant to be a true pool, that expands and contracts (it has trimming capabilities)

The drawback is, that ONLY ONE TYPE of descriptor set can be created from it - ONE LAYOUT, but you can add/delete any number of those sets;

  -you configure it, with only one function, specifying how many sets you _think_ you will use, so you just set how big one segment of the pool is
  -you can add and delete VkoDynamicSets at free will, there will be a Vulkan memory allocation ONLY if space runs out in the segments of the pool
  -you can trim the pool, compacting all segments and deleting empty segments, ofc the operation can be costly;


  In theory, no memory allocation could happen on add/delete, if all sets are pre-created, but this will require more memory for the VkoDynamicSets
  I have choosen the other method, to make a small memory alloc for the VkoDynamicSet struct;
  The reason is, that these sets will be created when a new resource will created, so alot of memory management will happen for the textures/buffers anyway

  It's highly possible i will create the first method too, with zero memory allocations on add/delete (only when the segments are full, another alloc will happen)
*/


//class VkoDynamicSetSegment;

// VkoDynamicSetSegment
///====================


// each segment has a VkDescriptorPool
class VkoDynamicSetSegment: public chainData {
public:
  VkDescriptorPool pool;            // the Vulkan descriptor pool;
  chainList sets;                   // list with all the sets

  uint32_t freeSpcPeak;             // free space amount; if reaches 0, the pool is full
  VkDescriptorSet *freeSpc;         // list will all free set slots in pool
};


// VkoDynamicSet
///=============
struct VkoDynamicSet: public chainData {
  VkDescriptorSet set;
  VkoDynamicSetSegment *segment;       // segment this set is part of; a segment has the VkDescriptorSet pool inside it
  
  //inline VkoDescriptorSetLayout *getLayout() { return segment-> ;} THIS CAN HAPPEN WITH A POINTER IN THE SEGMENT
  inline VkDescriptorPool getPool() { return segment->pool; }
};





///=======================///
// VkoDynamicSetPool class //
///=======================///

class VkoDynamicSetPool: public chainData {
public:

  VkoDescriptorSetLayout *layout;   // the layout all sets will be based on
  uint32_t poolSize;                // how many sets one pool/segment will handle

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

  virtual VkoDynamicSet *addSet();
  void addCustomSet (VkoDynamicSet *);  // alloc mem first, then call this func
  void delSet(VkoDynamicSet *);

  // class handling

  void trimPools();              // COSTLY OPERATION- compacts the pool, then empties the empty segments

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










