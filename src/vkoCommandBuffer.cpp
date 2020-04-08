#include "vko/include/vkObject.h"

///=======================///
// VkoCommandBuffer object //
///=======================///


// constructor / destructor =====================---------------------------

VkoCommandBuffer::VkoCommandBuffer(VkoCommandPool *in_pool): pool(in_pool), _vko(in_pool->_vko) {
  buffer= 0;
  
  waitSemaphores=   nullptr; // INIT 1
  signalSemaphores= nullptr; // INIT 2
  _submitInfo.pWaitSemaphores=   nullptr; // INIT 3
  _submitInfo.pWaitDstStageMask= nullptr; // INIT 4
  _submitInfo.pSignalSemaphores= nullptr; // INIT 5

  delData();
}

VkoCommandBuffer::~VkoCommandBuffer() {
  destroy();
  delData();
}


void VkoCommandBuffer::delData() {
  // deallocs
  if(waitSemaphores)   { delete[] waitSemaphores;   waitSemaphores=   nullptr; } // DEALLOC 1
  if(signalSemaphores) { delete[] signalSemaphores; signalSemaphores= nullptr; } // DEALLOC 2
  if(_submitInfo.pWaitSemaphores)   { delete[] _submitInfo.pWaitSemaphores;   _submitInfo.pWaitSemaphores=   nullptr; } // DEALLOC 3
  if(_submitInfo.pWaitDstStageMask) { delete[] _submitInfo.pWaitDstStageMask; _submitInfo.pWaitDstStageMask= nullptr; } // DEALLOC 4
  if(_submitInfo.pSignalSemaphores) { delete[] _submitInfo.pSignalSemaphores; _submitInfo.pSignalSemaphores= nullptr; } // DEALLOC 5

  pNext.delData();

  // default values
  fence= 0;

  nrWaitSemaphores= 0;
  nrSignalSemaphores= 0;

  _level= VK_COMMAND_BUFFER_LEVEL_PRIMARY;

  _beginInfo.sType= VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO;
  _beginInfo.pNext= nullptr;
  _beginInfo.flags= VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT;
  _beginInfo.pInheritanceInfo= &_inheritanceInfo;
  
  _inheritanceInfo.sType= VK_STRUCTURE_TYPE_COMMAND_BUFFER_INHERITANCE_INFO;
  _inheritanceInfo.pNext= nullptr;
  _inheritanceInfo.renderPass= VK_NULL_HANDLE,
  _inheritanceInfo.subpass= 0,
  _inheritanceInfo.framebuffer= VK_NULL_HANDLE,
  _inheritanceInfo.occlusionQueryEnable= false,
  _inheritanceInfo.queryFlags= 0,
  _inheritanceInfo.pipelineStatistics= 0;

  _submitInfo.sType= VK_STRUCTURE_TYPE_SUBMIT_INFO;
  _submitInfo.pNext= nullptr;
  _submitInfo.waitSemaphoreCount= 0;
  _submitInfo.signalSemaphoreCount= 0;
  _submitInfo.commandBufferCount= 1;
  _submitInfo.pCommandBuffers= &buffer;
}

void VkoCommandBuffer::free() {
  if(buffer) {
    if(_vko->device)
      _vko->FreeCommandBuffers(*_vko, *pool, 1, &buffer);
    buffer= 0;
  }
}



// configure funcs =====================---------------------------



// add a wait semaphore and what pipeline stages should wait for it [def:all].
void VkoCommandBuffer::addCustomWaitSemaphore(VkoSemaphore *in_s, VkPipelineStageFlags in_stages) {
  VkoSemaphore **oldList= waitSemaphores;
  const VkPipelineStageFlags *oldStages= _submitInfo.pWaitDstStageMask;

  if(waitSemaphores)                { delete[] waitSemaphores;                waitSemaphores=                nullptr; }
  if(_submitInfo.pWaitSemaphores)   { delete[] _submitInfo.pWaitSemaphores;   _submitInfo.pWaitSemaphores=   nullptr; }
  if(_submitInfo.pWaitDstStageMask) { delete[] _submitInfo.pWaitDstStageMask; _submitInfo.pWaitDstStageMask= nullptr; }

  nrWaitSemaphores++, _submitInfo.waitSemaphoreCount++;

  waitSemaphores=                new VkoSemaphore *[nrWaitSemaphores];
  _submitInfo.pWaitSemaphores=   new VkSemaphore [nrWaitSemaphores];
  _submitInfo.pWaitDstStageMask= new VkPipelineStageFlags[nrWaitSemaphores];
  
  // copy from old list
  for(uint32_t a= 0; a< nrWaitSemaphores- 1; a++)
    waitSemaphores[a]= oldList[a],
    ((VkSemaphore *)_submitInfo.pWaitSemaphores)[a]= waitSemaphores[a]->semaphore,
    ((VkPipelineStageFlags *)_submitInfo.pWaitDstStageMask)[a]= oldStages[a];

  // add new member
                                           waitSemaphores[nrWaitSemaphores- 1]= in_s;
             ((VkSemaphore *)_submitInfo.pWaitSemaphores)[nrWaitSemaphores- 1]= in_s->semaphore;
  ((VkPipelineStageFlags *)_submitInfo.pWaitDstStageMask)[nrWaitSemaphores- 1]= in_stages;

  if(oldList) delete[] oldList;
  if(oldStages) delete[] oldStages;
}


