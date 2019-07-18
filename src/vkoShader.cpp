#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS 1
#endif

#include "../include/vkObject.h"


/* TODO:
  - [TOP PRIORITY] compute pipeline



*/


///====================================///
// -----===== VkoShader class =====----- //
///====================================///




VkoShader::VkoShader() {
  parent= nullptr;

  //nrDescriptorSets= 0;      SCRAPED
  //descriptorsLayout= nullptr;
  
  pipelineLayout= NULL;
  renderPass= NULL;

  vert= tesc= tese= geom= frag= comp= NULL;
  vertFile= tescFile= teseFile= geomFile= fragFile= compFile= nullptr;

  subpass= NULL;
  pipeline= NULL;

  /// input assembly
  _topology= VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST;
  _primitiveRestartEnable= false;

  _teseControlPoints= 1;
  _teseDomainOrigin= VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT;

  
  _dynamicViewports= 0;

  /// rasterization state
  _depthClampEnable= false;
  _rasterizerDiscardEnable= false;
  _polygonMode= VK_POLYGON_MODE_FILL;
  _cullMode= VK_CULL_MODE_BACK_BIT;
  _frontFace= VK_FRONT_FACE_COUNTER_CLOCKWISE;

  _depthBiasEnable= false;         // [def:false] [enable/disable] controls whether to bias fragment depth values
  _depthBiasConstantFactor= 0.0f;  // depthBiasConstantFactor is a scalar factor controlling the constant depth value added to each fragment.
  _depthBiasClamp= 0.0f;           // depthBiasClamp is the maximum (or minimum) depth bias of a fragment.
  _depthBiasSlopeFactor= 0.0f;     // depthBiasSlopeFactor is a scalar factor applied to a fragment’s slope in depth bias calculations.

  _lineWidth= 1.0f;

  // multisample antialiasing defaults

  _nrMultisamples= VK_SAMPLE_COUNT_1_BIT;  // in vulkan, setting it to 1 sample, basically disables it
  _sampleShadingEnable= false;             // can be used to enable Sample Shading. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap24.html#primsrast-sampleshading
  _minSampleShading= 1.0f;                 // specifies a minimum fraction of sample shading if sampleShadingEnable is set to VK_TRUE.
  _sampleMask= nullptr;
  for(uint32_t a= 0; a< VKO_SHADER_SAMPLE_MASK_MAX_SIZE; a++)
    _sampleMaskData[a]= 0;

  _alphaToCoverageEnable= false;
  _alphaToOneEnable= false;

  // depth / stencil
  _depthTestEnable= false;
  _depthTestWrite= false;
  _depthTestOp= VK_COMPARE_OP_LESS;
  _depthBoundsTestEnable= false;
  _depthBoundsConstMin= 0.0f;
  _depthBoundsConstMax= 1.0f;
  _depthBoundsDynamic= false;

  _stencilTestEnable= false;             // controls whether stencil testing is enabled. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-stencil

  // color blend
  _colorBlendLogicOpEnable= false;
  _colorBlendLogicOp= VK_LOGIC_OP_COPY;
  
  _colorBlendConstColor[0]= 0.0f,
  _colorBlendConstColor[1]= 0.0f,
  _colorBlendConstColor[2]= 0.0f,
  _colorBlendConstColor[3]= 0.0f;
}


VkoShader::~VkoShader() {
  destroy();
  if(vertFile) delete[] vertFile;
  if(tescFile) delete[] tescFile;
  if(teseFile) delete[] teseFile;
  if(geomFile) delete[] geomFile;
  if(fragFile) delete[] fragFile;
  if(compFile) delete[] compFile;

}


void VkoShader::destroy() {
  if(parent)
    if(parent->device) {

      /* SCRAPED
    if(descriptorsLayout) {
      for(uint32_t a= 0; a< nrDescriptorSets; a++)
        if(descriptorsLayout[a])
          parent->vk->DestroyDescriptorSetLayout(*parent, descriptorsLayout[a], *parent);
      delete[] descriptorsLayout;
      descriptorsLayout= nullptr;
      nrDescriptorSets= 0;
    }
    */
    if(pipelineLayout) { parent->DestroyPipelineLayout(*parent, pipelineLayout, *parent); pipelineLayout= NULL; }
  }
}



/*
void VkoShader::addDescriptor(uint32_t in_set, uint32_t in_binding, VkDescriptorType in_type, uint32_t in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler) {
  _Descriptor *p= new _Descriptor;
  if(p== nullptr) { error.alloc(__FUNCTION__); return; }

  p->set= in_set;
  p->binding= in_binding;
  p->type= in_type;
  p->count= in_count;
  p->shaderStages= in_stages;
  p->pImutableSamplers= in_pImutableSampler;
  _descriptors.add(p);
}


void VkoShader::addDescriptor(const VkoDescriptor *in_desc) {
  _Descriptor *p= new _Descriptor;
  if(p== nullptr) { error.alloc(__FUNCTION__); return; }

  p->set= in_desc->set;
  p->binding= in_desc->binding;
  p->type= in_desc->type;
  p->count= in_desc->arrayCount;
  p->shaderStages= in_desc->shaderStages;
  p->pImutableSamplers= in_desc->pImutableSamplers;

  _descriptors.add(p);
}



void VkoShader::addUniformBlock() {
  addDescriptor(0, 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_ALL);
}



void VkoShader::setDescriptorSetFlags(uint32_t in_set, VkDescriptorSetLayoutCreateFlags in_flags) {
  _DescriptorSetFlags *p= nullptr;
  /// search maybe there are flags already for this set
  for(p= (_DescriptorSetFlags *)_descriptorSetFlags.first; p; p= (_DescriptorSetFlags *)p->next)
    if(p->set== in_set)
      break;

  /// there are existing flags for this set ... should pop an error imho
  if(p)
    p->flags= p->flags| in_flags;

  // create flags for this set
  else {
    p= new _DescriptorSetFlags;
    p->set= in_set;
    p->flags= in_flags;
  }
}

*/


