#pragma once

// configuration

// if this define exists, VKO will create all the global vulkan functions, linked by instance,
//   and the vkObject::glb pointer that can be changed to make global funcs call a specific device/vko
#define VKO_USE_GLOBAL_FUNCS 1

// prints various info on console - helps for info/debug
#if !defined NDEBUG
#define VKO_BE_CHATTY 1
#endif

#if defined _WIN32 && !defined _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

//#include <stdio.h>
#include <stdint.h>
#include "chainList.hpp"


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


/*  WIP, trying to get rid of <windows.h>-type of headers
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
*/



#define VK_NO_PROTOTYPES 1

#ifdef VKO_USE_VULKAN_INCLUDE_DIR
#include VKO_USE_VULKAN_INCLUDE_DIR
#else
#include "vulkan.h"
//#include "../extlib/vulkan/vulkan.h"
#endif

struct VkoPhysicalDevice;
class vkObject;

#include "vkoFuncs.h"
#include "vkoExt.h"

#include "vkoMemory.h"
#include "vkoBuffer.h"
#include "vkoImage.h"

#include "vkoSwapchain.h"
#include "vkoCommandPool.h"
//#include "vkoCommandBuffer.h"
#include "vkoShader.h"

#include "vkoSetLayout.h"
//#include "vkoSet.h"
#include "vkoDescriptorPool.h"
#include "vkoDynamicSet.h"

#include "vkoRenderPass.h"
#include "vkoFramebuffer.h"

#include "vkoSampler.h"


class VkoSemaphore;
class VkoFence;
//struct VkoQueue;
struct VkoFuncs;

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
  inline operator VkPhysicalDevice() { return physicalDevice; }
};


class vkObject: public VkoFuncs {
public:

  // informational structure, physical devices are populated after the instance is created
  struct VkoInfo {
    uint32_t apiVersion; // [def:0] installed vulkan version; if it is 0, vulkan is not present on system. Use VK_VERSION_MAJOR, xx_MINOR, xx_PATCH, to extract

    // nr physical devices on system; populated after buildInstance() is called
    inline static uint32_t &nrPhysicalDevices()               { static uint32_t n= 0;                      return n; }
    // list with every phyical device on system; populated after buildInstance() is called
    inline static VkoPhysicalDevice **physicalDevice()        { static VkoPhysicalDevice *pd= nullptr;     return &pd; } 
    // memory properties struct
    VkPhysicalDeviceMemoryProperties memProp;         // memory properties, tied to current device/vkObject

    ~VkoInfo();
  } info;


  struct VkoConfiguration {

    // instance / application settings
    
    // [def: 1, 1, 0] requested vulkan version; if you set appInfo::apiVersion directly, this is ignored
    struct VkoVer { uint32_t major, minor, patch; };
    inline static VkoVer &versionRequest() { static VkoVer v= {1, 1, 0 }; return v; }

    // instanceInfo.pApplicationInfo points to this. if apiVersion is 0, version struct is used
    inline static VkApplicationInfo &appInfo() { static VkApplicationInfo _appInfo= { VK_STRUCTURE_TYPE_APPLICATION_INFO, nullptr, 0, 0, 0, 0 }; return _appInfo; }

    // [def:null] if left null, settings.vulkan.extensions struct is used to create VkInstanceCreateInfo struct, else create it as you wish and point this to it
    inline static VkInstanceCreateInfo **instanceInfo() { static VkInstanceCreateInfo *_instanceInfo= nullptr; return &_instanceInfo; }

    // [def:null] if you want to create your own instance, point this to the custom created instance.
    inline static VkInstance &customInstance() { static VkInstance _customInstance= 0; return _customInstance; }


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

  // the instance; gets created when buildInstance() is called. Only one instance is needed for multiple vkObjects
  inline static VkInstance &instance() { static VkInstance _i= nullptr; return _i; }
  VkDevice device;                    // the device; gets created when build() is called.
  VkoPhysicalDevice *physicalDevice;  // use cfg.setPhysicalDevice to set it- 
  VkAllocationCallbacks *memCallback; // [def:null] memory allocation callback struct, you can use one or let it null

