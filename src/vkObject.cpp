#include "../include/vkoPlatform.h"
#include "../include/vkObject.h"
#include <stdio.h>

/*
  TODO:

*/


vkObject::vkObject(): VkoFuncs() {
  objects._vko= this;

  memCallback= nullptr;
  device= nullptr;

  nrQueues= 0;
  queue= nullptr;              // INIT 1 - NOT DEALOCATED <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

  cfg.parent= this;
  cfg.extensions._vko= this;

  info.apiVersion= 0;
  info.memProp.memoryHeapCount= 0;
  info.memProp.memoryTypeCount= 0;

  _linkLib();
  _linkCriticalFuncs(this);
  cfg.extensions.populateAvailabilityInstance();
  if(instance()) {
    _linkInstanceFuncs(this, instance());
    _populatePhysicalDeviceInfo();
  }
  
  #ifdef VKO_USE_GLOBAL_FUNCS
  _linkCriticalFuncs(&instanceLinked());
  #endif
}



vkObject::~vkObject() {
  destroy();
}


void vkObject::destroy() {
  if(device)
    DeviceWaitIdle(device);

  objects.delAllShaders();
  objects.delAllCommandPools();
  objects.delAllSwapchains();
  objects.delAllRenderPasses();
  objects.delAllFramebuffers();
  objects.delAllDescriptorPools();
  objects.delAllDescriptorSetLayouts();
  objects.delAllBuffers();
  objects.delAllImages();
  objects.delAllSamplers();
  objects.delAllSemaphores();
  objects.delAllFences();
  objects.delAllMemories();

}


vkObject::VkoInfo::~VkoInfo() {
  if(*physicalDevice())
    delete[] *physicalDevice();
  *physicalDevice()= nullptr;
  nrPhysicalDevices()= 0; 
}


// until funcs

uint32_t vkObject::findMemory(uint32_t in_memTypeBits, VkMemoryPropertyFlags in_prop) {
  // mem type https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap10.html#VkMemoryPropertyFlagBits
  for(uint32_t a= 0; a< info.memProp.memoryTypeCount; a++)
    if((in_memTypeBits& (1 << a)) && ((info.memProp.memoryTypes[a].propertyFlags& in_prop)== in_prop))
      return a;

  return ~0u;
}




// VkoBuffer

VkoBuffer *vkObject::Objects::addBuffer() {
  VkoBuffer *p= new VkoBuffer(_vko);
  buffers.add(p);
  return p;
}

void vkObject::Objects::delBuffer(VkoBuffer *out_p) {
  out_p->destroy();
  buffers.del(out_p);
}

void vkObject::Objects::delAllBuffers() {
  while(buffers.first)
    delBuffer((VkoBuffer *)buffers.first);
}

// VkoImage

VkoImage *vkObject::Objects::addImage() {
  VkoImage *p= new VkoImage(_vko);
  images.add(p);
  return p;
}

void vkObject::Objects::delImage(VkoImage *out_p) {
  out_p->destroy();
  images.del(out_p);
}

void vkObject::Objects::delAllImages() {
  while(images.first)
    delImage((VkoImage *)images.first);
}

// VkoMemory

VkoMemory *vkObject::Objects::addMemory() {
  VkoMemory *p= new VkoMemory(_vko);
  memories.add(p);
  return p;
}

void vkObject::Objects::delMemory(VkoMemory *out_p) {
  out_p->destroy();
  memories.del(out_p);
}

void vkObject::Objects::delAllMemories() {
  while(memories.first)
    delMemory((VkoMemory *)memories.first);
}

// VkoShader

VkoShader *vkObject::Objects::addShader() {
  VkoShader *p= new VkoShader(_vko);
  shaders.add(p);
  return p;
}

void vkObject::Objects::delShader(VkoShader *out_p) {
  out_p->destroy();
  shaders.del(out_p);
}

void vkObject::Objects::delAllShaders() {
  while(shaders.first)
    delShader((VkoShader *)shaders.first);
}

// VkoSwapchain

VkoSwapchain *vkObject::Objects::addSwapchain() {
  VkoSwapchain *p= new VkoSwapchain(_vko);
  swapchains.add(p);
  return p;
}

