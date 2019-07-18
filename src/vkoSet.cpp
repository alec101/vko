#include "../include/vkObject.h"




VkoSet::~VkoSet() {
  destroyLayout();
}


void VkoSet::destroyLayout() {
  if((layout!= NULL) && (parent->_parent->device!= nullptr))
    parent->_parent->DestroyDescriptorSetLayout(*parent->_parent, layout, parent->_parent->memCallback);
}


bool VkoSet::buildLayout() {

  VkDescriptorSetLayoutCreateInfo layoutInfo; // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorSetLayoutCreateInfo
  // bindings https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorSetLayoutBinding
  VkDescriptorSetLayoutBinding *bindings= nullptr; // INIT 1
  bool ret= false;                              /// return value

  destroyLayout();

  // populate layout info
  layoutInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.pNext= nullptr;

  layoutInfo.flags= flags;
  layoutInfo.bindingCount= descriptors.nrNodes;
  
  if(descriptors.nrNodes) {
    bindings= new VkDescriptorSetLayoutBinding[descriptors.nrNodes]; // ALLOC 1
    
    uint32_t a= 0;
    for(VkoDescriptor *p= (VkoDescriptor *)descriptors.first; p; p= (VkoDescriptor *)p->next, a++) {
      bindings[a].binding=            p->binding;
      bindings[a].descriptorType=     p->type;
      bindings[a].descriptorCount=    p->arrayCount;
      bindings[a].stageFlags=         p->shaderStages;
      bindings[a].pImmutableSamplers= p->pImutableSamplers;

    } /// loop thru all descriptors in this set
  } /// if there are descriptors in this set
  layoutInfo.pBindings= bindings;
  
  if(!parent->_parent->errorCheck(parent->_parent->CreateDescriptorSetLayout(*parent->_parent, &layoutInfo, parent->_parent->memCallback, &layout),
    __FUNCTION__": Vulkan Descriptor Set Layout create fail"))
    goto Exit;

  ret= true;    // success if reached this point

Exit:
  if(bindings) delete[] bindings;           // DEALLOC 1
  return ret;
}




void VkoSet::setDescriptorSetFlags(VkDescriptorSetLayoutCreateFlags in_flags) {
  flags= in_flags;
}



VkoDescriptor *VkoSet::addDescriptor(uint32_t in_binding, VkDescriptorType in_type, uint32_t in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler) {
  VkoDescriptor *p= new VkoDescriptor;

  p->set= index;
  p->binding= in_binding;
  p->type= in_type;
  p->arrayCount= in_count;
  p->shaderStages= in_stages;
  p->pImutableSamplers= in_pImutableSampler;

  p->parent= this;
  descriptors.add(p);
  
  return p;
}










