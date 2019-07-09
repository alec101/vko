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


  // NEW VVVVVVVVVVVVVV


  #ifdef VK_AMD_display_native_hdr
  VKO_FUNC(SetLocalDimmingAMD);
  #endif

  #ifdef VK_EXT_buffer_device_address
  VKO_FUNC(GetBufferDeviceAddressEXT);
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

  #ifdef VK_EXT_host_query_reset
  VKO_FUNC(ResetQueryPoolEXT);
  #endif

  // NEW ^^^^^^^^^^^^^^





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
  vkObject::glb->ResetCommandBuffer(commandBuffer, flags); }
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














// EXTENSIONS =============================================================================


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
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDescriptorUpdateTemplateKHR(VkDevice device, const VkDescriptorUpdateTemplateCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDescriptorUpdateTemplate *pDescriptorUpdateTemplate);
VKAPI_ATTR void VKAPI_CALL vkDestroyDescriptorUpdateTemplateKHR(VkDevice device, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const VkAllocationCallbacks *pAllocator);
VKAPI_ATTR void VKAPI_CALL vkUpdateDescriptorSetWithTemplateKHR(VkDevice device, VkDescriptorSet descriptorSet, VkDescriptorUpdateTemplate descriptorUpdateTemplate, const void *pData);
#endif /// VK_KHR_descriptor_update_template

#ifdef VK_KHR_create_renderpass2 // "VK_KHR_create_renderpass2"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateRenderPass2KHR(VkDevice device, const VkRenderPassCreateInfo2KHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkRenderPass *pRenderPass);
VKAPI_ATTR void VKAPI_CALL vkCmdBeginRenderPass2KHR(VkCommandBuffer commandBuffer, const VkRenderPassBeginInfo *pRenderPassBegin, const VkSubpassBeginInfoKHR *pSubpassBeginInfo);
VKAPI_ATTR void VKAPI_CALL vkCmdNextSubpass2KHR(VkCommandBuffer commandBuffer, const VkSubpassBeginInfoKHR *pSubpassBeginInfo, const VkSubpassEndInfoKHR *pSubpassEndInfo);
VKAPI_ATTR void VKAPI_CALL vkCmdEndRenderPass2KHR(VkCommandBuffer commandBuffer, const VkSubpassEndInfoKHR *pSubpassEndInfo);
#endif /// VK_KHR_create_renderpass2

#ifdef VK_KHR_shared_presentable_image // "VK_KHR_shared_presentable_image"
VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainStatusKHR(VkDevice device, VkSwapchainKHR swapchain);
#endif /// VK_KHR_shared_presentable_image

#ifdef VK_KHR_external_fence_capabilities // "VK_KHR_external_fence_capabilities"
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceExternalFencePropertiesKHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceExternalFenceInfo *pExternalFenceInfo, VkExternalFenceProperties *pExternalFenceProperties);
#endif /// VK_KHR_external_fence_capabilities

#ifdef VK_KHR_external_fence_fd // "VK_KHR_external_fence_fd"
VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceFdKHR(VkDevice device, const VkImportFenceFdInfoKHR *pImportFenceFdInfo);
VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceFdKHR(VkDevice device, const VkFenceGetFdInfoKHR *pGetFdInfo, int *pFd);
#endif
  
#ifdef VK_KHR_get_surface_capabilities2 // "VK_KHR_get_surface_capabilities2"
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo, VkSurfaceCapabilities2KHR *pSurfaceCapabilities);
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceFormats2KHR(VkPhysicalDevice physicalDevice, const VkPhysicalDeviceSurfaceInfo2KHR *pSurfaceInfo, uint32_t *pSurfaceFormatCount, VkSurfaceFormat2KHR *pSurfaceFormats);
#endif

