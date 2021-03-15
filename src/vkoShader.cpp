#include "../include/vkObject.h"
#include <stdio.h>

/* TODO:
  - [TOP PRIORITY] compute pipeline



*/


///====================================///
// -----===== VkoShader class =====----- //
///====================================///




VkoShader::VkoShader(vkObject *in_parent): _vko(in_parent) {

  pipeline= VK_NULL_HANDLE;
  pipelineLayout= VK_NULL_HANDLE;
  vert= tesc= tese= geom= frag= comp= VK_NULL_HANDLE;

  descSet= nullptr;           // INIT 1
  vertFile= tescFile= teseFile= geomFile= fragFile= compFile= nullptr;  // INIT 2, 3, 4, 5, 6, 7

  delData();
}


VkoShader::~VkoShader() {
  delData();
}


void VkoShader::delData() {
  if(pipeline || pipelineLayout) destroy();
  
  if(descSet)  { delete[] descSet;  descSet=  nullptr; } // DEALLOC 1

  if(vertFile) { delete[] vertFile; vertFile= nullptr; } // DEALLOC 2
  if(tescFile) { delete[] tescFile; tescFile= nullptr; } // DEALLOC 3
  if(teseFile) { delete[] teseFile; teseFile= nullptr; } // DEALLOC 4
  if(geomFile) { delete[] geomFile; geomFile= nullptr; } // DEALLOC 5
  if(fragFile) { delete[] fragFile; fragFile= nullptr; } // DEALLOC 6
  if(compFile) { delete[] compFile; compFile= nullptr; } // DEALLOC 7

  // default values

  pNext.delData();

  renderPass= VK_NULL_HANDLE;
  subpass= VK_NULL_HANDLE;
  nrDescSets= 0;

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
  
  // <failOp> is a VkStencilOp value specifying the action performed on samples that fail the stencil test.
  // <passOp> is a VkStencilOp value specifying the action performed on samples that pass both the depth and stencil tests.
  // <depthFailOp> is a VkStencilOp value specifying the action performed on samples that pass the stencil test and fail the depth test.
  // <compareOp> is a VkCompareOp value specifying the comparison operator used in the stencil test.
  // <compareMask> selects the bits of the unsigned integer stencil values participating in the stencil test.
  // <writeMask> selects the bits of the unsigned integer stencil values updated by the stencil test in the stencil framebuffer attachment.
  // <reference> is an integer reference value that is used in the unsigned stencil comparison.
  
  _stencilTestOpBack= {};
  _stencilTestOpFront= {};
  
  
  // color blend
  _colorBlendLogicOpEnable= false;
  _colorBlendLogicOp= VK_LOGIC_OP_COPY;
  
  _colorBlendConstColor[0]= 0.0f,
  _colorBlendConstColor[1]= 0.0f,
  _colorBlendConstColor[2]= 0.0f,
  _colorBlendConstColor[3]= 0.0f;
}


void VkoShader::destroy() {
  if(_vko)
    if(_vko->device) {
      _destroyModules();
      if(pipelineLayout) _vko->DestroyPipelineLayout(*_vko, pipelineLayout, *_vko);
      if(pipeline)       _vko->DestroyPipeline(*_vko, pipeline, *_vko);
    }

  pipelineLayout= 0;
  pipeline= 0;
}




VkoDescriptorSetLayout *VkoShader::addDescriptorSet(VkDescriptorSetLayoutCreateFlags in_flags) {
  VkoDescriptorSetLayout *p= _vko->objects.addDescriptorSetLayout();
  p->cfgDescriptorSetFlags(in_flags);

  addDescriptorSetFromExisting(p);

  return p;
}


void VkoShader::addDescriptor(uint32_t in_set, uint32_t in_binding, VkDescriptorType in_type, uint32_t in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler) {
  _vko->clearError();
  if(descSet== nullptr) { _vko->result= VK_INCOMPLETE, _vko->errorText= "no descriptor set was added prior"; return; }
  if(in_set> nrDescSets- 1) { _vko->result= VK_INCOMPLETE, _vko->errorText= "<in_set> greater than current number of sets"; return; }

  descSet[in_set]->cfgAddDescriptor(in_binding, in_type, in_count, in_stages, in_pImutableSampler);
}


