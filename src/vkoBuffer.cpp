#include "vko/include/vkObject.h"



///======================---------------------///
// buffer MANAGER object ===================== //
///======================---------------------///

VkoBufferManager::VkoBufferManager() {
  _parent= null;
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


VkoBuffer::VkoBuffer(): buffer(null), _parent(null) {
  _createInfo.sType= VK_STRUCTURE_TYPE_BUFFER_CREATE_INFO;
  _createInfo.pNext= null;
  _createInfo.flags= 0;

  _createInfo.size= 0;
  _createInfo.usage= VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT;
  _createInfo.sharingMode= VK_SHARING_MODE_EXCLUSIVE;

  _createInfo.queueFamilyIndexCount= 0;
  _createInfo.pQueueFamilyIndices= null;        // INIT 1

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
  if(_parent->_parent->device== null) return;
  if(buffer) {
    _parent->_parent->DestroyBuffer(_parent->_parent->device, buffer, _parent->_parent->memCallback);
    buffer= null;
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


void VkoBuffer::addFamily(uint32 in_f) {
  uint32 oldNr= _createInfo.queueFamilyIndexCount;
  uint32 *oldFamilies= (uint32 *)_createInfo.pQueueFamilyIndices;

  _createInfo.queueFamilyIndexCount++;
  _createInfo.pQueueFamilyIndices= null;
  _createInfo.pQueueFamilyIndices= new uint32[_createInfo.queueFamilyIndexCount];

  if(_createInfo.pQueueFamilyIndices== null) {
    /// revert
    _createInfo.queueFamilyIndexCount= oldNr;
    _createInfo.pQueueFamilyIndices= oldFamilies;
    oldFamilies= null;
    goto Exit;
  }

  // copy old families
  if(oldNr)
    for(uint32 a= 0; a< oldNr; a++) // ye, well, code 'analyzer' is utter crap. cannot follow simple var changes
    //for(uint32 a= 0; a< _createInfo.queueFamilyIndexCount- 1; a++)  // this1 works with no warnings lol
      ((uint32 *)_createInfo.pQueueFamilyIndices)[a]= oldFamilies[a];

  ((uint32 *)_createInfo.pQueueFamilyIndices)[_createInfo.queueFamilyIndexCount- 1]= in_f;
  
Exit:
  if(oldFamilies) delete[] oldFamilies;
}



// same as addFamily, but sets all families in one go
void VkoBuffer::setFamilies(uint32 in_nrFamilies, const uint32 *in_families) {
  if(_createInfo.pQueueFamilyIndices) {
    delete[] _createInfo.pQueueFamilyIndices;
    _createInfo.pQueueFamilyIndices= null;
  }
  
  _createInfo.pQueueFamilyIndices= new uint32[in_nrFamilies];
  _createInfo.queueFamilyIndexCount= in_nrFamilies;
  for(uint a= 0; a< in_nrFamilies; a++)
    ((uint32 *)_createInfo.pQueueFamilyIndices)[a]= in_families[a];

}






///======---------------------------------///
// BUILD ==================--------------- //
///======---------------------------------///

bool VkoBuffer::build() {
  bool ret= false;


  VkResult res= _parent->_parent->CreateBuffer(*_parent->_parent, &_createInfo, *_parent->_parent, &buffer);

  if(res!= VK_SUCCESS) {
    error.detail("Vulkan buffer create failed.", __FUNCTION__);
    error.vkPrint(res);
    goto Exit;
  }

  _parent->_parent->GetBufferMemoryRequirements(*_parent->_parent, *this, &memRequirements);

  continue all this.
    so basically errors are split into errorText and result (for vulkan result)
    everything should be easy from here on



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














