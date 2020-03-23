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




#define VKO_FUNC(func) PFN_vk##func func


struct VkoFuncs {
  bool critInit, instInit, devInit;
  VkoFuncs();

  // critical funcs, avaible from start - at least these 5 will be declared no matter what
  VKO_FUNC(GetInstanceProcAddr);                      // vulkan 1.0
  VKO_FUNC(CreateInstance);                           // vulkan 1.0
  VKO_FUNC(EnumerateInstanceExtensionProperties);     // vulkan 1.0
  VKO_FUNC(EnumerateInstanceLayerProperties);         // vulkan 1.0
  VKO_FUNC(EnumerateInstanceVersion);                 // vulkan 1.1

  // VULKAN 1.0 ========================================================================
  #ifdef VK_VERSION_1_0
  //VKO_FUNC(CreateInstance);                          // 1.0 critical func, avaible from start
  VKO_FUNC(DestroyInstance);
  VKO_FUNC(EnumeratePhysicalDevices);
  VKO_FUNC(GetPhysicalDeviceFeatures);
  VKO_FUNC(GetPhysicalDeviceFormatProperties);
  VKO_FUNC(GetPhysicalDeviceImageFormatProperties);
  VKO_FUNC(GetPhysicalDeviceProperties);
  VKO_FUNC(GetPhysicalDeviceQueueFamilyProperties);
  VKO_FUNC(GetPhysicalDeviceMemoryProperties);
  //VKO_FUNC(GetInstanceProcAddr);                       // 1.0 critical func, avaible from start
  VKO_FUNC(GetDeviceProcAddr);
  VKO_FUNC(CreateDevice);
  VKO_FUNC(DestroyDevice);
  //VKO_FUNC(EnumerateInstanceExtensionProperties);    // 1.0 critical func, avaible from start
  VKO_FUNC(EnumerateDeviceExtensionProperties);      
  //VKO_FUNC(EnumerateInstanceLayerProperties);        // 1.0 critical func, avaible from start
  VKO_FUNC(EnumerateDeviceLayerProperties);
  VKO_FUNC(GetDeviceQueue);
  VKO_FUNC(QueueSubmit);
  VKO_FUNC(QueueWaitIdle);
  VKO_FUNC(DeviceWaitIdle);
  VKO_FUNC(AllocateMemory);
  VKO_FUNC(FreeMemory);
  VKO_FUNC(MapMemory);
  VKO_FUNC(UnmapMemory);
  VKO_FUNC(FlushMappedMemoryRanges);
  VKO_FUNC(InvalidateMappedMemoryRanges);
  VKO_FUNC(GetDeviceMemoryCommitment);
  VKO_FUNC(BindBufferMemory);
  VKO_FUNC(BindImageMemory);
  VKO_FUNC(GetBufferMemoryRequirements);
  VKO_FUNC(GetImageMemoryRequirements);
  VKO_FUNC(GetImageSparseMemoryRequirements);
  VKO_FUNC(GetPhysicalDeviceSparseImageFormatProperties);
  VKO_FUNC(QueueBindSparse);
  VKO_FUNC(CreateFence);
  VKO_FUNC(DestroyFence);
  VKO_FUNC(ResetFences);
  VKO_FUNC(GetFenceStatus);
  VKO_FUNC(WaitForFences);
  VKO_FUNC(CreateSemaphore);
  VKO_FUNC(DestroySemaphore);
  VKO_FUNC(CreateEvent);
  VKO_FUNC(DestroyEvent);
  VKO_FUNC(GetEventStatus);
  VKO_FUNC(SetEvent);
  VKO_FUNC(ResetEvent);
  VKO_FUNC(CreateQueryPool);
  VKO_FUNC(DestroyQueryPool);
  VKO_FUNC(GetQueryPoolResults);
  VKO_FUNC(CreateBuffer);
  VKO_FUNC(DestroyBuffer);
  VKO_FUNC(CreateBufferView);
  VKO_FUNC(DestroyBufferView);
  VKO_FUNC(CreateImage);
  VKO_FUNC(DestroyImage);
  VKO_FUNC(GetImageSubresourceLayout);
  VKO_FUNC(CreateImageView);
  VKO_FUNC(DestroyImageView);
  VKO_FUNC(CreateShaderModule);
  VKO_FUNC(DestroyShaderModule);
  VKO_FUNC(CreatePipelineCache);
  VKO_FUNC(DestroyPipelineCache);
  VKO_FUNC(GetPipelineCacheData);
  VKO_FUNC(MergePipelineCaches);
  VKO_FUNC(CreateGraphicsPipelines);
  VKO_FUNC(CreateComputePipelines);
  VKO_FUNC(DestroyPipeline);
  VKO_FUNC(CreatePipelineLayout);
  VKO_FUNC(DestroyPipelineLayout);
  VKO_FUNC(CreateSampler);
  VKO_FUNC(DestroySampler);
  VKO_FUNC(CreateDescriptorSetLayout);
  VKO_FUNC(DestroyDescriptorSetLayout);
  VKO_FUNC(CreateDescriptorPool);
  VKO_FUNC(DestroyDescriptorPool);
  VKO_FUNC(ResetDescriptorPool);
  VKO_FUNC(AllocateDescriptorSets);
  VKO_FUNC(FreeDescriptorSets);
  VKO_FUNC(UpdateDescriptorSets);
  VKO_FUNC(CreateFramebuffer);
  VKO_FUNC(DestroyFramebuffer);
  VKO_FUNC(CreateRenderPass);
  VKO_FUNC(DestroyRenderPass);
  VKO_FUNC(GetRenderAreaGranularity);
  VKO_FUNC(CreateCommandPool);
  VKO_FUNC(DestroyCommandPool);
  VKO_FUNC(ResetCommandPool);
  VKO_FUNC(AllocateCommandBuffers);
  VKO_FUNC(FreeCommandBuffers);
  VKO_FUNC(BeginCommandBuffer);
  VKO_FUNC(EndCommandBuffer);
  VKO_FUNC(ResetCommandBuffer);
  VKO_FUNC(CmdBindPipeline);
  VKO_FUNC(CmdSetViewport);
  VKO_FUNC(CmdSetScissor);
  VKO_FUNC(CmdSetLineWidth);
  VKO_FUNC(CmdSetDepthBias);
  VKO_FUNC(CmdSetBlendConstants);
  VKO_FUNC(CmdSetDepthBounds);
  VKO_FUNC(CmdSetStencilCompareMask);
  VKO_FUNC(CmdSetStencilWriteMask);
  VKO_FUNC(CmdSetStencilReference);
  VKO_FUNC(CmdBindDescriptorSets);
  VKO_FUNC(CmdBindIndexBuffer);
  VKO_FUNC(CmdBindVertexBuffers);
  VKO_FUNC(CmdDraw);
  VKO_FUNC(CmdDrawIndexed);
  VKO_FUNC(CmdDrawIndirect);
  VKO_FUNC(CmdDrawIndexedIndirect);
  VKO_FUNC(CmdDispatch);
  VKO_FUNC(CmdDispatchIndirect);
  VKO_FUNC(CmdCopyBuffer);
  VKO_FUNC(CmdCopyImage);
  VKO_FUNC(CmdBlitImage);
  VKO_FUNC(CmdCopyBufferToImage);
  VKO_FUNC(CmdCopyImageToBuffer);
  VKO_FUNC(CmdUpdateBuffer);
  VKO_FUNC(CmdFillBuffer);
  VKO_FUNC(CmdClearColorImage);
  VKO_FUNC(CmdClearDepthStencilImage);
  VKO_FUNC(CmdClearAttachments);
  VKO_FUNC(CmdResolveImage);
  VKO_FUNC(CmdSetEvent);
  VKO_FUNC(CmdResetEvent);
  VKO_FUNC(CmdWaitEvents);
  VKO_FUNC(CmdPipelineBarrier);
  VKO_FUNC(CmdBeginQuery);
  VKO_FUNC(CmdEndQuery);
  VKO_FUNC(CmdResetQueryPool);
  VKO_FUNC(CmdWriteTimestamp);
  VKO_FUNC(CmdCopyQueryPoolResults);
  VKO_FUNC(CmdPushConstants);
  VKO_FUNC(CmdBeginRenderPass);
  VKO_FUNC(CmdNextSubpass);
  VKO_FUNC(CmdEndRenderPass);
  VKO_FUNC(CmdExecuteCommands);
  #endif // VK_VERSION_1_0

