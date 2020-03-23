#pragma once

///==================///
// VkoSemaphore class //
///==================///

class VkoSemaphore: public chainData {
public:
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap6.html#synchronization-semaphores

  VkSemaphore semaphore;
  inline operator VkSemaphore() { return semaphore; }

  VkPipelineStageFlags stages; // [def:0] _IF_ applicable, what pipeline stages are affected by it

  inline void addExport(VkExternalSemaphoreHandleTypeFlags in_handleTypes) { _handleTypes= in_handleTypes; }
  void addWin32Export(const SECURITY_ATTRIBUTES *in_pAttributes, DWORD in_dwAccess, LPCWSTR in_name);

  struct PNext {
    void *VkExportSemaphoreCreateInfo;
    void delData() { VkExportSemaphoreCreateInfo= nullptr; }
  } pNext;


  bool build();    // set everything then this func will build the semaphore
  void destroy();
  inline bool rebuild() { destroy(); return build(); }

  VkoSemaphore(vkObject *in_parent);
  ~VkoSemaphore() { destroy(); delData(); }
  void delData();

private:
  // export info
  VkExternalSemaphoreHandleTypeFlags _handleTypes;
  // win32 additional export info
  SECURITY_ATTRIBUTES pAttributes;
  DWORD               dwAccess;
  LPCWSTR             name;

  vkObject *_vko;
  friend class vkObject;
};








