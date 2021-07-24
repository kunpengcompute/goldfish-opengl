LOCAL_PATH := $(call my-dir)

### GLESv2 implementation ###########################################
$(call emugl-begin-shared-library,libGLESv2_emulation)
$(call emugl-import,libOpenglSystemCommon libGLESv2_enc)

LOCAL_CFLAGS += -DLOG_TAG=\"GLESv2_emulation\" -DGL_GLEXT_PROTOTYPES

LOCAL_SRC_FILES := gl2.cpp
ifeq ($(shell test $(PLATFORM_SDK_VERSION) -lt 21 && echo PreLollipop),PreLollipop)
    LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/egl
else
    LOCAL_MODULE_RELATIVE_PATH := egl
endif

ifdef USE_PREBUILT_LIBS
LOCAL_C_INCLUDES += \
    $(REPO_ROOT_DIR)/CloudDemo/InstructionEngine/Libs/Cloud/InstructionEngine \
    $(REPO_ROOT_DIR)/CloudDemo/InstructionEngine/Libs/libs/Common
else ifdef USE_PREBUILT_LIBS_KGPU
LOCAL_C_INCLUDES += \
    $(REPO_ROOT_DIR)/VMI_Cloud/3rd_groupware/instruction_engine/libs/Cloud/InstructionEngine \
    $(REPO_ROOT_DIR)/VMI_Cloud/3rd_groupware/instruction_engine/libs/libs/Common
else
LOCAL_C_INCLUDES += \
    $(REPO_ROOT_DIR)/Cloud/InstructionEngine \
    $(REPO_ROOT_DIR)/libs/Common
endif

LOCAL_SHARED_LIBRARIES += \
    libInstructionEngine

$(call emugl-end-module)