  // VULKAN 1.1 ========================================================================
  #ifdef VK_VERSION_1_1
  //VKO_FUNC(EnumerateInstanceVersion);                // 1.1 critical func, avaible from start
  VKO_FUNC(BindBufferMemory2);
  VKO_FUNC(BindImageMemory2);
  VKO_FUNC(GetDeviceGroupPeerMemoryFeatures);
  VKO_FUNC(CmdSetDeviceMask);
  VKO_FUNC(CmdDispatchBase);
  VKO_FUNC(EnumeratePhysicalDeviceGroups);
  VKO_FUNC(GetImageMemoryRequirements2);
  VKO_FUNC(GetBufferMemoryRequirements2);
  VKO_FUNC(GetImageSparseMemoryRequirements2);
  VKO_FUNC(GetPhysicalDeviceFeatures2);
  VKO_FUNC(GetPhysicalDeviceProperties2);
  VKO_FUNC(GetPhysicalDeviceFormatProperties2);
  VKO_FUNC(GetPhysicalDeviceImageFormatProperties2);
  VKO_FUNC(GetPhysicalDeviceQueueFamilyProperties2);
  VKO_FUNC(GetPhysicalDeviceMemoryProperties2);
  VKO_FUNC(GetPhysicalDeviceSparseImageFormatProperties2);
  VKO_FUNC(TrimCommandPool);
  VKO_FUNC(GetDeviceQueue2);
  VKO_FUNC(CreateSamplerYcbcrConversion);
  VKO_FUNC(DestroySamplerYcbcrConversion);
  VKO_FUNC(CreateDescriptorUpdateTemplate);
  VKO_FUNC(DestroyDescriptorUpdateTemplate);
  VKO_FUNC(UpdateDescriptorSetWithTemplate);
  VKO_FUNC(GetPhysicalDeviceExternalBufferProperties);
  VKO_FUNC(GetPhysicalDeviceExternalFenceProperties);
  VKO_FUNC(GetPhysicalDeviceExternalSemaphoreProperties);
  VKO_FUNC(GetDescriptorSetLayoutSupport);
  #endif // VK_VERSION_1_1

