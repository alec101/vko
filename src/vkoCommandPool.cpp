#include "vko/include/vkObject.h"


///===================------------------///
// COMMANDPOOL object ================== //
///===================------------------///


// construction / destruction
///--------------------------///

VkoCommandPool::VkoCommandPool(vkObject *in_parent): _vko(in_parent) {
  commandPool= 0;

  delData();
}

VkoCommandPool::~VkoCommandPool() {
  destroy();
  delData();
}

void VkoCommandPool::delData() {
  _flags= VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT& VK_COMMAND_POOL_CREATE_TRANSIENT_BIT;
  _queueFamily= ~0;

  pNext.delData();

  // delete all created command buffers
  while(buffers.first)
    delCommandBuffer((VkoCommandBuffer *)buffers.first);
}

void VkoCommandPool::destroy() {
  if(commandPool) {
    if(_vko->device)
      _vko->DestroyCommandPool(_vko->device, commandPool, _vko->memCallback);
    commandPool= 0;
  }

  // all buffers VkCommandBuffer get destroyed, therefore setting them to null
  for(VkoCommandBuffer *p= (VkoCommandBuffer *)buffers.first; p; p= (VkoCommandBuffer *)p->next)
    p->buffer= 0;
}




// CONFIGURATION //
///-------------///

void VkoCommandPool::configure(uint32_t in_queueFamily, VkCommandPoolCreateFlags in_flags) {
  _queueFamily= in_queueFamily;
  if(in_flags!= ~0) _flags= in_flags;
}


// funcs

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
    cpInfo.pNext= pNext.VkCommandPoolCreateInfo;
    cpInfo.flags= _flags;
    cpInfo.queueFamilyIndex= _queueFamily;
  if(!_vko->errorCheck(_vko->CreateCommandPool(*_vko, &cpInfo, *_vko, &commandPool), __FUNCTION__": Vulkan command pool creation failed"))
    goto Exit;

  // if this is a rebuild, there are already created VkoCommandBuffers
  // therefore they need to be re-allocated/built from this pool
  for(VkoCommandBuffer *p= (VkoCommandBuffer *)buffers.first; p; p= (VkoCommandBuffer *)p->next)
    p->build();

  ret= true; // success

Exit:
  return ret;
}



// command buffer add/del

VkoCommandBuffer *VkoCommandPool::addCommandBuffer() {
  VkoCommandBuffer *p= new VkoCommandBuffer(this);
  buffers.add(p);
  return p;
}


void VkoCommandPool::delCommandBuffer(VkoCommandBuffer *in_b) {
  buffers.del(in_b);
}