#ifdef VK_KHR_get_display_properties2 // "VK_KHR_get_display_properties2"
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkDisplayProperties2KHR *pProperties);
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceDisplayPlaneProperties2KHR(VkPhysicalDevice physicalDevice, uint32_t *pPropertyCount, VkDisplayPlaneProperties2KHR *pProperties);
VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayModeProperties2KHR(VkPhysicalDevice physicalDevice, VkDisplayKHR display, uint32_t *pPropertyCount, VkDisplayModeProperties2KHR *pProperties);
VKAPI_ATTR VkResult VKAPI_CALL vkGetDisplayPlaneCapabilities2KHR(VkPhysicalDevice physicalDevice, const VkDisplayPlaneInfo2KHR *pDisplayPlaneInfo, VkDisplayPlaneCapabilities2KHR *pCapabilities);
#endif

#ifdef VK_KHR_get_memory_requirements2 // "VK_KHR_get_memory_requirements2"
VKAPI_ATTR void VKAPI_CALL vkGetImageMemoryRequirements2KHR(VkDevice device, const VkImageMemoryRequirementsInfo2 *pInfo, VkMemoryRequirements2 *pMemoryRequirements);
VKAPI_ATTR void VKAPI_CALL vkGetBufferMemoryRequirements2KHR(VkDevice device, const VkBufferMemoryRequirementsInfo2 *pInfo, VkMemoryRequirements2 *pMemoryRequirements);
VKAPI_ATTR void VKAPI_CALL vkGetImageSparseMemoryRequirements2KHR(VkDevice device, const VkImageSparseMemoryRequirementsInfo2 *pInfo, uint32_t *pSparseMemoryRequirementCount, VkSparseImageMemoryRequirements2 *pSparseMemoryRequirements);
#endif

#ifdef VK_KHR_sampler_ycbcr_conversion // "VK_KHR_sampler_ycbcr_conversion"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateSamplerYcbcrConversionKHR(VkDevice device, const VkSamplerYcbcrConversionCreateInfo *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSamplerYcbcrConversion *pYcbcrConversion);
VKAPI_ATTR void VKAPI_CALL vkDestroySamplerYcbcrConversionKHR(VkDevice device, VkSamplerYcbcrConversion ycbcrConversion, const VkAllocationCallbacks *pAllocator);
#endif

#ifdef VK_KHR_bind_memory2 // "VK_KHR_bind_memory2"
VKAPI_ATTR VkResult VKAPI_CALL vkBindBufferMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindBufferMemoryInfo *pBindInfos);
VKAPI_ATTR VkResult VKAPI_CALL vkBindImageMemory2KHR(VkDevice device, uint32_t bindInfoCount, const VkBindImageMemoryInfo *pBindInfos);
#endif

#ifdef VK_KHR_maintenance3 // "VK_KHR_maintenance3"
VKAPI_ATTR void VKAPI_CALL vkGetDescriptorSetLayoutSupportKHR(VkDevice device, const VkDescriptorSetLayoutCreateInfo *pCreateInfo, VkDescriptorSetLayoutSupport *pSupport);
#endif

#ifdef VK_KHR_draw_indirect_count // "VK_KHR_draw_indirect_count"
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCountKHR(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif
  
#ifdef VK_EXT_debug_report // "VK_EXT_debug_report"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugReportCallbackEXT(VkInstance instance, const VkDebugReportCallbackCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugReportCallbackEXT *pCallback);
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugReportCallbackEXT(VkInstance instance, VkDebugReportCallbackEXT callback, const VkAllocationCallbacks *pAllocator);
VKAPI_ATTR void VKAPI_CALL vkDebugReportMessageEXT(VkInstance instance, VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objectType, uint64_t object, size_t location, int32_t messageCode, const char *pLayerPrefix, const char *pMessage);
#endif

#ifdef VK_EXT_debug_marker // "VK_EXT_debug_marker"
VKAPI_ATTR VkResult VKAPI_CALL vkDebugMarkerSetObjectTagEXT(VkDevice device, const VkDebugMarkerObjectTagInfoEXT *pTagInfo);
VKAPI_ATTR VkResult VKAPI_CALL vkDebugMarkerSetObjectNameEXT(VkDevice device, const VkDebugMarkerObjectNameInfoEXT *pNameInfo);
VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerBeginEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT *pMarkerInfo);
VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerEndEXT(VkCommandBuffer commandBuffer);
VKAPI_ATTR void VKAPI_CALL vkCmdDebugMarkerInsertEXT(VkCommandBuffer commandBuffer, const VkDebugMarkerMarkerInfoEXT *pMarkerInfo);
#endif