void VkoShader::addDescriptorSet(const VkoSet *in_set) {
  _SetLayout *p= new _SetLayout;
  p->layout= in_set->layout;
  _setLayouts.add(p);
}


void VkoShader::addDescriptorSet(const VkDescriptorSetLayout in_layout) {
  _SetLayout *p= new _SetLayout;
  p->layout= in_layout;
  _setLayouts.add(p);
}




void VkoShader::addPushConsts(uint32_t in_nrBytes, uint32_t in_offset, VkShaderStageFlags in_stages) {
  _PushConsts *p= new _PushConsts;

  p->nrBytes= in_nrBytes;
  p->offset= in_offset;
  p->shaderStages= in_stages;

  _pushConsts.add(p);
}


void VkoShader::addSpecializationConst(uint32_t in_ID, VkShaderStageFlags in_stage, uint32_t in_size, void *in_value) {
  _SpecConst *c= new _SpecConst;      // c will be the created _SpecConst
  /// p will point to the last spec const in that shader stage (used to compute the offset)
  _SpecConst *p= nullptr;
  for(_SpecConst *s= (_SpecConst *)_specConsts.first; s; s= (_SpecConst *)s->next)
    if(s->stage== in_stage)
      p= s;

  c->id= in_ID;
  c->stage= in_stage;
  c->size= in_size;

  c->offset= (p? p->offset+ p->size: 0);
  
  c->value= new uint8_t[in_size];
  vkObject::_memcpy(c->value, in_value, in_size);
  
  _specConsts.add(c);
}




void VkoShader::addVertexBinding(uint32_t in_binding, uint32_t in_stride, VkVertexInputRate in_rate) {
  _VertBinding *v= new _VertBinding;
  v->binding= in_binding;
  v->stride= in_stride;
  v->rate= in_rate;
  _vertBindings.add(v);
}


void VkoShader::addVertexAttribute(uint32_t in_location, uint32_t in_binding, VkFormat in_format, uint32_t in_offset) {
  _VertAttribs *v= new _VertAttribs;
  v->location= in_location;
  v->binding= in_binding;
  v->format= in_format;
  v->offset= in_offset;
  _vertAttribs.add(v);
}



void VkoShader::setConstantViewport(const VkViewport *in_v, const VkRect2D *in_scissor) {
  _ConstViewport *c= new _ConstViewport;
  c->view= *in_v;
  c->scissor= *in_scissor;
  _constViewports.add(c);
  //dynamicViewports= false;
}


void VkoShader::setConstantViewport2(float x0, float y0, float dx, float dy, float minDepth, float maxDepth, float scissorX0, float scissorY0, float scissorDx, float scissorDy) {
  _ConstViewport *c= new _ConstViewport;
  c->view.x= x0;
  c->view.y= y0;
  c->view.width= dx;
  c->view.height= dy;
  c->view.minDepth= minDepth;
  c->view.maxDepth= maxDepth;
  c->scissor.offset.x= (int32_t)scissorX0;
  c->scissor.offset.y= (int32_t)scissorY0;
  c->scissor.extent.width= (uint32_t)scissorDx;
  c->scissor.extent.height= (uint32_t)scissorDy;
  _constViewports.add(c);
  //dynamicViewports= false;
}




void VkoShader::setDepthTest(bool in_enableDT, bool in_enableDW, VkCompareOp in_depthOp, bool in_enableDB, float in_min, float in_max) {
  _depthTestEnable= in_enableDT;
  _depthTestWrite= in_enableDW;
  _depthTestOp= in_depthOp;
  _depthBoundsTestEnable= in_enableDB;
  _depthBoundsConstMin= in_min;
  _depthBoundsConstMax= in_max;
}


void VkoShader::setStencilTestFrontOp(VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp, uint32_t compareMask, uint32_t writeMask, uint32_t reference) {
  _stencilTestOpFront.failOp= failOp;
  _stencilTestOpFront.passOp= passOp;
  _stencilTestOpFront.depthFailOp= depthFailOp;
  _stencilTestOpFront.compareOp= compareOp;
  _stencilTestOpFront.compareMask= compareMask;
  _stencilTestOpFront.writeMask= writeMask;
  _stencilTestOpFront.reference= reference;
}


void VkoShader::setStencilTestBackOp(VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp, uint32_t compareMask, uint32_t writeMask, uint32_t reference) {
  _stencilTestOpBack.failOp= failOp;
  _stencilTestOpBack.passOp= passOp;
  _stencilTestOpBack.depthFailOp= depthFailOp;
  _stencilTestOpBack.compareOp= compareOp;
  _stencilTestOpBack.compareMask= compareMask;
  _stencilTestOpBack.writeMask= writeMask;
  _stencilTestOpBack.reference= reference;
}


void VkoShader::setColorBlend(bool in_enableLogicOp, VkLogicOp in_logicOp, const float *in_constColor) {
  _colorBlendLogicOpEnable= in_enableLogicOp;
  _colorBlendLogicOp= in_logicOp;
  if(in_constColor)
    _colorBlendConstColor[0]= in_constColor[0],
    _colorBlendConstColor[1]= in_constColor[1],
    _colorBlendConstColor[2]= in_constColor[2],
    _colorBlendConstColor[3]= in_constColor[3];
}


