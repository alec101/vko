//#define OSI_USE_OPENGL_EXOTIC_EXT 1
//#include "osinteraction.h"
//#include "ix/ix.h"




#include "util/typeShortcuts.h"






#include "ix/vko/vkObject.h"
//#include "ix/GFX/ixvk.h"


  /*

  TODO:
  -PRIORITY specialized descriptor for textures
  -PRIORITY specialized descriptor for buffers of any kind
  -VkoTexture ? VkoBuffer? in any case a base descriptor class i think, is needed.



  -VkoCommandPool must be extended into VkoCommands object.
    it must incorporate ONE pool/
    it must be able to create many primary buffers
    it must be able to create many secondary buffers
    when it's built, you should just have handy vars for everything command-buffer/pool related

  -VkoMemory object must handle everything memory - alloc / dealloc required
    -i don't think it should have a build func, it should be created on vkObject::init()

  


  designing stuff:


  i think... vko::pNext.a= point to your specific extension
           vko::pNext.b= point to your specific extension
           vko::pNext.c= point to your specific extension
           vko::pNext.d= point to your specific extension

  and this should handle all new extensions, for example
  if not, just add new funcs
    but im thinking new funcs for KHR extensions imho...




  Command Pools:
  - vk->TrimCommandPool(device, commandPool, 0);
    Trimming may be an expensive operation, and should not be called frequently.
    Trimming should be treated as a way to relieve memory pressure after application-known points
    when there exists enough unused memory that the cost of trimming is “worth” it.

  - vk->ResetCommandPool(device, commandPool, VK_COMMAND_POOL_RESET_RELEASE_RESOURCES_BIT); // that flag will release all memory
    Resetting the command pool will remove all allocated memory for command buffers. all recording buffers will be marked invalid
  

  Swap Chain:
  - the swapchain is an extension that has to be enabled, unless i'm gonna do with these imageViews and manually draw them,
      that will probly be a magnitude slower, unless i know the optimal way to show for every OS

  Descriptor Pools:
    -the free func is optional, and must be treated with care, can create fragmentation problems.
       i am thinking whatever is freed, must be alocated with the same block size
       if you use only alloc + reset, it is guaranteed to work.

    -also, descriptor pools can be created on the fly, they are not really tied to anything

  */




VkoFuncs *vkoGlb= null;



vkObject::vkObject() /*: parent(in_parent) */ {
  //vkr= null;
  //vk= null;

  memCallback= null;
  device= null;

  memory._parent= this;
  buffers._parent= this;


  cfg.parent= this;
  glb= &instanceLinked;
}




void vkObject::init(const osiRenderer *in_r) {
  if(in_r->type!= 1) return;
  vkr= (osiVkRenderer *)in_r;
  vk= &vkr->vk;

  device= vkr->vkDevice;
  memory.init();
}



void vkObject::close() {
  if(device== null) return;

  // SHADERS >>> parent->shaders.delData();

  delCommandPools();
  delDescriptorManagers();
  delSwapchains();
  delRenderPasses();
  delFramebuffers();
  
  // VkoSemaphore destroy
  for(VkoSemaphore *p= (VkoSemaphore *)_VkoSemaphores.first; p; p= (VkoSemaphore *)p->next)
    p->destroy();



}






VkoSwapchain *vkObject::addSwapchain() {
  VkoSwapchain *p= new VkoSwapchain;
  if(p== null) { error.alloc(__FUNCTION__); return null; }




  p->_parent= this;

  swapchainList.add(p);
  return p;
}


void vkObject::delSwapchains() {
  // from specs: The surface must not be destroyed until after the swapchain is destroyed.
  for(VkoSwapchain *p= (VkoSwapchain *)swapchainList.first; p; p= (VkoSwapchain *)p->next)
    p->destroy();
}


VkoRenderPass *vkObject::addRenderPass() {
  VkoRenderPass *p= new VkoRenderPass;
  if(p== null) { error.alloc(__FUNCTION__); return null; }

  p->_parent= this;

  renderPassList.add(p);
  return p;
}


void vkObject::delRenderPasses() {
  for(VkoRenderPass *p= (VkoRenderPass *)renderPassList.first; p; p= (VkoRenderPass *)p->next)
    if(p->renderPass!= null)
      p->destroy();
}


VkoFramebuffer *vkObject::addFramebuffer() {
  VkoFramebuffer *p= new VkoFramebuffer;
  if(p== null) { error.alloc(__FUNCTION__); return null; }

  p->_parent= this;

  framebuffersList.add(p);
  return p;
}


