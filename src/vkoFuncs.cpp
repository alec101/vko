#include "vko/include/vkObject.h"
// dynamic library link
#ifdef OS_WIN
#include <Windows.h>
#endif

#if defined(OS_LINUX) || defined(OS_MAC)
#include <dlfcn.h>
#endif



/// there is a conflict with some WIN32 defines for CreateSemaphore and CreateEvent
#ifdef CreateSemaphore
#define OSICREATESEMAPHOREDEF CreateSemaphore
#undef CreateSemaphore
#endif
#ifdef CreateEvent
#define OSICREATEEVENT CreateEvent
#undef CreateEvent
#endif



//#define VKO_LINK_INSTANCE_FUNC(instance, func) func= (PFN_##func)vkGetInstanceProcAddr(instance, #func)
//#define VKO_LINK_DEVICE_FUNC(device, func) func= (PFN_##func)vkGetDeviceProcAddr(device, #func)

#define VKO_LINK_INSTANCE_FUNC(instance, func) in_f->func= (PFN_vk##func)in_f->GetInstanceProcAddr(instance, "vk"#func)


#define VKO_LINK_DEVICE_FUNC(func) if(in_d== nullptr) in_f->func= (PFN_vk##func)in_f->GetInstanceProcAddr(in_i, "vk"#func); \
                                                 else in_f->func= (PFN_vk##func)in_f->GetDeviceProcAddr(in_d, "vk"#func)



VkoFuncs::VkoFuncs() {
  uint8_t *p= (uint8_t *)this;
  for(uint32_t a= 0; a< sizeof(VkoFuncs); a++, p++)
    *p= 0;
}




///=================///
// FUNCTIONS LINKING //
///=================///

#ifdef UNICODE
#define VKO_STR2WIN(x) L##x
#else
#define VKO_STR2WIN(x) x
#endif

void vkObject::_linkLib() {
  #ifdef VK_VERSION_1_0
  // link to Vulkan library
  if(_vulkanLib== nullptr) {
    #if defined(OS_WIN)
    //_vulkanLib= LoadLibrary(str8("vulkan-1.dll"));
    _vulkanLib= LoadLibrary(VKO_STR2WIN("vulkan-1.dll"));
    #elif defined(OS_LINUX) || defined(OS_MAC)

    
      and ofc, libvulkan.so is not the easily advetised link to vulkan

        vvv
        ye but if no driver instals it, then the app will HAVE to come with it
        therefore, i just get that file and that's that!
        so libvulkan.so will be required to be on the executable path dir
        ^^^

        ye, so if libvulkan.so is required to go with the application, then why not link statically, just incorporate it in the executable
        probly it's the best way to go imho
        grab the vulkan1.1 library, link it with the program.

        DO NOT DEL THIS TEXT, COMMENT IT, UNTIL IT'S FULLY STATICALLY LINKED IN


    _osiVulkanLib= dlopen("libvulkan.so.1.1.92.osi", RTLD_NOW);



    #endif
  }

  #endif /// vulkan 1,0



  if(_vulkanLib== nullptr) { errorText= "Couldn't open vulkan library"; return; }
}
#undef VKO_STR2WIN

/*
// this is called by vko constructor, imediatly linking to the library and getting global-critical functions
void vkObject::_linkLibAndCriticalFuncs(VkoFuncs *in_f) {
  bool chatty= true;
  #ifdef VK_VERSION_1_0
  // link to Vulkan library
  if(_vulkanLib== nullptr) {
    #if defined(OS_WIN)
    _vulkanLib= LoadLibrary(str8("vulkan-1.dll"));
    #elif defined(OS_LINUX) || defined(OS_MAC)

    
      and ofc, libvulkan.so is not the easily advetised link to vulkan

        vvv
        ye but if no driver instals it, then the app will HAVE to come with it
        therefore, i just get that file and that's that!
        so libvulkan.so will be required to be on the executable path dir
        ^^^

        ye, so if libvulkan.so is required to go with the application, then why not link statically, just incorporate it in the executable
        probly it's the best way to go imho
        grab the vulkan1.1 library, link it with the program.

        DO NOT DEL THIS TEXT, COMMENT IT, UNTIL IT'S FULLY STATICALLY LINKED IN


    _osiVulkanLib= dlopen("libvulkan.so.1.1.92.osi", RTLD_NOW);



    #endif
  }


  if(_vulkanLib== nullptr) { errorText= "Couldn't open vulkan library"; return; }

  // instance/global function grabber
  in_f->GetInstanceProcAddr= nullptr;
  #if defined(OS_WIN)
  in_f->GetInstanceProcAddr= (PFN_vkGetInstanceProcAddr)GetProcAddress((HMODULE)_vulkanLib, "vkGetInstanceProcAddr");
  #elif defined(OS_LINUX) || defined(OS_MAC)
  in_f->GetInstanceProcAddr= (PFN_vkGetInstanceProcAddr)dlsym(_vulkanLib, "vkGetInstanceProcAddr");
  #endif
  if(in_f->GetInstanceProcAddr== nullptr)
    return;
  
  // global functions that will work without a created instance
  VKO_LINK_INSTANCE_FUNC(nullptr, CreateInstance);
  VKO_LINK_INSTANCE_FUNC(nullptr, EnumerateInstanceExtensionProperties);
  VKO_LINK_INSTANCE_FUNC(nullptr, EnumerateInstanceLayerProperties);
  #endif  /// vulkan 1.0

  #ifdef VK_VERSION_1_1   // vulkan 1.1
  VKO_LINK_INSTANCE_FUNC(nullptr, EnumerateInstanceVersion);
  #endif
  
  // installed api version on the system, instance level
  if(in_f->CreateInstance) {                             // if not even vkCreateInstance is avaible, the api version will stay 0.0.0
    if(!in_f->EnumerateInstanceVersion)                  // if EnumerateInstanceVersion is not on the system, it's vulkan 1.0
      info.installedVulkanVersion= VK_MAKE_VERSION(1, 0, 0);
      osi.vkApiVersion= VK_MAKE_VERSION(1, 0, 0);
    else
      in_f->EnumerateInstanceVersion(&osi.vkApiVersion); // grab the vulkan version
  }

  if(chatty)
    printf("Installed Vulkan API ver[%u.%u.%u]\n", VK_VERSION_MAJOR(osi.vkApiVersion), VK_VERSION_MINOR(osi.vkApiVersion), VK_VERSION_PATCH(osi.vkApiVersion));
}
*/




void vkObject::_linkCriticalFuncs(VkoFuncs *in_f) {
  /// abort if already linked
  if(in_f->critInit)
    return;

  #ifdef VK_VERSION_1_0
  // instance/global function grabber
  in_f->GetInstanceProcAddr= nullptr;                      // vulkan 1.0
  #if defined(OS_WIN)
  in_f->GetInstanceProcAddr= (PFN_vkGetInstanceProcAddr)GetProcAddress((HMODULE)_vulkanLib, "vkGetInstanceProcAddr");
  #elif defined(OS_LINUX) || defined(OS_MAC)
  in_f->GetInstanceProcAddr= (PFN_vkGetInstanceProcAddr)dlsym(_vulkanLib, "vkGetInstanceProcAddr");
  #endif
  if(in_f->GetInstanceProcAddr== nullptr) { errorText= "could not link critical function GetInstanceProcAddr"; return; }

  // global functions that will work without a created instance
  VKO_LINK_INSTANCE_FUNC(nullptr, CreateInstance);
  VKO_LINK_INSTANCE_FUNC(nullptr, EnumerateInstanceExtensionProperties);
  VKO_LINK_INSTANCE_FUNC(nullptr, EnumerateInstanceLayerProperties);
  #endif /// vulkan 1.0

  #ifdef VK_VERSION_1_1   // vulkan 1.1
  VKO_LINK_INSTANCE_FUNC(nullptr, EnumerateInstanceVersion);
  #endif
  
  // installed api version on the system, instance level
  if(in_f->CreateInstance) {                             // if not even vkCreateInstance is avaible, the api version will stay 0.0.0
    if(in_f->EnumerateInstanceVersion== nullptr)                  // if EnumerateInstanceVersion is not on the system, it's vulkan 1.0
      info.apiVersion= VK_MAKE_VERSION(1, 0, 0);
    else
      in_f->EnumerateInstanceVersion(&info.apiVersion); // grab the vulkan version
  }
  in_f->critInit= true;
}






void vkObject::_linkInstanceFuncs(VkoFuncs *in_f, VkInstance in_i) {
  /// abort if already linked
  if(in_f->instInit)
    return;

  #ifdef VK_VERSION_1_0
  VKO_LINK_INSTANCE_FUNC(in_i, DestroyInstance);
  VKO_LINK_INSTANCE_FUNC(in_i, EnumeratePhysicalDevices);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceFeatures);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceFormatProperties);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceImageFormatProperties);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceProperties);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceQueueFamilyProperties);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceMemoryProperties);
  //VKO_LINK_INSTANCE_FUNC(in_i, GetInstanceProcAddr);                   // critical func
  VKO_LINK_INSTANCE_FUNC(in_i, GetDeviceProcAddr);
  VKO_LINK_INSTANCE_FUNC(in_i, CreateDevice);
  //VKO_LINK_INSTANCE_FUNC(in_i, EnumerateInstanceExtensionProperties);  // critical func
  VKO_LINK_INSTANCE_FUNC(in_i, EnumerateDeviceExtensionProperties);
  //VKO_LINK_INSTANCE_FUNC(in_i, EnumerateInstanceLayerProperties);      // critical func
  VKO_LINK_INSTANCE_FUNC(in_i, EnumerateDeviceLayerProperties);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSparseImageFormatProperties);
  #endif /// VK_VERSION_1_0

  #ifdef VK_VERSION_1_1
  //VKO_LINK_INSTANCE_FUNC(in_i, EnumerateInstanceVersion);              // critical func
  VKO_LINK_INSTANCE_FUNC(in_i, EnumeratePhysicalDeviceGroups);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceFeatures2);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceProperties2);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceFormatProperties2);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceImageFormatProperties2);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceQueueFamilyProperties2);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceMemoryProperties2);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSparseImageFormatProperties2);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceExternalBufferProperties);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceExternalFenceProperties);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceExternalSemaphoreProperties);
  #endif ///VK_VERSION_1_0

  #ifdef VK_KHR_surface // "VK_KHR_surface"
  VKO_LINK_INSTANCE_FUNC(in_i, DestroySurfaceKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSurfaceSupportKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSurfaceCapabilitiesKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSurfaceFormatsKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSurfacePresentModesKHR);
  #endif /// VK_KHR_surface

  #ifdef VK_KHR_swapchain // "VK_KHR_swapchain"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDevicePresentRectanglesKHR);
  #endif /// VK_KHR_swapchain

  #ifdef VK_KHR_display // "VK_KHR_display"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceDisplayPropertiesKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceDisplayPlanePropertiesKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetDisplayPlaneSupportedDisplaysKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetDisplayModePropertiesKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, CreateDisplayModeKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetDisplayPlaneCapabilitiesKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, CreateDisplayPlaneSurfaceKHR);
  #endif /// VK_KHR_display

  #ifdef VK_KHR_get_physical_device_properties2 // "VK_KHR_get_physical_device_properties2"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceFeatures2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceProperties2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceFormatProperties2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceImageFormatProperties2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceQueueFamilyProperties2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceMemoryProperties2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSparseImageFormatProperties2KHR);
  #endif /// VK_KHR_get_physical_device_properties2

  #ifdef VK_KHR_device_group_creation // "VK_KHR_device_group_creation"
  VKO_LINK_INSTANCE_FUNC(in_i, EnumeratePhysicalDeviceGroupsKHR);
  #endif /// VK_KHR_device_group_creation

  #ifdef VK_KHR_external_memory_capabilities // "VK_KHR_external_memory_capabilities"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceExternalBufferPropertiesKHR);
  #endif /// VK_KHR_external_memory_capabilities

  #ifdef VK_KHR_external_semaphore_capabilities // "VK_KHR_external_semaphore_capabilities"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceExternalSemaphorePropertiesKHR);
  #endif /// VK_KHR_external_semaphore_capabilities

  #ifdef VK_KHR_get_surface_capabilities2 // "VK_KHR_get_surface_capabilities2"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSurfaceCapabilities2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSurfaceFormats2KHR);
  #endif

  
  #ifdef VK_KHR_get_display_properties2 // "VK_KHR_get_display_properties2"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceDisplayProperties2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceDisplayPlaneProperties2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetDisplayModeProperties2KHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetDisplayPlaneCapabilities2KHR);
  #endif

  
  #ifdef VK_EXT_debug_report // "VK_EXT_debug_report"
  VKO_LINK_INSTANCE_FUNC(in_i, CreateDebugReportCallbackEXT);
  VKO_LINK_INSTANCE_FUNC(in_i, DestroyDebugReportCallbackEXT);
  VKO_LINK_INSTANCE_FUNC(in_i, DebugReportMessageEXT);
  #endif

  #ifdef VK_NV_external_memory_capabilities // "VK_NV_external_memory_capabilities"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceExternalImageFormatPropertiesNV);
  #endif

  #ifdef VK_NVX_device_generated_commands // "VK_NVX_device_generated_commands"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceGeneratedCommandsPropertiesNVX);
  #endif

  #ifdef VK_EXT_direct_mode_display // "VK_EXT_direct_mode_display"
  VKO_LINK_INSTANCE_FUNC(in_i, ReleaseDisplayEXT);
  #endif
  
  #ifdef VK_EXT_display_surface_counter // "VK_EXT_display_surface_counter"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSurfaceCapabilities2EXT);
  #endif

  #ifdef VK_EXT_debug_utils // "VK_EXT_debug_utils"
  VKO_LINK_INSTANCE_FUNC(in_i, CreateDebugUtilsMessengerEXT);
  VKO_LINK_INSTANCE_FUNC(in_i, DestroyDebugUtilsMessengerEXT);
  VKO_LINK_INSTANCE_FUNC(in_i, SubmitDebugUtilsMessageEXT);
  #endif

  #ifdef VK_EXT_sample_locations // "VK_EXT_sample_locations"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceMultisamplePropertiesEXT);
  #endif

  #ifdef VK_EXT_calibrated_timestamps // "VK_EXT_calibrated_timestamps"
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceCalibrateableTimeDomainsEXT);
  #endif

  #ifdef VK_NV_cooperative_matrix
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceCooperativeMatrixPropertiesNV);
  #endif
  
  #ifdef VK_NV_coverage_reduction_mode
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV);
  #endif

  #ifdef VK_EXT_headless_surface
  VKO_LINK_INSTANCE_FUNC(in_i, CreateHeadlessSurfaceEXT);
  #endif








  



  

  // ANDROID OS specific =====================================================================================

  #ifdef VK_KHR_android_surface
  VKO_LINK_INSTANCE_FUNC(in_i, CreateAndroidSurfaceKHR);
  #endif
  
  // FUCHSIA specific ========================================================================================

  #ifdef VK_FUCHSIA_imagepipe_surface
  VKO_LINK_INSTANCE_FUNC(in_i, CreateImagePipeSurfaceFUCHSIA);
  #endif
  
  // IOS specific ============================================================================================

  #ifdef VK_MVK_ios_surface
  VKO_LINK_INSTANCE_FUNC(in_i, CreateIOSSurfaceMVK);
  #endif

  // MAC OS specific =========================================================================================

  #ifdef VK_MVK_macos_surface // "VK_MVK_macos_surface"
  VKO_LINK_INSTANCE_FUNC(in_i, CreateMacOSSurfaceMVK);
  #endif

  // vulkan_metal.h
  #ifdef VK_EXT_metal_surface
  VKO_LINK_INSTANCE_FUNC(in_i, CreateMetalSurfaceEXT);
  #endif

  // VI specific =============================================================================================

  #ifdef VK_NN_vi_surface
  VKO_LINK_INSTANCE_FUNC(in_i, CreateViSurfaceNN);
  #endif

  // WAYLAND specific ========================================================================================

  #ifdef VK_KHR_wayland_surface // "VK_KHR_wayland_surface"
  VKO_LINK_INSTANCE_FUNC(in_i, CreateWaylandSurfaceKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceWaylandPresentationSupportKHR);
  #endif
  
  // WINDOWS specifi =========================================================================================

  #ifdef VK_KHR_win32_surface // "VK_KHR_win32_surface"
  VKO_LINK_INSTANCE_FUNC(in_i, CreateWin32SurfaceKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceWin32PresentationSupportKHR);
  #endif

  #ifdef VK_EXT_full_screen_exclusive
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceSurfacePresentModes2EXT);
  #endif

  // LINUX XCB specific ======================================================================================

  #ifdef VK_KHR_xcb_surface // "VK_KHR_xcb_surface"
  VKO_LINK_INSTANCE_FUNC(in_i, CreateXcbSurfaceKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceXcbPresentationSupportKHR);
  #endif

  // LINUX XLIB specific =====================================================================================

  #ifdef VK_KHR_xlib_surface // "VK_KHR_xlib_surface"
  VKO_LINK_INSTANCE_FUNC(in_i, CreateXlibSurfaceKHR);
  VKO_LINK_INSTANCE_FUNC(in_i, GetPhysicalDeviceXlibPresentationSupportKHR);
  #endif

  // LINUX XRANDR specific ===================================================================================

  #ifdef VK_EXT_acquire_xlib_display // "VK_EXT_acquire_xlib_display"
  VKO_LINK_INSTANCE_FUNC(in_i, AcquireXlibDisplayEXT);
  VKO_LINK_INSTANCE_FUNC(in_i, GetRandROutputDisplayEXT);
  #endif

  // GGP specific ============================================================================================

  #ifdef VK_GGP_stream_descriptor_surface
  VKO_LINK_INSTANCE_FUNC(in_i, CreateStreamDescriptorSurfaceGGP);
  #endif

  in_f->instInit= true;
}







