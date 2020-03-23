#pragma once

///====================------------------------///
// CommandBuffer class ======================== //
///====================------------------------///

class VkoSemaphore;
class vkObject;

class VkoCommandBuffer: public chainData {
public:

  inline operator VkCommandBuffer() { return buffer; }
  VkCommandBuffer buffer;     // [def:0] vulkan buffer handle, created on build()
  VkoCommandPool *pool;       // parent pool that was alocated from

  // syncronization

  uint32_t nrWaitSemaphores;
  uint32_t nrSignalSemaphores;
  VkoSemaphore **waitSemaphores;   // [def:null] list with all wait semaphores
  VkoSemaphore **signalSemaphores; // [def:null] list with all signal semaphores
  VkFence fence;                   // [def:0] the fence from vkQueueSubmit

  //chainList waitSemaphores;   // chainlist with all wait semaphores
  //chainList signalSemaphores; // chainList with all signal semaphores
  //VkoSemaphore **waitSemaphores;    // list with all wait semaphores
  //VkoSemaphore **signalSemaphores;  // list with all signal semaphores

  // configuration

  // Set buffer's level [def:VK_COMMAND_BUFFER_LEVEL_PRIMARY]
  // https://www.khronos.org/registry/vulkan/specs/1.1/html/chap5.html#VkCommandBufferLevel
  inline void setLevel(VkCommandBufferLevel in_level) { _level= in_level; }

  // Set buffer's usage flags on submit [def:VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT]
  // usage flags: https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap5.html#VkCommandBufferUsageFlagBits
  inline void setUsage(VkCommandBufferUsageFlags in_flags) { _beginInfo.flags= in_flags; }
   
  // Adds a custom pre-created wait semaphore and specify what pipeline stages are afected by it
  void addCustomWaitSemaphore(VkoSemaphore *in_s, VkPipelineStageFlags in_stages= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT);

  // Creates and adds a wait semaphore. You can specify what pipeline stages are affected by it
  VkoSemaphore *addWaitSemaphore(VkPipelineStageFlags in_stages= VK_PIPELINE_STAGE_TOP_OF_PIPE_BIT);

  // Adds a custom pre-created signal semaphore. It's signaled when job is done
  void addCustomSignalSemaphore(VkoSemaphore *in_s);

  // Creates and adds a signal semaphore. It's signaled when job is done
  VkoSemaphore *addSignalSemaphore();

  inline void setFence(VkFence in_f) { fence= in_f; }

  // if this is a secondary buffer, the inheritance should be filled in
  // https://www.khronos.org/registry/vulkan/specs/1.1/html/chap5.html#VkCommandBufferBeginInfo
  void setInheritance(VkRenderPass renderPass,                           // [def:null]
                      uint32_t subpass,                                  // [def:0]
                      VkFramebuffer framebuffer,                         // [def:null]
                      VkBool32 occlusionQueryEnable,                     // [def:false]
                      VkQueryControlFlags queryFlags,                    // [def:0]
                      VkQueryPipelineStatisticFlags pipelineStatistics); // [def:0]

  struct PNext {
    void *VkCommandBufferAllocateInfo;
    void *VkCommandBufferBeginInfo;
    void *VkSubmitInfo;
    void *VkCommandBufferInheritanceInfo;
    void delData() { VkCommandBufferAllocateInfo= VkCommandBufferBeginInfo= VkSubmitInfo= VkCommandBufferInheritanceInfo= nullptr; }
  } pNext;

  // main usage funs

  void alloc();
  void free();
  inline void build()   { alloc(); }  // allocates memory;
  inline void destroy() { free(); }   // frees memory

  inline void startRecording()         { _vko->BeginCommandBuffer(buffer, &_beginInfo); }       // start recording of the command buffer;
  inline void endRecording()           { _vko->EndCommandBuffer(buffer); }                      // end recording of the buffer
  inline void submit(VkQueue in_queue) { _vko->QueueSubmit(in_queue, 1, &_submitInfo, fence); } // queue submit the buffer, with configured semaphores, usage and such

  inline void reset(VkCommandBufferResetFlags in_flags= 0) { _vko->ResetCommandBuffer(buffer, in_flags); } // reset flags: https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap5.html#VkCommandBufferResetFlagBits

  // constructor / destructor

  VkoCommandBuffer(VkoCommandPool *in_pool);
  virtual ~VkoCommandBuffer();
  void delData();

private:
  vkObject *_vko;

  VkCommandBufferLevel _level;
  VkCommandBufferBeginInfo       _beginInfo;
  VkSubmitInfo                   _submitInfo;
  VkCommandBufferInheritanceInfo _inheritanceInfo;
  
  friend class VkoCommandPool;
};










