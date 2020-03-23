#pragma once

/// there is a conflict with some WIN32 defines for CreateSemaphore and CreateEvent
#ifdef CreateSemaphore
#define OSICREATESEMAPHOREDEF CreateSemaphore
#undef CreateSemaphore
#endif
#ifdef CreateEvent
#define OSICREATEEVENT CreateEvent
#undef CreateEvent
#endif










///============///
// GLOBAL funcs //
///============///


#ifdef VKO_USE_GLOBAL_FUNCS
// VULKAN 1.0 ========================================================================
#ifdef VK_VERSION_1_0
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateInstance(const VkInstanceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkInstance *pInstance) {
  vkObject::glb->CreateInstance(pCreateInfo, pAllocator, pInstance); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyInstance(VkInstance instance, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyInstance(instance, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDevices(VkInstance instance, uint32_t *pPhysicalDeviceCount, VkPhysicalDevice *pPhysicalDevices) {
  vkObject::glb->EnumeratePhysicalDevices(instance, pPhysicalDeviceCount, pPhysicalDevices); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures *pFeatures) {
  vkObject::glb->GetPhysicalDeviceFeatures(physicalDevice, pFeatures); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties *pFormatProperties) {
  vkObject::glb->GetPhysicalDeviceFormatProperties(physicalDevice, format, pFormatProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkImageFormatProperties *pImageFormatProperties) {
  vkObject::glb->GetPhysicalDeviceImageFormatProperties(physicalDevice, format, type, tiling, usage, flags, pImageFormatProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties *pProperties) {
  vkObject::glb->GetPhysicalDeviceProperties(physicalDevice, pProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties(VkPhysicalDevice physicalDevice, uint32_t *pQueueFamilyPropertyCount, VkQueueFamilyProperties *pQueueFamilyProperties) {
  vkObject::glb->GetPhysicalDeviceQueueFamilyProperties(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties *pMemoryProperties) {
  vkObject::glb->GetPhysicalDeviceMemoryProperties(physicalDevice, pMemoryProperties); }
inline VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetInstanceProcAddr(VkInstance instance, const char *pName) {
  vkObject::glb->GetInstanceProcAddr(instance, pName); }
inline VKAPI_ATTR PFN_vkVoidFunction VKAPI_CALL vkGetDeviceProcAddr(VkDevice device, const char *pName) {
  vkObject::glb->GetDeviceProcAddr(device, pName); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDevice(VkPhysicalDevice physicalDevice, const VkDeviceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDevice *pDevice) {
  vkObject::glb->CreateDevice(physicalDevice, pCreateInfo, pAllocator, pDevice); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDevice(VkDevice device, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyDevice(device, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceExtensionProperties(const char *pLayerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties) {
  vkObject::glb->EnumerateInstanceExtensionProperties(pLayerName, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceExtensionProperties(VkPhysicalDevice physicalDevice, const char *pLayerName, uint32_t *pPropertyCount, VkExtensionProperties *pProperties) {
  vkObject::glb->EnumerateDeviceExtensionProperties(physicalDevice, pLayerName, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceLayerProperties(uint32_t *pPropertyCount, VkLayerProperties *pProperties) {
  vkObject::glb->EnumerateInstanceLayerProperties(pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateDeviceLayerProperties(VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkLayerProperties *pProperties) {
  vkObject::glb->EnumerateDeviceLayerProperties(physicalDevice, pPropertyCount, pProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue(VkDevice device, uint32_t queueFamilyIndex, uint32_t queueIndex, VkQueue *pQueue) {
  vkObject::glb->GetDeviceQueue(device, queueFamilyIndex, queueIndex, pQueue); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkQueueSubmit(VkQueue queue, uint32_t submitCount, const VkSubmitInfo *pSubmits, VkFence fence) {
  vkObject::glb->QueueSubmit(queue, submitCount, pSubmits, fence); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkQueueWaitIdle(VkQueue queue) {
  vkObject::glb->QueueWaitIdle(queue); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkDeviceWaitIdle(VkDevice device) {
  vkObject::glb->DeviceWaitIdle(device); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkAllocateMemory(VkDevice device, const VkMemoryAllocateInfo *pAllocateInfo, const VkAllocationCallbacks *pAllocator, VkDeviceMemory *pMemory) {
  vkObject::glb->AllocateMemory(device, pAllocateInfo, pAllocator, pMemory); }
inline VKAPI_ATTR void VKAPI_CALL vkFreeMemory(VkDevice device, VkDeviceMemory memory, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->FreeMemory(device, memory, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkMapMemory(VkDevice device, VkDeviceMemory memory, VkDeviceSize offset, VkDeviceSize size, VkMemoryMapFlags flags, void **ppData) {
  vkObject::glb->MapMemory(device, memory, offset, size, flags, ppData); }
inline VKAPI_ATTR void VKAPI_CALL vkUnmapMemory(VkDevice device, VkDeviceMemory memory) {
  vkObject::glb->UnmapMemory(device, memory); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkFlushMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange *pMemoryRanges) {
  vkObject::glb->FlushMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkInvalidateMappedMemoryRanges(VkDevice device, uint32_t memoryRangeCount, const VkMappedMemoryRange *pMemoryRanges) {
  vkObject::glb->InvalidateMappedMemoryRanges(device, memoryRangeCount, pMemoryRanges); }
inline VKAPI_ATTR void VKAPI_CALL vkGetDeviceMemoryCommitment(VkDevice device, VkDeviceMemory memory, VkDeviceSize *pCommittedMemoryInBytes) {
  vkObject::glb->GetDeviceMemoryCommitment(device, memory, pCommittedMemoryInBytes); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory(VkDevice device, VkBuffer buffer, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
  vkObject::glb->BindBufferMemory(device, buffer, memory, memoryOffset); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory(VkDevice device, VkImage image, VkDeviceMemory memory, VkDeviceSize memoryOffset) {
  vkObject::glb->BindImageMemory(device, image, memory, memoryOffset); }
inline VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements(VkDevice device, VkBuffer buffer, VkMemoryRequirements *pMemoryRequirements) {
  vkObject::glb->GetBufferMemoryRequirements(device, buffer, pMemoryRequirements); }
inline VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements(VkDevice device, VkImage image, VkMemoryRequirements *pMemoryRequirements) {
  vkObject::glb->GetImageMemoryRequirements(device, image, pMemoryRequirements); }
inline VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements(VkDevice device, VkImage image, uint32_t *pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements *pSparseMemoryRequirements) {
  vkObject::glb->GetImageSparseMemoryRequirements(device, image, pSparseMemoryRequirementCount, pSparseMemoryRequirements); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceSparseImageFormatProperties(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkSampleCountFlagBits samples, VkImageUsageFlags usage, VkImageTiling tiling, uint32_t *pPropertyCount, VkSparseImageFormatProperties *pProperties) {
  vkObject::glb->GetPhysicalDeviceSparseImageFormatProperties(physicalDevice, format, type, samples, usage, tiling, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkQueueBindSparse(VkQueue queue, uint32_t bindInfoCount, const VkBindSparseInfo *pBindInfo, VkFence fence) {
  vkObject::glb->QueueBindSparse(queue, bindInfoCount, pBindInfo, fence); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateFence(VkDevice device, const VkFenceCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkFence *pFence) {
  vkObject::glb->CreateFence(device, pCreateInfo, pAllocator, pFence); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyFence(VkDevice device, VkFence fence, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyFence(device, fence, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkResetFences(VkDevice device, uint32_t fenceCount, const VkFence *pFences) {
  vkObject::glb->ResetFences(device, fenceCount, pFences); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceStatus(VkDevice device, VkFence fence) {
  vkObject::glb->GetFenceStatus(device, fence);  }
inline VKAPI_ATTR VkResult VKAPI_CALL vkWaitForFences(VkDevice device, uint32_t fenceCount, const VkFence *pFences, VkBool32 waitAll, uint64_t timeout) {
  vkObject::glb->WaitForFences(device, fenceCount, pFences, waitAll, timeout); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateSemaphore(VkDevice device, const VkSemaphoreCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSemaphore *pSemaphore) {
  vkObject::glb->CreateSemaphore(device, pCreateInfo, pAllocator, pSemaphore); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroySemaphore(VkDevice device, VkSemaphore semaphore, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroySemaphore(device, semaphore, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateEvent(VkDevice device, const VkEventCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkEvent *pEvent) {
  vkObject::glb->CreateEvent(device, pCreateInfo, pAllocator, pEvent); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyEvent(VkDevice device, VkEvent event, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyEvent(device, event, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetEventStatus(VkDevice device, VkEvent event) {
  vkObject::glb->GetEventStatus(device, event); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkSetEvent(VkDevice device, VkEvent event) {
  vkObject::glb->SetEvent(device, event); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkResetEvent(VkDevice device, VkEvent event) {
  vkObject::glb->ResetEvent(device, event); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateQueryPool(VkDevice device, const VkQueryPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkQueryPool *pQueryPool) {
  vkObject::glb->CreateQueryPool(device, pCreateInfo, pAllocator, pQueryPool); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyQueryPool(VkDevice device, VkQueryPool queryPool, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyQueryPool(device, queryPool, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetQueryPoolResults(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, size_t dataSize, void *pData, VkDeviceSize stride, VkQueryResultFlags flags) {
  vkObject::glb->GetQueryPoolResults(device, queryPool, firstQuery, queryCount, dataSize, pData, stride, flags); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateBuffer(VkDevice device, const VkBufferCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkBuffer *pBuffer) {
  vkObject::glb->CreateBuffer(device, pCreateInfo, pAllocator, pBuffer); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyBuffer(VkDevice device, VkBuffer buffer, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyBuffer(device, buffer, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateBufferView(VkDevice device, const VkBufferViewCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkBufferView *pView) {
  vkObject::glb->CreateBufferView(device, pCreateInfo, pAllocator, pView); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyBufferView(VkDevice device, VkBufferView bufferView, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyBufferView(device, bufferView, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateImage(VkDevice device, const VkImageCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkImage *pImage) {
  vkObject::glb->CreateImage(device, pCreateInfo, pAllocator, pImage); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyImage(VkDevice device, VkImage image, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyImage(device, image, pAllocator); }
inline VKAPI_ATTR void VKAPI_CALL vkGetImageSubresourceLayout(VkDevice device, VkImage image, const VkImageSubresource *pSubresource, VkSubresourceLayout *pLayout) {
  vkObject::glb->GetImageSubresourceLayout(device, image, pSubresource, pLayout); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateImageView(VkDevice device, const VkImageViewCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkImageView *pView) {
  vkObject::glb->CreateImageView(device, pCreateInfo, pAllocator, pView); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyImageView(VkDevice device, VkImageView imageView, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyImageView(device, imageView, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateShaderModule(VkDevice device, const VkShaderModuleCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkShaderModule *pShaderModule) {
  vkObject::glb->CreateShaderModule(device, pCreateInfo, pAllocator, pShaderModule); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyShaderModule(VkDevice device, VkShaderModule shaderModule, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyShaderModule(device, shaderModule, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineCache(VkDevice device, const VkPipelineCacheCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkPipelineCache *pPipelineCache) {
  vkObject::glb->CreatePipelineCache(device, pCreateInfo, pAllocator, pPipelineCache); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineCache(VkDevice device, VkPipelineCache pipelineCache, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyPipelineCache(device, pipelineCache, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineCacheData(VkDevice device, VkPipelineCache pipelineCache, size_t *pDataSize, void *pData) {
  vkObject::glb->GetPipelineCacheData(device, pipelineCache, pDataSize, pData); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkMergePipelineCaches(VkDevice device, VkPipelineCache dstCache, uint32_t srcCacheCount, const VkPipelineCache *pSrcCaches) {
  vkObject::glb->MergePipelineCaches(device, dstCache, srcCacheCount, pSrcCaches); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateGraphicsPipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkGraphicsPipelineCreateInfo *pCreateInfos, const VkAllocationCallbacks *pAllocator, VkPipeline *pPipelines) {
  vkObject::glb->CreateGraphicsPipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateComputePipelines(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkComputePipelineCreateInfo *pCreateInfos, const VkAllocationCallbacks *pAllocator, VkPipeline *pPipelines) {
  vkObject::glb->CreateComputePipelines(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyPipeline(VkDevice device, VkPipeline pipeline, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyPipeline(device, pipeline, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreatePipelineLayout(VkDevice device,const VkPipelineLayoutCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkPipelineLayout *pPipelineLayout) {
  vkObject::glb->CreatePipelineLayout(device, pCreateInfo, pAllocator, pPipelineLayout); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyPipelineLayout(VkDevice device, VkPipelineLayout pipelineLayout, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyPipelineLayout(device, pipelineLayout, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateSampler(VkDevice device, const VkSamplerCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSampler *pSampler) {
  vkObject::glb->CreateSampler(device, pCreateInfo, pAllocator, pSampler); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroySampler(VkDevice device, VkSampler sampler, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroySampler(device, sampler, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorSetLayout(VkDevice device, const VkDescriptorSetLayoutCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDescriptorSetLayout *pSetLayout) {
  vkObject::glb->CreateDescriptorSetLayout(device, pCreateInfo, pAllocator, pSetLayout); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorSetLayout(VkDevice device, VkDescriptorSetLayout descriptorSetLayout, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyDescriptorSetLayout(device, descriptorSetLayout, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorPool(VkDevice device, const VkDescriptorPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDescriptorPool *pDescriptorPool) {
  vkObject::glb->CreateDescriptorPool(device, pCreateInfo, pAllocator, pDescriptorPool); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyDescriptorPool(device, descriptorPool, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkResetDescriptorPool(VkDevice device, VkDescriptorPool descriptorPool, VkDescriptorPoolResetFlags flags) {
  vkObject::glb->ResetDescriptorPool(device, descriptorPool, flags); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkAllocateDescriptorSets(VkDevice device, const VkDescriptorSetAllocateInfo *pAllocateInfo, VkDescriptorSet *pDescriptorSets) {
  vkObject::glb->AllocateDescriptorSets(device, pAllocateInfo, pDescriptorSets); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkFreeDescriptorSets(VkDevice device, VkDescriptorPool descriptorPool, uint32_t descriptorSetCount, const VkDescriptorSet *pDescriptorSets) {
  vkObject::glb->FreeDescriptorSets(device, descriptorPool, descriptorSetCount, pDescriptorSets); }
inline VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSets(VkDevice device, uint32_t descriptorWriteCount, const VkWriteDescriptorSet *pDescriptorWrites, uint32_t descriptorCopyCount, const VkCopyDescriptorSet *pDescriptorCopies) {
  vkObject::glb->UpdateDescriptorSets(device, descriptorWriteCount, pDescriptorWrites, descriptorCopyCount, pDescriptorCopies); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateFramebuffer(VkDevice device, const VkFramebufferCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkFramebuffer *pFramebuffer) {
  vkObject::glb->CreateFramebuffer(device, pCreateInfo, pAllocator, pFramebuffer); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyFramebuffer(VkDevice device, VkFramebuffer framebuffer, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyFramebuffer(device, framebuffer, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass(VkDevice device, const VkRenderPassCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkRenderPass *pRenderPass) {
  vkObject::glb->CreateRenderPass(device, pCreateInfo, pAllocator, pRenderPass); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyRenderPass(VkDevice device, VkRenderPass renderPass, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyRenderPass(device, renderPass, pAllocator); }
inline VKAPI_ATTR void VKAPI_CALL vkGetRenderAreaGranularity(VkDevice device, VkRenderPass renderPass, VkExtent2D *pGranularity) {
  vkObject::glb->GetRenderAreaGranularity(device, renderPass, pGranularity); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateCommandPool(VkDevice device, const VkCommandPoolCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkCommandPool *pCommandPool) {
  vkObject::glb->CreateCommandPool(device, pCreateInfo, pAllocator, pCommandPool); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyCommandPool(VkDevice device, VkCommandPool commandPool, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyCommandPool(device, commandPool, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolResetFlags flags) {
  vkObject::glb->ResetCommandPool(device, commandPool, flags); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkAllocateCommandBuffers(VkDevice device, const VkCommandBufferAllocateInfo *pAllocateInfo, VkCommandBuffer *pCommandBuffers) {
  vkObject::glb->AllocateCommandBuffers(device, pAllocateInfo, pCommandBuffers); }
inline VKAPI_ATTR void VKAPI_CALL vkFreeCommandBuffers(VkDevice device, VkCommandPool commandPool, uint32_t commandBufferCount, const VkCommandBuffer *pCommandBuffers) {
  vkObject::glb->FreeCommandBuffers(device, commandPool, commandBufferCount, pCommandBuffers); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkBeginCommandBuffer(VkCommandBuffer commandBuffer, const VkCommandBufferBeginInfo *pBeginInfo) {
  vkObject::glb->BeginCommandBuffer(commandBuffer, pBeginInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkEndCommandBuffer(VkCommandBuffer commandBuffer) {
  vkObject::glb->EndCommandBuffer(commandBuffer); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkResetCommandBuffer(VkCommandBuffer commandBuffer, VkCommandBufferResetFlags flags) {
  return vkObject::glb->ResetCommandBuffer(commandBuffer, flags); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBindPipeline(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipeline pipeline) {
  vkObject::glb->CmdBindPipeline(commandBuffer, pipelineBindPoint, pipeline); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetViewport(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewport *pViewports) {
  vkObject::glb->CmdSetViewport(commandBuffer, firstViewport, viewportCount, pViewports); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetScissor(VkCommandBuffer commandBuffer, uint32_t firstScissor, uint32_t scissorCount, const VkRect2D *pScissors) {
  vkObject::glb->CmdSetScissor(commandBuffer, firstScissor, scissorCount, pScissors); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetLineWidth(VkCommandBuffer commandBuffer, float lineWidth) {
  vkObject::glb->CmdSetLineWidth(commandBuffer, lineWidth); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBias(VkCommandBuffer commandBuffer, float depthBiasConstantFactor, float depthBiasClamp, float depthBiasSlopeFactor) {
  vkObject::glb->CmdSetDepthBias(commandBuffer, depthBiasConstantFactor, depthBiasClamp, depthBiasSlopeFactor); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetBlendConstants(VkCommandBuffer commandBuffer, const float blendConstants[4]) {
  vkObject::glb->CmdSetBlendConstants(commandBuffer, blendConstants); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetDepthBounds(VkCommandBuffer commandBuffer, float minDepthBounds, float maxDepthBounds) {
  vkObject::glb->CmdSetDepthBounds(commandBuffer, minDepthBounds, maxDepthBounds); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilCompareMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t compareMask) {
  vkObject::glb->CmdSetStencilCompareMask(commandBuffer, faceMask, compareMask); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilWriteMask(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t writeMask) {
  vkObject::glb->CmdSetStencilWriteMask(commandBuffer, faceMask, writeMask); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetStencilReference(VkCommandBuffer commandBuffer, VkStencilFaceFlags faceMask, uint32_t reference) {
  vkObject::glb->CmdSetStencilReference(commandBuffer, faceMask, reference); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBindDescriptorSets(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t firstSet, uint32_t descriptorSetCount, const VkDescriptorSet *pDescriptorSets, uint32_t dynamicOffsetCount, const uint32_t *pDynamicOffsets) {
  vkObject::glb->CmdBindDescriptorSets(commandBuffer, pipelineBindPoint, layout, firstSet, descriptorSetCount, pDescriptorSets, dynamicOffsetCount, pDynamicOffsets); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBindIndexBuffer(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkIndexType indexType) {
  vkObject::glb->CmdBindIndexBuffer(commandBuffer, buffer, offset, indexType); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBindVertexBuffers(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer *pBuffers, const VkDeviceSize *pOffsets) {
  vkObject::glb->CmdBindVertexBuffers(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDraw(VkCommandBuffer commandBuffer, uint32_t vertexCount, uint32_t instanceCount, uint32_t firstVertex, uint32_t firstInstance) {
  vkObject::glb->CmdDraw(commandBuffer, vertexCount, instanceCount, firstVertex, firstInstance); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexed(VkCommandBuffer commandBuffer, uint32_t indexCount, uint32_t instanceCount, uint32_t firstIndex, int32_t vertexOffset, uint32_t firstInstance) {
  vkObject::glb->CmdDrawIndexed(commandBuffer, indexCount, instanceCount, firstIndex, vertexOffset, firstInstance); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
  vkObject::glb->CmdDrawIndirect(commandBuffer, buffer, offset, drawCount, stride); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
  vkObject::glb->CmdDrawIndexedIndirect(commandBuffer, buffer, offset, drawCount, stride); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDispatch(VkCommandBuffer commandBuffer, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
  vkObject::glb->CmdDispatch(commandBuffer, groupCountX, groupCountY, groupCountZ); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDispatchIndirect(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset) {
  vkObject::glb->CmdDispatchIndirect(commandBuffer, buffer, offset); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdCopyBuffer(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferCopy *pRegions) {
  vkObject::glb->CmdCopyBuffer(commandBuffer, srcBuffer, dstBuffer, regionCount, pRegions); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdCopyImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageCopy *pRegions) {
  vkObject::glb->CmdCopyImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBlitImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageBlit *pRegions, VkFilter filter) {
  vkObject::glb->CmdBlitImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions, filter); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdCopyBufferToImage(VkCommandBuffer commandBuffer, VkBuffer srcBuffer, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkBufferImageCopy *pRegions) {
  vkObject::glb->CmdCopyBufferToImage(commandBuffer, srcBuffer, dstImage, dstImageLayout, regionCount, pRegions); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdCopyImageToBuffer(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkBuffer dstBuffer, uint32_t regionCount, const VkBufferImageCopy *pRegions) {
  vkObject::glb->CmdCopyImageToBuffer(commandBuffer, srcImage, srcImageLayout, dstBuffer, regionCount, pRegions); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdUpdateBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize dataSize, const void *pData) {
  vkObject::glb->CmdUpdateBuffer(commandBuffer, dstBuffer, dstOffset, dataSize, pData); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdFillBuffer(VkCommandBuffer commandBuffer, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize size, uint32_t data) {
  vkObject::glb->CmdFillBuffer(commandBuffer, dstBuffer, dstOffset, size, data); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdClearColorImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearColorValue *pColor, uint32_t rangeCount, const VkImageSubresourceRange *pRanges) {
  vkObject::glb->CmdClearColorImage(commandBuffer, image, imageLayout, pColor, rangeCount, pRanges); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdClearDepthStencilImage(VkCommandBuffer commandBuffer, VkImage image, VkImageLayout imageLayout, const VkClearDepthStencilValue *pDepthStencil, uint32_t rangeCount, const VkImageSubresourceRange *pRanges) {
  vkObject::glb->CmdClearDepthStencilImage(commandBuffer, image, imageLayout, pDepthStencil, rangeCount, pRanges); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdClearAttachments(VkCommandBuffer commandBuffer, uint32_t attachmentCount, const VkClearAttachment *pAttachments, uint32_t rectCount, const VkClearRect *pRects) {
  vkObject::glb->CmdClearAttachments(commandBuffer, attachmentCount, pAttachments, rectCount, pRects); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdResolveImage(VkCommandBuffer commandBuffer, VkImage srcImage, VkImageLayout srcImageLayout, VkImage dstImage, VkImageLayout dstImageLayout, uint32_t regionCount, const VkImageResolve *pRegions) {
  vkObject::glb->CmdResolveImage(commandBuffer, srcImage, srcImageLayout, dstImage, dstImageLayout, regionCount, pRegions); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
  vkObject::glb->CmdSetEvent(commandBuffer, event, stageMask); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdResetEvent(VkCommandBuffer commandBuffer, VkEvent event, VkPipelineStageFlags stageMask) {
  vkObject::glb->CmdResetEvent(commandBuffer, event, stageMask); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdWaitEvents(VkCommandBuffer commandBuffer, uint32_t eventCount, const VkEvent *pEvents, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, uint32_t memoryBarrierCount, const VkMemoryBarrier *pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier *pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier *pImageMemoryBarriers) {
  vkObject::glb->CmdWaitEvents(commandBuffer, eventCount, pEvents, srcStageMask, dstStageMask, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdPipelineBarrier(VkCommandBuffer commandBuffer, VkPipelineStageFlags srcStageMask, VkPipelineStageFlags dstStageMask, VkDependencyFlags dependencyFlags, uint32_t memoryBarrierCount, const VkMemoryBarrier *pMemoryBarriers, uint32_t bufferMemoryBarrierCount, const VkBufferMemoryBarrier *pBufferMemoryBarriers, uint32_t imageMemoryBarrierCount, const VkImageMemoryBarrier *pImageMemoryBarriers) {
  vkObject::glb->CmdPipelineBarrier(commandBuffer, srcStageMask, dstStageMask, dependencyFlags, memoryBarrierCount, pMemoryBarriers, bufferMemoryBarrierCount, pBufferMemoryBarriers, imageMemoryBarrierCount, pImageMemoryBarriers); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBeginQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags) {
  vkObject::glb->CmdBeginQuery(commandBuffer, queryPool, query, flags); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdEndQuery(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query) {
  vkObject::glb->CmdEndQuery(commandBuffer, queryPool, query); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdResetQueryPool(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
  vkObject::glb->CmdResetQueryPool(commandBuffer, queryPool, firstQuery, queryCount); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdWriteTimestamp(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkQueryPool queryPool, uint32_t query) {
  vkObject::glb->CmdWriteTimestamp(commandBuffer, pipelineStage, queryPool, query); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdCopyQueryPoolResults(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount, VkBuffer dstBuffer, VkDeviceSize dstOffset, VkDeviceSize stride, VkQueryResultFlags flags) {
  vkObject::glb->CmdCopyQueryPoolResults(commandBuffer, queryPool, firstQuery, queryCount, dstBuffer, dstOffset, stride, flags); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdPushConstants(VkCommandBuffer commandBuffer, VkPipelineLayout layout, VkShaderStageFlags stageFlags, uint32_t offset, uint32_t size, const void *pValues) {
  vkObject::glb->CmdPushConstants(commandBuffer, layout, stageFlags, offset, size, pValues); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo *pRenderPassBegin, VkSubpassContents contents) {
  vkObject::glb->CmdBeginRenderPass(commandBuffer, pRenderPassBegin, contents); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass(VkCommandBuffer commandBuffer, VkSubpassContents contents) {
  vkObject::glb->CmdNextSubpass(commandBuffer, contents); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass(VkCommandBuffer commandBuffer) {
  vkObject::glb->CmdEndRenderPass(commandBuffer); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdExecuteCommands(VkCommandBuffer commandBuffer, uint32_t commandBufferCount, const VkCommandBuffer *pCommandBuffers) {
  vkObject::glb->CmdExecuteCommands(commandBuffer, commandBufferCount, pCommandBuffers); }
#endif // VULKAN 1.0


// VULKAN 1.1 ========================================================================
#ifdef VK_VERSION_1_1
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumerateInstanceVersion(uint32_t *pApiVersion) {
  vkObject::glb->EnumerateInstanceVersion(pApiVersion); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo *pBindInfos) {
  vkObject::glb->BindBufferMemory2(device, bindInfoCount, pBindInfos); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory2(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo *pBindInfos) {
  vkObject::glb->BindImageMemory2(device, bindInfoCount, pBindInfos); }
inline VKAPI_ATTR void VKAPI_CALL vkGetDeviceGroupPeerMemoryFeatures(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags *pPeerMemoryFeatures) {
  vkObject::glb->GetDeviceGroupPeerMemoryFeatures(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetDeviceMask(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
  vkObject::glb->CmdSetDeviceMask(commandBuffer, deviceMask); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDispatchBase(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
  vkObject::glb->CmdDispatchBase(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceGroups(VkInstance instance, uint32_t *pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties *pPhysicalDeviceGroupProperties) {
  vkObject::glb->EnumeratePhysicalDeviceGroups(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements2(VkDevice device, const VkImageMemoryRequirementsInfo2 *pInfo, VkMemoryRequirements2 *pMemoryRequirements) {
  vkObject::glb->GetImageMemoryRequirements2(device, pInfo, pMemoryRequirements); }
inline VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements2(VkDevice device, const VkBufferMemoryRequirementsInfo2 *pInfo, VkMemoryRequirements2 *pMemoryRequirements) {
  vkObject::glb->GetBufferMemoryRequirements2(device, pInfo, pMemoryRequirements); }
inline VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements2(VkDevice device, const VkImageSparseMemoryRequirementsInfo2 *pInfo, uint32_t *pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 *pSparseMemoryRequirements) {
  vkObject::glb->GetImageSparseMemoryRequirements2(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2 *pFeatures) {
  vkObject::glb->GetPhysicalDeviceFeatures2(physicalDevice, pFeatures); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2 *pProperties) {
  vkObject::glb->GetPhysicalDeviceProperties2(physicalDevice, pProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties2(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2 *pFormatProperties) {
  vkObject::glb->GetPhysicalDeviceFormatProperties2(physicalDevice, format, pFormatProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2 *pImageFormatInfo, VkImageFormatProperties2 *pImageFormatProperties) {
  vkObject::glb->GetPhysicalDeviceImageFormatProperties2(physicalDevice, pImageFormatInfo, pImageFormatProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2(VkPhysicalDevice physicalDevice, uint32_t *pQueueFamilyPropertyCount, VkQueueFamilyProperties2 *pQueueFamilyProperties) {
  vkObject::glb->GetPhysicalDeviceQueueFamilyProperties2(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties2(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2 *pMemoryProperties) {
  vkObject::glb->GetPhysicalDeviceMemoryProperties2(physicalDevice, pMemoryProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceSparseImageFormatProperties2(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2 *pFormatInfo, uint32_t *pPropertyCount, VkSparseImageFormatProperties2 *pProperties) {
  vkObject::glb->GetPhysicalDeviceSparseImageFormatProperties2(physicalDevice, pFormatInfo, pPropertyCount, pProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkTrimCommandPool(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) {
  vkObject::glb->TrimCommandPool(device, commandPool, flags); }
inline VKAPI_ATTR void VKAPI_CALL vkGetDeviceQueue2(VkDevice device, const VkDeviceQueueInfo2 *pQueueInfo, VkQueue *pQueue) {
  vkObject::glb->GetDeviceQueue2(device, pQueueInfo, pQueue); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateSamplerYcbcrConversion(VkDevice device, const VkSamplerYcbcrConversionCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSamplerYcbcrConversion *pYcbcrConversion) {
  vkObject::glb->CreateSamplerYcbcrConversion(device, pCreateInfo, pAllocator, pYcbcrConversion); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroySamplerYcbcrConversion(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroySamplerYcbcrConversion(device, ycbcrConversion, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorUpdateTemplate(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDescriptorUpdateTemplate *pDescriptorUpdateTemplate) {
  vkObject::glb->CreateDescriptorUpdateTemplate(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorUpdateTemplate(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyDescriptorUpdateTemplate(device, descriptorUpdateTemplate, pAllocator); }
inline VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSetWithTemplate(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void *pData) {
  vkObject::glb->UpdateDescriptorSetWithTemplate(device, descriptorSet, descriptorUpdateTemplate, pData); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalBufferProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo *pExternalBufferInfo, VkExternalBufferProperties *pExternalBufferProperties) {
  vkObject::glb->GetPhysicalDeviceExternalBufferProperties(physicalDevice, pExternalBufferInfo, pExternalBufferProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalFenceProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo *pExternalFenceInfo, VkExternalFenceProperties *pExternalFenceProperties) {
  vkObject::glb->GetPhysicalDeviceExternalFenceProperties(physicalDevice, pExternalFenceInfo, pExternalFenceProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalSemaphoreProperties(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo *pExternalSemaphoreInfo, VkExternalSemaphoreProperties *pExternalSemaphoreProperties) {
  vkObject::glb->GetPhysicalDeviceExternalSemaphoreProperties(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSupport(VkDevice device, const VkDescriptorSetLayoutCreateInfo *pCreateInfo, VkDescriptorSetLayoutSupport *pSupport) {
  vkObject::glb->GetDescriptorSetLayoutSupport(device, pCreateInfo, pSupport); }
#endif // VULKAN 1.1

// VULKAN 1.2 ========================================================================
#ifdef VK_VERSION_1_2
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
  vkObject::glb->CmdDrawIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCount(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
  vkObject::glb->CmdDrawIndexedIndirectCount(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass2(VkDevice device, const VkRenderPassCreateInfo2 *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkRenderPass *pRenderPass) {
  vkObject::glb->CreateRenderPass2(device, pCreateInfo, pAllocator, pRenderPass); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass2(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo *pRenderPassBegin, const VkSubpassBeginInfo *pSubpassBeginInfo) {
  vkObject::glb->CmdBeginRenderPass2(commandBuffer, pRenderPassBegin, pSubpassBeginInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass2(VkCommandBuffer commandBuffer, const VkSubpassBeginInfo *pSubpassBeginInfo, const VkSubpassEndInfo *pSubpassEndInfo) {
  vkObject::glb->CmdNextSubpass2(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass2(VkCommandBuffer commandBuffer, const VkSubpassEndInfo *pSubpassEndInfo) {
  vkObject::glb->CmdEndRenderPass2(commandBuffer, pSubpassEndInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkResetQueryPool(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
  vkObject::glb->ResetQueryPool(device, queryPool, firstQuery, queryCount); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreCounterValue(VkDevice device, VkSemaphore semaphore, uint64_t *pValue) {
  vkObject::glb->GetSemaphoreCounterValue(device, semaphore, pValue); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkWaitSemaphores(VkDevice device, const VkSemaphoreWaitInfo *pWaitInfo, uint64_t timeout) {
  vkObject::glb->WaitSemaphores(device, pWaitInfo, timeout); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkSignalSemaphore(VkDevice device, const VkSemaphoreSignalInfo *pSignalInfo) {
  vkObject::glb->SignalSemaphore(device, pSignalInfo); }
inline VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetBufferDeviceAddress(VkDevice device, const VkBufferDeviceAddressInfo *pInfo) {
  vkObject::glb->GetBufferDeviceAddress(device, pInfo); }
inline VKAPI_ATTR uint64_t VKAPI_CALL vkGetBufferOpaqueCaptureAddress(VkDevice device, const VkBufferDeviceAddressInfo *pInfo) {
  vkObject::glb->GetBufferOpaqueCaptureAddress(device, pInfo); }
inline VKAPI_ATTR uint64_t VKAPI_CALL vkGetDeviceMemoryOpaqueCaptureAddress(VkDevice device, const VkDeviceMemoryOpaqueCaptureAddressInfo *pInfo) {
  vkObject::glb->GetDeviceMemoryOpaqueCaptureAddress(device, pInfo); }
#endif // VK_VERSION_1_2


















///========================================================================================///
// EXTENSIONS ============================================================================= //
///========================================================================================///






#ifdef VK_KHR_surface // "VK_KHR_surface"
inline VKAPI_ATTR void VKAPI_CALL vkDestroySurfaceKHR(VkInstance instance, VkSurfaceKHR surface, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroySurfaceKHR(instance, surface, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, VkSurfaceKHR surface, VkBool32 *pSupported) {
  vkObject::glb->GetPhysicalDeviceSurfaceSupportKHR(physicalDevice, queueFamilyIndex, surface, pSupported); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilitiesKHR *pSurfaceCapabilities) {
  vkObject::glb->GetPhysicalDeviceSurfaceCapabilitiesKHR(physicalDevice, surface, pSurfaceCapabilities); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormatsKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t *pSurfaceFormatCount, VkSurfaceFormatKHR *pSurfaceFormats) {
  vkObject::glb->GetPhysicalDeviceSurfaceFormatsKHR(physicalDevice, surface, pSurfaceFormatCount, pSurfaceFormats); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfacePresentModesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t *pPresentModeCount, VkPresentModeKHR *pPresentModes) {
  vkObject::glb->GetPhysicalDeviceSurfacePresentModesKHR(physicalDevice, surface, pPresentModeCount, pPresentModes); }
#endif /// VK_KHR_surface

#ifdef VK_KHR_swapchain // "VK_KHR_swapchain"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateSwapchainKHR(VkDevice device, const VkSwapchainCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSwapchainKHR *pSwapchain) {
  vkObject::glb->CreateSwapchainKHR(device, pCreateInfo, pAllocator, pSwapchain); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroySwapchainKHR(VkDevice device, VkSwapchainKHR swapchain, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroySwapchainKHR(device, swapchain, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainImagesKHR(VkDevice device, VkSwapchainKHR swapchain, uint32_t *pSwapchainImageCount, VkImage *pSwapchainImages) {
  vkObject::glb->GetSwapchainImagesKHR(device, swapchain, pSwapchainImageCount, pSwapchainImages); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImageKHR(VkDevice device, VkSwapchainKHR swapchain, uint64_t timeout, VkSemaphore semaphore, VkFence fence, uint32_t *pImageIndex) {
  vkObject::glb->AcquireNextImageKHR(device, swapchain, timeout, semaphore, fence, pImageIndex); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkQueuePresentKHR(VkQueue queue, const VkPresentInfoKHR *pPresentInfo) {
  vkObject::glb->QueuePresentKHR(queue, pPresentInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupPresentCapabilitiesKHR(VkDevice device, VkDeviceGroupPresentCapabilitiesKHR *pDeviceGroupPresentCapabilities) {
  vkObject::glb->GetDeviceGroupPresentCapabilitiesKHR(device, pDeviceGroupPresentCapabilities); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetDeviceGroupSurfacePresentModesKHR(VkDevice device, VkSurfaceKHR surface, VkDeviceGroupPresentModeFlagsKHR *pModes) {
  vkObject::glb->GetDeviceGroupSurfacePresentModesKHR(device, surface, pModes); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDevicePresentRectanglesKHR(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, uint32_t *pRectCount, VkRect2D *pRects) {
  vkObject::glb->GetPhysicalDevicePresentRectanglesKHR(physicalDevice, surface, pRectCount, pRects); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkAcquireNextImage2KHR(VkDevice device, const VkAcquireNextImageInfoKHR *pAcquireInfo, uint32_t *pImageIndex) {
  vkObject::glb->AcquireNextImage2KHR(device, pAcquireInfo, pImageIndex); }
#endif /// VK_KHR_swapchain

#ifdef VK_KHR_display // "VK_KHR_display"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkDisplayPropertiesKHR *pProperties) {
  vkObject::glb->GetPhysicalDeviceDisplayPropertiesKHR(physicalDevice, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPlanePropertiesKHR(VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkDisplayPlanePropertiesKHR *pProperties) {
  vkObject::glb->GetPhysicalDeviceDisplayPlanePropertiesKHR(physicalDevice, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneSupportedDisplaysKHR(VkPhysicalDevice physicalDevice, uint32_t planeIndex, uint32_t *pDisplayCount, VkDisplayKHR *pDisplays) {
  vkObject::glb->GetDisplayPlaneSupportedDisplaysKHR(physicalDevice, planeIndex, pDisplayCount, pDisplays); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayModePropertiesKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t *pPropertyCount, VkDisplayModePropertiesKHR *pProperties) {
  vkObject::glb->GetDisplayModePropertiesKHR(physicalDevice, display, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDisplayModeKHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, const VkDisplayModeCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDisplayModeKHR *pMode) {
  vkObject::glb->CreateDisplayModeKHR(physicalDevice, display, pCreateInfo, pAllocator, pMode); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneCapabilitiesKHR(VkPhysicalDevice physicalDevice, VkDisplayModeKHR mode, uint32_t planeIndex, VkDisplayPlaneCapabilitiesKHR *pCapabilities) {
  vkObject::glb->GetDisplayPlaneCapabilitiesKHR(physicalDevice, mode, planeIndex, pCapabilities); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDisplayPlaneSurfaceKHR(VkInstance instance, const VkDisplaySurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
  vkObject::glb->CreateDisplayPlaneSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface); }
#endif /// VK_KHR_display

#ifdef VK_KHR_display_swapchain // "VK_KHR_display_swapchain"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateSharedSwapchainsKHR(VkDevice device, uint32_t swapchainCount, const VkSwapchainCreateInfoKHR *pCreateInfos, const VkAllocationCallbacks *pAllocator, VkSwapchainKHR *pSwapchains) {
  vkObject::glb->CreateSharedSwapchainsKHR(device, swapchainCount, pCreateInfos, pAllocator, pSwapchains); }
#endif /// VK_KHR_display_swapchain

#ifdef VK_KHR_get_physical_device_properties2 // "VK_KHR_get_physical_device_properties2"
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFeatures2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceFeatures2 *pFeatures) {
  vkObject::glb->GetPhysicalDeviceFeatures2KHR(physicalDevice, pFeatures); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceProperties2 *pProperties) {
  vkObject::glb->GetPhysicalDeviceProperties2KHR(physicalDevice, pProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceFormatProperties2KHR(VkPhysicalDevice physicalDevice, VkFormat format, VkFormatProperties2 *pFormatProperties) {
  vkObject::glb->GetPhysicalDeviceFormatProperties2KHR(physicalDevice, format, pFormatProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceImageFormatInfo2 *pImageFormatInfo, VkImageFormatProperties2 *pImageFormatProperties) {
  vkObject::glb->GetPhysicalDeviceImageFormatProperties2KHR(physicalDevice, pImageFormatInfo, pImageFormatProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t *pQueueFamilyPropertyCount, VkQueueFamilyProperties2 *pQueueFamilyProperties) {
  vkObject::glb->GetPhysicalDeviceQueueFamilyProperties2KHR(physicalDevice, pQueueFamilyPropertyCount, pQueueFamilyProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMemoryProperties2KHR(VkPhysicalDevice physicalDevice, VkPhysicalDeviceMemoryProperties2 *pMemoryProperties) {
  vkObject::glb->GetPhysicalDeviceMemoryProperties2KHR(physicalDevice, pMemoryProperties); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceSparseImageFormatProperties2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSparseImageFormatInfo2 *pFormatInfo, uint32_t *pPropertyCount, VkSparseImageFormatProperties2 *pProperties) {
  vkObject::glb->GetPhysicalDeviceSparseImageFormatProperties2KHR(physicalDevice, pFormatInfo, pPropertyCount, pProperties); }
#endif /// VK_KHR_get_physical_device_properties2

#ifdef VK_KHR_device_group // "VK_KHR_device_group"
inline VKAPI_ATTR void VKAPI_CALL vkGetDeviceGroupPeerMemoryFeaturesKHR(VkDevice device, uint32_t heapIndex, uint32_t localDeviceIndex, uint32_t remoteDeviceIndex, VkPeerMemoryFeatureFlags *pPeerMemoryFeatures) {
  vkObject::glb->GetDeviceGroupPeerMemoryFeaturesKHR(device, heapIndex, localDeviceIndex, remoteDeviceIndex, pPeerMemoryFeatures); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetDeviceMaskKHR(VkCommandBuffer commandBuffer, uint32_t deviceMask) {
  vkObject::glb->CmdSetDeviceMaskKHR(commandBuffer, deviceMask); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDispatchBaseKHR(VkCommandBuffer commandBuffer, uint32_t baseGroupX, uint32_t baseGroupY, uint32_t baseGroupZ, uint32_t groupCountX, uint32_t groupCountY, uint32_t groupCountZ) {
  vkObject::glb->CmdDispatchBaseKHR(commandBuffer, baseGroupX, baseGroupY, baseGroupZ, groupCountX, groupCountY, groupCountZ); }
#endif /// VK_KHR_device_group

#ifdef VK_KHR_maintenance1 // "VK_KHR_maintenance1"
inline VKAPI_ATTR void VKAPI_CALL vkTrimCommandPoolKHR(VkDevice device, VkCommandPool commandPool, VkCommandPoolTrimFlags flags) {
  vkObject::glb->TrimCommandPoolKHR(device, commandPool, flags); }
#endif /// VK_KHR_maintenance1

#ifdef VK_KHR_device_group_creation // "VK_KHR_device_group_creation"
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceGroupsKHR(VkInstance instance, uint32_t *pPhysicalDeviceGroupCount, VkPhysicalDeviceGroupProperties *pPhysicalDeviceGroupProperties) {
  vkObject::glb->EnumeratePhysicalDeviceGroupsKHR(instance, pPhysicalDeviceGroupCount, pPhysicalDeviceGroupProperties); }
#endif /// VK_KHR_device_group_creation

#ifdef VK_KHR_external_memory_capabilities // "VK_KHR_external_memory_capabilities"
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalBufferPropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalBufferInfo *pExternalBufferInfo, VkExternalBufferProperties *pExternalBufferProperties) {
  vkObject::glb->GetPhysicalDeviceExternalBufferPropertiesKHR(physicalDevice, pExternalBufferInfo, pExternalBufferProperties); }
#endif /// VK_KHR_external_memory_capabilities

#ifdef VK_KHR_external_memory_fd // "VK_KHR_external_memory_fd"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryFdKHR(VkDevice device, const VkMemoryGetFdInfoKHR *pGetFdInfo, int *pFd) {
  vkObject::glb->GetMemoryFdKHR(device, pGetFdInfo, pFd); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryFdPropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, int fd, VkMemoryFdPropertiesKHR *pMemoryFdProperties) {
  vkObject::glb->GetMemoryFdPropertiesKHR(device, handleType, fd, pMemoryFdProperties); }
#endif /// VK_KHR_external_memory_fd

#ifdef VK_KHR_external_semaphore_capabilities // "VK_KHR_external_semaphore_capabilities"
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalSemaphorePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalSemaphoreInfo *pExternalSemaphoreInfo, VkExternalSemaphoreProperties *pExternalSemaphoreProperties) {
  vkObject::glb->GetPhysicalDeviceExternalSemaphorePropertiesKHR(physicalDevice, pExternalSemaphoreInfo, pExternalSemaphoreProperties); }
#endif /// VK_KHR_external_semaphore_capabilities

#ifdef VK_KHR_external_semaphore_fd // "VK_KHR_external_semaphore_fd"
inline VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreFdKHR(VkDevice device, const VkImportSemaphoreFdInfoKHR *pImportSemaphoreFdInfo) {
  vkObject::glb->ImportSemaphoreFdKHR(device, pImportSemaphoreFdInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreFdKHR(VkDevice device, const VkSemaphoreGetFdInfoKHR *pGetFdInfo, int *pFd) {
  vkObject::glb->GetSemaphoreFdKHR(device, pGetFdInfo, pFd); }
#endif /// VK_KHR_external_semaphore_fd

#ifdef VK_KHR_push_descriptor // "VK_KHR_push_descriptor"
inline VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetKHR(VkCommandBuffer commandBuffer, VkPipelineBindPoint pipelineBindPoint, VkPipelineLayout layout, uint32_t set, uint32_t descriptorWriteCount, const VkWriteDescriptorSet *pDescriptorWrites) {
  vkObject::glb->CmdPushDescriptorSetKHR(commandBuffer, pipelineBindPoint, layout, set, descriptorWriteCount, pDescriptorWrites); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdPushDescriptorSetWithTemplateKHR(VkCommandBuffer commandBuffer, VkDescriptorUpdateTemplate descriptorUpdateTemplate, VkPipelineLayout layout, uint32_t set, const void *pData) {
  vkObject::glb->CmdPushDescriptorSetWithTemplateKHR(commandBuffer, descriptorUpdateTemplate, layout, set, pData); }
#endif

#ifdef VK_KHR_descriptor_update_template // "VK_KHR_descriptor_update_template"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDescriptorUpdateTemplate *pDescriptorUpdateTemplate) {
  vkObject::glb->CreateDescriptorUpdateTemplateKHR(device, pCreateInfo, pAllocator, pDescriptorUpdateTemplate); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyDescriptorUpdateTemplateKHR(device, descriptorUpdateTemplate, pAllocator); }
inline VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void *pData) {
  vkObject::glb->UpdateDescriptorSetWithTemplateKHR(device, descriptorSet, descriptorUpdateTemplate, pData); }
#endif /// VK_KHR_descriptor_update_template

#ifdef VK_KHR_create_renderpass2 // "VK_KHR_create_renderpass2"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2KHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkRenderPass *pRenderPass) {
  vkObject::glb->CreateRenderPass2KHR(device, pCreateInfo, pAllocator, pRenderPass); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo *pRenderPassBegin, const VkSubpassBeginInfoKHR *pSubpassBeginInfo) {
  vkObject::glb->CmdBeginRenderPass2KHR(commandBuffer, pRenderPassBegin, pSubpassBeginInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfoKHR *pSubpassBeginInfo, const VkSubpassEndInfoKHR *pSubpassEndInfo) {
  vkObject::glb->CmdNextSubpass2KHR(commandBuffer, pSubpassBeginInfo, pSubpassEndInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfoKHR *pSubpassEndInfo) {
  vkObject::glb->CmdEndRenderPass2KHR(commandBuffer, pSubpassEndInfo); }
#endif /// VK_KHR_create_renderpass2

#ifdef VK_KHR_shared_presentable_image // "VK_KHR_shared_presentable_image"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain) {
  vkObject::glb->GetSwapchainStatusKHR(device, swapchain); }
#endif /// VK_KHR_shared_presentable_image

#ifdef VK_KHR_external_fence_capabilities // "VK_KHR_external_fence_capabilities"
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo *pExternalFenceInfo, VkExternalFenceProperties *pExternalFenceProperties) {
  vkObject::glb->GetPhysicalDeviceExternalFencePropertiesKHR(physicalDevice, pExternalFenceInfo, pExternalFenceProperties); }
#endif /// VK_KHR_external_fence_capabilities

#ifdef VK_KHR_external_fence_fd // "VK_KHR_external_fence_fd"
inline VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR *pImportFenceFdInfo) {
  vkObject::glb->ImportFenceFdKHR(device, pImportFenceFdInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR *pGetFdInfo, int *pFd) {
  vkObject::glb->GetFenceFdKHR(device, pGetFdInfo, pFd); }
#endif

#ifdef VK_KHR_performance_query // "VK_KHR_performance_query"
inline VKAPI_ATTR VkResult VKAPI_CALL vkEnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, uint32_t *pCounterCount, VkPerformanceCounterKHR *pCounters, VkPerformanceCounterDescriptionKHR *pCounterDescriptions) {
  vkObject::glb->EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR(physicalDevice, queueFamilyIndex, pCounterCount, pCounters, pCounterDescriptions); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(VkPhysicalDevice physicalDevice, const VkQueryPoolPerformanceCreateInfoKHR *pPerformanceQueryCreateInfo, uint32_t *pNumPasses) {
  vkObject::glb->GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR(physicalDevice, pPerformanceQueryCreateInfo, pNumPasses); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkAcquireProfilingLockKHR(VkDevice device, const VkAcquireProfilingLockInfoKHR *pInfo) {
  vkObject::glb->AcquireProfilingLockKHR(device, pInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkReleaseProfilingLockKHR(VkDevice device) {
  vkObject::glb->ReleaseProfilingLockKHR(device); }
#endif

#ifdef VK_KHR_get_surface_capabilities2 // "VK_KHR_get_surface_capabilities2"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo, VkSurfaceCapabilities2KHR *pSurfaceCapabilities) {
  vkObject::glb->GetPhysicalDeviceSurfaceCapabilities2KHR(physicalDevice, pSurfaceInfo, pSurfaceCapabilities); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo, uint32_t *pSurfaceFormatCount, VkSurfaceFormat2KHR *pSurfaceFormats) {
  vkObject::glb->GetPhysicalDeviceSurfaceFormats2KHR(physicalDevice, pSurfaceInfo, pSurfaceFormatCount, pSurfaceFormats); }
#endif

#ifdef VK_KHR_get_display_properties2 // "VK_KHR_get_display_properties2"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkDisplayProperties2KHR *pProperties) {
  vkObject::glb->GetPhysicalDeviceDisplayProperties2KHR(physicalDevice, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkDisplayPlaneProperties2KHR *pProperties) {
  vkObject::glb->GetPhysicalDeviceDisplayPlaneProperties2KHR(physicalDevice, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t *pPropertyCount, VkDisplayModeProperties2KHR *pProperties) {
  vkObject::glb->GetDisplayModeProperties2KHR(physicalDevice, display, pPropertyCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR *pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR *pCapabilities) {
  vkObject::glb->GetDisplayPlaneCapabilities2KHR(physicalDevice, pDisplayPlaneInfo, pCapabilities); }
#endif

#ifdef VK_KHR_get_memory_requirements2 // "VK_KHR_get_memory_requirements2"
inline VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2 *pInfo, VkMemoryRequirements2 *pMemoryRequirements) {
  vkObject::glb->GetImageMemoryRequirements2KHR(device, pInfo, pMemoryRequirements); }
inline VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2 *pInfo, VkMemoryRequirements2 *pMemoryRequirements) {
  vkObject::glb->GetBufferMemoryRequirements2KHR(device, pInfo, pMemoryRequirements); }
inline VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2 *pInfo, uint32_t *pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 *pSparseMemoryRequirements) {
  vkObject::glb->GetImageSparseMemoryRequirements2KHR(device, pInfo, pSparseMemoryRequirementCount, pSparseMemoryRequirements); }
#endif

#ifdef VK_KHR_sampler_ycbcr_conversion // "VK_KHR_sampler_ycbcr_conversion"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSamplerYcbcrConversion *pYcbcrConversion) {
  vkObject::glb->CreateSamplerYcbcrConversionKHR(device, pCreateInfo, pAllocator, pYcbcrConversion); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroySamplerYcbcrConversionKHR(device, ycbcrConversion, pAllocator); }
#endif

#ifdef VK_KHR_bind_memory2 // "VK_KHR_bind_memory2"
inline VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo *pBindInfos) {
  vkObject::glb->BindBufferMemory2KHR(device, bindInfoCount, pBindInfos); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo *pBindInfos) {
  vkObject::glb->BindImageMemory2KHR(device, bindInfoCount, pBindInfos); }
#endif

#ifdef VK_KHR_maintenance3 // "VK_KHR_maintenance3"
inline VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo *pCreateInfo, VkDescriptorSetLayoutSupport *pSupport) {
  vkObject::glb->GetDescriptorSetLayoutSupportKHR(device, pCreateInfo, pSupport); }
#endif

#ifdef VK_KHR_draw_indirect_count // "VK_KHR_draw_indirect_count"
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
  vkObject::glb->CmdDrawIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
  vkObject::glb->CmdDrawIndexedIndirectCountKHR(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride); }
#endif

#ifdef VK_KHR_timeline_semaphore // "VK_KHR_timeline_semaphore"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreCounterValueKHR(VkDevice device, VkSemaphore semaphore, uint64_t *pValue) {
  vkObject::glb->GetSemaphoreCounterValueKHR(device, semaphore, pValue); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkWaitSemaphoresKHR(VkDevice device, const VkSemaphoreWaitInfo *pWaitInfo, uint64_t timeout) {
  vkObject::glb->WaitSemaphoresKHR(device, pWaitInfo, timeout); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkSignalSemaphoreKHR(VkDevice device, const VkSemaphoreSignalInfo *pSignalInfo) {
  vkObject::glb->SignalSemaphoreKHR(device, pSignalInfo); }
#endif

#ifdef VK_KHR_pipeline_executable_properties // "VK_KHR_pipeline_executable_properties"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutablePropertiesKHR(VkDevice device, const VkPipelineInfoKHR *pPipelineInfo, uint32_t *pExecutableCount, VkPipelineExecutablePropertiesKHR *pProperties) {
  vkObject::glb->GetPipelineExecutablePropertiesKHR(device, pPipelineInfo, pExecutableCount, pProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutableStatisticsKHR(VkDevice device, const VkPipelineExecutableInfoKHR *pExecutableInfo, uint32_t *pStatisticCount, VkPipelineExecutableStatisticKHR *pStatistics) {
  vkObject::glb->GetPipelineExecutableStatisticsKHR(device, pExecutableInfo, pStatisticCount, pStatistics); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPipelineExecutableInternalRepresentationsKHR(VkDevice device, const VkPipelineExecutableInfoKHR *pExecutableInfo, uint32_t *pInternalRepresentationCount, VkPipelineExecutableInternalRepresentationKHR *pInternalRepresentations) {
  vkObject::glb->GetPipelineExecutableInternalRepresentationsKHR(device, pExecutableInfo, pInternalRepresentationCount, pInternalRepresentations); }
#endif

#ifdef VK_EXT_debug_report // "VK_EXT_debug_report"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugReportCallbackEXT *pCallback) {
  vkObject::glb->CreateDebugReportCallbackEXT(instance, pCreateInfo, pAllocator, pCallback); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyDebugReportCallbackEXT(instance, callback, pAllocator); }
inline VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char *pLayerPrefix, const char *pMessage) {
  vkObject::glb->DebugReportMessageEXT(instance, flags, objectType, object, location, messageCode, pLayerPrefix, pMessage); }
#endif

#ifdef VK_EXT_debug_marker // "VK_EXT_debug_marker"
inline VKAPI_ATTR VkResult VKAPI_CALL vkDebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT *pTagInfo) {
  vkObject::glb->DebugMarkerSetObjectTagEXT(device, pTagInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkDebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT *pNameInfo) {
  vkObject::glb->DebugMarkerSetObjectNameEXT(device, pNameInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT *pMarkerInfo) {
  vkObject::glb->CmdDebugMarkerBeginEXT(commandBuffer, pMarkerInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer) {
  vkObject::glb->CmdDebugMarkerEndEXT(commandBuffer); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT *pMarkerInfo) {
  vkObject::glb->CmdDebugMarkerInsertEXT(commandBuffer, pMarkerInfo); }
#endif

#ifdef VK_EXT_transform_feedback // "VK_EXT_transform_feedback"
inline VKAPI_ATTR void VKAPI_CALL vkCmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer *pBuffers, const VkDeviceSize *pOffsets, const VkDeviceSize *pSizes) {
  vkObject::glb->CmdBindTransformFeedbackBuffersEXT(commandBuffer, firstBinding, bindingCount, pBuffers, pOffsets, pSizes); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer *pCounterBuffers, const VkDeviceSize *pCounterBufferOffsets) {
  vkObject::glb->CmdBeginTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer *pCounterBuffers, const VkDeviceSize *pCounterBufferOffsets) {
  vkObject::glb->CmdEndTransformFeedbackEXT(commandBuffer, firstCounterBuffer, counterBufferCount, pCounterBuffers, pCounterBufferOffsets); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index) {
  vkObject::glb->CmdBeginQueryIndexedEXT(commandBuffer, queryPool, query, flags, index); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index) {
  vkObject::glb->CmdEndQueryIndexedEXT(commandBuffer, queryPool, query, index); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride) {
  vkObject::glb->CmdDrawIndirectByteCountEXT(commandBuffer, instanceCount, firstInstance, counterBuffer, counterBufferOffset, counterOffset, vertexStride); }
#endif

#ifdef VK_NVX_image_view_handle 
inline VKAPI_ATTR uint32_t VKAPI_CALL vkGetImageViewHandleNVX(VkDevice device, const VkImageViewHandleInfoNVX *pInfo) {
 vkObject::glb->GetImageViewHandleNVX(device, pInfo); }
#endif

#ifdef VK_AMD_draw_indirect_count // "VK_AMD_draw_indirect_count"
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
  vkObject::glb->CmdDrawIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
  vkObject::glb->CmdDrawIndexedIndirectCountAMD(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride); }
#endif

#ifdef VK_AMD_shader_info // "VK_AMD_shader_info"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t *pInfoSize, void *pInfo) {
  vkObject::glb->GetShaderInfoAMD(device, pipeline, shaderStage, infoType, pInfoSize, pInfo); }
#endif

#ifdef VK_NV_external_memory_capabilities // "VK_NV_external_memory_capabilities"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV *pExternalImageFormatProperties) {
  vkObject::glb->GetPhysicalDeviceExternalImageFormatPropertiesNV(physicalDevice, format, type, tiling, usage, flags, externalHandleType, pExternalImageFormatProperties); }
#endif

#ifdef VK_EXT_conditional_rendering // "VK_EXT_conditional_rendering"
inline VKAPI_ATTR void VKAPI_CALL vkCmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT *pConditionalRenderingBegin) {
  vkObject::glb->CmdBeginConditionalRenderingEXT(commandBuffer, pConditionalRenderingBegin); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer) {
  vkObject::glb->CmdEndConditionalRenderingEXT(commandBuffer); }
#endif

#ifdef VK_NVX_device_generated_commands // "VK_NVX_device_generated_commands"
inline VKAPI_ATTR void VKAPI_CALL vkCmdProcessCommandsNVX(VkCommandBuffer commandBuffer, const VkCmdProcessCommandsInfoNVX *pProcessCommandsInfo) {
  vkObject::glb->CmdProcessCommandsNVX(commandBuffer, pProcessCommandsInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdReserveSpaceForCommandsNVX(VkCommandBuffer commandBuffer, const VkCmdReserveSpaceForCommandsInfoNVX *pReserveSpaceInfo) {
  vkObject::glb->CmdReserveSpaceForCommandsNVX(commandBuffer, pReserveSpaceInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateIndirectCommandsLayoutNVX(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNVX *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkIndirectCommandsLayoutNVX *pIndirectCommandsLayout) {
  vkObject::glb->CreateIndirectCommandsLayoutNVX(device, pCreateInfo, pAllocator, pIndirectCommandsLayout); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyIndirectCommandsLayoutNVX(VkDevice device, VkIndirectCommandsLayoutNVX indirectCommandsLayout, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyIndirectCommandsLayoutNVX(device, indirectCommandsLayout, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateObjectTableNVX(VkDevice device, const VkObjectTableCreateInfoNVX *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkObjectTableNVX *pObjectTable) {
  vkObject::glb->CreateObjectTableNVX(device, pCreateInfo, pAllocator, pObjectTable); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyObjectTableNVX(VkDevice device, VkObjectTableNVX objectTable, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyObjectTableNVX(device, objectTable, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkRegisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, const VkObjectTableEntryNVX *const *ppObjectTableEntries, const uint32_t *pObjectIndices) {
  vkObject::glb->RegisterObjectsNVX(device, objectTable, objectCount, ppObjectTableEntries, pObjectIndices); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkUnregisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, const VkObjectEntryTypeNVX *pObjectEntryTypes, const uint32_t *pObjectIndices) {
  vkObject::glb->UnregisterObjectsNVX(device, objectTable, objectCount, pObjectEntryTypes, pObjectIndices); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(VkPhysicalDevice physicalDevice, VkDeviceGeneratedCommandsFeaturesNVX *pFeatures, VkDeviceGeneratedCommandsLimitsNVX *pLimits) {
  vkObject::glb->GetPhysicalDeviceGeneratedCommandsPropertiesNVX(physicalDevice, pFeatures, pLimits); }
#endif

#ifdef VK_NV_clip_space_w_scaling // "VK_NV_clip_space_w_scaling"
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV *pViewportWScalings) {
  vkObject::glb->CmdSetViewportWScalingNV(commandBuffer, firstViewport, viewportCount, pViewportWScalings); }
#endif

#ifdef VK_EXT_direct_mode_display // "VK_EXT_direct_mode_display"
inline VKAPI_ATTR VkResult VKAPI_CALL vkReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display) {
  vkObject::glb->ReleaseDisplayEXT(physicalDevice, display); }
#endif

#ifdef VK_EXT_display_surface_counter // "VK_EXT_display_surface_counter"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT *pSurfaceCapabilities) {
  vkObject::glb->GetPhysicalDeviceSurfaceCapabilities2EXT(physicalDevice, surface, pSurfaceCapabilities); }
#endif

#ifdef VK_EXT_display_control // "VK_EXT_display_control"
inline VKAPI_ATTR VkResult VKAPI_CALL vkDisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT *pDisplayPowerInfo) {
  vkObject::glb->DisplayPowerControlEXT(device, display, pDisplayPowerInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkRegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT *pDeviceEventInfo, const VkAllocationCallbacks *pAllocator, VkFence *pFence) {
  vkObject::glb->RegisterDeviceEventEXT(device, pDeviceEventInfo, pAllocator, pFence); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkRegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT *pDisplayEventInfo, const VkAllocationCallbacks *pAllocator, VkFence *pFence) {
  vkObject::glb->RegisterDisplayEventEXT(device, display, pDisplayEventInfo, pAllocator, pFence); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t *pCounterValue) {
  vkObject::glb->GetSwapchainCounterEXT(device, swapchain, counter, pCounterValue); }
#endif

#ifdef VK_GOOGLE_display_timing // "VK_GOOGLE_display_timing"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE *pDisplayTimingProperties) {
  vkObject::glb->GetRefreshCycleDurationGOOGLE(device, swapchain, pDisplayTimingProperties); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t *pPresentationTimingCount, VkPastPresentationTimingGOOGLE *pPresentationTimings) {
  vkObject::glb->GetPastPresentationTimingGOOGLE(device, swapchain, pPresentationTimingCount, pPresentationTimings); }
#endif

#ifdef VK_EXT_discard_rectangles // "VK_EXT_discard_rectangles"
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D *pDiscardRectangles) {
  vkObject::glb->CmdSetDiscardRectangleEXT(commandBuffer, firstDiscardRectangle, discardRectangleCount, pDiscardRectangles); }
#endif

#ifdef VK_EXT_hdr_metadata // "VK_EXT_hdr_metadata"
inline VKAPI_ATTR void VKAPI_CALL vkSetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR *pSwapchains, const VkHdrMetadataEXT *pMetadata) {
  vkObject::glb->SetHdrMetadataEXT(device, swapchainCount, pSwapchains, pMetadata); }
#endif
  
#ifdef VK_EXT_debug_utils // "VK_EXT_debug_utils"
inline VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT *pNameInfo) {
  vkObject::glb->SetDebugUtilsObjectNameEXT(device, pNameInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT *pTagInfo) {
  vkObject::glb->SetDebugUtilsObjectTagEXT(device, pTagInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT *pLabelInfo) {
  vkObject::glb->QueueBeginDebugUtilsLabelEXT(queue, pLabelInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkQueueEndDebugUtilsLabelEXT(VkQueue queue) {
  vkObject::glb->QueueEndDebugUtilsLabelEXT(queue); }
inline VKAPI_ATTR void VKAPI_CALL vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT *pLabelInfo) {
  vkObject::glb->QueueInsertDebugUtilsLabelEXT(queue, pLabelInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT *pLabelInfo) {
  vkObject::glb->CmdBeginDebugUtilsLabelEXT(commandBuffer, pLabelInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer) {
  vkObject::glb->CmdEndDebugUtilsLabelEXT(commandBuffer); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT *pLabelInfo) {
  vkObject::glb->CmdInsertDebugUtilsLabelEXT(commandBuffer, pLabelInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pMessenger) {
  vkObject::glb->CreateDebugUtilsMessengerEXT(instance, pCreateInfo, pAllocator, pMessenger); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyDebugUtilsMessengerEXT(instance, messenger, pAllocator); }
inline VKAPI_ATTR void VKAPI_CALL vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData) {
  vkObject::glb->SubmitDebugUtilsMessageEXT(instance, messageSeverity, messageTypes, pCallbackData); }
#endif

#ifdef VK_EXT_sample_locations // "VK_EXT_sample_locations"
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT *pSampleLocationsInfo) {
  vkObject::glb->CmdSetSampleLocationsEXT(commandBuffer, pSampleLocationsInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT *pMultisampleProperties) {
  vkObject::glb->GetPhysicalDeviceMultisamplePropertiesEXT(physicalDevice, samples, pMultisampleProperties); }
#endif

#ifdef VK_EXT_image_drm_format_modifier // "VK_EXT_image_drm_format_modifier"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT *pProperties) {
  vkObject::glb->GetImageDrmFormatModifierPropertiesEXT(device, image, pProperties); }
#endif

#ifdef VK_EXT_validation_cache // "VK_EXT_validation_cache"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkValidationCacheEXT *pValidationCache) {
  vkObject::glb->CreateValidationCacheEXT(device, pCreateInfo, pAllocator, pValidationCache); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyValidationCacheEXT(device, validationCache, pAllocator); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkMergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT *pSrcCaches) {
  vkObject::glb->MergeValidationCachesEXT(device, dstCache, srcCacheCount, pSrcCaches); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t *pDataSize, void *pData) {
  vkObject::glb->GetValidationCacheDataEXT(device, validationCache, pDataSize, pData); }
#endif

#ifdef VK_NV_shading_rate_image // "VK_NV_shading_rate_image"
inline VKAPI_ATTR void VKAPI_CALL vkCmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout) {
  vkObject::glb->CmdBindShadingRateImageNV(commandBuffer, imageView, imageLayout); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV *pShadingRatePalettes) {
  vkObject::glb->CmdSetViewportShadingRatePaletteNV(commandBuffer, firstViewport, viewportCount, pShadingRatePalettes); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV *pCustomSampleOrders) {
  vkObject::glb->CmdSetCoarseSampleOrderNV(commandBuffer, sampleOrderType, customSampleOrderCount, pCustomSampleOrders); }
#endif

#ifdef VK_NV_ray_tracing // "VK_NV_ray_tracing"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkAccelerationStructureNV *pAccelerationStructure) {
  vkObject::glb->CreateAccelerationStructureNV(device, pCreateInfo, pAllocator, pAccelerationStructure); }
inline VKAPI_ATTR void VKAPI_CALL vkDestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks *pAllocator) {
  vkObject::glb->DestroyAccelerationStructureNV(device, accelerationStructure, pAllocator); }
inline VKAPI_ATTR void VKAPI_CALL vkGetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV *pInfo, VkMemoryRequirements2KHR *pMemoryRequirements) {
  vkObject::glb->GetAccelerationStructureMemoryRequirementsNV(device, pInfo, pMemoryRequirements); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkBindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV *pBindInfos) {
  vkObject::glb->BindAccelerationStructureMemoryNV(device, bindInfoCount, pBindInfos); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV *pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset) {
  vkObject::glb->CmdBuildAccelerationStructureNV(commandBuffer, pInfo, instanceData, instanceOffset, update, dst, src, scratch, scratchOffset); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeNV mode) {
  vkObject::glb->CmdCopyAccelerationStructureNV(commandBuffer, dst, src, mode); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth) {
  vkObject::glb->CmdTraceRaysNV(commandBuffer, raygenShaderBindingTableBuffer, raygenShaderBindingOffset, missShaderBindingTableBuffer, missShaderBindingOffset, missShaderBindingStride, hitShaderBindingTableBuffer, hitShaderBindingOffset, hitShaderBindingStride, callableShaderBindingTableBuffer, callableShaderBindingOffset, callableShaderBindingStride, width, height, depth); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV *pCreateInfos, const VkAllocationCallbacks *pAllocator, VkPipeline *pPipelines) {
  vkObject::glb->CreateRayTracingPipelinesNV(device, pipelineCache, createInfoCount, pCreateInfos, pAllocator, pPipelines); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void *pData) {
  vkObject::glb->GetRayTracingShaderGroupHandlesNV(device, pipeline, firstGroup, groupCount, dataSize, pData); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void *pData) {
  vkObject::glb->GetAccelerationStructureHandleNV(device, accelerationStructure, dataSize, pData); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV *pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery) {
  vkObject::glb->CmdWriteAccelerationStructuresPropertiesNV(commandBuffer, accelerationStructureCount, pAccelerationStructures, queryType, queryPool, firstQuery); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader) {
  vkObject::glb->CompileDeferredNV(device, pipeline, shader); }
#endif

#ifdef VK_EXT_external_memory_host // "VK_EXT_external_memory_host"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void *pHostPointer, VkMemoryHostPointerPropertiesEXT *pMemoryHostPointerProperties) {
  vkObject::glb->GetMemoryHostPointerPropertiesEXT(device, handleType, pHostPointer, pMemoryHostPointerProperties); }
#endif

#ifdef VK_AMD_buffer_marker // "VK_AMD_buffer_marker"
inline VKAPI_ATTR void VKAPI_CALL vkCmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker) {
  vkObject::glb->CmdWriteBufferMarkerAMD(commandBuffer, pipelineStage, dstBuffer, dstOffset, marker); }
#endif

#ifdef VK_EXT_calibrated_timestamps // "VK_EXT_calibrated_timestamps"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice physicalDevice, uint32_t *pTimeDomainCount, VkTimeDomainEXT *pTimeDomains) {
  vkObject::glb->GetPhysicalDeviceCalibrateableTimeDomainsEXT(physicalDevice, pTimeDomainCount, pTimeDomains); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT *pTimestampInfos, uint64_t *pTimestamps, uint64_t *pMaxDeviation) {
  vkObject::glb->GetCalibratedTimestampsEXT(device, timestampCount, pTimestampInfos, pTimestamps, pMaxDeviation); }
#endif

#ifdef VK_NV_mesh_shader // "VK_NV_mesh_shader"
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask) {
  vkObject::glb->CmdDrawMeshTasksNV(commandBuffer, taskCount, firstTask); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride) {
  vkObject::glb->CmdDrawMeshTasksIndirectNV(commandBuffer, buffer, offset, drawCount, stride); }
inline VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride) {
  vkObject::glb->CmdDrawMeshTasksIndirectCountNV(commandBuffer, buffer, offset, countBuffer, countBufferOffset, maxDrawCount, stride); }
#endif

#ifdef VK_NV_scissor_exclusive // "VK_NV_scissor_exclusive"
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D *pExclusiveScissors) {
  vkObject::glb->CmdSetExclusiveScissorNV(commandBuffer, firstExclusiveScissor, exclusiveScissorCount, pExclusiveScissors); }
#endif

#ifdef VK_NV_device_diagnostic_checkpoints // "VK_NV_device_diagnostic_checkpoints"
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void *pCheckpointMarker) {
  vkObject::glb->CmdSetCheckpointNV(commandBuffer, pCheckpointMarker); }
inline VKAPI_ATTR void VKAPI_CALL vkGetQueueCheckpointDataNV(VkQueue queue, uint32_t *pCheckpointDataCount, VkCheckpointDataNV *pCheckpointData) {
  vkObject::glb->GetQueueCheckpointDataNV(queue, pCheckpointDataCount, pCheckpointData); }
#endif

#ifdef VK_INTEL_performance_query // "VK_INTEL_performance_query"
inline VKAPI_ATTR VkResult VKAPI_CALL vkInitializePerformanceApiINTEL(VkDevice device, const VkInitializePerformanceApiInfoINTEL *pInitializeInfo) {
  vkObject::glb->InitializePerformanceApiINTEL(device, pInitializeInfo); }
inline VKAPI_ATTR void VKAPI_CALL vkUninitializePerformanceApiINTEL(VkDevice device) {
  vkObject::glb->UninitializePerformanceApiINTEL(device); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCmdSetPerformanceMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceMarkerInfoINTEL *pMarkerInfo) {
  vkObject::glb->CmdSetPerformanceMarkerINTEL(commandBuffer, pMarkerInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCmdSetPerformanceStreamMarkerINTEL(VkCommandBuffer commandBuffer, const VkPerformanceStreamMarkerInfoINTEL *pMarkerInfo) {
  vkObject::glb->CmdSetPerformanceStreamMarkerINTEL(commandBuffer, pMarkerInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkCmdSetPerformanceOverrideINTEL(VkCommandBuffer commandBuffer, const VkPerformanceOverrideInfoINTEL *pOverrideInfo) {
  vkObject::glb->CmdSetPerformanceOverrideINTEL(commandBuffer, pOverrideInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkAcquirePerformanceConfigurationINTEL(VkDevice device, const VkPerformanceConfigurationAcquireInfoINTEL *pAcquireInfo, VkPerformanceConfigurationINTEL *pConfiguration) {
  vkObject::glb->AcquirePerformanceConfigurationINTEL(device, pAcquireInfo, pConfiguration); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkReleasePerformanceConfigurationINTEL(VkDevice device, VkPerformanceConfigurationINTEL configuration) {
  vkObject::glb->ReleasePerformanceConfigurationINTEL(device, configuration); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkQueueSetPerformanceConfigurationINTEL(VkQueue queue, VkPerformanceConfigurationINTEL configuration) {
  vkObject::glb->QueueSetPerformanceConfigurationINTEL(queue, configuration); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPerformanceParameterINTEL(VkDevice device, VkPerformanceParameterTypeINTEL parameter, VkPerformanceValueINTEL *pValue) {
  vkObject::glb->GetPerformanceParameterINTEL(device, parameter, pValue); }
#endif

#ifdef VK_AMD_display_native_hdr
inline VKAPI_ATTR void VKAPI_CALL vkSetLocalDimmingAMD(VkDevice device, VkSwapchainKHR swapChain, VkBool32 localDimmingEnable) {
  vkObject::glb->SetLocalDimmingAMD(device, swapChain, localDimmingEnable); }
#endif

#ifdef VK_EXT_buffer_device_address
inline VKAPI_ATTR VkDeviceAddress VKAPI_CALL vkGetBufferDeviceAddressEXT(VkDevice device, const VkBufferDeviceAddressInfo *pInfo) {
  vkObject::glb->GetBufferDeviceAddressEXT(device, pInfo); }
#endif

#ifdef VK_EXT_tooling_info
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceToolPropertiesEXT(VkPhysicalDevice physicalDevice, uint32_t *pToolCount, VkPhysicalDeviceToolPropertiesEXT *pToolProperties) {
  vkObject::glb->GetPhysicalDeviceToolPropertiesEXT(physicalDevice, pToolCount, pToolProperties); }
#endif

#ifdef VK_NV_cooperative_matrix
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCooperativeMatrixPropertiesNV(VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkCooperativeMatrixPropertiesNV *pProperties) {
  vkObject::glb->GetPhysicalDeviceCooperativeMatrixPropertiesNV(physicalDevice, pPropertyCount, pProperties); }
#endif

#ifdef VK_EXT_headless_surface
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateHeadlessSurfaceEXT(VkInstance instance, const VkHeadlessSurfaceCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
  vkObject::glb->CreateHeadlessSurfaceEXT(instance, pCreateInfo, pAllocator, pSurface); }
#endif

#ifdef VK_EXT_line_rasterization
inline VKAPI_ATTR void VKAPI_CALL vkCmdSetLineStippleEXT(VkCommandBuffer commandBuffer, uint32_t lineStippleFactor, uint16_t lineStipplePattern) {
  vkObject::glb->CmdSetLineStippleEXT(commandBuffer, lineStippleFactor, lineStipplePattern); }
#endif

#ifdef VK_EXT_host_query_reset
inline VKAPI_ATTR void VKAPI_CALL vkResetQueryPoolEXT(VkDevice device, VkQueryPool queryPool, uint32_t firstQuery, uint32_t queryCount) {
  vkObject::glb->ResetQueryPoolEXT(device, queryPool, firstQuery, queryCount); }
#endif




// MAC OS specific =========================================================================================

#ifdef VK_MVK_macos_surface // "VK_MVK_macos_surface"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateMacOSSurfaceMVK(VkInstance instance, const VkMacOSSurfaceCreateInfoMVK *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
  vkObject::glb->CreateMacOSSurfaceMVK(instance, pCreateInfo, pAllocator, pSurface); }
#endif

// WAYLAND specific ========================================================================================

#ifdef VK_KHR_wayland_surface // "VK_KHR_wayland_surface"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
  vkObject::glb->CreateWaylandSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface); }
inline VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display *display) {
  vkObject::glb->GetPhysicalDeviceWaylandPresentationSupportKHR(physicalDevice, queueFamilyIndex, display); }
#endif

// WINDOWS specifi =========================================================================================

#ifdef VK_KHR_win32_surface // "VK_KHR_win32_surface"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
  vkObject::glb->CreateWin32SurfaceKHR(instance, pCreateInfo, pAllocator, pSurface); }
inline VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex) {
  vkObject::glb->GetPhysicalDeviceWin32PresentationSupportKHR(physicalDevice, queueFamilyIndex); }
#endif

#ifdef VK_KHR_external_memory_win32 // "VK_KHR_external_memory_win32"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR *pGetWin32HandleInfo, HANDLE *pHandle) {
  vkObject::glb->GetMemoryWin32HandleKHR(device, pGetWin32HandleInfo, pHandle); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR *pMemoryWin32HandleProperties) {
  vkObject::glb->GetMemoryWin32HandlePropertiesKHR(device, handleType, handle, pMemoryWin32HandleProperties); }
#endif
  
#ifdef VK_KHR_external_semaphore_win32 // "VK_KHR_external_semaphore_win32"
inline VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR *pImportSemaphoreWin32HandleInfo) {
  vkObject::glb->ImportSemaphoreWin32HandleKHR(device, pImportSemaphoreWin32HandleInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR *pGetWin32HandleInfo, HANDLE *pHandle) {
  vkObject::glb->GetSemaphoreWin32HandleKHR(device, pGetWin32HandleInfo, pHandle); }
#endif

#ifdef VK_KHR_external_fence_win32 // "VK_KHR_external_fence_win32"
inline VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR *pImportFenceWin32HandleInfo) {
  vkObject::glb->ImportFenceWin32HandleKHR(device, pImportFenceWin32HandleInfo); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR *pGetWin32HandleInfo, HANDLE *pHandle) {
  vkObject::glb->GetFenceWin32HandleKHR(device, pGetWin32HandleInfo, pHandle); }
#endif

#ifdef VK_NV_external_memory_win32 // "VK_NV_external_memory_win32"
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE *pHandle) {
  vkObject::glb->GetMemoryWin32HandleNV(device, memory, handleType, pHandle); }
#endif

// LINUX XCB specific ======================================================================================

#ifdef VK_KHR_xcb_surface // "VK_KHR_xcb_surface"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
  vkObject::glb->CreateXcbSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface); }
inline VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t *connection, xcb_visualid_t visual_id) {
  vkObject::glb->GetPhysicalDeviceXcbPresentationSupportKHR(physicalDevice, queueFamilyIndex, connection, visual_id); }
#endif

// LINUX XLIB specific =====================================================================================

#ifdef VK_KHR_xlib_surface // "VK_KHR_xlib_surface"
inline VKAPI_ATTR VkResult VKAPI_CALL vkCreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface) {
  vkObject::glb->CreateXlibSurfaceKHR(instance, pCreateInfo, pAllocator, pSurface); }
inline VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display *dpy, VisualID visualID) {
  vkObject::glb->GetPhysicalDeviceXlibPresentationSupportKHR(physicalDevice, queueFamilyIndex, dpy, visualID); }
#endif

// LINUX XRANDR specific ===================================================================================

#ifdef VK_EXT_acquire_xlib_display // "VK_EXT_acquire_xlib_display"
inline VKAPI_ATTR VkResult VKAPI_CALL vkAcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display *dpy, VkDisplayKHR display) {
  vkObject::glb->AcquireXlibDisplayEXT(physicalDevice, dpy, display); }
inline VKAPI_ATTR VkResult VKAPI_CALL vkGetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display *dpy, RROutput rrOutput, VkDisplayKHR *pDisplay) {
  vkObject::glb->GetRandROutputDisplayEXT(physicalDevice, dpy, rrOutput, pDisplay); }
#endif


#endif // VKO_USE_GLOBAL_FUNCS



