#include "vkObject.h"



///===========///
// render pass // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#renderpass
///===========///



VkoRenderPass::VkoRenderPass() {
  _parent= null;
  renderPass= null;
}


VkoRenderPass::~VkoRenderPass() {

}


void VkoRenderPass::destroy() {
  if(!_parent->device) return;
  if(renderPass) {
    _parent->vk->DestroyRenderPass(_parent->device, *this, _parent->memCallback);
    renderPass= null;
  }
}

// customization funcs


void VkoRenderPass::addAttachment(const VkAttachmentDescription *in_attDescription) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkAttachmentDescription
  _Attachment *p= new _Attachment;
  if(!p) { error.alloc(__FUNCTION__); return; }
  p->att= *in_attDescription;
  _attachments.add(p);
}


void VkoRenderPass::addAttachment2(VkAttachmentDescriptionFlags in_flags, VkFormat in_format, VkSampleCountFlagBits in_samples,
                                   VkAttachmentLoadOp in_loadOp, VkAttachmentStoreOp in_storeOp, VkAttachmentLoadOp in_stencilLoadOp,
                                   VkAttachmentStoreOp in_stencilStoreOp, VkImageLayout in_initialLayout, VkImageLayout in_finalLayout) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkAttachmentDescription
  _Attachment *p= new _Attachment;
  if(!p) { error.alloc(__FUNCTION__); return; }
  p->att.flags= in_flags,
  p->att.format= in_format,
  p->att.samples= in_samples,
  p->att.loadOp= in_loadOp,
  p->att.storeOp= in_storeOp,
  p->att.stencilLoadOp= in_stencilLoadOp,
  p->att.stencilStoreOp= in_stencilStoreOp,
  p->att.initialLayout= in_initialLayout,
  p->att.finalLayout= in_finalLayout;
  _attachments.add(p);
}


void VkoRenderPass::addSubpass(VkSubpassDescriptionFlags in_flags, VkPipelineBindPoint in_pipelineBindPoint) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkSubpassDescription
  _Subpass *p= new _Subpass;
  if(p== null) { error.alloc(__FUNCTION__); return; }
  p->flags= in_flags;
  p->pipelineBindPoint= in_pipelineBindPoint;
  _subpasses.add(p);
}


void VkoRenderPass::addSubpassInputAttachment(uint32 in_subpass, uint32_t in_attachment, VkImageLayout in_layout) {
  if(in_subpass+ 1> (uint32)_subpasses.nrNodes) { error.detail("<in_subpass> parameter out of bounds of current amount of subpassses", __FUNCTION__); return; }
  _Subpass *s= (_Subpass *)_subpasses.get(in_subpass);
  _AttachmentRef *p= new _AttachmentRef;
  if(!p) { error.alloc(__FUNCTION__); return; }
  p->attachment= in_attachment;
  p->layout= in_layout;
  s->inputAttachments.add(p);
}


void VkoRenderPass::addSubpassColorAttachment(uint32 in_subpass,       uint32_t in_colorAtt,        VkImageLayout in_colorLayout,
                                              bool enableResolve,      uint32_t in_resolveAtt,      VkImageLayout in_resolveLayout,
                                              bool enableDepthStencil, uint32_t in_depthStencilAtt, VkImageLayout in_depthStencilLayout) {

  if(in_subpass+ 1> (uint32)_subpasses.nrNodes) { error.detail("<in_subpass> parameter out of bounds of current amount of subpassses", __FUNCTION__); return; }
  _Subpass *s= (_Subpass *)_subpasses.get(in_subpass);
  _ColorAtt *p= new _ColorAtt;
  if(p== null) { error.alloc(__FUNCTION__); return; }
  p->colorAtt= in_colorAtt;
  p->colorLayout= in_colorLayout;

  if(enableResolve)
    s->enableResolve= true,
    p->resolveAtt= in_resolveAtt,
    p->resolveLayout= in_resolveLayout;
  else
    p->resolveAtt= VK_ATTACHMENT_UNUSED,
    p->resolveLayout= VK_IMAGE_LAYOUT_UNDEFINED;

  if(enableDepthStencil)
    s->enableDepthStencil= true,
    p->depthStencilAtt= in_depthStencilAtt,
    p->depthStencilLayout= in_depthStencilLayout;
  else
    p->depthStencilAtt= VK_ATTACHMENT_UNUSED,
    p->depthStencilLayout= VK_IMAGE_LAYOUT_UNDEFINED;

  s->colorAttachments.add(p);
}