void VkoShader::addDescriptorSetFromExisting(VkoDescriptorSetLayout *in_set) {

  nrDescSets++;

  VkoDescriptorSetLayout **newLayouts= new VkoDescriptorSetLayout*[nrDescSets];

  /// copy the old list to the new one
  if(nrDescSets> 1)
    for(uint32_t a= 0; a< nrDescSets- 1; a++)
      newLayouts[a]= descSet[a];
  
  newLayouts[nrDescSets- 1]= in_set;/// add the new member
  
  if(descSet) delete[] descSet;     /// delete the old list

  descSet= newLayouts;              /// update the descSet list

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
  if(nrDescSets) {
    setLayout= new VkDescriptorSetLayout[nrDescSets];           // ALLOC 2

    for(uint32_t a= 0; a< nrDescSets; a++) {
      if(descSet[a]->layout== 0) descSet[a]->build();
      setLayout[a]= descSet[a]->layout;
    }
  }

  /*
  if(_setLayouts.nrNodes) {
    setLayout= new VkDescriptorSetLayout[_setLayouts.nrNodes];  // ALLOC 2

    _SetLayout *p= (_SetLayout *)_setLayouts.first;
    for(uint32_t a= 0; p; p= (_SetLayout *)p->next, a++)
      setLayout[a]= p->layout;
  }
  */

  /// populate create info struct
  VkPipelineLayoutCreateInfo plci;    // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkPipelineLayoutCreateInfo
  plci.sType= VK_STRUCTURE_TYPE_PIPELINE_LAYOUT_CREATE_INFO;
  plci.pNext= pNext.VkPipelineLayoutCreateInfo;
  plci.flags= 0;
  plci.setLayoutCount= nrDescSets;  //_setLayouts.nrNodes;
  plci.pSetLayouts= setLayout;
  plci.pushConstantRangeCount= _pushConsts.nrNodes;
  plci.pPushConstantRanges= pcRange;

  _vko->errorCheck(_vko->CreatePipelineLayout(*_vko, &plci, *_vko, &pipelineLayout),
    "VkoShader::_vkCreatePipelineLayout(): Shader Pipeline layout creation failed.");

  if(pcRange)   delete[] pcRange;     // DEALLOC 1
  if(setLayout) delete[] setLayout;   // DEALLOC 2
}


bool VkoShader::_loadModules() {
  if(vertFile) if(!_loadModule(vertFile, &vert)) return false;
  if(tescFile) if(!_loadModule(tescFile, &tesc)) return false;
  if(teseFile) if(!_loadModule(teseFile, &tese)) return false;
  if(geomFile) if(!_loadModule(geomFile, &geom)) return false;
  if(fragFile) if(!_loadModule(fragFile, &frag)) return false;
  if(compFile) if(!_loadModule(compFile, &comp)) return false;
  return true;
}

void VkoShader::_destroyModules() {
  if(_vko->device== nullptr) return;
  if(vert) { _vko->DestroyShaderModule(*_vko, vert, *_vko); vert= VK_NULL_HANDLE; }
  if(tesc) { _vko->DestroyShaderModule(*_vko, tesc, *_vko); tesc= VK_NULL_HANDLE; }
  if(tese) { _vko->DestroyShaderModule(*_vko, tese, *_vko); tese= VK_NULL_HANDLE; }
  if(geom) { _vko->DestroyShaderModule(*_vko, geom, *_vko); geom= VK_NULL_HANDLE; }
  if(frag) { _vko->DestroyShaderModule(*_vko, frag, *_vko); frag= VK_NULL_HANDLE; }
  if(comp) { _vko->DestroyShaderModule(*_vko, comp, *_vko); comp= VK_NULL_HANDLE; }
}



