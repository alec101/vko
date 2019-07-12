#include "../include/vkObject.h"






///==================///
// VkoSemaphore class //
///==================///

void VkoSemaphore::addWin32Export(const SECURITY_ATTRIBUTES *in_pAttributes, DWORD in_dwAccess, LPCWSTR in_name) {
  pAttributes= *in_pAttributes, dwAccess= in_dwAccess;
  if(name) delete[] name; name= nullptr;

  int32_t l= vkObject::_strlen16((char16_t *)in_name);
  if(l) {
    name= (LPCWSTR)new uint8_t[l];
    vkObject::_memcpy((void *)name, in_name, l);
  }
}


bool VkoSemaphore::build() {
  bool ret= false;
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap6.html#synchronization-semaphores
  VkSemaphoreCreateInfo semInfo= { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, nullptr, 0 };
  VkExportSemaphoreCreateInfo exportInfo; 
  VkExportSemaphoreWin32HandleInfoKHR win32ExportInfo;
  const void **pNext= &semInfo.pNext;
  
  if(semaphore!= nullptr) destroy();

  if(_handleTypes!= 0) {
    *pNext= &exportInfo;
    exportInfo.sType= VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO;
    exportInfo.pNext= nullptr;
    exportInfo.handleTypes= _handleTypes;
    pNext= &exportInfo.pNext;
  }

  if(dwAccess!= 0 || name || pAttributes.nLength || pAttributes.bInheritHandle || pAttributes.lpSecurityDescriptor|| pAttributes.nLength) {
    *pNext= &win32ExportInfo;
    win32ExportInfo.sType= VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
    win32ExportInfo.pNext= nullptr;
    win32ExportInfo.dwAccess= dwAccess;
    win32ExportInfo.pAttributes= &pAttributes;
    win32ExportInfo.name= name;
    pNext= &win32ExportInfo.pNext;
  }

  if(!_parent->errorCheck(_parent->CreateSemaphore(_parent->device, &semInfo, _parent->memCallback, &semaphore),
    __FUNCTION__": vko semaphore create failed."))
    goto Exit;

  ret= true;

Exit:
  return ret;
}


void VkoSemaphore::destroy() {
  if(!_parent->device) return;
  if(semaphore)
    _parent->DestroySemaphore(_parent->device, semaphore, _parent->memCallback);
  semaphore= nullptr;
}



























