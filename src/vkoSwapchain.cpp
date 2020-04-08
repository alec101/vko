#include "../include/vkObject.h"



///=======================///
// SWAPCHAIN class / funcs //
///=======================///



VkoSwapchain::VkoSwapchain(vkObject *in_parent): cfg(this), _vko(in_parent) {
  
  swapchain= 0;

  images= nullptr;                        // INIT 1
  _formats= nullptr;                      // INIT 2
  swapInfo.pQueueFamilyIndices= nullptr;  // INIT 3
  _imgFormatInfo.pViewFormats= nullptr;   // INIT 4
  rebuildRequired= false;

  delData();
}


VkoSwapchain::~VkoSwapchain() {
  destroy();
  delData();
}


void VkoSwapchain::delData() {
  if(images)   { delete[] images;   images=   nullptr; } // MEM DEALLOC 1
  if(_formats) { delete[] _formats; _formats= nullptr; } // MEM DEALLOC 2
  if(swapInfo.pQueueFamilyIndices) { delete[] swapInfo.pQueueFamilyIndices; swapInfo.pQueueFamilyIndices= nullptr; } // MEM DEALLOC 3
  if(_imgFormatInfo.pViewFormats)  { delete[] _imgFormatInfo.pViewFormats;  _imgFormatInfo.pViewFormats=  nullptr; } // MEM DEALLOC 4

  // default values
  
  cfg.pNext.delData();

  queueFamily= (_vko->queue? _vko->queue[0].family: 0);
  nrImages= 0;
  currentIndex= ~0U;
  dx= dy= 0;

  swapInfo.sType= VK_STRUCTURE_TYPE_SWAPCHAIN_CREATE_INFO_KHR;
  swapInfo.pNext= nullptr;
  swapInfo.flags= 0;
  
  swapInfo.surface= 0;
  swapInfo.minImageCount= 2;    // default: 2 buffers to swap between
  swapInfo.imageFormat= VK_FORMAT_B8G8R8A8_UNORM;
  swapInfo.imageColorSpace= VK_COLOR_SPACE_SRGB_NONLINEAR_KHR;
  
  // imageExtent is the size (in pixels) of the swapchain image(s). The behavior is platform-dependent if the image extent
  //   does not match the surface’s currentExtent as returned by vkGetPhysicalDeviceSurfaceCapabilitiesKHR.
  // Note:
  //  On some platforms, it is normal that maxImageExtent may become (0, 0), for example when the window is minimized.
  //  In such a case, it is not possible to create a swapchain due to the Valid Usage requirements.
  swapInfo.imageExtent.width= 0;     // taken from surface if left 0
  swapInfo.imageExtent.height= 0;    // taken from surface if left 0
  swapInfo.imageArrayLayers= 1;      // imageArrayLayers is the number of views in a multiview/stereo surface. For non-stereoscopic-3D applications, this value is 1.
  swapInfo.imageUsage=       VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT;
  swapInfo.imageSharingMode= VK_SHARING_MODE_EXCLUSIVE;              // only one queue family will share this swapchain (VK_SHARING_MODE_CONCURRENT will be set if shared between multiple queue families)
  swapInfo.preTransform=     VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR;
  swapInfo.compositeAlpha=   VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR;
  swapInfo.presentMode=      VK_PRESENT_MODE_FIFO_KHR;               // vsync on; mailbox and another buffer can use triple buffering; imediate is vsync off, there's more modes.
  swapInfo.clipped= false;
  swapInfo.queueFamilyIndexCount= 0;

  _deviceGroupInfo.sType= VK_STRUCTURE_TYPE_DEVICE_GROUP_SWAPCHAIN_CREATE_INFO_KHR;
  _deviceGroupInfo.pNext= nullptr;
  _deviceGroupInfo.modes= 0;
  
  _imgFormatInfo.sType= VK_STRUCTURE_TYPE_IMAGE_FORMAT_LIST_CREATE_INFO_KHR;
  _imgFormatInfo.pNext= nullptr;
  _imgFormatInfo.viewFormatCount= 0;

  /// present info struct
  _presentInfo.sType= VK_STRUCTURE_TYPE_PRESENT_INFO_KHR;
  _presentInfo.pNext= nullptr;
  _presentInfo.waitSemaphoreCount= 1;
  _presentInfo.swapchainCount= 1;
  
  _oldSwapchain= 0;

  _nformats= 0;
  cfg._customSize.height= cfg._customSize.width= 0;
}


void VkoSwapchain::destroy() {
  if(swapchain) {
    if(_vko->device) 
      _vko->DestroySwapchainKHR(*_vko, swapchain, *_vko);
    swapchain= 0;
  }

  rebuildRequired= false;

  currentIndex= ~0;
  dx= dy= 0;
}




// configuration funcs

void VkoSwapchain::Config::setSurface(VkSurfaceKHR in_surface) {
  parent->swapInfo.surface= in_surface;
  parent->_populateFormats();
  parent->_vko->GetPhysicalDeviceSurfaceCapabilitiesKHR(*parent->_vko, parent->swapInfo.surface, &parent->surfaceCfg);
}


