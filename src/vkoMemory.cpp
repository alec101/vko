#include "../include/vkObject.h"

/*

DESIGNING STUFF, MEMORY FRAGMENTATION, MEMORY ALOCATION THINKING
================================================================

- for any blocks of memory that need alocation / dealocation and are the same size, the segList is the answer, and there won't be any fragmentation
- textures would use seglists, for sure
- there are multiple texture sizes tho, so you'd need mutliple seglists, where would you put them in memory...
- the fixed stuff could be at start
- there could be no difference between allocationg at the end and backwards, and allocating after the fixed stuff
  so there will be 2 fixed points, after fixed stuff and at the end.

  or a system that would know where to fit other textures, when there are gaps, due you know the slot sizes...
  so slots would appear at certain points hmm

  -maybe a system with slots, the minimum slot would be 128x128 texture? and you go forward from that. a 512x512 would need 16 slots
   a 1024x1024 texture would need 16x16 slots... hmmm

   or, for each texture size, you'd have a vkMemory, fixed number, and deal if there's not enough by clearing some older stuff?

   i think the latter method would be better

   M1: 1 contigious vkMemory for all texture sizes, all sizes will have a fixed chunk from that vkMemory
       
   M2: 1 vkMemory for each texture size

   M3: 1 contigious vkMemory for all texture sizes, each texture size will have "slots". the lowest level slot would be 128x128 or higher
       a 512x512 texture would occupy 16x16 slots if i compute right
       but you'd need a complex and clever system to know where slots are free
       so you'd have a list of slots for the whole memory. not that bad, and not that hard to implement
       you could have a rule that big textures would be alocated at the end
       and 128x128 + 256x256 would be alocated at start?

       atlases ...
       yeah...

       i dono what to say... vulkan is already 3 years in and nothing is changing
       so nvidia cannot even benefit from vulkan atm, there's like 3% improvements
       on the amd cards you see huge speeds, from all the multiple threadings


       to be or not to be, this is the question
       it... seems they wanna go forward with it... i dono , but it's extreem fuzy if they continue vulkan or not
       cuz nobody gives a damn about it atm, i mean, the amount of time you have to invest only to make it work is just too big

       i'm already 4-5 months into this
       in this time i could've started the darn game, and i am pretty sure something nice would've been done by now
       this vulkan thing is really starting to drag me down



       OK SECOND DAY OF THINKING:
       - everything must be perfectly ordered, so the need for a defragmentor disapears
       - the memory will be extreem good managed to the byte
       - the problem will be vertex attribute buffers. they will vary in length, but they are way smaller, at least.
       - can you make block of vertex attribute buffers? then what? you'd still have to put other buffer objects in these blocks and still need defrag
       - ofc you can make slots and know how many slots the buffer would take, but still there will be wasted space appearing between buffers

        you need to eliminate the wasted space between buffers, that's the problem
        can you do this without a defragmentor?
        could this problem not exist with a good(perfect) buffer ordering?

        neah, there's no way, you need defragmenter

        soo... a defragmenter too
        this is going too far


        ===================================================
        the main question is:
        would you not need a defragmenter in a system that adds and substracts vertex attrib blocks?
        ===================================================

        so im not sure that vulkan would limit this
        i am at the point of creating all these objects easy anyway, so i dono what would opengl gain me atm


        i think i should start doing it. i went too far anyway
       

       vvvvvvvvvvvvvv
        so... the defragger would copy 1 object per frame, maybe? depends how many objects there are
        so you lock your buffer, and copy 1-2-3 per frame, unlock
        ^^^^^^^^^^^^^^^^^^^^^^
        you'd have more than 1 deffraging buffer, probly i will have this functionality in the vkoBuffer object, with a buffer that can hold the copied thing
        maybe the lock could happen only per item, somehow, not the whole buffer, i dono



        but i am really thinking all the way here
        the memory/buffers are next


*/




///======================///
// VkoMEMORYMANAGER class //
///======================///

VkoMemoryManager::VkoMemoryManager() {
  _parent= nullptr;
  memProp.memoryHeapCount= 0;
  memProp.memoryTypeCount= 0;

  // makeme;
}


VkoMemoryManager::~VkoMemoryManager() {
  // makeme;
}


void VkoMemoryManager::init() {
  // mem allocation https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#memory
  // pipeline barriers https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap6.html#synchronization-pipeline-barriers
  // mem bariers https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap6.html#synchronization-memory-barriers

  // device memory https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#memory-device
  
  _parent->GetPhysicalDeviceMemoryProperties(*_parent, &memProp);
}












