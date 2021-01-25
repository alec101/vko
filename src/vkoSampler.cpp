#include "../include/vkObject.h"



///================///
// VkoSampler class //
///================///


VkoSampler::VkoSampler(vkObject *in_parent): sampler(0), _vko(in_parent){
  delData();
}


void VkoSampler::delData() {
  pNext.delData();

  // default values
  createInfo.sType= VK_STRUCTURE_TYPE_SAMPLER_CREATE_INFO;
  createInfo.pNext= nullptr;
  createInfo.flags= 0;

  createInfo.magFilter= VK_FILTER_LINEAR;
  createInfo.minFilter= VK_FILTER_LINEAR;
  createInfo.mipmapMode= VK_SAMPLER_MIPMAP_MODE_LINEAR;

  createInfo.addressModeU=
    createInfo.addressModeV=
    createInfo.addressModeW= VK_SAMPLER_ADDRESS_MODE_REPEAT;

  createInfo.mipLodBias= 0.0f;

  createInfo.anisotropyEnable= false;
  createInfo.maxAnisotropy= 1.0f;
  createInfo.compareEnable= false;
  createInfo.compareOp= VK_COMPARE_OP_ALWAYS;
  createInfo.minLod= 0.0f;
  createInfo.maxLod= 1.0f;
  createInfo.borderColor= VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK;
  createInfo.unnormalizedCoordinates= false;
}


void VkoSampler::destroy() {
  if(sampler) { 
    if(_vko->device) _vko->DestroySampler(*_vko, sampler, *_vko);
    sampler= 0;
  }
}


bool VkoSampler::build() {
  createInfo.pNext= pNext.VkSamplerCreateInfo;
  return _vko->errorCheck(_vko->CreateSampler(*_vko, &createInfo, *_vko, &sampler), "VkoSampler::build(): vko sampler create failed.");
}












