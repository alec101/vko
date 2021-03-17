#include "../include/vkObject.h"



///======================///
// DYNAMIC SET POOL class //
///======================///


// constructor / destructor
VkoDynamicSetPool::VkoDynamicSetPool(vkObject *in_parent): _vko(in_parent) {
  layout= nullptr;
  poolSize= 0;

  _nrDescriptorTypes= 0;
  _descriptorType= nullptr;
  pNext.delData();
}


VkoDynamicSetPool::~VkoDynamicSetPool() {
  destroy();
  if(_descriptorType) delete[] _descriptorType;
}



void VkoDynamicSetPool::destroy() {
  while(_segments.first) {
    _delSegment((VkoDynamicSetSegment *)_segments.first);
    //_segments.del(_segments.first);
  }
}



VkoDynamicSetSegment *VkoDynamicSetPool::_addSegment() {
  bool success= false;

  VkoDynamicSetSegment *p= new VkoDynamicSetSegment;
  
  p->freeSpc= nullptr;                // INIT 1

  // VkDescriptorPool creation
  VkDescriptorPoolCreateInfo info;
    info.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_POOL_CREATE_INFO;
    info.pNext= nullptr;
    info.flags= 0;

    info.maxSets= poolSize;

    info.poolSizeCount= _nrDescriptorTypes;
    info.pPoolSizes= _descriptorType;
  if(!_vko->errorCheck(_vko->CreateDescriptorPool(*_vko, &info, *_vko, &p->pool), "VkoDynamicSetSegment::_addSegment(): failed to create pool."))
    goto Exit;


  // sets creation - the sets will always exist;
  p->freeSpc= new VkDescriptorSet[poolSize];
  p->freeSpcPeak= poolSize;
  
  VkDescriptorSetAllocateInfo allocInfo;
    allocInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_ALLOCATE_INFO;
    allocInfo.pNext= pNext.VkDescriptorSetAllocateInfo;
    allocInfo.descriptorPool= p->pool;
    allocInfo.descriptorSetCount= 1;
    allocInfo.pSetLayouts= &layout->layout;

  for(uint32_t a= 0; a< poolSize; a++)
    if(!_vko->errorCheck(_vko->AllocateDescriptorSets(*_vko, &allocInfo, &p->freeSpc[a]), "VkoDynamicSetSegment::_addSegment(): failed to create set"))
      goto Exit;

  _segments.add(p);

  success= true;

Exit:
  // failed
  if(!success) {
    if(p) {
      if(p->freeSpc) delete[] p->freeSpc;
      delete p;
    }
    return nullptr;

  // success
  } else
    return p;
}


void VkoDynamicSetPool::_delSegment(VkoDynamicSetSegment *out_segment) {
  if(out_segment->pool)
    _vko->DestroyDescriptorPool(*_vko, out_segment->pool, *_vko);

  if(out_segment->freeSpc) { delete[] out_segment->freeSpc; out_segment->freeSpc= nullptr; }
  _segments.del(out_segment);
}




// configuration:
// <in_layout>: the set's layout that will be used;
// <in_number>: set the number of sets you _think_ you are going to use;
//              if this number is exceeded, another pool will be created;
void VkoDynamicSetPool::configure(VkoDescriptorSetLayout *in_layout, uint32_t in_n) {
  layout= in_layout;
  poolSize= in_n;



  // count the descriptor types
  class DescType: public chainData { public: VkDescriptorPoolSize type; };
  chainList types;
  for(VkoDescriptorLayout *p= (VkoDescriptorLayout *)layout->descriptors.first; p; p= (VkoDescriptorLayout *)p->next) {
    bool found= false;
    for(DescType *t= (DescType *)types.first; t; t= (DescType *)t->next)
      if(t->type.type== p->type) {
        t->type.descriptorCount++;
        found= true;
        break;
      }

    if(!found) {
      DescType *t= new DescType;
      t->type.descriptorCount= 1;
      t->type.type= p->type;
      types.add(t);
    }
  }

  // populate findings to the array that will be passed to the Vk..CreateInfo struct
  if(_descriptorType) { delete[] _descriptorType; _descriptorType= nullptr; }

  _nrDescriptorTypes= types.nrNodes;
  if(_nrDescriptorTypes) {
    _descriptorType= new VkDescriptorPoolSize[_nrDescriptorTypes];
    uint32_t a= 0;
    for(DescType *t= (DescType *)types.first; t; t= (DescType *)t->next, a++)
      _descriptorType[a].descriptorCount= t->type.descriptorCount,
      _descriptorType[a].type=            t->type.type;
  }
}