/*
// Find a memory in `memoryTypeBitsRequirement` that includes all of `requiredProperties`
int32_t findProperties(const VkPhysicalDeviceMemoryProperties* pMemoryProperties, uint32_t memoryTypeBitsRequirement, VkMemoryPropertyFlags requiredProperties) {
  const uint32_t memoryCount = pMemoryProperties->memoryTypeCount;
  for (uint32_t a = 0; a < memoryCount; ++a) {

    const uint32_t memoryTypeBits = (1 << a);
    const bool isRequiredMemoryType = memoryTypeBitsRequirement & memoryTypeBits;

    const VkMemoryPropertyFlags properties = pMemoryProperties->memoryTypes[a].propertyFlags;
    const bool hasRequiredProperties = (properties & requiredProperties) == requiredProperties;

    if (isRequiredMemoryType && hasRequiredProperties)
      return static_cast<int32_t>(a);
  }

    // failed to find memory type
    return -1;
}
*/

uint32_t VkoMemoryManager::findMemory(uint32_t in_memTypeBits, VkMemoryPropertyFlags in_prop) {
  // mem type https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryPropertyFlagBits
  for(uint32_t a= 0; a< memProp.memoryTypeCount; a++)
    if((in_memTypeBits& (1 << a)) && ((memProp.memoryTypes[a].propertyFlags& in_prop)== in_prop))
      return a;

  return ~0u;
}


VkoMemory *VkoMemoryManager::addMemoryBlock() {
  VkoMemory *p= nullptr;
  p= new VkoMemory;
  p->_parent= this;
  p->_vko= _parent;
  memoryBlocks.add(p);
  return p;
}









///===============///
// vkoMEMORY class //
///===============///

VkoMemory::VkoMemory() {
  _parent= nullptr;
  memory= nullptr;
  size= 0;
  typeIndex= 0;
  typeFlags= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;

  // export/import

  _exportInfo=    nullptr;
  _exportWin32=   nullptr;
  _importFd=      nullptr;
  _importWin32=   nullptr;
  _flagsInfo=     nullptr;
  _dedicatedInfo= nullptr;
}


VkoMemory::~VkoMemory() {
  
  if(_exportWin32) {
    if(_exportWin32->pAttributes) delete   _exportWin32->pAttributes;
    if(_exportWin32->name)        delete[] _exportWin32->name;
    delete _exportWin32;
  }

  if(_importWin32) {
    if(_importWin32->name)        delete[] _importWin32->name;
    delete _importWin32;
  }

  if(_exportInfo)    delete _exportInfo;
  if(_importFd)      delete _importFd;
  if(_flagsInfo)     delete _flagsInfo;
  if(_dedicatedInfo) delete _dedicatedInfo;
}



// VkoMemory CONFIGURATION


bool VkoMemory::configure(VkDeviceSize in_size, VkMemoryPropertyFlags in_required, VkMemoryPropertyFlags in_prefered, uint32_t in_typeBits) {
  _vko->clearError();
  uint32_t found= _parent->findMemory(in_typeBits, in_required| in_prefered);
  if(found== ~0u)
    found= _parent->findMemory(in_typeBits, in_required);

  if(found== ~0u) { _vko->errorText= __FUNCTION__": Could not find required Vulkan physical device memory"; return false; }

  // found

  size= in_size;
  typeIndex= found;
  typeFlags= _parent->memProp.memoryTypes[found].propertyFlags;
  return true;
}



void VkoMemory::addVkExportMemoryAllocateInfo(VkExternalMemoryHandleTypeFlags handleTypes) {
  if(_exportInfo== nullptr)
    _exportInfo= new VkExportMemoryAllocateInfo;
  _exportInfo->sType= VK_STRUCTURE_TYPE_EXPORT_MEMORY_ALLOCATE_INFO;
  _exportInfo->handleTypes= handleTypes;
}


void VkoMemory::addVkExportMemoryWin32HandleInfoKHR(const SECURITY_ATTRIBUTES* pAttributes, DWORD dwAccess, LPCWSTR name) {
  if(_exportWin32== nullptr)
    _exportWin32= new VkExportMemoryWin32HandleInfoKHR;
  else {
    if(_exportWin32->pAttributes) delete _exportWin32->pAttributes; _exportWin32->pAttributes= nullptr;
    if(_exportWin32->name) delete[] _exportWin32->name; _exportWin32->name= nullptr;
  }

  _exportWin32->sType= VK_STRUCTURE_TYPE_EXPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
  _exportWin32->pAttributes= new SECURITY_ATTRIBUTES;
  ((SECURITY_ATTRIBUTES *)_exportWin32->pAttributes)->bInheritHandle= pAttributes->bInheritHandle;
  ((SECURITY_ATTRIBUTES *)_exportWin32->pAttributes)->lpSecurityDescriptor= pAttributes->lpSecurityDescriptor;
  ((SECURITY_ATTRIBUTES *)_exportWin32->pAttributes)->nLength= pAttributes->nLength;

  _exportWin32->dwAccess= dwAccess;
  _exportWin32->name= (LPCWSTR)new uint8_t[vkObject::_strlen16((char16_t *)name)];
  vkObject::_strcpy16((char16_t *)_exportWin32->name, (char16_t *)name);
}


