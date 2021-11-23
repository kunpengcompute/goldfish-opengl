LOCAL_PATH := $(call my-dir)

$(call emugl-begin-shared-library,libRenderControl_enc)
LOCAL_SRC_FILES := \
    renderControl_client_context.cpp

$(call emugl-export,C_INCLUDES,$(LOCAL_PATH))
$(call emugl-import,libOpenglCodecCommon)
$(call emugl-end-module)