bool VkoShader::_loadModule(const char *in_file, VkShaderModule *out_module) {
  #ifdef VKO_BE_CHATTY
  bool chatty= true;
  #endif

  *out_module= NULL;
  _vko->clearError();

  /// tmp vars
  uint8_t *buf= nullptr;
  int64_t fs= 0;
  int64_t pos;
  FILE *f= nullptr;
  bool ret= false;

  // file open & read into mem
  f= fopen(in_file, "rb");
  if(f== nullptr) { _vko->errorText= "VkoShader::_loadModule(): file not found. aborting."; goto Exit; }

  /// file size
  pos= ftell(f);
  fseek(f, 0, SEEK_END);
  fs= ftell(f);
  fseek(f, (long)pos, SEEK_SET);

  #ifdef VKO_BE_CHATTY
  if(chatty) printf("opening file[%s] [%lld]bytes\n", in_file, fs);
  #endif

  if(fs<= 0) { _vko->errorText= "VkoShader::_loadModule(): filesize is <= 0. aborting."; goto Exit; }
  if((fs% 4) != 0) { _vko->errorText= "VkoShader::_loadModule(): shader filesize is not divisible by 4. aborting."; goto Exit; }

  buf= new uint8_t[fs];
  if(buf== nullptr) { _vko->errorText= "VkoShader::_loadModule(): buffer allocation failed"; goto Exit; }
  if(fread(buf, 1, fs, f)!= fs) { _vko->errorText= "VkoShader::_loadModule(): file read error. aborting"; goto Exit; }

  fclose(f); f= nullptr;

  // vulkan shader module creation
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap8.html#shader-modules
  VkShaderModuleCreateInfo smci;
  smci.sType= VK_STRUCTURE_TYPE_SHADER_MODULE_CREATE_INFO;
  smci.pNext= pNext.VkShaderModuleCreateInfo;
  smci.flags= 0;
  smci.pCode= (const uint32_t *)buf;
  smci.codeSize= (size_t)fs;                // <<< must be divisible by 4

  if(!_vko->errorCheck(_vko->CreateShaderModule(*_vko, &smci, *_vko, out_module), "VkoShader::_loadModule(): Shader module create failed")) {
    *out_module= NULL;
    goto Exit;
  }

  ret= true;

  Exit:
  if(f) fclose(f);
  if(buf) delete[] buf;
  return ret;
}


void VkoShader::loadModules(const char *in_vert, const char *in_tesc, const char *in_tese, const char *in_geom, const char *in_frag, const char *in_comp) {
  if(in_vert) loadModuleVert(in_vert);
  if(in_tesc) loadModuleTesc(in_tesc);
  if(in_tese) loadModuleTese(in_tese);
  if(in_geom) loadModuleGeom(in_geom);
  if(in_frag) loadModuleFrag(in_frag);
  if(in_comp) loadModuleComp(in_comp);
}


void VkoShader::loadModuleVert(const char *in_vert) {
  vkObject::_strCopy((char **)&vertFile, in_vert);
}

void VkoShader::loadModuleFrag(const char *in_frag) {
  vkObject::_strCopy((char **)&fragFile, in_frag);
}

void VkoShader::loadModuleTesc(const char *in_tesc) {
  vkObject::_strCopy((char **)&tescFile, in_tesc);
}

void VkoShader::loadModuleTese(const char *in_tese) {
  vkObject::_strCopy((char **)&teseFile, in_tese);
}

void VkoShader::loadModuleGeom(const char *in_geom) {
  vkObject::_strCopy((char **)&geomFile, in_geom);
}

