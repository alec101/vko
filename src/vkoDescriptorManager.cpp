#include "vko/include/vkObject.h"


///==========================---------------------///
// Descriptor Manager object ===================== //
///==========================---------------------///

VkoDescriptorManager::VkoDescriptorManager() {
  descriptorPool= 0;
  flags= 0;

  _maxSets= 0;
  _parent= nullptr;
}



void VkoDescriptorManager::destroy() {
  // all allocated sets are destroyed with the pool.
  if(_parent->device) {
    if(descriptorPool) {
      _parent->DestroyDescriptorPool(*_parent, *this, _parent->memCallback);
      descriptorPool= 0;
    }
  }
}



// set funcs

VkoSet *VkoDescriptorManager::getSet(uint32_t in_i) {
  VkoSet *p= (VkoSet *)sets.first;
  for(uint32_t a= 0; p; p= (VkoSet *)p->next, a++)
    if(a== in_i) return p;

  return nullptr;
}

/*
VkoSet *VkoDescriptorManager::getDescriptorSet(VkoDescriptor *in_p) {
  for(VkoSet *p= (VkoSet *)sets.first; p; p= (VkoSet *)p->next)
    if(p->index== in_p->set)
      return p;
  return nullptr;
}
*/

VkoSet *VkoDescriptorManager::addDescriptorSet(uint32_t in_i) {
  VkoSet *p= new VkoSet;
  p->index= in_i;
  p->parent= this;
  sets.add(p);
  return p;
}


void VkoDescriptorManager::setDescriptorSetFlags(uint32_t in_set, VkDescriptorSetLayoutCreateFlags in_flags) {
  _parent->clearError();
  VkoSet *p= getSet(in_set);
  if(p== nullptr) {
    _parent->errorText= __FUNCTION__": <in_set> not found";
    return;
  }

  p->flags= in_flags;
}



VkoDescriptor *VkoDescriptorManager::addDescriptor(uint32_t in_set, uint32_t in_binding, VkDescriptorType in_type, uint32_t in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler) {
  _parent->clearError();
  VkoSet *p= getSet(in_set);
  if(p== nullptr) {
    _parent->errorText= __FUNCTION__": <in_set> not found";
    return nullptr;
  }
  return p->addDescriptor(in_binding, in_type, in_count, in_stages, in_pImutableSampler);
}


VkoDescriptorManager::_DescriptorMax *VkoDescriptorManager::_getDescMaxForType(VkDescriptorType in_type) {
  for(_DescriptorMax *p= (_DescriptorMax *)_maxDescriptors.first; p; p= (_DescriptorMax *)p->next)
    if(p->type= in_type)
      return p;
  return nullptr;
}


VkoDescriptorManager::_DescriptorMax *VkoDescriptorManager::_addDescMax(VkDescriptorType in_type) {
  _DescriptorMax *p= new _DescriptorMax;
  p->type= in_type;
  p->descriptorCount= 0;
  _maxDescriptors.add(p);
  return p;
}



void VkoDescriptorManager::_computeMaxPoolNumbers() {
  // if not manually specified, computes the maximum number of sets the pool can have based on the number of descriptors added and their sets
  // and the max number of descriptor types for this pool also.

  // max number of sets
  if(_maxSets== 0) {                  // auto-compute only if not specified
    /// such compute the world has never seen
    _maxSets= sets.nrNodes;    
  }

  // max number of descriptor types
  if(_maxDescriptors.nrNodes== 0) {   // auto-compute only if not manually specified
    /// loop thru all descriptors in all sets
    for(VkoSet *s= (VkoSet *)sets.first; s; s= (VkoSet *)s->next) {
      for(VkoDescriptor *d= (VkoDescriptor *)s->descriptors.first; d; d= (VkoDescriptor *)d->next) {
        _DescriptorMax *dm= _getDescMaxForType(d->type);
        if(dm== nullptr)
          dm= _addDescMax(d->type);
        dm->descriptorCount++;
      } /// for each descriptor
    } /// for each set
  }
}


void VkoDescriptorManager::setPoolMaxDescriptorType(VkDescriptorType in_type, uint32_t in_maxDescriptors) {
  _DescriptorMax *dm= _getDescMaxForType(in_type);
  if(dm== nullptr)
    dm= _addDescMax(in_type);
  if(dm)
    dm->descriptorCount= in_maxDescriptors;
}


