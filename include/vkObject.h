#pragma once

// configuration

// if this define exists, VKO will create all the global vulkan functions, linked by instance,
//   and the vkObject::glb pointer that can be changed to make global funcs call a specific device/vko
#define VKO_USE_GLOBAL_FUNCS 1

// includes stdio.h, prints various info on console - helps for info/debug
#define VKO_BE_CHATTY 1


//#include "util/typeShortcuts.h"
//#include "osinteraction.h"
#include <stdint.h>
#include "chainList.hpp"

#ifdef VKO_BE_CHATTY
#include <stdio.h>
#endif

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
//#include "../extlib/vulkan/vulkan.h"
#ifdef VKO_USE_VULKAN_INCLUDE_DIR
#include VKO_USE_VULKAN_INCLUDE_DIR
#else
#include "vulkan.h"
#endif

struct VkoPhysicalDevice;
class vkObject;

#include "vkoFuncs.h"
#include "vkoExt.h"

#include "vkoMemory.h"
#include "vkoBuffer.h"

#include "vkoSwapchain.h"
#include "vkoCommandPool.h"
//#include "vkoCommandBuffer.h"
#include "vkoShader.h"

#include "vkoSetLayout.h"
#include "vkoSet.h"
#include "vkoDescriptorPool.h"

#include "vkoRenderPass.h"
#include "vkoFramebuffer.h"

#include "vkoSampler.h"


class VkoSemaphore;
struct VkoQueue;
struct VkoFuncs;

class vkObject: public VkoFuncs {
public:

  // informational structure, physical devices are populated after the instance is created
  struct VkoInfo {
    uint32_t apiVersion; // [def:0] installed vulkan version; if it is 0, vulkan is not present on system. Use VK_VERSION_MAJOR, xx_MINOR, xx_PATCH, to extract
    static uint32_t nrPhysicalDevices;          // nr physical devices on system; populated after buildInstance() is called
    static VkoPhysicalDevice *physicalDevice;   // list with every phyical device on system; populated after buildInstance() is called

    static VkPhysicalDeviceMemoryProperties memProp;   // memory properties struct

    ~VkoInfo();
  } info;


  struct VkoConfiguration {

    // instance / application settings
    struct VkoVer { uint32_t major, minor, patch; } static versionRequest; // [def: 1, 1, 0] requested vulkan version; if you set appInfo::apiVersion directly, this is ignored
    static VkApplicationInfo appInfo;             // instanceInfo.pApplicationInfo points to this. if apiVersion is 0, version struct is used
    static VkInstanceCreateInfo *instanceInfo;    // [def:null] if left null, settings.vulkan.extensions struct is used to create VkInstanceCreateInfo struct, else create it as you wish and point this to it
    static VkInstance customInstance;             // [def:null] if you want to create your own instance, point this to the custom created instance.

    // device settings

    VkDeviceCreateInfo *deviceInfo;                   // [def:null] if left null, settings.vulkan.extensions struct / next settings are used to create VkDeviceCreateInfo struct, else create it as you wish and point this to it
    VkPhysicalDeviceFeatures *gpuFeatures;            // [def:null] !!! gpu features to enable. VKO will enable everything the GPU has, if this is left null. it is ADVISED to fill in this struct and point to it with this
    void addValidationLayer(const char *in_name) { parent->_addValidationLayer(in_name); }  // adds a validation layer

    int32_t queueRequestUniversal;                   // [def:1] request a number of queues that can do anything (graphics, compute, transfer). used if deviceInfo is NULL
    int32_t queueRequestGraphics;                    // [def:0] request a number of graphics VkQueues. used if deviceInfo is NULL
    int32_t queueRequestCompute;                     // [def:0] request a number of compute VkQueues. used if deviceInfo is NULL
    int32_t queueRequestTransfer;                    // [def:0] request a number of transfer VkQueues. used if deviceInfo is NULL
    bool queueRequestAll;                            // [def:false] request all avaible queues
    VkQueueFlagBits queueExtraFlagBits;              // [def:0] request VK_QUEUE_SPARSE_BINDING_BIT or VK_QUEUE_PROTECTED_BIT for queues if needed

    // instance & device extensions;
    // set the "enable" bool variable to true, to request enabling the extension.
    // enable every extension that is to be used. Avoid enabling extensions that are not used, due they will change the way vulkan works.
    VkoExtensions extensions;     // enable each extension from this OR, manually populate instanceInfo / deviceInfo