#ifdef VK_EXT_transform_feedback // "VK_EXT_transform_feedback"
VKAPI_ATTR void VKAPI_CALL vkCmdBindTransformFeedbackBuffersEXT(VkCommandBuffer commandBuffer, uint32_t firstBinding, uint32_t bindingCount, const VkBuffer *pBuffers, const VkDeviceSize *pOffsets, const VkDeviceSize *pSizes);
VKAPI_ATTR void VKAPI_CALL vkCmdBeginTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer *pCounterBuffers, const VkDeviceSize *pCounterBufferOffsets);
VKAPI_ATTR void VKAPI_CALL vkCmdEndTransformFeedbackEXT(VkCommandBuffer commandBuffer, uint32_t firstCounterBuffer, uint32_t counterBufferCount, const VkBuffer *pCounterBuffers, const VkDeviceSize *pCounterBufferOffsets);
VKAPI_ATTR void VKAPI_CALL vkCmdBeginQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, VkQueryControlFlags flags, uint32_t index);
VKAPI_ATTR void VKAPI_CALL vkCmdEndQueryIndexedEXT(VkCommandBuffer commandBuffer, VkQueryPool queryPool, uint32_t query, uint32_t index);
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectByteCountEXT(VkCommandBuffer commandBuffer, uint32_t instanceCount, uint32_t firstInstance, VkBuffer counterBuffer, VkDeviceSize counterBufferOffset, uint32_t counterOffset, uint32_t vertexStride);
#endif