void vkObject::Objects::delSwapchain(VkoSwapchain *out_p) {
  // from specs: The surface must not be destroyed until after the swapchain is destroyed.
  out_p->destroy();
  swapchains.del(out_p);
}

void vkObject::Objects::delAllSwapchains() {
  while(swapchains.first)
    delSwapchain((VkoSwapchain *)swapchains.first);
}


// VkoRenderpass

VkoRenderPass *vkObject::Objects::addRenderPass() {
  VkoRenderPass *p= new VkoRenderPass(_vko);
  renderPasses.add(p);
  return p;
}

void vkObject::Objects::delRenderPass(VkoRenderPass *out_p) {
  out_p->destroy();
  renderPasses.del(out_p);
}

void vkObject::Objects::delAllRenderPasses() {
  while(renderPasses.first)
    delRenderPass((VkoRenderPass *)renderPasses.first);
}

// frame buffers

VkoFramebuffer *vkObject::Objects::addFramebuffer() {
  VkoFramebuffer *p= new VkoFramebuffer(_vko);
  framebuffers.add(p);
  return p;
}

void vkObject::Objects::delFramebuffer(VkoFramebuffer *out_p) {
  out_p->destroy();
  framebuffers.del(out_p);
}

void vkObject::Objects::delAllFramebuffers() {
  while(framebuffers.first)
    delFramebuffer((VkoFramebuffer *)framebuffers.first);
}

// command pools

VkoCommandPool *vkObject::Objects::addCommandPool() {
  VkoCommandPool *p= new VkoCommandPool(_vko);
  commandPools.add(p);
  return p;
}

void vkObject::Objects::delCommandPool(VkoCommandPool *out_p) {
  out_p->destroy();
  commandPools.del(out_p);
}

void vkObject::Objects::delAllCommandPools() {
  while(commandPools.first)
    delCommandPool((VkoCommandPool *)commandPools.first);
}

// descriptor pools

VkoDescriptorPool *vkObject::Objects::addDescriptorPool() {
  VkoDescriptorPool *p= new VkoDescriptorPool(_vko);
  descriptorPools.add(p);
  return p;
}

void vkObject::Objects::delDescriptorPool(VkoDescriptorPool *out_p) {
  out_p->destroy();
  descriptorPools.del(out_p);
}

void vkObject::Objects::delAllDescriptorPools() {
  while(descriptorPools.first)
    delDescriptorPool((VkoDescriptorPool *)descriptorPools.first);
}

// dynamic descriptor pools

VkoDynamicSetPool *vkObject::Objects::addDynamicSetPool() {
  VkoDynamicSetPool *p= new VkoDynamicSetPool(_vko);
  dynamicSetPools.add(p);
  return p;
}

void vkObject::Objects::delDynamicSetPool(VkoDynamicSetPool *out_p) {
  out_p->destroy();
  dynamicSetPools.del(out_p);
}

void vkObject::Objects::delAllDynamicSetPools() {
  while(dynamicSetPools.first)
    delDynamicSetPool((VkoDynamicSetPool *)dynamicSetPools.first);
}


// descriptor set layouts

VkoDescriptorSetLayout *vkObject::Objects::addDescriptorSetLayout() {
  VkoDescriptorSetLayout *p= new VkoDescriptorSetLayout(_vko);
  descriptorSetLayouts.add(p);
  return p;
}

void vkObject::Objects::delDescriptorSetLayout(VkoDescriptorSetLayout *out_p) {
  out_p->destroy();
  descriptorSetLayouts.del(out_p);
}

void vkObject::Objects::delAllDescriptorSetLayouts() {
  while(descriptorSetLayouts.first)
    delDescriptorSetLayout((VkoDescriptorSetLayout *)descriptorSetLayouts.first);
}

// semaphores

VkoSemaphore *vkObject::Objects::addSemaphore() {
  VkoSemaphore *s= new VkoSemaphore(_vko);
  semaphores.add(s);
  return s;
}

void vkObject::Objects::delSemaphore(VkoSemaphore *out_p) {
  out_p->destroy();
  semaphores.del(out_p);
}

void vkObject::Objects::delAllSemaphores() {
  while(semaphores.first)
    delSemaphore((VkoSemaphore *)semaphores.first);
}

// fences