    // PNext struct is a tool to add to any .pNext create info struct extra structures/configurations/extensions
    // usage ex: object.pNext.VkInstanceCreateInfo= &yourChainOfExtraStructuresThatWillBeAddedToPnext;
    struct PNext {
      void *VkInstanceCreateInfo;
      void *VkDeviceCreateInfo;
      PNext(): VkInstanceCreateInfo(nullptr), VkDeviceCreateInfo(nullptr) {}
    } pNext;

  private:
    vkObject *parent;
    friend class vkObject;
  } cfg;


  static VkInstance instance;         // the instance; gets created when buildInstance() is called. Only one instance is needed for multiple vkObjects
  VkDevice device;                    // the device; gets created when build() is called.
  VkPhysicalDevice physicalDevice;    // use cfg.setPhysicalDevice to set it- 
  VkAllocationCallbacks *memCallback; // [def:null] memory allocation callback struct, you can use one or let it null

  uint32_t nrQueues;          // number of queues in queue array; gets populated after build() is called
  VkoQueue *queue;            // all requested queues from cfg::queueRequestXX;

  const char *errorText;      // if any of the functions fail, this var will hold a description why things failed
  VkResult result;            // the success/failure reported by Vulkan. if applicable.
  inline void clearError() { errorText= nullptr, result= VK_SUCCESS; }
  bool errorCheck(VkResult in_res, const char *in_errorText);

  inline operator VkDevice() { return device; }
  inline operator VkAllocationCallbacks*() { return memCallback; }
  inline operator VkInstance() { return instance; }
  inline operator VkPhysicalDevice() { return physicalDevice; }


  #ifdef VKO_USE_GLOBAL_FUNCS
  static VkoFuncs *glb;           // pointer to the instance-linked vulkan funcs. This can be changed to point to specific device-linked funcs.
  static VkoFuncs instanceLinked; // global instance-linked vulkan funcs. they have higher CPU usage
  #endif



  // build / destroy

  bool buildInstance();           // creates the unique instance. Setup what is needed in vkObject::cfg struct

  bool build();                   // creates the device. Setup what is needed in vkObject::cfg struct
  void destroy();                 // destroys all vulkan objects

  vkObject();
  ~vkObject();

  // useful funcs

  uint32_t findMemory(uint32_t memoryTypeBitsRequirement, VkMemoryPropertyFlags requiredProperties); //  https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryPropertyFlagBits




  // various objects creation
  ///========================

  struct Objects {
    chainList memories;             // [VkoMemory:              chainData] list with all created memory blocks
    chainList buffers;              // [VkoBuffer:              chainData] list with all created buffers
    chainList shaders;              // [VkoShader:              chainData] list with all created shaders
    chainList commandPools;         // [VkoCommands:            chainData] all created commands objects
    chainList descriptorPools;      // [VkoDescriptorSetPool:   chainData] all created descriptor pools
    chainList descriptorSetLayouts; // [VkoDescriptorSetLayout: chainData] all created descriptor set layouts
    chainList swapchains;           // [VkoSwapchain:           chainData] all created swapchains
    chainList renderPasses;         // [VkoRenderPass:          chainData] all created render pass objects
    chainList framebuffers;         // [VkoFramebuffer:         chainData] all created framebuffers
    chainList samplers;             // [VkoSampler:             chainData]
    chainList semaphores;           // [VkoSemaphore:           chainData]

