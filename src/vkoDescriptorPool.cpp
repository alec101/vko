#include "vko/include/vkObject.h"


///==========================---------------------///
// Descriptor Manager object ===================== //
///==========================---------------------///

void VkoDescriptorPool::delData() {
  _flags= 0;
  _maxSets= 0;

  pNext.delData();

  /// delete all created sets
  while(sets.first)
    sets.del(sets.first);
}


void VkoDescriptorPool::destroy() {
  
  if(descriptorPool) {
    if(_vko->device)
      _vko->DestroyDescriptorPool(*_vko, *this, _vko->memCallback);
    descriptorPool= 0;
  }

  /// all allocated sets are destroyed with the pool
  for(VkoSet *p= (VkoSet *)sets.first; p; p= (VkoSet *)p->next)
    p->set= 0;
}



bool VkoDescriptorPool::build() {
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
  descInfo.pNext= pNext.VkDescriptorPoolCreateInfo;

  descInfo.flags= _flags;
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
  if(!_vko->errorCheck(_vko->CreateDescriptorPool(*_vko, &descInfo, *_vko, &descriptorPool), __FUNCTION__": Vulkan Descriptor Pool create falied."))
    goto Exit;

  /// if this is a rebuild, all previously created sets can be re-allocated from this pool
  for(VkoSet *p= (VkoSet *)sets.first; p; p= (VkoSet *)p->next)
    if(!p->alloc())
      goto Exit;

  ret= true;    // success

Exit:
  if(descInfo.pPoolSizes) delete[] descInfo.pPoolSizes;   // DEALLOC 1
  return ret;
}



// add a set, doesn't allocate mem from pool
VkoSet *VkoDescriptorPool::addDescriptorSet(VkoDescriptorSetLayout *in_layout) {
  VkoSet *p= new VkoSet(this);
  p->layout= in_layout;
  sets.add(p);
  return p;
}


void VkoDescriptorPool::setPoolMaxDescriptorType(VkDescriptorType in_type, uint32_t in_maxDescriptors) {
  _DescriptorMax *dm= _getDescMaxForType(in_type);
  if(dm== nullptr)
    dm= _addDescMax(in_type);
  if(dm)
    dm->descriptorCount= in_maxDescriptors;
}






void VkoDescriptorPool::resetPool() {
  _vko->errorCheck(_vko->ResetDescriptorPool(*_vko, descriptorPool, 0), __FUNCTION__": Reset descriptor pool failed");

  /// mark all sets from this pool as not allocated
  for(VkoSet *p= (VkoSet *)sets.first; p; p= (VkoSet *)p->next)
    p->set= (VkDescriptorSet)0;
}














VkoDescriptorPool::_DescriptorMax *VkoDescriptorPool::_getDescMaxForType(VkDescriptorType in_type) {
  for(_DescriptorMax *p= (_DescriptorMax *)_maxDescriptors.first; p; p= (_DescriptorMax *)p->next)
    if(p->type= in_type)
      return p;
  return nullptr;
}


VkoDescriptorPool::_DescriptorMax *VkoDescriptorPool::_addDescMax(VkDescriptorType in_type) {
  _DescriptorMax *p= new _DescriptorMax;
  p->type= in_type;
  p->descriptorCount= 0;
  _maxDescriptors.add(p);
  return p;
}


void VkoDescriptorPool::_computeMaxPoolNumbers() {
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
      for(VkoDescriptorLayout *d= (VkoDescriptorLayout *)s->layout->descriptors.first; d; d= (VkoDescriptorLayout *)d->next) {
        _DescriptorMax *dm= _getDescMaxForType(d->type);
        if(dm== nullptr)
          dm= _addDescMax(d->type);
        dm->descriptorCount++;
      } /// for each descriptor
    } /// for each set
  }
}







