# This build script corresponds to a library containing many definitions
# common to both the guest and the host. They relate to
#
LOCAL_PATH := $(call my-dir)

commonSources := \
        GLClientState.cpp \
        GLESTextureUtils.cpp \
        ChecksumCalculator.cpp \
        GLSharedGroup.cpp \
        glUtils.cpp \
        IndexRangeCache.cpp \
        SocketStream.cpp \
        TcpStream.cpp \

### CodecCommon  guest ##############################################
$(call emugl-begin-static-library,libOpenglCodecCommon)

LOCAL_SRC_FILES := $(commonSources)

LOCAL_CFLAGS += -DLOG_TAG=\"eglCodecCommon\"

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


$(call emugl-export,SHARED_LIBRARIES,libcutils libutils liblog)
$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-end-module)
