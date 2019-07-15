#pragma once
//#include "util/typeShortcuts.h"
//#include "util/str8.h"
#include "chainList.hpp"
//#include "util/mlib.hpp"
//#include "ix/util/common.hpp"

#define VKO_SHADER_SAMPLE_MASK_MAX_SIZE 2



class VkoSet;
class vkObject;

//using namespace mlib;



class VkoShader: public chainData {
public:

  VkShaderModule vert, tesc, tese, geom, frag, comp;    // all shader modules; they're null if not used/loaded; will be dealocated once the shader is built/functional
  const char *vertFile, *tescFile, *teseFile, *geomFile, *fragFile, *compFile; // all shader modules filenames; these will remain thruout the life of the shader
  VkPipeline pipeline;    //   the shader pipeline

  // SCRAPED VV THERE IS VKOMANAGER OBJECT THAT HANDLES ALL THE SETS. WOULD A LIST OF USED SETS HAVE ANY USE HERE?
  //VkDescriptorSetLayout *descriptorsLayout; // array of descriptor sets (if more than one). descriptorsLayout[0] is set 0, describing all bindings
  //uint32_t nrDescriptorSets;
  VkPipelineLayout pipelineLayout;

  inline void setSubpass(uint32_t in_subpassNr) { subpass= in_subpassNr; }
  uint32_t subpass; // [def:0] subpass that will be used <<<< IS THIS OK?
  VkRenderPass renderPass; // renderPass that will work on this shader (i am guessing all compatible renderpasses with this1 will work)


  // set a renderpass that will work with this shader
  inline void setRenderPass(const VkRenderPass in_r) { renderPass= in_r; }

  /*
  // creates a descriptor (a descriptor can be any kind of buffer, texture, sampler. it's a vague description of all those things)
  // <in_set>:     set number. (make sure set 0 actually exists if you create set 1)
  // <in_binding>: binding number (again, create them in order OR make sure prev number exists OR at least use in_count 0, if you skip it)
  // <in_type>:    VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER / VK_DESCRIPTOR_TYPE_COMBINED_IMAGE_SAMPLER / etc https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap13.html#VkDescriptorType
  // <in_count>:   accessed in a shader as an array, when multiple. Can be 0, so it's reserved, and never accessed
  // <in_stages>:  shader stages that will use this descriptor https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap9.html#VkShaderStageFlagBits
  // <in_imutableSampler>: imutable / constant samplers, but i'd just not change them -.- imhho this ext is extra stuff that could be avoided. i think there's an extension for these
  void addDescriptor(uint32_t in_set, uint32_t in_binding, VkDescriptorType in_type, uint32_t in_count, VkShaderStageFlags in_stages, VkSampler *in_pImutableSampler= null);
  void addDescriptor(const VkoDescriptor *in_descriptor);
  void addUniformBlock();     // [shortcut] this basically creates a descriptor for set 0, binding 0, to be used as the main uniform variables block

  // this func is mainly for descriptor push
  //  VK_DESCRIPTOR_SET_LAYOUT_CREATE_PUSH_DESCRIPTOR_BIT_KHR - specifies that descriptor sets must not be allocated using this layout,
  //  and descriptors are instead pushed by vkCmdPushDescriptorSetKHR
  // In specs, it says there should be only one set with dynamic push, in an array of sets that are to be used
  void setDescriptorSetFlags(uint32_t in_set, VkDescriptorSetLayoutCreateFlags in_flags);
  */




  // create the descriptors / sets, then pass the layouts or VkoSet objects, that this shader will use
  void addDescriptorSet(const VkDescriptorSetLayout in_setLayout);
  void addDescriptorSet(const VkoSet *in_set);
  





  // adds a new range of push constants.
  // call per shader stage(s) or just once for all stages, usually it's best to just be 1 range;
  // from vulkan specs, do not add twice per same shader stage.
  // <in_nrBytes>: number of push constants that will exist
  // <in_offset>:  offset these consts will start from. On a bigger picture, all ranges of push constants must form a packed block.
  //               this offset will indicate where to start this range of constants, in this block.
  //               the simplest and best way to define push constants, would be to just offset:0 and nrBytes:sizeof(all combined push consts that will be used)
  // <in_stages>:  shader stages that will use this range of push constants https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap9.html#VkShaderStageFlagBits
  void addPushConsts(uint32_t in_nrBytes, uint32_t in_offset, VkShaderStageFlags in_stages);