void VkoSwapchain::Config::addShareBetwenQueueFamily(uint32_t in_family) {
  uint32_t *old= (uint32_t *)parent->swapInfo.pQueueFamilyIndices;

  parent->swapInfo.imageSharingMode= VK_SHARING_MODE_CONCURRENT;     // set the image share mode to concurrent
  parent->swapInfo.queueFamilyIndexCount++;
  parent->swapInfo.pQueueFamilyIndices= new uint32_t[parent->swapInfo.queueFamilyIndexCount];

  /// copy old data
  for(uint32_t a= 0; a< parent->swapInfo.queueFamilyIndexCount- 1; a++)
    ((uint32_t *)parent->swapInfo.pQueueFamilyIndices)[a]= old[a];

  if(old) delete[] old;
}


void VkoSwapchain::Config::addMultipleFormat(VkFormat in_f) {
  VkFormat *old= (VkFormat *)parent->_imgFormatInfo.pViewFormats;

  parent->_imgFormatInfo.viewFormatCount++;
  parent->_imgFormatInfo.pViewFormats= new VkFormat[parent->_imgFormatInfo.viewFormatCount];

  /// copy old data
  for(uint32_t a= 0; a< parent->_imgFormatInfo.viewFormatCount- 1; a++)
    ((VkFormat *)parent->_imgFormatInfo.pViewFormats)[a]= old[a];

  if(old) delete[] old;
}


/// surface's possible formats
void VkoSwapchain::_populateFormats() {
  if(_formats) { delete[] _formats; _formats= nullptr; }
  _nformats= 0;

  if(swapInfo.surface) {
    _vko->GetPhysicalDeviceSurfaceFormatsKHR(*_vko, swapInfo.surface, &_nformats, nullptr);
    if(_nformats) {
      _formats= new VkSurfaceFormatKHR[_nformats];
      _vko->GetPhysicalDeviceSurfaceFormatsKHR(*_vko, swapInfo.surface, &_nformats, _formats);
    }
  }
}

/// check format against surface's possible formats
bool VkoSwapchain::_isFormatOk(VkFormat in_f, VkColorSpaceKHR in_c) {
  for(uint32_t a= 0; a< _nformats; a++)
    if((_formats[a].format== in_f) && (_formats[a].colorSpace== in_c))
      return true;

  return false;
}


// SWAPCHAIN build --------------- //

