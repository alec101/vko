#include "vkObject.h"



///=======================///
// SWAPCHAIN class / funcs //
///=======================///



VkoSwapchain::VkoSwapchain() {
  _parent= null;
  _index= 0;

  swapchain= null;

  nrImages= 0;
  images= null;         // MEM INIT
  //semaphore= null;

  currentIndex= ~0U;
  dx= dy= 0;

  cfg.flags= 0;
  cfg.surface= null;
  cfg.minBuffers= 2;    // default: 2 buffers to swap between
  cfg.imageFormat= VK_FORMAT_B8G8R8A8_UNORM;
  cfg.colorSpace= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  
  // imageExtent is the size (in pixels) of the swapchain image(s). The behavior is platform-dependent if the image extent
  //   does not match the surface’s currentExtent as returned by vkGetPhysicalDeviceSurfaceCapabilitiesKHR.
  // Note:
  //  On some platforms, it is normal that maxImageExtent may become (0, 0), for example when the window is minimized.
  //  In such a case, it is not possible to create a swapchain due to the Valid Usage requirements.
  
  cfg.imageSize.width=  0, cfg.imageSize.height= 0; // taken from surface if left 0
  cfg.imageArrayLayers= 1;  // imageArrayLayers is the number of views in a multiview/stereo surface. For non-stereoscopic-3D applications, this value is 1.
  cfg.imageUsage=       VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  cfg.imageSharingMode= VK_SHARING_MODE_EXCLUSIVE;  // only one queue family will share this swapchain (VK_SHARING_MODE_CONCURRENT will be set if shared between multiple queue families)
  cfg.preTransform=     VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  cfg.compositeAlpha=   VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  cfg.presentMode=      VK_PRESENT_MODE_FIFO_KHR;   // vsync on; mailbox and another buffer can use triple buffering; imediate is vsync off, there's more modes.
  cfg.clipped= false;
  cfg.deviceGroupFlags= 0;

  /// present info struct
  _showInfo.sType= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  _showInfo.pNext= null;
  _showInfo.waitSemaphoreCount= 1;
  _showInfo.swapchainCount= 1;

  _oldSwapchain= null;

  _nformats= 0;
  _formats= null;
}


VkoSwapchain::~VkoSwapchain() {
  if(images) delete[] images; // MEM DEALLOC 1
  if(_formats) delete[] _formats;
}


void VkoSwapchain::destroy() {
  if((swapchain!= null) && (_parent->device!= null) && (_parent->vk->DestroySwapchainKHR))
    _parent->vk->DestroySwapchainKHR(_parent->device, swapchain, _parent->memCallback);

  swapchain= null;
  if(images!= null) { delete[] images; images= null; } // MEM DEALLOC 1
  nrImages= 0;
  currentIndex= ~0;
  dx= dy= 0;
}


void VkoSwapchain::SwapchainSettings::addShareBetwenQueueFamily(uint32 in_family) {
  _Share *p= new _Share;
  if(p== null) { error.alloc(__FUNCTION__); return; }
  p->queueFamilyIndex= in_family;
  _sharedQueues.add(p);
  
  imageSharingMode= VK_SHARING_MODE_CONCURRENT;     // set the image share mode to concurrent
}


void VkoSwapchain::SwapchainSettings::addMultipleFormat(VkFormat in_f) {
  _Format *p= new _Format;
  if(p== null) { error.alloc(__FUNCTION__); return; }
  p->format= in_f;
  _multipleFormats.add(p);
}



bool VkoSwapchain::_isFormatOk(VkSurfaceKHR in_s, VkFormat in_f, VkColorSpaceKHR in_c) {
  /// populate (only once)
  if(_formats== null) {
    vk.GetPhysicalDeviceSurfaceFormatsKHR(_parent->vkr->vkGPU, in_s, &_nformats, null);
    if(_nformats) {
      _formats= new VkSurfaceFormatKHR[_nformats];
      vk.GetPhysicalDeviceSurfaceFormatsKHR(_parent->vkr->vkGPU, in_s, &_nformats, _formats);
    }
  }

  for(uint a= 0; a< _nformats; a++)
    if((_formats[a].format== in_f) && (_formats[a].colorSpace== in_c))
      return true;

  return false;
}




// SWAPCHAIN build --------------- //

