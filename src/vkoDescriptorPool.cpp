#include "../include/vkObject.h"


///=======================---------------------///
// Descriptor Pool object ===================== //
///=======================---------------------///

void VkoDescriptorPool::delData() {
  _createInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
  _createInfo.flags= 0;
  _createInfo.maxSets= 0;
  _createInfo.pNext= nullptr;

  _createInfo.poolSizeCount= 0;
  _createInfo.pPoolSizes= nullptr;

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


void VkoDescriptorPool::resetPool() {
  _vko->errorCheck(_vko->ResetDescriptorPool(*_vko, descriptorPool, 0), "VkoDescriptorPool::resetPool(): Reset descriptor pool failed");

  /// mark all sets from this pool as not allocated
  for(VkoSet *p= (VkoSet *)sets.first; p; p= (VkoSet *)p->next)
    p->set= (VkDescriptorSet)0;
}



bool VkoDescriptorPool::build() {
  // create info https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorPoolCreateInfo
  //
  // research:
  //
  // alloc / free / reset:
  // VK_DESCRIPTOR_POOL_CREATE_FREE_DESCRIPTOR_SET_BIT - allows for the vkFreeDescriptorSets func, otherwise, ONLY alloc and reset are allowed
  // if freeing and allocating happens often, allocation can fail, due fragmentation
  // so it is advised the allocation happens once, and maybe reset
  //
  // so it seems this pool is bit different from the command pool. it is dangerous to have multiple frees allocs.
  // the pool almost defines the amount of memory to be allocated for your images/buffers, not much of a clever pool here...
  //
  // mkay, this pool seems to be more like a fixed size pool or a description of what you gonna alloc, the sizes too.

  
  
  // -vkUpdateDescriptorSets:
  //  "Once allocated, descriptor sets can be updated with a combination of write and copy operations."
  
  // in any case, the pools are not thread safe, from what i know,
  // and these are not actually pools, it's just a fixed array of descriptors that are pre-allocated, it can't expand or have any clever functionality

  // create
  if(!_vko->errorCheck(_vko->CreateDescriptorPool(*_vko, &_createInfo, *_vko, &descriptorPool), "VkoDescriptorPool::build(): Vulkan Descriptor Pool create falied."))
    return false;

  /// if this is a rebuild, all previously created sets can be re-allocated from this pool
  for(VkoSet *p= (VkoSet *)sets.first; p; p= (VkoSet *)p->next)
    p->alloc();

  return true;
}





void VkoDescriptorPool::addDescriptorsFromLayout(VkoDescriptorSetLayout *in_layout, uint32_t in_nrSets) {

  /// loop thru all descriptors in set layout
  for(VkoDescriptorLayout *d= (VkoDescriptorLayout *)in_layout->descriptors.first; d; d= (VkoDescriptorLayout *)d->next) {

    // search current list for the decriptor type, add to it's count if found
    bool found= false;
    for(uint32_t a= 0; a< _createInfo.poolSizeCount; a++)
      if(_createInfo.pPoolSizes[a].type== d->type) {                // found
        ((VkDescriptorPoolSize *)(_createInfo.pPoolSizes))[a].descriptorCount+= in_nrSets;     /// 1 * nrSets
        found= true;
      }
    // if not found, add the descriptor type to the pool list
    if(!found)
      _addDescriptorTypeToList(d->type, in_nrSets);                           /// 1 * nrSets
  } /// for each descriptor

  _createInfo.maxSets+= in_nrSets;
}



void VkoDescriptorPool::_addDescriptorTypeToList(VkDescriptorType in_type, uint32_t in_nr) {
  VkDescriptorPoolSize *oldList= (VkDescriptorPoolSize *)_createInfo.pPoolSizes;
  VkDescriptorPoolSize *newList= new VkDescriptorPoolSize[_createInfo.poolSizeCount+ 1];

  /// copy from old list to new
  if(_createInfo.poolSizeCount)
    for(uint32_t a= 0; a< _createInfo.poolSizeCount; a++)
      newList[a].type=            oldList[a].type,
      newList[a].descriptorCount= oldList[a].descriptorCount;
      
  // add the new type of descriptor
  newList[_createInfo.poolSizeCount].type= in_type;
  newList[_createInfo.poolSizeCount].descriptorCount= in_nr;

  _createInfo.poolSizeCount++;
  _createInfo.pPoolSizes= newList;
}


void VkoDescriptorPool::addManualDescriptors(VkDescriptorType in_type, uint32_t in_maxDescriptors) {
  
  /// search for existing 
  for(uint32_t a= 0; a< _createInfo.poolSizeCount; a++)
    // if found, update, return
    if(_createInfo.pPoolSizes[a].type== in_type) {
      ((VkDescriptorPoolSize *)(_createInfo.pPoolSizes))[a].descriptorCount+= in_maxDescriptors;
      return;
    }

  _addDescriptorTypeToList(in_type, in_maxDescriptors);
}











// this func should be used to allocate a big array of non-managed VkDescriptorSets, from this pool

void VkoDescriptorPool::allocateSets(VkDescriptorSet *out_sets, uint32_t in_nr, VkoDescriptorSetLayout *in_layout, void *pNext) {
  
  VkDescriptorSetAllocateInfo allocInfo;  // alloc info struct https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorSetAllocateInfo
  allocInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
  allocInfo.pNext= pNext;
  allocInfo.descriptorPool= descriptorPool;
  allocInfo.descriptorSetCount= in_nr;

  if(in_nr== 1) 
    allocInfo.pSetLayouts= &in_layout->layout;
  else {
    allocInfo.pSetLayouts= new VkDescriptorSetLayout[in_nr];
    for(uint32_t a= 0; a< in_nr; a++)
      ((VkDescriptorSetLayout *)(allocInfo.pSetLayouts))[a]= in_layout->layout;
  }

  _vko->errorCheck(_vko->AllocateDescriptorSets(*_vko, &allocInfo, out_sets), "VkoDescriptorPool::allocateSets(): Vulkan allocation func failed.");

  if((in_nr> 1) && (allocInfo.pSetLayouts!= nullptr))
    delete[] allocInfo.pSetLayouts;
}


// allocates managed VkoSet class
VkoSet *VkoDescriptorPool::allocVkoSet(VkoDescriptorSetLayout *in_layout, void *pNext) {
  VkoSet *p= new VkoSet(this);
  p->layout= in_layout;
  p->pNext.VkDescriptorSetAllocateInfo= pNext;
  
  sets.add(p);
  if(!p->alloc()) { delete p; return nullptr; }
  return p;
}



// VkoSet alloc function
bool VkoSet::alloc() {
  if((!pool) || (!layout)) return false;

  VkDescriptorSetAllocateInfo allocInfo;  // alloc info struct https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorSetAllocateInfo
    allocInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.pNext= pNext.VkDescriptorSetAllocateInfo;
    allocInfo.descriptorPool= pool->descriptorPool;
    allocInfo.descriptorSetCount= 1;
    allocInfo.pSetLayouts= &layout->layout;
  if(!pool->_vko->errorCheck(pool->_vko->AllocateDescriptorSets(*pool->_vko, &allocInfo, &set), "VkoSet::alloc(): Vulkan set allocation func failed."))
    return false;
  return true;
}






void VkoDescriptorPool::freeSets(VkDescriptorSet *out_sets, uint32_t in_nr) {
  _vko->errorCheck(_vko->FreeDescriptorSets(*_vko, descriptorPool, in_nr, out_sets), "VkoDescriptorPool::freeSets(): free descriptor sets failed");
}


void VkoSet::free() {
  pool->_vko->errorCheck(pool->_vko->FreeDescriptorSets(*pool->_vko, *pool, 1, &set), "VkoSet::free(): free descriptor sets failed");
}