  // specialization constants are true constants (c/c++ meaning) in the shader.
  // shader code ex:  "layout (constant_id = 0) const int NUM_SAMPLES = 64;"
  // they can be omited from pipeline creation and be used only by the shader, but they can be initialized from c++.
  // using the next func, specialization constants can be made aware from c++ code and can be custom initialized
  // <in_ID>: id of the spec const
  // <in_stage>: the shader stage of the const
  // <in_size>: size in bytes of the spec const

  // DEL vvv
  // <in_offset>: starting point, in bytes, of the spec const;
  //              there is a big block of data for these consts, and each const will be placed at <in_offset> in this block
  // DEL ^^^
  
  // <in_value>: the spec const initialization value
  void addSpecializationConst(uint32_t in_ID, VkShaderStageFlags in_stage, uint32_t in_size, void *in_value);
  void addSpecConstf(uint32_t in_ID, VkShaderStageFlags in_stage, float in_val) { addSpecializationConst(in_ID, in_stage, sizeof(float), &in_val); }
  void addSpecConsti(uint32_t in_ID, VkShaderStageFlags in_stage, int32_t in_val) { addSpecializationConst(in_ID, in_stage, sizeof(int32_t), &in_val); }
  

  // vertex binding & attrib
  ///=======================

  // describes the binding between the [vertex atrib] and the [vertex buffer]
  // <in_binding>: the binding number - ID of the buffer basically, if there's more than one, starting from 0
  // <in_stride>:  It specifies the number of bytes between data entries
  // <in_rate>:    move to the next data entry after each vertex or after each instance (VK_VERTEX_INPUT_RATE_VERTEX/VK_VERTEX_INPUT_RATE_INSTANCE)
  void addVertexBinding(uint32_t in_binding, uint32_t in_stride, VkVertexInputRate in_rate);

  // describes the vertex attribute in the shader
  // <in_location>: location of the vertex atribute (location:x)
  // <in_binding>:  the binding
  // <in_format>:   format of the data (float: VK_FORMAT_R32_SFLOAT
  //                                    vec2: VK_FORMAT_R32G32_SFLOAT
  //                                    vec3: VK_FORMAT_R32G32B32_SFLOAT
  //                                    vec4: VK_FORMAT_R32G32B32A32_SFLOAT  etc)
  // <in_offset>:   specifies the number of bytes since the start of the per-vertex data to read from
  void addVertexAttribute(uint32_t in_location, uint32_t in_binding, VkFormat in_format, uint32_t in_offset);

  // input assembly https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap19.html#VkPipelineInputAssemblyStateCreateInfo
  ///==============

  // <in_topology>: [def:VK_PRIMITIVE_TOPOLOGY_TRIANGLE_LIST] points, lines, triangles, triangle strips/fans, etc https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap19.html#VkPrimitiveTopology
  // <in_primitiveRestartEnable>: [def:false] mark a specific vertex index to restart the assembly of primitives. check specs. (0xFFFFFFFF is the marker)
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap19.html#VkPipelineInputAssemblyStateCreateInfo
  inline void setInputAssembly(VkPrimitiveTopology in_topology, VkBool32 in_primitiveRestartEnable) { _topology= in_topology, _primitiveRestartEnable= in_primitiveRestartEnable; }


  // teselation control points, if teselation is enabled [def:1]
  // patchControlPoints must be greater than zero and less than or equal to VkPhysicalDeviceLimits::maxTessellationPatchSize
  inline void setTeselationControlPoints(uint32_t in_nrControlPoints) { _teseControlPoints= in_nrControlPoints; }

  // the default is top-left
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap21.html#VkTessellationDomainOrigin
  inline void setTeselationDomainOrigin(VkTessellationDomainOrigin in_origin) { _teseDomainOrigin= in_origin; }

  // viewports
  ///=========

  // there are two types of viewport linkage: constant, set in the pipeline, and dynamic, that has to be updated in the cmd buffers
  // the program has to choose between either constant or dynamic viewports