  // VULKAN 1.2 ========================================================================
  #ifdef VK_VERSION_1_2
  VKO_FUNC(CmdDrawIndirectCount);
  VKO_FUNC(CmdDrawIndexedIndirectCount);
  VKO_FUNC(CreateRenderPass2);
  VKO_FUNC(CmdBeginRenderPass2);
  VKO_FUNC(CmdNextSubpass2);
  VKO_FUNC(CmdEndRenderPass2);
  VKO_FUNC(ResetQueryPool);
  VKO_FUNC(GetSemaphoreCounterValue);
  VKO_FUNC(WaitSemaphores);
  VKO_FUNC(SignalSemaphore);
  VKO_FUNC(GetBufferDeviceAddress);
  VKO_FUNC(GetBufferOpaqueCaptureAddress);
  VKO_FUNC(GetDeviceMemoryOpaqueCaptureAddress);
  #endif // VK_VERSION_1_2








  // EXTENSIONS =============================================================================


  #ifdef VK_KHR_surface // "VK_KHR_surface"
  VKO_FUNC(DestroySurfaceKHR);
  VKO_FUNC(GetPhysicalDeviceSurfaceSupportKHR);
  VKO_FUNC(GetPhysicalDeviceSurfaceCapabilitiesKHR);
  VKO_FUNC(GetPhysicalDeviceSurfaceFormatsKHR);
  VKO_FUNC(GetPhysicalDeviceSurfacePresentModesKHR);
  #endif /// VK_KHR_surface

  #ifdef VK_KHR_swapchain // "VK_KHR_swapchain"
  VKO_FUNC(CreateSwapchainKHR);
  VKO_FUNC(DestroySwapchainKHR);
  VKO_FUNC(GetSwapchainImagesKHR);
  VKO_FUNC(AcquireNextImageKHR);
  VKO_FUNC(QueuePresentKHR);
  VKO_FUNC(GetDeviceGroupPresentCapabilitiesKHR);
  VKO_FUNC(GetDeviceGroupSurfacePresentModesKHR);
  VKO_FUNC(GetPhysicalDevicePresentRectanglesKHR);
  VKO_FUNC(AcquireNextImage2KHR);
  #endif /// VK_KHR_swapchain

  #ifdef VK_KHR_display // "VK_KHR_display"
  VKO_FUNC(GetPhysicalDeviceDisplayPropertiesKHR);
  VKO_FUNC(GetPhysicalDeviceDisplayPlanePropertiesKHR);
  VKO_FUNC(GetDisplayPlaneSupportedDisplaysKHR);
  VKO_FUNC(GetDisplayModePropertiesKHR);
  VKO_FUNC(CreateDisplayModeKHR);
  VKO_FUNC(GetDisplayPlaneCapabilitiesKHR);
  VKO_FUNC(CreateDisplayPlaneSurfaceKHR);
  #endif /// VK_KHR_display

  #ifdef VK_KHR_display_swapchain // "VK_KHR_display_swapchain"
  VKO_FUNC(CreateSharedSwapchainsKHR);
  #endif /// VK_KHR_display_swapchain