VkoSemaphore *VkoCommandBuffer::addWaitSemaphore(VkPipelineStageFlags in_stages) {
  VkoSemaphore *p= _vko->objects.addSemaphore();
  p->stages= in_stages;
  p->build();

  addCustomWaitSemaphore(p, in_stages);

  return p;
}


// add a signal semaphore. this is signaled when job is done
void VkoCommandBuffer::addCustomSignalSemaphore(VkoSemaphore *in_s) {
  VkoSemaphore **oldList= signalSemaphores;
  if(signalSemaphores) { delete[] signalSemaphores; signalSemaphores= nullptr; }
  if(_submitInfo.pSignalSemaphores) { delete[] _submitInfo.pSignalSemaphores; _submitInfo.pSignalSemaphores= nullptr; }

  nrSignalSemaphores++, _submitInfo.signalSemaphoreCount++;

  signalSemaphores= new VkoSemaphore *[nrSignalSemaphores];
  _submitInfo.pSignalSemaphores= new VkSemaphore[nrSignalSemaphores];

  // copy from old list
  for(uint32_t a= 0; a< nrSignalSemaphores- 1; a++)
    signalSemaphores[a]= oldList[a],
    ((VkSemaphore *)_submitInfo.pSignalSemaphores)[a]= oldList[a]->semaphore;

  // add new member
  signalSemaphores[nrSignalSemaphores- 1]= in_s;
  ((VkSemaphore *)_submitInfo.pSignalSemaphores)[nrSignalSemaphores- 1]= in_s->semaphore;

  if(oldList) delete[] oldList;
}


VkoSemaphore *VkoCommandBuffer::addSignalSemaphore() {
  VkoSemaphore *p= _vko->objects.addSemaphore();
  p->build();

  addCustomSignalSemaphore(p);

  return p;
}


// if this is a secondary buffer, the inheritance should be filled in https://www.khronos.org/registry/vulkan/specs/1.1/html/chap5.html#VkCommandBufferBeginInfo
void VkoCommandBuffer::setInheritance(VkRenderPass in_renderPass, uint32_t in_subpass, VkFramebuffer in_framebuffer, VkBool32 in_occlusionQueryEnable, VkQueryControlFlags in_queryFlags, VkQueryPipelineStatisticFlags in_pipelineStatistics) {
  _inheritanceInfo.renderPass=           in_renderPass;
  _inheritanceInfo.subpass=              in_subpass;
  _inheritanceInfo.framebuffer=          in_framebuffer;
  _inheritanceInfo.occlusionQueryEnable= in_occlusionQueryEnable;
  _inheritanceInfo.queryFlags=           in_queryFlags;
  _inheritanceInfo.pipelineStatistics=   in_pipelineStatistics;
}



///=========================///
// CommandBuffer USAGE funcs //
///=========================///

void VkoCommandBuffer::alloc() {
  VkCommandBufferAllocateInfo allocInfo;
    allocInfo.sType= VK_STRUCTURE_TYPE_COMMAND_BUFFER_ALLOCATE_INFO;
    allocInfo.pNext= pNext.VkCommandBufferAllocateInfo;
    allocInfo.level= _level;
    allocInfo.commandPool= *pool;
    allocInfo.commandBufferCount= 1;
  _vko->AllocateCommandBuffers(*_vko, &allocInfo, &buffer);

  // pInfo setup
  _beginInfo.pNext= pNext.VkCommandBufferBeginInfo;
  _inheritanceInfo.pNext= pNext.VkCommandBufferInheritanceInfo;

  _submitInfo.pNext= pNext.VkSubmitInfo;
  _submitInfo.commandBufferCount= 1;
  _submitInfo.pCommandBuffers= &buffer;

}


/*
void VkoCommandBuffer::reset(VkCommandBufferResetFlags in_flags) {
  _vko->ResetCommandBuffer(buffer, in_flags);
}


void VkoCommandBuffer::startRecording() {
  _vko->BeginCommandBuffer(buffer, &_beginInfo);
}


void VkoCommandBuffer::submit(VkQueue in_q) {
  _vko->QueueSubmit(in_q, 1, &_submitInfo, fence);
}
*/


void VkoCommandBuffer::updateSemaphoreData() {
  for(uint32_t a= 0; a< nrSignalSemaphores; a++)
    ((VkSemaphore *)_submitInfo.pSignalSemaphores)[a]= signalSemaphores[a]->semaphore;
  for(uint32_t a= 0; a< nrWaitSemaphores; a++)
    ((VkSemaphore *)_submitInfo.pWaitSemaphores)[a]= waitSemaphores[a]->semaphore;

}