#ifdef VK_AMD_draw_indirect_count // "VK_AMD_draw_indirect_count"
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
VKAPI_ATTR void VKAPI_CALL vkCmdDrawIndexedIndirectCountAMD(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif

#ifdef VK_AMD_shader_info // "VK_AMD_shader_info"
VKAPI_ATTR VkResult VKAPI_CALL vkGetShaderInfoAMD(VkDevice device, VkPipeline pipeline, VkShaderStageFlagBits shaderStage, VkShaderInfoTypeAMD infoType, size_t *pInfoSize, void *pInfo);
#endif

#ifdef VK_NV_external_memory_capabilities // "VK_NV_external_memory_capabilities"
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceExternalImageFormatPropertiesNV(VkPhysicalDevice physicalDevice, VkFormat format, VkImageType type, VkImageTiling tiling, VkImageUsageFlags usage, VkImageCreateFlags flags, VkExternalMemoryHandleTypeFlagsNV externalHandleType, VkExternalImageFormatPropertiesNV *pExternalImageFormatProperties);
#endif

#ifdef VK_EXT_conditional_rendering // "VK_EXT_conditional_rendering"
VKAPI_ATTR void VKAPI_CALL vkCmdBeginConditionalRenderingEXT(VkCommandBuffer commandBuffer, const VkConditionalRenderingBeginInfoEXT *pConditionalRenderingBegin);
VKAPI_ATTR void VKAPI_CALL vkCmdEndConditionalRenderingEXT(VkCommandBuffer commandBuffer);
#endif

#ifdef VK_NVX_device_generated_commands // "VK_NVX_device_generated_commands"
VKAPI_ATTR void VKAPI_CALL vkCmdProcessCommandsNVX(VkCommandBuffer commandBuffer, const VkCmdProcessCommandsInfoNVX *pProcessCommandsInfo);
VKAPI_ATTR void VKAPI_CALL vkCmdReserveSpaceForCommandsNVX(VkCommandBuffer commandBuffer, const VkCmdReserveSpaceForCommandsInfoNVX *pReserveSpaceInfo);
VKAPI_ATTR VkResult VKAPI_CALL vkCreateIndirectCommandsLayoutNVX(VkDevice device, const VkIndirectCommandsLayoutCreateInfoNVX *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkIndirectCommandsLayoutNVX *pIndirectCommandsLayout);
VKAPI_ATTR void VKAPI_CALL vkDestroyIndirectCommandsLayoutNVX(VkDevice device, VkIndirectCommandsLayoutNVX indirectCommandsLayout, const VkAllocationCallbacks *pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL vkCreateObjectTableNVX(VkDevice device, const VkObjectTableCreateInfoNVX *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkObjectTableNVX *pObjectTable);
VKAPI_ATTR void VKAPI_CALL vkDestroyObjectTableNVX(VkDevice device, VkObjectTableNVX objectTable, const VkAllocationCallbacks *pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL vkRegisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, const VkObjectTableEntryNVX *const *ppObjectTableEntries, const uint32_t *pObjectIndices);
VKAPI_ATTR VkResult VKAPI_CALL vkUnregisterObjectsNVX(VkDevice device, VkObjectTableNVX objectTable, uint32_t objectCount, const VkObjectEntryTypeNVX *pObjectEntryTypes, const uint32_t *pObjectIndices);
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceGeneratedCommandsPropertiesNVX(VkPhysicalDevice physicalDevice, VkDeviceGeneratedCommandsFeaturesNVX *pFeatures, VkDeviceGeneratedCommandsLimitsNVX *pLimits);
#endif

#ifdef VK_NV_clip_space_w_scaling // "VK_NV_clip_space_w_scaling"
VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportWScalingNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkViewportWScalingNV *pViewportWScalings);
#endif

#ifdef VK_EXT_direct_mode_display // "VK_EXT_direct_mode_display"
VKAPI_ATTR VkResult VKAPI_CALL vkReleaseDisplayEXT(VkPhysicalDevice physicalDevice, VkDisplayKHR display);
#endif

#ifdef VK_EXT_display_surface_counter // "VK_EXT_display_surface_counter"
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceSurfaceCapabilities2EXT(VkPhysicalDevice physicalDevice, VkSurfaceKHR surface, VkSurfaceCapabilities2EXT *pSurfaceCapabilities);
#endif

#ifdef VK_EXT_display_control // "VK_EXT_display_control"
VKAPI_ATTR VkResult VKAPI_CALL vkDisplayPowerControlEXT(VkDevice device, VkDisplayKHR display, const VkDisplayPowerInfoEXT *pDisplayPowerInfo);
VKAPI_ATTR VkResult VKAPI_CALL vkRegisterDeviceEventEXT(VkDevice device, const VkDeviceEventInfoEXT *pDeviceEventInfo, const VkAllocationCallbacks *pAllocator, VkFence *pFence);
VKAPI_ATTR VkResult VKAPI_CALL vkRegisterDisplayEventEXT(VkDevice device, VkDisplayKHR display, const VkDisplayEventInfoEXT *pDisplayEventInfo, const VkAllocationCallbacks *pAllocator, VkFence *pFence);
VKAPI_ATTR VkResult VKAPI_CALL vkGetSwapchainCounterEXT(VkDevice device, VkSwapchainKHR swapchain, VkSurfaceCounterFlagBitsEXT counter, uint64_t *pCounterValue);
#endif

#ifdef VK_GOOGLE_display_timing // "VK_GOOGLE_display_timing"
VKAPI_ATTR VkResult VKAPI_CALL vkGetRefreshCycleDurationGOOGLE(VkDevice device, VkSwapchainKHR swapchain, VkRefreshCycleDurationGOOGLE *pDisplayTimingProperties);
VKAPI_ATTR VkResult VKAPI_CALL vkGetPastPresentationTimingGOOGLE(VkDevice device, VkSwapchainKHR swapchain, uint32_t *pPresentationTimingCount, VkPastPresentationTimingGOOGLE *pPresentationTimings);
#endif

#ifdef VK_EXT_discard_rectangles // "VK_EXT_discard_rectangles"
VKAPI_ATTR void VKAPI_CALL vkCmdSetDiscardRectangleEXT(VkCommandBuffer commandBuffer, uint32_t firstDiscardRectangle, uint32_t discardRectangleCount, const VkRect2D *pDiscardRectangles);
#endif

#ifdef VK_EXT_hdr_metadata // "VK_EXT_hdr_metadata"
VKAPI_ATTR void VKAPI_CALL vkSetHdrMetadataEXT(VkDevice device, uint32_t swapchainCount, const VkSwapchainKHR *pSwapchains, const VkHdrMetadataEXT *pMetadata);
#endif
  
#ifdef VK_EXT_debug_utils // "VK_EXT_debug_utils"
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectNameEXT(VkDevice device, const VkDebugUtilsObjectNameInfoEXT *pNameInfo);
VKAPI_ATTR VkResult VKAPI_CALL vkSetDebugUtilsObjectTagEXT(VkDevice device, const VkDebugUtilsObjectTagInfoEXT *pTagInfo);
VKAPI_ATTR void VKAPI_CALL vkQueueBeginDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT *pLabelInfo);
VKAPI_ATTR void VKAPI_CALL vkQueueEndDebugUtilsLabelEXT(VkQueue queue);
VKAPI_ATTR void VKAPI_CALL vkQueueInsertDebugUtilsLabelEXT(VkQueue queue, const VkDebugUtilsLabelEXT *pLabelInfo);
VKAPI_ATTR void VKAPI_CALL vkCmdBeginDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT *pLabelInfo);
VKAPI_ATTR void VKAPI_CALL vkCmdEndDebugUtilsLabelEXT(VkCommandBuffer commandBuffer);
VKAPI_ATTR void VKAPI_CALL vkCmdInsertDebugUtilsLabelEXT(VkCommandBuffer commandBuffer, const VkDebugUtilsLabelEXT *pLabelInfo);
VKAPI_ATTR VkResult VKAPI_CALL vkCreateDebugUtilsMessengerEXT(VkInstance instance, const VkDebugUtilsMessengerCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkDebugUtilsMessengerEXT *pMessenger);
VKAPI_ATTR void VKAPI_CALL vkDestroyDebugUtilsMessengerEXT(VkInstance instance, VkDebugUtilsMessengerEXT messenger, const VkAllocationCallbacks *pAllocator);
VKAPI_ATTR void VKAPI_CALL vkSubmitDebugUtilsMessageEXT(VkInstance instance, VkDebugUtilsMessageSeverityFlagBitsEXT messageSeverity, VkDebugUtilsMessageTypeFlagsEXT messageTypes, const VkDebugUtilsMessengerCallbackDataEXT *pCallbackData);
#endif

