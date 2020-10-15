#include "../include/vkObject.h"




///==============------------------///
// BUFFER object ================== //
///==============------------------///


VkoBuffer::VkoBuffer(vkObject *in_parent): _vko(in_parent) {
  buffer= 0;

  _createInfo.pQueueFamilyIndices= nullptr;        // INIT 1

  delData();
}


VkoBuffer::~VkoBuffer() {
  delData();
}


void VkoBuffer::delData() {
  if(buffer) destroy();
  offset= 0;
  size= 0;

  pNext.delData();

  memRequirements.alignment= 0;
  memRequirements.memoryTypeBits= 0;
  memRequirements.size= 0;

  _createInfo.sType= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  _createInfo.pNext= nullptr;
  _createInfo.flags= 0;

  _createInfo.size= 0;
  _createInfo.usage= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  _createInfo.sharingMode= VK_SHARING_MODE_EXCLUSIVE;
  
  _createInfo.queueFamilyIndexCount= 0;
  if(_createInfo.pQueueFamilyIndices) {
    delete[] _createInfo.pQueueFamilyIndices;   // DEALLOC 1
    _createInfo.pQueueFamilyIndices= nullptr;
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

void VkoBuffer::setSize(VkDeviceSize in_size, VkDeviceSize in_offset) {
  size= in_size;
  offset= in_offset;
  _createInfo.size= in_size;
}


void VkoBuffer::setFlags(VkBufferCreateFlagBits in_flags) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferCreateFlagBits
  _createInfo.flags= in_flags;
}


void VkoBuffer::setUsage(VkBufferUsageFlags in_usage) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferUsageFlagBits
  _createInfo.usage= in_usage;
}


void VkoBuffer::setSharingMode(VkSharingMode in_sharing) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkSharingMode
  _createInfo.sharingMode= in_sharing;
}


void VkoBuffer::addFamily(uint32_t in_f) {
  uint32_t oldNr= _createInfo.queueFamilyIndexCount;
  uint32_t *oldFamilies= (uint32_t *)_createInfo.pQueueFamilyIndices;

  _createInfo.queueFamilyIndexCount++;
  _createInfo.pQueueFamilyIndices= nullptr;
  _createInfo.pQueueFamilyIndices= new uint32_t[_createInfo.queueFamilyIndexCount];

  if(_createInfo.pQueueFamilyIndices== nullptr) {
    /// revert
    _createInfo.queueFamilyIndexCount= oldNr;
    _createInfo.pQueueFamilyIndices= oldFamilies;
    oldFamilies= nullptr;
    goto Exit;
  }

  // copy old families
  if(oldNr)
    for(uint32_t a= 0; a< oldNr; a++) // ye, well, code 'analyzer' is utter crap. cannot follow simple var changes
    //for(uint32_t a= 0; a< _createInfo.queueFamilyIndexCount- 1; a++)  // this1 works with no warnings lol
      ((uint32_t *)_createInfo.pQueueFamilyIndices)[a]= oldFamilies[a];

  ((uint32_t *)_createInfo.pQueueFamilyIndices)[_createInfo.queueFamilyIndexCount- 1]= in_f;
  
Exit:
  if(oldFamilies) delete[] oldFamilies;
}



// same as addFamily, but sets all families in one go
void VkoBuffer::setFamilies(uint32_t in_nrFamilies, const uint32_t *in_families) {
  if(_createInfo.pQueueFamilyIndices) {
    delete[] _createInfo.pQueueFamilyIndices;
    _createInfo.pQueueFamilyIndices= nullptr;
  }
  
  _createInfo.pQueueFamilyIndices= new uint32_t[in_nrFamilies];
  _createInfo.queueFamilyIndexCount= in_nrFamilies;
  for(uint32_t a= 0; a< in_nrFamilies; a++)
    ((uint32_t *)_createInfo.pQueueFamilyIndices)[a]= in_families[a];

}






///======---------------------------------///
// BUILD ==================--------------- //
///======---------------------------------///

bool VkoBuffer::build() {
  bool ret= false;

  _createInfo.pNext= pNext.VkBufferCreateInfo;

  if(!_vko->errorCheck(_vko->CreateBuffer(*_vko, &_createInfo, *_vko, &buffer), __FUNCTION__": Vulkan buffer create failed"))
    goto Exit;

  _vko->GetBufferMemoryRequirements(*_vko, *this, &memRequirements);

  ret= true; // success

Exit:
  return ret;
}