VkoFence *vkObject::Objects::addFence() {
  VkoFence *s= new VkoFence(_vko);
  fences.add(s);
  return s;
}

void vkObject::Objects::delFence(VkoFence *out_p) {
  out_p->destroy();
  fences.del(out_p);
}

void vkObject::Objects::delAllFences() {
  while(fences.first)
    delFence((VkoFence *)fences.first);
}

// samplers

VkoSampler *vkObject::Objects::addSampler() {
  VkoSampler *p= new VkoSampler(_vko);
  samplers.add(p);
  return p;
}

void vkObject::Objects::delSampler(VkoSampler *out_p) {
  out_p->destroy();
  samplers.del(out_p);
}

void vkObject::Objects::delAllSamplers() {
  while(samplers.first)
    delSampler((VkoSampler *)samplers.first);
}




















bool vkObject::_createInstance() {
  clearError();

  bool ret= false;
  bool allocated;
  VkInstanceCreateInfo instInfo;
  VkInstanceCreateInfo *iiToUse;

  // set the requested vulkan version
  if(cfg.appInfo().apiVersion== 0)
    cfg.appInfo().apiVersion= VK_MAKE_VERSION(cfg.versionRequest().major, cfg.versionRequest().minor, cfg.versionRequest().patch);

  // create the instance info here
  if(*cfg.instanceInfo()== nullptr) {

    instInfo.sType= VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    instInfo.pNext= cfg.pNext.VkInstanceCreateInfo;
    instInfo.flags= 0;
    instInfo.pApplicationInfo= &cfg.appInfo();

    /// enable requested layers
    instInfo.enabledLayerCount= _validationLayers.nrNodes;
    instInfo.ppEnabledLayerNames= nullptr;

    if(_validationLayers.nrNodes) {
      instInfo.ppEnabledLayerNames= new const char *[_validationLayers.nrNodes];
      uint32_t a= 0;
      for(_ValidationLayer *p= (_ValidationLayer *)_validationLayers.first; p; p= (_ValidationLayer *)p->next, a++)
        ((char **)instInfo.ppEnabledLayerNames)[a]= (char *)p->name;
    }

    /// populate extension list
    instInfo.enabledExtensionCount= 0;
    instInfo.ppEnabledExtensionNames= nullptr;
    cfg.extensions.createInstanceExtensionsStringArray((char ***)&instInfo.ppEnabledExtensionNames, &instInfo.enabledExtensionCount);

    iiToUse= &instInfo;
    allocated= true;

  // use provided custom instance info
  } else {
    iiToUse= *cfg.instanceInfo();
    allocated= false;
  }

  // create the instance
  result= CreateInstance(iiToUse, *this, &instance());
  if(result!= VK_SUCCESS) {
    errorText= "vkObject::_createInstance(): vkCreateInstance failed";
    goto Exit;
  }

  ret= true;

Exit:
  if(allocated) {
    if(instInfo.ppEnabledExtensionNames) {
      for(uint32_t a= 0; a< instInfo.enabledExtensionCount; a++)
        if(instInfo.ppEnabledExtensionNames[a])
          delete[] instInfo.ppEnabledExtensionNames[a];
      delete[] instInfo.ppEnabledExtensionNames;
    }

    if(instInfo.ppEnabledLayerNames)
      delete[] instInfo.ppEnabledLayerNames;
  }

  return ret;
}






