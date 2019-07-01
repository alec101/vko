#pragma once

///==================///
// VkoSemaphore class //
///==================///

class VkoSemaphore: public chainData {
public:
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap6.html#synchronization-semaphores

  VkSemaphore semaphore;
  inline operator VkSemaphore() { return semaphore; }

  inline VkoSemaphore(): semaphore(null), _parent(null), _handleTypes(null), name(null) { dwAccess= 0, pAttributes.bInheritHandle= 0, pAttributes.lpSecurityDescriptor= 0, pAttributes.nLength= 0; }
  inline VkoSemaphore(vkObject *in_parent): VkoSemaphore() { _parent= in_parent; }
  inline ~VkoSemaphore() { if(name) delete[] name; }

  // must set, if not using constructor to set it
  // inline void setParent(vkObject *in_parent) { _parent= in_parent; }
  inline void addExport(VkExternalSemaphoreHandleTypeFlags in_handleTypes) { _handleTypes= in_handleTypes; }
  void addWin32Export(const SECURITY_ATTRIBUTES *in_pAttributes, DWORD in_dwAccess, LPCWSTR in_name);

  bool build();    // set everything then this func will build the semaphore
  void destroy();
  
private:
  // export info
  VkExternalSemaphoreHandleTypeFlags _handleTypes;
  // win32 additional export info
  SECURITY_ATTRIBUTES pAttributes;
  DWORD               dwAccess;
  LPCWSTR             name;

  vkObject *_parent;
  friend class vkObject;
};


























