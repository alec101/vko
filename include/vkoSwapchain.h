#pragma once


///================--------------------------///
// swapchain class ========================== //
///================--------------------------///



class VkoSwapchain: public chainData {
public:
  // VK_CHR_swapchain extension https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap40.html#VK_KHR_swapchain

  VkSwapchainKHR swapchain; // [init:null] vulkan object - gets populated when build() is called
  inline operator VkSwapchainKHR() const { return swapchain; }

  uint32_t queueFamily;       // main queue family this swapchain will work with
  uint32_t nrImages;          // [init:0] number of images (buffers). Gets populated after calling build() func
  VkImage *images;            // [init:null] array with all images (buffers). Gets populated after calling build() func
  uint32_t currentIndex;      // after calling aquire(), this will hold the index of the image currently aquired and can be drawn upon
  uint32_t dx, dy;            // swapchain's current dimensions, populated after it is built/rebuilt or checked the status

  bool rebuildRequired;

  VkSwapchainCreateInfoKHR swapInfo;      // struct used with build(), contains all settings
  VkSurfaceCapabilitiesKHR surfaceCfg;    // populated after the surface is set / on build()
  //void populateSurfaceCfg();

  // all configuration vars / funcs:
  struct Config {
    
    // [def:0, 0] set a preffered size; if left zero, the whole surface's size is used
    void setCustomSize(uint32_t in_dx, uint32_t in_dy) { _customSize.width= in_dx, _customSize.height= in_dy; }

    // [def:0 / vkObject::queue[0] ] MUST specify a main queue family this swapchain will work with
    void setQueueFamily(uint32_t in_q) { parent->queueFamily= in_q; }

    // [def:null] MUST specify a surface to use.
    void setSurface(VkSurfaceKHR in_s);

    // [def:0] surface create flags https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkSwapchainCreateFlagBitsKHR
    void setFlags(VkSwapchainCreateFlagsKHR in_f) { parent->swapInfo.flags= in_f; }

    // [def:2] number of images (buffers) to create for the swapchain
    void setMinImageCount(uint32_t in_n)          { parent->swapInfo.minImageCount= in_n; }

    // [def:VK_FORMAT_B8G8R8A8_UNORM] the image format the buffers will be created with
    void setImageFormat(VkFormat in_f)            { parent->swapInfo.imageFormat= in_f; }

    // [def:VK_COLOR_SPACE_SRGB_NONLINEAR_KHR] - this is weird, cuz there's only one option here, and you can't even make it undefined
    void setImageColorSpace(VkColorSpaceKHR in_c) { parent->swapInfo.imageColorSpace= in_c; }

    // [def:0] if left 0, image size will be taken from the surface. Optionally you can specify the image buffers size in here(window size)
    void setImageSize(uint32_t dx, uint32_t dy)   { parent->swapInfo.imageExtent.width= dx, parent->swapInfo.imageExtent.height= dy; }

    // [def:1] imageArrayLayers is the number of views in a multiview/stereo surface. For non-stereoscopic-3D applications, this value is 1.
    void setImageArrayLayers(uint32_t in_n)       { parent->swapInfo.imageArrayLayers= in_n; }

    // [def: VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT] specify aditional image buffers usage. Color att should be enough for a swapchain.
    // If the buffers will be used for something else, in shaders/etc, it must be specified here.
    void setImageUsage(VkImageUsageFlags in_u)    { parent->swapInfo.imageUsage= in_u; }

    // this func will turn VK_SHARING_MODE_CONCURRENT on, for VkSharingMode
    // else, the sharing more will be VK_SHARING_MODE_EXCLUSIVE
    void addShareBetwenQueueFamily(uint32_t familyIndex);

    // [def:VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR] identity means unchanged; you can rotate and do other transforms to the images
    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkSurfaceTransformFlagBitsKHR
    void setSurfaceTransformFlags(VkSurfaceTransformFlagBitsKHR in_f) { parent->swapInfo.preTransform= in_f; }

     // [def:VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR opaque]  https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkCompositeAlphaFlagBitsKHR
    void setCompositeAlphaFlags(VkCompositeAlphaFlagBitsKHR in_f)     { parent->swapInfo.compositeAlpha= in_f; }