void VkoRenderPass::addSubpassColorAttachment2(uint32 in_subpass, VkAttachmentReference *in_color, VkAttachmentReference *in_resolve, VkAttachmentReference *in_depthStencil) {
  if(in_color== null) { error.detail("<in_color> parameter null", __FUNCTION__); return; }
  if(in_subpass+ 1> (uint32)_subpasses.nrNodes) { error.detail("<in_subpass> parameter out of bounds of current amount of subpassses", __FUNCTION__); return; }

  _Subpass *s= (_Subpass *)_subpasses.get(in_subpass);
  _ColorAtt *p= new _ColorAtt;
  if(p== null) { error.alloc(__FUNCTION__); return; }

  p->colorAtt=    in_color->attachment;
  p->colorLayout= in_color->layout;

  if(in_resolve)
    s->enableResolve= true,
    p->resolveAtt=    in_resolve->attachment,
    p->resolveLayout= in_resolve->layout;
  else
    p->resolveAtt=    VK_ATTACHMENT_UNUSED,
    p->resolveLayout= VK_IMAGE_LAYOUT_UNDEFINED;

  if(in_depthStencil)
    s->enableDepthStencil= true,
    p->depthStencilAtt=    in_depthStencil->attachment,
    p->depthStencilLayout= in_depthStencil->layout;
  else
    p->depthStencilAtt=    VK_ATTACHMENT_UNUSED,
    p->depthStencilLayout= VK_IMAGE_LAYOUT_UNDEFINED;

  s->colorAttachments.add(p);
}


void VkoRenderPass::addSubpassDependency(uint32_t             in_srcSubpass,    uint32_t             in_dstSubpass, 
                                         VkPipelineStageFlags in_srcStageMask,  VkPipelineStageFlags in_dstStageMask,
                                         VkAccessFlags        in_srcAccessMask, VkAccessFlags        in_dstAccessMask,
                                         VkDependencyFlags    in_dependencyFlags) {
  _Dependency *p= new _Dependency;
  if(p== null) { error.alloc(__FUNCTION__); return; }

  p->dep.srcSubpass=      in_srcSubpass;
  p->dep.dstSubpass=      in_dstSubpass;
  p->dep.srcStageMask=    in_srcStageMask;
  p->dep.dstStageMask=    in_dstStageMask;
  p->dep.srcAccessMask=   in_srcAccessMask;
  p->dep.dstAccessMask=   in_dstAccessMask;
  p->dep.dependencyFlags= in_dependencyFlags;
  _dependencies.add(p);
}


void VkoRenderPass::addSubpassDependency2(const VkSubpassDependency *in_dependency) {
  _Dependency *p= new _Dependency;
  if(p== null) { error.alloc(__FUNCTION__); return; }
  p->dep= *in_dependency;
  _dependencies.add(p);
}



void VkoRenderPass::addSubpassPreserveAttachment(uint32 in_subpass, uint32_t in_attachment) {
  // attachments that are not used by this subpass, but whose contents must be preserved throughout the subpass.
  if(in_subpass+ 1> (uint32)_subpasses.nrNodes) { error.detail("<in_subpass> parameter out of bounds of current amount of subpassses", __FUNCTION__); return; }
  _Subpass *s= (_Subpass *)_subpasses.get(in_subpass);
  _AttachmentRef *p= new _AttachmentRef;
  if(!p) { error.alloc(__FUNCTION__); return; }
  p->attachment= in_attachment;
  s->preserveAttachments.add(p);
}


