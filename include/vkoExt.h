#pragma once




// Vulkan EXTENSIONS

struct VkoExt {
  const char *name;     // extension's name
  int32_t regNr;        // registered extension number
  int8_t type;          // 0= instance, 1= device
  bool enable;          // set this to true to enable the extension
  bool isAvaible;       // this will be automatically filled to true or false, if the extension is avaible in the current vulkan instance / device
};



struct VkoExtensions {
  VkoExtensions();

  VkoExt *getDeviceExt(const char *name);
  VkoExt *getInstanceExt(const char *name);
  VkoExt *getExtension(const char *name);

  VkoExt *getInstanceExtByNumber(int32_t registeredExtensionNumber);
  VkoExt *getDeviceExtByNumber(int32_t registeredExtensionNumber);
  VkoExt *getExtensionByNumber(int32_t registeredExtensionNumber);

  bool enableExtension(const char *name);
  bool isExtensionAvaible(const char *name);

  bool populateAvailabilityInstance();
  bool populateAvailabilityDevice(VkPhysicalDevice);

  // from all the manually enabled instance extensions, creates the array of null-terminated strings to pass to vulkan; <out_nrExtensions> will return number of extensions written; dealloc with delete[]
  void createInstanceExtensionsStringArray(char ***out_stringArray, uint32_t *out_nrExtensions= NULL) { _createExtStr(0, out_stringArray, out_nrExtensions); }
  // from all the manually enabled device extensions, creates the array of null-terminated strings to pass to vulkan; <out_nrExtensions> will return number of extensions written; dealloc with delete[]
  void createDeviceExtensionsStringArray(char ***out_stringArray, uint32_t *out_nrExtensions= NULL) { _createExtStr(1, out_stringArray, out_nrExtensions); }


  // new extensions must be added in their proper placement in this structure,
  //   then added in the rawClass too, at the back of the list in that constructor
  // deprecated extensions should only be moved to the deprecated struct, and not changed in the rawClass, in the cpp


  // instance extensions

  union {
    struct {
      VkoExt vk_KHR_android_surface;                // #009 [instance] [android surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_android_surface
      VkoExt vk_KHR_display;                        // #003 [instance] [enumerate displays and available modes on a given device (it has some create stuff too)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_display
      VkoExt vk_KHR_get_display_properties2;        // #122 [instance] [extra device display properties and capabilities] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_get_display_properties2
      VkoExt vk_KHR_get_surface_capabilities2;      // #120 [instance] [extra device surface capabilities] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_get_surface_capabilities2
      VkoExt vk_KHR_surface;                        // #001 [instance] [surfaces] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_surface
      VkoExt vk_KHR_wayland_surface;                // #007 [instance] [WAYLAND surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_wayland_surface
      VkoExt vk_KHR_win32_surface;                  // #010 [instance] [WIN surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_win32_surface
      VkoExt vk_KHR_xcb_surface;                    // #006 [instance] [XCB surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_xcb_surface
      VkoExt vk_KHR_xlib_surface;                   // #005 [instance] [XLIB surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_xlib_surface
      VkoExt vk_EXT_acquire_xlib_display;           // #090 [instance] [exclusive control on a display currently associated with an X11 screen] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_acquire_xlib_display
      // 10
      VkoExt vk_EXT_debug_utils;                    // #129 [instance] [tons of debug, tag objects, message back, more stuff if you enable validation layers] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_debug_utils
      VkoExt vk_EXT_direct_mode_display;            // #089 [instance] [take exclusive control of displays] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_direct_mode_display
      VkoExt vk_EXT_display_surface_counter;        // #091 [instance] [vertical blanking period counter associated with display surfaces] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_display_surface_counter
      VkoExt vk_EXT_swapchain_colorspace;           // #105 [instance] [Extending VkColorSpaceKHR? i guess] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_swapchain_colorspace
      VkoExt vk_FUCHSIA_imagepipe_surface;          // #215 [instance] [create a VkSurfaceKHR object that refers to a Fuchsia imagePipeHandle] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_FUCHSIA_imagepipe_surface
      VkoExt vk_MVK_ios_surface;                    // #123 [instance] [surface to UIView (iOS)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_MVK_ios_surface
      VkoExt vk_MVK_macos_surface;                  // #124 [instance] [surface to NSView (MAC)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_MVK_macos_surface
      VkoExt vk_NN_vi_surface;                      // #063 [instance] [surface to nn::vi::Layer] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NN_vi_surface
      VkoExt vk_EXT_headless_surface;               // #257 [instance] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_headless_surface
      VkoExt vk_KHR_surface_protected_capabilities; // #240 [instance] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_KHR_surface_protected_capabilities
      // 20
      VkoExt vk_EXT_metal_surface;                  // #218 [instance] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_metal_surface
      VkoExt vk_EXT_validation_features;            // #248 [instance] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_validation_features
      VkoExt vk_GGP_stream_descriptor_surface;      // #50  [Instance] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_GGP_stream_descriptor_surface
      //VkoExt ; // #000 [Instance] 
    };
    VkoExt raw[24]; // +terminator
  } instance;