bool VkoSwapchain::build() {
  // intel tutorial https://software.intel.com/en-us/articles/api-without-secrets-introduction-to-vulkan-part-2
  // tutorial 2 https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain

  /* research:

  vkAcquireNextImageKHR - start drawing on it (IT SEEMS). MUST use a semaphore here

  -if vkAcquireNextImageKHR returns  VK_SUBOPTIMAL_KHR if the window resized. At this point the swapchain should be re-created.
      using the oldswapchain in the createinfo would help things i am sure, for this case

  -if vkAcquireNextImageKHR returns VK_ERROR_OUT_OF_DATE_KHR - the swapchain must be recreated. the window propreties changed or watever.

  vkQueuePresentKHR - show the image (IT SEEMS). _Releases_ the aquisition of the image.

  V-Sync :
  "To avoid tearing, an application should coordinate access with the presentation engine.
  This requires presentation engine timing information through platform-specific mechanisms
  and ensuring that color attachment writes are made available during the portion
  of the presentation engine’s refresh cycle they are intended for."
  */

  // swapchain - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#_wsi_swapchain
  // createinfo - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkSwapchainCreateInfoKHR
  
  destroy();
  
  bool ret= false;                            /// return value
  uint a;
  VkBool32 supported;
  VkSwapchainCreateInfoKHR swapInfo;
  VkDeviceGroupSwapchainCreateInfoKHR deviceGroupInfo;
  VkImageFormatListCreateInfoKHR imageFormatListInfo;
  VkSurfaceCapabilitiesKHR surfaceCfg;
  //VkSemaphoreCreateInfo semaphoreInfo;

  imageFormatListInfo.pViewFormats= null;     // INIT 1
  swapInfo.pQueueFamilyIndices= null;         // INIT 2

  swapInfo.sType= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  
  swapInfo.pNext= null;
  const void **pNext= &swapInfo.pNext;

  /// device group
  if(cfg.deviceGroupFlags!= 0) {
    *pNext= &deviceGroupInfo;
    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkDeviceGroupSwapchainCreateInfoKHR
    deviceGroupInfo.sType= VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR;
    deviceGroupInfo.pNext= null;
    deviceGroupInfo.modes= cfg.deviceGroupFlags;
    pNext= &deviceGroupInfo.pNext;
  }

  /// multiple image formats
  if(cfg._multipleFormats.nrNodes> 0) {
    *pNext= &imageFormatListInfo;
    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkImageFormatListCreateInfoKHR
    imageFormatListInfo.sType= VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR;
    imageFormatListInfo.pNext= null;
    imageFormatListInfo.pViewFormats= new VkFormat[cfg._multipleFormats.nrNodes]; // ALLOC 1
    if(imageFormatListInfo.pViewFormats== null) { error.alloc(__FUNCTION__); goto Exit; }
    a= 0;
    for(_Format *p= (_Format *)cfg._multipleFormats.first; p; p= (_Format *)p->next, a++)
      ((VkFormat *)imageFormatListInfo.pViewFormats)[a]= p->format;

    pNext= &imageFormatListInfo.pNext;
  }
  
  /// surface
  if(cfg.surface!= null)
    swapInfo.surface= cfg.surface;
  else
    swapInfo.surface= (VkSurfaceKHR)_parent->vkr->monitor->win->vkSurface;

  vk.GetPhysicalDeviceSurfaceSupportKHR(_parent->vkr->vkGPU, _parent->vkr->vkQueues[0].family, swapInfo.surface, &supported);
  if(supported== false) { error.detail("Swapchain: Surface not supported", __FUNCTION__); goto Exit; }

  if(swapInfo.surface== null) { error.detail("No VkSurfaceKHR specified, or present on current osiWindow. Aborting.", __FUNCTION__); goto Exit; }
  
  /// image size
  if(cfg.imageSize.height && cfg.imageSize.width) {
    swapInfo.imageExtent= cfg.imageSize;
    dx= cfg.imageSize.width;
    dy= cfg.imageSize.height;
  } else {
    _parent->vk->GetPhysicalDeviceSurfaceCapabilitiesKHR((VkPhysicalDevice)_parent->vkr->GPU->vkGPU, swapInfo.surface, &surfaceCfg);
    swapInfo.imageExtent= surfaceCfg.currentExtent;
    dx= surfaceCfg.currentExtent.width;
    dy= surfaceCfg.currentExtent.height;
  }

  swapInfo.flags= cfg.flags;
  swapInfo.minImageCount=         cfg.minBuffers;
  swapInfo.imageFormat=           cfg.imageFormat;
  swapInfo.imageColorSpace=       cfg.colorSpace;
  if(!_isFormatOk(swapInfo.surface, swapInfo.imageFormat, swapInfo.imageColorSpace)) { error.detail("Requested format is not avaible for this surface", __FUNCTION__); goto Exit; }

  swapInfo.imageArrayLayers=      cfg.imageArrayLayers;
  swapInfo.imageUsage=            cfg.imageUsage;
  swapInfo.imageSharingMode=      cfg.imageSharingMode;
  swapInfo.queueFamilyIndexCount= cfg._sharedQueues.nrNodes;
  if(cfg._sharedQueues.nrNodes> 0) {
    swapInfo.pQueueFamilyIndices= new uint32[cfg._sharedQueues.nrNodes];    // ALLOC 2
    if(swapInfo.pQueueFamilyIndices== null) { error.alloc(__FUNCTION__); goto Exit; }
    a= 0;
    for(_Share *p= (_Share *)cfg._sharedQueues.first; p; p= (_Share *)p->next, a++)
      ((uint32 *)swapInfo.pQueueFamilyIndices)[a]= p->queueFamilyIndex;
  }
  swapInfo.preTransform=   cfg.preTransform;
  swapInfo.compositeAlpha= cfg.compositeAlpha;
  swapInfo.presentMode=    cfg.presentMode;
  swapInfo.clipped=        cfg.clipped;
  swapInfo.oldSwapchain= _oldSwapchain;
  
  VkResult res= _parent->vk->CreateSwapchainKHR(_parent->device, &swapInfo, _parent->memCallback, &swapchain);
  if(res!= VK_SUCCESS) {
    error.detail("Swapchain create fail.", __FUNCTION__);
    error.vkPrint(res);
    goto Exit;
  }

  // populate images / nrImages
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#vkGetSwapchainImagesKHR
  _parent->vk->GetSwapchainImagesKHR(_parent->device, swapchain, &nrImages, null);
  if(nrImages) {
    if(images) delete[] images; images= null;
    images= new VkImage[nrImages];
    if(images== null) { error.alloc(__FUNCTION__, __LINE__); goto Exit; }
    _parent->vk->GetSwapchainImagesKHR(_parent->device, swapchain, &nrImages, images);
  }

  /// showInfo, the struct that is used for presenting images
  _showInfo.pSwapchains= &swapchain;
  
  // success
  ret= true;

Exit:
  if(ret== false && swapchain!= null) destroy();
  if(imageFormatListInfo.pViewFormats) delete[] imageFormatListInfo.pViewFormats; // DEALLOC 1
  if(swapInfo.pQueueFamilyIndices) delete[]  swapInfo.pQueueFamilyIndices;        // DEALLOC 2
  if(_oldSwapchain) {
    _parent->vk->DestroySwapchainKHR(_parent->device, _oldSwapchain, _parent->memCallback);
    _oldSwapchain= null;
  }

  return ret;
}