bool vkObject::_createDevice(VkPhysicalDevice in_GPU, VkDevice *out_dev, uint32_t *out_nrQueues, VkoQueue **out_osiQueues) {
  if(instance()== nullptr) { errorText= "vkObject::_createDevice(): vkInstance is nullptr. no instance created? aborting."; return false; }
  bool ret= false;
  errorText= nullptr;

  VkDeviceCreateInfo dci;
  VkDeviceCreateInfo *dciToUse;
  VkPhysicalDeviceFeatures pdf;
  VkPhysicalDeviceFeatures *pdfToUse;
 
  cfg.extensions.populateAvailabilityDevice(*physicalDevice);

  // custom deviceInfo would be best, if not, one will be created, enabling everything
  if(cfg.deviceInfo== nullptr) {
    dci.sType= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    dci.pNext= cfg.pNext.VkDeviceCreateInfo;
    dci.flags= 0;
    dci.enabledLayerCount= 0;
    dci.ppEnabledLayerNames= nullptr;
  
    // enable custom GPU features - THIS IS A MUST, enabling all can create unnecesary lag
    if(cfg.gpuFeatures)
      pdfToUse= cfg.gpuFeatures;
    else {
      // enable all GPU features
      GetPhysicalDeviceFeatures(in_GPU, &pdf);
      pdfToUse= &pdf;
    }
    dci.pEnabledFeatures= pdfToUse;

    // queues
    if(!_getRequestedQueues(in_GPU, &dci.queueCreateInfoCount, (VkDeviceQueueCreateInfo **)&dci.pQueueCreateInfos, out_nrQueues, out_osiQueues))
      return false;
    
    /// device extensions
    cfg.extensions.createDeviceExtensionsStringArray((char ***)&dci.ppEnabledExtensionNames, &dci.enabledExtensionCount);

    dciToUse= &dci;
  } else
    dciToUse= cfg.deviceInfo;

  // create the device
  result= CreateDevice(in_GPU, dciToUse, memCallback, out_dev);
  if(result!= VK_SUCCESS) {
    errorText= "vkObject::_createDevice(): vkCreateDevice failed";
    *out_nrQueues= 0;
    delete[] *out_osiQueues;
  } else ret= true;


  if(dciToUse== &dci) {
    delete[] dci.pQueueCreateInfos[0].pQueuePriorities;
    delete[] dci.pQueueCreateInfos;
  }

  return ret;
}