    VkoMemory *addMemory();
    void addCustomMemory(VkoMemory *p) { memories.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delMemory(VkoMemory *out_mem);
    void delAllMemories();

    VkoBuffer *addBuffer();
    void addCustomBuffer(VkoBuffer *p) { buffers.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delBuffer(VkoBuffer *out_buffer);
    void delAllBuffers();

    VkoShader *addShader();
    void addCustomShader(VkoShader *p) { shaders.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delShader(VkoShader *out_shader);
    void delAllShaders();

    VkoCommandPool *addCommandPool(); 
    void addCustomCommandPool(VkoCommandPool *p) { commandPools.add((chainData *)p);} // alloc your own object, then call this to link it to VKO
    void delCommandPool(VkoCommandPool *out_cmdPool);
    void delAllCommandPools();

    VkoDescriptorPool *addDescriptorPool();
    void addCustomDescriptorPool(VkoDescriptorPool *p) { descriptorPools.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delDescriptorPool(VkoDescriptorPool *out_descPool);
    void delAllDescriptorPools();

    VkoDescriptorSetLayout *addDescriptorSetLayout();
    void addCustomDescriptorSetLayout(VkoDescriptorSetLayout *p) { descriptorSetLayouts.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delDescriptorSetLayout(VkoDescriptorSetLayout *out_layout);
    void delAllDescriptorSetLayouts();

    VkoSwapchain *addSwapchain();
    void addCustomSwapchain(VkoSwapchain *p) { swapchains.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delSwapchain(VkoSwapchain *out_swapchain);
    void delAllSwapchains();           // from specs: The surface must not be destroyed until after the swapchain is destroyed.

    VkoRenderPass *addRenderPass();
    void addCustomRenderPass(VkoRenderPass *p) { renderPasses.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delRenderPass(VkoRenderPass *out_renderPass);
    void delAllRenderPasses();

    VkoFramebuffer *addFramebuffer();
    void addCustomFramebuffer(VkoFramebuffer *p) { framebuffers.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delFramebuffer(VkoFramebuffer *out_framebuffer);
    void delAllFramebuffers();

    VkoSampler *addSampler();
    void addCustomSampler(VkoSampler *p) { samplers.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delSampler(VkoSampler *out_sampler);
    void delAllSamplers();

    VkoSemaphore *addSemaphore();
    void addCustomSemaphore(VkoSemaphore *p) { semaphores.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delSemaphore(VkoSemaphore *out_semaphore);
    void delAllSemaphores();

  private:
    vkObject *_vko;
    friend class vkObject;
  } objects;


private:
  static void *_vulkanLib;           // vulkan library linking

  

  void constructorLevelInit(); // TO BE OR NOT TO BE

  bool _createInstance();
  bool _createDevice(VkPhysicalDevice in_GPU, VkDevice *out_device, uint32_t *out_nrQueues, VkoQueue **out_queues);
  bool _getRequestedQueues(VkPhysicalDevice in_GPU, uint32_t *out_nrStructs, VkDeviceQueueCreateInfo **out_structs, uint32_t *out_nrQueues, VkoQueue **out_queues);
  void _populateVkQueue();
  

  //void _linkLibAndCriticalFuncs(VkoFuncs *in_f);
  void _linkLib();
  void _linkCriticalFuncs(VkoFuncs *in_f);
  void _linkInstanceFuncs(VkoFuncs *in_f, VkInstance in_i);
  void _linkDeviceFuncs(VkoFuncs *in_f, VkInstance in_i, VkDevice in_d);

  void _addValidationLayer(const char *);
  chainList _validationLayers;
  class _ValidationLayer: public chainData {
  public:
    const char *name;
    _ValidationLayer(): name(nullptr) {}
    ~_ValidationLayer() { if(name) delete[] name; }
  };

  void _populatePhysicalDeviceInfo();

  
  static void _memcpy(void *dst, const void *src, uint64_t n);  // copies 8 bytes at a time - 2x- 3x slower than Microsoft memcpy
  

  static uint32_t _strlen8(const char *x);
  static uint32_t _strlen16(const char16_t *s);

  static void _strcpy8(char *dst, const char *src);
  static void _strcpy16(char16_t *dst, const char16_t *src);

  static int32_t _strcmp8(const char *, const char *);

  static void _strCopy(char **out_dst, const char *src);        // deletes <dst> if not null, allocates <dst> then copyes <src> into <dst>


  friend class VkoSemaphore;
  friend class VkoShader;
  friend class VkoMemory;
  friend struct VkoExtensions;
}; // vkObject




#include "vkoSemaphore.h"
#include "vkoCommandBuffer.h"
inline void VkoSwapchain::queueShow(uint32_t in_surfaceIndex, VkQueue in_queue, VkSemaphore in_finishDrawing) { _presentInfo.pWaitSemaphores= &in_finishDrawing, _presentInfo.pImageIndices= &in_surfaceIndex; _vko->QueuePresentKHR(in_queue, &_presentInfo); };   // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkPresentInfoKHR



  struct VkoQueue {
    uint32_t family;
    uint32_t index;           // queue index in family
    VkQueueFlags typeFlags;
    VkQueue queue;
    inline operator VkQueue() { return queue; }
  };

  struct VkoPhysicalDevice {
    VkPhysicalDevice physicalDevice;
    VkPhysicalDeviceProperties prop;
  };


#include "vkoGlbFuncs.hpp"