bool VkoDescriptorManager::build() {
  // create info https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorPoolCreateInfo
  //
  // research:
  //
  // alloc / free / reset:
  // VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT - allows for the vkFreeDescriptorSets func, otherwise, ONLY alloc and reset are allowed
  // if freeing and allocating happens often, allocation can fail, due fragmentation
  // so it is advised the allocation happens once, and maybe reset, or i am thinking of a clever use of the free + alloc, of same sizes, maybe
  // basically free a fixed size block, alloc the same fixed size block, maybe that could work
  //
  // so it seems this pool is bit different from the command pool. it is dangerous to have multiple frees allocs.
  // the pool almost defines the amount of memory to be allocated for your images/buffers, not much of a clever pool here...
  //
  // mkay, this pool seems to be more like a fixed size pool or a description of what you gonna alloc, the sizes too.

  
  
  // -vkUpdateDescriptorSets:
  //  "Once allocated, descriptor sets can be updated with a combination of write and copy operations."
  
  // in any case, the pools are not thread safe, from what i know

  // there is a ton of copy/update/write/etc funcs to fill in descriptors
  // so the class i have to make, should handle these i think




  // POOL creation ===---------
  bool ret= false;
  VkDescriptorPoolCreateInfo descInfo;
  descInfo.pPoolSizes= nullptr;              // INIT 1

  _computeMaxPoolNumbers();

  /// populate descriptor info
  descInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  descInfo.pNext= nullptr;

  descInfo.flags= flags;
  descInfo.maxSets= _maxSets;
  descInfo.poolSizeCount= _maxDescriptors.nrNodes;

  if(_maxDescriptors.nrNodes) {
    descInfo.pPoolSizes= new VkDescriptorPoolSize[_maxDescriptors.nrNodes];  // ALLOC 1
    uint32_t a= 0;
    for(_DescriptorMax *p= (_DescriptorMax *)_maxDescriptors.first; p; p= (_DescriptorMax *)p->next, a++)
      ((VkDescriptorPoolSize *)descInfo.pPoolSizes)[a].type= p->type,
      ((VkDescriptorPoolSize *)descInfo.pPoolSizes)[a].descriptorCount= p->descriptorCount;
  }

  // create
  if(!_parent->errorCheck(_parent->CreateDescriptorPool(*_parent, &descInfo, _parent->memCallback, &descriptorPool), __FUNCTION__": Vulkan Descriptor Pool create falied."))
    goto Exit;

  // build all sets (create layouts, VkDescriptorSet objects, allocate them)
  ret= buildAllSets();

  Exit:
  if(descInfo.pPoolSizes) delete[] descInfo.pPoolSizes;   // DEALLOC 1
  return ret;
}







bool VkoDescriptorManager::buildSet(uint32_t in_index) {
  // descriptor sets https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#descriptorsets-sets
  _parent->clearError();
  VkDescriptorSetAllocateInfo dsInfo; // alloc info struct https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorSetAllocateInfo
  bool ret= false;      /// return value

  VkoSet *s= getSet(in_index);
  if(s== nullptr) { _parent->errorText= __FUNCTION__": Set not found"; goto Exit; }

  s->buildLayout();

  // allocate + create the set 

  dsInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  dsInfo.pNext= nullptr;

  dsInfo.descriptorPool= descriptorPool;

  dsInfo.descriptorSetCount= 1;
  dsInfo.pSetLayouts= &s->layout;

  if(!_parent->errorCheck(_parent->AllocateDescriptorSets(*_parent, &dsInfo, &s->set), __FUNCTION__": Vulkan Descriptor Set alloc failed"))
    goto Exit;

  ret= true;  // success

Exit:
  return ret;
}



bool VkoDescriptorManager::buildAllSets() {
  for(VkoSet *p= (VkoSet *)sets.first; p; p= (VkoSet *)p->next)
    if(!buildSet(p->index))
      return false;

  return true;
}


void VkoDescriptorManager::resetPool() {
  _parent->errorCheck(_parent->ResetDescriptorPool(*_parent, descriptorPool, 0), __FUNCTION__": Reset descriptor pool failed");
  sets.delData();
}


void VkoDescriptorManager::freeSet(uint32_t in_i) {
  _parent->clearError();
  VkoSet *p= getSet(in_i);
  if(p== nullptr) { _parent->errorText= "VkoDescriptorManager::freeSet(): index not found. aborting."; return; }

  _parent->errorCheck(_parent->FreeDescriptorSets(*_parent, descriptorPool, 1, &p->set), __FUNCTION__": vkFreeDescriptorSets() failed");
  p->set= NULL;
  
  /// all descriptors will be destroyed too, fromt he p->descriptors chainList
  sets.del(p);
}


