bool vkObject::_getRequestedQueues(VkPhysicalDevice in_GPU, uint32_t *out_nrStructs, VkDeviceQueueCreateInfo **out_structs, uint32_t *out_nrQueues, VkoQueue **out_osiQueues) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#devsandqueues-queues
  clearError();

  #ifdef VKO_BE_CHATTY
  bool chatty= true;
  #endif

  bool found;
  uint32_t n;

  /// mem allocated tmp vars
  VkQueueFamilyProperties *qfp= nullptr;   // 1 delete here
  uint32_t *requested= nullptr;              // 2 delete here

  float *qp= nullptr;                      // 1 delete in _createDevice (or here if error)
                            // out_structs 2 delete in _createDevice
                            // out_osiQueues is handled by osiVkRenderer, deleted in destructor
  *out_nrStructs= 0;
  *out_structs= nullptr;
  *out_nrQueues= 0;
  *out_osiQueues= nullptr;
  
  /// get the number of queue families
  GetPhysicalDeviceQueueFamilyProperties(in_GPU, &n, nullptr);
  if(n== 0) { errorText= "vkObject::_getRequestedQueues(): Vulkan returns no queues"; goto Error; }

  qfp= new VkQueueFamilyProperties[n];
  
  /// get all queue families in an array
  GetPhysicalDeviceQueueFamilyProperties(in_GPU, &n, qfp);

  #ifdef VKO_BE_CHATTY
  if(chatty) {
    printf("Found %u Vulkan Queue families\n", n);
    for(uint32_t a= 0; a< n; a++) {
      printf(" -Family %u\n", a);
      printf("  %u queues\n", qfp[a].queueCount);
      printf("  Type: ");
      if(qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT)
        printf("[Graphics] ");
      if(qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT)
        printf("[Compute] ");
      if(qfp[a].queueFlags& VK_QUEUE_TRANSFER_BIT)
        printf("[Transfer] ");
      if(qfp[a].queueFlags& VK_QUEUE_SPARSE_BINDING_BIT)
        printf("[Sparse mem] ");
      if(qfp[a].queueFlags& VK_QUEUE_PROTECTED_BIT)
        printf("[Protected] ");
      printf("\n");
    }
  }
  #endif

  /// create requested struct. it will count how many queues are requested from each queue family, if any (requested from osi.settings)
  requested= new uint32_t[n];
  
  for(uint32_t a= 0; a< n; a++)
    requested[a]= 0;


  // universal queues (compute/graphics/transfer)
  if(cfg.queueRequestUniversal> 0) {

    for(uint32_t a= 0; a< n; a++)
      if((qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT) && (qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT)) {
        /// check for extra requested flags
        if(cfg.queueExtraFlagBits)
          if(!(qfp[a].queueFlags& cfg.queueExtraFlagBits))
            continue;

        // found
        requested[a]+= cfg.queueRequestUniversal;
        if(requested[a]> qfp[a].queueCount)
          requested[a]= qfp[a].queueCount;
      }

  } /// if requested universal


  // graphics queues (i think there's no way to have graphics without the others !!!!!!!)
  if(cfg.queueRequestGraphics> 0) {

    // search for graphics only queues (atm there's no such thing in the current drivers, but who knows)
    found= false;
    for(uint32_t a= 0; a< n; a++)
      if((qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT) && !(qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT)) {
        /// check for extra requested flags
        if(cfg.queueExtraFlagBits)
          if(!(qfp[a].queueFlags& cfg.queueExtraFlagBits))
            continue;

        // found
        found= true;
        requested[a]+= cfg.queueRequestGraphics;
        if(requested[a]> qfp[a].queueCount)
          requested[a]= qfp[a].queueCount;
      }

    // search for graphics& compute queues (universal)
    if(!found) {
      for(uint32_t a= 0; a< n; a++)
        if(qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT) {
          /// check for extra requested flags
          if(cfg.queueExtraFlagBits)
            if(!(qfp[a].queueFlags& cfg.queueExtraFlagBits))
              continue;

          // found
          requested[a]+= cfg.queueRequestGraphics;
          if(requested[a]> qfp[a].queueCount)
            requested[a]= qfp[a].queueCount;
        }
    }
  } /// if requested graphics only queues
  
  
  // compute queues
  if(cfg.queueRequestCompute> 0) {
    /// search for compute-only queues (AMD GPU's do have them it seems)
    found= false;
    for(uint32_t a= 0; a< n; a++)
      if((qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT) && !(qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT)) {
        /// check for extra requested flags
        if(cfg.queueRequestGraphics)
          if(!(qfp[a].queueFlags& cfg.queueExtraFlagBits))
            continue;

        // found
        found= true;
        requested[a]+= cfg.queueRequestCompute;
        if(requested[a]> qfp[a].queueCount)
          requested[a]= qfp[a].queueCount;
      }

    /// search for graphics& compute queues (universal)
    if(!found) {
      for(uint32_t a= 0; a< n; a++)
        if(qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT) {
          /// check for extra requested flags
          if(cfg.queueExtraFlagBits)
            if(!(qfp[a].queueFlags& cfg.queueExtraFlagBits))
              continue;

          // found
          requested[a]+= cfg.queueRequestCompute;
          if(requested[a]> qfp[a].queueCount)
            requested[a]= qfp[a].queueCount;
        }
    }
  } /// request compute queues


  // transfer queues
  if(cfg.queueRequestTransfer> 0) {
    /// search for transfer-only queues first (both AMD and NVIDIA seem to have it nowadays)
    found= false;

    for(uint32_t a= 0; a< n; a++)
      if((qfp[a].queueFlags& VK_QUEUE_TRANSFER_BIT) && (!(qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT)) && (!(qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT))) {
        /// check for extra requested flags
        if(cfg.queueExtraFlagBits)
          if(!(qfp[a].queueFlags& cfg.queueExtraFlagBits))
            continue;

        // found
        found= true;
        requested[a]+= cfg.queueRequestTransfer;
        if(requested[a]> qfp[a].queueCount)
          requested[a]= qfp[a].queueCount;
      }

    /// search for universal queues
    if(!found) {
      for(uint32_t a= 0; a< n; a++)
        if((qfp[a].queueFlags& VK_QUEUE_TRANSFER_BIT) || (qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT)) { // graphics queues have capacity for transfer for sure, and it's not requested to put the transfer bit anymore
          /// check for extra requested flags
          if(cfg.queueExtraFlagBits)
            if(!(qfp[a].queueFlags& cfg.queueExtraFlagBits))
              continue;

          // found
          requested[a]+= cfg.queueRequestTransfer;
          if(requested[a]> qfp[a].queueCount)
            requested[a]= qfp[a].queueCount;
        }
    }

  } /// request transfer queues


  /// count how many queues will be created in total
  for(uint32_t a= 0; a< n; a++)
    (*out_nrQueues)+= requested[a];
  if(*out_nrQueues== 0) { errorText= "Found zero vulkan queues that match any requested"; goto Error; }


  /// queue priorities array - gonna be all 1.0f
  qp= new float[*out_nrQueues];
  for(uint32_t a= 0; a< *out_nrQueues; a++)
    qp[a]= 1.0f;

  /// osiQueues - the renderer stored queue data
  *out_osiQueues= new VkoQueue[*out_nrQueues];
  
  /// count how many structs will be returned
  for(uint32_t a= 0; a< n; a++)
    if(requested[a]> 0)
      (*out_nrStructs)++;
  
  /// populate the returned structures
  *out_structs= new VkDeviceQueueCreateInfo[*out_nrStructs];

  /// a= family, b= loop thru out_structs, c= loop thru osiQueues, d= loop thru family
  for(uint32_t a= 0, b= 0, c= 0; a< n; a++)
    if(requested[a]> 0) {
      (*out_structs)[b].sType= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      (*out_structs)[b].pNext= nullptr;
      if(cfg.queueExtraFlagBits& VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT)
        (*out_structs)[b].flags= VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;
      else
        (*out_structs)[b].flags= 0;
      (*out_structs)[b].queueFamilyIndex= a;
      (*out_structs)[b].queueCount= requested[a];
      (*out_structs)[b].pQueuePriorities= qp;
      b++;

      /// populate out_osiQueues
      for(uint32_t d= 0; d< requested[a]; d++) {
        (*out_osiQueues)[c].family= a;
        (*out_osiQueues)[c].index= d;
        (*out_osiQueues)[c].typeFlags= qfp[a].queueFlags;
        (*out_osiQueues)[c].queue= nullptr;
        c++;
      } /// loop thru family
    } /// requested in this family


  // success
  if(qfp) delete[] qfp;
  if(requested) delete[] requested;

  return true;