void VkoShader::addColorBlendAttachement(bool blendEnable, VkBlendFactor srcBlendFactor, VkBlendFactor dstBlendFactor, VkBlendOp blendOp, VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp alphaBlendOp, VkColorComponentFlags colorWriteMask) {
  _ColorBlendAttachment *p= new _ColorBlendAttachment;
  p->att.blendEnable= blendEnable;
  p->att.srcColorBlendFactor= srcBlendFactor;
  p->att.dstColorBlendFactor= dstBlendFactor;
  p->att.colorBlendOp= blendOp;
  p->att.srcAlphaBlendFactor= srcAlphaBlendFactor;
  p->att.dstAlphaBlendFactor= dstAlphaBlendFactor;
  p->att.alphaBlendOp= alphaBlendOp;
  p->att.colorWriteMask= colorWriteMask;
  _colorBlendAttachements.add(p);
}


void VkoShader::addColorBlendAttachement2(const VkPipelineColorBlendAttachmentState *in_att) {
  _ColorBlendAttachment *p= new _ColorBlendAttachment;
  p->att= *in_att;
  _colorBlendAttachements.add(p);
}


void VkoShader::addDynamicState(VkDynamicState in_dyn) {
  /// search to see if already added
  for(_DynamicState *f= (_DynamicState *)_dynamicStates.first; f; f= (_DynamicState *)f->next)
    if(f->dyn== in_dyn)
      return;

  /// not found, add it
  _DynamicState *p= new _DynamicState; p->dyn= in_dyn; _dynamicStates.add(p);
}


/*
void VkoShader::_vkCreateDescriptorsLayout() {
  /// https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#descriptorsets-sets

  // from the specs:
  //  "The maximum binding number specified should be as compact as possible to avoid wasted memory."

  // can be multiple sets, each set can have muliple bindings
  // the layout will find the maximum existing bindings, from what i am digging thru these hieroglyphs

  _Descriptor *p= nullptr;
  uint32_t nrSets= 0, nrBindings;
  VkDescriptorSetLayoutBinding *bindings= nullptr;


  /// find out how many sets there are
  for(p= (_Descriptor *)_descriptors.first; p; p= (_Descriptor *)p->next)
    if((p->set+ 1)> nrSets)
      nrSets= p->set+ 1;

  nrDescriptorSets= nrSets;

  descriptorsLayout= new VkDescriptorSetLayout[nrSets];
  if(descriptorsLayout== nullptr) { error.detail("descriptorsLayout mem alloc failed. aborting.", __FUNCTION__); goto Exit; }

  /// loop thru all sets
  for(uint32_t a= 0; a< nrSets; a++) {
    /// find out how many bindings are in this set (set:a)
    nrBindings= 0;
    for(p= (_Descriptor *)_descriptors.first; p; p= (_Descriptor *)p->next)
      if((p->binding+ 1)> nrBindings)
        nrBindings= p->binding+ 1;

    if(nrBindings== 0) { error.detail("nr bindings found, is zero. aborting.", __FUNCTION__); goto Exit; }

    bindings= new VkDescriptorSetLayoutBinding[nrBindings];
    if(bindings== nullptr) { error.detail("mem alloc error (bindings)", __FUNCTION__); goto Exit; }

    /// loop thru all bindings in this set
    for(uint32_t b= 0; b< nrBindings; b++) {
      /// find descritor with set:a and binding:b
      for(p= (_Descriptor *)_descriptors.first; p; p= (_Descriptor *)p->next)
        if(p->set== a && p->binding== b)
          break;

      if(p== nullptr) { error.detail("binding not found. list is not complete and gap-less?. aborting.", __FUNCTION__); goto Exit; }

      bindings[b].binding=            p->binding;
      bindings[b].descriptorCount=    p->count;
      bindings[b].descriptorType=     p->type;
      bindings[b].stageFlags=         p->shaderStages;
      bindings[b].pImmutableSamplers= p->pImutableSamplers;
    }

    VkDescriptorSetLayoutCreateFlags flags= 0;
    for(_DescriptorSetFlags *p= (_DescriptorSetFlags *)_descriptorSetFlags.first; p; p= (_DescriptorSetFlags *)p->next)
      if(p->set== a) {
        flags= p->flags;
        break;
      }

    // create the descriptor set
    VkDescriptorSetLayoutCreateInfo setInfo;
    setInfo.sType= VK_STRUCTURE_TYPE_DESCRIPTOR_SET_LAYOUT_CREATE_INFO;
    setInfo.pNext= nullptr;
    setInfo.flags= flags; // VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR - specifies that descriptor sets must not be allocated using this layout, and descriptors are instead pushed by vkCmdPushDescriptorSetKHR
    setInfo.bindingCount= nrBindings;
    setInfo.pBindings= bindings;
    
    if(parent->vk->CreateDescriptorSetLayout(*parent, &setInfo, *parent, &descriptorsLayout[a])!= VK_SUCCESS) {
      error.detail(str8().f("Vulkan descriptor set[%d] layout create failed", a), __FUNCTION__, __LINE__);
      descriptorsLayout[a]= nullptr;
    }

    if(bindings) delete[] bindings;
    bindings= nullptr;
  }

Exit:
  if(bindings) delete[] bindings;
}
*/