  #ifdef VK_KHR_get_physical_device_properties2 // "VK_KHR_get_physical_device_properties2"
  VKO_FUNC(GetPhysicalDeviceFeatures2KHR);
  VKO_FUNC(GetPhysicalDeviceProperties2KHR);
  VKO_FUNC(GetPhysicalDeviceFormatProperties2KHR);
  VKO_FUNC(GetPhysicalDeviceImageFormatProperties2KHR);
  VKO_FUNC(GetPhysicalDeviceQueueFamilyProperties2KHR);
  VKO_FUNC(GetPhysicalDeviceMemoryProperties2KHR);
  VKO_FUNC(GetPhysicalDeviceSparseImageFormatProperties2KHR);
  #endif /// VK_KHR_get_physical_device_properties2

  #ifdef VK_KHR_device_group // "VK_KHR_device_group"
  VKO_FUNC(GetDeviceGroupPeerMemoryFeaturesKHR);
  VKO_FUNC(CmdSetDeviceMaskKHR);
  VKO_FUNC(CmdDispatchBaseKHR);
  #endif /// VK_KHR_device_group

  #ifdef VK_KHR_maintenance1 // "VK_KHR_maintenance1"
  VKO_FUNC(TrimCommandPoolKHR);
  #endif /// VK_KHR_maintenance1

  #ifdef VK_KHR_device_group_creation // "VK_KHR_device_group_creation"
  VKO_FUNC(EnumeratePhysicalDeviceGroupsKHR);
  #endif /// VK_KHR_device_group_creation

  #ifdef VK_KHR_external_memory_capabilities // "VK_KHR_external_memory_capabilities"
  VKO_FUNC(GetPhysicalDeviceExternalBufferPropertiesKHR);
  #endif /// VK_KHR_external_memory_capabilities

  #ifdef VK_KHR_external_memory_fd // "VK_KHR_external_memory_fd"
  VKO_FUNC(GetMemoryFdKHR);
  VKO_FUNC(GetMemoryFdPropertiesKHR);
  #endif /// VK_KHR_external_memory_fd

  #ifdef VK_KHR_external_semaphore_capabilities // "VK_KHR_external_semaphore_capabilities"
  VKO_FUNC(GetPhysicalDeviceExternalSemaphorePropertiesKHR);
  #endif /// VK_KHR_external_semaphore_capabilities

  #ifdef VK_KHR_external_semaphore_fd // "VK_KHR_external_semaphore_fd"
  VKO_FUNC(ImportSemaphoreFdKHR);
  VKO_FUNC(GetSemaphoreFdKHR);
  #endif /// VK_KHR_external_semaphore_fd

  #ifdef VK_KHR_push_descriptor // "VK_KHR_push_descriptor"
  VKO_FUNC(CmdPushDescriptorSetKHR);
  VKO_FUNC(CmdPushDescriptorSetWithTemplateKHR);
  #endif

  #ifdef VK_KHR_descriptor_update_template // "VK_KHR_descriptor_update_template"
  VKO_FUNC(CreateDescriptorUpdateTemplateKHR);
  VKO_FUNC(DestroyDescriptorUpdateTemplateKHR);
  VKO_FUNC(UpdateDescriptorSetWithTemplateKHR);
  #endif /// VK_KHR_descriptor_update_template

  #ifdef VK_KHR_create_renderpass2 // "VK_KHR_create_renderpass2"
  VKO_FUNC(CreateRenderPass2KHR);
  VKO_FUNC(CmdBeginRenderPass2KHR);
  VKO_FUNC(CmdNextSubpass2KHR);
  VKO_FUNC(CmdEndRenderPass2KHR);
  #endif /// VK_KHR_create_renderpass2

  #ifdef VK_KHR_shared_presentable_image // "VK_KHR_shared_presentable_image"
  VKO_FUNC(GetSwapchainStatusKHR);
  #endif /// VK_KHR_shared_presentable_image

  #ifdef VK_KHR_external_fence_capabilities // "VK_KHR_external_fence_capabilities"
  VKO_FUNC(GetPhysicalDeviceExternalFencePropertiesKHR);
  #endif /// VK_KHR_external_fence_capabilities

  #ifdef VK_KHR_external_fence_fd // "VK_KHR_external_fence_fd"
  VKO_FUNC(ImportFenceFdKHR);
  VKO_FUNC(GetFenceFdKHR);
  #endif
  