bool VkoSwapchain::rebuild() {
  _oldSwapchain= swapchain;
  swapchain= null;
  dx= dy= 0;
  currentIndex= ~0;
  return build();
}






bool VkoSwapchain::check() {
  // VK_SUCCESS                 = ok
  // VK_SUBOPTIMAL_KHR          = no longer matches the surface size, it still functions, but RECREATE is needed
  // VK_ERROR_OUT_OF_DATE_KHR   = the surface has changed in such a way that it is no longer compatible with the swapchain. No longer functions at all.
  // VK_ERROR_SURFACE_LOST_KHR  = the surface is no longer available.

  // VK_ERROR_OUT_OF_HOST_MEMORY
  // VK_ERROR_OUT_OF_DEVICE_MEMORY
  // VK_ERROR_DEVICE_LOST

  // CHOOSEN THE FAST WAY, ONLY TRUE AND FALSE. SUBJECT TO CHANGE

  VkResult r= _parent->vk->GetSwapchainStatusKHR(_parent->device, swapchain);
  if(r== VK_SUCCESS) return true;
  else return false;
}





// 
bool VkoSwapchain::aquire(VkSemaphore in_finishPresenting, VkFence in_finishPresentingFence, uint64 in_timeout, uint32 *out_index) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkAcquireNextImageInfoKHR
  /*
  VK_SUCCESS        =is returned if an image became available.
  VK_ERROR_SURFACE_LOST_KHR =if the surface becomes no longer available.
  VK_NOT_READY      =is returned if timeout is zero and no image was available.
  VK_TIMEOUT        =is returned if timeout is greater than zero and less than UINT64_MAX, and no image became available within the time allowed.
  VK_SUBOPTIMAL_KHR =is returned if an image became available, and the swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully.
  VK_ERROR_OUT_OF_DATE_KHR happened <<<<<<<<<<<<<<<<<
  */

  // IMAGE BARIERS
  // Setting the old layout to VK_IMAGE_LAYOUT_UNDEFINED implies that the contents of the image subresource need not be preserved.
  //  Implementations may use this information to avoid performing expensive data transition operations.
  //  (AFTER PRESENTING, YOU DON'T CARE ABOUT THE IMAGE ANYMORE)


  bool chatty= true;      // DEBUG
  bool ret= true;

  VkResult res= _parent->vk->AcquireNextImageKHR(_parent->device, swapchain, in_timeout, in_finishPresenting, in_finishPresentingFence, &currentIndex);
  if(res!= VK_SUCCESS) {
    if(res== VK_SUBOPTIMAL_KHR) {
      if(rebuild()) {
        if(chatty) error.simple("WARNING: Vulkan surface rebuilt due VK_SUBOPTIMAL_KHR"); // DEBUG
        if(_parent->vk->AcquireNextImageKHR(_parent->device, swapchain, in_timeout, in_finishPresenting, in_finishPresentingFence, &currentIndex)!= VK_SUCCESS)
          currentIndex= ~0, ret= false;
      }
    } else if(res== VK_ERROR_OUT_OF_DATE_KHR) {
      if(rebuild()) {
        if(chatty) error.simple("WARNING: Vulkan surface rebuilt due VK_ERROR_OUT_OF_DATE_KHR");
        if(_parent->vk->AcquireNextImageKHR(_parent->device, swapchain, in_timeout, in_finishPresenting, in_finishPresentingFence, &currentIndex)!= VK_SUCCESS)
          currentIndex= ~0, ret= false;
      }
    } else 
      currentIndex= ~0, ret= false;
  }

  if(out_index) *out_index= currentIndex;
  return ret;
}














