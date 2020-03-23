#pragma once

///================///
// VkoSampler class //
///================///


class VkoSampler: public chainData {
public:
  VkSampler sampler;
  inline operator VkSampler() { return sampler; }
  
  VkSamplerCreateInfo createInfo;   // createInfo struct, used with build();

  // configuration - https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap12.html#VkSamplerCreateInfo

  // set the minification/magnification/mipmap filters/mode
  // [def: VK_FILTER_LINEAR, VK_FILTER_LINEAR, VK_SAMPLER_MIPMAP_MODE_LINEAR]
  inline void setFilters(VkFilter mag, VkFilter min, VkSamplerMipmapMode mipmap) { createInfo.magFilter= mag, createInfo.minFilter= min, createInfo.mipmapMode= mipmap; }


  // set the Level Of Detail for mipmaping
  // minLOD is the minimum mipmap level
  // maxLOD is the maximum mipmap level
  // bias forces a lower resolution to be used (higher bias = higher level = lower resolution, as level 0 is the highest resolution)
  // [def: bias(0), min(0.0f), max(0)]
  inline void setLOD(float mipLodBias, float minLod, float maxLod) { createInfo.mipLodBias= mipLodBias, createInfo.minLod= minLod, createInfo.maxLod= maxLod; }

  // set the wrapping/address mode
  // [def: VK_SAMPLER_ADDRESS_MODE_REPEAT]
  inline void setAddressMode(VkSamplerAddressMode u, VkSamplerAddressMode v, VkSamplerAddressMode w) { createInfo.addressModeU= u, createInfo.addressModeV= v, createInfo.addressModeW= w; }

  // enable anisotropy and set it's quality (usually 16 is maximum)
  // [def: false, 1.0f]
  inline void setAnysotropy(bool anysotropyEnable, float maxAnisotropy) { createInfo.maxAnisotropy= maxAnisotropy, createInfo.anisotropyEnable= anysotropyEnable; }

  // set the compare operation
  // [def: false, VK_COMPARE_OP_ALWAYS]
  inline void setCompare(bool compareEnable, VkCompareOp compareOp) { createInfo.compareEnable= compareEnable, createInfo.compareOp= compareOp; }

  // set the texture border
  // [def: VK_BORDER_COLOR_FLOAT_TRANSPARENT_BLACK]
  inline void setBorder(VkBorderColor color) { createInfo.borderColor= color; }

  // [def: false]
  inline void setUnnormalizedCoordinates(bool b) { createInfo.unnormalizedCoordinates= b; }

  struct PNext {
    void *VkSamplerCreateInfo;
    void delData() { VkSamplerCreateInfo= nullptr; }
  } pNext;


  // build / destroy

  bool build();
  void destroy();
  inline bool rebuild() { destroy(); return build(); }

  VkoSampler(vkObject *in_parent);
  inline virtual ~VkoSampler() { destroy(); } // no need to call delData() ATM
  void delData();
  

private:
  

  vkObject *_vko;
  friend class vkObject;
};

