  #ifdef VK_KHR_performance_query
  VKO_FUNC(EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR);
  VKO_FUNC(GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR);
  VKO_FUNC(AcquireProfilingLockKHR);
  VKO_FUNC(ReleaseProfilingLockKHR);
  #endif

  #ifdef VK_KHR_get_surface_capabilities2 // "VK_KHR_get_surface_capabilities2"
  VKO_FUNC(GetPhysicalDeviceSurfaceCapabilities2KHR);
  VKO_FUNC(GetPhysicalDeviceSurfaceFormats2KHR);
  #endif

  #ifdef VK_KHR_get_display_properties2 // "VK_KHR_get_display_properties2"
  VKO_FUNC(GetPhysicalDeviceDisplayProperties2KHR);
  VKO_FUNC(GetPhysicalDeviceDisplayPlaneProperties2KHR);
  VKO_FUNC(GetDisplayModeProperties2KHR);
  VKO_FUNC(GetDisplayPlaneCapabilities2KHR);
  #endif

  #ifdef VK_KHR_get_memory_requirements2 // "VK_KHR_get_memory_requirements2"
  VKO_FUNC(GetImageMemoryRequirements2KHR);
  VKO_FUNC(GetBufferMemoryRequirements2KHR);
  VKO_FUNC(GetImageSparseMemoryRequirements2KHR);
  #endif

  #ifdef VK_KHR_sampler_ycbcr_conversion // "VK_KHR_sampler_ycbcr_conversion"
  VKO_FUNC(CreateSamplerYcbcrConversionKHR);
  VKO_FUNC(DestroySamplerYcbcrConversionKHR);
  #endif

  #ifdef VK_KHR_bind_memory2 // "VK_KHR_bind_memory2"
  VKO_FUNC(BindBufferMemory2KHR);
  VKO_FUNC(BindImageMemory2KHR);
  #endif

  #ifdef VK_KHR_maintenance3 // "VK_KHR_maintenance3"
  VKO_FUNC(GetDescriptorSetLayoutSupportKHR);
  #endif

  #ifdef VK_KHR_draw_indirect_count // "VK_KHR_draw_indirect_count"
  VKO_FUNC(CmdDrawIndirectCountKHR);
  VKO_FUNC(CmdDrawIndexedIndirectCountKHR);
  #endif
  
  #ifdef VK_KHR_timeline_semaphore
  VKO_FUNC(GetSemaphoreCounterValueKHR);
  VKO_FUNC(WaitSemaphoresKHR);
  VKO_FUNC(SignalSemaphoreKHR);
  #endif
  
  #ifdef VK_KHR_buffer_device_address
  VKO_FUNC(GetBufferDeviceAddressKHR);
  VKO_FUNC(GetBufferOpaqueCaptureAddressKHR);
  VKO_FUNC(GetDeviceMemoryOpaqueCaptureAddressKHR);
  #endif

  #ifdef VK_KHR_pipeline_executable_properties
  VKO_FUNC(GetPipelineExecutablePropertiesKHR);
  VKO_FUNC(GetPipelineExecutableStatisticsKHR);
  VKO_FUNC(GetPipelineExecutableInternalRepresentationsKHR);
  #endif

  #ifdef VK_EXT_debug_report // "VK_EXT_debug_report"
  VKO_FUNC(CreateDebugReportCallbackEXT);
  VKO_FUNC(DestroyDebugReportCallbackEXT);
  VKO_FUNC(DebugReportMessageEXT);
  #endif

  #ifdef VK_EXT_debug_marker // "VK_EXT_debug_marker"
  VKO_FUNC(DebugMarkerSetObjectTagEXT);
  VKO_FUNC(DebugMarkerSetObjectNameEXT);
  VKO_FUNC(CmdDebugMarkerBeginEXT);
  VKO_FUNC(CmdDebugMarkerEndEXT);
  VKO_FUNC(CmdDebugMarkerInsertEXT);
  #endif

  #ifdef VK_EXT_transform_feedback // "VK_EXT_transform_feedback"
  VKO_FUNC(CmdBindTransformFeedbackBuffersEXT);
  VKO_FUNC(CmdBeginTransformFeedbackEXT);
  VKO_FUNC(CmdEndTransformFeedbackEXT);
  VKO_FUNC(CmdBeginQueryIndexedEXT);
  VKO_FUNC(CmdEndQueryIndexedEXT);
  VKO_FUNC(CmdDrawIndirectByteCountEXT);
  #endif

  #ifdef VK_NVX_image_view_handle // "VK_NVX_image_view_handle"
  VKO_FUNC(GetImageViewHandleNVX);
  #endif

