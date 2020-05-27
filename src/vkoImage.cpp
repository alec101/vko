#include "vko/include/vkObject.h"




///==============------------------///
// BUFFER object ================== //
///==============------------------///


VkoImage::VkoImage(vkObject *in_parent): _vko(in_parent) {
  image= 0;

  createInfo.pQueueFamilyIndices= nullptr;        // INIT 1
  
  delData();
}


VkoImage::~VkoImage() {
  delData();
}


void VkoImage::delData() {
  if(image) destroy();
  offset= 0;
  size= 0;

  pNext.delData();

  memRequirements.alignment= 0;
  memRequirements.memoryTypeBits= 0;
  memRequirements.size= 0;


  // DEFAULT values

  createInfo.sType= VK_STRUCTURE_TYPE_IMAGE_CREATE_INFO;
  createInfo.pNext= nullptr;

  createInfo.flags= 0;                     // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageCreateFlagBits
  createInfo.imageType= VK_IMAGE_TYPE_2D;  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageType
  createInfo.format= VK_FORMAT_UNDEFINED;  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap36.html#VkFormat

  createInfo.extent.width= 0;
  createInfo.extent.height= 0;
  createInfo.extent.depth= 0;
  createInfo.mipLevels= 0;
  createInfo.arrayLayers= 0; // 2048->8192 image array size (from https://vulkan.gpuinfo.org/listlimits.php)

  createInfo.samples= VK_SAMPLE_COUNT_1_BIT; // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap35.html#VkSampleCountFlagBits
  
  createInfo.tiling= VK_IMAGE_TILING_OPTIMAL;

  createInfo.usage= 0;                     // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageUsageFlagBits

  createInfo.sharingMode= VK_SHARING_MODE_EXCLUSIVE;
  createInfo.queueFamilyIndexCount= 0;
  if(createInfo.pQueueFamilyIndices) {
    delete[] createInfo.pQueueFamilyIndices;   // DEALLOC 1
    createInfo.pQueueFamilyIndices= nullptr;
  }

  createInfo.initialLayout= VK_IMAGE_LAYOUT_UNDEFINED; 
}


void VkoImage::destroy() {
  if(image) {
    if(_vko)
      if(_vko->device)
        _vko->DestroyImage(*_vko, image, *_vko);
    image= 0;
  }
}


// settings

void VkoImage::setSize(uint32_t in_dx, uint32_t in_dy, uint32_t in_depth, uint32_t in_mipLevels, uint32_t in_layers) {
  createInfo.extent.width=  in_dx,
  createInfo.extent.height= in_dy,
  createInfo.extent.depth=  in_depth,
  createInfo.mipLevels=     in_mipLevels,
  createInfo.arrayLayers=   in_layers;
}

void VkoImage::setSize2(VkExtent3D in_size, uint32_t in_mipLevels, uint32_t in_layers) {
  createInfo.extent= in_size,
  createInfo.mipLevels= in_mipLevels,
  createInfo.arrayLayers= in_layers;
}

void VkoImage::setFlags(VkImageCreateFlags in_flags) {
  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageCreateFlagBits
  createInfo.flags= in_flags;
}

void VkoImage::setType(VkImageType in_type) {
  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageType
  createInfo.imageType= in_type;
}

void VkoImage::setFormat(VkFormat in_format) {
  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageType
  createInfo.format= in_format;
}

void VkoImage::setSamples(VkSampleCountFlagBits in_samples) {
  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap35.html#VkSampleCountFlagBits  
  createInfo.samples= in_samples;
}

void VkoImage::setTiling(VkImageTiling in_tiling) {
  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageTiling
  createInfo.tiling= in_tiling;
}

void VkoImage::setUsage(VkImageUsageFlags in_usage) {
  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageUsageFlagBits
  createInfo.usage= in_usage;
}

void VkoImage::setSharingMode(VkSharingMode in_sharing) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkSharingMode
  createInfo.sharingMode= in_sharing;
}

void VkoImage::addFamily(uint32_t in_f) {
  uint32_t oldNr= createInfo.queueFamilyIndexCount;
  uint32_t *oldFamilies= (uint32_t *)createInfo.pQueueFamilyIndices;

  createInfo.queueFamilyIndexCount++;
  createInfo.pQueueFamilyIndices= nullptr;
  createInfo.pQueueFamilyIndices= new uint32_t[createInfo.queueFamilyIndexCount];

  if(createInfo.pQueueFamilyIndices== nullptr) {
    /// revert
    createInfo.queueFamilyIndexCount= oldNr;
    createInfo.pQueueFamilyIndices= oldFamilies;
    oldFamilies= nullptr;
    goto Exit;
  }

  // copy old families
  if(oldNr)
    for(uint32_t a= 0; a< oldNr; a++)
      ((uint32_t *)createInfo.pQueueFamilyIndices)[a]= oldFamilies[a];

  ((uint32_t *)createInfo.pQueueFamilyIndices)[createInfo.queueFamilyIndexCount- 1]= in_f;
  
Exit:
  if(oldFamilies) delete[] oldFamilies;
}

// same as addFamily, but sets all families in one go
void VkoImage::setFamilies(uint32_t in_nrFamilies, const uint32_t *in_families) {
  if(createInfo.pQueueFamilyIndices) {
    delete[] createInfo.pQueueFamilyIndices;
    createInfo.pQueueFamilyIndices= nullptr;
  }
  
  createInfo.pQueueFamilyIndices= new uint32_t[in_nrFamilies];
  createInfo.queueFamilyIndexCount= in_nrFamilies;
  for(uint32_t a= 0; a< in_nrFamilies; a++)
    ((uint32_t *)createInfo.pQueueFamilyIndices)[a]= in_families[a];

}

void VkoImage::setInitialLayout(VkImageLayout in_initial) {
  // https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap11.html#VkImageLayout
  createInfo.initialLayout= in_initial;
}




///======---------------------------------///
// BUILD ==================--------------- //
///======---------------------------------///

bool VkoImage::build() {
  bool ret= false;

  createInfo.pNext= pNext.VkImageCreateInfo;

  if(!_vko->errorCheck(_vko->CreateImage(*_vko, &createInfo, *_vko, &image), __FUNCTION__": Vulkan image create failed"))
    goto Exit;

  _vko->GetImageMemoryRequirements(*_vko, *this, &memRequirements);

  ret= true; // success

Exit:
  return ret;
}