void VkoShader::loadModuleComp(const char *in_comp) {
  vkObject::_strCopy((char **)&compFile, in_comp);
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
  #define VKO_MAX_SHADER_STAGES 6    // vert+tesc+tese+geom+frag+comp = 6; more can just be added
  _vko->clearError();
  bool ret= false;
  VkPipelineShaderStageCreateInfo ssInfo[VKO_MAX_SHADER_STAGES];
  VkSpecializationInfo sConsts[VKO_MAX_SHADER_STAGES];
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
  for(uint32_t a= 0; a< VKO_MAX_SHADER_STAGES; a++)
    sConsts[a].pData= nullptr,             // INIT 1
    sConsts[a].pMapEntries= nullptr;       // INIT 2
  viewports.pViewports= nullptr;           // INIT 3
  viewports.pScissors= nullptr;            // INIT 4
  colorBlendAtt= nullptr;                  // INIT 5
  dynStates.pDynamicStates= nullptr;       // INIT 6
  vertAttribs= nullptr;                    // INIT 7
  vertBindings= nullptr;                   // INIT 8

  /// load all the shader module files from disk
  if(!_loadModules()) return false;

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
    graphInfo.pNext= pNext.VkGraphicsPipelineCreateInfo;   /// or an extension, atm none i think
    graphInfo.flags= 0;                            // https://www.khronos.org/registry/vulkan/specs/1.1/html/chap9.html#VkPipelineCreateFlagBits

    if(renderPass== NULL) { _vko->errorText= "VkoShader::build(): Vulkan renderpass not set. aborting."; goto Exit; }
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
        ssInfo[a].pNext= nullptr,                 // << I DON'T SEE ATM HOW TO LINK A CUSTOM PNEXT TO THIS
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
    pvisci.pNext= pNext.VkPipelineVertexInputStateCreateInfo;
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
    piasci.pNext= pNext.VkPipelineInputAssemblyStateCreateInfo;
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

    ptsci.pNext= pNext.VkPipelineTessellationStateCreateInfo;

    ptsci.patchControlPoints= _teseControlPoints;

    graphInfo.pTessellationState= &ptsci;
    
    // pipeline viewport - ignored if rasterization is disabled
    // https://www.khronos.org/registry/vulkan/specs/1.1/html/chap23.html#VkPipelineViewportStateCreateInfo
    viewports.sType= VK_STRUCTURE_TYPE_PIPELINE_VIEWPORT_STATE_CREATE_INFO;
    viewports.pNext= pNext.VkPipelineViewportStateCreateInfo;
    viewports.flags= 0;

    // TO THINK ABOUT: MULTIPLE VIEWPORTS? WOULD SETTING THESE TO CONSTANT IN HERE BE BETTER?
    /// -when using dynamic state for the viewports (resizing windows, etc), the pointers are ignored, therefore nullptr
    ///  graphInfo.pDynamicState is the way to define dynamic viewports
    /// -if the viewports are static, maybe a fullscreen view, these can be populated.
    /// -i cannot find anywhere any impact on speed

    /// constant viewports
    if(_dynamicViewports== 0) {
      if(_constViewports.nrNodes== 0) {
        _vko->errorText= "VkoShader::build(): Shader pipeline creation failed: no constant or dynamic viewports were defined (use setDynamicViewport()/setConstViewport())";
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
    raster.pNext= pNext.VkPipelineRasterizationStateCreateInfo; /// extension (none atm)
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
    msAntiAlias.pNext= pNext.VkPipelineMultisampleStateCreateInfo;
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
    depthStencil.pNext= pNext.VkPipelineDepthStencilStateCreateInfo;
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
    colorBlend.pNext= pNext.VkPipelineColorBlendStateCreateInfo;
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
    dynStates.pNext= pNext.VkPipelineDynamicStateCreateInfo;
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
    if(!_vko->errorCheck(_vko->CreateGraphicsPipelines(*_vko, VK_NULL_HANDLE, 1, &graphInfo, *_vko, &pipeline), "VkoShader::build(): Vulkan pipeline creation failed")) {
      pipeline= NULL;
      goto Exit;
    }
  } /// compute / graphics pipeline

  ret= true; // success

  Exit:

  for(uint32_t a= 0; a< VKO_MAX_SHADER_STAGES; a++) {
    if(sConsts[a].pMapEntries)
      delete[] sConsts[a].pMapEntries;    // DEALLOC 1 (in vkPopulateSpecConsts())
    if(sConsts[a].pData)
      delete[] (uint8_t *)sConsts[a].pData;          // DEALLOC 2 (in vkPopulateSpecConsts())
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

  this->_destroyModules();

  #undef IX_MAX_SHADER_STAGES
  return ret;
}