#ifdef VK_EXT_sample_locations // "VK_EXT_sample_locations"
VKAPI_ATTR void VKAPI_CALL vkCmdSetSampleLocationsEXT(VkCommandBuffer commandBuffer, const VkSampleLocationsInfoEXT *pSampleLocationsInfo);
VKAPI_ATTR void VKAPI_CALL vkGetPhysicalDeviceMultisamplePropertiesEXT(VkPhysicalDevice physicalDevice, VkSampleCountFlagBits samples, VkMultisamplePropertiesEXT *pMultisampleProperties);
#endif

#ifdef VK_EXT_image_drm_format_modifier // "VK_EXT_image_drm_format_modifier"
VKAPI_ATTR VkResult VKAPI_CALL vkGetImageDrmFormatModifierPropertiesEXT(VkDevice device, VkImage image, VkImageDrmFormatModifierPropertiesEXT *pProperties);
#endif

#ifdef VK_EXT_validation_cache // "VK_EXT_validation_cache"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateValidationCacheEXT(VkDevice device, const VkValidationCacheCreateInfoEXT *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkValidationCacheEXT *pValidationCache);
VKAPI_ATTR void VKAPI_CALL vkDestroyValidationCacheEXT(VkDevice device, VkValidationCacheEXT validationCache, const VkAllocationCallbacks *pAllocator);
VKAPI_ATTR VkResult VKAPI_CALL vkMergeValidationCachesEXT(VkDevice device, VkValidationCacheEXT dstCache, uint32_t srcCacheCount, const VkValidationCacheEXT *pSrcCaches);
VKAPI_ATTR VkResult VKAPI_CALL vkGetValidationCacheDataEXT(VkDevice device, VkValidationCacheEXT validationCache, size_t *pDataSize, void *pData);
#endif

