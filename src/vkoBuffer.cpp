#include "../include/vkObject.h"


///==============------------------///
// BUFFER object ================== //
///==============------------------///


VkoBuffer::VkoBuffer(vkObject *in_parent): _vko(in_parent) {
  buffer= 0;

  createInfo.pQueueFamilyIndices= nullptr;        // INIT 1

  delData();
}


VkoBuffer::~VkoBuffer() {
  delData();
}


void VkoBuffer::delData() {
  if(buffer) destroy();
  offset= 0;

  memRequirements.alignment= 0;
  memRequirements.memoryTypeBits= 0;
  memRequirements.size= 0;

  createInfo.sType= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  createInfo.pNext= nullptr;
  createInfo.flags= 0;

  createInfo.size= 0;
  createInfo.usage= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  createInfo.sharingMode= VK_SHARING_MODE_EXCLUSIVE;
  
  createInfo.queueFamilyIndexCount= 0;
  if(createInfo.pQueueFamilyIndices) {
    delete[] createInfo.pQueueFamilyIndices;   // DEALLOC 1
    createInfo.pQueueFamilyIndices= nullptr;
  }
}


void VkoBuffer::destroy() {
  if(buffer) {
    if(_vko)
      if(_vko->device)
        _vko->DestroyBuffer(*_vko, buffer, *_vko);
    buffer= 0;
  }
}


// settings

void VkoBuffer::cfgSize(VkDeviceSize in_size, VkDeviceSize in_offset) {
  //size= in_size;
  offset= in_offset;
  createInfo.size= in_size;
}


void VkoBuffer::cfgFlags(VkBufferCreateFlagBits in_flags) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferCreateFlagBits
  createInfo.flags= in_flags;
}


void VkoBuffer::cfgUsage(VkBufferUsageFlags in_usage) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferUsageFlagBits
  createInfo.usage= in_usage;
}


void VkoBuffer::cfgSharingMode(VkSharingMode in_sharing) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkSharingMode
  createInfo.sharingMode= in_sharing;
}


void VkoBuffer::cfgAddFamily(uint32_t in_f) {
  uint32_t oldNr= createInfo.queueFamilyIndexCount;
  uint32_t *oldFamilies= (uint32_t *)createInfo.pQueueFamilyIndices;

  createInfo.queueFamilyIndexCount++;
  createInfo.pQueueFamilyIndices= nullptr;
  createInfo.pQueueFamilyIndices= new uint32_t[createInfo.queueFamilyIndexCount];

  // copy old families
  if(oldNr)
    for(uint32_t a= 0; a< oldNr; a++) // ye, well, code 'analyzer' is utter crap. cannot follow simple var changes
    //for(uint32_t a= 0; a< createInfo.queueFamilyIndexCount- 1; a++)  // this1 works with no warnings lol
      ((uint32_t *)createInfo.pQueueFamilyIndices)[a]= oldFamilies[a];

  ((uint32_t *)createInfo.pQueueFamilyIndices)[createInfo.queueFamilyIndexCount- 1]= in_f;
  
  if(oldFamilies) delete[] oldFamilies;
}



// same as addFamily, but sets all families in one go
void VkoBuffer::cfgFamilies(uint32_t in_nrFamilies, const uint32_t *in_families) {
  if(createInfo.pQueueFamilyIndices) {
    delete[] createInfo.pQueueFamilyIndices;
    createInfo.pQueueFamilyIndices= nullptr;
  }
  
  createInfo.pQueueFamilyIndices= new uint32_t[in_nrFamilies];
  createInfo.queueFamilyIndexCount= in_nrFamilies;
  for(uint32_t a= 0; a< in_nrFamilies; a++)
    ((uint32_t *)createInfo.pQueueFamilyIndices)[a]= in_families[a];
}






///======---------------------------------///
// BUILD ==================--------------- //
///======---------------------------------///

bool VkoBuffer::build() {
  if(!_vko->errorCheck(_vko->CreateBuffer(*_vko, &createInfo, *_vko, &buffer), "VkoBuffer::build(): Vulkan buffer create failed"))
    return false;

  _vko->GetBufferMemoryRequirements(*_vko, *this, &memRequirements);

  return true;
}