void VkoMemory::addVkImportMemoryFdInfoKHR(VkExternalMemoryHandleTypeFlagBits handleType, int fd) {
  if(_importFd== nullptr)
    _importFd= new VkImportMemoryFdInfoKHR;
  _importFd->sType= VK_STRUCTURE_TYPE_IMPORT_MEMORY_FD_INFO_KHR;
  _importFd->handleType= handleType;
  _importFd->fd= fd;
}


void VkoMemory::addVkImportMemoryWin32HandleInfoKHR(VkExternalMemoryHandleTypeFlagBits handleType, HANDLE handle, LPCWSTR name) {
  if(_importWin32== nullptr)
    _importWin32= new VkImportMemoryWin32HandleInfoKHR;
  else {
    if(_importWin32->name) delete[] _importWin32->name; _importWin32->name= nullptr;
  }
  _importWin32->sType= VK_STRUCTURE_TYPE_IMPORT_MEMORY_WIN32_HANDLE_INFO_KHR;
  _importWin32->handleType= handleType;
  _importWin32->handle= handle;

  _importWin32->name= (LPCWSTR)new uint8_t[vkObject::_strlen16((char16_t *)name)];
  vkObject::_strcpy16((char16_t *)_importWin32->name, (char16_t *)name);
}


void VkoMemory::addVkMemoryAllocateFlagsInfo(VkMemoryAllocateFlags flags, uint32_t deviceMask) {
  if(_flagsInfo== nullptr)
    _flagsInfo= new VkMemoryAllocateFlagsInfo;
  _flagsInfo->sType= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_FLAGS_INFO;
  _flagsInfo->flags= flags;
  _flagsInfo->deviceMask= deviceMask;
}


void VkoMemory::addVkMemoryDedicatedAllocateInfo(VkImage image, VkBuffer buffer) {
  if(_dedicatedInfo== nullptr)
    _dedicatedInfo= new VkMemoryDedicatedAllocateInfo;
  _dedicatedInfo->sType= VK_STRUCTURE_TYPE_MEMORY_DEDICATED_ALLOCATE_INFO;
  _dedicatedInfo->image= image;
  _dedicatedInfo->buffer= buffer;
}





// VkoMemory BUILD

bool VkoMemory::build() {
  /* from the specs:
  Allocations returned by vkAllocateMemory are guaranteed to meet any alignment requirement of the implementation.
  For example, if an implementation requires 128 byte alignment for images and 64 byte alignment for buffers,
  the device memory returned through this mechanism would be 128-byte aligned.
  This ensures that applications can correctly suballocate objects of different types
  (with potentially different alignment requirements) in the same memory object.
  */

  bool ret= false;
  
  VkMemoryAllocateInfo allocInfo;   // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryAllocateInfo
  allocInfo.sType= VK_STRUCTURE_TYPE_MEMORY_ALLOCATE_INFO;
  allocInfo.pNext= nullptr;
  const void **pNext= &allocInfo.pNext;

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkExportMemoryAllocateInfo
  if(_exportInfo!= nullptr) {
    *pNext= _exportInfo;
    _exportInfo->pNext= nullptr;
    pNext= &_exportInfo->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkExportMemoryWin32HandleInfoKHR
  if(_exportWin32!= nullptr) {
    *pNext= _exportWin32;
    _exportWin32->pNext= nullptr;
    pNext= &_exportWin32->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkImportMemoryFdInfoKHR
  if(_importFd!= nullptr) {
    *pNext= _importFd;
    _importFd->pNext= nullptr;
    pNext= &_importFd->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkImportMemoryWin32HandleInfoKHR
  if(_importWin32!= nullptr) {
    *pNext= _importWin32;
    _importWin32->pNext= nullptr;
    pNext= &_importWin32->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryAllocateFlagsInfo
  if(_flagsInfo!= nullptr) {
    *pNext= _flagsInfo;
    _flagsInfo->pNext= nullptr;
    pNext= &_flagsInfo->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryDedicatedAllocateInfo
  if(_dedicatedInfo!= nullptr) {
    *pNext= _dedicatedInfo;
    _dedicatedInfo->pNext= nullptr;
    pNext= &_dedicatedInfo->pNext;
  }

  allocInfo.allocationSize= size;
  allocInfo.memoryTypeIndex= typeIndex;
  
  if(!_vko->errorCheck(_vko->AllocateMemory(*_parent->_parent, &allocInfo, *_parent->_parent, &memory),
    __FUNCTION__": Failed to build Vulkan memory block."))
    goto Exit;

  // success
  ret= true;

Exit:
  return ret;
}











