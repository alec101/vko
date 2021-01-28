#include "../include/vkObject.h"

#ifdef VKO_BE_CHATTY
#include <stdio.h>
#endif




bool VkoExtensions::populateAvailabilityInstance() {
  uint32_t n;
  VkExtensionProperties *ext= nullptr;
  bool ret= true;
  #ifdef VKO_BE_CHATTY
  bool chatty= true;
  #endif

  if(_vko->EnumerateInstanceExtensionProperties== nullptr) return false;

  /// get the number of instance extensions avaible
  if(_vko->EnumerateInstanceExtensionProperties(nullptr, &n, nullptr)!= VK_SUCCESS)
    return false;
  if(n== 0) return false;

  /// grab all extensions
  ext= new VkExtensionProperties[n];
  if(_vko->EnumerateInstanceExtensionProperties(nullptr, &n, ext)!= VK_SUCCESS) { ret= false; goto Exit; }

  // populate the availability of known extensions
  
  #ifdef VKO_BE_CHATTY
  if(chatty) printf("\npopulating instance extensions...\n");
  #endif

  for(uint32_t a= 0; a< n; a++) {
    VkoExt *e= getInstanceExt(ext[a].extensionName);
    if(e) {
      e->isAvaible= true;
      #ifdef VKO_BE_CHATTY
      if(chatty) {
        if(e->type!= 0) printf("Extension [%s] should be instance extension but it's a device extension\n", e->name);
        else            printf("Extension [%s]\n", e->name);
      }
      #endif
    } else {
      #ifdef VKO_BE_CHATTY
      if(chatty) printf("Unknown Vulkan instance extension [%s]\n", ext[a].extensionName);
      #endif
    }
  }

Exit:
  if(ext)
    delete[] ext;
  return ret;
}


bool VkoExtensions::populateAvailabilityDevice(VkPhysicalDevice in_gpu) {
  if(in_gpu== nullptr) return false;
  if(_vko->EnumerateDeviceExtensionProperties== nullptr) return false;

  #ifdef VKO_BE_CHATTY
  bool chatty= true;
  #endif

  uint32_t n;
  VkExtensionProperties *ext= nullptr;
  bool ret= true;
  
  /// get the number of instance extensions avaible
  if(_vko->EnumerateDeviceExtensionProperties(in_gpu, nullptr, &n, nullptr)!= VK_SUCCESS)
    return false;
  if(n== 0) return false;

  /// grab all extensions
  ext= new VkExtensionProperties[n];
  if(_vko->EnumerateDeviceExtensionProperties(in_gpu, nullptr, &n, ext)!= VK_SUCCESS) { ret= false; goto Exit; }

  // populate the availability of known extensions

  #ifdef VKO_BE_CHATTY
  if(chatty) printf("\npopulating device extensions...\n");
  #endif

  for(uint32_t a= 0; a< n; a++) {
    VkoExt *e= getDeviceExt(ext[a].extensionName);
    if(e) {
      e->isAvaible= true;
      #ifdef VKO_BE_CHATTY
      if(chatty) {
        if(e->type!= 1) printf("Extension [%s] should be device extension but it's instance extension\n", e->name);
        else            printf("Extension [%s]\n", e->name);
      }
      #endif
    } else {
      #ifdef VKO_BE_CHATTY
      if(chatty) printf("Unknown Vulkan device extension [%s]\n", ext[a].extensionName);
      #endif
    }
  }

Exit:
  if(ext)
    delete[] ext;
  return ret;
}



VkoExt *VkoExtensions::getInstanceExt(const char *in_name) {
  for(VkoExt *p= instance.raw; p->name!= nullptr; p++)
    if(vkObject::_strcmp8(p->name, in_name)== 0)
      return p;

  for(VkoExt *p= instanceDeprecated.raw; p->name!= nullptr; p++)
    if(vkObject::_strcmp8(p->name, in_name)== 0)
      return p;

  return nullptr;
}


VkoExt *VkoExtensions::getDeviceExt(const char *in_name) {
  for(VkoExt *p= device.raw; p->name!= nullptr; p++)
    if(vkObject::_strcmp8(p->name, in_name)== 0)
      return p;

  for(VkoExt *p= deviceDeprecated.raw; p->name!= nullptr; p++)
    if(vkObject::_strcmp8(p->name, in_name)== 0)
      return p;

  return nullptr;
}


VkoExt *VkoExtensions::getExtension(const char *in_name) {
  VkoExt *ret= getInstanceExt(in_name);
  if(ret== nullptr)
    ret= getDeviceExt(in_name);
  return ret;
}



VkoExt *VkoExtensions::getInstanceExtByNumber(int32_t in_n) {
  for(VkoExt *p= instance.raw; p->name!= nullptr; p++)
    if(p->regNr== in_n)
      return p;

  for(VkoExt *p= instanceDeprecated.raw; p->name!= nullptr; p++)
    if(p->regNr== in_n)
      return p;
  return nullptr;
}

VkoExt *VkoExtensions::getDeviceExtByNumber(int32_t in_n) {
  for(VkoExt *p= device.raw; p->name!= nullptr; p++)
    if(p->regNr== in_n)
      return p;

  for(VkoExt *p= deviceDeprecated.raw; p->name!= nullptr; p++)
    if(p->regNr== in_n)
      return p;

  return nullptr;
}




VkoExt *VkoExtensions::getExtensionByNumber(int32_t in_n) {
  VkoExt *ret= getInstanceExtByNumber(in_n);
  if(ret== nullptr)
    ret= getDeviceExtByNumber(in_n);
  return ret;
}


