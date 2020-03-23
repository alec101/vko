#pragma once


///=================--------------------------///
// renderpass class ========================== //
///=================--------------------------///

class VkoRenderPass: public chainData {
public:
  VkRenderPass renderPass;    // vulkan render pass instance
  inline operator VkRenderPass() { return renderPass; }

  // customisation funcs - add stuff to the renderpass / configure, then call build() to finalize

  void addAttachment(const VkAttachmentDescription *in_attDescription);
  void addAttachment2(VkAttachmentDescriptionFlags flags,          VkFormat            format,        VkSampleCountFlagBits samples,
                      VkAttachmentLoadOp           loadOp,         VkAttachmentStoreOp storeOp,       VkAttachmentLoadOp    stencilLoadOp,
                      VkAttachmentStoreOp          stencilStoreOp, VkImageLayout       initialLayout, VkImageLayout         finalLayout);

  // subpasses

  // the order of adding new subpasses is important. Further configuring them, will require their index. The first subpass added will be index 0, etc.
  // subpass description specs: https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkSubpassDescription
  // <in_flags>: subpass flags, some extensions use some flags, otherwise must be 0
  // <in_pipelineBindPoint>: usage for the subpass, one of VK_PIPELINE_BIND_POINT_GRAPHICS or VK_PIPELINE_BIND_POINT_COMPUTE, atm
  void addSubpass(VkSubpassDescriptionFlags in_flags, VkPipelineBindPoint in_pipelineBindPoint);

  // shader image InputAttachmentIndex=X <->pInputAttachements[X]
  // <in_subpass>:    index of the subpass that will add the imput atachment
  // <in_attachment>: attachment index
  // <in_layout>:     image layout of the attachment
  void addSubpassInputAttachment(uint32_t in_subpass, uint32_t in_attachment, VkImageLayout in_layout);

  // fragment shader Location=X <-> pColorAtachements[x]
  // <in_subpass>:     index of the subpass that will add the color attachment
  // <in_colorAtt>:    attachment index
  // <in_colorLayout>: color attachment layout
  // <enableResolve> & <enableDepthStencil> will toggle usage of <in_resolveAtt>/<in_resolveLayout> and <in_depthStencilAtt>/<in_depthStencilLayout>
  // if all color attachments have resolve disabled, their array will be passed to Vulkan as nullptr, same with depth/stencil.
  // if one of the color attachments have resolve enabled, but the rest don't, the ones that don't, will be flagged as VK_ATTACHMENT_UNUSED 
  void addSubpassColorAttachment(uint32_t in_subpass, uint32_t in_colorAtt, VkImageLayout in_colorLayout,
                                  bool enableResolve,      uint32_t in_resolveAtt,      VkImageLayout in_resolveLayout,
                                  bool enableDepthStencil, uint32_t in_depthStencilAtt, VkImageLayout in_depthStencilLayout);
  // <in_subpass>:    index of the subpass that will add the color attachment
  // <in_color>:      color attachment
  // <in_resolve>/<in_depthStencil>: resolve and depth/stencil attachments; if left nullptr, the color attachment won't use them
  // if all color attachments have resolve disabled, their array will be passed to Vulkan as nullptr, same with depth/stencil.
  // if one of the color attachments have resolve enabled, but the rest don't, the ones that don't, will be flagged as VK_ATTACHMENT_UNUSED 
  void addSubpassColorAttachment2(uint32_t in_subpass, VkAttachmentReference *in_color, VkAttachmentReference *in_resolve= nullptr, VkAttachmentReference *in_depthStencil= nullptr);

  // preserve attachments will remain untouched thruout the subpass, they're not used
  // <in_subpass>: index of the subpass that will add the preserve attachment
  // <in_attachment>: attachment index
  void addSubpassPreserveAttachment(uint32_t in_subpass, uint32_t in_attachment);

  // subpass dependencies - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkSubpassDependency
  // !!! Care should be taken to avoid a data race here;
  // !!! if any subpasses access attachments with overlapping memory locations,
  // !!! and one of those accesses is a write, a subpass dependency needs to be included between them.