  #ifdef VK_AMD_draw_indirect_count // "VK_AMD_draw_indirect_count"
  VKO_FUNC(CmdDrawIndirectCountAMD);
  VKO_FUNC(CmdDrawIndexedIndirectCountAMD);
  #endif

  #ifdef VK_AMD_shader_info // "VK_AMD_shader_info"
  VKO_FUNC(GetShaderInfoAMD);
  #endif

  #ifdef VK_NV_external_memory_capabilities // "VK_NV_external_memory_capabilities"
  VKO_FUNC(GetPhysicalDeviceExternalImageFormatPropertiesNV);
  #endif

  #ifdef VK_EXT_conditional_rendering // "VK_EXT_conditional_rendering"
  VKO_FUNC(CmdBeginConditionalRenderingEXT);
  VKO_FUNC(CmdEndConditionalRenderingEXT);
  #endif

  #ifdef VK_NVX_device_generated_commands // "VK_NVX_device_generated_commands"
  VKO_FUNC(CmdProcessCommandsNVX);
  VKO_FUNC(CmdReserveSpaceForCommandsNVX);
  VKO_FUNC(CreateIndirectCommandsLayoutNVX);
  VKO_FUNC(DestroyIndirectCommandsLayoutNVX);
  VKO_FUNC(CreateObjectTableNVX);
  VKO_FUNC(DestroyObjectTableNVX);
  VKO_FUNC(RegisterObjectsNVX);
  VKO_FUNC(UnregisterObjectsNVX);
  VKO_FUNC(GetPhysicalDeviceGeneratedCommandsPropertiesNVX);
  #endif

  #ifdef VK_NV_clip_space_w_scaling // "VK_NV_clip_space_w_scaling"
  VKO_FUNC(CmdSetViewportWScalingNV);
  #endif

  #ifdef VK_EXT_direct_mode_display // "VK_EXT_direct_mode_display"
  VKO_FUNC(ReleaseDisplayEXT);
  #endif

  #ifdef VK_EXT_display_surface_counter // "VK_EXT_display_surface_counter"
  VKO_FUNC(GetPhysicalDeviceSurfaceCapabilities2EXT);
  #endif

  #ifdef VK_EXT_display_control // "VK_EXT_display_control"
  VKO_FUNC(DisplayPowerControlEXT);
  VKO_FUNC(RegisterDeviceEventEXT);
  VKO_FUNC(RegisterDisplayEventEXT);
  VKO_FUNC(GetSwapchainCounterEXT);
  #endif

  #ifdef VK_GOOGLE_display_timing // "VK_GOOGLE_display_timing"
  VKO_FUNC(GetRefreshCycleDurationGOOGLE);
  VKO_FUNC(GetPastPresentationTimingGOOGLE);
  #endif

  #ifdef VK_EXT_discard_rectangles // "VK_EXT_discard_rectangles"
  VKO_FUNC(CmdSetDiscardRectangleEXT);
  #endif

  #ifdef VK_EXT_hdr_metadata // "VK_EXT_hdr_metadata"
  VKO_FUNC(SetHdrMetadataEXT);
  #endif
  
  #ifdef VK_EXT_debug_utils // "VK_EXT_debug_utils"
  VKO_FUNC(SetDebugUtilsObjectNameEXT);
  VKO_FUNC(SetDebugUtilsObjectTagEXT);
  VKO_FUNC(QueueBeginDebugUtilsLabelEXT);
  VKO_FUNC(QueueEndDebugUtilsLabelEXT);
  VKO_FUNC(QueueInsertDebugUtilsLabelEXT);
  VKO_FUNC(CmdBeginDebugUtilsLabelEXT);
  VKO_FUNC(CmdEndDebugUtilsLabelEXT);
  VKO_FUNC(CmdInsertDebugUtilsLabelEXT);
  VKO_FUNC(CreateDebugUtilsMessengerEXT);
  VKO_FUNC(DestroyDebugUtilsMessengerEXT);
  VKO_FUNC(SubmitDebugUtilsMessageEXT);
  #endif

  #ifdef VK_EXT_sample_locations // "VK_EXT_sample_locations"
  VKO_FUNC(CmdSetSampleLocationsEXT);
  VKO_FUNC(GetPhysicalDeviceMultisamplePropertiesEXT);
  #endif

  #ifdef VK_EXT_image_drm_format_modifier // "VK_EXT_image_drm_format_modifier"
  VKO_FUNC(GetImageDrmFormatModifierPropertiesEXT);
  #endif

