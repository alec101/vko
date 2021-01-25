#include "../include/vkObject.h"



///===============///
// vkoMEMORY class //
///===============///

VkoMemory::VkoMemory(vkObject *in_parent): _vko(in_parent) {
  memory= 0;

  // init pointers

  _exportInfo=    nullptr;
  _exportWin32=   nullptr;
  _importFd=      nullptr;
  _importWin32=   nullptr;
  _flagsInfo=     nullptr;
  _dedicatedInfo= nullptr;

  delData();      // sets default values too
}


VkoMemory::~VkoMemory() {
  if(memory) destroy();
  delData();
}


void VkoMemory::delData() {
  if(_exportWin32) {
    if(_exportWin32->pAttributes) delete   _exportWin32->pAttributes;
    if(_exportWin32->name)        delete[] _exportWin32->name;
    delete _exportWin32; _exportWin32= nullptr;
  }

  if(_importWin32) {
    if(_importWin32->name)        delete[] _importWin32->name;
    delete _importWin32; _importWin32= nullptr;
  }

  if(_exportInfo)    { delete _exportInfo;    _exportInfo=    nullptr; }
  if(_importFd)      { delete _importFd;      _importFd=      nullptr; }
  if(_flagsInfo)     { delete _flagsInfo;     _flagsInfo=     nullptr; }
  if(_dedicatedInfo) { delete _dedicatedInfo; _dedicatedInfo= nullptr; }

  pNext.delData();

  // DEFAULT values

  size= 0;
  typeIndex= 0;
  typeFlags= VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT;
}


// VkoMemory CONFIGURATION


bool VkoMemory::configure(VkDeviceSize in_size, VkMemoryPropertyFlags in_required, VkMemoryPropertyFlags in_prefered, uint32_t in_typeBits) {
  _vko->clearError();
  uint32_t found= _vko->findMemory(in_typeBits, in_required| in_prefered);
  if(found== ~0u)
    found= _vko->findMemory(in_typeBits, in_required);

  if(found== ~0u) { _vko->errorText= "VkoMemory::configure(): Could not find required Vulkan physical device memory"; return false; }

  // found

  size= in_size;
  typeIndex= found;
  typeFlags= _vko->info.memProp().memoryTypes[found].propertyFlags;
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
  const void **_pNext= &allocInfo.pNext;

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkExportMemoryAllocateInfo
  if(_exportInfo!= nullptr) {
    *_pNext= _exportInfo;
    _exportInfo->pNext= nullptr;
    _pNext= &_exportInfo->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkExportMemoryWin32HandleInfoKHR
  if(_exportWin32!= nullptr) {
    *_pNext= _exportWin32;
    _exportWin32->pNext= nullptr;
    _pNext= &_exportWin32->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkImportMemoryFdInfoKHR
  if(_importFd!= nullptr) {
    *_pNext= _importFd;
    _importFd->pNext= nullptr;
    _pNext= &_importFd->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkImportMemoryWin32HandleInfoKHR
  if(_importWin32!= nullptr) {
    *_pNext= _importWin32;
    _importWin32->pNext= nullptr;
    _pNext= &_importWin32->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryAllocateFlagsInfo
  if(_flagsInfo!= nullptr) {
    *_pNext= _flagsInfo;
    _flagsInfo->pNext= nullptr;
    _pNext= &_flagsInfo->pNext;
  }

  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryDedicatedAllocateInfo
  if(_dedicatedInfo!= nullptr) {
    *_pNext= _dedicatedInfo;
    _dedicatedInfo->pNext= nullptr;
    _pNext= &_dedicatedInfo->pNext;
  }

  *_pNext= pNext.VkMemoryAllocateInfo;  // final chain in pNext is the custom one, if it is used

  allocInfo.allocationSize= size;
  allocInfo.memoryTypeIndex= typeIndex;
  
  if(!_vko->errorCheck(_vko->AllocateMemory(*_vko, &allocInfo, *_vko, &memory),
    "VkoMemory::build(): Failed to build Vulkan memory block."))
    goto Exit;

  // success
  ret= true;

Exit:
  return ret;
}



void VkoMemory::destroy() {
  if(memory) {
    if(_vko) _vko->FreeMemory(*_vko, memory, *_vko);
    memory= 0;
  }
}







