#pragma once


///============--------------------------///
// fence class ========================== //
///============--------------------------///



class VkoFence: public chainData {
public:

  VkFence fence; // [init:null] vulkan object - gets populated when build() is called
  inline operator VkFence() const { return fence; }

  // configuration

  struct PNext {
    void *VkFenceCreateInfo;
    void delData() { VkFenceCreateInfo= nullptr; }
  } pNext;

  // VK_FENCE_CREATE_SIGNALED_BIT - specifies that the fence object is created in the signaled state
  inline void setFlags(VkFenceCreateFlagBits in_flags) { _createInfo.flags= in_flags; }

  // main usage funcs

  bool build();     // returns true if successful
  inline bool rebuild() { destroy(); return build(); }
  void destroy();


  VkoFence(vkObject *in_parent);
  ~VkoFence();
  void delData();

private:

  /// build structs
  VkFenceCreateInfo _createInfo;

  vkObject *_vko;
  friend class vkObject;
}; /// VkoFence class









