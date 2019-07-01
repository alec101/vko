#pragma once
//#include "osinteraction.h"
#include <stdint.h>
#include "util/typeShortcuts.h"
#ifndef _OS_TYPE
#define _OS_TYPE
#ifdef _WIN32
#define OS_WIN 1
#elif defined __linux__
#define OS_LINUX 1
#elif defined __APPLE__
#define OS_MAC 1
#endif
#endif


#ifdef OS_WIN
#define VK_USE_PLATFORM_WIN32_KHR 1
#endif
#ifdef OS_LINUX
//#define VK_USE_PLATFORM_WAYLAND_KHR 1   <<<<<<<<<< FUTURE?
//#define VK_USE_PLATFORM_XCB_KHR 1
#define VK_USE_PLATFORM_XLIB_KHR 1
#define VK_USE_PLATFORM_XLIB_XRANDR_EXT 1
#endif
#ifdef OS_MAC
#define VK_USE_PLATFORM_MACOS_MVK 1
#endif

#define VK_NO_PROTOTYPES 1
#include "../extlib/vulkan/vulkan.h"
//#include "vulkan.h"

class vkObject;

#include "vkoDevice.h"
#include "vkoFuncs.h"
#include "vkoExt.h"

#include "vkoMemory.h"
#include "vkoBuffer.h"

#include "vkoSwapchain.h"
#include "vkoCommandPool.h"
#include "vkoShader.h"

#include "vkoSet.h"
#include "vkoDescriptor.h"
#include "vkoDescriptorManager.h"

#include "vkoRenderPass.h"
#include "vkoFramebuffer.h"



class VkoSemaphore;
struct VkoQueue;


class vkObject /*: public _osiVkFuncs    THESE ARE IN VKR.......*/ {
public:


  struct VkoConfiguration {
    void addValidationLayer(const char *);








  private:
    vkObject *parent;
    friend class vkObject;
  } cfg;


  //Ix *parent;                   // parent Ix engine
  //osiVkRenderer *vkr;           // osi renderer tied to this ix engine
  //_osiVkFuncs *vk;              // renderer's direct vulkan device funcs

  VkDevice device;              // the device (vkr->vkDevice)
  VkAllocationCallbacks *memCallback;

  inline operator VkDevice() { return device; }
  inline operator VkAllocationCallbacks*() { return memCallback; }

  VkoMemoryManager memory;
  VkoBufferManager buffers;

  const char *errorText;        // if any of the functions fail, this var will hold a description why things failed


  static VkoFuncs *glb;           // pointer to the instance-linked vulkan funcs. This can be changed to point to a specific device-linked funcs.
  static VkoFuncs instanceLinked; // instance-linked vulkan funcs. they have higher CPU usage




  chainList shaders;            // list with all created shaders
  
  // Commands object - handles pools, alocates primary and secondary command buffers

  VkoCommandPool *addCommandPool(); 
  chainList commandPoolList;      // [VkoCommands: chainData] all created commands objects
  void delCommandPools();

  // Descriptor Manager - handles the descriptor pool and creates descriptors and sets

  VkoDescriptorManager *addDescriptorManager();
  chainList descriptorManagerList; // [VkoDescriptorManager: chainData] all created descriptor managers
  void delDescriptorManagers();

  // swap chain
  
  VkoSwapchain *addSwapchain();
  chainList swapchainList;        // [VkoSwapchain: chainData] all created swapchains
  void delSwapchains();           // from specs: The surface must not be destroyed until after the swapchain is destroyed.

  // render pass chainlist
  
  VkoRenderPass *addRenderPass();
  chainList renderPassList;       // [VkoRenderPass: chainData] all created render pass objects
  void delRenderPasses();

  // frame buffer

  VkoFramebuffer *addFramebuffer();
  chainList framebuffersList;     // [Framebuffer: chainData] all created framebuffers
  void delFramebuffers();

  // shader handling

  template <class T>
  inline void createShader(T **out_shader) {
    *out_shader= new T;
    if(*out_shader== null) { error.alloc(__FUNCTION__); return; }
    ((vkoShader *)(*out_shader))->parent= this;
    shaders.add(*out_shader);
  }
  inline void delShader(vkoShader *in_s) { shaders.del(in_s); }




  VkoSemaphore *addSemaphore();




  void init(const osiRenderer *); // init after the device is created
  void close();                   // releases pools / everything, prepares for object destruction, devices should be still alive


  vkObject();
private:
  static void *_vulkanLib;           // vulkan library linking
  chainList _VkoSemaphores;
  friend class VkoSemaphore;


  static bool _createDevice(VkPhysicalDevice in_GPU, VkDevice *out_device, uint32_t *out_nrQueues, VkoQueue **out_queues);
  static bool _getRequestedQueues(VkPhysicalDevice in_GPU, uint32_t *out_nrStructs, VkDeviceQueueCreateInfo **out_structs, uint32_t *out_nrQueues, VkoQueue **out_osiQueues);
  static void _populateVkQueue(osiVkRenderer *);
  
  static void _linkLibAndCriticalFuncs(VkoFuncs *in_f);
  static void _linkInstanceFuncs(VkoFuncs *in_f, VkInstance in_i);
  static void _linkDeviceFuncs(VkoFuncs *in_f, VkInstance in_i, VkDevice in_d);

  
  
  class _ValidationLayer: public chainData {
  public:
    str8 name;
  };
  









}; // vkObject




#include "vkoSemaphore.h"
inline void VkoSwapchain::queueShow(uint32 in_surfaceIndex, VkQueue in_queue, VkSemaphore in_finishDrawing) { _showInfo.pWaitSemaphores= &in_finishDrawing, _showInfo.pImageIndices= &in_surfaceIndex; _parent->vk->QueuePresentKHR(in_queue, &_showInfo); };   // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkPresentInfoKHR



  struct VkoQueue {
    uint32_t family;
    uint32_t index;           // queue index in family
    VkQueueFlags typeFlags;
    VkQueue queue;
  };