  void addSubpassDependency(uint32_t             srcSubpass,    uint32_t             dstSubpass, 
                            VkPipelineStageFlags srcStageMask,  VkPipelineStageFlags dstStageMask,
                            VkAccessFlags        srcAccessMask, VkAccessFlags        dstAccessMask,
                            VkDependencyFlags dependencyFlags);

  void addSubpassDependency2(const VkSubpassDependency *in_dependency);

  // specify which aspects of an input attachment can be read (NEED FURTHER CLARIFICATION FOR THIS)
  // <in_subpass>: the subpass of the atachment
  // <in_inputAttachmentIndex>: index of the input attachment
  // <in_aspectMask>: VkImageAspectFlagBits: https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkImageAspectFlagBits
  void addInputAttachmentAspect(uint32_t in_subpass, uint32_t in_inputAttachmentIndex, VkImageAspectFlags in_aspectMask);

  // enable render pass multiview. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkRenderPassMultiviewCreateInfo
  // there is not much info on all of this.
  // all pointers are copied from, so if they're allocated, they can be safely deleted after calling the func
  void addMultiView(uint32_t subpassCount, const uint32_t *pViewMasks,
                              uint32_t dependencyCount, const int32_t *pViewOffsets,
                              uint32_t correlationMaskCount, const uint32_t *pCorrelationMasks);

  inline void disableMultiView() { _multiView.delData(); }


  struct PNext {
    void *VkRenderPassCreateInfo;
    void delData() { VkRenderPassCreateInfo= nullptr; }
  } pNext;


  // after everything is setup, call build to have a fully functional object

  bool build();
  void destroy();
  inline bool rebuild() { destroy(); return build(); }

  // constructor / destructor

  VkoRenderPass(vkObject *in_parent);
  ~VkoRenderPass();
  void delData();

private:
  chainList _attachments;       // _Attachment
  chainList _subpasses;         // _Subpass
  chainList _dependencies;      // _Dependency
  chainList _aspectAttachments; // _InputAttAspect

  class _Attachment: public chainData {
  public:
    VkAttachmentDescription att; // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkAttachmentDescription
  };

  class _AttachmentRef: public chainData {
  public:
    uint32_t attachment;
    VkImageLayout layout;
  };

  class _Subpass: public chainData {
  public:
    VkSubpassDescriptionFlags flags;
    VkPipelineBindPoint pipelineBindPoint;
    chainList inputAttachments;           // _AttachmentRef
    chainList colorAttachments;           // _ColorAtt
    chainList preserveAttachments;        // _AttachmentRef
    bool enableResolve;
    bool enableDepthStencil;
    inline _Subpass() { delData(); }
    inline void delData() { enableResolve= false; enableDepthStencil= false; }
  };

  class _ColorAtt: public chainData {
  public:
    uint32_t      colorAtt;
    VkImageLayout colorLayout;
    uint32_t      resolveAtt;
    VkImageLayout resolveLayout;
    uint32_t      depthStencilAtt;
    VkImageLayout depthStencilLayout;
  };

  class _Dependency: public chainData {
  public:
    VkSubpassDependency dep;
  };

  class _InputAttAspect: public chainData {
  public:
    uint32_t           subpass;
    uint32_t           inputAttachmentIndex;
    VkImageAspectFlags aspectMask;
  };

  struct _MultiView {
    bool            enable;
    uint32_t        subpassCount;
    const uint32_t  *pViewMasks;
    uint32_t        dependencyCount;
    const int32_t   *pViewOffsets;
    uint32_t        correlationMaskCount;
    const uint32_t  *pCorrelationMasks;
    _MultiView(): pViewMasks(nullptr), pViewOffsets(nullptr), pCorrelationMasks(nullptr) { delData(); }
    void delData() { enable= false; subpassCount= dependencyCount= correlationMaskCount= 0;
                      if(pViewMasks)        delete[] pViewMasks;        pViewMasks=        nullptr;
                      if(pViewOffsets)      delete[] pViewOffsets;      pViewOffsets=      nullptr;
                      if(pCorrelationMasks) delete[] pCorrelationMasks; pCorrelationMasks= nullptr; }
    ~_MultiView() { delData(); }
  } _multiView;

  vkObject *_vko;
  friend class vkObject;
}; // renderPass;
  
  




