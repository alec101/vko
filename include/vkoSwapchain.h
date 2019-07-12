#pragma once


///================--------------------------///
// swapchain class ========================== //
///================--------------------------///



class VkoSwapchain: public chainData {
public:
  // VK_CHR_swapchain extension https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap40.html#VK_KHR_swapchain

  VkSwapchainKHR swapchain; // [init:null] vulkan object - gets populated when build() is called
  inline operator VkSwapchainKHR() const { return swapchain; }

  uint32_t nrImages;          // [init:0] number of images (buffers). Gets populated after calling build() func
  VkImage *images;          // [init:null] array with all images (buffers). Gets populated after calling build() func
  uint32_t currentIndex;      // after calling aquire(), this will hold the index of the image currently aquired and can be drawn upon
  uint32_t dx, dy;            // swapchain's dimensions, after it is built

  // all configuration vars / funcs:
  struct SwapchainSettings {
    //uint32_t nrSemaphorePairs;
    //uint32_t nrFencePairs;


    VkSwapchainCreateFlagsKHR flags;  // [def:0] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkSwapchainCreateFlagBitsKHR
    VkSurfaceKHR surface;             // [def:null] MUST specify a surface to use.
    uint32_t minBuffers;                // [def:2] number of images (buffers) to create for the swapchain
    VkFormat imageFormat;             // [def:VK_FORMAT_B8G8R8A8_UNORM] the image format the buffers will be created with
    VkColorSpaceKHR colorSpace;       // [def:VK_COLOR_SPACE_SRGB_NONLINEAR_KHR] - this is weird, cuz there's only one option here, and you can't even make it undefined
    VkExtent2D imageSize;             // [def:0] if left 0, image size will be taken from the surface. Optionally you can specify the image buffers size in here(window size)
    uint32_t imageArrayLayers;        // [def:1] imageArrayLayers is the number of views in a multiview/stereo surface. For non-stereoscopic-3D applications, this value is 1.
    VkImageUsageFlags imageUsage;     // [def: VK_IMAGE_USAGE_COLOR_ATTACHMENT_BIT] specify aditional image buffers usage. Color att should be enough for a swapchain. If the buffers will be used for something else, in shaders/etc, it must be specified here tho.

    // this func will turn VK_SHARING_MODE_CONCURRENT on, for VkSharingMode
    // else, the sharing more will be VK_SHARING_MODE_EXCLUSIVE
    void addShareBetwenQueueFamily(uint32_t familyIndex);
    VkSharingMode imageSharingMode; // [def: VK_SHARING_MODE_EXCLUSIVE]; call addShareBetwenQueueFamily() multiple times to activate VK_SHARING_MODE_CONCURRENT, and set what queue families will use this swapchain

    VkSurfaceTransformFlagBitsKHR preTransform; // [def:VK_SURFACE_TRANSFORM_IDENTITY_BIT_KHR] identity means unchanged; you can rotate and do other transforms to the images https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkSurfaceTransformFlagBitsKHR
    VkCompositeAlphaFlagBitsKHR compositeAlpha; // [def:VK_COMPOSITE_ALPHA_OPAQUE_BIT_KHR opaque]  https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkCompositeAlphaFlagBitsKHR

    // VK_PRESENT_MODE_IMMEDIATE_KHR - no waiting, tearing (no vsync)
    // VK_PRESENT_MODE_MAILBOX_KHR - with another buffer you can make triple buffering - i think it's more demanding
    // VK_PRESENT_MODE_FIFO_KHR - wait for vsync, aquire actually waits, so it's relaxed on the fps also
    // VK_PRESENT_MODE_SHARED_CONTINUOUS_REFRESH_KHR- continuously draws an image, without the need to call any func. uses vsync.
    VkPresentModeKHR presentMode; // [def:VK_PRESENT_MODE_FIFO_KHR vsync on] https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkPresentModeKHR

    // if set to true, pixels that have other windows over them, for example, will have undefined contents, vulkan will not render to them
    // BUT, if you intend to read from such pixels, with shaders or after aquiring the image, you should put this to false;
    // on true, things will work faster, if parts of the view is obstructed

    // Applications should set this value to VK_TRUE if they do not expect to read back the content of presentable images
    //  before presenting them or after reacquiring them, and if their pixel shaders do not have any side effects
    //  that require them to run for all pixels in the presentable image.
    VkBool32 clipped; // [def:false]

    VkDeviceGroupPresentModeFlagsKHR deviceGroupFlags; // [def:0] add device group info here if needed https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkDeviceGroupPresentModeFlagBitsKHR
    void addMultipleFormat(VkFormat in_format);         // if the swapchain should support multiple image formats, use this func multiple times to add them all

  private:
    chainList _multipleFormats;
    chainList _sharedQueues;  // [_Share chainData] shared between these queue families
    friend class VkoSwapchain;
  } cfg; // all swapchain's settings


  // after all parameters are set, call this func to create the vulkan swapchain
  bool build();     // returns true if successful. WARNING: A swapchain cannot be built on a minimized window (from specs, not tested)
  bool rebuild();
  bool check();
  void destroy();

  bool aquire(VkSemaphore in_finishPresenting, VkFence in_finishPresentingFence= nullptr, uint64_t timeout= ~0, uint32_t *out_index= nullptr);     //
  inline void queueShow(uint32_t in_surfaceIndex, VkQueue in_queue, VkSemaphore in_finishDrawing);// { _showInfo.pWaitSemaphores= &in_finishDrawing, _showInfo.pImageIndices= &in_surfaceIndex; _parent->vk->QueuePresentKHR(in_queue, &_showInfo); };   // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkPresentInfoKHR
  inline void queueShowCurrent(VkQueue in_queue, VkSemaphore in_finishDrawing) { queueShow(currentIndex, in_queue, in_finishDrawing); }

    

  VkoSwapchain();
  ~VkoSwapchain();

private:
  VkPresentInfoKHR _showInfo;
  VkSwapchainKHR _oldSwapchain;

  uint32_t _nformats;
  VkSurfaceFormatKHR *_formats;
  bool _isFormatOk(VkSurfaceKHR in_surface, VkFormat in_format, VkColorSpaceKHR in_colorSpace);


  uint32_t _index;    // index of the image currently being drawn by the app
  class _Share:  public chainData { public: uint32_t queueFamilyIndex; };
  class _Format: public chainData { public: VkFormat format; };
  vkObject *_parent;
  friend class vkObject;
}; /// Swapchain class



