  // constant viewports are automatically setup in the command buffers
  // - for example, if an OS window that uses vulkan to draw things resizes, the pipeline would have to be rebuilt, to change the constant viewport(s)
  // - you can add multiple viewports by calling the func multiple times. All of them will be added to the pipeline, in order.
  // - i cannot find anywhere if they are faster or the same as the dynamic ones, but the constant viewports could be faster
  void setConstantViewport(const VkViewport *in_viewPort, const VkRect2D *in_scissor);
  void setConstantViewport2(float x0, float y0, float dx, float dy, float minDepth, float maxDepth, float scissorX0, float scissorY0, float scissorDx, float scissorDy);

  // - if the dynamic viewports are enabled in the pipeline, it signals Vulkan that the viewport parameters are dynamically set and changed
  //   using vkCmdSetViewport()
  // - i cannot find a clear statement that these viewports are slower than the constant viewports,
  //   therefore, in theory, even fullscreen windows could use the dynamic viewports
  // - enables VK_DYNAMIC_STATE_VIEWPORT and VK_DYNAMIC_STATE_SCISSOR
  // <in_nrViewports>: how many viewports will be used in the pipeline
  inline void setDynamicViewports(uint32_t in_nrViewports) { _dynamicViewports= in_nrViewports; addDynamicState(VK_DYNAMIC_STATE_VIEWPORT); addDynamicState(VK_DYNAMIC_STATE_SCISSOR); }


  // rasterization state
  ///===================

  // [def:false] depthClampEnable controls whether to clamp the fragment’s depth values as described in Depth Test.
  // Enabling depth clamp will also disable clipping primitives to the z planes of the frustrum as described in Primitive Clipping
  // (https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap23.html#vertexpostproc-clipping).
  inline void setDepthClampEnable(bool in_enable) { _depthClampEnable= in_enable; }

  // [def:false] controls whether primitives are discarded immediately before the rasterization stage.
  inline void setRasterizerDiscardEnable(bool in_enable) { _rasterizerDiscardEnable= in_enable; }

  // [def:VK_POLYGON_MODE_FILL] polygonMode is the triangle rendering mode. See VkPolygonMode.
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap24.html#VkPolygonMode
  inline void setPolygonMode(const VkPolygonMode in_m) { _polygonMode= in_m; }

  // [def:VK_CULL_MODE_BACK_BIT] cullMode is the triangle facing direction used for primitive culling. See VkCullModeFlagBits.
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap24.html#VkCullModeFlagBits
  inline void setCullModeFlags(const VkCullModeFlags in_cull) { _cullMode= in_cull; }

  // [def:VK_FRONT_FACE_COUNTER_CLOCKWISE] frontFace is a VkFrontFace value specifying the front-facing triangle orientation to be used for culling.
  inline void setFrontFace(const VkFrontFace in_face) { _frontFace= in_face; }
  
  // <in_enable>: [def:false] controls whether to bias fragment depth values.
  // depthBiasConstantFactor is a scalar factor controlling the constant depth value added to each fragment.
  // depthBiasClamp is the maximum (or minimum) depth bias of a fragment.
  // depthBiasSlopeFactor is a scalar factor applied to a fragment’s slope in depth bias calculations.
  inline void setDepthBias(bool in_enable, float constantFactor, float clamp, float slopeFactor) { _depthBiasEnable= in_enable; _depthBiasConstantFactor= constantFactor; _depthBiasClamp= clamp; _depthBiasSlopeFactor= slopeFactor; }

  // [def:1.0f] lineWidth is the width of rasterized line segments.
  inline void setLineWidth(float in_width) { _lineWidth= in_width; }

  // multisample antialiasing
  ///========================

  // [def:VK_SAMPLE_COUNT_1_BIT / disabled] antialiasing samples
  inline void setMultisampleAliasingSamples(VkSampleCountFlagBits in_n) { _nrMultisamples= in_n; }

  // can be used to enable Sample Shading. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap24.html#primsrast-sampleshading
  // <in_enable>:           [def:false] enable/disable sample shading
  // <in_minSampleShading>: [def:1.0f] specifies a minimum fraction of sample shading if sampleShadingEnable is set to VK_TRUE.
  inline void setSampleShading(bool in_enable, float in_minSampleShading) { _sampleShadingEnable= in_enable, _minSampleShading= in_minSampleShading; }