bool VkoDynamicSetPool::build() {
  // always there will be one pool/segment
  VkoDynamicSetSegment *s= _addSegment();

  return (s? true: false);
}




void VkoDynamicSetPool::addCustomSet(VkoDynamicSet *out_set) {
  // find a segment with free space
  VkoDynamicSetSegment *s= (VkoDynamicSetSegment *)_segments.first;
  while(s) {
    if(s->freeSpcPeak) break;                 /// found
    s= (VkoDynamicSetSegment *)s->next;
  }

  // not found? alloc mem for another segment
  if(s== nullptr)
    s= _addSegment();

  // populate set
  out_set->segment= s;
  out_set->set= s->freeSpc[s->freeSpcPeak- 1];

  // update segment
  s->sets.add(out_set);                         /// add set to the segment
  s->freeSpcPeak--;                         /// decrease segment free space
}


VkoDynamicSet *VkoDynamicSetPool::addSet() {
  VkoDynamicSet *ret= new VkoDynamicSet;
  addCustomSet(ret);
  return ret;
}




void VkoDynamicSetPool::delSet(VkoDynamicSet *out_set) {
  VkoDynamicSetSegment *s= out_set->segment;
  s->freeSpc[s->freeSpcPeak]= out_set->set;
  s->freeSpcPeak++;
  s->sets.del(out_set);
}







void VkoDynamicSetPool::trimPools() {
  if(_segments.nrNodes<= 1) return;     // quick return on only 1 segment

  // compact segments - move from later segments to first segments, loop thru all sets

  /// static data in VkCopyDescriptorSet
  VkCopyDescriptorSet copy;
  copy.sType= VK_STRUCTURE_TYPE_COPY_DESCRIPTOR_SET;
  copy.pNext= nullptr;

  /// loop thru all starting segments
  for(VkoDynamicSetSegment *dst= (VkoDynamicSetSegment *)_segments.first; dst; dst= (VkoDynamicSetSegment *)dst->next) {

    if(dst->freeSpcPeak)              // proceed only if there's free space in destination
      for(VkoDynamicSetSegment *src= (VkoDynamicSetSegment *)_segments.last; src; src= (VkoDynamicSetSegment *)src->prev) {
        
        if(src== dst)                /// same segment, src loop halts
          break;

        /// while there's free space in dst, and sets in src
        while(src->sets.nrNodes && dst->freeSpcPeak) {
          VkoDynamicSet *set= (VkoDynamicSet *)src->sets.first;
          VkDescriptorSet oldSet= set->set;

          set->segment= dst;
          set->set= dst->freeSpc[dst->freeSpcPeak- 1];
          
          // copy src set to dst set, whole size (thank God for VkoDescriptorLayout, or this wouldn't have happened)
          copy.srcSet= oldSet;
          copy.dstSet= set->set;
          copy.srcArrayElement= 0;
          copy.dstArrayElement= 0;

          for(VkoDescriptorLayout *desc= (VkoDescriptorLayout *)layout->descriptors.first; desc; desc= (VkoDescriptorLayout *)desc->next) {
            copy.srcBinding= desc->binding;
            copy.dstBinding= desc->binding;

            copy.descriptorCount= desc->arrayCount;
            _vko->UpdateDescriptorSets(*_vko, 0, nullptr, 1, &copy);
          } /// for each descriptor

          // update src+dst segments data
          src->sets.release(set);
          src->freeSpc[src->freeSpcPeak]= oldSet;
          src->freeSpcPeak++;
          
          dst->sets.add(set);
          dst->freeSpcPeak--;
        } /// while there's space in p, and sets in l
      } /// loop thru last segments, backwards
  } /// loop thru first segments, forwards


  // free/delete empty segments - starting with second (never delete first segment)
  for(VkoDynamicSetSegment *p= (VkoDynamicSetSegment *)_segments.first->next; p; )
    if(p->freeSpcPeak== poolSize) {
      VkoDynamicSetSegment *toDel= p;
      p= (VkoDynamicSetSegment *)p->next;
      _delSegment(toDel);
      _segments.del(toDel);
    }
}











