#include "../include/vkObject.h"


///==============///
// VkoFence class //
///==============///



VkoFence::VkoFence(vkObject *in_parent): fence(0), _vko(in_parent) {
  delData();
}

VkoFence::~VkoFence() {
  destroy();
}

void VkoFence::delData() {

  pNext.delData();
  _createInfo.sType= VK_STRUCTURE_TYPE_FENCE_CREATE_INFO;
  _createInfo.pNext= nullptr;
  _createInfo.flags= 0;
}


void VkoFence::destroy() {
  if(fence) {
    if(_vko->device) _vko->DestroyFence(*_vko, fence, *_vko);
    fence= 0;
  }
}




bool VkoFence::build() {
  
  if(_vko->CreateFence(*_vko, &_createInfo, *_vko, &fence)== VK_SUCCESS)
    return true;
  else
    return false;
}













