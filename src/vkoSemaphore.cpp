#include "vkObject.h"






///==================///
// VkoSemaphore class //
///==================///

void VkoSemaphore::addWin32Export(const SECURITY_ATTRIBUTES *in_pAttributes, DWORD in_dwAccess, LPCWSTR in_name) {
  pAttributes= *in_pAttributes, dwAccess= in_dwAccess;
  if(name) delete[] name; name= null;

  int32 l= Str::strlen16((char16 *)in_name);
  if(l) {
    name= (LPCWSTR)new uint8[l];
    Str::memcpy((void *)name, in_name, l);
  }
}


bool VkoSemaphore::build() {
  bool ret= false;
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap6.html#synchronization-semaphores
  VkSemaphoreCreateInfo semInfo= { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, null, 0 };
  VkExportSemaphoreCreateInfo exportInfo; 
  VkExportSemaphoreWin32HandleInfoKHR win32ExportInfo;
  const void **pNext= &semInfo.pNext;
  
  if(semaphore!= null) destroy();

  if(_handleTypes!= 0) {
    *pNext= &exportInfo;
    exportInfo.sType= VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO;
    exportInfo.pNext= null;
    exportInfo.handleTypes= _handleTypes;
    pNext= &exportInfo.pNext;
  }

  if(dwAccess!= 0 || name || pAttributes.nLength || pAttributes.bInheritHandle || pAttributes.lpSecurityDescriptor|| pAttributes.nLength) {
    *pNext= &win32ExportInfo;
    win32ExportInfo.sType= VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
    win32ExportInfo.pNext= null;
    win32ExportInfo.dwAccess= dwAccess;
    win32ExportInfo.pAttributes= &pAttributes;
    win32ExportInfo.name= name;
    pNext= &win32ExportInfo.pNext;
  }

  VkResult res= _parent->vk->CreateSemaphore(_parent->device, &semInfo, _parent->memCallback, &semaphore);
  if(res!= VK_SUCCESS) {
    error.detail("vko semaphore create failed.", __FUNCTION__);
    error.vkPrint(res);
    goto Exit;
  }

  ret= true;

Exit:
  return ret;
}


void VkoSemaphore::destroy() {
  if(!_parent->device) return;
  if(semaphore)
    _parent->vk->DestroySemaphore(_parent->device, semaphore, _parent->memCallback);
  semaphore= null;
}



























