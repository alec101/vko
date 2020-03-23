#include "../include/vkObject.h"



///===========///
// render pass // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#renderpass
///===========///



VkoRenderPass::VkoRenderPass(vkObject *in_parent): _vko(in_parent), renderPass(0) {
  pNext.delData();
}

VkoRenderPass::~VkoRenderPass() {
  destroy();
}

void VkoRenderPass::delData() {
  pNext.delData();
  _attachments.delData();
  _subpasses.delData();
  _dependencies.delData();
  _aspectAttachments.delData();
  _multiView.delData();
}


void VkoRenderPass::destroy() {
  if(renderPass) {
    if(_vko->device)
      _vko->DestroyRenderPass(*_vko, *this, *_vko);
    renderPass= 0;
  }
}





// configuration funcs //
///-------------------///

void VkoRenderPass::addAttachment(const VkAttachmentDescription *in_attDescription) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkAttachmentDescription
  _Attachment *p= new _Attachment;
  p->att= *in_attDescription;
  _attachments.add(p);
}


void VkoRenderPass::addAttachment2(VkAttachmentDescriptionFlags in_flags, VkFormat in_format, VkSampleCountFlagBits in_samples,
                                   VkAttachmentLoadOp in_loadOp, VkAttachmentStoreOp in_storeOp, VkAttachmentLoadOp in_stencilLoadOp,
                                   VkAttachmentStoreOp in_stencilStoreOp, VkImageLayout in_initialLayout, VkImageLayout in_finalLayout) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkAttachmentDescription
  _Attachment *p= new _Attachment;
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
  p->flags= in_flags;
  p->pipelineBindPoint= in_pipelineBindPoint;
  _subpasses.add(p);
}


void VkoRenderPass::addSubpassInputAttachment(uint32_t in_subpass, uint32_t in_attachment, VkImageLayout in_layout) {
  _vko->clearError();
  if(in_subpass+ 1> (uint32_t)_subpasses.nrNodes) { _vko->errorText= __FUNCTION__": <in_subpass> parameter out of bounds of current amount of subpassses"; return; }
  _Subpass *s= (_Subpass *)_subpasses.get(in_subpass);
  _AttachmentRef *p= new _AttachmentRef;
  p->attachment= in_attachment;
  p->layout= in_layout;
  s->inputAttachments.add(p);
}