  // [def:0/not used] bitmask of static coverage information that is ANDed with the coverage information generated during rasterization,
  //                  as described in Sample Mask. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-samplemask
  inline void setSampleMask(uint32_t in_mask[VKO_SHADER_SAMPLE_MASK_MAX_SIZE]) { for(uint32_t a= 0; a< VKO_SHADER_SAMPLE_MASK_MAX_SIZE; a++) _sampleMaskData[a]= in_mask[a]; _sampleMask= _sampleMaskData; }

  // [def:false] controls whether a temporary coverage value is generated based on the alpha component of the fragment’s first color output as specified in the Multisample Coverage section.
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-covg
  inline void setAlphaToCoverageEnable(bool in_enable) { _alphaToCoverageEnable= in_enable; }

  // [def:false] controls whether the alpha component of the fragment’s first color output is replaced with one as described in Multisample Coverage.
  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-covg
  inline void setAlphaToOneEnable(bool in_enable) { _alphaToOneEnable= in_enable; }

  // depth / stencil
  ///===============

  // <in_enableDepthTest>: [def:false] enables / disables the depth test
  // <in_enableDepthWrite>: [def:false] enables / disables the depth writites if depth testing is enabled
  // <in_depthOp>: the comparison operator used in the depth test. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-depth
  // <in_depthBoundsTestEnable>: enables/disables depth bound test https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-dbt
  // <in_minConstBounds / in_maxConstBounds>: define the range of values used in the depth bounds test.
  //                                          This range is used if DYNAMIC bounds testing is NOT ENABLED.
  //                                          To enable dynamic bounds range for the depth bound test, use func setDepthDynamicBounds(...)
  void setDepthTest(bool in_enableDepthTest, bool in_enableDepthWrite, VkCompareOp in_depthOp, bool depthBoundsTestEnable, float in_minConstBounds= 0.0f, float in_maxConstBounds= 1.0f);


  // - enables VK_DYNAMIC_STATE_DEPTH_BOUNDS
  // [def:false] enables / disables the dynamic range for the depth bounds test. Use vkCmdSetDepthBounds() to set the bounds dynamically
  inline void setDepthDynamicBoundsTest(bool in_depthBoundsTestEnable) { _depthBoundsDynamic= in_depthBoundsTestEnable; addDynamicState(VK_DYNAMIC_STATE_DEPTH_BOUNDS); }


  // <in_stencilTestEnable>: [def:false] enable/disable stencil test https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-stencil
  // <in_front> / <in_back>: optional direct VkStencilOpState structs. If left null, use setStencilFrontOp()/ setStencilBackOp() funcs, optionally
  inline void setStencilTest(bool in_stencilTestEnable, VkStencilOpState *in_front= nullptr, VkStencilOpState *in_back= nullptr) { _stencilTestEnable= in_stencilTestEnable;}

  // <failOp> is a VkStencilOp value specifying the action performed on samples that fail the stencil test.
  // <passOp> is a VkStencilOp value specifying the action performed on samples that pass both the depth and stencil tests.
  // <depthFailOp> is a VkStencilOp value specifying the action performed on samples that pass the stencil test and fail the depth test.
  // <compareOp> is a VkCompareOp value specifying the comparison operator used in the stencil test.
  // <compareMask> selects the bits of the unsigned integer stencil values participating in the stencil test.
  // <writeMask> selects the bits of the unsigned integer stencil values updated by the stencil test in the stencil framebuffer attachment.
  // <reference> is an integer reference value that is used in the unsigned stencil comparison.
  void setStencilTestFrontOp(VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp, uint32_t compareMask, uint32_t writeMask, uint32_t reference);
  void setStencilTestBackOp(VkStencilOp failOp, VkStencilOp passOp, VkStencilOp depthFailOp, VkCompareOp compareOp, uint32_t compareMask, uint32_t writeMask, uint32_t reference);

  // color blending
  ///==============

  // <in_enableLogicOp>: [def:false] enable/disable color blending
  // <in_logicOp>: [def:VK_LOGIC_OP_COPY] the logical operation to perform for the blending
  // <in_constColor>: [def:0,0,0,0] the constant color, if used, in the logical operations
  void setColorBlend(bool in_enableLogicOp, VkLogicOp in_logicOp, const float *in_constColor= nullptr/*= &vec4(0.0f, 0.0f, 0.0f, 0.0f)*/);

