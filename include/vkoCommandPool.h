#pragma once



///==================------------------------///
// CommandPool class ======================== //
///==================------------------------///

class VkoCommandBuffer;

class VkoCommandPool: public chainData {
public:
  VkCommandPool commandPool;
  inline operator VkCommandPool() { return commandPool; }

  // configure the commandPool.
  // <in_queueFamily>: all queues that will be used with this pool must be from this family
  // <in_flags>: [def:VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT & VK_COMMAND_POOL_CREATE_TRANSIENT_BIT]
  void configure(uint32_t in_queueFamily, VkCommandPoolCreateFlags in_flags= ~0);

  struct PNext {
    void *VkCommandPoolCreateInfo;
    void *VkCommandBufferAllocateInfo;
    void delData() { VkCommandPoolCreateInfo= VkCommandBufferAllocateInfo= nullptr; }
  } pNext;


  bool build();
  inline bool rebuild() { destroy(); return build(); }
  void destroy();     // all created vko buffers get dealocated from the pool, but all their settings are intact, so they can be rebuilt, if this pool gets rebuilt

  inline void reset(VkCommandPoolResetFlags in_flags= 0); // { _vko->ResetCommandPool(*_vko, commandPool, in_flags); }

  VkoCommandPool(vkObject *in_parent);
  virtual ~VkoCommandPool();
  void delData();     // all created VkoCommandBuffers get deleted also
  

  // VkoCommandBuffer creation / destruction.

  chainList buffers;  // [VkoCommandBuffer:chainData] list with all allocated buffers from this pool
  VkoCommandBuffer *addCommandBuffer();
  inline void addCustomCommandBuffer(VkoCommandBuffer *p) { buffers.add((chainData *)p); } // alloc your custom derived object and link it here.
  void delCommandBuffer(VkoCommandBuffer *in_buffer);
  

private:
  uint32_t _queueFamily;
  VkCommandPoolCreateFlags _flags;

  vkObject *_vko;
  friend class vkObject;
  friend class VkoCommandBuffer;
};