  uint32_t nrQueues;          // number of queues in queue array; gets populated after build() is called
  VkoQueue *queue;            // all requested queues from cfg::queueRequestXX;

  const char *errorText;      // if any of the functions fail, this var will hold a description why things failed
  VkResult result;            // the success/failure reported by Vulkan. if applicable.
  inline void clearError() { errorText= nullptr, result= VK_SUCCESS; }
  bool errorCheck(VkResult in_res, const char *in_errorText);

  inline operator VkDevice() { return device; }
  inline operator VkAllocationCallbacks*() { return memCallback; }
  inline operator VkInstance() { return instance(); }
  inline operator VkPhysicalDevice() { return physicalDevice->physicalDevice; }


  #ifdef VKO_USE_GLOBAL_FUNCS
  // pointer to the instance-linked vulkan funcs. This can be changed to point to specific device-linked funcs.
  inline static VkoFuncs **glb()           { static VkoFuncs *_glb= &instanceLinked();  return &_glb; }
  // global instance-linked vulkan funcs. they have higher CPU usage
  inline static VkoFuncs &instanceLinked() { static VkoFuncs _i;                        return _i; }
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
    chainList images;               // [VkoImage:               chainData] list with all created images
    chainList shaders;              // [VkoShader:              chainData] list with all created shaders
    chainList commandPools;         // [VkoCommands:            chainData] all created commands objects
    chainList descriptorPools;      // [VkoDescriptorSetPool:   chainData] all created descriptor pools
    chainList descriptorSetLayouts; // [VkoDescriptorSetLayout: chainData] all created descriptor set layouts
    chainList swapchains;           // [VkoSwapchain:           chainData] all created swapchains
    chainList renderPasses;         // [VkoRenderPass:          chainData] all created render pass objects
    chainList framebuffers;         // [VkoFramebuffer:         chainData] all created framebuffers
    chainList samplers;             // [VkoSampler:             chainData]
    chainList semaphores;           // [VkoSemaphore:           chainData]
    chainList fences;               // [VkoFence:               chainData] all created fences
    chainList dynamicSetPools;      // [VkoDynamicSetPool:      chainData] all created dynamic descriptor pools

    VkoMemory *addMemory();
    void addCustomMemory(VkoMemory *p) { memories.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delMemory(VkoMemory *out_mem);
    void delAllMemories();

    VkoBuffer *addBuffer();
    void addCustomBuffer(VkoBuffer *p) { buffers.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delBuffer(VkoBuffer *out_buffer);
    void delAllBuffers();

    VkoImage *addImage();
    void addCustomImage(VkoImage *p) { images.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delImage(VkoImage *out_image);
    void delAllImages();

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


    VkoDynamicSetPool *addDynamicSetPool();
    void addCustomDynamicSetPool(VkoDynamicSetPool *p) { dynamicSetPools.add((chainData *)p); }
    void delDynamicSetPool(VkoDynamicSetPool *out_pool);
    void delAllDynamicSetPools();

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

    VkoFence *addFence();
    void addCustomFence(VkoFence *p) { fences.add((chainData *)p); } // alloc your own object, then call this to link it to VKO
    void delFence(VkoFence *out_fence);
    void delAllFences();



  private:
    vkObject *_vko;
    friend class vkObject;
  } objects;


private:
  inline static void **_vulkanLib() { static void *p= nullptr; return &p; } // vulkan library linking

  

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

  

  static void _memcpy(void *dst, const void *src, uint64_t n);  // copies 8 bytes at a time
  
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
#include "vkoFence.h"
#include "vkoCommandBuffer.h"
//inline void VkoSwapchain::queueShow(uint32_t in_surfaceIndex, VkQueue in_queue, VkSemaphore in_finishDrawing) { _presentInfo.pWaitSemaphores= &in_finishDrawing, _presentInfo.pImageIndices= &in_surfaceIndex; _vko->QueuePresentKHR(in_queue, &_presentInfo); };   // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap29.html#VkPresentInfoKHR


void VkoCommandPool::reset(VkCommandPoolResetFlags in_flags) { _vko->ResetCommandPool(*_vko, commandPool, in_flags); }

#include "vkoGlbFuncs.hpp"







