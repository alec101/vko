#pragma once


///==================------------------------///
// Framebuffer class ======================== //
///==================------------------------///

class VkoFramebuffer: public chainData {
public:
  VkFramebuffer framebuffer;  // after being built, this will hold the VkFramebuffer handle 

  VkRenderPass renderPass;    // the renderpass working with this framebuffer
  uint32_t dx, dy, layers;    // framebuffer dimensions

  VkImageView *imageView;     // after being built, this is an array of imageviews for every attachement
  uint32_t nrImageViews;      // after being built, this is the number of imageviews

  inline operator VkFramebuffer() { return framebuffer; }

  // configuration funcs

  // Set the dimensions of the framebuffer.
  // All images that will work with this framebuffer must be equal or less than the framebuffer's dimensions
  inline void setDimensions(uint32_t in_dx, uint32_t in_dy, int32_t in_layers= 1) { dx= in_dx, dy= in_dy, layers= in_layers; }

  // must set the renderpass that works with this framebuffer
  inline void setRenderPass(const VkRenderPass in_r) { renderPass= in_r; }

  // if not using a swapchain, add each image / buffer, one by one that will be used with this framebuffer
  // <in_image>: VkImage handle
  // <in_format>: the format of the image
  // <in_aspect>: VK_IMAGE_ASPECT_COLOR_BIT for color images, VK_IMAGE_ASPECT_DEPTH_BIT & VK_IMAGE_ASPECT_STENCIL_BIT for depth/stencil
  // <in_baseLayer>/<in_nrLayers>: if using multiview black magic, you can populate these, else leave them base(0) and nrLayers(1)
  void addAttachment(VkImage in_image, VkFormat in_imageFormat, VkImageAspectFlags in_aspect, uint32_t in_baseLayer= 0, uint32_t in_nrLayers= 1);
  // if the image changed (resize, etc), the framebuffer must be rebuilt. This func will allow to change current linked images to new ones
  // <in_index>: already built attachment index that will be changed
  void changeAttachment(uint32_t in_index, VkImage in_image, VkFormat in_imageFormat, VkImageAspectFlags in_aspect, uint32_t in_baseLayer= 0, uint32_t in_nrLayers= 1);

  struct PNext {
    void *VkImageViewCreateInfo;
    void *VkFramebufferCreateInfo;
    void delData() { VkImageViewCreateInfo= VkFramebufferCreateInfo= nullptr; }
  } pNext;


  // main funcs

  bool build();
  void destroy();
  inline bool rebuild() { destroy(); return build(); }

  VkoFramebuffer(vkObject *in_parent);
  ~VkoFramebuffer() { destroy(); delData(); }
  void delData();

private:
  chainList _attachments;
  class _Attachment: public chainData {
  public:
    VkImage image;
    VkFormat imageFormat;
    VkImageAspectFlags aspect;
    uint32_t baseLayer;
    uint32_t nrLayers;
    _Attachment(): image(NULL) {}
  };

  vkObject *_vko;
  friend class vkObject;
};










