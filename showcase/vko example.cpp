#include "osi/include/osinteraction.h"
#include "vko/include/vkObject.h"
#include "util/mlib.hpp"

// This example of a draw with vulkan is in no way optimized. This is just a showcase of what it can be done with vko.
// The example was done extremly hastly, with commands thrown left and right.
// The initial intent was to have 2 command buffers and every frame switching between them.
// If it is needed, the example will be cleared out and optimized, but atm i don't see a point in doing it.

using namespace mlib;
vkObject vk;
float angle= 0;

class VulkanExample {
public:
  mat4 worldMat, projMat, cameraMat;
  VkoSwapchain *vkSwap;
  VkoCommandPool *cmdPool;
  VkCommandBuffer cmdBuffers[2];
  VkoRenderPass *vkRP;
  VkoFramebuffer **vkFB;
  VkoDescriptorManager *vkManager;
  VkoShader *s1;
  VkoMemory *mem;
  VkoBuffer *buf1, *buf2;
  VkoSemaphore *vkSem1, *vkSem2;

  void init();
  void draw();

  void vkInitBuffers(VkoMemory *out_mem);
  void vkUpdateUniformBuffer(VkoMemory *out_memory, VkoBuffer *in_buffer, const mlib::mat4 *in_mat);
  void setPerspective(mat4 *out_camera, const vec3 &in_pos, const vec3 &in_eye, float in_fov, float in_aspect, float in_zClipNear, float in_zClipFar);
} vulkan;



