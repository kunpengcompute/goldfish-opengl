LOCAL_PATH := $(call my-dir)

### GLESv1_enc Encoder ###########################################
$(call emugl-begin-shared-library,libGLESv1_enc)

LOCAL_CFLAGS += -DLOG_TAG=\"emuglGLESv1_enc\"

LOCAL_SRC_FILES := \
        GLEncoder.cpp \
        GLEncoderUtils.cpp \
        gl_client_context.cpp \
        gl_enc.cpp \
        gl_entry.cpp

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

$(call emugl-import,libOpenglCodecCommon)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-export,C_INCLUDES,$(intermediates))

$(call emugl-end-module)