bool VkoSwapchain::build() {
  // intel tutorial https://software.intel.com/en-us/articles/api-without-secrets-introduction-to-vulkan-part-2
  // tutorial 2 https://vulkan-tutorial.com/Drawing_a_triangle/Presentation/Swap_chain

  /* research:

  vkAcquireNextImageKHR - start drawing on it. MUST use a semaphore here

  -if vkAcquireNextImageKHR returns  VK_SUBOPTIMAL_KHR if the window resized. At this point the swapchain should be re-created.
      using the oldswapchain in the createinfo would help things i am sure, for this case

  -if vkAcquireNextImageKHR returns VK_ERROR_OUT_OF_DATE_KHR - the swapchain must be recreated. the window propreties changed or watever.

  vkQueuePresentKHR - show the image. _Releases_ the aquisition of the image.

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
  VkBool32 supported= VK_FALSE;
  const void **_pNext= nullptr;

  /// surface checks / capabilities
  if(swapInfo.surface== 0) {
    _vko->errorText= __FUNCTION__": No VkSurfaceKHR specified. Aborting."; goto Exit; }

  _vko->GetPhysicalDeviceSurfaceSupportKHR(*_vko, queueFamily, swapInfo.surface, &supported);
  if(supported== false) {
    _vko->errorText= __FUNCTION__": Swapchain: Surface not supported on configured queue family"; goto Exit; }

  if(_vko->GetPhysicalDeviceSurfaceCapabilitiesKHR(*_vko, swapInfo.surface, &surfaceCfg)!= VK_SUCCESS) {
    _vko->errorText= __FUNCTION__": Swapchain: Could not get capabilities. Aborting."; goto Exit; }

  if(!_isFormatOk(swapInfo.imageFormat, swapInfo.imageColorSpace)) {
    _vko->errorText= __FUNCTION__": Requested format is not avaible for this surface"; goto Exit; }  

  // check to see if window is minimized 
  if((!surfaceCfg.currentExtent.height) || (!surfaceCfg.currentExtent.width))
    goto Exit;

  // pNext handling
    swapInfo.pNext= nullptr;
  

  _pNext= &swapInfo.pNext;

  /// device group https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkDeviceGroupSwapchainCreateInfoKHR
  if(_deviceGroupInfo.modes) {
    *_pNext= &_deviceGroupInfo;
    _deviceGroupInfo.pNext= nullptr;
    _pNext= &_deviceGroupInfo.pNext;
  }

  /// multiple image formats https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkImageFormatListCreateInfoKHR
  if(_imgFormatInfo.viewFormatCount) {
    *_pNext= &_imgFormatInfo;
    _imgFormatInfo.pNext= nullptr;
    _pNext= &_imgFormatInfo.pNext;
  }

  *_pNext= cfg.pNext.VkSwapchainCreateInfoKHR;  // last pNext in chain is the custom one

  /// image size
  if(cfg._customSize.width && cfg._customSize.height)         // custom size
    swapInfo.imageExtent= cfg._customSize;
  else
    swapInfo.imageExtent= surfaceCfg.currentExtent;

  dx= swapInfo.imageExtent.width, dy= swapInfo.imageExtent.height;

  /// old swapchain is saved on check()
  swapInfo.oldSwapchain= _oldSwapchain;
  
  if(!_vko->errorCheck(_vko->CreateSwapchainKHR(*_vko, &swapInfo, *_vko, &swapchain),
    __FUNCTION__": Swapchain create fail."))
    goto Exit;

  _populateImages();

  /// presentInfo, the struct that is used for presenting images
  _presentInfo.pNext= cfg.pNext.VkPresentInfoKHR;
  _presentInfo.pSwapchains= &swapchain;
  
  // success
  ret= true;

Exit:
  if(ret== false && swapchain!= 0) destroy();
  if(_oldSwapchain) {
    _vko->DestroySwapchainKHR(*_vko, _oldSwapchain, *_vko);
    _oldSwapchain= 0;
  }

  return ret;
}


void VkoSwapchain::_populateImages() {
  // populate images / nrImages
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#vkGetSwapchainImagesKHR
  uint32_t n;
  _vko->GetSwapchainImagesKHR(*_vko, swapchain, &n, nullptr);

  /// resize array only if neccesary
  if(n!= nrImages) {
    nrImages= n;
    if(images) { delete[] images; images= nullptr; }
    if(nrImages)
      images= new VkImage[nrImages];
  }
  
  /// populate
  if(nrImages)
    _vko->GetSwapchainImagesKHR(*_vko, swapchain, &nrImages, images);
}


bool VkoSwapchain::rebuild() {
  _oldSwapchain= swapchain;
  swapchain= NULL;
  dx= dy= 0;
  currentIndex= ~0;
  return build();
}





// 
bool VkoSwapchain::aquire(VkSemaphore in_finishPresenting, VkFence in_finishPresentingFence, uint64_t in_timeout, uint32_t *out_index) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkAcquireNextImageInfoKHR
  /*
  VK_SUCCESS        =is returned if an image became available.
  VK_ERROR_SURFACE_LOST_KHR =if the surface becomes no longer available.
  VK_NOT_READY      =is returned if timeout is zero and no image was available.
  VK_TIMEOUT        =is returned if timeout is greater than zero and less than UINT64_MAX, and no image became available within the time allowed.
  VK_SUBOPTIMAL_KHR =is returned if an image became available, and the swapchain no longer matches the surface properties exactly, but can still be used to present to the surface successfully.
  VK_ERROR_OUT_OF_DATE_KHR happened <<<<<<<<<<<<<<<<<
  */

  if(!swapchain) { currentIndex= ~0; if(out_index) *out_index= currentIndex; return false; }

  #ifdef VKO_BE_CHATTY
  bool chatty= true;      // DEBUG
  #endif

  bool ret= true;
  
  VkResult res= _vko->AcquireNextImageKHR(*_vko, swapchain, in_timeout, in_finishPresenting, in_finishPresentingFence, &currentIndex);

  if(res!= VK_SUCCESS) {
    if((res== VK_SUBOPTIMAL_KHR) || (res== VK_ERROR_OUT_OF_DATE_KHR)) {
      _vko->DeviceWaitIdle(*_vko);
      
      if(rebuild()) {
        #ifdef VKO_BE_CHATTY
        if(chatty) printf("WARNING: Vulkan surface rebuilt due %s\n", (res== VK_SUBOPTIMAL_KHR? "VK_SUBOPTIMAL_KHR": "VK_ERROR_OUT_OF_DATE_KHR")); // DEBUG
        #endif

        if(_vko->AcquireNextImageKHR(*_vko, swapchain, in_timeout, in_finishPresenting, in_finishPresentingFence, &currentIndex)!= VK_SUCCESS)
          currentIndex= ~0, ret= false;
      }
    } else 
      currentIndex= ~0, ret= false;
  }

  if(out_index) *out_index= currentIndex;
  return ret;
}




void VkoSwapchain::queueShow(uint32_t in_surfaceIndex, VkQueue in_queue, VkSemaphore in_finishDrawing) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkPresentInfoKHR
  
  _presentInfo.pWaitSemaphores= &in_finishDrawing, _presentInfo.pImageIndices= &in_surfaceIndex;

  VkResult res= _vko->QueuePresentKHR(in_queue, &_presentInfo);

  rebuildRequired= (res== VK_SUCCESS? false: true);
};