bool VkoExtensions::enableExtension(const char *in_name) {
  VkoExt *p= getExtension(in_name);
  if(p== nullptr) return false;

  p->enable= true;
  return true;
}


bool VkoExtensions::isExtensionAvaible(const char *in_name) {
  VkoExt *p= getExtension(in_name);
  if(p== nullptr) return false;
  return p->isAvaible;
}




void VkoExtensions::_createExtStr(int8_t type, char ***out_s, uint32_t *out_nrext) {
  if(out_s== nullptr) return;
  uint32_t nrext= 0;   /// will hold the number of extensions to enable
  int8_t *s8;
  uint32_t a= 0;

  // loop thru all extensions to find how many are enabled

  // ORIGINAL
  //for(VkoExt *p= _osiVkExtensionsRaw._ext; p->name!= nullptr; p++)
  //  if((p->type== type) && (p->enable== true))
  //    nrext++;

  for(VkoExt *p= instance.raw; p->name!= nullptr; p++)
    if((p->type== type) && (p->enable== true))
      nrext++;
  for(VkoExt *p= instanceDeprecated.raw; p->name!= nullptr; p++)
    if((p->type== type) && (p->enable== true))
      nrext++;
  for(VkoExt *p= device.raw; p->name!= nullptr; p++)
    if((p->type== type) && (p->enable== true))
      nrext++;
  for(VkoExt *p= deviceDeprecated.raw; p->name!= nullptr; p++)
    if((p->type== type) && (p->enable== true))
      nrext++;


  if(out_nrext) *out_nrext= nrext;
  if(nrext== 0) {
    *out_s= nullptr;
    return;
  }

  *out_s= new char *[nrext];

  // loop thru all extensions to create the big string array

  // ORIGINAL
  //for(VkoExt *p= _osiVkExtensionsRaw._ext; p->name!= nullptr; p++)
  //  if((p->type== type) && (p->enable== true)) {
  //    s8= new int8_t[vkObject::_strlen8(p->name)];
  //    vkObject::_strcpy8((char *)s8, p->name);
  //    (*out_s)[a++]= (char *)s8;
  //  }
  for(VkoExt *p= instance.raw; p->name!= nullptr; p++)
    if((p->type== type) && (p->enable== true)) {
      s8= new int8_t[vkObject::_strlen8(p->name)];
      vkObject::_strcpy8((char *)s8, p->name);
      (*out_s)[a++]= (char *)s8;
    }
  for(VkoExt *p= instanceDeprecated.raw; p->name!= nullptr; p++)
    if((p->type== type) && (p->enable== true)) {
      s8= new int8_t[vkObject::_strlen8(p->name)];
      vkObject::_strcpy8((char *)s8, p->name);
      (*out_s)[a++]= (char *)s8;
    }
  for(VkoExt *p= device.raw; p->name!= nullptr; p++)
    if((p->type== type) && (p->enable== true)) {
      s8= new int8_t[vkObject::_strlen8(p->name)];
      vkObject::_strcpy8((char *)s8, p->name);
      (*out_s)[a++]= (char *)s8;
    }
  for(VkoExt *p= deviceDeprecated.raw; p->name!= nullptr; p++)
    if((p->type== type) && (p->enable== true)) {
      s8= new int8_t[vkObject::_strlen8(p->name)];
      vkObject::_strcpy8((char *)s8, p->name);
      (*out_s)[a++]= (char *)s8;
    }

}


