#ifdef VK_NV_shading_rate_image // "VK_NV_shading_rate_image"
VKAPI_ATTR void VKAPI_CALL vkCmdBindShadingRateImageNV(VkCommandBuffer commandBuffer, VkImageView imageView, VkImageLayout imageLayout);
VKAPI_ATTR void VKAPI_CALL vkCmdSetViewportShadingRatePaletteNV(VkCommandBuffer commandBuffer, uint32_t firstViewport, uint32_t viewportCount, const VkShadingRatePaletteNV *pShadingRatePalettes);
VKAPI_ATTR void VKAPI_CALL vkCmdSetCoarseSampleOrderNV(VkCommandBuffer commandBuffer, VkCoarseSampleOrderTypeNV sampleOrderType, uint32_t customSampleOrderCount, const VkCoarseSampleOrderCustomNV *pCustomSampleOrders);
#endif

#ifdef VK_NV_ray_tracing // "VK_NV_ray_tracing"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateAccelerationStructureNV(VkDevice device, const VkAccelerationStructureCreateInfoNV *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkAccelerationStructureNV *pAccelerationStructure);
VKAPI_ATTR void VKAPI_CALL vkDestroyAccelerationStructureNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, const VkAllocationCallbacks *pAllocator);
VKAPI_ATTR void VKAPI_CALL vkGetAccelerationStructureMemoryRequirementsNV(VkDevice device, const VkAccelerationStructureMemoryRequirementsInfoNV *pInfo, VkMemoryRequirements2KHR *pMemoryRequirements);
VKAPI_ATTR VkResult VKAPI_CALL vkBindAccelerationStructureMemoryNV(VkDevice device, uint32_t bindInfoCount, const VkBindAccelerationStructureMemoryInfoNV *pBindInfos);
VKAPI_ATTR void VKAPI_CALL vkCmdBuildAccelerationStructureNV(VkCommandBuffer commandBuffer, const VkAccelerationStructureInfoNV *pInfo, VkBuffer instanceData, VkDeviceSize instanceOffset, VkBool32 update, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkBuffer scratch, VkDeviceSize scratchOffset);
VKAPI_ATTR void VKAPI_CALL vkCmdCopyAccelerationStructureNV(VkCommandBuffer commandBuffer, VkAccelerationStructureNV dst, VkAccelerationStructureNV src, VkCopyAccelerationStructureModeNV mode);
VKAPI_ATTR void VKAPI_CALL vkCmdTraceRaysNV(VkCommandBuffer commandBuffer, VkBuffer raygenShaderBindingTableBuffer, VkDeviceSize raygenShaderBindingOffset, VkBuffer missShaderBindingTableBuffer, VkDeviceSize missShaderBindingOffset, VkDeviceSize missShaderBindingStride, VkBuffer hitShaderBindingTableBuffer, VkDeviceSize hitShaderBindingOffset, VkDeviceSize hitShaderBindingStride, VkBuffer callableShaderBindingTableBuffer, VkDeviceSize callableShaderBindingOffset, VkDeviceSize callableShaderBindingStride, uint32_t width, uint32_t height, uint32_t depth);
VKAPI_ATTR VkResult VKAPI_CALL vkCreateRayTracingPipelinesNV(VkDevice device, VkPipelineCache pipelineCache, uint32_t createInfoCount, const VkRayTracingPipelineCreateInfoNV *pCreateInfos, const VkAllocationCallbacks *pAllocator, VkPipeline *pPipelines);
VKAPI_ATTR VkResult VKAPI_CALL vkGetRayTracingShaderGroupHandlesNV(VkDevice device, VkPipeline pipeline, uint32_t firstGroup, uint32_t groupCount, size_t dataSize, void *pData);
VKAPI_ATTR VkResult VKAPI_CALL vkGetAccelerationStructureHandleNV(VkDevice device, VkAccelerationStructureNV accelerationStructure, size_t dataSize, void *pData);
VKAPI_ATTR void VKAPI_CALL vkCmdWriteAccelerationStructuresPropertiesNV(VkCommandBuffer commandBuffer, uint32_t accelerationStructureCount, const VkAccelerationStructureNV *pAccelerationStructures, VkQueryType queryType, VkQueryPool queryPool, uint32_t firstQuery);
VKAPI_ATTR VkResult VKAPI_CALL vkCompileDeferredNV(VkDevice device, VkPipeline pipeline, uint32_t shader);
#endif

