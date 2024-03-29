#include "../include/vkObject.h"


///=========================///
// FRAMEBUFFER class / funcs //
///=========================///

VkoFramebuffer::VkoFramebuffer(vkObject *in_parent): _vko(in_parent) {
  framebuffer= 0;
  imageView= nullptr;
  delData();
}

void VkoFramebuffer::delData() {
  if(imageView) { delete[] imageView; imageView= nullptr; }

  pNext.delData();
  renderPass= 0;
  nrImageViews= 0;
  dx= dy= layers= 0;
  _attachments.delData();
}

void VkoFramebuffer::destroy() {
  if(framebuffer) {
    if(_vko->device)
      _vko->DestroyFramebuffer(*_vko, *this, *_vko);
    framebuffer= 0;
  }

  if(imageView) {
    if(_vko->device)
      for(uint32_t a= 0; a< nrImageViews; a++)
        _vko->DestroyImageView(*_vko, imageView[a], *_vko);
    delete[] imageView;
    imageView= nullptr;
  }

  nrImageViews= 0;
}



// configuration funcs
///-------------------///

void VkoFramebuffer::cfgAddAttachment(VkImage in_image, VkFormat in_imageFormat, VkImageAspectFlags in_aspect, uint32_t in_baseLayer, uint32_t in_nrLayers) {
  _Attachment *p= new _Attachment;
  p->image= in_image;
  p->imageFormat= in_imageFormat;
  p->aspect= in_aspect;
  p->baseLayer= in_baseLayer;
  p->nrLayers= in_nrLayers;

  _attachments.add(p);
}


void VkoFramebuffer::changeAttachment(uint32_t in_index, VkImage in_image, VkFormat in_imageFormat, VkImageAspectFlags in_aspect, uint32_t in_baseLayer, uint32_t in_nrLayers) {
  _Attachment *p= (_Attachment *)_attachments.get(in_index);
  p->image= in_image;
  p->imageFormat= in_imageFormat;
  p->aspect= in_aspect;
  p->baseLayer= in_baseLayer;
  p->nrLayers= in_nrLayers;
}





// FRAMEBUFFER build ===============--------------- //

bool VkoFramebuffer::build() {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap7.html#_framebuffers
  // intel tutorial https://software.intel.com/en-us/articles/api-without-secrets-introduction-to-vulkan-part-3
  // from specs:
  // Applications must ensure that all accesses to memory that backs image subresources used as attachments
  //  in a given renderpass instance either happen-before the load operations for those attachments,
  //  or happen-after the store operations for those attachments.

  
  // the frame buffer image view
  // -VkFormat must match
  // -SWIZZLE MUST BE IDENTITY, THEREFORE NO SWIZZLE
  // -ONLY 1 MIPMAP LEVEL
  // -DIMENSIONS OF ATACHMENTS MUST BE AS BIG OR LESS THAN THE FRAMEBUFFER
  // -aspectMask must be only VK_IMAGE_ASPECT_COLOR_BIT, VK_IMAGE_ASPECT_DEPTH_BIT or VK_IMAGE_ASPECT_STENCIL_BIT.
  
  bool ret= false;      /// return value

  VkFramebufferCreateInfo fbInfo;
  VkImageViewCreateInfo viewInfo; // https://www.khronos.org/registry/vulkan/specs/1.1/html/chap11.html#resources-image-views

  viewInfo.sType= VK_STRUCTURE_TYPE_IMAGE_VIEW_CREATE_INFO;
  viewInfo.pNext= pNext.VkImageViewCreateInfo;
  viewInfo.flags= 0;
  viewInfo.viewType= VK_IMAGE_VIEW_TYPE_2D;
  ///viewInfo.format= VK_FORMAT_R8G8B8A8_UINT;
  viewInfo.components.r= VK_COMPONENT_SWIZZLE_IDENTITY;
  viewInfo.components.g= VK_COMPONENT_SWIZZLE_IDENTITY;
  viewInfo.components.b= VK_COMPONENT_SWIZZLE_IDENTITY;
  viewInfo.components.a= VK_COMPONENT_SWIZZLE_IDENTITY;
  viewInfo.subresourceRange.aspectMask= VK_IMAGE_ASPECT_COLOR_BIT;
  viewInfo.subresourceRange.baseMipLevel= 0;    // mipmap accesible to this view
  viewInfo.subresourceRange.levelCount= 1;      // mipmap levels
  viewInfo.subresourceRange.baseArrayLayer= 0;
  viewInfo.subresourceRange.layerCount= 1;
  

  if(_attachments.nrNodes) {
    nrImageViews= _attachments.nrNodes;
    imageView= new VkImageView[_attachments.nrNodes];

    uint32_t a= 0;
    for(_Attachment *p= (_Attachment *)_attachments.first; p; p= (_Attachment *)p->next, a++) {
      viewInfo.image= p->image;
      viewInfo.format= p->imageFormat;
      viewInfo.subresourceRange.aspectMask= p->aspect;
      viewInfo.subresourceRange.baseArrayLayer= p->baseLayer;
      viewInfo.subresourceRange.layerCount= p->nrLayers;
      
      if(!_vko->errorCheck(_vko->CreateImageView(*_vko, &viewInfo, *_vko, &imageView[a]), "VkoFramebuffer::build(): Vulkan frame buffer image view creation failed"))
        goto Exit;
    } /// for each attachment
  }


  // start populating fbInfo

  fbInfo.sType= VK_STRUCTURE_TYPE_FRAMEBUFFER_CREATE_INFO;
  fbInfo.pNext= pNext.VkFramebufferCreateInfo;
  fbInfo.flags= 0;
  fbInfo.attachmentCount= _attachments.nrNodes;
  fbInfo.pAttachments= imageView;
  fbInfo.width= dx;
  fbInfo.height= dy;
  fbInfo.layers= layers;
  fbInfo.renderPass= renderPass;

  if(!_vko->errorCheck(_vko->CreateFramebuffer(*_vko, &fbInfo, *_vko, &framebuffer), "VkoFramebuffer::build(): Vulkan Framebuffer creation failed"))
    goto Exit;

  ret= true; // success

Exit:
  if(ret== false) {
    if(imageView) delete[] imageView;
    imageView= nullptr;
  }
  return ret;
}















