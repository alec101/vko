  vkObject vko;

  vko.cfg.addValidationLayer("VK_LAYER_KHRONOS_validation");
  vko.cfg.queueRequestUniversal= 1;
  vko.cfg.extensions.instance.vk_KHR_win32_surface.enable= 1;
  vko.cfg.extensions.instance.vk_KHR_surface.enable= 1;
  vko.cfg.extensions.instance.vk_EXT_debug_utils.enable= 1;
  
  vko.buildInstance();


  VkPhysicalDeviceFeatures f;
  memclr(&f, sizeof(VkPhysicalDeviceFeatures));  
  f.depthBounds= 1;
  f.samplerAnisotropy= 1;
  vko.cfg.gpuFeatures= &f;

  vko.cfg.extensions.device.vk_KHR_swapchain.enable= 1;
  vko.physicalDevice= vk.info.physicalDevice[0].physicalDevice;
  vko.build();


  // create your window with glsl/osi/watever  
  osi.vkCreateWindow(&osi.win[0], &osi.display.monitor[0], "Vulkan Window (win0)", 500, 500, 1);


  // swapchain
  
  VkoSwapchain *vkSwap= vko->addSwapchain();
  vkSwap->cfg.surface= (VkSurfaceKHR)osi.primWin->vkSurface;

  if(vkSwap->build()!= true) { error.window("swapchain build failed"); return; }

  
  // command pool / buffers

  VkoCommandPool *cmdPool= vko->addCommandPool();
  cmdPool->configure(vko->queue[0].family, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
  cmdPool->build();

  cmdBuffers[0]= cmdPool->addCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);
  cmdBuffers[1]= cmdPool->addCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);

  // render pass

  VkoRenderPass *vkRP= vko->addRenderPass();
  
  vkRP->addAttachment2(0, VK_FORMAT_B8G8R8A8_UNORM,     VK_SAMPLE_COUNT_1_BIT,
                       VK_ATTACHMENT_LOAD_OP_CLEAR,     VK_ATTACHMENT_STORE_OP_STORE,
                       VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
                       VK_IMAGE_LAYOUT_UNDEFINED,       VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

  vkRP->addSubpassDependency(VK_SUBPASS_EXTERNAL, 0, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, 0);
  
  vkRP->addSubpass(0, VK_PIPELINE_BIND_POINT_GRAPHICS);


  vkRP->addSubpassColorAttachment(0, 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, false, 0, VK_IMAGE_LAYOUT_UNDEFINED, false, 0, VK_IMAGE_LAYOUT_UNDEFINED);
  
  if(!vkRP->build()) error.simple("render pass build failed");
    
  // framebuffer

  VkoFramebuffer **vkFB= new VkoFramebuffer*[2];

  vkFB[0]= vko->addFramebuffer();
  vkFB[0]->setRenderPass(*vkRP);
  vkFB[0]->addAttachment(vkSwap->images[0], vkSwap->cfg.imageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
  vkFB[0]->setDimensions(vkSwap->dx, vkSwap->dy);
  if(!vkFB[0]->build()) error.simple("framebuffer 1 failed");

  vkFB[1]= vko->addFramebuffer();
  vkFB[1]->setRenderPass(*vkRP);
  vkFB[1]->addAttachment(vkSwap->images[1], vkSwap->cfg.imageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
  vkFB[1]->setDimensions(vkSwap->dx, vkSwap->dy);
  if(!vkFB[1]->build()) error.simple("framebuffer 2 failed")

  // descriptor manager

  VkoDescriptorManager *vkManager= vko->addDescriptorManager();
  vkManager->addDescriptorSet(0);
  vkManager->addDescriptor(0, 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT);

  if(!vkManager->build()) error.simple("descriptor manager build failed.");


  // shader

  VkoShader *s1; 
  vko->createShader(&s1);

  s1->addVertexBinding(0, 28, VK_VERTEX_INPUT_RATE_VERTEX);   // size of stride is vec3(position)+ vec4(color), 12+ 16
  s1->addVertexAttribute(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0);
  s1->addVertexAttribute(1, 0, VK_FORMAT_R32G32B32A32_SFLOAT, 12);
  
  s1->loadModuleVert("../source/shaders/testChamber3.vert.spv");
  s1->loadModuleFrag("../source/shaders/testChamber3.frag.spv");

  s1->setRenderPass(*vkRP);
  //s1->setConstantViewport2(0, 0, 400, 400, 0, 1, 0, 0, 400, 400);
  s1->setDynamicViewports(1);
  
  s1->addColorBlendAttachement(false, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);
  
  s1->setFrontFace(VK_FRONT_FACE_COUNTER_CLOCKWISE);
  s1->setCullModeFlags(VK_CULL_MODE_BACK_BIT);
  s1->addPushConsts(sizeof(mlib::mat4), 0, VK_SHADER_STAGE_VERTEX_BIT);

  s1->build();
  
  // buffers

  VkoBuffer *buf1= vko->buffers.addBuffer();
  VkoBuffer *buf2= vko->buffers.addBuffer();
  buf1->setSize(sizeof(mlib::mat4));
  buf1->setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
  buf1->offset= 4096;
  buf1->build();
  
  buf2->setSize(2048);
  buf2->setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
  buf2->build();
  
  if(vko->errorText)
    printf("%s\n", vko->errorText);

  // memory
  
  VkoMemory *mem= vko->memory.addMemoryBlock();
  mem->configure(262144, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 0, buf2->memRequirements.memoryTypeBits);
  mem->build();
  
  printf("buffer 1 -> memory compatibility: %d\n", buf1->isMemoryCompatible(mem));
  printf("buffer 2 -> memory compatibility: %d\n", buf2->isMemoryCompatible(mem));
  vko->BindBufferMemory(*vko, *buf2, *mem, buf2->offset);
  vko->BindBufferMemory(*vko, *buf1, *mem, buf1->offset);
  vkInitBuffers(); // your custom init

  // syncronisation

  VkoSemaphore *vkSem1= vko->addSemaphore();
  vkSem1->build();
  VkoSemaphore *vkSem2= vko->addSemaphore();
  vkSem2->build();

