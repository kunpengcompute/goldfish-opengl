LOCAL_PATH := $(call my-dir)

$(call emugl-begin-shared-library,vulkan.radv)
$(call emugl-set-shared-library-subpath,hw)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-import,libOpenglSystemCommon libvulkan_enc libRenderControl_enc)
$(call emugl-import,libOpenglCodecCommon$(GOLDFISH_OPENGL_LIB_SUFFIX))

# Vulkan include dir
#ifeq (true,$(GOLDFISH_OPENGL_BUILD_FOR_HOST))

#	$(HOST_EMUGL_PATH)/host/include
LOCAL_C_INCLUDES += \
	$(LOCAL_PATH)/../../android-emu \
	frameworks/native/vulkan/include

#endif

ifneq (true,$(GOLDFISH_OPENGL_BUILD_FOR_HOST))

# Only import androidemu if not building for host.
# if building for host, we already import android-emu.
$(call emugl-export,SHARED_LIBRARIES,libandroidemu)
ifeq (1,$(filter 1,$(shell echo "$$(( $(PLATFORM_SDK_VERSION) > 28 ))" )))
LOCAL_HEADER_LIBRARIES += \
    hwvulkan_headers \
    vulkan_headers

endif

endif

LOCAL_CFLAGS += \
    -DLOG_TAG=\"goldfish_vulkan\" \
    -Wno-missing-field-initializers \
    -fvisibility=hidden \
    -fstrict-aliasing \
    -DVK_USE_PLATFORM_ANDROID_KHR \
    -DVK_NO_PROTOTYPES \
    -Wno-unused-parameter \
    -Wno-unused-function \
	-Wno-cast-calling-convention

LOCAL_SRC_FILES := \
    func_table.cpp \
    goldfish_vulkan.cpp \

$(call emugl-end-module)
