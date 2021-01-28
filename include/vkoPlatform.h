#pragma once

// the purpose of this file, is to eliminate specific OS header files that will clog your project (aka <windows.h>)
// include this before vkObject.h, only in source files that actually will need specific OS extra headers / vulkan OS extensions (like surfaces)

#ifdef _WIN32
#define VK_USE_PLATFORM_WIN32_KHR 1
#endif
#ifdef __linux__
//#define VK_USE_PLATFORM_WAYLAND_KHR 1   <<<<<<<<<< FUTURE?
//#define VK_USE_PLATFORM_XCB_KHR 1
#define VK_USE_PLATFORM_XLIB_KHR 1
#define VK_USE_PLATFORM_XLIB_XRANDR_EXT 1
#endif
#ifdef __APPLE__
#define VK_USE_PLATFORM_MACOS_MVK 1
#endif