void vkObject::delFramebuffers() {
  for(VkoFramebuffer *p= (VkoFramebuffer *)framebuffersList.first; p; p= (VkoFramebuffer *)p->next)
    if(p->framebuffer!= null)
      p->destroy();
}




VkoCommandPool *vkObject::addCommandPool() {
  VkoCommandPool *p= new VkoCommandPool;
  if(p== null) { error.alloc(__FUNCTION__); return null; }

  p->_parent= this;

  commandPoolList.add(p);
  return p;
}


void vkObject::delCommandPools() {
  for(VkoCommandPool *p= (VkoCommandPool *)commandPoolList.first; p; p= (VkoCommandPool *)p->next)
    p->destroy();
}


VkoDescriptorManager *vkObject::addDescriptorManager() {
  VkoDescriptorManager *p= new VkoDescriptorManager;
  if(p== null) { error.alloc(__FUNCTION__); return null; }

  p->_parent= this;

  descriptorManagerList.add(p);
  return p;
}


void vkObject::delDescriptorManagers() {
  for(VkoDescriptorManager *p= (VkoDescriptorManager *)descriptorManagerList.first; p; p= (VkoDescriptorManager *)p->next)
    p->destroy();
}



VkoSemaphore *vkObject::addSemaphore() {
  VkoSemaphore *s= new VkoSemaphore;

  s->_parent= this;

  _VkoSemaphores.add(s);
  return s;

}























bool _createDevice(VkPhysicalDevice in_GPU, VkDevice *out_dev, uint32_t *out_nrQueues, VkoQueue **out_osiQueues) {
  if(osi.vkInstance== null) { error.simple("osiVkRenderer::_createDevice(): osi.vkInstance is null. no instance created? aborting."); return false; }
  bool ret= false;
  //bool alocated= false;
  VkDeviceCreateInfo dci;
  VkDeviceCreateInfo *dciToUse;
  VkPhysicalDeviceFeatures pdf;
  VkPhysicalDeviceFeatures *pdfToUse;
  //VkDeviceQueueCreateInfo qci;
  //float queuePriority= 1.0f;

  osi.settings.vulkan.extensions.populateAvailabilityDevice(in_GPU);

  // custom deviceInfo would be best, if not osi will create an automatic one enabling everything
  if(osi.settings.vulkan.deviceInfo== null) {
    dci.sType= VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
    dci.pNext= NULL;
    dci.flags= 0;
    dci.enabledLayerCount= 0;
    dci.ppEnabledLayerNames= null;
  
    // enable custom GPU features - THIS IS A MUST, enabling all can create unnecesary lag
    if(osi.settings.vulkan.gpuFeatures)
      pdfToUse= osi.settings.vulkan.gpuFeatures;
    else {
      // enable all GPU features
      ::vk.GetPhysicalDeviceFeatures(in_GPU, &pdf);
      pdfToUse= &pdf;
    }
    dci.pEnabledFeatures= pdfToUse;

    // queues
    if(!_getRequestedQueues(in_GPU, &dci.queueCreateInfoCount, (VkDeviceQueueCreateInfo **)&dci.pQueueCreateInfos, out_nrQueues, out_osiQueues))
      return false;
    

    /// device extensions
    osi.settings.vulkan.extensions.createDeviceExtensionsStringArray((char ***)&dci.ppEnabledExtensionNames, &dci.enabledExtensionCount);

    dciToUse= &dci;
  } else
    dciToUse= osi.settings.vulkan.deviceInfo;

  // create the device
  if(::vk.CreateDevice(in_GPU, dciToUse, osi.settings.vulkan.memAllocCallback, out_dev)!= VK_SUCCESS) {
    error.detail("vkCreateDevice failed", __FUNCTION__, __LINE__);
    *out_nrQueues= 0;
    delete[] *out_osiQueues;
  } else ret= true;


  if(dciToUse== &dci) {
    delete[] dci.pQueueCreateInfos[0].pQueuePriorities;
    delete[] dci.pQueueCreateInfos;
  }

  return ret;
}