void VkoRenderPass::addInputAttachmentAspect(uint32 in_subpass, uint32_t in_inputAttachmentIndex, VkImageAspectFlags in_aspectMask) {
  // att aspect create info: https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkRenderPassInputAttachmentAspectCreateInfo
  // input attach ref: https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkInputAttachmentAspectReference
  //if(in_subpass+ 1> (uint32)_subpasses.nrNodes) { error.detail("<in_subpass> parameter out of bounds of current amount of subpassses", __FUNCTION__); return; }
  _InputAttAspect *p= new _InputAttAspect;
  if(!p) { error.alloc(__FUNCTION__); return; }
  p->subpass= in_subpass;
  p->inputAttachmentIndex= in_inputAttachmentIndex;
  p->aspectMask= in_aspectMask;
  _aspectAttachments.add(p);
}


void VkoRenderPass::addMultiView(uint32_t in_subpassCount,         const uint32_t *in_pViewMasks,
                                 uint32_t in_dependencyCount,      const int32_t  *in_pViewOffsets,
                                 uint32_t in_correlationMaskCount, const uint32_t *in_pCorrelationMasks) {

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkRenderPassMultiviewCreateInfo
  _multiView.delData();

  _multiView.enable= true;

  /// each mask is a bitfield of view indices describing which views rendering is broadcast to in each subpass
  /// If subpassCount is zero, each view mask is treated as zero.
  _multiView.subpassCount= in_subpassCount;
  if(in_subpassCount) {
    _multiView.pViewMasks= new uint32_t[in_subpassCount];
    for(uint a= 0; a< in_subpassCount; a++)
      ((uint32 *)_multiView.pViewMasks)[a]= in_pViewMasks[a];
  }
  /// Each view offset controls which views in the source subpass the views in the destination subpass depend on
  /// If dependencyCount is zero, each dependency’s view offset is treated as zero
  _multiView.dependencyCount= in_dependencyCount;
  if(in_dependencyCount) {
    _multiView.pViewOffsets= new int32_t[in_dependencyCount];
    for(uint a= 0; a< in_dependencyCount; a++)
      ((int32 *)_multiView.pViewOffsets)[a]= in_pViewOffsets[a];
  }
  /// indicates sets of views that may be more efficient to render concurrently.
  _multiView.correlationMaskCount= in_correlationMaskCount;
  if(in_correlationMaskCount) {
    _multiView.pCorrelationMasks= new uint32_t[in_correlationMaskCount];
    for(uint a= 0; a< in_correlationMaskCount; a++)
      ((uint32 *)_multiView.pCorrelationMasks)[a]= in_pCorrelationMasks[a];
  }
}












///==================----------------------------------------
// BUILD render pass ====================--------------------
///==================----------------------------------------

