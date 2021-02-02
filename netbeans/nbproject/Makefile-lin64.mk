#
# Generated Makefile - do not edit!
#
# Edit the Makefile in the project folder instead (../Makefile). Each target
# has a -pre and a -post target defined where you can add customized code.
#
# This makefile implements configuration specific macros and targets.


# Environment
MKDIR=mkdir
CP=cp
GREP=grep
NM=nm
CCADMIN=CCadmin
RANLIB=ranlib
CC=clang
CCC=clang++
CXX=clang++
FC=gfortran
AS=as

# Macros
CND_PLATFORM=CLang-Linux
CND_DLIB_EXT=so
CND_CONF=lin64
CND_DISTDIR=dist
CND_BUILDDIR=build

# Include project Makefile
include Makefile

# Object Directory
OBJECTDIR=${CND_BUILDDIR}/${CND_CONF}/${CND_PLATFORM}

# Object Files
OBJECTFILES= \
	${OBJECTDIR}/_ext/511e4115/vkObject.o \
	${OBJECTDIR}/_ext/511e4115/vkoBuffer.o \
	${OBJECTDIR}/_ext/511e4115/vkoCommandBuffer.o \
	${OBJECTDIR}/_ext/511e4115/vkoCommandPool.o \
	${OBJECTDIR}/_ext/511e4115/vkoDescriptorPool.o \
	${OBJECTDIR}/_ext/511e4115/vkoDynamicSet.o \
	${OBJECTDIR}/_ext/511e4115/vkoExt.o \
	${OBJECTDIR}/_ext/511e4115/vkoFence.o \
	${OBJECTDIR}/_ext/511e4115/vkoFramebuffer.o \
	${OBJECTDIR}/_ext/511e4115/vkoFuncs.o \
	${OBJECTDIR}/_ext/511e4115/vkoImage.o \
	${OBJECTDIR}/_ext/511e4115/vkoMemory.o \
	${OBJECTDIR}/_ext/511e4115/vkoRenderPass.o \
	${OBJECTDIR}/_ext/511e4115/vkoSampler.o \
	${OBJECTDIR}/_ext/511e4115/vkoSemaphore.o \
	${OBJECTDIR}/_ext/511e4115/vkoSetLayout.o \
	${OBJECTDIR}/_ext/511e4115/vkoShader.o \
	${OBJECTDIR}/_ext/511e4115/vkoSwapchain.o


# C Compiler Flags
CFLAGS=

# CC Compiler Flags
CCFLAGS=
CXXFLAGS=

# Fortran Compiler Flags
FFLAGS=

# Assembler Flags
ASFLAGS=

# Link Libraries and Options
LDLIBSOPTIONS=

# Build Targets
.build-conf: ${BUILD_SUBPROJECTS}
	"${MAKE}"  -f nbproject/Makefile-${CND_CONF}.mk ../lib/vko.lin64.so

../lib/vko.lin64.so: ${OBJECTFILES}
	${MKDIR} -p ../lib
	${RM} ../lib/vko.lin64.so
	${AR} -rv ../lib/vko.lin64.so ${OBJECTFILES} 
	$(RANLIB) ../lib/vko.lin64.so

${OBJECTDIR}/_ext/511e4115/vkObject.o: ../src/vkObject.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkObject.o ../src/vkObject.cpp

${OBJECTDIR}/_ext/511e4115/vkoBuffer.o: ../src/vkoBuffer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoBuffer.o ../src/vkoBuffer.cpp

${OBJECTDIR}/_ext/511e4115/vkoCommandBuffer.o: ../src/vkoCommandBuffer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoCommandBuffer.o ../src/vkoCommandBuffer.cpp

${OBJECTDIR}/_ext/511e4115/vkoCommandPool.o: ../src/vkoCommandPool.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoCommandPool.o ../src/vkoCommandPool.cpp

${OBJECTDIR}/_ext/511e4115/vkoDescriptorPool.o: ../src/vkoDescriptorPool.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoDescriptorPool.o ../src/vkoDescriptorPool.cpp

${OBJECTDIR}/_ext/511e4115/vkoDynamicSet.o: ../src/vkoDynamicSet.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoDynamicSet.o ../src/vkoDynamicSet.cpp

${OBJECTDIR}/_ext/511e4115/vkoExt.o: ../src/vkoExt.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoExt.o ../src/vkoExt.cpp

${OBJECTDIR}/_ext/511e4115/vkoFence.o: ../src/vkoFence.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoFence.o ../src/vkoFence.cpp

${OBJECTDIR}/_ext/511e4115/vkoFramebuffer.o: ../src/vkoFramebuffer.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoFramebuffer.o ../src/vkoFramebuffer.cpp

${OBJECTDIR}/_ext/511e4115/vkoFuncs.o: ../src/vkoFuncs.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoFuncs.o ../src/vkoFuncs.cpp

${OBJECTDIR}/_ext/511e4115/vkoImage.o: ../src/vkoImage.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoImage.o ../src/vkoImage.cpp

${OBJECTDIR}/_ext/511e4115/vkoMemory.o: ../src/vkoMemory.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoMemory.o ../src/vkoMemory.cpp

${OBJECTDIR}/_ext/511e4115/vkoRenderPass.o: ../src/vkoRenderPass.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoRenderPass.o ../src/vkoRenderPass.cpp

${OBJECTDIR}/_ext/511e4115/vkoSampler.o: ../src/vkoSampler.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoSampler.o ../src/vkoSampler.cpp

${OBJECTDIR}/_ext/511e4115/vkoSemaphore.o: ../src/vkoSemaphore.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoSemaphore.o ../src/vkoSemaphore.cpp

${OBJECTDIR}/_ext/511e4115/vkoSetLayout.o: ../src/vkoSetLayout.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoSetLayout.o ../src/vkoSetLayout.cpp

${OBJECTDIR}/_ext/511e4115/vkoShader.o: ../src/vkoShader.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoShader.o ../src/vkoShader.cpp

${OBJECTDIR}/_ext/511e4115/vkoSwapchain.o: ../src/vkoSwapchain.cpp
	${MKDIR} -p ${OBJECTDIR}/_ext/511e4115
	${RM} "$@.d"
	$(COMPILE.cc) -O2 -I../.. -I../../Vulkan-Headers/include/vulkan -MMD -MP -MF "$@.d" -o ${OBJECTDIR}/_ext/511e4115/vkoSwapchain.o ../src/vkoSwapchain.cpp

# Subprojects
.build-subprojects:

# Clean Targets
.clean-conf: ${CLEAN_SUBPROJECTS}
	${RM} -r ${CND_BUILDDIR}/${CND_CONF}

# Subprojects
.clean-subprojects:

# Enable dependency checking
.dep.inc: .depcheck-impl

include .dep.inc