void VkoShader::_vkCreatePipelineLayout() {

  // push constants will be defined here

  // "Push constants represent a high speed path to modify constant data in pipelines that is expected to outperform memory-backed resource updates"
  // i think these are basically old uniforms, but it seems they're faster. you set their layout in the shader.
  // (INITIALLY I THOUT THEY'RE HIGHER UNIFORMS FOR THE WHOLE PIPELINE, NOT TIED TO ANY SHADER, TO BE CHECKED BUT I THINK IT'S WRONG)
  // these ranges are basically tied to the shader TYPES, you must not have 2 ranges that are on the same stage flag, even if combined with another

  VkPushConstantRange *pcRange= nullptr;               // INIT 1
  VkDescriptorSetLayout *setLayout= nullptr;           // INIT 2

  /// populate all push consts ranges
  if(_pushConsts.nrNodes) {
    pcRange= new VkPushConstantRange[_pushConsts.nrNodes];

    _PushConsts *p= (_PushConsts *)_pushConsts.first;           // ALLOC 1
    for(uint32_t a= 0; p; p= (_PushConsts *)p->next, a++)
      pcRange[a].stageFlags= p->shaderStages,
      pcRange[a].size= p->nrBytes,
      pcRange[a].offset= p->offset;
  }

  /// populate all set layouts
  if(_setLayouts.nrNodes) {
    setLayout= new VkDescriptorSetLayout[_setLayouts.nrNodes];  // ALLOC 2

    _SetLayout *p= (_SetLayout *)_setLayouts.first;
    for(uint32_t a= 0; p; p= (_SetLayout *)p->next, a++)
      setLayout[a]= p->layout;
  }

  /// populate create info struct
  VkPipelineLayoutCreateInfo plci;    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkPipelineLayoutCreateInfo
  plci.sType= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  plci.pNext= nullptr;
  plci.flags= 0;
  plci.setLayoutCount= _setLayouts.nrNodes;
  plci.pSetLayouts= setLayout;
  plci.pushConstantRangeCount= _pushConsts.nrNodes;
  plci.pPushConstantRanges= pcRange;

  parent->errorCheck(parent->CreatePipelineLayout(*parent, &plci, *parent, &pipelineLayout),
    __FUNCTION__": Shader Pipeline layout creation failed.");

  if(pcRange)   delete[] pcRange;     // DEALLOC 1
  if(setLayout) delete[] setLayout;   // DEALLOC 2
}




bool VkoShader::loadModule(const char *in_file, VkShaderModule *out_module) {
  #ifdef VKO_BE_CHATTY
  bool chatty= true;
  #endif

  *out_module= NULL;
  parent->clearError();

  /// tmp vars
  uint8_t *buf= nullptr;
  int64_t fs= 0;
  int64_t pos;
  FILE *f= nullptr;
  bool ret= false;

  // file open & read into mem
  f= fopen(in_file, "rb");
  if(f== nullptr) { parent->errorText= __FUNCTION__": file not found. aborting."; goto Exit; }

  /// file size
  pos= ftell(f);
  fseek(f, 0, SEEK_END);
  fs= ftell(f);
  fseek(f, pos, SEEK_SET);

  #ifdef VKO_BE_CHATTY
  if(chatty) printf("opening file[%s] [%lld]bytes\n", in_file, fs);
  #endif

  if(fs<= 0) { parent->errorText= __FUNCTION__": filesize is <= 0. aborting."; goto Exit; }
  if((fs% 4) != 0) { parent->errorText= __FUNCTION__": shader filesize is not divisible by 4. aborting."; goto Exit; }

  buf= new uint8_t[fs];
  if(buf== nullptr) { parent->errorText= __FUNCTION__": buffer allocation failed"; goto Exit; }
  if(fread(buf, 1, fs, f)!= fs) { parent->errorText= __FUNCTION__": file read error. aborting"; goto Exit; }

  fclose(f); f= nullptr;

  // vulkan shader module creation
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap8.html#shader-modules
  VkShaderModuleCreateInfo smci;
  smci.sType= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  smci.pNext= nullptr;
  smci.flags= 0;
  smci.pCode= (const uint32_t *)buf;
  smci.codeSize= (size_t)fs;                // <<< must be divisible by 4

  if(!parent->errorCheck(parent->CreateShaderModule(*parent, &smci, *parent, out_module), __FUNCTION__": Shader module create failed")) {
    *out_module= NULL;
    goto Exit;
  }

  ret= true;

  Exit:
  if(f) fclose(f);
  if(buf) delete[] buf;
  return ret;
}


bool VkoShader::loadModules(const char *in_vert, const char *in_tesc, const char *in_tese, const char *in_geom, const char *in_frag, const char *in_comp) {
  if(in_vert) if(!loadModuleVert(in_vert)) return false;
  if(in_tesc) if(!loadModuleTesc(in_tesc)) return false;
  if(in_tese) if(!loadModuleTese(in_tese)) return false;
  if(in_geom) if(!loadModuleGeom(in_geom)) return false;
  if(in_frag) if(!loadModuleFrag(in_frag)) return false;
  if(in_comp) if(!loadModuleComp(in_comp)) return false;

  return true;
}


inline bool VkoShader::loadModuleVert(const char *in_vert) {
  if(loadModule(in_vert, &vert)) {
    vkObject::_strCopy((char **)&vertFile, in_vert);
    return true; }
  else
    return false;
}

inline bool VkoShader::loadModuleFrag(const char *in_frag) {
  if(loadModule(in_frag, &frag)) {
    vkObject::_strCopy((char **)&fragFile, in_frag);
    return true;
  } else
    return false;
}

inline bool VkoShader::loadModuleTesc(const char *in_tesc) {
  if(loadModule(in_tesc, &tese)) {
    vkObject::_strCopy((char **)&tescFile, in_tesc);
    return true;
  } else
    return false;
}