#ifdef VK_EXT_external_memory_host // "VK_EXT_external_memory_host"
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryHostPointerPropertiesEXT(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, const void *pHostPointer, VkMemoryHostPointerPropertiesEXT *pMemoryHostPointerProperties);
#endif

#ifdef VK_AMD_buffer_marker // "VK_AMD_buffer_marker"
VKAPI_ATTR void VKAPI_CALL vkCmdWriteBufferMarkerAMD(VkCommandBuffer commandBuffer, VkPipelineStageFlagBits pipelineStage, VkBuffer dstBuffer, VkDeviceSize dstOffset, uint32_t marker);
#endif

#ifdef VK_EXT_calibrated_timestamps // "VK_EXT_calibrated_timestamps"
VKAPI_ATTR VkResult VKAPI_CALL vkGetPhysicalDeviceCalibrateableTimeDomainsEXT(VkPhysicalDevice physicalDevice, uint32_t *pTimeDomainCount, VkTimeDomainEXT *pTimeDomains);
VKAPI_ATTR VkResult VKAPI_CALL vkGetCalibratedTimestampsEXT(VkDevice device, uint32_t timestampCount, const VkCalibratedTimestampInfoEXT *pTimestampInfos, uint64_t *pTimestamps, uint64_t *pMaxDeviation);
#endif

#ifdef VK_NV_mesh_shader // "VK_NV_mesh_shader"
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksNV(VkCommandBuffer commandBuffer, uint32_t taskCount, uint32_t firstTask);
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, uint32_t drawCount, uint32_t stride);
VKAPI_ATTR void VKAPI_CALL vkCmdDrawMeshTasksIndirectCountNV(VkCommandBuffer commandBuffer, VkBuffer buffer, VkDeviceSize offset, VkBuffer countBuffer, VkDeviceSize countBufferOffset, uint32_t maxDrawCount, uint32_t stride);
#endif

#ifdef VK_NV_scissor_exclusive // "VK_NV_scissor_exclusive"
VKAPI_ATTR void VKAPI_CALL vkCmdSetExclusiveScissorNV(VkCommandBuffer commandBuffer, uint32_t firstExclusiveScissor, uint32_t exclusiveScissorCount, const VkRect2D *pExclusiveScissors);
#endif

#ifdef VK_NV_device_diagnostic_checkpoints // "VK_NV_device_diagnostic_checkpoints"
VKAPI_ATTR void VKAPI_CALL vkCmdSetCheckpointNV(VkCommandBuffer commandBuffer, const void *pCheckpointMarker);
VKAPI_ATTR void VKAPI_CALL vkGetQueueCheckpointDataNV(VkQueue queue, uint32_t *pCheckpointDataCount, VkCheckpointDataNV *pCheckpointData);
#endif

// MAC OS specific =========================================================================================

#ifdef VK_MVK_macos_surface // "VK_MVK_macos_surface"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateMacOSSurfaceMVK(VkInstance instance, const VkMacOSSurfaceCreateInfoMVK *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface);
#endif

// WAYLAND specific ========================================================================================