  #ifdef VK_EXT_validation_cache // "VK_EXT_validation_cache"
  VKO_FUNC(CreateValidationCacheEXT);
  VKO_FUNC(DestroyValidationCacheEXT);
  VKO_FUNC(MergeValidationCachesEXT);
  VKO_FUNC(GetValidationCacheDataEXT);
  #endif

  #ifdef VK_NV_shading_rate_image // "VK_NV_shading_rate_image"
  VKO_FUNC(CmdBindShadingRateImageNV);
  VKO_FUNC(CmdSetViewportShadingRatePaletteNV);
  VKO_FUNC(CmdSetCoarseSampleOrderNV);
  #endif

  #ifdef VK_NV_ray_tracing // "VK_NV_ray_tracing"
  VKO_FUNC(CreateAccelerationStructureNV);
  VKO_FUNC(DestroyAccelerationStructureNV);
  VKO_FUNC(GetAccelerationStructureMemoryRequirementsNV);
  VKO_FUNC(BindAccelerationStructureMemoryNV);
  VKO_FUNC(CmdBuildAccelerationStructureNV);
  VKO_FUNC(CmdCopyAccelerationStructureNV);
  VKO_FUNC(CmdTraceRaysNV);
  VKO_FUNC(CreateRayTracingPipelinesNV);
  VKO_FUNC(GetRayTracingShaderGroupHandlesNV);
  VKO_FUNC(GetAccelerationStructureHandleNV);
  VKO_FUNC(CmdWriteAccelerationStructuresPropertiesNV);
  VKO_FUNC(CompileDeferredNV);
  #endif

  #ifdef VK_EXT_external_memory_host // "VK_EXT_external_memory_host"
  VKO_FUNC(GetMemoryHostPointerPropertiesEXT);
  #endif

  #ifdef VK_AMD_buffer_marker // "VK_AMD_buffer_marker"
  VKO_FUNC(CmdWriteBufferMarkerAMD);
  #endif

  #ifdef VK_EXT_calibrated_timestamps // "VK_EXT_calibrated_timestamps"
  VKO_FUNC(GetPhysicalDeviceCalibrateableTimeDomainsEXT);
  VKO_FUNC(GetCalibratedTimestampsEXT);
  #endif

  #ifdef VK_NV_mesh_shader // "VK_NV_mesh_shader"
  VKO_FUNC(CmdDrawMeshTasksNV);
  VKO_FUNC(CmdDrawMeshTasksIndirectNV);
  VKO_FUNC(CmdDrawMeshTasksIndirectCountNV);
  #endif

  #ifdef VK_NV_scissor_exclusive // "VK_NV_scissor_exclusive"
  VKO_FUNC(CmdSetExclusiveScissorNV);
  #endif

  #ifdef VK_NV_device_diagnostic_checkpoints // "VK_NV_device_diagnostic_checkpoints"
  VKO_FUNC(CmdSetCheckpointNV);
  VKO_FUNC(GetQueueCheckpointDataNV);
  #endif

  #ifdef VK_INTEL_performance_query // "VK_NV_device_diagnostic_checkpoints"
  VKO_FUNC(InitializePerformanceApiINTEL);
  VKO_FUNC(UninitializePerformanceApiINTEL);
  VKO_FUNC(CmdSetPerformanceMarkerINTEL);
  VKO_FUNC(CmdSetPerformanceStreamMarkerINTEL);
  VKO_FUNC(CmdSetPerformanceOverrideINTEL);
  VKO_FUNC(AcquirePerformanceConfigurationINTEL);
  VKO_FUNC(ReleasePerformanceConfigurationINTEL);
  VKO_FUNC(QueueSetPerformanceConfigurationINTEL);
  VKO_FUNC(GetPerformanceParameterINTEL);
  #endif

  #ifdef VK_AMD_display_native_hdr
  VKO_FUNC(SetLocalDimmingAMD);
  #endif

  #ifdef VK_EXT_buffer_device_address
  VKO_FUNC(GetBufferDeviceAddressEXT);
  #endif

  #ifdef VK_EXT_tooling_info // VK_EXT_tooling_info
  VKO_FUNC(GetPhysicalDeviceToolPropertiesEXT);
  #endif

  #ifdef VK_NV_cooperative_matrix
  VKO_FUNC(GetPhysicalDeviceCooperativeMatrixPropertiesNV);
  #endif

  #ifdef VK_NV_coverage_reduction_mode
  VKO_FUNC(GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV);
  #endif

  #ifdef VK_EXT_headless_surface
  VKO_FUNC(CreateHeadlessSurfaceEXT);
  #endif

