LOCAL_PATH := $(call my-dir)

### GLESv2_enc Encoder ###########################################
$(call emugl-begin-shared-library,libGLESv2_enc)

LOCAL_SRC_FILES := \
    GL2Encoder.cpp \
    GLESv2Validation.cpp

LOCAL_CFLAGS += -DLOG_TAG=\"emuglGLESv2_enc\"

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

LOCAL_SHARED_LIBRARIES := \
    libInstructionEngine

$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-import,libOpenglCodecCommon)

$(call emugl-end-module)