void VkoRenderPass::addSubpassColorAttachment(uint32_t in_subpass,     uint32_t in_colorAtt,        VkImageLayout in_colorLayout,
                                              bool enableResolve,      uint32_t in_resolveAtt,      VkImageLayout in_resolveLayout,
                                              bool enableDepthStencil, uint32_t in_depthStencilAtt, VkImageLayout in_depthStencilLayout) {
  _vko->clearError();
  if(in_subpass+ 1> (uint32_t)_subpasses.nrNodes) { _vko->errorText= __FUNCTION__": <in_subpass> parameter out of bounds of current amount of subpassses"; return; }
  _Subpass *s= (_Subpass *)_subpasses.get(in_subpass);
  _ColorAtt *p= new _ColorAtt;
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


void VkoRenderPass::addSubpassColorAttachment2(uint32_t in_subpass, VkAttachmentReference *in_color, VkAttachmentReference *in_resolve, VkAttachmentReference *in_depthStencil) {
  _vko->clearError();
  if(in_color== nullptr) { _vko->errorText= __FUNCTION__": <in_color> parameter nullptr"; return; }
  if(in_subpass+ 1> (uint32_t)_subpasses.nrNodes) { _vko->errorText= __FUNCTION__": <in_subpass> parameter out of bounds of current amount of subpassses"; return; }

  _Subpass *s= (_Subpass *)_subpasses.get(in_subpass);
  _ColorAtt *p= new _ColorAtt;

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
  p->dep= *in_dependency;
  _dependencies.add(p);
}



void VkoRenderPass::addSubpassPreserveAttachment(uint32_t in_subpass, uint32_t in_attachment) {
  // attachments that are not used by this subpass, but whose contents must be preserved throughout the subpass.
  _vko->clearError();
  if(in_subpass+ 1> (uint32_t)_subpasses.nrNodes) { _vko->errorText= __FUNCTION__": <in_subpass> parameter out of bounds of current amount of subpassses"; return; }
  _Subpass *s= (_Subpass *)_subpasses.get(in_subpass);
  _AttachmentRef *p= new _AttachmentRef;
  p->attachment= in_attachment;
  s->preserveAttachments.add(p);
}


void VkoRenderPass::addInputAttachmentAspect(uint32_t in_subpass, uint32_t in_inputAttachmentIndex, VkImageAspectFlags in_aspectMask) {
  // att aspect create info: https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkRenderPassInputAttachmentAspectCreateInfo
  // input attach ref: https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkInputAttachmentAspectReference
  //if(in_subpass+ 1> (uint32_t)_subpasses.nrNodes) { error.detail("<in_subpass> parameter out of bounds of current amount of subpassses", __FUNCTION__); return; }
  _InputAttAspect *p= new _InputAttAspect;
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
    for(uint32_t a= 0; a< in_subpassCount; a++)
      ((uint32_t *)_multiView.pViewMasks)[a]= in_pViewMasks[a];
  }
  /// Each view offset controls which views in the source subpass the views in the destination subpass depend on
  /// If dependencyCount is zero, each dependency’s view offset is treated as zero
  _multiView.dependencyCount= in_dependencyCount;
  if(in_dependencyCount) {
    _multiView.pViewOffsets= new int32_t[in_dependencyCount];
    for(uint32_t a= 0; a< in_dependencyCount; a++)
      ((int32_t *)_multiView.pViewOffsets)[a]= in_pViewOffsets[a];
  }
  /// indicates sets of views that may be more efficient to render concurrently.
  _multiView.correlationMaskCount= in_correlationMaskCount;
  if(in_correlationMaskCount) {
    _multiView.pCorrelationMasks= new uint32_t[in_correlationMaskCount];
    for(uint32_t a= 0; a< in_correlationMaskCount; a++)
      ((uint32_t *)_multiView.pCorrelationMasks)[a]= in_pCorrelationMasks[a];
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
  uint32_t a, b;
  VkRenderPassCreateInfo renderPassInfo;
  VkRenderPassInputAttachmentAspectCreateInfo aspectInfo;
  VkRenderPassMultiviewCreateInfo multiViewInfo;

  aspectInfo.pAspectReferences= nullptr;       // INIT ALLOC 1
  renderPassInfo.pAttachments= nullptr;        // INIT ALLOC 2
  renderPassInfo.pSubpasses= nullptr;          // INIT ALLOC 3
  renderPassInfo.pDependencies= nullptr;       // INIT ALLOC 9


  renderPassInfo.sType= VK_STRUCTURE_TYPE_RENDER_PASS_CREATE_INFO;
  renderPassInfo.flags= 0;            // reserved ATM
  renderPassInfo.pNext= nullptr;         //  VkRenderPassInputAttachmentAspectCreateInfo or VkRenderPassMultiviewCreateInfo
  const void **_pNext= &renderPassInfo.pNext;

  // input attachment aspect - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkRenderPassInputAttachmentAspectCreateInfo
  /// To specify which aspects of an input attachment can be read add a VkRenderPassInputAttachmentAspectCreateInfo
  /// you use that struct to pinpoint the atachement and subpass that can be read by a shader stage it seems

  if(_aspectAttachments.nrNodes) {
    *_pNext= &aspectInfo;
    aspectInfo.sType= VK_STRUCTURE_TYPE_RENDER_PASS_INPUT_ATTACHMENT_ASPECT_CREATE_INFO;
    aspectInfo.pNext= nullptr;
    aspectInfo.aspectReferenceCount= _aspectAttachments.nrNodes;
    aspectInfo.pAspectReferences= new VkInputAttachmentAspectReference[_aspectAttachments.nrNodes]; // ALLOC 1

    a= 0;
    for(_InputAttAspect *p= (_InputAttAspect *)_aspectAttachments.first; p; p= (_InputAttAspect *)p->next)
      ((VkInputAttachmentAspectReference *)aspectInfo.pAspectReferences)->subpass= p->subpass,
      ((VkInputAttachmentAspectReference *)aspectInfo.pAspectReferences)->inputAttachmentIndex= p->inputAttachmentIndex,
      ((VkInputAttachmentAspectReference *)aspectInfo.pAspectReferences)->aspectMask= p->aspectMask,
      a++;
    _pNext= &aspectInfo.pNext;
  }

  // multiviews - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkRenderPassMultiviewCreateInfo
  if(_multiView.enable) {
    *_pNext= &multiViewInfo;
    multiViewInfo.sType= VK_STRUCTURE_TYPE_RENDER_PASS_MULTIVIEW_CREATE_INFO;
    multiViewInfo.pNext= nullptr;
    multiViewInfo.subpassCount=         _multiView.subpassCount;
    multiViewInfo.pViewMasks=           _multiView.pViewMasks;
    multiViewInfo.dependencyCount=      _multiView.dependencyCount;
    multiViewInfo.pViewOffsets=         _multiView.pViewOffsets;
    multiViewInfo.correlationMaskCount= _multiView.correlationMaskCount;
    multiViewInfo.pCorrelationMasks=    _multiView.pCorrelationMasks;
    _pNext= &multiViewInfo.pNext;
  }

  *_pNext= pNext.VkRenderPassCreateInfo;  // last pNext link is the custom one


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
    a= 0;
    for(_Attachment *p= (_Attachment *)_attachments.first; p; p= (_Attachment *)p->next)
      ((VkAttachmentDescription *)renderPassInfo.pAttachments)[a++]= p->att;
  }

  // subpasses - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#VkSubpassDescription
  renderPassInfo.subpassCount= _subpasses.nrNodes;
  if(renderPassInfo.subpassCount) {
    renderPassInfo.pSubpasses= new VkSubpassDescription[renderPassInfo.subpassCount];       // ALLOC 3
    a= 0;
    for(_Subpass *p= (_Subpass *)_subpasses.first; p; p= (_Subpass *)p->next) {
      VkSubpassDescription *sd= (VkSubpassDescription *)&renderPassInfo.pSubpasses[a];    /// shortcut
      sd->pInputAttachments= nullptr;        // INIT ALLOC 4
      sd->pColorAttachments= nullptr;        // INIT ALLOC 5
      sd->pResolveAttachments= nullptr;      // INIT ALLOC 6
      sd->pDepthStencilAttachment= nullptr;  // INIT ALLOC 7
      sd->pPreserveAttachments= nullptr;     // INIT ALLOC 8

      sd->flags= p->flags;
      sd->pipelineBindPoint= p->pipelineBindPoint;

      // subpass input attachments
      sd->inputAttachmentCount= p->inputAttachments.nrNodes;

      if(sd->inputAttachmentCount) {
        sd->pInputAttachments= new VkAttachmentReference[sd->inputAttachmentCount];         // ALLOC 4
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
        if(p->enableResolve) {
          sd->pResolveAttachments= new VkAttachmentReference[sd->colorAttachmentCount];     // ALLOC 6
        } else
          sd->pResolveAttachments= nullptr;

        if(p->enableDepthStencil) {
          sd->pDepthStencilAttachment= new VkAttachmentReference[sd->colorAttachmentCount]; // ALLOC 7
        } else
          sd->pDepthStencilAttachment= nullptr;

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
        sd->pPreserveAttachments= new uint32_t[sd->preserveAttachmentCount];              // ALLOC 8
        b= 0;
        for(_AttachmentRef *ar= (_AttachmentRef *)p->preserveAttachments.first; ar; ar= (_AttachmentRef *)p->next, b++)
          ((uint32_t *)sd->pPreserveAttachments)[b]= ar->attachment;
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
    a= 0;
    for(_Dependency *p= (_Dependency *)_dependencies.first; p; p= (_Dependency *)p->next, a++)
      ((VkSubpassDependency *)renderPassInfo.pDependencies)[a]= p->dep;
  } /// if there are dependencies

  
  if(!_vko->errorCheck(_vko->CreateRenderPass(*_vko, &renderPassInfo, *_vko, &renderPass),
    __FUNCTION__": Vulkan render pass creation failed"))
    goto Exit;

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

















