#include "../include/vkObject.h"



///==============///
// vko SET LAYOUT //
///==============///

// constructor / destructor

VkoDescriptorSetLayout::VkoDescriptorSetLayout(vkObject *in_parent): _vko(in_parent) {
  layout= 0;
  delData();
}


void VkoDescriptorSetLayout::delData() {
  pNext.delData();
  _flags= 0;
  descriptors.delData();
}


void VkoDescriptorSetLayout::destroy() {
  if(layout) {
    if(_vko)
      if(_vko->device)
        _vko->DestroyDescriptorSetLayout(*_vko, layout, *_vko);
    layout= 0;
  }
}




// funcs

VkoDescriptorLayout *VkoDescriptorSetLayout::addDescriptor(uint32_t in_binding, VkDescriptorType in_type, uint32_t in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler) {
  VkoDescriptorLayout *p= new VkoDescriptorLayout(this);
    p->binding= in_binding;
    p->type= in_type;
    p->arrayCount= in_count;
    p->shaderStages= in_stages;
    p->pImutableSamplers= in_pImutableSampler;
  descriptors.add(p);
  
  return p;
}


bool VkoDescriptorSetLayout::build() {
  VkDescriptorSetLayoutCreateInfo layoutInfo; // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorSetLayoutCreateInfo
  // bindings https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorSetLayoutBinding
  VkDescriptorSetLayoutBinding *bindings= nullptr; // INIT 1
  bool ret= false;                              /// return value

  destroy();

  // populate layout info
  layoutInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
  layoutInfo.pNext= pNext.VkDescriptorSetLayoutCreateInfo;

  layoutInfo.flags= _flags;
  layoutInfo.bindingCount= descriptors.nrNodes;
  
  if(descriptors.nrNodes) {
    bindings= new VkDescriptorSetLayoutBinding[descriptors.nrNodes]; // ALLOC 1
    
    uint32_t a= 0;
    for(VkoDescriptorLayout *p= (VkoDescriptorLayout *)descriptors.first; p; p= (VkoDescriptorLayout *)p->next, a++) {
      bindings[a].binding=            p->binding;
      bindings[a].descriptorType=     p->type;
      bindings[a].descriptorCount=    p->arrayCount;
      bindings[a].stageFlags=         p->shaderStages;
      bindings[a].pImmutableSamplers= p->pImutableSamplers;

    } /// loop thru all descriptors in this set
  } /// if there are descriptors in this set
  layoutInfo.pBindings= bindings;
  
  if(!_vko->errorCheck(_vko->CreateDescriptorSetLayout(*_vko, &layoutInfo, *_vko, &layout),
    "VkoDescriptorSetLayout::build(): Vulkan Descriptor Set Layout create fail"))
    goto Exit;

  ret= true;    // success if reached this point

Exit:
  if(bindings) delete[] bindings;           // DEALLOC 1
  return ret;
}





