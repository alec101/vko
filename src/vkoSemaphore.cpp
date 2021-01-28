#include "../include/vkObject.h"


///==================///
// VkoSemaphore class //
///==================///


VkoSemaphore::VkoSemaphore(vkObject *in_parent): semaphore(0), _vko(in_parent) {
  //name= nullptr;                                // INIT 1
  
  delData();
}


void VkoSemaphore::delData() {
  // dealocs
  //if(name) { delete[] name; name= nullptr; }    // DEALOC 1

  pNext.delData();

  stages= 0,
  _handleTypes= 0;
  //dwAccess= 0,
  //pAttributes.bInheritHandle= 0,
  //pAttributes.lpSecurityDescriptor= 0,
  //pAttributes.nLength= 0;
}


void VkoSemaphore::destroy() {
  if(semaphore) {
    if(_vko->device) _vko->DestroySemaphore(*_vko, semaphore, *_vko);
    semaphore= 0;
  }
}





/*
void VkoSemaphore::addWin32Export(const SECURITY_ATTRIBUTES *in_pAttributes, DWORD in_dwAccess, LPCWSTR in_name) {
  pAttributes= *in_pAttributes, dwAccess= in_dwAccess;
  if(name) delete[] name; name= nullptr;

  int32_t l= vkObject::_strlen16((char16_t *)in_name);
  if(l) {
    name= (LPCWSTR)new uint8_t[l];                    // ALLOC 1
    vkObject::_memcpy((void *)name, in_name, l);
  }
}
*/

bool VkoSemaphore::build() {
  bool ret= false;
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap6.html#synchronization-semaphores
  VkSemaphoreCreateInfo semInfo= { VK_STRUCTURE_TYPE_SEMAPHORE_CREATE_INFO, nullptr, 0 };
  VkExportSemaphoreCreateInfo exportInfo; 
  //VkExportSemaphoreWin32HandleInfoKHR win32ExportInfo;
  const void **_pNext= &semInfo.pNext;
  
  if(semaphore!= NULL) destroy();

  if(_handleTypes!= 0) {
    *_pNext= &exportInfo;
    exportInfo.sType= VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_CREATE_INFO;
    exportInfo.pNext= nullptr;
    exportInfo.handleTypes= _handleTypes;
    _pNext= &exportInfo.pNext;
  }
  /*
  if(dwAccess!= 0 || name || pAttributes.nLength || pAttributes.bInheritHandle || pAttributes.lpSecurityDescriptor|| pAttributes.nLength) {
    *_pNext= &win32ExportInfo;
    win32ExportInfo.sType= VK_STRUCTURE_TYPE_EXPORT_SEMAPHORE_WIN32_HANDLE_INFO_KHR;
    win32ExportInfo.pNext= nullptr;
    win32ExportInfo.dwAccess= dwAccess;
    win32ExportInfo.pAttributes= &pAttributes;
    win32ExportInfo.name= name;
    _pNext= &win32ExportInfo.pNext;
  }
  */
  *_pNext= pNext.VkExportSemaphoreCreateInfo;   // final pnext is the custom one

  if(!_vko->errorCheck(_vko->CreateSemaphore(*_vko, &semInfo, *_vko, &semaphore),
    "VkoSemaphore::build(): vko semaphore create failed."))
    goto Exit;

  ret= true;

Exit:
  return ret;
}