bool VkoRenderPass::build() {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#renderpass
  /// -so this will define the drawing 'frame' - you start the drawing to something, and define how detailed that drawing will be, it seems
  /// -from what i read, you can have multiple views - probably drawing on multiple things, of the same things, and have corelations between those views
  /// -usually it's best to have 1 render pass. if for some reason i will need more than 1, they can be compatible, if they are kinda the same
  ///    same nr of atachements, same number of subpasses, etc

  bool ret= false;
  uint a, b;
  VkRenderPassCreateInfo renderPassInfo;
  VkRenderPassInputAttachmentAspectCreateInfo aspectInfo;
  VkRenderPassMultiviewCreateInfo multiViewInfo;

  aspectInfo.pAspectReferences= null;       // INIT ALLOC 1
  renderPassInfo.pAttachments= null;        // INIT ALLOC 2
  renderPassInfo.pSubpasses= null;          // INIT ALLOC 3
  renderPassInfo.pDependencies= null;       // INIT ALLOC 9


  renderPassInfo.sType= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.flags= 0;            // reserved ATM
  renderPassInfo.pNext= null;         //  VkRenderPassInputAttachmentAspectCreateInfo or VkRenderPassMultiviewCreateInfo
  const void **pNext= &renderPassInfo.pNext;

  // input attachment aspect - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkRenderPassInputAttachmentAspectCreateInfo
  /// To specify which aspects of an input attachment can be read add a VkRenderPassInputAttachmentAspectCreateInfo
  /// you use that struct to pinpoint the atachement and subpass that can be read by a shader stage it seems

  if(_aspectAttachments.nrNodes) {
    *pNext= &aspectInfo;
    aspectInfo.sType= VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO;
    aspectInfo.pNext= null;
    aspectInfo.aspectReferenceCount= _aspectAttachments.nrNodes;
    aspectInfo.pAspectReferences= new VkInputAttachmentAspectReference[_aspectAttachments.nrNodes]; // ALLOC 1
    if(!aspectInfo.pAspectReferences) { error.alloc(__FUNCTION__); goto Exit; }

    a= 0;
    for(_InputAttAspect *p= (_InputAttAspect *)_aspectAttachments.first; p; p= (_InputAttAspect *)p->next)
      ((VkInputAttachmentAspectReference *)aspectInfo.pAspectReferences)->subpass= p->subpass,
      ((VkInputAttachmentAspectReference *)aspectInfo.pAspectReferences)->inputAttachmentIndex= p->inputAttachmentIndex,
      ((VkInputAttachmentAspectReference *)aspectInfo.pAspectReferences)->aspectMask= p->aspectMask,
      a++;
    pNext= &aspectInfo.pNext;
  }

  // multiviews - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkRenderPassMultiviewCreateInfo
  if(_multiView.enable) {
    *pNext= &multiViewInfo;
    multiViewInfo.sType= VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
    multiViewInfo.pNext= null;
    multiViewInfo.subpassCount=         _multiView.subpassCount;
    multiViewInfo.pViewMasks=           _multiView.pViewMasks;
    multiViewInfo.dependencyCount=      _multiView.dependencyCount;
    multiViewInfo.pViewOffsets=         _multiView.pViewOffsets;
    multiViewInfo.correlationMaskCount= _multiView.correlationMaskCount;
    multiViewInfo.pCorrelationMasks=    _multiView.pCorrelationMasks;
    pNext= &multiViewInfo.pNext;
  }

  // atachements used by this renderpass - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkAttachmentDescription

  /// specify which aspects of an input attachment can be read
  /// FEW NOTES:
  /// start and end of the operation; when a color is present, stencil is ignored; 
  /// if depth and/or stencil format, load and store will handle depth settings, stencilOp will handle stencil

  /// start of the operation on this atachement;
  /// color load will happen on VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;
  /// stencil load will happen VK_PIPELINE_STAGE_EARLY_FRAGMENT_TESTS_BIT
  /// ad.loadOp= VkAttachmentLoadOp::VK_ATTACHMENT_LOAD_OP_CLEAR;  // clears the image; can be VK_ATTACHMENT_LOAD_OP_LOAD to preserve last frame or VK_ATTACHMENT_LOAD_OP_DONT_CARE

  /// end of the operation on this atachement
  /// stencil final operations happen in VK_PIPELINE_STAGE_LATE_FRAGMENT_TESTS_BIT
  /// color final operations happen in VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT
  /// ad.storeOp=  VkAttachmentStoreOp::VK_ATTACHMENT_STORE_OP_STORE; // the result will be written in memory; DONT_CARE- the contents after rendering can be discarded

  /// when a color format is present, stencil is ignored

  renderPassInfo.attachmentCount= _attachments.nrNodes;
  if(renderPassInfo.attachmentCount) {
    renderPassInfo.pAttachments= new VkAttachmentDescription[renderPassInfo.attachmentCount]; // ALLOC 2
    if(!renderPassInfo.pAttachments) { error.alloc(__FUNCTION__); goto Exit; }
    a= 0;
    for(_Attachment *p= (_Attachment *)_attachments.first; p; p= (_Attachment *)p->next)
      ((VkAttachmentDescription *)renderPassInfo.pAttachments)[a++]= p->att;
  }

  // subpasses - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkSubpassDescription
  renderPassInfo.subpassCount= _subpasses.nrNodes;
  if(renderPassInfo.subpassCount) {
    renderPassInfo.pSubpasses= new VkSubpassDescription[renderPassInfo.subpassCount];       // ALLOC 3
    if(!renderPassInfo.pSubpasses) { error.alloc(__FUNCTION__); goto Exit; }
    a= 0;
    for(_Subpass *p= (_Subpass *)_subpasses.first; p; p= (_Subpass *)p->next) {
      VkSubpassDescription *sd= (VkSubpassDescription *)&renderPassInfo.pSubpasses[a];    /// shortcut
      sd->pInputAttachments= null;        // INIT ALLOC 4
      sd->pColorAttachments= null;        // INIT ALLOC 5
      sd->pResolveAttachments= null;      // INIT ALLOC 6
      sd->pDepthStencilAttachment= null;  // INIT ALLOC 7
      sd->pPreserveAttachments= null;     // INIT ALLOC 8

      sd->flags= p->flags;
      sd->pipelineBindPoint= p->pipelineBindPoint;

      // subpass input attachments
      sd->inputAttachmentCount= p->inputAttachments.nrNodes;

      if(sd->inputAttachmentCount) {
        sd->pInputAttachments= new VkAttachmentReference[sd->inputAttachmentCount];         // ALLOC 4
        if(!sd->pInputAttachments) { error.alloc(__FUNCTION__); goto Exit; }
        b= 0;
        for(_AttachmentRef *ar= (_AttachmentRef *)p->inputAttachments.first; ar; ar= (_AttachmentRef *)ar->next)
          ((VkAttachmentReference *)sd->pInputAttachments)[b].attachment= ar->attachment,
          ((VkAttachmentReference *)sd->pInputAttachments)[b].layout= ar->layout,
          b++;
      } /// if there's input attachments
      
      // subpass color attachments
      sd->colorAttachmentCount= p->colorAttachments.nrNodes;

      if(sd->colorAttachmentCount) {
        sd->pColorAttachments= new VkAttachmentReference[sd->colorAttachmentCount];         // ALLOC 5
        if(!sd->pColorAttachments) { error.alloc(__FUNCTION__); goto Exit; }
        if(p->enableResolve) {
          sd->pResolveAttachments= new VkAttachmentReference[sd->colorAttachmentCount];     // ALLOC 6
          if(sd->pResolveAttachments== null) { error.alloc(__FUNCTION__); goto Exit; }
        } else
          sd->pResolveAttachments= null;

        if(p->enableDepthStencil) {
          sd->pDepthStencilAttachment= new VkAttachmentReference[sd->colorAttachmentCount]; // ALLOC 7
          if(sd->pDepthStencilAttachment== null) { error.alloc(__FUNCTION__); goto Exit; }
        } else
          sd->pDepthStencilAttachment= null;

        b= 0;
        for(_ColorAtt *c= (_ColorAtt *)p->colorAttachments.first; c; c= (_ColorAtt *)c->next, b++) {
          /// color attachments
          ((VkAttachmentReference *)sd->pColorAttachments)[b].attachment= c->colorAtt,
          ((VkAttachmentReference *)sd->pColorAttachments)[b].layout= c->colorLayout;
          /// resolve attachments
          if(p->enableResolve)
            ((VkAttachmentReference *)sd->pResolveAttachments)[b].attachment= c->resolveAtt,
            ((VkAttachmentReference *)sd->pResolveAttachments)[b].layout= c->resolveLayout;
          /// depth stencil attachments
          if(p->enableDepthStencil)
            ((VkAttachmentReference *)sd->pDepthStencilAttachment)[b].attachment= c->depthStencilAtt,
            ((VkAttachmentReference *)sd->pDepthStencilAttachment)[b].layout= c->depthStencilLayout;
        } /// for each color attachment
      } /// if there are color attachments

      // subpass preserve attachments
      sd->preserveAttachmentCount= p->preserveAttachments.nrNodes;

      if(sd->preserveAttachmentCount) {
        sd->pPreserveAttachments= new uint32[sd->preserveAttachmentCount];              // ALLOC 8
        if(sd->pPreserveAttachments== null) { error.alloc(__FUNCTION__); goto Exit; }
        b= 0;
        for(_AttachmentRef *ar= (_AttachmentRef *)p->preserveAttachments.first; ar; ar= (_AttachmentRef *)p->next, b++)
          ((uint32 *)sd->pPreserveAttachments)[b]= ar->attachment;
      } /// if there's preserve attachments
    }
  }

  // dependencies - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkSubpassDependency

  // !!!
  // Care should be taken to avoid a data race here;
  //  if any subpasses access attachments with overlapping memory locations,
  //  and one of those accesses is a write, a subpass dependency needs to be included between them.
  // !!!

  renderPassInfo.dependencyCount= _dependencies.nrNodes;
  if(renderPassInfo.dependencyCount) {
    renderPassInfo.pDependencies= new VkSubpassDependency[renderPassInfo.dependencyCount];
    if(renderPassInfo.pDependencies== null) { error.alloc(__FUNCTION__); goto Exit; }
    a= 0;
    for(_Dependency *p= (_Dependency *)_dependencies.first; p; p= (_Dependency *)p->next, a++)
      ((VkSubpassDependency *)renderPassInfo.pDependencies)[a]= p->dep;
  } /// if there are dependencies

  
  
  if(_parent->vk->CreateRenderPass(_parent->device, &renderPassInfo, _parent->memCallback, &renderPass)!= VK_SUCCESS) {
    error.detail("Vulkan render pass creation failed", __FUNCTION__, __LINE__);
    goto Exit;
  }
  ret= true;

Exit:
  if(aspectInfo.pAspectReferences) delete[] aspectInfo.pAspectReferences; // DEALLOC 1
  if(renderPassInfo.pAttachments) delete[] renderPassInfo.pAttachments;   // DEALLOC 2
  if(renderPassInfo.pSubpasses) {
    for(a= 0; a< renderPassInfo.subpassCount; a++) {
      if(renderPassInfo.pSubpasses[a].pInputAttachments)       delete[] renderPassInfo.pSubpasses[a].pInputAttachments;       // DEALLOC 4
      if(renderPassInfo.pSubpasses[a].pColorAttachments)       delete[] renderPassInfo.pSubpasses[a].pColorAttachments;       // DEALLOC 5
      if(renderPassInfo.pSubpasses[a].pResolveAttachments)     delete[] renderPassInfo.pSubpasses[a].pResolveAttachments;     // DEALLOC 6
      if(renderPassInfo.pSubpasses[a].pDepthStencilAttachment) delete[] renderPassInfo.pSubpasses[a].pDepthStencilAttachment; // DEALLOC 7
      if(renderPassInfo.pSubpasses[a].pPreserveAttachments)    delete[] renderPassInfo.pSubpasses[a].pPreserveAttachments;    // DEALLOC 8
    }
    delete[] renderPassInfo.pSubpasses;                                   // DEALLOC 3
  }
  if(renderPassInfo.pDependencies) delete[] renderPassInfo.pDependencies; // DEALLOC 9

  return ret;
}

