inline bool VkoShader::loadModuleTese(const char *in_tese) {
  if(loadModule(in_tese, &tese)) {
    vkObject::_strCopy((char **)&teseFile, in_tese);
    return true;
  } else
    return false;
}

inline bool VkoShader::loadModuleGeom(const char *in_geom) {
  if(loadModule(in_geom, &geom)) {
    vkObject::_strCopy((char **)&geomFile, in_geom);
    return true;
  } else
    return false;
}

inline bool VkoShader::loadModuleComp(const char *in_comp) {
  if(loadModule(in_comp, &comp)) {
    vkObject::_strCopy((char **)&compFile, in_comp);
    return true;
  } else
    return false;
}


void VkoShader::destroyModules() {
  if(parent->device== nullptr) return;
  if(vert) { parent->DestroyShaderModule(*parent, vert, *parent); vert= NULL; }
  if(tesc) { parent->DestroyShaderModule(*parent, tesc, *parent); tesc= NULL; }
  if(tese) { parent->DestroyShaderModule(*parent, tese, *parent); tese= NULL; }
  if(geom) { parent->DestroyShaderModule(*parent, geom, *parent); geom= NULL; }
  if(frag) { parent->DestroyShaderModule(*parent, frag, *parent); frag= NULL; }
  if(comp) { parent->DestroyShaderModule(*parent, comp, *parent); comp= NULL; }
}







void VkoShader::_vkPopulateSpecConsts(VkShaderStageFlags in_stage, VkSpecializationInfo *out_sConst) {
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap9.html#pipelines-specialization-constants
  /// count the number of spec consts for this shader stage + the data size of the buffer that will be sent
  out_sConst->dataSize= 0;
  out_sConst->mapEntryCount= 0;
  for(_SpecConst *p= (_SpecConst *)_specConsts.first; p; p= (_SpecConst *)p->next)
    if(p->stage== in_stage)
      out_sConst->dataSize+= p->size,
      out_sConst->mapEntryCount++;

  /// alloc mem
  if(out_sConst->mapEntryCount)
    out_sConst->pMapEntries= new VkSpecializationMapEntry[out_sConst->mapEntryCount];  // ALLOC 1 <<<<<<<<<<<<
  if(out_sConst->dataSize)
    out_sConst->pData= new uint8_t[out_sConst->dataSize];                                // ALLOC 2 <<<<<<<<<<<<

  // populate map entries + actual values of the spec consts
  uint32_t a= 0;
  for(_SpecConst *p= (_SpecConst *)_specConsts.first; p; p= (_SpecConst *)p->next)
    if(p->stage== in_stage) {
      ((VkSpecializationMapEntry *)out_sConst->pMapEntries)[a].constantID= p->id;
      ((VkSpecializationMapEntry *)out_sConst->pMapEntries)[a].offset=     p->offset;
      ((VkSpecializationMapEntry *)out_sConst->pMapEntries)[a].size=       p->size;
      vkObject::_memcpy(((uint8_t *)out_sConst->pData)+ p->offset, p->value, p->size);
      a++;
    }
}