  union {
    struct {
      VkoExt vk_KHR_device_group_creation;            // #071 [instance] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_device_group_creation
      VkoExt vk_KHR_external_fence_capabilities;      // #113 [instance] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_fence_capabilities
      VkoExt vk_KHR_external_memory_capabilities;     // #072 [instance] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_memory_capabilities
      VkoExt vk_KHR_external_semaphore_capabilities;  // #077 [instance] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_semaphore_capabilities
      VkoExt vk_KHR_get_physical_device_properties2;  // #060 [instance] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_get_physical_device_properties2
      VkoExt vk_EXT_debug_report;                     // #012 [instance] [DEPRECATED by VK_EXT_debug_utils] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_debug_report
      VkoExt vk_NV_external_memory_capabilities;      // #056 [instance] [DEPRECATED by VK_KHR_external_memory_capabilities that was promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_external_memory_capabilities
      VkoExt vk_EXT_validation_flags;                 // #062 [instance] Deprecated by VK_EXT_validation_features [instance creation: pNext extra struct] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_validation_flags
    };
    VkoExt raw[9]; // +terminator
  } instanceDeprecated;


  // device extensions
  union {
    struct {
      VkoExt vk_KHR_display_swapchain;              // #004 [device] [create a swapchain directly on a device�s display] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_display_swapchain
      VkoExt vk_KHR_external_fence_fd;              // #116 [device] [import/export fence payload POSIX] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_fence_fd
      VkoExt vk_KHR_external_fence_win32;           // #115 [device] [import/export fence payload WIN] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_fence_win32
      VkoExt vk_KHR_external_memory_fd;             // #075 [device] [import/export POSIX file descr/vulkan mem] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_memory_fd
      VkoExt vk_KHR_external_memory_win32;          // #074 [device] [import/export WIN file descr/vulkan mem] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_memory_win32
      VkoExt vk_KHR_external_semaphore_fd;          // #080 [device] [import/export semaphore payload POSIX] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_semaphore_fd
      VkoExt vk_KHR_external_semaphore_win32;       // #079 [device] [import/export semaphore payload WIN] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_semaphore_win32
      VkoExt vk_KHR_incremental_present;            // #085 [device] [avoid wasting time presenting parts of the surface that haven�t changed] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_incremental_present
      VkoExt vk_KHR_push_descriptor;                // #081 [device] [Push descriptors may enable easier porting from older APIs] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_push_descriptor
      VkoExt vk_KHR_shared_presentable_image;       // #112 [device] [shared presentable image] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_shared_presentable_image
      // 10
      VkoExt vk_KHR_swapchain;                      // #002 [device] [present rendering results to a surface] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_swapchain
      VkoExt vk_KHR_win32_keyed_mutex;              // #076 [device] [Vulkan/Direct3D mem access mutex] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_win32_keyed_mutex
      VkoExt vk_EXT_astc_decode_mode;               // #068 [device] [compressed textures exact decoding] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_astc_decode_mode
      VkoExt vk_EXT_blend_operation_advanced;       // #149 [device] [..advanced blending, what else?] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_blend_operation_advanced
      VkoExt vk_EXT_calibrated_timestamps;          // #185 [device] ["query calibrated timestamps obtained quasi simultaneously from two time domains"] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_calibrated_timestamps
      VkoExt vk_EXT_conditional_rendering;          // #082 [device] [rendering conditional on a val in buff memory] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_conditional_rendering
      VkoExt vk_EXT_conservative_rasterization;     // #102 [device] [new rasterization mode, culling stuff, probly to avoid stuff just apearing on the screen] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_conservative_rasterization
      VkoExt vk_EXT_depth_range_unrestricted;       // #014 [device] [~3 depth restriction removes] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_depth_range_unrestricted
      VkoExt vk_EXT_discard_rectangles;             // #100 [device] [�discard rectangles� (no lines/points/triangles in that space)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_discard_rectangles
      VkoExt vk_EXT_display_control;                // #092 [device] [utility functions for display/swapchain] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_display_control
      // 20
      VkoExt vk_EXT_external_memory_dma_buf;        // #126 [device] [LINUX those files that act like memory] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_external_memory_dma_buf
      VkoExt vk_EXT_external_memory_host;           // #179 [device] [import host alocations/maped foreign device to vulkan mem] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_external_memory_host
      VkoExt vk_EXT_global_priority;                // #175 [device] [system-wide scope for queue priorities] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_global_priority
      VkoExt vk_EXT_hdr_metadata;                   // #106 [devoce] [SMPTECTA (hdr) metadata to a swapchain] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_hdr_metadata
      VkoExt vk_EXT_image_drm_format_modifier;      // #159 [device] [LINUX drm format modifiers for images] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_image_drm_format_modifier
      VkoExt vk_EXT_inline_uniform_block;           // #139 [device] [uniform blocks -> descriptor sets] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_inline_uniform_block
      VkoExt vk_EXT_pci_bus_info;                   // #213 [device] [PCI bus information about a physical device] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_pci_bus_info
      VkoExt vk_EXT_post_depth_coverage;            // #156 [device] [support for SPIR-V SPV_KHR_post_depth_coverage] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_post_depth_coverage
      VkoExt vk_EXT_queue_family_foreign;           // #127 [device] [special queue family] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_queue_family_foreign
      VkoExt vk_EXT_sample_locations;               // #144 [device] [modify the locations of samples within a pixel used in rasterization] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_sample_locations
      // 30
      VkoExt vk_EXT_shader_stencil_export;          // #141 [device] [support for SPIR-V SPV_EXT_shader_stencil_export] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_shader_stencil_export
      VkoExt vk_EXT_shader_subgroup_ballot;         // #065 [device] [support for SPIR-V SPV_KHR_shader_ballot] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_shader_subgroup_ballot
      VkoExt vk_EXT_shader_subgroup_vote;           // #066 [device] [support for SPIR-V SPV_KHR_subgroup_vote] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_shader_subgroup_vote
      VkoExt vk_EXT_transform_feedback;             // #029 [device] [match OpenGL core transform feedback functionality] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_transform_feedback
      VkoExt vk_EXT_validation_cache;               // #161 [device] [mechanism for caching the results of potentially expensive internal validation operations] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_validation_cache
      VkoExt vk_EXT_vertex_attribute_divisor;       // #191 [device] [instanced rendering: repeat vertex attrib a nr of times] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_vertex_attribute_divisor
      VkoExt vk_AMD_buffer_marker;                  // #180 [device] [debug:tracking which pipelined command contributed to device loss] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_buffer_marker
      VkoExt vk_AMD_gcn_shader;                     // #026 [device] [support for SPV_AMD_gcn_shader] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_gcn_shader
      VkoExt vk_AMD_memory_overallocation_behavior; // #190 [device] [explicit overallocation beyond the device memory heap sizes] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_memory_overallocation_behavior
      VkoExt vk_AMD_mixed_attachment_samples;       // #137 [device] [depth/stencil sample count that is larger than the color sample count] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_mixed_attachment_samples
      // 40
      VkoExt vk_AMD_rasterization_order;            // #019 [device] [control the order of primitive rasterization] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_rasterization_order
      VkoExt vk_AMD_shader_ballot;                  // #038 [device] [support for SPV_AMD_shader_ballot] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_ballot
      VkoExt vk_AMD_shader_core_properties;         // #186 [device] [exposes shader core properties] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_core_properties
      VkoExt vk_AMD_shader_explicit_vertex_parameter; // #022 [device] [support for SPV_AMD_shader_explicit_vertex_parameter] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_explicit_vertex_parameter
      VkoExt vk_AMD_shader_fragment_mask;           // #138 [device] [efficient read access to the fragment mask in compressed multisampled color surfaces] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_fragment_mask
      VkoExt vk_AMD_shader_image_load_store_lod;    // #047 [device] [support for SPV_AMD_shader_image_load_store_lod] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_image_load_store_lod
      VkoExt vk_AMD_shader_info;                    // #043 [device] [query info about a compiled shader, part of a pipeline] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_info
      VkoExt vk_AMD_shader_trinary_minmax;          // #021 [device] [support for SPV_AMD_shader_trinary_minmax] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_shader_trinary_minmax
      VkoExt vk_AMD_texture_gather_bias_lod;        // #042 [device] [support for SPV_AMD_texture_gather_bias_lod] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_texture_gather_bias_lod
      VkoExt vk_ANDROID_external_memory_android_hardware_buffer; // #130 [device] [import Android AHardwareBuffer objects] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_ANDROID_external_memory_android_hardware_buffer
      // 50
      VkoExt vk_GOOGLE_decorate_string;             // #225 [device] [support for SPV_GOOGLE_decorate_string] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_GOOGLE_decorate_string
      VkoExt vk_GOOGLE_display_timing;              // #093 [device] [obtain info about the presentation engine�s display] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_GOOGLE_display_timing
      VkoExt vk_GOOGLE_hlsl_functionality1;         // #224 [device] [support for SPV_GOOGLE_hlsl_functionality1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_GOOGLE_hlsl_functionality1
      VkoExt vk_IMG_filter_cubic;                   // #016 [device] [high quality cubic filtering mode] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_IMG_filter_cubic
      VkoExt vk_IMG_format_pvrtc;                   // #017 [] [] ??? NO INFO ATM ON THE REGISTRY
      VkoExt vk_NVX_device_generated_commands;      // #087 [device] [generate a number of critical commands for command buffers] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NVX_device_generated_commands
      VkoExt vk_NVX_multiview_per_view_attributes;  // #098 [device] [may only execute the vertex processing stages once for all views rather than once per-view] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NVX_multiview_per_view_attributes
      VkoExt vk_NV_clip_space_w_scaling;            // #088 [device] [accurate VR barrel distortion] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_clip_space_w_scaling
      VkoExt vk_NV_compute_shader_derivatives;      // #202 [device] [support for SPV_NV_compute_shader_derivatives] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_compute_shader_derivatives
      VkoExt vk_NV_corner_sampled_image;            // #051 [device] [new image organization �corner-sampled� (ints, best for texture dictionary i guess)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_corner_sampled_image
      // 60
      VkoExt vk_NV_device_diagnostic_checkpoints;   // #207 [device] [insert markers in the command stream and associate them with custom data] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_device_diagnostic_checkpoints
      VkoExt vk_NV_fill_rectangle;                  // #154 [device] [draw rectangles with only one triangle] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_fill_rectangle
      VkoExt vk_NV_fragment_coverage_to_color;      // #150 [device] [] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_fragment_coverage_to_color
      VkoExt vk_NV_fragment_shader_barycentric;     // #204 [device] [support for SPV_NV_fragment_shader_barycentric] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_fragment_shader_barycentric
      VkoExt vk_NV_framebuffer_mixed_samples;       // #153 [device] [] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_framebuffer_mixed_samples
      VkoExt vk_NV_geometry_shader_passthrough;     // #096 [device] [support for SPV_NV_geometry_shader_passthrough] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_geometry_shader_passthrough
      VkoExt vk_NV_mesh_shader;                     // #203 [device] [generate collections of geometric primitives ] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_mesh_shader
      VkoExt vk_NV_ray_tracing;                     // #166 [device] [raytracing, what else] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_ray_tracing
      VkoExt vk_NV_representative_fragment_test;    // #167 [device] [useful for apps that render to determine what primitives are visible] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_representative_fragment_test
      VkoExt vk_NV_sample_mask_override_coverage;   // #095 [device] [support for SPV_NV_sample_mask_override_coverage] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_sample_mask_override_coverage
      // 70
      VkoExt vk_NV_scissor_exclusive;               // #206 [device] [basically inverse-scencil] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_scissor_exclusive
      VkoExt vk_NV_shader_image_footprint;          // #205 [device] [support for SPV_NV_shader_image_footprint] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_shader_image_footprint
      VkoExt vk_NV_shader_subgroup_partitioned;     // #199 [device] [support for SPV_NV_shader_subgroup_partitioned] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_shader_subgroup_partitioned
      VkoExt vk_NV_shading_rate_image;              // #165 [device] [eye focus, the blur parts can get less fragments] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_shading_rate_image
      VkoExt vk_NV_viewport_array2;                 // #097 [device] [support for SPV_NV_viewport_array2] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_viewport_array2
      VkoExt vk_NV_viewport_swizzle;                // #099 [device] [] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_viewport_swizzle
      VkoExt vk_KHR_performance_query;              // #117 [device] [...adds a mechanism to allow querying of performance counters for use in applications and by profiling tools.] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap40.html#VK_KHR_performance_query
      VkoExt vk_KHR_pipeline_executable_properties; // #270 [device] [debugging and performance tool] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap40.html#VK_KHR_pipeline_executable_properties
      VkoExt vk_NVX_image_view_handle;              // #31  [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NVX_image_view_handle
      VkoExt vk_INTEL_performance_query;            // #211 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_INTEL_performance_query
      // 80
      VkoExt vk_AMD_display_native_hdr;             // #214 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_AMD_display_native_hdr
      VkoExt vk_EXT_tooling_info;                   // #246 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_tooling_info
      VkoExt vk_NV_cooperative_matrix;              // #250 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NV_cooperative_matrix
      VkoExt vk_NV_coverage_reduction_mode;         // #251 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NV_coverage_reduction_mode
      VkoExt vk_EXT_line_rasterization;             // #260 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_line_rasterization
      VkoExt vk_KHR_shader_clock;                   // #182 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_KHR_shader_clock
      VkoExt vk_KHR_swapchain_mutable_format;       // #201 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_KHR_swapchain_mutable_format
      VkoExt vk_EXT_depth_clip_enable;              // #103 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_depth_clip_enable
      VkoExt vk_EXT_filter_cubic;                   // #171 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_filter_cubic
      VkoExt vk_EXT_fragment_density_map;           // #219 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_fragment_density_map
      // 90
      VkoExt vk_EXT_fragment_shader_interlock;      // #252 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_fragment_shader_interlock
      VkoExt vk_EXT_full_screen_exclusive;          // #256 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_fragment_shader_interlock
      VkoExt vk_EXT_index_type_uint8;               // #266 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_index_type_uint8
      VkoExt vk_EXT_memory_budget;                  // #238 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_memory_budget
      VkoExt vk_EXT_memory_priority;                // #239 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_memory_priority
      VkoExt vk_EXT_pipeline_creation_feedback;     // #193 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_pipeline_creation_feedback
      VkoExt vk_EXT_shader_demote_to_helper_invocation; // #277 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_shader_demote_to_helper_invocation
      VkoExt vk_EXT_subgroup_size_control;          // #226 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_subgroup_size_control
      VkoExt vk_EXT_texel_buffer_alignment;         // #282 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_texel_buffer_alignment
      VkoExt vk_EXT_texture_compression_astc_hdr;   // #67  [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_texture_compression_astc_hdr
      // 100
      VkoExt vk_EXT_ycbcr_image_arrays;             // #253 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_ycbcr_image_arrays
      VkoExt vk_AMD_device_coherent_memory;         // #230 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_AMD_device_coherent_memory
      VkoExt vk_AMD_pipeline_compiler_control;      // #184 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_AMD_pipeline_compiler_control
      VkoExt vk_AMD_shader_core_properties2;        // #228 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_AMD_shader_core_properties2
      VkoExt vk_GGP_frame_token;                    // #192 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_GGP_frame_token
      VkoExt vk_GOOGLE_user_type;                   // #290 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_GOOGLE_user_type
      VkoExt vk_INTEL_shader_integer_functions2;    // #210 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_INTEL_shader_integer_functions2
      VkoExt vk_NV_dedicated_allocation_image_aliasing; // #241 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NV_dedicated_allocation_image_aliasing
      VkoExt vk_NV_shader_sm_builtins;              // #155 [device] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_NV_shader_sm_builtins
    };
    VkoExt raw[110]; // +terminator
  } device;