  // the number of attachements must equal the colorAttachmentCount for the subpass in which this shader pipeline is used.
  // all func parameters match VkPipelineColorBlendAttachmentState struct https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap26.html#VkPipelineColorBlendAttachmentState
  void addColorBlendAttachement(bool blendEnable, VkBlendFactor srcBlendFactor, VkBlendFactor dstBlendFactor, VkBlendOp blendOp, VkBlendFactor srcAlphaBlendFactor, VkBlendFactor dstAlphaBlendFactor, VkBlendOp alphaBlendOp, VkColorComponentFlags colorWriteMask);
  void addColorBlendAttachement2(const VkPipelineColorBlendAttachmentState *in_attachement);
  
  // dynamic states of the shader pipeline
  ///=====================================

  // all dynamic states that can be added: https://www.khronos.org/registry/vulkan/specs/1.1/html/chap9.html#VkDynamicState
  // if adding dynamic viewports, make sure and setDynamicViewports() to the number of viewports that will be used (a total number has to be avaible, i think at least)
  // - calling setDynamicViewports or any function similar to that, also sets the dynamic state for that specific state
  // - the function checks if the state is not already added, so do not worry about it.
  void addDynamicState(VkDynamicState in_dyn);


  // shader modules
  ///==============

  // loads shaer's modules from files; any stage that is not present, must be marked by null;
  // or, load each module that will be used with "loadModuleXXXX(..)" funcs
  // if comp is loaded, the shader will be created with a compute pipeline, else it's a graphics pipeline
  bool loadModules(const char *in_vert, const char *in_tesc, const char *in_tese, const char *in_geom, const char *in_frag, const char *in_comp);
  bool loadModuleVert(const char *in_vert);
  bool loadModuleFrag(const char *in_frag);
  bool loadModuleTesc(const char *in_tesc);
  bool loadModuleTese(const char *in_tese);
  bool loadModuleGeom(const char *in_geom);
  bool loadModuleComp(const char *in_comp);

  bool loadModule(const char *in_file, VkShaderModule *out_module);    // loads a shader module
  void destroyModules();            // modules can/should be destroyed after the shader is completed/operational

  // after setting all the data, adding all the descriptors, call this func to create the pipeline, descriptors, layouts, etc.
  // this func will make this shader object fully functional
  bool build();

  void destroy();



  //void updateViewportPos();

  // constructor/destructor

  VkoShader();
  virtual ~VkoShader();
  //virtual void delData();

  //Ix *ix;                           // parent ix engine this shader belongs to
  vkObject *parent;




  // PRIVATE STUFF FROM HERE ON
  ///--------------------------
private:
  //chainList _descriptors;
  //chainList _descriptorSetFlags;
  chainList _setLayouts;
  chainList _pushConsts;
  chainList _specConsts;
  chainList _vertBindings;
  chainList _vertAttribs;

  VkPrimitiveTopology _topology; // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap19.html#VkPrimitiveTopology
  bool _primitiveRestartEnable;  // https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap19.html#VkPipelineInputAssemblyStateCreateInfo

  uint32_t _teseControlPoints;
  VkTessellationDomainOrigin _teseDomainOrigin;

  uint32_t _dynamicViewports;
  chainList _constViewports;

  bool _depthClampEnable;
  bool _rasterizerDiscardEnable;
  VkPolygonMode _polygonMode;
  VkCullModeFlags _cullMode;
  VkFrontFace _frontFace;
  float _depthBiasConstantFactor;  // depthBiasConstantFactor is a scalar factor controlling the constant depth value added to each fragment.
  float _depthBiasClamp;           // depthBiasClamp is the maximum (or minimum) depth bias of a fragment.
  float _depthBiasSlopeFactor;     // depthBiasSlopeFactor is a scalar factor applied to a fragment’s slope in depth bias calculations.
  bool _depthBiasEnable;           // [def:false] [enable/disable] controls whether to bias fragment depth values
  float _lineWidth;