bool _getRequestedQueues(VkPhysicalDevice in_GPU, uint32_t *out_nrStructs, VkDeviceQueueCreateInfo **out_structs, uint32_t *out_nrQueues, osiVkQueue **out_osiQueues) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#devsandqueues-queues
  bool chatty= true;
  bool found;
  uint32 n;

  /// mem allocated tmp vars
  VkQueueFamilyProperties *qfp= null;   // 1 delete here
  uint32 *requested= null;              // 2 delete here

  float *qp= null;                      // 1 delete in _createDevice (or here if error)
                            // out_structs 2 delete in _createDevice
                            // out_osiQueues is handled by osiVkRenderer, deleted in destructor
  *out_nrStructs= 0;
  *out_structs= null;
  *out_nrQueues= 0;
  *out_osiQueues= null;
  
  /// get the number of queue families
  ::vk.GetPhysicalDeviceQueueFamilyProperties(in_GPU, &n, null);
  if(n== 0) { error.detail("Vulkan returns no queues", __FUNCTION__, __LINE__); goto Error; }
  //if(chatty) printf("VK returned %u queues for GPU\n", n);

  qfp= new VkQueueFamilyProperties[n];
  if(qfp== null) { error.detail("mem alloc error", __FUNCTION__, __LINE__); goto Error; }
  
  /// get all queue families in an array
  ::vk.GetPhysicalDeviceQueueFamilyProperties(in_GPU, &n, qfp);

  if(chatty) {
    printf("Found %u Vulkan Queue families\n", n);
    for(uint a= 0; a< n; a++) {
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

  /// create requested struct. it will count how many queues are requested from each queue family, if any (requested from osi.settings)
  requested= new uint32[n];
  if(requested== null) { error.detail("mem alloc error", __FUNCTION__, __LINE__); goto Error; }
  
  for(uint a= 0; a< n; a++)
    requested[a]= 0;



  // universal queues (compute/graphics/transfer)
  if(osi.settings.vulkan.requestUniversalQueues> 0) {

    for(uint a= 0; a< n; a++)
      if((qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT) && (qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT)) {
        /// check for extra requested flags
        if(osi.settings.vulkan.extraFlagBits)
          if(!(qfp[a].queueFlags& osi.settings.vulkan.extraFlagBits))
            continue;

        // found
        requested[a]+= osi.settings.vulkan.requestUniversalQueues;
        if(requested[a]> qfp[a].queueCount)
          requested[a]= qfp[a].queueCount;
      }

  } /// if requested universal


  // graphics queues (i think there's no way to have graphics without the others !!!!!!!)
  if(osi.settings.vulkan.requestGraphicsQueues> 0) {

    // search for graphics only queues (atm there's no such thing in the current drivers, but who knows)
    found= false;
    for(uint a= 0; a< n; a++)
      if((qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT) && !(qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT)) {
        /// check for extra requested flags
        if(osi.settings.vulkan.extraFlagBits)
          if(!(qfp[a].queueFlags& osi.settings.vulkan.extraFlagBits))
            continue;

        // found
        found= true;
        requested[a]+= osi.settings.vulkan.requestGraphicsQueues;
        if(requested[a]> qfp[a].queueCount)
          requested[a]= qfp[a].queueCount;
      }

    // search for graphics& compute queues (universal)
    if(!found) {
      for(uint a= 0; a< n; a++)
        if(qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT) {
          /// check for extra requested flags
          if(osi.settings.vulkan.extraFlagBits)
            if(!(qfp[a].queueFlags& osi.settings.vulkan.extraFlagBits))
              continue;

          // found
          requested[a]+= osi.settings.vulkan.requestGraphicsQueues;
          if(requested[a]> qfp[a].queueCount)
            requested[a]= qfp[a].queueCount;
        }
    }
  } /// if requested graphics only queues
  
  
  // compute queues
  if(osi.settings.vulkan.requestComputeQueues> 0) {
    /// search for compute-only queues (AMD GPU's do have them it seems)
    found= false;
    for(uint a= 0; a< n; a++)
      if((qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT) && !(qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT)) {
        /// check for extra requested flags
        if(osi.settings.vulkan.extraFlagBits)
          if(!(qfp[a].queueFlags& osi.settings.vulkan.extraFlagBits))
            continue;

        // found
        found= true;
        requested[a]+= osi.settings.vulkan.requestComputeQueues;
        if(requested[a]> qfp[a].queueCount)
          requested[a]= qfp[a].queueCount;
      }

    /// search for graphics& compute queues (universal)
    if(!found) {
      for(uint a= 0; a< n; a++)
        if(qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT) {
          /// check for extra requested flags
          if(osi.settings.vulkan.extraFlagBits)
            if(!(qfp[a].queueFlags& osi.settings.vulkan.extraFlagBits))
              continue;

          // found
          requested[a]+= osi.settings.vulkan.requestComputeQueues;
          if(requested[a]> qfp[a].queueCount)
            requested[a]= qfp[a].queueCount;
        }
    }
  } /// request compute queues


  // transfer queues
  if(osi.settings.vulkan.requestTransferQueues> 0) {
    /// search for transfer-only queues first (both AMD and NVIDIA seem to have it nowadays)
    found= false;

    for(uint a= 0; a< n; a++)
      if((qfp[a].queueFlags& VK_QUEUE_TRANSFER_BIT) && (!(qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT)) && (!(qfp[a].queueFlags& VK_QUEUE_COMPUTE_BIT))) {
        /// check for extra requested flags
        if(osi.settings.vulkan.extraFlagBits)
          if(!(qfp[a].queueFlags& osi.settings.vulkan.extraFlagBits))
            continue;

        // found
        found= true;
        requested[a]+= osi.settings.vulkan.requestTransferQueues;
        if(requested[a]> qfp[a].queueCount)
          requested[a]= qfp[a].queueCount;
      }

    /// search for universal queues
    if(!found) {
      for(uint a= 0; a< n; a++)
        if((qfp[a].queueFlags& VK_QUEUE_TRANSFER_BIT) || (qfp[a].queueFlags& VK_QUEUE_GRAPHICS_BIT)) { // graphics queues have capacity for transfer for sure, and it's not requested to put the transfer bit anymore
          /// check for extra requested flags
          if(osi.settings.vulkan.extraFlagBits)
            if(!(qfp[a].queueFlags& osi.settings.vulkan.extraFlagBits))
              continue;

          // found
          requested[a]+= osi.settings.vulkan.requestTransferQueues;
          if(requested[a]> qfp[a].queueCount)
            requested[a]= qfp[a].queueCount;
        }
    }

  } /// request transfer queues


  /// count how many queues will be created in total
  for(uint a= 0; a< n; a++)
    (*out_nrQueues)+= requested[a];
  if(*out_nrQueues== 0) { error.detail("found zero vulkan queues that match any requested", __FUNCTION__); goto Error; }


  /// queue priorities array - gonna be all 1.0f
  qp= new float[*out_nrQueues];
  if(qp== null) { error.detail("mem alloc error", __FUNCTION__, __LINE__); goto Error; }
  for(uint a= 0; a< *out_nrQueues; a++)
    qp[a]= 1.0f;

  /// osiQueues - the renderer stored queue data
  *out_osiQueues= new osiVkQueue[*out_nrQueues];
  if(*out_osiQueues== null) { error.detail("mem alloc error", __FUNCTION__, __LINE__); goto Error; }
  
  /// count how many structs will be returned
  for(uint a= 0; a< n; a++)
    if(requested[a]> 0)
      (*out_nrStructs)++;
  
  /// populate the returned structures
  *out_structs= new VkDeviceQueueCreateInfo[*out_nrStructs];
  if(*out_structs== null) { error.detail("mem alloc error", __FUNCTION__, __LINE__); goto Error; }

  /// a= family, b= loop thru out_structs, c= loop thru osiQueues, d= loop thru family
  for(uint a= 0, b= 0, c= 0; a< n; a++)
    if(requested[a]> 0) {
      (*out_structs)[b].sType= VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
      (*out_structs)[b].pNext= null;
      if(osi.settings.vulkan.extraFlagBits& VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT)
        (*out_structs)[b].flags= VK_DEVICE_QUEUE_CREATE_PROTECTED_BIT;
      else
        (*out_structs)[b].flags= 0;
      (*out_structs)[b].queueFamilyIndex= a;
      (*out_structs)[b].queueCount= requested[a];
      (*out_structs)[b].pQueuePriorities= qp;
      b++;

      /// populate out_osiQueues
      for(uint d= 0; d< requested[a]; d++) {
        (*out_osiQueues)[c].family= a;
        (*out_osiQueues)[c].index= d;
        (*out_osiQueues)[c].typeFlags= qfp[a].queueFlags;
        (*out_osiQueues)[c].queue= null;
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


void _populateVkQueue(osiVkRenderer *out_r) {
  if((out_r->vk.GetDeviceQueue== null) || (out_r->nrQueues== 0)) return;
  for(uint a= 0; a< out_r->nrQueues; a++)
    out_r->vk.GetDeviceQueue(out_r->vkDevice, out_r->vkQueues[a].family, out_r->vkQueues[a].index, &out_r->vkQueues[a].queue);
}





void _addValidationLayer(const char *in_name) {
  _ValidationLayer *p= new _ValidationLayer;
  p->name= in_name;
  _validationLayers.add(p);
}