bool VkoShader::build() {
  #define IX_MAX_SHADER_STAGES 6    // vert+tesc+tese+geom+frag+comp = 6; more can just be added
  parent->clearError();
  bool ret= false;
  VkPipelineShaderStageCreateInfo ssInfo[IX_MAX_SHADER_STAGES];
  VkSpecializationInfo sConsts[IX_MAX_SHADER_STAGES];
  uint32_t nrStages= 0;
  VkVertexInputAttributeDescription     *vertAttribs;           /// vertex attribs
  VkVertexInputBindingDescription       *vertBindings;          /// vertex bindings
  VkPipelineTessellationDomainOriginStateCreateInfo teseOrigin; /// tesselation origin
  VkPipelineViewportStateCreateInfo      viewports;             /// viewport state
  VkPipelineRasterizationStateCreateInfo raster;                /// rasterization state
  VkPipelineMultisampleStateCreateInfo   msAntiAlias;           /// multisample state
  VkPipelineDepthStencilStateCreateInfo  depthStencil;          /// depth / stencil tests
  VkPipelineColorBlendStateCreateInfo    colorBlend;            /// color blend
  VkPipelineColorBlendAttachmentState   *colorBlendAtt= nullptr;   /// color blend attachements
  VkPipelineDynamicStateCreateInfo       dynStates;             /// dynamic parts of the pipeline

  /// setting all allocation pointers to nullptr, to know if they are to be deallocated
  for(uint32_t a= 0; a< IX_MAX_SHADER_STAGES; a++)
    sConsts[a].pData= nullptr,             // INIT 1
    sConsts[a].pMapEntries= nullptr;       // INIT 2
  viewports.pViewports= nullptr;           // INIT 3
  viewports.pScissors= nullptr;            // INIT 4
  colorBlendAtt= nullptr;                  // INIT 5
  dynStates.pDynamicStates= nullptr;       // INIT 6
  vertAttribs= nullptr;                    // INIT 7
  vertBindings= nullptr;                   // INIT 8


  /// find out the number of stages that will be used
  /// add more possible stages if raytrace/ new stuff gets added
  if(vert) nrStages++;
  if(tesc) nrStages++;
  if(tese) nrStages++;
  if(geom) nrStages++;
  if(frag) nrStages++;
  if(comp) nrStages++;      // there's either comp or the others



  // if there's a compute module, then it's a compute shader
  // IS THIS OK? WOULD THIS BE ALL THAT IS NEEDED <<<<<<<<<<<<<<<<<<<<<,

  // COMPUTE pipeline
  if(comp) {
    
    VkComputePipelineCreateInfo compInfo;
    // MAKEME







  // GRAPHICS pipeline
  } else {
    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap9.html#pipelines-graphics
    //VkPipelineDynamicStateCreateInfo grInfo2;
    //grInfo2.
    
    VkGraphicsPipelineCreateInfo graphInfo;
    graphInfo.sType= VK_STRUCTURE_TYPE_GRAPHICS_PIPELINE_CREATE_INFO;
    graphInfo.pNext= nullptr;                         /// or an extension, atm none i think
    graphInfo.flags= 0;                            // https://www.khronos.org/registry/vulkan/specs/1.1/html/chap9.html#VkPipelineCreateFlagBits

    if(renderPass== NULL) { parent->errorText= __FUNCTION__": Vulkan renderpass not set. aborting."; goto Exit; }
    graphInfo.renderPass= renderPass;              // the renderpass
    graphInfo.subpass= subpass;                    // index of the subpass

    /// pipeline derivates - https://www.khronos.org/registry/vulkan/specs/1.1/html/chap9.html#pipelines-pipeline-derivatives
    /// set the flags to accept parent/childs
    graphInfo.basePipelineHandle= VK_NULL_HANDLE;  /// pipeline to derive from. (child/parent style)
    graphInfo.basePipelineIndex= 0;                /// index into the pCreateInfos parameter to use as a pipeline to derive from.

    //_vkCreateDescriptorsLayout();
    _vkCreatePipelineLayout();
    graphInfo.layout= pipelineLayout;              /// pipeline layout
    
  
    // pipeline shader stages https://www.khronos.org/registry/vulkan/specs/1.1/html/chap9.html#VkPipelineShaderStageCreateInfo
  
    if(nrStages) {
      /// common data shared thru all
      uint32_t a;
      for(a= 0; a< nrStages; a++)
        ssInfo[a].sType= VK_STRUCTURE_TYPE_PIPELINE_SHADER_STAGE_CREATE_INFO,
        ssInfo[a].pNext= nullptr,
        ssInfo[a].flags= 0;

      /// per stage specific data
      a= 0;
      if(vert) {
        ssInfo[a].module= vert;
        ssInfo[a].stage= VK_SHADER_STAGE_VERTEX_BIT;
        ssInfo[a].pName= "main";
        _vkPopulateSpecConsts(VK_SHADER_STAGE_VERTEX_BIT, &sConsts[a]);
        ssInfo[a].pSpecializationInfo= &sConsts[a];
        a++;
      }

      if(tesc) {
        ssInfo[a].module= tesc;
        ssInfo[a].stage= VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT;
        ssInfo[a].pName= "main";
        _vkPopulateSpecConsts(VK_SHADER_STAGE_TESSELLATION_CONTROL_BIT, &sConsts[a]);
        ssInfo[a].pSpecializationInfo= &sConsts[a];
        a++;
      }

      if(tese) {
        ssInfo[a].module= tese;
        ssInfo[a].stage= VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT;
        ssInfo[a].pName= "main";
        _vkPopulateSpecConsts(VK_SHADER_STAGE_TESSELLATION_EVALUATION_BIT, &sConsts[a]);
        ssInfo[a].pSpecializationInfo= &sConsts[a];
        a++;
      }

      if(geom) {
        ssInfo[a].module= geom;
        ssInfo[a].stage= VK_SHADER_STAGE_GEOMETRY_BIT;
        ssInfo[a].pName= "main";
        _vkPopulateSpecConsts(VK_SHADER_STAGE_GEOMETRY_BIT, &sConsts[a]);
        ssInfo[a].pSpecializationInfo= &sConsts[a];
        a++;
      }

      if(frag) {
        ssInfo[a].module= frag;
        ssInfo[a].stage= VK_SHADER_STAGE_FRAGMENT_BIT;
        ssInfo[a].pName= "main";
        _vkPopulateSpecConsts(VK_SHADER_STAGE_FRAGMENT_BIT, &sConsts[a]);
        ssInfo[a].pSpecializationInfo= &sConsts[a];
        a++;
      }

      if(comp) {
        ssInfo[a].module= comp;
        ssInfo[a].stage= VK_SHADER_STAGE_COMPUTE_BIT;
        ssInfo[a].pName= "main";
        _vkPopulateSpecConsts(VK_SHADER_STAGE_COMPUTE_BIT, &sConsts[a]);
        ssInfo[a].pSpecializationInfo= &sConsts[a];
        a++;
      }
    }
  
    graphInfo.stageCount= nrStages;
    graphInfo.pStages= ssInfo;

    
    // pipeline vertex input https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap20.html#VkPipelineVertexInputStateCreateInfo
    VkPipelineVertexInputStateCreateInfo pvisci;
    pvisci.sType= VK_STRUCTURE_TYPE_PIPELINE_VERTEX_INPUT_STATE_CREATE_INFO;
    pvisci.pNext= nullptr;
    pvisci.flags= 0;

    /// vertex bindings
    if(_vertAttribs.nrNodes) {
      vertAttribs= new VkVertexInputAttributeDescription[_vertAttribs.nrNodes];         // ALLOC 7
      uint32_t n= 0;
      for(_VertAttribs *v= (_VertAttribs *)_vertAttribs.first; v; v= (_VertAttribs *)v->next, n++)
        vertAttribs[n].binding=  v->binding,
        vertAttribs[n].format=   v->format,
        vertAttribs[n].location= v->location,
        vertAttribs[n].offset=   v->offset;
    }

    pvisci.vertexAttributeDescriptionCount= _vertAttribs.nrNodes;
    pvisci.pVertexAttributeDescriptions= vertAttribs;

    /// vertex attributes
    if(_vertBindings.nrNodes) {
      vertBindings= new VkVertexInputBindingDescription[_vertBindings.nrNodes];         // ALLOC 8
      uint32_t n= 0;
      for(_VertBinding *v= (_VertBinding *)_vertBindings.first; v; v= (_VertBinding *)v->next, n++)
        vertBindings[n].binding= v->binding,
        vertBindings[n].stride= v->stride,
        vertBindings[n].inputRate= v->rate;
    }

    pvisci.vertexBindingDescriptionCount= _vertBindings.nrNodes;
    pvisci.pVertexBindingDescriptions= vertBindings;

    graphInfo.pVertexInputState= &pvisci;


    // pipeline input asembly https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap19.html#VkPipelineInputAssemblyStateCreateInfo
    VkPipelineInputAssemblyStateCreateInfo piasci;
    piasci.sType= VK_STRUCTURE_TYPE_PIPELINE_INPUT_ASSEMBLY_STATE_CREATE_INFO;
    piasci.pNext= nullptr;
    piasci.flags= 0;
    piasci.primitiveRestartEnable= _primitiveRestartEnable;
    piasci.topology= _topology;
    
    graphInfo.pInputAssemblyState= &piasci;


    // pipeline teselation state - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap21.html#VkPipelineTessellationStateCreateInfo
    /// ignored if teselation shader stage is not created
    VkPipelineTessellationStateCreateInfo ptsci; 
    ptsci.sType= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_STATE_CREATE_INFO;
    ptsci.flags= 0;
    if(_teseDomainOrigin!= VK_TESSELLATION_DOMAIN_ORIGIN_UPPER_LEFT) {
      // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap21.html#VkPipelineTessellationDomainOriginStateCreateInfo
      teseOrigin.sType= VK_STRUCTURE_TYPE_PIPELINE_TESSELLATION_DOMAIN_ORIGIN_STATE_CREATE_INFO;
      teseOrigin.pNext= nullptr;
      teseOrigin.domainOrigin= _teseDomainOrigin;
      ptsci.pNext= &teseOrigin;
    } else 
      ptsci.pNext= nullptr;
    ptsci.patchControlPoints= _teseControlPoints;

    graphInfo.pTessellationState= &ptsci;
    
    // pipeline viewport - ignored if rasterization is disabled
    // https://www.khronos.org/registry/vulkan/specs/1.1/html/chap23.html#VkPipelineViewportStateCreateInfo
    viewports.sType= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewports.pNext= nullptr;
    viewports.flags= 0;

    // TO THINK ABOUT: MULTIPLE VIEWPORTS? WOULD SETTING THESE TO CONSTANT IN HERE BE BETTER?
    /// -when using dynamic state for the viewports (resizing windows, etc), the pointers are ignored, therefore nullptr
    ///  graphInfo.pDynamicState is the way to define dynamic viewports
    /// -if the viewports are static, maybe a fullscreen view, these can be populated.
    /// -i cannot find anywhere any impact on speed

    /// constant viewports
    if(_dynamicViewports== 0) {
      if(_constViewports.nrNodes== 0) {
        parent->errorText= __FUNCTION__": Shader pipeline creation failed: no constant or dynamic viewports were defined (use setDynamicViewport()/setConstViewport())";
        goto Exit;
      }
      viewports.viewportCount= _constViewports.nrNodes;
      viewports.scissorCount= _constViewports.nrNodes;
      viewports.pViewports= new VkViewport[viewports.viewportCount];      // ALLOC 3
      viewports.pScissors= new VkRect2D[viewports.scissorCount];          // ALLOC 4
      uint32_t a= 0;
      for(_ConstViewport *p= (_ConstViewport *)_constViewports.first; p; p= (_ConstViewport *)p->next)
        ((VkViewport *)viewports.pViewports)[a]= p->view,
        ((VkRect2D *)  viewports.pScissors)[a]=  p->scissor,
        a++;
    /// dynamic viewports
    } else
      viewports.viewportCount= _dynamicViewports,
      viewports.scissorCount= _dynamicViewports;

    graphInfo.pViewportState= &viewports;


    // pipeline rasterization state - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap24.html#VkPipelineRasterizationStateCreateInfo
    raster.sType= VK_STRUCTURE_TYPE_PIPELINE_RASTERIZATION_STATE_CREATE_INFO;
    raster.pNext= nullptr;                  /// extension (none atm)
    raster.flags= 0;                     /// reserved
    raster.depthClampEnable=        _depthClampEnable;        // "controls whether to clamp the fragment’s depth values as described in Depth Test. Enabling depth clamp will also disable clipping primitives to the z planes of the frustrum as described in Primitive Clipping."
    raster.rasterizerDiscardEnable= _rasterizerDiscardEnable; // "controls whether primitives are discarded immediately before the rasterization stage."
    raster.polygonMode=             _polygonMode;             // fill/line/point https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap24.html#VkPolygonMode
    raster.cullMode=                _cullMode;
    raster.frontFace=               _frontFace;
    raster.depthBiasEnable=         _depthBiasEnable;
    raster.depthBiasConstantFactor= _depthBiasConstantFactor;
    raster.depthBiasClamp=          _depthBiasClamp;
    raster.depthBiasSlopeFactor=    _depthBiasSlopeFactor;
    raster.lineWidth=               _lineWidth;

    graphInfo.pRasterizationState= &raster;

    // pipeline multisample - ignored if rasterization is disabled
    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap24.html#VkPipelineMultisampleStateCreateInfo
    msAntiAlias.sType= VK_STRUCTURE_TYPE_PIPELINE_MULTISAMPLE_STATE_CREATE_INFO;
    msAntiAlias.pNext= nullptr;
    msAntiAlias.flags= 0;
    msAntiAlias.rasterizationSamples=  _nrMultisamples;
    msAntiAlias.sampleShadingEnable=   _sampleShadingEnable;
    msAntiAlias.minSampleShading=      _minSampleShading;
    msAntiAlias.pSampleMask=           _sampleMask;

    msAntiAlias.alphaToCoverageEnable= _alphaToCoverageEnable;
    msAntiAlias.alphaToOneEnable=      _alphaToOneEnable;

    graphInfo.pMultisampleState= &msAntiAlias;


    // depth / stencil - ignored if rasterization is disabled OR renderpass has no depth/stencil atachement
    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#VkPipelineDepthStencilStateCreateInfo
    depthStencil.sType= VK_STRUCTURE_TYPE_PIPELINE_DEPTH_STENCIL_STATE_CREATE_INFO;
    depthStencil.pNext= nullptr;
    depthStencil.flags= 0;
    depthStencil.depthTestEnable=       _depthTestEnable;
    depthStencil.depthWriteEnable=      _depthTestWrite;
    depthStencil.depthCompareOp=        _depthTestOp;
    depthStencil.depthBoundsTestEnable= _depthBoundsTestEnable;
    depthStencil.stencilTestEnable=     _stencilTestEnable;
    depthStencil.front=                 _stencilTestOpFront;
    depthStencil.back=                  _stencilTestOpBack;
    depthStencil.minDepthBounds=        _depthBoundsConstMin;
    depthStencil.maxDepthBounds=        _depthBoundsConstMax;
    graphInfo.pDepthStencilState= &depthStencil;

    // color blend - https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap26.html#VkPipelineColorBlendStateCreateInfo
    colorBlend.sType= VK_STRUCTURE_TYPE_PIPELINE_COLOR_BLEND_STATE_CREATE_INFO;
    colorBlend.pNext= nullptr;
    colorBlend.flags= 0;
    colorBlend.logicOpEnable=     _colorBlendLogicOpEnable;
    colorBlend.logicOp=           _colorBlendLogicOp;
    colorBlend.blendConstants[0]= _colorBlendConstColor[0];
    colorBlend.blendConstants[1]= _colorBlendConstColor[1];
    colorBlend.blendConstants[2]= _colorBlendConstColor[2];
    colorBlend.blendConstants[3]= _colorBlendConstColor[3];
    colorBlend.attachmentCount=   _colorBlendAttachements.nrNodes;
    if(colorBlend.attachmentCount) {
      colorBlendAtt= new VkPipelineColorBlendAttachmentState[colorBlend.attachmentCount]; // ALLOC 5
      uint32_t a= 0;
      for(_ColorBlendAttachment *p= (_ColorBlendAttachment *)_colorBlendAttachements.first; p; p= (_ColorBlendAttachment *)p->next)
        colorBlendAtt[a++]= p->att;
    } 
    
    colorBlend.pAttachments= colorBlendAtt;

    graphInfo.pColorBlendState= &colorBlend;

    // pipeline dynamic states
    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap9.html#VkPipelineDynamicStateCreateInfo
    /// everything defined in here, is considered dynamic, changed by vkCmd funcs in the command buffer.
    /// the constant variants are ingored
    
    dynStates.sType= VK_STRUCTURE_TYPE_PIPELINE_DYNAMIC_STATE_CREATE_INFO;
    dynStates.pNext= nullptr;
    dynStates.flags= 0;
    dynStates.dynamicStateCount= _dynamicStates.nrNodes;
    if(dynStates.dynamicStateCount) {
      dynStates.pDynamicStates= new VkDynamicState[dynStates.dynamicStateCount];        // ALLOC 6
      uint32_t a= 0;
      for(_DynamicState *p= (_DynamicState *)_dynamicStates.first; p; p= (_DynamicState *)p->next)
        ((VkDynamicState *)dynStates.pDynamicStates)[a++]= p->dyn;
    }

    graphInfo.pDynamicState= &dynStates; // This can be NULL, which means no state in the pipeline is considered dynamic.
    
      
    // pipeline cache is VK_NULL_HANDLE, ATM
    if(!parent->errorCheck(parent->CreateGraphicsPipelines(*parent, VK_NULL_HANDLE, 1, &graphInfo, *parent, &pipeline), __FUNCTION__": Vulkan pipeline creation failed")) {
      pipeline= NULL;
      goto Exit;
    }
  } /// compute / graphics pipeline

  ret= true; // success

  Exit:

  for(uint32_t a= 0; a< IX_MAX_SHADER_STAGES; a++) {
    if(sConsts[a].pMapEntries)
      delete[] sConsts[a].pMapEntries;    // DEALLOC 1 (in vkPopulateSpecConsts())
    if(sConsts[a].pData)
      delete[] sConsts[a].pData;          // DEALLOC 2 (in vkPopulateSpecConsts())
  }
  if(viewports.pViewports)
    delete[] viewports.pViewports;        // DEALLOC 3 (const viewports)
  if(viewports.pScissors)
    delete[] viewports.pScissors;         // DEALLOC 4 (const viewports)
  if(colorBlendAtt)
    delete[] colorBlendAtt;               // DEALLOC 5
  if(dynStates.pDynamicStates)
    delete[] dynStates.pDynamicStates;    // DEALLOC 6
  if(vertAttribs)
    delete[] vertAttribs;                 // DEALLOC 7
  if(vertBindings)
    delete[] vertBindings;                // DEALLOC 8

  //this->destroyModules();

  #undef IX_MAX_SHADER_STAGES
  return ret;
}







