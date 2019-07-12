#include "vko/include/vkObject.h"



///======================---------------------///
// buffer MANAGER object ===================== //
///======================---------------------///

VkoBufferManager::VkoBufferManager() {
  _parent= nullptr;
}


VkoBufferManager::~VkoBufferManager() {

}





VkoBuffer *VkoBufferManager::addBuffer() {
  VkoBuffer *p= new VkoBuffer;
  p->_parent= this;
  list.add(p);
  return p;
}



///==============------------------///
// BUFFER object ================== //
///==============------------------///


VkoBuffer::VkoBuffer(): buffer(nullptr), _parent(nullptr) {
  _createInfo.sType= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  _createInfo.pNext= nullptr;
  _createInfo.flags= 0;

  _createInfo.size= 0;
  _createInfo.usage= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  _createInfo.sharingMode= VK_SHARING_MODE_EXCLUSIVE;

  _createInfo.queueFamilyIndexCount= 0;
  _createInfo.pQueueFamilyIndices= nullptr;        // INIT 1

  memRequirements.alignment= 0;
  memRequirements.memoryTypeBits= 0;
  memRequirements.size= 0;

  offset= 0;
}


VkoBuffer::~VkoBuffer() {
  if(_createInfo.pQueueFamilyIndices)
    delete[] _createInfo.pQueueFamilyIndices;   // DEALLOC 1
}


void VkoBuffer::destroy() {
  if(_parent->_parent->device== nullptr) return;
  if(buffer) {
    _parent->_parent->DestroyBuffer(_parent->_parent->device, buffer, _parent->_parent->memCallback);
    buffer= nullptr;
  }
}


// settings

void VkoBuffer::setSize(uint32_t in_size) {
  _createInfo.size= in_size;
}


void VkoBuffer::setFlags(VkBufferCreateFlagBits in_flags) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap11.html#VkBufferCreateFlagBits
  _createInfo.flags= in_flags;
}


void VkoBuffer::setUsage(VkBufferUsageFlagBits in_usage) {
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

  if(!_parent->_parent->errorCheck(_parent->_parent->CreateBuffer(*_parent->_parent, &_createInfo, *_parent->_parent, &buffer), __FUNCTION__": Vulkan buffer create failed"))
    goto Exit;

  _parent->_parent->GetBufferMemoryRequirements(*_parent->_parent, *this, &memRequirements);

  ret= true; // success

Exit:
  return ret;
}





///=================///
// memory management //
///=================///


bool VkoBuffer::allocMem() {
   

  // WOULD BE ONLY THIS FUNC?
  
  //_parent->vk->BindBufferMemory( );
  
  return false;

  // could possibly create chainlists in the VkoMemory objects, so know the buffers/images allocated from it
  // could possibly create chainlists in the vkobject, or a bufferManager object
}