Error:
  *out_nrStructs= 0;
  *out_nrQueues= 0;
  if(*out_osiQueues) delete[] *out_osiQueues;
  if(*out_structs) delete[] *out_structs;
  if(qfp) delete[] qfp;
  if(requested) delete[] requested;
  if(qp) delete[] qp;
  
  return false;
}


void vkObject::_populateVkQueue() {
  if((GetDeviceQueue== nullptr) || (nrQueues== 0)) return;
  for(uint32_t a= 0; a< nrQueues; a++)
    GetDeviceQueue(device, queue[a].family, queue[a].index, &queue[a].queue);
}


void vkObject::_addValidationLayer(const char *in_name) {
  _ValidationLayer *p= new _ValidationLayer;
  _strCopy((char **)&p->name, in_name);
  _validationLayers.add(p);
}


void vkObject::_populatePhysicalDeviceInfo() {
  if(*info.physicalDevice()) return;     // populate only once

  uint32_t npd= 0;
  VkPhysicalDevice *pd= nullptr;

  /// number of physical devices on system
  EnumeratePhysicalDevices(instance(), &npd, nullptr);
  if(npd== 0) return;
  info.nrPhysicalDevices()= npd;

  /// list with all VkPhysicalDevices
  pd= new VkPhysicalDevice[npd];
  EnumeratePhysicalDevices(instance(), &npd, pd);

  /// populate VkoPhysicalDevices
  if(npd) {
    *info.physicalDevice()= new VkoPhysicalDevice[npd];

    for(uint32_t a= 0; a< npd; a++) {
      (*info.physicalDevice())[a].physicalDevice= pd[a];
      GetPhysicalDeviceProperties(pd[a], &((*info.physicalDevice())[a]).prop);
    }
  }

  if(pd) delete[] pd;
}








///==============///
// BUILD instance //
///==============///

bool vkObject::buildInstance() {
  clearError();

  if(CreateInstance== nullptr) {
    errorText= "vkObject::buildInstance(): Vulkan Critical funcs not linked (no link to the library?). Aborting";
    return false;
  }

  // instance

  if(instance()== nullptr) {
    if(cfg.customInstance())
      instance()= cfg.customInstance();
    else
      if(_createInstance()== false)
        return false;
  }
  
  // aquire all instance functions

  _linkInstanceFuncs(this, instance());
  _populatePhysicalDeviceInfo();

  #ifdef VKO_USE_GLOBAL_FUNCS
  _linkInstanceFuncs(&instanceLinked(), instance());
  #endif

  return true;    // success
}