// call it with device=nullptr and the funcs will be linked with the instance (more driver overhead, the global funcs work with this)
void vkObject::_linkDeviceFuncs(VkoFuncs *in_f, VkInstance in_i, VkDevice in_d) {
  /// abort if already linked
  if(in_f->devInit)
    return;

  errorText= nullptr;

  #ifdef VK_VERSION_1_0

  // get the instance-level GetDeviceProcAddr
  in_f->GetDeviceProcAddr= (PFN_vkGetDeviceProcAddr)in_f->GetInstanceProcAddr(instance, "vkGetDeviceProcAddr");
  if(in_f->GetDeviceProcAddr== nullptr) { errorText= "Could not aquire instance-level vkGetDeviceProcAddr. aborting"; return; }

  // get the device-level GetDeviceProcAddr - IS THIS RIGHT? PROBLY IT'S THE SAME THING BUT, WHO THE HECK KNOWS
  if(in_d) {
    in_f->GetDeviceProcAddr= (PFN_vkGetDeviceProcAddr)in_f->GetDeviceProcAddr(in_d, "vkGetDeviceProcAddr");
    if(in_f->GetDeviceProcAddr== nullptr) { errorText= "Could not aquire device-level vkGetDeviceProcAddr. aborting"; return; }
  }
  

  VKO_LINK_DEVICE_FUNC(DestroyDevice);
  VKO_LINK_DEVICE_FUNC(GetDeviceQueue);
  VKO_LINK_DEVICE_FUNC(QueueSubmit);
  VKO_LINK_DEVICE_FUNC(QueueWaitIdle);
  VKO_LINK_DEVICE_FUNC(DeviceWaitIdle);
  VKO_LINK_DEVICE_FUNC(AllocateMemory);
  VKO_LINK_DEVICE_FUNC(FreeMemory);
  VKO_LINK_DEVICE_FUNC(MapMemory);
  VKO_LINK_DEVICE_FUNC(UnmapMemory);
  VKO_LINK_DEVICE_FUNC(FlushMappedMemoryRanges);
  VKO_LINK_DEVICE_FUNC(InvalidateMappedMemoryRanges);
  VKO_LINK_DEVICE_FUNC(GetDeviceMemoryCommitment);
  VKO_LINK_DEVICE_FUNC(BindBufferMemory);
  VKO_LINK_DEVICE_FUNC(BindImageMemory);
  VKO_LINK_DEVICE_FUNC(GetBufferMemoryRequirements);
  VKO_LINK_DEVICE_FUNC(GetImageMemoryRequirements);
  VKO_LINK_DEVICE_FUNC(GetImageSparseMemoryRequirements);
  VKO_LINK_DEVICE_FUNC(QueueBindSparse);
  VKO_LINK_DEVICE_FUNC(CreateFence);
  VKO_LINK_DEVICE_FUNC(DestroyFence);
  VKO_LINK_DEVICE_FUNC(ResetFences);
  VKO_LINK_DEVICE_FUNC(GetFenceStatus);
  VKO_LINK_DEVICE_FUNC(WaitForFences);
  VKO_LINK_DEVICE_FUNC(CreateSemaphore);
  VKO_LINK_DEVICE_FUNC(DestroySemaphore);
  VKO_LINK_DEVICE_FUNC(CreateEvent);
  VKO_LINK_DEVICE_FUNC(DestroyEvent);
  VKO_LINK_DEVICE_FUNC(GetEventStatus);
  VKO_LINK_DEVICE_FUNC(SetEvent);
  VKO_LINK_DEVICE_FUNC(ResetEvent);
  VKO_LINK_DEVICE_FUNC(CreateQueryPool);
  VKO_LINK_DEVICE_FUNC(DestroyQueryPool);
  VKO_LINK_DEVICE_FUNC(GetQueryPoolResults);
  VKO_LINK_DEVICE_FUNC(CreateBuffer);
  VKO_LINK_DEVICE_FUNC(DestroyBuffer);
  VKO_LINK_DEVICE_FUNC(CreateBufferView);
  VKO_LINK_DEVICE_FUNC(DestroyBufferView);
  VKO_LINK_DEVICE_FUNC(CreateImage);
  VKO_LINK_DEVICE_FUNC(DestroyImage);
  VKO_LINK_DEVICE_FUNC(GetImageSubresourceLayout);
  VKO_LINK_DEVICE_FUNC(CreateImageView);
  VKO_LINK_DEVICE_FUNC(DestroyImageView);
  VKO_LINK_DEVICE_FUNC(CreateShaderModule);
  VKO_LINK_DEVICE_FUNC(DestroyShaderModule);
  VKO_LINK_DEVICE_FUNC(CreatePipelineCache);
  VKO_LINK_DEVICE_FUNC(DestroyPipelineCache);
  VKO_LINK_DEVICE_FUNC(GetPipelineCacheData);
  VKO_LINK_DEVICE_FUNC(MergePipelineCaches);
  VKO_LINK_DEVICE_FUNC(CreateGraphicsPipelines);
  VKO_LINK_DEVICE_FUNC(CreateComputePipelines);
  VKO_LINK_DEVICE_FUNC(DestroyPipeline);
  VKO_LINK_DEVICE_FUNC(CreatePipelineLayout);
  VKO_LINK_DEVICE_FUNC(DestroyPipelineLayout);
  VKO_LINK_DEVICE_FUNC(CreateSampler);
  VKO_LINK_DEVICE_FUNC(DestroySampler);
  VKO_LINK_DEVICE_FUNC(CreateDescriptorSetLayout);
  VKO_LINK_DEVICE_FUNC(DestroyDescriptorSetLayout);
  VKO_LINK_DEVICE_FUNC(CreateDescriptorPool);
  VKO_LINK_DEVICE_FUNC(DestroyDescriptorPool);
  VKO_LINK_DEVICE_FUNC(ResetDescriptorPool);
  VKO_LINK_DEVICE_FUNC(AllocateDescriptorSets);
  VKO_LINK_DEVICE_FUNC(FreeDescriptorSets);
  VKO_LINK_DEVICE_FUNC(UpdateDescriptorSets);
  VKO_LINK_DEVICE_FUNC(CreateFramebuffer);
  VKO_LINK_DEVICE_FUNC(DestroyFramebuffer);
  VKO_LINK_DEVICE_FUNC(CreateRenderPass);
  VKO_LINK_DEVICE_FUNC(DestroyRenderPass);
  VKO_LINK_DEVICE_FUNC(GetRenderAreaGranularity);
  VKO_LINK_DEVICE_FUNC(CreateCommandPool);
  VKO_LINK_DEVICE_FUNC(DestroyCommandPool);
  VKO_LINK_DEVICE_FUNC(ResetCommandPool);
  VKO_LINK_DEVICE_FUNC(AllocateCommandBuffers);
  VKO_LINK_DEVICE_FUNC(FreeCommandBuffers);
  VKO_LINK_DEVICE_FUNC(BeginCommandBuffer);
  VKO_LINK_DEVICE_FUNC(EndCommandBuffer);
  VKO_LINK_DEVICE_FUNC(ResetCommandBuffer);
  VKO_LINK_DEVICE_FUNC(CmdBindPipeline);
  VKO_LINK_DEVICE_FUNC(CmdSetViewport);
  VKO_LINK_DEVICE_FUNC(CmdSetScissor);
  VKO_LINK_DEVICE_FUNC(CmdSetLineWidth);
  VKO_LINK_DEVICE_FUNC(CmdSetDepthBias);
  VKO_LINK_DEVICE_FUNC(CmdSetBlendConstants);
  VKO_LINK_DEVICE_FUNC(CmdSetDepthBounds);
  VKO_LINK_DEVICE_FUNC(CmdSetStencilCompareMask);
  VKO_LINK_DEVICE_FUNC(CmdSetStencilWriteMask);
  VKO_LINK_DEVICE_FUNC(CmdSetStencilReference);
  VKO_LINK_DEVICE_FUNC(CmdBindDescriptorSets);
  VKO_LINK_DEVICE_FUNC(CmdBindIndexBuffer);
  VKO_LINK_DEVICE_FUNC(CmdBindVertexBuffers);
  VKO_LINK_DEVICE_FUNC(CmdDraw);
  VKO_LINK_DEVICE_FUNC(CmdDrawIndexed);
  VKO_LINK_DEVICE_FUNC(CmdDrawIndirect);
  VKO_LINK_DEVICE_FUNC(CmdDrawIndexedIndirect);
  VKO_LINK_DEVICE_FUNC(CmdDispatch);
  VKO_LINK_DEVICE_FUNC(CmdDispatchIndirect);
  VKO_LINK_DEVICE_FUNC(CmdCopyBuffer);
  VKO_LINK_DEVICE_FUNC(CmdCopyImage);
  VKO_LINK_DEVICE_FUNC(CmdBlitImage);
  VKO_LINK_DEVICE_FUNC(CmdCopyBufferToImage);
  VKO_LINK_DEVICE_FUNC(CmdCopyImageToBuffer);
  VKO_LINK_DEVICE_FUNC(CmdUpdateBuffer);
  VKO_LINK_DEVICE_FUNC(CmdFillBuffer);
  VKO_LINK_DEVICE_FUNC(CmdClearColorImage);
  VKO_LINK_DEVICE_FUNC(CmdClearDepthStencilImage);
  VKO_LINK_DEVICE_FUNC(CmdClearAttachments);
  VKO_LINK_DEVICE_FUNC(CmdResolveImage);
  VKO_LINK_DEVICE_FUNC(CmdSetEvent);
  VKO_LINK_DEVICE_FUNC(CmdResetEvent);
  VKO_LINK_DEVICE_FUNC(CmdWaitEvents);
  VKO_LINK_DEVICE_FUNC(CmdPipelineBarrier);
  VKO_LINK_DEVICE_FUNC(CmdBeginQuery);
  VKO_LINK_DEVICE_FUNC(CmdEndQuery);
  VKO_LINK_DEVICE_FUNC(CmdResetQueryPool);
  VKO_LINK_DEVICE_FUNC(CmdWriteTimestamp);
  VKO_LINK_DEVICE_FUNC(CmdCopyQueryPoolResults);
  VKO_LINK_DEVICE_FUNC(CmdPushConstants);
  VKO_LINK_DEVICE_FUNC(CmdBeginRenderPass);
  VKO_LINK_DEVICE_FUNC(CmdNextSubpass);
  VKO_LINK_DEVICE_FUNC(CmdEndRenderPass);
  VKO_LINK_DEVICE_FUNC(CmdExecuteCommands);
  #endif // VK_VERSION_1_0

  #ifdef VK_VERSION_1_1
  VKO_LINK_DEVICE_FUNC(BindBufferMemory2);
  VKO_LINK_DEVICE_FUNC(BindImageMemory2);
  VKO_LINK_DEVICE_FUNC(GetDeviceGroupPeerMemoryFeatures);
  VKO_LINK_DEVICE_FUNC(CmdSetDeviceMask);
  VKO_LINK_DEVICE_FUNC(CmdDispatchBase);
  VKO_LINK_DEVICE_FUNC(GetImageMemoryRequirements2);
  VKO_LINK_DEVICE_FUNC(GetBufferMemoryRequirements2);
  VKO_LINK_DEVICE_FUNC(GetImageSparseMemoryRequirements2);
  VKO_LINK_DEVICE_FUNC(TrimCommandPool);
  VKO_LINK_DEVICE_FUNC(GetDeviceQueue2);
  VKO_LINK_DEVICE_FUNC(CreateSamplerYcbcrConversion);
  VKO_LINK_DEVICE_FUNC(DestroySamplerYcbcrConversion);
  VKO_LINK_DEVICE_FUNC(CreateDescriptorUpdateTemplate);
  VKO_LINK_DEVICE_FUNC(DestroyDescriptorUpdateTemplate);
  VKO_LINK_DEVICE_FUNC(UpdateDescriptorSetWithTemplate);
  VKO_LINK_DEVICE_FUNC(GetDescriptorSetLayoutSupport);
  #endif /// #ifdef VK_VERSION_1_1

  // VULKAN EXTENSIONS ==================================================================================

  #ifdef VK_KHR_swapchain // "VK_KHR_swapchain"
  VKO_LINK_DEVICE_FUNC(CreateSwapchainKHR);
  VKO_LINK_DEVICE_FUNC(DestroySwapchainKHR);
  VKO_LINK_DEVICE_FUNC(GetSwapchainImagesKHR);
  VKO_LINK_DEVICE_FUNC(AcquireNextImageKHR);
  VKO_LINK_DEVICE_FUNC(QueuePresentKHR);
  VKO_LINK_DEVICE_FUNC(GetDeviceGroupPresentCapabilitiesKHR);
  VKO_LINK_DEVICE_FUNC(GetDeviceGroupSurfacePresentModesKHR);
  VKO_LINK_DEVICE_FUNC(AcquireNextImage2KHR);
  #endif /// VK_KHR_swapchain

  #ifdef VK_KHR_display_swapchain // "VK_KHR_display_swapchain"
  VKO_LINK_DEVICE_FUNC(CreateSharedSwapchainsKHR);
  #endif /// VK_KHR_display_swapchain

  #ifdef VK_KHR_device_group // "VK_KHR_device_group"
  VKO_LINK_DEVICE_FUNC(GetDeviceGroupPeerMemoryFeaturesKHR);
  VKO_LINK_DEVICE_FUNC(CmdSetDeviceMaskKHR);
  VKO_LINK_DEVICE_FUNC(CmdDispatchBaseKHR);
  #endif /// VK_KHR_device_group

  #ifdef VK_KHR_maintenance1 // "VK_KHR_maintenance1"
  VKO_LINK_DEVICE_FUNC(TrimCommandPoolKHR);
  #endif /// VK_KHR_maintenance1

  #ifdef VK_KHR_external_memory_fd // "VK_KHR_external_memory_fd"
  VKO_LINK_DEVICE_FUNC(GetMemoryFdKHR);
  VKO_LINK_DEVICE_FUNC(GetMemoryFdPropertiesKHR);
  #endif /// VK_KHR_external_memory_fd

  #ifdef VK_KHR_external_semaphore_fd // "VK_KHR_external_semaphore_fd"
  VKO_LINK_DEVICE_FUNC(ImportSemaphoreFdKHR);
  VKO_LINK_DEVICE_FUNC(GetSemaphoreFdKHR);
  #endif /// VK_KHR_external_semaphore_fd

  #ifdef VK_KHR_push_descriptor // "VK_KHR_push_descriptor"
  VKO_LINK_DEVICE_FUNC(CmdPushDescriptorSetKHR);
  VKO_LINK_DEVICE_FUNC(CmdPushDescriptorSetWithTemplateKHR);
  #endif

  #ifdef VK_KHR_descriptor_update_template // "VK_KHR_descriptor_update_template"
  VKO_LINK_DEVICE_FUNC(CreateDescriptorUpdateTemplateKHR);
  VKO_LINK_DEVICE_FUNC(DestroyDescriptorUpdateTemplateKHR);
  VKO_LINK_DEVICE_FUNC(UpdateDescriptorSetWithTemplateKHR);
  #endif /// VK_KHR_descriptor_update_template

  #ifdef VK_KHR_create_renderpass2 // "VK_KHR_create_renderpass2"
  VKO_LINK_DEVICE_FUNC(CreateRenderPass2KHR);
  VKO_LINK_DEVICE_FUNC(CmdBeginRenderPass2KHR);
  VKO_LINK_DEVICE_FUNC(CmdNextSubpass2KHR);
  VKO_LINK_DEVICE_FUNC(CmdEndRenderPass2KHR);
  #endif /// VK_KHR_create_renderpass2

  #ifdef VK_KHR_shared_presentable_image // "VK_KHR_shared_presentable_image"
  VKO_LINK_DEVICE_FUNC(GetSwapchainStatusKHR);
  #endif /// VK_KHR_shared_presentable_image

  #ifdef VK_KHR_external_fence_capabilities // "VK_KHR_external_fence_capabilities"
  VKO_LINK_DEVICE_FUNC(GetPhysicalDeviceExternalFencePropertiesKHR);
  #endif /// VK_KHR_external_fence_capabilities

  #ifdef VK_KHR_external_fence_fd // "VK_KHR_external_fence_fd"
  VKO_LINK_DEVICE_FUNC(ImportFenceFdKHR);
  VKO_LINK_DEVICE_FUNC(GetFenceFdKHR);
  #endif

  #ifdef VK_KHR_performance_query
  VKO_LINK_DEVICE_FUNC(EnumeratePhysicalDeviceQueueFamilyPerformanceQueryCountersKHR);
  VKO_LINK_DEVICE_FUNC(GetPhysicalDeviceQueueFamilyPerformanceQueryPassesKHR);
  VKO_LINK_DEVICE_FUNC(AcquireProfilingLockKHR);
  VKO_LINK_DEVICE_FUNC(ReleaseProfilingLockKHR);
  #endif

  #ifdef VK_KHR_get_memory_requirements2 // "VK_KHR_get_memory_requirements2"
  VKO_LINK_DEVICE_FUNC(GetImageMemoryRequirements2KHR);
  VKO_LINK_DEVICE_FUNC(GetBufferMemoryRequirements2KHR);
  VKO_LINK_DEVICE_FUNC(GetImageSparseMemoryRequirements2KHR);
  #endif

  #ifdef VK_KHR_sampler_ycbcr_conversion // "VK_KHR_sampler_ycbcr_conversion"
  VKO_LINK_DEVICE_FUNC(CreateSamplerYcbcrConversionKHR);
  VKO_LINK_DEVICE_FUNC(DestroySamplerYcbcrConversionKHR);
  #endif

  #ifdef VK_KHR_bind_memory2 // "VK_KHR_bind_memory2"
  VKO_LINK_DEVICE_FUNC(BindBufferMemory2KHR);
  VKO_LINK_DEVICE_FUNC(BindImageMemory2KHR);
  #endif

  #ifdef VK_KHR_maintenance3 // "VK_KHR_maintenance3"
  VKO_LINK_DEVICE_FUNC(GetDescriptorSetLayoutSupportKHR);
  #endif

  #ifdef VK_KHR_draw_indirect_count // "VK_KHR_draw_indirect_count"
  VKO_LINK_DEVICE_FUNC(CmdDrawIndirectCountKHR);
  VKO_LINK_DEVICE_FUNC(CmdDrawIndexedIndirectCountKHR);
  #endif
  
  #ifdef VK_KHR_timeline_semaphore // "VK_KHR_timeline_semaphore"
  VKO_LINK_DEVICE_FUNC(GetSemaphoreCounterValueKHR);
  VKO_LINK_DEVICE_FUNC(WaitSemaphoresKHR);
  VKO_LINK_DEVICE_FUNC(SignalSemaphoreKHR);
  #endif
  
  #ifdef VK_KHR_buffer_device_address
  VKO_LINK_DEVICE_FUNC(GetBufferDeviceAddressKHR);
  VKO_LINK_DEVICE_FUNC(GetBufferOpaqueCaptureAddressKHR);
  VKO_LINK_DEVICE_FUNC(GetDeviceMemoryOpaqueCaptureAddressKHR);
  #endif

  #ifdef VK_KHR_pipeline_executable_properties
  VKO_LINK_DEVICE_FUNC(GetPipelineExecutablePropertiesKHR);
  VKO_LINK_DEVICE_FUNC(GetPipelineExecutableStatisticsKHR);
  VKO_LINK_DEVICE_FUNC(GetPipelineExecutableInternalRepresentationsKHR);
  #endif

  #ifdef VK_EXT_debug_marker // "VK_EXT_debug_marker"
  VKO_LINK_DEVICE_FUNC(DebugMarkerSetObjectTagEXT);
  VKO_LINK_DEVICE_FUNC(DebugMarkerSetObjectNameEXT);
  VKO_LINK_DEVICE_FUNC(CmdDebugMarkerBeginEXT);
  VKO_LINK_DEVICE_FUNC(CmdDebugMarkerEndEXT);
  VKO_LINK_DEVICE_FUNC(CmdDebugMarkerInsertEXT);
  #endif

  #ifdef VK_EXT_transform_feedback // "VK_EXT_transform_feedback"
  VKO_LINK_DEVICE_FUNC(CmdBindTransformFeedbackBuffersEXT);
  VKO_LINK_DEVICE_FUNC(CmdBeginTransformFeedbackEXT);
  VKO_LINK_DEVICE_FUNC(CmdEndTransformFeedbackEXT);
  VKO_LINK_DEVICE_FUNC(CmdBeginQueryIndexedEXT);
  VKO_LINK_DEVICE_FUNC(CmdEndQueryIndexedEXT);
  VKO_LINK_DEVICE_FUNC(CmdDrawIndirectByteCountEXT);
  #endif
  
  #ifdef VK_NVX_image_view_handle // "VK_NVX_image_view_handle"
  VKO_LINK_DEVICE_FUNC(GetImageViewHandleNVX);
  #endif

  #ifdef VK_AMD_draw_indirect_count // "VK_AMD_draw_indirect_count"
  VKO_LINK_DEVICE_FUNC(CmdDrawIndirectCountAMD);
  VKO_LINK_DEVICE_FUNC(CmdDrawIndexedIndirectCountAMD);
  #endif

  #ifdef VK_AMD_shader_info // "VK_AMD_shader_info"
  VKO_LINK_DEVICE_FUNC(GetShaderInfoAMD);
  #endif

  #ifdef VK_EXT_conditional_rendering // "VK_EXT_conditional_rendering"
  VKO_LINK_DEVICE_FUNC(CmdBeginConditionalRenderingEXT);
  VKO_LINK_DEVICE_FUNC(CmdEndConditionalRenderingEXT);
  #endif

  #ifdef VK_NVX_device_generated_commands // "VK_NVX_device_generated_commands"
  VKO_LINK_DEVICE_FUNC(CmdProcessCommandsNVX);
  VKO_LINK_DEVICE_FUNC(CmdReserveSpaceForCommandsNVX);
  VKO_LINK_DEVICE_FUNC(CreateIndirectCommandsLayoutNVX);
  VKO_LINK_DEVICE_FUNC(DestroyIndirectCommandsLayoutNVX);
  VKO_LINK_DEVICE_FUNC(CreateObjectTableNVX);
  VKO_LINK_DEVICE_FUNC(DestroyObjectTableNVX);
  VKO_LINK_DEVICE_FUNC(RegisterObjectsNVX);
  VKO_LINK_DEVICE_FUNC(UnregisterObjectsNVX);
  #endif

  #ifdef VK_NV_clip_space_w_scaling // "VK_NV_clip_space_w_scaling"
  VKO_LINK_DEVICE_FUNC(CmdSetViewportWScalingNV);
  #endif

  #ifdef VK_EXT_display_control // "VK_EXT_display_control"
  VKO_LINK_DEVICE_FUNC(DisplayPowerControlEXT);
  VKO_LINK_DEVICE_FUNC(RegisterDeviceEventEXT);
  VKO_LINK_DEVICE_FUNC(RegisterDisplayEventEXT);
  VKO_LINK_DEVICE_FUNC(GetSwapchainCounterEXT);
  #endif

  #ifdef VK_GOOGLE_display_timing // "VK_GOOGLE_display_timing"
  VKO_LINK_DEVICE_FUNC(GetRefreshCycleDurationGOOGLE);
  VKO_LINK_DEVICE_FUNC(GetPastPresentationTimingGOOGLE);
  #endif

  #ifdef VK_EXT_discard_rectangles // "VK_EXT_discard_rectangles"
  VKO_LINK_DEVICE_FUNC(CmdSetDiscardRectangleEXT);
  #endif

  #ifdef VK_EXT_hdr_metadata // "VK_EXT_hdr_metadata"
  VKO_LINK_DEVICE_FUNC(SetHdrMetadataEXT);
  #endif
  
  #ifdef VK_EXT_debug_utils // "VK_EXT_debug_utils"
  VKO_LINK_DEVICE_FUNC(SetDebugUtilsObjectNameEXT);
  VKO_LINK_DEVICE_FUNC(SetDebugUtilsObjectTagEXT);
  VKO_LINK_DEVICE_FUNC(QueueBeginDebugUtilsLabelEXT);
  VKO_LINK_DEVICE_FUNC(QueueEndDebugUtilsLabelEXT);
  VKO_LINK_DEVICE_FUNC(QueueInsertDebugUtilsLabelEXT);
  VKO_LINK_DEVICE_FUNC(CmdBeginDebugUtilsLabelEXT);
  VKO_LINK_DEVICE_FUNC(CmdEndDebugUtilsLabelEXT);
  VKO_LINK_DEVICE_FUNC(CmdInsertDebugUtilsLabelEXT);
  #endif

  #ifdef VK_EXT_sample_locations // "VK_EXT_sample_locations"
  VKO_LINK_DEVICE_FUNC(CmdSetSampleLocationsEXT);
  #endif

  #ifdef VK_EXT_image_drm_format_modifier // "VK_EXT_image_drm_format_modifier"
  VKO_LINK_DEVICE_FUNC(GetImageDrmFormatModifierPropertiesEXT);
  #endif

  #ifdef VK_EXT_validation_cache // "VK_EXT_validation_cache"
  VKO_LINK_DEVICE_FUNC(CreateValidationCacheEXT);
  VKO_LINK_DEVICE_FUNC(DestroyValidationCacheEXT);
  VKO_LINK_DEVICE_FUNC(MergeValidationCachesEXT);
  VKO_LINK_DEVICE_FUNC(GetValidationCacheDataEXT);
  #endif

  #ifdef VK_NV_shading_rate_image // "VK_NV_shading_rate_image"
  VKO_LINK_DEVICE_FUNC(CmdBindShadingRateImageNV);
  VKO_LINK_DEVICE_FUNC(CmdSetViewportShadingRatePaletteNV);
  VKO_LINK_DEVICE_FUNC(CmdSetCoarseSampleOrderNV);
  #endif

  #ifdef VK_NV_ray_tracing // "VK_NV_ray_tracing"
  VKO_LINK_DEVICE_FUNC(CreateAccelerationStructureNV);
  VKO_LINK_DEVICE_FUNC(DestroyAccelerationStructureNV);
  VKO_LINK_DEVICE_FUNC(GetAccelerationStructureMemoryRequirementsNV);
  VKO_LINK_DEVICE_FUNC(BindAccelerationStructureMemoryNV);
  VKO_LINK_DEVICE_FUNC(CmdBuildAccelerationStructureNV);
  VKO_LINK_DEVICE_FUNC(CmdCopyAccelerationStructureNV);
  VKO_LINK_DEVICE_FUNC(CmdTraceRaysNV);
  VKO_LINK_DEVICE_FUNC(CreateRayTracingPipelinesNV);
  VKO_LINK_DEVICE_FUNC(GetRayTracingShaderGroupHandlesNV);
  VKO_LINK_DEVICE_FUNC(GetAccelerationStructureHandleNV);
  VKO_LINK_DEVICE_FUNC(CmdWriteAccelerationStructuresPropertiesNV);
  VKO_LINK_DEVICE_FUNC(CompileDeferredNV);
  #endif

  #ifdef VK_EXT_external_memory_host // "VK_EXT_external_memory_host"
  VKO_LINK_DEVICE_FUNC(GetMemoryHostPointerPropertiesEXT);
  #endif

  #ifdef VK_AMD_buffer_marker // "VK_AMD_buffer_marker"
  VKO_LINK_DEVICE_FUNC(CmdWriteBufferMarkerAMD);
  #endif

  #ifdef VK_EXT_calibrated_timestamps // "VK_EXT_calibrated_timestamps"
  VKO_LINK_DEVICE_FUNC(GetCalibratedTimestampsEXT);
  #endif

  #ifdef VK_NV_mesh_shader // "VK_NV_mesh_shader"
  VKO_LINK_DEVICE_FUNC(CmdDrawMeshTasksNV);
  VKO_LINK_DEVICE_FUNC(CmdDrawMeshTasksIndirectNV);
  VKO_LINK_DEVICE_FUNC(CmdDrawMeshTasksIndirectCountNV);
  #endif

  #ifdef VK_NV_scissor_exclusive // "VK_NV_scissor_exclusive"
  VKO_LINK_DEVICE_FUNC(CmdSetExclusiveScissorNV);
  #endif

  #ifdef VK_NV_device_diagnostic_checkpoints // "VK_NV_device_diagnostic_checkpoints"
  VKO_LINK_DEVICE_FUNC(CmdSetCheckpointNV);
  VKO_LINK_DEVICE_FUNC(GetQueueCheckpointDataNV);
  #endif
  
  #ifdef VK_INTEL_performance_query // "VK_NV_device_diagnostic_checkpoints"
  VKO_LINK_DEVICE_FUNC(InitializePerformanceApiINTEL);
  VKO_LINK_DEVICE_FUNC(UninitializePerformanceApiINTEL);
  VKO_LINK_DEVICE_FUNC(CmdSetPerformanceMarkerINTEL);
  VKO_LINK_DEVICE_FUNC(CmdSetPerformanceStreamMarkerINTEL);
  VKO_LINK_DEVICE_FUNC(CmdSetPerformanceOverrideINTEL);
  VKO_LINK_DEVICE_FUNC(AcquirePerformanceConfigurationINTEL);
  VKO_LINK_DEVICE_FUNC(ReleasePerformanceConfigurationINTEL);
  VKO_LINK_DEVICE_FUNC(QueueSetPerformanceConfigurationINTEL);
  VKO_LINK_DEVICE_FUNC(GetPerformanceParameterINTEL);
  #endif

  #ifdef VK_AMD_display_native_hdr
  VKO_LINK_DEVICE_FUNC(SetLocalDimmingAMD);
  #endif

  #ifdef VK_EXT_buffer_device_address
  VKO_LINK_DEVICE_FUNC(GetBufferDeviceAddressEXT);
  #endif
  
  #ifdef VK_EXT_tooling_info // VK_EXT_tooling_info
  VKO_LINK_DEVICE_FUNC(GetPhysicalDeviceToolPropertiesEXT);
  #endif

  #ifdef VK_NV_cooperative_matrix
  VKO_LINK_DEVICE_FUNC(GetPhysicalDeviceCooperativeMatrixPropertiesNV);
  #endif

  #ifdef VK_NV_coverage_reduction_mode
  VKO_LINK_DEVICE_FUNC(GetPhysicalDeviceSupportedFramebufferMixedSamplesCombinationsNV);
  #endif

  #ifdef VK_EXT_headless_surface
  VKO_LINK_DEVICE_FUNC(CreateHeadlessSurfaceEXT);
  #endif

  #ifdef VK_EXT_line_rasterization
  VKO_LINK_DEVICE_FUNC(CmdSetLineStippleEXT);
  #endif

  #ifdef VK_EXT_host_query_reset
  VKO_LINK_DEVICE_FUNC(ResetQueryPoolEXT);
  #endif


  // ANDROID OS specific =====================================================================================

  #ifdef VK_ANDROID_external_memory_android_hardware_buffer
  VKO_LINK_DEVICE_FUNC(GetAndroidHardwareBufferPropertiesANDROID);
  VKO_LINK_DEVICE_FUNC(GetMemoryAndroidHardwareBufferANDROID);
  #endif

  // WINDOWS specific =========================================================================================

  #ifdef VK_KHR_external_memory_win32 // "VK_KHR_external_memory_win32"
  VKO_LINK_DEVICE_FUNC(GetMemoryWin32HandleKHR);
  VKO_LINK_DEVICE_FUNC(GetMemoryWin32HandlePropertiesKHR);
  #endif
  
  #ifdef VK_KHR_external_semaphore_win32 // "VK_KHR_external_semaphore_win32"
  VKO_LINK_DEVICE_FUNC(ImportSemaphoreWin32HandleKHR);
  VKO_LINK_DEVICE_FUNC(GetSemaphoreWin32HandleKHR);
  #endif

  #ifdef VK_KHR_external_fence_win32 // "VK_KHR_external_fence_win32"
  VKO_LINK_DEVICE_FUNC(ImportFenceWin32HandleKHR);
  VKO_LINK_DEVICE_FUNC(GetFenceWin32HandleKHR);
  #endif

  #ifdef VK_NV_external_memory_win32 // "VK_NV_external_memory_win32"
  VKO_LINK_DEVICE_FUNC(GetMemoryWin32HandleNV);
  #endif

  #ifdef VK_EXT_full_screen_exclusive
  VKO_LINK_DEVICE_FUNC(AcquireFullScreenExclusiveModeEXT);
  VKO_LINK_DEVICE_FUNC(ReleaseFullScreenExclusiveModeEXT);
  VKO_LINK_DEVICE_FUNC(GetDeviceGroupSurfacePresentModes2EXT);
  #endif

  in_f->devInit= true;
}