  VkSampleCountFlagBits _nrMultisamples;   // [def:VK_SAMPLE_COUNT_1_BIT / disabled] antialiasing samples 
  bool _sampleShadingEnable;               // can be used to enable Sample Shading. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap24.html#primsrast-sampleshading
  float _minSampleShading;                 // specifies a minimum fraction of sample shading if sampleShadingEnable is set to VK_TRUE.
  uint32_t *_sampleMask;                     // bitmask of static coverage information that is ANDed with the coverage information generated during rasterization, as described in Sample Mask.
  uint32_t _sampleMaskData[VKO_SHADER_SAMPLE_MASK_MAX_SIZE];
  bool _alphaToCoverageEnable; // controls whether a temporary coverage value is generated based on the alpha component of the fragment’s first color output as specified in the Multisample Coverage section.
  bool _alphaToOneEnable;      // controls whether the alpha component of the fragment’s first color output is replaced with one as described in Multisample Coverage.

  bool _depthTestEnable;         // enable / disable the depth test
  bool _depthTestWrite;          // enable / disable the depth write
  VkCompareOp _depthTestOp;      // the comparison operator used in the depth test. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-depth
  bool _depthBoundsTestEnable;   // enables/disables depth bound test https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-dbt
  float _depthBoundsConstMin;    // constant depth bounds range (min)
  float _depthBoundsConstMax;    // constant depth bounds range (max)
  bool _depthBoundsDynamic;      // enables / disables dynamic range for the depth bounds test. Use vkCmdSetDepthBounds() to set the bounds dynamically
  bool _stencilTestEnable;               // controls whether stencil testing is enabled. https://www.khronos.org/registry/vulkan/specs/1.1-khr-extensions/html/chap25.html#fragops-stencil
  VkStencilOpState _stencilTestOpFront;  // control the parameters of the stencil test.
  VkStencilOpState _stencilTestOpBack;   // control the parameters of the stencil test.

  bool _colorBlendLogicOpEnable;      // controls whether to apply Logical Operations.
  VkLogicOp _colorBlendLogicOp;       // selects which logical operation to apply.
  float _colorBlendConstColor[4];     // R, G, B, and A components of the blend constant that are used in blending, depending on the blend factor.
  chainList _colorBlendAttachements;  // color blend attachements. The number of attachements must be equal to colorAttachmentCount for the subpass in wich this pipeline is used

  chainList _dynamicStates;


  // void _vkCreateDescriptorsLayout();  SCRAPED - DESCRIPTORS/SETS ARE DONE IN ANOTHER OBJECT, AND LAYOUTS PASSED TO THIS1
  void _vkCreatePipelineLayout();
  void _vkPopulateSpecConsts(VkShaderStageFlags in_stage, VkSpecializationInfo *out_sConst);

  class _PushConsts: public chainData {
  public:
    uint32_t nrBytes;
    uint32_t offset;
    VkShaderStageFlags shaderStages;
  };

  /*
  class _Descriptor: public chainData {
  public:
    uint32_t set, binding;
    VkDescriptorType type;
    uint32_t count;
    VkShaderStageFlags shaderStages;
    VkSampler *pImutableSamplers;
  };

  class _DescriptorSetFlags: public chainData {
  public:
    uint32_t set;
    VkDescriptorSetLayoutCreateFlags flags;
  };
  */

  class _SetLayout: public chainData {
  public:
      VkDescriptorSetLayout layout;
  };

  class _SpecConst: public chainData {
  public:
    uint32_t id;                // ID of the constant
    VkShaderStageFlags stage; // shader stage
    uint32_t size;              // in bytes;
    uint32_t offset;            // in bytes; (starting point in the specialization constants data buffer)
    void *value;              // the actual value of the constant, whatever type and size it is
    _SpecConst(): value(nullptr) {}
    ~_SpecConst() { if(value) delete[] value; } 
  };

  class _VertBinding: public chainData {
  public:
    uint32_t binding;
    uint32_t stride;
    VkVertexInputRate rate;
  };

  class _VertAttribs: public chainData {
  public:
    uint32_t location;
    uint32_t binding;
    VkFormat format;
    uint32_t offset;
  };

  class _ConstViewport: public chainData {
  public:
    VkViewport view;
    VkRect2D scissor;
  };

  class _ColorBlendAttachment: public chainData {
  public:
    VkPipelineColorBlendAttachmentState att;
  };

  class _DynamicState: public chainData {
  public:
    VkDynamicState dyn;
  };

  friend class ixShaderSys;
  friend class Ix;
};