int main() {
  vk.cfg.addValidationLayer("VK_LAYER_KHRONOS_validation");
  vk.cfg.queueRequestUniversal= 1;
  vk.cfg.extensions.instance.vk_KHR_win32_surface.enable= 1;
  vk.cfg.extensions.instance.vk_KHR_surface.enable= 1;
  vk.cfg.extensions.instance.vk_EXT_debug_utils.enable= 1;
  vk.buildInstance();   // instance built

  osi.vkInit(&vk);      // osi populates graphic card info with vulkan extra info, and will use this vkObject

  VkPhysicalDeviceFeatures f;
  Str::memclr(&f, sizeof(VkPhysicalDeviceFeatures));  
  f.depthBounds= 1;
  f.samplerAnisotropy= 1;
  vk.cfg.gpuFeatures= &f;

  vk.cfg.extensions.device.vk_KHR_swapchain.enable= 1;
  vk.physicalDevice= vk.info.physicalDevice[0].physicalDevice;

  vk.build();           // device built

  osi.vkCreateWindow(&osi.win[0], &osi.display.monitor[0], "Vulkan Window (win0)", 500, 500, 1);
  in.init();

  vulkan.init();
  
  
  while(1) {
    angle++;

    osi.checkMSG();
    in.update();

    // esc - quit
    if(in.k.key[in.Kv.esc] || osi.flags.exit)
      break;

    // window resized - swapchain must be rebuilt
    if(osi.flags.windowResized) {
      vulkan.vkSwap->rebuild();
      vulkan.vkFB[0]->changeAttachment(0, vulkan.vkSwap->images[0], vulkan.vkSwap->cfg.imageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
      vulkan.vkFB[0]->setDimensions(vulkan.vkSwap->dx, vulkan.vkSwap->dy);
      vulkan.vkFB[0]->rebuild();

      vulkan.vkFB[1]->changeAttachment(0, vulkan.vkSwap->images[1], vulkan.vkSwap->cfg.imageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
      vulkan.vkFB[1]->setDimensions(vulkan.vkSwap->dx, vulkan.vkSwap->dy);
      vulkan.vkFB[1]->rebuild();
    }


    if(osi.primWin->isCreated) {
      vulkan.vkSwap->aquire(*vulkan.vkSem1);
      vulkan.draw();
    }

    if(osi.primWin->isCreated) {
      vk.DeviceWaitIdle(vk);
      vulkan.vkSwap->queueShowCurrent(vk.queue[0].queue, *vulkan.vkSem2);
      vk.DeviceWaitIdle(vk);
    }
  } // infinite loop

  return 0;
} // main - program end












void VulkanExample::init() {
  
  // swapchain
  
  vkSwap= vk.addSwapchain();
  vkSwap->cfg.surface= (VkSurfaceKHR)osi.primWin->vkSurface;

  if(vkSwap->build()!= true) { error.window("swapchain build failed"); return; }
  
  // command pool / buffers

  cmdPool= vk.addCommandPool();
  cmdPool->configure(vk.queue[0].family, VK_COMMAND_POOL_CREATE_RESET_COMMAND_BUFFER_BIT);
  cmdPool->build();

  cmdBuffers[0]= cmdPool->addCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);
  cmdBuffers[1]= cmdPool->addCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);

  // render pass

  vkRP= vk.addRenderPass();
  
  vkRP->addAttachment2(0, VK_FORMAT_B8G8R8A8_UNORM,     VK_SAMPLE_COUNT_1_BIT,
                       VK_ATTACHMENT_LOAD_OP_CLEAR,     VK_ATTACHMENT_STORE_OP_STORE,
                       VK_ATTACHMENT_LOAD_OP_DONT_CARE, VK_ATTACHMENT_STORE_OP_DONT_CARE,
                       VK_IMAGE_LAYOUT_UNDEFINED,       VK_IMAGE_LAYOUT_PRESENT_SRC_KHR);

  vkRP->addSubpassDependency(VK_SUBPASS_EXTERNAL, 0, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT, 0, VK_ACCESS_COLOR_ATTACHMENT_READ_BIT | VK_ACCESS_COLOR_ATTACHMENT_WRITE_BIT, 0);
  
  vkRP->addSubpass(0, VK_PIPELINE_BIND_POINT_GRAPHICS);


  vkRP->addSubpassColorAttachment(0, 0, VK_IMAGE_LAYOUT_COLOR_ATTACHMENT_OPTIMAL, false, 0, VK_IMAGE_LAYOUT_UNDEFINED, false, 0, VK_IMAGE_LAYOUT_UNDEFINED);
  
  if(!vkRP->build()) error.simple("render pass build failed");
    
  // framebuffer

  vkFB= new VkoFramebuffer*[2];

  vkFB[0]= vk.addFramebuffer();
  vkFB[0]->setRenderPass(*vkRP);
  vkFB[0]->addAttachment(vkSwap->images[0], vkSwap->cfg.imageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
  vkFB[0]->setDimensions(vkSwap->dx, vkSwap->dy);
  if(!vkFB[0]->build()) error.simple("framebuffer 1 failed");

  vkFB[1]= vk.addFramebuffer();
  vkFB[1]->setRenderPass(*vkRP);
  vkFB[1]->addAttachment(vkSwap->images[1], vkSwap->cfg.imageFormat, VK_IMAGE_ASPECT_COLOR_BIT);
  vkFB[1]->setDimensions(vkSwap->dx, vkSwap->dy);
  if(!vkFB[1]->build()) error.simple("framebuffer 2 failed");

  // descriptor manager

  VkoDescriptorManager *vkManager= vk.addDescriptorManager();
  vkManager->addDescriptorSet(0);
  vkManager->addDescriptor(0, 0, VK_DESCRIPTOR_TYPE_UNIFORM_BUFFER, 1, VK_SHADER_STAGE_VERTEX_BIT);

  if(!vkManager->build()) error.simple("descriptor manager build failed.");

  // shader

  vk.createShader(&s1);

  s1->addVertexBinding(0, 28, VK_VERTEX_INPUT_RATE_VERTEX);   // size of stride is vec3(position)+ vec4(color), 12+ 16
  s1->addVertexAttribute(0, 0, VK_FORMAT_R32G32B32_SFLOAT, 0);
  s1->addVertexAttribute(1, 0, VK_FORMAT_R32G32B32A32_SFLOAT, 12);
  
  s1->loadModuleVert("../shader1.vert.spv");
  s1->loadModuleFrag("../shader1.frag.spv");

  s1->setRenderPass(*vkRP);
  //s1->setConstantViewport2(0, 0, 400, 400, 0, 1, 0, 0, 400, 400);
  s1->setDynamicViewports(1);
  
  s1->addColorBlendAttachement(false, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, VK_BLEND_FACTOR_ONE, VK_BLEND_FACTOR_ZERO, VK_BLEND_OP_ADD, VK_COLOR_COMPONENT_R_BIT | VK_COLOR_COMPONENT_G_BIT | VK_COLOR_COMPONENT_B_BIT | VK_COLOR_COMPONENT_A_BIT);
  
  s1->setFrontFace(VK_FRONT_FACE_COUNTER_CLOCKWISE);
  s1->setCullModeFlags(VK_CULL_MODE_BACK_BIT);
  s1->addPushConsts(sizeof(mlib::mat4), 0, VK_SHADER_STAGE_VERTEX_BIT);

  s1->build();
  
  // buffers

  buf1= vk.buffers.addBuffer();
  buf2= vk.buffers.addBuffer();
  buf1->setSize(sizeof(mlib::mat4));
  buf1->setUsage(VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT);
  buf1->offset= 4096;
  buf1->build();
  
  buf2->setSize(2048);
  buf2->setUsage(VK_BUFFER_USAGE_VERTEX_BUFFER_BIT);
  buf2->build();
  
  if(vk.errorText)
    printf("%s\n", vk.errorText);

  // memory
  
  mem= vk.memory.addMemoryBlock();
  mem->configure(8192, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT| VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, 0, buf2->memRequirements.memoryTypeBits);
  mem->build();
  
  printf("buffer 1 -> memory compatibility: %d\n", buf1->isMemoryCompatible(mem));
  printf("buffer 2 -> memory compatibility: %d\n", buf2->isMemoryCompatible(mem));
  vk.BindBufferMemory(vk, *buf2, *mem, buf2->offset);
  vk.BindBufferMemory(vk, *buf1, *mem, buf1->offset);
  vkInitBuffers(mem);

  // syncronisation

  vkSem1= vk.addSemaphore();
  vkSem1->build();
  vkSem2= vk.addSemaphore();
  vkSem2->build();
}




void VulkanExample::vkInitBuffers(VkoMemory *out_mem) {
  float *buf= null;
  float dat[]= {
    // position                  color
    // red - front
    -1.0f,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,
     1.0f,  1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,
     1.0f, -1.0f, 1.0f,     1.0f, 0.0f, 0.0f, 1.0f,
     // green - back
    -1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f,
     1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f,
     1.0f,  1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f,
     1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 0.0f, 1.0f,
    // blue - right
     1.0f,  1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,    0.0f, 0.0f, 1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,    0.0f, 0.0f, 1.0f, 1.0f,
      // yellow - left
    -1.0f,  1.0f, -1.0f,    1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,    1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,    1.0f, 1.0f, 0.0f, 1.0f,
    -1.0f, -1.0f,  1.0f,    1.0f, 1.0f, 0.0f, 1.0f,
    // cyan - bottom
    -1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 1.0f, 1.0f,
     1.0f, -1.0f,  1.0f,    0.0f, 1.0f, 1.0f, 1.0f,
    -1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 1.0f, 1.0f,
     1.0f, -1.0f, -1.0f,    0.0f, 1.0f, 1.0f, 1.0f,
    // magenta - top
    -1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 1.0f, 1.0f,
     1.0f,  1.0f, -1.0f,    1.0f, 0.0f, 1.0f, 1.0f,
    -1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 1.0f, 1.0f,
     1.0f,  1.0f,  1.0f,    1.0f, 0.0f, 1.0f, 1.0f
  };

  vk.DeviceWaitIdle(vk);

  // 36vert* 3axis, 24colors* 4 channels 
  vk.MapMemory(vk, *out_mem, 0, (36* 3+ 36* 4)* 4, 0, (void **)&buf);
  Str::memcpy(buf, dat, (36* 7)* 4);
  vk.UnmapMemory(vk, *out_mem);
  vk.DeviceWaitIdle(vk);
}


void VulkanExample::vkUpdateUniformBuffer(VkoMemory *out_memory, VkoBuffer *in_buffer, const mlib::mat4 *in_mat) {
  float *p;
  VkResult res;

  vk.DeviceWaitIdle(vk);
  res= vk.MapMemory(vk, *out_memory, in_buffer->offset, sizeof(mlib::mat4), 0, (void **)&p);
  if(res!= VK_SUCCESS) {
    error.simple("could not map memory for uniform buffer");
    error.vkPrint(res);
    return;
  }

  Str::memcpy(p, in_mat, sizeof(mlib::mat4));

  vk.UnmapMemory(vk, *out_memory);
  vk.DeviceWaitIdle(vk);
}


void VulkanExample::setPerspective(mat4 *out_camera, const vec3 &in_pos, const vec3 &in_eye, float in_fov, float in_aspect, float in_zClipNear, float in_zClipFar) {
  projMat.perspective(in_fov, in_aspect, in_zClipNear, in_zClipFar);
  worldMat.lookAt(in_pos, in_eye, vec3(0.0f, 1.0f, 0.0f));
  *out_camera= projMat* worldMat;
}








///=========================================================///
// DRAW ========================---------------------------- //
///=========================================================///

void VulkanExample::draw() {
  // this example of a draw with vulkan is in no way optimized. this is just a showcase of what it can be done with vko
  // the example was done extremly hastly, with commands thrown left and right
  // the initial intent was to have 2 command buffers and every frame switching between them
  // if it is needed, the example will be cleared out and optimized, but atm i don't see a point in doing it

  osiWindow *w= osi.primWin;
  uint32 i= vkSwap->currentIndex;
  VkResult res;

  VkCommandBuffer buffer= cmdBuffers[i];
  VkImage image= vkSwap->images[i];
  vk.DeviceWaitIdle(vk);
  vk.FreeCommandBuffers(vk, *cmdPool, 1, &buffer);

  buffer= cmdPool->addCommandBuffer(VK_COMMAND_BUFFER_LEVEL_PRIMARY);

  /// static structs
  VkCommandBufferBeginInfo bufferInfo = {
    VK_STRUCTURE_TYPE_COMMAND_BUFFER_BEGIN_INFO,  /// VkStructureType                        sType
    nullptr,                                      /// const void                            *pNext
    //VK_COMMAND_BUFFER_USAGE_SIMULTANEOUS_USE_BIT& /// VkCommandBufferUsageFlags              flags
    VK_COMMAND_BUFFER_USAGE_ONE_TIME_SUBMIT_BIT,
    nullptr                                       /// const VkCommandBufferInheritanceInfo  *pInheritanceInfo
  };
 
  VkViewport view= { 0, 0, (float)vkSwap->dx, (float)vkSwap->dy, 0.0f, 1.0f};
  VkRect2D scissor= {0, 0, vkSwap->dx, vkSwap->dy};

  // command buffer recording

  res= vk.BeginCommandBuffer(buffer, &bufferInfo);
  if(res!= VK_SUCCESS) {
    error.detail("Vulkan command buffer BEGIN failed.", __FUNCTION__);
    error.vkPrint(res);
    error.window("pause");
    return;
  }

  VkRenderPassBeginInfo rpInfo;
  rpInfo.sType= VK_STRUCTURE_TYPE_RENDER_PASS_BEGIN_INFO;
  rpInfo.pNext= null;
  rpInfo.renderPass= *vkRP;
  rpInfo.framebuffer= *vkFB[i];
  rpInfo.renderArea.offset.x= 0;
  rpInfo.renderArea.offset.y= 0;
  rpInfo.renderArea.extent.width= vkSwap->dx;
  rpInfo.renderArea.extent.height= vkSwap->dy;

  VkClearValue rpColor[2] = { {0.3f, 0.2f, 0.6f, 1.0f}, {0.0f} };
  rpColor[1].depthStencil.depth= 0.0f;
  rpColor[1].depthStencil.stencil= 0;

  rpInfo.clearValueCount= 2;
  rpInfo.pClearValues= rpColor;

  vk.CmdSetViewport(buffer, 0, 1, &view);
  vk.CmdSetScissor(buffer, 0, 1, &scissor);

  vk.CmdBeginRenderPass(buffer, &rpInfo, VK_SUBPASS_CONTENTS_INLINE);
    vk.CmdBindPipeline(buffer, VK_PIPELINE_BIND_POINT_GRAPHICS, s1->pipeline);

    VkDeviceSize s= 0;
    vk.CmdBindVertexBuffers(buffer, 0, 1, &(buf2->buffer), &s);
      
    /// set the camera
    setPerspective(&cameraMat, vec3(0.0f), vec3(0.0f, 0.0f, 1.0f), 80.0f, (float)w->dx/ (float)(w->dy? w->dy: 1), 0.0f, 1200.0f);
    cameraMat*= mat4().translate(0, 0, 20);

    // MULTIPLE cubes draw
    mat4 model;
    mat4 fin;

    for(int a= -3; a<= 3; a++)
      for(int b= -3; b<= 3; b++) {
        model.identity();
        model.translate((float)(a* 4), (float)(b* 4), 0.0f);
        model*= mat4().rotate(angle, 1, 1, 0);
        model*= mat4().rotate(angle, 0, 0, 1);

        fin= cameraMat* model;

        vk.CmdPushConstants(buffer, s1->pipelineLayout, VK_SHADER_STAGE_VERTEX_BIT, 0, sizeof(mlib::mat4), &fin);
        vk.CmdDraw(buffer, 36* 3, 1, 0, 0);
      }
  vk.CmdEndRenderPass(buffer);

  res= vk.EndCommandBuffer(buffer);

  if(res!= VK_SUCCESS ) {
    error.detail("Vulkan command buffer record failed.", __FUNCTION__);
    error.vkPrint(res);
    return;
  }




  // submit cmd buffer to draw
  vk.DeviceWaitIdle(vk);
  VkPipelineStageFlags waitDstStageMask= VK_PIPELINE_STAGE_COLOR_ATTACHMENT_OUTPUT_BIT;

  VkSubmitInfo submitInfo = {
    VK_STRUCTURE_TYPE_SUBMIT_INFO,                // VkStructureType              sType
    nullptr,                                      // const void                  *pNext
    1,                                            // uint32_t                     waitSemaphoreCount
    &vkSem1->semaphore,                           // const VkSemaphore           *pWaitSemaphores
    &waitDstStageMask,                            // const VkPipelineStageFlags  *pWaitDstStageMask;
    1,                                            // uint32_t                     commandBufferCount
    &buffer,            // const VkCommandBuffer       *pCommandBuffers
    1,                                            // uint32_t                     signalSemaphoreCount
    &vkSem2->semaphore                            // const VkSemaphore           *pSignalSemaphores
  };

  res= vk.QueueSubmit(vk.queue[0].queue, 1, &submitInfo, VK_NULL_HANDLE);
  if(res!= VK_SUCCESS) {
    error.detail("Vulkan queue command buffer failed.", __FUNCTION__);
    error.vkPrint(res);
    error.window("pause");
    return;
  }

  vk.QueueWaitIdle(vk.queue[0].queue);
}