    // [def:VK_PRESENT_MODE_FIFO_KHR vsync on] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkPresentModeKHR
    // VK_PRESENT_MODE_IMMEDIATE_KHR - no waiting, tearing (no vsync)
    // VK_PRESENT_MODE_MAILBOX_KHR - with another buffer you can make triple buffering - i think it's more demanding
    // VK_PRESENT_MODE_FIFO_KHR - wait for vsync, aquire actually waits, so it's relaxed on the fps also
    // VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR- continuously draws an image, without the need to call any func. uses vsync.
    void setPresentMode(VkPresentModeKHR in_p) { parent->swapInfo.presentMode= in_p; }

    // [def:false]
    // if set to true, pixels that have other windows over them, for example, will have undefined contents, vulkan will not render to them
    // BUT, if you intend to read from such pixels, with shaders or after aquiring the image, you should put this to false;
    // on true, things will work faster, if parts of the view is obstructed

    // Applications should set this value to VK_TRUE if they do not expect to read back the content of presentable images
    //  before presenting them or after reacquiring them, and if their pixel shaders do not have any side effects
    //  that require them to run for all pixels in the presentable image.
    void setClipped(VkBool32 clipped) { parent->swapInfo.clipped= clipped; }

    // [def:0] add device group info here if needed https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkDeviceGroupPresentModeFlagBitsKHR
    void setDeviceGroupPresentModeFlags(VkDeviceGroupPresentModeFlagsKHR in_f) { parent->_deviceGroupInfo.modes= in_f; }

    // if the swapchain should support multiple image formats, use this func multiple times to add them all
    void addMultipleFormat(VkFormat in_format);

    struct PNext {
      void *VkSwapchainCreateInfoKHR;
      void *VkPresentInfoKHR;
      void delData() { VkSwapchainCreateInfoKHR= VkPresentInfoKHR= nullptr; }
    } pNext;

  private:
    Config(VkoSwapchain *in_parent): parent(in_parent) {}

    VkExtent2D _customSize;    // user-specified size
    //uint32_t _customDx, _customDy;
    VkoSwapchain *parent;
    //chainList _multipleFormats;
    //chainList _sharedQueues;        // [_Share chainData] shared between these queue families
    
    friend class VkoSwapchain;
  } cfg; // all swapchain's settings


  // after all parameters are set, call this func to create the vulkan swapchain
  bool build();     // returns true if successful. WARNING: A swapchain cannot be built on a minimized window (from specs, not tested)
  bool rebuild();
  void destroy();

  bool aquire(VkSemaphore in_finishPresenting, VkFence in_finishPresentingFence= 0, uint64_t timeout= ~0, uint32_t *out_index= nullptr);     //
  void queueShow(uint32_t in_surfaceIndex, VkQueue in_queue, VkSemaphore in_finishDrawing);   // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkPresentInfoKHR
  inline void queueShowCurrent(VkQueue in_queue, VkSemaphore in_finishDrawing) { queueShow(currentIndex, in_queue, in_finishDrawing); }

    

  VkoSwapchain(vkObject *in_parent);
  ~VkoSwapchain();
  void delData();

private:
  VkPresentInfoKHR _presentInfo;
  VkSwapchainKHR _oldSwapchain;


  /// build structs
  
  VkDeviceGroupSwapchainCreateInfoKHR _deviceGroupInfo; // in pNext of _swapInfo
  VkImageFormatListCreateInfoKHR _imgFormatInfo;  // in pNext of _swapInfo

  /// surface's accepted formats
  void _populateFormats();
  uint32_t _nformats;
  VkSurfaceFormatKHR *_formats;
  bool _isFormatOk(VkFormat in_format, VkColorSpaceKHR in_colorSpace);

  void _populateImages();

  //uint32_t _index;    // index of the image currently being drawn by the app
  //class _Share:  public chainData { public: uint32_t queueFamilyIndex; };
  //class _Format: public chainData { public: VkFormat format; };

  vkObject *_vko;
  friend class vkObject;
  friend struct Config;
}; /// Swapchain class