  #ifdef VK_EXT_line_rasterization
  VKO_FUNC(CmdSetLineStippleEXT);
  #endif

  #ifdef VK_EXT_host_query_reset
  VKO_FUNC(ResetQueryPoolEXT);
  #endif

  // ANDROID OS specific =====================================================================================

  #ifdef VK_KHR_android_surface
  VKO_FUNC(CreateAndroidSurfaceKHR);
  #endif

  #ifdef VK_ANDROID_external_memory_android_hardware_buffer
  VKO_FUNC(GetAndroidHardwareBufferPropertiesANDROID);
  VKO_FUNC(GetMemoryAndroidHardwareBufferANDROID);
  #endif

  // FUCHSIA specific ========================================================================================

  #ifdef VK_FUCHSIA_imagepipe_surface
  VKO_FUNC(CreateImagePipeSurfaceFUCHSIA);
  #endif

  // IOS specific ============================================================================================

  #ifdef VK_MVK_ios_surface
  VKO_FUNC(CreateIOSSurfaceMVK);
  #endif

  // MAC OS specific =========================================================================================

  #ifdef VK_MVK_macos_surface // "VK_MVK_macos_surface"
  VKO_FUNC(CreateMacOSSurfaceMVK);
  #endif
  
  #ifdef VK_EXT_metal_surface
  VKO_FUNC(CreateMetalSurfaceEXT);
  #endif

  // VI specific =============================================================================================

  #ifdef VK_NN_vi_surface
  VKO_FUNC(CreateViSurfaceNN);
  #endif

  // WAYLAND specific ========================================================================================

  #ifdef VK_KHR_wayland_surface // "VK_KHR_wayland_surface"
  VKO_FUNC(CreateWaylandSurfaceKHR);
  VKO_FUNC(GetPhysicalDeviceWaylandPresentationSupportKHR);
  #endif

  // WINDOWS specifi =========================================================================================

  #ifdef VK_KHR_win32_surface // "VK_KHR_win32_surface"
  VKO_FUNC(CreateWin32SurfaceKHR);
  VKO_FUNC(GetPhysicalDeviceWin32PresentationSupportKHR);
  #endif

  #ifdef VK_KHR_external_memory_win32 // "VK_KHR_external_memory_win32"
  VKO_FUNC(GetMemoryWin32HandleKHR);
  VKO_FUNC(GetMemoryWin32HandlePropertiesKHR);
  #endif
  
  #ifdef VK_KHR_external_semaphore_win32 // "VK_KHR_external_semaphore_win32"
  VKO_FUNC(ImportSemaphoreWin32HandleKHR);
  VKO_FUNC(GetSemaphoreWin32HandleKHR);
  #endif

  #ifdef VK_KHR_external_fence_win32 // "VK_KHR_external_fence_win32"
  VKO_FUNC(ImportFenceWin32HandleKHR);
  VKO_FUNC(GetFenceWin32HandleKHR);
  #endif

  #ifdef VK_NV_external_memory_win32 // "VK_NV_external_memory_win32"
  VKO_FUNC(GetMemoryWin32HandleNV);
  #endif

  #ifdef VK_EXT_full_screen_exclusive
  VKO_FUNC(GetPhysicalDeviceSurfacePresentModes2EXT);
  VKO_FUNC(AcquireFullScreenExclusiveModeEXT);
  VKO_FUNC(ReleaseFullScreenExclusiveModeEXT);
  VKO_FUNC(GetDeviceGroupSurfacePresentModes2EXT);
  #endif

  // LINUX XCB specific ======================================================================================

  #ifdef VK_KHR_xcb_surface // "VK_KHR_xcb_surface"
  VKO_FUNC(CreateXcbSurfaceKHR);
  VKO_FUNC(GetPhysicalDeviceXcbPresentationSupportKHR);
  #endif

  // LINUX XLIB specific =====================================================================================

  #ifdef VK_KHR_xlib_surface // "VK_KHR_xlib_surface"
  VKO_FUNC(CreateXlibSurfaceKHR);
  VKO_FUNC(GetPhysicalDeviceXlibPresentationSupportKHR);
  #endif

  // LINUX XRANDR specific ===================================================================================

  #ifdef VK_EXT_acquire_xlib_display // "VK_EXT_acquire_xlib_display"
  VKO_FUNC(AcquireXlibDisplayEXT);
  VKO_FUNC(GetRandROutputDisplayEXT);
  #endif

  // GGP specific ============================================================================================

  #ifdef VK_GGP_stream_descriptor_surface
  VKO_FUNC(CreateStreamDescriptorSurfaceGGP);
  #endif
};














