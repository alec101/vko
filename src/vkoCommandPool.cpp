#include "vkObject.h"




///===================------------------///
// COMMANDPOOL object ================== //
///===================------------------///

VkoCommandPool::VkoCommandPool(): commandPool(null), _parent(null) {
  _flags= 0;
  _queueFamily= ~0;
}



void VkoCommandPool::destroy() {
  if(_parent->device== null) return;
  if(commandPool) {
    _parent->vk->DestroyCommandPool(_parent->device, commandPool, _parent->memCallback);
    commandPool= null;
  }
}


void VkoCommandPool::configure(uint32 in_queueFamily, VkCommandPoolCreateFlags in_flags) {
  _flags= in_flags;
  _queueFamily= in_queueFamily;
  // defaul flags
  if(_flags== 0) _flags= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT & VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
}


bool VkoCommandPool::build() {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap5.html#commandbuffers-pools

  /// VK_COMMAND_POOL_CREATE_TRANSIENT_BIT specifies that command buffers allocated from the pool will be short-lived,
  ///    meaning that they will be reset or freed in a relatively short timeframe. This flag may be used by the implementation
  ///    to control memory allocation behavior within the pool.
  /// VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT allows any command buffer allocated from a pool to be individually reset to the initial state;
  ///    either by calling vkResetCommandBuffer, or via the implicit reset when calling vkBeginCommandBuffer. If this flag
  ///    is not set on a pool, then vkResetCommandBuffer must not be called for any command buffer allocated from that pool.
  /// VK_COMMAND_POOL_CREATE_PROTECTED_BIT specifies that command buffers allocated from the pool are protected command buffers.
  ///    If the protected memory feature is not enabled, the VK_COMMAND_POOL_CREATE_PROTECTED_BIT bit of flags must not be set.

  bool ret= false;
  VkCommandPoolCreateInfo cpInfo; // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap5.html#VkCommandPoolCreateInfo

  cpInfo.sType= VK_STRUCTURE_TYPE_COMMAND_POOL_CREATE_INFO;
  cpInfo.pNext= null;
  cpInfo.flags= _flags;
  cpInfo.queueFamilyIndex= _queueFamily;
  
  // create the pool
  VkResult res= _parent->vk->CreateCommandPool(_parent->device, &cpInfo, _parent->memCallback, &commandPool);

  // error
  if(res!= VK_SUCCESS) {
    error.detail("Vulkan command pool creation failed", __FUNCTION__, __LINE__);
    error.vkPrint(res);
    goto Exit;
  }

  ret= true; // success

Exit:
  return ret;
}




VkCommandBuffer VkoCommandPool::addCommandBuffer(VkCommandBufferLevel in_level) {

  VkCommandBufferAllocateInfo cbInfo;
  VkCommandBuffer ret;

  cbInfo.sType= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cbInfo.pNext= null;
  cbInfo.commandBufferCount= 1;
  cbInfo.commandPool= commandPool;
  cbInfo.level= in_level;

  _parent->vk->AllocateCommandBuffers(*_parent, &cbInfo, &ret);
  return ret;
}



void VkoCommandPool::addCommandBuffers(uint32 in_nr, VkCommandBufferLevel in_level, VkCommandBuffer *out_buffers) {
  VkCommandBufferAllocateInfo cbInfo;

  cbInfo.sType= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
  cbInfo.pNext= null;
  cbInfo.commandBufferCount= in_nr;
  cbInfo.commandPool= commandPool;
  cbInfo.level= in_level;

  _parent->vk->AllocateCommandBuffers(*_parent, &cbInfo, out_buffers);
}



void VkoCommandPool::freeCommandBuffer(VkCommandBuffer in_buffer) {
  _parent->vk->FreeCommandBuffers(*_parent, commandPool, 1, &in_buffer);
}


void VkoCommandPool::freeCommandBuffers(uint32 in_nr, VkCommandBuffer *in_buffer) {
  _parent->vk->FreeCommandBuffers(*_parent, commandPool, in_nr, in_buffer);
}






