VkoExtensions::VkoExtensions() {
  // instance extensions
  uint32_t a= 0; 
  instance.raw[a++]= {"VK_KHR_android_surface",                 9, 0, 0, 0}; // [android surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_android_surface
  instance.raw[a++]= {"VK_KHR_display",                         3, 0, 0, 0}; // [enumerate displays and available modes on a given device (it has some create stuff too)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_display
  instance.raw[a++]= {"VK_KHR_get_display_properties2",       122, 0, 0, 0}; // [extra device display properties and capabilities] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_get_display_properties2
  instance.raw[a++]= {"VK_KHR_get_surface_capabilities2",     120, 0, 0, 0}; // [extra device surface capabilities] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_get_surface_capabilities2
  instance.raw[a++]= {"VK_KHR_surface",                         1, 0, 0, 0}; // [surfaces] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_surface
  instance.raw[a++]= {"VK_KHR_wayland_surface",                 7, 0, 0, 0}; // [WAYLAND surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_wayland_surface
  instance.raw[a++]= {"VK_KHR_win32_surface",                  10, 0, 0, 0}; // [WIN surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_win32_surface
  instance.raw[a++]= {"VK_KHR_xcb_surface",                     6, 0, 0, 0}; // [XCB surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_xcb_surface
  instance.raw[a++]= {"VK_KHR_xlib_surface",                    5, 0, 0, 0}; // [XLIB surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_xlib_surface
  instance.raw[a++]= {"VK_EXT_acquire_xlib_display",           90, 0, 0, 0}; // [exclusive control on a display currently associated with an X11 screen] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_acquire_xlib_display
  // 10
  instance.raw[a++]= {"VK_EXT_debug_utils",                   129, 0, 0, 0}; // [tons of debug, tag objects, message back, more stuff if you enable validation layers] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_debug_utils
  instance.raw[a++]= {"VK_EXT_direct_mode_display",            89, 0, 0, 0}; // [take exclusive control of displays] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_direct_mode_display
  instance.raw[a++]= {"VK_EXT_display_surface_counter",        91, 0, 0, 0}; // [vertical blanking period counter associated with display surfaces] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_display_surface_counter
  instance.raw[a++]= {"VK_EXT_swapchain_colorspace",          105, 0, 0, 0}; // [Extending VkColorSpaceKHR? i guess] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_swapchain_colorspace
  instance.raw[a++]= {"VK_FUCHSIA_imagepipe_surface",         215, 0, 0, 0}; // [create a VkSurfaceKHR object that refers to a Fuchsia imagePipeHandle] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_FUCHSIA_imagepipe_surface
  instance.raw[a++]= {"VK_MVK_ios_surface",                   123, 0, 0, 0}; // [surface to UIView (iOS)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_MVK_ios_surface
  instance.raw[a++]= {"VK_MVK_macos_surface",                 124, 0, 0, 0}; // [surface to NSView (MAC)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_MVK_macos_surface
  instance.raw[a++]= {"VK_NN_vi_surface",                      63, 0, 0, 0}; // [surface to nn::vi::Layer] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NN_vi_surface
  instance.raw[a++]= {"VK_EXT_headless_surface",              257, 0, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_headless_surface
  instance.raw[a++]= {"VK_KHR_surface_protected_capabilities",240, 0, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_KHR_surface_protected_capabilities
  // 20
  instance.raw[a++]= {"VK_EXT_metal_surface",                 218, 0, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_metal_surface
  instance.raw[a++]= {"VK_EXT_validation_features",           248, 0, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_validation_features
  instance.raw[a++]= {"VK_GGP_stream_descriptor_surface",      50, 0, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_GGP_stream_descriptor_surface
  instance.raw[a++]= {"VK_EXT_directfb_surface",              347, 0, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_directfb_surface
  //instance.raw[a++]= {"",           000, 0, 0, 0}; // 
  instance.raw[a++]= { nullptr, 0, 0, 0, 0}; // terminator



  // instance extensions DEPRECATED - stop using them
  a= 0;
  instanceDeprecated.raw[a++]= {"VK_KHR_device_group_creation",            71, 0, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_device_group_creation
  instanceDeprecated.raw[a++]= {"VK_KHR_external_fence_capabilities",     113, 0, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_fence_capabilities
  instanceDeprecated.raw[a++]= {"VK_KHR_external_memory_capabilities",     72, 0, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_memory_capabilities
  instanceDeprecated.raw[a++]= {"VK_KHR_external_semaphore_capabilities",  77, 0, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_semaphore_capabilities
  instanceDeprecated.raw[a++]= {"VK_KHR_get_physical_device_properties2",  60, 0, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_get_physical_device_properties2
  instanceDeprecated.raw[a++]= {"VK_EXT_debug_report",                     12, 0, 0, 0}; // [Deprecated by VK_EXT_debug_utils] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_debug_report
  instanceDeprecated.raw[a++]= {"VK_NV_external_memory_capabilities",      56, 0, 0, 0}; // [Deprecated by VK_KHR_external_memory_capabilities that was promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_external_memory_capabilities
  instanceDeprecated.raw[a++]= {"VK_EXT_validation_flags",                 62, 0, 0, 0}; // Deprecated by VK_EXT_validation_features[instance creation: pNext extra struct] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_validation_flags
  instanceDeprecated.raw[a++]= { nullptr, 0, 0, 0, 0}; // terminator



  // device extensions
  a= 0;
// 0
  device.raw[a++]= {"VK_KHR_display_swapchain",                  4, 1, 0, 0}; // [create a swapchain directly on a device�s display] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_display_swapchain
  device.raw[a++]= {"VK_KHR_external_fence_fd",                116, 1, 0, 0}; // [import/export fence payload POSIX] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_fence_fd
  device.raw[a++]= {"VK_KHR_external_fence_win32",             115, 1, 0, 0}; // [import/export fence payload WIN] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_fence_win32
  device.raw[a++]= {"VK_KHR_external_memory_fd",                75, 1, 0, 0}; // [import/export POSIX file descr/vulkan mem] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_memory_fd
  device.raw[a++]= {"VK_KHR_external_memory_win32",             74, 1, 0, 0}; // [import/export WIN file descr/vulkan mem] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_memory_win32
  device.raw[a++]= {"VK_KHR_external_semaphore_fd",             80, 1, 0, 0}; // [import/export semaphore payload POSIX] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_semaphore_fd
  device.raw[a++]= {"VK_KHR_external_semaphore_win32",          79, 1, 0, 0}; // [import/export semaphore payload WIN] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_semaphore_win32
  device.raw[a++]= {"VK_KHR_incremental_present",               85, 1, 0, 0}; // [avoid wasting time presenting parts of the surface that haven�t changed] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_incremental_present
  device.raw[a++]= {"VK_KHR_push_descriptor",                   81, 1, 0, 0}; // [Push descriptors may enable easier porting from older APIs] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_push_descriptor
  device.raw[a++]= {"VK_KHR_shared_presentable_image",         112, 1, 0, 0}; // [shared presentable image] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_shared_presentable_image
  // 10
  device.raw[a++]= {"VK_KHR_swapchain",                          2, 1, 0, 0}; // [present rendering results to a surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_swapchain
  device.raw[a++]= {"VK_KHR_win32_keyed_mutex",                 76, 1, 0, 0}; // [Vulkan/Direct3D mem access mutex] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_win32_keyed_mutex
  device.raw[a++]= {"VK_EXT_astc_decode_mode",                  68, 1, 0, 0}; // [compressed textures exact decoding] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_astc_decode_mode
  device.raw[a++]= {"VK_EXT_blend_operation_advanced",         149, 1, 0, 0}; // [..advanced blending, what else?] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_blend_operation_advanced
  device.raw[a++]= {"VK_EXT_calibrated_timestamps",            185, 1, 0, 0}; // ["query calibrated timestamps obtained quasi simultaneously from two time domains"] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_calibrated_timestamps
  device.raw[a++]= {"VK_EXT_conditional_rendering",             82, 1, 0, 0}; // [rendering conditional on a val in buff memory] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_conditional_rendering
  device.raw[a++]= {"VK_EXT_conservative_rasterization",       102, 1, 0, 0}; // [new rasterization mode, culling stuff, probly to avoid stuff just apearing on the screen] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_conservative_rasterization
  device.raw[a++]= {"VK_EXT_depth_range_unrestricted",          14, 1, 0, 0}; // [~3 depth restriction removes] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_depth_range_unrestricted
  device.raw[a++]= {"VK_EXT_discard_rectangles",               100, 1, 0, 0}; // [�discard rectangles� (no lines/points/triangles in that space)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_discard_rectangles
  device.raw[a++]= {"VK_EXT_display_control",                   92, 1, 0, 0}; // [utility functions for display/swapchain] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_display_control
  // 20
  device.raw[a++]= {"VK_EXT_external_memory_dma_buf",          126, 1, 0, 0}; // [LINUX those files that act like memory] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_external_memory_dma_buf
  device.raw[a++]= {"VK_EXT_external_memory_host",             179, 1, 0, 0}; // [import host alocations/maped foreign device to vulkan mem] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_external_memory_host
  device.raw[a++]= {"VK_EXT_global_priority",                  175, 1, 0, 0}; // [system-wide scope for queue priorities] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_global_priority
  device.raw[a++]= {"VK_EXT_hdr_metadata",                     106, 1, 0, 0}; // [SMPTE&CTA (hdr) metadata to a swapchain] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_hdr_metadata
  device.raw[a++]= {"VK_EXT_image_drm_format_modifier",        159, 1, 0, 0}; // [LINUX drm format modifiers for images] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_image_drm_format_modifier
  device.raw[a++]= {"VK_EXT_inline_uniform_block",             139, 1, 0, 0}; // [uniform blocks -> descriptor sets] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_inline_uniform_block
  device.raw[a++]= {"VK_EXT_pci_bus_info",                     213, 1, 0, 0}; // [PCI bus information about a physical device] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_pci_bus_info
  device.raw[a++]= {"VK_EXT_post_depth_coverage",              156, 1, 0, 0}; // [support for SPIR-V SPV_KHR_post_depth_coverage] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_post_depth_coverage
  device.raw[a++]= {"VK_EXT_queue_family_foreign",             127, 1, 0, 0}; // [special queue family] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_queue_family_foreign
  device.raw[a++]= {"VK_EXT_sample_locations",                 144, 1, 0, 0}; // [modify the locations of samples within a pixel used in rasterization] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_sample_locations
  // 30
  device.raw[a++]= {"VK_EXT_shader_stencil_export",            141, 1, 0, 0}; // [support for SPIR-V SPV_EXT_shader_stencil_export] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_shader_stencil_export
  device.raw[a++]= {"VK_EXT_shader_subgroup_ballot",            65, 1, 0, 0}; // [support for SPIR-V SPV_KHR_shader_ballot] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_shader_subgroup_ballot
  device.raw[a++]= {"VK_EXT_shader_subgroup_vote",              66, 1, 0, 0}; // [support for SPIR-V SPV_KHR_subgroup_vote] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_shader_subgroup_vote
  device.raw[a++]= {"VK_EXT_transform_feedback",                29, 1, 0, 0}; // [match OpenGL core transform feedback functionality] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_transform_feedback
  device.raw[a++]= {"VK_EXT_validation_cache",                 161, 1, 0, 0}; // [mechanism for caching the results of potentially expensive internal validation operations] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_validation_cache
  device.raw[a++]= {"VK_EXT_vertex_attribute_divisor",         191, 1, 0, 0}; // [instanced rendering: repeat vertex attrib a nr of times] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_vertex_attribute_divisor
  device.raw[a++]= {"VK_AMD_buffer_marker",                    180, 1, 0, 0}; // [debug:tracking which pipelined command contributed to device loss] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_buffer_marker
  device.raw[a++]= {"VK_AMD_gcn_shader",                        26, 1, 0, 0}; // [support for SPV_AMD_gcn_shader] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_gcn_shader
  device.raw[a++]= {"VK_AMD_memory_overallocation_behavior",   190, 1, 0, 0}; // [explicit overallocation beyond the device memory heap sizes] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_memory_overallocation_behavior
  device.raw[a++]= {"VK_AMD_mixed_attachment_samples",         137, 1, 0, 0}; // [depth/stencil sample count that is larger than the color sample count] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_mixed_attachment_samples
  // 40
  device.raw[a++]= {"VK_AMD_rasterization_order",               19, 1, 0, 0}; // [control the order of primitive rasterization] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_rasterization_order
  device.raw[a++]= {"VK_AMD_shader_ballot",                     38, 1, 0, 0}; // [support for SPV_AMD_shader_ballot] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_ballot
  device.raw[a++]= {"VK_AMD_shader_core_properties",           186, 1, 0, 0}; // [exposes shader core properties] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_core_properties
  device.raw[a++]= {"VK_AMD_shader_explicit_vertex_parameter",  22, 1, 0, 0}; // [device] [support for SPV_AMD_shader_explicit_vertex_parameter] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_explicit_vertex_parameter
  device.raw[a++]= {"VK_AMD_shader_fragment_mask",             138, 1, 0, 0}; // [efficient read access to the fragment mask in compressed multisampled color surfaces] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_fragment_mask
  device.raw[a++]= {"VK_AMD_shader_image_load_store_lod",       47, 1, 0, 0}; // [support for SPV_AMD_shader_image_load_store_lod] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_image_load_store_lod
  device.raw[a++]= {"VK_AMD_shader_info",                       43, 1, 0, 0}; // [query info about a compiled shader, part of a pipeline] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_info
  device.raw[a++]= {"VK_AMD_shader_trinary_minmax",             21, 1, 0, 0}; // [support for SPV_AMD_shader_trinary_minmax] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_trinary_minmax
  device.raw[a++]= {"VK_AMD_texture_gather_bias_lod",           42, 1, 0, 0}; // [support for SPV_AMD_texture_gather_bias_lod] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_texture_gather_bias_lod
  device.raw[a++]= {"VK_ANDROID_external_memory_android_hardware_buffer", 130, 1, 0, 0}; // [device] [import Android AHardwareBuffer objects] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_ANDROID_external_memory_android_hardware_buffer
  // 50
  device.raw[a++]= {"VK_GOOGLE_decorate_string",               225, 1, 0, 0}; // [support for SPV_GOOGLE_decorate_string] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_GOOGLE_decorate_string
  device.raw[a++]= {"VK_GOOGLE_display_timing",                 93, 1, 0, 0}; // [obtain info about the presentation engine�s display] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_GOOGLE_display_timing
  device.raw[a++]= {"VK_GOOGLE_hlsl_functionality1",           224, 1, 0, 0}; // [support for SPV_GOOGLE_hlsl_functionality1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_GOOGLE_hlsl_functionality1
  device.raw[a++]= {"VK_IMG_filter_cubic",                      16, 1, 0, 0}; // [high quality cubic filtering mode] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_IMG_filter_cubic
  device.raw[a++]= {"VK_IMG_format_pvrtc",                      17, 1, 0, 0}; // [] [] ??? NO INFO ATM ON THE REGISTRY
  device.raw[a++]= {"VK_NVX_device_generated_commands",         87, 1, 0, 0}; // [generate a number of critical commands for command buffers] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NVX_device_generated_commands
  device.raw[a++]= {"VK_NVX_multiview_per_view_attributes",     98, 1, 0, 0}; // [may only execute the vertex processing stages once for all views rather than once per-view] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NVX_multiview_per_view_attributes
  device.raw[a++]= {"VK_NV_clip_space_w_scaling",               88, 1, 0, 0}; // [accurate VR barrel distortion] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_clip_space_w_scaling
  device.raw[a++]= {"VK_NV_compute_shader_derivatives",        202, 1, 0, 0}; // [support for SPV_NV_compute_shader_derivatives] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_compute_shader_derivatives
  device.raw[a++]= {"VK_NV_corner_sampled_image",               51, 1, 0, 0}; // [new image organization �corner-sampled� (ints, best for texture dictionary i guess)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_corner_sampled_image
  // 60
  device.raw[a++]= {"VK_NV_device_diagnostic_checkpoints",     207, 1, 0, 0}; // [insert markers in the command stream and associate them with custom data] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_device_diagnostic_checkpoints
  device.raw[a++]= {"VK_NV_fill_rectangle",                    154, 1, 0, 0}; // [draw rectangles with only one triangle] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_fill_rectangle
  device.raw[a++]= {"VK_NV_fragment_coverage_to_color",        150, 1, 0, 0}; // [] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_fragment_coverage_to_color
  device.raw[a++]= {"VK_NV_fragment_shader_barycentric",       204, 1, 0, 0}; // [support for SPV_NV_fragment_shader_barycentric] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_fragment_shader_barycentric
  device.raw[a++]= {"VK_NV_framebuffer_mixed_samples",         153, 1, 0, 0}; // [] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_framebuffer_mixed_samples
  device.raw[a++]= {"VK_NV_geometry_shader_passthrough",        96, 1, 0, 0}; // [support for SPV_NV_geometry_shader_passthrough] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_geometry_shader_passthrough
  device.raw[a++]= {"VK_NV_mesh_shader",                       203, 1, 0, 0}; // [generate collections of geometric primitives ] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_mesh_shader
  device.raw[a++]= {"VK_NV_ray_tracing",                       166, 1, 0, 0}; // [raytracing, what else] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_ray_tracing
  device.raw[a++]= {"VK_NV_representative_fragment_test",      167, 1, 0, 0}; // [useful for apps that render to determine what primitives are visible] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_representative_fragment_test
  device.raw[a++]= {"VK_NV_sample_mask_override_coverage",      95, 1, 0, 0}; // [support for SPV_NV_sample_mask_override_coverage] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_sample_mask_override_coverage
  // 70
  device.raw[a++]= {"VK_NV_scissor_exclusive",                 206, 1, 0, 0}; // [basically inverse-scencil] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_scissor_exclusive
  device.raw[a++]= {"VK_NV_shader_image_footprint",            205, 1, 0, 0}; // [support for SPV_NV_shader_image_footprint] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_shader_image_footprint
  device.raw[a++]= {"VK_NV_shader_subgroup_partitioned",       199, 1, 0, 0}; // [support for SPV_NV_shader_subgroup_partitioned] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_shader_subgroup_partitioned
  device.raw[a++]= {"VK_NV_shading_rate_image",                165, 1, 0, 0}; // [eye focus, the blur parts can get less fragments] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_shading_rate_image
  device.raw[a++]= {"VK_NV_viewport_array2",                    97, 1, 0, 0}; // [support for SPV_NV_viewport_array2] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_viewport_array2
  device.raw[a++]= {"VK_NV_viewport_swizzle",                   99, 1, 0, 0}; // [] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_viewport_swizzle
  device.raw[a++]= {"VK_KHR_performance_query",                117, 1, 0, 0}; // [...adds a mechanism to allow querying of performance counters for use in applications and by profiling tools.] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap40.html#VK_KHR_performance_query  device.raw[a++]= { nullptr, 0, 0, 0, 0}; // terminator
  device.raw[a++]= {"VK_KHR_pipeline_executable_properties",   270, 1, 0, 0}; // [debugging and performance tool] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap40.html#VK_KHR_pipeline_executable_properties
  device.raw[a++]= {"VK_NVX_image_view_handle",                 31, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NVX_image_view_handle
  device.raw[a++]= {"VK_INTEL_performance_query",              211, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_INTEL_performance_query
  // 80
  device.raw[a++]= {"VK_AMD_display_native_hdr",               214, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_AMD_display_native_hdr
  device.raw[a++]= {"VK_EXT_tooling_info",                     246, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_tooling_info
  device.raw[a++]= {"VK_NV_cooperative_matrix",                250, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NV_cooperative_matrix
  device.raw[a++]= {"VK_NV_coverage_reduction_mode",           251, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NV_coverage_reduction_mode
  device.raw[a++]= {"VK_EXT_line_rasterization",               260, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_line_rasterization
  device.raw[a++]= {"VK_KHR_shader_clock",                     182, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_KHR_shader_clock
  device.raw[a++]= {"VK_KHR_swapchain_mutable_format",         201, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_KHR_swapchain_mutable_format
  device.raw[a++]= {"VK_EXT_depth_clip_enable",                103, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_depth_clip_enable
  device.raw[a++]= {"VK_EXT_filter_cubic",                     171, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_filter_cubic
  device.raw[a++]= {"VK_EXT_fragment_density_map",             219, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_fragment_density_map
  // 90
  device.raw[a++]= {"VK_EXT_fragment_shader_interlock",        252, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_fragment_shader_interlock
  device.raw[a++]= {"VK_EXT_full_screen_exclusive",            256, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_full_screen_exclusive
  device.raw[a++]= {"VK_EXT_index_type_uint8",                 266, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_index_type_uint8
  device.raw[a++]= {"VK_EXT_memory_budget",                    238, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_memory_budget
  device.raw[a++]= {"VK_EXT_memory_priority",                  239, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_memory_priority
  device.raw[a++]= {"VK_EXT_pipeline_creation_feedback",       193, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_pipeline_creation_feedback
  device.raw[a++]= {"VK_EXT_shader_demote_to_helper_invocation", 277, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_shader_demote_to_helper_invocation
  device.raw[a++]= {"VK_EXT_subgroup_size_control",            226, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_subgroup_size_control
  device.raw[a++]= {"VK_EXT_texel_buffer_alignment",           282, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_texel_buffer_alignment
  device.raw[a++]= {"VK_EXT_texture_compression_astc_hdr",      67, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_texture_compression_astc_hdr
  // 100
  device.raw[a++]= {"VK_EXT_ycbcr_image_arrays",               253, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_ycbcr_image_arrays
  device.raw[a++]= {"VK_AMD_device_coherent_memory",           230, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_AMD_device_coherent_memory
  device.raw[a++]= {"VK_AMD_pipeline_compiler_control",        184, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_AMD_pipeline_compiler_control
  device.raw[a++]= {"VK_AMD_shader_core_properties2",          228, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_AMD_shader_core_properties2
  device.raw[a++]= {"VK_GGP_frame_token",                      192, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_GGP_frame_token
  device.raw[a++]= {"VK_GOOGLE_user_type",                     290, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_GOOGLE_user_type
  device.raw[a++]= {"VK_INTEL_shader_integer_functions2",      210, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_INTEL_shader_integer_functions2
  device.raw[a++]= {"VK_NV_dedicated_allocation_image_aliasing", 241, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NV_dedicated_allocation_image_aliasing
  device.raw[a++]= {"VK_NV_shader_sm_builtins",                155, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NV_shader_sm_builtins
  device.raw[a++]= {"VK_EXT_extended_dynamic_state",           268, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap48.html#VK_EXT_extended_dynamic_state
  // 110
  device.raw[a++]= {"VK_NV_device_generated_commands",         278, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap48.html#VK_NV_device_generated_commands
  device.raw[a++]= {"VK_EXT_private_data",                     296, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap48.html#VK_EXT_private_data
  device.raw[a++]= {"VK_QCOM_render_pass_transform",           283, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_QCOM_render_pass_transform
  device.raw[a++]= {"VK_EXT_device_memory_report",             285, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_device_memory_report
  device.raw[a++]= {"VK_EXT_robustness2",                      287, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_robustness2
  device.raw[a++]= {"VK_EXT_custom_border_color",              288, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_custom_border_color
  device.raw[a++]= {"VK_EXT_pipeline_creation_cache_control",  298, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_pipeline_creation_cache_control
  device.raw[a++]= {"VK_NV_device_diagnostics_config",         301, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_NV_device_diagnostics_config
  device.raw[a++]= {"VK_QCOM_render_pass_store_ops",           302, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_QCOM_render_pass_store_ops
  device.raw[a++]= {"VK_NV_fragment_shading_rate_enums",       327, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_NV_fragment_shading_rate_enums
  // 120
  device.raw[a++]= {"VK_EXT_fragment_density_map2",            333, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_fragment_density_map2
  device.raw[a++]= {"VK_QCOM_rotated_copy_commands",           334, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_QCOM_rotated_copy_commands
  device.raw[a++]= {"VK_EXT_image_robustness",                 336, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_image_robustness
  device.raw[a++]= {"VK_EXT_4444_formats",                     341, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_4444_formats
  device.raw[a++]= {"VK_NV_acquire_winrt_display",             346, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_NV_acquire_winrt_display
  device.raw[a++]= {"VK_VALVE_mutable_descriptor_type",        352, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_VALVE_mutable_descriptor_type
  device.raw[a++]= {"VK_KHR_acceleration_structure",           151, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_acceleration_structure
  device.raw[a++]= {"VK_KHR_ray_tracing_pipeline",             348, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_ray_tracing_pipeline
  device.raw[a++]= {"VK_KHR_ray_query",                        349, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_ray_query
  device.raw[a++]= {"VK_EXT_shader_image_atomic_int64",        235, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_shader_image_atomic_int64
  // 130
  device.raw[a++]= {"VK_EXT_shader_atomic_float",              261, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_EXT_shader_atomic_float
  device.raw[a++]= {"VK_KHR_shader_non_semantic_info",         294, 1, 0, 0}; // https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_shader_non_semantic_info
  //device.raw[a++]= {"",        000, 1, 0, 0}; // 
  device.raw[a++]= { nullptr, 0, 0, 0, 0}; // terminator
  

  // device extensions - DEPRECATED 
  a= 0;
  deviceDeprecated.raw[a++]= {"VK_KHR_16bit_storage",                   84, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_16bit_storage
  deviceDeprecated.raw[a++]= {"VK_KHR_bind_memory2",                   158, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_bind_memory2
  deviceDeprecated.raw[a++]= {"VK_KHR_dedicated_allocation",           128, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_dedicated_allocation
  deviceDeprecated.raw[a++]= {"VK_KHR_descriptor_update_template",      86, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_descriptor_update_template
  deviceDeprecated.raw[a++]= {"VK_KHR_device_group",                    61, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_device_group
  deviceDeprecated.raw[a++]= {"VK_KHR_external_fence",                 114, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_fence
  deviceDeprecated.raw[a++]= {"VK_KHR_external_memory",                 73, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_memory
  deviceDeprecated.raw[a++]= {"VK_KHR_external_semaphore",              78, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_semaphore
  deviceDeprecated.raw[a++]= {"VK_KHR_get_memory_requirements2",       147, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_get_memory_requirements2
  deviceDeprecated.raw[a++]= {"VK_KHR_maintenance1",                    70, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_maintenance1
  // 10
  deviceDeprecated.raw[a++]= {"VK_KHR_maintenance2",                   118, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_maintenance2
  deviceDeprecated.raw[a++]= {"VK_KHR_maintenance3",                   169, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_maintenance3
  deviceDeprecated.raw[a++]= {"VK_KHR_multiview",                       54, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_multiview
  deviceDeprecated.raw[a++]= {"VK_KHR_relaxed_block_layout",           145, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_relaxed_block_layout
  deviceDeprecated.raw[a++]= {"VK_KHR_sampler_ycbcr_conversion",       157, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_sampler_ycbcr_conversion
  deviceDeprecated.raw[a++]= {"VK_KHR_shader_draw_parameters",          64, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_shader_draw_parameters
  deviceDeprecated.raw[a++]= {"VK_KHR_storage_buffer_storage_class",   132, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_storage_buffer_storage_class
  deviceDeprecated.raw[a++]= {"VK_KHR_variable_pointers",              121, 1, 0, 0}; // [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_variable_pointers
  deviceDeprecated.raw[a++]= {"VK_EXT_debug_marker",                    23, 1, 0, 0}; // [Promoted to VK_EXT_debug_utils] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_debug_marker
  deviceDeprecated.raw[a++]= {"VK_AMD_draw_indirect_count",             34, 1, 0, 0}; // [Promoted to VK_KHR_draw_indirect_count] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_draw_indirect_count
  // 20
  deviceDeprecated.raw[a++]= {"VK_AMD_negative_viewport_height",        36, 1, 0, 0}; // [deprecated by VK_KHR_maintenance1 that is promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_negative_viewport_height
  deviceDeprecated.raw[a++]= {"VK_NV_dedicated_allocation",             27, 1, 0, 0}; // [deprecated by VK_KHR_dedicated_allocation that was promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_dedicated_allocation
  deviceDeprecated.raw[a++]= {"VK_NV_external_memory",                  57, 1, 0, 0}; // [deprecated by VK_KHR_external_memory that was promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_external_memory
  deviceDeprecated.raw[a++]= {"VK_NV_external_memory_win32",            58, 1, 0, 0}; // [Deprecated by VK_KHR_external_memory_win32] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_external_memory_win32
  deviceDeprecated.raw[a++]= {"VK_NV_glsl_shader",                      13, 1, 0, 0}; // [Deprecated (ABANDONED!!!)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_glsl_shader
  deviceDeprecated.raw[a++]= {"VK_NV_win32_keyed_mutex",                59, 1, 0, 0}; // [Promoted to VK_KHR_win32_keyed_mutex] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_win32_keyed_mutex
  deviceDeprecated.raw[a++]= {"VK_KHR_timeline_semaphore",             208, 1, 0, 0}; // [Promoted to Vulkan 1.2] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap40.html#VK_KHR_timeline_semaphore
  deviceDeprecated.raw[a++]= {"VK_KHR_buffer_device_address",          258, 1, 0, 0}; // [Promoted to Vulkan 1.2] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap40.html#VK_KHR_buffer_device_address
  deviceDeprecated.raw[a++]= {"VK_EXT_buffer_device_address",          245, 1, 0, 0}; // [DEPRECATED by VK_KHR_buffer_device_address -> Promoted to Vulkan 1.2] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_buffer_device_address
  deviceDeprecated.raw[a++]= {"VK_EXT_host_query_reset",               262, 1, 0, 0}; // [Promoted to Vulkan 1.2] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_host_query_reset
  // 30
  deviceDeprecated.raw[a++]= {"VK_KHR_8bit_storage",                   178, 1, 0, 0}; // Promoted to Vulkan 1.2 [allows use of 8-bit types in uniform and storage buffers] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_8bit_storage
  deviceDeprecated.raw[a++]= {"VK_KHR_create_renderpass2",             110, 1, 0, 0}; // Promoted to Vulkan 1.2 [extended render passes] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_create_renderpass2
  deviceDeprecated.raw[a++]= {"VK_KHR_draw_indirect_count",            170, 1, 0, 0}; // Promoted to Vulkan 1.2 [generate arbitrary amounts of draw commands and execute them without host intervention] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_draw_indirect_count
  deviceDeprecated.raw[a++]= {"VK_KHR_driver_properties",              197, 1, 0, 0}; // Promoted to Vulkan 1.2 [what driver coresponds to what GPU] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_driver_properties
  deviceDeprecated.raw[a++]= {"VK_KHR_image_format_list",              148, 1, 0, 0}; // Promoted to Vulkan 1.2 [provide the list of all formats that can be used with an image when it is created] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_image_format_list
  deviceDeprecated.raw[a++]= {"VK_KHR_sampler_mirror_clamp_to_edge",    15, 1, 0, 0}; // Promoted to Vulkan 1.2 [mirror_clamp_to_edge<- textures] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_sampler_mirror_clamp_to_edge
  deviceDeprecated.raw[a++]= {"VK_KHR_shader_atomic_int64",            181, 1, 0, 0}; // Promoted to Vulkan 1.2 [int64] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_shader_atomic_int64
  deviceDeprecated.raw[a++]= {"VK_EXT_descriptor_indexing",            162, 1, 0, 0}; // [descriptor sets containing substantially all of app resources] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_descriptor_indexing
  deviceDeprecated.raw[a++]= {"VK_EXT_sampler_filter_minmax",          131, 1, 0, 0}; // Promoted to Vulkan 1.2 [new sampler parameter] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_sampler_filter_minmax
  deviceDeprecated.raw[a++]= {"VK_EXT_scalar_block_layout",            222, 1, 0, 0}; // Promoted to Vulkan 1.2 [modifies the alignment rules for uniforms/etc buffers] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_scalar_block_layout
  // 40
  deviceDeprecated.raw[a++]= {"VK_EXT_separate_stencil_usage",         247, 1, 0, 0}; // Promoted to Vulkan 1.2 [image creation flags for stencil/depth stencil] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_separate_stencil_usage
  deviceDeprecated.raw[a++]= {"VK_EXT_shader_viewport_index_layer",    163, 1, 0, 0}; // Promoted to Vulkan 1.2 [vars with Layer and ViewportIndex built-ins can be exported] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_shader_viewport_index_layer
  deviceDeprecated.raw[a++]= {"VK_AMD_gpu_shader_half_float",           37, 1, 0, 0}; // Deprecated by VK_KHR_shader_float16_int8 -> Promoted to Vulkan 1.2 [support for SPV_AMD_gpu_shader_half_float] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_gpu_shader_half_float
  deviceDeprecated.raw[a++]= {"VK_AMD_gpu_shader_int16",               133, 1, 0, 0}; // Deprecated by VK_KHR_shader_float16_int8 -> Promoted to Vulkan 1.2 [support for SPV_AMD_gpu_shader_int16] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_gpu_shader_int16
  deviceDeprecated.raw[a++]= {"VK_KHR_vulkan_memory_model",            212, 1, 0, 0}; // Promoted to Vulkan 1.2 [sync memory accessed by multiple shaders] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_vulkan_memory_model
  deviceDeprecated.raw[a++]= {"VK_KHR_depth_stencil_resolve",          200, 1, 0, 0}; // Promoted to 1.2 https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_depth_stencil_resolve
  deviceDeprecated.raw[a++]= {"VK_KHR_imageless_framebuffer",          109, 1, 0, 0}; // Promoted to 1.2 https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_imageless_framebuffer
  deviceDeprecated.raw[a++]= {"VK_KHR_separate_depth_stencil_layouts", 242, 1, 0, 0}; // Promoted to 1.2 https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_separate_depth_stencil_layouts
  deviceDeprecated.raw[a++]= {"VK_KHR_shader_float_controls",          198, 1, 0, 0}; // Promoted to 1.2 https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_shader_float_controls
  deviceDeprecated.raw[a++]= {"VK_KHR_shader_subgroup_extended_types", 176, 1, 0, 0}; // Promoted to 1.2 https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_shader_subgroup_extended_types
  // 50
  deviceDeprecated.raw[a++]= {"VK_KHR_spirv_1_4",                      237, 1, 0, 0}; // Promoted to 1.2 https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_spirv_1_4
  deviceDeprecated.raw[a++]= {"VK_KHR_uniform_buffer_standard_layout", 254, 1, 0, 0}; // Promoted to 1.2 https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_uniform_buffer_standard_layout
  deviceDeprecated.raw[a++]= {"VK_KHR_shader_float16_int8",             83, 1, 0, 0}; // Promoted to 1.2 https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap50.html#VK_KHR_shader_float16_int8
  deviceDeprecated.raw[a++]= { nullptr, 0, 0, 0, 0}; // terminator
  
  // NEW EXTENSIONS SHOULD BE ADDED AT THE BACK OF EACH LIST

  //{"", 000, 0/1, 0, 0}; // [dev/inst] [description] https://location

  //{nullptr, 0, 1, 0, 0}    // terminator, do not remove, must be last
}









