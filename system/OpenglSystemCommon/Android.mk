LOCAL_PATH := $(call my-dir)

$(call emugl-begin-shared-library,libOpenglSystemCommon)
$(call emugl-import,libGLESv1_enc libGLESv2_enc libRenderControl_enc)

$(call emugl-import,libvulkan_enc)

LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../../android-emu \
	$(LOCAL_PATH)/../../shared/GoldfishAddressSpace/include \
    frameworks/native/vulkan/include

LOCAL_SRC_FILES := \
    FormatConversions.cpp \
    HostConnection.cpp \
    ExtendedRCEncoderContext.cpp \
    QemuPipeStream.cpp \
    ThreadInfo.cpp

ifdef IS_AT_LEAST_OPD1
LOCAL_HEADER_LIBRARIES += libnativebase_headers

ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) > 28 ))" )))
LOCAL_HEADER_LIBRARIES += vulkan_headers
endif

$(call emugl-export,HEADER_LIBRARIES,libnativebase_headers)
endif

ifdef IS_AT_LEAST_OPD1
LOCAL_HEADER_LIBRARIES += libhardware_headers
$(call emugl-export,HEADER_LIBRARIES,libhardware_headers)
endif
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH) bionic/libc/private bionic/libc)

$(call emugl-end-module)
