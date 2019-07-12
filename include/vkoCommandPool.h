#pragma once



///==================------------------------///
// CommandPool class ======================== //
///==================------------------------///

class VkoCommandPool: public chainData {



public:
  VkCommandPool commandPool;
  inline operator VkCommandPool() { return commandPool; }


  // configure the commandPool.
  // <in_queueFamily>: all queues that will be used with this pool must be from this family
  // <in_flags>: [def:0:VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT & VK_COMMAND_POOL_CREATE_TRANSIENT_BIT]
  void configure(uint32_t in_queueFamily, VkCommandPoolCreateFlags in_flags= 0);

  bool build();
  inline bool rebuild() { destroy(); return build(); }
  void destroy();
  VkoCommandPool();

  
  // buffer funcs. these are not really required but will automatically use the created pool to alloc new buffers and such

  VkCommandBuffer addCommandBuffer(VkCommandBufferLevel in_level);
  void addCommandBuffers(uint32_t in_nr, VkCommandBufferLevel in_level, VkCommandBuffer *out_buffers);

  void freeCommandBuffer(VkCommandBuffer in_buffer);                    // freeing is not required if the pool is destroyed
  void freeCommandBuffers(uint32_t in_nr, VkCommandBuffer *in_buffer);    // freeing is not required if the pool is destroyed

private:
  uint32_t _queueFamily;
  VkCommandPoolCreateFlags _flags;

  vkObject *_parent;
  friend class vkObject;
};





