///============///
// BUILD device //
///============///

bool vkObject::build() {
  clearError();

  if(!_createDevice(*physicalDevice, &device, &nrQueues, &queue))
    return false;

  _linkDeviceFuncs(this, instance(), *this);

  // memory information
  GetPhysicalDeviceMemoryProperties(*this, &info.memProp);

  _populateVkQueue();

  #ifdef VKO_USE_GLOBAL_FUNCS
  _linkDeviceFuncs(&instanceLinked(), instance(), nullptr);
  #endif
  return true; // success
}










bool vkObject::errorCheck(VkResult in_res, const char *in_text) {
  result= in_res;
  if(in_res!= VK_SUCCESS) {
    errorText= in_text;
    return false;
  }
  errorText= nullptr;
  return true;
}




// util funcs

void vkObject::_memcpy(void *dst, const void *src, uint64_t n) {
  if(dst< src) {
      
    uint64_t *p1= (uint64_t *)dst, *p2= (uint64_t *)src;
    while(n>= 8)                /// 8 bytes at a time copy
      *p1++= *p2++, n-= 8;

    uint8_t *p3= (uint8_t *)p1, *p4= (uint8_t *)p2;
    while(n)                    /// rest of bytes 1 by 1 (max 7)
      *p3++= *p4++, n--;

  } else {
    uint64_t *p1= (uint64_t *)((uint8_t *)dst+ n), *p2= (uint64_t *)((uint8_t *)src+ n);
    while(n>= 8)                /// 8 bytes at a time copy
      *--p1= *--p2, n-= 8;

    uint8_t *p3= (uint8_t *)p1, *p4= (uint8_t *)p2;
    while(n)                    /// rest of bytes 1 by 1 (max 7)
      *--p3= *--p4, n--;
  }
}

/// returns utf-8 string length in BYTES (includes str terminator)
uint32_t vkObject::_strlen8(const char *s) {
  if(!s) return 0;
  uint8_t *p= (uint8_t *)s;
  while(*p++);
  return (int32_t)(p- (uint8_t *)s);
}


/// returns utf-16 string length in BYTES (includes str terminator)
uint32_t vkObject::_strlen16(const char16_t *s) {
  if(!s) return 0;
  uint16_t *p= (uint16_t *)s;
  while(*p++);
  return (int32_t)((uint8_t *)p- (uint8_t *)s);
}



/// copies src to dest (both utf-8 array strings
void vkObject::_strcpy8(char *dst, const char *src) {
  uint8_t *p1= (uint8_t *)dst, *p2= (uint8_t *)src;

  while(*p2)
    *p1++= *p2++;

  *p1= 0;
}


void vkObject::_strcpy16(char16_t *dst, const char16_t *src) {
  uint16_t *p1= (uint16_t *)dst, *p2= (uint16_t *)src;
  while(*p2)
    *p1++= *p2++;
  *p1= 0;  /// terminator
}


int32_t vkObject::_strcmp8(const char *s1, const char *s2) {
  /// if both are NULL, then there's no difference
  if(s2== nullptr) {
    if(s1== nullptr) return 0;
    else             return 1;
  }
  if(s1== nullptr) return -1;

  uint8_t *p1= (uint8_t *)s1, *p2= (uint8_t *)s2;

  /// pass thru each character to check for differences
  while(*p1 && *p2)
    if(*p1 != *p2)
      return -1;
    else p1++, p2++;

  if(*p1) return 1;   /// still stuff in str1, strings not the same
  if(*p2) return -1;  /// still stuff in str2, strings not the same

  return 0;           // reached this point, there is no difference
}


// deletes <dst> if not nullptr, allocates <dst> then copyes <src> into <dst>
void vkObject::_strCopy(char **out_dst, const char *in_src) {
  if(*out_dst)
    delete[] *out_dst;
  *out_dst= nullptr;

  if(in_src== nullptr)
    return;

  *out_dst= (char *)new uint8_t[_strlen8(in_src)];
  _strcpy8(*out_dst, in_src);
}