  // DEPRECATED
  union {
    struct {
      VkoExt vk_KHR_16bit_storage;                  // #084 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_16bit_storage
      VkoExt vk_KHR_bind_memory2;                   // #158 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_bind_memory2
      VkoExt vk_KHR_dedicated_allocation;           // #128 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_dedicated_allocation
      VkoExt vk_KHR_descriptor_update_template;     // #086 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_descriptor_update_template
      VkoExt vk_KHR_device_group;                   // #061 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_device_group
      VkoExt vk_KHR_external_fence;                 // #114 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_fence
      VkoExt vk_KHR_external_memory;                // #073 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_memory
      VkoExt vk_KHR_external_semaphore;             // #078 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_external_semaphore
      VkoExt vk_KHR_get_memory_requirements2;       // #147 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_get_memory_requirements2
      VkoExt vk_KHR_maintenance1;                   // #070 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_maintenance1
      // 10
      VkoExt vk_KHR_maintenance2;                   // #118 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_maintenance2
      VkoExt vk_KHR_maintenance3;                   // #169 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_maintenance3
      VkoExt vk_KHR_multiview;                      // #054 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_multiview
      VkoExt vk_KHR_relaxed_block_layout;           // #145 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_relaxed_block_layout
      VkoExt vk_KHR_sampler_ycbcr_conversion;       // #157 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_sampler_ycbcr_conversion
      VkoExt vk_KHR_shader_draw_parameters;         // #064 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_shader_draw_parameters
      VkoExt vk_KHR_storage_buffer_storage_class;   // #132 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_storage_buffer_storage_class
      VkoExt vk_KHR_variable_pointers;              // #121 [device] [Promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_variable_pointers
      VkoExt vk_EXT_debug_marker;                   // #023 [device] [Promoted to VK_EXT_debug_utils] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_debug_marker
      VkoExt vk_AMD_draw_indirect_count;            // #034 [device] [Promoted to VK_KHR_draw_indirect_count] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_draw_indirect_count
      // 20
      VkoExt vk_AMD_negative_viewport_height;       // #036 [device] [DEPRECATED by VK_KHR_maintenance1 -> promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_negative_viewport_height
      VkoExt vk_NV_dedicated_allocation;            // #027 [device] [DEPRECATED by VK_KHR_dedicated_allocation -> Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_dedicated_allocation
      VkoExt vk_NV_external_memory;                 // #057 [device] [DEPRECATED by VK_KHR_external_memory -> promoted to Vulkan 1.1] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_external_memory
      VkoExt vk_NV_external_memory_win32;           // #058 [device] [DEPRECATED by VK_KHR_external_memory_win32] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_external_memory_win32
      VkoExt vk_NV_glsl_shader;                     // #013 [device] [DEPRECATED (ABANDONED!!!)] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_glsl_shader
      VkoExt vk_NV_win32_keyed_mutex;               // #059 [device] [Promoted to VK_KHR_win32_keyed_mutex] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_NV_win32_keyed_mutex
      VkoExt vk_KHR_timeline_semaphore;             // #208 [device] [Promoted to Vulkan 1.2] [type of semaphore] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap40.html#VK_KHR_timeline_semaphore
      VkoExt vk_KHR_buffer_device_address;          // #258 [device] [Promoted to Vulkan 1.2] https://www.khronos.org/registry/vulkan/specs/1.2-khr-extensions/html/chap40.html#VK_KHR_buffer_device_address
      VkoExt vk_EXT_buffer_device_address;          // #245 [device] [DEPRECATED by VK_KHR_buffer_device_address -> Promoted to Vulkan 1.2] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_buffer_device_address
      VkoExt vk_EXT_host_query_reset;               // #262 [device] [Promoted to Vulkan 1.2] https://www.khronos.org/registry/vulkan/specs/1.2-extensions/html/chap44.html#VK_EXT_host_query_reset
      // 30
      VkoExt vk_KHR_8bit_storage;                   // #178 [device] Promoted to Vulkan 1.2 [allows use of 8-bit types in uniform and storage buffers] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_8bit_storage
      VkoExt vk_KHR_create_renderpass2;             // #110 [device] Promoted to Vulkan 1.2 [extended render passes] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_create_renderpass2
      VkoExt vk_KHR_draw_indirect_count;            // #170 [device] Promoted to Vulkan 1.2 [generate arbitrary amounts of draw commands and execute them without host intervention] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_draw_indirect_count
      VkoExt vk_KHR_driver_properties;              // #197 [device] Promoted to Vulkan 1.2 [what driver coresponds to what GPU] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_driver_properties
      VkoExt vk_KHR_image_format_list;              // #148 [device] Promoted to Vulkan 1.2 [provide the list of all formats that can be used with an image when it is created] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_image_format_list
      VkoExt vk_KHR_sampler_mirror_clamp_to_edge;   // #015 [device] Promoted to Vulkan 1.2 [mirror_clamp_to_edge<- textures] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_sampler_mirror_clamp_to_edge
      VkoExt vk_KHR_shader_atomic_int64;            // #181 [device] Promoted to Vulkan 1.2 [int64] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_shader_atomic_int64
      VkoExt vk_EXT_descriptor_indexing;            // #162 [device] Promoted to Vulkan 1.2 [descriptor sets containing substantially all of app resources] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_descriptor_indexing
      VkoExt vk_EXT_sampler_filter_minmax;          // #131 [device] Promoted to Vulkan 1.2 [new sampler parameter] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_sampler_filter_minmax
      VkoExt vk_EXT_scalar_block_layout;            // #222 [device] Promoted to Vulkan 1.2 [modifies the alignment rules for uniforms/etc buffers] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_scalar_block_layout
      // 40
      VkoExt vk_EXT_separate_stencil_usage;         // #247 [device] Promoted to Vulkan 1.2 [image creation flags for stencil/depth stencil] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_separate_stencil_usage
      VkoExt vk_EXT_shader_viewport_index_layer;    // #163 [device] Promoted to Vulkan 1.2 [vars with Layer and ViewportIndex built-ins can be exported] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_EXT_shader_viewport_index_layer
      VkoExt vk_AMD_gpu_shader_half_float;          // #037 [device] Deprecated by VK_KHR_shader_float16_int8 -> Promoted to Vulkan 1.2 [support for SPV_AMD_gpu_shader_half_float] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_gpu_shader_half_float
      VkoExt vk_AMD_gpu_shader_int16;               // #133 [device] Deprecated by VK_KHR_shader_float16_int8 -> Promoted to Vulkan 1.2 [support for SPV_AMD_gpu_shader_int16] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_AMD_gpu_shader_int16
      VkoExt vk_KHR_vulkan_memory_model;            // #212 [device] Promoted to Vulkan 1.2 [sync memory accessed by multiple shaders] https://www.khronos.org/registry/vulkan/specs/1.1-extensions/html/vkspec.html#VK_KHR_vulkan_memory_model
    };
    VkoExt raw[46]; // +terminator
  } deviceDeprecated;


  private:
  void _createExtStr(int8_t type, char ***out_stringArray, uint32_t *out_nrExtensions);
  vkObject *_vko;
  friend class vkObject;
};










