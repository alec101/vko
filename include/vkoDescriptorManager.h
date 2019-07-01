#pragma once



///==========================---------------------///
// Descriptor Manager object ===================== //
///==========================---------------------///

class VkoDescriptorManager: public chainData {
public:
  VkDescriptorPool descriptorPool;
  inline operator VkDescriptorPool() { return descriptorPool; }

  VkDescriptorPoolCreateFlags flags; 

  //chainList descriptors;       // [VkoDescriptor: chainData] list with all descriptors
  chainList sets;              // [VkoSet: chainData] list with all sets

  // configuration

  // [def:0] can be VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT, allowing the use of vkFreeDescriptorSets;
  inline void setPoolFlags(VkDescriptorPoolCreateFlags in_flags) { flags= in_flags; }

  // [def:0] set the maximum number of descriptor sets that can be allocated from the pool
  // if left 0, it will automatically count them from the descriptor sets added in this manager/pool, before calling build() func
  inline void setPoolMaxSets(uint32 in_maxSets) { _maxSets= in_maxSets; }

  // manually set the maximum amount of a certain descriptor type, the pool can handle. 
  // if this func is not used, the maximum amounts is auto-calculated from the added descriptors, once calling build() func
  // if this func is called ONCE, then ALL maximum amounts must be set manually by calling this func for all types
  void setPoolMaxDescriptorType(VkDescriptorType in_type, uint32 in_maxDescriptors);



  // adds a descriptor set
  // <in_setNumber>: set index. coresponds to X in a shader sourcecode: " layout(set= X, binding= Y) ... "
  VkoSet *addDescriptorSet(uint32 in_setNumber);       // can be used to manually add an empty VkoSet
  
  // this func is mainly for descriptor push
  //  VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR - specifies that descriptor sets must not be allocated using this layout,
  //  and descriptors are instead pushed by vkCmdPushDescriptorSetKHR
  // In specs, it says there should be only one set with dynamic push, in an array of sets that are to be used
  // <in_set>: index of the set, counted from the first set created with this class
  void setDescriptorSetFlags(uint32 in_set, VkDescriptorSetLayoutCreateFlags in_flags);


  // creates a descriptor (a descriptor can be any kind of buffer, texture, sampler. it's a vague description of all those things)
  // alternatively, you can create the descriptor by calling the same addDescriptor func of the VkoSet class
  // <in_set>:     set index, counted from the first set created with this class
  // <in_binding>: binding number (again, create them in order OR make sure prev number exists OR at least use in_count 0, if you skip it)
  // <in_type>:    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER / VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER / etc https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorType
  // <in_count>:   accessed in a shader as an array, when multiple. Can be 0, so it's reserved, and never accessed
  // <in_stages>:  shader stages that will use this descriptor https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap9.html#VkShaderStageFlagBits
  // <in_imutableSampler>: imutable / constant samplers, but i'd just not change them -.- imhho this ext is extra stuff that could be avoided. i think there's an extension for these
  // returns the created VkoDescriptor object.
  VkoDescriptor *addDescriptor(uint32 in_set, uint32 in_binding, VkDescriptorType in_type, uint32 in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler= null);


  

  // util funcs

  VkoSet *getSet(uint32 index);       // <index>: the set index, counted from the first set created with this object.
  //VkoSet *getDescriptorSet(VkoDescriptor *);
  
  bool build();                       // this will create the pool and all descriptors and their sets that were added
  bool buildSet(uint32 in_setIndex);  // 
  bool buildAllSets();                // builds all added sets.
  void resetPool();                   // frees all sets, destroys all created VkoDescriptors and VkoSets. You can add new descriptors/sets, then use buildAllSets() or buildSet(..) funcs
  void freeSet(uint32 index);         // frees and deletes all data about a specific set. Specs say it's dangerous to use if adding new sets that are not the same/compatible like the one freed. Use resetPool() and re-create the descriptors is safer

  // rebuild will work with currently added VkoDescriptors and sets to recreate the same pool

  bool rebuild() { destroy(); return build(); }
  void destroy();
  VkoDescriptorManager();


private:
  class _DescriptorMax;

  uint32 _maxSets;
  chainList _maxDescriptors;    // [_DescriptorMax: chainData]
  void _computeMaxPoolNumbers();
  _DescriptorMax *_getDescMaxForType(VkDescriptorType in_type);
  _DescriptorMax *_addDescMax(VkDescriptorType in_type);

  // used for manually setting the maximum number of descriptor types that a pool can handle
  class _DescriptorMax: public chainData {
  public:
    VkDescriptorType type;      // type of descriptor
    uint32_t descriptorCount;   // number of descriptors of that type
  };

  vkObject *_parent;
  friend class vkObject;
  friend class VkoSet;
  friend class VkoDescriptor;
};




















