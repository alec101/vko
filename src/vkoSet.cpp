#include "../include/vkObject.h"




bool VkoSet::alloc() {
  // descriptor sets https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#descriptorsets-sets
  parent->_vko->clearError();
  
  bool ret= false;                    /// return value

  // allocate + create the set 
  VkDescriptorSetAllocateInfo dsInfo; // alloc info struct https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorSetAllocateInfo
    dsInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    dsInfo.pNext= pNext.VkDescriptorSetAllocateInfo;
    dsInfo.descriptorPool= parent->descriptorPool;
    dsInfo.descriptorSetCount= 1;
    dsInfo.pSetLayouts= &layout->layout;
  if(!parent->_vko->errorCheck(parent->_vko->AllocateDescriptorSets(*parent->_vko, &dsInfo, &set), __FUNCTION__": Vulkan Descriptor Set alloc failed"))
    goto Exit;

  ret= true;  // success

Exit:
  return ret;
}


void VkoSet::free() {
  if(set!= (VkDescriptorSet)0) {
    if(parent)
      if(parent->descriptorPool)
        if(parent->_vko)
          if(parent->_vko->device)
            parent->_vko->FreeDescriptorSets(*parent->_vko, *parent, 1, &set);
    set= (VkDescriptorSet)0;
  }
}



