#ifdef VK_KHR_wayland_surface // "VK_KHR_wayland_surface"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateWaylandSurfaceKHR(VkInstance instance, const VkWaylandSurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface);
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWaylandPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, struct wl_display *display);
#endif

// WINDOWS specifi =========================================================================================

#ifdef VK_KHR_win32_surface // "VK_KHR_win32_surface"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateWin32SurfaceKHR(VkInstance instance, const VkWin32SurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface);
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceWin32PresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex);
#endif

#ifdef VK_KHR_external_memory_win32 // "VK_KHR_external_memory_win32"
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleKHR(VkDevice device, const VkMemoryGetWin32HandleInfoKHR *pGetWin32HandleInfo, HANDLE *pHandle);
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandlePropertiesKHR(VkDevice device, VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, VkMemoryWin32HandlePropertiesKHR *pMemoryWin32HandleProperties);
#endif
  
#ifdef VK_KHR_external_semaphore_win32 // "VK_KHR_external_semaphore_win32"
VKAPI_ATTR VkResult VKAPI_CALL vkImportSemaphoreWin32HandleKHR(VkDevice device, const VkImportSemaphoreWin32HandleInfoKHR *pImportSemaphoreWin32HandleInfo);
VKAPI_ATTR VkResult VKAPI_CALL vkGetSemaphoreWin32HandleKHR(VkDevice device, const VkSemaphoreGetWin32HandleInfoKHR *pGetWin32HandleInfo, HANDLE *pHandle);
#endif

#ifdef VK_KHR_external_fence_win32 // "VK_KHR_external_fence_win32"
VKAPI_ATTR VkResult VKAPI_CALL vkImportFenceWin32HandleKHR(VkDevice device, const VkImportFenceWin32HandleInfoKHR *pImportFenceWin32HandleInfo);
VKAPI_ATTR VkResult VKAPI_CALL vkGetFenceWin32HandleKHR(VkDevice device, const VkFenceGetWin32HandleInfoKHR *pGetWin32HandleInfo, HANDLE *pHandle);
#endif

#ifdef VK_NV_external_memory_win32 // "VK_NV_external_memory_win32"
VKAPI_ATTR VkResult VKAPI_CALL vkGetMemoryWin32HandleNV(VkDevice device, VkDeviceMemory memory, VkExternalMemoryHandleTypeFlagsNV handleType, HANDLE *pHandle);
#endif

// LINUX XCB specific ======================================================================================

#ifdef VK_KHR_xcb_surface // "VK_KHR_xcb_surface"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateXcbSurfaceKHR(VkInstance instance, const VkXcbSurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface);
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXcbPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, xcb_connection_t *connection, xcb_visualid_t visual_id);
#endif

// LINUX XLIB specific =====================================================================================

#ifdef VK_KHR_xlib_surface // "VK_KHR_xlib_surface"
VKAPI_ATTR VkResult VKAPI_CALL vkCreateXlibSurfaceKHR(VkInstance instance, const VkXlibSurfaceCreateInfoKHR *pCreateInfo, const VkAllocationCallbacks *pAllocator, VkSurfaceKHR *pSurface);
VKAPI_ATTR VkBool32 VKAPI_CALL vkGetPhysicalDeviceXlibPresentationSupportKHR(VkPhysicalDevice physicalDevice, uint32_t queueFamilyIndex, Display *dpy, VisualID visualID);
#endif

// LINUX XRANDR specific ===================================================================================

#ifdef VK_EXT_acquire_xlib_display // "VK_EXT_acquire_xlib_display"
VKAPI_ATTR VkResult VKAPI_CALL vkAcquireXlibDisplayEXT(VkPhysicalDevice physicalDevice, Display *dpy, VkDisplayKHR display);
VKAPI_ATTR VkResult VKAPI_CALL vkGetRandROutputDisplayEXT(VkPhysicalDevice physicalDevice, Display *dpy, RROutput rrOutput, VkDisplayKHR *pDisplay);
#endif


#endif // VKO_USE_GLOBAL_FUNCS



